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

  // ClearInitInfo();
  // ClearCrossInfo();

  // geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  // // E16ANA_GeometryV2::SetGlobalPointer(geometry);

}
E16ANA_LGProjection::~E16ANA_LGProjection(){
  // delete geometry;
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

// bool E16ANA_LGProjection::CalcCrossBlock(){

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

// TVector2 RYPlaneCrossPoint(TVector2 a, TVector2 b, TVector2 p){

//   double s = p.Y()/p.X();
//   double q = (b.Y()-a.Y())/(b.X()-a.X());
//   double cr_r = (a.Y()-q*a.X())/(s-q);
//   TVector2 cr(cr_r,s*cr_r);
//   return cr;
// }

// bool E16ANA_LGProjection::CalcCrossBlockForCalib(){

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

// double E16ANA_LGProjection::CalibFunction(){

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

// double E16ANA_LGProjection::CalibParameter(){

//   return 1./CalibFunction();

// }
