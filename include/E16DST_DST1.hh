#ifndef E16DST_DST1_HH
#define E16DST_DST1_HH

#include <iostream>
#include <unordered_map>
#include <vector>

#include "TVector3.h"
#include "E16ANA_TriggerCalib.hh"
#include "E16ANA_GeometryV2.hh"
#include "E16DST_Constant.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1Constant.hh"

class E16DST_DST1Hit {
 public:
  E16DST_DST1Hit() { SetInvalid(); }
  ~E16DST_DST1Hit() {}
  virtual void     SetInvalid() { SetBaseInvalid(); }
  void             SetBaseInvalid() {
    module_id  = E16DST_DST1Constant::kInvalidValue;
    channel_id = E16DST_DST1Constant::kInvalidValue;
    timing     = E16DST_DST1Constant::kInvalidValue;
  }
  void             SetIds(int16_t _module_id, int16_t _channel_id) {
    module_id  = _module_id;
    channel_id = _channel_id;
  }
  void             SetTiming(float _timing) { timing = _timing; }
  virtual void     SetPeakHeight(float _peak_height) = 0;
  int16_t          ModuleId() { return module_id; }
  int16_t          ChannelId() { return channel_id; }
  float            Timing() { return timing; }
  virtual float    PeakHeight() = 0;
  virtual TVector3 LocalPos(E16ANA_GeometryV2& geometry) = 0;
  virtual TVector3 GlobalPos(E16ANA_GeometryV2& geometry) = 0;
  virtual void     Print() {
    std::cout << "Module ID: " << module_id << ", Channel ID: " << channel_id << ", Timing: " << timing << std::endl;
  }
 protected:
  virtual int ModuleId2020To2013(int module_id) = 0;
  int16_t     module_id;
  int16_t     channel_id;
  float       timing; // 50% of peak
};

class E16DST_DST1Cluster {
 public:
  E16DST_DST1Cluster() { SetInvalid(); }
  ~E16DST_DST1Cluster() {}
  virtual void              SetInvalid() { SetBaseInvalid(); }
  void                      SetBaseInvalid() {
    module_id       = E16DST_DST1Constant::kInvalidValue;
    max_peak_ch     = E16DST_DST1Constant::kInvalidValue;
    max_peak_height = E16DST_DST1Constant::kInvalidValue;
    timing          = E16DST_DST1Constant::kInvalidValue;
    peak_sum        = E16DST_DST1Constant::kInvalidValue;
  }
  void                          SetModuleId(int16_t _module_id) { module_id = _module_id; }
  void                          SetMaxPeakCh(int _max_peak_ch) { max_peak_ch = _max_peak_ch; }
  void                          SetMaxPeakHeight(int _max_peak_height) { max_peak_height = _max_peak_height; }
  void                          SetTiming(float _timing) { timing = _timing; }
  void                          SetPeakSum(float _peak_sum) { peak_sum = _peak_sum; }
  void                          SetHitOrders(std::vector<int16_t>& _hit_orders);
  int16_t                       ModuleId() { return module_id; }
  int                           MaxPeakCh() { return max_peak_ch; }
  float                         MaxPeakHeight() { return max_peak_height; }
  float                         Timing() { return timing; }
  float                         PeakSum() { return peak_sum; }
  int                           NumHits() { return hit_orders.NumberOfHits(); }
  E16DST_DST0Detector<int16_t>& HitOrders() { return hit_orders; }
  int16_t                       HitOrder(int n) { return hit_orders.Hit(n); }
  virtual TVector3              LocalPos() = 0;
  virtual TVector3              GlobalPos(E16ANA_GeometryV2& geometry) = 0;
  virtual void                  Print() {
    std::cout << "Module ID: " << module_id << ", Max peak channel: " << max_peak_ch << ", Max peak height: " << max_peak_height << ", Timing: " << timing << ", Peak sum: " << peak_sum << ", Number of hits: " << NumHits() << std::endl;
  }
 protected:
  virtual int                  ModuleId2020To2013(int module_id) = 0;
  int16_t                      module_id;
  int                          max_peak_ch;
  float                        max_peak_height;
  float                        timing;
  float                        peak_sum;
  E16DST_DST0Detector<int16_t> hit_orders; // Order in E16DST_DST0Detector<E16DST_DST1xxxHit>
};

class E16DST_DST1SSDHit : public E16DST_DST1Hit {
 public:
  E16DST_DST1SSDHit() { SetInvalid(); }
  ~E16DST_DST1SSDHit() {}
  void     SetInvalid() override {
    SetBaseInvalid();
    peak_height = E16DST_DST1Constant::kInvalidValue;
    hit_time    = E16DST_DST1Constant::kInvalidValue;
    peak_time   = E16DST_DST1Constant::kInvalidValue;
  }
  void     SetPeakHeight(float _peak_height) override { peak_height = _peak_height; }
  void     SetHitTime(float _hit_time) { hit_time = _hit_time; }
  void     SetPeakTime(float _peak_time) { peak_time = _peak_time; }
  float    PeakHeight() override { return peak_height; }
  float    HitTime() { return hit_time; }
  float    PeakTime() { return peak_time; }
  double   LocalX();
  TVector3 LocalPos(E16ANA_GeometryV2& geometry) override;
  TVector3 GlobalPos(E16ANA_GeometryV2& geometry) override;
 private:
  int   ModuleId2020To2013(int module_id) override { return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100]; }
  float peak_height;
  float hit_time;
  float peak_time;
};

class E16DST_DST1SSDCluster : public E16DST_DST1Cluster {
 public:
  E16DST_DST1SSDCluster() { SetInvalid(); }
  ~E16DST_DST1SSDCluster() {}
  void SetInvalid() override {
    SetBaseInvalid();
    center_of_gravity  = E16DST_DST1Constant::kInvalidValue;
    tdc_pos            = E16DST_DST1Constant::kInvalidValue;
    tan_incident_angle = E16DST_DST1Constant::kInvalidValue;
  }
  void     SetCogPos(double _center_of_gravity)    { center_of_gravity = _center_of_gravity; }
  void     SetTdcPos(double _tdc_pos)              { tdc_pos = _tdc_pos; }
  void     SetTanTheta(float _tan_incident_angle) { tan_incident_angle = _tan_incident_angle; }
  double   CogPos() { return center_of_gravity; }
  double   TdcPos() { return tdc_pos; }
  float    TanTheta() { return tan_incident_angle; }
  double   LocalX();
  TVector3 LocalPos() override;
  TVector3 GlobalPos(E16ANA_GeometryV2& geometry) override;
  void     Print() override {
    std::cout << "E16DST_DST1SSDCluster : "
              << "Num hit strips = " << NumHits() << ", Cluster charge = " << peak_sum
              << ", Cog hit pos = " << center_of_gravity << " [mm], TDC hit pos = " << tdc_pos 
              << " [mm]" << std::endl;
  }
 private:
  int    ModuleId2020To2013(int module_id) override { return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100]; }
  double center_of_gravity; // mm
  double tdc_pos;           // mm
  float  tan_incident_angle;    // radian
};

class E16DST_DST1GTRHit : public E16DST_DST1Hit {
 public:
  E16DST_DST1GTRHit() { SetInvalid(); }
  ~E16DST_DST1GTRHit() {}
  void SetInvalid() override {
    SetBaseInvalid();
    layer_id    = E16DST_DST1Constant::kInvalidValue;
    type        = E16DST_DST1Constant::kInvalidValue;
    peak_height = E16DST_DST1Constant::kInvalidValue;
    tot         = E16DST_DST1Constant::kInvalidValue;
  }
  void SetLayerId(int16_t _layer_id) { layer_id = _layer_id; }
  void SetType(int16_t _type) { type = _type; }
  void SetPeakHeight(float _peak_height) override { peak_height = _peak_height; }
  void SetTot(float _tot) { tot = _tot; }
  int16_t LayerId() { return layer_id; }
  bool IsX() { return type == E16DST_DST1Constant::kIsX; }
  bool IsY() { return type == E16DST_DST1Constant::kIsY; }
  bool IsYb() { return type == E16DST_DST1Constant::kIsYb; }
  int16_t Type() { return type; }
  float PeakHeight() override { return peak_height; }
  float Tot() { return tot; }
  double LocalX();
  TVector3 LocalPos(E16ANA_GeometryV2& geometry) override;
  TVector3 GlobalPos(E16ANA_GeometryV2& geometry) override;
 private:
  int     ModuleId2020To2013(int module_id) override { return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100]; }
  int16_t layer_id;
  int16_t type;
  float   peak_height;
  float   tot;
 };

class E16DST_DST1GTRCluster : public E16DST_DST1Cluster {
 public:
  E16DST_DST1GTRCluster() { SetInvalid(); }
  ~E16DST_DST1GTRCluster() {}
  void SetInvalid() override {
    SetBaseInvalid();
    layer_id           = E16DST_DST1Constant::kInvalidValue;
    type               = E16DST_DST1Constant::kInvalidValue;
    center_of_gravity  = E16DST_DST1Constant::kInvalidValue;
    tdc_pos            = E16DST_DST1Constant::kInvalidValue;
    tan_incident_angle = E16DST_DST1Constant::kInvalidValue;
  }
  void SetLayerId(int16_t _layer_id) { layer_id = _layer_id; }
  void SetType(int16_t _type) { type = _type; }
  void SetCogPos(double _center_of_gravity) { center_of_gravity = _center_of_gravity; }
  void SetTdcPos(double _tdc_pos) { tdc_pos = _tdc_pos; }
  void SetTanTheta(float _tan_incident_angle) { tan_incident_angle = _tan_incident_angle; }
  int16_t LayerId() { return layer_id; }
  bool IsX() { return type == E16DST_DST1Constant::kIsX; }
  bool IsY() { return type == E16DST_DST1Constant::kIsY; }
  bool IsYb() { return type == E16DST_DST1Constant::kIsYb; }
  int16_t Type() { return type; }
  double CogPos() { return center_of_gravity; }
  double TdcPos() { return tdc_pos; }
  float TanTheta() { return tan_incident_angle; }
  double LocalX();
  TVector3 LocalPos() override;
  TVector3 GlobalPos(E16ANA_GeometryV2& geometry) override;
  void Print() override {
    std::cout << "E16DST_DST1GTRCluster : "
              << "Num hit strips = " << NumHits() << ", Cluster charge = " << peak_sum
              << ", Cog hit pos = " << center_of_gravity << " [mm], TDC hit pos = " << tdc_pos 
              << " [mm]" << std::endl;
  }
 private:
  int   ModuleId2020To2013(int module_id) override { return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100]; }
  int16_t layer_id;
  int16_t type;
  double center_of_gravity; // mm
  double tdc_pos;           // mm
  float tan_incident_angle;    // radian
};

class E16DST_DST1HBDHit : public E16DST_DST1Hit {
 public:
  E16DST_DST1HBDHit(){}
  ~E16DST_DST1HBDHit(){}
  void SetInvalid() override {
    SetBaseInvalid();
    peak_height = E16DST_DST1Constant::kInvalidValue;
  }
  void SetPeakHeight(float _peak_height) override { peak_height = peak_height; }
  float PeakHeight() override { return peak_height; }
  TVector3 LocalPos(E16ANA_GeometryV2& geometry) override;
  TVector3 GlobalPos(E16ANA_GeometryV2& geometry) override;
  void Print() override {
  }
 private:
  int   ModuleId2020To2013(int module_id) override { return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100 + 1]; }
  float peak_height;
};

class E16DST_DST1HBDCluster : public E16DST_DST1Cluster {
 public:
  E16DST_DST1HBDCluster() { SetInvalid(); }
  ~E16DST_DST1HBDCluster() {}
  void SetInvalid() override {
    SetBaseInvalid();
    first_timing    = E16DST_DST1Constant::kInvalidValue;
    time_difference = E16DST_DST1Constant::kInvalidValue;
  }
  float FirstTiming() { return first_timing; }
  float TimeDifference() { return time_difference; }
  TVector3 LocalPos() override;
  TVector3 GlobalPos(E16ANA_GeometryV2& geometry) override;
  void Print() override {}
 private:
  int   ModuleId2020To2013(int module_id) override { return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100 + 1]; }
  float first_timing;
  float time_difference;
};

class E16DST_DST1LGHit : public E16DST_DST1Hit {
 public:
  E16DST_DST1LGHit() { SetInvalid(); }
  ~E16DST_DST1LGHit() {}
  void SetInvalid() override {
    SetBaseInvalid();
    peak_height = E16DST_DST1Constant::kInvalidValue;
    peak_time= E16DST_DST1Constant::kInvalidValue;
    baseline = E16DST_DST1Constant::kInvalidValue;
    baseline_rms = E16DST_DST1Constant::kInvalidValue;
    integral = E16DST_DST1Constant::kInvalidValue;
  }
  void SetPeakHeight(float _peak_height) override { peak_height = _peak_height; }
  void SetPeakTime(int _peak_time) { peak_time = _peak_time; }
  void SetBaseline(float _baseline) { baseline = _baseline; }
  void SetBaselineRms(float _baseline_rms) { baseline_rms = _baseline_rms; }
  void SetIntegral(float _integral) { integral = _integral; }
  float PeakHeight() override { return peak_height; }
  int PeakTime() { return peak_time; }
  float Baseline() { return baseline; }
  float BaselineRms() { return baseline_rms; }
  float Integral() { return integral; }
  TVector3 LocalPos(E16ANA_GeometryV2& geometry) override;
  TVector3 GlobalPos(E16ANA_GeometryV2& geometry) override;
 private:
  int   ModuleId2020To2013(int module_id) override { return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100 + 1]; }
  float peak_height;
  int   peak_time;
  float baseline;
  float baseline_rms;
  float integral; // baseline subtracted
};

class E16DST_DST1LGCluster : public E16DST_DST1Cluster {
 public:
  E16DST_DST1LGCluster() {}
  ~E16DST_DST1LGCluster() {}
  void SetInvalid() override {
    SetBaseInvalid();
  }
  TVector3 LocalPos() override;
  TVector3 GlobalPos(E16ANA_GeometryV2& geometry) override;
  void Print() override {}
 private:
  int ModuleId2020To2013(int module_id) override { return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100 + 1]; }
};

class E16DST_DST1TriggerHit : public E16DST_DST1Hit {
 public:
  E16DST_DST1TriggerHit() { SetInvalid(); }
  ~E16DST_DST1TriggerHit() {}
  void SetInvalid() override {
    SetBaseInvalid();
    detector = E16DST_DST1Constant::kInvalidValue;
  }
  void SetPeakHeight(float _peak_height) override {}
  void SetDetector(int16_t _detector) {
    if (_detector < E16DST_DST1Constant::kGTR300 || _detector > E16DST_DST1Constant::kLG) {
      std::cerr << "Invalid detector ID: " << _detector << std::endl;
      std::exit(1);
    }
    detector = _detector;
  }
  float PeakHeight() override { return E16DST_DST1Constant::kInvalidValue; }
  int16_t Detector() { return detector; }
  TVector3 LocalPos(E16ANA_GeometryV2& geometry) override;
  TVector3 GlobalPos(E16ANA_GeometryV2& geometry) override;
 private:
  int ModuleId2020To2013(int module_id) override {
    if (detector == E16DST_DST1Constant::kSSD || detector == E16DST_DST1Constant::kGTR300) {
      return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100];
    } else if (detector == E16DST_DST1Constant::kHBD || detector == E16DST_DST1Constant::kLG) {
      return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100 + 1];
    } else {
      return E16DST_DST1Constant::kInvalidValue;
    }
  }
  int16_t detector;
};

class E16DST_DST1TriggerCluster : public E16DST_DST1Cluster {
 public:
  E16DST_DST1TriggerCluster() {}
  ~E16DST_DST1TriggerCluster() {}
 private:
  int ModuleId2020To2013(int module_id) override { return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100 + 1]; }
};

template <class T, class U>
class E16DST_DST1Detector {
 public:
  using value_type0 = T;
  using value_type1 = U;
  E16DST_DST1Detector() {}
  ~E16DST_DST1Detector() {}
  void Clear() {
    valid_flag = 0;
    detector = E16DST_DST1Constant::kInvalidValue;
    hits.clear();
    clusters.clear();
    hit_ptrs.clear();
    cluster_ptrs.clear();
  }
  void             SetValidFlag(int16_t _valid_flag) { valid_flag = _valid_flag; }
  void             SetDetector(int16_t _detector) {
    if (_detector >= E16DST_DST1Constant::kNumDetectors) {
      std::cerr << "Invalid detector ID: " << _detector << std::endl;
      std::exit(1);
    } else {
      detector = _detector;
    }
  }
  int16_t          ValidFlag()                        { return valid_flag; }
  int16_t          Detector()                         { return detector; }
  void             HitResize(int n)                   { hits.resize(n); }
  void             HitReserve(int n)                  { hits.reserve(n); }
  void             HitPushBack()                      { hits.push_back(T()); }
  void             HitPushBack(const T& hit)          { hits.push_back(hit); }
  T&               HitBack()                          { return hits.back(); }
  T&               Hit(int i)                         { return hits[i]; }
  std::vector<T>&  Hits()                             { return hits; }
  int              NumHits()                          { return hits.size(); }
  void             ClusterResize(int n)               { clusters.resize(n); }
  void             ClusterReserve(int n)              { clusters.reserve(n); }
  void             ClusterPushBack()                  { clusters.push_back(T()); }
  void             ClusterPushBack(const U& cluster)  { clusters.push_back(cluster); }
  U&               ClusterBack()                      { return clusters.back(); }
  U&               Cluster(int i)                     { return clusters[i]; }
  std::vector<U>&  Clusters()                         { return clusters; }
  int              NumClusters()                      { return clusters.size(); }
  void             UpdateHitPtrs();
  void             UpdateClusterPtrs();
  void             UpdatePtrs() {
    UpdateHitPtrs();
    UpdateClusterPtrs();
  }
  std::vector<T*>& HitPtrs(int module_id, int layer_id, int type) {
    int id_sum = IdSum(module_id, layer_id, type);
    return hit_ptrs[id_sum];
  }
  std::vector<U*>& ClusterPtrs(int module_id, int layer_id, int type) {
    int id_sum = IdSum(module_id, layer_id, type);
    return cluster_ptrs[id_sum];
  }
  std::vector<T*>  ClusterMembers(int cluster_id);
  T&               ClusterMember(int cluster_id, int hit_id);
  int              Write(E16DST_File* fp);
  int              Read(E16DST_File* fp);
  void             Append(E16DST_DST1Detector<T, U>& rhs);
  int              GetEventSize();
  void             Print();
 private:
  int                                      IdSum(int module_id, int layer_id, int type) { return 10000 * module_id + 100 * layer_id + type; }
  int16_t                                  valid_flag;
  int16_t                                  detector;
  std::vector<T>                           hits;
  std::vector<U>                           clusters;
  std::unordered_map<int, std::vector<T*>> hit_ptrs;
  std::unordered_map<int, std::vector<U*>> cluster_ptrs;
};

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
int E16DST_DST1Detector<T, U>::Write(E16DST_File* fp) {
}

template <class T, class U>
int E16DST_DST1Detector<T, U>::Read(E16DST_File* fp) {
}

template <class T, class U>
void E16DST_DST1Detector<T, U>::Append(E16DST_DST1Detector<T, U>& rhs) {
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
  for (auto& hit : hits) {
    hit.Print();
  }
  std::cout << "Number of clusters: " << clusters.size() << std::endl;
  for (auto& cluster : clusters) {
    cluster.Print();
  }
}

class E16DST_DST1TriggerTrackSet {
 public:
  E16DST_DST1TriggerTrackSet() {}
  ~E16DST_DST1TriggerTrackSet() {}
  void Clear() {
    gtr_hit_orders.clear();
    gtr_hit_is_used.clear();
    gtr_unrecorded_hits.clear();
    hbd_hit_orders.clear();
    hbd_hit_is_used.clear();
    hbd_unrecorded_hits.clear();
    lg_hit_orders.clear();
    lg_hit_is_used.clear();
    lg_unrecorded_hits.clear();
  }
  int                          NumGTRHits()            { return gtr_hit_orders.size(); }
  std::vector<int16_t>&        GTRHitOrders()          { return gtr_hit_orders; }
  int16_t                      GTRHitOrder(int n)      { return gtr_hit_orders[n]; }
  std::vector<bool>&           GTRHitIsUsed()          { return gtr_hit_is_used; }
  bool                         GTRHitIsUsed(int n)     { return gtr_hit_is_used[n]; }
  std::vector<E16DST_DST0Hit>& GTRUnrecordedHits()     { return gtr_unrecorded_hits; }
  E16DST_DST0Hit&              GTRUnrecordedHit(int n) { return gtr_unrecorded_hits[n]; }
  int                          NumHBDHits()            { return hbd_hit_orders.size(); }
  std::vector<int16_t>&        HBDHitOrders()          { return hbd_hit_orders; }
  int16_t                      HBDHitOrder(int n)      { return hbd_hit_orders[n]; }
  std::vector<bool>&           HBDHitIsUsed()          { return hbd_hit_is_used; }
  bool                         HBDHitIsUsed(int n)     { return hbd_hit_is_used[n]; }
  std::vector<E16DST_DST0Hit>& HBDUnrecordedHits()     { return hbd_unrecorded_hits; }
  E16DST_DST0Hit&              HBDUnrecordedHit(int n) { return hbd_unrecorded_hits[n]; }
  int                          NumLGHits()             { return lg_hit_orders.size(); }
  std::vector<int16_t>&        LGHitOrders()           { return lg_hit_orders; }
  int16_t                      LGHitOrder(int n)       { return lg_hit_orders[n]; }
  std::vector<bool>&           LGHitIsUsed()           { return lg_hit_is_used; }
  bool                         LGHitIsUsed(int n)      { return lg_hit_is_used[n]; }
  std::vector<E16DST_DST0Hit>& LGUnrecordedHits()      { return lg_unrecorded_hits; }
  E16DST_DST0Hit&              LGUnrecordedHit(int n)  { return lg_unrecorded_hits[n]; }
 private:
  std::vector<int16_t>        gtr_hit_orders;
  std::vector<bool>           gtr_hit_is_used;
  std::vector<E16DST_DST0Hit> gtr_unrecorded_hits;
  std::vector<int16_t>        hbd_hit_orders;
  std::vector<bool>           hbd_hit_is_used;
  std::vector<E16DST_DST0Hit> hbd_unrecorded_hits;
  std::vector<int16_t>        lg_hit_orders; // always 1 element in run0
  std::vector<bool>           lg_hit_is_used; // always 1 element in run0
  std::vector<E16DST_DST0Hit> lg_unrecorded_hits; // always no element in run0
};

class E16DST_DST1Trigger {
 public:
  E16DST_DST1Trigger() {}
  ~E16DST_DST1Trigger() {}
  void Clear() {
    valid_flag = E16DST_DST1Constant::kInvalidValue;
    gtr_hits.Clear();
    gtr_clusters.Clear();
    hbd_hits.Clear();
    hbd_clusters.Clear();
    lg_hits.Clear();
    lg_clusters.Clear();
    tracks.Clear();
    hit_sets.Clear();
    track_sets.Clear();
//    gtr_hits.clear();
//    gtr_clusters.clear();
//    hbd_hits.clear();
//    hbd_clusters.clear();
//    lg_hits.clear();
//    lg_clusters.clear();
//    tracks.clear();
//    hit_sets.clear();
//    track_sets.clear();
  }
  void SetValidFlag(int16_t _valid_flag) { valid_flag = _valid_flag; }
  void SetNumTriggers(int16_t _n_triggers) { n_triggers = _n_triggers; }
  int16_t ValidFlag() { return valid_flag; }
  int GetEventSize() const;
//  int GetEventSize() const { return GetEventSizeImpl(gtr_hits, gtr_clusters, hbd_hits, hbd_clusters, lg_hits, lg_clusters, tracks, hit_sets, track_sets) + sizeof(int); }
  E16DST_DST0Detector<E16DST_DST1TriggerHit>&      GTRHits()     { return gtr_hits; }
  E16DST_DST0Detector<E16DST_DST1TriggerCluster>&  GTRClusters() { return gtr_clusters; }
  E16DST_DST0Detector<E16DST_DST1TriggerHit>&      HBDHits()     { return hbd_hits; }
  E16DST_DST0Detector<E16DST_DST1TriggerCluster>&  HBDClusters() { return hbd_clusters; }
  E16DST_DST0Detector<E16DST_DST1TriggerHit>&      LGHits()      { return lg_hits; }
  E16DST_DST0Detector<E16DST_DST1TriggerCluster>&  LGClusters()  { return lg_clusters; }
  E16DST_DST0Detector<E16DST_DST1TriggerHit>&      Tracks()      { return tracks; }
  E16DST_DST0Detector<E16DST_DST1TriggerTrackSet>& HitSets()     { return hit_sets; }
  E16DST_DST0Detector<E16DST_DST1TriggerTrackSet>& TrackSets()   { return track_sets; }
//  std::vector<E16DST_DST1TriggerHit>&      GTRHits()     { return gtr_hits; }
//  std::vector<E16DST_DST1TriggerCluster>&  GTRClusters() { return gtr_clusters; }
//  std::vector<E16DST_DST1TriggerHit>&      HBDHits()     { return hbd_hits; }
//  std::vector<E16DST_DST1TriggerCluster>&  HBDClusters() { return hbd_clusters; }
//  std::vector<E16DST_DST1TriggerHit>&      LGHits()      { return lg_hits; }
//  std::vector<E16DST_DST1TriggerCluster>&  LGClusters()  { return lg_clusters; }
//  std::vector<E16DST_DST1TriggerHit>&      Tracks()      { return tracks; }
//  std::vector<E16DST_DST1TriggerTrackSet>& HitSets()     { return hit_sets; }
//  std::vector<E16DST_DST1TriggerTrackSet>& TrackSets()   { return track_sets; }
  int16_t NumTriggers() { return n_triggers; }
  bool IsTriggerHit(E16DST_DST1GTRHit& hit);
  bool IsTriggerHit(E16DST_DST1HBDHit& hit);
  bool IsTriggerHit(E16DST_DST1LGHit&  hit);
//  std:::vector<E16DST_DST1TriggerHit*> HitsIncludedTrackSet(bool is_track, int n);
  void Print();
  void Print(E16ANA_GeometryV2& geometry);
 private:
  bool SearchTriggerHit(E16DST_DST0Detector<E16DST_DST1TriggerHit>& hits, int module_id, int channel_id);
  int16_t valid_flag;
  E16DST_DST0Detector<E16DST_DST1TriggerHit>      gtr_hits;
  E16DST_DST0Detector<E16DST_DST1TriggerCluster>  gtr_clusters;
  E16DST_DST0Detector<E16DST_DST1TriggerHit>      hbd_hits;
  E16DST_DST0Detector<E16DST_DST1TriggerCluster>  hbd_clusters;
  E16DST_DST0Detector<E16DST_DST1TriggerHit>      lg_hits;
  E16DST_DST0Detector<E16DST_DST1TriggerCluster>  lg_clusters;
  E16DST_DST0Detector<E16DST_DST1TriggerHit>      tracks;
  E16DST_DST0Detector<E16DST_DST1TriggerTrackSet> hit_sets;
  E16DST_DST0Detector<E16DST_DST1TriggerTrackSet> track_sets;
//  std::vector<E16DST_DST1TriggerHit>      gtr_hits;
//  std::vector<E16DST_DST1TriggerCluster>  gtr_clusters;
//  std::vector<E16DST_DST1TriggerHit>      hbd_hits;
//  std::vector<E16DST_DST1TriggerCluster>  hbd_clusters;
//  std::vector<E16DST_DST1TriggerHit>      lg_hits;
//  std::vector<E16DST_DST1TriggerCluster>  lg_clusters;
//  std::vector<E16DST_DST1TriggerHit>      tracks;
//  std::vector<E16DST_DST1TriggerTrackSet> hit_sets;
//  std::vector<E16DST_DST1TriggerTrackSet> track_sets;
  int16_t n_triggers;
};

//class E16DST_DST1Trigger {
// public:
//  E16DST_DST1Trigger() {}
//  ~E16DST_DST1Trigger() {}
//  void Clear() {
//    valid_flag = E16DST_DST1Constant::kInvalidValue;
//    gtr_hits.Clear();
//    hbd_hits.Clear();
//    lg_hits.Clear();
////    gtr_hits.clear();
////    gtr_clusters.clear();
////    hbd_hits.clear();
////    hbd_clusters.clear();
////    lg_hits.clear();
////    lg_clusters.clear();
////    tracks.clear();
////    hit_sets.clear();
////    track_sets.clear();
//  }
//  void SetValidFlag(int16_t _valid_flag) { valid_flag = _valid_flag; }
//  int16_t ValidFlag() { return valid_flag; }
//  int GetEventSize() const;
////  int GetEventSize() const { return GetEventSizeImpl(gtr_hits, gtr_clusters, hbd_hits, hbd_clusters, lg_hits, lg_clusters, tracks, hit_sets, track_sets) + sizeof(int); }
//  E16DST_DST0Detector<E16DST_DST1TriggerHit>&      GTRHits()     { return gtr_hits; }
//  E16DST_DST0Detector<E16DST_DST1TriggerCluster>&  GTRClusters() { return gtr_clusters; }
//  E16DST_DST0Detector<E16DST_DST1TriggerHit>&      HBDHits()     { return hbd_hits; }
//  E16DST_DST0Detector<E16DST_DST1TriggerCluster>&  HBDClusters() { return hbd_clusters; }
//  E16DST_DST0Detector<E16DST_DST1TriggerHit>&      LGHits()      { return lg_hits; }
//  E16DST_DST0Detector<E16DST_DST1TriggerCluster>&  LGClusters()  { return lg_clusters; }
//  E16DST_DST0Detector<E16DST_DST1TriggerHit>&      Tracks()      { return tracks; }
//  E16DST_DST0Detector<E16DST_DST1TriggerTrackSet>& HitSets()     { return hit_sets; }
//  E16DST_DST0Detector<E16DST_DST1TriggerTrackSet>& TrackSets()   { return track_sets; }
////  std::vector<E16DST_DST1TriggerHit>&      GTRHits()     { return gtr_hits; }
////  std::vector<E16DST_DST1TriggerCluster>&  GTRClusters() { return gtr_clusters; }
////  std::vector<E16DST_DST1TriggerHit>&      HBDHits()     { return hbd_hits; }
////  std::vector<E16DST_DST1TriggerCluster>&  HBDClusters() { return hbd_clusters; }
////  std::vector<E16DST_DST1TriggerHit>&      LGHits()      { return lg_hits; }
////  std::vector<E16DST_DST1TriggerCluster>&  LGClusters()  { return lg_clusters; }
////  std::vector<E16DST_DST1TriggerHit>&      Tracks()      { return tracks; }
////  std::vector<E16DST_DST1TriggerTrackSet>& HitSets()     { return hit_sets; }
////  std::vector<E16DST_DST1TriggerTrackSet>& TrackSets()   { return track_sets; }
//  int16_t NumTriggers() { return n_triggers; }
//  void Print();
//  void Print(E16ANA_GeometryV2& geometry);
// private:
//  int16_t valid_flag;
//  E16DST_DST0Detector<E16DST_DST0TriggerHit> gtr_hits;
//  E16DST_DST0Detector<E16DST_DST0TriggerHit> hbd_hits;
//  E16DST_DST0Detector<E16DST_DST0TriggerHit> lg_hits;
//  E16DST_DST0UT3                             ut3;
//  int16_t n_triggers;
//};

class E16DST_DST1Track {
 public:
  E16DST_DST1Track() {}
  ~E16DST_DST1Track() {}
 private:
  std::array<double, 3> initial_point_at_target_plain;
  std::array<double, 3> initial_momentum_at_initial_point;
};

class E16DST_DST1PhysicsEvent : public E16DST_DST0Event {
 public:
  E16DST_DST1PhysicsEvent() {}
  ~E16DST_DST1PhysicsEvent() {}
//  int GetEventSize() const override { return E16DST_DST0Event::GetEventSize() + ssd.GetEventSize() + gtr.GetEventSize() + hbd.GetEventSize() + lg.GetEventSize() + trigger.GetEventSize(); }
  int Write(E16DST_File* fp) override;
  int Read(E16DST_File* fp) override;
  void Clear() override;
  bool Append(E16DST_DST0Event* _another_event) override;
  uint16_t EventType() { return E16DST_DST0EventType::Physics; }
//  E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster>& SSD() { return ssd; }
  E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster>& GTR() { return gtr; }
//  E16DST_DST1Detector<E16DST_DST1HBDHit, E16DST_DST1HBDCluster>& HBD() { return hbd; }
  E16DST_DST1Detector<E16DST_DST1LGHit,  E16DST_DST1LGCluster>&  LG()  { return lg; }
  E16DST_DST0Detector<E16DST_DST1SSDHit>&     SSDHits()     { return ssd_hits; }
  E16DST_DST0Detector<E16DST_DST1SSDCluster>& SSDClusters() { return ssd_clusters; }
  E16DST_DST0Detector<E16DST_DST1GTRHit>&     GTRHits()     { return gtr_hits; }
  E16DST_DST0Detector<E16DST_DST1GTRCluster>& GTRClusters() { return gtr_clusters; }
  E16DST_DST0Detector<E16DST_DST1HBDHit>&     HBDHits()     { return hbd_hits; }
  E16DST_DST0Detector<E16DST_DST1HBDCluster>& HBDClusters() { return hbd_clusters; }
  E16DST_DST0Detector<E16DST_DST1LGHit>&      LGHits()      { return lg_hits; }
  E16DST_DST0Detector<E16DST_DST1LGCluster>&  LGClusters()  { return lg_clusters; }
  E16DST_DST1Trigger&                         Trigger()     { return trigger; }
 private:
//  E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> ssd;
  E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> gtr;
//  E16DST_DST1Detector<E16DST_DST1HBDHit, E16DST_DST1HBDCluster> hbd;
  E16DST_DST1Detector<E16DST_DST1LGHit,  E16DST_DST1LGCluster>  lg;
  E16DST_DST0Detector<E16DST_DST1SSDHit>     ssd_hits;
  E16DST_DST0Detector<E16DST_DST1SSDCluster> ssd_clusters;
  E16DST_DST0Detector<E16DST_DST1GTRHit>     gtr_hits;
  E16DST_DST0Detector<E16DST_DST1GTRCluster> gtr_clusters;
  E16DST_DST0Detector<E16DST_DST1HBDHit>     hbd_hits;
  E16DST_DST0Detector<E16DST_DST1HBDCluster> hbd_clusters;
  E16DST_DST0Detector<E16DST_DST1LGHit>      lg_hits;
  E16DST_DST0Detector<E16DST_DST1LGCluster>  lg_clusters;
  E16DST_DST1Trigger                         trigger;
};

//class E16DST_DST1 {
//public:
//   enum {
////      Version = 5, // should be incremented when a major update is implemented
//      WriteMode = 0,
//      ReadMode = 1
//   };
//   enum {
//      Auto,
//      NonCompressed,
//      ZlibGzip
//   };
//   E16DST_DST1();
//   ~E16DST_DST1();
//   bool Open(std::string file_name, int open_mode, int compress_mode = Auto);
//   void Close() { if (file) file->close(); };
//   E16DST_DST0Event *Event() { return event; };
//   uint16_t EventType() { return eventType.EventType(); };
//   int GetEventSize() const { return sizeof(E16DST_DST0EventType) + event->GetEventSize(); }
//   void SetEventType(uint16_t type);
//   void WriteAnEvent() { WriteAnEvent(file); };
//   int ReadAnEvent() { return ReadAnEvent(file); };
//   void WriteAnEvent(uint16_t type, E16DST_DST0Event *_event);
//   void WriteAnEvent(E16DST_DST0Event *_event) { WriteAnEvent(_event->EventType(), _event); };
////   void SetStartTime(uint16_t _hour, uint16_t _min, uint16_t _sec) { header.SetStartTime(_hour, _min, _sec); };
////   void SetTrgVer(uint32_t _trgVer) { header.SetTrgVer(_trgVer); };
//private:
//   //int open_mode;
//   E16DST_DST0Header header;
//   E16DST_DST0EventType eventType;
//   E16DST_DST0Event *event;
//   E16DST_DST0Event *eventStorage[E16DST_DST0EventType::NEventTypes];
//   E16DST_File *file{nullptr};
//   void WriteAnEvent(E16DST_File *fp);
//   int ReadAnEvent(E16DST_File *fp);
//};

int E16DST_DST1SSDFactory(E16DST_DST0Detector<E16DST_DST0SSDHit>& hits0, E16DST_DST0Detector<E16DST_DST1SSDHit>* hits1, E16DST_DST0Detector<E16DST_DST1SSDCluster>* clusters1); // return size
int E16DST_DST1SSDFactory(E16DST_DST0Detector<E16DST_DST0SSDHit>& hits0, E16DST_DST0Detector<E16DST_DST1SSDHit>* hits1, E16DST_DST0Detector<E16DST_DST1SSDCluster>* clusters1); // return size
class E16DST_DST1GTRAnalyzerMaker;
int E16DST_DST1GTRHitAndClusterFactory(E16DST_DST0Detector<E16DST_DST0GTRHit>& hits0, E16DST_DST0Detector<E16DST_DST1GTRHit>* hits1, E16DST_DST0Detector<E16DST_DST1GTRCluster>* clusters1);
//int E16DST_DST1GTRFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0GTRHit>& hits0, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster>* gtr1);
//int E16DST_DST1GTRFactory(E16DST_DST0Detector<E16DST_DST0GTRHit>& hits0, E16DST_DST0Detector<E16DST_DST1GTRHit>* hits1, E16DST_DST0Detector<E16DST_DST1GTRCluster>* clusters1);
int E16DST_DST1HBDFactory(E16DST_DST0Detector<E16DST_DST0HBDHit>& hits0, E16DST_DST0Detector<E16DST_DST1HBDHit>* hits1, E16DST_DST0Detector<E16DST_DST1HBDCluster>* clusters1);
int E16DST_DST1LGFactory(E16DST_DST0Detector<E16DST_DST0LGHit>& hits0,   E16DST_DST0Detector<E16DST_DST1LGHit>* hits1,  E16DST_DST0Detector<E16DST_DST1LGCluster>* clusters1);
int E16DST_DST1LGFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0LGHit>& hits0,   E16DST_DST1Detector<E16DST_DST1LGHit, E16DST_DST1LGCluster>* lg1);
int E16DST_DST1TriggerFactory(E16ANA_TriggerCalibParam& trigger_param, E16DST_DST0Detector<E16DST_DST0TriggerHit>& gtr_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& hbd_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& lg_hits, E16DST_DST0UT3& ut3, E16DST_DST1Trigger* trigger);
int E16DST_DST1TrackFactory();

#endif
