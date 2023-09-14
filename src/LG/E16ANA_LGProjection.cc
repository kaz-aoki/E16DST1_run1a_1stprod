#include "E16ANA_LGProjection.hh"
#include "E16ANA_LGStraightProj.hh"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_TrackAnalyzerFromTreeV2.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include <stdio.h>
#include <iostream>
#include <fstream>

E16ANA_LGProjection::E16ANA_LGProjection(){

  ClearInitInfo();
  ClearCrossInfo();

  // geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  // E16ANA_GeometryV2::SetGlobalPointer(geometry);

  geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
  bfield_map->Initialize_binary();
  E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);

  fitter = new E16ANA_MultiTrack(bfield_map, geometry, 1);
  fitter->SetRungeKuttaStepSize(kStepSize);
  fitter->SetMaxSteps(kMaxSteps);

}
E16ANA_LGProjection::~E16ANA_LGProjection(){
  delete geometry;
  delete bfield_map;
  delete fitter;
}

void E16ANA_LGProjection::ClearInitInfo(){
  initvtx.SetXYZ(-10000.,-10000.,-10000.);
  initmom.SetXYZ(-10000.,-10000.,-10000.);
  initcharge = -10000.;
}

void E16ANA_LGProjection::ClearCrossInfo(){
  module = -10000;
  module2013 = -10000;
  is_crossed = false;
  lcross0.SetXYZ(-10000.,-10000.,-10000.);
  lcross1.SetXYZ(-10000.,-10000.,-10000.);
  lcross2.SetXYZ(-10000.,-10000.,-10000.);
  lcross3.SetXYZ(-10000.,-10000.,-10000.);
  plane = -10000;
  block_x = -10000;
  block_y = -10000;
  block = -10000;
  angle_x = -10000.;
  angle_y = -10000.;
  gcross1.SetXYZ(-10000.,-10000.,-10000.);
  lmom1.SetXYZ(-10000.,-10000.,-10000.);
  gmom1.SetXYZ(-10000.,-10000.,-10000.);
}

void E16ANA_LGProjection::SetInitInfo(TVector3& _initvtx, TVector3& _initmom, double _initcharge){
  initvtx = _initvtx;
  initmom = _initmom;
  initcharge = _initcharge;
  ClearCrossInfo();
}

void E16ANA_LGProjection::CalcCrossPos(){

  int min_n_steps = kMaxSteps + 1;
  for (int m = 101; m < 101 + 9; ++m) {
    if (m == 105) {
      continue;
    }
    for (int i=0;i<3;i++) {
      int j = 2-i;
      auto mid2013 = E16ANA_TrackConstant::ModuleID2020To2013_27(m);
      auto tmp_geom = geometry->LG(mid2013, E16ANA_LGStraightProj::planeblock[j]);
      fitter->Clear();
      TVector3 O(0., 0., 0.);
      fitter->AddHit(0, 0, tmp_geom, O, O);
      fitter->RungeKuttaTracking(0, initvtx, initmom, initcharge);
      std::vector<int> mids;
      std::vector<TVector3> lposs;
      std::vector<TVector3> lmoms;
      fitter->GetFitLPos(0, 0, mids, lposs);
      fitter->GetFitLMom(0, 0, mids, lmoms);
      auto tmp_gpos = tmp_geom->GetGPos(lposs[0]);
      auto tmp_lpos = geometry->LGVD(mid2013)->GetLPos(tmp_gpos);//only X&Y
      auto tmp_gmom = tmp_geom->GetGMom(lmoms[0]);
      int out_block_y;
      if( !E16ANA_LGStraightProj::IsInAcceptance(j, tmp_lpos, out_block_y) ){
	continue;
      }
      auto n_steps = fitter->GetTrackSteps( 0 ).size();
      if (n_steps < min_n_steps) {
	min_n_steps = n_steps;
	module      = m;
	module2013  = mid2013;
	is_crossed  = true;
	plane       = j;
	block_y     = out_block_y;
	lcross1     = tmp_lpos;
	gcross1     = tmp_gpos;
	lmom1       = lmoms[0];
	gmom1       = tmp_gmom;
      }
    }
  }

}

#ifdef TMPXXX
void ProjectionHBDAndLG(E16ANA_GeometryV2* geometry, E16ANA_MultiTrack* pair_fitter, const TVector3& vertex, const TVector3& mom, double charge, int mid[], TVector3 out_lposs[], TVector3 out_gposs[], TVector3 out_lmoms[], TVector3 out_gmoms[]) {
  const int n_layers = E16ANA_TrackConstant::kNumDetectorLayers - E16ANA_TrackConstant::kHBD;
  const int tid = 0;
  const TVector3 lpos(0., 0., 0.);
  const TVector3 lsigma(0., 0., 0.);
  const int lid = 0; // only 1 layer in 1 RK
  const int hid = 0; // only 1 hit in 1 RK
  const int max_steps = 2000;
  const int tmp_lg_block_id[3] = {0, 10, 20};
  const TVector3 error_vector = {-10000., -10000., -10000.};

  std::vector<int> mids;
  std::vector<TVector3> lposs;
  std::vector<TVector3> lmoms;
  for (int l = 0; l < n_layers; ++l) {
    if (mid[l] < 0) {
      out_lposs[l] = error_vector;
      out_gposs[l] = error_vector;
      out_lmoms[l] = error_vector;
      out_gmoms[l] = error_vector;
      continue;
    }
    auto mid2013 = E16ANA_TrackConstant::ModuleID2020To2013_27(mid[l]);
    pair_fitter->Clear();
    if (l == 0) { // HBD
      auto tmp_geom = geometry->HBD(mid2013);
      pair_fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
    } else {
      auto tmp_geom = geometry->LG(mid2013, tmp_lg_block_id[l - 1]);
      pair_fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
    }
    pair_fitter->SetMaxSteps(max_steps);
    pair_fitter->RungeKuttaTracking(tid, vertex, mom, charge);
    pair_fitter->GetFitLPos(tid, lid, mids, lposs);
    pair_fitter->GetFitLMom(tid, lid, mids, lmoms);
    out_lmoms[l] = lmoms[hid];
    if (l == 0) {
      out_lposs[l] = lposs[hid];
      out_gposs[l] = geometry->HBD(mid2013)->GetGPos(lposs[hid]);
      out_gmoms[l] = geometry->HBD(mid2013)->GetGMom(lmoms[hid]);
    } else {
      out_gposs[l] = geometry->LG(mid2013, tmp_lg_block_id[l - 1])->GetGPos(lposs[hid]);
      out_lposs[l] = geometry->LGVD(mid2013)->GetLPos(out_gposs[l]);
      out_gmoms[l] = geometry->LG(mid2013, tmp_lg_block_id[l - 1])->GetGMom(lmoms[hid]);
    }
  }
  return;
}
int E16ANA_EIDSingleTrackAnalyzer::CalcAngleOnLGPlane(Long64_t entry, Int_t itrack, E16ANA_GeometryV2* geometry, E16ANA_MultiTrack* pair_fitter, double hbdmid, double lgmid, int ytype, double& lg_angle_lx, double& lg_angle_ly, double& lg_position_block_lx, double& lg_position_block_ly, TVector3& vertex, TVector3& mom)
{
  double charge=rk_charge->at(itrack);
  int mid[4]={hbdmid,lgmid,lgmid,lgmid};
  TVector3 out_lposs[4];
  TVector3 out_gposs[4];
  TVector3 out_lmoms[4];
  TVector3 out_gmoms[4];
  const double PI = acos(-1.);
  double pmtangle[4]={0.,14.0*PI/180.,9.6*PI/180.,4.9*PI/180.};//0,c,b,a
  double ycenter[4]={0.,(243.2+388.7)/2.,(137.7+281.0)/2.,(6.5+160.7)/2.};//0,c,b,a

  ProjectionHBDAndLG(geometry, pair_fitter, vertex, mom,charge,mid,out_lposs,out_gposs,out_lmoms,out_gmoms);

  if(ytype==0||ytype==5){
    lg_angle_lx = atan(out_lmoms[1].X()/out_lmoms[1].Z());
    lg_position_block_lx = ((int)out_lposs[1].X()+124*10)%124-62;
    if(ytype==5){
      lg_angle_ly = atan(out_lmoms[1].Y()/out_lmoms[1].Z())-pmtangle[1];
      lg_position_block_ly = -(out_lposs[1].Y()-ycenter[1]);
    }
    else{
      lg_angle_ly = -(atan(out_lmoms[1].Y()/out_lmoms[1].Z())+pmtangle[1]);
      lg_position_block_ly = out_lposs[1].Y()+ycenter[1];
    }
    return ytype;
  }
  else if(ytype==1||ytype==4){
    lg_angle_lx = tan(out_lmoms[2].X()/out_lmoms[2].Z());
    lg_position_block_lx = ((int)out_lposs[2].X()+124*10)%124-62;
    if(ytype==4){
      lg_angle_ly = atan(out_lmoms[2].Y()/out_lmoms[2].Z())-pmtangle[2];
      lg_position_block_ly = -(out_lposs[2].Y()-ycenter[2]);
    }
    else{
      lg_angle_ly = -(atan(out_lmoms[2].Y()/out_lmoms[2].Z())+pmtangle[2]);
      lg_position_block_ly = out_lposs[2].Y()+ycenter[2];
    }
    return ytype;
  }
  else if(ytype==2||ytype==3){
    lg_angle_lx = tan(out_lmoms[3].X()/out_lmoms[3].Z());
    lg_position_block_lx = ((int)out_lposs[3].X()+124*10+62)%124-62;
    if(ytype==3){
      lg_angle_ly = atan(out_lmoms[3].Y()/out_lmoms[3].Z())-pmtangle[3];
      lg_position_block_ly = -(out_lposs[3].Y()-ycenter[3]);
    }
    else{
      lg_angle_ly = -(atan(out_lmoms[3].Y()/out_lmoms[3].Z())+pmtangle[3]);
      lg_position_block_ly = out_lposs[3].Y()+ycenter[3];
    }
    return ytype;
  }
  else{
    return -1;
  }
}
#endif
