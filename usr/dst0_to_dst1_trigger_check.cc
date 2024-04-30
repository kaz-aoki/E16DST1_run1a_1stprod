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

#ifdef TRACK_EFF_CHECK
#include "E16ANA_GTRAnalyzerMaker.hh"
#include "E16ANA_MakeDummyDST1.hh"
#include "E16ANA_MockTrackOutputData.hh"
//#include "mockdataIOtestSimple.hh"
#endif // TRACK_EFF_CHECK

#include "STS/E16ANA_STSGlobalGeometry.hh"
#include "STS/E16ANA_EventDisplay.hh"

using namespace std;
//namespace  bpo = boost::program_options;

constexpr bool kIsElectronRun = true;
constexpr bool kSelectEvent   = false;

#ifdef TRACK_EFF_CHECK
enum {
  kVectorMesonData,
  kKsData
};
enum {
  kMergeSingleTrack,
  kMergeTrackPair
};
enum {
  kReadMockAlive,
  kReadMockDead,
  kReadMockError
};

int ReadAndAddMockVectorMesonTrackPair(E16ANA_MakeDummyDST1& data_merger, E16ANA_MockTrackOutputData* mock_data, E16ANA_MockTrack mock_tracks[],
                                       E16ANA_TrackCheckFile* check_file) {
  bool is_dead = false;
  for (int i = 0; i < 2; ++i) {
    if (mock_data->ReadATrack() != E16ANA_MockTrackOutputData::OK) {
      cerr << "mock data finished at " << endl;
      return kReadMockError;
    }
    if (mock_data->TrackID() % 2 != 1 - i)  {
      cerr << "something error occured in mock track reading: " << mock_data->TrackID() << endl;
      return kReadMockError;
    }
    mock_tracks[i] = mock_data->Track();
    auto is_dead_track = data_merger.IsDeadRegion(mock_tracks[i]) || data_merger.IsDiscriDeadRegion(mock_tracks[i]);
    check_file->AddSimTrack(is_dead_track, mock_tracks[i]);
    if (is_dead_track) {
      is_dead = true;
    }
  }
  if (is_dead) {
    return kReadMockDead;
  }
  return kReadMockAlive;
}

enum {
  kKs,
  kPiPlus,
  kPiMinus,
  kNumParticles
};
int ReadAndAddMockKsTrackPair(E16ANA_MakeDummyDST1& data_merger, E16ANA_MockTrackOutputData* mock_data, E16ANA_MockTrack mock_tracks[],
                              E16ANA_TrackCheckFile* check_file) {
  bool is_dead = false;
  array<int, kNumParticles> charges;
  for (int i = 0; i < 3; ++i) {
    if (mock_data->ReadATrack() != E16ANA_MockTrackOutputData::OK) {
      cerr << "mock data finished at " << endl;
      return kReadMockError;
    }
    auto& track = mock_data->Track();
    charges[i] = track.Charge();
    if (i == 0) {
      if (charges[i] != 0) {
        cerr << "unexpected particle: " << charges[i] << ", order: " << i << endl;
        return kReadMockError;
      }
      check_file->AddSimTrack(false, track);
    } else {
      if (charges[i] == 0) {
        cerr << "unexpected particle: " << charges[i] << ", order: " << i << endl;
        return kReadMockError;
      }
      if (i == 2) {
        if (charges[1] == charges[2]) {
          cerr << "unexpected particle: " << charges[i] << ", order: " << i << endl;
          return kReadMockError;
        }
      }
      if (charges[i] == 1) {
        mock_tracks[0] = track;
      } else {
        mock_tracks[1] = track;
      }
//      auto is_dead_track = data_merger.IsDeadRegion(track) || data_merger.IsDiscriDeadRegion(track);
      auto is_dead_track = data_merger.IsDeadRegion(track);
      check_file->AddSimTrack(is_dead_track, track);
      if (is_dead_track) {
        is_dead = true;
      }
    }
  }
  if (is_dead) {
    return kReadMockDead;
  }
  return kReadMockAlive;
}
#endif // TRACK_EFF_CHECK

int main(int argc, char* argv[]) {
#ifndef TRACK_EFF_CHECK
  if (argc != 6) {
    cerr << "./bin [input.dst0] [output.root] [run ID] [physics event start] [physics event end (all : -1)] " << endl;
#else
  if (argc != 11) {
    cerr << "./bin [input.dst0] [output.root] [run ID] [physics event start] [physics event end (all : -1)] [mockdata.mockout] [mock flag] [merge mock flag] [smear flag] [dead region flag]" << endl;
    cerr << "mock data flag 0: vector meson, 1: Ks" << endl;
    cerr << "merge mock flag 0: merge single track (maybe doesn't work well), 1: merge track pair" << endl;
    cerr << "smear flag 0: no smear, 1: design smear, 2: TDR2105 smear, 3: other" << endl;
    cerr << "dead region flag 0: no dead region, 1: w/ dead region" << endl;
#endif
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto run_id        = stoi(argv[3]);
  auto event_start   = stoi(argv[4]);
  auto event_end     = stoi(argv[5]);
#ifdef TRACK_EFF_CHECK
  auto mock_data_name   = argv[6];
  auto mock_data_flag   = stoi(argv[7]);
  auto merge_mock_flag  = stoi(argv[8]);
  auto smear_flag       = stoi(argv[9]);
  auto dead_region_flag = stoi(argv[10]);
  if (mock_data_flag != 0 && mock_data_flag != 1) {
    cerr << "Invalid dead region flag: " << smear_flag << endl;
    return -1;
  }
  if (merge_mock_flag != 0 && merge_mock_flag != 1) {
    cerr << "Invalid dead region flag: " << smear_flag << endl;
    return -1;
  }
  if (smear_flag < 0 || smear_flag > 3) {
    cerr << "Invalid smear flag: " << smear_flag << endl;
    return -1;
  }
  if (dead_region_flag != 0 && dead_region_flag != 1) {
    cerr << "Invalid dead region flag: " << smear_flag << endl;
    return -1;
  }
#endif
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
  
#ifdef TRACK_EFF_CHECK
  auto mock_data = E16ANA_MockTrackOutputData();
  if (mock_data.OpenReadFile(mock_data_name) != E16ANA_MockTrackOutputData::OK) {
    cerr << "cannot open mock data file" << endl;
    return -1;
  }
  
  E16ANA_GTRcalibParams gtr_params;
  gtr_params.ReadCalibData(run_id);
  auto gtr_analyzers = new E16ANA_GTRAnalyzerMaker(gtr_params);
  for(int mid = 100; mid <= 110; ++mid) {
    for(int lid = 0; lid < 3; ++lid) {
      auto gtr_analyzer2 = gtr_analyzers->Chamber(mid, lid);
      int n_strips = gtr_analyzer2->GetNumberOfStrips();
      for(int strip_id = 0; strip_id < n_strips; ++strip_id) {
        double ped = gtrped.GetPedestal(mid, lid, strip_id).Value();
        double sigma = gtrped.GetPedestal(mid, lid, strip_id).Sigma();
        gtr_analyzer2->SetPedestal(strip_id, ped);
        gtr_analyzer2->SetPedestalSigma(strip_id, sigma);
      }
    }
  }
  auto gtr_stat = E16ANA_GTRStatus(run_id);
  auto hbd_dead_ch = E16ANA_HBDDeadChannel();
  hbd_dead_ch.ReadDeadChannelData(run_id);
  auto lg_dead_ch = E16ANA_LGDeadChannel();
  lg_dead_ch.ReadDeadChannelData();
  auto data_merger = E16ANA_MakeDummyDST1(smear_flag, gtr_analyzers, &gtr_stat, gtr_stat.ASDDeadChannel(), &hbd_dead_ch, &lg_dead_ch);

#endif // TRACK_EFF_CHECK
  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
  E16DST_DST1PhysicsRecord record;
  E16DST_DST1PhysicsRecord record_for_another_hbd_cluster;
#ifdef DST1_EVENT_MIX
  E16DST_DST1PhysicsRecord prev_record;
#endif // DST1_EVENT_MIX


  int n_event = 0;
  int n_physics_event = 0;
#ifndef REMOVE_REAL_HIT
  while (dst0->ReadAnEvent()) {
#else // REMOVE_REAL_HIT
  while (true) {
    dst0->ReadAnEvent();
    if (dst0->EventType() == E16DST_DST0EventType::Physics) {
      break;
    }
  }
  while (true) {
#endif // REMOVE_REAL_HIT
    record.Clear();
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
	   E16DST_DST1SSDFactory(ssd_hits0, &record.SSD());
      record.SSD().AddHitAndClusterIds();
		E16DST_DST1STSFactory(stsg_hits0, sts_hits0, &record.STS());
      record.STS().UpdatePtrs();
#endif
      E16DST_DST1GTRFactory(gtr_hits0, &record.GTR(), gtrped, gtr_lorentz_angle_calib_params);
      record.GTR().AddHitAndClusterIds();
      E16DST_DST1HBDFactory(hbd_hits0, hbd_calib, hbd_cut, wf1d_fitter, &record.HBD());
      record.HBD().AddHitAndClusterIds();
      E16DST_DST1LGFactory(lg_hits0, &record.LG(), 1, geometry); // w/ fit
      record.LG().AddHitAndClusterIds();
#ifdef TMP_NIM_TRIGGER
      auto time_stamp = event0->TimeStamp();
      E16DST_DST1TriggerFactory(time_stamp, trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
#else // TMP_NIM_TRIGGER
      E16DST_DST1TriggerFactory(trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
#endif // TMP_NIM_TRIGGER
      record.Trigger().AddHitAndClusterIDs();
// HBD clustering w/o timing selection begin
      E16DST_DST1HBDFactory(hbd_hits0, hbd_calib, hbd_cut_wo_timing, wf1d_fitter, &record_for_another_hbd_cluster.HBD());
      record_for_another_hbd_cluster.HBD().AddHitAndClusterIds();
      record_for_another_hbd_cluster.HBD().UpdatePtrs();
      check_file.AddHBDClusters(*geometry, record_for_another_hbd_cluster.HBD());
// HBD clustering w/o timing selection end
#endif // REMOVE_REAL_HIT
#ifdef TRACK_EFF_CHECK
      record.SSD().UpdatePtrs();
      record.GTR().UpdatePtrs();
      record.HBD().UpdatePtrs();
      record.LG().UpdatePtrs();
      record.Trigger().UpdatePtrs();

// ------------------ Easy Event Selection by LG Trigger Hit ----------------------- // 240501 changed a litte from Morino-san ana
   	int nlg = record.Trigger().NumLGHits();
		int tnlg = 0;
		int tnlg2 = 0;
		for (int k=0; k < nlg; k++){
			auto &hit = record.Trigger().LGHit(k);
			if(fabs(hit.Timing()) > 10 && fabs(hit.Timing()) < 200 tnlg++;
			if(fabs(hit.Timing()) < 10 ) tnlg2++;
		}
		if(tnlg2> 15) continue;
		if(tnlg> 30) continue;
		
		int tngt = 0;
		int ngt = record.Trigger().NumGTRHits();
		for(int k=0; jk < ngt; k++){
			auto &hit = record.Trigger().GTRHit(k);
			if(hit.Timing() > -50 && hit.Timing() < 350) tngt++;
		}
//		if(tngt > 12) continue;
		if(tngt > 36) continue;

// -------------------------------------------------------------------------------------

      check_file.ClearSimTrack();
      if (merge_mock_flag == kMergeSingleTrack) {
        if (mock_data.ReadATrack() != E16ANA_MockTrackOutputData::OK) {
          cerr << "mock data finished at " << n_physics_event << " events" << endl;
          break;
        }
        bool is_finished = false;
//        while (data_merger.IsDeadRegion(mock_data.Track())) {
        while (data_merger.IsDeadRegion(mock_data.Track()) || data_merger.IsDiscriDeadRegion(mock_data.Track())) {
          check_file.AddSimTrack(true, mock_data.Track());
          if (mock_data.ReadATrack() != E16ANA_MockTrackOutputData::OK) {
            cerr << "mock data finished at " << n_physics_event << " events" << endl;
            is_finished = true;
            break;
          }
        }
        if (is_finished) {
          break;
        }
        check_file.AddSimTrack(false, mock_data.Track());
        data_merger.MergeMockToRealData(0, mock_data.Track(), &record);
      } else if (merge_mock_flag == kMergeTrackPair) {
        int mock_read_flag;
        E16ANA_MockTrack mock_tracks[2];
        while (true) {
          if (mock_data_flag == kVectorMesonData) {
            mock_read_flag = ReadAndAddMockVectorMesonTrackPair(data_merger, &mock_data, mock_tracks, &check_file);
          } else if (mock_data_flag == kKsData) {
            mock_read_flag = ReadAndAddMockKsTrackPair(data_merger, &mock_data, mock_tracks, &check_file);
          }
          if (dead_region_flag == 1 && mock_read_flag == kReadMockDead) {
            continue;
          }
          break;
        }
        if (mock_read_flag == kReadMockError) {
          break;
        }
        data_merger.MergeMockToRealData(0, mock_tracks[0], &record);
        data_merger.MergeMockToRealData(1, mock_tracks[1], &record);
      }
#endif // TRACK_EFF_CHECK
      record.SSD().UpdatePtrs();
      record.GTR().UpdatePtrs();
      record.HBD().UpdatePtrs();
      record.LG().UpdatePtrs();
      record.Trigger().UpdatePtrs();
      check_file.AddRecord(*geometry, event0->EventID(), event0->SpillID(), event0->TimeStampInSpill(), event0->UT3().TriggerTime() % 8, record, lgbasic);
//      check_file.FillTree();
#ifndef DST1_EVENT_MIX
      E16DST_DST1TrackFactory(*geometry, *bfield_map, &fitter, &pair_fitter, kIsElectronRun, &record, &check_file);
#else // DST1_EVENT_MIX
      E16DST_DST1TrackFactory(*geometry, *bfield_map, &fitter, &pair_fitter, kIsElectronRun, &record, &prev_record, &check_file);
      E16DST_DST1SSDFactory(ssd_hits0, &prev_record.SSD());
      prev_record.SSD().AddHitAndClusterIds();
      E16DST_DST1GTRFactory(gtr_hits0, &prev_record.GTR(), gtrped, gtr_lorentz_angle_calib_params);
      prev_record.GTR().AddHitAndClusterIds();
      prev_record.UpdatePtrs();
#endif // DST1_EVENT_MIX

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
