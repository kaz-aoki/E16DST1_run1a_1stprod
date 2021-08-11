#ifndef E16DST_DST1_HH
#define E16DST_DST1_HH

#include <iostream>
#include <vector>

#include <TVector3.h>

#include "E16DST_Constant.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1Constant.hh"

//template <class T>
//class E16DST_DST1Detector {
// public:
//  E16DST_DST1Detector() {}
//  ~E16DST_DST1Detector() {}
//  void     SetValidFlag(uint32_t _valid_flag) { valid_flag = _valid_flag; }
//  uint32_t ValidFlag() { return valid_flag; }
//  void     Resize(int n) { hits.resize(n); }
//  void     Reserve(int n) { hits.reserve(n); }
//  void     PushBack() { hits.push_back(T()); }
//  void     PushBack(const T& hit) { hits.push_back(hit); }
//  void     Clear() {
//    valid_flag = 0;
//    hits.clear();
//  }
//  T&       Back() { return hits.back(); }
//  T&       Hit(int i) { return hits[i]; }
//  int      Size() { return hits.size(); }
//  int      Write(E16DST_File* fp);
//  int      Read(E16DST_File* fp);
//  void     Append(E16DST_DST1Detector<T>& rhs);
//  int      GetEventSize();
// private:
//  uint32_t       valid_flag;
//  std::array<std::vector<T>, 8> hits;
//};

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
  void             SetIds(uint16_t _module_id, uint16_t _channel_id) {
    module_id  = _module_id;
    channel_id = _channel_id;
  }
  void             SetTiming(float _timing) { timing = _timing; }
  virtual void     SetPeakHeight(float _peak_height) = 0;
  int16_t          ModuleId() { return module_id; }
  int16_t          ChannelId() { return channel_id; }
  float            Timing() { return timing; }
  virtual float    PeakHeight() = 0;
  virtual TVector3 LocalPos() = 0;
  virtual TVector3 GlobalPos() = 0;
  virtual void     Print() {
    std::cout << "Module ID: " << module_id << ", Channel ID: " << channel_id << ", Timing: " << timing << std::endl;
  }
 protected:
  int16_t module_id;
  int16_t channel_id;
  float   timing; // 50% of peak
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
  void                      SetModuleId(int _module_id) { module_id = _module_id; }
  void                      SetMaxPeakCh(int _max_peak_ch) { max_peak_ch = _max_peak_ch; }
  void                      SetMaxPeakHeight(int _max_peak_height) { max_peak_height = _max_peak_height; }
  void                      SetTiming(float _timing) { timing = _timing; }
  void                      SetPeakSum(float _peak_sum) { peak_sum = _peak_sum; }
  void                      SetHitOrders(E16DST_DST0Detector<int>& _hit_orders);
  int                       ModuleId() { return module_id; }
  int                       MaxPeakCh() { return max_peak_ch; }
  float                     MaxPeakHeight() { return max_peak_height; }
  float                     Timing() { return timing; }
  float                     PeakSum() { return peak_sum; }
  int                       NumHits() { return hit_orders.NumberOfHits(); }
  E16DST_DST0Detector<int>& HitOrders() { return hit_orders; }
  int                       HitOrders(int n) { return hit_orders.Hit(n); }
  virtual TVector3          LocalPos() = 0;
  virtual TVector3          GlobalPos() = 0;
  virtual void              Print() {
    std::cout << "Module ID: " << module_id << ", Max peak channel: " << max_peak_ch << ", Max peak height: " << max_peak_height << ", Timing: " << timing << ", Peak sum: " << peak_sum << ", Number of hits: " << NumHits() << std::endl;
  }
 protected:
  int                      module_id;
  int                      max_peak_ch;
  float                    max_peak_height;
  float                    timing;
  float                    peak_sum;
  E16DST_DST0Detector<int> hit_orders; // Order in E16DST_DST0Detector<E16DST_DST1xxxHit>
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
  TVector3 LocalPos() override;
  TVector3 GlobalPos() override;
 private:
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
  void     SetCogPos(float _center_of_gravity)    { center_of_gravity = _center_of_gravity; }
  void     SetTdcPos(float _tdc_pos)              { tdc_pos = _tdc_pos; }
  void     SetTanTheta(float _tan_incident_angle) { tan_incident_angle = _tan_incident_angle; }
  float    CogPos() { return center_of_gravity; }
  float    TdcPos() { return tdc_pos; }
  float    TanTheta() { return tan_incident_angle; }
  double   LocalX();
  TVector3 LocalPos() override;
  TVector3 GlobalPos() override;
  void     Print() override {
    std::cout << "E16DST_DST1SSDCluster : "
              << "Num hit strips = " << NumHits() << ", Cluster charge = " << peak_sum
              << ", Cog hit pos = " << center_of_gravity << " [mm], TDC hit pos = " << tdc_pos 
              << " [mm]" << std::endl;
  }
 private:
  float center_of_gravity; // mm
  float tdc_pos;           // mm
  float tan_incident_angle;    // radian
};

class E16DST_DST1GTRHit : public E16DST_DST1Hit {
 public:
  E16DST_DST1GTRHit() { SetInvalid(); }
  ~E16DST_DST1GTRHit() {}
  void SetInvalid() override {
    SetBaseInvalid();
    peak_height = E16DST_DST1Constant::kInvalidValue;
    tot = E16DST_DST1Constant::kInvalidValue;
  }
  void SetPeakHeight(float _peak_height) override { peak_height = _peak_height; }
  void SetTot(float _tot) { tot = _tot; }
  float PeakHeight() override { return peak_height; }
  float Tot() { return tot; }
  double LocalX();
  TVector3 LocalPos() override;
  TVector3 GlobalPos() override;
 private:
//  int layer_id;
//  int type;
  float peak_height;
  float tot;
 };

class E16DST_DST1GTRCluster : public E16DST_DST1Cluster {
 public:
  E16DST_DST1GTRCluster() { SetInvalid(); }
  ~E16DST_DST1GTRCluster() {}
  void SetInvalid() override {
    SetBaseInvalid();
    center_of_gravity = E16DST_DST1Constant::kInvalidValue;
    tdc_pos = E16DST_DST1Constant::kInvalidValue;
    tan_incident_angle = E16DST_DST1Constant::kInvalidValue;
  }
  void SetCogPos(float _center_of_gravity) { center_of_gravity = _center_of_gravity; }
  void SetTdcPos(float _tdc_pos) { tdc_pos = _tdc_pos; }
  void SetTanTheta(float _tan_incident_angle) { tan_incident_angle = _tan_incident_angle; }
  float CogPos() { return center_of_gravity; }
  float TdcPos() { return tdc_pos; }
  float TanTheta() { return tan_incident_angle; }
  double LocalX();
  TVector3 LocalPos() override;
  TVector3 GlobalPos() override;
  void Print() override {
    std::cout << "E16DST_DST1GTRCluster : "
              << "Num hit strips = " << NumHits() << ", Cluster charge = " << peak_sum
              << ", Cog hit pos = " << center_of_gravity << " [mm], TDC hit pos = " << tdc_pos 
              << " [mm]" << std::endl;
  }
 private:
  float center_of_gravity; // mm
  float tdc_pos;           // mm
  float tan_incident_angle;    // radian
};

//class E16DST_DST1GTR {
// public:
//  E16DST_DST1GTR() {}
//  ~E16DST_DST1GTR() {}
//  void SetGTRHit(std::vector<E16DST_DST1GTRHit> _hit);
// private:
//  E16DST_DST1Detector<E16DST_DST1GTRHit>     hits;
//  E16DST_DST1Detector<E16DST_DST1GTRCluster> clusters;
//}

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
  TVector3 LocalPos() override;
  TVector3 GlobalPos() override;
  void Print() override {
  }
 private:
  float peak_height;
};

class E16DST_DST1HBDCluster : public E16DST_DST1Cluster {
 public:
  E16DST_DST1HBDCluster() { SetInvalid(); }
  ~E16DST_DST1HBDCluster() {}
  void SetInvalid() override {
    SetBaseInvalid();
  }
  TVector3 LocalPos() override;
  TVector3 GlobalPos() override;
  void Print() override {}
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
  TVector3 LocalPos() override;
  TVector3 GlobalPos() override;
 private:
  float peak_height;
  int peak_time;
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
  TVector3 GlobalPos() override;
  void Print() override {}
};

class E16DST_DST1TriggerHit : public E16DST_DST1Hit {
 public:
  E16DST_DST1TriggerHit() { SetInvalid(); }
  ~E16DST_DST1TriggerHit() {}
  void SetInvalid() override {
    SetBaseInvalid();
  }
  void SetPeakHeight(float _peak_height) override {}
  float PeakHeight() override { return E16DST_DST1Constant::kInvalidValue; }
  TVector3 LocalPos() override;
  TVector3 GlobalPos() override;
};

class E16DST_DST1TriggerCluster {
 public:
  E16DST_DST1TriggerCluster() {}
  ~E16DST_DST1TriggerCluster() {}
};

class E16DST_DST1TriggerTrackSet {
 public:
  E16DST_DST1TriggerTrackSet() {}
  ~E16DST_DST1TriggerTrackSet() {}
  void              Set();
  int               LGHitOrder()       { return lg_hit_order; }
  int               NumGtrHits()       { return gtr_hit_orders.size(); }
  std::vector<int>& GTRHitOrders()     { return gtr_hit_orders; }
  int               GTRHitOrder(int n) { return gtr_hit_orders[n]; }
  int               NumHbdHits()       { return hbd_hit_orders.size(); }
  std::vector<int>& HBDHitOrders()     { return hbd_hit_orders; }
  int               HBDHitOrder(int n) { return hbd_hit_orders[n]; }
 private:
  int              lg_hit_order;
  std::vector<int> gtr_hit_orders;
  std::vector<int> hbd_hit_orders;
};

class E16DST_DST1Trigger {
 public:
  E16DST_DST1Trigger() {}
  ~E16DST_DST1Trigger() {}
  void SetValidFlag(int _valid_flag) { valid_flag = _valid_flag; }
  int ValidFlag() { return valid_flag; }
  int GetEventSize() const {}
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
  int NumTriggers() { return n_triggers; }
 private:
  int valid_flag;
  E16DST_DST0Detector<E16DST_DST1TriggerHit>      gtr_hits;
  E16DST_DST0Detector<E16DST_DST1TriggerHit>      hbd_hits;
  E16DST_DST0Detector<E16DST_DST1TriggerHit>      lg_hits;
  E16DST_DST0Detector<E16DST_DST1TriggerCluster>  gtr_clusters;
  E16DST_DST0Detector<E16DST_DST1TriggerCluster>  hbd_clusters;
  E16DST_DST0Detector<E16DST_DST1TriggerCluster>  lg_clusters;
  E16DST_DST0Detector<E16DST_DST1TriggerHit>      tracks;
  E16DST_DST0Detector<E16DST_DST1TriggerTrackSet> hit_sets;
  E16DST_DST0Detector<E16DST_DST1TriggerTrackSet> track_sets;
  int n_triggers;
};

class E16DST_DST1PhysicsEvent : public E16DST_DST0Event {
 public:
  E16DST_DST1PhysicsEvent() {}
  ~E16DST_DST1PhysicsEvent() {}
  int GetEventSize() const override { return E16DST_DST0Event::GetEventSize() + GetEventSizeImpl(ssd_hits, ssd_clusters, gtr_100_x_hits, gtr_100_x_clusters, gtr_100_y_hits, gtr_100_y_clusters, gtr_100_yb_hits, gtr_100_yb_clusters, gtr_200_x_hits, gtr_200_x_clusters, gtr_200_y_hits, gtr_200_y_clusters, gtr_300_x_hits, gtr_300_x_clusters, gtr_300_y_hits, gtr_300_y_clusters, hbd_hits, hbd_clusters, lg_hits, lg_clusters) + trigger.GetEventSize(); }
  int Write(E16DST_File* fp);
  int Read(E16DST_File* fp);
  void Clear();
  bool Append(E16DST_DST0Event* _another_event);
  uint16_t EventType() { return E16DST_DST0EventType::Physics; }
  E16DST_DST0Detector<E16DST_DST1SSDHit>&     SSDHits()          { return ssd_hits; }
  E16DST_DST0Detector<E16DST_DST1SSDCluster>& SSDClusters()      { return ssd_clusters; }
  E16DST_DST0Detector<E16DST_DST1GTRHit>&     GTR100XHits()      { return gtr_100_x_hits; }
  E16DST_DST0Detector<E16DST_DST1GTRCluster>& GTR100XClusters()  { return gtr_100_x_clusters; }
  E16DST_DST0Detector<E16DST_DST1GTRHit>&     GTR100YHits()      { return gtr_100_y_hits; }
  E16DST_DST0Detector<E16DST_DST1GTRCluster>& GTR100YClusters()  { return gtr_100_y_clusters; }
  E16DST_DST0Detector<E16DST_DST1GTRHit>&     GTR100YbHits()     { return gtr_100_yb_hits; }
  E16DST_DST0Detector<E16DST_DST1GTRCluster>& GTR100YbClusters() { return gtr_100_yb_clusters; }
  E16DST_DST0Detector<E16DST_DST1GTRHit>&     GTR200XHits()      { return gtr_200_x_hits; }
  E16DST_DST0Detector<E16DST_DST1GTRCluster>& GTR200XClusters()  { return gtr_200_x_clusters; }
  E16DST_DST0Detector<E16DST_DST1GTRHit>&     GTR200YHits()      { return gtr_200_y_hits; }
  E16DST_DST0Detector<E16DST_DST1GTRCluster>& GTR200YClusters()  { return gtr_200_y_clusters; }
  E16DST_DST0Detector<E16DST_DST1GTRHit>&     GTR300XHits()      { return gtr_300_x_hits; }
  E16DST_DST0Detector<E16DST_DST1GTRCluster>& GTR300XClusters()  { return gtr_300_x_clusters; }
  E16DST_DST0Detector<E16DST_DST1GTRHit>&     GTR300YHits()      { return gtr_300_y_hits; }
  E16DST_DST0Detector<E16DST_DST1GTRCluster>& GTR300YClusters()  { return gtr_300_y_clusters; }
  E16DST_DST0Detector<E16DST_DST1HBDHit>&     HBDHits()          { return hbd_hits; }
  E16DST_DST0Detector<E16DST_DST1HBDCluster>& HBDClusters()      { return hbd_clusters; }
  E16DST_DST0Detector<E16DST_DST1LGHit>&      LGHits()           { return lg_hits; }
  E16DST_DST0Detector<E16DST_DST1LGCluster>&  LGClusters()       { return lg_clusters; }
  E16DST_DST1Trigger&                         Trigger()          { return trigger; }
 private:
  E16DST_DST0Detector<E16DST_DST1SSDHit>     ssd_hits;
  E16DST_DST0Detector<E16DST_DST1SSDCluster> ssd_clusters;
  E16DST_DST0Detector<E16DST_DST1GTRHit>     gtr_100_x_hits;
  E16DST_DST0Detector<E16DST_DST1GTRCluster> gtr_100_x_clusters;
  E16DST_DST0Detector<E16DST_DST1GTRHit>     gtr_100_y_hits;
  E16DST_DST0Detector<E16DST_DST1GTRCluster> gtr_100_y_clusters;
  E16DST_DST0Detector<E16DST_DST1GTRHit>     gtr_100_yb_hits;
  E16DST_DST0Detector<E16DST_DST1GTRCluster> gtr_100_yb_clusters;
  E16DST_DST0Detector<E16DST_DST1GTRHit>     gtr_200_x_hits;
  E16DST_DST0Detector<E16DST_DST1GTRCluster> gtr_200_x_clusters;
  E16DST_DST0Detector<E16DST_DST1GTRHit>     gtr_200_y_hits;
  E16DST_DST0Detector<E16DST_DST1GTRCluster> gtr_200_y_clusters;
  E16DST_DST0Detector<E16DST_DST1GTRHit>     gtr_300_x_hits;
  E16DST_DST0Detector<E16DST_DST1GTRCluster> gtr_300_x_clusters;
  E16DST_DST0Detector<E16DST_DST1GTRHit>     gtr_300_y_hits;
  E16DST_DST0Detector<E16DST_DST1GTRCluster> gtr_300_y_clusters;
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

int E16DST_DST1SSDHitAndClusterFactory(E16DST_DST0Detector<E16DST_DST0SSDHit>& hits0, E16DST_DST0Detector<E16DST_DST1SSDHit>& hits1, E16DST_DST0Detector<E16DST_DST1SSDCluster>& clusters1); // return size
int E16DST_DST1GTRHitAndClusterFactory(E16DST_DST0Detector<E16DST_DST0GTRHit>& hits0,
                                       E16DST_DST0Detector<E16DST_DST1GTRHit>* hits_100_x_1,  E16DST_DST0Detector<E16DST_DST1GTRCluster>* clusters_100_x_1,
                                       E16DST_DST0Detector<E16DST_DST1GTRHit>* hits_100_y_1,  E16DST_DST0Detector<E16DST_DST1GTRCluster>* clusters_100_y_1,
                                       E16DST_DST0Detector<E16DST_DST1GTRHit>* hits_100_yb_1, E16DST_DST0Detector<E16DST_DST1GTRCluster>* clusters_100_yb_1,
                                       E16DST_DST0Detector<E16DST_DST1GTRHit>* hits_200_x_1,  E16DST_DST0Detector<E16DST_DST1GTRCluster>* clusters_200_x_1,
                                       E16DST_DST0Detector<E16DST_DST1GTRHit>* hits_200_y_1,  E16DST_DST0Detector<E16DST_DST1GTRCluster>* clusters_200_y_1,
                                       E16DST_DST0Detector<E16DST_DST1GTRHit>* hits_300_x_1,  E16DST_DST0Detector<E16DST_DST1GTRCluster>* clusters_300_x_1,
                                       E16DST_DST0Detector<E16DST_DST1GTRHit>* hits_300_y_1,  E16DST_DST0Detector<E16DST_DST1GTRCluster>* clusters_300_y_1);
int E16DST_DST1HBDHitAndClusterFactory(E16DST_DST0Detector<E16DST_DST0HBDHit>&         hits0,                      E16DST_DST0Detector<E16DST_DST1HBDHit>*     hits1, E16DST_DST0Detector<E16DST_DST1HBDCluster>*     clusters1);
int E16DST_DST1LGHitAndClusterFactory(E16DST_DST0Detector<E16DST_DST0LGHit>&           hits0,                      E16DST_DST0Detector<E16DST_DST1LGHit>*      hits1, E16DST_DST0Detector<E16DST_DST1LGCluster>*      clusters1);
int E16DST_DST1TriggerHitAndClusterFactory(E16DST_DST0Detector<E16DST_DST0TriggerHit>& hits0, uint64_t time_stamp, E16DST_DST0Detector<E16DST_DST1TriggerHit>* hits1, E16DST_DST0Detector<E16DST_DST1TriggerCluster>* clusters1);
int E16DST_DST1TiggerFactory(E16DST_DST0Detector<E16DST_DST1TriggerHit>& gtr_hits, E16DST_DST0Detector<E16DST_DST1TriggerHit>& hbd_hits, E16DST_DST0Detector<E16DST_DST1TriggerHit>& lg_hits, E16DST_DST1Trigger* trigger);

template <typename T>
int E16DST_DST1IsTriggerHit(T hit);

#endif
