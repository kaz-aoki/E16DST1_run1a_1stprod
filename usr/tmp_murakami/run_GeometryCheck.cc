#include <iostream>
#include <TROOT.h>
#include <TStyle.h>
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
//#include <boost/program_options.hpp>

#include "E16ANA_GeometryV2.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1DefaultFilePath.hh"
//#include "E16ANA_GTRcalib.hh"
//#include "E16ANA_TriggerCalib.hh"
//#include "E16DST_DST0.hh"
//#include "E16DST_DST1.hh"
//#include "E16DST_DST1DefaultFilePath.hh"
//#include "E16DST_DST1DetectorFactory.hh"
#include "E16ANA_TrackConstant.hh"

using namespace std;
//namespace  bpo = boost::program_options;

int main(int argc, char* argv[]) {
//  if (argc != 5) {
//    cerr << "Invalid argc: " << argc << endl;
////    cerr << "./bin [input.dst0] [output.dst1] [run ID] [max physics event (all: -1)] " << endl;
//    return -1;
//  }
//  auto in_file_name  = argv[1];
//  auto out_file_name = argv[2];
//  auto run_id        = stoi(argv[3]);
//  auto max_event     = stoi(argv[4]);
//
//  TFile *fout = new TFile(out_file_name,"recreate");


//	auto record = new E16DST_DST1PhysicsRecord();
//	auto *gtrhist = new GTRCheckHist();
	auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
	cout << "Read Geometry :: " << static_cast<std::string>(GeometryFile) << endl;
	E16ANA_GeometryV2::SetGlobalPointer(geometry);
//	auto dst0 = new E16DST_DST0();
// 	if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
//		std::cerr << "### Cannot open file ###" << std::endl;
//		return -1;
//	}

//	int n_event = 0;
//	int n_physics_event = 0;
//	int print_cycle = 100;
	TVector3 lpos = {30, 0.0, 0.0};
	TVector3 gpos;
//	int mid2020[10] = {100, 101, 102, 103, 104, 105, 106, 107, 108, 109};//example	
	int mid2020 = 106;//example
	int mid2013 = E16ANA_TrackConstant::ModuleID2020To2013(mid2020);	
	gpos = geometry->STS(mid2013)->GetGPos(lpos);
	std::cout << "GPos : " << std::endl;
	gpos.Print();
	
	
	
//  while (dst0->ReadAnEvent()) {
//    if (max_event != -1 && n_event >= max_event) {
//      break;
//    }
//    if (n_event % print_cycle == 0) {
//      cout << "NReadEvents =  " << n_event  << ", EventID = " << dst0->Event()->EventID() << endl;
//    }
//    if (dst0->EventType() != E16DST_DST0EventType::Physics){
//        std::cout << "Event ID = " << dst0->Event()->EventID() << " is not Physics Event, Event Type =" << dst0->Event()->EventType() << std::endl;
//        continue;
//    }
//    
//    auto event_type = dst0->EventType();
//      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
//      auto& ssd_hits0         = event0->SSD();
//		auto& sts_hits0         = event0->STS();
//      auto& gtr_hits0         = event0->GTR();
//      auto& hbd_hits0         = event0->HBD();
//      auto& lg_hits0          = event0->LG();
//      auto& trigger_gtr_hits0 = event0->TriggerGTR();
//      auto& trigger_hbd_hits0 = event0->TriggerHBD();
//      auto& trigger_lg_hits0  = event0->TriggerLG();
////      E16DST_DST0Detector<E16DST_DST1GTRHit> gtr_hits;
////      E16DST_DST0Detector<E16DST_DST1GTRCluster> gtr_clusters;
////      auto& gtr_hits = record->GTR().Hits();
//      auto& gtr_clusters = record->GTR().Clusters();
////      E16DST_DST1SSDFactory(ssd_hits0, &event1->SSDHits(), &event1->SSDClusters());
//	  E16DST_DST1GTRFactory(gtr_hits0, &record->GTR(), gtrped, gtr_lorentz_angle_calib_params);
//  	record->GTR().UpdatePtrs();
//   gtrhist->Fill(record);
//
//   ++n_event;
//    ++n_physics_event;
//  }
//  TCanvas *c1 = new TCanvas("c1", "c1", 1024, 768);
//  TString pdf_name;
////  pdf_name.Form("/ccj/w/data06a/E16/user/nakasuga/output/gtr/dst1check/pdf/gtrtest%06d.pdf",run_id);
//  pdf_name.Form("c_gtr_check_run%d.pdf", run_id);
//  c1->SaveAs(pdf_name + "[", "pdf");
//  
//  gStyle->SetOptStat(111111);
//
//  c1->SaveAs( pdf_name + "]", "pdf");
//
//  fout->Write();
//  fout->Close();


  delete geometry;
//  delete dst0;
//  dst1->Close();
  return 0;
}
