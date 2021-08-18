#include "E16DST_DST1.hh"

template <class T, class U>
void E16DST_DST1Detector<T, U>::UpdateHitPtrs() {
  if (detector == E16DST_DST1Constant::kInvalidValue) {
    return;
  }
  hit_ptrs.clear();
  for (const auto& hit : hits) {
    int module_id = hit.ModuleId();
    int layer_id  = 0;
    int type      = 0;
    if (detector == E16DST_DST1Constant::kGTR100 || detector == E16DST_DST1Constant::kGTR200 || detector == E16DST_DST1Constant::kGTR300) {
      layer_id = hit.LayerId();
      type     = hit.Type();
    }
    int id = IdSum(module_id, layer_id, type);
    if (hit_ptrs.count(id) == 0) {
      std::vector hit_vector = {*hit};
      hit_ptrs.emplace(id, hit_vector);
    } else {
      hit_ptrs[id].emplace_back(*hit);
    }
  }
}

template <class T, class U>
void E16DST_DST1Detector<T, U>::UpdateClusterPtrs() {
  if (detector == E16DST_DST1Constant::kInvalidValue) {
    return;
  }
  cluster_ptrs.clear();
  for (const auto& cluster : clusters) {
    int module_id = cluster.ModuleId();
    int layer_id  = 0;
    int type      = 0;
    if (detector == E16DST_DST1Constant::kGTR100 || detector == E16DST_DST1Constant::kGTR200 || detector == E16DST_DST1Constant::kGTR300) {
      layer_id = cluster.LayerId();
      type     = cluster.Type();
    }
    int id = IdSum(module_id, layer_id, type);
    if (cluster_ptrs.count(id) == 0) {
      std::vector cluster_vector = {*cluster};
      cluster_ptrs.emplace(id, cluster_vector);
    } else {
      cluster_ptrs[id].emplace_back(*cluster);
    }
  }
}

template <class T, class U>
int E16DST_DST1Detector<T, U>::Write(E16DST_File* fp) {
}

template <class T, class U>
int E16DST_DST1Detector<T, U>::Read(E16DST_File* fp) {
}

template <class T, class U>
void E16DST_DST1Detector<T, U>::Append(E16DST_DST1Detector<T, U>& rhs) {
}

template <class T, class U>
std::vector<T*> E16DST_DST1Detector<T, U>::ClusterMembers(int cluster_id) {
  if (cluster_id < 0 || cluster_id >= clusters.size()) {
    std::cerr << "Invalid cluster ID in E16DST_DST1Detector::ClusterMember: " << cluster_id << std::endl;
    std::exit(1);
  }
  auto num_hits = clusters[cluster_id].NumHits();
  std::vector<T*> hit_vector(num_hits);
  for (int n_hit = 0; n_hit < num_hits; ++n_hit) {
    hit_vector[n_hit] = &hits[clusters[cluster_id].HitOrder(n_hit)];
  }
  return hit_vector;
}

template <class T, class U>
T& E16DST_DST1Detector<T, U>::ClusterMember(int cluster_id, int hit_id) {
  if (cluster_id < 0 || cluster_id >= clusters.size()) {
    std::cerr << "Invalid cluster ID in E16DST_DST1Detector::ClusterMember: " << cluster_id << std::endl;
    std::exit(1);
  }
  auto num_hits = clusters[cluster_id].NumHits();
  if (hit_id < 0 || hit_id >= num_hits) {
    std::cerr << "Invalid hit ID in E16DST_DST1Detector::ClusterMember: " << hit_id << std::endl;
    std::exit(1);
  }
  auto hit_orders = clusters.HitOrders();
  return hits[clusters[cluster_id].HitOrder(hit_id)];
}

template <class T, class U>
int E16DST_DST1Detector<T, U>::GetEventSize() {
  int size = sizeof(uint32_t);
  for (const auto& hit: hits) {
    size += sizeof(T) * hit.size();
  }
  for (const auto& cluster: clusters) {
    size += sizeof(U) * cluster.size();
  }
  return size;
}

template <class T, class U>
void E16DST_DST1Detector<T, U>::Print() {
  std::cout << "Number of hits: " << hits.size() << std::endl;
  for (int n_hit = 0; n_hit < hits.size(); ++n_hit) {
    hits[n_hit].Print();
  }
  std::cout << "Number of clusters: " << clusters.size() << std::endl;
  for (int n_cluster = 0; n_cluster < clusters.size(); ++n_cluster) {
    clusters[n_cluster].Print();
  }
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

//E16DST_DST1SSDModule& E16DST_DST1SSD::Module(int _module) {
//  if (_module < 101) {
//  } else if (_module < 105) {
//    return modules[_module - 101];
//  } 
//  else if (_module < 106) {
//  } else if (_module < 110) {
//    return modules[_module - 101 - 1];
//  }
//  std::cerr << "Invalid module ID (101 - 109): " << _module << std::endl;
//  std::exit(1);
//}
//
//int E16DST_DST1SSD::GetEventSize() const {
//  int size = 0;
//  for (const auto& module : modules) {
//    size += module.GetEventSize();
//  }
//  return size;
//}

double E16DST_DST1GTRHit::LocalX() {
}

TVector3 E16DST_DST1GTRHit::LocalPos(E16ANA_GeometryV2& geometry) {
}

TVector3 E16DST_DST1GTRHit::GlobalPos(E16ANA_GeometryV2& geometry) {
}

double E16DST_DST1GTRCluster::LocalX() {
}

TVector3 E16DST_DST1GTRCluster::LocalPos() {
}

TVector3 E16DST_DST1GTRCluster::GlobalPos(E16ANA_GeometryV2& geometry) {
}

//E16DST_DST0Detector<E16DST_DST1GTRHit>& E16DST_DST1GTRModule::Hits(int _layer, int _axis) {
//  if (_layer == 0) {
//    if (_axis == E16DST_DST1Constant::kIsX) {
//      return hits_100_x;
//    } else if (_axis == E16DST_DST1Constant::kIsY) {
//      return hits_100_y;
//    } else if (_axis == E16DST_DST1Constant::kIsYb) {
//      return hits_100_yb;
//    } else {
//      std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
//      std::exit(1);
//    }
//  } else if (_layer == 1) {
//    if (_axis == E16DST_DST1Constant::kIsX) {
//      return hits_200_x;
//    } else if (_axis == E16DST_DST1Constant::kIsY) {
//      return hits_200_y;
//    } else {
//      std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
//      std::exit(1);
//    }
//  } else if (_layer == 2) {
//    if (_axis == E16DST_DST1Constant::kIsX) {
//      return hits_300_x;
//    } else if (_axis == E16DST_DST1Constant::kIsY) {
//      return hits_300_y;
//    } else {
//      std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
//      std::exit(1);
//    }
//  } else {
//    std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
//    std::exit(1);
//  }
//}
//
//E16DST_DST0Detector<E16DST_DST1GTRCluster>& E16DST_DST1GTRModule::Clusters(int _layer, int _axis) {
//  if (_layer == 0) {
//    if (_axis == E16DST_DST1Constant::kIsX) {
//      return clusters_100_x;
//    } else if (_axis == E16DST_DST1Constant::kIsY) {
//      return clusters_100_y;
//    } else if (_axis == E16DST_DST1Constant::kIsYb) {
//      return clusters_100_yb;
//    } else {
//      std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
//      std::exit(1);
//    }
//  } else if (_layer == 1) {
//    if (_axis == E16DST_DST1Constant::kIsX) {
//      return clusters_200_x;
//    } else if (_axis == E16DST_DST1Constant::kIsY) {
//      return clusters_200_y;
//    } else {
//      std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
//      std::exit(1);
//    }
//  } else if (_layer == 2) {
//    if (_axis == E16DST_DST1Constant::kIsX) {
//      return clusters_300_x;
//    } else if (_axis == E16DST_DST1Constant::kIsY) {
//      return clusters_300_y;
//    } else {
//      std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
//      std::exit(1);
//    }
//  } else {
//    std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
//    std::exit(1);
//  }
//}
//
//E16DST_DST1GTRModule& E16DST_DST1GTR::Module(int _module) {
//  if (_module < 101) {
//  } else if (_module < 105) {
//    return modules[_module - 101];
//  } 
//  else if (_module < 106) {
//  } else if (_module < 110) {
//    return modules[_module - 101 - 1];
//  }
//  std::cerr << "Invalid module ID (101 - 109): " << _module << std::endl;
//  std::exit(1);
//}
//
//int E16DST_DST1GTR::GetEventSize() const {
//  int size = 0;
//  for (const auto& module : modules) {
//    size += module.GetEventSize();
//  }
//  return size;
//}

TVector3 E16DST_DST1HBDHit::LocalPos(E16ANA_GeometryV2& geometry) {
}

TVector3 E16DST_DST1HBDHit::GlobalPos(E16ANA_GeometryV2& geometry) {
}

TVector3 E16DST_DST1HBDCluster::LocalPos() {
}

TVector3 E16DST_DST1HBDCluster::GlobalPos(E16ANA_GeometryV2& geometry) {
}

//E16DST_DST1HBDModule& E16DST_DST1HBD::Module(int _module) {
//  if (_module < 101) {
//  } else if (_module < 105) {
//    return modules[_module - 101];
//  } 
//  else if (_module < 106) {
//  } else if (_module < 110) {
//    return modules[_module - 101 - 1];
//  }
//  std::cerr << "Invalid module ID (101 - 109): " << _module << std::endl;
//  std::exit(1);
//}
//
//int E16DST_DST1HBD::GetEventSize() const {
//  int size = 0;
//  for (const auto& module : modules) {
//    size += module.GetEventSize();
//  }
//  return size;
//}

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

//E16DST_DST1LGModule& E16DST_DST1LG::Module(int _module) {
//  if (_module < 101) {
//  } else if (_module < 105) {
//    return modules[_module - 101];
//  } 
//  else if (_module < 106) {
//  } else if (_module < 110) {
//    return modules[_module - 101 - 1];
//  }
//  std::cerr << "Invalid module ID (101 - 109): " << _module << std::endl;
//  std::exit(1);
//}
//
//int E16DST_DST1LG::GetEventSize() const {
//  int size = 0;
//  for (const auto& module : modules) {
//    size += module.GetEventSize();
//  }
//  return size;
//}

TVector3 E16DST_DST1TriggerHit::LocalPos(E16ANA_GeometryV2& geometry) {
  TVector3 pos = {0., 0., 0.};
  return pos;
}

TVector3 E16DST_DST1TriggerHit::GlobalPos(E16ANA_GeometryV2& geometry) {
  TVector3 pos = {E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue};
  int geometry_module_id = ModuleId2020To2013(module_id);
  if (detector == E16DST_DST1Constant::kGTR300) {
    TVector3 local_pos = {0., -150. + 12.5 * (channel_id + 0.5), 0.};
    pos = geometry.GTR3(geometry_module_id)->GetGPos(local_pos);
  } else if (detector == E16DST_DST1Constant::kHBD) {
    pos = {0., 0., 0.};
  } else if (detector == E16DST_DST1Constant::kLG) {
    pos = geometry.LG(geometry_module_id, channel_id)->GetDetectorCenter();
  }
  return pos;
}

int E16DST_DST1Trigger::GetEventSize() const {
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
      << ", global position = (" << hit.GlobalPos(geometry).X() << ", " << hit.GlobalPos(geometry).Y() << ", " << hit.GlobalPos(geometry).Z() << ")" << std::endl;
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
      std::cout << "    Tracked LG hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId()
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
