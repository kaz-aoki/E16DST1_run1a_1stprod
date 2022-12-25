#ifndef E16ANA_TRACKCANDIDATE_HH
#define E16ANA_TRACKCANDIDATE_HH

#include <array>
#include <iostream>
#include <vector>

#include "TVector3.h"
#include "E16ANA_TrackConstant.hh"
#include "E16ANA_TrackParameter.hh"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_MagneticFieldMap.hh"
#include "E16ANA_MultiTrack.hh"
#include "E16ANA_StepTrack.hh"
#include "E16DST_DST1.hh"

class E16ANA_TrackClusterPair {
 public:
  E16ANA_TrackClusterPair()
      : set_flag(0),
        layer_order(E16DST_DST1Constant::kInvalidValue), module_id(E16DST_DST1Constant::kInvalidValue),
        clusters({nullptr, nullptr}),
        local_pos(E16DST_DST1Constant::kInvalidVector) {}
  ~E16ANA_TrackClusterPair() {}
  void Set(const E16ANA_GeometryV2* _geometry, int _layer_order, int _module_id, const TVector3& _global_pos, E16DST_DST1Cluster* x_cluster) { // SSD
    set_flag = 1;
    layer_order = _layer_order;
    module_id = _module_id;
    clusters[0] = x_cluster;
    clusters[1] = nullptr;
    local_pos = {dynamic_cast<E16DST_DST1SSDCluster*>(x_cluster)->LocalPos().X(), 0., 0.}; // z = 0?
//    global_pos = _geometry->SSD(E16ANA_TrackConstant::ModuleID2020To2013(module_id))->GetGPos(local_pos);
    global_pos = _global_pos;
  }
  void Set(const E16ANA_GeometryV2* _geometry, int _layer_order, int _module_id, const TVector3& _x_global_pos, const TVector3& _y_global_pos, E16DST_DST1Cluster* x_cluster, E16DST_DST1Cluster* y_cluster) { // GTR
    set_flag = 1;
    layer_order = _layer_order;
    module_id = _module_id;
    clusters[0] = x_cluster;
    clusters[1] = y_cluster;
    local_pos = {dynamic_cast<E16DST_DST1GTRCluster*>(x_cluster)->LocalPosT().X(), dynamic_cast<E16DST_DST1GTRCluster*>(y_cluster)->LocalPosT().Y(), 0.}; // z = 0?
//    global_pos = _geometry->GTR(E16ANA_TrackConstant::ModuleID2020To2013(module_id), layer_order - 1)->GetGPos(local_pos);
    global_pos = {_x_global_pos.X(), _y_global_pos.Y(), _x_global_pos.Z()};
  }
  void Clear() {
    set_flag = 0;
    layer_order = E16DST_DST1Constant::kInvalidValue;
    module_id = E16DST_DST1Constant::kInvalidValue;
    clusters.fill(nullptr);
    local_pos = E16DST_DST1Constant::kInvalidVector;
    local_t2pos = E16DST_DST1Constant::kInvalidVector;
    ctiming.clear();
    cpos.clear();
  }
  int SetFlag() { return set_flag; }
  int LayerOrder() { return layer_order; }
  int ModuleID() { return module_id; }
  E16DST_DST1Cluster* Cluster(int type) { return clusters[type]; }
  TVector3& LocalPos() { return local_pos; }
  TVector3& GlobalPos() { return global_pos; }
  TVector3& LocalPosT() { return local_t2pos; }
  TVector3& GlobalPosT() { return global_t2pos; }
  
  void SetT(const E16ANA_GeometryV2* _geometry, int _layer_order, int _module_id, const TVector3& _x_local_pos) { // GTR
    local_t2pos  = {_x_local_pos.X(),_x_local_pos.Y(),_x_local_pos.Z()}; // z = 0?
    global_t2pos = _geometry->GTR(E16ANA_TrackConstant::ModuleID2020To2013(_module_id), _layer_order - 1)->GetGPos(local_t2pos);
    //global_pos = {_x_global_pos.X(), _y_global_pos.Y(), _x_global_pos.Z()};
  }

  int                           NumCls() { return ctiming.size(); }
  double                        CTiming(int i) { return ctiming[i]; }
  double                        CPos(int i)    { return cpos[i]; }
  void                          SetCTiming(double t) { ctiming.push_back(t); }
  void                          SetCPos(double t)    { cpos.push_back(t); }


  void SetTheta(double _ctheta){ ctheta = _ctheta;}
  double Theta(){return ctheta;}
 private:
  int set_flag;
  int layer_order; // order in all detectors (E16ANA_MutiTrack::layer_id: only in GTR)
  int module_id;
  std::array<E16DST_DST1Cluster*, 2> clusters; // x, y
//  std::array<std::shared_ptr<E16DST_DST1Cluster>, 2> clusters; // x, y
  TVector3 local_pos;
  TVector3 global_pos;
  TVector3 local_t2pos;
  TVector3 global_t2pos;
  double ctheta;
  std::vector<double>           ctiming;
  std::vector<double>           cpos;
};

class E16ANA_TrackCandidate {
 public:
  struct FitResult {
    int set_flag;
    int layer_order;
    int module_id;
    TVector3 local_pos;
    TVector3 local_mom;
    TVector3 global_pos;
    TVector3 global_mom;
//    TVector3 local_sigma;
    TVector3 residual_pos;
    TVector3 residual_post;
    TVector3 residual_post2;
    void Clear() {
      set_flag = 0;
      layer_order = E16DST_DST1Constant::kInvalidValue;
      module_id = E16DST_DST1Constant::kInvalidValue;
      local_pos = E16DST_DST1Constant::kInvalidVector;
      local_mom = E16DST_DST1Constant::kInvalidVector;
      global_pos = E16DST_DST1Constant::kInvalidVector;
      global_mom = E16DST_DST1Constant::kInvalidVector;
      residual_pos = E16DST_DST1Constant::kInvalidVector;
      residual_post = E16DST_DST1Constant::kInvalidVector;
      residual_post2 = E16DST_DST1Constant::kInvalidVector;
    }
    void Set(int _layer_order, int _module_id, TVector3 _local_pos, TVector3 _local_mom, TVector3 _global_pos, TVector3 _global_mom, TVector3 _residual_pos) {
      set_flag = 1;
      layer_order = _layer_order;
      module_id = _module_id;
      local_pos = _local_pos;
      local_mom = _local_mom;
      global_pos = _global_pos;
      global_mom = _global_mom;
      residual_pos = _residual_pos;
    }
    void SetT(TVector3 _residual_pos) { residual_post  = _residual_pos;}
    void SetT2(TVector3 _residual_pos){ residual_post2 = _residual_pos;}
    void SetC(TVector3 _residual_pos) { residual_pos   = _residual_pos;}
  };
  E16ANA_TrackCandidate(E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map)
      : geometry(_geometry), bfield_map(_bfield_map), is_selected(false),
        pos_at_targets({E16DST_DST1Constant::kInvalidVector, E16DST_DST1Constant::kInvalidVector, E16DST_DST1Constant::kInvalidVector}),
        mom_at_targets({E16DST_DST1Constant::kInvalidVector, E16DST_DST1Constant::kInvalidVector, E16DST_DST1Constant::kInvalidVector}) {}
  E16ANA_TrackCandidate& operator = (const E16ANA_TrackCandidate& rhs) {
    Copy(rhs);
    return (*this);
  }
  ~E16ANA_TrackCandidate() {}
  void SetTrackID(int _track_id) { track_id = _track_id; }
  void SetIsSearchAssociatedHits(bool _is_search_associated_hits) { is_search_associated_hits = _is_search_associated_hits; }
  void SetHasElectronHBDCluster(bool _has_e_hbd_cluster) { has_e_hbd_cluster = _has_e_hbd_cluster; }
  void SetHasElectronLGHit(bool _has_e_lg_hit) { has_e_lg_hit = _has_e_lg_hit; }
  void SetIsLargeResidual(bool _is_large_residual) { is_large_residual = _is_large_residual; }
  void SetIsNearTarget(bool _is_near_target) { is_near_target = _is_near_target; }
  void SetIsClusterUsed(bool _is_cluster_used) { is_cluster_used = _is_cluster_used; }
  void SetIsSelected(bool _is_selected) { is_selected = _is_selected; }
  void SetCharge(int _charge) { charge = _charge; }
  void SetInitX(double _x) { init_pos.SetX(_x); }
  void SetInitY(double _y) { init_pos.SetY(_y); }
  void SetInitZ(int _target_id) {
    target_id = _target_id;
    init_pos.SetZ(E16ANA_TrackConstant::kTargetZ[target_id]);
  }
  void SetSigma(int layer_index, TVector3 _sigma) { sigma[layer_index] = _sigma; }
  void SetDefaultSigma();
  void SetPosAtX0(TVector3 _pos) { pos_at_x0 = _pos; }
  void SetMomAtX0(TVector3 _mom) { mom_at_x0 = _mom; }
//  TVector3 Sigma() { return kSigma; }
  TVector3 EachSigma(int n);
  TVector3 InitPosError();
  int TrackingMaxSteps();
  int ProjectionMaxSteps();
  int TrackID() { return track_id; }
  int TargetID() { return target_id; }
  bool HasElectronHBDCluster() { return has_e_hbd_cluster; }
  bool HasElectronLGHit() { return has_e_lg_hit; }
  bool IsLargeResidual() { return is_large_residual; }
  bool IsNearTarget() { return is_near_target; }
  bool IsClusterUsed() { return is_cluster_used; }
  bool IsSelected() { return is_selected; }
  int Charge() { return charge; }
  TVector3 InitPos() { return init_pos; }
  TVector3 InitMom() { return init_mom; }
  TVector3 Sigma(int n) { return sigma[n]; }
  TVector3 FitInitPos() { return init_pos_fit; }
  TVector3 FitInitMom() { return init_mom_fit; }
  TVector3 FitInitPosSigma() { return init_pos_sigma; }
  const FitResult& LocalFitResult(int n) const { return fit_results[n]; }
  const std::array<FitResult, E16ANA_TrackConstant::kNumDetectorLayers> LocalFitResults() const { return fit_results; }
  double ChiSquare() { return chisq; }
  int MinimizeStatus() { return minimize_status; }
  int MatrixStatus() { return matrix_status; }
  int NumSteps() { return n_steps; }
  int NumCalls() { return n_calls; }
  bool IsSearchAssociatedHits() { return is_search_associated_hits; }
  int ProjectionFlag() { return projection_flag; }
  E16ANA_TrackClusterPair& ClusterPair(int layer_index) { return cluster_pairs[layer_index]; }
  std::array<E16ANA_TrackClusterPair, E16ANA_TrackConstant::kNumTrackingLayers>& ClusterPairs() { return cluster_pairs; }
  TVector3 PosAtTarget(int n) { return pos_at_targets[n]; }
  std::array<TVector3, E16ANA_TrackConstant::kNumTargets>& PosAtTargets() { return pos_at_targets; }
  TVector3 MomAtTarget(int n) { return mom_at_targets[n]; }
  std::array<TVector3, E16ANA_TrackConstant::kNumTargets>& MomAtTargets() { return mom_at_targets; }
  TVector3 PosAtX0() { return pos_at_x0; }
  TVector3 MomAtX0() { return mom_at_x0; }
  std::vector<E16DST_DST1HBDHit*>& ProjectedHBDHits() { return hbd_hits; }
  std::vector<E16DST_DST1HBDCluster*>& ProjectedHBDClusters() { return hbd_clusters; }
  std::vector<E16DST_DST1LGHit*>& ProjectedLGHits() { return lg_hits; }
  std::vector<E16DST_DST1LGCluster*>& ProjectedLGClusters() { return lg_clusters; }
  double Fit(E16ANA_MultiTrack* fitter, bool vertex_xy_fix_flag, bool py_fix_flag, bool vertex_z_fix_flag);
  void Print() {
    if (chisq >= 1.0e10 || minimize_status == 0) {
      return;
    }
    std::cout << "Track ID : " << track_id << ", Target ID : " << target_id << ", Charge : " << charge << std::endl;
    std::cout << "Chi Square : " << chisq << ", Minimize Status : " << minimize_status << ", Matrix Status : " << matrix_status << std::endl;
    std::cout << "  Initial Position : (" << init_pos_fit.X() << ", " << init_pos_fit.Y() << ", " << init_pos_fit.Z() << ")" << std::endl;
    std::cout << "  Initial Momentum : (" << init_mom_fit.X() << ", " << init_mom_fit.Y() << ", " << init_mom_fit.Z() << ")" << std::endl;
    for (int l = 0; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l) {
      std::cout << "  Detector : " << E16ANA_TrackConstant::kDetectorName[l] << " (Layer ID : " << l << "), Module ID : " << fit_results[l].module_id << std::endl;
      auto fit_local_pos = fit_results[l].local_pos;
      auto fit_global_pos = fit_results[l].global_pos;
      if (l < E16ANA_TrackConstant::kNumTrackingLayers) {
        auto& pair = cluster_pairs[l];
        auto local_pos = pair.LocalPos();
        auto global_pos = pair.GlobalPos();
        std::cout << "    Local  Position (Hit) : (" << local_pos.X()  << ", " << local_pos.Y()  << ", " << local_pos.Z()  << ")" << std::endl;
        std::cout << "    Global Position (Hit) : (" << global_pos.X() << ", " << global_pos.Y() << ", " << global_pos.Z() << ")" << std::endl;
      }
      if (fit_results[l].set_flag == 1) {
        std::cout << "    Local  Position (Fit) : (" << fit_local_pos.X()  << ", " << fit_local_pos.Y()  << ", " << fit_local_pos.Z()  << ")" << std::endl;
        std::cout << "    Global Position (Fit) : (" << fit_global_pos.X() << ", " << fit_global_pos.Y() << ", " << fit_global_pos.Z() << ")" << std::endl;
      } else {
        std::cout << "    Runge Kutta Failure" << std::endl;
      }
    }
    std::cout << "  Number of Projection LG Hits : " << lg_hits.size() << std::endl;
    for (auto& hit : lg_hits) {
      std::cout << "    Module ID : " << hit->ModuleId() << ", Channel ID : " << hit->ChannelId() << ", Timing : " << hit->Timing()  << std::endl;
    }
  }
  void PrintParam();
  // tmp
  void SetXCoef(int n, double coef) { x_coef[n] = coef; }
  void SetXChiSquare(double _chi_square) { x_chi_square = _chi_square; }
  void SetAssociatedHBD(const std::vector<int>& _hbd_ids, const std::vector<double>& _hbd_ress, const std::vector<bool>& _hbd_y_oks) {
    hbd_ids.clear();
    hbd_ress.clear();
    hbd_y_oks.clear();
    copy(_hbd_ids.begin(),  _hbd_ids.end(),  back_inserter(hbd_ids));
    copy(_hbd_ress.begin(), _hbd_ress.end(), back_inserter(hbd_ress));
    copy(_hbd_y_oks.begin(), _hbd_y_oks.end(), back_inserter(hbd_y_oks));
    return;
  }
  void SetYCoef(int n, double coef) { y_coef[n] = coef; }
  void SetYChiSquare(double _chi_square) { y_chi_square = _chi_square; }
  double XCoef(int n) { return x_coef[n]; }
  double XChiSquare() { return x_chi_square; }
  std::vector<int>& RoughAssociatedHBDIDs() { return hbd_ids; }
  std::vector<double>& RoughAssociatedHBDResiduals() { return hbd_ress; }
  std::vector<bool>& RoughAssociatedHBDYOKs() { return hbd_y_oks; }
  double YCoef(int n) { return y_coef[n]; }
  double YChiSquare() { return y_chi_square; }
 private:
  static constexpr int kRKPrintLevel = 1; // tmp
  static constexpr std::array<int, E16ANA_TrackConstant::kNumLGLayers> kTypicalLGBlocks = {0, 10, 20};
//  static constexpr int kMinuitStrategy = 0;
//  static constexpr int kMinuitMaxFunctionCalls = 1.0e3;
//  static constexpr double kTrackingStepSize = 5.;
//  static constexpr int kTrackingMaxSteps = 300;
//  static constexpr int kTrackingMaxSteps = 400;
//  static constexpr int kTrackingMaxSteps = 80;
//  static constexpr int kTrackingMaxSteps = 600;
//  static constexpr int kProjectionMaxSteps = 2000;
  static constexpr double drift_v  = 8e-3;
  static constexpr double centtdc = 328;
  static constexpr double kGTRLorentzAngle[3]   = {7.5 * 0.35, -5.5 * 0.35, -3. * 0.35};
  static constexpr double kGTRLorentzAngleA[3]  = {0.313, -0.233, -0.129};
  // parameter
//  static inline const TVector3 kSigma = {800.0e-3, 5000.0e-3, 0.};
//  static inline const std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> kSigmas = {{{0.1, 0., 0.}, {0.3, 1., 0.}, {0.3, 1., 0.}, {0.3, 1., 0.}}}; // -> parameter
//  static inline const TVector3 kInitPosError = {1.5, 1.7, 0.};
//  static inline const TVector3 kInitPosError = {3., 3.4, 0.}; // -> paramter
//  static inline const TVector3 kInitPosError = {0., 0., 0.};
//  static inline const TVector3 kInitPosError = {5., 5., 0.};
  void Copy(const E16ANA_TrackCandidate& rhs) {
    this->geometry = rhs.geometry;
    this->bfield_map = rhs.bfield_map;
    this->track_id = rhs.track_id;
    this->target_id = rhs.target_id;
    this->has_e_hbd_cluster = rhs.has_e_hbd_cluster;
    this->has_e_lg_hit = rhs.has_e_lg_hit;
    this->is_large_residual = rhs.is_large_residual;
    this->is_near_target = rhs.is_near_target;
    this->is_cluster_used = rhs.is_cluster_used;
    this->is_selected = rhs.is_selected;
    this->cluster_pairs = rhs.cluster_pairs;
    this->charge = rhs.charge;
    this->init_pos = rhs.init_pos;
    this->init_mom = rhs.init_mom;
    this->sigma = rhs.sigma;
    this->x_coef = rhs.x_coef;
    this->x_chi_square = rhs.x_chi_square;
    this->hbd_ids = rhs.hbd_ids;
    this->hbd_ress = rhs.hbd_ress;
    this->hbd_y_oks = rhs.hbd_y_oks;
    this->y_coef = rhs.y_coef;
    this->y_chi_square = rhs.y_chi_square;
    this->init_pos_fit = rhs.init_pos_fit;
    this->init_mom_fit = rhs.init_mom_fit;
    this->init_pos_sigma = rhs.init_pos_sigma;
    this->fit_results = rhs.fit_results;
    this->chisq = rhs.chisq;
    this->minimize_status = rhs.minimize_status;
    this->matrix_status = rhs.matrix_status;
    this->n_steps = rhs.n_steps;
    this->n_calls = rhs.n_calls;
    this->pos_at_targets = rhs.pos_at_targets;
    this->mom_at_targets = rhs.mom_at_targets;
    this->pos_at_x0 = rhs.pos_at_x0;
    this->mom_at_x0 = rhs.mom_at_x0;
    this->projection_flag = rhs.projection_flag;
    this->hbd_hits = rhs.hbd_hits;
    this->hbd_clusters = rhs.hbd_clusters;
    this->lg_hits = rhs.lg_hits;
    this->lg_clusters = rhs.lg_clusters;
  }
  static TVector3 ConformalTransformation(const TVector3& h) {
    double u = h.X() / (h.X() * h.X() + h.Z() + h.Z());
    double v = h.Z() / (h.X() * h.X() + h.Z() + h.Z());
    return TVector3(u, 0, v);
  }
  static double CalcPhaseDiff(const TVector3& v0, const TVector3& v1) {
    double p0 = atan2(v0.X(), v0.Z());
    double p1 = atan2(v1.X(), v1.Z());
    double diff = p0 - p1;
    if (diff > TMath::Pi()) {
      diff = diff - 2. * TMath::Pi();
    } else if (diff < -TMath::Pi()) {
      diff = diff + 2. * TMath::Pi();
    }
    return diff;
  }
  static TVector3 CalcRoughMomentum(const TVector3& gxz0, const TVector3& gxz1);
  bool CalcRoughMomentum();
  bool CalcRoughMomentumV2();
  void AddTrackHit(E16ANA_MultiTrack* single_track);
  void Projection(E16ANA_MultiTrack* fitter);
  void UpdateFitResult(E16ANA_MultiTrack* fitter);
  E16ANA_GeometryV2* geometry;
  E16ANA_MagneticFieldMap* bfield_map;
  int track_id;
  int target_id;
  bool has_e_hbd_cluster;
  bool has_e_lg_hit;
  bool is_large_residual;
  bool is_near_target;
  bool is_cluster_used;
  bool is_selected;
  std::array<E16ANA_TrackClusterPair, E16ANA_TrackConstant::kNumTrackingLayers> cluster_pairs;
  // Preset Value
  int charge;
  TVector3 init_pos;
  TVector3 init_mom;
  TVector3 init_circ;
  std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> sigma;
  // raugh fit chi square (tmp?)
  std::array<double, 3> x_coef;
  double x_chi_square;
  std::vector<int> hbd_ids;
  std::vector<double> hbd_ress;
  std::vector<bool> hbd_y_oks;
  std::array<double, 2> y_coef;
  double y_chi_square;
  // Fit Result
  TVector3 init_pos_fit;
  TVector3 init_mom_fit;
  TVector3 init_pos_sigma;
  std::array<FitResult, E16ANA_TrackConstant::kNumDetectorLayers> fit_results;
  double chisq;
  int minimize_status;
  int matrix_status;
  int n_steps;
  int n_calls;
  // projection
  std::array<TVector3, E16ANA_TrackConstant::kNumTargets> pos_at_targets;
  std::array<TVector3, E16ANA_TrackConstant::kNumTargets> mom_at_targets;
  TVector3 pos_at_x0;
  TVector3 mom_at_x0;
  bool is_search_associated_hits;
  int projection_flag; // bit0: HBD, 1: LG0, 2: LG1, 3: LG2
  std::vector<E16DST_DST1HBDHit*> hbd_hits;
  std::vector<E16DST_DST1HBDCluster*> hbd_clusters;
  std::vector<E16DST_DST1LGHit*> lg_hits;
  std::vector<E16DST_DST1LGCluster*> lg_clusters;
};

class E16ANA_TrackCandidates {
 public:
  struct TrackPair {
    E16ANA_TrackCandidate* cand_minus;
    E16ANA_TrackCandidate* cand_plus;
    TVector3 vtx;
    double distance;
    TVector3 mom_minus;
    TVector3 mom_plus;
    bool is_refit;
    bool is_selected;
    double chi_square_refit;
    TVector3 vtx_refit;
    TVector3 mom_minus_refit;
    TVector3 mom_plus_refit;
    std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> track_minus_pos_refit;
    std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> track_plus_pos_refit;
    std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> track_minus_mom_refit;
    std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> track_plus_mom_refit;
    std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> track_minus_res_refit;
    std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> track_plus_res_refit;
    TrackPair& operator = (const TrackPair& rhs) {
      Copy(rhs);
      return (*this);
    }
    void Copy(const TrackPair& rhs) {
      this->cand_minus = rhs.cand_minus;
      this->cand_plus = rhs.cand_plus;
      this->vtx = rhs.vtx;
      this->distance = rhs.distance;
      this->mom_minus = rhs.mom_minus;
      this->mom_plus = rhs.mom_plus;
      this->is_refit = rhs.is_refit;
      this->is_selected = rhs.is_selected;
      this->chi_square_refit = rhs.chi_square_refit;
      this->vtx_refit = rhs.vtx_refit;
      this->mom_minus_refit = rhs.mom_minus_refit;
      this->mom_plus_refit = rhs.mom_plus_refit;
      this->track_minus_pos_refit = rhs.track_minus_pos_refit;
      this->track_plus_pos_refit = rhs.track_plus_pos_refit;
      this->track_minus_mom_refit = rhs.track_minus_mom_refit;
      this->track_plus_mom_refit = rhs.track_plus_mom_refit;
      this->track_minus_res_refit = rhs.track_minus_res_refit;
      this->track_plus_res_refit = rhs.track_plus_res_refit;
      return;
    }
    void Clear() {
      cand_minus = nullptr;
      cand_plus = nullptr;
      vtx = E16DST_DST1Constant::kInvalidVector;
      distance = E16DST_DST1Constant::kInvalidValue;
      mom_minus = E16DST_DST1Constant::kInvalidVector;
      mom_plus = E16DST_DST1Constant::kInvalidVector;
      is_refit = false;
      is_selected = false;
      vtx_refit = E16DST_DST1Constant::kInvalidVector;
//      distance_refit = E16DST_DST1Constant::kInvalidValue;
      mom_minus_refit = E16DST_DST1Constant::kInvalidVector;
      mom_plus_refit = E16DST_DST1Constant::kInvalidVector;
      track_minus_pos_refit.fill(E16DST_DST1Constant::kInvalidVector);
      track_plus_pos_refit.fill(E16DST_DST1Constant::kInvalidVector);
      track_minus_mom_refit.fill(E16DST_DST1Constant::kInvalidVector);
      track_plus_mom_refit.fill(E16DST_DST1Constant::kInvalidVector);
      track_minus_res_refit.fill(E16DST_DST1Constant::kInvalidVector);
      track_plus_res_refit.fill(E16DST_DST1Constant::kInvalidVector);
    }
  };
  E16ANA_TrackCandidates(E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map, E16ANA_MultiTrack* _fitter, E16ANA_MultiTrack* _pair_fitter, bool _is_electron_run, E16DST_DST1PhysicsRecord* _record)
      : geometry(_geometry), bfield_map(_bfield_map), fitter(_fitter), pair_fitter(_pair_fitter),
        is_electron_run(_is_electron_run), is_used_layer({true, true, true, true}), vertex_xy_fix_flag(false), py_fix_flag(false),
        vertex_z_fix_flag(E16ANA_TrackParameter::kVtxZFixFlag),
        record(_record) {
    track_candidates.clear();
  }
  ~E16ANA_TrackCandidates() {}
  void SetIsUseLayer(int n, bool _is_used) { is_used_layer[n] = _is_used; }
  void SetFlags(bool _vertex_xy_fix_flag, bool _py_fix_flag, bool _vertex_z_fix_flag) {
    vertex_xy_fix_flag = _vertex_xy_fix_flag;
    py_fix_flag = _py_fix_flag;
    vertex_z_fix_flag = _vertex_z_fix_flag;
  }
  bool IsElectronRun() { return is_electron_run; }
  bool IsUsedLayer(int n) { return is_used_layer[n]; }
  bool VertexXYFixFlag() { return vertex_xy_fix_flag; }
  bool PyFixFlag() { return py_fix_flag; }
  bool VertexZFixFlag() { return vertex_z_fix_flag; }
  double GTRTimeDiffThreshold(int n);
  double XSigma(int n);
  double XWeight(int n);
  double YSigma(int n);
  double YWeight(int n);
  int MinHitsInXCluster();
  double GTRYDiffThreshold();
  double GTRPeakSumThresholdX(int n);
  double GTRPeakSumThresholdY();
  double RoughFitChiSquareThreshold(int n);
  double RoughXFitCoefficientThreshold(int n);
  double RoughYFitCoefficientThreshold(int n);
  double HBDProjectionThreshold() { return kHBDProjectionThreshold; }
  double LGProjectionThreshold() { return kLGProjectionThreshold; }
  double LGElectronThreshold() { return kLGElectronThreshold; }
  double ResidualThresholdX(int n) { return kResidualThresholdX[n]; }
  double ResidualThresholdY(int n) { return kResidualThresholdY[n]; }
  double NearTargetThreshold() { return kNearTargetThreshold; }
  double StepTrackStepSizeCm() { return kStepTrackStepSizeCm; }
  int StepTrackArraySize() { return kStepTrackArraySize; }
  TVector3 VertexSigma() { return kVertexSigma; }
//  TVector3 PairFitSigma(int n) { return kSigmas[n]; }
  int NumXCandidates() { return n_x_cands; }
  int NumYCandidates() { return n_y_cands; }
  int NumTrackCandidates() { return track_candidates.size(); }
  E16ANA_TrackCandidate& TrackCandidate(int n) { return track_candidates[n]; }
  std::vector<E16ANA_TrackCandidate>& TrackCandidates() { return track_candidates; }
  int NumSelectedTrackCandidates() { return selected_track_candidates.size(); }
  E16ANA_TrackCandidate* SelectedTrackCandidate(int n) { return selected_track_candidates[n]; }
  std::vector<E16ANA_TrackCandidate*>& SelectedTrackCandidates() { return selected_track_candidates; }
  int NumTrackCandidatePairs() { return track_pairs.size(); }
  TrackPair& TrackCandidatePair(int n) { return track_pairs[n]; }
  std::vector<TrackPair>& TrackCandidatePairs() { return track_pairs; }
  int NumSelectedTrackCandidatePairs() { return selected_track_pairs.size(); }
  TrackPair* SelectedTrackCandidatePair(int n) {return selected_track_pairs[n]; }
  std::vector<TrackPair*>& SelectedTrackCandidatePairs() { return selected_track_pairs; }
  void Analyze();
  void Print(int i) {
    if (i % 2 == 1) {
      std::cout << "Track Candidates :" << std::endl;
      for (auto& cand : track_candidates) {
        cand.Print();
      }
    }
    i /= 2;
    if (i % 2 == 1) {
      std::cout << "Selected Track Candidates :" << std::endl;
      for (auto& cand : selected_track_candidates) {
        cand->Print();
      }
    }
    std::cout << "Number of track candidates : " << NumTrackCandidates() << std::endl;
    std::cout << "Number of selected track candidates : " << NumSelectedTrackCandidates() << std::endl;
  }
  void PrintParam();
#ifdef TRACK_EFF_CHECK
  uint32_t XSearchRejectPoint(int n) { return x_search_reject_point[n]; }
  uint32_t XFitRejectPoint(int n) { return x_fit_reject_point[n]; }
  uint32_t YRejectPoint(int n) { return y_reject_point[n]; }
  uint32_t XYRejectPoint(int n) { return xy_reject_point[n]; }
  uint32_t RejectPoint(int n) { return reject_point[n]; }
  bool     SimTrackDetected(int n) { return sim_track_detected[n]; }
  uint32_t Pow2(int n) {
    uint32_t val = 1;
    for (int i = 0; i < n; ++i) {
      val *= 2;
    }
    return val;
  }
#endif // TRACK_EFF_CHECK
 private:
  struct OneAxisClusterSet {
    int target_id; // only x
    double xy;
    int charge; // only x
    double chi_square;
    std::array<double, 3> coefs;
    std::vector<int> hbd_indexs;
    std::vector<int> hbd_ids;
    std::vector<double> hbd_ress;
    std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> global_poss;
//    std::array<double, E16ANA_TrackConstant::kNumTrackingLayers> timings;
    E16DST_DST1SSDCluster* ssd_cluster;
//    std::array<E16DST_DST1GTRCluster*, kNumGTRLayers> gtr_clusters;
    std::array<E16DST_DST1GTRCluster*, 3> gtr_clusters;
  };
  static constexpr int kNumTrackingLayersWTarget = 1 + E16ANA_TrackConstant::kNumTrackingLayers;
  static constexpr int kNumGTRLayers = E16ANA_TrackConstant::kNumTrackingLayers - 1;
  static constexpr std::array<int, 2> kNumRoughFitDegree = {3, 2}; // x, y
  static constexpr std::array<double, kNumGTRLayers> kGTRSizeCoef = {2.7, 1.4, 1.};
  static constexpr std::array<int, 3> kNumReserveTracks = {1000, 1000, 100};
//  static constexpr int kMaxOneAxisCandidates = 100;
  // parameter
//  static constexpr std::array<double, kNumGTRLayers> kGTRTimeDiffThreshold = {40., 60., 60.};
//  static constexpr std::array<double, kNumGTRLayers> kGTRTimeDiffThreshold = {120., 120., 120.};
//  static constexpr std::array<double, kNumGTRLayers> kGTRTimeDiffThreshold = {40., 60., 120.}; // -> parameter
//  static constexpr std::array<double, kNumGTRLayers> kGTRTimeDiffThreshold = {40., 80., 120.}; // ozawa v8
//  static constexpr const std::array<double, kNumTrackingLayersWTarget> kXSigma = {5., 0.05, 0.1, 0.1, 0.1};
//  static constexpr const std::array<double, kNumTrackingLayersWTarget> kXSigma = {20., 0.05, 0.1, 0.1, 0.1};
//  static constexpr const std::array<double, kNumTrackingLayersWTarget> kXSigma = {1000., 0.05, 0.1, 0.1, 0.1};
//  static constexpr const std::array<double, kNumTrackingLayersWTarget> kXSigma = {100., 0.05, 0.1, 0.1, 0.1}; // -> parameter
//  static constexpr std::array<double, kNumTrackingLayersWTarget> kXWeight = {1. / (kXSigma[0] * kXSigma[0]),
//                                                                             1. / (kXSigma[1] * kXSigma[1]),
//                                                                             1. / (kXSigma[2] * kXSigma[2]),
//                                                                             1. / (kXSigma[3] * kXSigma[3]),
//                                                                             1. / (kXSigma[4] * kXSigma[4])};
//  static constexpr std::array<double, kNumGTRLayers> kYSigma = {1., 1., 1.}; // -> parameter
//  static constexpr std::array<double, kNumGTRLayers> kYWeight = {1. / (kYSigma[0] * kYSigma[0]),
//                                                                 1. / (kYSigma[1] * kYSigma[1]),
//                                                                 1. / (kYSigma[2] * kYSigma[2])};
//  static constexpr int kMinHitsInXCluster = 2; // -> parameter
//  static constexpr double kGTRYDiffThreshold = 20.; // mm -> parameter
//  static constexpr double kGTRPeakSumThresholdX = 180.;
//  static constexpr std::array<double, kNumGTRLayers> kGTRPeakSumThresholdX = {80., 150., 250.}; // -> parameter
//  static constexpr double kGTRPeakSumThresholdY = 10.;
//  static constexpr double kGTRPeakSumThresholdY = 50.; // -> parameter
//  static constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {50., 10.}; // x, y
//  static constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {200., 10.}; // x, y
//  static constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {200., 20.}; // x, y -> parameter
//  static constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {200., 150.}; // x, y
//  static constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {1000., 10.}; // x, y. ozawa v8
//  static constexpr std::array<double, kNumRoughFitDegree[0]> kRoughXFitCoefficientThreshold = {10., 0., 0.001}; // coef[1] not used
//  static constexpr std::array<double, kNumRoughFitDegree[0]> kRoughXFitCoefficientThreshold = {25., 0., 0.001}; // coef[1] not used. ozawa v8
//  static constexpr std::array<double, kNumRoughFitDegree[0]> kRoughXFitCoefficientThreshold = {1000., 0., 0.001};
//  static constexpr std::array<double, kNumRoughFitDegree[0]> kRoughXFitCoefficientThreshold = {100., 0., 0.001}; // -> parameter
//  static constexpr std::array<double, kNumRoughFitDegree[0]> kRoughXFitCoefficientThreshold = {25., 0., 0.01}; // coef[1] not used. ozawa v8
//  static constexpr std::array<double, kNumRoughFitDegree[1]> kRoughYFitCoefficientThreshold = {15., 0.}; // coef[1] not used.
//  static constexpr std::array<double, kNumRoughFitDegree[1]> kRoughYFitCoefficientThreshold = {25., 0.}; // coef[1] not used.
//  static constexpr std::array<double, kNumRoughFitDegree[1]> kRoughYFitCoefficientThreshold = {1000., 0.}; // coef[1] not used.
//  static constexpr std::array<double, kNumRoughFitDegree[1]> kRoughYFitCoefficientThreshold = {50., 0.}; // coef[1] not used. -> parameter
//  static constexpr double kHBDProjectionThreshold = 20.;
  static constexpr double kHBDProjectionThreshold = 40.;
  static constexpr double kLGProjectionThreshold = 100.; // 98.
  static constexpr double kLGElectronThreshold = 50.;
  static constexpr double kNearTargetThreshold = 100.; // square value
  static constexpr std::array<double, E16ANA_TrackConstant::kNumTrackingLayers> kResidualThresholdX = {1., 2., 2., 1.5};
  static constexpr std::array<double, E16ANA_TrackConstant::kNumTrackingLayers> kResidualThresholdY = {0., 4., 4., 4.};
  static constexpr double kStepTrackStepSizeCm = 0.1; // cm
  static constexpr int kStepTrackArraySize = 1000; // 0.1 cm x 1000 = 1 m
  static constexpr double kPairTrackingStepSize = 1.;
  static constexpr int kPairTrackingMaxSteps = 400;
  static constexpr int kPairMinuitStrategy = 2;
  static constexpr int kPairMinuitMaxFunctionCalls = 1.0e4;
//  static inline const TVector3 kVertexSigma = {3., 3., 0.};
  static inline const TVector3 kVertexSigma = {0., 0., 0.};
//  static inline const std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> kSigmas = {{{0.1, 0., 0.}, {0.3, 1., 0.}, {0.3, 1., 0.}, {0.3, 1., 0.}}};

  static bool IsLModule(int module_id) { return module_id > 105 ? true : false; }
  static bool IsCurveCorrelation(double tgt_z, const std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers>& pos_set);
  static TVector3 Lotate(double rot_cos, double rot_sin, double offset, const TVector3& pos) {
    auto x = rot_cos * pos.X() - rot_sin * (pos.Z() - offset);
    auto z = rot_sin * pos.X() + rot_cos * (pos.Z() - offset);
    return TVector3(x, 0, z);
  }
  static void CalcLotatedPos(std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers>& pos, double tgt_z, double rot_cos, double rot_sin, std::array<TVector3, kNumTrackingLayersWTarget>* lotated_pos);
  static void AddMatrixElement(double w, const TVector3& lotated_pos, std::array<double, kNumTrackingLayersWTarget>* zz, std::array<double, kNumRoughFitDegree[0]>* zx) {
    auto x = lotated_pos.X();
    auto z = lotated_pos.Z();
    (*zz)[4] += w * z * z * z * z; // delete at
    (*zz)[3] += w * z * z * z;
    (*zz)[2] += w * z * z;
    (*zz)[1] += w * z;
    (*zz)[0] += w;
    (*zx)[2] += w * x * z * z;
    (*zx)[1] += w * x * z;
    (*zx)[0] += w * x;
    return;
  }
  static void CalcQuadCurve(const std::array<TVector3, kNumTrackingLayersWTarget>& lotated_pos,
                            std::array<double, kNumTrackingLayersWTarget>* zz,
                            std::array<double, kNumRoughFitDegree[0]>* zx,
                            std::array<double, kNumRoughFitDegree[0]>* coef);
  static void CalcInverseMatrix(const std::array<double, 1 + E16ANA_TrackConstant::kNumTrackingLayers>& zz, std::array<std::array<double, kNumRoughFitDegree[0]>, kNumRoughFitDegree[0]>* line);
  static void CalcCoefficients(const std::array<double, kNumRoughFitDegree[0]>& zx,
                               const std::array<std::array<double, kNumRoughFitDegree[0]>, kNumRoughFitDegree[0]>& line,
                               std::array<double, kNumRoughFitDegree[0]>* coef) {
    (*coef)[0] = line[2][0] * zx[2] + line[2][1] * zx[1] + line[2][2] * zx[0];
    (*coef)[1] = line[1][0] * zx[2] + line[1][1] * zx[1] + line[1][2] * zx[0];
    (*coef)[2] = line[0][0] * zx[2] + line[0][1] * zx[1] + line[0][2] * zx[0];
    return;
  }
//  static void CalcTargetX();
//  static void CalcTargetZ();
//  static void CalcChiSquare();
  bool HasXAssociatedHBD(int tgt_id, const OneAxisClusterSet& cluster_set, const std::array<double, kNumRoughFitDegree[0]>& coef,
                         std::vector<int>* hbd_indexs, std::vector<int>* hbd_ids, std::vector<double>* hbd_ress);
  bool IsXTrackCandidate(int tgt_id, double prev_chi2, OneAxisClusterSet* cluster_set);
  bool IsYTrackCandidate(OneAxisClusterSet* cluster_set);
//  static bool ExistADCCorrelation(float x_adc, float y_adc) {
////    if (y_adc < 0.74 * x_adc + 600. && (y_adc > 0.74 * x_adc - 600. || y_adc > 1200.)) {
//    if (y_adc < 0.74 * x_adc + 800. && (y_adc > 0.74 * x_adc - 800. || y_adc > 1200.)) {
//      return true;
//    }
//    return false;
//  }
  bool HasAssociatedHBD(const OneAxisClusterSet& x_cand, const OneAxisClusterSet& y_cand, std::vector<bool>* hbd_y_oks);
  void SearchTrackCandidates();
  void Fit();
  void SearchHBDAndLGHits();
  void SelectTracks();
  void ProjectionTarget();
  void ProjectionX0();
  double SearchVertex(TrackPair* track_pair);
  void AddTracks(TrackPair* track_pair, double tgt_z);
  void UpdateFitResult(TrackPair* track_pair);
  void PairTracking(TrackPair* track_pair, double tgt_z);
  void SelectTrackPairs();
  void AnalyzeTrackPairs();
  void AddTracksToRecord();
  E16ANA_GeometryV2* geometry;
  E16ANA_MagneticFieldMap* bfield_map;
  E16ANA_MultiTrack* fitter;
  E16ANA_MultiTrack* pair_fitter;
  bool is_electron_run;
  std::array<bool, E16ANA_TrackConstant::kNumTrackingLayers> is_used_layer;
  bool vertex_xy_fix_flag;
  bool py_fix_flag;
  bool vertex_z_fix_flag;
  E16DST_DST1PhysicsRecord* record;
  int n_x_cands;
  int n_y_cands;
  std::vector<E16ANA_TrackCandidate> track_candidates;
  std::vector<E16ANA_TrackCandidate*> selected_track_candidates;
  std::vector<TrackPair> track_pairs;
  std::vector<TrackPair*> selected_track_pairs;
#ifdef TRACK_EFF_CHECK
  std::array<std::array<bool, 4>, 2> is_xchecked;
  std::array<std::array<bool, 3>, 2> is_ychecked;
  std::array<std::array<bool, 4>, 2> is_sim_xcluster;
  std::array<std::array<bool, 3>, 2> is_sim_ycluster;
  std::array<uint32_t, 2> x_search_reject_point;
  std::array<uint32_t, 2> x_fit_reject_point;
  std::array<uint32_t, 2> y_reject_point;
  std::array<uint32_t, 2> xy_reject_point;
  std::array<uint32_t, 2> reject_point;
  std::array<bool, 2>     sim_track_detected;
#endif
};

#endif // E16ANA_TRACKCANDIDATE_HH
