#ifndef E16DST_DST1_HH
#define E16DST_DST1_HH

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "TVector3.h"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_MagneticFieldMap.hh"
#include "E16ANA_MultiTrack.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TrackConstant.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16ANA_LGBasic.hh"
#include "E16DST_Constant.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1Constant.hh"

#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDCut.hh"
#include "E16ANA_WaveformFitter.hh"
//#pragma pack(2)

class E16DST_DST1Hit {
 public:
  E16DST_DST1Hit()
      : module_id(E16DST_DST1Constant::kInvalidValue),
        channel_id(E16DST_DST1Constant::kInvalidValue),
        timing(E16DST_DST1Constant::kInvalidValue) {}
  ~E16DST_DST1Hit() {}
  virtual void     SetInvalid() { SetBaseInvalid(); }
  void             SetBaseInvalid() {
    module_id  = E16DST_DST1Constant::kInvalidValue;
    channel_id = E16DST_DST1Constant::kInvalidValue;
    timing     = E16DST_DST1Constant::kInvalidValue;
  }
  void             SetHitId(int _hit_id) { hit_id = _hit_id; }
  void             SetIds(int16_t _module_id, int16_t _channel_id) {
    module_id  = _module_id;
    channel_id = _channel_id;
  }
  void             SetTiming(float _timing) { timing = _timing; }
  virtual void     SetPeakHeight(float _peak_height) = 0;
  int              HitId() { return hit_id; }
  int16_t          ModuleId() { return module_id; }
  virtual int16_t  LayerId() { return 0; }
  virtual int16_t  Type() { return 0; }
  int16_t          ChannelId() { return channel_id; }
  float            Timing() { return timing; }
  virtual float    PeakHeight() = 0;
  virtual TVector3 LocalPos(E16ANA_GeometryV2& geometry) = 0;
  virtual TVector3 GlobalPos(E16ANA_GeometryV2& geometry) = 0;
  virtual void     Print() {
std::cout << "print begin" << std::endl;
    std::cout << "Module ID: " << module_id << ", Channel ID: " << channel_id << ", Timing: " << timing << std::endl;
std::cout << "print end" << std::endl;
  }
 protected:
  virtual int ModuleId2020To2013(int module_id) = 0;
  int         hit_id;
  int16_t     module_id;
  int16_t     channel_id;
  float       timing; // 50% of peak
};

class E16DST_DST1Cluster {
 public:
  E16DST_DST1Cluster()
      : module_id(E16DST_DST1Constant::kInvalidValue),
        max_peak_ch(E16DST_DST1Constant::kInvalidValue),
        max_peak_height(E16DST_DST1Constant::kInvalidValue),
        timing(E16DST_DST1Constant::kInvalidValue),
        peak_sum(E16DST_DST1Constant::kInvalidValue),
        hit_orders({}) {}
//  ~E16DST_DST1Cluster() { hit_orders.clear(); }
  ~E16DST_DST1Cluster() { std::vector<int16_t>().swap(hit_orders); }
  virtual void                  SetInvalid() { SetBaseInvalid(); }
  void                          SetBaseInvalid() {
    module_id       = E16DST_DST1Constant::kInvalidValue;
    max_peak_ch     = E16DST_DST1Constant::kInvalidValue;
    max_peak_height = E16DST_DST1Constant::kInvalidValue;
    timing          = E16DST_DST1Constant::kInvalidValue;
    peak_sum        = E16DST_DST1Constant::kInvalidValue;
    hit_orders.clear();
  }
  void                          SetClusterId(int _cluster_id) { cluster_id = _cluster_id; }
  void                          SetModuleId(int _module_id) { module_id = _module_id; }
  void                          SetMaxPeakCh(int _max_peak_ch) { max_peak_ch = _max_peak_ch; }
  void                          SetMaxPeakHeight(int _max_peak_height) { max_peak_height = _max_peak_height; }
  void                          SetTiming(float _timing) { timing = _timing; }
  void                          SetPeakSum(float _peak_sum) { peak_sum = _peak_sum; }
  void                          SetHitOrders(std::vector<int16_t>& _hit_orders);
  int                           ClusterId() { return cluster_id; }
  int                           ModuleId() { return module_id; }
  virtual int16_t               LayerId() { return 0; }
  virtual int16_t               Type() { return 0; }
  int                           MaxPeakCh() { return max_peak_ch; }
  float                         MaxPeakHeight() { return max_peak_height; }
  float                         Timing() { return timing; }
  float                         PeakSum() { return peak_sum; }
//  int                           NumHits() { return hit_orders.NumberOfHits(); }
//  E16DST_DST0Detector<int16_t>& HitOrders() { return hit_orders; }
//  int16_t                       HitOrder(int n) { return hit_orders.Hit(n); }
  int                           NumHits() { return hit_orders.size(); }
  std::vector<int16_t>&         HitOrders() { return hit_orders; }
  int16_t                       HitOrder(int n) { return hit_orders[n]; }
  virtual TVector3              LocalPos() = 0;
  virtual TVector3              GlobalPos(E16ANA_GeometryV2& geometry) = 0;
//  int                           GetBaseSize() { return sizeof(module_id) + sizeof(int16_t) + sizeof(max_peak_ch) + sizeof(max_peak_height) + sizeof(timing) + sizeof(peak_sum) + sizeof(int16_t) * hit_orders.size(); }
  virtual int                   GetSize() = 0;
  virtual void                  Print() {
    std::cout << "Module ID: " << module_id << ", Max peak channel: " << max_peak_ch << ", Max peak height: " << max_peak_height << ", Timing: " << timing << ", Peak sum: " << peak_sum << ", Number of hits: " << NumHits() << std::endl;
  }
 protected:
  virtual int                  ModuleId2020To2013(int module_id) = 0;
  int                          cluster_id;
  int                          module_id;
  int                          max_peak_ch;
  float                        max_peak_height;
  float                        timing;
  float                        peak_sum;
//  E16DST_DST0Detector<int16_t> hit_orders; // Order in E16DST_DST0Detector<E16DST_DST1xxxHit>
  std::vector<int16_t> hit_orders; // Order in E16DST_DST0Detector<E16DST_DST1xxxHit>
};

class E16DST_DST1SSDHit : public E16DST_DST1Hit {
 public:
  E16DST_DST1SSDHit()
      : peak_height(E16DST_DST1Constant::kInvalidValue),
        hit_time(E16DST_DST1Constant::kInvalidValue),
        peak_time(E16DST_DST1Constant::kInvalidValue) {}
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
  E16DST_DST1SSDCluster()
      : center_of_gravity(E16DST_DST1Constant::kInvalidValue),
        tdc_pos(E16DST_DST1Constant::kInvalidValue),
        tan_incident_angle(E16DST_DST1Constant::kInvalidValue) {}
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
  double   LocalX() { return center_of_gravity; };
  TVector3 LocalPos() override;
  TVector3 GlobalPos(E16ANA_GeometryV2& geometry) override;
  int      GetSize() override {}
//  int      GetSize() override { return GetBaseEventSize() + sizeof(center_of_gravity) + sizeof(tdc_pos) + sizeof(tan_incident_angle); }
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
  E16DST_DST1GTRHit()
      : layer_id(E16DST_DST1Constant::kInvalidValue),
        type(E16DST_DST1Constant::kInvalidValue),
        peak_height(E16DST_DST1Constant::kInvalidValue),
        tot(E16DST_DST1Constant::kInvalidValue) {}
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
  int16_t LayerId() override { return layer_id; }
  bool IsX() { return type == E16DST_DST1Constant::kIsX; }
  bool IsY() { return type == E16DST_DST1Constant::kIsY; }
  bool IsYb() { return type == E16DST_DST1Constant::kIsYb; }
  int16_t Type() override { return type; }
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
  E16DST_DST1GTRCluster()
      : layer_id(E16DST_DST1Constant::kInvalidValue),
        type(E16DST_DST1Constant::kInvalidValue),
        center_of_gravity(E16DST_DST1Constant::kInvalidValue),
        tdc_pos(E16DST_DST1Constant::kInvalidValue),
        tan_incident_angle(E16DST_DST1Constant::kInvalidValue) {}
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
  int16_t LayerId() override { return layer_id; }
  bool IsX() { return type == E16DST_DST1Constant::kIsX; }
  bool IsY() { return type == E16DST_DST1Constant::kIsY; }
  bool IsYb() { return type == E16DST_DST1Constant::kIsYb; }
  int16_t Type() override { return type; }
  double CogPos() { return center_of_gravity; }
  double TdcPos() { return tdc_pos; }
  float TanTheta() { return tan_incident_angle; }
  double LocalX() { return center_of_gravity; };
  TVector3 LocalPos() override;
  TVector3 GlobalPos(E16ANA_GeometryV2& geometry) override;
  int GetSize() override {}
//  int GetSize() override { return GetBaseSize() + sizeof(layer_id) + sizeof(type) + sizeof(center_of_gravity) + sizeof(tdc_pos) + sizeof(tan_incident_angle); }
  void Print() override {
    std::cout << "E16DST_DST1GTRCluster : "
              << "Num hit strips = " << NumHits() << 
              ", Cluster charge = " << peak_sum
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
  E16DST_DST1HBDHit()
    : chi2(E16DST_DST1Constant::kInvalidValue),
      peak_height(E16DST_DST1Constant::kInvalidValue),
      lpos(E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue){};
  ~E16DST_DST1HBDHit(){}
  void SetInvalid() override {
    SetBaseInvalid();
    chi2 = E16DST_DST1Constant::kInvalidValue;
    peak_height = E16DST_DST1Constant::kInvalidValue;
    lpos = TVector3(E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue);
  }
  void SetChi2(float _chi2){ chi2 = _chi2;};
  void SetPeakHeight(float _peak_height) override { peak_height = _peak_height; }
  void SetLocalPos(TVector3 _lpos){ lpos = _lpos; };
  float PeakHeight() override { return peak_height; }
  float Chi2(){return chi2;};
  TVector3 LocalPos(E16ANA_GeometryV2& geometry) override;
  TVector3 GlobalPos(E16ANA_GeometryV2& geometry) override;
  void Print() override {
  }
 private:
  int   ModuleId2020To2013(int module_id) override { return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100 + 1]; }
  float chi2; //chi2 of waveform fitting, NOT divided by ndf
  float peak_height;
  TVector3 lpos;
};

class E16DST_DST1HBDCluster : public E16DST_DST1Cluster {
 public:
  E16DST_DST1HBDCluster()
      : fastest_timing(E16DST_DST1Constant::kInvalidValue),
        time_difference(E16DST_DST1Constant::kInvalidValue),
	csize(E16DST_DST1Constant::kInvalidValue),
	eprob(E16DST_DST1Constant::kInvalidValue),
	cprob(E16DST_DST1Constant::kInvalidValue),
	sadc(E16DST_DST1Constant::kInvalidValue),
	lpos(E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue,E16DST_DST1Constant::kInvalidValue),
	lpos_w_adc(E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue,E16DST_DST1Constant::kInvalidValue){};
  
  ~E16DST_DST1HBDCluster() {}
  void SetInvalid() override {
    SetBaseInvalid();
    fastest_timing    = E16DST_DST1Constant::kInvalidValue;
    time_difference = E16DST_DST1Constant::kInvalidValue;
    csize = E16DST_DST1Constant::kInvalidValue;
    eprob = E16DST_DST1Constant::kInvalidValue;
    cprob = E16DST_DST1Constant::kInvalidValue;
    sadc = E16DST_DST1Constant::kInvalidValue;
    lpos = TVector3(E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue);
    lpos_w_adc = TVector3(E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue);
  }
  void SetFastestTiming(float _fastest_timing){ fastest_timing = _fastest_timing; };
  void SetTimeDifference(float _time_difference){ time_difference = _time_difference; };
  void SetClusterSize(int _csize){ csize = _csize; };
  void SetLocalPos(TVector3 _lpos){ lpos = _lpos; };
  void SetLocalPosWADC(TVector3 _lpos){ lpos_w_adc = _lpos; };
  void SetEProb(float _eprob){ eprob = _eprob; };
  void SetCProb(float _cprob){ cprob = _cprob; };
  void SetSADC(float _sadc){ sadc = _sadc; };
  float FastestTiming() { return fastest_timing; }
  float TimeDifference() { return time_difference; }
  int ClusterSize(){ return csize; };
  float IsE(){ return eprob;};
  float IsChargedParticle(){ return cprob;};
  float SADC(){ return sadc; };
  TVector3 LocalPos() override;
  TVector3 GlobalPos(E16ANA_GeometryV2& geometry) override;
  TVector3 GlobalPosWADC(E16ANA_GeometryV2& geometry);
  int GetSize() override {}
  void Print() override {}
 private:
  int   ModuleId2020To2013(int module_id) override { return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100 + 1]; }
  float fastest_timing;
  float time_difference;
  int csize; //cluster size = the number of pads belonging to a cluster
  float eprob;
  float cprob;
  float sadc;
  TVector3 lpos;
  TVector3 lpos_w_adc;
  int calib_status;
};

class E16DST_DST1LGHit : public E16DST_DST1Hit {
 public:
  E16DST_DST1LGHit()
      : peak_height(E16DST_DST1Constant::kInvalidValue),
        peak_time(E16DST_DST1Constant::kInvalidValue),
        baseline(E16DST_DST1Constant::kInvalidValue),
        baseline_rms(E16DST_DST1Constant::kInvalidValue),
        integral(E16DST_DST1Constant::kInvalidValue) {}
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
  void SetNpeaks(int _npeaks) { npeaks = _npeaks; }
  void SetNpeak(int _npeak) { npeak = _npeak; }
  void SetFitFlag(int _fitflag) { fitflag = _fitflag; }
  void SetFitPeak(float _fitpeak) { fitpeak = _fitpeak; }
  void SetFitPeakTime(float _fitpeaktime) { fitpeaktime = _fitpeaktime; }
  void SetFitTiming(float _fittiming) { fittiming = _fittiming; }
  void SetFitWidth(float _fitwidth) { fitwidth = _fitwidth; }
  void SetFitChi2(float _fitchi2) { fitchi2 = _fitchi2; }
  float PeakHeight() override { return peak_height; }
  int PeakTime() { return peak_time; }
  float Baseline() { return baseline; }
  float BaselineRms() { return baseline_rms; }
  float Integral() { return integral; }
  int Npeaks() { return npeaks; }
  int Npeak() { return npeak; }
  int FitFlag() { return fitflag; }
  float FitPeak() { return fitpeak; }
  float FitPeakTime() { return fitpeaktime; }
  float FitTiming() { return fittiming; }
  float FitWidth() { return fitwidth; }
  float FitChi2() { return fitchi2; }
  float GetCalibTiming(E16ANA_LGBasic& lgbasic);
  float GetCalibTiming(E16ANA_LGBasic& lgbasic, float _timing);
  float GetEnergyDeposit(E16ANA_LGBasic& lgbasic);
  TVector3 LocalPos(E16ANA_GeometryV2& geometry) override;
  TVector3 GlobalPos(E16ANA_GeometryV2& geometry) override;
 private:
  int   ModuleId2020To2013(int module_id) override { return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100 + 1]; }
  float peak_height; // baseline subtracted
  int   peak_time;
  float baseline;
  float baseline_rms;
  float integral; // baseline subtracted
  int npeaks;
  int npeak;
  int fitflag; // 0: not fitted (no pulse), 1: fit OK, 2: fit failed
  float fitpeak;
  float fitpeaktime;
  float fittiming;// calibrated channel by channel
  float fitwidth;
  float fitchi2;
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
  int GetSize() override {}
  void Print() override {}
 private:
  int ModuleId2020To2013(int module_id) override { return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100 + 1]; }
};

class E16DST_DST1TriggerHit : public E16DST_DST1Hit {
 public:
  E16DST_DST1TriggerHit()
      : detector(E16DST_DST1Constant::kInvalidValue) {}
  ~E16DST_DST1TriggerHit() {}
  void SetInvalid() override {
    SetBaseInvalid();
    detector = E16DST_DST1Constant::kInvalidValue;
  }
  void SetPeakHeight(float _peak_height) override {}
  void SetDetector(int16_t _detector) {
    if (_detector < E16DST_DST1Constant::kGTR || _detector > E16DST_DST1Constant::kLG) {
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
    if (detector == E16DST_DST1Constant::kGTR) {
      return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100];
    } else if (detector == E16DST_DST1Constant::kHBD || detector == E16DST_DST1Constant::kLG) {
      return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100 + 1];
    } else {
      return E16DST_DST1Constant::kInvalidValue;
    }
  }
  int detector;
};

class E16DST_DST1TriggerCluster : public E16DST_DST1Cluster {
 public:
  E16DST_DST1TriggerCluster()
      : detector(E16DST_DST1Constant::kInvalidValue) {}
  ~E16DST_DST1TriggerCluster() {}
 private:
  int ModuleId2020To2013(int module_id) override { return E16DST_DST1Constant::kModuleId2020To2013[module_id / 100][module_id % 100 + 1]; }
  int detector;
};

//class E16DST_DST1DetectorHeader {
// public:
//  E16DST_DST1DetectorHeader() {
//    valid_flag = E16DST_DST1Constant::kInvalidValue;
//    detector_version = E16DST_DST1Constant::kInvalidValue;
//    detector_id = E16DST_DST1Constant::kInvalidValue;
//    n_const_components = E16DST_DST1Constant::kInvalidValue;
//    n_var_components = E16DST_DST1Constant::kInvalidValue;
//    for (int i = 0; i < E16DST_DST1Constant::kNumDetectorComponents; ++i) {
//      const_component_version[i] = E16DST_DST1Constant::kInvalidValue;
//      const_component_id[i] = E16DST_DST1Constant::kInvalidValue;
//      const_component_qty[i] = E16DST_DST1Constant::kInvalidValue;
//      var_component_version[i] = E16DST_DST1Constant::kInvalidValue;
//      var_component_id[i] = E16DST_DST1Constant::kInvalidValue;
//      var_component_qty[i] = E16DST_DST1Constant::kInvalidValue;
//    }
//  }
//  ~E16DST_DST1DetectorHeader() {}
//  void SetValidFlag(int _valid_flag) { valid_flag = _valid_flag; }
//  void SetDetectorVersion(int16_t _detector_version) { detector_version = _detector_version; }
//  void SetDetectorId(int16_t _detector_id) { detector_id = _detector_id; }
//  void SetNumConstComponents(int16_t _n_const_components) { n_const_components = _n_const_components; }
//  void SetNumVarComponents(int16_t _n_var_components) { n_var_components = _n_var_components; }
//  void SetConstComponent(int n, int16_t version, int16_t id, int16_t qty) {
//    const_component_version[n] = version;
//    const_component_id[n]      = id;
//    const_component_qty[n]     = qty;
//  }
//  void SetVarComponent(int n, int16_t version, int16_t id, int16_t qty) {
//    var_component_version[n] = version;
//    var_component_id[n]      = id;
//    var_component_qty[n]     = qty;
//  }
//  int     ValidFlag()                  { return valid_flag; }
//  int16_t DetectorVersion()            { return detector_version; }
//  int16_t DetectorId()                 { return detector_id; }
//  int16_t NumConstComponents()         { return n_const_components; }
//  int16_t NumVarComponents()           { return n_var_components; }
//  int16_t ConstComponentVersion(int n) { return const_component_version[n]; }
//  int16_t ConstComponentId(int n)      { return const_component_id[n]; }
//  int16_t ConstComponentQty(int n)     { return const_component_qty[n]; }
//  int16_t VarComponentVersion(int n)   { return var_component_version[n]; }
//  int16_t VarComponentId(int n)        { return var_component_id[n]; }
//  int16_t VarComponentQty(int n)       { return var_component_qty[n]; }
//  virtual int Read(std::fstream* fp);
//  void    PrintHeader() {
//    std::cout << "detector version: " << detector_version << ", detector ID: " << detector_id
//              << ", number of const components: " << n_const_components << ", number of variable components: " << n_var_components << std::endl;
//  }
// protected:
//  int valid_flag;
//  int16_t detector_version;
//  int16_t detector_id;
//  int16_t n_const_components;
//  int16_t n_var_components;
//  int16_t const_component_version[E16DST_DST1Constant::kNumDetectorComponents];
//  int16_t const_component_id[E16DST_DST1Constant::kNumDetectorComponents];
//  int16_t const_component_qty[E16DST_DST1Constant::kNumDetectorComponents];
//  int16_t var_component_version[E16DST_DST1Constant::kNumDetectorComponents];
//  int16_t var_component_id[E16DST_DST1Constant::kNumDetectorComponents];
//  int16_t var_component_qty[E16DST_DST1Constant::kNumDetectorComponents];
//};

//template <class T, class U>
//class E16DST_DST1Detector : public E16DST_DST1DetectorHeader {
// public:
//  using value_type0 = T;
//  using value_type1 = U;
//  E16DST_DST1Detector() {
//    detector_version   = 0;
//    detector_id        = 0;
//    n_const_components = 1;
//    n_var_components   = 1;
//    const_component_version[0] = 0;
//    var_component_version[0]   = 0;
//    const_component_id[0] = E16DST_DST1Constant::kGTR;
//    var_component_id[0]   = E16DST_DST1Constant::kGTR;
////    auto const_component_name = getNameByNameInfo(typeid(T));
////    auto var_component_name   = getNameByNameInfo(typeid(U));
////    if (const_component_name == "E16DST_DST1GTRHit") {
////      const_component_id[0] = E16DST_DST1Constant::kGTR;
////    } else {
////      std::cerr << "invalid type: " << const_component_name << std::endl;
////      std::exit(1);
////    }
////    if (var_component_name == "E16DST_DST1GTRCluster") {
////      var_component_id[0] = E16DST_DST1Constant::kGTR;
////    } else {
////      std::cerr << "invalid type: " << var_component_name << std::endl;
////      std::exit(1);
////    }
//  }
//  ~E16DST_DST1Detector() {}
//  void Clear() {
//    hits.clear();
//    clusters.clear();
//    hit_ptrs.clear();
//    cluster_ptrs.clear();
//  }
//  void             ResizeHit(int n)                   { hits.resize(n); }
//  void             ReserveHit(int n)                  { hits.reserve(n); }
//  void             PushBackHit()                      { hits.push_back(T()); }
//  void             PushBackHit(const T& hit)          { hits.push_back(hit); }
//  T&               BackHit()                          { return hits.back(); }
//  T&               Hit(int i)                         { return hits[i]; }
//  std::vector<T>&  Hits()                             { return hits; }
//  int              NumHits()                          { return hits.size(); }
//  void             ResizeCluster(int n)               { clusters.resize(n); }
//  void             ReserveCluster(int n)              { clusters.reserve(n); }
//  void             PushBackCluster()                  { clusters.push_back(T()); }
//  void             PushBackCluster(const U& cluster)  { clusters.push_back(cluster); }
//  U&               BackCluster()                      { return clusters.back(); }
//  U&               Cluster(int i)                     { return clusters[i]; }
//  std::vector<U>&  Clusters()                         { return clusters; }
//  int              NumClusters()                      { return clusters.size(); }
//  void             UpdateHitPtrs();
//  void             UpdateClusterPtrs();
//  void             UpdatePtrs() {
//    UpdateHitPtrs();
//    UpdateClusterPtrs();
//  }
//  std::vector<T*>& HitPtrs(int module_id, int layer_id, int type) {
//    int id_sum = IdSum(module_id, layer_id, type);
//    return hit_ptrs[id_sum];
//  }
//  std::vector<U*>& ClusterPtrs(int module_id, int layer_id, int type) {
//    int id_sum = IdSum(module_id, layer_id, type);
//    return cluster_ptrs[id_sum];
//  }
//  std::vector<T*>  ClusterMembers(int cluster_id);
//  T&               ClusterMember(int cluster_id, int hit_id);
//  int              Write(std::fstream* fp);
//  int              Read(std::fstream* fp) override;
//  int              GetSize();
//  void             Print();
// private:
//  int                                      IdSum(int module_id, int layer_id, int type) { return 10000 * module_id + 100 * layer_id + type; }
//  std::vector<T>                           hits;
//  std::vector<U>                           clusters;
//  std::unordered_map<int, std::vector<T*>> hit_ptrs;
//  std::unordered_map<int, std::vector<U*>> cluster_ptrs;
//};

class E16DST_DST1TriggerTrackSet {
 public:
  E16DST_DST1TriggerTrackSet() {}
  ~E16DST_DST1TriggerTrackSet() {}
  int GetEventSize();
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
  int Write(std::fstream* fp);
  int Read(std::fstream* fp);
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
    gtr_hits.clear();
    gtr_clusters.clear();
    hbd_hits.clear();
    hbd_clusters.clear();
    lg_hits.clear();
    lg_clusters.clear();
    tracks.clear();
    hit_sets.clear();
    track_sets.clear();
  }
  void SetValidFlag(int16_t _valid_flag) { valid_flag = _valid_flag; }
  void SetNumTriggers(int16_t _n_triggers) { n_triggers = _n_triggers; }
  int16_t ValidFlag() { return valid_flag; }
  int GetEventSize() const;
//  int GetEventSize() const { return GetEventSizeImpl(gtr_hits, gtr_clusters, hbd_hits, hbd_clusters, lg_hits, lg_clusters, tracks, hit_sets, track_sets) + sizeof(int); }
  std::vector<E16DST_DST1TriggerHit>&      GTRHits()     { return gtr_hits; }
  std::vector<E16DST_DST1TriggerCluster>&  GTRClusters() { return gtr_clusters; }
  std::vector<E16DST_DST1TriggerHit>&      HBDHits()     { return hbd_hits; }
  std::vector<E16DST_DST1TriggerCluster>&  HBDClusters() { return hbd_clusters; }
  std::vector<E16DST_DST1TriggerHit>&      LGHits()      { return lg_hits; }
  std::vector<E16DST_DST1TriggerCluster>&  LGClusters()  { return lg_clusters; }
  std::vector<E16DST_DST1TriggerHit>&      Tracks()      { return tracks; }
  std::vector<E16DST_DST1TriggerTrackSet>& HitSets()     { return hit_sets; }
  std::vector<E16DST_DST1TriggerTrackSet>& TrackSets()   { return track_sets; }
  int16_t NumTriggers() { return n_triggers; }
  bool IsTriggerHit(E16DST_DST1GTRHit& hit);
  bool IsTriggerHit(E16DST_DST1HBDHit& hit);
  bool IsTriggerHit(E16DST_DST1LGHit&  hit);
//  std:::vector<E16DST_DST1TriggerHit*> HitsIncludedTrackSet(bool is_track, int n);
  void Print();
  void Print(E16ANA_GeometryV2& geometry);
  int Write(std::fstream* fp);
  int Read(std::fstream* fp);
 private:
  bool SearchTriggerHit(std::vector<E16DST_DST1TriggerHit>& hits, int module_id, int channel_id);
  int16_t valid_flag;
  int16_t n_triggers;
  std::vector<E16DST_DST1TriggerHit>      gtr_hits;
  std::vector<E16DST_DST1TriggerCluster>  gtr_clusters;
  std::vector<E16DST_DST1TriggerHit>      hbd_hits;
  std::vector<E16DST_DST1TriggerCluster>  hbd_clusters;
  std::vector<E16DST_DST1TriggerHit>      lg_hits;
  std::vector<E16DST_DST1TriggerCluster>  lg_clusters;
  std::vector<E16DST_DST1TriggerHit>      tracks;
  std::vector<E16DST_DST1TriggerTrackSet> hit_sets;
  std::vector<E16DST_DST1TriggerTrackSet> track_sets;
};

class E16DST_DST1StraightTrack3D {
public:
  E16DST_DST1StraightTrack3D()
//      : wire_x(E16DST_DST1Constant::kInvalidValue)
//        initial_pos_at_wire_yz(E16DST_DST1Constant::kInvalidVector),
//        initial_mom(E16DST_DST1Constant::kInvalidVector),
//        original_cluster_indexes({E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue})
         {}
  ~E16DST_DST1StraightTrack3D() {}
  void Clear(){
//    wire_x                 = E16DST_DST1Constant::kInvalidValue;
//    initial_pos_at_wire_yz = E16DST_DST1Constant::kInvalidVector;
//    initial_mom            = E16DST_DST1Constant::kInvalidVector;
//    original_cluster_indexes.fill(E16DST_DST1Constant::kInvalidValue);
//    hbd_indexes.clear();
//    lg_indexes.clear();
    }
//
   void SetModuleID(int m){ module_id = m;}
   int16_t ModuleID(){return module_id;}
   void SetXTrackID(int16_t id){xtrk_id = id;}
   void SetYTrackID(int16_t id){ytrk_id = id;}
   int16_t XTrackID(){return xtrk_id;}
   int16_t YTrackID(){return ytrk_id;}
   void SetChi2X(float chi){chi2_x = chi;}
   float Chi2X(){return chi2_x;} 
   float Chi2Y(){return chi2_y;} 
   void SetChi2Y(float chi){chi2_y = chi;}
//   float TgtZ(){return tgt_z;} 

//   float Distance(){return distance;} 
//   float SSDResidualExSelf(){return residual_ssd_ex_self;} 
   E16DST_DST1SSDCluster* SSDCluster(){return xclusterssd ;} 
   E16DST_DST1GTRCluster* GTR100XCluster(){return xcluster100 ;} 
   E16DST_DST1GTRCluster* GTR200XCluster(){return xcluster200 ;} 
   E16DST_DST1GTRCluster* GTR300XCluster(){return xcluster300 ;} 
   E16DST_DST1GTRCluster* GTR100YCluster(){return ycluster100 ;} 
   E16DST_DST1GTRCluster* GTR200YCluster(){return ycluster200 ;} 
   E16DST_DST1GTRCluster* GTR300YCluster(){return ycluster300 ;}
    
//   TVector2 PtOnTrackGTR100(){return point_on_track_gtr100;}
//   TVector2 PtOnTrackGTR300(){return point_on_track_gtr300;}
//   TVector2 PtOnTrack3000mm(){return point_on_track_3000mm;}
//   void SetModuleID(float _mid){module_id = _mid;}
//   void SetChi2(float _chi2){chi2 = _chi2;}
   float TgtPosZ(){return tgt_pos_z;}
//   float TgtPosY(){return tgt_pos_y;}
   void SetTgtPosZ(float _tgtz){tgt_pos_z = _tgtz;}
//   void SetTgtPosY(float _tgty){tgt_pos_y = _tgty;}
  
   void SetFitAX(float fit){fit_a_x = fit;}
   void SetFitBX(float fit){fit_b_x = fit;}
   void SetFitAY(float fit){fit_a_y = fit;}
   void SetFitBY(float fit){fit_b_y = fit;} 
   float FitAX(){return fit_a_x;}
   float FitBX(){return fit_b_x;}
   float FitAY(){return fit_a_y;}
   float FitBY(){return fit_b_y;}
   void SetDistanceFromTgtXZ(float _distance){distance_fromtgt_xz = _distance;}
//   void SetDistanceFromTgtYR(float _distance){distance_fromtgt_yr = _distance;}
   void SetDistanceFromUpWireYR(float _distance){distance_fromupwire_yr = _distance;}
   void SetDistanceFromDownWireYR(float _distance){distance_fromdownwire_yr = _distance;}
   float DistanceFromTgtXZ(){return distance_fromtgt_xz;}
//   float DistanceFromTgtYR(){return distance_fromtgt_yr;}
   float DistanceFromUpWireYR(){return distance_fromupwire_yr;}
   float DistanceFromDownWireYR(){return distance_fromdownwire_yr;}
   void SetResidualSSD(float _residualssd){residualssd =_residualssd; }
   void SetFitResidual100X(float _residual){fit_residual100_x =_residual; }
   void SetFitResidual200X(float _residual){fit_residual200_x =_residual; }
   void SetFitResidual300X(float _residual){fit_residual300_x =_residual; }
   void SetFitResidual100Y(float _residual){fit_residual100_y =_residual; }
   void SetFitResidual200Y(float _residual){fit_residual200_y =_residual; }
   void SetFitResidual300Y(float _residual){fit_residual300_y =_residual; }
   float ResidualSSD(){return residualssd;}//
   float FitResidual100X(){return fit_residual100_x;}
   float FitResidual200X(){return fit_residual200_x;}
   float FitResidual300X(){return fit_residual300_x;}
   float FitResidual100Y(){return fit_residual100_y;}
   float FitResidual200Y(){return fit_residual200_y;}
   float FitResidual300Y(){return fit_residual300_y;}
//   void SetSSDResidualExSelf(float _res){residual_ssd_ex_self = _res;}
   void SetSSDCluster(E16DST_DST1SSDCluster *_cluster){xclusterssd = _cluster;}
   void SetGTR100XCluster(E16DST_DST1GTRCluster *_cluster){xcluster100 = _cluster;}
   void SetGTR200XCluster(E16DST_DST1GTRCluster *_cluster){xcluster200 = _cluster;}
   void SetGTR300XCluster(E16DST_DST1GTRCluster *_cluster){xcluster300 = _cluster;}
   void SetGTR100YCluster(E16DST_DST1GTRCluster *_cluster){ycluster100 = _cluster;}
   void SetGTR200YCluster(E16DST_DST1GTRCluster *_cluster){ycluster200 = _cluster;}
   void SetGTR300YCluster(E16DST_DST1GTRCluster *_cluster){ycluster300 = _cluster;}
   void SetFitPtOnGTR100(TVector3 tv){fitpt_ongtr100 = tv;}
   void SetFitPtOnGTR200(TVector3 tv){fitpt_ongtr200 = tv;}
   void SetFitPtOnGTR300(TVector3 tv){fitpt_ongtr300 = tv;}
   TVector3 FitPtOnGTR100(){return fitpt_ongtr100;}
   TVector3 FitPtOnGTR200(){return fitpt_ongtr200;}
   TVector3 FitPtOnGTR300(){return fitpt_ongtr300;}
//   void SetPtOnTrackGTR100(TVector2 _pt0){point_on_track_gtr100 = _pt0;}
//   void SetPtOnTrackGTR300(TVector2 _pt0){point_on_track_gtr300 = _pt0;}
//   void SetPtOnTrack3000mm(TVector2 _pt0){point_on_track_3000mm = _pt0;}
//   
private:
   int module_id;
   int16_t xtrk_id;
   int16_t ytrk_id;
//   int16_t idssdxhit; 
//   int16_t id100xhit; 
//   int16_t id200xhit; 
//   int16_t id300xhit; 
//   int16_t id100yhit; 
//   int16_t id200yhit; 
//   int16_t id300yhit; 
   float fit_a_x;
   float fit_b_x;
   float fit_a_y;
   float fit_b_y;
   float chi2_x;
   float chi2_y;
   float tgt_pos_z;//intercept with track
//   float tgt_pos_y;//in cases of wire, -40 or 40 is filled. *values up to tgt pos calib file
   
   float distance_fromtgt_xz;
   float distance_fromupwire_yr;//distance  from the upstream wire on YR plane to the track
   float distance_fromdownwire_yr;//distance  from the upstream wire on YR plane to the track
   float residualssd;//residual ssd, fit without itself
   float fit_residual100_x; //fit including itself
   float fit_residual200_x;
   float fit_residual300_x;
   float fit_residual100_y;
   float fit_residual200_y;
   float fit_residual300_y;
//   float tgt_z;
//   float distance;//from a nearest target
   E16DST_DST1SSDCluster *xclusterssd;
   E16DST_DST1GTRCluster *xcluster100;
   E16DST_DST1GTRCluster *xcluster200;
   E16DST_DST1GTRCluster *xcluster300;
   E16DST_DST1GTRCluster *ycluster100;
   E16DST_DST1GTRCluster *ycluster200;
   E16DST_DST1GTRCluster *ycluster300;
   TVector3 fitpt_ongtr100;
   TVector3 fitpt_ongtr200;
   TVector3 fitpt_ongtr300;
//   TVector2 point_on_track_gtr100;	
//   TVector2 point_on_track_gtr300;	
//   TVector2 point_on_track_3000mm;
//   float residual_ssd_ex_self;
//   float residual_100;	
//   float residual_200;	
//   float residual_300;
//   TVector2 pt0_on_track;	
//   TVector2 pt1_on_track;	
//   TVector2 pt2_on_track;	
};



class E16DST_DST1StraightTrack2D {
public:
  E16DST_DST1StraightTrack2D()
//      : wire_x(E16DST_DST1Constant::kInvalidValue)
//        initial_pos_at_wire_yz(E16DST_DST1Constant::kInvalidVector),
//        initial_mom(E16DST_DST1Constant::kInvalidVector),
//        original_cluster_indexes({E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue})
         {}
  ~E16DST_DST1StraightTrack2D() {}
  void Clear(){
//    wire_x                 = E16DST_DST1Constant::kInvalidValue;
//    initial_pos_at_wire_yz = E16DST_DST1Constant::kInvalidVector;
//    initial_mom            = E16DST_DST1Constant::kInvalidVector;
//    original_cluster_indexes.fill(E16DST_DST1Constant::kInvalidValue);
//    hbd_indexes.clear();
//    lg_indexes.clear();
    }
//
//
   int16_t ModuleID(){return module_id;}
   float Chi2(){return chi2;} 
   float TgtZ(){return tgt_z;} 
   float Distance(){return distance;} 
   float SSDResidualExSelf(){return residual_ssd_ex_self;} 
   E16DST_DST1SSDCluster* SSDCluster(){return xclusterssd ;} 
   E16DST_DST1GTRCluster* GTR100XCluster(){return xcluster100 ;} 
   E16DST_DST1GTRCluster* GTR200XCluster(){return xcluster200 ;} 
   E16DST_DST1GTRCluster* GTR300XCluster(){return xcluster300 ;} 
   TVector2 PtOnTrackGTR100(){return point_on_track_gtr100;}
   TVector2 PtOnTrackGTR300(){return point_on_track_gtr300;}
   TVector2 PtOnTrack3000mm(){return point_on_track_3000mm;}
   void SetModuleID(float _mid){module_id = _mid;}
   void SetChi2(float _chi2){chi2 = _chi2;}
   void SetTgtZ(float _tgtz){tgt_z = _tgtz;}
   void SetDistance(float _distance){distance = _distance;}
   void SetSSDResidualExSelf(float _res){residual_ssd_ex_self = _res;}
   void SetSSDCluster(E16DST_DST1SSDCluster *_cluster){xclusterssd = _cluster;}
   void SetGTR100XCluster(E16DST_DST1GTRCluster *_cluster){xcluster100 = _cluster;}
   void SetGTR200XCluster(E16DST_DST1GTRCluster *_cluster){xcluster200 = _cluster;}
   void SetGTR300XCluster(E16DST_DST1GTRCluster *_cluster){xcluster300 = _cluster;}
   void SetPtOnTrackGTR100(TVector2 _pt0){point_on_track_gtr100 = _pt0;}
   void SetPtOnTrackGTR300(TVector2 _pt0){point_on_track_gtr300 = _pt0;}
   void SetPtOnTrack3000mm(TVector2 _pt0){point_on_track_3000mm = _pt0;}
   
private:
   int16_t module_id;
//   int16_t id100hit; 
//   int16_t id200hit; 
//   int16_t id300hit; 
   float chi2;
   float tgt_z;
   float distance;//from a nearest target
   E16DST_DST1SSDCluster *xclusterssd;
   E16DST_DST1GTRCluster *xcluster100;
   E16DST_DST1GTRCluster *xcluster200;
   E16DST_DST1GTRCluster *xcluster300;
   TVector2 point_on_track_gtr100;	
   TVector2 point_on_track_gtr300;	
   TVector2 point_on_track_3000mm;
   float residual_ssd_ex_self;
   float residual_100;	
   float residual_200;	
   float residual_300;
   TVector2 pt0_on_track;	
   TVector2 pt1_on_track;	
   TVector2 pt2_on_track;	
};




class E16DST_DST1WireTrack {
 public:
  E16DST_DST1WireTrack()
      : wire_x(E16DST_DST1Constant::kInvalidValue),
        initial_pos_at_wire_yz(E16DST_DST1Constant::kInvalidVector),
        initial_mom(E16DST_DST1Constant::kInvalidVector),
        original_cluster_indexes({E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue}) {}
  ~E16DST_DST1WireTrack() {}
  void                  Clear() {
    wire_x                 = E16DST_DST1Constant::kInvalidValue;
    initial_pos_at_wire_yz = E16DST_DST1Constant::kInvalidVector;
    initial_mom            = E16DST_DST1Constant::kInvalidVector;
    original_cluster_indexes.fill(E16DST_DST1Constant::kInvalidValue);
    hbd_indexes.clear();
    lg_indexes.clear();
  }
  void                  SetWireX(int _wire_x) { wire_x = _wire_x; }
  void                  SetInitialPosAtWireYZ(TVector3 _initial_pos) { initial_pos_at_wire_yz = _initial_pos; }
  void                  SetInitialMom(TVector3 _initial_mom) { initial_mom = _initial_mom; }
  void                  SetOriginalClusterIndex(int n, int16_t index) { original_cluster_indexes[n] = index; }
  int                   WireX() { return wire_x; }
  TVector3              InitialPosAtWireYZ() { return initial_pos_at_wire_yz; }
  TVector3              InitialMom() { return initial_mom; }
  int16_t               OriginalClusterIndex(int n) { return original_cluster_indexes[n]; }
  int                   NumHBDIndexes() { return hbd_indexes.size(); }
  int16_t               HBDIndex(int n) { return hbd_indexes[n]; }
  std::vector<int16_t>& HBDIndexes() { return hbd_indexes; }
  int                   NumLGIndexes() { return lg_indexes.size(); }
  int16_t               LGIndex(int n) { return lg_indexes[n]; }
  std::vector<int16_t>& LGIndexes() { return lg_indexes; }
 private:
  int      wire_x;
  TVector3 initial_pos_at_wire_yz;
  TVector3 initial_mom;
  std::array<int16_t, 4> original_cluster_indexes;
  std::vector<int16_t> hbd_indexes;
  std::vector<int16_t> lg_indexes;
};
//
//class E16DST_DST1Track {
// public:
//  E16DST_DST1Track()
//      : initial_pos_at_target_plane({E16DST_DST1Constant::kInvalidVector, E16DST_DST1Constant::kInvalidVector, E16DST_DST1Constant::kInvalidVector}),
//        initial_mom({E16DST_DST1Constant::kInvalidVector, E16DST_DST1Constant::kInvalidVector, E16DST_DST1Constant::kInvalidVector}),
//        tan_theta({E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue
//                   E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue}),
//        original_cluster_indexes({E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue}) {}
//  ~E16DST_DST1Track() {}
//  void Clear() {
//    for (auto& pos : initial_pos_at_target_plane) {
//      pos = E16DST_DST1Constant::kInvalidVector;
//    }
//    for (auto& mom : initial_mom) {
//      mom = E16DST_DST1Constant::kInvalidVector;
//    }
//    for (auto& angle : tan_theta) {
//      angle = E16DST_DST1Constant::kInvalidValue;
//    }
//    for (auto& index : original_cluster_indexes) {
//      index = E16DST_DST1Constant::kInvalidValue;
//    }
//    hbd_indexes.clear();
//    lg_indexes.clear();
//  }
//  void                  SetInitialPosAtTargetPlane(int n, TVector3 _pos) { initial_pos_at_target_plane[n] = _pos; }
//  void                  SetInitialMom(int n, TVector3 _mom) { initial_mom[n] = _mom; }
//  void                  SetTanTheta(int n, float angle) { tan_theta[n] = angle; }
//  void                  SetOriginalClusterINdex(int n, int _index) { original_cluster_indexes[n] = _index; }
//  TVector3              InitialPosAtTargetPlane(int n) { return initial_pos_at_target_plane[n]; }
//  TVector3              InitialMom(int n) { return initial_mom[n]; }
//  float                 TanTheta(int n) { return tan_theta[n]; }
//  int                   OriginalClusterIndex(int n) { return original_cluster_indexes[n]; }
//  int                   NumHBDIndexes() { return hbd_indexes.size(); }
//  int16_t               HBDIndex(int n) { return hbd_indexes[n]; }
//  std::vector<int16_t>& HBDIndexes() { return hbd_indexes; }
//  int                   NumLGIndexes() { return lg_indexes.size(); }
//  int16_t               LGIndex(int n) { return lg_indexes[n]; }
//  std::vector<int16_t>& LGIndexes() { return lg_indexes; }
// private:
//  std::array<TVector3, 3> initial_pos_at_target_plane; // z = -20, 0, 20
//  std::array<TVector3, 3> initial_mom;
//  std::array<float,    6> tan_theta;
//  std::array<int16_t,  4> original_cluster_indexes;
//  std::vector<int16_t>    hbd_indexes;
//  std::vector<int16_t>    lg_indexes;
//};

class E16DST_DST1Track {
 public:
  E16DST_DST1Track()
      : original_cluster_ptrs({nullptr, nullptr, nullptr, nullptr}) {}
  ~E16DST_DST1Track() {}
  void Clear() {
    initial_pos_at_target_plane.fill(E16DST_DST1Constant::kInvalidVector);
    initial_mom_at_target_plane.fill(E16DST_DST1Constant::kInvalidVector);
    original_cluster_ptrs.fill(nullptr);
    hbd_hit_ptrs.clear();
    hbd_cluster_ptrs.clear();
    lg_hit_ptrs.clear();
    lg_cluster_ptrs.clear();
  }
  void SetInitialPosAtTargetPlane(int n, const TVector3& _pos) { initial_pos_at_target_plane[n] = _pos; }
  void SetInitialMomAtTargetPlane(int n, const TVector3& _mom) { initial_mom_at_target_plane[n] = _mom; }
  void SetHitPos(int n, const TVector3& _pos) { hit_pos[n] = _pos; }
  void SetHitMom(int n, const TVector3& _mom) { hit_mom[n] = _mom; }
//  void SetTanTheta(int n, float angle) { tan_theta[n] = angle; }
  void SetOriginalClusterPtr(int n, E16DST_DST1Cluster* _ptr) { original_cluster_ptrs[n] = _ptr; }
  void ClearHBDHitPtr() { hbd_hit_ptrs.clear(); }
  void ClearHBDClusterPtr() { hbd_cluster_ptrs.clear(); }
  void ClearLGHitPtr() { lg_hit_ptrs.clear(); }
  void ClearLGClusterPtr() { lg_cluster_ptrs.clear(); }
  void EmplaceBackHBDHitPtr(E16DST_DST1HBDHit* _hit) { hbd_hit_ptrs.emplace_back(_hit); }
  void EmplaceBackHBDClusterPtr(E16DST_DST1HBDCluster* _cluster) { hbd_cluster_ptrs.emplace_back(_cluster); }
  void EmplaceBackLGHitPtr(E16DST_DST1LGHit* _hit) { lg_hit_ptrs.emplace_back(_hit); }
  void EmplaceBackLGClusterPtr(E16DST_DST1LGCluster* _cluster) { lg_cluster_ptrs.emplace_back(_cluster); }
  void SetHBDHitPtrs(const std::vector<E16DST_DST1HBDHit*>& _hits) {
    hbd_hit_ptrs.clear();
    std::copy(_hits.begin(), _hits.end(), std::back_inserter(hbd_hit_ptrs));
  }
  void SetHBDClusterPtrs(const std::vector<E16DST_DST1HBDCluster*>& _clusters) {
    hbd_cluster_ptrs.clear();
    std::copy(_clusters.begin(), _clusters.end(), std::back_inserter(hbd_cluster_ptrs));
  }
  void SetLGHitPtrs(const std::vector<E16DST_DST1LGHit*>& _hits) {
    lg_hit_ptrs.clear();
    std::copy(_hits.begin(), _hits.end(), std::back_inserter(lg_hit_ptrs));
  }
  void SetLGClusterPtrs(const std::vector<E16DST_DST1LGCluster*>& _clusters) {
    lg_cluster_ptrs.clear();
    std::copy(_clusters.begin(), _clusters.end(), std::back_inserter(lg_cluster_ptrs));
  }
  TVector3                                   InitialPosAtTargetPlane(int n) { return initial_pos_at_target_plane[n]; }
  TVector3                                   InitialMomAtTargetPlane(int n) { return initial_mom_at_target_plane[n]; }
  TVector3                                   HitPos(int n) { return hit_pos[n]; }
  TVector3                                   HitMom(int n) { return hit_mom[n]; }
  float                                      TanTheta(int n) { return hit_mom[n].X() / hit_mom[n].Z(); }
  E16DST_DST1Cluster*                        OriginalClusterPtr(int n) { return original_cluster_ptrs[n]; }
  int                                        NumHBDHitPtrs() { return hbd_hit_ptrs.size(); }
  E16DST_DST1HBDHit*                         HBDHitPtr(int n) { return hbd_hit_ptrs[n]; }
  const std::vector<E16DST_DST1HBDHit*>&     HBDHitPtrs() const { return hbd_hit_ptrs; }
  int                                        NumHBDClusterPtrs() { return hbd_cluster_ptrs.size(); }
  E16DST_DST1HBDCluster*                     HBDClusterPtr(int n) { return hbd_cluster_ptrs[n]; }
  const std::vector<E16DST_DST1HBDCluster*>& HBDClusterPtrs() const { return hbd_cluster_ptrs; }
  int                                        NumLGHitPtrs() { return lg_hit_ptrs.size(); }
  E16DST_DST1LGHit*                          LGHitPtr(int n) { return lg_hit_ptrs[n]; }
  const std::vector<E16DST_DST1LGHit*>&      LGHitPtrs() const { return lg_hit_ptrs; }
  int                                        NumLGClusterPtrs() { return lg_cluster_ptrs.size(); }
  E16DST_DST1LGCluster*                      LGClusterPtr(int n) { return lg_cluster_ptrs[n]; }
  const std::vector<E16DST_DST1LGCluster*>&  LGClusterPtrs() const { return lg_cluster_ptrs; }
  void Print() {
    for (int i = 0; i < E16ANA_TrackConstant::kNumTargets; ++i) {
      auto& pos = initial_pos_at_target_plane[i];
      auto& mom = initial_mom_at_target_plane[i];
      E16INFO("Target: %d, Position: (%lf, %lf, %lf), Momentum: (%lf, %lf, %lf)", i, pos(0), pos(1), pos(2), mom(0), mom(1), mom(2));
    }
    for (int i = 0; i< E16ANA_TrackConstant::kNumDetectorLayers; ++i) {
      auto& pos = hit_pos[i];
      auto& mom = hit_mom[i];
      E16INFO("Detector: %s, Position: (%lf, %lf, %lf), Momentum: (%lf, %lf, %lf)", E16ANA_TrackConstant::kDetectorName[i].c_str(), pos(0), pos(1), pos(2), mom(0), mom(1), mom(2));
    }
  }
 private:
  std::array<TVector3, E16ANA_TrackConstant::kNumTargets> initial_pos_at_target_plane;
  std::array<TVector3, E16ANA_TrackConstant::kNumTargets> initial_mom_at_target_plane;
  std::array<TVector3, E16ANA_TrackConstant::kNumDetectorLayers> hit_pos;
  std::array<TVector3, E16ANA_TrackConstant::kNumDetectorLayers> hit_mom;
//  std::array<float, E16DST_DST1Constant::kNumDetectorLayers> hit_tan_theta;
  std::array<E16DST_DST1Cluster*, E16ANA_TrackConstant::kNumClusters> original_cluster_ptrs;
  std::vector<E16DST_DST1HBDHit*> hbd_hit_ptrs;
  std::vector<E16DST_DST1HBDCluster*> hbd_cluster_ptrs;
  std::vector<E16DST_DST1LGHit*> lg_hit_ptrs;
  std::vector<E16DST_DST1LGCluster*> lg_cluster_ptrs;
};

class E16DST_DST1Tracks {
 public:
  E16DST_DST1Tracks() {}
  ~E16DST_DST1Tracks() {}
  int NumTracks() { return tracks.size(); }
  E16DST_DST1Track& Track(int n) { return tracks[n]; }
  std::vector<E16DST_DST1Track>& Tracks() { return tracks; }
  void Clear() { tracks.clear(); }
  int Write(std::fstream* fp);
  int Read(std::fstream* fp);
  void Print() {
    E16INFO("Number of Tracks: %d", tracks.size());
    for (int i = 0; i < tracks.size(); ++i) {
      E16INFO("Track: %d", i);
      tracks[i].Print();
    }
    return;
  }
 private:
  std::vector<E16DST_DST1Track> tracks;
};

class E16DST_DST1DetectorHeader {
 public:
  E16DST_DST1DetectorHeader(int16_t _detector_version, int16_t _detector_id, int16_t _hit_version, int16_t _cluster_version)
      : valid_flag(E16DST_DST1Constant::kInvalidValue),
        detector_version(_detector_version),          detector_id(_detector_id),
        hit_version(_hit_version),                    cluster_version(_cluster_version),
        num_hits(E16DST_DST1Constant::kInvalidValue), num_clusters(E16DST_DST1Constant::kInvalidValue),
        reserve() {}
  ~E16DST_DST1DetectorHeader() {}
  void        ClearHeader() {
    valid_flag      = E16DST_DST1Constant::kInvalidValue;
//    detector_id     = E16DST_DST1Constant::kInvalidValue;
//    hit_version     = E16DST_DST1Constant::kInvalidValue;
//    cluster_version = E16DST_DST1Constant::kInvalidValue;
    num_hits        = E16DST_DST1Constant::kInvalidValue;
    num_clusters    = E16DST_DST1Constant::kInvalidValue;
    reserve.fill(E16DST_DST1Constant::kInvalidValue);
  }
  void        SetValidFlag(int _valid_flag) { valid_flag = _valid_flag; }
  void        SetDetectorId(int16_t _detector_id) { detector_id = _detector_id; }
  void        SetHitVersion(int16_t _hit_version) { hit_version = _hit_version; }
  void        SetClusterVersion(int16_t _cluster_version) { cluster_version = _cluster_version; }
  int         ValidFlag()       { return valid_flag; }
  int16_t     DetectorVersion() { return detector_version; }
  int16_t     DetectorId()      { return detector_id; }
  int16_t     HitVersion()      { return hit_version; }
  int16_t     ClusterVersion()  { return cluster_version; }
  virtual int Read(std::fstream* fp);
  void        PrintHeader() {
    std::cout << "detector version: " << detector_version << ", detector ID: " << detector_id
              << ", hit version: " << hit_version << ", cluster version: " << cluster_version << std::endl;
  }
 protected:
  int                                            valid_flag;
  const int16_t                                  detector_version;
  int16_t                                        detector_id;
  int16_t                                        hit_version;
  int16_t                                        cluster_version;
  int16_t                                        num_hits;
  int16_t                                        num_clusters;
  std::array<int, E16DST_DST1Constant::kReserve> reserve;
};

template <class T, class U>
class E16DST_DST1Detector : public E16DST_DST1DetectorHeader {
 public:
  using value_type0 = T;
  using value_type1 = U;
//  E16DST_DST1Detector() : E16DST_DST1DetectorHeader(int16_t _detector_version, int16_t _detector_id, int16_t _hit_version, int16_t _cluster_version) { Clear(); }
  using E16DST_DST1DetectorHeader::E16DST_DST1DetectorHeader;
  ~E16DST_DST1Detector() {}
  void Clear() {
    ClearHeader();
    hits.clear();
    clusters.clear();
    hit_ptrs.clear();
    cluster_ptrs.clear();
  }
  void             ResizeHit(int n)                   { hits.resize(n); }
  void             ReserveHit(int n)                  { hits.reserve(n); }
  void             PushBackHit()                      { hits.push_back(T()); }
  void             PushBackHit(const T& hit)          { hits.push_back(hit); }
  T&               BackHit()                          { return hits.back(); }
  T&               Hit(int i)                         { return hits[i]; }
  std::vector<T>&  Hits()                             { return hits; }
  int              NumHits()                          { return hits.size(); }
  void             ResizeCluster(int n)               { clusters.resize(n); }
  void             ReserveCluster(int n)              { clusters.reserve(n); }
  void             PushBackCluster()                  { clusters.push_back(T()); }
  void             PushBackCluster(const U& cluster)  { clusters.push_back(cluster); }
  U&               BackCluster()                      { return clusters.back(); }
  U&               Cluster(int i)                     { return clusters[i]; }
  std::vector<U>&  Clusters()                         { return clusters; }
  int              NumClusters()                      { return clusters.size(); }
  void             AddHitAndClusterIds() {
    int n_hits = hits.size();
    for (int i = 0; i < n_hits; ++i) {
      hits[i].SetHitId(i);
    }
    int n_clusters = clusters.size();
    for (int i = 0; i < n_clusters; ++i) {
      clusters[i].SetClusterId(i);
    }
    return;
  }
  void             UpdateHitPtrs();
  void             UpdateClusterPtrs();
  void             UpdatePtrs() {
    UpdateHitPtrs();
    UpdateClusterPtrs();
  }
  int              NumHitPtrs(int module_id, int layer_id, int type) {
    auto id_sum = IdSum(module_id, layer_id, type);
    if (hit_ptrs.count(id_sum) == 1) {
      return hit_ptrs[id_sum].size();
    } else {
      return 0;
    }
  }
  int              NumClusterPtrs(int module_id, int layer_id, int type) {
    auto id_sum = IdSum(module_id, layer_id, type);
    if (cluster_ptrs.count(id_sum) == 1) {
      return cluster_ptrs[id_sum].size();
    } else {
      return 0;
    }
  }
  std::vector<T*>& HitPtrs(int module_id, int layer_id, int type) {
    auto id_sum = IdSum(module_id, layer_id, type);
    return hit_ptrs[id_sum];
  }
  std::vector<U*>& ClusterPtrs(int module_id, int layer_id, int type) {
    auto id_sum = IdSum(module_id, layer_id, type);
    return cluster_ptrs[id_sum];
  }
  std::vector<T*>  ClusterMembers(int cluster_id);
  T&               ClusterMember(int cluster_id, int hit_id);
  int              Write(std::fstream* fp);
  int              Read(std::fstream* fp) override;
  int              GetSize();
  void             Print();
 private:
  static int IdSum(int module_id, int layer_id, int type) { return 10000 * module_id + 100 * layer_id + type; }
  std::vector<T>                           hits;
  std::vector<U>                           clusters;
  std::unordered_map<int, std::vector<T*>> hit_ptrs;
  std::unordered_map<int, std::vector<U*>> cluster_ptrs;
};

//class E16DST_DST1PhysicsEvent : public E16DST_DST0Event {
// public:
//  E16DST_DST1PhysicsEvent() {}
//  ~E16DST_DST1PhysicsEvent() {}
//  int GetEventSize() const override {}
//  int Write(E16DST_File* fp) override {};
//  int Read(E16DST_File* fp) override {};
//  void Clear() override {};
//  bool Append(E16DST_DST0Event* _another_event) override {};
//  uint16_t EventType() { return E16DST_DST0EventType::Physics; }
//  E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster>& SSD() { return ssd; }
//  E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster>& GTR() { return gtr; }
//  E16DST_DST1Detector<E16DST_DST1HBDHit, E16DST_DST1HBDCluster>& HBD() { return hbd; }
//  E16DST_DST1Detector<E16DST_DST1LGHit,  E16DST_DST1LGCluster>&  LG()  { return lg; }
//  E16DST_DST0Detector<E16DST_DST1SSDHit>&     SSDHits()     { return ssd_hits; }
//  E16DST_DST0Detector<E16DST_DST1SSDCluster>& SSDClusters() { return ssd_clusters; }
//  E16DST_DST0Detector<E16DST_DST1GTRHit>&     GTRHits()     { return gtr_hits; }
//  E16DST_DST0Detector<E16DST_DST1GTRCluster>& GTRClusters() { return gtr_clusters; }
//  E16DST_DST0Detector<E16DST_DST1HBDHit>&     HBDHits()     { return hbd_hits; }
//  E16DST_DST0Detector<E16DST_DST1HBDCluster>& HBDClusters() { return hbd_clusters; }
//  E16DST_DST0Detector<E16DST_DST1LGHit>&      LGHits()      { return lg_hits; }
//  E16DST_DST0Detector<E16DST_DST1LGCluster>&  LGClusters()  { return lg_clusters; }
//  E16DST_DST1Trigger&                         Trigger()     { return trigger; }
// private:
//  E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> ssd;
//  E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> gtr;
//  E16DST_DST1Detector<E16DST_DST1HBDHit, E16DST_DST1HBDCluster> hbd;
//  E16DST_DST1Detector<E16DST_DST1LGHit,  E16DST_DST1LGCluster>  lg;
//  E16DST_DST0Detector<E16DST_DST1SSDHit>     ssd_hits;
//  E16DST_DST0Detector<E16DST_DST1SSDCluster> ssd_clusters;
//  E16DST_DST0Detector<E16DST_DST1GTRHit>     gtr_hits;
//  E16DST_DST0Detector<E16DST_DST1GTRCluster> gtr_clusters;
//  E16DST_DST0Detector<E16DST_DST1HBDHit>     hbd_hits;
//  E16DST_DST0Detector<E16DST_DST1HBDCluster> hbd_clusters;
//  E16DST_DST0Detector<E16DST_DST1LGHit>      lg_hits;
//  E16DST_DST0Detector<E16DST_DST1LGCluster>  lg_clusters;
//  E16DST_DST1Trigger                         trigger;
//};

class E16DST_DST1PhysicsHeader {
 public:
  E16DST_DST1PhysicsHeader() : version(0), reserve() {}
  ~E16DST_DST1PhysicsHeader() {}
 private:
  const int version;
  std::array<int, E16DST_DST1Constant::kReserve> reserve;
};

class E16DST_DST1PhysicsRecord : public E16DST_DST1PhysicsHeader {
 public:
  E16DST_DST1PhysicsRecord()
      : ssd(E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster>(0, E16DST_DST1Constant::kSSD, 0, 0)),
        gtr(E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster>(0, E16DST_DST1Constant::kGTR, 0, 0)),
        hbd(E16DST_DST1Detector<E16DST_DST1HBDHit, E16DST_DST1HBDCluster>(0, E16DST_DST1Constant::kHBD, 0, 0)),
        lg(E16DST_DST1Detector<E16DST_DST1LGHit, E16DST_DST1LGCluster>(0, E16DST_DST1Constant::kLG, 0, 0)) {
    Clear();
  }
  ~E16DST_DST1PhysicsRecord() {}
  void Clear() { 
    ssd.Clear();
    gtr.Clear();
    hbd.Clear();
    lg.Clear();
//    trigger.Clear();
    tracks.Clear();
  }
  E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster>& SSD()     { return ssd; }
  E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster>& GTR()     { return gtr; }
  E16DST_DST1Detector<E16DST_DST1HBDHit, E16DST_DST1HBDCluster>& HBD()     { return hbd; }
  E16DST_DST1Detector<E16DST_DST1LGHit,  E16DST_DST1LGCluster>&  LG()      { return lg; }
//  E16DST_DST1Trigger&                                            Trigger() { return trigger; }
  E16DST_DST1Tracks&                                             Tracks()  { return tracks; }
  int Write(std::fstream* fp);
  int Read(std::fstream* fp);
 private:
  E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> ssd;
  E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> gtr;
  E16DST_DST1Detector<E16DST_DST1HBDHit, E16DST_DST1HBDCluster> hbd;
  E16DST_DST1Detector<E16DST_DST1LGHit,  E16DST_DST1LGCluster>  lg;
//  E16DST_DST1Trigger                                            trigger;
  E16DST_DST1Tracks                                             tracks;
};

class E16DST_DST1RecordHeader {
 public:
  E16DST_DST1RecordHeader()
      : run_number(E16DST_DST1Constant::kInvalidValue), 
        spill_id(E16DST_DST1Constant::kInvalidValue), 
        event_id(E16DST_DST1Constant::kInvalidValue), 
        timestamp_in_spill(E16DST_DST1Constant::kInvalidValue), 
        type(E16DST_DST1Constant::kInvalidValue), 
        version(E16DST_DST1Constant::kInvalidValue), 
        size(E16DST_DST1Constant::kInvalidValue),
        reserve() {}
  ~E16DST_DST1RecordHeader() {}
  void   Clear() {
    run_number         = E16DST_DST1Constant::kInvalidValue;
    spill_id           = E16DST_DST1Constant::kInvalidValue;
    event_id           = E16DST_DST1Constant::kInvalidValue;
    timestamp_in_spill = E16DST_DST1Constant::kInvalidValue;
    type               = E16DST_DST1Constant::kInvalidValue;
    version            = E16DST_DST1Constant::kInvalidValue;
    size               = E16DST_DST1Constant::kInvalidValue;
  }
  void    SetRunNumber(int _run_number) { run_number = _run_number; }
  void    SetSpillId(int _spill_id) { spill_id = _spill_id; }
  void    SetEventId(int _event_id) { event_id = _event_id; }
  void    SetTimestampInSpill(int _timestamp_in_spill) { timestamp_in_spill = _timestamp_in_spill; }
  void    SetType(int _type)       { type = _type; }
  void    SetVersion(int _version) { version= _version; }
  int     RunNumber() { return run_number; }
  int     EventId() { return event_id; }
  int     SpillId() { return spill_id; }
  int     TimestampInSpill() { return timestamp_in_spill; }
  int16_t Type()                   { return type; }
  int16_t Version()                { return version; }
  int     Size()                   { return size; }
  int     Write(std::fstream* fp);
  int     Read(std::fstream* fp);
 private:
  int     run_number;
  int     spill_id;
  int     event_id;
  int     timestamp_in_spill;
  int16_t type;
  int16_t version;
  int     size;
  std::array<int, E16DST_DST1Constant::kReserve> reserve;
};


//int E16DST_DST1SSDFactory(E16DST_DST0Detector<E16DST_DST0SSDHit>& hits0, std::vector<E16DST_DST1SSDHit>* hits1, std::vector<E16DST_DST1SSDCluster>* clusters1);
////class E16DST_DST1GTRAnalyzerMaker;
//int E16DST_DST1GTRHitAndClusterFactory(E16DST_DST0Detector<E16DST_DST0GTRHit>& hits0, E16DST_DST0Detector<E16DST_DST1GTRHit>* hits1, E16DST_DST0Detector<E16DST_DST1GTRCluster>* clusters1, E16ANA_GTRcalibPedestal &gtrped);
//int E16DST_DST1HBDFactory(E16DST_DST0Detector<E16DST_DST0HBDHit>& hits0, E16DST_DST0Detector<E16DST_DST1HBDHit>* hits1, E16DST_DST0Detector<E16DST_DST1HBDCluster>* clusters1);
////int E16DST_DST1LGFactory(E16DST_DST0Detector<E16DST_DST0LGHit>& hits0,   E16DST_DST0Detector<E16DST_DST1LGHit>* hits1,  E16DST_DST0Detector<E16DST_DST1LGCluster>* clusters1);
//int E16DST_DST1HBDHitAndClusterFactory(E16DST_DST0Detector<E16DST_DST0HBDHit>& hits0, E16ANA_HBDCalibration *hbd_calib, E16ANA_HBDCut *hbd_cut, E16ANA_WaveformFitter *wf1d_fitter, E16DST_DST0Detector<E16DST_DST1HBDHit>* hits1, E16DST_DST0Detector<E16DST_DST1HBDCluster>* clusters1);
////int E16DST_DST1LGFactory(E16DST_DST0Detector<E16DST_DST0LGHit>& hits0,   E16DST_DST0Detector<E16DST_DST1LGHit>* hits1,  E16DST_DST0Detector<E16DST_DST1LGCluster>* clusters1, int hitoption); // 0: w/o fit, 1: w/ fit
////int E16DST_DST1SSDFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0SSDHit>& hits0, E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster>* gtr1);
//int E16DST_DST1GTRFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0GTRHit>& hits0, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster>* gtr1, E16ANA_GTRcalibPedestal& gtrped);
////int E16DST_DST1HBDFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0HBDHit>& hits0, E16DST_DST1Detector<E16DST_DST1HBDHit, E16DST_DST1HBDCluster>* gtr1);
////int E16DST_DST1LGFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0LGHit>& hits0,   E16DST_DST1Detector<E16DST_DST1LGHit,  E16DST_DST1LGCluster>*  lg1);
//int E16DST_DST1TriggerFactory(E16ANA_TriggerCalibParam& trigger_param, E16DST_DST0Detector<E16DST_DST0TriggerHit>& gtr_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& hbd_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& lg_hits, E16DST_DST0UT3& ut3, E16DST_DST1Trigger* trigger);
////int E16DST_DST1WireTrackFactory(E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> &ssd_detector, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> &gtr_detector, E16ANA_GeometryV2 *geom);
//int E16DST_DST1WireTrackFactory2D(E16DST_DST0PhysicsEvent *event0, E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1,std::vector<E16DST_DST1StraightTrack2D> &st_tracks,  E16ANA_GTRcalibPedestal& gtrped, E16ANA_GeometryV2 *geom);
////int E16DST_DST1WireTrackFactory(E16DST_DST1PhysicsRecord* record);
////int E16DST_DST1TrackFactory(E16ANA_GeometryV2& geometry, E16ANA_MagneticFieldMap& bfield_map, E16ANA_MultiTrack* fitter, E16DST_DST1PhysicsRecord* record);
//
//////int E16DST_DST1SSDFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0SSDHit>& hits0, E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster>* gtr1);
////int E16DST_DST1SSDFactory_dummy(E16DST_DST0Detector<E16DST_DST0SSDHit>& hits0, E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster>* ssd);
////int E16DST_DST1GTRFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0GTRHit>& hits0, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster>* gtr1, E16ANA_GTRcalibPedestal& gtrped);
//////int E16DST_DST1HBDFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0HBDHit>& hits0, E16ANA_HBDCalibration* hbd_calib, E16DST_DST1Detector<E16DST_DST1HBDHit, E16DST_DST1HBDCluster>* hbd1);
////int E16DST_DST1LGFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0LGHit>& hits0,   E16DST_DST1Detector<E16DST_DST1LGHit,  E16DST_DST1LGCluster>*  lg1);


template <class T, class U>
void E16DST_DST1Detector<T, U>::UpdateHitPtrs() {
  if (detector_id == E16DST_DST1Constant::kInvalidValue) {
    return;
  }
  hit_ptrs.clear();
  for (auto& hit : hits) {
    auto module_id = hit.ModuleId();
    auto layer_id  = hit.LayerId();
    auto type      = hit.Type();
//    int  layer_id  = 0;
//    int  type      = 0;
//    if (typeid(T) == typeid(E16DST_DST1GTRHit)) {
//      layer_id = hit.LayerId();
//      type     = hit.Type();
//    }
    auto id = IdSum(module_id, layer_id, type);
    if (hit_ptrs.count(id) == 0) {
      std::vector hit_vector = {&hit};
      hit_ptrs.emplace(id, hit_vector);
    } else {
      hit_ptrs[id].emplace_back(&hit);
    }
  }
}

template <class T, class U>
void E16DST_DST1Detector<T, U>::UpdateClusterPtrs() {
  if (detector_id == E16DST_DST1Constant::kInvalidValue) {
    return;
  }
  cluster_ptrs.clear();
  for (auto& cluster : clusters) {
    auto module_id = cluster.ModuleId();
    auto layer_id  = cluster.LayerId();
    auto type      = cluster.Type();
//    int layer_id  = 0;
//    int type      = 0;
//    if (typeid(U) == typeid(E16DST_DST1GTRCluster)) {
//      layer_id = cluster.LayerId();
//      type     = cluster.Type();
//    }
    auto id = IdSum(module_id, layer_id, type);
    if (cluster_ptrs.count(id) == 0) {
      std::vector cluster_vector = {&cluster};
      cluster_ptrs.emplace(id, cluster_vector);
    } else {
      cluster_ptrs[id].emplace_back(&cluster);
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
int E16DST_DST1Detector<T, U>::Write(std::fstream* fp) {
  int write_size = sizeof(E16DST_DST1DetectorHeader);
  num_hits     = hits.size();
  num_clusters = clusters.size();
  fp->write(reinterpret_cast<char*>(this), write_size);
  int hits_length = sizeof(T) * NumHits();
  write_size += hits_length;
  fp->write(reinterpret_cast<char*>(hits.data()), hits_length);
  std::vector<int16_t> cluster_sizes(NumClusters());
  if (NumClusters() % 2 == 1) {
    cluster_sizes.emplace_back(E16DST_DST1Constant::kInvalidValue);
  }
  int cluster_total_size = 0;
  auto cluster_base_size = sizeof(U);
  for (int i= 0; i < NumClusters(); ++i) {
    if (clusters[i].HitOrders().size() % 2 == 1) {
      clusters[i].HitOrders().emplace_back(E16DST_DST1Constant::kInvalidValue);
    }
    cluster_sizes[i] = cluster_base_size + sizeof(int16_t) * clusters[i].NumHits();
    cluster_total_size += cluster_sizes[i];
  }
  if (NumClusters() != 0) {
    int cluster_sizes_length = sizeof(int16_t) * cluster_sizes.size();
    write_size += cluster_sizes_length;
    fp->write(reinterpret_cast<char*>(cluster_sizes.data()), cluster_sizes_length);
//std::cout << "cluster sizes length: " << cluster_sizes_length << std::endl;
  }
  write_size += cluster_total_size;
  fp->write(reinterpret_cast<char*>(clusters.data()), cluster_total_size);
std::cout << "write size: " << write_size << std::endl;
  return write_size;
}

template <class T, class U>
int E16DST_DST1Detector<T, U>::Read(std::fstream* fp) {
  int read_size = sizeof(E16DST_DST1DetectorHeader);
  fp->read(reinterpret_cast<char*>(this), read_size);
  hits.resize(num_hits);
  int hits_size = sizeof(T) * num_hits;
  read_size += hits_size;
  fp->read(reinterpret_cast<char*>(hits.data()), hits_size);
std::cout << "read hits" << std::endl;
  int n_file_clusters = num_clusters;
  if (n_file_clusters % 2 == 1) {
    ++n_file_clusters;
  }
  std::vector<int16_t> cluster_sizes(n_file_clusters);
  int cluster_sizes_length = sizeof(int16_t) * n_file_clusters;
  if (n_file_clusters != 0) {
    read_size += cluster_sizes_length;
    fp->read(reinterpret_cast<char*>(cluster_sizes.data()), cluster_sizes_length);
std::cout << "cluster sizes length: " << cluster_sizes_length << std::endl;
  }
  clusters.resize(num_clusters);
  auto cluster_data_size = sizeof(U);
  for (int i = 0; i < num_clusters; ++i) {
//    int num_hits_in_cluster = (cluster_sizes[i] - cluster_data_size) / sizeof(int16_t);
//    clusters[i].HitOrders().resize(num_hits_in_cluster);
    read_size += cluster_sizes[i];
    fp->read(reinterpret_cast<char*>(&clusters[i]), cluster_sizes[i]);
std::cout << "read cluster" << i << ", size: " << cluster_sizes[i] << std::endl;
    if (clusters[i].NumHits() != 0) {
std::cout << "number of hits in cluster: " << clusters[i].NumHits() << std::endl;
for (auto& order : clusters[i].HitOrders()) {
  std::cout << "  " << order << std::endl;
}
      if (clusters[i].HitOrder(clusters[i].NumHits() - 1) == E16DST_DST1Constant::kInvalidValue) {
        clusters[i].HitOrders().pop_back();
      }
    }
  }
std::cout << "read size: " << read_size << std::endl;
  return read_size;
}

template <class T, class U>
int E16DST_DST1Detector<T, U>::GetSize() {
  int size = sizeof(uint32_t);
  for (const auto& hit: hits) {
    size += sizeof(T) * hit.size();
  }
  for (auto& cluster : clusters) {
    size += cluster.GetSize();
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

#endif
