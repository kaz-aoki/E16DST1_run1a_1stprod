//this is test for wire track factory 
//
//
//
#include <stdlib.h>
#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
//#include <boost/program_options.hpp>

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

using namespace std;
//namespace  bpo = boost::program_options;




int main(int argc, char* argv[]) {
//   if (argc != 5) {
//     cerr << "Invalid argc: " << argc << endl;
//     cerr << "./bin [input.dst0] [output.dst1] [run ID] [max physics event (all: -1)] " << endl;
//     return 1;
//   }
//    auto dst0 = new E16DST_DST0();
//   if (!dst0->Open(argv[1], E16DST_DST0::ReadMode)) {
//     std::cout << "failed to open file : " << argv[1]  <<std::endl;
// 	exit(1);
// //    return 1;
//   }
//   string in_file_name = argv[1];
//   int sink_id_pos = in_file_name.length() - 10;
//   string sink_id = in_file_name.substr(sink_id_pos, 1);
//   std::cout << "sink id = " << sink_id << std::endl;
//   int smallest_id_pos = in_file_name.length()-8;
//   string smallest_id = in_file_name.substr(smallest_id_pos, 3);
//   std::cout << "smallest  id = " << smallest_id << std::endl;
//   string runnum = argv[3];
//   string run = "g4run0" + runnum;
//   string outputfile = "./dst1_test/" + run + "_sink" + sink_id +"_"+ smallest_id+".root";

//   const char* c_out = outputfile.c_str();
//   //TFile *f = new TFile("./wire_root/output.run", "recreate");
//   TFile *f = new TFile( c_out, "recreate");
 
 
// //  TFile *f = new TFile("./dst1_test/output.root", "recreate");
//   TTree *tree = new TTree("tree", "tree");
//   Int_t event_id;
//   Int_t mod_id;
//   Int_t hitid_ssdx;
//   Int_t hitid_100x;
//   Int_t hitid_200x;
//   Int_t hitid_300x;
//   Int_t hitid_100y;
//   Int_t hitid_200y;
//   Int_t hitid_300y;
//   Int_t hasMatchedASDHit;
//   Double_t g_xssd;
//   Double_t g_zssd;
//   Double_t g_x100;
//   Double_t g_y100;
//   Double_t g_z100;
//   Double_t g_x200;
//   Double_t g_y200;
//   Double_t g_z200;
//   Double_t g_x300;
//   Double_t g_y300;
//   Double_t g_z300;
//   Double_t lxssd;//local pos1
//   Double_t lx100;//local pos1
//   Double_t ly100;
//   Double_t lx200;
//   Double_t ly200;
//   Double_t lx300;
//   Double_t ly300;
//   Double_t clc_xssd;
//   Double_t clc_x100;
//   Double_t clc_x200;
//   Double_t clc_x300;
//   Double_t clc_y100;
//   Double_t clc_y200;
//   Double_t clc_y300;
//   Double_t timing_xssd;
//   Double_t timing_x100;
//   Double_t timing_x200;
//   Double_t timing_x300;
//   Double_t timing_y100;
//   Double_t timing_y200;
//   Double_t timing_y300;
//   Double_t residual_ssdx;
//   Double_t residual_100x;
//   Double_t residual_200x;
//   Double_t residual_300x;
//   Double_t residual_100y;
//   Double_t residual_200y;
//   Double_t residual_300y;
//   Double_t fitresidual_ssdx;
//   Double_t fitresidual_100x;
//   Double_t fitresidual_200x;
//   Double_t fitresidual_300x;
//   Double_t fitresidual_100y;
//   Double_t fitresidual_200y;
//   Double_t fitresidual_300y;
//   Double_t chi2_x;
//   Double_t chi2_y;
//   Double_t tgt_z;
// //  Double_t tgtpos_y;
//   Double_t fit_a_x;
//   Double_t fit_b_x;
//   Double_t fit_a_y;
//   Double_t fit_b_y;
//   Double_t distance_x;
// //  Double_t distance_y;	
//   Double_t distance_fromtgt_y;	
//   Double_t distance_fromupwire_y;	
//   Double_t distance_fromdownwire_y;	
//   Double_t fit_g100x;
//   Double_t fit_g100y;
//   Double_t fit_g100z;
//   Double_t fit_g200x;
//   Double_t fit_g200y;
//   Double_t fit_g200z;
//   Double_t fit_g300x;
//   Double_t fit_g300y;
//   Double_t fit_g300z;

//   Int_t x_trk_used_times;
//   Int_t trkid_x;
//   Int_t trkid_y;
//   Int_t cluster_size_ssd;
//   Int_t cluster_size_g100x;
//   Int_t cluster_size_g200x;
//   Int_t cluster_size_g300x;
//   Int_t cluster_size_g100y;
//   Int_t cluster_size_g200y;
//   Int_t cluster_size_g300y;
//   Int_t asd_hit;
//   Int_t lg_hit;
//   TVector3 lg_cross_pos;
//   Int_t lg_module_id;
//   Int_t lg_channel_id;
//   Double_t timediff_in_cluster_100x;
//   Double_t timediff_in_cluster_200x;
//   Double_t timediff_in_cluster_300x;
//   vector<Double_t> timings_100x;
//   vector<Double_t> timings_200x;
//   vector<Double_t> timings_300x;
//   vector<Double_t> positions_100x;
//   vector<Double_t> positions_200x;
//   vector<Double_t> positions_300x;


//   //	std::vector<TVector3> two_points_on_track;
//   tree->Branch("event_id", &event_id, "event_id/I");
//   tree->Branch("mod_id", &mod_id, "mod_id/I");
//   tree->Branch("hitid_ssdx", &hitid_ssdx, "hitid_ssdx/I");
//   tree->Branch("hitid_100x", &hitid_100x, "hitid_100x/I");
//   tree->Branch("hitid_200x", &hitid_200x, "hitid_200x/I");
//   tree->Branch("hitid_300x", &hitid_300x, "hitid_300x/I");
//   tree->Branch("hitid_100y", &hitid_100y, "hitid_100y/I");
//   tree->Branch("hitid_200y", &hitid_200y, "hitid_200y/I");
//   tree->Branch("hitid_300y", &hitid_300y, "hitid_300y/I");
//   tree->Branch("g_xssd", &g_xssd, "g_xssd/D");
//   tree->Branch("g_zssd", &g_zssd, "g_zssd/D");
//   tree->Branch("g_x100", &g_x100, "g_x100/D");
//   tree->Branch("g_y100", &g_y100, "g_y100/D");
//   tree->Branch("g_z100", &g_z100, "g_z100/D");
//   tree->Branch("g_x200", &g_x200, "g_x200/D");
//   tree->Branch("g_y200", &g_y200, "g_y200/D");
//   tree->Branch("g_z200", &g_z200, "g_z200/D");
//   tree->Branch("g_x300", &g_x300, "g_x300/D");
//   tree->Branch("g_y300", &g_y300, "g_y300/D");
//   tree->Branch("g_z300", &g_z300, "g_z300/D");
//   tree->Branch("lxssd", &lxssd, "lxssd/D");
//   tree->Branch("lx100", &lx100, "lx100/D");
//   tree->Branch("ly100", &ly100, "ly100/D");
//   tree->Branch("lx200", &lx200, "lx200/D");
//   tree->Branch("ly200", &ly200, "ly200/D");
//   tree->Branch("lx300", &lx300, "lx300/D");
//   tree->Branch("ly300", &ly300, "ly300/D");
//   tree->Branch("clc_xssd", &clc_xssd, "clc_xssd/D");
//   tree->Branch("clc_x100", &clc_x100, "clc_x100/D");
//   tree->Branch("clc_x200", &clc_x200, "clc_x200/D");
//   tree->Branch("clc_x300", &clc_x300, "clc_x300/D");
//   tree->Branch("clc_y100", &clc_y100, "clc_y100/D");
//   tree->Branch("clc_y200", &clc_y200, "clc_y200/D");
//   tree->Branch("clc_y300", &clc_y300, "clc_y300/D");
//   tree->Branch("timing_xssd", &timing_xssd, "timing_xssd/D");
//   tree->Branch("timing_x100", &timing_x100, "timing_x100/D");
//   tree->Branch("timing_x200", &timing_x200, "timing_x200/D");
//   tree->Branch("timing_x300", &timing_x300, "timing_x300/D");
//   tree->Branch("timing_y100", &timing_y100, "timing_y100/D");
//   tree->Branch("timing_y200", &timing_y200, "timing_y200/D");
//   tree->Branch("timing_y300", &timing_y300, "timing_y300/D");
//   tree->Branch("residual_100x", &residual_100x, "residual_100x/D");
//   tree->Branch("residual_200x", &residual_200x, "residual_200x/D");
//   tree->Branch("residual_300x", &residual_300x, "residual_300x/D");
//   tree->Branch("residual_100y", &residual_100y, "residual_100y/D");
//   tree->Branch("residual_200y", &residual_200y, "residual_200y/D");
//   tree->Branch("residual_300y", &residual_300y, "residual_300y/D");
//   tree->Branch("residual_ssdx", &residual_ssdx, "residual_ssdx/D");
//   tree->Branch("fitresidual_100x", &fitresidual_100x, "fitresidual_100x/D");
//   tree->Branch("fitresidual_200x", &fitresidual_200x, "fitresidual_200x/D");
//   tree->Branch("fitresidual_300x", &fitresidual_300x, "fitresidual_300x/D");
//   tree->Branch("fitresidual_100y", &fitresidual_100y, "fitresidual_100y/D");
//   tree->Branch("fitresidual_200y", &fitresidual_200y, "fitresidual_200y/D");
//   tree->Branch("fitresidual_300y", &fitresidual_300y, "fitresidual_300y/D");
//   tree->Branch("fitresidual_ssdx", &fitresidual_ssdx, "fitresidual_ssdx/D");
 


//   tree->Branch("chi2_x", &chi2_x, "chi2_x/D");
//   tree->Branch("chi2_y", &chi2_y, "chi2_y/D");
//   tree->Branch("tgt_z", &tgt_z, "tgt_z/D");
// //  tree->Branch("tgtpos_y", &tgtpos_y, "tgtpos_y/D");
//   tree->Branch("fit_a_x", &fit_a_x, "fit_a_x/D");
//   tree->Branch("fit_b_x", &fit_b_x, "fit_b_x/D");
//   tree->Branch("fit_a_y", &fit_a_y, "fit_a_y/D");
//   tree->Branch("fit_b_y", &fit_b_y, "fit_b_y/D");
//   tree->Branch("distance_x", &distance_x, "distance_x/D");
// //  tree->Branch("distance_y", &distance_y, "distance_y/D");
//   tree->Branch("distance_fromtgt_y", &distance_fromtgt_y, "distance_fromtgt_y/D");
//   tree->Branch("distance_fromupwire_y", &distance_fromupwire_y, "distance_fromupwire_y/D");
//   tree->Branch("distance_fromdownwire_y", &distance_fromdownwire_y, "distance_fromdownwire_y/D");
//   tree->Branch("fit_g100x", &fit_g100x, "fit_g100x/D");
//   tree->Branch("fit_g100y", &fit_g100y, "fit_g100y/D");
//   tree->Branch("fit_g100z", &fit_g100z, "fit_g100z/D");
//   tree->Branch("fit_g200x", &fit_g200x, "fit_g200x/D");
//   tree->Branch("fit_g200y", &fit_g200y, "fit_g200y/D");
//   tree->Branch("fit_g200z", &fit_g200z, "fit_g200z/D");
//   tree->Branch("fit_g300x", &fit_g300x, "fit_g300x/D");
//   tree->Branch("fit_g300y", &fit_g300y, "fit_g300y/D");
//   tree->Branch("fit_g300z", &fit_g300z, "fit_g300z/D");


//   tree->Branch("hasMatchedASDHit", &hasMatchedASDHit, "hasMatchedASDHit/I");
//   tree->Branch("x_trk_used_times", &x_trk_used_times, "x_trk_used_times/I");
//   tree->Branch("trkid_x", &trkid_x, "trkid_x/I");
//   tree->Branch("trkid_y", &trkid_y, "trkid_y/I");
//   tree->Branch("hitid_ssdx", &hitid_ssdx, "hitid_ssdx/I");
//   tree->Branch("hitid_100x", &hitid_100x, "hitid_100x/I");
//   tree->Branch("hitid_200x", &hitid_200x, "hitid_200x/I");
//   tree->Branch("hitid_300x", &hitid_300x, "hitid_300x/I");
//   tree->Branch("hitid_100y", &hitid_100y, "hitid_100y/I");
//   tree->Branch("hitid_200y", &hitid_200y, "hitid_200y/I");
//   tree->Branch("hitid_300y", &hitid_300y, "hitid_300y/I");
//   tree->Branch("cluster_size_ssd", &cluster_size_ssd, "cluster_size_ssd/I");
//   tree->Branch("cluster_size_g100x", &cluster_size_g100x, "cluster_size_g100x/I");
//   tree->Branch("cluster_size_g200x", &cluster_size_g200x, "cluster_size_g200x/I");
//   tree->Branch("cluster_size_g300x", &cluster_size_g300x, "cluster_size_g300x/I");
//   tree->Branch("cluster_size_g100y", &cluster_size_g100y, "cluster_size_g100y/I");
//   tree->Branch("cluster_size_g200y", &cluster_size_g200y, "cluster_size_g200y/I");
//   tree->Branch("cluster_size_g300y", &cluster_size_g300y, "cluster_size_g300y/I");
//   tree->Branch("asd_hit",&asd_hit, "asd_hit/I" );
//   tree->Branch("lg_hit",&lg_hit, "lg_hit/I" );
//   tree->Branch("lg_cross_pos", &lg_cross_pos);
//   tree->Branch("lg_module_id", &lg_module_id, "lg_module_id/I");
//   tree->Branch("lg_channel_id", &lg_channel_id,"lg_channel_id/I" );

//   tree->Branch("timediff_in_cluster_100x", &timediff_in_cluster_100x, "timediff_in_cluster_100x/D"); 
//   tree->Branch("timediff_in_cluster_200x", &timediff_in_cluster_200x, "timediff_in_cluster_200x/D"); 
//   tree->Branch("timediff_in_cluster_300x", &timediff_in_cluster_300x, "timediff_in_cluster_300x/D"); 
//   tree->Branch("timings_100x"  , &timings_100x );
//   tree->Branch("timings_200x"  , &timings_200x );
//   tree->Branch("timings_300x"  , &timings_300x );
//   tree->Branch("positions_100x", &positions_100x );
//   tree->Branch("positions_200x", &positions_200x );
//   tree->Branch("positions_300x", &positions_300x );





//   //auto in_file_name  = argv[1];
//   auto out_file_name = argv[2];
//   auto run_id        = stoi(argv[3]);
//   auto max_event     = stoi(argv[4]);
//   auto& calib = E16ANA_CalibDBManager::Instance();
//   calib.SetRunID(run_id);
// //  E16ANA_RundependentName& name = E16ANA_RundependentName::Instance();
// //  string geomName = name.ReadNameWithRunID(run_id, "geometry", "/ccj/u/E16/database/");
// //  E16ANA_GeometryV2* geom = new E16ANA_GeometryV2(geomName);
// //  E16ANA_GeometryV2::SetGlobalPointer(geom);

// //  E16ANA_ParamManager *paramMgr;
// //  E16ANA_GTRAnalyzerManager *gtr_manager;
// //  const char *file = "/ccj/u/mtomoki/E16CalibFiles-local.cfg";
// //  paramMgr = new E16ANA_ParamManager(file);
// //  gtr_manager = new E16ANA_GTRAnalyzerManager(paramMgr);


//   auto trigger_param = new E16ANA_TriggerCalibParam();
//   trigger_param->ReadConstantData(calib.CurrentRunID());
//   E16ANA_GTRcalibPedestal gtrped;
//   gtrped.ReadCalibData( calib.CurrentRunID() );
//   E16ANA_TargetInfoManager& targets = E16ANA_TargetInfoManager::Instance();
//   targets.ReadInfoWithRunID( calib.CurrentRunID());
//   targets.Print();
//   E16ANA_GTRLorentzAngleCalibParamManager gtr_lorentz_angle_calib_param_manager;
//   gtr_lorentz_angle_calib_param_manager.ReadConstantData(calib.CurrentRunID());
//   auto gtr_lorentz_angle_calib_params = gtr_lorentz_angle_calib_param_manager.GTRLorentzAngleCalibParams();
//   auto record = new E16DST_DST1PhysicsRecord();
//   auto geom = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
//   auto *gtrhist = new GTRCheckHist();
//   auto gtr_status = new E16ANA_GTRStatus(calib.CurrentRunID());
//   //auto asd_dead = gtr_status->ASDDeadChannel();
// //  gtr_status->ASDDeadChannel()->ReadDeadChannelData( calib.CurrentRunID());
//   for (int m=101; m< 110; m++){
// 	for(int ch=0; ch < 24; ch++){
//  		std::cout << "isYOK ch``module = " << m << ", ch = " << ch << ", gtr_dead " <<  gtr_status->Is300YOK(m, ch) << std::endl;
// 	}
//   }
  
//   int n_event = 0;
//   int n_physics_event = 0;
//   std::cout << "here " << std::endl;
//   while (dst0->ReadAnEvent()) {
//     if (max_event != -1 && n_event >= max_event) {
//       break;
//     }
//     if (n_event % 100 == 0) {
//       cout << "Number of event: " << n_event << endl;
//     }
//     if (dst0->EventType() != E16DST_DST0EventType::Physics){
//         std::cout << "Event ID = " << dst0->Event()->EventID() << " is not Physics Event, Event Type =" << dst0->Event()->EventType() << std::endl;
//         continue;
//     }
// //
// //
//     auto event_type = dst0->EventType();
//     E16DST_DST0PhysicsEvent *event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
//     auto& gtr_hits0 = event0->GTR();
//     auto& ssd_hits0 = event0->SSD();
//     E16DST_DST1SSDFactory(ssd_hits0, &record->SSD());
//     E16DST_DST1GTRFactory(gtr_hits0, &record->GTR(), gtrped, gtr_lorentz_angle_calib_params);
//     record->GTR().UpdatePtrs();
//     record->SSD().UpdatePtrs();

// //---test --- //	
// //	for(int mid=100; mid<110; mid++){
// //		for(int l=0; l<2; l++){
// //		std::vector<E16DST_DST1GTRCluster*> &cls  = record->GTR().ClusterPtrs(mid, l, 0);
// //			for(int i =0; i<cls.size(); i++){
// //				for(int j=0; j< cls[i]->HitOrders().size() ; j++){
// //					std::cout << "id = " << cls[i]->HitOrders()[j] << std::endl;
// //				}
// //			}
// //		}
// //	}
// 	int noh_trg = event0->TriggerGTR().NumberOfHits();
// 	int hit_tile = -1000;
	
// 	std::vector<std::shared_ptr<E16DST_DST1StraightTrack3D>> st_tracks;
// 	if(targets.IsWire()){
// 		E16DST_DST1WireTrackFactory3D(event0, &record->SSD(), &record->GTR(), st_tracks, gtrped);
// 	}
// 	else if(targets.NoT() == 3){
// 		E16DST_DST1StraightTrackFactory3D(event0, &record->SSD(), &record->GTR(), st_tracks, gtrped);
// 	}
// 	for(int i=0; i < st_tracks.size(); i++){
// 		std::shared_ptr<E16DST_DST1StraightTrack3D> t = st_tracks[i];
// 		event_id = t->EventID();
// 		mod_id = t->ModuleID();	
// 		trkid_x    = t->XTrackID();
// 		trkid_y    = t->YTrackID();
// 		hitid_ssdx = t->SSDXHitID();
// 		hitid_100x = t->GTR100XHitID();
// 		hitid_200x = t->GTR200XHitID();
// 		hitid_300x = t->GTR300XHitID();
// 		hitid_100y = t->GTR100XHitID();
// 		hitid_200y = t->GTR200XHitID();
// 		hitid_300y = t->GTR300XHitID();
// 		cluster_size_ssd   = t->SSDCluster()->NumHits();
// 		cluster_size_g100x = t->GTR100XCluster()->NumHits();
// 		cluster_size_g200x = t->GTR200XCluster()->NumHits();
// 		cluster_size_g300x = t->GTR300XCluster()->NumHits();
// 		cluster_size_g100x = t->GTR100YCluster()->NumHits();
// 		cluster_size_g200x = t->GTR200YCluster()->NumHits();
// 		cluster_size_g300x = t->GTR300YCluster()->NumHits();
// 		lxssd    = t->SSDCluster()->CogPos();
// 		lx100    = t->GTR100XCluster()->CogPos();
// 		lx200    = t->GTR200XCluster()->CogPos();
// 		lx300    = t->GTR300XCluster()->CogPos();
// 		ly100    = t->GTR100YCluster()->CogPos();//local y
// 		ly200    = t->GTR200YCluster()->CogPos();//local y
// 		ly300    = t->GTR300YCluster()->CogPos();//local y
// 		g_xssd   = t->SSDCluster()->GlobalPos(*geom).X();
// 		g_x100   = t->GTR100XCluster()->GlobalPos(*geom).X();
// 		g_x200   = t->GTR200XCluster()->GlobalPos(*geom).X();
// 		g_x300   = t->GTR300XCluster()->GlobalPos(*geom).X();
// 		g_y100   = t->GTR100YCluster()->GlobalPos(*geom).Y();
// 		g_y200   = t->GTR200YCluster()->GlobalPos(*geom).Y();
// 		g_y300   = t->GTR300YCluster()->GlobalPos(*geom).Y();
// 		g_zssd   = t->SSDCluster()->GlobalPos(*geom).Z();
// 		g_z100   = t->GTR100XCluster()->GlobalPos(*geom).Z();
// 		g_z200   = t->GTR200XCluster()->GlobalPos(*geom).Z();
// 		g_z300   = t->GTR300XCluster()->GlobalPos(*geom).Z();
// 		clc_xssd = t->SSDCluster()->PeakSum();
// 		clc_x100 = t->GTR100XCluster()->PeakSum();
// 		clc_x200 = t->GTR200XCluster()->PeakSum();
// 		clc_x300 = t->GTR300XCluster()->PeakSum();
// 		clc_y100 = t->GTR100YCluster()->PeakSum();
// 		clc_y200 = t->GTR200YCluster()->PeakSum();
// 		clc_y300 = t->GTR300YCluster()->PeakSum();
// 		timing_xssd = t->SSDCluster()->Timing();
// 		timing_x100 = t->GTR100XCluster()->Timing();
// 		timing_x200 = t->GTR200XCluster()->Timing();
// 		timing_x300 = t->GTR300XCluster()->Timing();
// 		timing_y100 = t->GTR100YCluster()->Timing();
// 		timing_y200 = t->GTR200YCluster()->Timing();
// 		timing_y300 = t->GTR300YCluster()->Timing();
// 		chi2_x = t->Chi2X();
// 		chi2_y = t->Chi2Y();
// 		tgt_z  = t->TgtPosZ();
// //		tgtpos_y = t->TgtPosY();
// 	    fit_a_x = t->FitAX();
// 	    fit_b_x = t->FitBX();
// 	    fit_a_y = t->FitAY();
// 	    fit_b_y = t->FitBY();
// 		if(targets.IsWire()){
// 			distance_x = t->DistanceFromTgtXZ();
// //			distance_y = t->DistanceFromTgtYR();
// 			distance_fromupwire_y   = t->DistanceFromUpWireYR();
// 			distance_fromdownwire_y = t->DistanceFromDownWireYR();
// 		}
// 		distance_fromtgt_y = -1000;
//         distance_fromtgt_y  = t->DistanceYTrackAndTgt();
// 		residual_ssdx = t->ResidualSSD();
// //		residual_100x = t->Residual100();
// //		residual_200x = t->Residual200();
// //		residual_300x = t->Residual300();
// //		residual_100y = t->Residual100();
// //		residual_200y =	t->Residual200();
// ////		residual_300y = t->Residual300();
// //		fitresidual_ssdx = t->FitResidualSSD();
// 		fitresidual_100x = t->FitResidual100X();
// 		fitresidual_200x = t->FitResidual200X();
// 		fitresidual_300x = t->FitResidual300X();
// 		fitresidual_100y = t->FitResidual100Y();
// 		fitresidual_200y = t->FitResidual200Y();
// 		fitresidual_300y = t->FitResidual300Y();
// 		fit_g100x = t->FitPtOnGTR100().X();
// 		fit_g100y = t->FitPtOnGTR100().Y();
// 		fit_g100z = t->FitPtOnGTR100().Z();
// 		fit_g200x = t->FitPtOnGTR200().X();
// 		fit_g200y = t->FitPtOnGTR200().Y();
// 		fit_g200z = t->FitPtOnGTR200().Z();
// 		fit_g300x = t->FitPtOnGTR300().X();
// 		fit_g300y = t->FitPtOnGTR300().Y();
// 		fit_g300z = t->FitPtOnGTR300().Z();
// 		x_trk_used_times = t->XZTrackUsedTimes();
		
// 		timings_100x.clear();
// 		timings_200x.clear();
// 		timings_300x.clear();
// 		positions_100x.clear();
// 		positions_200x.clear();
// 		positions_300x.clear();

// 		hasMatchedASDHit = 0; //initialized 
// 		hit_tile = (int)((t->GTR300YCluster()->CogPos()+150.0)/12.5);
// 		for(int j=0; j<noh_trg; j++){
// 			E16DST_DST0TriggerHit &trg = event0->TriggerGTR().Hit(j);
// 			if(hit_tile == trg.ChannelID()){
// 				hasMatchedASDHit = 1;
// 			}
// 		}
// 		for(int l=1; l< 4 ; l++){
// 		    vector<int16_t> &hit_ids = t->GTRXCluster(l)->HitOrders();
// 		      int min_id = hit_ids[0];
// 			  int max_id = hit_ids[hit_ids.size()-1];
// 	      		std::vector<E16DST_DST1GTRHit> &hits  = record->GTR().Hits();
// 				for(int k=0; k<hit_ids.size(); k++){
// 					int hid = hit_ids[k];
// 					double timing = hits[hid].Timing();
// 					double lpos = hits[hid].LocalPos(*geom).X();
// 					if(l==1) {timings_100x.push_back(timing);}
// 					else if(l==2) {timings_200x.push_back(timing);}
// 					else if(l==3) {timings_300x.push_back(timing);}
// 					if(l==1) {positions_100x.push_back(lpos);}
// 					else if(l==2) {positions_200x.push_back(lpos);}
// 					else if(l==3) {positions_300x.push_back(lpos);}
// 						max_id = hit_ids[k];
// 				  }
// 				  hits.clear();
// //					  int16_t id = hit_ids[k];
// 		          double timing_diff = hits[min_id].Timing() - hits[max_id].Timing();
// 			      if (l == 1) timediff_in_cluster_100x = timing_diff;
// 			      else if (l == 2) timediff_in_cluster_200x = timing_diff;
// 			      else if (l == 3) timediff_in_cluster_300x = timing_diff;
// 		   	  	//std::cout << "hit ids = " << hit_ids[k] << std::endl; 
// 		      	  hit_ids.clear(); 
// 		}
// 		tree->Fill();
// 	}
	
// //	if(st_tracks.size() != 0)std::cout << "st_tracks size =  " << st_tracks.size() << std::endl;
// //	gtrhist->Fill(st_tracks);
// //	gtrhist->Fill();	
//     ++n_event;
//     ++n_physics_event;
//   }
//   f->Write();

 

//   TCanvas *c0 = new TCanvas("c0", "c0", 1024, 768);
//   TString pdf_name;
//   pdf_name.Form("gtrtest.pdf");
//   c0->SaveAs(pdf_name + "[", "pdf");

//   TCanvas *c1 = new TCanvas();
//   c1->Divide(3,2);
//   for(int m=102; m < 109 ; m++){
//     if(m == 105) continue;
// 	c1->cd(m-101);
//    	gtrhist->h_tgt_z[m-100]->Draw();
// 	if(m>105 ){
// 		c1->cd(m-102);
// 	    gtrhist->h_tgt_z[m-100]->Draw();
// 	}
//   }
//   c1->SaveAs(pdf_name, "pdf");



// //
// //  TCanvas *c_cl_charge_x[10]; 
// //  //= new TCanvas("cl charge ", 100,0,100);
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_charge_x[m-102] = new TCanvas(Form("ccx%d", m-102) , Form("ccx%d", m-102), 1024, 768);
// //    c_cl_charge_x[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_charge_x[m-102]->cd(l+1);
// //        gtrhist->h_cl_charge_x[m-100][l]->Draw();
// //    }
// //    c_cl_charge_x[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// // 
// //  TCanvas *c_cl_charge_y[10]; 
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_charge_y[m-102] = new TCanvas(Form("ccy%d", m-102), Form("ccy%d", m-102), 1024, 768);
// //    c_cl_charge_y[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_charge_y[m-102]->cd(l+1);
// //        gtrhist->h_cl_charge_y[m-100][l]->Draw();
// //    }
// //    c_cl_charge_y[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// //  
// //  TCanvas *c_cl_charge_yb[10]; 
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_charge_yb[m-102] = new TCanvas(Form("ccyb%d", m-102), Form("ccyb%d", m-102), 1024, 768);
// //    c_cl_charge_yb[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_charge_yb[m-102]->cd(l+1);
// //        gtrhist->h_cl_charge_yb[m-100][l]->Draw();
// //    }
// //    c_cl_charge_yb[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// //  
// //  TCanvas *c_cl_local_x[10]; 
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_local_x[m-102] = new TCanvas(Form("clx%d", m-102), Form("clx%d", m-102), 1024, 768);
// //    c_cl_local_x[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_local_x[m-102]->cd(l+1);
// //        gtrhist->h_cl_local_x[m-100][l]->Draw();
// //    }
// //    c_cl_local_x[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// //
// //  TCanvas *c_cl_local_y[10]; 
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_local_y[m-102] = new TCanvas(Form("cly%d", m-102), Form("cly%d", m-102), 1024, 768);
// //    c_cl_local_y[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_local_y[m-102]->cd(l+1);
// //        gtrhist->h_cl_local_y[m-100][l]->Draw();
// //    }
// //    c_cl_local_y[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// //   TCanvas *c_cl_local_yb[10]; 
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_local_yb[m-102] = new TCanvas(Form("clyb%d",m-102), Form("clyb%d", m-102), 1024, 768);
// //    c_cl_local_yb[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_local_yb[m-102]->cd(l+1);
// //        gtrhist->h_cl_local_yb[m-100][l]->Draw();
// //    }
// //    c_cl_local_yb[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// // 
// //  TCanvas *c_cl_max_peak_x[10]; 
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_max_peak_x[m-102] = new TCanvas(Form("clmpx%d", m-102), Form("clmpx%d", m-102), 1024, 768);
// //    c_cl_max_peak_x[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_max_peak_x[m-102]->cd(l+1);
// //        gtrhist->h_cl_max_peak_x[m-100][l]->Draw();
// //    }
// //    c_cl_max_peak_x[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// //  
// //  TCanvas *c_cl_max_peak_y[10]; 
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_max_peak_y[m-102] = new TCanvas(Form("clmpy%d",m-102), Form("clmpy%d", m-102), 1024, 768);
// //    c_cl_max_peak_y[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_max_peak_y[m-102]->cd(l+1);
// //        gtrhist->h_cl_max_peak_y[m-100][l]->Draw();
// //    }
// //    c_cl_max_peak_y[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// //
// //  TCanvas *c_cl_max_peak_yb[10]; 
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_max_peak_yb[m-102] = new TCanvas(Form("clmpyb%d", m-102), Form("clmpyb%d", m-102), 1024, 768);
// //    c_cl_max_peak_yb[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_max_peak_yb[m-102]->cd(l+1);
// //        gtrhist->h_cl_max_peak_yb[m-100][l]->Draw();
// //    }
// //    c_cl_max_peak_yb[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// //
// //  TCanvas *c_cl_max_peak_ch_x[10]; 
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_max_peak_ch_x[m-102] = new TCanvas(Form("clmpchx%d", m-102), Form("clmpchx%d", m-102), 1024, 768);
// //    c_cl_max_peak_ch_x[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_max_peak_ch_x[m-102]->cd(l+1);
// //        gtrhist->h_cl_max_peak_ch_x[m-100][l]->Draw();
// //    }
// //    c_cl_max_peak_x[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// // 
// //  TCanvas *c_cl_tdcpos_x[10]; 
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_tdcpos_x[m-102] = new TCanvas(Form("cltdcposx%d", m-102), Form("cltdcposx%d", m-102), 1024, 768);
// //    c_cl_tdcpos_x[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_tdcpos_x[m-102]->cd(l+1);
// //        gtrhist->h_cl_tdcpos_x[m-100][l]->Draw();
// //    }
// //    c_cl_tdcpos_x[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// // 
// //  TCanvas *c_cl_tdcpos_y[10]; 
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_tdcpos_y[m-102] = new TCanvas(Form("cltdcposy%d", m-102), Form("cltdcposy%d", m-102), 1024, 768);
// //    c_cl_tdcpos_y[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_tdcpos_x[m-102]->cd(l+1);
// //        gtrhist->h_cl_tdcpos_y[m-100][l]->Draw();
// //    }
// //    c_cl_tdcpos_y[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// //   TCanvas *c_cl_tdcpos_yb[10]; 
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_tdcpos_yb[m-102] = new TCanvas(Form("cltdcposyb%d", m-102), Form("cltdcposyb%d", m-102), 1024, 768);
// //    c_cl_tdcpos_yb[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_tdcpos_yb[m-102]->cd(l+1);
// //        gtrhist->h_cl_tdcpos_yb[m-100][l]->Draw();
// //    }
// //    c_cl_tdcpos_yb[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// //
// //  TCanvas *c_cl_tan_x[10]; 
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_tan_x[m-102] = new TCanvas(Form("cltanx%d", m-102), Form("cltanx%d", m-102), 1024, 768);
// //    c_cl_tan_x[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_tan_x[m-102]->cd(l+1);
// //        gtrhist->h_cl_tan_x[m-100][l]->Draw();
// //    }
// //    c_cl_tan_x[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// //   TCanvas *c_cl_tan_y[10]; 
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_tan_y[m-102] = new TCanvas(Form("cltany%d", m-102), Form("cltany%d", m-102), 1024, 768);
// //    c_cl_tan_y[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_tan_y[m-102]->cd(l+1);
// //        gtrhist->h_cl_tan_y[m-100][l]->Draw();
// //    }
// //    c_cl_tan_y[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// //    TCanvas *c_cl_tan_yb[10]; 
// //  for(int m=102; m < 109 ; m++){
// //    if(m == 105) continue;
// //    c_cl_tan_yb[m-102] = new TCanvas(Form("cltanyb%d", m-102), Form("cltanyb%d", m-102), 1024, 768);
// //    c_cl_tan_yb[m-102]->Divide(2,2);
// //    for(int l=0; l < 3; l++){
// //        c_cl_tan_yb[m-102]->cd(l+1);
// //        gtrhist->h_cl_tan_yb[m-100][l]->Draw();
// //    }
// //    c_cl_tan_yb[m-102]->SaveAs(pdf_name, "pdf");
// //  }
// // 
// //
//   c0->SaveAs( pdf_name + "]", "pdf");
// //

// //  delete geometry;
//   delete dst0;
// //  dst1->Close();
  return 0;
}
