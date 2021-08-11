#include "E16DST_DST1.hh"

#include <TVector3.h>

#include "E16DST_DST0.hh"

//template <class T>
//int E16DST_DST1Detector<T>::Write(E16DST_File* fp) {
//}
//
//template <class T>
//int E16DST_DST1Detector<T>::Read(E16DST_File* fp) {
//}
//
//template <class T>
//void E16DST_DST1Detector<T>::Append(E16DST_DST1Detector<T>& rhs) {
//}
//
//template <class T>
//int GetEventSize() {
//  int size = sizeof(uint32_t);
//  for (const auto& hit: hits) {
//    size += sizeof(T) * hit.size();
//  }
//  return size;
//}

void E16DST_DST1Cluster::SetHitOrders(std::vector<int>& _hit_orders) {
  hit_orders.Reserve(_hit_orders.size());
  for (const auto& hit_order : _hit_orders) {
    hit_orders.PushBack(hit_order);
  }
}

double E16DST_DST1SSDHit::LocalX() {
}

TVector3 E16DST_DST1SSDHit::LocalPos() {
}

TVector3 E16DST_DST1SSDHit::GlobalPos() {
}

double E16DST_DST1SSDCluster::LocalX() {
}

TVector3 E16DST_DST1SSDCluster::LocalPos() {
}

TVector3 E16DST_DST1SSDCluster::GlobalPos() {
}

E16DST_DST1SSDModule& E16DST_DST1SSD::Module(int _module) {
  if (_module < 101) {
  } else if (_module < 105) {
    return modules[_module - 101];
  } 
  else if (_module < 106) {
  } else if (_module < 110) {
    return modules[_module - 101 - 1];
  }
  std::cerr << "Invalid module ID (101 - 109): " << _module << std::endl;
  std::exit(1);
}

int E16DST_DST1SSD::GetEventSize() const {
  int size = 0;
  for (const auto& module : modules) {
    size += module.GetEventSize();
  }
  return size;
}

double E16DST_DST1GTRHit::LocalX() {
}

TVector3 E16DST_DST1GTRHit::LocalPos() {
}

TVector3 E16DST_DST1GTRHit::GlobalPos() {
}

double E16DST_DST1GTRCluster::LocalX() {
}

TVector3 E16DST_DST1GTRCluster::LocalPos() {
}

TVector3 E16DST_DST1GTRCluster::GlobalPos() {
}

E16DST_DST0Detector<E16DST_DST1GTRHit>& E16DST_DST1GTRModule::Hits(int _layer, int _axis) {
  if (_layer == 0) {
    if (_axis == E16DST_DST1Constant::kIsX) {
      return hits_100_x;
    } else if (_axis == E16DST_DST1Constant::kIsY) {
      return hits_100_y;
    } else if (_axis == E16DST_DST1Constant::kIsYb) {
      return hits_100_yb;
    } else {
      std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
      std::exit(1);
    }
  } else if (_layer == 1) {
    if (_axis == E16DST_DST1Constant::kIsX) {
      return hits_200_x;
    } else if (_axis == E16DST_DST1Constant::kIsY) {
      return hits_200_y;
    } else {
      std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
      std::exit(1);
    }
  } else if (_layer == 2) {
    if (_axis == E16DST_DST1Constant::kIsX) {
      return hits_300_x;
    } else if (_axis == E16DST_DST1Constant::kIsY) {
      return hits_300_y;
    } else {
      std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
      std::exit(1);
    }
  } else {
    std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
    std::exit(1);
  }
}

E16DST_DST0Detector<E16DST_DST1GTRCluster>& E16DST_DST1GTRModule::Clusters(int _layer, int _axis) {
  if (_layer == 0) {
    if (_axis == E16DST_DST1Constant::kIsX) {
      return clusters_100_x;
    } else if (_axis == E16DST_DST1Constant::kIsY) {
      return clusters_100_y;
    } else if (_axis == E16DST_DST1Constant::kIsYb) {
      return clusters_100_yb;
    } else {
      std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
      std::exit(1);
    }
  } else if (_layer == 1) {
    if (_axis == E16DST_DST1Constant::kIsX) {
      return clusters_200_x;
    } else if (_axis == E16DST_DST1Constant::kIsY) {
      return clusters_200_y;
    } else {
      std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
      std::exit(1);
    }
  } else if (_layer == 2) {
    if (_axis == E16DST_DST1Constant::kIsX) {
      return clusters_300_x;
    } else if (_axis == E16DST_DST1Constant::kIsY) {
      return clusters_300_y;
    } else {
      std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
      std::exit(1);
    }
  } else {
    std::cerr << "Invalid GTR chamber ID: " << _layer << ", " << _axis << std::endl;
    std::exit(1);
  }
}

E16DST_DST1GTRModule& E16DST_DST1GTR::Module(int _module) {
  if (_module < 101) {
  } else if (_module < 105) {
    return modules[_module - 101];
  } 
  else if (_module < 106) {
  } else if (_module < 110) {
    return modules[_module - 101 - 1];
  }
  std::cerr << "Invalid module ID (101 - 109): " << _module << std::endl;
  std::exit(1);
}

int E16DST_DST1GTR::GetEventSize() const {
  int size = 0;
  for (const auto& module : modules) {
    size += module.GetEventSize();
  }
  return size;
}

TVector3 E16DST_DST1HBDHit::LocalPos() {
}

TVector3 E16DST_DST1HBDHit::GlobalPos() {
}

TVector3 E16DST_DST1HBDCluster::LocalPos() {
}

TVector3 E16DST_DST1HBDCluster::GlobalPos() {
}

E16DST_DST1HBDModule& E16DST_DST1HBD::Module(int _module) {
  if (_module < 101) {
  } else if (_module < 105) {
    return modules[_module - 101];
  } 
  else if (_module < 106) {
  } else if (_module < 110) {
    return modules[_module - 101 - 1];
  }
  std::cerr << "Invalid module ID (101 - 109): " << _module << std::endl;
  std::exit(1);
}

int E16DST_DST1HBD::GetEventSize() const {
  int size = 0;
  for (const auto& module : modules) {
    size += module.GetEventSize();
  }
  return size;
}

TVector3 E16DST_DST1LGHit::LocalPos() {
}

TVector3 E16DST_DST1LGHit::GlobalPos() {
}

TVector3 E16DST_DST1LGCluster::LocalPos() {
}

TVector3 E16DST_DST1LGCluster::GlobalPos() {
}

E16DST_DST1LGModule& E16DST_DST1LG::Module(int _module) {
  if (_module < 101) {
  } else if (_module < 105) {
    return modules[_module - 101];
  } 
  else if (_module < 106) {
  } else if (_module < 110) {
    return modules[_module - 101 - 1];
  }
  std::cerr << "Invalid module ID (101 - 109): " << _module << std::endl;
  std::exit(1);
}

int E16DST_DST1LG::GetEventSize() const {
  int size = 0;
  for (const auto& module : modules) {
    size += module.GetEventSize();
  }
  return size;
}

int E16DST_DST1Trigger::GetEventSize() const {
}

int E16DST_DST1PhysicsEvent::Write(E16DST_File* fp) {
}
