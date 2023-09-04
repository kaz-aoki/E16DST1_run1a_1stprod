#ifndef E16ANA_LGStraightProj_h
#define E16ANA_LGStraightProj_h

#include "E16ANA_GeometryV2.hh"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TF1.h>
#include <TVector3.h>

#include <stdio.h>
#include <iostream>

class E16ANA_LGStraightProj{
private :

  //******* constant

  const double PI = acos(-1.);
  // plane a, b, c
  int planeblock[3] = {20, 10, 0};
  double xregion[3] = {433.,372.,372.};
  double yregion_in[3] = {6.5,  137.7,243.2};
  double yregion_out[3] = {160.7,281.0,388.7};
  double pmtangle[3]={4.9*PI/180., 9.6*PI/180., 14.0*PI/180.};
  // (strict) PMT position @ RY plane
  double pos_pmt_r[6] = {1417.4, 1587.0, 1748.2, 1748.2, 1587.0, 1417.4};
  double pos_pmt_y[6] = {-363.6, -278.6, -159.9,  159.9,  278.6,  363.6};
  double pos_cut_r[6] = {1451.7, 1610.7, 1761.4, 1761.4, 1610.7, 1451.7};
  double pos_cut_y[6] = {-245.8, -138.6,   -6.5,    6.5,  138.6,  245.8};
  double plane_r[6]   = {1436.4, 1600.7, 1756.8, 1756.8, 1600.7, 1436.4};


  //******* result

  //init info
  TVector3 initpos;
  TVector3 initdir;

  //cross info
  int module;
  int module2013;
  bool is_crossed;
  TVector3 lcross0;//LGVD local @LGVD plane
  TVector3 lcross1;//LGVD local @each LG plane (a,b,c)
  TVector3 lcross2;//LG local defined by E16ANA_Geometry
  TVector3 lcross3;//(LG local) for calib
  int plane;//0: a, 1: b, 2: c
  int block_x;
  int block_y;
  int block;
  double angle_x;
  double angle_y;
  bool calib_is_valid;
  TVector3 gpos;

  E16ANA_GeometryV2* geometry;


public :
  E16ANA_LGStraightProj();
  ~E16ANA_LGStraightProj();

  void ClearInitInfo();
  void ClearCrossInfo();
  void SetInitInfo(TVector3& _initpos, TVector3& _initdir);
  void SetCrossInfo();
  bool CalcCrossModule();
  bool CalcCrossPlane();
  bool CalcCrossBlock();
  void CalcCrossAngle();
  bool CalcCrossBlockForCalib();
  bool CalcCrossInfo();
  double CalibFunction();
  double CalibParameter();
  int Module(){return module;}
  int Module2013(){return module2013;}
  bool Is_crossed(){return is_crossed;}
  TVector3 LCross0(){return lcross0;}
  double LCross0_x(){return lcross0.X();}
  double LCross0_y(){return lcross0.Y();}
  double LCross0_z(){return lcross0.Z();}
  TVector3 LCross1(){return lcross1;}
  double LCross1_x(){return lcross1.X();}
  double LCross1_y(){return lcross1.Y();}
  double LCross1_z(){return lcross1.Z();}
  TVector3 LCross2(){return lcross2;}
  double LCross2_x(){return lcross2.X();}
  double LCross2_y(){return lcross2.Y();}
  double LCross2_z(){return lcross2.Z();}
  TVector3 LCross3(){return lcross3;}
  double LCross3_x(){return lcross3.X();}
  double LCross3_y(){return lcross3.Y();}
  double LCross3_z(){return lcross3.Z();}
  int Plane(){return plane;};
  int Block_x(){return block_x;};
  int Block_y(){return block_y;};
  int Block(){return block;};
  double Angle_x(){return angle_x;}
  double Angle_y(){return angle_y;}
  bool Calib_is_valid(){return calib_is_valid;}
  TVector3 GPos(){return gpos;}
  double GPos_x(){return gpos.X();}
  double GPos_y(){return gpos.Y();}
  double GPos_z(){return gpos.Z();}

};
#endif
