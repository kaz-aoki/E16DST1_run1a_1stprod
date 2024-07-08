#ifndef E16ANA_HBDADCwoTrack_h
#define E16ANA_HBDADCwoTrack_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <stdio.h>
#include <iostream>
using namespace std;
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_TrackAnalyzerFromTreeV2.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDDeadChannel.hh"
#include "E16ANA_EIDSingleTrackAnalyzer.hh"

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"
#include "vector"

class E16ANA_HBDADCwoTrack : public E16ANA_EIDSingleTrackAnalyzer {
private :

  struct hitset{
    int mid;
    int cid;
    double adc;
    double t;
    double x;
    double y;
    void Init(){
      mid = -10000;
      cid = -10000;
      adc = -10000.;
      t   = -10000.;
      x   = -10000.;
      y   = -10000.;
    }
    void Set(int mid_, int cid_, double adc_, double t_, double x_, double y_){
      mid = mid_;
      cid = cid_;
      adc = adc_;
      t   = t_;
      x   = x_;
      y   = y_;
    }
  };

public :

  E16ANA_HBDADCwoTrack(TTree *tree=0);
  virtual ~E16ANA_HBDADCwoTrack();
  virtual void MakeHist(int maxevent, char* out_pdf_name, char* out_root_name);
  virtual int ModuleToIndex(int module);
  virtual int IndexToModule(int index);
  virtual int GEMToIndex(int gem);
  virtual int IndexToGEM(int index);
};

#endif

#ifdef E16ANA_HBDADCwoTrack_cxx
E16ANA_HBDADCwoTrack::E16ANA_HBDADCwoTrack(TTree* tree) : E16ANA_EIDSingleTrackAnalyzer(tree)
{
}

E16ANA_HBDADCwoTrack::~E16ANA_HBDADCwoTrack()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

int E16ANA_HBDADCwoTrack::ModuleToIndex(int module)
{
  if( module>=101 && module<=104 ){
    return module - 101;
  }
  else if( module>=106 && module<=109 ){
    return module - 102;
  }
  else{
    return -1;
  }
}
int E16ANA_HBDADCwoTrack::IndexToModule(int index)
{
  if( index>=0 && index<=3 ){
    return index + 101;
  }
  else if( index>=4 && index<=7 ){
    return index + 102;
  }
  else{
    return -1;
  }
}
int E16ANA_HBDADCwoTrack::GEMToIndex(int gem)
{
  if(gem==0){return 3;}
  else if(gem==1){return 2;}
  else if(gem==10){return 1;}
  else if(gem==11){return 0;}
  else{return -1;}
}
int E16ANA_HBDADCwoTrack::IndexToGEM(int index)
{
  if(index==0){return 11;}
  else if(index==1){return 10;}
  else if(index==2){return 1;}
  else if(index==3){return 0;}
  else{return -1;}
}

#endif // #ifdef E16ANA_HBDADCwoTrack_cxx
