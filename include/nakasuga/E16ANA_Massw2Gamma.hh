#ifndef E16ANA_Massw2Gamma_h
#define E16ANA_Massw2Gamma_h

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

class E16ANA_Massw2Gamma : public E16ANA_EIDSingleTrackAnalyzer {
private :

  const double mvtoe = 0.005;

public :

  struct hitset{
    int id;
    int mid;
    int cid;
    double x;
    double y;
    double z;
    double gx;
    double gy;
    double gz;
    float adc;
    float t;
    void init(int _id, int _mid, int _cid, double _x, double _y, double _z, double _gx, double _gy, double _gz, float _adc, float _t){
      id = _id;
      mid = _mid;
      cid = _cid;
      x = _x;
      y = _y;
      z = _z;
      gx = _gx;
      gy = _gy;
      gz = _gz;
      adc = _adc;
      t = _t;
    }
  };

  E16ANA_Massw2Gamma(TTree *tree=0);
  virtual ~E16ANA_Massw2Gamma();
  virtual void     MakeHist(int runoption, int maxevent, char* out_file_name);
  virtual bool     InvalidLGhit(Long64_t entry, int ilg);
  virtual void     SetHit(Long64_t entry, int ilg, hitset &hit);
  virtual bool     InvalidLGPair(E16ANA_GeometryV2& geometry, Long64_t entry, hitset &hit0, hitset &hit1);

};

#endif

#ifdef E16ANA_Massw2Gamma_cxx
E16ANA_Massw2Gamma::E16ANA_Massw2Gamma(TTree* tree) : E16ANA_EIDSingleTrackAnalyzer(tree)
{
}

E16ANA_Massw2Gamma::~E16ANA_Massw2Gamma()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

bool E16ANA_Massw2Gamma::InvalidLGhit(Long64_t entry, int ilg)
{
  if( lg_hit_fflag->at(ilg)>=2 ){return true;}
  else if( lg_hit_adc->at(ilg)<30. ){return true;}
  // else if( lg_hit_mid->at(ilg)!=104 && lg_hit_mid->at(ilg)!=106 ){return true;}
  else{return false;}
}

void E16ANA_Massw2Gamma::SetHit(Long64_t entry, int ilg, hitset &hit)
{
  hit.id = lg_hit_id->at(ilg);
  hit.mid = lg_hit_mid->at(ilg);
  hit.cid = lg_hit_cid->at(ilg);
  hit.x = lg_hit_x->at(ilg);
  hit.y = lg_hit_y->at(ilg);
  hit.z = lg_hit_z->at(ilg);
  hit.gx = lg_hit_gx->at(ilg);
  hit.gy = lg_hit_gy->at(ilg);
  hit.gz = lg_hit_gz->at(ilg);
  hit.adc = lg_hit_adc->at(ilg);
  hit.t = lg_hit_t->at(ilg);
}

bool E16ANA_Massw2Gamma::InvalidLGPair(E16ANA_GeometryV2& geometry, Long64_t entry, hitset &hit0, hitset &hit1)
{
  if( fabs( hit0.t - hit1.t ) > 4. ){return true;}
  else if( hit0.mid==hit1.mid && IsNeighborBlock(geometry, hit0.cid, hit1.cid) ){return true;}
  // else if( hit0.mid!=hit1.mid ){return true;}
  else{return false;}
}

#endif // #ifdef E16ANA_Massw2Gamma_cxx
