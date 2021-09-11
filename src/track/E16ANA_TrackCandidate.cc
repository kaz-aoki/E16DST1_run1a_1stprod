#include "E16ANA_TrackCandidate.hh"

TVector3 E16ANA_TrackCandidate::CalcRoughMomentum(const TVector3& gxz0, const TVector3& gxz1) {
  TVector3 rough_mom;
  TVector3 u0 = ConformalTransformation(gxz0);
  TVector3 u1 = ConformalTransformation(gxz1);
  double By = 1. / 1.5; // need to be able to modify?
  double a = 1. /(u0.X() * u1.Z() - u0.Z() * u1.X()) * (u1.Z() - u0.Z());
  double b = 1. /(u0.X() * u1.Z() - u0.Z() * u1.X()) * (u0.X() - u1.X());
  double r = sqrt(a * a + b * b);
  double p = 0.3 * (r / 1000.) * By;
  //double phase_diff = calc_phase_diff(TVector3(gxz1.X()-a,0.0,gxz1.Z()-b),TVector3(-a,0.0,-b));
  double phase_diff = CalcPhaseDiff(gxz1, gxz0);
  double theta = CalcPhaseDiff(TVector3(gxz1.X() - a, 0., gxz1.Z() - b), TVector3(-a, 0., -b));
  double flight_length = fabs(theta) * r;
  double py = p * gxz1.Y() / flight_length;
  if (phase_diff > 0.0) {
    rough_mom.SetXYZ(-b, 0., +a);
    rough_mom = rough_mom.Unit() * p;
  } else {rough_mom.SetXYZ(+b, 0., -a);
    rough_mom.SetXYZ(+b, 0., -a);
    rough_mom = rough_mom.Unit() * p;
  }
  rough_mom.SetY(py);
  return rough_mom;
}

bool E16ANA_TrackCandidate::CalcRoughMomentum() {
  int l0 = -1, l1 = -1;
  for (int l = 0; l < E16ANA_TrackConstant::kNumTrackingLayers; ++l) {
    auto& c = cluster_pairs[l];
    if (c.SetFlag() == 0) {
      continue;
    }
    if (l0 < 0) {
      l0 = c.LayerOrder();
    } else if (l0 != c.LayerOrder()) {
      l1 = c.LayerOrder();
      break;
    }
  }
  if (l0 < 0 || l1 < 0 || l0 == l1) {
    return false;
  } else if (l0 < l1) {
    mom = CalcRoughMomentum(cluster_pairs[l0].GlobalPos(), cluster_pairs[l1].GlobalPos());
  }else{
    mom = CalcRoughMomentum(cluster_pairs[l1].GlobalPos(), cluster_pairs[l0].GlobalPos());
  }
  return true;
}

void E16ANA_TrackCandidate::SetSingleTrackFit(E16ANA_MultiTrack* single_track, int _track_id) {
  for (auto& fit_result : fit_results) {
    fit_result.set_flag = 0;
  }
  TVector3 vtx_err(1.5, 1.7, 20e-3);
  single_track->SetInitialVertex(Vertex(), vtx_err);
  single_track->SetInitialMomentum(track_id, mom);
  single_track->SetCharge(track_id, charge);
  int l = 0;
  for (auto& c : cluster_pairs) {
    single_track->AddHit(track_id, c.LayerOrder(), c.Geometry(), c.LocalPos(), sigma[l]);
    fit_results[l].set_flag = 1;
    ++l;
  }
  auto module_id = cluster_pairs[E16ANA_TrackConstant::kNumTrackingLayers - 1].ModuleID();
  for (int layer_index = E16ANA_TrackConstant::kNumTrackingLayers; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l) {
    for (const auto& geom : tmp_geoms[layer_index - E16ANA_TrackConstant::kNumTrackingLayers])
    single_track->AddHit(track_id, l, geom, {0., 0., 0.}, {0., 0., 0.});
  }
}

void E16ANA_TrackCandidate::ProjectionLG(E16ANA_MultiTrack* fitter) {
//  fitter->Clear();
//  for (int block_index = 0; block_index < E16DST_Constant::NBlocksLG) {
//    fitter->AddHit(0, 0, geom)
}

void E16ANA_TrackCandidate::UpdateFitResult(E16ANA_MultiTrack* fitter) {
  for (int l = 0; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l) {
    fit_results[l].Clear();
    std::vector<TVector3> lpos;
    std::vector<TVector3> lmom;
    std::vector<int> mid;
    fitter->GetFitLPos(track_id, l, mid, lpos);
    fitter->GetFitLMom(track_id, l, mid, lmom);
    TVector3 gpos;
    TVector3 gmom;
    if (l < 1) {
      gpos = geometry->SSD(mid[0])->GetGPos(lpos[0]);
      gmom = geometry->SSD(mid[0])->GetGMom(lmom[0]);
    } else if (l < 4) {
      gpos = geometry->GTR(mid[0], l - 1)->GetGPos(lpos[0]);
      gmom = geometry->GTR(mid[0], l - 1)->GetGMom(lmom[0]);
    } else if (l < 5) {
      gpos = geometry->HBD(mid[0])->GetGPos(lpos[0]);
      gmom = geometry->HBD(mid[0])->GetGMom(lmom[0]);
    } else {
      gpos = geometry->LGVD(mid[0])->GetGPos(lpos[0]);
      gmom = geometry->LGVD(mid[0])->GetGMom(lmom[0]);
    }
    fit_results[l].set_flag = 1;
    fit_results[l].layer_order = l;
    if (l < E16ANA_TrackConstant::kNumTrackingLayers) {
      fit_results[l].module_id = ModuleID2013To2020(mid[0]);
    } else {
      fit_results[l].module_id = ModuleID2013To2020_27(mid[0]);
    }
    fit_results[l].local_pos = lpos[0];
    fit_results[l].local_mom = lmom[0];
    fit_results[l].global_pos = gpos;
    fit_results[l].global_mom = gmom;
    fit_results[l].residual_pos = cluster_pairs[l].LocalPos() - lpos[0];
  }
  // ProjectionLG
}

double E16ANA_TrackCandidate::Fit(E16ANA_MultiTrack* fitter, bool vertex_fix_flag, bool py_fix_flag) {
  fitter->Clear();
  this->SetSingleTrackFit(fitter, track_id);
  chisq = fitter->Fit(vertex_fix_flag, py_fix_flag);
  vtx_fit = fitter->GetFitVertex();
  mom_fit = fitter->GetFitMomentum(0);
  UpdateFitResult(fitter);
  return chisq;
}

E16ANA_TrackCandidates::E16ANA_TrackCandidates() {
}

E16ANA_TrackCandidates::~E16ANA_TrackCandidates() {
}

void E16ANA_TrackCandidates::SetTrackCandidates() {
}

void E16ANA_TrackCandidates::RequireLGCut() {
  for (int tgt_index = 0; tgt_index < kNumTargets; ++tgt_index) {
    for (auto& cand : track_candidates[tgt_index]) {
      const auto& lg_fit = cand.LocalFitResult(E16ANA_TrackConstant::kLG);
      auto& tracked_lg_hits = cand.ProjectionLGHits();
      auto fit_mid = lg_fit.module_id;
      auto fit_lpos = lg_fit.local_pos;
      auto& lg_hits = record->LG().HitPtrs(fit_mid, 0, 0);
      for (const auto& lg_hit : lg_hits) {
        auto residual = lg_hit->LocalPos(*geometry) - fit_lpos;
        if (residual.Mag() < lg_residual_threshold) {
          tracked_lg_hits.emplace_back(lg_hit);
        }
      }
    }
  }
}

void E16ANA_TrackCandidates::SelectTracks() {
  for (auto& cands : selected_track_candidates) {
    cands.clear();
  }
  RequireLGCut();
  std::array<std::vector<E16DST_DST1Cluster*>, E16ANA_TrackConstant::kNumTrackingLayers> used_clusters;
  for (int tgt_index = 0; tgt_index < kNumTargets; ++tgt_index) {
    for (auto& clsts : used_clusters) {
      clsts.clear();
    }
    std::sort(track_candidates[tgt_index].begin(), track_candidates[tgt_index].end(), [](auto& lhs, auto& rhs) {
      return lhs.ChiSquare() < rhs.ChiSquare();
    });
    for (auto& track_candidate : track_candidates[tgt_index]) {
      if (track_candidate.ProjectionLGHits().size() == 0) {
        continue;
      }
      bool is_used = false;
      for (int l = 0; l < E16ANA_TrackConstant::kNumTrackingLayers; ++l) {
        int n_types = 2;
        if (l == E16DST_DST1Constant::kSSD) {
          n_types = 1;
        }
        for (int type = 0; type < n_types; ++type) {
          auto cluster = track_candidate.ClusterPair(l).Cluster(type);
          for (const auto& clst : used_clusters[l]) {
            if (cluster == clst) {
              is_used = true;
              break;
            }
          }
          if (is_used) {
            break;
          }
          used_clusters[l].emplace_back(cluster);
        }
        if (is_used) {
          break;
        }
      }
      if (is_used) {
        continue;
      }
      selected_track_candidates[tgt_index].emplace_back(track_candidate);
    }
  }
}

int E16ANA_TrackCandidates::SelectTargetID() {
}
