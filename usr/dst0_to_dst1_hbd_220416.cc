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
  
  //--- define tree ---//
  TFile *fout = new TFile(out_file_name,"recreate");
  TTree *tree = new TTree("tree","tree");

  int event_id;
  int n_hits1;
  int n_hits2;
  int n_clusters1;
  int n_clusters2;
  vector<int> h_hid1;
  vector<int> h_hid2;
  vector<float> h_tdc1;
  vector<float> h_tdc2;
  vector<int> c_cid1;
  vector<int> c_cid2;
  vector<float> c_tdc1;
  vector<float> c_tdc2;
  vector<vector<int>> c_hitmembers1;
  vector<vector<int>> c_hitmembers2;
  
  tree->Branch("event_id", &event_id, "event_id/I");
  tree->Branch("n_hits1", &n_hits1, "n_hits1/I");
  tree->Branch("n_hits2", &n_hits2, "n_hits2/I");
  tree->Branch("n_clusters1", &n_clusters1, "n_clusters1/I");
  tree->Branch("n_clusters2", &n_clusters2, "n_clusters2/I");
  tree->Branch("h_hid1", &h_hid1);
  tree->Branch("h_hid2", &h_hid2);
  tree->Branch("h_tdc1", &h_tdc1);
  tree->Branch("h_tdc2", &h_tdc2);
  tree->Branch("c_cid1", &c_cid1);
  tree->Branch("c_cid2", &c_cid2);
  tree->Branch("c_tdc1", &c_tdc1);
  tree->Branch("c_tdc2", &c_tdc2);
  tree->Branch("c_hitmembers1", &c_hitmembers1);
  tree->Branch("c_hitmembers2", &c_hitmembers2);
  //--- define tree ---//
  
  //--- calibration initialization ---//
  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  
  E16ANA_HBDCalibration *hbd_calib = new E16ANA_HBDCalibration();
  hbd_calib->ReadCalibrationData(calib.CurrentRunID());
  E16ANA_HBDCut *hbd_cut1 = new E16ANA_HBDCut();
  E16ANA_HBDCut *hbd_cut2 = new E16ANA_HBDCut();
  hbd_cut1->ReadCutData(calib.CurrentRunID());
  hbd_cut2->ReadCutData(calib.CurrentRunID());
  hbd_cut2->SetCut("clustering_time_window_start", -10000.);
  hbd_cut2->SetCut("clustering_time_window_end", 10000.);
  E16ANA_WaveformFitterCRRC *wf1d_fitter = new E16ANA_WaveformFitterCRRC();
  //--- calibration initialization ---//

  auto record1 = new E16DST_DST1PhysicsRecord();
  auto record2 = new E16DST_DST1PhysicsRecord();
  
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
      
      //--- 220416 waveform fitting method updated ---//
      E16DST_DST1HBDFactory(hbd_hits0, hbd_calib, hbd_cut1, wf1d_fitter, &record1->HBD()); //clustering w/  tdc selection of 0--100 ns
      E16DST_DST1HBDFactory(hbd_hits0, hbd_calib, hbd_cut2, wf1d_fitter, &record2->HBD()); //clustering w/o tdc selection (-10000--10000 ns)
      //--- 220416 waveform fitting method updated ---//
      
      event_id = event0->EventID();
      
      auto& hbd_dst1hits1 = record1->HBD().Hits();
      auto& hbd_dst1hits2 = record2->HBD().Hits();
      auto& hbd_dst1clusters1 = record1->HBD().Clusters();
      auto& hbd_dst1clusters2 = record2->HBD().Clusters();
      n_hits1 = hbd_dst1hits1.size();
      n_hits2 = hbd_dst1hits2.size();
      n_clusters1 = hbd_dst1clusters1.size();
      n_clusters2 = hbd_dst1clusters2.size();

      for(auto hit : hbd_dst1hits1){
	h_hid1.push_back(hit.HitId());
	h_tdc1.push_back(hit.Timing());
      }
      for(auto hit : hbd_dst1hits2){
	h_hid2.push_back(hit.HitId());
	h_tdc2.push_back(hit.Timing());
      }
      for(auto cluster : hbd_dst1clusters1){
	c_cid1.push_back(cluster.ClusterId());
	c_tdc1.push_back(cluster.Timing());
	vector<int> hitmembers;
	for(auto hit_id : cluster.HitOrders()) hitmembers.push_back((int) hit_id);
	c_hitmembers1.push_back(hitmembers);
      }
      for(auto cluster : hbd_dst1clusters2){
	c_cid2.push_back(cluster.ClusterId());
	c_tdc2.push_back(cluster.Timing());
	vector<int> hitmembers;
	for(auto hit_id : cluster.HitOrders()) hitmembers.push_back((int) hit_id);
	c_hitmembers2.push_back(hitmembers);
      }
      
      tree->Fill();
      
      //clear vector
      h_hid1.clear();
      h_hid2.clear();
      h_tdc1.clear();
      h_tdc2.clear();
      c_cid1.clear();
      c_cid2.clear();
      c_tdc1.clear();
      c_tdc2.clear();
      c_hitmembers1.clear();
      c_hitmembers2.clear();
      
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
