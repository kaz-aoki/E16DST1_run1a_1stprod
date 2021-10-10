#ifndef E16ANA_TRACKCANDIDATE_HH
#define E16ANA_TRACKCANDIDATE_HH

#include <array>
#include <iostream>
#include <vector>

#include "TVector3.h"
#include "E16ANA_TrackConstant.hh"
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
    local_pos = {dynamic_cast<E16DST_DST1GTRCluster*>(x_cluster)->LocalPos().X(), dynamic_cast<E16DST_DST1GTRCluster*>(y_cluster)->LocalPos().Y(), 0.}; // z = 0?
//    global_pos = _geometry->GTR(E16ANA_TrackConstant::ModuleID2020To2013(module_id), layer_order - 1)->GetGPos(local_pos);
    global_pos = {_x_global_pos.X(), _y_global_pos.Y(), _x_global_pos.Z()};
  }
  void Clear() {
    set_flag = 0;
    layer_order = E16DST_DST1Constant::kInvalidValue;
    module_id = E16DST_DST1Constant::kInvalidValue;
    clusters.fill(nullptr);
    local_pos = E16DST_DST1Constant::kInvalidVector;
  }
  int SetFlag() { return set_flag; }
  int LayerOrder() { return layer_order; }
  int ModuleID() { return module_id; }
  E16DST_DST1Cluster* Cluster(int type) { return clusters[type]; }
  TVector3& LocalPos() { return local_pos; }
  TVector3& GlobalPos() { return global_pos; }
 private:
  int set_flag;
  int layer_order; // order in all detectors (E16ANA_MutiTrack::layer_id: only in GTR)
  int module_id;
  std::array<E16DST_DST1Cluster*, 2> clusters; // x, y
  TVector3 local_pos;
  TVector3 global_pos;
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
    void Clear() {
      set_flag = 0;
      layer_order = E16DST_DST1Constant::kInvalidValue;
      module_id = E16DST_DST1Constant::kInvalidValue;
      local_pos = E16DST_DST1Constant::kInvalidVector;
      local_mom = E16DST_DST1Constant::kInvalidVector;
      global_pos = E16DST_DST1Constant::kInvalidVector;
      global_mom = E16DST_DST1Constant::kInvalidVector;
      residual_pos = E16DST_DST1Constant::kInvalidVector;
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
  void SetIsSelected(bool _is_selected) { is_selected = _is_selected; }
  void SetCharge(int _charge) { charge = _charge; }
  void SetInitPos(int _target_id) {
    target_id = _target_id;
    init_pos = {0., 0., E16ANA_TrackConstant::kTargetZ[target_id]};
  }
  void SetSigma(int layer_index, TVector3 _sigma) { sigma[layer_index] = _sigma; }
  void SetDefaultSigma() {
    for (auto& s : sigma) {
      s = kSigma;
    }
    sigma[0].SetY(0.); // SSD-y
  }
  TVector3 Sigma() { return kSigma; }
  TVector3 InitPosError() { return kInitPosError; }
  int TrackingMaxSteps() { return kTrackingMaxSteps; }
  int ProjectionMaxSteps() { return kProjectionMaxSteps; }
  int TrackID() { return track_id; }
  int TargetID() { return target_id; }
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
  int ProjectionFlag() { return projection_flag; }
  E16ANA_TrackClusterPair& ClusterPair(int layer_index) { return cluster_pairs[layer_index]; }
  std::array<E16ANA_TrackClusterPair, E16ANA_TrackConstant::kNumTrackingLayers>& ClusterPairs() { return cluster_pairs; }
  TVector3 PosAtTarget(int n) { return pos_at_targets[n]; }
  std::array<TVector3, E16ANA_TrackConstant::kNumTargets>& PosAtTargets() { return pos_at_targets; }
  TVector3 MomAtTarget(int n) { return mom_at_targets[n]; }
  std::array<TVector3, E16ANA_TrackConstant::kNumTargets>& MomAtTargets() { return mom_at_targets; }
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
  void PrintParam() {
    std::cout << "Sigma : ("  << kSigma(0) << ", " << kSigma(1) << ", " << kSigma(2) << ")" << std::endl;
    std::cout << "Initial Position Error : (" << kInitPosError(0) << ", " << kInitPosError(1) << ", " << kInitPosError(2) << ")" << std::endl;
    std::cout << "Runge Kutta Tracking Max Steps : " << kTrackingMaxSteps << std::endl;
    std::cout << "Runge Kutta Projection Max Steps : " << kProjectionMaxSteps << std::endl;
  }
  // tmp
  void SetXCoef(int n, double coef) { x_coef[n] = coef; }
  void SetXChiSquare(double _chi_square) { x_chi_square = _chi_square; }
  void SetYCoef(int n, double coef) { y_coef[n] = coef; }
  void SetYChiSquare(double _chi_square) { y_chi_square = _chi_square; }
  double XCoef(int n) { return x_coef[n]; }
  double XChiSquare() { return x_chi_square; }
  double YCoef(int n) { return y_coef[n]; }
  double YChiSquare() { return y_chi_square; }
 private:
  static constexpr int kRKPrintLevel = 1; // tmp
  static constexpr std::array<int, E16ANA_TrackConstant::kNumLGLayers> kTypicalLGBlocks = {0, 10, 20};
  // parameter
  static inline const TVector3 kSigma = {800.0e-3, 5000.0e-3, 0.};
//  static inline const TVector3 kVertexError = {1.5, 1.7, 20e-3};
  static inline const TVector3 kInitPosError = {0., 0., 0.};
//  static constexpr int kTrackingMaxSteps = 300;
  static constexpr int kTrackingMaxSteps = 400;
  static constexpr int kProjectionMaxSteps = 2000;
  void Copy(const E16ANA_TrackCandidate& rhs) {
    this->geometry = rhs.geometry;
    this->bfield_map = rhs.bfield_map;
    this->track_id = rhs.track_id;
    this->target_id = rhs.target_id;
    this->is_selected = rhs.is_selected;
    this->cluster_pairs = rhs.cluster_pairs;
    this->charge = rhs.charge;
    this->init_pos = rhs.init_pos;
    this->init_mom = rhs.init_mom;
    this->sigma = rhs.sigma;
    this->x_coef = rhs.x_coef;
    this->x_chi_square = rhs.x_chi_square;
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
  void AddTrackHit(E16ANA_MultiTrack* single_track);
  void Projection(E16ANA_MultiTrack* fitter);
  void UpdateFitResult(E16ANA_MultiTrack* fitter);
  E16ANA_GeometryV2* geometry;
  E16ANA_MagneticFieldMap* bfield_map;
  int track_id;
  int target_id;
  bool is_selected;
  std::array<E16ANA_TrackClusterPair, E16ANA_TrackConstant::kNumTrackingLayers> cluster_pairs;
  // Preset Value
  int charge;
  TVector3 init_pos;
  TVector3 init_mom;
  std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> sigma;
  // raugh fit chi square (tmp?)
  std::array<double, 3> x_coef;
  double x_chi_square;
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
    TVector3 mom_minus;
    TVector3 mom_plus;
    void Clear() {
      cand_minus = nullptr;
      cand_plus = nullptr;
      vtx = E16DST_DST1Constant::kInvalidVector;
    }
  };
  E16ANA_TrackCandidates(E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map, E16ANA_MultiTrack* _fitter, E16DST_DST1PhysicsRecord* _record)
      : geometry(_geometry), bfield_map(_bfield_map), fitter(_fitter),
        is_used_layer({true, true, true, true}), vertex_xy_fix_flag(false), py_fix_flag(false), vertex_z_fix_flag(true), record(_record) {
  track_candidates.clear();
  }
  ~E16ANA_TrackCandidates() {}
  void SetIsUseLayer(int n, bool _is_used) { is_used_layer[n] = _is_used; }
  void SetFlags(bool _vertex_xy_fix_flag, bool _py_fix_flag, bool _vertex_z_fix_flag) {
    vertex_xy_fix_flag = _vertex_xy_fix_flag;
    py_fix_flag = _py_fix_flag;
    vertex_z_fix_flag = _vertex_z_fix_flag;
  }
  bool IsUsedLayer(int n) { return is_used_layer[n]; }
  bool VertexXYFixFlag() { return vertex_xy_fix_flag; }
  bool PyFixFlag() { return py_fix_flag; }
  bool VertexZFixFlag() { return vertex_z_fix_flag; }
  double GTRTimeDiffThreshold(int n) { return kGTRTimeDiffThreshold[n]; }
  double XSigma(int n) { return kXSigma[n]; }
  double XWeight(int n) { return kXWeight[n]; }
  double YSigma(int n) { return kYSigma[n]; }
  double YWeight(int n) { return kYWeight[n]; }
  int MinHitsInXCluster() { return kMinHitsInXCluster; }
  double GTRYDiffThreshold() { return kGTRYDiffThreshold; }
  double GTRPeakSumThresholdX(int n) { return kGTRPeakSumThresholdX[n]; }
  double GTRPeakSumThresholdY() { return kGTRPeakSumThresholdY; }
  double RaughFitChiSquareThreshold(int n) { return kRaughFitChiSquareThreshold[n]; }
  double RaughXFitCoefficientThreshold(int n) { return kRaughXFitCoefficientThreshold[n]; }
  double RaughYFitCoefficientThreshold(int n) { return kRaughYFitCoefficientThreshold[n]; }
  double HBDProjectionThreshold() { return kHBDProjectionThreshold; }
  double LGProjectionThreshold() { return kLGProjectionThreshold; }
  double VertexSquareThreshold() { return kVertexSquareThreshold; }
  double StepTrackStepSizeCm() { return kStepTrackStepSizeCm; }
  int StepTrackArraySize() { return kStepTrackArraySize; }
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
  void PrintParam() {
    std::cout << "GTR Time Difference Threshold :" << std::endl;
    std::cout << "  GTR100 : " << kGTRTimeDiffThreshold[0] << ", GTR200 : " << kGTRTimeDiffThreshold[1] << ", GTR300 : " << kGTRTimeDiffThreshold[2] << std::endl;
    std::cout << "Sigma at X Rough Fit :" << std::endl;
    std::cout << "  Target : " << kXSigma[0] << ", SSD : " << kXSigma[1] << ", GTR100 : " << kXSigma[2] << ", GTR200 : " << kXSigma[3] << ", GTR300 : " << kXSigma[4] << std::endl;
    std::cout << "Sigma at Y Rough Fit :" << std::endl;
    std::cout << "  GTR100 : " << kYSigma[0] << ", GTR200 : " << kYSigma[2] << ", GTR300 : " << kYSigma[2] << std::endl;
    std::cout << "Minimum Hits in X Cluster : " << kMinHitsInXCluster << std::endl;
    std::cout << "GTR Position Difference Threshold between Layers at Y Candidate Search : " << kGTRYDiffThreshold << std::endl;
    std::cout << "GTR X ADC Peak Sum Threshold :" << std::endl;
    std::cout << "  GTR100 : " << kGTRPeakSumThresholdX[0] << ", GTR200 : " << kGTRPeakSumThresholdX[1] << ", GTR300 : " << kGTRPeakSumThresholdX[2] << std::endl;
    std::cout << "GTR Y ADC Peak Sum Threshold : " << kGTRPeakSumThresholdY << std::endl;
    std::cout << "Raugh Fit Chi Square Threshold :" << std::endl;
    std::cout << "  X : " << kRaughFitChiSquareThreshold[0] << ", Y : " << kRaughFitChiSquareThreshold[1] << std::endl;
    std::cout << "X Raugh Fit Coefficient Threshold : " 
              << kRaughXFitCoefficientThreshold[0] << ", " << kRaughXFitCoefficientThreshold[1] << kRaughXFitCoefficientThreshold[2] << std::endl;
    std::cout << "Y Raugh Fit Coefficient Threshold : " << kRaughYFitCoefficientThreshold[0] << ", " << kRaughYFitCoefficientThreshold[1] << std::endl;
    std::cout << "HBD Projection Threshold : " << kHBDProjectionThreshold << std::endl;
    std::cout << "LG  Projection Threshold : " << kLGProjectionThreshold << std::endl;
    std::cout << "Vertex Threshold (square) : " << kVertexSquareThreshold << std::endl;
    std::cout << "E16ANA_StepTrack Step Size [cm] : " << kStepTrackStepSizeCm << std::endl;
    std::cout << "E16ANA_StepTrack Array Size : " << kStepTrackArraySize << std::endl;
  }
 private:
  struct OneAxisClusterSet {
    int target_id; // only x
    int charge; // only x
    double chi_square;
    std::array<double, 3> coefs;
    std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> global_poss;
//    std::array<double, E16ANA_TrackConstant::kNumTrackingLayers> timings;
    E16DST_DST1SSDCluster* ssd_cluster;
//    std::array<E16DST_DST1GTRCluster*, kNumGTRLayers> gtr_clusters;
    std::array<E16DST_DST1GTRCluster*, 3> gtr_clusters;
  };
  static constexpr int kNumTrackingLayersWTarget = 1 + E16ANA_TrackConstant::kNumTrackingLayers;
  static constexpr int kNumGTRLayers = E16ANA_TrackConstant::kNumTrackingLayers - 1;
  static constexpr std::array<int, 2> kNumRaughFitDegree = {3, 2}; // x, y
  static constexpr std::array<double, kNumGTRLayers> kGTRSizeCoef = {2.7, 1.4, 1.};
  static constexpr std::array<int, 3> kNumReserveTracks = {1000, 1000, 100};
//  static constexpr int kMaxOneAxisCandidates = 100;
  // parameter
//  static constexpr std::array<double, kNumGTRLayers> kGTRTimeDiffThreshold = {40., 40., 40.};
  static constexpr std::array<double, kNumGTRLayers> kGTRTimeDiffThreshold = {40., 80., 120.}; // ozawa v8
//  static constexpr const std::array<double, kNumTrackingLayersWTarget> kXSigma = {5., 0.05, 0.1, 0.1, 0.1};
  static constexpr const std::array<double, kNumTrackingLayersWTarget> kXSigma = {20., 0.05, 0.1, 0.1, 0.1};
  static constexpr std::array<double, kNumTrackingLayersWTarget> kXWeight = {1. / (kXSigma[0] * kXSigma[0]),
                                                                             1. / (kXSigma[1] * kXSigma[1]),
                                                                             1. / (kXSigma[2] * kXSigma[2]),
                                                                             1. / (kXSigma[3] * kXSigma[3]),
                                                                             1. / (kXSigma[4] * kXSigma[4])};
  static constexpr std::array<double, kNumGTRLayers> kYSigma = {1., 1., 1.};
  static constexpr std::array<double, kNumGTRLayers> kYWeight = {1. / (kYSigma[0] * kYSigma[0]),
                                                                 1. / (kYSigma[1] * kYSigma[1]),
                                                                 1. / (kYSigma[2] * kYSigma[2])};
  static constexpr int kMinHitsInXCluster = 2;
  static constexpr double kGTRYDiffThreshold = 20.; // mm
//  static constexpr double kGTRPeakSumThresholdX = 180.;
  static constexpr std::array<double, kNumGTRLayers> kGTRPeakSumThresholdX = {80., 150., 250.};
  static constexpr double kGTRPeakSumThresholdY = 10.;
  static constexpr std::array<double, 2> kRaughFitChiSquareThreshold = {50., 10.}; // x, y
//  static constexpr std::array<double, 2> kRaughFitChiSquareThreshold = {1000., 10.}; // x, y. ozawa v8
//  static constexpr std::array<double, kNumRaughFitDegree[0]> kRaughXFitCoefficientThreshold = {10., 0., 0.001}; // coef[1] not used
  static constexpr std::array<double, kNumRaughFitDegree[0]> kRaughXFitCoefficientThreshold = {25., 0., 0.001}; // coef[1] not used. ozawa v8
  static constexpr std::array<double, kNumRaughFitDegree[1]> kRaughYFitCoefficientThreshold = {15., 0.}; // coef[1] not used.
//  static constexpr double kHBDProjectionThreshold = 20.;
  static constexpr double kHBDProjectionThreshold = 40.;
  static constexpr double kLGProjectionThreshold = 100.; // 98.
  static constexpr double kVertexSquareThreshold = 5. * 5.;
  static constexpr double kStepTrackStepSizeCm = 0.1; // cm
  static constexpr int kStepTrackArraySize = 1000; // 0.1 cm x 1000 = 1 m

  static bool IsLModule(int module_id) { return module_id > 105 ? true : false; }
  static bool IsCurveCorrelation(double tgt_z, const std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers>& pos_set);
  static TVector3 Lotate(double rot_cos, double rot_sin, double offset, const TVector3& pos) {
    auto x = rot_cos * pos.X() - rot_sin * (pos.Z() - offset);
    auto z = rot_sin * pos.X() + rot_cos * (pos.Z() - offset);
    return TVector3(x, 0, z);
  }
  static void CalcLotatedPos(std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers>& pos, double tgt_z, double rot_cos, double rot_sin, std::array<TVector3, kNumTrackingLayersWTarget>* lotated_pos);
  static void AddMatrixElement(double w, const TVector3& lotated_pos, std::array<double, kNumTrackingLayersWTarget>* zz, std::array<double, kNumRaughFitDegree[0]>* zx) {
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
                            std::array<double, kNumRaughFitDegree[0]>* zx,
                            std::array<double, kNumRaughFitDegree[0]>* coef);
  static void CalcInverseMatrix(const std::array<double, 1 + E16ANA_TrackConstant::kNumTrackingLayers>& zz, std::array<std::array<double, kNumRaughFitDegree[0]>, kNumRaughFitDegree[0]>* line);
  static void CalcCoefficients(const std::array<double, kNumRaughFitDegree[0]>& zx,
                               const std::array<std::array<double, kNumRaughFitDegree[0]>, kNumRaughFitDegree[0]>& line,
                               std::array<double, kNumRaughFitDegree[0]>* coef) {
    (*coef)[0] = line[2][0] * zx[2] + line[2][1] * zx[1] + line[2][2] * zx[0];
    (*coef)[1] = line[1][0] * zx[2] + line[1][1] * zx[1] + line[1][2] * zx[0];
    (*coef)[2] = line[0][0] * zx[2] + line[0][1] * zx[1] + line[0][2] * zx[0];
    return;
  }
//  static void CalcTargetX();
//  static void CalcTargetZ();
//  static void CalcChiSquare();
  static bool IsXTrackCandidate(OneAxisClusterSet* cluster_set);
  static bool IsYTrackCandidate(OneAxisClusterSet* cluster_set);
  static bool ExistADCCorrelation(float x_adc, float y_adc) {
    if (y_adc < 0.74 * x_adc + 600. && (y_adc > 0.74 * x_adc - 600. || y_adc > 1200.)) {
      return true;
    }
    return false;
  }
  void SearchTrackCandidates();
  void Fit();
  void SearchHBDAndLGHits();
  void SortTracks();
  void ProjectionTarget();
  double SearchVertex(TrackPair* track_pair);
  void SelectTrackPairs();
  void MakeTrackPairs();
  void AddTracksToRecord();
  E16ANA_GeometryV2* geometry;
  E16ANA_MagneticFieldMap* bfield_map;
  E16ANA_MultiTrack* fitter;
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
//  int most_likely_target_id;
};

#endif // E16ANA_TRACKCANDIDATE_HH
