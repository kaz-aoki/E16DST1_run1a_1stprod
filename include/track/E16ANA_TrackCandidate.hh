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
#include "E16DST_DST1.hh"

//class E16ANA_TrackAnalyzedHit {
// public:
//  E16ANA_TrackAnalyzedHit() {}
//  ~E16ANA_TrackAnalyzedHit() {}
// protected:
//  E16ANA_GeometryV2* geom;
//  int layer_order;
//  int module_id;
//  TVector3 local_pos;
//  TVector3 local_mom;
//  TVector3 global_pos;
//  TVector3 global_mom;
//};

class E16ANA_TrackClusterPair {
 public:
  E16ANA_TrackClusterPair() {}
  E16ANA_TrackClusterPair(E16ANA_DetectorGeometry* _geom)
      : set_flag(0),
        layer_order(E16DST_DST1Constant::kInvalidValue), module_id(E16DST_DST1Constant::kInvalidValue),
        geom(_geom),
        clusters({nullptr, nullptr}),
        local_pos({E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue}) {}
  ~E16ANA_TrackClusterPair() {}
  void Set(E16ANA_GeometryV2& geometry, int _layer_order, int _module_id, E16DST_DST1Cluster* x_cluster) { // SSD
    set_flag = 1;
    layer_order = _layer_order;
    module_id = _module_id;
    clusters[0] = x_cluster;
    clusters[1] = nullptr;
    local_pos = {dynamic_cast<E16DST_DST1SSDCluster*>(x_cluster)->LocalPos().X(), 0., 0.}; // z = 0?
  }
  void Set(E16ANA_GeometryV2& geometry, int _layer_order, int _module_id, E16DST_DST1Cluster* x_cluster, E16DST_DST1Cluster* y_cluster) { // GTR
    set_flag = 1;
    layer_order = _layer_order;
    module_id = _module_id;
    clusters[0] = x_cluster;
    clusters[1] = y_cluster;
    local_pos = {dynamic_cast<E16DST_DST1GTRCluster*>(x_cluster)->LocalPos().X(), dynamic_cast<E16DST_DST1GTRCluster*>(y_cluster)->LocalPos().Y(), 0.}; // z = 0?
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
  E16ANA_DetectorGeometry* Geometry() { return geom; }
  E16DST_DST1Cluster* Cluster(int type) { return clusters[type]; }
  TVector3 LocalPos() { return local_pos; }
  TVector3 GlobalPos() { return geom->GetGPos(local_pos); }
 private:
  int set_flag;
  int layer_order; // all detector (layer_id: only GTR in E16ANA_MultiTrack)
  int module_id;
  E16ANA_DetectorGeometry* geom;
  std::array<E16DST_DST1Cluster*, 2> clusters; // x, y
  TVector3 local_pos;
};

class E16ANA_TrackCandidate {
 public:
  struct FitResult {
    int set_flag;
    int layer_order;
    int module_id;
//    int block_id; // only LG
    TVector3 local_pos;
    TVector3 local_mom;
    TVector3 global_pos;
    TVector3 global_mom;
//    TVector3 local_sigma;
    TVector3 residual_pos;
    void Clear() {
      set_flag = 0;
      layer_order = -1;
      module_id = -1;
//      block_id = -1;
      local_pos = E16DST_DST1Constant::kInvalidVector;
      local_mom = E16DST_DST1Constant::kInvalidVector;
      residual_pos = E16DST_DST1Constant::kInvalidVector;
    }
  };
  E16ANA_TrackCandidate(E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map, const std::array<std::array<E16ANA_DetectorGeometry*, E16ANA_TrackConstant::kNumModules>, 2> _tmp_geoms)
      : geometry(_geometry), bfield_map(_bfield_map),
        tmp_geoms(_tmp_geoms) {}
//        tmp_geoms({{_geometry->HBD(ModuleID2020To2013_27(101)),
//                    _geometry->HBD(ModuleID2020To2013_27(102)),
//                    _geometry->HBD(ModuleID2020To2013_27(103)),
//                    _geometry->HBD(ModuleID2020To2013_27(104)),
//                    _geometry->HBD(ModuleID2020To2013_27(106)),
//                    _geometry->HBD(ModuleID2020To2013_27(107)),
//                    _geometry->HBD(ModuleID2020To2013_27(108)),
//                    _geometry->HBD(ModuleID2020To2013_27(109))},
//                   {_geometry->LGVD(ModuleID2020To2013_27(101)),
//                    _geometry->LGVD(ModuleID2020To2013_27(102)),
//                    _geometry->LGVD(ModuleID2020To2013_27(103)),
//                    _geometry->LGVD(ModuleID2020To2013_27(104)),
//                    _geometry->LGVD(ModuleID2020To2013_27(106)),
//                    _geometry->LGVD(ModuleID2020To2013_27(107)),
//                    _geometry->LGVD(ModuleID2020To2013_27(108)),
//                    _geometry->LGVD(ModuleID2020To2013_27(109))}}) {}
  E16ANA_TrackCandidate& operator = (const E16ANA_TrackCandidate& rhs) {
    Copy(rhs);
    return (*this);
  }
  ~E16ANA_TrackCandidate() {}
  void SetTrackID(int _track_id) { track_id = _track_id; }
  void SetCharge(double _charge) { charge = _charge; }
  void SetVertex(int _target_id) {
    target_id = _target_id;
    if (target_id == 0) {
      vtx = {0., 0., -20.};
    } else if (target_id == 1) {
      vtx = {0., 0., 0.};
    } else if (target_id == 2) {
      vtx = {0., 0., 20.};
    } else {
      std::cerr << "Invalid target ID (0 - 2): " << target_id << std::endl;
      std::exit(1);
    }
  }
  void SetSigma(int layer_index, TVector3 _sigma) { sigma[layer_index] = _sigma; }
  void SetDefaultSigma();
  int TrackID() { return track_id; }
  double Charge() { return charge; }
  TVector3 Vertex() { return vtx; }
  TVector3 Sigma(int n) { return sigma[n]; }
  TVector3 FitVertex() { return vtx_fit; }
  TVector3 FitMomntum() { return mom_fit; }
  TVector3 FitSigma() { return vtx_sigma; }
  const FitResult& LocalFitResult(int n) const { return fit_results[n]; }
  double ChiSquare() { return chisq; }
  E16ANA_TrackClusterPair& ClusterPair(int layer_index) { return cluster_pairs[layer_index]; }
  std::array<E16ANA_TrackClusterPair, E16ANA_TrackConstant::kNumTrackingLayers>& ClusterPairs() { return cluster_pairs; }
  std::vector<E16DST_DST1HBDHit*>& ProjectionHBDHits() { return hbd_hits; }
  std::vector<E16DST_DST1HBDCluster*>& ProjectionHBDClusters() { return hbd_clusters; }
  std::vector<E16DST_DST1LGHit*>& ProjectionLGHits() { return lg_hits; }
  std::vector<E16DST_DST1LGCluster*>& ProjectionLGClusters() { return lg_clusters; }
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
  void SetSingleTrackFit(E16ANA_MultiTrack* single_track, int _track_id);
  void UpdateFitResult(E16ANA_MultiTrack* fitter);
  double Fit(E16ANA_MultiTrack* fitter, bool vertex_fix_flag, bool py_fix_flag);
  void ProjectionLG(E16ANA_MultiTrack* fitter);
 private:
  void Copy(const E16ANA_TrackCandidate& rhs) {
    this->geometry = rhs.geometry;
    this->bfield_map = rhs.bfield_map;
    this->track_id = rhs.track_id;
    this->target_id = rhs.target_id;
    this->cluster_pairs = rhs.cluster_pairs;
    this->charge = rhs.charge;
    this->vtx = rhs.vtx;
    this->mom = rhs.mom;
    this->sigma = rhs.sigma;
    this->vtx_fit = rhs.vtx_fit;
    this->mom_fit = rhs.mom_fit;
    this->vtx_sigma = rhs.vtx_sigma;
    this->fit_results = rhs.fit_results;
    this->chisq = rhs.chisq;
    this->hbd_hits = rhs.hbd_hits;
    this->hbd_clusters = rhs.hbd_clusters;
    this->lg_hits = rhs.lg_hits;
    this->lg_clusters = rhs.lg_clusters;
  }
  static int ModuleID2020To2013(int _module_id) { return E16ANA_TrackConstant::kModuleID2020To2013[_module_id / 100][_module_id % 100]; }
  static int ModuleID2013To2020(int _module_id);
  static int ModuleID2020To2013_27(int _module_id) { return E16ANA_TrackConstant::kModuleID2020To2013[_module_id / 100][_module_id % 100 + 1]; }
  static int ModuleID2013To2020_27(int _module_id);
  E16ANA_GeometryV2* geometry;
  E16ANA_MagneticFieldMap* bfield_map;
  int track_id;
  int target_id; // <-> vtx
  std::array<E16ANA_TrackClusterPair, E16ANA_TrackConstant::kNumTrackingLayers> cluster_pairs;
  // Preset Value
  double charge;
  TVector3 vtx;
  TVector3 mom;
  std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> sigma;
  // Fit Result
  TVector3 vtx_fit;
  TVector3 mom_fit; // each cluster?
  TVector3 vtx_sigma;
  std::array<FitResult, E16ANA_TrackConstant::kNumDetectorLayers> fit_results;
  double chisq;
  const std::array<std::array<E16ANA_DetectorGeometry*, E16ANA_TrackConstant::kNumModules>, E16ANA_TrackConstant::kNumRemainingLayers> tmp_geoms;
  std::vector<E16DST_DST1HBDHit*> hbd_hits;
  std::vector<E16DST_DST1HBDCluster*> hbd_clusters;
  std::vector<E16DST_DST1LGHit*> lg_hits;
  std::vector<E16DST_DST1LGCluster*> lg_clusters;
};

class E16ANA_TrackCandidates {
 public:
//  E16ANA_TrackCandidates(E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map, E16DST_DST1PhysicsRecord* _record)
//      : geometry(_geometry), bfield_map(_bfield_map), record(_record) {}
  E16ANA_TrackCandidates(E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map,
                         std::array<std::array<E16ANA_DetectorGeometry*, E16ANA_TrackConstant::kNumModules>, E16ANA_TrackConstant::kNumRemainingLayers> _tmp_geoms,
                         E16DST_DST1PhysicsRecord* _record)
      : geometry(_geometry), bfield_map(_bfield_map), tmp_geoms(_tmp_geoms), record(_record) {}
  ~E16ANA_TrackCandidates() {}
  int NumTrackCandidates() { return track_candidates.size(); }
  void SelectTracks();
 private:
  struct OneAxisClusterSet {
    int target_id;
    int charge;
    E16DST_DST1SSDCluster* ssd_cluster;
    std::array<E16DST_DST1GTRCluster*, 3> gtr_clusters;
  };
  static constexpr int kNumTrackingLayersWTarget = 1 + E16ANA_TrackConstant::kNumTrackingLayers;
  static constexpr int kNumGTRLayers = E16ANA_TrackConstant::kNumTrackingLayers - 1;
  static constexpr double kGTRTimeDiffThreshold = 40.;
  static constexpr double kLGResidualThreshold = 100.;
  static constexpr const std::array<double, kNumTrackingLayersWTarget> kXSigma = {5., 0.05, 0.1, 0.1, 0.1};
  static constexpr std::array<double, kNumTrackingLayersWTarget> kXWeight = {1. / (kXSigma[0] * kXSigma[0]),
                                                                             1. / (kXSigma[1] * kXSigma[1]),
                                                                             1. / (kXSigma[2] * kXSigma[2]),
                                                                             1. / (kXSigma[3] * kXSigma[3]),
                                                                             1. / (kXSigma[4] * kXSigma[4])};
  static constexpr std::array<double, kNumGTRLayers> kYSigma = {1., 1., 1.};
  static constexpr std::array<double, kNumGTRLayers> kYWeight = {1. / (kYSigma[0] * kYSigma[0]),
                                                                 1. / (kYSigma[1] * kYSigma[1]),
                                                                 1. / (kYSigma[2]  * kYSigma[2])};
  static constexpr int kNumRaughFitDegree = 3;
  static constexpr std::array<double, 2> kRaughFitChiSquareThreshold = {100., 10.};
  static constexpr std::array<int, 3> kNumReserveTracks = {1000, 1000, 100};
  static TVector3 Lotate(double rot_cos, double rot_sin, const TVector3& pos) {
    auto x =  rot_cos * pos.Z() + rot_sin * pos.X();
    auto z = -rot_sin * pos.Z() + rot_cos * pos.X();
    return TVector3(x, 0, z);
  }
  static void AddMatrixElement(double w, const TVector3& lotated_pos, std::array<double, kNumTrackingLayersWTarget>* zz, std::array<double, kNumTrackingLayersWTarget>* zx) {
    auto x = lotated_pos.X();
    auto z = lotated_pos.Z();
    zz->at(4) += w * z * z * z * z;
    zz->at(3) += w * z * z * z;
    zz->at(2) += w * z * z;
    zz->at(1) += w * z;
    zz->at(0) += w;
    zx->at(2) += w * x * z * z;
    zx->at(1) += w * x * z;
    zx->at(0) += w * x;
    return;
  }
  static void CalcInverseMatrix(const std::array<double, 1 + E16ANA_TrackConstant::kNumTrackingLayers>& zz, std::array<std::array<double, kNumRaughFitDegree>, kNumRaughFitDegree>* line);
  static void CalcCoefficients(const std::array<double, kNumTrackingLayersWTarget>& zx,
                               const std::array<std::array<double, kNumRaughFitDegree>, kNumRaughFitDegree>& line,
                               std::array<double, kNumRaughFitDegree>* corr) {
    corr->at(0) = line[2][0] * zx[2] + line[2][1] * zx[1] + line[2][2] * zx[0];
    corr->at(1) = line[1][0] * zx[2] + line[1][1] * zx[1] + line[1][2] * zx[0];
    corr->at(2) = line[0][0] * zx[2] + line[0][1] * zx[1] + line[0][2] * zx[0];
    return;
  }
//  static bool IsXTrackCandidate(double tgt_z, const std::array<TVector3*, E16ANA_TrackConstant::kNumTrackingLayers>& pos_set);
  bool IsXTrackCandidate(OneAxisClusterSet* cluster_set);
  bool IsYTrackCandidate(const OneAxisClusterSet& cluster_set);
  void SetTrackCandidates();
  void RequireLGCut();
  int SelectTargetID();
  E16ANA_GeometryV2* geometry;
  E16ANA_MagneticFieldMap* bfield_map;
  const std::array<std::array<E16ANA_DetectorGeometry*, E16ANA_TrackConstant::kNumModules>, E16ANA_TrackConstant::kNumRemainingLayers> tmp_geoms;
  E16DST_DST1PhysicsRecord* record;
  std::array<std::vector<E16ANA_TrackCandidate>, E16ANA_TrackConstant::kNumTargets> track_candidates;
  int most_likely_target_id;
  std::array<std::vector<E16ANA_TrackCandidate>, E16ANA_TrackConstant::kNumTargets> selected_track_candidates;
};

#endif // E16ANA_TRACKCANDIDATE_HH
