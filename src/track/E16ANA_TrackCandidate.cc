#include "E16ANA_TrackCandidate.hh"

#include "TF1.h"
#include "TROOT.h"

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

void E16ANA_TrackCandidate::AddTrackHit(E16ANA_MultiTrack* single_track) {
  for (auto& fit_result : fit_results) {
    fit_result.set_flag = 0;
  }
  if (!CalcRoughMomentum()) {
    std::cerr << "Cannot calculate rough momentum" << std::endl;
  }
  int tid = 0; // only 1 track is fitted by the fitter
  single_track->Clear();
  single_track->SetInitialVertex(vtx, kVertexError);
  single_track->SetInitialMomentum(tid, mom);
  single_track->SetCharge(tid, charge);
  for (int l = 0; l < E16ANA_TrackConstant::kNumTrackingLayers; ++l) {
    auto& c = cluster_pairs[l];
    if (l == E16ANA_TrackConstant::kSSD) {
      single_track->AddHit(tid, c.LayerOrder(), geometry->SSD(E16ANA_TrackConstant::ModuleID2020To2013(c.ModuleID())), c.LocalPos(), sigma[l]);
    } else {
      single_track->AddHit(tid, c.LayerOrder(), geometry->GTR(E16ANA_TrackConstant::ModuleID2020To2013(c.ModuleID()), c.LayerOrder() - 1), c.LocalPos(), sigma[l]);
    }
  }
}

void E16ANA_TrackCandidate::Projection(E16ANA_MultiTrack* fitter) {
  projection_flag = 0;
  fitter->Clear();
  if (chisq >= 1.0e10) {
    return;
  }
  int tid = 0;
  TVector3 lpos(0., 0., 0.);
  TVector3 lsigma(0., 0., 0.);
  auto module_id = cluster_pairs[E16ANA_TrackConstant::kNumTrackingLayers - 1].ModuleID();
//  for (int l = E16ANA_TrackConstant::kHBD; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l) {
////    for (int mid = module_id - 2; mid <= module_id + 2; ++mid) {
////      if (mid == 105 || mid < E16ANA_TrackConstant::kModuleIDs[0] || mid > E16ANA_TrackConstant::kModuleIDs[E16ANA_TrackConstant::kNumModules - 1]) {
////        continue;
////      }
//    for (int mid = 101; mid <= 109; ++mid) {
//      auto mid2013 = E16ANA_TrackConstant::ModuleID2020To2013_27(mid);
//      if (l == E16ANA_TrackConstant::kHBD) {
//        auto tmp_geom = geometry->HBD(mid2013);
//        fitter->AddHit(tid, l - E16ANA_TrackConstant::kHBD, tmp_geom, lpos, lsigma);
//      } else {
//        auto tmp_geom = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG]);
//        fitter->AddHit(tid, l - E16ANA_TrackConstant::kHBD, tmp_geom, lpos, lsigma);
////        for (const auto& b : kLGBlocks[l - E16ANA_TrackConstant::kLG0]) {
////          auto tmp_geom = geometry->LG(mid2013, b);
////          fitter->AddHit(tid, l, tmp_geom, lpos, lsigma);
////        }
////        if (l == 5) {
////          auto tmp_geom = geometry->LGVD(mid2013);
////          fitter->AddHit(tid, l, tmp_geom, lpos, lsigma);
////        }
//      }
//    }
//  }
//  fitter->RungeKuttaTracking(tid, vtx_fit, mom_fit, charge);
//  for (int l = E16ANA_TrackConstant::kHBD; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l) {
//    fit_results[l].Clear();
//    std::vector<int> mids;
//    std::vector<TVector3> lposs;
//    std::vector<TVector3> lmoms;
//    fitter->GetFitLPos(0, l - E16ANA_TrackConstant::kHBD, mids, lposs);
//    fitter->GetFitLMom(0, l - E16ANA_TrackConstant::kHBD, mids, lmoms);
//    std::vector<FitResult> results;
//    double r;
//    int min_r_hit = E16DST_DST1Constant::kInvalidValue;
//    for (int hit_index = 0; hit_index < mids.size(); ++hit_index) {
//      auto mid = mids[hit_index];
//      auto mid2020 = E16ANA_TrackConstant::ModuleID2013To2020_27(mids[hit_index]);
//      auto lpos = lposs[hit_index];
//      auto lmom = lmoms[hit_index];
//      if (fabs(lpos.X()) >= fabs(E16DST_DST1Constant::kInvalidValue)) {
//        continue;
//      }
//      results.emplace_back(FitResult());
//      auto& result = results.back();
//      TVector3 gpos;
//      TVector3 gmom;
//      if (l = E16ANA_TrackConstant::kHBD) {
//        gpos = geometry->HBD(mid)->GetGPos(lpos);
//        gmom = geometry->HBD(mid)->GetGMom(lmom);
//      } else {
//        gpos = geometry->LG(mid, kTypicalLGBlocks[l - E16ANA_TrackConstant::kHBD])->GetGPos(lpos);
//        gmom = geometry->LG(mid, kTypicalLGBlocks[l - E16ANA_TrackConstant::kHBD])->GetGMom(lmom);
//      }
//      result.Set(l, mid2020, lpos, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
//      if (hit_index == 0) {
//        min_r_hit = 0;
//        r = gpos.Mag();
//      } else if (gpos.Mag() < r) {
//        min_r_hit = hit_index;
//        r = gpos.Mag();
//      }
//    }
//    if (min_r_hit == E16DST_DST1Constant::kInvalidValue) {
//      continue;
//    }
//    fit_results[l] = results[min_r_hit];
//    projection_flag += pow(2, l - E16ANA_TrackConstant::kHBD);
//  }
  int lid = 0; // only 1 layer in 1 RK
  int hid = 0; // oonly 1 hit in 1 RK
  std::vector<int> mids;
  std::vector<TVector3> lposs;
  std::vector<TVector3> lmoms;
  for (int l = E16ANA_TrackConstant::kHBD; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l) {
    fit_results[l].Clear();
    auto& result = fit_results[l];
//    int nstps;
    double r;
    for (int mid = module_id - 2; mid <= module_id + 2; ++mid) {
      if (mid == 105 || mid < E16ANA_TrackConstant::kModuleIDs.front() || mid > E16ANA_TrackConstant::kModuleIDs.back()) {
        continue;
      }
      auto mid2013 = E16ANA_TrackConstant::ModuleID2020To2013_27(mid);
      fitter->Clear();
      if (l == E16ANA_TrackConstant::kHBD) {
        auto tmp_geom = geometry->HBD(mid2013);
        fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
      } else {
        auto tmp_geom = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG]);
        fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
      }
      fitter->SetMaxSteps(kProjectionMaxSteps);
      fitter->RungeKuttaTracking(tid, vtx_fit, mom_fit, charge);
      fitter->GetFitLPos(tid, lid, mids, lposs);
      fitter->GetFitLMom(tid, lid, mids, lmoms);
      auto lpos = lposs[hid];
      auto lmom = lmoms[hid];
      if (fabs(lpos.X()) >= fabs(E16DST_DST1Constant::kInvalidValue)) {
        continue;
      }
      TVector3 gpos;
      TVector3 gmom;
      if (l == E16ANA_TrackConstant::kHBD) {
        gpos = geometry->HBD(mid2013)->GetGPos(lpos);
        gmom = geometry->HBD(mid2013)->GetGMom(lmom);
      } else {
        gpos = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG0])->GetGPos(lpos);
        gmom = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG0])->GetGMom(lmom);
      }
      if (result.set_flag == 0) {
        result.Set(l, mid, lpos, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
//        nstps = fitter->NumSteps();
        r = gpos.Mag();
//      } else if (fitter->NumSteps() < nstps) {
      } else if (gpos.Mag() < r) {
        result.Set(l, mid, lpos, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
//        nstps = fitter->NumSteps();
        r = gpos.Mag();
      }
    }
    if (result.set_flag == 1) {
      projection_flag += pow(2, l - E16ANA_TrackConstant::kHBD);
    }
  }
//auto& track_steps = fitter->GetTrackSteps(tid);
//for (int s = 0; s < track_steps.size(); ++s) {
//  auto& step = track_steps[s];
//  E16MESSAGE("step %d: (%lf, %lf, %lf), r = %lf", s, step.X(), step.Y(), step.Z(), step.Mag());
//}
//for (int l = 4; l < 8; ++l) {
//  auto& result = fit_results[l];
//  auto& gpos = result.global_pos;
//  if (result.set_flag == 0) {
//    E16INFO("%s: RK failure", E16ANA_TrackConstant::kDetectorName[l].c_str());
//  } else {
//    E16INFO("%s, Module ID = %d: (%lf, %lf, %lf), r = %lf", E16ANA_TrackConstant::kDetectorName[l].c_str(), result.module_id, gpos.X(), gpos.Y(), gpos.Z(), gpos.Mag());
//  }
//}
  return;
}

void E16ANA_TrackCandidate::UpdateFitResult(E16ANA_MultiTrack* fitter) {
  int tid = 0;
  int hid = 0;
  vtx_fit = fitter->GetFitVertex();
  mom_fit = fitter->GetFitMomentum(tid);
  minimize_status = fitter->GetMinimizeStatus();
  matrix_status = fitter->GetMatrixStatus();
  n_steps = fitter->GetTrackSteps(tid).size();
  n_calls = fitter->GetNumCalls();
  for (int l = 0; l < E16ANA_TrackConstant::kNumTrackingLayers; ++l) {
    fit_results[l].Clear();
    std::vector<TVector3> lpos;
    std::vector<TVector3> lmom;
    std::vector<int> mid;
    fitter->GetFitLPos(tid, l, mid, lpos);
    fitter->GetFitLMom(tid, l, mid, lmom);
    TVector3 gpos;
    TVector3 gmom;
    auto mid2020 = E16ANA_TrackConstant::ModuleID2013To2020(mid[hid]);
    if (l <= E16ANA_TrackConstant::kSSD) {
      gpos = geometry->SSD(mid[hid])->GetGPos(lpos[hid]);
      gmom = geometry->SSD(mid[hid])->GetGMom(lmom[hid]);
    } else {
      gpos = geometry->GTR(mid[hid], l - 1)->GetGPos(lpos[hid]);
      gmom = geometry->GTR(mid[hid], l - 1)->GetGMom(lmom[hid]);
    }
    auto rpos = cluster_pairs[l].LocalPos() - lpos[hid];
    fit_results[l].Set(l, mid2020, lpos[hid], lmom[hid], gpos, gmom, rpos);
  }
  Projection(fitter);
  return;
}

double E16ANA_TrackCandidate::Fit(E16ANA_MultiTrack* fitter, bool vertex_xy_fix_flag, bool py_fix_flag, bool vertex_z_fix_flag) {
  fitter->Clear();
//  fitter->SetPrintLevel(kRKPrintLevel);
  this->AddTrackHit(fitter);
  fitter->SetMaxSteps(kTrackingMaxSteps);
  chisq = fitter->Fit(vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag);
  UpdateFitResult(fitter);
//E16INFO("vtx (set): (%lf, %lf, %lf)", vtx.X(), vtx.Y(), vtx.Z());
//E16INFO("vtx (fit): (%lf, %lf, %lf)", vtx_fit.X(), vtx_fit.Y(), vtx_fit.Z());
//E16INFO("mom (set): (%lf, %lf, %lf)", mom.X(), mom.Y(), mom.Z());
//E16INFO("mom (fit): (%lf, %lf, %lf)", mom_fit.X(), mom_fit.Y(), mom_fit.Z());
//E16INFO("SSD (hit): (%lf, %lf, %lf)", cluster_pairs[0].GlobalPos().X(), cluster_pairs[0].GlobalPos().Y(), cluster_pairs[0].GlobalPos().Z());
//E16INFO("SSD (fit): (%lf, %lf, %lf)", fit_results[0].global_pos.X(),    fit_results[0].global_pos.Y(),    fit_results[0].global_pos.Z());
//E16INFO("GTR (hit): (%lf, %lf, %lf)", cluster_pairs[1].GlobalPos().X(), cluster_pairs[1].GlobalPos().Y(), cluster_pairs[1].GlobalPos().Z());
//E16INFO("GTR (fit): (%lf, %lf, %lf)", fit_results[1].global_pos.X(),    fit_results[1].global_pos.Y(),    fit_results[1].global_pos.Z());
//E16INFO("GTR (hit): (%lf, %lf, %lf)", cluster_pairs[2].GlobalPos().X(), cluster_pairs[2].GlobalPos().Y(), cluster_pairs[2].GlobalPos().Z());
//E16INFO("GTR (fit): (%lf, %lf, %lf)", fit_results[2].global_pos.X(),    fit_results[2].global_pos.Y(),    fit_results[2].global_pos.Z());
//E16INFO("GTR (hit): (%lf, %lf, %lf)", cluster_pairs[3].GlobalPos().X(), cluster_pairs[3].GlobalPos().Y(), cluster_pairs[3].GlobalPos().Z());
//E16INFO("GTR (fit): (%lf, %lf, %lf)", fit_results[3].global_pos.X(),    fit_results[3].global_pos.Y(),    fit_results[3].global_pos.Z());
//auto& track_steps = fitter->GetTrackSteps(0);
//for (int s = 0; s < track_steps.size(); ++s) {
//  auto& step = track_steps[s];
//  E16MESSAGE("step %d: (%lf, %lf, %lf)", s, step.X(), step.Y(), step.Z());
//}
  return chisq;
}

void E16ANA_TrackCandidates::CalcInverseMatrix(const std::array<double, kNumTrackingLayersWTarget>& zz, std::array<std::array<double, kNumRaughFitDegree[0]>, kNumRaughFitDegree[0]>* line) {
  double m11 = zz[4];
  double m12 = zz[3];
  double m21 = zz[3];
  double m13 = zz[2];
  double m22 = zz[2];
  double m31 = zz[2];
  double m23 = zz[1];
  double m32 = zz[1];
  double m33 = zz[0];
  double det = m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 -
               m13 * m22 * m31 - m12 * m21 * m33 - m11 * m23 * m32;
  (*line)[0][0] =       (m22 * m33 - m23 * m32) / det;
  (*line)[0][1] = -1. * (m12 * m33 - m13 * m32) / det;
  (*line)[0][2] =       (m12 * m23 - m13 * m22) / det;
  (*line)[1][0] = -1. * (m21 * m33 - m23 * m31) / det;
  (*line)[1][1] =       (m11 * m33 - m13 * m31) / det;
  (*line)[1][2] = -1. * (m11 * m23 - m13 * m21) / det;
  (*line)[2][0] =       (m21 * m32 - m22 * m31) / det;
  (*line)[2][1] = -1. * (m11 * m32 - m12 * m31) / det;
  (*line)[2][2] =       (m11 * m22 - m12 * m21) / det;
  return;
}

bool E16ANA_TrackCandidates::IsXTrackCandidate(OneAxisClusterSet* cluster_set) {
  auto& tgt_z = E16ANA_TrackConstant::kTargetZ[cluster_set->target_id];
//  std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> pos_set = {cluster_set->ssd_cluster->GlobalPos(*geometry),
//                                                                            cluster_set->gtr_clusters[0]->GlobalPos(*geometry),
//                                                                            cluster_set->gtr_clusters[1]->GlobalPos(*geometry),
//                                                                            cluster_set->gtr_clusters[2]->GlobalPos(*geometry)};
//  std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> pos_set = cluster_set->global_poss;
////  if (pos_set[3].X() * pos_set[0].X() < 0. || pos_set[3].X() * pos_set[1].X() < 0. || pos_set[3].X() * pos_set[2].X() < 0.) {
////    return false;
////  }
//  double x[kNumTrackingLayersWTarget], z[kNumTrackingLayersWTarget];
//  x[0] = 0.;
//  z[0] = 0.;
//  auto angle = -std::atan2(pos_set[E16ANA_TrackConstant::kGTR300].X(), pos_set[E16ANA_TrackConstant::kGTR300].Z() - tgt_z);
//  for (int i = 0; i < E16ANA_TrackConstant::kNumTrackingLayers; ++i) {
//    pos_set[i] -= TVector3(0., 0., tgt_z);
//    pos_set[i].RotateY(angle);
//    x[1 + i] = pos_set[i].X();
//    z[1 + i] = pos_set[i].Z();
//  }
//  TGraph xz_pos(kNumTrackingLayersWTarget, z, x);
//  xz_pos.Fit("pol2", "Q");
//  std::array<double, kNumRaughFitDegree[0]> coef;
//  auto fit_func = static_cast<TF1*>(gROOT->FindObject("pol2"));
//  for (int i = 0; i < kNumRaughFitDegree[0]; ++i) {
//    coef[i] = fit_func->GetParameter(i);
//  }
//  cluster_set->charge = coef[2] > 0 ? 1 : -1;
//  auto chi2_cand = fit_func->GetChisquare();
//  auto pol2_det = coef[1] * coef[1] - 4. * coef[2] * coef[0];
//  if (pol2_det < 0) {
//    return false;
//  }
//  std::array<double, 2> x0_point = {(-coef[1] + sqrt(pol2_det)) / (2. * coef[2]), (-coef[1] - sqrt(pol2_det)) / (2. * coef[2])};
//  auto target_x_fit = fabs(x0_point[0]) < fabs(x0_point[1]) ? fabs(x0_point[0]) : fabs(x0_point[1]);
//  if (target_x_fit > kRaughFitTargetXThreshold) {
//    return false;
//  }

  auto& pos_set = cluster_set->global_poss;
//  if (pos_set[3].X() * pos_set[0].X() < 0. || pos_set[3].X() * pos_set[1].X() < 0. || pos_set[3].X() * pos_set[2].X() < 0.) {
//    return false;
//  }
  std::array<TVector3, kNumTrackingLayersWTarget> lotated_pos;
//  CalcLotatePos(pos_set, tgt_z, &lotated_pos);
  auto rot_phi = std::atan2(pos_set[3].X(), pos_set[3].Z() - tgt_z);
  auto rot_cos = std::cos(rot_phi);
  auto rot_sin = std::sin(rot_phi);
  lotated_pos[0] = {0., 0., 0.};
  lotated_pos[1] = Lotate(rot_cos, rot_sin, tgt_z, pos_set[0]);
  lotated_pos[2] = Lotate(rot_cos, rot_sin, tgt_z, pos_set[1]);
  lotated_pos[3] = Lotate(rot_cos, rot_sin, tgt_z, pos_set[2]);
  lotated_pos[4] = Lotate(rot_cos, rot_sin, tgt_z, pos_set[3]);

//  CalcQuadCurve();
  std::array<double, kNumTrackingLayersWTarget> zz;
  std::array<double, kNumRaughFitDegree[0]> zx;
  zz.fill(0.);
  zx.fill(0.);
  for (int i = 0; i < kNumTrackingLayersWTarget; ++i) {
    AddMatrixElement(kXWeight[i], lotated_pos[i], &zz, &zx);
  }
  std::array<std::array<double, kNumRaughFitDegree[0]>, kNumRaughFitDegree[0]> line;
  CalcInverseMatrix(zz, &line);
  std::array<double, kNumRaughFitDegree[0]> coef;
  std::array<double, kNumTrackingLayersWTarget> fit_z_diff;
  CalcCoefficients(zx, line, &coef);
  cluster_set->charge = coef[2] > 0 ? 1 : -1;

//  CalcTargetZ();
  double grad = -1. * (rot_sin / rot_cos);
  double BB_fit = coef[1] - grad;
  double det_tgt_fit = BB_fit * BB_fit - 4 * coef[2] * coef[0];
  double tgt_z_cand = E16DST_DST1Constant::kInvalidValue;
  if (det_tgt_fit > 0) {
    double fit_tgt1  = (-1. * BB_fit + sqrt(det_tgt_fit)) / (2. * coef[2]);
    double fit_tgt2  = (-1. * BB_fit - sqrt(det_tgt_fit)) / (2. * coef[2]);
    double tgt_z_prime_cand = fabs(fit_tgt1) < fabs(fit_tgt2) ? fit_tgt1 : fit_tgt2; 
    tgt_z_cand = rot_cos * tgt_z_prime_cand - rot_sin * grad * tgt_z_prime_cand;
  }

//  double chi2_cand = 0.;
//  for (int point_index = 0; point_index < kNumTrackingLayersWTarget; ++point_index) {
//    fit_z_diff[point_index] = coef[2] * lotated_pos[point_index].X() * lotated_pos[point_index].X() + coef[1] * lotated_pos[point_index].X() + coef[0];
//    chi2_cand += kXWeight[point_index] * (fit_z_diff[point_index] - lotated_pos[point_index].X()) * (fit_z_diff[point_index] - lotated_pos[point_index].X());
//  }

//  CalcTargetX();
  double tgt_x_cand;
  grad = rot_cos / rot_sin;
  double BBtgt = coef[1] - grad;
//  double CCtgt = coef[0] + tgt_z / rot_sin;
  double CCtgt = coef[0];
  det_tgt_fit = BBtgt * BBtgt - 4 * coef[2] * CCtgt;
  double z0_cand = 0.;
  double x0 = E16DST_DST1Constant::kInvalidValue;
  if (det_tgt_fit > 0) {
    double fit_tgt1 = (-1. * BBtgt + sqrt(det_tgt_fit)) / (2. * coef[2]);
    double fit_tgt2 = (-1. * BBtgt - sqrt(det_tgt_fit)) / (2. * coef[2]);
    z0_cand = fabs(fit_tgt1) < fabs(fit_tgt2) ? fit_tgt1 : fit_tgt2; 
//    x0 = rot_sin * z0_cand + rot_cos * (grad * z0_cand - tgt_z / rot_sin);
    x0 = rot_sin * z0_cand + rot_cos * grad * z0_cand;
  }
  tgt_x_cand = x0;

//  CalcChiSquare();
  double chi2_cand = 0.;
  double fit_posx[kNumTrackingLayersWTarget];
  for (int i = 0; i < kNumTrackingLayersWTarget; ++i) {
    fit_posx[i] = coef[2] * lotated_pos[i].Z() * lotated_pos[i].Z() + coef[1] * lotated_pos[i].Z() + coef[0];
    chi2_cand += kXWeight[i] * (fit_posx[i] - lotated_pos[i].X()) * (fit_posx[i] - lotated_pos[i].X());
  }

  if (chi2_cand < kRaughFitChiSquareThreshold[0] && fabs(coef[2]) < 0.001 && fabs(coef[0]) < 10.) {
    return true;
  }
  return false;
}

//bool E16ANA_TrackCandidates::IsYTrackCandidate(std::array<TVector3h, kNumGTRLayers>& pos_set) {
bool E16ANA_TrackCandidates::IsYTrackCandidate(const OneAxisClusterSet& cluster_set) {
//  std::array<TVector3, kNumGTRLayers> pos_set = {cluster_set.gtr_clusters[0]->GlobalPos(*geometry),
//                                                 cluster_set.gtr_clusters[1]->GlobalPos(*geometry),
//                                                 cluster_set.gtr_clusters[2]->GlobalPos(*geometry)};
//  std::array<TVector3, kNumGTRLayers> pos_set = {cluster_set.global_poss[E16ANA_TrackConstant::kGTR100],
//                                                 cluster_set.global_poss[E16ANA_TrackConstant::kGTR200],
//                                                 cluster_set.global_poss[E16ANA_TrackConstant::kGTR300]};
//
//  double r[kNumGTRLayers];
//  double y[kNumGTRLayers];
//  for (int i = 0; i < kNumGTRLayers; ++i) {
//    r[i] = sqrt(pos_set[i].X() * pos_set[i].X() + pos_set[i].Z() * pos_set[i].Z());
//    y[i] = pos_set[i].Y();
//  }
//  TGraph ry_pos(kNumGTRLayers, r, y);
//  ry_pos.Fit("pol1", "Q");
//  std::array<double, kNumRaughFitDegree[1]> coef;
//  auto fit_func = static_cast<TF1*>(gROOT->FindObject("pol1"));
//  for (int i = 0; i < kNumRaughFitDegree[1]; ++i) {
//    coef[i] = fit_func->GetParameter(i);
//  }
//  auto chi2_cand = fit_func->GetChisquare();

  auto& pos_set = cluster_set.global_poss;
  std::array<double, kNumGTRLayers> gtr_y({pos_set[1].Y(), pos_set[2].Y(), pos_set[3].Y()});
  std::array<double, kNumGTRLayers> gtr_r({sqrt(pos_set[1].X() * pos_set[1].X() + pos_set[1].Z() * pos_set[1].Z()),
                                           sqrt(pos_set[2].X() * pos_set[2].X() + pos_set[2].Z() * pos_set[2].Z()),
                                           sqrt(pos_set[3].X() * pos_set[3].X() + pos_set[3].Z() * pos_set[3].Z())});
//  if (fabs(kGTRSizeCoef[0] * gtr_y[0] + kGTRSizeCoef[1] * gtr_y[1]) > kGTRYDiffThreshold ||
//      fabs(kGTRSizeCoef[0] * gtr_y[0] + kGTRSizeCoef[2] * gtr_y[2]) > kGTRYDiffThreshold ||
//      fabs(kGTRSizeCoef[1] * gtr_y[1] - kGTRSizeCoef[2] * gtr_y[2]) > kGTRYDiffThreshold) { // Is GTR 100 y right?
  if (fabs(kGTRSizeCoef[0] * gtr_y[0] - kGTRSizeCoef[1] * gtr_y[1]) > kGTRYDiffThreshold ||
      fabs(kGTRSizeCoef[0] * gtr_y[0] - kGTRSizeCoef[2] * gtr_y[2]) > kGTRYDiffThreshold ||
      fabs(kGTRSizeCoef[1] * gtr_y[1] - kGTRSizeCoef[2] * gtr_y[2]) > kGTRYDiffThreshold) { // Is GTR 100 y right?
    return false;
  }
  
  double r2 = 0.;
  double r  = 0.;
  double c  = 0.;
  double ry = 0.;
  double y  = 0.;
  for (int i = 0; i < kNumGTRLayers; ++i) {
    r2 += kYWeight[i] * gtr_r[i] * gtr_r[i];
    r  += kYWeight[i] * gtr_r[i];
    c  += kYWeight[i];
    ry += kYWeight[i] * gtr_r[i] * gtr_y[i];
    y  += kYWeight[i] * gtr_y[i];
  }
  std::array<double, kNumRaughFitDegree[1]> coef({(r2 * y  - r * ry) / (c * r2 - r * r),
                                                  (c  * ry - r * y)  / (c * r2 - r * r)});
  double chi2_cand = 0.;
  std::array<double, kNumGTRLayers> fit_y;
  for (int i = 0; i < kNumGTRLayers; ++i) {
    fit_y[i] = coef[0] + coef[1] * gtr_r[i];
    chi2_cand += kYWeight[i] * (fit_y[i] - gtr_y[i]) * (fit_y[i] - gtr_y[i]);
  }
  if (chi2_cand < kRaughFitChiSquareThreshold[1] && fabs(coef[0]) < kRaughFitTargetYThreshold) {
    return true;
  }
  return false;
}

void E16ANA_TrackCandidates::SearchTrackCandidates() {
  for (auto& cands : track_candidates) {
    cands.clear();
    cands.reserve(kNumReserveTracks[2]);
  }
  auto& ssd = record->SSD();
  auto& gtr = record->GTR();
//E16INFO("number of SSD clusters: %d", ssd.NumClusters());
//E16INFO("number of GTR clusters: %d", gtr.NumClusters());
  std::array<std::vector<OneAxisClusterSet>, 2> cluster_sets;
  cluster_sets[0].reserve(kNumReserveTracks[0]);
  cluster_sets[1].reserve(kNumReserveTracks[1]);
  auto cluster_set = new OneAxisClusterSet();

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
            cluster_set->ssd_cluster = ssd_cluster;
            cluster_set->global_poss[E16ANA_TrackConstant::kSSD] = ssd_cluster->GlobalPos(*geometry);
            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
              cluster_set->gtr_clusters[0] = gtr100x_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100x_cluster->GlobalPos(*geometry);
              for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
                cluster_set->gtr_clusters[1] = gtr200x_cluster;
                cluster_set->global_poss[E16ANA_TrackConstant::kGTR200] = gtr200x_cluster->GlobalPos(*geometry);
                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
                  cluster_set->gtr_clusters[2] = gtr300x_cluster;
                  cluster_set->global_poss[E16ANA_TrackConstant::kGTR300] = gtr300x_cluster->GlobalPos(*geometry);
                  for (int tgt_index = 0; tgt_index < 3; ++tgt_index) {
                    cluster_set->target_id= tgt_index;
                    if (IsXTrackCandidate(cluster_set)) {
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
          cluster_set->gtr_clusters[2] = gtr300y_cluster;
          cluster_set->global_poss[E16ANA_TrackConstant::kGTR300] = gtr300y_cluster->GlobalPos(*geometry);
          for (const auto& gtr200y_cluster : gtr200y_cluster_ptrs) {
            cluster_set->gtr_clusters[1] = gtr200y_cluster;
            cluster_set->global_poss[E16ANA_TrackConstant::kGTR200] = gtr200y_cluster->GlobalPos(*geometry);
            for (const auto& gtr100y_cluster : gtr100y_cluster_ptrs) {
              cluster_set->gtr_clusters[0] = gtr100y_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100y_cluster->GlobalPos(*geometry);
              if (IsYTrackCandidate(*cluster_set)) {
                cluster_sets[1].emplace_back(*cluster_set);
              }
            }
            for (const auto& gtr100yb_cluster : gtr100yb_cluster_ptrs) {
              cluster_set->gtr_clusters[0] = gtr100yb_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100yb_cluster->GlobalPos(*geometry);
              if (IsYTrackCandidate(*cluster_set)) {
                cluster_sets[1].emplace_back(*cluster_set);
              }
            }
          }
        }
      }
    }
  }
  delete cluster_set;

//std::cout << cluster_sets[0].size() << ", " << cluster_sets[1].size() << std::endl;
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
      track_candidates[x_cand.target_id].emplace_back(E16ANA_TrackCandidate(geometry, bfield_map));
      auto& tmp_cand = track_candidates[x_cand.target_id].back();
      tmp_cand.SetTrackID(track_candidates[x_cand.target_id].size() - 1);
      tmp_cand.SetCharge(x_cand.charge);
      tmp_cand.SetVertex(x_cand.target_id);
      tmp_cand.SetDefaultSigma();
      auto& cluster_pairs = tmp_cand.ClusterPairs();
      cluster_pairs[0].Set(geometry, 0, ssdx.ModuleId(), x_cand.global_poss[0], &ssdx);
      for (int i = 0; i < kNumGTRLayers; ++i) {
        cluster_pairs[1 + i].Set(geometry, 1 + i, gtrx[i]->ModuleId(), x_cand.global_poss[1 + i], y_cand.global_poss[1 + i], gtrx[i], gtry[i]);
      }
    }
  }
}

void E16ANA_TrackCandidates::Fit() {
  for (int target_index = 0; target_index < E16ANA_TrackConstant::kNumTargets; ++target_index) {
    for (auto& cand : track_candidates[target_index]) {
      cand.Fit(fitter, vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag);
    }
  }
}

void E16ANA_TrackCandidates::SearchHBDAndLGHits() {
  auto& hbd = record->HBD();
  auto& lg  = record->LG();
  for (auto& cands : track_candidates) {
    for (auto& cand : cands) {
      if (cand.ChiSquare() >= 1.0e10) {
        continue;
      }
      auto& fit_results = cand.LocalFitResults();
      for (int l = E16ANA_TrackConstant::kHBD; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l) {
        if (fit_results[l].set_flag == 0) {
          continue;
        }
        auto& fit_pos = fit_results[l].global_pos;
        if (fit_results[l].set_flag == 0) {
          continue;
        }
        auto fit_module_id = fit_results[l].module_id;
        if (l == E16ANA_TrackConstant::kHBD) {
          auto& hits = hbd.HitPtrs(fit_module_id, 0, 0);
          auto& clusters = hbd.ClusterPtrs(fit_module_id, 0, 0);
          for (auto& hit : hits) {
            if (fabs((hit->GlobalPos(*geometry) - fit_pos).Mag()) < kHBDProjectionThreshold) {
              cand.ProjectedHBDHits().emplace_back(hit);
            }
          }
          for (auto& cluster : clusters) {
            if (fabs((cluster->GlobalPos(*geometry) - fit_pos).Mag()) < kHBDProjectionThreshold) {
              cand.ProjectedHBDClusters().emplace_back(cluster);
            }
          }
        } else {
          auto& hits = lg.HitPtrs(fit_module_id, 0, 0);
          auto& clusters = lg.ClusterPtrs(fit_module_id, 0, 0);
          for (auto& hit : hits) {
            int lgh = hit->ChannelId() / 10;
            if (l == E16ANA_TrackConstant::kLG0) {
              if (lgh != 0 && lgh != 5) {
                continue;
              }
            } else if (l == E16ANA_TrackConstant::kLG1) {
              if (lgh != 1 && lgh != 4) {
                continue;
              }
            } else {
              if (lgh != 2 && lgh != 3) {
                continue;
              }
            }
//E16INFO("LG Module ID: %d, Block ID: %d, Length: %lf", fit_module_id, hit->ChannelId(), fabs((hit->GlobalPos(*geometry) - fit_pos).Mag()));
//E16INFO("LG hit: (%lf, %lf, %lf)", hit->GlobalPos(*geometry).X(), hit->GlobalPos(*geometry).Y(), hit->GlobalPos(*geometry).Z());
//E16INFO("fit: (%lf, %lf, %lf)", fit_pos.X(), fit_pos.Y(), fit_pos.Z());
//E16INFO("LG hit - fit: %lf", fabs((hit->GlobalPos(*geometry) - fit_pos).Mag()));
            if ((hit->GlobalPos(*geometry) - fit_pos).Mag() < kLGProjectionThreshold) {
              cand.ProjectedLGHits().emplace_back(hit);
            }
          }
          for (auto& cluster : clusters) {
            if ((cluster->GlobalPos(*geometry) - fit_pos).Mag() < kLGProjectionThreshold) {
              cand.ProjectedLGClusters().emplace_back(cluster);
            }
          }
//int bid = -1000;
//double r = 10000.;
//for (int i = 0; i < 6; ++i) {
//  for (int j = 0; j < 7; ++j) {
//    if (l != 7 && j == 6) {
//      continue;
//    }
//    auto gpos = geometry->LG(E16ANA_TrackConstant::ModuleID2020To2013_27(fit_module_id), 10 * i + j)->GetDetectorCenter();
//    auto length = (gpos - fit_pos).Mag();
//    if (length < r) {
//      r = length;
//      bid = 10 * i + j;
//    }
//  }
//}
//E16INFO("LG Module ID: %d, Block ID: %d, Length: %lf", fit_module_id, bid, r);
        }
      }
    }
  }
  return;
}

void E16ANA_TrackCandidates::SelectTracks() {
  for (auto& cands : selected_track_candidates) {
    cands.clear();
  }
  SearchTrackCandidates();
//E16INFO("number of track candidate: %d", track_candidates[0].size());
//E16INFO("number of track candidate: %d", track_candidates[1].size());
//E16INFO("number of track candidate: %d", track_candidates[2].size());
//for (int i = 0; i < 3; ++i) {
//  for (auto& cand : track_candidates[i]) {
//    for (auto& pair : cand.ClusterPairs()) {
//      auto& pos = pair.GlobalPos();
//      std::cout << pos(0) << ", " << pos(1) << ", " << pos(2) << std::endl;
//    }
//  }
//}
  Fit();
  SearchHBDAndLGHits();
  std::array<std::vector<E16DST_DST1Cluster*>, E16ANA_TrackConstant::kNumTrackingLayers> used_clusters;
  for (int tgt_index = 0; tgt_index < E16ANA_TrackConstant::kNumTargets; ++tgt_index) {
    for (auto& clsts : used_clusters) {
      clsts.clear();
    }
    std::sort(track_candidates[tgt_index].begin(), track_candidates[tgt_index].end(), [](auto& lhs, auto& rhs) {
      return lhs.ChiSquare() < rhs.ChiSquare();
    });
    for (auto& track_candidate : track_candidates[tgt_index]) {
      if (track_candidate.ProjectedLGHits().size() == 0) {
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
      selected_track_candidates[tgt_index].emplace_back(&track_candidate);
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
      track.SetHBDHitPtrs(cand.ProjectedHBDHits());
      track.SetHBDClusterPtrs(cand.ProjectedHBDClusters());
      track.SetLGHitPtrs(cand.ProjectedLGHits());
      track.SetLGClusterPtrs(cand.ProjectedLGClusters());
    }
  }
  return;
}
