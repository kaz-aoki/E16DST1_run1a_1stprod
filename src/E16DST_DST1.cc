#include "E16DST_DST1.hh"

template <class T, class U>
int E16DST_DST1Detector<T, U>::Write(E16DST_File* fp) {
}

template <class T, class U>
int E16DST_DST1Detector<T, U>::Read(E16DST_File* fp) {
}

template <class T, class U>
void E16DST_DST1Detector<T, U>::Append(E16DST_DST1Detector<T, U>& rhs) {
}

void E16DST_DST1Cluster::SetHitOrders(std::vector<int>& _hit_orders) {
  hit_orders.Reserve(_hit_orders.size());
  for (const auto& hit_order : _hit_orders) {
    hit_orders.PushBack(hit_order);
  }
}

double E16DST_DST1SSDHit::LocalX() {
}

TVector3 E16DST_DST1SSDHit::LocalPos(E16ANA_GeometryV2& geometry) {
}

TVector3 E16DST_DST1SSDHit::GlobalPos(E16ANA_GeometryV2& geometry) {
}

double E16DST_DST1SSDCluster::LocalX() {
}

TVector3 E16DST_DST1SSDCluster::LocalPos() {
}

TVector3 E16DST_DST1SSDCluster::GlobalPos(E16ANA_GeometryV2& geometry) {
}

double E16DST_DST1GTRHit::LocalX() {
}

TVector3 E16DST_DST1GTRHit::LocalPos(E16ANA_GeometryV2& geometry) {
}

TVector3 E16DST_DST1GTRHit::GlobalPos(E16ANA_GeometryV2& geometry) {
}

double E16DST_DST1GTRCluster::LocalX() {
//    return center_of_gravity; 
}

TVector3 E16DST_DST1GTRCluster::LocalPos() {
//    return TVector3(center_of_gravity, 0.0, 0.0);
}

TVector3 E16DST_DST1GTRCluster::GlobalPos(E16ANA_GeometryV2& geometry) {
//    TVector3(geometry.GTR(ModuleId2020To2013(module_id), layer_id).GetGPos(center_of_grabity, 0.0, 0.0));
}

TVector3 E16DST_DST1HBDHit::LocalPos(E16ANA_GeometryV2& geometry) {
}

TVector3 E16DST_DST1HBDHit::GlobalPos(E16ANA_GeometryV2& geometry) {
}

TVector3 E16DST_DST1HBDCluster::LocalPos() {
}

TVector3 E16DST_DST1HBDCluster::GlobalPos(E16ANA_GeometryV2& geometry) {
}

TVector3 E16DST_DST1LGHit::LocalPos(E16ANA_GeometryV2& geometry) {
  TVector3 gpos = {E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue};
  TVector3 lpos = {E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue};
  gpos = geometry.LG(3 * (109 - module_id) + 1, channel_id)->GetDetectorCenter();
  lpos = geometry.LGVD(3 * (109 - module_id) + 1)->GetLPos(gpos);
  return lpos;
}

TVector3 E16DST_DST1LGHit::GlobalPos(E16ANA_GeometryV2& geometry) {
  TVector3 pos = {E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue};
  pos = geometry.LG(3 * (109 - module_id) + 1, channel_id)->GetDetectorCenter();
  return pos;
}

TVector3 E16DST_DST1LGCluster::LocalPos() {
}

TVector3 E16DST_DST1LGCluster::GlobalPos(E16ANA_GeometryV2& geometry) {
}

TVector3 E16DST_DST1TriggerHit::LocalPos(E16ANA_GeometryV2& geometry) {
  TVector3 pos = {E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue};
  int geometry_module_id = ModuleId2020To2013(module_id);
  if (detector == E16DST_DST1Constant::kGTR300) {
    TVector3 local_pos = {0., - E16DST_DST1Constant::kGtr300ModuleSize / 2 + (double{E16DST_DST1Constant::kGtr300ModuleSize} / E16DST_Constant::NTriggerChannelsGTR) * (channel_id + 0.5), 0.};
    return local_pos;
  } else if (detector == E16DST_DST1Constant::kHBD) {
    int x = - E16DST_DST1Constant::kHbdModuleSize / 2 + (double{E16DST_DST1Constant::kHbdModuleSize} / E16DST_DST1Constant::kNumHbdTriggerChannelOneAxis) * (channel_id % 10 + 0.5);
    int y = - E16DST_DST1Constant::kHbdModuleSize / 2 + (double{E16DST_DST1Constant::kHbdModuleSize} / E16DST_DST1Constant::kNumHbdTriggerChannelOneAxis) * (channel_id / 10 + 0.5);
    TVector3 local_pos = {x, y, 0.};
    return local_pos;
  } else if (detector == E16DST_DST1Constant::kLG) {
    return geometry.LGVD(geometry_module_id)->GetLPos(GlobalPos(geometry));
  }
  return pos;
}

TVector3 E16DST_DST1TriggerHit::GlobalPos(E16ANA_GeometryV2& geometry) {
  TVector3 pos = {E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue};
  int geometry_module_id = ModuleId2020To2013(module_id);
  if (detector == E16DST_DST1Constant::kGTR300) {
    return geometry.GTR(geometry_module_id, 2)->GetGPos(LocalPos(geometry));
  } else if (detector == E16DST_DST1Constant::kHBD) {
    return geometry.HBD(geometry_module_id)->GetGPos(LocalPos(geometry));
  } else if (detector == E16DST_DST1Constant::kLG) {
    pos = geometry.LG(geometry_module_id, channel_id)->GetDetectorCenter();
  }
  return pos;
}

int E16DST_DST1Trigger::GetEventSize() const {
}

bool E16DST_DST1Trigger::SearchTriggerHit(E16DST_DST0Detector<E16DST_DST1TriggerHit>& hits, int module_id, int channel_id) {
  auto num_hits = hits.NumberOfHits();
  for (int n_hit = 0; n_hit < num_hits; ++n_hit) {
    auto& hit = hits.Hit(n_hit);
    if (hit.ModuleId() == module_id && hit.ChannelId() == channel_id) {
      return true;
    }
  }
  return false;
}

bool E16DST_DST1Trigger::IsTriggerHit(E16DST_DST1GTRHit& hit) {
  auto layer_id = hit.LayerId();
  auto type     = hit.Type();
  if (layer_id != 2 || type != E16DST_DST1Constant::kIsY) {
    return false;
  }
  int module_id = hit.ModuleId();
  int channel_id = E16DST_Constant::NTriggerChannelsGTR - 1 - hit.ChannelId() / (E16DST_DST1Constant::kNumGtr300YSignalChannel / E16DST_Constant::NTriggerChannelsGTR);
  return SearchTriggerHit(gtr_hits, module_id, channel_id);
}

bool E16DST_DST1Trigger::IsTriggerHit(E16DST_DST1HBDHit& hit) {
}

bool E16DST_DST1Trigger::IsTriggerHit(E16DST_DST1LGHit& hit) {
  return SearchTriggerHit(lg_hits, hit.ModuleId(), hit.ChannelId());
}

void E16DST_DST1Trigger::Print() {
  auto max_track = track_sets.NumberOfHits();
  std::cout << "Number of tracks: " << max_track << std::endl << std::endl;
  for (int n_track = 0; n_track < max_track; ++n_track) {
    std::cout << "Track ID: " << n_track << std::endl;
    auto track_set = track_sets.Hit(n_track);
    auto n_gtr_hits = track_set.NumGTRHits();
    auto n_hbd_hits = track_set.NumHBDHits();
    auto n_lg_hits = track_set.NumLGHits();
    std::cout << "  Number of tracked GTR: " << n_gtr_hits << std::endl;
    for (int n_hit = 0; n_hit < n_gtr_hits; ++n_hit) {
      auto order = track_set.GTRHitOrder(n_hit);
      auto hit = gtr_hits.Hit(order);
      std::cout << "    Tracked GTR hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId() << std::endl;
    }
    std::cout << "  Number of tracked HBD: " << n_hbd_hits << std::endl;
    for (int n_hit = 0; n_hit < n_hbd_hits; ++n_hit) {
      auto order = track_set.HBDHitOrder(n_hit);
      auto hit = hbd_hits.Hit(order);
      std::cout << "    Tracked HBD hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId() << std::endl;
    }
    std::cout << "  Number of tracked LG: " << n_lg_hits << std::endl;
    if (track_set.NumLGHits() == 1) {
      auto order = track_set.LGHitOrder(0);
      auto hit = lg_hits.Hit(order);
      std::cout << "    Tracked LG hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId() << std::endl;
    } else {
      std::cerr << "    Invalid number of LG Hits: " << track_set.NumLGHits() << std::endl;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void E16DST_DST1Trigger::Print(E16ANA_GeometryV2& geometry) {
  auto max_track = track_sets.NumberOfHits();
  std::cout << "Number of tracks: " << max_track << std::endl << std::endl;
  for (int n_track = 0; n_track < max_track; ++n_track) {
    std::cout << "Track ID: " << n_track << std::endl;
    auto track_set = track_sets.Hit(n_track);
    auto n_gtr_hits = track_set.NumGTRHits();
    auto n_hbd_hits = track_set.NumHBDHits();
    auto n_lg_hits = track_set.NumLGHits();
    std::cout << "  Number of tracked GTR: " << n_gtr_hits << std::endl;
    for (int n_hit = 0; n_hit < n_gtr_hits; ++n_hit) {
      auto order = track_set.GTRHitOrder(n_hit);
      auto hit = gtr_hits.Hit(order);
      std::cout << "    Tracked GTR hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId()
      << ", local position = (" << hit.LocalPos(geometry).X() << ", " << hit.LocalPos(geometry).Y() << ", " << hit.LocalPos(geometry).Z() << ")"
      << ", global position = (" << hit.GlobalPos(geometry).X() << ", " << hit.GlobalPos(geometry).Y() << ", " << hit.GlobalPos(geometry).Z() << ")" << std::endl;
    }
    std::cout << "  Number of tracked HBD: " << n_hbd_hits << std::endl;
    for (int n_hit = 0; n_hit < n_hbd_hits; ++n_hit) {
      auto order = track_set.HBDHitOrder(n_hit);
      auto hit = hbd_hits.Hit(order);
      std::cout << "    Tracked HBD hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId()
      << ", local position = (" << hit.LocalPos(geometry).X() << ", " << hit.LocalPos(geometry).Y() << ", " << hit.LocalPos(geometry).Z() << ")"
      << ", global position = (" << hit.GlobalPos(geometry).X() << ", " << hit.GlobalPos(geometry).Y() << ", " << hit.GlobalPos(geometry).Z() << ")" << std::endl;
    }
    std::cout << "  Number of tracked LG: " << n_lg_hits << std::endl;
    if (track_set.NumLGHits() == 1) {
      auto order = track_set.LGHitOrder(0);
      auto hit = lg_hits.Hit(order);
      std::cout << "    Tracked LG hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId()
      << ", local position = (" << hit.LocalPos(geometry).X() << ", " << hit.LocalPos(geometry).Y() << ", " << hit.LocalPos(geometry).Z() << ")"
      << ", global position = (" << hit.GlobalPos(geometry).X() << ", " << hit.GlobalPos(geometry).Y() << ", " << hit.GlobalPos(geometry).Z() << ")" << std::endl;
    } else {
      std::cerr << "    Invalid number of LG Hits: " << track_set.NumLGHits() << std::endl;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int E16DST_DST1PhysicsEvent::Write(E16DST_File* fp) {
}

int E16DST_DST1PhysicsEvent::Read(E16DST_File* fp) {
}

bool E16DST_DST1PhysicsEvent::Append(E16DST_DST0Event* _another_event) {
}

void E16DST_DST1PhysicsEvent::Clear() {
  trigger.Clear();
}
