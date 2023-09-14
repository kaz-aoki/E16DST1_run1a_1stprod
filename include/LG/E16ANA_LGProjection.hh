#ifndef E16ANA_LGProjection_h
#define E16ANA_LGProjection_h

#include "E16ANA_GeometryV2.hh"
#include "E16ANA_TrackAnalyzerFromTreeV2.hh"
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

class E16ANA_LGProjection{
private :

  //constant
  double kStepSize    = 5.;
  int    kMaxSteps    = 1000;

  //init info
  TVector3 initvtx;
  TVector3 initmom;
  double initcharge;

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
  TVector3 gcross1;
  TVector3 lmom1;
  TVector3 gmom1;

  E16ANA_GeometryV2* geometry;
  E16ANA_MagneticFieldMap3D* bfield_map;
  E16ANA_MultiTrack* fitter;

public :
  E16ANA_LGProjection();
  ~E16ANA_LGProjection();

  void ClearInitInfo();
  void ClearCrossInfo();
  void SetInitInfo(TVector3& _initvtx, TVector3& _initmom, double _initcharge);
  void CalcCrossPos();
  // void CalcCrossBlock();
  // void CalcCrossAngle();
  // bool CalcCrossBlockForCalib();
  // bool CalcCrossInfo();
  // double CalibFunction();
  // double CalibParameter();
  // int Module(){return module;}
  // int Module2013(){return module2013;}
  // bool Is_crossed(){return is_crossed;}
  // TVector3 LCross0(){return lcross0;}
  // double LCross0_x(){return lcross0.X();}
  // double LCross0_y(){return lcross0.Y();}
  // double LCross0_z(){return lcross0.Z();}
  // TVector3 LCross1(){return lcross1;}
  // double LCross1_x(){return lcross1.X();}
  // double LCross1_y(){return lcross1.Y();}
  // double LCross1_z(){return lcross1.Z();}
  // TVector3 LCross2(){return lcross2;}
  // double LCross2_x(){return lcross2.X();}
  // double LCross2_y(){return lcross2.Y();}
  // double LCross2_z(){return lcross2.Z();}
  // TVector3 LCross3(){return lcross3;}
  // double LCross3_x(){return lcross3.X();}
  // double LCross3_y(){return lcross3.Y();}
  // double LCross3_z(){return lcross3.Z();}
  // int Plane(){return plane;};
  // int Block_x(){return block_x;};
  // int Block_y(){return block_y;};
  // int Block(){return block;};
  // double Angle_x(){return angle_x;}
  // double Angle_y(){return angle_y;}
  // bool Calib_is_valid(){return calib_is_valid;}
  // TVector3 GCross1(){return gcross1;}
  // double GCross1_x(){return gcross1.X();}
  // double GCross1_y(){return gcross1.Y();}
  // double GCross1_z(){return gcross2.Z();}

};
#endif
