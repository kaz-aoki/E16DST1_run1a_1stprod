#include <stdlib.h>
#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "GTR/GTRCheckHist.hh"
#include "E16ANA_TargetInfo.hh"
#include "E16ANA_RundependentName.hh"
#include "straight_track/StraightTrackAnalyzerV0.h"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16ANA_GTRStatus.h"
#include "E16ANA_GTRChannelManager.h"
#include "E16ANA_GTRAnalyzerMaker.hh"
#include "E16ANA_GTRAnalyzer2.h"
#include "E16ANA_GTRStripAnalyzer.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [output.dst1] [run ID] [max physics event (all: -1)] " << endl;
    return 1;
  }
   auto dst0 = new E16DST_DST0();
  if (!dst0->Open(argv[1], E16DST_DST0::ReadMode)) {
    std::cout << "failed to open file : " << argv[1]  <<std::endl;
	exit(1);
//    return 1;
  }
  string in_file_name = argv[1];
  int sink_id_pos = in_file_name.length() - 10;
  string sink_id = in_file_name.substr(sink_id_pos, 1);
  std::cout << "sink id = " << sink_id << std::endl;
  int smallest_id_pos = in_file_name.length()-8;
  string smallest_id = in_file_name.substr(smallest_id_pos, 3);
  std::cout << "smallest  id = " << smallest_id << std::endl;
  string runnum = argv[3];
  string run = "g4run0" + runnum;
  string outputfile = "./dst1_test/" + run + "_sink" + sink_id +"_"+ smallest_id+".root";

  const char* c_out = outputfile.c_str();
  auto out_file_name = argv[2];
  auto run_id        = stoi(argv[3]);
  auto max_event     = stoi(argv[4]);
  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  auto trigger_param = new E16ANA_TriggerCalibParam();
  trigger_param->ReadConstantData(calib.CurrentRunID());
  E16ANA_GTRcalibPedestal gtrped;
  gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_TargetInfoManager& targets = E16ANA_TargetInfoManager::Instance();
  targets.ReadInfoWithRunID( calib.CurrentRunID());
  targets.Print();
  E16ANA_GTRLorentzAngleCalibParamManager gtr_lorentz_angle_calib_param_manager;
  gtr_lorentz_angle_calib_param_manager.ReadConstantData(calib.CurrentRunID());
  auto gtr_lorentz_angle_calib_params = gtr_lorentz_angle_calib_param_manager.GTRLorentzAngleCalibParams();
  auto record = new E16DST_DST1PhysicsRecord();
  auto geom = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  auto *gtrhist = new GTRCheckHist();
  auto gtr_status = new E16ANA_GTRStatus(calib.CurrentRunID());
  
  E16ANA_GTRcalibParams gtr_params;
  gtr_params.ReadCalibData(calib.CurrentRunID());
  E16ANA_GTRAnalyzerMaker *gtr_analyzers = new E16ANA_GTRAnalyzerMaker(gtr_params);
  for(int mid=100; mid <=110; mid++){
  	 for(int lid = 0; lid < 3; lid++){
       E16ANA_GTRAnalyzer2 *analyzer = gtr_analyzers->Chamber(mid, lid);
	   int n_strips = analyzer->GetNumberOfStrips();
	   for(int strip_id = 0; strip_id < n_strips; strip_id++){
                    double ped = gtrped.GetPedestal(mid, lid, strip_id).Value();
                    double sigma = gtrped.GetPedestal(mid, lid, strip_id).Sigma();
                    analyzer->SetPedestal(strip_id, ped);
                    analyzer->SetPedestalSigma(strip_id, sigma);
                }
	 }
  }
  //auto asd_dead = gtr_status->ASDDeadChannel();
//  gtr_status->ASDDeadChannel()->ReadDeadChannelData( calib.CurrentRunID());
  for (int m=101; m< 110; m++){
	for(int ch=0; ch < 24; ch++){
 		std::cout << "GEM Status : module = " << m << ", ch = " << ch << ", gtr_dead " <<  gtr_status->GEMDeadArea300()->IsYOK(m, ch) << std::endl;
	}
  }
  std::cout << "Is X GEM OK  == " << gtr_status->GEMDeadArea300()->IsXOK(106, 13.2) << std::endl;//GEM  
  std::cout << "apv ch convorotor returns   == " << E16ANA_GTRChannelManager::ConvLocalXToAPVch(0, 0.2) << std::endl;//
  int apv_ch = E16ANA_GTRChannelManager::ConvLocalXToAPVch(0, 12);//(gtr_size, local_pos[mm])
  std::cout << "is bad apv ? : "  << gtr_analyzers->Chamber(106, 1)->GetStripX()->IsBadStrip(apv_ch) << std::endl;
  
  
//  int n_event = 0;
//  int n_physics_event = 0;
//  std::cout << "here " << std::endl;
//  while (dst0->ReadAnEvent()) {
//    if (max_event != -1 && n_event >= max_event) {
//      break;
//    }
//    if (n_event % 100 == 0) {
//      cout << "Number of event: " << n_event << endl;
//    }
//    if (dst0->EventType() != E16DST_DST0EventType::Physics){
//        std::cout << "Event ID = " << dst0->Event()->EventID() << " is not Physics Event, Event Type =" << dst0->Event()->EventType() << std::endl;
//        continue;
//    }
////
//	
////	if(st_tracks.size() != 0)std::cout << "st_tracks size =  " << st_tracks.size() << std::endl;
////	gtrhist->Fill(st_tracks);
////	gtrhist->Fill();	
//    ++n_event;
//    ++n_physics_event;
//  }
//
 
  return 0;
}
