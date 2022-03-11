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
#include "E16ANA_HBDDeadChannel.hh"

#include "TVector3.h"

//------------------------------------------------------------
#include <fstream>
//------------------------------------------------------------

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
  uint32_t tdc_diff;
  int dst1_hid = 0;
  int dst1_cid = 0;
  
  //----------- get gain calibration status
  bool gain_calibration_status = hbd_calib->GetGainCalibrationStatus();//true: normal operation, false: low gain

  //----------- get cut criteria
  double n_sigma = hbd_cut->GetNSigmaWfDST1();//dst0 hit discard criterion, adc noise*n_sigma
  int n_waves = hbd_cut->GetNWavesDST1(); //number of acceptable waves in each waveform
  int th_csize = hbd_cut->GetThCSizeDST1(); //required cluster size for an electron candidate
  double th_wf_chi2 = hbd_cut->GetThWaveformChi2(); //required chi2(not divided by ndf) for hbd hit waveform
  double th_ccharge = hbd_cut->GetThCChargeDST1(); //required cluster charge for an electron candidate
  double n_sigma_cadc = hbd_cut->GetNSigmaCADCDST1(); //required cluster adc for a charged particle
  
  //----------- prepare for waveform fit
  wf1d_fitter->SetNumWaveforms(n_waves);
  wf1d_fitter->SetClockPeriod(HBD_Circuit_Constant::apv25_period);

  //----------- prepare for clustering
  std::vector<E16ANA_HBDClusterAnalysis> cs;
  cs.resize(n_modules);
  for(int i=0; i<n_modules; i++){
    cs.at(i).SetModuleID(E16ANA_HBDChannelManager::ConvMIDKToE16(i));
  }
  
  for(int ith_dst0hit = 0; ith_dst0hit < dst0_hits.NumberOfHits(); ith_dst0hit++){
    E16DST_DST0HBDHit dst0_hit = dst0_hits.Hit(ith_dst0hit);
    in_waveform = dst0_hit.Waveform();
    mid = dst0_hit.ModuleID();
    pid = dst0_hit.ChannelID();
    tdc_diff = dst0_hit.TDC();
    hbd_calib->GetCalibratedSignal(mid, pid, in_waveform, out_waveform);
    is_dst0hit = hbd_calib->HitDecision(mid, pid, out_waveform, n_sigma);
    
    //std::cout<<"IN FACTORY OF HBD: "<<mid<<" "<<pid<<" "<<is_dst0hit<<" "<<hbd_calib->GetGain(mid, pid)<<" "<<gain_calibration_status<<" "<<hbd_calib->GetDeadChannel()->IsOK(mid, pid)<<std::endl;//nakasuga
    
    if(is_dst0hit
       && ((hbd_calib->GetGain(mid, pid) == 0. && !gain_calibration_status) ||
	   (hbd_calib->GetGain(mid, pid) >  0. &&  gain_calibration_status))
       && hbd_calib->GetDeadChannel()->IsOK(mid, pid)
       ){/* dst0 hit is mandatry.
	    and
	    (gain calibration not performed || gain value is correct && gain calibration performed)
	    and
	    not dead ch */
      E16DST_DST1HBDHit &dst1_hit = dst1_hits[dst1_hid];
      wf1d_fitter->SetNoiseSigma(hbd_calib->GetNoise(mid, pid));//noise of first sampling point, can be optimized
      wf1d_fitter->SetWaveform(out_waveform, n_samples);
      wf1d_fitter->Fit();
      
      double t0 = wf1d_fitter->GetWaveformTime(0);
      //----this template fit seem to underestimte the peak height
      peak = wf1d_fitter->GetWaveformPeak(0);//in units of adc
      //----should be modified
      
      timing = wf1d_fitter->GetTimeOverThreshold(0, 0.5);//only one wave is accepted
      timing = timing + tdc_diff*HBD_Circuit_Constant::SRS_ATCA_TDC;//add delay between B2TT trig. and SRS ATCA trig.
      pe = peak*hbd_calib->GetGain(mid, pid);
      double par[2] = {peak, t0};
      chi2 = wf1d_fitter->MinuitFunction(par);
      
      dst1_hit.SetInvalid();
      dst1_hit.SetIds(mid, pid);
      dst1_hit.SetHitId(dst1_hid);
      dst1_hit.SetChi2(chi2);
      if(gain_calibration_status){
	dst1_hit.SetPeakHeight(pe);//peak should be expressed in units of p.e.
      }else{
	dst1_hit.SetPeakHeight(peak);
      }
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
      dst1_cl.SetClusterId(dst1_cid);
      dst1_cl.SetModuleId(cl.module_id);
      dst1_cl.SetMaxPeakCh(cl.max_pe_id);
      dst1_cl.SetMaxPeakHeight(cl.max_pe);
      dst1_cl.SetTiming(cl.average_time);
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
      if(gain_calibration_status){//gain calib normal operation
	lpos = TVector3(cl.lpos_w_pe[0], cl.lpos_w_pe[1], cl.lpos_w_pe[2]);
	dst1_cl.SetPeakSum(cl.spe);
      }else{//gain calib not done, low-gain operation
	lpos = TVector3(cl.lpos_w_adc[0], cl.lpos_w_adc[1], cl.lpos_w_adc[2]);
	dst1_cl.SetPeakSum(cl.sadc);
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
