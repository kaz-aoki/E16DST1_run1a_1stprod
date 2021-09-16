#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
//#include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DefaultFilePath.hh"

using namespace std;
//namespace  bpo = boost::program_options;

int main(int argc, char* argv[]) {
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

//  bpo::options_description command_options("command options");
//  command_options.add_options()
//    ("in",                           bpo::value<string>(&in_file_name),                                                                "Input file name (string)\n")
//    ("out",                          bpo::value<string>(&out_file_name),                                                               "Output file name (string)\n")
//    ("coincidence-map-file-w-mag0",  bpo::value<string>(&coincidence_map_files[0])->default_value(string(CoincidenceMapWMagFile0)),    "Coincidence map file w/ mag 0 (string)\n");
//    ("coincidence-map-file-w-mag1",  bpo::value<string>(&coincidence_map_files[1])->default_value(string(CoincidenceMapWMagFile1)),    "Coincidence map file w/ mag 1 (string)\n");
//    ("coincidence-map-file-w-mag2",  bpo::value<string>(&coincidence_map_files[2])->default_value(string(CoincidenceMapWMagFile2)),    "Coincidence map file w/ mag 2 (string)\n");
//    ("coincidence-map-file-w-mag3",  bpo::value<string>(&coincidence_map_files[3])->default_value(string(CoincidenceMapWMagFile3)),    "Coincidence map file w/ mag 3 (string)\n");
//    ("coincidence-map-file-w-mag4",  bpo::value<string>(&coincidence_map_files[4])->default_value(string(CoincidenceMapWMagFile4)),    "Coincidence map file w/ mag 4 (string)\n");
//    ("coincidence-map-file-w-mag5",  bpo::value<string>(&coincidence_map_files[5])->default_value(string(CoincidenceMapWMagFile5)),    "Coincidence map file w/ mag 5 (string)\n");
//    ("coincidence-map-file-wo-mag0", bpo::value<string>(&coincidence_map_files[6])->default_value(string(CoincidenceMapWoMagFile0)),   "Coincidence map file w/o mag 0 (string)\n");
//    ("coincidence-map-file-wo-mag1", bpo::value<string>(&coincidence_map_files[7])->default_value(string(CoincidenceMapWoMagFile1)),   "Coincidence map file w/o mag 1 (string)\n");
//    ("coincidence-map-file-wo-mag2", bpo::value<string>(&coincidence_map_files[8])->default_value(string(CoincidenceMapWoMagFile2)),   "Coincidence map file w/o mag 2 (string)\n");
//    ("coincidence-map-file-wo-mag3", bpo::value<string>(&coincidence_map_files[9])->default_value(string(CoincidenceMapWoMagFile3)),   "Coincidence map file w/o mag 3 (string)\n");
//    ("coincidence-map-file-wo-mag4", bpo::value<string>(&coincidence_map_files[10])->default_value(string(CoincidenceMapWoMagFile4)),  "Coincidence map file w/o mag 4 (string)\n");
//    ("coincidence-map-file-wo-mag5", bpo::value<string>(&coincidence_map_files[11])->default_value(string(CoincidenceMapWoMagFile5)),  "Coincidence map file w/o mag 5 (string)\n");
//    ("trigger-gtr-channel-map",      bpo::value<string>(&trigger_channel_map_files[0])->default_value(string(TriggerChannelMapFile0)), "Trigger GTR channel map file (string)\n");
//    ("trigger-hbd-channel-map",      bpo::value<string>(&trigger_channel_map_files[1])->default_value(string(TriggerChannelMapFile1)), "Trigger HBD channel map file (string)\n");
//    ("trigger-lg-channel-map",       bpo::value<string>(&trigger_channel_map_files[2])->default_value(string(TriggerChannelMapFile2)), "Trigger LG channel map file (string)\n");
//
//  auto file_check = [&vm, &in_file_name, &out_file_name]() {
//    if (in_file_name.empty()) {
//      throw invalid_argument("Invalid input file name: "s + in_file_name);
//    }
//    if (out_file_name.empty()) {
//      throw invalid_argument("Invalid output file name: "s + out_file_name);
//    }
//  };

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  auto trigger_param = new E16ANA_TriggerCalibParam();
  trigger_param->ReadConstantData(calib.CurrentRunID());
  E16ANA_GTRcalibPedestal gtrped;
  gtrped.ReadCalibData( calib.CurrentRunID() );

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  auto bfield_map_3d = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
  E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map_3d);
  auto bfield_map = dynamic_cast<E16ANA_MagneticFieldMap*>(bfield_map_3d);


  auto record = new E16DST_DST1PhysicsRecord();

  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
//  E16ANA_GTRPedestal *gtr_pedestal = new E16ANA_GTRPedestal();
//  gtr_pedestal->Read(argv[5]);
//  auto dst1 = new E16DST_DST1();
//  auto dst1 = new E16DST_DST0();
//  if (!dst1->Open(out_file_name, E16DST_DST0::WriteMode)) {
//    std::cerr << "Cannot open output file: " << out_file_name << std::endl;
//    return -1;
//   }

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
//    dst1->SetEventType(event_type);
    if (event_type == E16DST_DST0EventType::Physics) {
      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
//      auto event1 = dynamic_cast<E16DST_DST1PhysicsEvent*>(dst1->Event());
//      auto event1 = new E16DST_DST1PhysicsEvent();
      auto& ssd_hits0         = event0->SSD();
      auto& gtr_hits0         = event0->GTR();
      auto& hbd_hits0         = event0->HBD();
      auto& lg_hits0          = event0->LG();
      auto& trigger_gtr_hits0 = event0->TriggerGTR();
      auto& trigger_hbd_hits0 = event0->TriggerHBD();
      auto& trigger_lg_hits0  = event0->TriggerLG();
//      E16DST_DST1SSDFactory(ssd_hits0, &event1->SSDHits(), &event1->SSDClusters());
      E16DST_DST1SSDFactory_dummy(ssd_hits0, &record->SSD());
      record->SSD().UpdatePtrs();
//      E16DST_DST1GTRHitAndClusterFactory(gtr_hits0, &event1->GTRHits(), &event1->GTRClusters(), gtrped);
//      std::cout << "GTR factory returns :: " << E16DST_DST1GTRHitAndClusterFactory(gtr_hits0, &event1->GTRHits(), &event1->GTRClusters(), gtrped) << std::endl;
      E16DST_DST1GTRFactoryDST1Detector(gtr_hits0, &record->GTR(), gtrped);
      record->GTR().UpdatePtrs();
//      E16DST_DST1HBDFactory(hbd_hits0, &event1->HBDHits(), &event1->HBDClusters());
//      E16DST_DST1LGHitAndClusterFactory(lg_hits0,   event1->LGHits(),  event1->LGClusters());
//      E16DST_DST1LGFactory(lg_hits0,   &event1->LGHits(),  &event1->LGClusters());
//      E16DST_DST1LGFactoryDST1Detector(lg_hits0, &event1->LG());
//      E16DST_DST1TriggerFactory(*trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &event1->Trigger());
      E16DST_DST1TrackFactory(*geometry, *bfield_map, record);
//      event1->GTR().SetValidFlag(1);
//      event1->LG().SetValidFlag(1);
//      event1->Trigger().SetValidFlag(1);


//// Check begin
//      auto event_id = event0->EventID();
//      cout << "Event ID: " << event_id << endl;
//// SSD
//
//// GTR
//      cout << "Number of event: " << n_event << endl << endl;
//      auto n_gtr_hits = event1->GTRHits().NumberOfHits();
//      cout << "Number of GTR hits: " << n_gtr_hits << endl;
//      for (int n_hit = 0; n_hit < n_gtr_hits; ++n_hit) {
//        auto hit = event1->GTRHits().Hit(n_hit);
//        hit.Print();
//      }
//      auto n_gtr_clusters = event1->GTRClusters().NumberOfHits();
//      cout << endl << endl;
//      cout << "Number of GTR clusters: " << n_gtr_clusters << endl;
//      for (int n_cluster = 0; n_cluster < n_gtr_clusters; ++n_cluster) {
//        auto cluster = event1->GTRClusters().Hit(n_cluster);
//        cluster.Print();
//      }
//      
//// HBD
//
//// LG
//      if (event1->LGHits().NumberOfHits() != 0) {
//        auto lghit = event1->LGHits().Hit(0);                                                          
//        lghit.Print();                                                                                 
//        std::cout<<"LPos:("<<lghit.LocalPos(*geometry).X()<< ","<<lghit.LocalPos(*geometry).Y()<<","<<lghit.LocalPos(*geometry).Z()<<")"<<std::endl;  
//        std::cout<<"GPos:("<<lghit.GlobalPos(*geometry).X()<< ","<<lghit.GlobalPos(*geometry).Y()<<","<<lghit.GlobalPos(*geometry).Z()<<")"<<std::endl;     
//      }
//
//// trigger
//      event1->Trigger().Print(*geometry);
//
//// other
////      event1->GTR().Print();
////
////      if (event1->LG().NumHits() != 0) {
////        auto lghit = event1->LG().Hit(0);                                                          
////        lghit.Print();                                                                                 
////        std::cout<<"LPos:("<<lghit.LocalPos(*geometry).X()<< ","<<lghit.LocalPos(*geometry).Y()<<","<<lghit.LocalPos(*geometry).Z()<<")"<<std::endl;  
////        std::cout<<"GPos:("<<lghit.GlobalPos(*geometry).X()<< ","<<lghit.GlobalPos(*geometry).Y()<<","<<lghit.GlobalPos(*geometry).Z()<<")"<<std::endl;     
////      }
//
//      cout << endl << endl;
//// Check end

//      dst1->WriteAnEvent();
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

  delete geometry;
  delete dst0;
//  dst1->Close();
  return 0;
}
