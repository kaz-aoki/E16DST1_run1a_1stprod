#include "E16ANA_LGProjection.hh"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_TrackAnalyzerFromTreeV2.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include <TH1.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TVector3.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

E16ANA_LGProjection::E16ANA_LGProjection(){

  // geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  // // E16ANA_GeometryV2::SetGlobalPointer(geometry);

  geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
  bfield_map->Initialize_binary();
  E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);

  fitter = new E16ANA_MultiTrack(bfield_map, geometry, 1);
  fitter->SetRungeKuttaStepSize(kStepSize);
  fitter->SetMaxSteps(kMaxSteps);

  ClearInitInfo();
  ClearCrossInfo();

}
E16ANA_LGProjection::~E16ANA_LGProjection(){
  delete geometry;
  delete bfield_map;
  delete fitter;
}

bool E16ANA_LGProjection::IsInAcceptance(int j, TVector3& v, int& out_block_y){
  if( fabs(v.Y()) > yregion_in[j] && fabs(v.Y()) < yregion_out[j] ){
    if( fabs(v.X()) < xregion[j] ){
      if( v.Y()>0 ){
	out_block_y = j+3;
      }
      else{
	out_block_y = 2-j;
      }
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}

void E16ANA_LGProjection::LposToBlock(int in_module2013, int in_block_y, TVector3& in_v, int& out_block_x, TVector3& out_v){

  double lxtmp = 10000.;
  if( in_block_y>=0 && in_block_y<=5 ){
    int xmax = 6;
    if( in_block_y==2 || in_block_y==3 ){
      xmax = 7;
    }
    for(int i=0;i<xmax;i++){
      int blocktmp = in_block_y*10+i;
      TVector3 v0 = geometry->LGVD(in_module2013)->GetGPos(in_v);
      TVector3 v1 = geometry->LG(in_module2013, blocktmp)->GetLPos(v0);
      if( fabs(v1.X()) < fabs(lxtmp) ){
	lxtmp = v1.X();
	out_v = v1;
	out_block_x = i;
      }
    }
  }

}

void E16ANA_LGProjection::LmomToAngle(int in_block_y, int in_plane, TVector3& in_v, double& out_angle_x, double& out_angle_y){

  out_angle_x = atan( in_v.X() / in_v.Z() );
  if(in_block_y>=3){
    out_angle_y = atan( in_v.Y() / in_v.Z() ) - pmtangle[in_plane];
  }
  else{
    out_angle_y = -atan( in_v.Y() / in_v.Z() ) - pmtangle[in_plane];
  }

}

TVector2 E16ANA_LGProjection::RYPlaneCrossPoint(TVector2& a, TVector2& b, TVector2& p){

  double s = p.Y()/p.X();
  double q = (b.Y()-a.Y())/(b.X()-a.X());
  double cr_r = (a.Y()-q*a.X())/(s-q);
  TVector2 cr(cr_r,s*cr_r);
  return cr;
}

bool E16ANA_LGProjection::LposToCalibpos(int in_block_y, TVector3& in_v1, double in_angle_x, TVector3& in_v2, TVector3& out_v){

  // local-x info and local-y info are needed for calibration of position dependence.

  // local-y: calc distance between a projection-point and a pmt-plane
  // consider grobal R-Y plane
  // including approximation as target pos ~ O
  TVector2 pos_pmt( pos_pmt_r[in_block_y], pos_pmt_y[in_block_y] );
  TVector2 pos_cut( pos_cut_r[in_block_y], pos_cut_y[in_block_y] );
  TVector2 pos_proj( plane_r[in_block_y], in_v1.Y() );
  TVector2 cs = RYPlaneCrossPoint(pos_pmt,pos_cut,pos_proj);
  TVector2 vec_y = cs - pos_pmt;
  double lcross3_y = vec_y.Mod();

  bool tmp_calib_is_valid = true;
  if( lcross3_y<10. ){
    tmp_calib_is_valid = false;
  }

  // local-x: calc distance between a track and a CENTER OF SOLID BLOCK.
  // consider local X-Z plane
  double lcross3_x = in_v2.X() + 135./2.*tan(in_angle_x);
  lcross3_x = lcross3_x*cos(in_angle_x);
  lcross3_x = (-in_angle_x/fabs(in_angle_x))*lcross3_x;
  lcross3_x = lcross3_x/cos(in_angle_x);

  out_v.SetXYZ(lcross3_x, lcross3_y, 0.);

  return tmp_calib_is_valid;
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
      auto tmp_geom = geometry->LG(mid2013, planeblock[j]);
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
      if( !IsInAcceptance(j, tmp_lpos, out_block_y) ){
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

  int out_block_x = -10000;
  TVector3 out_v(-10000.,-10000.,-10000.);
  LposToBlock(module2013, block_y, lcross1, out_block_x, out_v);
  lcross2 = out_v;
  block_x = out_block_x;
  block = block_y*10+block_x;

}

void E16ANA_LGProjection::CalcCrossAngle(){

  double out_angle_x, out_angle_y;
  LmomToAngle(block_y, plane, lmom1, out_angle_x, out_angle_y);
  angle_x = out_angle_x;
  angle_y = out_angle_y;

}

void E16ANA_LGProjection::CalcCrossBlockForCalib(){

  TVector3 out_v(-10000.,-10000.,-10000.);
  calib_is_valid = LposToCalibpos(block_y, lcross1, angle_x, lcross2, out_v);
  lcross3 = out_v;

}

bool E16ANA_LGProjection::CalcCrossInfo(){
  CalcCrossPos();
  if( !is_crossed ){
    return false;
  }
  CalcCrossAngle();
  CalcCrossBlockForCalib();
  if( !calib_is_valid ){
    return false;
  }
  return true;
}

double E16ANA_LGProjection::CalcCalibFunction(bool in_calib_is_valid, double in_x, double in_y){

  TF1 *fc = new TF1("fc","[0]+ ( -39.56E-4*x*x + 41.71E-6*fabs(x)*x*x + 1E-8*x*x*x*x )*[1]",-65.,65.);
  fc->FixParameter(0,1.857 -1.143*in_y*0.01);
  fc->FixParameter(1,0.2755-0.334*in_y*0.01);

  if( !in_calib_is_valid ){
    delete fc;
    return -0.0001;
  }
  else if( in_y<75. ){
    double ret = fc->Eval( in_x );
    delete fc;
    return ret;
  }
  else{
    delete fc;
    return 1.;
  }
}

double E16ANA_LGProjection::CalibFunction(){
  return CalcCalibFunction(calib_is_valid, lcross3.X(), lcross3.Y() );
}
double E16ANA_LGProjection::CalibParameter(){
  return 1./CalibFunction();
}
