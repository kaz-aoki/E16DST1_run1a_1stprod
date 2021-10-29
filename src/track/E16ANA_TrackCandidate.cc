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
    init_mom = CalcRoughMomentum(cluster_pairs[l0].GlobalPos(), cluster_pairs[l1].GlobalPos());
  }else{
    init_mom = CalcRoughMomentum(cluster_pairs[l1].GlobalPos(), cluster_pairs[l0].GlobalPos());
  }
  return true;
}

bool E16ANA_TrackCandidate::CalcRoughMomentumV2() {
  int n=5;
  double x[5],y[5];
  double By = 1.3; 
  x[0] = 0;
  y[0] = init_pos.Z();
  double the;
  for (int l = 0; l < E16ANA_TrackConstant::kNumTrackingLayers; ++l) {
    auto& c = cluster_pairs[l];
    x[l+1] = c.GlobalPos().X();
    y[l+1] = c.GlobalPos().Z();
    if(l==E16ANA_TrackConstant::kNumTrackingLayers-1){
      double fr = sqrt(x[l+1]*x[l+1]+(y[l+1]-y[0])*(y[l+1]-y[0]));
      the      = c.GlobalPos().Y()/fr;
    }
  }
  double  sx=0., sy=0., mxx=0., myy=0., mxy=0., mxz=0., myz=0., mzz=0.;
  double  xa, ya, xi, yi, zi, mz, cov_xy, var_z, a3, a2, a1, a0, a22, a33;
  double  xn, yn, dyn, xnnew, ynnew, det, xc, yc, serr=0., dum;
  int itmax=99;
  for (int i=0; i<n; i++){
    sx += x[i];   sy += y[i];
  }
  xa = sx/n;   ya = sy/n;
  for (int i=0; i<n; i++){
    xi = x[i] - xa;   yi = y[i] - ya;
    zi = xi*xi + yi*yi;
    mxx += xi*xi;   myy += yi*yi;   mxy += xi*yi;
    mxz += xi*zi;   myz += yi*zi;   mzz += zi*zi;
  }
  mxx /= n;  myy /= n;  mxy /= n;  mxz /= n;  myz /= n;  mzz /= n;
  mz = mxx + myy;   cov_xy = mxx*myy - mxy*mxy;
  var_z = mzz - mz*mz;
  a3 = 4.*mz;   a2 = -3.*mz*mz - mzz;
  a1 = var_z*mz + 4.*cov_xy*mz - mxz*mxz - myz*myz;
  a0 = mxz*(mxz*myy - myz*mxy) + myz*(myz*mxx - mxz*mxy) - var_z*cov_xy;
  a22 = a2 + a2;   
  a33 = a3 + a3 + a3;
  xn=0.;yn=a0;
  for (int i=0; i<itmax; i++){
    dyn = a1 + xn*(a22 + a33*xn);
    xnnew = xn - yn/dyn;
    if ((xnnew==xn) || (!isfinite(xnnew))) break;
    ynnew = a0 + xnnew*(a1 + xnnew*(a2 + xnnew*a3));
    if (fabs(ynnew) >= fabs(yn)) break;
    xn = xnnew;   yn = ynnew;
    if(i==itmax-1) std::cout<<"Iteration exceeded itmax!" <<std::endl;
  }
  det = xn*xn - xn*mz + cov_xy;
  xc = (mxz*(myy - xn) - myz*mxy)/det/2.;
  yc = (myz*(mxx - xn) - mxz*mxy)/det/2.;
  double x0 = xc + xa;   
  double y0 = yc + ya;
  double r = sqrt(xc*xc + yc*yc + mz);

  double p    = 0.3 * (r / 1000.) * By;
  double sin0  = x0/r;
  double cos0  = -(y0-y[0])/r;
  if((cos0*x[1]+sin0*(y[1]-y[0]))<0){
    sin0 = -sin0;
    cos0 = -cos0;
  }
  double py = p * the;
  init_mom.SetXYZ(p*cos0, py, p*sin0);
  return true;
}

//bool E16ANA_TrackCandidate::CalcRoughMomentumV3() {
//}

void E16ANA_TrackCandidate::AddTrackHit(E16ANA_MultiTrack* single_track) {
  for (auto& fit_result : fit_results) {
    fit_result.set_flag = 0;
  }
//  if (!CalcRoughMomentum()) {
  if (!CalcRoughMomentumV2()) {
    std::cerr << "Cannot calculate rough momentum" << std::endl;
  }
  int tid = 0; // only 1 track is fitted by the fitter
  single_track->Clear();
//  single_track->SetInitialVertex(init_pos, kInitPosError);
  single_track->SetInitialVertex(TVector3(0., 0., init_pos.Z()), kInitPosError);
  single_track->SetInitialMomentum(tid, init_mom);
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
  for (int l = E16ANA_TrackConstant::kHBD; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l) {
    fit_results[l].Clear();
  }
  if (chisq >= 1.0e10) {
    return;
  }
  int tid = 0;
  TVector3 lpos(0., 0., 0.);
  TVector3 lsigma(0., 0., 0.);
  auto module_id = cluster_pairs[E16ANA_TrackConstant::kNumTrackingLayers - 1].ModuleID();
  int lid = 0; // only 1 layer in 1 RK
  int hid = 0; // oonly 1 hit in 1 RK
  std::vector<int> mids;
  std::vector<TVector3> lposs;
  std::vector<TVector3> lmoms;
  for (int l = E16ANA_TrackConstant::kHBD; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l) {
    auto& result = fit_results[l];
    result.Clear();
    int nstps;
//    double r;
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
      fitter->RungeKuttaTracking(tid, init_pos_fit, init_mom_fit, charge);
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
      auto nstps_tmp = fitter->GetTrackSteps(tid).size();
      if (result.set_flag == 0) {
        if (l == E16ANA_TrackConstant::kHBD) {
          result.Set(l, mid, lpos, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
        } else {
          auto lpos_lgvd = geometry->LGVD(mid2013)->GetLPos(gpos);
          result.Set(l, mid, lpos_lgvd, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
        }
        nstps = nstps_tmp;
//        r = gpos.Mag();
      } else if (nstps_tmp < nstps) {
//      } else if (gpos.Mag() < r) {
        if (l == E16ANA_TrackConstant::kHBD) {
          result.Set(l, mid, lpos, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
        } else {
          auto lpos_lgvd = geometry->LGVD(mid2013)->GetLPos(gpos);
          result.Set(l, mid, lpos_lgvd, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
        }
        nstps = nstps_tmp;
//        r = gpos.Mag();
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
  init_pos_fit = fitter->GetFitVertex();
  init_mom_fit = fitter->GetFitMomentum(tid);
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
  fitter->SetRungeKuttaStepSize(kTrackingStepSize);
  fitter->SetMaxSteps(kTrackingMaxSteps);
  chisq = fitter->Fit(vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag, kMinuitStrategy, kMinuitMaxFunctionCalls);
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

bool E16ANA_TrackCandidates::IsCurveCorrelation(double tgt_z, const std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers>& pos_set) {
  double coef1_0 = pos_set[1].X() / (pos_set[1].Z() - tgt_z);
  double coef0_0 = -1. * coef1_0 * tgt_z;
  double dist0   = fabs(coef1_0 * pos_set[0].Z() + coef0_0 + -1. * pos_set[0].X()) / sqrt(coef1_0 * coef1_0 + 1.);
  double coef1_1 = (pos_set[3].X() - pos_set[1].X()) / (pos_set[3].Z() - pos_set[1].Z());
  double coef0_1 = pos_set[1].X() -1. * coef1_1 * pos_set[1].Z();
  double dist1   = fabs(coef1_1 * pos_set[2].Z() -1. * pos_set[2].X() + coef0_1) / sqrt(coef1_1 * coef1_1 + 1.);
  if (dist1 > (15. / 4.) * dist0 + 10. ||
      dist1 < (8. / 6.) * (dist0 - 4.)) {
    return false;
  }
  return true;
}

void E16ANA_TrackCandidates::CalcLotatedPos(std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers>& pos, double tgt_z, double rot_cos, double rot_sin, std::array<TVector3, kNumTrackingLayersWTarget>* lotated_pos) {
  (*lotated_pos)[0] = {0., 0., 0.};
  (*lotated_pos)[1] = Lotate(rot_cos, rot_sin, tgt_z, pos[0]);
  (*lotated_pos)[2] = Lotate(rot_cos, rot_sin, tgt_z, pos[1]);
  (*lotated_pos)[3] = Lotate(rot_cos, rot_sin, tgt_z, pos[2]);
  (*lotated_pos)[4] = Lotate(rot_cos, rot_sin, tgt_z, pos[3]);
}

void E16ANA_TrackCandidates::CalcInverseMatrix(const std::array<double, kNumTrackingLayersWTarget>& zz, std::array<std::array<double, kNumRoughFitDegree[0]>, kNumRoughFitDegree[0]>* line) {
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

void E16ANA_TrackCandidates::CalcQuadCurve(const std::array<TVector3, kNumTrackingLayersWTarget>& lotated_pos,
                   std::array<double, kNumTrackingLayersWTarget>* zz,
                   std::array<double, kNumRoughFitDegree[0]>* zx,
                   std::array<double, kNumRoughFitDegree[0]>* coef) {
  zz->fill(0.);
  zx->fill(0.);
  for (int i = 0; i < kNumTrackingLayersWTarget; ++i) {
    AddMatrixElement(kXWeight[i], lotated_pos[i], zz, zx);
  }
  std::array<std::array<double, kNumRoughFitDegree[0]>, kNumRoughFitDegree[0]> line;
  CalcInverseMatrix(*zz, &line);
//  std::array<double, kNumTrackingLayersWTarget> fit_z_diff;
  CalcCoefficients(*zx, line, coef);
  return;
}

bool E16ANA_TrackCandidates::IsXTrackCandidate(OneAxisClusterSet* cluster_set) {
  auto& pos_set = cluster_set->global_poss;
  auto& tgt_z = E16ANA_TrackConstant::kTargetZ[cluster_set->target_id];
  
  if (!IsCurveCorrelation(tgt_z, pos_set)) {
    return false;
  }
  
  std::array<TVector3, kNumTrackingLayersWTarget> lotated_pos;
//  auto rot_phi = std::atan2(pos_set[E16ANA_TrackConstant::kGTR300].X(), pos_set[E16ANA_TrackConstant::kGTR300].Z() - tgt_z);
  auto rot_phi = std::atan2(pos_set[E16ANA_TrackConstant::kSSD].X(), pos_set[E16ANA_TrackConstant::kSSD].Z() - tgt_z); // ozawa v8
  auto rot_cos = std::cos(rot_phi);
  auto rot_sin = std::sin(rot_phi);
  CalcLotatedPos(pos_set, tgt_z, rot_cos, rot_sin, &lotated_pos);

  std::array<double, kNumTrackingLayersWTarget> zz;
  std::array<double, kNumRoughFitDegree[0]> zx;
  std::array<double, kNumRoughFitDegree[0]> coef;
  CalcQuadCurve(lotated_pos, &zz, &zx, &coef);
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
    x0 = rot_sin * z0_cand + rot_cos * grad * z0_cand;
  }
  tgt_x_cand = x0;

//  CalcChiSquare();
  double chi2_cand = 0.;
  for (int i = 0; i < kNumTrackingLayersWTarget; ++i) {
    double fit_posx = coef[2] * lotated_pos[i].Z() * lotated_pos[i].Z() + coef[1] * lotated_pos[i].Z() + coef[0];
    chi2_cand += kXWeight[i] * (fit_posx - lotated_pos[i].X()) * (fit_posx - lotated_pos[i].X());
  }

  if (chi2_cand < kRoughFitChiSquareThreshold[0] && fabs(coef[0]) < kRoughXFitCoefficientThreshold[0] && fabs(coef[2]) < kRoughXFitCoefficientThreshold[2]) {
    cluster_set->xy = tgt_x_cand;
    cluster_set->chi_square = chi2_cand;
    for (int i = 0; i < kNumRoughFitDegree[0]; ++i) {
      cluster_set->coefs[i] = coef[i];
    }
    return true;
  }
  return false;
}

bool E16ANA_TrackCandidates::IsYTrackCandidate(OneAxisClusterSet* cluster_set) {
  auto& pos_set = cluster_set->global_poss;
  std::array<double, kNumGTRLayers> gtr_y({pos_set[1].Y(), pos_set[2].Y(), pos_set[3].Y()});
  std::array<double, kNumGTRLayers> gtr_r({sqrt(pos_set[1].X() * pos_set[1].X() + pos_set[1].Z() * pos_set[1].Z()),
                                           sqrt(pos_set[2].X() * pos_set[2].X() + pos_set[2].Z() * pos_set[2].Z()),
                                           sqrt(pos_set[3].X() * pos_set[3].X() + pos_set[3].Z() * pos_set[3].Z())});
  if (fabs(kGTRSizeCoef[0] * gtr_y[0] - kGTRSizeCoef[1] * gtr_y[1]) > kGTRYDiffThreshold ||
      fabs(kGTRSizeCoef[0] * gtr_y[0] - kGTRSizeCoef[2] * gtr_y[2]) > kGTRYDiffThreshold ||
      fabs(kGTRSizeCoef[1] * gtr_y[1] - kGTRSizeCoef[2] * gtr_y[2]) > kGTRYDiffThreshold) {
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
  std::array<double, kNumRoughFitDegree[1]> coef({(r2 * y  - r * ry) / (c * r2 - r * r),
                                                  (c  * ry - r * y)  / (c * r2 - r * r)});
  double chi2_cand = 0.;
  std::array<double, kNumGTRLayers> fit_y;
  for (int i = 0; i < kNumGTRLayers; ++i) {
    fit_y[i] = coef[0] + coef[1] * gtr_r[i];
    chi2_cand += kYWeight[i] * (fit_y[i] - gtr_y[i]) * (fit_y[i] - gtr_y[i]);
  }
  if (chi2_cand < kRoughFitChiSquareThreshold[1] && fabs(coef[0]) < kRoughYFitCoefficientThreshold[0]) {
    cluster_set->xy = coef[0];
    cluster_set->chi_square = chi2_cand;
    for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
      cluster_set->coefs[i] = coef[i];
    }
    return true;
  }
  return false;
}

void E16ANA_TrackCandidates::SearchTrackCandidates() {
  track_candidates.clear();
  track_candidates.reserve(kNumReserveTracks[2]); // tmp
  auto& ssd = record->SSD();
  auto& gtr = record->GTR();
E16INFO("number of SSD clusters: %d", ssd.NumClusters());
E16INFO("number of GTR clusters: %d", gtr.NumClusters());
  std::array<std::vector<OneAxisClusterSet>, 2> cluster_sets;
  cluster_sets[0].reserve(kNumReserveTracks[0]);
  cluster_sets[1].reserve(kNumReserveTracks[1]);
  auto cluster_set = new OneAxisClusterSet();

  for (const auto& ssd_module_id : E16ANA_TrackConstant::kModuleIDs) {
    if (ssd_module_id == 105) {
      continue;
    }
    auto is_l = IsLModule(ssd_module_id);
    auto& ssd_cluster_ptrs = ssd.ClusterPtrs(ssd_module_id, 0, 0);
    for (const auto& gtr100_module_id : E16ANA_TrackConstant::kModuleIDs) {
//      if (abs(gtr100_module_id - ssd_module_id) > 1) {
      if (is_l != IsLModule(gtr100_module_id)) {
        continue;
      }
      auto& gtr100x_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsX);
      for (const auto& gtr200_module_id : E16ANA_TrackConstant::kModuleIDs) {
//        if (abs(gtr200_module_id - ssd_module_id) > 1) {
        if (is_l != IsLModule(gtr200_module_id)) {
          continue;
        }
        auto& gtr200x_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsX);
        for (const auto& gtr300_module_id : E16ANA_TrackConstant::kModuleIDs) {
//          if (abs(gtr300_module_id - ssd_module_id) > 1) {
          if (is_l != IsLModule(gtr300_module_id)) {
            continue;
          }
          auto& gtr300x_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsX);
          for (const auto& ssd_cluster : ssd_cluster_ptrs) {
            cluster_set->ssd_cluster = ssd_cluster;
            cluster_set->global_poss[E16ANA_TrackConstant::kSSD] = ssd_cluster->GlobalPos(*geometry);
            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
              if (gtr100x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR100 - 1]) {
                continue;
              }
              if (gtr100x_cluster->NumHits() < kMinHitsInXCluster) {
                continue;
              }
              cluster_set->gtr_clusters[0] = gtr100x_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100x_cluster->GlobalPos(*geometry);
              for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
                if (gtr200x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR200 - 1]) {
                  continue;
                }
                if (gtr200x_cluster->NumHits() < kMinHitsInXCluster) {
                  continue;
                }
                cluster_set->gtr_clusters[1] = gtr200x_cluster;
                cluster_set->global_poss[E16ANA_TrackConstant::kGTR200] = gtr200x_cluster->GlobalPos(*geometry);
                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
                  if (gtr300x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR300 - 1]) {
                    continue;
                  }
                  if (gtr300x_cluster->NumHits() < kMinHitsInXCluster) {
                    continue;
                  }
                  cluster_set->gtr_clusters[2] = gtr300x_cluster;
                  cluster_set->global_poss[E16ANA_TrackConstant::kGTR300] = gtr300x_cluster->GlobalPos(*geometry);
//                  bool is_cand = false;
                  for (int tgt_index = 0; tgt_index < 3; ++tgt_index) {
                    cluster_set->target_id= tgt_index;
                    if (IsXTrackCandidate(cluster_set)) {
//                      is_cand = true;
//                      break;
                      cluster_sets[0].emplace_back(*cluster_set);
                    }
                  }
//                  if (is_cand) {
//                    cluster_sets[0].emplace_back(*cluster_set);
//                  }
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
    auto is_l = IsLModule(gtr300_module_id);
    auto& gtr300y_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsY);
    for (const auto& gtr200_module_id : E16ANA_TrackConstant::kModuleIDs) {
//      if (abs(gtr200_module_id - gtr300_module_id) > 1) {
      if (is_l != IsLModule(gtr200_module_id)) {
        continue;
      }
      auto& gtr200y_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsY);
      for (const auto& gtr100_module_id : E16ANA_TrackConstant::kModuleIDs) {
//        if (abs(gtr100_module_id - gtr300_module_id) > 1) {
        if (is_l != IsLModule(gtr100_module_id)) {
          continue;
        }
        auto& gtr100y_cluster_ptrs  = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsY);
        auto& gtr100yb_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsYb);
        for (const auto& gtr300y_cluster : gtr300y_cluster_ptrs) {
          if (gtr300y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
            continue;
          }
          cluster_set->gtr_clusters[2] = gtr300y_cluster;
          cluster_set->global_poss[E16ANA_TrackConstant::kGTR300] = gtr300y_cluster->GlobalPos(*geometry);
          for (const auto& gtr200y_cluster : gtr200y_cluster_ptrs) {
            if (gtr200y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
              continue;
            }
            cluster_set->gtr_clusters[1] = gtr200y_cluster;
            cluster_set->global_poss[E16ANA_TrackConstant::kGTR200] = gtr200y_cluster->GlobalPos(*geometry);
            for (const auto& gtr100y_cluster : gtr100y_cluster_ptrs) {
              if (gtr100y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
                continue;
              }
              cluster_set->gtr_clusters[0] = gtr100y_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100y_cluster->GlobalPos(*geometry);
              if (IsYTrackCandidate(cluster_set)) {
                cluster_sets[1].emplace_back(*cluster_set);
              }
            }
            for (const auto& gtr100yb_cluster : gtr100yb_cluster_ptrs) {
              if (gtr100yb_cluster->PeakSum() < kGTRPeakSumThresholdY) {
                continue;
              }
              cluster_set->gtr_clusters[0] = gtr100yb_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100yb_cluster->GlobalPos(*geometry);
              if (IsYTrackCandidate(cluster_set)) {
                cluster_sets[1].emplace_back(*cluster_set);
              }
            }
          }
        }
      }
    }
  }
  delete cluster_set;
  n_x_cands = cluster_sets[0].size();
  n_y_cands = cluster_sets[1].size();
E16INFO("number of x candidates: %d", n_x_cands);
E16INFO("number of y candidates: %d", n_y_cands);
  
  for (const auto& x_cand : cluster_sets[0]) {
    auto& ssdx = *x_cand.ssd_cluster;
    auto& gtrx = x_cand.gtr_clusters;
    std::array<int, kNumGTRLayers> x_module_ids = {gtrx[0]->ModuleId(), gtrx[1]->ModuleId(), gtrx[2]->ModuleId()};
    std::array<float, kNumGTRLayers> x_timings = {gtrx[0]->Timing(), gtrx[1]->Timing(), gtrx[2]->Timing()};
    std::array<float, kNumGTRLayers> x_peak_sums = {gtrx[0]->PeakSum(), gtrx[1]->PeakSum(), gtrx[2]->PeakSum()};
    for (const auto& y_cand : cluster_sets[1]) {
      auto& gtry = y_cand.gtr_clusters;
//      IsSameModules();
      bool is_same_module = true;
      if ((gtry[0]->IsY() && gtrx[0]->LocalPos().X() <= 0) || (gtry[0]->IsYb() && gtrx[0]->LocalPos().X() >= 0)) {
        continue;
      }
      for (int i = 0; i < kNumGTRLayers; ++i) {
//        if (x_module_ids[i] != gtry[i]->ModuleId() || fabs(x_timings[i] - gtry[i]->Timing()) > kGTRTimeDiffThreshold[i]) {
        if (x_module_ids[i] != gtry[i]->ModuleId() || fabs(x_timings[i] - gtry[i]->Timing()) > kGTRTimeDiffThreshold[i] || !ExistADCCorrelation(x_peak_sums[i], gtry[i]->PeakSum())) { // ozawa v8
          is_same_module = false;
          break;
        }
      }
      if (!is_same_module) {
        continue;
      }
      track_candidates.emplace_back(E16ANA_TrackCandidate(geometry, bfield_map));
      auto& tmp_cand = track_candidates.back();
      tmp_cand.SetTrackID(track_candidates.size() - 1);
      tmp_cand.SetCharge(x_cand.charge);
      tmp_cand.SetInitX(x_cand.xy);
      tmp_cand.SetInitY(y_cand.xy);
      tmp_cand.SetInitZ(x_cand.target_id);
      tmp_cand.SetDefaultSigma();
      tmp_cand.SetXChiSquare(x_cand.chi_square);
      tmp_cand.SetYChiSquare(y_cand.chi_square);
      for (int i = 0; i < kNumRoughFitDegree[0]; ++i) {
        tmp_cand.SetXCoef(i, x_cand.coefs[i]);
      }
      for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
        tmp_cand.SetYCoef(i, y_cand.coefs[i]);
      }
      auto& cluster_pairs = tmp_cand.ClusterPairs();
      cluster_pairs[0].Set(geometry, 0, ssdx.ModuleId(), x_cand.global_poss[0], &ssdx);
      for (int i = 0; i < kNumGTRLayers; ++i) {
        cluster_pairs[1 + i].Set(geometry, 1 + i, gtrx[i]->ModuleId(), x_cand.global_poss[1 + i], y_cand.global_poss[1 + i], gtrx[i], gtry[i]);
      }
    }
  }
}

void E16ANA_TrackCandidates::Fit() {
  for (auto& cand : track_candidates) {
    cand.Fit(fitter, vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag);
  }
}

void E16ANA_TrackCandidates::SearchHBDAndLGHits() {
  auto& hbd = record->HBD();
  auto& lg  = record->LG();
//  for (auto& cands : track_candidates) {
//    for (auto& cand : cands) {
  for (auto& cand : track_candidates) {
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
        }
      }
//    }
  }
  return;
}

void E16ANA_TrackCandidates::SelectTracks() {
  std::array<std::vector<E16DST_DST1Cluster*>, E16ANA_TrackConstant::kNumTrackingLayers> used_clusters;
  for (auto& clsts : used_clusters) {
    clsts.clear();
  }
  std::sort(track_candidates.begin(), track_candidates.end(), [](auto& lhs, auto& rhs) {
    return lhs.ChiSquare() < rhs.ChiSquare();
  });
  for (auto& cand : track_candidates) {
    cand.SetIsSelected(false);
    if (cand.ChiSquare() > 1.0e9) {
      break;
    }
    if (cand.MinimizeStatus() == 0) {
      continue;
    }
    if (cand.ProjectedHBDClusters().size() == 0) {
      continue;
    }
    if (cand.ProjectedLGHits().size() == 0) {
      continue;
    }
    if (is_electron_run) {
      bool has_e_hbd_cluster = false;
      bool has_e_lg_hit      = false;
      for (auto& cluster : cand.ProjectedHBDClusters()) {
        if (cluster->IsE() == 1.) {
          has_e_hbd_cluster = true;
          cand.SetHasElectronHBDCluster(true);
          break;
        }
      }
      for (auto& hit : cand.ProjectedLGHits()) {
        if (hit->FitPeak() > kLGElectronThreshold) {
          has_e_lg_hit = true;
          cand.SetHasElectronLGHit(true);
          break;
        }
      }
      if (!has_e_hbd_cluster || !has_e_lg_hit) {
        continue;
      }
    }
    bool is_large_residual = false;
    for (int i = 0; i < E16ANA_TrackConstant::kNumTargets; ++i) {
      auto& res = cand.LocalFitResult(i).residual_pos;
      if (fabs(res.X()) > kResidualThresholdX[i]) {
        is_large_residual = true;
        break;
      }
      if (i != E16DST_DST1Constant::kSSD && fabs(res.Y()) > kResidualThresholdY[i]) {
        is_large_residual = true;
        break;
      }
    }
    cand.SetIsLargeResidual(is_large_residual);
    if (is_large_residual) {
      continue;
    }
    bool is_near_target = false;
    for (auto& pos : cand.PosAtTargets()) {
      double mag2 = pos.X() * pos.X() + pos.Y() * pos.Y();
      if (mag2 < kNearTargetThreshold) {
        is_near_target = true;
        break;
      }
    }
    cand.SetIsNearTarget(is_near_target);
    if (!is_near_target) {
      continue;
    }
    bool is_used = false;
    for (int l = 0; l < E16ANA_TrackConstant::kNumTrackingLayers; ++l) {
      int n_types = 2;
      if (l == E16DST_DST1Constant::kSSD) {
        n_types = 1;
      }
      for (int type = 0; type < n_types; ++type) {
        auto cluster = cand.ClusterPair(l).Cluster(type);
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
    cand.SetIsClusterUsed(is_used);
    if (is_used) {
      continue;
    }
    cand.SetIsSelected(true);
    selected_track_candidates.emplace_back(&cand);
  }
  return;
}

void E16ANA_TrackCandidates::ProjectionTarget() {
  Hep3Vector cross_pos;
  Hep3Vector cross_mom;
  for (auto& cand : track_candidates) {
    auto& pos = cand.PosAtTargets();
    auto& mom = cand.MomAtTargets();
    if (cand.ChiSquare() > 1.0e9) {
      for (int i = 0; i < E16ANA_TrackConstant::kNumTargets; ++i) {
        pos[i] = E16DST_DST1Constant::kInvalidVector;
        mom[i] = E16DST_DST1Constant::kInvalidVector;
      }
      continue;
    }
    auto t_init_pos = cand.FitInitPos();
    auto t_init_mom = cand.FitInitMom();
    Hep3Vector init_pos(t_init_pos(0) * 0.1, t_init_pos(1) * 0.1, t_init_pos(2) * 0.1);
    Hep3Vector init_mom(t_init_mom(0),       t_init_mom(1),       t_init_mom(2));
    E16ANA_StepTrack step_track(bfield_map, init_pos, init_mom, cand.Charge(), kStepTrackStepSizeCm, kStepTrackArraySize);
    for (int i = 0; i < E16ANA_TrackConstant::kNumTargets; ++i) {
      if (step_track.CrossZconstPlane(E16ANA_TrackConstant::kTargetZ[i] * 0.1, cross_pos, cross_mom) == -1) {
        pos[i] = E16DST_DST1Constant::kInvalidVector;
        mom[i] = E16DST_DST1Constant::kInvalidVector;
      } else {
        pos[i].SetXYZ(cross_pos.x() * 10., cross_pos.y() * 10., cross_pos.z() * 10.);
        mom[i].SetXYZ(cross_mom.x(),       cross_mom.y(),       cross_mom.z());
      }
    }
  }
  return;
}

void E16ANA_TrackCandidates::ProjectionX0() {
  Hep3Vector cross_pos;
  Hep3Vector cross_mom;
  for (auto& cand : track_candidates) {
    TVector3 pos = E16DST_DST1Constant::kInvalidVector;
    TVector3 mom = E16DST_DST1Constant::kInvalidVector;
    if (cand.ChiSquare() > 1.0e9) {
      cand.SetPosAtX0(pos);
      cand.SetMomAtX0(mom);
      continue;
    }
    auto t_init_pos = cand.FitInitPos();
    auto t_init_mom = cand.FitInitMom();
    Hep3Vector init_pos(t_init_pos(0) * 0.1, t_init_pos(1) * 0.1, t_init_pos(2) * 0.1);
    Hep3Vector init_mom(t_init_mom(0),       t_init_mom(1),       t_init_mom(2));
    E16ANA_StepTrack step_track(bfield_map, init_pos, init_mom, cand.Charge(), kStepTrackStepSizeCm, kStepTrackArraySize);
    if (step_track.CrossXconstPlane(0., cross_pos, cross_mom) != -1) {
      pos.SetXYZ(cross_pos.x() * 10., cross_pos.y() * 10., cross_pos.z() * 10.);
      mom.SetXYZ(cross_mom.x(),       cross_mom.y(),       cross_mom.z());
    }
    cand.SetPosAtX0(pos);
    cand.SetMomAtX0(mom);
  }
  return;
}

double E16ANA_TrackCandidates::SearchVertex(TrackPair* track_pair) {
  auto& cand_minus = track_pair->cand_minus;
  auto& cand_plus  = track_pair->cand_plus;
  auto t_init_pos0 = cand_minus->FitInitPos();
  auto t_init_mom0 = cand_minus->FitInitMom();
  auto t_init_pos1 = cand_plus->FitInitPos();
  auto t_init_mom1 = cand_plus->FitInitMom();
  Hep3Vector init_pos0(t_init_pos0(0) * 0.1, t_init_pos0(1) * 0.1, t_init_pos0(2) * 0.1);
  Hep3Vector init_mom0(t_init_mom0(0),       t_init_mom0(1),       t_init_mom0(2));
  Hep3Vector init_pos1(t_init_pos1(0) * 0.1, t_init_pos1(1) * 0.1, t_init_pos1(2) * 0.1);
  Hep3Vector init_mom1(t_init_mom1(0),       t_init_mom1(1),       t_init_mom1(2));
  E16ANA_StepTrack step_track0(bfield_map, init_pos0, init_mom0, -1, kStepTrackStepSizeCm, kStepTrackArraySize);
  E16ANA_StepTrack step_track1(bfield_map, init_pos1, init_mom1,  1, kStepTrackStepSizeCm, kStepTrackArraySize);
  double distance;
  Hep3Vector cross_point;
  Hep3Vector mom0;
  Hep3Vector mom1;
  auto flag = step_track0.Cross(step_track1, &distance, &cross_point, &mom0, &mom1);
  track_pair->vtx = {cross_point.x() * 10., cross_point.y() * 10., cross_point.z() * 10.};
  track_pair->distance = distance * 10.;
  track_pair->mom_minus = {mom0.x(), mom0.y(), mom0.z()};
  track_pair->mom_plus  = {mom1.x(), mom1.y(), mom1.z()};
  return distance * 10.;
}

void E16ANA_TrackCandidates::SelectTrackPairs() {
  selected_track_pairs.clear();
  std::vector<E16ANA_TrackCandidate*> used_minus_cands;
  std::vector<E16ANA_TrackCandidate*> used_plus_cands;
  std::sort(track_pairs.begin(), track_pairs.end(), [](auto& lhs, auto& rhs) {
    return lhs.chi_square_refit < rhs.chi_square_refit;
  });
  for (auto& pair : track_pairs) {
    bool is_used = false;
    for (auto& used_cand : used_minus_cands) {
      if (used_cand == pair.cand_minus) {
        is_used = true;
        break;
      }
    }
    if (!is_used) {
      for (auto& used_cand : used_plus_cands) {
        if (used_cand == pair.cand_plus) {
          is_used = true;
          break;
        }
      }
    }
    if (is_used) {
      continue;
    }
    pair.is_selected = true;
    selected_track_pairs.emplace_back(&pair);
    used_minus_cands.emplace_back(pair.cand_minus);
    used_plus_cands.emplace_back(pair.cand_plus);
  }
  return;
}

void E16ANA_TrackCandidates::AddTracks(TrackPair* track_pair, double tgt_z) {
  pair_fitter->Clear();
  std::array<E16ANA_TrackCandidate*, 2> cands = {track_pair->cand_minus, track_pair->cand_plus};
//  pair_fitter->SetInitialVertex(track_pair->vtx, kVertexSigma);
  pair_fitter->SetInitialVertex(TVector3(0., 0., tgt_z), kVertexSigma);
  pair_fitter->SetInitialMomentum(0, track_pair->mom_minus);
  pair_fitter->SetCharge(0, -1.);
  pair_fitter->SetInitialMomentum(1, track_pair->mom_plus);
  pair_fitter->SetCharge(1, 1.);
  for (int track_index = 0; track_index < cands.size(); ++track_index) {
    for (int layer_index = 0; layer_index < E16ANA_TrackConstant::kNumTrackingLayers; ++layer_index) {
      auto& fit_result = cands[track_index]->LocalFitResult(layer_index);
      if (layer_index == E16ANA_TrackConstant::kSSD) {
        pair_fitter->AddHit(track_index, layer_index, geometry->SSD(E16ANA_TrackConstant::ModuleID2020To2013(fit_result.module_id)),
                            fit_result.local_pos, kSigmas[layer_index]);
      } else {
        pair_fitter->AddHit(track_index, layer_index, geometry->GTR(E16ANA_TrackConstant::ModuleID2020To2013(fit_result.module_id), layer_index - 1),
                            fit_result.local_pos, kSigmas[layer_index]);
      }
    }
  }
  return;
}

void E16ANA_TrackCandidates::UpdateFitResult(TrackPair* track_pair) {
  track_pair->vtx_refit = pair_fitter->GetFitVertex();
  track_pair->mom_minus_refit = pair_fitter->GetFitMomentum(0);
  track_pair->mom_plus_refit = pair_fitter->GetFitMomentum(1);
  for (int track_index = 0; track_index < 2; ++track_index) {
    for (int layer_index = 0; layer_index < E16ANA_TrackConstant::kNumTrackingLayers; ++layer_index) {
      std::vector<int> mid;
      std::vector<TVector3> lpos;
      std::vector<TVector3> lmom;
      std::vector<TVector3> lres;
      pair_fitter->GetFitLPos(track_index, layer_index, mid, lpos);
      pair_fitter->GetFitLMom(track_index, layer_index, mid, lmom);
      pair_fitter->GetFitResidual(track_index, layer_index, mid, lres);
      int hid = 0; // hit ID
      if (layer_index == E16ANA_TrackConstant::kSSD) {
        if (track_index == 0) {
          track_pair->track_minus_pos_refit[layer_index] = geometry->SSD(mid[hid])->GetGPos(lpos[hid]);
          track_pair->track_minus_mom_refit[layer_index] = geometry->SSD(mid[hid])->GetGMom(lmom[hid]);
          track_pair->track_minus_res_refit[layer_index] = lres[hid];
        } else {
          track_pair->track_plus_pos_refit[layer_index] = geometry->SSD(mid[hid])->GetGPos(lpos[hid]);
          track_pair->track_plus_mom_refit[layer_index] = geometry->SSD(mid[hid])->GetGMom(lmom[hid]);
          track_pair->track_plus_res_refit[layer_index] = lres[hid];
        }
      } else {
        if (track_index == 0) {
          track_pair->track_minus_pos_refit[layer_index] = geometry->GTR(mid[hid], layer_index - 1)->GetGPos(lpos[hid]);
          track_pair->track_minus_mom_refit[layer_index] = geometry->GTR(mid[hid], layer_index - 1)->GetGMom(lmom[hid]);
          track_pair->track_minus_res_refit[layer_index] = lres[hid];
        } else {
          track_pair->track_plus_pos_refit[layer_index] = geometry->GTR(mid[hid], layer_index - 1)->GetGPos(lpos[hid]);
          track_pair->track_plus_mom_refit[layer_index] = geometry->GTR(mid[hid], layer_index - 1)->GetGMom(lmom[hid]);
          track_pair->track_plus_res_refit[layer_index] = lres[hid];
        }
      }
    }
  }
  track_pair->is_refit = true;
  return;
}

void E16ANA_TrackCandidates::PairTracking(TrackPair* track_pair, double tgt_z) {
  AddTracks(track_pair, tgt_z);
  pair_fitter->SetRungeKuttaStepSize(kTrackingStepSize);
  pair_fitter->SetMaxSteps(kTrackingMaxSteps);
  track_pair->chi_square_refit = pair_fitter->Fit(vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag, kMinuitStrategy, kMinuitMaxFunctionCalls);
  UpdateFitResult(track_pair);
  return;
}

void E16ANA_TrackCandidates::AnalyzeTrackPairs() {
  track_pairs.clear();
  TrackPair track_pair;
  int n_cands = selected_track_candidates.size();
  for (int cand_index0 = 0; cand_index0 < n_cands; ++cand_index0) {
    auto cand0 = selected_track_candidates[cand_index0];
    auto charge0 = cand0->Charge();
    auto tgt_z0 = cand0->InitPos().Z();
    for (int cand_index1 = cand_index0; cand_index1 < n_cands; ++cand_index1) {
      auto cand1 = selected_track_candidates[cand_index1];
      auto charge1 = cand1->Charge();
      auto tgt_z1 = cand1->InitPos().Z();
      if (charge0 == charge1 || tgt_z0 != tgt_z1) {
        continue;
      }
      track_pair.Clear();
      if (charge0 == -1) {
        track_pair.cand_minus = cand0;
        track_pair.cand_plus  = cand1;
      } else {
        track_pair.cand_minus = cand1;
        track_pair.cand_plus  = cand0;
      }
      SearchVertex(&track_pair);
      PairTracking(&track_pair, tgt_z0);
      track_pairs.emplace_back(track_pair);
    }
  }
  SelectTrackPairs();
  return;
}

void E16ANA_TrackCandidates::AddTracksToRecord() {
  auto& tracks = record->Tracks().Tracks();
  tracks.resize(selected_track_candidates.size());
  for (int track_index = 0; track_index < selected_track_candidates.size(); ++track_index) {
    auto& cand = track_candidates[track_index];
    auto& track = tracks[track_index];
    for (int i = 0; i < E16ANA_TrackConstant::kNumTargets; ++i) {
      track.SetInitialPosAtTargetPlane(i, cand.PosAtTarget(i));
      track.SetInitialMomAtTargetPlane(i, cand.MomAtTarget(i));
    }
    for (int i = 0; i < E16ANA_TrackConstant::kNumDetectorLayers; ++i) {
      auto& lpos = cand.LocalFitResult(i).local_pos;
      auto& lmom = cand.LocalFitResult(i).local_mom;
      track.SetHitPos(i, lpos);
      track.SetHitMom(i, lmom);
    }
    for (int i = 0; i < E16ANA_TrackConstant::kNumTrackingLayers; ++i) {
      for (int j = 0; j < 2; ++j) {
        if (i == E16ANA_TrackConstant::kSSD) {
          if (j == 0) {
            track.SetOriginalClusterPtr(2 * i + j, cand.ClusterPair(i).Cluster(j));
          } else {
            continue;
          }
        }
        track.SetOriginalClusterPtr(2 * i + j - 1, cand.ClusterPair(i).Cluster(j));
      }
    }
    track.SetHBDHitPtrs(cand.ProjectedHBDHits());
    track.SetHBDClusterPtrs(cand.ProjectedHBDClusters());
    track.SetLGHitPtrs(cand.ProjectedLGHits());
    track.SetLGClusterPtrs(cand.ProjectedLGClusters());
  }
  return;
}

void E16ANA_TrackCandidates::Analyze() {
  track_candidates.clear();
  selected_track_candidates.clear();
  SearchTrackCandidates();
E16INFO("number of track candidate: %d", track_candidates.size());
  Fit();
  ProjectionTarget();
  ProjectionX0();
  SearchHBDAndLGHits();
  SelectTracks();
  AnalyzeTrackPairs();
  AddTracksToRecord();
  return;
}

void E16ANA_TrackCandidates::InputDataFromTree(TTree& tree, int entry_index) {
  tree.GetEntry(entry_index);
//  tree.SetBranchAddress();
  return;
}

void E16ANA_TrackCandidates::AnalyzeFromTree(TTree& tree, int entry_index) {
  track_candidates.clear();
  selected_track_candidates.clear();
  InputDataFromTree(tree, entry_index);
  SelectTracks();
  AnalyzeTrackPairs();
  AddTracksToRecord();
  return;
}
