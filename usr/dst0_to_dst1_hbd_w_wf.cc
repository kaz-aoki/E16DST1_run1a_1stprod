#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TInterpreter.h>
//#include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_Constant.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"

#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"

#include "E16ANA_WaveformFitter.hh"
#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDCut.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDChannelManager.hh"
#include "E16ANA_HBDConstant.hh"
#include "E16ANA_HBDClusterAnalysis.hh"

#include "E16ANA_GTRcalib.hh"
#include "GTR/GTRCheckHist.hh"
#include "E16ANA_TargetInfo.hh"

using namespace std;

int main(int argc, char* argv[]) {
  
  gInterpreter->GenerateDictionary("vector<vector<int>>; vector<vector<double>>", "vector");
  
  if (argc != 5) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [output.dst1] [run ID] [max physics event (all: -1)] " << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto run_id        = stoi(argv[3]);
  auto max_event     = stoi(argv[4]);
//  bpo::variables_map vm;
//  string in_file_name;
//  string out_file_name;
//  int run_num;
  
  
  TFile *fout = new TFile(out_file_name,"recreate");
  TTree *tree = new TTree("tree","tree");

  int event_id;
  int n_hits;
  int n_clusters;
  
  vector<int> h_hid;
  vector<int> h_mid;
  vector<int> h_ch; 
  vector<float> h_chi2;
  vector<float> h_pe;
  vector<float> h_tdc;
  vector<float> h_lpos_x;
  vector<float> h_lpos_y;
  vector<float> h_lpos_z;
  vector<vector<double>> h_wf;

  vector<int> c_cid;
  vector<int> c_mid;
  vector<int> c_maxch;
  vector<int> c_maxheight;
  vector<float> c_sadc;
  vector<float> c_tdc;
  vector<float> c_pe;
  vector<float> c_tdc_fastest;
  vector<float> c_tdc_diff;
  vector<int> c_size;
  vector<float> c_lpos_x;
  vector<float> c_lpos_y;
  vector<float> c_lpos_z;
  vector<vector<int>> c_hitmembers;
  vector<float> c_cprob;
  vector<float> c_eprob;

  tree->Branch("event_id", &event_id, "event_id/I");
  tree->Branch("n_hits", &n_hits, "n_hits/I");
  tree->Branch("n_clusters", &n_clusters, "n_clusters/I");
  
  tree->Branch("h_hid", &h_hid);
  tree->Branch("h_mid", &h_mid);
  tree->Branch("h_ch", &h_ch);
  tree->Branch("h_chi2", &h_chi2);
  tree->Branch("h_pe", &h_pe);
  tree->Branch("h_tdc", &h_tdc);
  tree->Branch("h_lpos_x", &h_lpos_x);
  tree->Branch("h_lpos_y", &h_lpos_y);
  tree->Branch("h_lpos_z", &h_lpos_z);
  tree->Branch("h_wf", &h_wf);
  
  tree->Branch("c_cid", &c_cid);
  tree->Branch("c_mid", &c_mid);
  tree->Branch("c_maxch", &c_maxch);
  tree->Branch("c_maxheight", &c_maxheight);
  tree->Branch("c_sadc", &c_sadc);
  tree->Branch("c_tdc", &c_tdc);
  tree->Branch("c_pe", &c_pe);
  tree->Branch("c_tdc_fastest", &c_tdc_fastest);
  tree->Branch("c_tdc_diff", &c_tdc_diff);
  tree->Branch("c_size", &c_size);
  tree->Branch("c_lpos_x", &c_lpos_x);
  tree->Branch("c_lpos_y", &c_lpos_y);
  tree->Branch("c_lpos_z", &c_lpos_z);
  tree->Branch("c_hitmembers", &c_hitmembers);
  tree->Branch("c_cprob", &c_cprob);
  tree->Branch("c_eprob", &c_eprob);
  
  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  
  //HBD initialize
  E16ANA_HBDCalibration *hbd_calib = new E16ANA_HBDCalibration();
  hbd_calib->ReadCalibrationData(calib.CurrentRunID());
  E16ANA_HBDCut *hbd_cut = new E16ANA_HBDCut();
  hbd_cut->ReadCutData(calib.CurrentRunID());
  std::string hbd_waveform_template = calib.CalibFileName("HBD-waveform-template", 0);
  E16ANA_WaveformFitter *wf1d_fitter = new E16ANA_WaveformFitter(hbd_waveform_template);
  
  auto record = new E16DST_DST1PhysicsRecord();
  
  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }

  int n_event = 0;
  int n_physics_event = 0;
  while (dst0->ReadAnEvent()) {
    if (max_event != -1 && n_physics_event >= max_event) {
      break;
    }
    if (n_event % 1000 == 0) {
      cout << "Number of event: " << n_event << endl;
    }
    auto event_type = dst0->EventType();
    ////////    dst1->SetEventType(event_type);
    if (event_type == E16DST_DST0EventType::Physics) {
      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
      E16DST_DST0Detector<E16DST_DST0HBDHit> hbd_hits0 = event0->HBD();
      
      E16DST_DST1HBDFactory(hbd_hits0, hbd_calib, hbd_cut, wf1d_fitter, &record->HBD());
      event_id = event0->EventID();
      
      auto& hbd_hits1 = record->HBD().Hits();
      auto& hbd_clusters1 = record->HBD().Clusters();
      n_hits = hbd_hits1.size();
      n_clusters = hbd_clusters1.size();
      
      for(auto hit : hbd_hits1){
	h_hid.push_back(hit.HitId());
	h_mid.push_back(hit.ModuleId());
	h_ch.push_back(hit.ChannelId());
	h_chi2.push_back(hit.Chi2());
	h_pe.push_back(hit.PeakHeight());
	h_tdc.push_back(hit.Timing());
	h_lpos_x.push_back(hit.LocalPos(*geometry).X());
	h_lpos_y.push_back(hit.LocalPos(*geometry).Y());
	h_lpos_z.push_back(hit.LocalPos(*geometry).Z());
	
	for(int ith_dst0hit =0; ith_dst0hit < hbd_hits0.NumberOfHits(); ith_dst0hit++){
	  E16DST_DST0HBDHit dst0_hit = hbd_hits0.Hit(ith_dst0hit);
	  if(dst0_hit.ModuleID() == hit.ModuleId()){
	    if(dst0_hit.ChannelID() == hit.ChannelId()){
	      int16_t *in_wf = dst0_hit.Waveform();
	      double out_wf[E16DST_Constant::NSamplesHBD];
	      vector<double> out_wf_vector;
	      hbd_calib->GetCalibratedSignal(hit.ModuleId(), hit.ChannelId(), in_wf, out_wf);
	      for(int i=0; i<E16DST_Constant::NSamplesHBD; i++) out_wf_vector.push_back(out_wf[i]);
	      out_wf_vector.resize(E16DST_Constant::NSamplesHBD);
	      h_wf.push_back(out_wf_vector);
	    }
	  }
	}
      }
      h_wf.resize(n_hits);
      
      for(auto cluster : hbd_clusters1){
	c_cid.push_back(cluster.ClusterId());
	c_mid.push_back(cluster.ModuleId());
	c_maxch.push_back(cluster.MaxPeakCh());
	c_tdc.push_back(cluster.Timing());
	c_sadc.push_back(cluster.SADC());
	c_tdc_fastest.push_back(cluster.FastestTiming());
	c_tdc_diff.push_back(cluster.TimeDifference());
	c_size.push_back(cluster.ClusterSize());
	c_pe.push_back(cluster.PeakSum());
	c_lpos_x.push_back(cluster.LocalPos().X());
	c_lpos_y.push_back(cluster.LocalPos().Y());
	c_lpos_z.push_back(cluster.LocalPos().Z());
	c_cprob.push_back(cluster.IsChargedParticle());
	c_eprob.push_back(cluster.IsE());

	vector<int> hitmembers;
	for(auto hit_id : cluster.HitOrders()) hitmembers.push_back((int) hit_id);
	hitmembers.resize(cluster.ClusterSize());
	c_hitmembers.push_back(hitmembers);
      }
      c_hitmembers.resize(n_clusters);
      
      tree->Fill();
      
      //clear vector
      h_hid.clear();
      h_mid.clear();
      h_ch.clear();
      h_chi2.clear();
      h_pe.clear();
      h_tdc.clear();
      h_lpos_x.clear();
      h_lpos_y.clear();
      h_lpos_z.clear();
      h_wf.clear();
      
      c_cid.clear();
      c_mid.clear();
      c_maxch.clear();
      c_tdc.clear();
      c_sadc.clear();
      c_tdc_fastest.clear();
      c_tdc_diff.clear();
      c_size.clear();
      c_pe.clear();
      c_lpos_x.clear();
      c_lpos_y.clear();
      c_lpos_z.clear();
      c_cprob.clear();
      c_eprob.clear();
      c_hitmembers.clear();
      
    } else if (event_type == E16DST_DST0EventType::Scaler) {
      auto event0 = dynamic_cast<E16DST_DST0ScalerEvent*>(dst0->Event());
//      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillStart) {
      auto event0 = dynamic_cast<E16DST_DST0SpillStartEvent*>(dst0->Event());
//      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillEnd) {
      auto event0 = dynamic_cast<E16DST_DST0SpillEndEvent*>(dst0->Event());
//      dst1->WriteAnEvent(event0);
    } else {
      std::cerr << "Invalid Event Type: " << event_type << std::endl;
      return -1;
    }
    ++n_event;
    ++n_physics_event;
  }

  fout->Write();
  fout->Close();

  delete dst0;
  return 0;
}
