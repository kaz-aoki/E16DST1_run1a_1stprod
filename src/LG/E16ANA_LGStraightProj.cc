#include "E16ANA_LGStraightProj.hh"
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

E16ANA_LGStraightProj::E16ANA_LGStraightProj(E16ANA_GeometryV2* in_geometry, E16ANA_MagneticFieldMap3D* in_bfield_map, E16ANA_MultiTrack* in_fitter) : E16ANA_LGProjection(geometry, bfield_map, fitter){

  ClearInitInfo();
  ClearCrossInfo();

  // geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  // // E16ANA_GeometryV2::SetGlobalPointer(geometry);

}
E16ANA_LGStraightProj::~E16ANA_LGStraightProj(){
  // delete geometry;
}

void E16ANA_LGStraightProj::ClearInitInfo(){
  initpos.SetXYZ(-10000.,-10000.,-10000.);
  initdir.SetXYZ(-10000.,-10000.,-10000.);
}

void E16ANA_LGStraightProj::ClearCrossInfo(){
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
  gpos.SetXYZ(-10000.,-10000.,-10000.);
}

void E16ANA_LGStraightProj::SetInitInfo(TVector3& _initpos, TVector3& _initdir){
  initpos = _initpos;
  initdir = _initdir;
  double norm = 1./initdir.Mag();
  initdir = initdir*norm;
  ClearCrossInfo();
}

bool E16ANA_LGStraightProj::CalcCrossModule(){

  TVector3 p0 = initpos;
  TVector3 p1 = initpos + initdir*2000;

  double tdist = 10000.;
  for(int i=0;i<9;i++){
    int tmid = i+101;
    auto mid2013 = E16ANA_TrackConstant::ModuleID2020To2013_27(tmid);//HBD, LG
    auto lg_geom = geometry->LGVD(mid2013);
    TVector3 tlcross;
    bool tis_crossed = lg_geom->IsCrossed(p0,p1,tlcross);
    if( tis_crossed && tlcross.Mag()<tdist ){
      module = tmid;
      module2013 = mid2013;
      is_crossed = true;
      lcross0 = tlcross;
      tdist = tlcross.Mag();
    }
  }
  if(module==105){
    is_crossed = false;
  }
  // std::cout<<module<<" "<<is_crossed<<" "<<lcross0.Mag()<<std::endl;

  return is_crossed;
}

// bool E16ANA_LGStraightProj::CalcCrossPlane(){

//   TVector3 p0 = initpos;
//   TVector3 p1 = initpos + initdir*2000;

//   for(int i=0;i<3;i++){
//     int j = 2-i;
//     TVector3 v0;
//     bool tis_crossed = geometry->LG(module2013,planeblock[j])->IsCrossed(p0,p1,v0);
//     TVector3 v1 = geometry->LG(module2013, planeblock[j])->GetGPos(v0);
//     TVector3 v2 = geometry->LGVD(module2013)->GetLPos(v1);
//     if( fabs(v2.Y()) > yregion_in[j] && fabs(v2.Y()) < yregion_out[j] ){
//       if( fabs(v2.X()) < xregion[j] ){
// 	plane = j;
// 	lcross1 = v2;
// 	if( v2.Y()>0 ){
// 	  block_y = j+3;
// 	}
// 	else{
// 	  block_y = 2-j;
// 	}
// 	break;
//       }
//       else{
// 	is_crossed = false;
// 	return is_crossed;
//       }
//       break;
//     }
//     if( i==2 ){
//       is_crossed = false;
//       return is_crossed;
//     }
//   }

//   return is_crossed;

// }
bool E16ANA_LGStraightProj::CalcCrossPlane(){

  TVector3 p0 = initpos;
  TVector3 p1 = initpos + initdir*2000;

  for(int i=0;i<3;i++){
    int j = 2-i;
    TVector3 v0;
    bool tis_crossed = geometry->LG(module2013,planeblock[j])->IsCrossed(p0,p1,v0);
    TVector3 v1 = geometry->LG(module2013, planeblock[j])->GetGPos(v0);
    TVector3 v2 = geometry->LGVD(module2013)->GetLPos(v1);
    int out_block_y;
    if( IsInAcceptance(j,v2,out_block_y) ){
      plane = j;
      lcross1 = v2;
      block_y = out_block_y;
      break;
    }
    if( i==2 ){
      is_crossed = false;
      return is_crossed;
    }
  }

  return is_crossed;

}

// bool E16ANA_LGStraightProj::CalcCrossBlock(){

//   double lxtmp = 10000.;
//   if( block_y>=0 && block_y<=5 ){
//     int xmax = 6;
//     if( block_y==2 || block_y==3 ){
//       xmax = 7;
//     }
//     for(int i=0;i<xmax;i++){
//       int blocktmp = block_y*10+i;
//       TVector3 v0 = geometry->LGVD(module2013)->GetGPos(lcross1);
//       TVector3 v1 = geometry->LG(module2013, blocktmp)->GetLPos(v0);
//       if( fabs(v1.X()) < fabs(lxtmp) ){
// 	lxtmp = v1.X();
// 	lcross2 = v1;
// 	block_x = i;
// 	block = blocktmp;
//       }
//     }
//   }
//   else{
//     is_crossed = false;
//   }

//   return is_crossed;

// }
bool E16ANA_LGStraightProj::CalcCrossBlock(){

  int out_block_x = -10000;
  TVector3 out_v(-10000.,-10000.,-10000.);
  LposToBlock(module2013, block_y, lcross1, out_block_x, out_v);
  lcross2 = out_v;
  block_x = out_block_x;
  block = block_y*10+block_x;

  return is_crossed;

}

// void E16ANA_LGStraightProj::CalcCrossAngle(){

//   TVector3 v0 = geometry->LG(module2013, block)->GetDetectorCenter();
//   TVector3 v1 = geometry->LG(module2013, block)->GetLPos(v0+initdir);
//   angle_x = atan( v1.X()/v1.Z() );
//   if(block_y>=3){
//     angle_y = atan( v1.Y()/v1.Z() ) - pmtangle[plane];
//   }
//   else{
//     angle_y = -atan( v1.Y()/v1.Z() ) - pmtangle[plane];
//   }

// }
void E16ANA_LGStraightProj::CalcCrossAngle(){

  TVector3 v0 = geometry->LG(module2013, block)->GetDetectorCenter();
  TVector3 v1 = geometry->LG(module2013, block)->GetLPos(v0+initdir);
  double out_angle_x, out_angle_y;
  LmomToAngle(block_y, plane, v1, out_angle_x, out_angle_y);
  angle_x = out_angle_x;
  angle_y = out_angle_y;

}

TVector2 RYPlaneCrossPoint(TVector2 a, TVector2 b, TVector2 p){

  double s = p.Y()/p.X();
  double q = (b.Y()-a.Y())/(b.X()-a.X());
  double cr_r = (a.Y()-q*a.X())/(s-q);
  TVector2 cr(cr_r,s*cr_r);
  return cr;
}

// bool E16ANA_LGStraightProj::CalcCrossBlockForCalib(){

//   // local-x info and local-y info are needed for calibration of position dependence.

//   // local-y: calc distance between a projection-point and a pmt-plane
//   // consider grobal R-Y plane
//   // including approximation as target pos ~ O
//   TVector2 pos_pmt( pos_pmt_r[block_y], pos_pmt_y[block_y] );
//   TVector2 pos_cut( pos_cut_r[block_y], pos_cut_y[block_y] );
//   TVector2 pos_proj( plane_r[block_y], lcross1.Y() );
//   TVector2 cs = RYPlaneCrossPoint(pos_pmt,pos_cut,pos_proj);
//   TVector2 vec_y = cs - pos_pmt;
//   double lcross3_y = vec_y.Mod();

//   calib_is_valid = true;
//   if( lcross3_y<10. ){
//     calib_is_valid = false;
//   }

//   // local-x: calc distance between a track and a CENTER OF SOLID BLOCK.
//   // consider local X-Z plane
//   double lcross3_x = lcross2.X() + 135./2.*tan(angle_x);
//   lcross3_x = lcross3_x*cos(angle_x);
//   lcross3_x = (-angle_x/fabs(angle_x))*lcross3_x;
//   lcross3_x = lcross3_x/cos(angle_x);

//   lcross3.SetXYZ(lcross3_x, lcross3_y, 0.);

//   return calib_is_valid;
// }
bool E16ANA_LGStraightProj::CalcCrossBlockForCalib(){
  TVector3 out_v(-10000.,-10000.,-10000.);
  calib_is_valid = LposToCalibpos(block_y, lcross1, angle_x, lcross2, out_v);
  lcross3 = out_v;
  return calib_is_valid;
}

bool E16ANA_LGStraightProj::CalcCrossInfo(){
  if( !CalcCrossModule() ){
    // std::cout<<"not crossed module"<<std::endl;
    return false;
  }
  if( !CalcCrossPlane() ){
    // std::cout<<"not crossed plane"<<std::endl;
    return false;
  }
  if( !CalcCrossBlock() ){
    // std::cout<<"not crossed block"<<std::endl;
    return false;
  }
  CalcCrossAngle();
  if( !CalcCrossBlockForCalib() ){
    // std::cout<<"not crossed calib"<<std::endl;
    return false;
  }
  gpos = geometry->LG(module2013, block)->GetDetectorCenter();

  return true;
}

// double E16ANA_LGStraightProj::CalibFunction(){

//   double by = lcross3.Y();
//   TF1 *fc = new TF1("fc","[0]+ ( -39.56E-4*x*x + 41.71E-6*fabs(x)*x*x + 1E-8*x*x*x*x )*[1]",-65.,65.);
//   fc->FixParameter(0,1.857 -1.143*by*0.01);
//   fc->FixParameter(1,0.2755-0.334*by*0.01);

//   if( !calib_is_valid ){
//     delete fc;
//     return -0.0001;
//   }
//   else if( lcross3.Y()<75. ){
//     double ret = fc->Eval(lcross3.X());
//     delete fc;
//     return ret;
//   }
//   else{
//     delete fc;
//     return 1.;
//   }
// }

double E16ANA_LGStraightProj::CalibFunction(){
  return CalcCalibFunction(calib_is_valid, lcross3.X(), lcross3.Y() );
}
double E16ANA_LGStraightProj::CalibParameter(){
  return 1./CalibFunction();
}
