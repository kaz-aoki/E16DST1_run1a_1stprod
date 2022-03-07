#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
//#include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_WaveformFitter.hh"
#include "E16ANA_FieldMapCalib.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_GTRLorentzAngleCalib.hh"
#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDCut.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"

#include "E16ANA_TrackCheckFile.hh"

using namespace std;
//namespace  bpo = boost::program_options;

const bool kIsElectronRun = true;

int main(int argc, char* argv[]) {
  if (argc != 6) {
    cerr << "./bin [input.dst0] [output.root] [run ID] [physics event start] [physics event end (all : -1)]" << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto run_id        = stoi(argv[3]);
  auto event_start   = stoi(argv[4]);
  auto event_end     = stoi(argv[5]);
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

  FILE* fp = fopen(in_file_name, "r");
  if (!fp) {
    cerr << "could not open file : " << in_file_name << endl;
    return -1;
  }
  fclose(fp);

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  E16ANA_FieldMapCalibParam field_map_param;
  field_map_param.ReadConstantData(calib.CurrentRunID());
  E16ANA_GTRcalibPedestal gtrped;
  gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_GTRLorentzAngleCalibParam gtr_lorentz_angle_calib_param;
  gtr_lorentz_angle_calib_param.ReadConstantData(calib.CurrentRunID());
//  if (field_map_param.FMCurrent() == 2450.) {
//    E16DST_DST1GTRHit::lorentz_angle_calib_params     = gtr_lorentz_angle_calib_param.GTRLorentzAngleCalibParams();
//    E16DST_DST1GTRCluster::lorentz_angle_calib_params = gtr_lorentz_angle_calib_param.GTRLorentzAngleCalibParams();
//  } else { // FMCurrent() == 0.
//    E16DST_DST1GTRHit::lorentz_angle_calib_params     = {0., 0., 0.};
//    E16DST_DST1GTRCluster::lorentz_angle_calib_params = {0., 0., 0.};
//  }
  E16ANA_HBDCalibration *hbd_calib = new E16ANA_HBDCalibration();
  hbd_calib->ReadCalibrationData(calib.CurrentRunID());
  E16ANA_HBDCut *hbd_cut = new E16ANA_HBDCut();
  hbd_cut->ReadCutData(calib.CurrentRunID());
  std::string hbd_waveform_template = calib.CalibFileName("HBD-waveform-template", 0);
  E16ANA_LGBasic lgbasic;
  lgbasic.SetCalibMap();
  E16ANA_TriggerCalibParam trigger_param;
  trigger_param.ReadConstantData(calib.CurrentRunID());

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
  bfield_map->Initialize_binary();
  E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
  
  E16ANA_WaveformFitter *wf1d_fitter = new E16ANA_WaveformFitter(hbd_waveform_template);
  E16ANA_MultiTrack fitter(bfield_map, geometry, 1);
  E16ANA_MultiTrack pair_fitter(bfield_map, geometry, 2);

  E16ANA_TrackCheckFile check_file(out_file_name, run_id);
  
  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
  E16DST_DST1PhysicsRecord record;

  int n_event = 0;
  int n_physics_event = 0;
  while (dst0->ReadAnEvent()) {
    if (event_end != -1 && n_physics_event > event_end) {
      break;
    }
//    if (n_event % 1000 == 0) {
      cout << "Number of event: " << n_event << endl;
//    }
    auto event_type = dst0->EventType();
    if (event_type == E16DST_DST0EventType::Physics) {
      if (n_physics_event < event_start) {
        ++n_event;
        ++n_physics_event;
        continue;
      }
      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
      auto& ssd_hits0         = event0->SSD();
      auto& gtr_hits0         = event0->GTR();
      auto& hbd_hits0         = event0->HBD();
      auto& lg_hits0          = event0->LG();
      auto& trigger_gtr_hits0 = event0->TriggerGTR();
      auto& trigger_hbd_hits0 = event0->TriggerHBD();
      auto& trigger_lg_hits0  = event0->TriggerLG();
      E16DST_DST1SSDFactory(ssd_hits0, &record.SSD());
      record.SSD().AddHitAndClusterIds();
      record.SSD().UpdatePtrs();
      E16DST_DST1GTRFactory(gtr_hits0, &record.GTR(), gtrped);
      record.GTR().AddHitAndClusterIds();
      record.GTR().UpdatePtrs();
      E16DST_DST1HBDFactory(hbd_hits0, hbd_calib, hbd_cut, wf1d_fitter, &record.HBD());
      record.HBD().AddHitAndClusterIds();
      record.HBD().UpdatePtrs();
//      E16DST_DST1LGFactory(lg_hits0, &record.LG(), 0);
      E16DST_DST1LGFactory(lg_hits0, &record.LG(), 1);
      record.LG().AddHitAndClusterIds();
      record.LG().UpdatePtrs();
      E16DST_DST1TriggerFactory(trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
      record.Trigger().AddHitAndClusterIDs();
      record.Trigger().UpdatePtrs();
//cout << event0->EventID() << endl;
      check_file.AddRecord(*geometry, event0->EventID(), event0->SpillID(), event0->TimeStampInSpill(), record);
//      check_file.FillTree();
      E16DST_DST1TrackFactory(*geometry, *bfield_map, &fitter, &pair_fitter, kIsElectronRun, &record, &check_file);

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
// track
      record.Tracks().Print();
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
  return 0;
}
