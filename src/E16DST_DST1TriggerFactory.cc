#include "E16DST_DST1.hh"

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_TriggerConstant.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16DST_TriggerChannelMap.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16ANA_TriggerCoincidenceMap.hh"

int E16ANA_TriggerTime(E16ANA_TriggerCalibParam& trigger_param, int detector, uint32_t trigger_tdc, uint32_t tdc) {
  auto delay         = trigger_param.MrgDelay(detector - E16DST_DST1Constant::kNumTriggerOffset);
  auto trigger_delay = trigger_param.MrgDelay(E16DST_DST1Constant::kLG - E16DST_DST1Constant::kNumTriggerOffset);
  int offset = 0;
  if (int{trigger_tdc} - int{tdc} > 10000) {
    offset = -0x40000;
  } else if (int{trigger_tdc} - int{tdc} < -10000) {
    offset = 0x40000;
  }
  return int{trigger_tdc} - int{tdc} + E16ANA_TriggerConstant::kMRGDelayOrderNs * (trigger_delay - delay) + offset;
}

bool E16ANA_TriggerSingleHitFactory(E16ANA_TriggerCalibParam& trigger_param, E16DST_DST0TriggerHit& hit0, uint32_t trigger_tdc, int detector, E16DST_DST1TriggerHit* hit1) {
  hit1->SetInvalid();
  hit1->SetIds(hit0.ModuleID(), hit0.ChannelID());
  hit1->SetDetector(detector);
  hit1->SetTiming(float{E16ANA_TriggerTime(trigger_param, detector, trigger_tdc, hit0.Time())});
  return true;
}

int E16ANA_TriggerHitAndClusterFactory(E16ANA_TriggerCalibParam& trigger_param, E16DST_DST0Detector<E16DST_DST0TriggerHit>& hits0, uint32_t trigger_tdc, int detector, std::vector<E16DST_DST1TriggerHit>* hits1, std::vector<E16DST_DST1TriggerCluster>* clusters1) {
  auto max_hit = hits0.NumberOfHits();
  hits1->resize(max_hit);
  for (int n_hit = 0; n_hit < max_hit; ++n_hit) {
    E16ANA_TriggerSingleHitFactory(trigger_param, hits0.Hit(n_hit), trigger_tdc, detector, &hits1->at(n_hit));
  }
  return hits1->size() * sizeof(E16DST_DST1TriggerHit);
}

bool E16ANA_TriggerIsGenerateTrigger(E16ANA_TriggerCalibParam& trigger_param, E16DST_DST0TriggerHit& track0, E16DST_DST0TriggerHit& track1) {
  auto min_width    = trigger_param.MinimumWidth();
  auto max_width    = trigger_param.MaximumWidth();
  auto time_width   = trigger_param.TimeWidth();
  auto is_hbd_cut   = trigger_param.IsHBDCut();
  auto is_y_cut     = trigger_param.IsYCut();
  auto is_max_width = trigger_param.IsMaximumWidth();
  int pos_width = 7 * (track0.ModuleID() - track1.ModuleID()) + track0.ChannelID() / 10 - track1.ChannelID() / 10;




  return false;
}

int E16ANA_TriggerNumTriggers(E16ANA_TriggerCalibParam& trigger_param, E16DST_DST0UT3& ut3) {
  auto trigger_type = ut3.TriggerType();
  if (trigger_type == E16ANA_TriggerConstant::kMultiTrack || trigger_type == E16ANA_TriggerConstant::kClock || trigger_type == E16ANA_TriggerConstant::kNim) {
    return 1;
  } else if (trigger_type == E16ANA_TriggerConstant::k1Track) {
    return ut3.NumberOfTracks();
  } else if (trigger_type == E16ANA_TriggerConstant::kTrackCorreration) {
    int n_trigger = 0;
    auto max_track = ut3.NumberOfTracks();
    std::vector<E16DST_DST0TriggerHit*> tracks(max_track);
    for (int n_track0 = 0; n_track0 < max_track; ++n_track0) {
      auto& track0 = ut3.Track(n_track0);
      for (int n_track1 = n_track0; n_track1 < max_track; ++n_track1) {
        auto& track1 = ut3.Track(n_track1);
        if (E16ANA_TriggerIsGenerateTrigger(trigger_param, track0, track1)) {
          ++n_trigger;
        }
      }
    }
    return n_trigger;
  }
  return -1;
}

int E16ANA_TriggerSearchCoincidenceHit(int coincidence_window, int track_coarse_time, int module_id, int channel_id, E16DST_DST0Detector<E16DST_DST0TriggerHit>& hits, std::vector<int16_t>* coincidence_hit_orders, std::vector<bool>* coincidence_hit_is_used, std::vector<E16DST_DST0Hit>* unrecorded_hits) {
  auto n_hits = hits.NumberOfHits();
  int n_coincidence_hits = 0;
  for (int hit_num = 0; hit_num < n_hits; ++hit_num) {
    auto& hit = hits.Hit(hit_num);
    if (hit.ModuleID() == module_id && hit.ChannelID() == channel_id) {
      coincidence_hit_orders->emplace_back(hit_num);
      auto coarse_time = hit.Time() / E16ANA_TriggerConstant::kMRGTransmitCycleNs;
      int coarse_time_diff = track_coarse_time - coarse_time;
      if (coarse_time_diff >= 0 && coarse_time_diff < coincidence_window) {
        coincidence_hit_is_used->emplace_back(true);
      } else {
        coincidence_hit_is_used->emplace_back(false);
      }
      ++n_coincidence_hits;
    }
  }
  if (n_coincidence_hits == 0) {
    unrecorded_hits->push_back(E16DST_DST0Hit());
    unrecorded_hits->back().SetIDs(module_id, channel_id);
    coincidence_hit_orders->emplace_back(-unrecorded_hits->size());
    coincidence_hit_is_used->emplace_back(false);
  }
  return n_coincidence_hits;
}

int E16DST_DST1TriggerFactory(E16ANA_TriggerCalibParam& trigger_param, E16DST_DST0Detector<E16DST_DST0TriggerHit>& gtr_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& hbd_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& lg_hits, E16DST_DST0UT3& ut3, E16DST_DST1Trigger* trigger) {
  bool is_mag_field = true; // tmp
  auto gtr_coincidence_window = E16ANA_TriggerConstant::kMRGTransmitCycleNs * trigger_param.CoincidenceWindow(E16DST_DST1Constant::kGTR - E16DST_DST1Constant::kNumTriggerOffset);
  auto hbd_coincidence_window = E16ANA_TriggerConstant::kMRGTransmitCycleNs * trigger_param.CoincidenceWindow(E16DST_DST1Constant::kHBD - E16DST_DST1Constant::kNumTriggerOffset);

  static auto* channel_map      = new E16DST_TriggerChannelMap(static_cast<std::string>(TriggerChannelMapFiles[0]), static_cast<std::string>(TriggerChannelMapFiles[1]), static_cast<std::string>(TriggerChannelMapFiles[2]));
  static auto* coincidence_maps = new E16ANA_TriggerCoincidenceMap(CoincidenceMapFiles, TriggerChannelMapFiles);
  trigger->Clear();

  auto trigger_tdc = ut3.TriggerTime();
  E16ANA_TriggerHitAndClusterFactory(trigger_param, gtr_hits, trigger_tdc, E16DST_DST1Constant::kGTR, &trigger->GTRHits(), &trigger->GTRClusters());
  E16ANA_TriggerHitAndClusterFactory(trigger_param, hbd_hits, trigger_tdc, E16DST_DST1Constant::kHBD, &trigger->HBDHits(), &trigger->HBDClusters());
  E16ANA_TriggerHitAndClusterFactory(trigger_param, lg_hits,  trigger_tdc, E16DST_DST1Constant::kLG,  &trigger->LGHits(),  &trigger->LGClusters());
  auto max_track =ut3.NumberOfTracks();
  trigger->Tracks().resize(max_track);
  for (int n_track = 0; n_track < max_track; ++n_track) {
    E16ANA_TriggerSingleHitFactory(trigger_param, ut3.Track(n_track), trigger_tdc, E16DST_DST1Constant::kLG, &trigger->Tracks()[n_track]);
  }
  
  // track_set
  static std::array<std::array<bool, E16DST_Constant::NModules * E16DST_Constant::NTriggerChannelsGTR>, 2> gtr_maps;
  static std::array<std::array<bool, E16DST_Constant::NModules * E16DST_Constant::NTriggerChannelsHBD>, 2> hbd_maps;
  E16DST_DST0UT3Hitmap hitmaps;
  for (int packet = 0; packet < 2; ++packet) {
    if (packet == 0) {
      hitmaps = ut3.HitmapOld();
    } else {
      hitmaps = ut3.Hitmap();
    }
    for (int module = 0; module < E16DST_Constant::NModules; ++module) {
      for (int channel = 0; channel < E16DST_Constant::NTriggerChannelsGTR; ++channel) {
        if (hitmaps.GTR[module][channel] == 1) {
          gtr_maps[packet][E16DST_Constant::NTriggerChannelsGTR * module + channel] = true;
        } else {
          gtr_maps[packet][E16DST_Constant::NTriggerChannelsGTR * module + channel] = false;
        }
      }
      for (int channel = 0; channel < E16DST_Constant::NTriggerChannelsHBD; ++channel) {
        if (hitmaps.HBD[module][channel] == 1) {
          E16DST_TriggerChannelMap::IDs ids;
          hbd_maps[packet][E16DST_Constant::NTriggerChannelsHBD * module + channel] = true;
        } else {
          hbd_maps[packet][E16DST_Constant::NTriggerChannelsHBD * module + channel] = false;
        }
      }
    }
  }

  auto n_tracks = ut3.NumberOfTracks();
  trigger->TrackSets().resize(n_tracks);
  auto run_id = trigger_param.RunId();
  std::array<int, 2> coarse_time;
  coarse_time.fill(E16DST_DST1Constant::kInvalidValue);
  for (int track_num = 0; track_num < n_tracks; ++track_num) {
    auto& track = ut3.Track(track_num);
    int track_coarse_time = track.Time() / E16ANA_TriggerConstant::kMRGTransmitCycleNs;
    if (coarse_time[0] == E16DST_DST1Constant::kInvalidValue) {
      coarse_time[0] = track_coarse_time;
    } else if (track_coarse_time != coarse_time[0]) {
      coarse_time[1] = track_coarse_time;
      break;
    }
  }
  std::sort(coarse_time.begin(), coarse_time.end());
  for (int track_num = 0; track_num < n_tracks; ++track_num) {
    auto& track_set = trigger->TrackSets()[track_num];
    track_set.Clear();
    auto& track = ut3.Track(track_num);
    int is_new;
    int track_coarse_time = track.Time() / E16ANA_TriggerConstant::kMRGTransmitCycleNs;
    if (run_id < 30000) {
      if (track_coarse_time == coarse_time[0]) {
        is_new = 0;
      } else {
        is_new = 1;
      }
    } else {
      if (track.HitNumber() < 64) {
        is_new = 0;
      } else {
        is_new = 1;
      }
    }
    track_set.LGHitOrders().emplace_back(track_num);
    auto& coincidence_map = coincidence_maps->CoincidenceMap(track.ModuleID(), track.ChannelID(), is_mag_field);
    for (int channel = 0; channel < coincidence_map.gtr_map.size(); ++channel) {
      if (coincidence_map.gtr_map[channel] && gtr_maps[is_new][E16DST_Constant::NTriggerChannelsGTR * coincidence_map.gtr_start_module + channel]) {
        auto ids = channel_map->GetDetectorIDs(32 * (coincidence_map.gtr_start_module + int{channel / E16DST_Constant::NTriggerChannelsGTR}) + channel % E16DST_Constant::NTriggerChannelsGTR);
        E16ANA_TriggerSearchCoincidenceHit(gtr_coincidence_window, track_coarse_time, ids.moduleID, ids.channelID, gtr_hits, &track_set.GTRHitOrders(), &track_set.GTRHitIsUsed(), &track_set.GTRUnrecordedHits());
      }
    }
    for (int channel = 0; channel < coincidence_map.hbd_map.size(); ++channel) {
      if (coincidence_map.hbd_map[channel] && hbd_maps[is_new][E16DST_Constant::NTriggerChannelsHBD * coincidence_map.hbd_start_module + channel]) {
        auto ids = channel_map->GetDetectorIDs(256 + 64 * coincidence_map.hbd_start_module + 32 * int{channel / (E16DST_Constant::NTriggerChannelsHBD / 2)} + channel % (E16DST_Constant::NTriggerChannelsHBD / 2));
        E16ANA_TriggerSearchCoincidenceHit(hbd_coincidence_window, track_coarse_time, ids.moduleID, ids.channelID, hbd_hits, &track_set.HBDHitOrders(), &track_set.HBDHitIsUsed(), &track_set.HBDUnrecordedHits());
      }
    }
  }

  auto n_hits = lg_hits.NumberOfHits();
  trigger->HitSets().resize(n_hits);
  for (int hit_num = 0; hit_num < n_hits; ++hit_num) {
    auto& hit_set = trigger->HitSets()[hit_num];
    hit_set.Clear();
    auto& hit = lg_hits.Hit(hit_num);
    int is_new;
    int hit_coarse_time = hit.Time() / E16ANA_TriggerConstant::kMRGTransmitCycleNs;
    if (hit_coarse_time == coarse_time[0]) {
      is_new = 0;
    } else if (hit_coarse_time == coarse_time[1]) {
      is_new = 1;
    } else {
      continue;
    }
    hit_set.LGHitOrders().emplace_back(hit_num);
    auto& coincidence_map = coincidence_maps->CoincidenceMap(hit.ModuleID(), hit.ChannelID(), is_mag_field);
    for (int channel = 0; channel < coincidence_map.gtr_map.size(); ++channel) {
      if (coincidence_map.gtr_map[channel] && gtr_maps[is_new][E16DST_Constant::NTriggerChannelsGTR * coincidence_map.gtr_start_module + channel]) {
        auto ids = channel_map->GetDetectorIDs(32 * (coincidence_map.gtr_start_module + int{channel / E16DST_Constant::NTriggerChannelsGTR}) + channel % E16DST_Constant::NTriggerChannelsGTR);
        E16ANA_TriggerSearchCoincidenceHit(gtr_coincidence_window, hit_coarse_time, ids.moduleID, ids.channelID, gtr_hits, &hit_set.GTRHitOrders(), &hit_set.GTRHitIsUsed(), &hit_set.GTRUnrecordedHits());
      }
    }
    for (int channel = 0; channel < coincidence_map.hbd_map.size(); ++channel) {
      if (coincidence_map.hbd_map[channel] && hbd_maps[is_new][E16DST_Constant::NTriggerChannelsHBD * coincidence_map.hbd_start_module + channel]) {
        auto ids = channel_map->GetDetectorIDs(256 + 64 * coincidence_map.hbd_start_module + 32 * int{channel / (E16DST_Constant::NTriggerChannelsHBD / 2)} + channel % (E16DST_Constant::NTriggerChannelsHBD / 2));
        E16ANA_TriggerSearchCoincidenceHit(hbd_coincidence_window, hit_coarse_time, ids.moduleID, ids.channelID, hbd_hits, &hit_set.HBDHitOrders(), &hit_set.HBDHitIsUsed(), &hit_set.HBDUnrecordedHits());
      }
    }
  }
  
  trigger->SetNumTriggers(E16ANA_TriggerNumTriggers(trigger_param, ut3));

  return 1;
}
