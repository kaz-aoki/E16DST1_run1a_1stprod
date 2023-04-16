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
#include "E16ANA_TrackAnalyzerFromTree.hh"
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

public :

  E16ANA_Massw2Gamma(TTree *tree=0);
  virtual ~E16ANA_Massw2Gamma();
  virtual void     MakeHist(int runoption, int maxevent, char* out_file_name);
  virtual bool     InvalidLGhit(Long64_t entry, int ilg);
  // virtual bool     InvalidLGPair(Long64_t entry, int ilg1, int ilg2);

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
  else{return false;}
}

// bool E16ANA_Massw2Gamma::InvalidLGPair(Long64_t entry, int ilg1, int ilg2)
// {
//   if( fabs( lg_hit_t->at(ilg1) - lg_hit_t->at(ilg2) ) > 4. ){return true;}
//   else if( lg_hit_mid->at(ilg1)==lg_hit_mid->at(ilg2) && IsNeighborBlock(lg_hit_cid->at(ilg1),lg_hit_cid->at(ilg2)) ){return true;}
//   else{return false;}
// }

#endif // #ifdef E16ANA_Massw2Gamma_cxx
