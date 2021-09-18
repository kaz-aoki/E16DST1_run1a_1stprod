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

#include "TFile.h"
#include "TGraph.h"
#include "TH1.h"
#include "TTree.h"

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
  E16ANA_TrackClusterPair()
      : set_flag(0),
        layer_order(E16DST_DST1Constant::kInvalidValue), module_id(E16DST_DST1Constant::kInvalidValue),
        clusters({nullptr, nullptr}),
        local_pos(E16DST_DST1Constant::kInvalidVector) {}
  ~E16ANA_TrackClusterPair() {}
  void Set(const E16ANA_GeometryV2* _geometry, int _layer_order, int _module_id, E16DST_DST1Cluster* x_cluster) { // SSD
    set_flag = 1;
    layer_order = _layer_order;
    module_id = _module_id;
    clusters[0] = x_cluster;
    clusters[1] = nullptr;
    local_pos = {dynamic_cast<E16DST_DST1SSDCluster*>(x_cluster)->LocalPos().X(), 0., 0.}; // z = 0?
    global_pos = _geometry->SSD(E16ANA_TrackConstant::ModuleID2020To2013(module_id))->GetGPos(local_pos);
  }
  void Set(const E16ANA_GeometryV2* _geometry, int _layer_order, int _module_id, E16DST_DST1Cluster* x_cluster, E16DST_DST1Cluster* y_cluster) { // GTR
    set_flag = 1;
    layer_order = _layer_order;
    module_id = _module_id;
    clusters[0] = x_cluster;
    clusters[1] = y_cluster;
    local_pos = {dynamic_cast<E16DST_DST1GTRCluster*>(x_cluster)->LocalPos().X(), dynamic_cast<E16DST_DST1GTRCluster*>(y_cluster)->LocalPos().Y(), 0.}; // z = 0?
    global_pos = _geometry->GTR(E16ANA_TrackConstant::ModuleID2020To2013(module_id), layer_order - 1)->GetGPos(local_pos);
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
  int layer_order; // all detector (layer_id: only GTR in E16ANA_MultiTrack)
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
//  E16ANA_TrackCandidate(E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map, const std::array<std::array<E16ANA_DetectorGeometry*, E16ANA_TrackConstant::kNumModules>, 2> _tmp_geoms)
  E16ANA_TrackCandidate(E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map)
      : geometry(_geometry), bfield_map(_bfield_map) {}
//        tmp_geoms(_tmp_geoms) {}
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
  void SetDefaultSigma() {
    for (auto& s : sigma) {
      s = kSigma;
    }
    sigma[0].SetY(0.);
sigma[0].SetX(0.);
  }
  int TrackID() { return track_id; }
  int TargetID() { return target_id; }
  double Charge() { return charge; }
  TVector3 Vertex() { return vtx; }
  TVector3 Momentum() { return mom; }
  TVector3 Sigma(int n) { return sigma[n]; }
  TVector3 FitVertex() { return vtx_fit; }
  TVector3 FitMomentum() { return mom_fit; }
  TVector3 FitSigma() { return vtx_sigma; }
  const FitResult& LocalFitResult(int n) const { return fit_results[n]; }
  const std::array<FitResult, E16ANA_TrackConstant::kNumDetectorLayers> LocalFitResults() const { return fit_results; }
  double ChiSquare() { return chisq; }
  int MinimizeStatus() { return minimize_status; }
  int MatrixStatus() { return matrix_status; }
  int ProjectionFlag() { return projection_flag; }
  E16ANA_TrackClusterPair& ClusterPair(int layer_index) { return cluster_pairs[layer_index]; }
  std::array<E16ANA_TrackClusterPair, E16ANA_TrackConstant::kNumTrackingLayers>& ClusterPairs() { return cluster_pairs; }
  std::vector<E16DST_DST1HBDHit*>& ProjectedHBDHits() { return hbd_hits; }
  std::vector<E16DST_DST1HBDCluster*>& ProjectedHBDClusters() { return hbd_clusters; }
  std::vector<E16DST_DST1LGHit*>& ProjectedLGHits() { return lg_hits; }
  std::vector<E16DST_DST1LGCluster*>& ProjectedLGClusters() { return lg_clusters; }
  double Fit(E16ANA_MultiTrack* fitter, bool vertex_fix_flag, bool py_fix_flag);
  void Print() {
if (chisq >= 1.0e10) {
  return;
}
    std::cout << "Track ID: " << track_id << ", Target ID: " << target_id << ", Charge: " << charge << std::endl;
    std::cout << "Chi Square: " << chisq << ", Minimize Status: " << minimize_status << ", Matrix Status: " << matrix_status << std::endl;
    std::cout << "  Vertex Position: (" << vtx_fit.X() << ", " << vtx_fit.Y() << ", " << vtx_fit.Z() << ")" << std::endl;
    std::cout << "  Vertex Momentum: (" << mom_fit.X() << ", " << mom_fit.Y() << ", " << mom_fit.Z() << ")" << std::endl;
    for (int l = 0; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l) {
      std::cout << "  Detector: " << E16ANA_TrackConstant::kDetectorName[l] << " (Layer ID: " << l << "), Module ID: " << fit_results[l].module_id << std::endl;
      auto fit_local_pos = fit_results[l].local_pos;
      auto fit_global_pos = fit_results[l].global_pos;
      if (l < E16ANA_TrackConstant::kNumTrackingLayers) {
        auto& pair = cluster_pairs[l];
        auto local_pos = pair.LocalPos();
        auto global_pos = pair.GlobalPos();
        std::cout << "    Local  Position (Hit): (" << local_pos.X()  << ", " << local_pos.Y()  << ", " << local_pos.Z()  << ")" << std::endl;
        std::cout << "    Global Position (Hit): (" << global_pos.X() << ", " << global_pos.Y() << ", " << global_pos.Z() << ")" << std::endl;
      }
      if (fit_results[l].set_flag == 1) {
        std::cout << "    Local  Position (Fit): (" << fit_local_pos.X()  << ", " << fit_local_pos.Y()  << ", " << fit_local_pos.Z()  << ")" << std::endl;
        std::cout << "    Global Position (Fit): (" << fit_global_pos.X() << ", " << fit_global_pos.Y() << ", " << fit_global_pos.Z() << ")" << std::endl;
      } else {
        std::cout << "    Runge Kutta Failure" << std::endl;
      }
    }
  }
 private:
  static constexpr int kRKPrintLevel = 1; // tmp
  static constexpr std::array<int, E16ANA_TrackConstant::kNumLGLayers> kTypicalLGBlocks = {0, 10, 20};
//  static constexpr std::array<std::vector<int>, E16ANA_TrackConstant::kNumLGLayers> kLGBlocks = {{{0,  1 , 2,  3,  4,  5,     50, 51, 52, 53, 54, 55},
//                                                                                                 {10, 11, 12, 13, 14, 15,     40, 41, 42, 43, 44, 45},
//                                                                                                 {20, 21, 22, 23, 24, 25, 26, 30, 31, 32, 33, 34, 35, 36}}};
  static inline const TVector3 kSigma = {800.0e-3, 5000.0e-3, 0.};
  static inline const TVector3 kVertexError = {1.5, 1.7, 20e-3};
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
  int minimize_status;
  int matrix_status;
  // projection
  int projection_flag; // bit0: HBD, 1: LG0, 2: LG1, 3: LG2
  std::vector<E16DST_DST1HBDHit*> hbd_hits;
  std::vector<E16DST_DST1HBDCluster*> hbd_clusters;
  std::vector<E16DST_DST1LGHit*> lg_hits;
  std::vector<E16DST_DST1LGCluster*> lg_clusters;
};

class E16ANA_TrackCandidates {
 public:
  E16ANA_TrackCandidates(E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map, E16ANA_MultiTrack* _fitter,
//                         std::array<std::array<E16ANA_DetectorGeometry*, E16ANA_TrackConstant::kNumModules>, E16ANA_TrackConstant::kNumRemainingLayers> _tmp_geoms,
                         E16DST_DST1PhysicsRecord* _record)
      : geometry(_geometry), bfield_map(_bfield_map), fitter(_fitter), vertex_fix_flag(false), py_fix_flag(false), record(_record) {}
  ~E16ANA_TrackCandidates() {}
  void SetFlags(bool _vertex_fox_flag, bool _py_fix_flag) {
    vertex_fix_flag = _vertex_fox_flag;
    py_fix_flag = _py_fix_flag;
  }
  bool VertexFixFlag() { return vertex_fix_flag; }
  bool PyFixFlag() { return py_fix_flag; }
  int NumTrackCandidates() {
    int n_cands = 0;
    for (int i = 0; i < E16ANA_TrackConstant::kNumTargets; ++i) {
      n_cands += track_candidates.size();
    }
    return n_cands;
  }
  int NumTrackCandidates(int n) { return track_candidates[n].size(); }
  std::vector<E16ANA_TrackCandidate>& TrackCandidates(int n) { return track_candidates[n]; }
  void SelectTracks();
  void Print() {
    for (auto& cands : track_candidates) {
      for (auto& cand : cands) {
        cand.Print();
      }
    }
    std::cout << "Number of track candidates: " << NumTrackCandidates() << std::endl;
  }
  void PrintSelected() {
    for (auto& cands : selected_track_candidates) {
      for (auto& cand : cands) {
        cand->Print();
      }
    }
  }
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
  static constexpr std::array<int, 2> kNumRaughFitDegree = {3, 2}; // x, y
  static constexpr double kRaughFitTargetXThreshold = 5.; // tmp
  static constexpr double kRaughFitTargetYThreshold = 15.; // tmp
  static constexpr std::array<double, 2> kRaughFitChiSquareThreshold = {100., 10.};
  static constexpr std::array<int, 3> kNumReserveTracks = {1000, 1000, 100};
  static constexpr double kHBDProjectionThreshold = 20.;
  static constexpr double kLGProjectionThreshold = 150.;
//  static constexpr double kLGResidualThreshold = 150.;
  static TVector3 Lotate(double rot_cos, double rot_sin, const TVector3& pos) {
    auto x =  rot_cos * pos.Z() + rot_sin * pos.X();
    auto z = -rot_sin * pos.Z() + rot_cos * pos.X();
    return TVector3(x, 0, z);
  }
  static void AddMatrixElement(double w, const TVector3& lotated_pos, std::array<double, kNumTrackingLayersWTarget>* zz, std::array<double, kNumRaughFitDegree[0]>* zx) {
    auto x = lotated_pos.X();
    auto z = lotated_pos.Z();
    zz->at(4) += w * z * z * z * z; // delete at
    zz->at(3) += w * z * z * z;
    zz->at(2) += w * z * z;
    zz->at(1) += w * z;
    zz->at(0) += w;
    zx->at(2) += w * x * z * z;
    zx->at(1) += w * x * z;
    zx->at(0) += w * x;
    return;
  }
  static void CalcInverseMatrix(const std::array<double, 1 + E16ANA_TrackConstant::kNumTrackingLayers>& zz, std::array<std::array<double, kNumRaughFitDegree[0]>, kNumRaughFitDegree[0]>* line);
  static void CalcCoefficients(const std::array<double, kNumTrackingLayersWTarget>& zx,
                               const std::array<std::array<double, kNumRaughFitDegree[0]>, kNumRaughFitDegree[0]>& line,
                               std::array<double, kNumRaughFitDegree[0]>* corr) {
    (*corr)[0] = line[2][0] * zx[2] + line[2][1] * zx[1] + line[2][2] * zx[0];
    (*corr)[1] = line[1][0] * zx[2] + line[1][1] * zx[1] + line[1][2] * zx[0];
    (*corr)[2] = line[0][0] * zx[2] + line[0][1] * zx[1] + line[0][2] * zx[0];
    return;
  }
  bool IsXTrackCandidate(OneAxisClusterSet* cluster_set);
  bool IsYTrackCandidate(const OneAxisClusterSet& cluster_set);
  void SearchTrackCandidates();
  void Fit();
  void SearchHBDAndLGHits();
  void AddTracksToRecord();
  E16ANA_GeometryV2* geometry;
  E16ANA_MagneticFieldMap* bfield_map;
  E16ANA_MultiTrack* fitter;
  bool vertex_fix_flag;
  bool py_fix_flag;
  E16DST_DST1PhysicsRecord* record;
  std::array<std::vector<E16ANA_TrackCandidate>, E16ANA_TrackConstant::kNumTargets> track_candidates;
  int most_likely_target_id;
  std::array<std::vector<E16ANA_TrackCandidate*>, E16ANA_TrackConstant::kNumTargets> selected_track_candidates;
};

class CheckFile {
 public:
  CheckFile(char* file_name = "~/tmp/tmp.root")
      : file(TFile(file_name, "recreate")) {
    tree = new TTree("tree", "tree");
    tree->Branch("event_id", &event_id, "event_id/I");
    tree->Branch("track_id", &track_id, "track_id/I");
    tree->Branch("chi_square", &chi_square, "chi_square/D");
    tree->Branch("vtx_gpos_hit", &vtx_gpos_hit);
    tree->Branch("ssd_module_id", &ssd_module_id), "ssd_module_id/I";
    tree->Branch("gtr1_module_id", &gtr1_module_id), "gtr1_module_id/I";
    tree->Branch("gtr2_module_id", &gtr2_module_id), "gtr2_module_id/I";
    tree->Branch("gtr3_module_id", &gtr3_module_id), "gtr3_module_id/I";
    tree->Branch("hbd_module_id", &hbd_module_id), "hbd_module_id/I";
    tree->Branch("lg0_module_id", &lg0_module_id), "lg0_module_id/I";
    tree->Branch("lg1_module_id", &lg1_module_id), "lg1_module_id/I";
    tree->Branch("lg2_module_id", &lg2_module_id), "lg2_module_id/I";
    tree->Branch("ssd_lpos_hit", &ssd_lpos_hit);
    tree->Branch("ssd_gpos_hit", &ssd_gpos_hit);
    tree->Branch("gtr1_lpos_hit", &gtr1_lpos_hit);
    tree->Branch("gtr1_gpos_hit", &gtr1_gpos_hit);
    tree->Branch("gtr2_lpos_hit", &gtr2_lpos_hit);
    tree->Branch("gtr2_gpos_hit", &gtr2_gpos_hit);
    tree->Branch("gtr3_lpos_hit", &gtr3_lpos_hit);
    tree->Branch("gtr3_gpos_hit", &gtr3_gpos_hit);
    tree->Branch("hbd_lpos_fit", &hbd_lpos_fit);
    tree->Branch("vtx_gpos_fit", &vtx_gpos_fit);
    tree->Branch("ssd_lpos_fit", &ssd_lpos_fit);
    tree->Branch("ssd_gpos_fit", &ssd_gpos_fit);
    tree->Branch("gtr1_lpos_fit", &gtr1_lpos_fit);
    tree->Branch("gtr1_gpos_fit", &gtr1_gpos_fit);
    tree->Branch("gtr2_lpos_fit", &gtr2_lpos_fit);
    tree->Branch("gtr2_gpos_fit", &gtr2_gpos_fit);
    tree->Branch("gtr3_lpos_fit", &gtr3_lpos_fit);
    tree->Branch("gtr3_gpos_fit", &gtr3_gpos_fit);
    tree->Branch("hbd_lpos_fit", &hbd_lpos_fit);
    tree->Branch("hbd_gpos_fit", &hbd_gpos_fit);
    tree->Branch("lg0_lpos_fit", &lg0_lpos_fit);
    tree->Branch("lg0_gpos_fit", &lg0_gpos_fit);
    tree->Branch("lg1_lpos_fit", &lg1_lpos_fit);
    tree->Branch("lg1_gpos_fit", &lg1_gpos_fit);
    tree->Branch("lg2_lpos_fit", &lg2_lpos_fit);
    tree->Branch("lg2_gpos_fit", &lg2_gpos_fit);
  };
  ~CheckFile() {
    for (int i = 0; i < xz_track_graphs.size(); ++i) {
      auto& xz_gr = xz_track_graphs[i];
      auto& ry_gr = xz_track_graphs[i];
      xz_gr->SetName(Form("xz_%d", i));
      xz_gr->SetTitle(Form("xz_%d", i));
      xz_gr->Write();
      ry_gr->SetName(Form("ry_%d", i));
      ry_gr->SetTitle(Form("ry_%d", i));
      ry_gr->Write();
    }
    file.Write();
  }
  void AddFit(const TVector3& vtx, const TVector3& mom,  const std::array<E16ANA_TrackCandidate::FitResult, E16ANA_TrackConstant::kNumDetectorLayers>& fit_results) {
    const int n_point = E16ANA_TrackConstant::kNumDetectorLayers;
    double x[n_point], y[n_point], z[n_point], r[n_point];
    for (int i = 0; i < n_point; ++i) {
      auto& result = fit_results[i];
      if (result.set_flag == 0) {
        continue;
      }
      auto mid = result.module_id;
      auto lpos = result.local_pos;
      auto gpos = result.global_pos;
      x[i] = gpos.X();
      y[i] = gpos.Y();
      z[i] = gpos.Z();
      r[i] = sqrt(x[i] * x[i] + z[i] * z[i]);
      if (i == 0) {
        ssd_module_id = mid;
        ssd_lpos_fit = lpos;
        ssd_gpos_fit = gpos;
      } else if (i == 1) {
        gtr1_module_id = mid;
        gtr1_lpos_fit = lpos;
        gtr1_gpos_fit = gpos;
      } else if (i == 2) {
        gtr2_module_id = mid;
        gtr2_lpos_fit = lpos;
        gtr2_gpos_fit = gpos;
      } else if (i == 3) {
        gtr3_module_id = mid;
        gtr3_lpos_fit = lpos;
        gtr3_gpos_fit = gpos;
      } else if (i == 4) {
        hbd_module_id = mid;
        hbd_lpos_fit = lpos;
        hbd_gpos_fit = gpos;
      } else if (i == 5) {
        lg0_module_id = mid;
        lg0_lpos_fit = lpos;
        lg0_gpos_fit = gpos;
      } else if (i == 6) {
        lg1_module_id = mid;
        lg1_lpos_fit = lpos;
        lg1_gpos_fit = gpos;
      } else if (i == 7) {
        lg2_module_id = mid;
        lg2_lpos_fit = lpos;
        lg2_gpos_fit = gpos;
      }
    }
    xz_track_graphs.emplace_back(new TGraph(n_point, x, z));
    ry_track_graphs.emplace_back(new TGraph(n_point, r, y));
    vtx_gpos_fit = vtx;
    vtx_gmom_fit = mom;
    return;
  }
  void AddHit(TVector3& vtx, TVector3& mom, std::array<E16ANA_TrackClusterPair, 4>& cluster_pairs) {
    vtx_gpos_hit = vtx;
    vtx_gmom_hit = mom;
    for (int i = 0; i < 4; ++i) {
      auto& clst = cluster_pairs[i];
      auto lpos = clst.LocalPos();
      auto gpos = clst.GlobalPos();
      if (i == 0) {
        ssd_lpos_hit = lpos;
        ssd_gpos_hit = gpos;
      } else if (i == 1) {
        gtr1_lpos_hit = lpos;
        gtr1_gpos_hit = gpos;
      } else if (i == 2) {
        gtr2_lpos_hit = lpos;
        gtr2_gpos_hit = gpos;
      } else if (i == 3) {
        gtr3_lpos_hit = lpos;
        gtr3_gpos_hit = gpos;
      }
    }
    return;
  }
  void AddEntry(int _event_id, E16ANA_TrackCandidate& cand) {
    event_id = _event_id;
    track_id = cand.TrackID();
    chi_square = cand.ChiSquare();
    auto&& vtx = cand.Vertex();
    auto&& mom = cand.Momentum();
    auto&& vtx_fit = cand.FitVertex();
    auto&& mom_fit = cand.FitMomentum();
    const auto& fit_results = cand.LocalFitResults();
    AddFit(vtx_fit, mom_fit, fit_results);
    AddHit(vtx, mom, cand.ClusterPairs());
    tree->Fill();
  }
 private:
  TFile file;
  TTree* tree;
  int event_id;
  int track_id;
  double chi_square;
  TVector3 vtx_gpos_hit;
  TVector3 vtx_gmom_hit;
  int ssd_module_id;
  int gtr1_module_id;
  int gtr2_module_id;
  int gtr3_module_id;
  int hbd_module_id;
  int lg0_module_id;
  int lg1_module_id;
  int lg2_module_id;
  TVector3 ssd_lpos_hit;
  TVector3 ssd_gpos_hit;
  TVector3 gtr1_lpos_hit;
  TVector3 gtr1_gpos_hit;
  TVector3 gtr2_lpos_hit;
  TVector3 gtr2_gpos_hit;
  TVector3 gtr3_lpos_hit;
  TVector3 gtr3_gpos_hit;
  TVector3 vtx_gpos_fit;
  TVector3 vtx_gmom_fit;
  TVector3 ssd_lpos_fit;
  TVector3 ssd_gpos_fit;
  TVector3 gtr1_lpos_fit;
  TVector3 gtr1_gpos_fit;
  TVector3 gtr2_lpos_fit;
  TVector3 gtr2_gpos_fit;
  TVector3 gtr3_lpos_fit;
  TVector3 gtr3_gpos_fit;
  TVector3 hbd_lpos_fit;
  TVector3 hbd_gpos_fit;
  TVector3 lg0_lpos_fit;
  TVector3 lg0_gpos_fit;
  TVector3 lg1_lpos_fit;
  TVector3 lg1_gpos_fit;
  TVector3 lg2_lpos_fit;
  TVector3 lg2_gpos_fit;
  std::vector<TGraph*> xz_track_graphs;
  std::vector<TGraph*> ry_track_graphs;
};

#endif // E16ANA_TRACKCANDIDATE_HH
