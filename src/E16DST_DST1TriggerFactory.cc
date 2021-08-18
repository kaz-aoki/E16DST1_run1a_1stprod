#include "E16DST_DST1.hh"

#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16DST_TriggerChannelMap.hh"
#include "E16ANA_TriggerCoincidenceMap.hh"

uint16_t E16ANA_TriggerTime(uint64_t _timestamp, uint32_t _tdc) {
  int32_t time = (_timestamp * 8) % 0x40000 - _tdc;
  if (time >= 0) {
    return uint16_t{time};
  } else {
    return uint16_t{time + 0x40000};
  }
}

bool E16ANA_TriggerSingleHitFactory(E16DST_DST0TriggerHit& hit0, uint64_t timestamp, int detector, E16DST_DST1TriggerHit* hit1) {
  hit1->SetInvalid();
  hit1->SetIds(hit0.ModuleID(), hit0.ChannelID());
  hit1->SetDetector(detector);
  hit1->SetTiming(float{E16ANA_TriggerTime(timestamp, hit0.Time())});
  return true;
}

int E16ANA_TriggerHitAndClusterFactory(E16DST_DST0Detector<E16DST_DST0TriggerHit>& hits0, uint64_t timestamp, int detector, E16DST_DST0Detector<E16DST_DST1TriggerHit>* hits1, E16DST_DST0Detector<E16DST_DST1TriggerCluster>* clusters1) {
  auto max_hit = hits0.NumberOfHits();
  hits1->Resize(max_hit);
  for (int n_hit = 0; n_hit < max_hit; ++n_hit) {
    E16ANA_TriggerSingleHitFactory(hits0.Hit(n_hit), timestamp, detector, &hits1->Hit(n_hit));
  }
  return hits1->GetEventSize() + clusters1->GetEventSize();
}

//int E16ANA_TriggerNumTriggers(E16DST_DST0UT3& ut3) {
//  // must use calib DB
//  auto& calib = E16ANA_CalibDBManager::Instance();
//  int n_trigger = 0;
//  auto max_track = ut3.NumberOfTracks();
//  std:;vector<E16DST_DST0TriggerHit*> tracks(max_track);
//  for (int n_track = 0; n_track < max_track; ++n_track) {
//    auto track = ut3.Track(n_track);
//    for (const auto& ref_track : tracks) {
//      
//
//    }
//    tracks[n_track] = &track;
//  }

int E16ANA_TriggerSearchCoincidenceHit(int module_id, int channel_id, E16DST_DST0Detector<E16DST_DST0TriggerHit>& hits, std::vector<int>* coincidence_hit_orders, std::vector<E16DST_DST0Hit>* unrecorded_hits) {
  // must use calib DB
  auto& calib = E16ANA_CalibDBManager::Instance();
  auto n_hits = hits.NumberOfHits();
  int n_coincidence_hits = 0;
  for (int hit_num = 0; hit_num < n_hits; ++hit_num) {
    auto hit = hits.Hit(hit_num);
    if (hit.ModuleID() == module_id && hit.ChannelID() == channel_id) {
      coincidence_hit_orders->emplace_back(hit_num);
      ++n_coincidence_hits;
    }
  }
  if (n_coincidence_hits == 0) {
    auto hit = new E16DST_DST0Hit();
    hit->SetIDs(module_id, channel_id);
    unrecorded_hits->emplace_back(*hit);
    coincidence_hit_orders->emplace_back(-unrecorded_hits->size());
  }
  return n_coincidence_hits;
}

int E16DST_DST1TriggerFactory(E16DST_DST0Detector<E16DST_DST0TriggerHit>& gtr_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& hbd_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& lg_hits, E16DST_DST0UT3& ut3, uint64_t timestamp, E16DST_DST1Trigger* trigger) {
  static auto channel_map      = new E16DST_TriggerChannelMap(static_cast<std::string>(TriggerChannelMapFiles[0]), static_cast<std::string>(TriggerChannelMapFiles[1]), static_cast<std::string>(TriggerChannelMapFiles[2]));
  static auto coincidence_maps = new E16ANA_TriggerCoincidenceMap(CoincidenceMapFiles, TriggerChannelMapFiles);
  
  trigger->Clear();
  E16ANA_TriggerHitAndClusterFactory(gtr_hits, timestamp, E16DST_DST1Constant::kGTR300, &trigger->GTRHits(), &trigger->GTRClusters());
  E16ANA_TriggerHitAndClusterFactory(hbd_hits, timestamp, E16DST_DST1Constant::kHBD,    &trigger->HBDHits(), &trigger->HBDClusters());
  E16ANA_TriggerHitAndClusterFactory(lg_hits,  timestamp, E16DST_DST1Constant::kLG,     &trigger->LGHits(),  &trigger->LGClusters());
  auto max_track =ut3.NumberOfTracks();
  trigger->Tracks().Resize(max_track);
  for (int n_track = 0; n_track < max_track; ++n_track) {
    E16ANA_TriggerSingleHitFactory(ut3.Track(n_track), timestamp, E16DST_DST1Constant::kLG, &trigger->Tracks().Hit(n_track));
  }
  
//  n_teriggers = E16ANA_TriggerNumTrigger(ut3);

  // track_set
  static std::array<std::array<bool, E16DST_Constant::NModules * E16DST_Constant::NTriggerChannelsGTR>, 2> gtr_maps;
  static std::array<std::array<bool, E16DST_Constant::NModules * E16DST_Constant::NTriggerChannelsHBD>, 2> hbd_maps;
  E16DST_DST0UT3Hitmap hitmaps;
//std::cout << std::endl;
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
 
  auto track_set = new E16DST_DST1TriggerTrackSet();
  auto n_tracks = ut3.NumberOfTracks();
  trigger->TrackSets().Reserve(n_tracks);
  for (int track_num = 0; track_num < n_tracks; ++track_num) {
    track_set->Clear();
    auto track = ut3.Track(track_num);
    int is_new;
    if (track.HitNumber() < 64) {
      is_new = 0;
    } else {
      is_new = 1;
    }
    track_set->LGHitOrders().emplace_back(track_num);
    bool is_mag_field = true; // tmp
    auto coincidence_map = coincidence_maps->CoincidenceMap(track.ModuleID(), track.ChannelID(), is_mag_field);
    for (int channel = 0; channel < coincidence_map.gtr_map.size(); ++channel) {
      if (coincidence_map.gtr_map[channel] && gtr_maps[is_new][E16DST_Constant::NTriggerChannelsGTR * coincidence_map.gtr_start_module + channel]) {
        auto ids = channel_map->GetDetectorIDs(32 * (coincidence_map.gtr_start_module + int{channel / E16DST_Constant::NTriggerChannelsGTR}) + channel % E16DST_Constant::NTriggerChannelsGTR);
        E16ANA_TriggerSearchCoincidenceHit(ids.moduleID, ids.channelID, gtr_hits, &track_set->GTRHitOrders(), &track_set->GTRUnrecordedHits());
      }
    }
    for (int channel = 0; channel < coincidence_map.hbd_map.size(); ++channel) {
      if (coincidence_map.hbd_map[channel] && hbd_maps[is_new][E16DST_Constant::NTriggerChannelsHBD * coincidence_map.hbd_start_module + channel]) {
        auto ids = channel_map->GetDetectorIDs(256 + 64 * coincidence_map.hbd_start_module + 32 * int{channel / (E16DST_Constant::NTriggerChannelsHBD / 2)} + channel % (E16DST_Constant::NTriggerChannelsHBD / 2));
        E16ANA_TriggerSearchCoincidenceHit(ids.moduleID, ids.channelID, hbd_hits, &track_set->HBDHitOrders(), &track_set->HBDUnrecordedHits());
      }
    }
    trigger->TrackSets().PushBack(*track_set);
  }
  delete track_set;
  track_set = nullptr;
  return 1;
}
