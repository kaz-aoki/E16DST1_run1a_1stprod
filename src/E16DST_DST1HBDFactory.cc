#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_WaveformFitter.hh"
#include "E16DST_DST1.hh"
#include "E16DST_Constant.hh"

#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDCut.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDChannelManager.hh"
#include "E16ANA_HBDConstant.hh"
#include "E16ANA_HBDClusterAnalysis.hh"

#include "TVector3.h"

int E16DST_DST1HBDFactory(E16DST_DST0Detector<E16DST_DST0HBDHit>& dst0_hits,
  E16ANA_HBDCalibration *hbd_calib,
  E16ANA_HBDCut *hbd_cut,
  E16ANA_WaveformFitter *wf1d_fitter,
  E16DST_DST1Detector<E16DST_DST1HBDHit, E16DST_DST1HBDCluster>* hbd1)
{
  auto& dst1_hits = hbd1->Hits();
  auto& dst1_clusters = hbd1->Clusters();
  
  dst1_hits.resize(dst0_hits.NumberOfHits()*2.);
  dst1_clusters.resize(dst0_hits.NumberOfHits());
  
  //----------- const
  int n_modules = E16DST_Constant::NModules;//number of hbd modules
  int n_samples = E16DST_Constant::NSamplesHBD;//number of apv25 samples
  
  //----------- local variablus
  int16_t *in_waveform;
  double out_waveform[n_samples];
  int mid; //module id
  int pid; //pad id
  double lpos[3];
  bool is_dst0hit;
  double timing;
  double peak;
  double pe;
  double chi2;
  int dst1_hid = 0;
  int dst1_cid = 0;
  
  //----------- get calib manager
  auto &calib = E16ANA_CalibDBManager::Instance();

  //----------- get cut criteria
  //std::string hbd_cut_filename = calib.CalibFileName("HBD-cut", 0);
  //E16ANA_HBDCut hbd_cut;
  //hbd_cut.ReadFile(hbd_cut_filename.c_str());
  double n_sigma = hbd_cut->GetNSigmaWfDST1();//dst0 hit discard criterion
  int n_waves = hbd_cut->GetNWavesDST1(); //number of acceptable waves in each waveform
  int th_csize = hbd_cut->GetThCSizeDST1(); //required cluster size for an electron candidate
  double th_ccharge = hbd_cut->GetThCChargeDST1(); //required cluster charge for an electron candidate
  double n_sigma_cadc = hbd_cut->GetNSigmaCADCDST1(); //required cluster adc for a charged particle
  
  //----------- prepare for waveform fit
  //std::string hbd_waveform_template = calib.CalibFileName("HBD-waveform-template", 0);
  //E16ANA_WaveformFitter wf1d_fitter(hbd_waveform_template);
  wf1d_fitter->SetNumWaveforms(n_waves);
  wf1d_fitter->SetClockPeriod(HBD_Circuit_Constant::apv25_period);

  //prepare for clustering
  std::vector<E16ANA_HBDClusterAnalysis> cs;
  cs.resize(n_modules);
  for(int i=0; i<n_modules; i++){
    cs.at(i).SetModuleID(E16ANA_HBDChannelManager::ConvMIDKToE16(i));
  }
  //prepare for clustering
  
  for(int ith_dst0hit = 0; ith_dst0hit < dst0_hits.NumberOfHits(); ith_dst0hit++){
    E16DST_DST0HBDHit dst0_hit = dst0_hits.Hit(ith_dst0hit);
    in_waveform = dst0_hit.Waveform();
    mid = dst0_hit.ModuleID();
    pid = dst0_hit.ChannelID();
    hbd_calib->GetCalibratedSignal(mid, pid, in_waveform, out_waveform);
    is_dst0hit = hbd_calib->HitDecision(mid, pid, out_waveform, n_sigma);
    
    if(is_dst0hit && hbd_calib->GetGain(mid, pid) > 0.){// gain < 0. happens when gain calib. is wrong or dead channel
      E16DST_DST1HBDHit &dst1_hit = dst1_hits[dst1_hid];
      wf1d_fitter->SetNoiseSigma(hbd_calib->GetNoise(mid, pid));//noise of first sampling point, can be optimized
      wf1d_fitter->SetWaveform(out_waveform, n_samples);
      wf1d_fitter->Fit();
      
      double t0 = wf1d_fitter->GetWaveformTime(0);
      //----this template fit seem to underestimte the peak height
      peak = wf1d_fitter->GetWaveformPeak(0);//in units of adc
      //----should be modified
      
      timing = wf1d_fitter->GetTimeOverThreshold(0, 0.5);//only one wave is accepted
      pe = peak*hbd_calib->GetGain(mid, pid);
      double par[2] = {peak, t0};
      chi2 = wf1d_fitter->MinuitFunction(par);
      
      dst1_hit.SetInvalid();
      dst1_hit.SetIds(mid, pid);
      dst1_hit.SetChi2(chi2);
      dst1_hit.SetPeakHeight(pe);//peak should be expressed in units of p.e.
      dst1_hit.SetTiming(timing);//50% of maximum peak height
      dst1_hit.SetLocalPos(E16ANA_HBDGeometry::GetPadLocalCOG(mid, pid));
      cs.at(E16ANA_HBDChannelManager::ConvMIDE16ToK(mid)).SetData(mid, pid, peak, pe, timing, dst1_hid);
      dst1_hid++;

    }
  }
  
  for(auto p : cs){
    p.DoClustering();
    std::vector<E16ANA_HBDClusterAnalysis::hbd_cluster> clusters = p.GetClusters();
    for(auto cl : clusters){
      double e_prob = 0.;
      double c_prob = 0.;
      E16DST_DST1HBDCluster &dst1_cl = dst1_clusters[dst1_cid];
      dst1_cl.SetInvalid();
      dst1_cl.SetModuleId(cl.module_id);
      dst1_cl.SetMaxPeakCh(cl.max_pe_id);
      dst1_cl.SetMaxPeakHeight(cl.max_pe);
      dst1_cl.SetTiming(cl.average_time);
      dst1_cl.SetPeakSum(cl.spe);
      dst1_cl.SetSADC(cl.sadc);
      dst1_cl.SetHitOrders(cl.dst_id);
      
      dst1_cl.SetFastestTiming(cl.fastest_tdc);
      dst1_cl.SetTimeDifference(cl.time_diff);
      dst1_cl.SetClusterSize(cl.size);
      if(cl.spe >= th_ccharge && cl.size >= th_csize) e_prob = 1.;
      dst1_cl.SetEProb(e_prob);

      std::vector<int> id = cl.id;
      double th_cadc = 0.;
      for(auto p : id){
	th_cadc += std::pow(hbd_calib->GetNoise(cl.module_id, p), 2.);
      }
      th_cadc = std::sqrt(th_cadc);
      if(th_cadc*n_sigma_cadc <= cl.sadc) c_prob = 1.; 
      dst1_cl.SetCProb(c_prob);
      TVector3 lpos;
      if(hbd_calib->GetGainCalibrationStatus()){//gain calib normal operation
	lpos = TVector3(cl.lpos_w_pe[0], cl.lpos_w_pe[1], cl.lpos_w_pe[2]);
      }else{//gain calib not done, low-gain operation
	lpos = TVector3(cl.lpos_w_adc[0], cl.lpos_w_adc[1], cl.lpos_w_adc[2]);
      }
      TVector3 lpos_adc(cl.lpos_w_adc[0], cl.lpos_w_adc[1], cl.lpos_w_adc[2]);
      dst1_cl.SetLocalPos(lpos);
      dst1_cl.SetLocalPosWADC(lpos_adc);
      
      dst1_cid++;
    }
  }
  
  dst1_hits.resize(dst1_hid);
  dst1_clusters.resize(dst1_cid);
  
  return sizeof(E16DST_DST1HBDHit)*dst1_hid + sizeof(E16DST_DST1HBDCluster)*dst1_cid;
}
