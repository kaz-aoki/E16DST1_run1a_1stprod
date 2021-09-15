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
  for (int l = E16ANA_TrackConstant::kNumTrackingLayers; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l) {
//    for (const auto& geom : tmp_geoms[layer_index - E16ANA_TrackConstant::kNumTrackingLayers])
//    single_track->AddHit(track_id, l, geom, {0., 0., 0.}, {0., 0., 0.});
    for (int mid = module_id - 1; mid <= module_id + 1; ++module_id) {
      if (mid < E16ANA_TrackConstant::kModuleIDs[0] || mid > E16ANA_TrackConstant::kModuleIDs[E16ANA_TrackConstant::kNumModules - 1]) {
        continue;
      }
      auto mid2013 = ModuleID2020To2013_27(mid);
      if (l = E16ANA_TrackConstant::kHBD) {
        auto tmp_geom = geometry->HBD(mid2013);
        single_track->AddHit(track_id, l, tmp_geom, {0., 0., 0.}, {0., 0., 0.});
      } else {
        auto tmp_geom = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG]);
        single_track->AddHit(track_id, l, tmp_geom, {0., 0., 0.}, {0., 0., 0.});
      }
    }
  }
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

void E16ANA_TrackCandidates::CalcInverseMatrix(const std::array<double, kNumTrackingLayersWTarget>& zz, std::array<std::array<double, kNumRaughFitDegree>, kNumRaughFitDegree>* line) {
  double m11 = zz[4];
  double m12 = zz[3];
  double m21 = zz[3];
  double m13 = zz[2];
  double m22 = zz[2];
  double m31 = zz[2];
  double m23 = zz[1];
  double m32 = zz[1];
  double m33 = zz[0];
  double det = m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 - m13 * m22 * m31 - m12 * m21 * m33 - m11 * m23 * m32;

  line->at(0)[0] =       (m22 * m33 - m23 * m32) / det;
  line->at(0)[1] = -1. * (m12 * m33 - m13 * m32) / det;
  line->at(0)[2] =       (m12 * m23 - m13 * m22) / det;
  line->at(1)[0] = -1. * (m21 * m33 - m23 * m31) / det;
  line->at(1)[1] =       (m11 * m33 - m13 * m31) / det;
  line->at(1)[2] = -1. * (m11 * m23 - m13 * m21) / det;
  line->at(2)[0] =       (m21 * m32 - m22 * m31) / det;
  line->at(2)[1] = -1. * (m11 * m32 - m12 * m31) / det;
  line->at(2)[2] =       (m11 * m22 - m12 * m21) / det;
  return;
}

//bool E16ANA_TrackCandidates::IsXTrackCandidate(double tgt_z, const std::array<TVector3*, E16ANA_TrackConstant::kNumTrackingLayers>& pos_set) {
bool E16ANA_TrackCandidates::IsXTrackCandidate(OneAxisClusterSet* cluster_set) {
  auto& tgt_z = E16ANA_TrackConstant::kTargetZ[cluster_set->target_id];
  std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> pos_set = {cluster_set->ssd_cluster->GlobalPos(*geometry),
                                                                            cluster_set->gtr_clusters[0]->GlobalPos(*geometry),
                                                                            cluster_set->gtr_clusters[1]->GlobalPos(*geometry),
                                                                            cluster_set->gtr_clusters[2]->GlobalPos(*geometry)};
  
  if (pos_set[3].X() * pos_set[0].X() < 0. || pos_set[3].X() * pos_set[1].X() < 0. || pos_set[3].X() * pos_set[2].X() < 0.) {
    return false;
  }

  std::array<TVector3, kNumTrackingLayersWTarget> lotated_pos;
  auto rot_phi = std::atan2(pos_set[3].X(), pos_set[3].Z() - tgt_z);
  auto rot_cos = std::cos(rot_phi);
  auto rot_sin = std::sin(rot_phi);
  lotated_pos[0] = {0., 0., 0.};
  lotated_pos[1] = Lotate(rot_cos, rot_sin, pos_set[0]);
  lotated_pos[2] = Lotate(rot_cos, rot_sin, pos_set[1]);
  lotated_pos[3] = Lotate(rot_cos, rot_sin, pos_set[2]);
  lotated_pos[4] = Lotate(rot_cos, rot_sin, pos_set[3]);
  
  std::array<double, kNumTrackingLayersWTarget> zz;
  std::array<double, kNumTrackingLayersWTarget> zx;
  for (int i = 0; i < kNumTrackingLayersWTarget; ++i) {
    AddMatrixElement(kXWeight[i], lotated_pos[i], &zz, &zx);
  }
  
  std::array<std::array<double, kNumRaughFitDegree>, kNumRaughFitDegree> line;
  CalcInverseMatrix(zz, &line);
  std::array<double, kNumRaughFitDegree> corr;
  std::array<double, kNumTrackingLayersWTarget> fit_z_diff;
  CalcCoefficients(zx, line, &corr);
  cluster_set->charge = corr[2] > 0 ? 1 : -1;

  double grad = -1. * (rot_sin / rot_cos);
  double BB_fit = corr[1] - grad;
  double det_tgt_fit = BB_fit * BB_fit - 4 * corr[2] * corr[0];
  double tgt_z_cand = -9999.;
  if (det_tgt_fit > 0) {
    double fit_tgt1  = (-1. * BB_fit + sqrt(det_tgt_fit)) / (2. * corr[2]);
    double fit_tgt2  = (-1. * BB_fit - sqrt(det_tgt_fit)) / (2. * corr[2]);
    double tgt_z_prime_cand = fabs(fit_tgt1) < fabs(fit_tgt2) ? fit_tgt1 : fit_tgt2; 
    tgt_z_cand = rot_cos * tgt_z_prime_cand - rot_sin * grad * tgt_z_prime_cand;
  }

  double chi2_cand = 0.;
  for (int point_index = 0; point_index < kNumTrackingLayersWTarget; ++point_index) {
    fit_z_diff[point_index] = corr[2] * lotated_pos[point_index].X() * lotated_pos[point_index].X() + corr[1] * lotated_pos[point_index].X() + corr[0];
    chi2_cand += kXWeight[point_index] * (fit_z_diff[point_index] - lotated_pos[point_index].X()) * (fit_z_diff[point_index] - lotated_pos[point_index].X());
  }

  double tgt_x_cand;
  grad = rot_cos / rot_sin;
  double BBtgt = corr[1] - grad;
  double CCtgt = corr[0] + tgt_z / rot_sin;
  det_tgt_fit = BBtgt * BBtgt - 4 * corr[2] * CCtgt;
  double z0_cand = 0.;
  double x0 = -9999.;
  if (det_tgt_fit > 0) {
    double fit_tgt1 = (-1. * BBtgt + sqrt(det_tgt_fit)) / (2. * corr[2]);
    double fit_tgt2 = (-1. * BBtgt - sqrt(det_tgt_fit)) / (2. * corr[2]);
    z0_cand = fabs(fit_tgt1) < fabs(fit_tgt2) ? fit_tgt1 : fit_tgt2; 
    x0 = rot_sin * z0_cand + rot_cos * (grad * z0_cand - tgt_z / rot_sin);
  }
  tgt_x_cand = x0;

//  int tmp_mid = module_ids[1] % 100;
//  double gtr100_ia_cand = atan(2 * corr[2] * gtr100_tr_z[ntrack] + corr[1]) - center_angle[tmp_mid] + rot_phi;
//  tmp_mid = gtr200_midx[i_200] % 100;
//  double gtr200_ia_cand = atan(2 * corr[2] * gtr200_tr_z[ntrack] + corr[1]) - center_angle[tmp_mid] + atan(rot_sin / rot_cos);
//  tmp_mid = gtr300_midx[i_300] % 100;
//  double gtr300_ia_cand = atan(2 * corr[2] * gtr300_tr_z[ntrack] + corr[1]) - center_angle[tmp_mid] + atan(rot_sin / rot_cos);

  if (chi2_cand < kRaughFitChiSquareThreshold[0] && fabs(corr[2]) < 0.001 && fabs(corr[0]) < 10.) {
    return true;
  }
  return false;
}

//bool E16ANA_TrackCandidates::IsYTrackCandidate(std::array<TVector3h, kNumGTRLayers>& pos_set) {
bool E16ANA_TrackCandidates::IsYTrackCandidate(const OneAxisClusterSet& cluster_set) {
  std::array<TVector3, kNumGTRLayers> pos_set = {cluster_set.gtr_clusters[0]->GlobalPos(*geometry),
                                                 cluster_set.gtr_clusters[1]->GlobalPos(*geometry),
                                                 cluster_set.gtr_clusters[2]->GlobalPos(*geometry)};

  std::array<double, kNumGTRLayers> gtr_y({pos_set[0].Y(), pos_set[1].Y(), pos_set[2].Y()});
  std::array<double, kNumGTRLayers> gtr_r({pow(pos_set[0].X() * pos_set[0].X() + pos_set[0].Z() * pos_set[0].Z(), 0.5),
                                           pow(pos_set[1].X() * pos_set[1].X() + pos_set[1].Z() * pos_set[1].Z(), 0.5),
                                           pow(pos_set[2].X() * pos_set[2].X() + pos_set[2].Z() * pos_set[2].Z(), 0.5)});
  if (2.7 * gtr_y[0] + 1.4 * gtr_y[1] > 20. || 2.7 * gtr_y[0] + gtr_y[2] > 20. || 1.4 * gtr_y[1] - gtr_y[2] > 20.) { // ???
    return false;
  }
  
  double r2 = 0.;
  double r  = 0.;
  double cy = 0.;
  double ry = 0.;
  double y  = 0.;
  for (int i = 0; i < kNumGTRLayers; ++i) {
    r2 += gtr_r[i] * gtr_r[i];
    r  += gtr_r[i];
    cy += kYWeight[i] * gtr_y[i];
    ry += kYWeight[i] * gtr_r[i] * gtr_y[i];
    y  += kYWeight[i] * gtr_y[i];
  }
  std::array<double, 2> corr({(r2 * y - r * ry) / (cy * r2 - r * r), (cy * ry - r * y) / (cy * r2 - r * r)});
  double chi2_cand = 0.;
  std::array<double, 3> fit_y;
  for (int i = 0; i < kNumGTRLayers; ++i) {
    fit_y[i] = corr[0] + corr[1] * gtr_r[i];
    chi2_cand += kYWeight[i] * (fit_y[i] - gtr_y[i]) * (fit_y[i] - gtr_y[i]);
  }
  if (chi2_cand < kRaughFitChiSquareThreshold[1] && fabs(corr[0]) < 15.) {
    return true;
  }
  return false;
}

void E16ANA_TrackCandidates::SetTrackCandidates() {
  for (auto& cands : track_candidates) {
    cands.clear();
    cands.reserve(kNumReserveTracks[2]);
  }
  auto& ssd = record->SSD();
  auto& gtr = record->GTR();
  std::array<std::vector<OneAxisClusterSet>, 2> cluster_sets;
  cluster_sets[0].reserve(kNumReserveTracks[0]);
  cluster_sets[1].reserve(kNumReserveTracks[1]);
  auto cluster_set = new OneAxisClusterSet();

//  std::array<TVector3&, E16ANA_TrackConstant::kNumTrackingLayers> x_pos_set;
  for (const auto& ssd_module_id : E16ANA_TrackConstant::kModuleIDs) {
    if (ssd_module_id == 105) {
      continue;
    }
    auto& ssd_cluster_ptrs = ssd.ClusterPtrs(ssd_module_id, 0, 0);
    for (const auto& gtr100_module_id : E16ANA_TrackConstant::kModuleIDs) {
      if (abs(gtr100_module_id - ssd_module_id) > 1) {
        continue;
      }
      auto& gtr100x_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsX);
      for (const auto& gtr200_module_id : E16ANA_TrackConstant::kModuleIDs) {
        if (abs(gtr200_module_id - ssd_module_id) > 1) {
          continue;
        }
        auto& gtr200x_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsX);
        for (const auto& gtr300_module_id : E16ANA_TrackConstant::kModuleIDs) {
          if (abs(gtr300_module_id - ssd_module_id) > 1) {
            continue;
          }
          auto& gtr300x_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsX);
          for (const auto& ssd_cluster : ssd_cluster_ptrs) {
//            auto ssd_pos = ssd_cluster->GlobalPos(*geometry);
//            x_pos_set[0] = ssd_pos;
            cluster_set->ssd_cluster = ssd_cluster;;
            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
//              auto gtr100_pos = gtr100_cluster->GlobalPos(*geometry);
//              x_pos_set[1] = gtr100_pos;
              cluster_set->gtr_clusters[0] = gtr100x_cluster;
              for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
//                auto gtr200_pos = gtr200_cluster->GlobalPos(*geometry);
//                x_pos_set[2] = gtr200_pos;
                cluster_set->gtr_clusters[1] = gtr200x_cluster;
                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
//                  auto gtr300_pos = gtr300_cluster->GlobalPos(*geometry);
//                  x_pos_set[3] = gtr300_pos;
                  cluster_set->gtr_clusters[2] = gtr300x_cluster;
                  for (int tgt_index = 0; tgt_index < 3; ++tgt_index) {
//                    auto tgt_z = E16ANA_TrackConstant::kTargetZ[tgt_index];
                    cluster_set->target_id= tgt_index;
//                    if (IsXTrackCandidate(tgt_z, x_pos_set)) {
                    if (IsXTrackCandidate(cluster_set)) {
//                      cluster_sets[0].emplace_back(OneAxisClusterSet());
//                      auto& cluster_set = cluster_sets[0].back();
//                      cluster_set.tgt_z = tgt_z;
//                      cluster_set.ssd_cluster = ssd_cluster;
//                      cluster_set.gtr_cluster = {gtr100x_cluster, gtr200x_cluster, gtr300x_cluster};
                      cluster_sets[0].emplace_back(*cluster_set);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

//  std::array<TVector3&, kNumGTRLayers> y_pos_set;
  for (const auto& gtr300_module_id : E16ANA_TrackConstant::kModuleIDs) {
    if (gtr300_module_id == 105) {
      continue;
    }
    auto& gtr300y_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsY);
    for (const auto& gtr200_module_id : E16ANA_TrackConstant::kModuleIDs) {
      if (abs(gtr200_module_id - gtr300_module_id) > 1) {
        continue;
      }
      auto& gtr200y_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsY);
      for (const auto& gtr100_module_id : E16ANA_TrackConstant::kModuleIDs) {
        if (abs(gtr100_module_id - gtr300_module_id) > 1) {
          continue;
        }
        auto& gtr100y_cluster_ptrs  = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsY);
        auto& gtr100yb_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsYb);
        for (const auto& gtr300y_cluster : gtr300y_cluster_ptrs) {
//          auto gtr300_pos = gtr300_cluster->GlobalPos(*geometry);
//          y_pos_set[2] = gtr300_cluster->GlobalPos(*geometry);
          cluster_set->gtr_clusters[2] = gtr300y_cluster;
          for (const auto& gtr200y_cluster : gtr200y_cluster_ptrs) {
//            auto gtr200_pos = gtr200_cluster->LocalPos(*geometry);
//            y_pos_set[1] = gtr200_cluster->GlobalPos(*geometry);
            cluster_set->gtr_clusters[1] = gtr200y_cluster;
            for (const auto& gtr100y_cluster : gtr100y_cluster_ptrs) {
//              auto gtr100_pos = gtr100_cluster->LocalPos(*geometry);
//              y_pos_set[0] = gtr100_cluster->GlobalPos(*geometry);
              cluster_set->gtr_clusters[0] = gtr100y_cluster;
//              if (IsYTrackCandidate(y_pos_set)) {
              if (IsYTrackCandidate(*cluster_set)) {
//                cluster_sets[1].emplace_back(OneAxisClusterSet());
//                auto& cluster_set = cluster_sets[1].back();
//                cluster_set.gtr_cluster = {gtr100y_cluster, gtr200y_cluster, gtr300y_cluster};
                cluster_sets[1].emplace_back(*cluster_set);
              }
            }
            for (const auto& gtr100yb_cluster : gtr100yb_cluster_ptrs) {
//              auto gtr100_pos = gtr100_cluster->LocalPos(*geometry);
//              y_set.gtr100_global_pos = gtr100_cluster->GlobalPos(*geometry);
              cluster_set->gtr_clusters[0] = gtr100yb_cluster;
//              if (IsYTrackCandidate(y_pos_set)) {
              if (IsYTrackCandidate(*cluster_set)) {
//                cluster_sets[1].emplace_back(OneAxisClusterSet());
//                auto& cluster_set = cluster_sets[1].back();
//                cluster_set.gtr_cluster = {gtr100y_cluster, gtr200y_cluster, gtr300y_cluster};
                cluster_sets[1].emplace_back(*cluster_set);
              }
            }
          }
        }
      }
    }
  }
  delete cluster_set;
 
  for (const auto& x_cand : cluster_sets[0]) {
    for (const auto& y_cand : cluster_sets[1]) {
      auto& ssdx = *x_cand.ssd_cluster;
      auto& gtrx = x_cand.gtr_clusters;
      auto& gtry = y_cand.gtr_clusters;
      bool is_same_module = true;
      for (int i = 0; i < kNumGTRLayers; ++i) {
        if (gtrx[i]->ModuleId() != gtry[i]->ModuleId() || fabs(gtrx[i]->Timing() - gtry[i]->Timing()) > kGTRTimeDiffThreshold) {
          is_same_module = false;
          break;
        }
      }
      if ((gtry[0]->IsY() && gtrx[0]->LocalPos().X() <= 0) || (gtry[0]->IsYb() && gtrx[0]->LocalPos().X() >= 0)) {
        is_same_module = false;
      }
      if (!is_same_module) {
        continue;
      }
//      track_candidates[x_cand.target_id].emplace_back(E16ANA_TrackCandidate(geometry, bfield_map, tmp_geoms));
      track_candidates[x_cand.target_id].emplace_back(E16ANA_TrackCandidate(geometry, bfield_map));
      auto& tmp_cand = track_candidates[x_cand.target_id].back();
      tmp_cand.SetTrackID(track_candidates.size() - 1);
      tmp_cand.SetCharge(x_cand.charge);
      tmp_cand.SetVertex(x_cand.target_id);
//      tmp_cand.SetSigma();
      auto& cluster_pairs = tmp_cand.ClusterPairs();
      cluster_pairs[0].Set(*geometry, 0, ssdx.ModuleId(), &ssdx);
      for (int i = 0; i < kNumGTRLayers; ++i) {
      cluster_pairs[1 + i].Set(*geometry, 1 + i, gtrx[i]->ModuleId(), gtrx[i], gtrx[i]);
      }
    }
  }
}

void E16ANA_TrackCandidates::SetHBDAndLGSignals() {
  auto& hbd = record->HBD();
  auto& lg  = record->LG();
  for (auto& cands : track_candidates) {
    for (auto& cand : cands) {
      auto& fit_results = cand.LocalFitResults();
      for (int l = E16ANA_TrackConstant::kHBD; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l) {
        auto& fit_pos = fit_results[l].local_pos;
        auto fit_module_id = fit_results[l].module_id;
        if (l == E16ANA_TrackConstant::kHBD) {
          auto& hits = hbd.HitPtrs(fit_module_id, 0, 0);
          auto& clusters = hbd.ClusterPtrs(fit_module_id, 0, 0);
          for (auto& hit : hits) {
            if (fabs((hit->LocalPos(*geometry) - fit_pos).Mag()) < kHBDProjectionThreshold) {
              cand.ProjectionHBDHits().emplace_back(hit);
            }
          }
          for (auto& cluster : clusters) {
            if (fabs((cluster->LocalPos() - fit_pos).Mag()) < kHBDProjectionThreshold) {
              cand.ProjectionHBDClusters().emplace_back(cluster);
            }
          }
        } else {
          auto& hits = lg.HitPtrs(fit_module_id, 0, 0);
          auto& clusters = lg.ClusterPtrs(fit_module_id, 0, 0);
          for (auto& hit : hits) {
            if (fabs((hit->LocalPos(*geometry) - fit_pos).Mag()) < kLGProjectionThreshold) {
              cand.ProjectionLGHits().emplace_back(hit);
            }
          }
          for (auto& cluster : clusters) {
            if (fabs((cluster->LocalPos() - fit_pos).Mag()) < kLGProjectionThreshold) {
              cand.ProjectionLGClusters().emplace_back(cluster);
            }
          }
        }
      }
    }
  }
  return;
}



void E16ANA_TrackCandidates::RequireLGCut() {
  for (int tgt_index = 0; tgt_index < E16ANA_TrackConstant::kNumTargets; ++tgt_index) {
    for (auto& cand : track_candidates[tgt_index]) {
      const auto& lg_fit = cand.LocalFitResult(E16ANA_TrackConstant::kLG);
      auto& tracked_lg_hits = cand.ProjectionLGHits();
      auto fit_mid = lg_fit.module_id;
      auto fit_lpos = lg_fit.local_pos;
      auto& lg_hits = record->LG().HitPtrs(fit_mid, 0, 0);
      for (const auto& lg_hit : lg_hits) {
        auto residual = lg_hit->LocalPos(*geometry) - fit_lpos;
        if (residual.Mag() < kLGResidualThreshold) {
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
  SetTrackCandidates();
  SetHBDAndLGSignals();
  RequireLGCut();
  std::array<std::vector<E16DST_DST1Cluster*>, E16ANA_TrackConstant::kNumTrackingLayers> used_clusters;
  for (int tgt_index = 0; tgt_index < E16ANA_TrackConstant::kNumTargets; ++tgt_index) {
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

void E16ANA_TrackCandidates::AddTracksToRecord() {
  auto& tracks = record->Tracks().Tracks();
  for (int target_index = 0; target_index < E16DST_DST1Constant::kNumTargets; ++target_index) {
    int prev_n_tracks = tracks.size();
    tracks.resize(prev_n_tracks + NumTrackCandidates(target_index));
    for (int track_index = 0; track_index < NumTrackCandidates(target_index); ++track_index) {
      auto& cand = track_candidates[target_index][track_index];
      auto& track = tracks[prev_n_tracks + track_index];
      track.SetTargetID(target_index);
      track.SetInitialPosAtTargetPlane(cand.FitVertex());
      track.SetInitialMom(cand.FitMomentum());
      for (int i = 0; i < E16DST_DST1Constant::kNumTrackingLayers; ++i) {
        auto& local_mom = cand.LocalFitResult(i).local_mom;
        track.SetTanTheta(i, local_mom.X() / local_mom.Z());
      } // HBD, LG
      track.SetHBDHitPtrs(cand.ProjectionHBDHits());
      track.SetHBDClusterPtrs(cand.ProjectionHBDClusters());
      track.SetLGHitPtrs(cand.ProjectionLGHits());
      track.SetLGClusterPtrs(cand.ProjectionLGClusters());
    }
  }
  return;
}
