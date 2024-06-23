#include "E16ANA_TrackCandidate.hh"

using namespace std;
using namespace E16DST_DST1Constant;
using namespace E16ANA_TrackConstant;
using namespace E16ANA_TrackParameter;
#ifdef TRACK_EFF_CHECK
#include "E16ANA_MakeDummyDST1Parameter.hh"
using namespace E16ANA_MakeDummyDST1Parameter;
#endif // TRACK_EFF_CHECK

void E16ANA_TrackCandidate::SetDefaultSigma() {
  for (int i = 0; i < E16ANA_TrackConstant::kNumTrackingLayers; ++i) {
    sigma[i] = kSigmas[i];
  }
}

TVector3 E16ANA_TrackCandidate::EachSigma(int n) { return kSigmas[n]; }

TVector3 E16ANA_TrackCandidate::InitPosError() { return kInitPosError; }
int E16ANA_TrackCandidate::TrackingMaxSteps() { return kTrackingMaxSteps; }
int E16ANA_TrackCandidate::ProjectionMaxSteps() { return kProjectionMaxSteps; }

#ifndef TRACK_FIND_WO_TARGET
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
#ifdef NoExist_SSD
  n = 4;
#endif
  double x[5],y[5];
  double By = 1.3; 
  x[0] = 0;
  y[0] = init_pos.Z();
//  y[0] = 0.;
  double the;
#ifndef NoExist_SSD
  for (int l = 0; l < E16ANA_TrackConstant::kNumTrackingLayers; ++l) {
    auto& c = cluster_pairs[l];
    x[l+1] = c.GlobalPos().X();
    y[l+1] = c.GlobalPos().Z();
    if(l==E16ANA_TrackConstant::kNumTrackingLayers-1){
      double fr = sqrt(x[l+1]*x[l+1]+(y[l+1]-y[0])*(y[l+1]-y[0]));
      the      = c.GlobalPos().Y()/fr;
    }
  }
#else // if no ssd
  for (int l = 1; l < E16ANA_TrackConstant::kNumTrackingLayers; ++l) {
    auto& c = cluster_pairs[l];
    x[l] = c.GlobalPos().X();
    y[l] = c.GlobalPos().Z();
    if(l==E16ANA_TrackConstant::kNumTrackingLayers-1){
      double fr = sqrt(x[l]*x[l]+(y[l]-y[0])*(y[l]-y[0]));
      the      = c.GlobalPos().Y()/fr;
    }
  }
#endif
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
    mxz += xi*zi;   myz += yi*zi;  mzz += zi*zi;
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
//  init_mom.SetXYZ(p*cos0, py, p*sin0);
  constexpr double mom_range = 3.;
  auto tmp_mom = TVector3(p * cos0, py, p * sin0);
  for (int i = 0; i < 3; ++i) {
    if (tmp_mom(i) > mom_range) {
      tmp_mom(i) = 3.;
    } else if (tmp_mom(i) < -1. * mom_range) {
      tmp_mom(i) = -3.;
    }
  }
  init_mom.SetXYZ(tmp_mom.X(), tmp_mom.Y(), tmp_mom.Z());
  init_circ.SetXYZ(x0, y0, r);
  return true;
}
#endif // TRACK_FIND_WO_TARGET

void E16ANA_TrackCandidate::AddTrackHit(E16ANA_MultiTrack* single_track) {
  for (auto& fit_result : fit_results) {
    fit_result.set_flag = 0;
  }
#ifndef TRACK_FIND_WO_TARGET
//  if (!CalcRoughMomentum()) {
  if (!CalcRoughMomentumV2()) {
    std::cerr << "Cannot calculate rough momentum" << std::endl;
  }
#endif // TRACK_FIND_WO_TARGET
  int tid = 0; // only 1 track is fitted by the fitter
  single_track->Clear();
//  single_track->SetInitialVertex(init_pos, kInitPosError);
//  single_track->SetInitialVertex(TVector3(0., 0., init_pos.Z()), kInitPosError);
//  single_track->SetInitialVertex(TVector3(0., 0., init_pos.Z()), TVector3(0., 0., 0.)); // for Ks
//  single_track->SetInitialVertex(TVector3(0., 0., 0.), kInitPosError);
  single_track->SetInitialVertex(init_pos, kInitPosError);
  single_track->SetInitialMomentum(tid, init_mom);
  single_track->SetCharge(tid, charge);
  for (int l = E16ANA_TrackConstant::kGTR100; l < E16ANA_TrackConstant::kNumTrackingLayers; ++l) {
    auto& c      = cluster_pairs[l];
#ifdef TRACK_EFF_CHECK
    auto cid = c.Cluster(0)->ClusterId();
    if (cid >= kMockClusterID) {
      cluster_pairs[l].SetT(geometry, l, c.ModuleID(), c.LocalPos());
      continue;
    }
#endif // TRACK_EFF_CHECK
#ifndef TRACK_FIND_WO_TARGET
    double phi   = atan2(c.GlobalPos().Z()-init_circ.Y(),c.GlobalPos().X()-init_circ.X());
    double x0    = init_circ.X()+init_circ.Z()*cos(phi);
    double z0    = init_circ.Y()+init_circ.Z()*sin(phi);
    double x1    = x0-sin(phi);
    double z1    = z0+cos(phi);
    TVector3 lc0 = geometry->GTR(E16ANA_TrackConstant::ModuleID2020To2013(c.ModuleID()),c.LayerOrder() - 1)->GetLPos(TVector3(x0,0,z0));
    TVector3 lc1 = geometry->GTR(E16ANA_TrackConstant::ModuleID2020To2013(c.ModuleID()),c.LayerOrder() - 1)->GetLPos(TVector3(x1,0,z1));
    double  thet = atan((lc1.X()-lc0.X())/(lc1.Z()-lc0.Z()));
    int lid      = c.LayerOrder()-1;
    double  tthe = tan(thet) - tan(kGTRDriftLorentzAngle[lid]);
    c.SetTheta(tthe);
    double sumx =0;
    int nhit = c.NumCls();
    for(int j=0;j<nhit;j++){
      double lz = c.CTiming(j)*kGTRDriftVelocity*cos(kGTRDriftLorentzAngle[lid]);//106
      sumx  += c.CPos(j)  - (tthe*lz);
    }
    double intc  = sumx/nhit;
    double ltdc2 = intc+tthe*kGTRTDCCenter[l - 1]*kGTRDriftVelocity*cos(kGTRDriftLorentzAngle[lid])+kGTRGEMLorentzLength[lid];
    TVector3 lc(ltdc2,c.LocalPos().Y(),c.LocalPos().Z());
    cluster_pairs[l].SetT(geometry,l,c.ModuleID(), lc);
#else // TRACK_FIND_WO_TARGET
    auto g_angle = atan2(c.GlobalPos().X() - circ_center.X(), c.GlobalPos().Z() - circ_center.Z());
    auto gpos0   = TVector3(circ_center.X() + sin(g_angle) * radius, 0., circ_center.Z() + cos(g_angle) * radius);
    auto gpos1   = TVector3(gpos0.X() - sin(g_angle), 0., gpos0.Z() + cos(g_angle));
    auto mid2013 = ModuleID2020To2013(c.ModuleID());
    auto lpos0   = geometry->GTR(mid2013, l - 1)->GetLPos(gpos0);
    auto lpos1   = geometry->GTR(mid2013, l - 1)->GetLPos(gpos1);
    auto l_angle = atan((lpos1.X() - lpos0.X()) / (lpos1.Z() - lpos0.Z()));
    double x_diff_order = tan(l_angle) - kGTRDriftLorentzTangent[l - 1];
    c.SetTheta(x_diff_order);
    double sumx = 0.;
    auto n_hits = c.NumCls();
    for (int i = 0; i < n_hits; ++i) {
      double local_z = c.CTiming(i) * kGTRDriftVelocity * kGTRDriftLorentzCosine[l - 1];
      sumx += c.CPos(i) - x_diff_order * local_z;
    }
    double xmean = sumx / n_hits;
    double newx = xmean + x_diff_order * kGTRTDCCenter[l - 1] * kGTRDriftVelocity * kGTRDriftLorentzCosine[l - 1] + kGTRGEMLorentzLength[l - 1];
    auto newlpos = TVector3(newx, c.LocalPos().Y(), c.LocalPos().Z());
    cluster_pairs[l].SetT(geometry, l, c.ModuleID(), newlpos);
#endif // TRACK_FIND_WO_TARGET
//    auto xclst = dynamic_cast<E16DST_DST1GTRCluster*>(cluster_pairs[l].Cluster(0));
//    printf("l:%d,  nhit:%d,  the1:%f, the2:%f,  x1:%f,  x2:%f, time:%f  \n",l,nhit,xclst->TanTheta(),tthe,c.LocalPos().X(),ltdc2,xclst->Timing());
  }
  for (int l = 0; l < E16ANA_TrackConstant::kNumTrackingLayers; ++l) {
    auto& c = cluster_pairs[l];
    if (l == E16ANA_TrackConstant::kSSD) {
		#ifdef NoExist_SSD
   		continue;
		#endif
		#ifdef UseSTS
      single_track->AddHit(tid, c.LayerOrder(), geometry->STS(E16ANA_TrackConstant::ModuleID2020To2013(c.ModuleID())), c.LocalPos(), sigma[l]);
		#else
      single_track->AddHit(tid, c.LayerOrder(), geometry->SSD(E16ANA_TrackConstant::ModuleID2020To2013(c.ModuleID())), c.LocalPos(), sigma[l]);
		#endif
		
//cout << l << " " << c.LocalPos().X() << " " << c.LocalPos().Y() << " " << c.LocalPos().Z() << endl;
//auto gpos = c.GlobalPos();
//cout << l << " " << gpos.X() << " " << gpos.Y() << " " << gpos.Z() << endl;
    } else {
      single_track->AddHit(tid, c.LayerOrder(), geometry->GTR(E16ANA_TrackConstant::ModuleID2020To2013(c.ModuleID()), c.LayerOrder() - 1), c.LocalPosT(), sigma[l]);
//cout << l << " " << c.LocalPosT().X() << " " << c.LocalPosT().Y() << " " << c.LocalPosT().Z() << endl;
//auto gpos = c.GlobalPosT();
//cout << l << " " << gpos.X() << " " << gpos.Y() << " " << gpos.Z() << endl;
    }
  }
#ifdef DEBUG_230209
if (track_id == 6) {
  for (int l = 0; l < 4; ++l) {
    auto& c = cluster_pairs[l];
    cerr << ModuleID2020To2013(c.ModuleID()) << endl;
    if (l == 0) {
      c.LocalPos().Print();
    } else {
      c.LocalPosT().Print();
    }
  }
  init_pos.Print();
  init_mom.Print();
}
#endif // DEBUG_230209
  return;
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
#ifndef TRACK_EFF_CHECK
      } else {
        auto tmp_geom = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG]);
        fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
      }
#else
      } else if (l < kLGVD) {
        auto tmp_geom = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG]);
        fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
      } else {
        auto tmp_geom = geometry->LGVD(mid2013);
        fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
      }
#endif
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
#ifndef TRACK_EFF_CHECK
      } else {
        gpos = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG0])->GetGPos(lpos);
        gmom = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG0])->GetGMom(lmom);
      }
#else
      } else if (l < kLGVD) {
        gpos = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG0])->GetGPos(lpos);
        gmom = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG0])->GetGMom(lmom);
      } else {
        gpos = geometry->LGVD(mid2013)->GetGPos(lpos);
        gmom = geometry->LGVD(mid2013)->GetGMom(lmom);
      }
#endif
      auto nstps_tmp = fitter->GetTrackSteps(tid).size();
      if (result.set_flag == 0) {
        if (l == E16ANA_TrackConstant::kHBD) {
          result.Set(l, mid, lpos, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
#ifndef TRACK_EFF_CHECK
        } else {
          auto lpos_lgvd = geometry->LGVD(mid2013)->GetLPos(gpos);
          result.Set(l, mid, lpos_lgvd, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
        }
#else
        } else if (l < kLGVD) {
          auto lpos_lgvd = geometry->LGVD(mid2013)->GetLPos(gpos);
          result.Set(l, mid, lpos_lgvd, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
        } else {
          result.Set(l, mid, lpos, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
        }
#endif
        nstps = nstps_tmp;
//        r = gpos.Mag();
      } else if (nstps_tmp < nstps) {
//      } else if (gpos.Mag() < r) {
        if (l == E16ANA_TrackConstant::kHBD) {
          result.Set(l, mid, lpos, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
#ifndef TRACK_EFF_CHECK
        } else {
          auto lpos_lgvd = geometry->LGVD(mid2013)->GetLPos(gpos);
          result.Set(l, mid, lpos_lgvd, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
        }
#else
        } else if (l < kLGVD) {
          auto lpos_lgvd = geometry->LGVD(mid2013)->GetLPos(gpos);
          result.Set(l, mid, lpos_lgvd, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
        } else {
          result.Set(l, mid, lpos, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
        }
#endif
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
  //if(chisq<20) fitter->PrintHits();
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
      #ifdef UseSTS
      gpos = geometry->STS(mid[hid])->GetGPos(lpos[hid]);
      gmom = geometry->STS(mid[hid])->GetGMom(lmom[hid]);
		#else
      gpos = geometry->SSD(mid[hid])->GetGPos(lpos[hid]);
      gmom = geometry->SSD(mid[hid])->GetGMom(lmom[hid]);
		#endif
    } else {
      gpos = geometry->GTR(mid[hid], l - 1)->GetGPos(lpos[hid]);
      gmom = geometry->GTR(mid[hid], l - 1)->GetGMom(lmom[hid]);
    }
    auto rpos = cluster_pairs[l].LocalPos() - lpos[hid];
//    TVector3 rpos = 
//    if (l == 0) {
//      rpos = cluster_pairs[l].LocalPos() - lpos[hid];
//    } else {
//      rpos = cluster_pairs[l].LocalPosT() - lpos[hid];
//    }
//    std::vector<TVector3> rposs;
//    fitter->GetFitResidual(tid, l, mid, rposs);
//    auto rpos = rposs[0];
    fit_results[l].Set(l, mid2020, lpos[hid], lmom[hid], gpos, gmom, rpos);
    //if(l==0 && chisq<20){
    //printf("%f res:%f, modsize:%d lx:%f %f , z:%f \n",chisq,rpos.X(), mid.size(),cluster_pairs[l].LocalPos().X(),lpos[hid].X(),init_pos_fit.Z() );
    //}
    if(l != E16ANA_TrackConstant::kSSD) {
      auto rpost2 = cluster_pairs[l].LocalPosT() - lpos[hid];
      auto rpost  = cluster_pairs[l].LocalPos() - lpos[hid];
      fit_results[l].SetT(rpost);
      fit_results[l].SetT2(rpost2);
      auto xclst = dynamic_cast<E16DST_DST1GTRCluster*>(cluster_pairs[l].Cluster(0));
      auto yclst = dynamic_cast<E16DST_DST1GTRCluster*>(cluster_pairs[l].Cluster(1));
      TVector3 lcx(xclst->LocalX()-lpos[hid].X(),yclst->LocalX()-lpos[hid].Y(),0);
      fit_results[l].SetC(lcx);
    }
  }
#ifdef DEBUG_230209
if (track_id == 6) {
  init_pos_fit.Print();
  init_mom_fit.Print();
}
#endif // DEBUG_230209
  Projection(fitter);
  return;
}

double E16ANA_TrackCandidate::Fit(E16ANA_MultiTrack* fitter, bool vertex_xy_fix_flag, bool py_fix_flag, bool vertex_z_fix_flag) {
  fitter->Clear();
//  fitter->SetPrintLevel(kRKPrintLevel);
  this->AddTrackHit(fitter);
  fitter->SetRungeKuttaStepSize(kTrackingStepSize);
  fitter->SetMaxSteps(kTrackingMaxSteps);
//  chisq = fitter->Fit(vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag, kMinuitStrategy, kMinuitMaxFunctionCalls);
  chisq = fitter->Fit(vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag, kMinuitStrategy, kMinuitMaxFunctionCalls,
                      kInitXRange[0], kInitXRange[1], kInitYRange[0], kInitYRange[1], kInitZRange[0], kInitZRange[1]);
#ifdef DEBUG_230209
if (track_id == 6) {
  cerr << "chi: " << chisq << endl;
}
#endif // DEBUG_230209
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

void E16ANA_TrackCandidate::PrintParam() {
//  std::cout << "Sigma : ("  << kSigma(0) << ", " << kSigma(1) << ", " << kSigma(2) << ")" << std::endl;
  for (int i = 0; i < E16ANA_TrackConstant::kNumTrackingLayers; ++i) {
    std::cout << "  " << E16ANA_TrackConstant::kDetectorName[i] << " : ("  << kSigmas[i](0) << ", " << kSigmas[i](1) << ", " << kSigmas[i](2) << ")" << std::endl;
  }
  std::cout << "Initial Position Error : (" << kInitPosError(0) << ", " << kInitPosError(1) << ", " << kInitPosError(2) << ")" << std::endl;
  std::cout << "Runge Kutta Tracking Max Steps : " << kTrackingMaxSteps << std::endl;
  std::cout << "Runge Kutta Projection Max Steps : " << kProjectionMaxSteps << std::endl;
}

#ifndef TRACK_FIND_WO_TARGET
bool E16ANA_TrackCandidates::IsCurveCorrelation(double tgt_z, const std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers>& pos_set) {
#ifdef NoExist_SSD
  double coef1_0 = pos_set[2].X() / (pos_set[2].Z() - tgt_z);
  double coef0_0 = -1. * coef1_0 * tgt_z;
  double dist0   = fabs(coef1_0 * pos_set[1].Z() + coef0_0 + -1. * pos_set[1].X()) / sqrt(coef1_0 * coef1_0 + 1.);
  double coef1_1 = (pos_set[3].X() - pos_set[1].X()) / (pos_set[3].Z() - pos_set[1].Z());
  double coef0_1 = pos_set[1].X() -1. * coef1_1 * pos_set[1].Z();
  double dist1   = fabs(coef1_1 * pos_set[2].Z() -1. * pos_set[2].X() + coef0_1) / sqrt(coef1_1 * coef1_1 + 1.);
  if (dist1 > 0.45  * dist0  + 18. ||
      dist1 <  0.5  * (dist0 - 15.)) {//morino value
//cout << "curve invalid. dist1: " << dist1 << ", dist0: " << dist0 << endl;
//cout << dist1 - ((15. / 4.) * dist0 + 10.) << " must <0, " << dist1 - ((8. / 6.) * (dist0 - 4.)) << " must >0" << endl;
    return false;
  }
  return true;
}
#else // this is for all layer tracking case, wo gtr case has not been developed yet.
  double coef1_0 = pos_set[1].X() / (pos_set[1].Z() - tgt_z);
  double coef0_0 = -1. * coef1_0 * tgt_z;
  double dist0   = fabs(coef1_0 * pos_set[0].Z() + coef0_0 + -1. * pos_set[0].X()) / sqrt(coef1_0 * coef1_0 + 1.);
  double coef1_1 = (pos_set[3].X() - pos_set[1].X()) / (pos_set[3].Z() - pos_set[1].Z());
  double coef0_1 = pos_set[1].X() -1. * coef1_1 * pos_set[1].Z();
  double dist1   = fabs(coef1_1 * pos_set[2].Z() -1. * pos_set[2].X() + coef0_1) / sqrt(coef1_1 * coef1_1 + 1.);
  if (dist1 > (15. / 4.) * dist0 + 10. ||
      dist1 < (8. / 6.) * (dist0 - 4.)) {
//cout << "curve invalid. dist1: " << dist1 << ", dist0: " << dist0 << endl;
//cout << dist1 - ((15. / 4.) * dist0 + 10.) << " must <0, " << dist1 - ((8. / 6.) * (dist0 - 4.)) << " must >0" << endl;
    return false;
  }
  return true;
}
#endif//NoExist_SSD

//bool E16ANA_TrackCandidates::IsCurveCorrelation(const std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers>& pos_set) {
//  for (int i = 0; i < 2; ++i) {
//    double coef1 = (pos_set[2 + i].X() - pos_set[i].X()) / (pos_set[2 + i].Z() - pos_set[i].Z());
//    double coef0 = pos_set[i].X() - coef1 * pos_set[i].Z();
//    double dist  = fabs(coef1 * pos_set[1 + i].Z() + coef0 - pos_set[1 + i].X()) / sqrt(coef1 * coef1 + 1.);
//    if (dist1 > (15. / 4.) * dist0 + 10. ||
//        dist1 < (8. / 6.) * (dist0 - 4.)) {
////cout << "curve invalid. dist1: " << dist1 << ", dist0: " << dist0 << endl;
////cout << dist1 - ((15. / 4.) * dist0 + 10.) << " must <0, " << dist1 - ((8. / 6.) * (dist0 - 4.)) << " must >0" << endl;
//    return false;
//  }
//  return true;
//}

void E16ANA_TrackCandidates::CalcRotatedPos(std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers>& pos, double tgt_z, double rot_cos, double rot_sin, std::array<TVector3, kNumTrackingLayersWTarget>* lotated_pos) {
  (*lotated_pos)[0] = {0., 0., 0.};
  (*lotated_pos)[1] = Rotate(rot_cos, rot_sin, tgt_z, pos[0]);
  (*lotated_pos)[2] = Rotate(rot_cos, rot_sin, tgt_z, pos[1]);
  (*lotated_pos)[3] = Rotate(rot_cos, rot_sin, tgt_z, pos[2]);
  (*lotated_pos)[4] = Rotate(rot_cos, rot_sin, tgt_z, pos[3]);
}

void E16ANA_TrackCandidates::CalcInverseMatrix(const array<double, 5>& mz, array<array<double, kNumRoughFitDegree[0]>, kNumRoughFitDegree[0]>* matrix) {
  double m11 = mz[4];
  double m12 = mz[3];
  double m21 = mz[3];
  double m13 = mz[2];
  double m22 = mz[2];
  double m31 = mz[2];
  double m23 = mz[1];
  double m32 = mz[1];
  double m33 = mz[0];
  double det = m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 -
               m13 * m22 * m31 - m12 * m21 * m33 - m11 * m23 * m32;
  (*matrix)[0][0] =       (m22 * m33 - m23 * m32) / det;
  (*matrix)[0][1] = -1. * (m12 * m33 - m13 * m32) / det;
  (*matrix)[0][2] =       (m12 * m23 - m13 * m22) / det;
  (*matrix)[1][0] = -1. * (m21 * m33 - m23 * m31) / det;
  (*matrix)[1][1] =       (m11 * m33 - m13 * m31) / det;
  (*matrix)[1][2] = -1. * (m11 * m23 - m13 * m21) / det;
  (*matrix)[2][0] =       (m21 * m32 - m22 * m31) / det;
  (*matrix)[2][1] = -1. * (m11 * m32 - m12 * m31) / det;
  (*matrix)[2][2] =       (m11 * m22 - m12 * m21) / det;
  return;
}

void E16ANA_TrackCandidates::CalcQuadCurve(const std::array<TVector3, kNumTrackingLayersWTarget>& lotated_pos,
                   std::array<double, kNumTrackingLayersWTarget>* zz,
                   std::array<double, kNumRoughFitDegree[0]>* zx,
                   std::array<double, kNumRoughFitDegree[0]>* coef) {
  zz->fill(0.);
  zx->fill(0.);

	for (int i = 0; i < kNumTrackingLayersWTarget; ++i) {
#ifdef NoExist_SSD
		if(i == 1) continue;
#endif
    AddMatrixElement(kXWeight[i], lotated_pos[i], zz, zx);
  }
  std::array<std::array<double, kNumRoughFitDegree[0]>, kNumRoughFitDegree[0]> line;
  CalcInverseMatrix(*zz, &line);
//  std::array<double, kNumTrackingLayersWTarget> fit_z_diff;
  CalcCoefficients(*zx, line, coef);
  return;
}

bool E16ANA_TrackCandidates::HasXAssociatedHBD(int tgt_id, const OneAxisClusterSet& cluster_set, const array<double, kNumRoughFitDegree[0]>& coef,
                                               vector<int>* hbd_indexs, vector<int>* hbd_ids, vector<double>* hbd_ress) {
  bool has_hbd = false;
  hbd_indexs->clear();
  hbd_ids->clear();
  hbd_ress->clear();
  auto offset = kTargetZ[tgt_id];
  auto& ssd = cluster_set.global_poss[0];
  auto rot_phi = std::atan2(ssd.X(), ssd.Z() - offset);
  auto rot_cos = std::cos(rot_phi);
  auto rot_sin = std::sin(rot_phi);
  
  auto& gtr300 = cluster_set.global_poss[3];
  auto x = gtr300.X();
  auto z = gtr300.Z();
  double lotate_x = rot_cos * x - rot_sin * (z - offset);
  double lotate_z = rot_sin * x + rot_cos * (z - offset);
  array<double, 2> coefs;
  coefs[1] = 2. * coef[2] * lotate_z + coef[1];
  coefs[0] = lotate_x - coefs[1] * lotate_z;
  
  auto n_hbds = record->HBD().NumClusters();
  for (int i = 0; i < n_hbds; ++i) {
    auto& hbd = record->HBD().Cluster(i);
    if (hbd.PeakSum() < kMinHBDADCForRK) {
      continue;
    }
    auto hit_x = hbd.GlobalPos(*geometry).X();
    auto hit_z = hbd.GlobalPos(*geometry).Z();
    double lotate_hit_x = rot_cos * hit_x - rot_sin * (hit_z - offset);
    double lotate_hit_z = rot_sin * hit_x + rot_cos * (hit_z - offset);
    auto res = pow((lotate_hit_x - coefs[0] - coefs[1] * lotate_hit_z) * (lotate_hit_x - coefs[0] - coefs[1] * lotate_hit_z) / (coefs[1] * coefs[1] + 1.), 0.5);
//int cid[4] = {cluster_set.ssd_cluster->ClusterId(), cluster_set.gtr_clusters[0]->ClusterId(), cluster_set.gtr_clusters[1]->ClusterId(), cluster_set.gtr_clusters[2]->ClusterId()};
//if (cid[0] == 7 && cid[1] == 28 && cid[2] == 63 && cid[3] == 93 && hbd.ClusterId() == 19) {
//  cout << "        ID: " << cid[0] << " " << cid[1] << " " << cid[2] << " " << cid[3] << endl;
//  cout << "        rot phi: " << rot_phi << " " << rot_cos << " " << rot_sin << " " << offset << endl;
//  cout << "        gtr: " << x << " " << z << endl;
//  cout << "        lotate gtr: " << lotate_x << " " << lotate_z << endl;
////  cout << "        x coefs: " << cluster_set.coefs[2] << " " << cluster_set.coefs[1] << endl;
//  cout << "        x coefs: " << coef[2] << " " << coef[1] << endl;
//  cout << "        coef: " << coefs[0] << " " << coefs[1] << endl;
//  cout << "        HBD ID: " << hbd.ClusterId() << endl;
//  cout << "        HBD: " << hit_x << " " << hit_z << endl;
//  cout << "        lotate HBD: " << lotate_hit_x << " " << lotate_hit_z << endl;
//  cout << "        res: " << res << endl;
//}
    if (res < kMaxHBDRoughXRes) {
      has_hbd = true;
      hbd_indexs->emplace_back(i);
      hbd_ids->emplace_back(hbd.ClusterId());
      hbd_ress->emplace_back(res);
//if (hbd.ClusterId() == 18 && fabs(rot_phi + 0.464793) < 0.01 && fabs(x + 243.727) < 0.01 && fabs(coefs[0] + 100.933) < 0.01 && fabs(coefs[1] - 0.224326) < 0.01) {
//if (hbd.ClusterId() == 19 && fabs(rot_phi + 0.952164) < 0.01 && fabs(x + 635.074) < 0.01) {
    }
  }
  return has_hbd;
}

bool E16ANA_TrackCandidates::IsXTrackCandidate(int tgt_id, double prev_chi2, OneAxisClusterSet* cluster_set) {
  auto& pos_set = cluster_set->global_poss;
  auto& tgt_z = E16ANA_TrackConstant::kTargetZ[tgt_id];

  if (!IsCurveCorrelation(tgt_z, pos_set)) {
  #ifdef TRACK_EFF_CHECK
    for (int i = 0; i < 2; ++i) {
      if (is_sim_xcluster[i][0] && is_sim_xcluster[i][1] && is_sim_xcluster[i][2] && is_sim_xcluster[i][3]) {
        x_fit_reject_point[i] += Pow2(kRejTgt0Curve + tgt_id);
      }
    }
  #endif // TRACK_EFF_CHECK
    return false;
  }
  
  std::array<TVector3, kNumTrackingLayersWTarget> lotated_pos;
//  auto rot_phi = std::atan2(pos_set[E16ANA_TrackConstant::kGTR300].X(), pos_set[E16ANA_TrackConstant::kGTR300].Z() - tgt_z);

#ifdef No_ExistSSD
  auto rot_phi = std::atan2(pos_set[E16ANA_TrackConstant::kGTR100].X(), pos_set[E16ANA_TrackConstant::kGTR100].Z() - tgt_z); // ozawa v8
#else
  auto rot_phi = std::atan2(pos_set[E16ANA_TrackConstant::kSSD].X(), pos_set[E16ANA_TrackConstant::kSSD].Z() - tgt_z); // ozawa v8
#endif
  auto rot_cos = std::cos(rot_phi);
  auto rot_sin = std::sin(rot_phi);
  CalcRotatedPos(pos_set, tgt_z, rot_cos, rot_sin, &lotated_pos);

  std::array<double, 5> zz;
  std::array<double, kNumRoughFitDegree[0]> zx;
  std::array<double, kNumRoughFitDegree[0]> coef;
  CalcQuadCurve(lotated_pos, &zz, &zx, &coef);

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
#ifdef NoExist_SSD
  for (int i = 0; i < kNumTrackingLayersWTarget; ++i) {
	 if( i  == 1 ) continue;
    double fit_posx = coef[2] * lotated_pos[i].Z() * lotated_pos[i].Z() + coef[1] * lotated_pos[i].Z() + coef[0];
    chi2_cand += kXWeight[i] * (fit_posx - lotated_pos[i].X()) * (fit_posx - lotated_pos[i].X());
  }
#else // no removed layer, wo gtr case has not been developed.
  for (int i = 0; i < kNumTrackingLayersWTarget; ++i) {
    double fit_posx = coef[2] * lotated_pos[i].Z() * lotated_pos[i].Z() + coef[1] * lotated_pos[i].Z() + coef[0];
    chi2_cand += kXWeight[i] * (fit_posx - lotated_pos[i].X()) * (fit_posx - lotated_pos[i].X());
  }

#endif//NoExist_SSD

  vector<int> hbd_indexs;
  vector<int> hbd_ids;
  vector<double> hbd_ress;
  if (chi2_cand < prev_chi2 && chi2_cand < kRoughFitChiSquareThreshold[0] &&
      fabs(coef[0]) < kRoughXFitCoefficientThreshold[0] && fabs(coef[2]) < kRoughXFitCoefficientThreshold[2] &&
      (!kReqHBDAssociation || HasXAssociatedHBD(tgt_id, *cluster_set, coef, &hbd_indexs, &hbd_ids, &hbd_ress))) {
    cluster_set->charge = coef[2] > 0 ? 1 : -1;
    cluster_set->target_id = tgt_id;
    cluster_set->xy = tgt_x_cand;
    cluster_set->chi_square = chi2_cand;
    cluster_set->hbd_indexs.clear();
    cluster_set->hbd_ids.clear();
    cluster_set->hbd_ress.clear();
    for (int i = 0; i < kNumRoughFitDegree[0]; ++i) {
      cluster_set->coefs[i] = coef[i];
    }
    copy(hbd_indexs.begin(),  hbd_indexs.end(),  back_inserter(cluster_set->hbd_indexs));
    copy(hbd_ids.begin(),     hbd_ids.end(),     back_inserter(cluster_set->hbd_ids));
    copy(hbd_ress.begin(),    hbd_ress.end(),    back_inserter(cluster_set->hbd_ress));
    return true;
  }
#ifdef TRACK_EFF_CHECK
  for (int i = 0; i < 2; ++i) {
    if (is_sim_xcluster[i][0] && is_sim_xcluster[i][1] && is_sim_xcluster[i][2] && is_sim_xcluster[i][3]) {
      if (chi2_cand >= kRoughFitChiSquareThreshold[0]) {
        x_fit_reject_point[i] += Pow2(kRejTgt0XChi2 + tgt_id);
      }
      if (fabs(coef[0]) >= kRoughXFitCoefficientThreshold[0]) {
        x_fit_reject_point[i] += Pow2(kRejTgt0XCoef0 + tgt_id);
      }
      if (fabs(coef[2]) >= kRoughXFitCoefficientThreshold[2]) {
        x_fit_reject_point[i] += Pow2(kRejTgt0XCoef2 + tgt_id);
      }
    }
  }
#endif // TRACK_EFF_CHECK
//cout << "x fit bad. chi2: " << chi2_cand << ", coef0: " << coef[0] << ", coef2: " << coef[2] << endl;
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
//cout << "y subtract bad" << endl;
#ifdef TRACK_EFF_CHECK
    for (int i = 0; i < 2; ++i) {
      if (is_sim_ycluster[i][0] && is_sim_ycluster[i][1] && is_sim_ycluster[i][2]) {
        y_reject_point[i] += Pow2(kRejYSubtract);
      }
    }
#endif
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
#ifdef TRACK_EFF_CHECK
  for (int i = 0; i < 2; ++i) {
    if (is_sim_ycluster[i][0] && is_sim_ycluster[i][1] && is_sim_ycluster[i][2]) {
      if (chi2_cand < kRoughFitChiSquareThreshold[1]) {
        y_reject_point[i] += Pow2(kRejYChi2);
      }
      if (fabs(coef[0]) < kRoughYFitCoefficientThreshold[0]) {
        y_reject_point[i] += Pow2(kRejYCoef0);
      }
    }
  }
#endif
//cout << "y chi2 bad" << endl;
  return false;
}

#else // TRACK_FIND_WO_TARGET

int E16ANA_TrackCandidates::ModuleSetType(const OneAxisClusterSet& cluster_set) {
  int t = 0;
#ifndef NoExist_SSD
  if (cluster_set.ssd_cluster->ModuleId() % 2 == 1) {
    t += 1;
  }
#endif
  if (cluster_set.gtr_clusters[0]->ModuleId() % 2 == 0) {
    t += 2;
  }
  if (cluster_set.gtr_clusters[1]->ModuleId() % 2 == 0) {
    t += 1;
  }
  if (cluster_set.gtr_clusters[2]->ModuleId() % 2 == 1) {
    t += 1;
  }
  return t;
}

bool E16ANA_TrackCandidates::IsCurveCorrelation(int module_set_type, const array<TVector3, kNumTrackingLayers>& pos_set, array<double, 2>* dists) {
  for (int i = 0; i < 2; ++i) {
    double coef1 = (pos_set[2 + i].X() - pos_set[i].X()) / (pos_set[2 + i].Z() - pos_set[i].Z());
    double coef0 = pos_set[i].X() - coef1 * pos_set[i].Z();
    (*dists)[i]  = fabs(coef1 * pos_set[1 + i].Z() + coef0 - pos_set[1 + i].X()) / sqrt(coef1 * coef1 + 1.);
  }
  double dist_ratio = (*dists)[0] / (*dists)[1];
  if (dist_ratio < kXCurveCorrWindow[module_set_type][0] || dist_ratio > kXCurveCorrWindow[module_set_type][1]) {
    return false;
  }
  return true;
}

void E16ANA_TrackCandidates::CalcRotatedPos(const array<TVector3, kNumTrackingLayers>& pos, double rot_cos, double rot_sin,
                                            array<TVector3, kNumTrackingLayers>* lotated_pos) {
  (*lotated_pos)[0] = TVector3(0., 0., 0.);
  for (int i = 1; i < 4; ++i) {
    (*lotated_pos)[i] = Rotate(rot_cos, rot_sin, pos[0], pos[i]);
  }
  return;
}

void E16ANA_TrackCandidates::CalcInverseMatrix(const array<double, 5>& mz, array<array<double, kNumRoughFitDegree[0]>, kNumRoughFitDegree[0]>* matrix) { // same
  double m11 = mz[4];
  double m12 = mz[3];
  double m13 = mz[2];
  double m21 = mz[3];
  double m22 = mz[2];
  double m23 = mz[1];
  double m31 = mz[2];
  double m32 = mz[1];
  double m33 = mz[0];
  double det = m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 -
               m13 * m22 * m31 - m12 * m21 * m33 - m11 * m23 * m32;
  (*matrix)[0][0] =       (m22 * m33 - m23 * m32) / det;
  (*matrix)[0][1] = -1. * (m12 * m33 - m13 * m32) / det;
  (*matrix)[0][2] =       (m12 * m23 - m13 * m22) / det;
  (*matrix)[1][0] = -1. * (m21 * m33 - m23 * m31) / det;
  (*matrix)[1][1] =       (m11 * m33 - m13 * m31) / det;
  (*matrix)[1][2] = -1. * (m11 * m23 - m13 * m21) / det;
  (*matrix)[2][0] =       (m21 * m32 - m22 * m31) / det;
  (*matrix)[2][1] = -1. * (m11 * m32 - m12 * m31) / det;
  (*matrix)[2][2] =       (m11 * m22 - m12 * m21) / det;
  return;
}

void E16ANA_TrackCandidates::CalcQuadCurve(const array<TVector3, kNumTrackingLayers>& lotated_pos,
                                           array<double, 5>* mz, array<double, kNumRoughFitDegree[0]>* mzx, array<double, kNumRoughFitDegree[0]>* coefs) {
  mz->fill(0.);
  mzx->fill(0.);
  for (int i = 0; i < kNumTrackingLayers; ++i) {
    AddMatrixElement(kXWeight[i], lotated_pos[i], mz, mzx);
  }
  array<array<double, kNumRoughFitDegree[0]>, kNumRoughFitDegree[0]> matrix;
  CalcInverseMatrix(*mz, &matrix);
  CalcCoefficients(*mzx, matrix, coefs);
  return;
}

bool E16ANA_TrackCandidates::HasXAssociatedHBD(double rot_cos, double rot_sin,
                                               const OneAxisClusterSet& cluster_set, const array<double, kNumRoughFitDegree[0]>& coefs,
                                               vector<int>* hbd_indexs, vector<int>* hbd_ids, vector<double>* hbd_ress) {
  bool has_hbd = false;
  hbd_indexs->clear();
  hbd_ids->clear();
  hbd_ress->clear();
  auto lotate_gtr300 = Rotate(rot_cos, rot_sin, cluster_set.global_poss[E16ANA_TrackConstant::kSSD], cluster_set.global_poss[E16ANA_TrackConstant::kGTR300]);
  auto n_hbds = record->HBD().NumClusters();
  for (int i = 0; i < n_hbds; ++i) {
    auto& hbd = record->HBD().Cluster(i);
    if (hbd.PeakSum() < kMinHBDADCForRK) {
      continue;
    }
    auto lotate_hbd = Rotate(rot_cos, rot_sin, cluster_set.global_poss[E16ANA_TrackConstant::kSSD], hbd.GlobalPos(*geometry));
    double z = lotate_hbd.Z();
    double x = coefs[2] * z * z + coefs[1] * z + coefs[0];
    array<double, 2> tan_coefs;
    tan_coefs[1] = 2. * coefs[2] * z + coefs[1];
    tan_coefs[0] = x - tan_coefs[1] * z;
    auto res = fabs(tan_coefs[1] * lotate_hbd.Z() + tan_coefs[0] - lotate_hbd.X()) / sqrt(tan_coefs[1] * tan_coefs[1] + 1.);
    if (res < kMaxHBDRoughXRes) {
      has_hbd = true;
      hbd_indexs->emplace_back(i);
      hbd_ids->emplace_back(hbd.ClusterId());
      hbd_ress->emplace_back(res);
    }
  }
  return has_hbd;
}

void E16ANA_TrackCandidates::CalcRoughZXMomentum(double xcoef2, const array<TVector3, 4>& pos_set,
                                                 double* radius, TVector3* circ_center, double* mom, TVector3* mom_zx) {
//  constexpr double kBy = 1.3; 
  constexpr double kBy = 1.13; 
  constexpr double kXMomOffset = 0.015;
  double cogz = 0.;
  double cogx = 0.;
  for (int i = 0; i < 4; ++i) {
    cogz += pos_set[i].Z();
    cogx += pos_set[i].X();
  }
  cogz /= 4;
  cogx /= 4;
  double t30 = 0.;
  double t20 = 0.;
  double t12 = 0.;
  double t11 = 0.;
  double t03 = 0.;
  double t02 = 0.;
  double t21 = 0.;
  for (int i = 0; i < 4; ++i) {
    double z = pos_set[i].Z() - cogz;
    double x = pos_set[i].X() - cogx;
    double zz = z * z;
    double xx = x * x;
    t30 += zz * z;
    t20 += zz;
    t12 += z * xx;
    t11 += z * x;
    t03 += xx * x;
    t02 += xx;
    t21 += zz * x;
  }
  double c = 0.5 / (t20 * t02 - t11 * t11);
  double cz = c * (t02 * (t30 + t12) - t11 * (t03 + t21));
  double cx = c * (t20 * (t03 + t21) - t11 * (t30 + t12));
  double r = sqrt(cz * cz + cx * cx + 0.25 * (t20 + t02));
  *mom = 0.3 * (r  * 0.001) * kBy;
  double sin = (pos_set[0].X() - (cx + cogx)) / r;
  double cos = (pos_set[0].Z() - (cz + cogz)) / r;
  *radius = r;
  circ_center->SetXYZ(cx + cogx, 0., cz + cogz);
//  if (xcoef2 > 0.) {
//    mom_zx->SetXYZ(cos * (*mom), 0., -1. * sin * (*mom));
//  } else {
//    mom_zx->SetXYZ(-1. * cos * (*mom), 0., sin * (*mom));
//  }
  if (xcoef2 > 0.) {
    if (cos > 0.) {
      mom_zx->SetXYZ(cos * (*mom) - kXMomOffset, 0., -1. * sin * (*mom));
    } else {
      mom_zx->SetXYZ(cos * (*mom) + kXMomOffset, 0., -1. * sin * (*mom));
    }
  } else {
    if (cos < 0.) {
      mom_zx->SetXYZ(-1. * cos * (*mom) - kXMomOffset, 0., sin * (*mom));
    } else {
      mom_zx->SetXYZ(-1. * cos * (*mom) + kXMomOffset, 0., sin * (*mom));
    }
  }
  return;
}

bool E16ANA_TrackCandidates::IsXTrackCandidate(OneAxisClusterSet* cluster_set) {
  auto& pos_set = cluster_set->global_poss;
  if (!IsCurveCorrelation(ModuleSetType(*cluster_set), pos_set, &(cluster_set->dists))) {
  #ifdef TRACK_EFF_CHECK
    for (int i = 0; i < 2; ++i) {
      if (is_sim_xcluster[i][0] && is_sim_xcluster[i][1] && is_sim_xcluster[i][2] && is_sim_xcluster[i][3]) {
        x_fit_reject_point[i] += Pow2(kRejTgt0Curve);
      }
    }
  #endif // TRACK_EFF_CHECK
    return false;
  }
  std::array<TVector3, kNumTrackingLayers> lotated_pos;
  auto rot_phi = std::atan2(pos_set[E16ANA_TrackConstant::kGTR100].X() - pos_set[E16ANA_TrackConstant::kSSD].X(),
                            pos_set[E16ANA_TrackConstant::kGTR100].Z() - pos_set[E16ANA_TrackConstant::kSSD].Z());
  auto rot_cos = std::cos(rot_phi);
  auto rot_sin = std::sin(rot_phi);
  CalcRotatedPos(pos_set, rot_cos, rot_sin, &lotated_pos);

  std::array<double, 5> mz;
  std::array<double, kNumRoughFitDegree[0]> mzx;
  std::array<double, kNumRoughFitDegree[0]> coefs;
  CalcQuadCurve(lotated_pos, &mz, &mzx, &coefs);

// CalcChiSquare();
  double chi2_cand = 0.;
  for (int i = 0; i < kNumTrackingLayers; ++i) {
    double fit_posx = coefs[2] * lotated_pos[i].Z() * lotated_pos[i].Z() + coefs[1] * lotated_pos[i].Z() + coefs[0];
    chi2_cand += kXWeight[i] * (fit_posx - lotated_pos[i].X()) * (fit_posx - lotated_pos[i].X());
  }

// HBD check
  if (chi2_cand < kRoughFitChiSquareThreshold[0] &&
      fabs(coefs[0]) < kRoughXFitCoefficientThreshold[0] &&
      fabs(coefs[1]) < kRoughXFitCoefficientThreshold[1] &&
      fabs(coefs[2]) < kRoughXFitCoefficientThreshold[2]) {
    if (!kReqHBDAssociation || HasXAssociatedHBD(rot_cos, rot_sin, *cluster_set, coefs,
                                                 &(cluster_set->hbd_indexs), &(cluster_set->hbd_ids), &(cluster_set->hbd_ress))) {
      cluster_set->charge     = coefs[2] > 0 ? 1 : -1;
      cluster_set->chi_square = chi2_cand;
      cluster_set->xy = pos_set[E16ANA_TrackConstant::kSSD].X();
      CalcRoughZXMomentum(coefs[2], pos_set, &(cluster_set->radius), &(cluster_set->circ_center), &(cluster_set->mom), &(cluster_set->mom_axis));
      for (int i = 0; i < kNumRoughFitDegree[0]; ++i) {
        cluster_set->coefs[i] = coefs[i];
      }
      return true;
    }
  }
#ifdef TRACK_EFF_CHECK
  for (int i = 0; i < 2; ++i) {
    if (is_sim_xcluster[i][0] && is_sim_xcluster[i][1] && is_sim_xcluster[i][2] && is_sim_xcluster[i][3]) {
      if (chi2_cand >= kRoughFitChiSquareThreshold[0]) {
        x_fit_reject_point[i] += Pow2(kRejTgt0XChi2);
      }
      if (fabs(coefs[0]) >= kRoughXFitCoefficientThreshold[0]) {
        x_fit_reject_point[i] += Pow2(kRejTgt0XCoef0);
      }
      if (fabs(coefs[1]) >= kRoughXFitCoefficientThreshold[1]) {
        x_fit_reject_point[i] += Pow2(kRejTgt0XCoef1);
      }
      if (fabs(coefs[2]) >= kRoughXFitCoefficientThreshold[2]) {
        x_fit_reject_point[i] += Pow2(kRejTgt0XCoef2);
      }
    }
  }
#endif // TRACK_EFF_CHECK
  return false;
}

bool E16ANA_TrackCandidates::IsYTrackCandidate(OneAxisClusterSet* cluster_set) {
  auto& pos_set = cluster_set->global_poss;
  array<double, kNumRoughFitDegree[1]> coefs;
  std::array<double, 3> gtr_y({pos_set[1].Y(), pos_set[2].Y(), pos_set[3].Y()});
  std::array<double, 3> gtr_r({sqrt(pos_set[1].X() * pos_set[1].X() + pos_set[1].Z() * pos_set[1].Z()),
                               sqrt(pos_set[2].X() * pos_set[2].X() + pos_set[2].Z() * pos_set[2].Z()),
                               sqrt(pos_set[3].X() * pos_set[3].X() + pos_set[3].Z() * pos_set[3].Z())});
  double r2 = 0.;
  double r  = 0.;
  double c  = 0.;
  double ry = 0.;
  double y  = 0.;
  for (int i = 0; i < 3; ++i) {
    r2 += kYWeight[i] * gtr_r[i] * gtr_r[i];
    r  += kYWeight[i] * gtr_r[i];
    c  += kYWeight[i];
    ry += kYWeight[i] * gtr_r[i] * gtr_y[i];
    y  += kYWeight[i] * gtr_y[i];
  }
  coefs[0] = (r2 * y  - r * ry) / (c * r2 - r * r);
  coefs[1] = (c  * ry - r * y)  / (c * r2 - r * r);
  double chi2 = 0.;
  std::array<double, 3> fit_y;
  for (int i = 0; i < 3; ++i) {
    fit_y[i] = coefs[0] + coefs[1] * gtr_r[i];
    chi2 += kYWeight[i] * (fit_y[i] - gtr_y[i]) * (fit_y[i] - gtr_y[i]);
  }
  
  if (chi2 < kRoughFitChiSquareThreshold[1] && fabs(coefs[0]) < kRoughYFitCoefficientThreshold[0]) {
    cluster_set->chi_square = chi2;
    for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
      cluster_set->coefs[i] = coefs[i];
    }
    return true;
  }
#ifdef TRACK_EFF_CHECK
  for (int i = 0; i < 2; ++i) {
    if (is_sim_ycluster[i][0] && is_sim_ycluster[i][1] && is_sim_ycluster[i][2]) {
      if (chi2 < kRoughFitChiSquareThreshold[1]) {
        y_reject_point[i] += Pow2(kRejYChi2);
      }
      if (fabs(coefs[0]) < kRoughYFitCoefficientThreshold[0]) {
        y_reject_point[i] += Pow2(kRejYCoef0);
      }
    }
  }
#endif
  return false;
}
#endif // TRACK_FIND_WO_TARGET

double E16ANA_TrackCandidates::GTRTimeDiffThreshold(int n) { return kGTRTimeDiffThreshold[n]; }
double E16ANA_TrackCandidates::XSigma(int n) { return kXSigma[n]; }
double E16ANA_TrackCandidates::XWeight(int n) { return kXWeight[n]; }
double E16ANA_TrackCandidates::YSigma(int n) { return kYSigma[n]; }
double E16ANA_TrackCandidates::YWeight(int n) { return kYWeight[n]; }
int E16ANA_TrackCandidates::MinHitsInXCluster() { return kMinHitsInXCluster; }
double E16ANA_TrackCandidates::GTRYDiffThreshold() { return kGTRYDiffThreshold; }
double E16ANA_TrackCandidates::GTRPeakSumThresholdX(int n) { return kGTRPeakSumThresholdX[n]; }
double E16ANA_TrackCandidates::GTRPeakSumThresholdY() { return kGTRPeakSumThresholdY; }
double E16ANA_TrackCandidates::RoughFitChiSquareThreshold(int n) { return kRoughFitChiSquareThreshold[n]; }
double E16ANA_TrackCandidates::RoughXFitCoefficientThreshold(int n) { return kRoughXFitCoefficientThreshold[n]; }
double E16ANA_TrackCandidates::RoughYFitCoefficientThreshold(int n) { return kRoughYFitCoefficientThreshold[n]; }

bool E16ANA_TrackCandidates::HasAssociatedHBD(const OneAxisClusterSet& x_cand, const OneAxisClusterSet& y_cand, vector<bool>* hbd_y_oks) {
  hbd_y_oks->clear();
  hbd_y_oks->assign(x_cand.hbd_indexs.size(), false);
  bool has_hbd = false;
  auto fit_y = y_cand.coefs[0] + y_cand.coefs[1] * kHBDRadius;
  for (int i = 0; i < x_cand.hbd_indexs.size(); ++i) {
    auto index = x_cand.hbd_indexs[i];
    auto y = record->HBD().Cluster(index).LocalPos().Y();
    if (fabs(y - fit_y) < kMaxHBDRoughYRes) {
      hbd_y_oks->at(i) = true;
      has_hbd = true;
    }
  }
  return has_hbd;
}

#ifdef TRACK_FIND_WO_TARGET
TVector3 E16ANA_TrackCandidates::BackInitPos(const TVector3& pos, const TVector3& mom) {
  auto coef = kInitPosBackRadius / mom.Mag();
  return TVector3(pos.X() - coef * mom.X(), pos.Y() - coef * mom.Y(), pos.Z() - coef * mom.Z());
}
#endif // TRACK_FIND_WO_TARGET


void E16ANA_TrackCandidates::SearchTrackCandidatesWithSTS() {
  track_candidates.clear();
  track_candidates.reserve(kNumReserveTracks[2]); // tmp
#ifndef DST1_EVENT_MIX
  auto& sts = record->STS();
#else // DST1_EVENT_MIX
#ifndef MIX_SSD
  auto& sts = record->STS();
#else // MIX_SSD
  auto& sts = prev_record->STS();
#endif // MIX_SSD
#endif // DST1_EVENT_MIX
  auto& gtr = record->GTR();
#ifdef DST1_EVENT_MIX
  auto& prev_gtr = prev_record->GTR();
#endif // DST1_EVENT_MIX
//E16INFO("number of SSD clusters: %d", ssd.NumClusters());
E16INFO("number of STS clusters: %d", sts.NumClusters());
E16INFO("number of GTR clusters: %d", gtr.NumClusters());
if (sts.NumClusters() > 200 ) return;
  std::array<std::vector<OneAxisClusterSet>, 2> cluster_sets;
  cluster_sets[0].reserve(kNumReserveTracks[0]);
  cluster_sets[1].reserve(kNumReserveTracks[1]);
  auto cluster_set = new OneAxisClusterSet();

#ifndef NoExist_SSD
  for (const auto& sts_module_id : E16ANA_TrackConstant::kModuleIDs) {
    if (sts_module_id == 105) {
      continue;
    }
    auto is_l = IsLModule(sts_module_id);
    auto& sts_cluster_ptrs = sts.ClusterPtrs(sts_module_id, 0, 0);
    for (const auto& gtr100_module_id : E16ANA_TrackConstant::kModuleIDs) {
//      if (abs(gtr100_module_id - ssd_module_id) > 1) {
      if (is_l != IsLModule(gtr100_module_id)) {
        continue;
      }
      auto& gtr100x_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsX);
#ifdef DST1_EVENT_MIX
      auto& prev_gtr100x_cluster_ptrs = prev_gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsX);
#endif // DST1_EVENT_MIX
      for (const auto& gtr200_module_id : E16ANA_TrackConstant::kModuleIDs) {
//        if (abs(gtr200_module_id - ssd_module_id) > 1) {
        if (is_l != IsLModule(gtr200_module_id)) {
          continue;
        }
        auto& gtr200x_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsX);
#ifdef DST1_EVENT_MIX
        auto& prev_gtr200x_cluster_ptrs = prev_gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsX);
#endif // DST1_EVENT_MIX
        for (const auto& gtr300_module_id : E16ANA_TrackConstant::kModuleIDs) {
//          if (abs(gtr300_module_id - ssd_module_id) > 1) {
          if (is_l != IsLModule(gtr300_module_id)) {
            continue;
          }
          auto& gtr300x_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsX);
#ifdef DST1_EVENT_MIX
          auto& prev_gtr300x_cluster_ptrs = prev_gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsX);
#endif // DST1_EVENT_MIX
          for (const auto& sts_cluster : sts_cluster_ptrs) {
            cluster_set->sts_cluster = sts_cluster;
            cluster_set->global_poss[E16ANA_TrackConstant::kSSD] = sts_cluster->GlobalPos(*geometry);
#ifndef DST1_EVENT_MIX
            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
#else // DST1_EVENT_MIX
#ifndef MIX_GTR100
            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
#else // MIX_GTR100
            for (const auto& gtr100x_cluster : prev_gtr100x_cluster_ptrs) {
#endif // MIX_GTR100
#endif // DST1_EVENT_MIX
              if (gtr100x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR100 - 1]) {
                continue;
              }
              if (gtr100x_cluster->NumHits() < kMinHitsInXCluster) {
                continue;
              }
              cluster_set->gtr_clusters[0] = gtr100x_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100x_cluster->GlobalPosT(*geometry);
        //TVector3 testg = gtr100x_cluster->GlobalPos(*geometry);
	      //printf("x:%f,%f    y:%f,%f     z:%f,%f \n",cluster_set->global_poss[E16ANA_TrackConstant::kGTR100].X(),testg.X(),
	      //     cluster_set->global_poss[E16ANA_TrackConstant::kGTR100].Y(),testg.Y(),
	      //     cluster_set->global_poss[E16ANA_TrackConstant::kGTR100].Z(),testg.Z());

#ifndef DST1_EVENT_MIX
              for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
#else // DST1_EVENT_MIX
#ifndef MIX_GTR200
              for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
#else // MIX_GTR200
              for (const auto& gtr200x_cluster : prev_gtr200x_cluster_ptrs) {
#endif // MIX_GTR200
#endif // DST1_EVENT_MIX
                if (gtr200x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR200 - 1]) {
                  continue;
                }
                if (gtr200x_cluster->NumHits() < kMinHitsInXCluster) {
                  continue;
                }
                cluster_set->gtr_clusters[1] = gtr200x_cluster;
                cluster_set->global_poss[E16ANA_TrackConstant::kGTR200] = gtr200x_cluster->GlobalPosT(*geometry);
#ifndef DST1_EVENT_MIX
                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
#else // DST1_EVENT_MIX
#ifndef MIX_GTR300
                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
#else // MIX_GTR300
                for (const auto& gtr300x_cluster : prev_gtr300x_cluster_ptrs) {
#endif // MIX_GTR300
#endif // DST1_EVENT_MIX
                  if (gtr300x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR300 - 1]) {
                    continue;
                  }
                  if (gtr300x_cluster->NumHits() < kMinHitsInXCluster) {
                    continue;
                  }
                  cluster_set->gtr_clusters[2] = gtr300x_cluster;
                  cluster_set->global_poss[E16ANA_TrackConstant::kGTR300] = gtr300x_cluster->GlobalPosT(*geometry);
#ifndef TRACK_FIND_WO_TARGET
                  bool is_cand = false;
                  double chi2 = 10000000.;
                  for (int tgt_index = 0; tgt_index < 3; ++tgt_index) {
                    if (IsXTrackCandidate(tgt_index, chi2, cluster_set)) {
                      is_cand = true;
                      chi2 = cluster_set->chi_square;
                    }
                  }
                  if (is_cand) {
                    cluster_sets[0].emplace_back(*cluster_set);
                  }
//                  cluster_set->target_id= 1;
//                  if (IsXTrackCandidate(cluster_set)) {
//                    cluster_sets[0].emplace_back(*cluster_set);
//                  }
//                  if (is_cand) {
//                    cluster_sets[0].emplace_back(*cluster_set);
//                  }
#else // TRACK_FIND_WO_TARGET
                  if (IsXTrackCandidate(cluster_set)) {
                    cluster_sets[0].emplace_back(*cluster_set);
                  }
#endif // TRACK_FIND_WO_TARGET
                }
              }
            }
          }
        }
      }
    }
  }
#else // NoExist_SSD
    for (const auto& gtr100_module_id : E16ANA_TrackConstant::kModuleIDs) {
		auto is_l = IsLModule(gtr100_module_id);
      auto& gtr100x_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsX);
      for (const auto& gtr200_module_id : E16ANA_TrackConstant::kModuleIDs) {
        if (is_l != IsLModule(gtr200_module_id)) {
          continue;
        }
        auto& gtr200x_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsX);
        for (const auto& gtr300_module_id : E16ANA_TrackConstant::kModuleIDs) {
          if (is_l != IsLModule(gtr300_module_id)) {
            continue;
          }
          auto& gtr300x_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsX);
            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
              if (gtr100x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR100 - 1]) {
                continue;
              }
              if (gtr100x_cluster->NumHits() < kMinHitsInXCluster) {
                continue;
              }
              cluster_set->gtr_clusters[0] = gtr100x_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100x_cluster->GlobalPosT(*geometry);
               for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
                if (gtr200x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR200 - 1]) {
                  continue;
                }
                if (gtr200x_cluster->NumHits() < kMinHitsInXCluster) {
                  continue;
                }
                cluster_set->gtr_clusters[1] = gtr200x_cluster;
                cluster_set->global_poss[E16ANA_TrackConstant::kGTR200] = gtr200x_cluster->GlobalPosT(*geometry);
                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
                  if (gtr300x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR300 - 1]) {
                    continue;
                  }
                  if (gtr300x_cluster->NumHits() < kMinHitsInXCluster) {
                    continue;
                  }
                  cluster_set->gtr_clusters[2] = gtr300x_cluster;
                  cluster_set->global_poss[E16ANA_TrackConstant::kGTR300] = gtr300x_cluster->GlobalPosT(*geometry);
#ifndef TRACK_FIND_WO_TARGET
                  bool is_cand = false;
                  double chi2 = 10000000.;
                  for (int tgt_index = 0; tgt_index < 3; ++tgt_index) {
                    if (IsXTrackCandidate(tgt_index, chi2, cluster_set)) {
                      is_cand = true;
                      chi2 = cluster_set->chi_square;
                    }
                  }
                  if (is_cand) {
                    cluster_sets[0].emplace_back(*cluster_set);
                  }
//                  cluster_set->target_id= 1;
//                  if (IsXTrackCandidate(cluster_set)) {
//                    cluster_sets[0].emplace_back(*cluster_set);
//                  }
//                  if (is_cand) {
//                    cluster_sets[0].emplace_back(*cluster_set);
//                  }
#else // TRACK_FIND_WO_TARGET
                  if (IsXTrackCandidate(cluster_set)) {
                    cluster_sets[0].emplace_back(*cluster_set);
                  }
#endif // TRACK_FIND_WO_TARGET
                }
              }
            }
          }
        }
    }


#endif//NoExist_SSD


// ------------- Y AXIS PART Begin -------------- //

  for (const auto& gtr300_module_id : E16ANA_TrackConstant::kModuleIDs) {
    if (gtr300_module_id == 105) {
      continue;
    }
    auto is_l = IsLModule(gtr300_module_id);
    auto& gtr300y_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsY);
#ifdef DST1_EVENT_MIX
    auto& prev_gtr300y_cluster_ptrs = prev_gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsY);
#endif // DST1_EVENT_MIX
    for (const auto& gtr200_module_id : E16ANA_TrackConstant::kModuleIDs) {
//      if (abs(gtr200_module_id - gtr300_module_id) > 1) {
      if (is_l != IsLModule(gtr200_module_id)) {
        continue;
      }
      auto& gtr200y_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsY);
#ifdef DST1_EVENT_MIX
      auto& prev_gtr200y_cluster_ptrs = prev_gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsY);
#endif // DST1_EVENT_MIX
      for (const auto& gtr100_module_id : E16ANA_TrackConstant::kModuleIDs) {
//        if (abs(gtr100_module_id - gtr300_module_id) > 1) {
        if (is_l != IsLModule(gtr100_module_id)) {
          continue;
        }
        auto& gtr100y_cluster_ptrs  = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsY);
        auto& gtr100yb_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsYb);
#ifdef DST1_EVENT_MIX
        auto& prev_gtr100y_cluster_ptrs  = prev_gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsY);
        auto& prev_gtr100yb_cluster_ptrs = prev_gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsYb);
#endif // DST1_EVENT_MIX
#ifndef DST1_EVENT_MIX
        for (const auto& gtr300y_cluster : gtr300y_cluster_ptrs) {
#else // DST1_EVENT_MIX
#ifndef MIX_GTR300
        for (const auto& gtr300y_cluster : gtr300y_cluster_ptrs) {
#else // MIX_GTR300
        for (const auto& gtr300y_cluster : prev_gtr300y_cluster_ptrs) {
#endif // MIX_GTR300
#endif // DST1_EVENT_MIX
          if (gtr300y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
            continue;
          }
          cluster_set->gtr_clusters[2] = gtr300y_cluster;
          cluster_set->global_poss[E16ANA_TrackConstant::kGTR300] = gtr300y_cluster->GlobalPosT(*geometry);
#ifndef  DST1_EVENT_MIX
          for (const auto& gtr200y_cluster : gtr200y_cluster_ptrs) {
#else // DST1_EVENT_MIX
#ifndef MIX_GTR300
          for (const auto& gtr200y_cluster : gtr200y_cluster_ptrs) {
#else // MIX_GTR300
          for (const auto& gtr200y_cluster : prev_gtr200y_cluster_ptrs) {
#endif // MIX_GTR300
#endif // DST1_EVENT_MIX
            if (gtr200y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
              continue;
            }
            cluster_set->gtr_clusters[1] = gtr200y_cluster;
            cluster_set->global_poss[E16ANA_TrackConstant::kGTR200] = gtr200y_cluster->GlobalPosT(*geometry);
#ifndef  DST1_EVENT_MIX
            for (const auto& gtr100y_cluster : gtr100y_cluster_ptrs) {
#else // DST1_EVENT_MIX
#ifndef MIX_GTR300
            for (const auto& gtr100y_cluster : gtr100y_cluster_ptrs) {
#else // MIX_GTR300
            for (const auto& gtr100y_cluster : prev_gtr100y_cluster_ptrs) {
#endif // MIX_GTR300
#endif // DST1_EVENT_MIX
              if (gtr100y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
                continue;
              }
              cluster_set->gtr_clusters[0] = gtr100y_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100y_cluster->GlobalPosT(*geometry);
              if (IsYTrackCandidate(cluster_set)) {
                cluster_sets[1].emplace_back(*cluster_set);
              }
            }
#ifndef  DST1_EVENT_MIX
            for (const auto& gtr100yb_cluster : gtr100yb_cluster_ptrs) {
#else // DST1_EVENT_MIX
#ifndef MIX_GTR300
            for (const auto& gtr100yb_cluster : gtr100yb_cluster_ptrs) {
#else // MIX_GTR300
            for (const auto& gtr100yb_cluster : prev_gtr100yb_cluster_ptrs) {
#endif // MIX_GTR300
#endif // DST1_EVENT_MIX
              if (gtr100yb_cluster->PeakSum() < kGTRPeakSumThresholdY) {
                continue;
              }
              cluster_set->gtr_clusters[0] = gtr100yb_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100yb_cluster->GlobalPosT(*geometry);
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
    auto& gtrx = x_cand.gtr_clusters;
    std::array<int, kNumGTRLayers> x_module_ids = {gtrx[0]->ModuleId(), gtrx[1]->ModuleId(), gtrx[2]->ModuleId()};
    std::array<float, kNumGTRLayers> x_timings = {gtrx[0]->Timing(), gtrx[1]->Timing(), gtrx[2]->Timing()};
    std::array<float, kNumGTRLayers> x_peak_sums = {gtrx[0]->PeakSum(), gtrx[1]->PeakSum(), gtrx[2]->PeakSum()};
    for (const auto& y_cand : cluster_sets[1]) {
      auto& gtry = y_cand.gtr_clusters;
//      IsSameModules();
      bool is_same_module = true;
      if ((gtry[0]->IsY() && gtrx[0]->LocalPosT().X() <= 0) || (gtry[0]->IsYb() && gtrx[0]->LocalPosT().X() >= 0)) {
//cout << "is y yb not match" << endl;
        continue;
      }
      for (int i = 0; i < kNumGTRLayers; ++i) {
//        if (x_module_ids[i] != gtry[i]->ModuleId() || fabs(x_timings[i] - gtry[i]->Timing()) > kGTRTimeDiffThreshold[i]) {
        if (x_module_ids[i] != gtry[i]->ModuleId() || fabs(x_timings[i] - gtry[i]->Timing()) > kGTRTimeDiffThreshold[i] || !ExistADCCorrelation(i, x_peak_sums[i], gtry[i]->PeakSum())) { // ozawa v8
//cout << "x y timing not match" << endl;
          is_same_module = false;
          break;
        }
      }
      if (!is_same_module) {
        continue;
      }
      vector<bool> hbd_y_oks;
      if (kReqHBDAssociation && !HasAssociatedHBD(x_cand, y_cand, &hbd_y_oks)) {
        continue;
      }
//auto offset = kTargetZ[x_cand.target_id];
//auto& ssd = x_cand.global_poss[0];
//auto rot_phi = std::atan2(ssd.X(), ssd.Z() - offset);
//auto rot_cos = std::cos(rot_phi);
//auto rot_sin = std::sin(rot_phi);
//
//auto gtr300 = x_cand.global_poss[3];
//auto x = gtr300.X();
//auto z = gtr300.Z();
//double lotate_x = rot_cos * x - rot_sin * (z - offset);
//double lotate_z = rot_sin * x + rot_cos * (z - offset);
//array<double, 2> coefs;
//coefs[1] = 2. * x_cand.coefs[2] * lotate_z + x_cand.coefs[1];
//coefs[0] = lotate_x - coefs[1] * lotate_z;
//int cid[4] = {x_cand.ssd_cluster->ClusterId(), x_cand.gtr_clusters[0]->ClusterId(), x_cand.gtr_clusters[1]->ClusterId(), x_cand.gtr_clusters[2]->ClusterId()};
//cout << "ID: " << cid[0] << " " << cid[1] << " " << cid[2] << " " << cid[3] << endl;
//cout << "rot phi: " << rot_phi << " " << rot_cos << " " << rot_sin << " " << offset << endl;
//cout << "gtr: " << x << " " << z << endl;
//cout << "lotate gtr: " << lotate_x << " " << lotate_z << endl;
//cout << "x coefs: " << x_cand.coefs[2] << " " << x_cand.coefs[1] << endl;
//cout << "coef: " << coefs[0] << " " << coefs[1] << endl;
//for (int i = 0; i < x_cand.hbd_indexs.size(); ++i) {
//  auto index = x_cand.hbd_indexs[i];
//  auto& hbd = record->HBD().Cluster(index);
//  auto hit_x = hbd.GlobalPos(*geometry).X();
//  auto hit_z = hbd.GlobalPos(*geometry).Z();
//  double lotate_hit_x = rot_cos * hit_x - rot_sin * (hit_z - offset);
//  double lotate_hit_z = rot_sin * hit_x + rot_cos * (hit_z - offset);
//  auto res = pow((lotate_hit_x - coefs[0] - coefs[1] * lotate_hit_z) * (lotate_hit_x - coefs[0] - coefs[1] * lotate_hit_z) / (coefs[1] * coefs[1] + 1.), 0.5);
//  auto res2 = x_cand.hbd_ress[i];
//  cout << "  HBD ID: " << hbd.ClusterId() << endl;
//  cout << "  HBD: " << hit_x << " " << hit_z << endl;
//  cout << "  lotate HBD: " << lotate_hit_x << " " << lotate_hit_z << endl;
//  cout << "  res: " << res << " " << res2 << endl;
//}
      track_candidates.emplace_back(E16ANA_TrackCandidate(geometry, bfield_map));
      auto& tmp_cand = track_candidates.back();
      tmp_cand.SetTrackID(track_candidates.size() - 1);
      tmp_cand.SetCharge(x_cand.charge);
#ifndef TRACK_FIND_WO_TARGET
      tmp_cand.SetInitX(x_cand.xy);
      tmp_cand.SetInitY(y_cand.xy);
      tmp_cand.SetInitZ(kTargetZ[x_cand.target_id]);
      tmp_cand.SetTargetID(x_cand.target_id);
#else // TRACK_FIND_WO_TARGET
      tmp_cand.SetTargetID(1);
      tmp_cand.SetRadius(x_cand.radius);
      tmp_cand.SetCircleCenter(x_cand.circ_center);
#ifndef NoExist_SSD
      auto sts_gpos = x_cand.sts_cluster->GlobalPos(*geometry);
      auto pre_init_pos = TVector3(sts_gpos.X(), CalcRoughYPosition(x_cand.sts_cluster->ModuleId(), y_cand.coefs), sts_gpos.Z());
#else // NoExist_SSD
      auto gtr100_gpos = gtrx[0]->GlobalPos(*geometry);
      auto pre_init_pos = TVector3(gtr100_gpos.X(), gtr100_gpos.Y(),gtr100_gpos.Z());
#endif// No Exist SSD
      auto init_mom = TVector3(x_cand.mom_axis.X(), CalcRoughYMomentum(x_cand.mom, y_cand.coefs[1]), x_cand.mom_axis.Z());
      auto init_pos = BackInitPos(pre_init_pos, init_mom);
      tmp_cand.SetInitX(init_pos.X());
      tmp_cand.SetInitY(init_pos.Y());
      tmp_cand.SetInitZ(init_pos.Z());
      tmp_cand.SetInitMomX(init_mom.X());
      tmp_cand.SetInitMomY(init_mom.Y());
      tmp_cand.SetInitMomZ(init_mom.Z());
#endif // TRACK_FIND_WO_TARGET
      tmp_cand.SetDefaultSigma();
      tmp_cand.SetXChiSquare(x_cand.chi_square);
      tmp_cand.SetYChiSquare(y_cand.chi_square);
#ifdef TRACK_FIND_WO_TARGET
      for (int i = 0; i < 2; ++i) {
        tmp_cand.SetXDist(i, x_cand.dists[i]);
      }
#endif // TRACK_FIND_WO_TARGET
      for (int i = 0; i < kNumRoughFitDegree[0]; ++i) {
        tmp_cand.SetXCoef(i, x_cand.coefs[i]);
      }
      for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
        tmp_cand.SetYCoef(i, y_cand.coefs[i]);
      }
      tmp_cand.SetAssociatedHBD(x_cand.hbd_ids, x_cand.hbd_ress, hbd_y_oks);
      auto& cluster_pairs = tmp_cand.ClusterPairs();
#ifndef NoExist_SSD
      auto& stsx = *x_cand.sts_cluster;
      cluster_pairs[0].Set(geometry, 0, stsx.ModuleId(), x_cand.global_poss[0], &stsx);
      for (int i = 0; i < kNumGTRLayers; ++i) {
        cluster_pairs[1 + i].Set(geometry, 1 + i, gtrx[i]->ModuleId(), x_cand.global_poss[1 + i], y_cand.global_poss[1 + i], gtrx[i], gtry[i]);
	      int nhit = gtrx[i]->NumCls();
	      for(int j=0;j<nhit;j++){
	        cluster_pairs[1+i].SetCTiming((double)gtrx[i]->CTiming(j));
	        cluster_pairs[1+i].SetCPos((double)gtrx[i]->CPos(j));
	      }
      }
#else 
//	   cluster_pairs[0].Set(geometry, 0, ssdx.ModuleId(), x_cand.global_poss[0], &ssdx);
      for (int i = 0; i < kNumGTRLayers; ++i) {
        cluster_pairs[1 + i].Set(geometry, 1 + i, gtrx[i]->ModuleId(), x_cand.global_poss[1 + i], y_cand.global_poss[1 + i], gtrx[i], gtry[i]);
	      int nhit = gtrx[i]->NumCls();
	      for(int j=0;j<nhit;j++){
	        cluster_pairs[1+i].SetCTiming((double)gtrx[i]->CTiming(j));
	        cluster_pairs[1+i].SetCPos((double)gtrx[i]->CPos(j));
	      }
      }
#endif
    }
  }
}













#ifndef TRACK_EFF_CHECK
void E16ANA_TrackCandidates::SearchTrackCandidates() {
  track_candidates.clear();
  track_candidates.reserve(kNumReserveTracks[2]); // tmp
#ifndef DST1_EVENT_MIX
  auto& ssd = record->SSD();
#else // DST1_EVENT_MIX
#ifndef MIX_SSD
  auto& ssd = record->SSD();
#else // MIX_SSD
  auto& ssd = prev_record->SSD();
#endif // MIX_SSD
#endif // DST1_EVENT_MIX
  auto& gtr = record->GTR();
#ifdef DST1_EVENT_MIX
  auto& prev_gtr = prev_record->GTR();
#endif // DST1_EVENT_MIX
E16INFO("number of SSD clusters: %d", ssd.NumClusters());
E16INFO("number of GTR clusters: %d", gtr.NumClusters());
  std::array<std::vector<OneAxisClusterSet>, 2> cluster_sets;
  cluster_sets[0].reserve(kNumReserveTracks[0]);
  cluster_sets[1].reserve(kNumReserveTracks[1]);
  auto cluster_set = new OneAxisClusterSet();

#ifndef NoExist_SSD
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
#ifdef DST1_EVENT_MIX
      auto& prev_gtr100x_cluster_ptrs = prev_gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsX);
#endif // DST1_EVENT_MIX
      for (const auto& gtr200_module_id : E16ANA_TrackConstant::kModuleIDs) {
//        if (abs(gtr200_module_id - ssd_module_id) > 1) {
        if (is_l != IsLModule(gtr200_module_id)) {
          continue;
        }
        auto& gtr200x_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsX);
#ifdef DST1_EVENT_MIX
        auto& prev_gtr200x_cluster_ptrs = prev_gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsX);
#endif // DST1_EVENT_MIX
        for (const auto& gtr300_module_id : E16ANA_TrackConstant::kModuleIDs) {
//          if (abs(gtr300_module_id - ssd_module_id) > 1) {
          if (is_l != IsLModule(gtr300_module_id)) {
            continue;
          }
          auto& gtr300x_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsX);
#ifdef DST1_EVENT_MIX
          auto& prev_gtr300x_cluster_ptrs = prev_gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsX);
#endif // DST1_EVENT_MIX
          for (const auto& ssd_cluster : ssd_cluster_ptrs) {
            cluster_set->ssd_cluster = ssd_cluster;
            cluster_set->global_poss[E16ANA_TrackConstant::kSSD] = ssd_cluster->GlobalPos(*geometry);
#ifndef DST1_EVENT_MIX
            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
#else // DST1_EVENT_MIX
#ifndef MIX_GTR100
            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
#else // MIX_GTR100
            for (const auto& gtr100x_cluster : prev_gtr100x_cluster_ptrs) {
#endif // MIX_GTR100
#endif // DST1_EVENT_MIX
              if (gtr100x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR100 - 1]) {
                continue;
              }
              if (gtr100x_cluster->NumHits() < kMinHitsInXCluster) {
                continue;
              }
              cluster_set->gtr_clusters[0] = gtr100x_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100x_cluster->GlobalPosT(*geometry);
        //TVector3 testg = gtr100x_cluster->GlobalPos(*geometry);
	      //printf("x:%f,%f    y:%f,%f     z:%f,%f \n",cluster_set->global_poss[E16ANA_TrackConstant::kGTR100].X(),testg.X(),
	      //     cluster_set->global_poss[E16ANA_TrackConstant::kGTR100].Y(),testg.Y(),
	      //     cluster_set->global_poss[E16ANA_TrackConstant::kGTR100].Z(),testg.Z());

#ifndef DST1_EVENT_MIX
              for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
#else // DST1_EVENT_MIX
#ifndef MIX_GTR200
              for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
#else // MIX_GTR200
              for (const auto& gtr200x_cluster : prev_gtr200x_cluster_ptrs) {
#endif // MIX_GTR200
#endif // DST1_EVENT_MIX
                if (gtr200x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR200 - 1]) {
                  continue;
                }
                if (gtr200x_cluster->NumHits() < kMinHitsInXCluster) {
                  continue;
                }
                cluster_set->gtr_clusters[1] = gtr200x_cluster;
                cluster_set->global_poss[E16ANA_TrackConstant::kGTR200] = gtr200x_cluster->GlobalPosT(*geometry);
#ifndef DST1_EVENT_MIX
                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
#else // DST1_EVENT_MIX
#ifndef MIX_GTR300
                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
#else // MIX_GTR300
                for (const auto& gtr300x_cluster : prev_gtr300x_cluster_ptrs) {
#endif // MIX_GTR300
#endif // DST1_EVENT_MIX
                  if (gtr300x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR300 - 1]) {
                    continue;
                  }
                  if (gtr300x_cluster->NumHits() < kMinHitsInXCluster) {
                    continue;
                  }
                  cluster_set->gtr_clusters[2] = gtr300x_cluster;
                  cluster_set->global_poss[E16ANA_TrackConstant::kGTR300] = gtr300x_cluster->GlobalPosT(*geometry);
#ifndef TRACK_FIND_WO_TARGET
                  bool is_cand = false;
                  double chi2 = 10000000.;
                  for (int tgt_index = 0; tgt_index < 3; ++tgt_index) {
                    if (IsXTrackCandidate(tgt_index, chi2, cluster_set)) {
                      is_cand = true;
                      chi2 = cluster_set->chi_square;
                    }
                  }
                  if (is_cand) {
                    cluster_sets[0].emplace_back(*cluster_set);
                  }
//                  cluster_set->target_id= 1;
//                  if (IsXTrackCandidate(cluster_set)) {
//                    cluster_sets[0].emplace_back(*cluster_set);
//                  }
//                  if (is_cand) {
//                    cluster_sets[0].emplace_back(*cluster_set);
//                  }
#else // TRACK_FIND_WO_TARGET
                  if (IsXTrackCandidate(cluster_set)) {
                    cluster_sets[0].emplace_back(*cluster_set);
                  }
#endif // TRACK_FIND_WO_TARGET
                }
              }
            }
          }
        }
      }
    }
  }
#else // NoExist_SSD
    for (const auto& gtr100_module_id : E16ANA_TrackConstant::kModuleIDs) {
		auto is_l = IsLModule(gtr100_module_id);
      auto& gtr100x_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsX);
      for (const auto& gtr200_module_id : E16ANA_TrackConstant::kModuleIDs) {
        if (is_l != IsLModule(gtr200_module_id)) {
          continue;
        }
        auto& gtr200x_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsX);
        for (const auto& gtr300_module_id : E16ANA_TrackConstant::kModuleIDs) {
          if (is_l != IsLModule(gtr300_module_id)) {
            continue;
          }
          auto& gtr300x_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsX);
            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
              if (gtr100x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR100 - 1]) {
                continue;
              }
              if (gtr100x_cluster->NumHits() < kMinHitsInXCluster) {
                continue;
              }
              cluster_set->gtr_clusters[0] = gtr100x_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100x_cluster->GlobalPosT(*geometry);
               for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
                if (gtr200x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR200 - 1]) {
                  continue;
                }
                if (gtr200x_cluster->NumHits() < kMinHitsInXCluster) {
                  continue;
                }
                cluster_set->gtr_clusters[1] = gtr200x_cluster;
                cluster_set->global_poss[E16ANA_TrackConstant::kGTR200] = gtr200x_cluster->GlobalPosT(*geometry);
                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
                  if (gtr300x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR300 - 1]) {
                    continue;
                  }
                  if (gtr300x_cluster->NumHits() < kMinHitsInXCluster) {
                    continue;
                  }
                  cluster_set->gtr_clusters[2] = gtr300x_cluster;
                  cluster_set->global_poss[E16ANA_TrackConstant::kGTR300] = gtr300x_cluster->GlobalPosT(*geometry);
#ifndef TRACK_FIND_WO_TARGET
                  bool is_cand = false;
                  double chi2 = 10000000.;
                  for (int tgt_index = 0; tgt_index < 3; ++tgt_index) {
                    if (IsXTrackCandidate(tgt_index, chi2, cluster_set)) {
                      is_cand = true;
                      chi2 = cluster_set->chi_square;
                    }
                  }
                  if (is_cand) {
                    cluster_sets[0].emplace_back(*cluster_set);
                  }
//                  cluster_set->target_id= 1;
//                  if (IsXTrackCandidate(cluster_set)) {
//                    cluster_sets[0].emplace_back(*cluster_set);
//                  }
//                  if (is_cand) {
//                    cluster_sets[0].emplace_back(*cluster_set);
//                  }
#else // TRACK_FIND_WO_TARGET
                  if (IsXTrackCandidate(cluster_set)) {
                    cluster_sets[0].emplace_back(*cluster_set);
                  }
#endif // TRACK_FIND_WO_TARGET
                }
              }
            }
          }
        }
    }


#endif//NoExist_SSD


// ------------- Y AXIS PART Begin -------------- //

  for (const auto& gtr300_module_id : E16ANA_TrackConstant::kModuleIDs) {
    if (gtr300_module_id == 105) {
      continue;
    }
    auto is_l = IsLModule(gtr300_module_id);
    auto& gtr300y_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsY);
#ifdef DST1_EVENT_MIX
    auto& prev_gtr300y_cluster_ptrs = prev_gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsY);
#endif // DST1_EVENT_MIX
    for (const auto& gtr200_module_id : E16ANA_TrackConstant::kModuleIDs) {
//      if (abs(gtr200_module_id - gtr300_module_id) > 1) {
      if (is_l != IsLModule(gtr200_module_id)) {
        continue;
      }
      auto& gtr200y_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsY);
#ifdef DST1_EVENT_MIX
      auto& prev_gtr200y_cluster_ptrs = prev_gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsY);
#endif // DST1_EVENT_MIX
      for (const auto& gtr100_module_id : E16ANA_TrackConstant::kModuleIDs) {
//        if (abs(gtr100_module_id - gtr300_module_id) > 1) {
        if (is_l != IsLModule(gtr100_module_id)) {
          continue;
        }
        auto& gtr100y_cluster_ptrs  = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsY);
        auto& gtr100yb_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsYb);
#ifdef DST1_EVENT_MIX
        auto& prev_gtr100y_cluster_ptrs  = prev_gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsY);
        auto& prev_gtr100yb_cluster_ptrs = prev_gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsYb);
#endif // DST1_EVENT_MIX
#ifndef DST1_EVENT_MIX
        for (const auto& gtr300y_cluster : gtr300y_cluster_ptrs) {
#else // DST1_EVENT_MIX
#ifndef MIX_GTR300
        for (const auto& gtr300y_cluster : gtr300y_cluster_ptrs) {
#else // MIX_GTR300
        for (const auto& gtr300y_cluster : prev_gtr300y_cluster_ptrs) {
#endif // MIX_GTR300
#endif // DST1_EVENT_MIX
          if (gtr300y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
            continue;
          }
          cluster_set->gtr_clusters[2] = gtr300y_cluster;
          cluster_set->global_poss[E16ANA_TrackConstant::kGTR300] = gtr300y_cluster->GlobalPosT(*geometry);
#ifndef  DST1_EVENT_MIX
          for (const auto& gtr200y_cluster : gtr200y_cluster_ptrs) {
#else // DST1_EVENT_MIX
#ifndef MIX_GTR300
          for (const auto& gtr200y_cluster : gtr200y_cluster_ptrs) {
#else // MIX_GTR300
          for (const auto& gtr200y_cluster : prev_gtr200y_cluster_ptrs) {
#endif // MIX_GTR300
#endif // DST1_EVENT_MIX
            if (gtr200y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
              continue;
            }
            cluster_set->gtr_clusters[1] = gtr200y_cluster;
            cluster_set->global_poss[E16ANA_TrackConstant::kGTR200] = gtr200y_cluster->GlobalPosT(*geometry);
#ifndef  DST1_EVENT_MIX
            for (const auto& gtr100y_cluster : gtr100y_cluster_ptrs) {
#else // DST1_EVENT_MIX
#ifndef MIX_GTR300
            for (const auto& gtr100y_cluster : gtr100y_cluster_ptrs) {
#else // MIX_GTR300
            for (const auto& gtr100y_cluster : prev_gtr100y_cluster_ptrs) {
#endif // MIX_GTR300
#endif // DST1_EVENT_MIX
              if (gtr100y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
                continue;
              }
              cluster_set->gtr_clusters[0] = gtr100y_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100y_cluster->GlobalPosT(*geometry);
              if (IsYTrackCandidate(cluster_set)) {
                cluster_sets[1].emplace_back(*cluster_set);
              }
            }
#ifndef  DST1_EVENT_MIX
            for (const auto& gtr100yb_cluster : gtr100yb_cluster_ptrs) {
#else // DST1_EVENT_MIX
#ifndef MIX_GTR300
            for (const auto& gtr100yb_cluster : gtr100yb_cluster_ptrs) {
#else // MIX_GTR300
            for (const auto& gtr100yb_cluster : prev_gtr100yb_cluster_ptrs) {
#endif // MIX_GTR300
#endif // DST1_EVENT_MIX
              if (gtr100yb_cluster->PeakSum() < kGTRPeakSumThresholdY) {
                continue;
              }
              cluster_set->gtr_clusters[0] = gtr100yb_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100yb_cluster->GlobalPosT(*geometry);
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
    auto& gtrx = x_cand.gtr_clusters;
    std::array<int, kNumGTRLayers> x_module_ids = {gtrx[0]->ModuleId(), gtrx[1]->ModuleId(), gtrx[2]->ModuleId()};
    std::array<float, kNumGTRLayers> x_timings = {gtrx[0]->Timing(), gtrx[1]->Timing(), gtrx[2]->Timing()};
    std::array<float, kNumGTRLayers> x_peak_sums = {gtrx[0]->PeakSum(), gtrx[1]->PeakSum(), gtrx[2]->PeakSum()};
    for (const auto& y_cand : cluster_sets[1]) {
      auto& gtry = y_cand.gtr_clusters;
//      IsSameModules();
      bool is_same_module = true;
      if ((gtry[0]->IsY() && gtrx[0]->LocalPosT().X() <= 0) || (gtry[0]->IsYb() && gtrx[0]->LocalPosT().X() >= 0)) {
//cout << "is y yb not match" << endl;
        continue;
      }
      for (int i = 0; i < kNumGTRLayers; ++i) {
//        if (x_module_ids[i] != gtry[i]->ModuleId() || fabs(x_timings[i] - gtry[i]->Timing()) > kGTRTimeDiffThreshold[i]) {
        if (x_module_ids[i] != gtry[i]->ModuleId() || fabs(x_timings[i] - gtry[i]->Timing()) > kGTRTimeDiffThreshold[i] || !ExistADCCorrelation(i, x_peak_sums[i], gtry[i]->PeakSum())) { // ozawa v8
//cout << "x y timing not match" << endl;
          is_same_module = false;
          break;
        }
      }
      if (!is_same_module) {
        continue;
      }
      vector<bool> hbd_y_oks;
      if (kReqHBDAssociation && !HasAssociatedHBD(x_cand, y_cand, &hbd_y_oks)) {
        continue;
      }
//auto offset = kTargetZ[x_cand.target_id];
//auto& ssd = x_cand.global_poss[0];
//auto rot_phi = std::atan2(ssd.X(), ssd.Z() - offset);
//auto rot_cos = std::cos(rot_phi);
//auto rot_sin = std::sin(rot_phi);
//
//auto gtr300 = x_cand.global_poss[3];
//auto x = gtr300.X();
//auto z = gtr300.Z();
//double lotate_x = rot_cos * x - rot_sin * (z - offset);
//double lotate_z = rot_sin * x + rot_cos * (z - offset);
//array<double, 2> coefs;
//coefs[1] = 2. * x_cand.coefs[2] * lotate_z + x_cand.coefs[1];
//coefs[0] = lotate_x - coefs[1] * lotate_z;
//int cid[4] = {x_cand.ssd_cluster->ClusterId(), x_cand.gtr_clusters[0]->ClusterId(), x_cand.gtr_clusters[1]->ClusterId(), x_cand.gtr_clusters[2]->ClusterId()};
//cout << "ID: " << cid[0] << " " << cid[1] << " " << cid[2] << " " << cid[3] << endl;
//cout << "rot phi: " << rot_phi << " " << rot_cos << " " << rot_sin << " " << offset << endl;
//cout << "gtr: " << x << " " << z << endl;
//cout << "lotate gtr: " << lotate_x << " " << lotate_z << endl;
//cout << "x coefs: " << x_cand.coefs[2] << " " << x_cand.coefs[1] << endl;
//cout << "coef: " << coefs[0] << " " << coefs[1] << endl;
//for (int i = 0; i < x_cand.hbd_indexs.size(); ++i) {
//  auto index = x_cand.hbd_indexs[i];
//  auto& hbd = record->HBD().Cluster(index);
//  auto hit_x = hbd.GlobalPos(*geometry).X();
//  auto hit_z = hbd.GlobalPos(*geometry).Z();
//  double lotate_hit_x = rot_cos * hit_x - rot_sin * (hit_z - offset);
//  double lotate_hit_z = rot_sin * hit_x + rot_cos * (hit_z - offset);
//  auto res = pow((lotate_hit_x - coefs[0] - coefs[1] * lotate_hit_z) * (lotate_hit_x - coefs[0] - coefs[1] * lotate_hit_z) / (coefs[1] * coefs[1] + 1.), 0.5);
//  auto res2 = x_cand.hbd_ress[i];
//  cout << "  HBD ID: " << hbd.ClusterId() << endl;
//  cout << "  HBD: " << hit_x << " " << hit_z << endl;
//  cout << "  lotate HBD: " << lotate_hit_x << " " << lotate_hit_z << endl;
//  cout << "  res: " << res << " " << res2 << endl;
//}
      track_candidates.emplace_back(E16ANA_TrackCandidate(geometry, bfield_map));
      auto& tmp_cand = track_candidates.back();
      tmp_cand.SetTrackID(track_candidates.size() - 1);
      tmp_cand.SetCharge(x_cand.charge);
#ifndef TRACK_FIND_WO_TARGET
      tmp_cand.SetInitX(x_cand.xy);
      tmp_cand.SetInitY(y_cand.xy);
      tmp_cand.SetInitZ(kTargetZ[x_cand.target_id]);
      tmp_cand.SetTargetID(x_cand.target_id);
#else // TRACK_FIND_WO_TARGET
      tmp_cand.SetTargetID(1);
      tmp_cand.SetRadius(x_cand.radius);
      tmp_cand.SetCircleCenter(x_cand.circ_center);
#ifndef NoExist_SSD
      auto ssd_gpos = x_cand.ssd_cluster->GlobalPos(*geometry);
      auto pre_init_pos = TVector3(ssd_gpos.X(), CalcRoughYPosition(x_cand.ssd_cluster->ModuleId(), y_cand.coefs), ssd_gpos.Z());
#else // NoExist_SSD
      auto gtr100_gpos = gtrx[0]->GlobalPos(*geometry);
      auto pre_init_pos = TVector3(gtr100_gpos.X(), gtr100_gpos.Y(),gtr100_gpos.Z());
#endif// No Exist SSD
      auto init_mom = TVector3(x_cand.mom_axis.X(), CalcRoughYMomentum(x_cand.mom, y_cand.coefs[1]), x_cand.mom_axis.Z());
      auto init_pos = BackInitPos(pre_init_pos, init_mom);
      tmp_cand.SetInitX(init_pos.X());
      tmp_cand.SetInitY(init_pos.Y());
      tmp_cand.SetInitZ(init_pos.Z());
      tmp_cand.SetInitMomX(init_mom.X());
      tmp_cand.SetInitMomY(init_mom.Y());
      tmp_cand.SetInitMomZ(init_mom.Z());
#endif // TRACK_FIND_WO_TARGET
      tmp_cand.SetDefaultSigma();
      tmp_cand.SetXChiSquare(x_cand.chi_square);
      tmp_cand.SetYChiSquare(y_cand.chi_square);
#ifdef TRACK_FIND_WO_TARGET
      for (int i = 0; i < 2; ++i) {
        tmp_cand.SetXDist(i, x_cand.dists[i]);
      }
#endif // TRACK_FIND_WO_TARGET
      for (int i = 0; i < kNumRoughFitDegree[0]; ++i) {
        tmp_cand.SetXCoef(i, x_cand.coefs[i]);
      }
      for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
        tmp_cand.SetYCoef(i, y_cand.coefs[i]);
      }
      tmp_cand.SetAssociatedHBD(x_cand.hbd_ids, x_cand.hbd_ress, hbd_y_oks);
      auto& cluster_pairs = tmp_cand.ClusterPairs();
#ifndef NoExist_SSD
      auto& ssdx = *x_cand.ssd_cluster;
      cluster_pairs[0].Set(geometry, 0, ssdx.ModuleId(), x_cand.global_poss[0], &ssdx);
      for (int i = 0; i < kNumGTRLayers; ++i) {
        cluster_pairs[1 + i].Set(geometry, 1 + i, gtrx[i]->ModuleId(), x_cand.global_poss[1 + i], y_cand.global_poss[1 + i], gtrx[i], gtry[i]);
	      int nhit = gtrx[i]->NumCls();
	      for(int j=0;j<nhit;j++){
	        cluster_pairs[1+i].SetCTiming((double)gtrx[i]->CTiming(j));
	        cluster_pairs[1+i].SetCPos((double)gtrx[i]->CPos(j));
	      }
      }
#else 
//	   cluster_pairs[0].Set(geometry, 0, ssdx.ModuleId(), x_cand.global_poss[0], &ssdx);
      for (int i = 0; i < kNumGTRLayers; ++i) {
        cluster_pairs[1 + i].Set(geometry, 1 + i, gtrx[i]->ModuleId(), x_cand.global_poss[1 + i], y_cand.global_poss[1 + i], gtrx[i], gtry[i]);
	      int nhit = gtrx[i]->NumCls();
	      for(int j=0;j<nhit;j++){
	        cluster_pairs[1+i].SetCTiming((double)gtrx[i]->CTiming(j));
	        cluster_pairs[1+i].SetCPos((double)gtrx[i]->CPos(j));
	      }
      }


#endif



    }
  }
}
#else // TRACK_EFF_CHECK

void E16ANA_TrackCandidates::SearchTrackCandidates() {//with Old SSD
  for (int i = 0; i < 2; ++i) {
    is_xchecked[i].fill(false);
    is_ychecked[i].fill(false);
    is_sim_xcluster[i].fill(false);
    is_sim_ycluster[i].fill(false);
  }
  x_search_reject_point.fill(0);
  x_fit_reject_point.fill(0);
  y_reject_point.fill(0);
  xy_reject_point.fill(0);
  reject_point.fill(0);
  sim_track_detected.fill(false);
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
            if (ssd_cluster->IsMerged()) {
              continue;
            }
            auto ssdcid = ssd_cluster->ClusterId();
            is_sim_xcluster[0][0] = ssdcid >= kMockClusterID && ssdcid < kMockClusterID * 2;
            is_sim_xcluster[1][0] = ssdcid >= kMockClusterID * 2;
            cluster_set->ssd_cluster = ssd_cluster;
            cluster_set->global_poss[E16ANA_TrackConstant::kSSD] = ssd_cluster->GlobalPos(*geometry);
            for (int i = 0; i < 2; ++i) {
              if (!is_xchecked[i][0] && is_sim_xcluster[i][0]) {
                is_xchecked[i][0] = true;
              }
            }
            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
              if (gtr100x_cluster->IsMerged()) {
                continue;
              }
              auto gtr1xcid = gtr100x_cluster->ClusterId();
              is_sim_xcluster[0][1] = gtr1xcid >= kMockClusterID && gtr1xcid < kMockClusterID * 2;
              is_sim_xcluster[1][1] = gtr1xcid >= kMockClusterID * 2;
              if (gtr100x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR100 - 1]) {
                for (int i = 0; i < 2; ++i) {
                  if (!is_xchecked[i][1] && is_sim_xcluster[i][0] && is_sim_xcluster[i][1]) {
                    x_search_reject_point[i] += Pow2(kRej100xADC);
                    reject_point[i] += Pow2(kRejXSearch);
                    is_xchecked[i][1] = true;
                  }
                }
                continue;
              }
              if (gtr100x_cluster->ClusterId() < kMockClusterID && gtr100x_cluster->NumHits() < kMinHitsInXCluster) {
                continue;
              }
//              if (gtr100x_cluster->NumHits() < kMinHitsInXCluster) {
//                if (!is_xchecked[1] && is_sim_xcluster[0] && is_sim_xcluster[1]) {
//                  x_search_reject_point += Pow2(kRej100xSize);
//                  reject_point += Pow2(kRejXSearch);
//                  is_xchecked[1] = true;
//                }
//                continue;
//              }
              cluster_set->gtr_clusters[0] = gtr100x_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100x_cluster->GlobalPosT(*geometry);
        //TVector3 testg = gtr100x_cluster->GlobalPos(*geometry);
	      //printf("x:%f,%f    y:%f,%f     z:%f,%f \n",cluster_set->global_poss[E16ANA_TrackConstant::kGTR100].X(),testg.X(),
	      //     cluster_set->global_poss[E16ANA_TrackConstant::kGTR100].Y(),testg.Y(),
	      //     cluster_set->global_poss[E16ANA_TrackConstant::kGTR100].Z(),testg.Z());

              for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
                if (gtr200x_cluster->IsMerged()) {
                  continue;
                }
                auto gtr2xcid = gtr200x_cluster->ClusterId();
                is_sim_xcluster[0][2] = gtr2xcid >= kMockClusterID && gtr2xcid < kMockClusterID * 2;
                is_sim_xcluster[1][2] = gtr2xcid >= kMockClusterID * 2;
                if (gtr200x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR200 - 1]) {
                  for (int i = 0; i < 2; ++i) {
                    if (!is_xchecked[i][2] && is_sim_xcluster[i][0] && is_sim_xcluster[i][1] && is_sim_xcluster[i][2]) {
                      x_search_reject_point[i] += Pow2(kRej200xADC);
                      reject_point[i] += Pow2(kRejXSearch);
                      is_xchecked[i][2] = true;
                    }
                  }
                  continue;
                }
                if (gtr200x_cluster->ClusterId() < kMockClusterID && gtr200x_cluster->NumHits() < kMinHitsInXCluster) {
                  continue;
                }
//                if (gtr200x_cluster->NumHits() < kMinHitsInXCluster) {
//                  if (!is_xchecked[2] && is_sim_xcluster[0] && is_sim_xcluster[1] && is_sim_xcluster[2]) {
//                    x_search_reject_point += Pow2(kRej200xSize);
//                    reject_point += Pow2(kRejXSearch);
//                    is_xchecked[2] = true;
//                  }
//                  continue;
//                }
                cluster_set->gtr_clusters[1] = gtr200x_cluster;
                cluster_set->global_poss[E16ANA_TrackConstant::kGTR200] = gtr200x_cluster->GlobalPosT(*geometry);
                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
                  if (gtr300x_cluster->IsMerged()) {
                    continue;
                  }
                  auto gtr3xcid = gtr300x_cluster->ClusterId();
                  is_sim_xcluster[0][3] = gtr3xcid >= kMockClusterID && gtr3xcid < kMockClusterID * 2;
                  is_sim_xcluster[1][3] = gtr3xcid >= kMockClusterID * 2;
                  if (gtr300x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_TrackConstant::kGTR300 - 1]) {
                    for (int i = 0; i < 2; ++i) {
                      if (!is_xchecked[i][3] && is_sim_xcluster[i][0] && is_sim_xcluster[i][1] && is_sim_xcluster[i][2] && is_sim_xcluster[i][3]) {
                        x_search_reject_point[i] += Pow2(kRej300xSize);
                        reject_point[i] += Pow2(kRejXSearch);
                        is_xchecked[i][3] = true;
                      }
                    }
                    continue;
                  }
                  if (gtr300x_cluster->ClusterId() < kMockClusterID && gtr300x_cluster->NumHits() < kMinHitsInXCluster) {
                    continue;
                  }
//                  if (gtr300x_cluster->NumHits() < kMinHitsInXCluster) {
//                    if (!is_xchecked[3] && is_sim_xcluster[0] && is_sim_xcluster[1] && is_sim_xcluster[2] && is_sim_xcluster[3]) {
//                      x_search_reject_point += Pow2(kRej300xSize);
//                      reject_point += Pow2(kRejXSearch);
//                      is_xchecked[3] = true;
//                    }
//                    continue;
//                  }
                  cluster_set->gtr_clusters[2] = gtr300x_cluster;
                  cluster_set->global_poss[E16ANA_TrackConstant::kGTR300] = gtr300x_cluster->GlobalPosT(*geometry);
#ifndef TRACK_FIND_WO_TARGET
                  bool is_cand = false;
                  double chi2 = 10000000.;
#ifdef SIM_DST1_GEOM_CHECK
for (int i = 0; i < 4; ++i) {
  auto& pos = cluster_set->global_poss[i];
  cout << i << " x: " << pos.X() << ", z: " << pos.Z() << endl;
}
#endif // SIM_DST1_GEOM_CHECK
                  for (int tgt_index = 0; tgt_index < 3; ++tgt_index) {
                    if (IsXTrackCandidate(tgt_index, chi2, cluster_set)) {
                      is_cand = true;
                      chi2 = cluster_set->chi_square;
                    }
                  }
                  if (is_cand) {
                    cluster_sets[0].emplace_back(*cluster_set);
                  } else {
                    for (int i = 0; i < 2; ++i) {
                      if (is_sim_xcluster[i][0] && is_sim_xcluster[i][1] && is_sim_xcluster[i][2] && is_sim_xcluster[i][3]) {
                        x_search_reject_point[i] += Pow2(kRejXFit);
                        reject_point[i] += Pow2(kTotalRejXFit);
                      }
                    }
                  }
#else // TRACK_FIND_WO_TARGET
                  if (IsXTrackCandidate(cluster_set)) {
                    cluster_sets[0].emplace_back(*cluster_set);
                  } else {
                    for (int i = 0; i < 2; ++i) {
                      if (is_sim_xcluster[i][0] && is_sim_xcluster[i][1] && is_sim_xcluster[i][2] && is_sim_xcluster[i][3]) {
                        x_search_reject_point[i] += Pow2(kRejXFit);
                        reject_point[i] += Pow2(kTotalRejXFit);
                      }
                    }
                  }
#endif // TRACK_FIND_WO_TARGET
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
          if (gtr300y_cluster->IsMerged()) {
            continue;
          }
          auto gtr3ycid = gtr300y_cluster->ClusterId();
          is_sim_ycluster[0][2] = gtr3ycid >= kMockClusterID && gtr3ycid < kMockClusterID * 2;
          is_sim_ycluster[1][2] = gtr3ycid >= kMockClusterID * 2;
          if (gtr300y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
            for (int i = 0; i < 2; ++i) {
              if (!is_ychecked[i][2] && is_sim_ycluster[i][2]) {
                y_reject_point[i] += Pow2(kRej300yADC);
                reject_point[i] += Pow2(kRejYSearch);
                is_ychecked[i][2] = true;
              }
            }
            continue;
          }
          cluster_set->gtr_clusters[2] = gtr300y_cluster;
          cluster_set->global_poss[E16ANA_TrackConstant::kGTR300] = gtr300y_cluster->GlobalPosT(*geometry);
          for (const auto& gtr200y_cluster : gtr200y_cluster_ptrs) {
            if (gtr200y_cluster->IsMerged()) {
              continue;
            }
            auto gtr2ycid = gtr200y_cluster->ClusterId();
            is_sim_ycluster[0][1] = gtr2ycid >= kMockClusterID && gtr2ycid < kMockClusterID * 2;
            is_sim_ycluster[1][1] = gtr2ycid >= kMockClusterID * 2;
            if (gtr200y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
              for (int i = 0; i < 2; ++i) {
                if (!is_ychecked[i][1] && is_sim_ycluster[i][2] && is_sim_ycluster[i][1]) {
                  y_reject_point[i] += Pow2(kRej200yADC);
                  reject_point[i] += Pow2(kRejYSearch);
                  is_ychecked[i][1] = true;
                }
              }
              continue;
            }
            cluster_set->gtr_clusters[1] = gtr200y_cluster;
            cluster_set->global_poss[E16ANA_TrackConstant::kGTR200] = gtr200y_cluster->GlobalPosT(*geometry);
            for (const auto& gtr100y_cluster : gtr100y_cluster_ptrs) {
              if (gtr100y_cluster->IsMerged()) {
                continue;
              }
              auto gtr1ycid = gtr100y_cluster->ClusterId();
              is_sim_ycluster[0][0] = gtr1ycid >= kMockClusterID && gtr1ycid < kMockClusterID * 2;
              is_sim_ycluster[1][0] = gtr1ycid >= kMockClusterID * 2;
              if (gtr100y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
                for (int i = 0; i < 2; ++i) {
                  if (!is_ychecked[i][0] && is_sim_ycluster[i][2] && is_sim_ycluster[i][1] && is_sim_ycluster[i][0]) {
                    y_reject_point[i] += Pow2(kRej100yADC);
                    reject_point[i] += Pow2(kRejYSearch);
                    is_ychecked[i][0] = true;
                  }
                }
                continue;
              }
              cluster_set->gtr_clusters[0] = gtr100y_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100y_cluster->GlobalPosT(*geometry);
#ifdef SIM_DST1_GEOM_CHECK
for (int i = 1; i < 4; ++i) {
  auto& pos = cluster_set->global_poss[i];
  cout << i << " y: " << pos.Y() << endl;
}
#endif // SIM_DST1_GEOM_CHECK
              if (IsYTrackCandidate(cluster_set)) {
                cluster_sets[1].emplace_back(*cluster_set);
              } else {
                for (int i = 0; i < 2; ++i) {
                  if (is_sim_ycluster[i][0] && is_sim_ycluster[i][1] && is_sim_ycluster[i][2]) {
                    reject_point[i] += Pow2(kRejYCand);
                  }
                }
              }
            }
            for (const auto& gtr100yb_cluster : gtr100yb_cluster_ptrs) {
              if (gtr100yb_cluster->IsMerged()) {
                continue;
              }
              auto gtr1ybcid = gtr100yb_cluster->ClusterId();
              is_sim_ycluster[0][0] = gtr1ybcid >= kMockClusterID && gtr1ybcid < kMockClusterID * 2;
              is_sim_ycluster[1][0] = gtr1ybcid >= kMockClusterID * 2;
              if (gtr100yb_cluster->PeakSum() < kGTRPeakSumThresholdY) {
                for (int i = 0; i < 2; ++i) {
                  if (is_sim_ycluster[i][2] && is_sim_ycluster[i][1] && is_sim_ycluster[i][0]) {
                    y_reject_point[i] += Pow2(kRej100yADC);
                    reject_point[i] += Pow2(kRejYSearch);
                  }
                }
                continue;
              }
              cluster_set->gtr_clusters[0] = gtr100yb_cluster;
              cluster_set->global_poss[E16ANA_TrackConstant::kGTR100] = gtr100yb_cluster->GlobalPosT(*geometry);
#ifdef SIM_DST1_GEOM_CHECK
for (int i = 1; i < 4; ++i) {
  auto& pos = cluster_set->global_poss[i];
  cout << i << " y: " << pos.Y() << endl;
}
#endif // SIM_DST1_GEOM_CHECK
              if (IsYTrackCandidate(cluster_set)) {
                cluster_sets[1].emplace_back(*cluster_set);
              } else {
                for (int i = 0; i < 2; ++i) {
                  if (is_sim_ycluster[i][0] && is_sim_ycluster[i][1] && is_sim_ycluster[i][2]) {
                    reject_point[i] += Pow2(kRejYCand);
                  }
                }
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
    bool is_sim_xtrack[2] = {ssdx.ClusterId()     >= kMockClusterID && ssdx.ClusterId()     < kMockClusterID * 2 &&
                             gtrx[0]->ClusterId() >= kMockClusterID && gtrx[0]->ClusterId() < kMockClusterID * 2 &&
                             gtrx[1]->ClusterId() >= kMockClusterID && gtrx[1]->ClusterId() < kMockClusterID * 2 &&
                             gtrx[2]->ClusterId() >= kMockClusterID && gtrx[2]->ClusterId() < kMockClusterID * 2, 
                             ssdx.ClusterId()     >= 2 * kMockClusterID &&
                             gtrx[0]->ClusterId() >= 2 * kMockClusterID &&
                             gtrx[1]->ClusterId() >= 2 * kMockClusterID &&
                             gtrx[2]->ClusterId() >= 2 * kMockClusterID};
    for (const auto& y_cand : cluster_sets[1]) {
      auto& gtry = y_cand.gtr_clusters;
//      IsSameModules();
      bool is_sim_track[2] = {is_sim_xtrack[0] &&
                              gtry[0]->ClusterId() >= kMockClusterID && gtry[0]->ClusterId() < kMockClusterID * 2 &&
                              gtry[1]->ClusterId() >= kMockClusterID && gtry[1]->ClusterId() < kMockClusterID * 2 &&
                              gtry[2]->ClusterId() >= kMockClusterID && gtry[2]->ClusterId() < kMockClusterID * 2,
                              is_sim_xtrack[1] &&
                              gtry[0]->ClusterId() >= 2 * kMockClusterID &&
                              gtry[1]->ClusterId() >= 2 * kMockClusterID &&
                              gtry[2]->ClusterId() >= 2 * kMockClusterID};
//#ifdef MOM_RECONSTRUCT_CHECK
      if (!is_sim_track) {
        continue;
      }
//#endif // MOM_RECONSTRUCT_CHECK
      bool is_same_module = true;
      if (!is_sim_track[0] && !is_sim_track[1]) {
        if ((gtry[0]->IsY() && gtrx[0]->LocalPosT().X() <= 0) || (gtry[0]->IsYb() && gtrx[0]->LocalPosT().X() >= 0)) {
//cout << "is y yb not match" << endl;
          continue;
        }
      }
      for (int i = 0; i < kNumGTRLayers; ++i) {
//        if (x_module_ids[i] != gtry[i]->ModuleId() || fabs(x_timings[i] - gtry[i]->Timing()) > kGTRTimeDiffThreshold[i]) {
        if (x_module_ids[i] != gtry[i]->ModuleId() || fabs(x_timings[i] - gtry[i]->Timing()) > kGTRTimeDiffThreshold[i] || !ExistADCCorrelation(i, x_peak_sums[i], gtry[i]->PeakSum())) { // ozawa v8
//cout << "x y timing not match" << endl;
          is_same_module = false;
          for (int j = 0; j < 2; ++j) {
            if (is_sim_track[j]) {
              if (x_module_ids[i] != gtry[i]->ModuleId()) {
                xy_reject_point[j] += Pow2(kRej100XYModule + i);
              }
              if (fabs(x_timings[i] - gtry[i]->Timing()) > kGTRTimeDiffThreshold[i]) {
                xy_reject_point[j] += Pow2(kRej100XYTime + i);
              }
              if (!ExistADCCorrelation(i, x_peak_sums[i], gtry[i]->PeakSum())) {
                xy_reject_point[j] += Pow2(kRej100XYADC + i);
              }
              reject_point[j] += Pow2(kRejXYMatch);
            }
          }
          break;
        }
      }
      if (!is_same_module) {
        continue;
      }
      for (int i = 0; i < 2; ++i) {
        if (is_sim_track[i]) {
          sim_track_detected[i] = true;
        }
      }
      track_candidates.emplace_back(E16ANA_TrackCandidate(geometry, bfield_map));
      auto& tmp_cand = track_candidates.back();
      tmp_cand.SetTrackID(track_candidates.size() - 1);
      tmp_cand.SetCharge(x_cand.charge);
#ifndef TRACK_FIND_WO_TARGET
      tmp_cand.SetInitX(x_cand.xy);
      tmp_cand.SetInitY(y_cand.xy);
      tmp_cand.SetInitZ(kTargetZ[x_cand.target_id]);
      tmp_cand.SetTargetID(x_cand.target_id);
#else // TRACK_FIND_WO_TARGET
      tmp_cand.SetTargetID(1);
      tmp_cand.SetRadius(x_cand.radius);
      tmp_cand.SetCircleCenter(x_cand.circ_center);
      auto ssd_gpos = x_cand.ssd_cluster->GlobalPos(*geometry);
      auto pre_init_pos = TVector3(ssd_gpos.X(), CalcRoughYPosition(x_cand.ssd_cluster->ModuleId(), y_cand.coefs), ssd_gpos.Z());
      auto init_mom = TVector3(x_cand.mom_axis.X(), CalcRoughYMomentum(x_cand.mom, y_cand.coefs[1]), x_cand.mom_axis.Z());
      auto init_pos = BackInitPos(pre_init_pos, init_mom);
      tmp_cand.SetInitX(init_pos.X());
      tmp_cand.SetInitY(init_pos.Y());
      tmp_cand.SetInitZ(init_pos.Z());
      tmp_cand.SetInitMomX(init_mom.X());
      tmp_cand.SetInitMomY(init_mom.Y());
      tmp_cand.SetInitMomZ(init_mom.Z());
#endif // TRACK_FIND_WO_TARGET
      tmp_cand.SetDefaultSigma();
      tmp_cand.SetXChiSquare(x_cand.chi_square);
      tmp_cand.SetYChiSquare(y_cand.chi_square);
#ifdef TRACK_FIND_WO_TARGET
      for (int i = 0; i < 2; ++i) {
        tmp_cand.SetXDist(i, x_cand.dists[i]);
      }
#endif // TRACK_FIND_WO_TARGET
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
	      int nhit = gtrx[i]->NumCls();
	      for(int j=0;j<nhit;j++){
	        cluster_pairs[1+i].SetCTiming((double)gtrx[i]->CTiming(j));
	        cluster_pairs[1+i].SetCPos((double)gtrx[i]->CPos(j));
	      }
      }
    }
  }
}
#endif // TRACK_EFF_CHECK

void E16ANA_TrackCandidates::Fit() {
  for (auto& cand : track_candidates) {
    cand.Fit(fitter, vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag);
  }
}

void E16ANA_TrackCandidates::SearchHBDAndLGHits() {
  auto& hbd = record->HBD();
  auto& lg  = record->LG();
  for (auto& cand : track_candidates) {
    if (cand.ChiSquare() >= 1.0e10) {
      cand.SetIsSearchAssociatedHits(false);
      continue;
    }
    if (cand.ChiSquare() >= kMaxChi2ForSearchAssociatedHits) {
      cand.SetIsSearchAssociatedHits(false);
      continue;
    }
    cand.SetIsSearchAssociatedHits(true);
    auto& fit_results = cand.LocalFitResults();
    for (int l = E16ANA_TrackConstant::kHBD; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l) {
      if (fit_results[l].set_flag == 0) {
        continue;
      }
      auto& fit_pos = fit_results[l].global_pos;
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
          if (hit->FitFlag() == E16ANA_LGConstant::kFitFailure) {
            continue;
          }
#ifdef TRACK_EFF_CHECK
          if (hit->ChannelId() >= kMockClusterID) {
            if ((hit->GlobalPos(*geometry) - fit_pos).Mag() < kLGProjectionThreshold) {
              cand.ProjectedLGHits().emplace_back(hit);
            }
            continue;
          }
#endif
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
    for (int i = 0; i < E16ANA_TrackConstant::kNumTrackingLayers; ++i) {
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
      auto& cluster_pair = cands[track_index]->ClusterPair(layer_index);
      auto module_id  = cluster_pair.ModuleID();
      auto local_pos  = cluster_pair.LocalPos();
      auto local_posT = cluster_pair.LocalPosT();
      if (layer_index == E16ANA_TrackConstant::kSSD) {
		  #ifdef UseSTS
        pair_fitter->AddHit(track_index, layer_index, geometry->STS(E16ANA_TrackConstant::ModuleID2020To2013(module_id)),
			#else
        pair_fitter->AddHit(track_index, layer_index, geometry->SSD(E16ANA_TrackConstant::ModuleID2020To2013(module_id)),
			#endif
                            local_pos, kSigmas[layer_index]);
      } else {
        pair_fitter->AddHit(track_index, layer_index, geometry->GTR(E16ANA_TrackConstant::ModuleID2020To2013(module_id), layer_index - 1),
                            local_posT, kSigmas[layer_index]);
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
			#ifdef UseSTS
          track_pair->track_minus_pos_refit[layer_index] = geometry->STS(mid[hid])->GetGPos(lpos[hid]);
          track_pair->track_minus_mom_refit[layer_index] = geometry->STS(mid[hid])->GetGMom(lmom[hid]);
		   #else
          track_pair->track_minus_pos_refit[layer_index] = geometry->SSD(mid[hid])->GetGPos(lpos[hid]);
          track_pair->track_minus_mom_refit[layer_index] = geometry->SSD(mid[hid])->GetGMom(lmom[hid]);
			#endif
          track_pair->track_minus_res_refit[layer_index] = lres[hid];
        } else {
			  #ifdef UseSTS
          track_pair->track_plus_pos_refit[layer_index] = geometry->STS(mid[hid])->GetGPos(lpos[hid]);
          track_pair->track_plus_mom_refit[layer_index] = geometry->STS(mid[hid])->GetGMom(lmom[hid]);
			 #else
          track_pair->track_plus_pos_refit[layer_index] = geometry->SSD(mid[hid])->GetGPos(lpos[hid]);
          track_pair->track_plus_mom_refit[layer_index] = geometry->SSD(mid[hid])->GetGMom(lmom[hid]);
		 	#endif
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
  pair_fitter->SetRungeKuttaStepSize(kPairTrackingStepSize);
  pair_fitter->SetMaxSteps(kPairTrackingMaxSteps);
  track_pair->chi_square_refit = pair_fitter->Fit(vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag, kPairMinuitStrategy, kPairMinuitMaxFunctionCalls);
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
#ifndef UseSTS
  SearchTrackCandidates();
#else 
  SearchTrackCandidatesWithSTS();
#endif
E16INFO("number of track candidate: %d", track_candidates.size());
 if ( track_candidates.size() > 5000 ) {
   std::cerr << "Too many track candidates. skip event." << std::endl;
   return;
 }
#ifndef WO_TRACK_FIT
 std::cout << "Fit(); " << std::endl;
  Fit();
  ProjectionTarget();
  ProjectionX0();
  SearchHBDAndLGHits();
  SelectTracks();
  if (kExecutePairFit) {
    AnalyzeTrackPairs();
  }
#endif // WO_TRACK_FIT
  AddTracksToRecord();
  return;
}






void E16ANA_TrackCandidates::PrintParam() {
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
  std::cout << "Rough Fit Chi Square Threshold :" << std::endl;
  std::cout << "  X : " << kRoughFitChiSquareThreshold[0] << ", Y : " << kRoughFitChiSquareThreshold[1] << std::endl;
  std::cout << "X Rough Fit Coefficient Threshold : " 
            << kRoughXFitCoefficientThreshold[0] << ", " << kRoughXFitCoefficientThreshold[1] << kRoughXFitCoefficientThreshold[2] << std::endl;
  std::cout << "Y Rough Fit Coefficient Threshold : " << kRoughYFitCoefficientThreshold[0] << ", " << kRoughYFitCoefficientThreshold[1] << std::endl;
  std::cout << "HBD Projection Threshold : " << kHBDProjectionThreshold << std::endl;
  std::cout << "LG  Projection Threshold : " << kLGProjectionThreshold << std::endl;
  std::cout << "Near Target Threshold : " << kNearTargetThreshold << std::endl;
  std::cout << "E16ANA_StepTrack Step Size [cm] : " << kStepTrackStepSizeCm << std::endl;
  std::cout << "E16ANA_StepTrack Array Size : " << kStepTrackArraySize << std::endl;
}
