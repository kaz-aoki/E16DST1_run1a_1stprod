#include <iostream>
#include <algorithm>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_Constant.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"

#include "E16ANA_WaveformFitter.hh"
#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDCut.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDChannelManager.hh"
#include "E16ANA_HBDConstant.hh"
#include "E16ANA_HBDClusterAnalysis.hh"

const int n_max_hits = 2000;
const int n_max_clusters = 2000;

int main(int argc, char **argv){

  if( argc != 4 ){
    std::cerr<<"usage: ./exe [input dst0] [run number] [output filename]"<<std::endl;
    return 0;
  }

   std::string input_filename = std::string(argv[1]);
   int runID = atoi(argv[2]);
   std::string output_filename = std::string(argv[3]);
   
   E16DST_DST0 *dst0 = new E16DST_DST0();
   if(!dst0->Open(input_filename, E16DST_DST0::ReadMode)){
     std::cerr<<"cannot open file"<<std::endl;
     return 0;
   }

   auto& calib = E16ANA_CalibDBManager::Instance();
   calib.SetRunID(runID);
   auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
   
   //HBD initialize
   E16ANA_HBDCalibration *hbd_calib = new E16ANA_HBDCalibration();
   hbd_calib->ReadCalibrationData(calib.CurrentRunID());
   E16ANA_HBDCut *hbd_cut = new E16ANA_HBDCut();
   hbd_cut->ReadCutData(calib.CurrentRunID());
   std::string hbd_waveform_template = calib.CalibFileName("HBD-waveform-template", 0);
   E16ANA_WaveformFitter *wf1d_fitter = new E16ANA_WaveformFitter(hbd_waveform_template);

   //----------- const
   int n_modules = E16DST_Constant::NModules;//number of hbd modules
   int n_samples = E16DST_Constant::NSamplesHBD;//number of apv25 samples
   
   int16_t *in_waveform;
   double hout_waveform[n_max_hits][n_samples];
   double hwaveform_max[n_max_hits];
   int hmid[n_max_hits]; //module id
   int hpid[n_max_hits]; //pad id
   double hlpos[n_max_hits][3];
   double htiming[n_max_hits];
   double hpeak[n_max_hits];
   double hpe[n_max_hits];
   double hchi2[n_max_hits];
   bool is_dst0hit;
   int dst1_hid = 0;
   int n_hits;
   
   int cmid[n_max_clusters];
   double ccharge[n_max_clusters];
   int csize[n_max_clusters];
   double ctiming[n_max_clusters];
   double ctimediff[n_max_clusters];
   double clpos[n_max_clusters][3];
   int dst1_cid = 0;
   int n_clusters;
   
   //----------- get gain calibration status
   bool gain_calibration_status = hbd_calib->GetGainCalibrationStatus();//true: normal operation, false: low gain

   //----------- get cut criteria
   double n_sigma = hbd_cut->GetNSigmaWfDST1();//dst0 hit discard criterion, adc noise*n_sigma
   int n_waves = hbd_cut->GetNWavesDST1(); //number of acceptable waves in each waveform
   int th_csize = hbd_cut->GetThCSizeDST1(); //required cluster size for an electron candidate
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
   
   //-----------
   TFile *f = new TFile(output_filename.c_str(), "recreate");
   TTree *tree = new TTree("tree", "tree");

   tree->Branch("n_hhits", &n_hits, "n_hhits/I");
   tree->Branch("n_chits", &n_clusters, "n_chits/I");

   tree->Branch("hwaveform", hout_waveform, Form("hwaveform[n_hits][%d]/D", n_samples));
   tree->Branch("hwaveform_max", hwaveform_max, "hwaveform_max[n_hits]/D");
   tree->Branch("hmid", hmid, "hmid[n_hits]/I");
   tree->Branch("hpid", hpid, "hpid[n_hits]/I");
   tree->Branch("hlpos", hlpos, "hlpos[n_hits][3]/D");
   tree->Branch("htiming", htiming, "htiming[n_hits]/D");
   tree->Branch("hpeak", hpeak, "hpeak[n_hits]/D");
   tree->Branch("hpe", hpe, "hpe[n_hits]/D");
   tree->Branch("hchi2", hchi2, "hchi2[n_hits]/D");
   
   tree->Branch("cmid", cmid, "cmid[n_clusters]/I");
   tree->Branch("ccharge", ccharge, "ccharge[n_clusters]/D");
   tree->Branch("csize", csize, "csize[n_clusters]/I");
   tree->Branch("ctiming", ctiming, "ctiming[n_clusters]/D");
   tree->Branch("ctimediff", ctimediff, "ctimediff[n_clusters]/D");
   tree->Branch("clpos", clpos, "clpos[n_clusters][3]/D");
   
   //---------------------------------------------------------------------------

   //event loop
   int n_read_event = 0;
   E16DST_DST0PhysicsEvent *phys_event;
   E16DST_DST0Detector<E16DST_DST0HBDHit> dst0_hits;
   int hid = 0;
   int cid = 0;
   while(dst0->ReadAnEvent() > 0){
     if(n_read_event >= 1000) break;
     //if(n_read_event%1000 == 0) std::cerr<<"n events read: "<<n_read_event<<std::endl;
     
     //std::cerr<<n_read_event<<" th event"<<std::endl;
     if(dst0->EventType() != E16DST_DST0EventType::Physics){
       continue;
     }
     phys_event = dynamic_cast<E16DST_DST0PhysicsEvent *>(dst0->Event());
     if(phys_event == nullptr){
       continue;
     }
     dst0_hits = phys_event->HBD();
     dst1_hid = 0;
     dst1_cid = 0;
     for(int i=0; i<dst0_hits.NumberOfHits(); i++){
       E16DST_DST0HBDHit dst0_hit = dst0_hits.Hit(i);
       in_waveform = dst0_hit.Waveform();
       uint32_t tdc = dst0_hit.TDC();
       int mid = dst0_hit.ModuleID();
       int pid = dst0_hit.ChannelID();
       double out_waveform[n_samples];
       hbd_calib->GetCalibratedSignal(mid, pid, in_waveform, out_waveform);
       is_dst0hit = hbd_calib->HitDecision(mid, pid, out_waveform, n_sigma);

       if(is_dst0hit
	  && ((hbd_calib->GetGain(mid, pid) == 0. && !gain_calibration_status) ||
	      (hbd_calib->GetGain(mid, pid) >  0. &&  gain_calibration_status))
	  && hbd_calib->GetDeadChannel()->IsOK(mid, pid)
	  ){/* dst0 hit is mandatry.
	       and
	       (gain calibration not performed || gain value is correct && gain calibration performed)
	       and
	       not dead ch */
	 hmid[dst1_hid] = mid;
	 hpid[dst1_hid] = pid;
	 for(int j=0; j<n_samples; j++){ hout_waveform[dst1_hid][j] = out_waveform[j]; } 
	 wf1d_fitter->SetNoiseSigma(hbd_calib->GetNoise(mid, pid));
	 wf1d_fitter->SetWaveform(out_waveform, n_samples);
	 wf1d_fitter->Fit();
	 
	 double t0 = wf1d_fitter->GetWaveformTime(0);
	 hpeak[dst1_hid] = wf1d_fitter->GetWaveformPeak(0);
	 
	 htiming[dst1_hid] = wf1d_fitter->GetTimeOverThreshold(0, 0.5);
	 hpe[dst1_hid] = hpeak[dst1_hid]*hbd_calib->GetGain(hmid[dst1_hid], hpid[dst1_hid]);
	 double par[2] = {hpeak[dst1_hid], t0};
	 hchi2[dst1_hid] = wf1d_fitter->MinuitFunction(par);
	 hwaveform_max[dst1_hid] = *std::max_element(hout_waveform[dst1_hid], hout_waveform[dst1_hid]+n_samples);
	 E16ANA_HBDGeometry::GetPadLocalCOG(mid, pid, hlpos[dst1_hid]);
	 cs.at(E16ANA_HBDChannelManager::ConvMIDE16ToK(mid)).SetData(mid, pid, hpeak[dst1_hid], hpe[dst1_hid], htiming[dst1_hid], dst1_hid);
	 dst1_hid++;
       }
     }
     
     for(auto p : cs){
       p.DoClustering();
       std::vector<E16ANA_HBDClusterAnalysis::hbd_cluster> clusters = p.GetClusters();
       for(auto cl : clusters){
	 cmid[dst1_cid] = cl.module_id;
	 ccharge[dst1_cid] = cl.sadc;
	 csize[dst1_cid] = cl.size;
	 ctiming[dst1_cid] = cl.average_time;
	 ctimediff[dst1_cid] = cl.time_diff;
	 for(int i=0; i<3; i++){ clpos[dst1_cid][i] = cl.lpos_w_pe[i]; }
	 dst1_cid++;
       }
     }
     
     n_hits = dst1_hid;
     n_clusters = dst1_cid;
     tree->Fill();
     n_read_event++;
   }
   //event loop
  //---------------------------------------------------------------------------

   tree->Write();
   f->Close();
   
   return 0;
}
