#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include "TTree.h"
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

#include "E16ANA_STSGlobalGeometry.hh"
#include "STS/E16ANA_EventDisplay.hh"

using namespace std;
//namespace  bpo = boost::program_options;

const bool visualization = true;

constexpr bool kIsElectronRun = false;
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
  if (argc != 7) {
    cerr << "./bin [input.dst0] [output.root] [run ID] [physics event start] [physics event end (all : -1)] "
	 << "[display.pdf]" << endl;
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
  std::string display_pdf = argv[6];
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
  
//  E16ANA_WaveformFitter *wf1d_fitter = new E16ANA_WaveformFitter(hbd_waveform_template);
  E16ANA_WaveformFitterCRRC *wf1d_fitter = new E16ANA_WaveformFitterCRRC();
  E16ANA_MultiTrack fitter(bfield_map, geometry, 1);
  E16ANA_MultiTrack pair_fitter(bfield_map, geometry, 2);

  E16ANA_TrackCheckFile check_file(out_file_name, run_id);

  std::vector< std::map<int,TH1D* > > histos_gtr;
  std::vector<int> modules{101,102,103,104,106,107,108,109,206,207};
  histos_gtr.resize(3);

  for ( int i = 0; i<histos_gtr.size() ; i++){
    for( int imod = 0; imod < modules.size(); imod++){
      std::cout << "module ID " << modules[imod] << std::endl;
      TString name; name.Form("hist_ngtrclust_%d_%d",i,modules[imod]);
      std::cout << name << std::endl;
      histos_gtr[i][modules[imod]] = new TH1D(name,name,500,0,500);
    }
  }

  ////////
  E16ANA_EventDisplay display;
  display.SetGeometry(geometry);
  display.SetMirror();
  bool pdf_first = true;
  //  auto* ggeom = E16ANA_STSGlobalGeometry::instance();
  //auto* lgeom = E16ANA_STSGeometry::instance();
  if ( visualization ) display.SetPdfName(display_pdf);
 
  
  ////////////////////// PREPARE STS TREE
  TTree* tree_sts = new TTree("tree_sts","tree_sts");

  uint32_t event_id; // i
  uint32_t spill_id; // i

  int16_t l1_trgtype;         // S
  uint32_t trgtyp_rcv_count;  // i
  uint32_t trgdata_rcv_count; // i
  uint32_t trglocal_count;    // i
  uint64_t l1_geritimestamp;  // l
  int16_t gbt;                // S
  int16_t port;               // S
  int16_t trgtype;            // S
  int16_t trg_num_emu2geri;   // S
  uint64_t ut3timestamp;      // l
  int32_t ut3spill;           // I
  int32_t ut3event;           // I
  uint64_t emu_timestamp;     // l

  std::vector<int16_t> sts_module;
  std::vector<int16_t> sts_pn;
  std::vector<int16_t> sts_channel;
  std::vector<float> sts_peakheight;
  std::vector<float> sts_hittime;
  std::vector<float> sts_lx;
  std::vector<float> sts_gx;
  std::vector<float> sts_gy;
  std::vector<float> sts_gz;
  std::vector<uint64_t> sts_geriTimestamp;
  std::vector<uint16_t> sts_elink;
  std::vector<int> sts_tdc_l1geri;
  std::vector<int> sts_tdc_l1geri2;
  std::vector<long> sts_geri_l1geri;
  std::vector<uint16_t> sts_tdc;
  std::vector<uint16_t> sts_adc;

  auto clear_sts = [&](){
    sts_module.clear();
    sts_pn.clear(); 
    sts_channel.clear();
    sts_peakheight.clear();
    sts_hittime.clear();
    sts_lx.clear();
    sts_gx.clear();
    sts_gy.clear();
    sts_gz.clear();
    sts_geriTimestamp.clear();
    sts_elink.clear();
    sts_tdc_l1geri.clear();
    sts_tdc_l1geri2.clear();
    sts_geri_l1geri.clear();
    sts_tdc.clear();
    sts_adc.clear();
  };
  
  TString br_int16 = "/S";
  TString br_uint32 = "/i";
  TString br_uint64 = "/l";
  TString br_int32 = "/I";

  tree_sts->Branch("event",&event_id,"event"+br_uint32);
  tree_sts->Branch("spill",&spill_id,"spill"+br_uint32);

  tree_sts->Branch("l1_trgtype",&l1_trgtype,"l1_trgtype"+br_int16);
  tree_sts->Branch("trgtyp_rcv_count" ,&trgtyp_rcv_count ,"trgtyp_rcv_count"+br_uint32);
  tree_sts->Branch("trgdata_rcv_count",&trgdata_rcv_count,"trgdata_rcv_count"+br_uint32);
  tree_sts->Branch("trglocal_count",&trglocal_count,"trglocal_count"+br_uint32);
  tree_sts->Branch("l1_geritimestamp",&l1_geritimestamp,"l1_geritimestamp"+br_uint64);
  tree_sts->Branch("gbt",&gbt,"gbt"+br_int16);
  tree_sts->Branch("port",&port,"port"+br_int16);
  tree_sts->Branch("trgtype",&trgtype,"trgtype"+br_int16);
  tree_sts->Branch("trg_num_emu2geri",&trg_num_emu2geri,"trg_num_emu2geri"+br_int16);
  tree_sts->Branch("ut3timestamp",&ut3timestamp,"ut3timestamp"+br_uint64);

  tree_sts->Branch("ut3spill",&ut3spill,"ut3spill"+br_int32);
  tree_sts->Branch("ut3event",&ut3event,"ut3event"+br_int32);
  tree_sts->Branch("emu_timestamp",&emu_timestamp,"emu_timestamp"+br_uint64);

  tree_sts->Branch("sts_module",&sts_module);
  tree_sts->Branch("sts_pn",&sts_pn);
  tree_sts->Branch("sts_channel",&sts_channel);

  tree_sts->Branch("sts_peakheight",&sts_peakheight);
  tree_sts->Branch("sts_hittime",&sts_hittime);
  tree_sts->Branch("sts_elink",&sts_elink);
  tree_sts->Branch("sts_tdc_l1geri",&sts_tdc_l1geri);
  tree_sts->Branch("sts_tdc_l1geri2",&sts_tdc_l1geri2);
  tree_sts->Branch("sts_geri_l1geri",&sts_geri_l1geri);
  
  tree_sts->Branch("sts_lx",&sts_lx);
  tree_sts->Branch("sts_gx",&sts_gx);
  tree_sts->Branch("sts_gy",&sts_gy);
  tree_sts->Branch("sts_gz",&sts_gz);

  tree_sts->Branch("sts_geriTimestamp",&sts_geriTimestamp);
  ////////////////////////////////////////////////

  // PREPARE LG HITO
  TTree* tree_lg = new TTree("tree_lg","tree_lg");
  std::vector<int16_t> lg_module;
  std::vector<int16_t> lg_channel;
  std::vector<float> lg_peakheight;
  std::vector<float> lg_peaktime;
  std::vector<float> lg_baseline;
  std::vector<float> lg_baselinerms;
  std::vector<float> lg_integral;
  std::vector<float> lg_gx;
  std::vector<float> lg_gy;
  std::vector<float> lg_gz;
  
  auto clear_lg = [&](){
    lg_module.clear();
    lg_channel.clear();
    lg_peakheight.clear();
    lg_baseline.clear();
    lg_baselinerms.clear();
    lg_integral.clear();
    lg_gx.clear();
    lg_gy.clear();
    lg_gz.clear();
  };

  tree_lg->Branch("event",&event_id,"event"+br_uint32);
  tree_lg->Branch("spill",&spill_id,"spill"+br_uint32);
  tree_lg->Branch("lg_module",&lg_module);
  tree_lg->Branch("lg_channel",&lg_channel);
  tree_lg->Branch("lg_peakheight",&lg_peakheight);
  tree_lg->Branch("lg_peaktime",&lg_peaktime);
  tree_lg->Branch("lg_baseline",&lg_baseline);
  tree_lg->Branch("lg_baselinerms",&lg_baselinerms);
  tree_lg->Branch("lg_integral",&lg_integral);
  tree_lg->Branch("lg_gx",&lg_gx);
  tree_lg->Branch("lg_gy",&lg_gy);
  tree_lg->Branch("lg_gz",&lg_gz);

  /////////////////////////////////////////////

  /*
  ///////////////////// PREPARE STS TREE
  TTree* tree_gtr = new TTree("tree_gtr","tree_gtr");

  std::vector<int> gtr_module;
  std::vector<int> gtr_layer;
  std::vector<float> gtr_timing;
  std::vector<float> gtr_peaksum;

  auto clear_gtr = [&](){
    gtr_module.clear();
    gtr_layer.clear();
    gtr_timing.clear();
    gtr_peaksum.clear();
  };
  
  tree_gtr->Branch("event",&event_id,"event"+br_uint32);
  tree_gtr->Branch("spill",&spill_id,"spill"+br_uint32);
  tree_gtr->Branch("gtr_module",&gtr_module);
  tree_gtr->Branch("gtr_layer",&gtr_layer);
  tree_gtr->Branch("gtr_timing",&gtr_timing);
  tree_gtr->Branch("gtr_peaksum",&gtr_peaksum);
  */
  
  //////////////////////////////////////////
  
  
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
      auto& stsg_dst0         = event0->STSG();
      auto& sts_dst0          = event0->STS();
      auto& ssd_hits0         = event0->SSD();
      auto& gtr_hits0         = event0->GTR();
      auto& hbd_hits0         = event0->HBD();
      auto& lg_hits0          = event0->LG();
//      auto& trigger_gtr_hits0 = event0->TriggerGTR();
//      auto& trigger_hbd_hits0 = event0->TriggerHBD();
//      auto& trigger_lg_hits0  = event0->TriggerLG();
      event_id = event0->EventID();
      spill_id = event0->SpillID();
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
//      E16DST_DST1SSDFactory(ssd_hits0, &record.SSD());
//      record.SSD().AddHitAndClusterIds();
      E16DST_DST1GTRFactory(gtr_hits0, &record.GTR(), gtrped, gtr_lorentz_angle_calib_params);
      record.GTR().AddHitAndClusterIds();
      E16DST_DST1HBDFactory(hbd_hits0, hbd_calib, hbd_cut, wf1d_fitter, &record.HBD());
      record.HBD().AddHitAndClusterIds();
      E16DST_DST1LGFactory(lg_hits0, &record.LG(), 1, geometry); // w/ fit
      record.LG().AddHitAndClusterIds();
      E16DST_DST1STSFactory(stsg_dst0,sts_dst0, &record.STS());
#ifdef TMP_NIM_TRIGGER
      auto time_stamp = event0->TimeStamp();
      E16DST_DST1TriggerFactory(time_stamp, trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
#else // TMP_NIM_TRIGGER
      E16DST_DST1TriggerFactory(trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
#endif // TMP_NIM_TRIGGER
      record.Trigger().AddHitAndClusterIDs();
// HBD clustering w/o timing selection begin
      E16DST_DST1HBDFactory(hbd_hits0, hbd_calib, hbd_cut_wo_timing, wf1d_fitter, &record_for_another_hbd_cluster.HBD
());
      record_for_another_hbd_cluster.HBD().AddHitAndClusterIds();
      record_for_another_hbd_cluster.HBD().UpdatePtrs();
      // kaz removed .
      //check_file.AddHBDClusterss(*geometry, record_for_another_hbd_cluster.HBD());
// HBD clustering w/o timing selection end
#endif // REMOVE_REAL_HIT
#ifdef TRACK_EFF_CHECK
      record.SSD().UpdatePtrs();
      record.GTR().UpdatePtrs();
      record.HBD().UpdatePtrs();
      record.LG().UpdatePtrs();
      record.Trigger().UpdatePtrs();
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
      std::cout << "Warning : AddRecord removed to avoid problem." << std::endl;
      //check_file.AddRecord(*geometry, event0->EventID(), event0->SpillID(), event0->TimeStampInSpill(), event0->UT3().TriggerTime() % 8, record, lgbasic);
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
      std::cout << "################################################ my event loop" << std::endl;


      auto do_first_when_vis = [&]() {
	if ( visualization ) {
	  display.DrawSensor();
	  display.DrawRun(run_id);
	  display.DrawEvent(event_id);
	  display.DrawWires();
	  display.DrawTargets();
	}
      };
      
      do_first_when_vis();
       
      auto lgcut_tdc =  [](auto& hit) ->bool { return ( hit.PeakTime()>0 && hit.PeakTime()<90.); };
      
      /////////////////////// FILL LG STANDALONE TREE.
      clear_lg();
      auto& lg_hits1 = record.LG().Hits(); // this is a std::vector<T>
      if ( lg_hits1.size() > 0 )  {
	for ( auto& lghit : lg_hits1 ) {
	  TVector3 gpos = lghit.GlobalPos(*geometry);
	  //std::cout << "LG " << module << " ch=" << channel << "  ";
	  //gpos.Print();
	  lg_module.push_back(lghit.ModuleId());
	  lg_channel.push_back(lghit.ChannelId());
	  lg_peakheight.push_back(lghit.PeakHeight());
	  lg_peaktime.push_back(lghit.PeakTime());
	  lg_baseline.push_back(lghit.Baseline());
	  lg_baseline.push_back(lghit.BaselineRms());
	  lg_integral.push_back(lghit.Integral());
	  lg_gx.push_back(gpos.X());
	  lg_gy.push_back(gpos.Y());
	  lg_gz.push_back(gpos.Z());
	  if ( lgcut_tdc(lghit) ){
	    if ( visualization ) {
	      //display.DrawHit(gpos.X(),gpos.Y(),gpos.Z());
	      display.SetHitColor(kBlue);
	      display.DrawLGHitBox(lghit.ModuleId(),lghit.ChannelId());
	      display.SetHitColor(kRed);
	    }
	  }

	}
      }
      tree_lg->Fill();

      if ( stsg_dst0.NumberOfHits() > 1 ){
	std::cout << "++++++ STSGlobal: # of hits more than 1. Indication of merged DST0." << std::endl;
      }

      auto stscut_tdc = [](auto& hit) ->bool { return ( fabs(hit.Timing()+95)<100.);};
      auto stscut_adc = [](auto& hit) ->bool { return ( hit.PeakHeight() > 0.00001 ); };


      ///////////////// FILL STS STANDALONE TREE.

      if ( stsg_dst0.NumberOfHits() > 0 ) {
	auto& hitg0 = stsg_dst0.Hit(0);
	l1_trgtype        = hitg0.get_l1_trgtype();
	trgtyp_rcv_count  = hitg0.get_trgtyp_rcv_count();
	gbt               = hitg0.get_gbt();
	port              = hitg0.get_port();
	trg_num_emu2geri  = hitg0.get_trg_num_emu2geri();
	trgtyp_rcv_count  = hitg0.get_trgtyp_rcv_count();
	trgdata_rcv_count = hitg0.get_trgdata_rcv_count();
	trglocal_count    = hitg0.get_trglocal_count();
	l1_geritimestamp  = hitg0.get_l1_geritimestamp();
	ut3timestamp      = hitg0.get_ut3timestamp();
	ut3spill          = hitg0.get_ut3spill();
	emu_timestamp     = hitg0.get_emu_timestamp();
      }else{
	continue;
      }

      clear_sts();

      auto fill_sts = [&](auto& hit1) {
	sts_module.push_back(hit1.ModuleId());
	sts_pn.push_back(hit1.PN());
	sts_channel.push_back(hit1.ChannelId());
	sts_peakheight.push_back(hit1.PeakHeight());
	sts_lx.push_back(hit1.LocalPos().X());
	sts_elink.push_back(hit1.Elink());
	
	if ( hit1.TDC() == 0xffff ) {
	  sts_tdc_l1geri2.push_back(-1000000);
	}else{
	  auto& hitg0 = stsg_dst0.Hit(0);
	  int geri14 = (int) ( hitg0.get_l1_geritimestamp()&0b11111111111111 );
	  sts_tdc_l1geri2.push_back((int)hit1.TDC() - geri14);
	}
	
	if ( fabs(hit1.Timing()-E16DST_DST1Constant::kInvalidValue) > 0.000001 ) {
	  sts_hittime.push_back(hit1.Timing());
	  sts_tdc_l1geri.push_back(hit1.Timing()-(l1_geritimestamp&0b11111111111111));
	}else{
	  sts_hittime.push_back   (-1000000.);
	  sts_tdc_l1geri.push_back(-1000000.);
	}
	
	TVector3 vec = hit1.GlobalPos();
	sts_gx.push_back(vec.X());
	sts_gy.push_back(vec.Y());
	sts_gz.push_back(vec.Z());
	sts_geriTimestamp.push_back(hit1.GeriTimestamp());
	int tmp = (   (int)(hit1.GeriTimestamp() & 0xffffffff) - (int)(l1_geritimestamp &0xffffffff) );
	sts_geri_l1geri.push_back(tmp);
      };
      
      auto& sts_hits1 = record.STS().Hits(); // hits1 is std::vector<T>;
      
      auto& gtr_clusters1 = record.GTR().Clusters();
      std::cout << "# of clusters in GTR : " << gtr_clusters1.size() << std::endl;

      std::vector<std::map<int,int> > nclus_gtr;
      nclus_gtr.resize(3);

      if ( gtr_clusters1.size() > 0 ) {
	for( auto& gtr_clust1 : gtr_clusters1 ){
	  try {
	    gtr_clust1.Type(); // 0 :x, 1:y 2:yb  100:y+yb, 200-300:y only.
	    if ( gtr_clust1.Type() != 0 ) continue;
	    nclus_gtr[gtr_clust1.LayerId()][gtr_clust1.ModuleId()]++;
	  } catch (...) {
	    std::cout << "ERROR: layer " << gtr_clust1.LayerId() << " mod " << gtr_clust1.ModuleId() << std::endl;
	  }
	}
      }

      for( int i = 0;i<histos_gtr.size();i++){
	for ( auto mod : modules ) {
	  try{
	    histos_gtr.at(i).at(mod)->Fill(nclus_gtr[i][mod]);
	  }catch (...){
	    std::cout << "error  i" << i << "  mod " << mod << std::endl;
	  }
	}
      }

      //class enum TGTType { TGT, WireR, WireL };
      //TGTType tgt_type = TGT;
      
      std::vector<TVector3> wiresR={ TVector3( 20.,0.,40.), TVector3( 20.,0.,-40.) };
      std::vector<TVector3> wiresL={ TVector3(-20.,0.,40.), TVector3(-20.,0.,-40.) };
      //TVector3 targets[3] = { TVector3(0.,0.,20), TVector3(0,0,0), TVector3(0,0,-20) };

      //std::vector<TVector3> origin = wireR;

      TVector3 origin(0.,0.,0.);
      auto get_phi = [](TVector3& vec) ->double {
	double phi = vec.Phi();
	if ( phi < - 3.1415926535/2. ) phi += 3.*3.14159265/2.;
	return phi;
      };

      bool has_sts_hits = false;

      if ( sts_hits1.size() > 0 ) {
	for( auto& hit1 : sts_hits1 ) {
	  fill_sts(hit1);
	  if ( visualization ){
	    if ( fabs(hit1.Timing()+95.) <100  && hit1.PeakHeight()>0 ) {
	      has_sts_hits = true;

	      TVector3 sts_vec = hit1.GlobalPos();
	      double sts_gpos[3]={sts_vec.X(),sts_vec.Y(),sts_vec.Z()};
	      display.DrawHit(sts_gpos);

	      TVector3 extpos = sts_vec*15;
	      double ext_gpos[3] = {extpos.X(),extpos.Y(),extpos.Z()};
	      display.SetLineColor(kBlue);
	      display.DrawLine(sts_gpos,ext_gpos);
	      
	      bool lg_found = false;

	      TVector2 sts_vec2(sts_vec.Z(),sts_vec.X());
	      
	      auto& lg_hits1 = record.LG().Hits(); // this is a std::vector<T>
	      if ( lg_hits1.size() > 0 )  {
		for ( auto& lghit : lg_hits1 ) {
		  if( lghit.ModuleId() == hit1.ModuleId() ||
		      abs(lghit.ModuleId() - hit1.ModuleId())<=1 ) {
		    if (! lgcut_tdc(lghit) ) continue;
		    TVector3 lgpos = lghit.GlobalPos(*geometry);
		    TVector2 lg_vec2(lgpos.Z(),lgpos.X());
		    if ( fabs(sts_vec2.Phi()-lg_vec2.Phi())*lgpos.Mag() < 65. ) {
		      lg_found = true;
		      display.SetHitColor(kRed);
		      display.DrawLGHitBox(lghit.ModuleId(),lghit.ChannelId());
		    }
		  }
		}
	      }
	      if (! lg_found ) continue;
	      
	      


	    }
	  }
	}
      }
      tree_sts->Fill();
      //auto& gtr_clusters1 = record.GTR().Clusters();
      if ( gtr_clusters1.size() > 0 ) {
	for ( auto& gtr_clust1 : gtr_clusters1 ) {
	  if ( visualization ) {
	    TVector3 pos = gtr_clust1.GlobalPos(*geometry);
	    double global[3] = {pos.X(),pos.Y(),pos.Z()};
	    display.DrawHit(global);
	  }
	}
      }

      /////////////////////// FILL GTR STANDALONE TREE.
      /*
      clear_gtr();
      auto& gtr_clusters1 = record.GTR().Clusters();
      if ( gtr_clusters1.size() > 0 ) {
	for ( auto& gtr_clust1 : gtr_clusters1 ) {
	  gtr_module.push_back(gtr_clust1.ModuleId());
	  gtr_layer.push_back(gtr_clust1.LayerId());
	  gtr_timing.push_back(gtr_clust1.Timing());
	  gtr_peaksum.push_back(gtr_clust1.PeakSum());
	  //

	  TVector3 pos = gtr_clust1.GlobalPos(*geometry);
	  double global[3] = {pos.X(),pos.Y(),pos.Z()};
	  display.DrawHit(global);
	}
      }
      tree_gtr->Fill();
      */


      //if ( visualization ) {
      //display.SetHitColor(kBlue);
      ///display.DrawHit(global_interp);
      //display.SetHitColor(kRed);
      //}
    
      ///////////////////////// STS-LG Correlation
      


      // 

      /*
      //auto LR = [](int mod) { return (mod < 105); };
      auto* ggeom = E16ANA_STSGlobalGeometry::instance();
      auto& lg_hits1 = record.LG().Hits(); // this is a std::vector<T>
      if ( lg_hits1.size() == 0 ) continue;
      auto& sts_hits1 = record.STS().Hits(); // hits1 is std::vector<T>;
      if ( sts_hits1.size() > 0 ) {
	for( auto& sts_hit : sts_hits1 ) {
	  int module_sts = sts_hit.ModuleId();
	  for ( auto& lg_hit : lg_hits1 ){
	    int module_lg = lg_hit.ModuleId();
	    if ( lr == LR(module_lg) ) {
	      
	      // Try
	      //ggeom->CalcPointOnPlane();
	    }
	  }
	}
      }
      */

      if ( visualization ) {
	display.DrawUpdate();
	if ( pdf_first ) {
	  display.SavePdfStart();
	  pdf_first = false;
	}else{
	  display.SavePdf();
	}
      }


      record.Tracks().Print();
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

  if ( visualization ) {
    display.DrawUpdate();
    if ( pdf_first ) {
      display.SavePdfStart();
      pdf_first = false;
    }else{
      display.SavePdf();
    }
  }

  if ( visualization ) display.SavePdfEnd();

  check_file.cd();
  for ( int i = 0;i<histos_gtr.size() ; i++){
    for ( auto& h : histos_gtr[i] ) {
      h.second->Write();
    }
  }
  


  delete geometry;
  delete dst0;
  return 0;
}
