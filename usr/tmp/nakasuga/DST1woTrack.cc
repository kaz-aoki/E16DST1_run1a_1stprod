#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
//#include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
//#include "E16ANA_WaveformFitter.hh"
#include "E16ANA_WaveformFitterCRRC.hh"
#include "E16ANA_FieldMapCalib.hh"
#include "E16ANA_EventSelect.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_GTRLorentzAngleCalib.hh"
#include "E16ANA_GTRStatus.h"
#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDCut.hh"
#include "E16ANA_HBDDeadChannel.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"

#include "E16ANA_TrackCheckFile.hh"

#include "E16ANA_STSGlobalGeometry.hh"
#include "STS/E16ANA_EventDisplay.hh"

using namespace std;
//namespace  bpo = boost::program_options;

constexpr bool kIsElectronRun = true;
constexpr bool kSelectEvent   = false;

int main(int argc, char* argv[]) {
  if (argc != 6) {
    cerr << "./bin [input.dst0] [output.root] [run ID] [physics event start] [physics event end (all : -1)] " << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto run_id        = stoi(argv[3]);
  auto event_start   = stoi(argv[4]);
  auto event_end     = stoi(argv[5]);

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
  E16ANA_EventSelect event_select;
  event_select.ReadConstantData(calib.CurrentRunID());
  auto& selected_event_ids = event_select.SelectedEventIDs();
  int current_ids_index = 0;
  auto n_selected_events = event_select.NumSelectedEventIDs();
  E16ANA_GTRcalibPedestal gtrped;
  gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_GTRLorentzAngleCalibParamManager gtr_lorentz_angle_calib_param_manager;
  gtr_lorentz_angle_calib_param_manager.ReadConstantData(calib.CurrentRunID());
  auto gtr_lorentz_angle_calib_params = gtr_lorentz_angle_calib_param_manager.GTRLorentzAngleCalibParams();
  E16ANA_HBDCalibration *hbd_calib = new E16ANA_HBDCalibration();
  hbd_calib->ReadCalibrationData(calib.CurrentRunID());
  E16ANA_HBDCut *hbd_cut = new E16ANA_HBDCut();
  hbd_cut->ReadCutData(calib.CurrentRunID());
  E16ANA_HBDCut *hbd_cut_wo_timing = new E16ANA_HBDCut();
  hbd_cut_wo_timing->ReadCutData(calib.CurrentRunID());
  hbd_cut_wo_timing->SetCut("clustering_time_window_start", -10000.);
  hbd_cut_wo_timing->SetCut("clustering_time_window_end", 10000.);
//  std::string hbd_waveform_template = calib.CalibFileName("HBD-waveform-template", 0);
  E16ANA_LGBasic lgbasic;
  lgbasic.SetMap();
  lgbasic.SetCalibMap();
  E16ANA_TriggerCalibParam trigger_param;
  trigger_param.ReadConstantData(calib.CurrentRunID());

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
  bfield_map->Initialize_binary();
  E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
  
  auto *sts_geom = E16ANA_STSGlobalGeometry::instance();
  

//  E16ANA_WaveformFitter *wf1d_fitter = new E16ANA_WaveformFitter(hbd_waveform_template);
  E16ANA_WaveformFitterCRRC *wf1d_fitter = new E16ANA_WaveformFitterCRRC();
  E16ANA_MultiTrack fitter(bfield_map, geometry, 1);
  E16ANA_MultiTrack pair_fitter(bfield_map, geometry, 2);

  E16ANA_TrackCheckFile check_file(out_file_name, run_id);
  
  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
  E16DST_DST1PhysicsRecord record;
  E16DST_DST1PhysicsRecord record_for_another_hbd_cluster;

  int n_event = 0;
  int n_physics_event = 0;
  while (dst0->ReadAnEvent()) {
    record.Clear();
    if (event_end != -1 && n_physics_event > event_end) {
      break;
    }
   if (n_event % 1000 == 0) {
      cout << "Number of event: " << n_event << endl;
   }
    auto event_type = dst0->EventType();
    if (event_type == E16DST_DST0EventType::Physics) {
      if (n_physics_event < event_start) {
        ++n_event;
        ++n_physics_event;
        continue;
      }
      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
      auto& ssd_hits0         = event0->SSD();
		auto& stsg_hits0         = event0->STSG();//gerry
		auto& sts_hits0         = event0->STS();
      auto& gtr_hits0         = event0->GTR();
      auto& hbd_hits0         = event0->HBD();
      auto& lg_hits0          = event0->LG();
//      auto& trigger_gtr_hits0 = event0->TriggerGTR();
//      auto& trigger_hbd_hits0 = event0->TriggerHBD();
//      auto& trigger_lg_hits0  = event0->TriggerLG();
      auto event_id = event0->EventID();
      if (kSelectEvent) {
        bool is_selected_event = false;
        while (true) {
          auto current_id = selected_event_ids[current_ids_index];
          if (event_id < current_id) {
            break;
          } else if (event_id == current_id) {
            is_selected_event = true;
            ++current_ids_index;
            break;
          } else if (event_id > current_id) {
            if (current_ids_index == n_selected_events - 1) {
              break;
            } else {
              ++current_ids_index;
              continue;
            }
          }
        }
        if (!is_selected_event) {
          ++n_event;
          ++n_physics_event;
          continue;
        }
      }
#ifndef REMOVE_REAL_HIT

#ifndef NoExist_SSD
		#ifndef UseSTS
	   E16DST_DST1SSDFactory(ssd_hits0, &record.SSD());
      record.SSD().AddHitAndClusterIds();
      record.SSD().UpdatePtrs();
		#else
		E16DST_DST1STSFactory(stsg_hits0, sts_hits0, &record.STS());
		record.STS().AddHitAndClusterIds();
      record.STS().UpdatePtrs();
		#endif
#endif
      E16DST_DST1GTRFactory(gtr_hits0, &record.GTR(), gtrped, gtr_lorentz_angle_calib_params);
      record.GTR().AddHitAndClusterIds();
      E16DST_DST1HBDFactory(hbd_hits0, hbd_calib, hbd_cut, wf1d_fitter, &record.HBD());
      record.HBD().AddHitAndClusterIds();
      E16DST_DST1LGFactory(lg_hits0, &record.LG(), 1, geometry); // w/ fit
      record.LG().AddHitAndClusterIds();
      E16DST_DST1TriggerFactory(trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
      record.Trigger().AddHitAndClusterIDs();
// HBD clustering w/o timing selection begin
      E16DST_DST1HBDFactory(hbd_hits0, hbd_calib, hbd_cut_wo_timing, wf1d_fitter, &record_for_another_hbd_cluster.HBD());
      record_for_another_hbd_cluster.HBD().AddHitAndClusterIds();
      record_for_another_hbd_cluster.HBD().UpdatePtrs();
      check_file.AddHBDClusters(*geometry, record_for_another_hbd_cluster.HBD());
// HBD clustering w/o timing selection end
#endif // REMOVE_REAL_HIT

      record.SSD().UpdatePtrs();
      record.GTR().UpdatePtrs();
      record.HBD().UpdatePtrs();
      record.LG().UpdatePtrs();
      record.Trigger().UpdatePtrs();
      check_file.AddRecord(*geometry, event0->EventID(), event0->SpillID(), event0->TimeStampInSpill(), event0->UT3().TriggerTime() % 8, record, lgbasic);
//      check_file.FillTree();
      E16DST_DST1TrackFactory(*geometry, *bfield_map, &fitter, &pair_fitter, kIsElectronRun, &record, &check_file);

//// Check begin
//      auto event_id = event0->EventID();
//      cout << "Event ID: " << event_id << endl;
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
      // record.Tracks().Print();
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
