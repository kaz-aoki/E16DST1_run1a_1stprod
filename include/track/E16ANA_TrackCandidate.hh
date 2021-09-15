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
  TVector3& LocalPos() { return local_pos; }
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
  void SetDefaultSigma();
  int TrackID() { return track_id; }
  int TargetID() { return target_id; }
  double Charge() { return charge; }
  TVector3 Vertex() { return vtx; }
  TVector3 Sigma(int n) { return sigma[n]; }
  TVector3 FitVertex() { return vtx_fit; }
  TVector3 FitMomentum() { return mom_fit; }
  TVector3 FitSigma() { return vtx_sigma; }
  const FitResult& LocalFitResult(int n) const { return fit_results[n]; }
  const std::array<FitResult, E16ANA_TrackConstant::kNumDetectorLayers> LocalFitResults() const { return fit_results; }
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
  void Print() {
    std::cout << "Track ID: " << track_id << ", Target ID: " << target_id << std::endl;
    std::cout << "Tracking Layers" << std::endl;
    for (int i = 0; i < E16ANA_TrackConstant::kNumTrackingLayers; ++i) {
      auto& pair = cluster_pairs[i];
      auto& local_pos = pair.LocalPos();
      std::cout << "  Layer ID: " << i << ", Module ID: " << pair.ModuleID() << std::endl;
      std::cout << "  Local Position: (" << local_pos.X() << ", " << local_pos.Y() << ", " << local_pos.Z() << std::endl;
    }
  }
 private:
//  static const int kNumLGLayers = 3;
  static constexpr std::array<int, E16ANA_TrackConstant::kNumLGLayers> kTypicalLGBlocks = {0, 10, 20};
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
  static int ModuleID2013To2020(int _module_id) { return E16ANA_TrackConstant::kModuleID2013To2020[_module_id]; }
  static int ModuleID2020To2013(int _module_id) { return E16ANA_TrackConstant::kModuleID2020To2013[_module_id / 100][_module_id % 100]; }
  static int ModuleID2013To2020_27(int _module_id) { return E16ANA_TrackConstant::kModuleID2013To2020[_module_id - 3]; }
  static int ModuleID2020To2013_27(int _module_id) { return E16ANA_TrackConstant::kModuleID2020To2013[_module_id / 100][_module_id % 100 + 1]; }
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
//  const std::array<std::array<E16ANA_DetectorGeometry*, E16ANA_TrackConstant::kNumModules>, E16ANA_TrackConstant::kNumRemainingLayers> tmp_geoms;
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
//                         E16DST_DST1PhysicsRecord* _record, OutputFile* _file)
//      : geometry(_geometry), bfield_map(_bfield_map), tmp_geoms(_tmp_geoms), record(_record) { file = _file; }
  ~E16ANA_TrackCandidates() {}
  int NumTrackCandidates(int n) { return track_candidates[n].size(); }
  void SelectTracks();
  void Print() {
    for (auto& cands : track_candidates) {
      for (auto& cand : cands) {
        cand.Print();
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
  static constexpr int kNumRaughFitDegree = 3;
  static constexpr std::array<double, 2> kRaughFitChiSquareThreshold = {100., 10.};
  static constexpr std::array<int, 3> kNumReserveTracks = {1000, 1000, 100};
  static constexpr double kHBDProjectionThreshold = 20.;
  static constexpr double kLGProjectionThreshold = 150.;
  static constexpr double kLGResidualThreshold = 150.;
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
  bool IsXTrackCandidate(OneAxisClusterSet* cluster_set);
  bool IsYTrackCandidate(const OneAxisClusterSet& cluster_set);
  void SetTrackCandidates();
  void SetHBDAndLGSignals();
  void RequireLGCut();
  void AddTracksToRecord();
  E16ANA_GeometryV2* geometry;
  E16ANA_MagneticFieldMap* bfield_map;
  const std::array<std::array<E16ANA_DetectorGeometry*, E16ANA_TrackConstant::kNumModules>, E16ANA_TrackConstant::kNumRemainingLayers> tmp_geoms;
  E16DST_DST1PhysicsRecord* record;
  std::array<std::vector<E16ANA_TrackCandidate>, E16ANA_TrackConstant::kNumTargets> track_candidates;
  int most_likely_target_id;
  std::array<std::vector<E16ANA_TrackCandidate>, E16ANA_TrackConstant::kNumTargets> selected_track_candidates;

//  OutputFile* file;
};

//class OutputFile {
//public:
//   OutputFile(char *fname_out) : n_max_hits(400) {
//      file = TFile::Open(fname_out, "recreate");
//      tree = new TTree("tree", "tree");
//      tree->Branch("g4_event_id", &g4_event_id);
//      tree->Branch("good_flag", &good_flag);
//      tree->Branch("dfit_flag", &dfit_flag);
//      tree->Branch("VTXpos", &VTXpos);
//      tree->Branch("VTXpos_cp", &VTXpos_cp);
//      tree->Branch("VTXpos_fitd", &VTXpos_fitd);
//      tree->Branch("chisq_fitd", &chisq_fitd);
//      tree->Branch("mass_org", &mass_org);
//      tree->Branch("bg_org", &bg_org);
//      tree->Branch("mass_fitd", &mass_fitd);
//      tree->Branch("bg_fitd", &bg_fitd);
//      tree->Branch("nGTRFrame1hit", &nGTRFrame1hit);
//      tree->Branch("nGTRFrame2hit", &nGTRFrame2hit);
//      tree->Branch("nGTRFrame3hit", &nGTRFrame3hit);
//      for(int i=0; i<n_primaries; i++){
//         tree->Branch(Form("chisq%d_fits",i), &chisq_fits[i]);
//         tree->Branch(Form("VTXpos%d_fits",i), &VTXpos_fits[i]);
//         tree->Branch(Form("VTXmom%d",i), &VTXmom[i]);
//         tree->Branch(Form("VTXmom%d_quad",i), &VTXmom_quad[i]);
//         tree->Branch(Form("VTXmom%d_fits",i), &VTXmom_fits[i]);
//         tree->Branch(Form("VTXmom%d_fitd",i), &VTXmom_fitd[i]);
//         tree->Branch(Form("GTR1id%d",i), &GTR1id[i]);
//         tree->Branch(Form("GTR2id%d",i), &GTR2id[i]);
//         tree->Branch(Form("GTR3id%d",i), &GTR3id[i]);
//         tree->Branch(Form("SSDid%d",i), &SSDid[i]);
//         tree->Branch(Form("GTR1gPos%d_g4",i), &GTR1gPos_g4[i]);
//         tree->Branch(Form("GTR2gPos%d_g4",i), &GTR2gPos_g4[i]);
//         tree->Branch(Form("GTR3gPos%d_g4",i), &GTR3gPos_g4[i]);
//         tree->Branch(Form("GTR1lPos%d_g4",i), &GTR1lPos_g4[i]);
//         tree->Branch(Form("GTR2lPos%d_g4",i), &GTR2lPos_g4[i]);
//         tree->Branch(Form("GTR3lPos%d_g4",i), &GTR3lPos_g4[i]);
//         tree->Branch(Form("GTR1gMom%d_g4",i), &GTR1gMom_g4[i]);
//         tree->Branch(Form("GTR2gMom%d_g4",i), &GTR2gMom_g4[i]);
//         tree->Branch(Form("GTR3gMom%d_g4",i), &GTR3gMom_g4[i]);
//         tree->Branch(Form("GTR1lMom%d_g4",i), &GTR1lMom_g4[i]);
//         tree->Branch(Form("GTR2lMom%d_g4",i), &GTR2lMom_g4[i]);
//         tree->Branch(Form("GTR3lMom%d_g4",i), &GTR3lMom_g4[i]);
//         tree->Branch(Form("GTR1gPos%d_ana",i), &GTR1gPos_ana[i]);
//         tree->Branch(Form("GTR2gPos%d_ana",i), &GTR2gPos_ana[i]);
//         tree->Branch(Form("GTR3gPos%d_ana",i), &GTR3gPos_ana[i]);
//         tree->Branch(Form("GTR1lPos%d_ana",i), &GTR1lPos_ana[i]);
//         tree->Branch(Form("GTR2lPos%d_ana",i), &GTR2lPos_ana[i]);
//         tree->Branch(Form("GTR3lPos%d_ana",i), &GTR3lPos_ana[i]);
//         tree->Branch(Form("GTR1gPos%d_fitd",i), &GTR1gPos_fitd[i]);
//         tree->Branch(Form("GTR2gPos%d_fitd",i), &GTR2gPos_fitd[i]);
//         tree->Branch(Form("GTR3gPos%d_fitd",i), &GTR3gPos_fitd[i]);
//         tree->Branch(Form("GTR1lPos%d_fitd",i), &GTR1lPos_fitd[i]);
//         tree->Branch(Form("GTR2lPos%d_fitd",i), &GTR2lPos_fitd[i]);
//         tree->Branch(Form("GTR3lPos%d_fitd",i), &GTR3lPos_fitd[i]);
//         tree->Branch(Form("GTR1lMom%d_fitd",i), &GTR1lMom_fitd[i]);
//         tree->Branch(Form("GTR2lMom%d_fitd",i), &GTR2lMom_fitd[i]);
//         tree->Branch(Form("GTR3lMom%d_fitd",i), &GTR3lMom_fitd[i]);
//         tree->Branch(Form("SSDgPos%d_g4",i), &SSDgPos_g4[i]);
//         tree->Branch(Form("SSDlPos%d_g4",i), &SSDlPos_g4[i]);
//         tree->Branch(Form("SSDgMom%d_g4",i), &SSDgMom_g4[i]);
//         tree->Branch(Form("SSDlMom%d_g4",i), &SSDlMom_g4[i]);
//         new(&GTR1lPos_multi_ana[i]) TClonesArray("TVector3", n_max_hits);
//         new(&GTR2lPos_multi_ana[i]) TClonesArray("TVector3", n_max_hits);
//         new(&GTR3lPos_multi_ana[i]) TClonesArray("TVector3", n_max_hits);
//         new(&GTR1lPos_multi_fitd[i]) TClonesArray("TVector3", n_max_hits);
//         new(&GTR2lPos_multi_fitd[i]) TClonesArray("TVector3", n_max_hits);
//         new(&GTR3lPos_multi_fitd[i]) TClonesArray("TVector3", n_max_hits);
//         new(&SSDgPos_multi_ana[i]) TClonesArray("TVector3", n_max_hits);
//         new(&SSDlPos_multi_ana[i]) TClonesArray("TVector3", n_max_hits);
//         new(&SSDlPos_multi_fitd[i]) TClonesArray("TVector3", n_max_hits);
//         new(&SSDlPos_multi_fits[i]) TClonesArray("TVector3", n_max_hits);
//         new(&GTR1lPos_multi_fits[i]) TClonesArray("TVector3", n_max_hits);
//         new(&GTR2lPos_multi_fits[i]) TClonesArray("TVector3", n_max_hits);
//         new(&GTR3lPos_multi_fits[i]) TClonesArray("TVector3", n_max_hits);
//         for(int k=0; k<3; k++){
//            new(&GTR_cluster[k][i]) TClonesArray("TVector3", n_max_hits);
//         }
//         for(int j=0; j<n_max_hits; j++){
//            new(GTR1lPos_multi_ana[i][j]) TVector3(error_value, error_value, error_value);
//            new(GTR2lPos_multi_ana[i][j]) TVector3(error_value, error_value, error_value);
//            new(GTR3lPos_multi_ana[i][j]) TVector3(error_value, error_value, error_value);
//            new(GTR1lPos_multi_fitd[i][j]) TVector3(error_value, error_value, error_value);
//            new(GTR2lPos_multi_fitd[i][j]) TVector3(error_value, error_value, error_value);
//            new(GTR3lPos_multi_fitd[i][j]) TVector3(error_value, error_value, error_value);
//            new(SSDgPos_multi_ana[i][j]) TVector3(error_value, error_value, error_value);
//            new(SSDlPos_multi_ana[i][j]) TVector3(error_value, error_value, error_value);
//            new(SSDlPos_multi_fitd[i][j]) TVector3(error_value, error_value, error_value);
//            new(GTR1lPos_multi_fits[i][j]) TVector3(error_value, error_value, error_value);
//            new(GTR2lPos_multi_fits[i][j]) TVector3(error_value, error_value, error_value);
//            new(GTR3lPos_multi_fits[i][j]) TVector3(error_value, error_value, error_value);
//            new(SSDlPos_multi_fits[i][j]) TVector3(error_value, error_value, error_value);
//            for(int k=0; k<3; k++){
//               new(GTR_cluster[k][i][j]) TVector3(error_value, error_value, error_value);
//            }
//         }
//         tree->Branch(Form("nGTR1lPos%d_multi_ana",i), &nGTR1lPos_multi_ana[i]);
//         tree->Branch(Form("nGTR2lPos%d_multi_ana",i), &nGTR2lPos_multi_ana[i]);
//         tree->Branch(Form("nGTR3lPos%d_multi_ana",i), &nGTR3lPos_multi_ana[i]);
//         tree->Branch(Form("nGTR1lPos%d_multi_fitd",i), &nGTR1lPos_multi_fitd[i]);
//         tree->Branch(Form("nGTR2lPos%d_multi_fitd",i), &nGTR2lPos_multi_fitd[i]);
//         tree->Branch(Form("nGTR3lPos%d_multi_fitd",i), &nGTR3lPos_multi_fitd[i]);
//         tree->Branch(Form("GTR1lPos%d_multi_ana",i), &GTR1lPos_multi_ana[i]);
//         tree->Branch(Form("GTR2lPos%d_multi_ana",i), &GTR2lPos_multi_ana[i]);
//         tree->Branch(Form("GTR3lPos%d_multi_ana",i), &GTR3lPos_multi_ana[i]);
//         tree->Branch(Form("GTR1lPos%d_multi_fitd",i), &GTR1lPos_multi_fitd[i]);
//         tree->Branch(Form("GTR2lPos%d_multi_fitd",i), &GTR2lPos_multi_fitd[i]);
//         tree->Branch(Form("GTR3lPos%d_multi_fitd",i), &GTR3lPos_multi_fitd[i]);
//         tree->Branch(Form("nSSDgPos%d_multi_ana",i), &nSSDgPos_multi_ana[i]);
//         tree->Branch(Form("nSSDlPos%d_multi_ana",i), &nSSDlPos_multi_ana[i]);
//         tree->Branch(Form("nSSDlPos%d_multi_fitd",i), &nSSDlPos_multi_fitd[i]);
//         tree->Branch(Form("SSDgPos%d_multi_ana",i), &SSDgPos_multi_ana[i]);
//         tree->Branch(Form("SSDlPos%d_multi_ana",i), &SSDlPos_multi_ana[i]);
//         tree->Branch(Form("SSDlPos%d_multi_fitd",i), &SSDlPos_multi_fitd[i]);
//         tree->Branch(Form("nGTR1lPos%d_multi_fits",i), &nGTR1lPos_multi_fits[i]);
//         tree->Branch(Form("nGTR2lPos%d_multi_fits",i), &nGTR2lPos_multi_fits[i]);
//         tree->Branch(Form("nGTR3lPos%d_multi_fits",i), &nGTR3lPos_multi_fits[i]);
//         tree->Branch(Form("nSSDlPos%d_multi_fits",i), &nSSDlPos_multi_fits[i]);
//         tree->Branch(Form("GTR1lPos%d_multi_fits",i), &GTR1lPos_multi_fits[i]);
//         tree->Branch(Form("GTR2lPos%d_multi_fits",i), &GTR2lPos_multi_fits[i]);
//         tree->Branch(Form("GTR3lPos%d_multi_fits",i), &GTR3lPos_multi_fits[i]);
//         tree->Branch(Form("SSDlPos%d_multi_fits",i), &SSDlPos_multi_fits[i]);
//         for(int k=0; k<3; k++){
//            tree->Branch(Form("GTR%d_cluster%d",k+1,i), &GTR_cluster[k][i]);
//            tree->Branch(Form("GTR%d_cluster_id%d",k+1,i), &GTR_cluster_id[k][i]);
//         }
//         tree->Branch("cluster_width_x", cluster_width_x, Form("cluster_width_x[%d]/D",n_primaries*3));
//         tree->Branch("cluster_width_y", cluster_width_y, Form("cluster_width_y[%d]/D",n_primaries*3));
//
//         g_track_xz[i] = new TGraph();
//         g_track_xy[i] = new TGraph();
//         g_track_zy[i] = new TGraph();
//         g_track_xyz[i] = new TGraph2D();
//         g_strack_xz[i] = new TGraph();
//      }
//      for(int i=0; i<33; i++){
//         for(int j=0; j<3; j++){
//            tree->Branch(Form("gtr_strips_%02d%02d"         ,i,j), &gtr_strips         [i][j]);
//            tree->Branch(Form("gtr_hit_strips_%02d%02d"     ,i,j), &gtr_hit_strips     [i][j]);
//            tree->Branch(Form("gtr_strip_occupancy_%02d%02d",i,j), &gtr_strip_occupancy[i][j]);
//         }
//      }
//   };
//   void Clear(){
//      module_org.clear();
//      g4_event_id = error_value;
//      good_flag = error_value;
//      dfit_flag = error_value;
//      Clear(VTXpos);
//      Clear(VTXpos_cp);
//      Clear(VTXpos_fitd);
//      chisq_fitd = error_value;
//      mass_org = error_value;
//      bg_org = error_value;
//      mass_fitd = error_value;
//      bg_fitd = error_value;
//      nGTRFrame1hit = error_value;
//      nGTRFrame2hit = error_value;
//      nGTRFrame3hit = error_value;
//      for(int i=0; i<n_primaries; i++){
//         chisq_fits[i] = error_value;
//         Clear(VTXpos_fits[i]);
//         GTR1id[i] = error_value;
//         GTR2id[i] = error_value;
//         GTR3id[i] = error_value;
//         SSDid[i] = error_value;
//         Clear(VTXmom[i]);
//         Clear(VTXmom_quad[i]);
//         Clear(VTXmom_fits[i]);
//         Clear(VTXmom_fitd[i]);
//         Clear(GTR1gPos_g4[i]);
//         Clear(GTR2gPos_g4[i]);
//         Clear(GTR3gPos_g4[i]);
//         Clear(GTR1lPos_g4[i]);
//         Clear(GTR2lPos_g4[i]);
//         Clear(GTR3lPos_g4[i]);
//         Clear(GTR1gMom_g4[i]);
//         Clear(GTR2gMom_g4[i]);
//         Clear(GTR3gMom_g4[i]);
//         Clear(GTR1lMom_g4[i]);
//         Clear(GTR2lMom_g4[i]);
//         Clear(GTR3lMom_g4[i]);
//         Clear(SSDgPos_g4[i]);
//         Clear(SSDlPos_g4[i]);
//         Clear(SSDgMom_g4[i]);
//         Clear(SSDlMom_g4[i]);
//         Clear(GTR1gPos_ana[i]);
//         Clear(GTR2gPos_ana[i]);
//         Clear(GTR3gPos_ana[i]);
//         Clear(GTR1lPos_ana[i]);
//         Clear(GTR2lPos_ana[i]);
//         Clear(GTR3lPos_ana[i]);
//         Clear(GTR1gPos_fitd[i]);
//         Clear(GTR2gPos_fitd[i]);
//         Clear(GTR3gPos_fitd[i]);
//         Clear(GTR1lPos_fitd[i]);
//         Clear(GTR2lPos_fitd[i]);
//         Clear(GTR3lPos_fitd[i]);
//         Clear(GTR1lMom_fitd[i]);
//         Clear(GTR2lMom_fitd[i]);
//         Clear(GTR3lMom_fitd[i]);
//         for(int j=0; j<n_max_hits; j++){
//            Clear((TVector3*)GTR1lPos_multi_ana[i][j]);
//            Clear((TVector3*)GTR2lPos_multi_ana[i][j]);
//            Clear((TVector3*)GTR3lPos_multi_ana[i][j]);
//            Clear((TVector3*)GTR1lPos_multi_fitd[i][j]);
//            Clear((TVector3*)GTR2lPos_multi_fitd[i][j]);
//            Clear((TVector3*)GTR3lPos_multi_fitd[i][j]);
//            Clear((TVector3*)GTR1lPos_multi_fits[i][j]);
//            Clear((TVector3*)GTR2lPos_multi_fits[i][j]);
//            Clear((TVector3*)GTR3lPos_multi_fits[i][j]);
//            Clear((TVector3*)SSDgPos_multi_ana[i][j]);
//            Clear((TVector3*)SSDlPos_multi_ana[i][j]);
//            Clear((TVector3*)SSDlPos_multi_fitd[i][j]);
//            Clear((TVector3*)SSDlPos_multi_fits[i][j]);
//            Clear((TVector3*)GTR_cluster[0][i][j]);
//            Clear((TVector3*)GTR_cluster[1][i][j]);
//            Clear((TVector3*)GTR_cluster[2][i][j]);
//         }
//         GTR_cluster_id[0][i].clear();
//         GTR_cluster_id[1][i].clear();
//         GTR_cluster_id[2][i].clear();
//         nGTR1lPos_multi_ana[i] = 0;
//         nGTR2lPos_multi_ana[i] = 0;
//         nGTR3lPos_multi_ana[i] = 0;
//         nGTR1lPos_multi_fitd[i] = 0;
//         nGTR2lPos_multi_fitd[i] = 0;
//         nGTR3lPos_multi_fitd[i] = 0;
//
//         nGTR1lPos_multi_fits[i] = 0;
//         nGTR2lPos_multi_fits[i] = 0;
//         nGTR3lPos_multi_fits[i] = 0;
//
//         nSSDgPos_multi_ana[i] = 0;
//         nSSDlPos_multi_ana[i] = 0;
//         nSSDlPos_multi_fitd[i] = 0;
//         nSSDlPos_multi_fits[i] = 0;
//         for(int j=0; j<3; j++){
//            cluster_width_x[i*3+j] = error_value;
//            cluster_width_y[i*3+j] = error_value;
//         }
//      }
//      for(int i=0; i<33; i++){
//         for(int j=0; j<3; j++){
//            gtr_strips         [i][j].clear();
//            gtr_hit_strips     [i][j].clear();
//            gtr_strip_occupancy[i][j].clear();
//         }
//      }
//   };
//   void TreeFill(){
//      if(good_flag == 1) tree->Fill();
//   };
//   void SaveAndClose(){
//      file->Write();
//      for(int i=0; i<n_primaries; i++){
//         g_track_xz[i]->Write();
//         g_track_xy[i]->Write();
//         g_track_zy[i]->Write();
//         g_track_xyz[i]->Write(); // TGraph2D
//         g_strack_xz[i]->Write();
//      }
//      file->Close();
//   };
//
//   void SetG4EventInfo(E16ANA_G4Event &g4event){
//      g4_event_id = g4event.G4EventID();
//      nGTRFrame1hit = g4event.GTRFrame1().Noh();
//      nGTRFrame2hit = g4event.GTRFrame2().Noh();
//      nGTRFrame3hit = g4event.GTRFrame3().Noh();
//   };
//   void SetPrimaryTracks(E16ANA_G4Track &t_pos, E16ANA_G4Track &t_ele){
//      VTXpos = t_pos.TVertex(); // mm -> mm
//      VTXmom[0] = t_pos.PTV();
//      VTXmom[1] = t_ele.PTV();
//   };
//   void SetInvMassOrg(double mass, double bg){
//      mass_org = mass;
//      bg_org = bg;
//   };
//   void SetQuadraticFitData(const TVector3 &p0, const TVector3 &p1){
//      VTXmom_quad[0] = p0;
//      VTXmom_quad[1] = p1;
//   };
//   void SetSingleFitData(const TVector3 v[2], const TVector3 &vcp, const TVector3 p[2], const double chisq[2]){
//      for(int i=0; i<n_primaries; i++){
//         VTXpos_fits[i] = v[i];
//         VTXmom_fits[i] = p[i];
//         chisq_fits[i] = chisq[i];
//      }
//      VTXpos_cp = vcp;
//   };
//   void SetDoubleFitData(
//         double chi2, double mass, double bg,
//         const TVector3 &vtx, const TVector3 &p_pos, const TVector3 &p_ele
//         ){
//      chisq_fitd = chi2;
//      mass_fitd = mass;
//      bg_fitd = bg;
//      VTXpos_fitd = vtx; // mm -> mm
//      VTXmom_fitd[0] = p_pos;
//      VTXmom_fitd[1] = p_ele;
//   };
//   void SetGTRPosG4(const TVector3 &gpos, const TVector3 &lpos, const TVector3 &gmom, const TVector3 &lmom, int module, int id){ // mm -> mm
//      if(id%3 == 0){
//         GTR1gPos_g4[id/3] = gpos;
//         GTR1lPos_g4[id/3] = lpos;
//         GTR1gMom_g4[id/3] = gmom;
//         GTR1lMom_g4[id/3] = lmom;
//         GTR1id[id/3] = module;
//      }else if(id%3 == 1){
//         GTR2gPos_g4[id/3] = gpos;
//         GTR2lPos_g4[id/3] = lpos;
//         GTR2gMom_g4[id/3] = gmom;
//         GTR2lMom_g4[id/3] = lmom;
//         GTR2id[id/3] = module;
//      }else if(id%3 == 2){
//         GTR3gPos_g4[id/3] = gpos;
//         GTR3lPos_g4[id/3] = lpos;
//         GTR3gMom_g4[id/3] = gmom;
//         GTR3lMom_g4[id/3] = lmom;
//         GTR3id[id/3] = module;
//      }
//   };
//   void SetSSDPosG4(const TVector3 &gpos, const TVector3 &lpos, const TVector3 &gmom, const TVector3 &lmom, int module, int track_id){ // mm -> mm
//      SSDgPos_g4[track_id] = gpos;
//      SSDlPos_g4[track_id] = lpos;
//      SSDgMom_g4[track_id] = gmom;
//      SSDlMom_g4[track_id] = lmom;
//      SSDid[track_id] = module;
//   }
//   void SetGTRPosAna(const TVector3 &gpos, const TVector3 &lpos, double width_x, double width_y, int id){ // mm -> mm
//      if(id%3 == 0){
//         GTR1gPos_ana[id/3] = gpos;
//         GTR1lPos_ana[id/3] = lpos;
//      }else if(id%3 == 1){
//         GTR2gPos_ana[id/3] = gpos;
//         GTR2lPos_ana[id/3] = lpos;
//      }else if(id%3 == 2){
//         GTR3gPos_ana[id/3] = gpos;
//         GTR3lPos_ana[id/3] = lpos;
//      }
//      cluster_width_x[id] = width_x;
//      cluster_width_y[id] = width_y;
//   };
//   void SetGTRPosDoubleFit(const TVector3 &gpos, const TVector3 &lpos, const TVector3 &lmom, int id){ // mm -> mm
//      if(id%3 == 0){
//         GTR1gPos_fitd[id/3] = gpos;
//         GTR1lPos_fitd[id/3] = lpos;
//         GTR1lMom_fitd[id/3] = lmom;
//      }else if(id%3 == 1){
//         GTR2gPos_fitd[id/3] = gpos;
//         GTR2lPos_fitd[id/3] = lpos;
//         GTR2lMom_fitd[id/3] = lmom;
//      }else if(id%3 == 2){
//         GTR3gPos_fitd[id/3] = gpos;
//         GTR3lPos_fitd[id/3] = lpos;
//         GTR3lMom_fitd[id/3] = lmom;
//      }
//   };
//   void SetGTRPosMultiAna(const std::vector<TVector3> &lpos, int id){
//      int n_filled_hits = min((int)lpos.size(), n_max_hits);
//      if(id%3 == 0){
//         nGTR1lPos_multi_ana[id/3] = lpos.size();
//         for(int i=0; i<n_filled_hits; i++){
//            SetToObject(&lpos[i], GTR1lPos_multi_ana[id/3][i]);
//         }
//      }else if(id%3 == 1){
//         nGTR2lPos_multi_ana[id/3] = lpos.size();
//         for(int i=0; i<n_filled_hits; i++){
//            SetToObject(&lpos[i], GTR2lPos_multi_ana[id/3][i]);
//         }
//      }else if(id%3 == 2){
//         nGTR3lPos_multi_ana[id/3] = lpos.size();
//         for(int i=0; i<n_filled_hits; i++){
//            SetToObject(&lpos[i], GTR3lPos_multi_ana[id/3][i]);
//         }
//      }
//   };
//   void SetGTRPosMultiSingleFit(const std::vector<TVector3> &lpos, int id){
//      int n_filled_hits = min((int)lpos.size(), n_max_hits);
//      if(id%3 == 0){
//         nGTR1lPos_multi_fits[id/3] = lpos.size();
//         for(int i=0; i<n_filled_hits; i++){
//            SetToObject(&lpos[i], GTR1lPos_multi_fits[id/3][i]);
//         }
//      }else if(id%3 == 1){
//         nGTR2lPos_multi_fits[id/3] = lpos.size();
//         for(int i=0; i<n_filled_hits; i++){
//            SetToObject(&lpos[i], GTR2lPos_multi_fits[id/3][i]);
//         }
//      }else if(id%3 == 2){
//         nGTR3lPos_multi_fits[id/3] = lpos.size();
//         for(int i=0; i<n_filled_hits; i++){
//            SetToObject(&lpos[i], GTR3lPos_multi_fits[id/3][i]);
//         }
//      }
//   };
//   void SetGTRPosMultiDoubleFit(const std::vector<TVector3> &lpos, int id){
//      int n_filled_hits = min((int)lpos.size(), n_max_hits);
//      if(id%3 == 0){
//         nGTR1lPos_multi_fitd[id/3] = lpos.size();
//         for(int i=0; i<n_filled_hits; i++){
//            SetToObject(&lpos[i], GTR1lPos_multi_fitd[id/3][i]);
//         }
//      }else if(id%3 == 1){
//         nGTR2lPos_multi_fitd[id/3] = lpos.size();
//         for(int i=0; i<n_filled_hits; i++){
//            SetToObject(&lpos[i], GTR2lPos_multi_fitd[id/3][i]);
//         }
//      }else if(id%3 == 2){
//         nGTR3lPos_multi_fitd[id/3] = lpos.size();
//         for(int i=0; i<n_filled_hits; i++){
//            SetToObject(&lpos[i], GTR3lPos_multi_fitd[id/3][i]);
//         }
//      }
//   };
//   void SetSSDPosMultiAna(const std::vector<TVector3> &lpos, int id){
//      int n_filled_hits = min((int)lpos.size(), n_max_hits);
//      nSSDlPos_multi_ana[id] = lpos.size();
//      for(int i=0; i<n_filled_hits; i++){
//         SetToObject(&lpos[i], SSDlPos_multi_ana[id][i]);
//      }
//   };
//   void SetSSDPosBkgAna(const std::vector<TVector3> &lpos, int id){
//      int n_filled_hits = min((int)lpos.size(), n_max_hits);
//      nSSDgPos_multi_ana[id] = lpos.size();
//      for(int i=0; i<n_filled_hits; i++){
//         SetToObject(&lpos[i], SSDgPos_multi_ana[id][i]);
//      }
//   };
//   void SetSSDPosMultiSingleFit(const std::vector<TVector3> &lpos, int id){
//      int n_filled_hits = min((int)lpos.size(), n_max_hits);
//      nSSDlPos_multi_fits[id] = lpos.size();
//      for(int i=0; i<n_filled_hits; i++){
//         SetToObject(&lpos[i], SSDlPos_multi_fits[id][i]);
//      }
//   };
//
//   void SetSSDPosMultiDoubleFit(const std::vector<TVector3> &lpos, int id){
//      int n_filled_hits = min((int)lpos.size(), n_max_hits);
//      nSSDlPos_multi_fitd[id] = lpos.size();
//      for(int i=0; i<n_filled_hits; i++){
//         SetToObject(&lpos[i], SSDlPos_multi_fitd[id][i]);
//      }
//   };
//   void SetToObject(const TVector3 *v, TObject *obj){
//      TVector3 *temp_ptr = (TVector3*)obj;
//      //temp_ptr->SetXYZ(v->X()*10.0, v->Y()*10.0, v->Z()*10.0); // cm -> mm
//      temp_ptr->SetXYZ(v->X(), v->Y(), v->Z()); // mm -> mm
//   };
//   void SetGood(int a){good_flag = a;};
//   void SetDfitFlag(int a){dfit_flag = a;};
//
//   void SetGTRCluster(E16ANA_GTRAnalyzedHit* hit, int id){
//      int track = id/3;
//      int layer = id%3;
//      int cluster = (GTR_cluster_id[layer][track].empty()) ? 0 : GTR_cluster_id[layer][track].back()+1;
//      E16ANA_GTRAnalyzedStripHit *strip = hit->XstripHit();
//      for(int i=0; i<strip->NumHit(); i++){
//         int j = GTR_cluster_id[layer][track].size();
//         GTR_cluster_id[layer][track].push_back(cluster);
//         TVector3 lpos(strip->StripPos(i), -10000.0, strip->StripPosZ(i));
//         SetToObject(&lpos, GTR_cluster[layer][track][j]);
//      }
//   };
//
//   void SetSingleTrackSteps(int track_id, const std::vector<TVector3> &track_steps){
//      g_strack_xz[track_id]->Set(0);
//      for(int i=0; i<(int)track_steps.size(); i++){
//         g_strack_xz[track_id]->SetPoint(i,track_steps[i].X(),track_steps[i].Z());
//      }
//   };
//   void SetTrackSteps(int track_id, const std::vector<TVector3> &track_steps){
//      g_track_xz[track_id]->Set(0);
//      g_track_xy[track_id]->Set(0);
//      g_track_zy[track_id]->Set(0);
//      g_track_xyz[track_id]->Set(0);
//      for(int i=0; i<(int)track_steps.size(); i++){
//         g_track_xz[track_id]->SetPoint(i,track_steps[i].X(),track_steps[i].Z());
//         g_track_xy[track_id]->SetPoint(i,track_steps[i].X(),track_steps[i].Y());
//         g_track_zy[track_id]->SetPoint(i,track_steps[i].Z(),track_steps[i].Y());
//         g_track_xyz[track_id]->SetPoint(i,track_steps[i].X(),track_steps[i].Y(),track_steps[i].Z());
//      }
//   };
//   void SetGTRStripOccupancy(int i, int j, E16ANA_GTRStripResponse *s){
//      gtr_strips         [i][j].push_back(s->GetNumStrips());
//      gtr_hit_strips     [i][j].push_back(s->GetNumHitStrips());
//      gtr_strip_occupancy[i][j].push_back(s->GetOccupancy());
//   };
//
//private:
//   TFile *file;
//   TTree *tree;
//
//   enum {n_primaries = 2, error_value = -10000};
//
//   TGraph *g_track_xz[n_primaries];
//   TGraph *g_track_xy[n_primaries];
//   TGraph *g_track_zy[n_primaries];
//   TGraph2D *g_track_xyz[n_primaries];
//   TGraph *g_strack_xz[n_primaries];
//
//   int g4_event_id;
//   int good_flag;
//   int dfit_flag;
//   TVector3 VTXpos;
//   TVector3 VTXpos_cp;
//   TVector3 VTXpos_fits[n_primaries];
//   TVector3 VTXpos_fitd;
//   double chisq_fits[n_primaries];
//   double chisq_fitd;
//   double mass_org;
//   double bg_org;
//   double mass_fitd;
//   double bg_fitd;
//   int nGTRFrame1hit;
//   int nGTRFrame2hit;
//   int nGTRFrame3hit;
//   int GTR1id[n_primaries];
//   int GTR2id[n_primaries];
//   int GTR3id[n_primaries];
//   int SSDid[n_primaries];
//   TVector3 VTXmom[n_primaries];
//   TVector3 VTXmom_quad[n_primaries];
//   TVector3 VTXmom_fits[n_primaries];
//   TVector3 VTXmom_fitd[n_primaries];
//   TVector3 GTR1gPos_g4[n_primaries];
//   TVector3 GTR2gPos_g4[n_primaries];
//   TVector3 GTR3gPos_g4[n_primaries];
//   TVector3 GTR1lPos_g4[n_primaries];
//   TVector3 GTR2lPos_g4[n_primaries];
//   TVector3 GTR3lPos_g4[n_primaries];
//   TVector3 GTR1gMom_g4[n_primaries];
//   TVector3 GTR2gMom_g4[n_primaries];
//   TVector3 GTR3gMom_g4[n_primaries];
//   TVector3 GTR1lMom_g4[n_primaries];
//   TVector3 GTR2lMom_g4[n_primaries];
//   TVector3 GTR3lMom_g4[n_primaries];
//   TVector3 SSDgPos_g4[n_primaries];
//   TVector3 SSDlPos_g4[n_primaries];
//   TVector3 SSDgMom_g4[n_primaries];
//   TVector3 SSDlMom_g4[n_primaries];
//   TVector3 GTR1gPos_ana[n_primaries];
//   TVector3 GTR2gPos_ana[n_primaries];
//   TVector3 GTR3gPos_ana[n_primaries];
//   TVector3 GTR1lPos_ana[n_primaries];
//   TVector3 GTR2lPos_ana[n_primaries];
//   TVector3 GTR3lPos_ana[n_primaries];
//   TVector3 GTR1gPos_fitd[n_primaries];
//   TVector3 GTR2gPos_fitd[n_primaries];
//   TVector3 GTR3gPos_fitd[n_primaries];
//   TVector3 GTR1lPos_fitd[n_primaries];
//   TVector3 GTR2lPos_fitd[n_primaries];
//   TVector3 GTR3lPos_fitd[n_primaries];
//   TVector3 GTR1lMom_fitd[n_primaries];
//   TVector3 GTR2lMom_fitd[n_primaries];
//   TVector3 GTR3lMom_fitd[n_primaries];
//   double cluster_width_x[n_primaries*3];
//   double cluster_width_y[n_primaries*3];
//
//   const int n_max_hits;
//   int nGTR1lPos_multi_ana[n_primaries];
//   int nGTR2lPos_multi_ana[n_primaries];
//   int nGTR3lPos_multi_ana[n_primaries];
//   int nGTR1lPos_multi_fitd[n_primaries];
//   int nGTR2lPos_multi_fitd[n_primaries];
//   int nGTR3lPos_multi_fitd[n_primaries];
//
//   int nGTR1lPos_multi_fits[n_primaries];
//   int nGTR2lPos_multi_fits[n_primaries];
//   int nGTR3lPos_multi_fits[n_primaries];
//
//   TClonesArray GTR1lPos_multi_ana[n_primaries];
//   TClonesArray GTR2lPos_multi_ana[n_primaries];
//   TClonesArray GTR3lPos_multi_ana[n_primaries];
//   TClonesArray GTR1lPos_multi_fitd[n_primaries];
//   TClonesArray GTR2lPos_multi_fitd[n_primaries];
//   TClonesArray GTR3lPos_multi_fitd[n_primaries];
//   TClonesArray GTR1lPos_multi_fits[n_primaries];
//   TClonesArray GTR2lPos_multi_fits[n_primaries];
//   TClonesArray GTR3lPos_multi_fits[n_primaries];
//
//   TClonesArray GTR_cluster[3][n_primaries];
//   std::vector<int> GTR_cluster_id[3][n_primaries];
//
//   int nSSDgPos_multi_ana[n_primaries];
//   int nSSDlPos_multi_ana[n_primaries];
//   int nSSDlPos_multi_fitd[n_primaries];
//   int nSSDlPos_multi_fits[n_primaries];
//   TClonesArray SSDgPos_multi_ana[n_primaries];
//   TClonesArray SSDlPos_multi_ana[n_primaries];
//   TClonesArray SSDlPos_multi_fitd[n_primaries];
//   TClonesArray SSDlPos_multi_fits[n_primaries];
//
//   std::vector<int> module_org;
//
//   std::vector<int> gtr_strips[33][3];
//   std::vector<int> gtr_hit_strips[33][3];
//   std::vector<double> gtr_strip_occupancy[33][3];
//
//   void Clear(TVector3 &v){
//      v.SetXYZ(error_value, error_value, error_value);
//   }
//   void Clear(TVector3 *v){
//      v->SetXYZ(error_value, error_value, error_value);
//   }
//
//};

#endif // E16ANA_TRACKCANDIDATE_HH
