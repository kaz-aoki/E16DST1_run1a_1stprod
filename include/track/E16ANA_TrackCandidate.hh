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
  E16ANA_TrackClusterPair(E16ANA_DetectorGeometry* _geom)
      : set_flag(0),
        layer_order(E16DST_DST1Constant::kInvalidValue), module_id(E16DST_DST1Constant::kInvalidValue),
        geom(_geom),
        clusters({nullptr, nullptr}),
        local_pos({E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue}) {}
  ~E16ANA_TrackClusterPair() {}
  void Set(E16ANA_GeometryV2& geometry, int _layer_order, int _module_id, E16DST_DST1Cluster* x_cluster, E16DST_DST1Cluster* y_cluster) {
    set_flag = 1;
    layer_order = _layer_order;
    module_id = _module_id;
    clusters[0] = x_cluster;
    clusters[1] = y_cluster;
    if (layer_order == E16DST_DST1Constant::kSSD) {
      local_pos = {dynamic_cast<E16DST_DST1SSDCluster*>(x_cluster)->LocalPos().X(), 0., 0.}; // z = 0?
    } else if (layer_order == E16DST_DST1Constant::kGTR) {
      local_pos = {dynamic_cast<E16DST_DST1GTRCluster*>(x_cluster)->LocalPos().X(), dynamic_cast<E16DST_DST1GTRCluster*>(y_cluster)->LocalPos().Y(), 0.}; // z = 0?
    }
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
  E16ANA_TrackCandidate(E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map)
      : geometry(_geometry), bfield_map(_bfield_map),
        cluster_pairs({nullptr, nullptr, nullptr, nullptr}),
        tmp_geoms({{_geometry->HBD(ModuleID2020To2013_27(101)),
                    _geometry->HBD(ModuleID2020To2013_27(102)),
                    _geometry->HBD(ModuleID2020To2013_27(103)),
                    _geometry->HBD(ModuleID2020To2013_27(104)),
                    _geometry->HBD(ModuleID2020To2013_27(106)),
                    _geometry->HBD(ModuleID2020To2013_27(107)),
                    _geometry->HBD(ModuleID2020To2013_27(108)),
                    _geometry->HBD(ModuleID2020To2013_27(109))},
                   {_geometry->LGVD(ModuleID2020To2013_27(101)),
                    _geometry->LGVD(ModuleID2020To2013_27(102)),
                    _geometry->LGVD(ModuleID2020To2013_27(103)),
                    _geometry->LGVD(ModuleID2020To2013_27(104)),
                    _geometry->LGVD(ModuleID2020To2013_27(106)),
                    _geometry->LGVD(ModuleID2020To2013_27(107)),
                    _geometry->LGVD(ModuleID2020To2013_27(108)),
                    _geometry->LGVD(ModuleID2020To2013_27(109))}}) {}
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
      vtx = {0., 0., -20.};
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
  enum {
    kNumLayers = 4,
    kNumDetectorLayers = 6
  };
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
  const std::array<std::array<E16ANA_DetectorGeometry*, 8>, 2> tmp_geoms;
  std::vector<E16DST_DST1HBDHit*> hbd_hits;
  std::vector<E16DST_DST1HBDCluster*> hbd_clusters;
  std::vector<E16DST_DST1LGHit*> lg_hits;
  std::vector<E16DST_DST1LGCluster*> lg_clusters;
};

class E16ANA_TrackCandidates {
 public:
  E16ANA_TrackCandidates();
  ~E16ANA_TrackCandidates();
  int NumTrackCandidates() { return track_candidates.size(); }
  void SetTrackCandidates(); // ozawa cut
  void RequireLGCut();
  void SelectTracks();
 private:
  int SelectTargetID();
  enum { kNumTargets = 3 };
  static constexpr double lg_residual_threshold = 100.;
  E16ANA_GeometryV2* geometry;
  E16ANA_MagneticFieldMap* bfield_map;
  E16DST_DST1PhysicsRecord* record;
  std::array<std::vector<E16ANA_TrackCandidate>, E16ANA_TrackConstant::kNumTargets> track_candidates;
  int most_likely_target_id;
  std::array<std::vector<E16ANA_TrackCandidate>, E16ANA_TrackConstant::kNumTargets> selected_track_candidates;
};

#endif // E16ANA_TRACKCANDIDATE_HH
