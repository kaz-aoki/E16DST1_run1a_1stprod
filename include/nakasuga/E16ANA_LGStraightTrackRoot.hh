//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jul 29 22:04:33 2023 by ROOT version 6.18/04
// from TTree tree/tree
// found on file: test.root
//////////////////////////////////////////////////////////

#ifndef E16ANA_LGStraightTrackRoot_h
#define E16ANA_LGStraightTrackRoot_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
using namespace std;
#include <stdio.h>
#include <iostream>


// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"

class E16ANA_LGStraightTrackRoot {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run_id;
   Int_t           event_id;
   Int_t           spill_id;
   Int_t           n_tracks;
   vector<double>  *trk_initpos_x;
   vector<double>  *trk_initpos_y;
   vector<double>  *trk_initpos_z;
   vector<double>  *trk_initdir_x;
   vector<double>  *trk_initdir_y;
   vector<double>  *trk_initdir_z;
   vector<int>     *trk_mid;
   vector<int>     *trk_cid;
   vector<double>  *trk_lx;
   vector<double>  *trk_ly;
   vector<double>  *trk_timing_100x;
   vector<double>  *trk_timing_100y;
   vector<double>  *trk_timing_200x;
   vector<double>  *trk_timing_200y;
   vector<double>  *trk_timing_300x;
   vector<double>  *trk_timing_300y;
   vector<double>  *trk_timing2_100x;
   vector<double>  *trk_timing2_100y;
   vector<double>  *trk_timing2_200x;
   vector<double>  *trk_timing2_200y;
   vector<double>  *trk_timing2_300x;
   vector<double>  *trk_timing2_300y;
   vector<double>  *trk_residual_100x;
   vector<double>  *trk_residual_100y;
   vector<double>  *trk_residual_200x;
   vector<double>  *trk_residual_200y;
   vector<double>  *trk_residual_300x;
   vector<double>  *trk_residual_300y;
   vector<double>  *trk_chi2_x;
   vector<double>  *trk_chi2_y;
   vector<double>  *trk_tgt_z;
   Int_t           n_lg_hits;
   vector<int>     *lg_mid;
   vector<int>     *lg_cid;
   vector<double>  *lg_lx;
   vector<double>  *lg_ly;
   vector<double>  *lg_adc;
   vector<double>  *lg_t;
   vector<int>     *lg_fflag;
   Int_t           n_lg_trg_hits;
   vector<int>     *lg_trg_mid;
   vector<int>     *lg_trg_cid;
   vector<float>   *lg_trg_t;
   vector<bool>    *lg_trg;
   vector<bool>    *lg_trg_trk;

   // List of branches
   TBranch        *b_run_id;   //!
   TBranch        *b_event_id;   //!
   TBranch        *b_spill_id;   //!
   TBranch        *b_n_tracks;   //!
   TBranch        *b_trk_initpos_x;   //!
   TBranch        *b_trk_initpos_y;   //!
   TBranch        *b_trk_initpos_z;   //!
   TBranch        *b_trk_initdir_x;   //!
   TBranch        *b_trk_initdir_y;   //!
   TBranch        *b_trk_initdir_z;   //!
   TBranch        *b_trk_mid;   //!
   TBranch        *b_trk_cid;   //!
   TBranch        *b_trk_lx;   //!
   TBranch        *b_trk_ly;   //!
   TBranch        *b_trk_timing_100x;   //!
   TBranch        *b_trk_timing_100y;   //!
   TBranch        *b_trk_timing_200x;   //!
   TBranch        *b_trk_timing_200y;   //!
   TBranch        *b_trk_timing_300x;   //!
   TBranch        *b_trk_timing_300y;   //!
   TBranch        *b_trk_timing2_100x;   //!
   TBranch        *b_trk_timing2_100y;   //!
   TBranch        *b_trk_timing2_200x;   //!
   TBranch        *b_trk_timing2_200y;   //!
   TBranch        *b_trk_timing2_300x;   //!
   TBranch        *b_trk_timing2_300y;   //!
   TBranch        *b_trk_residual_100x;   //!
   TBranch        *b_trk_residual_100y;   //!
   TBranch        *b_trk_residual_200x;   //!
   TBranch        *b_trk_residual_200y;   //!
   TBranch        *b_trk_residual_300x;   //!
   TBranch        *b_trk_residual_300y;   //!
   TBranch        *b_trk_chi2_x;   //!
   TBranch        *b_trk_chi2_y;   //!
   TBranch        *b_trk_tgt_z;   //!
   TBranch        *b_n_lg_hits;   //!
   TBranch        *b_lg_mid;   //!
   TBranch        *b_lg_cid;   //!
   TBranch        *b_lg_lx;   //!
   TBranch        *b_lg_ly;   //!
   TBranch        *b_lg_adc;   //!
   TBranch        *b_lg_t;   //!
   TBranch        *b_lg_fflag;   //!
   TBranch        *b_n_lg_trg_hits;   //!
   TBranch        *b_lg_trg_mid;   //!
   TBranch        *b_lg_trg_cid;   //!
   TBranch        *b_lg_trg_t;   //!
   TBranch        *b_lg_trg;   //!
   TBranch        *b_lg_trg_trk;   //!

   E16ANA_LGStraightTrackRoot(TTree *tree=0);
   virtual ~E16ANA_LGStraightTrackRoot();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual void     Residual();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef E16ANA_LGStraightTrackRoot_cxx
E16ANA_LGStraightTrackRoot::E16ANA_LGStraightTrackRoot(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("test.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("test.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

E16ANA_LGStraightTrackRoot::~E16ANA_LGStraightTrackRoot()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t E16ANA_LGStraightTrackRoot::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t E16ANA_LGStraightTrackRoot::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void E16ANA_LGStraightTrackRoot::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   trk_initpos_x = 0;
   trk_initpos_y = 0;
   trk_initpos_z = 0;
   trk_initdir_x = 0;
   trk_initdir_y = 0;
   trk_initdir_z = 0;
   trk_mid = 0;
   trk_cid = 0;
   trk_lx = 0;
   trk_ly = 0;
   trk_timing_100x = 0;
   trk_timing_100y = 0;
   trk_timing_200x = 0;
   trk_timing_200y = 0;
   trk_timing_300x = 0;
   trk_timing_300y = 0;
   trk_timing2_100x = 0;
   trk_timing2_100y = 0;
   trk_timing2_200x = 0;
   trk_timing2_200y = 0;
   trk_timing2_300x = 0;
   trk_timing2_300y = 0;
   trk_residual_100x = 0;
   trk_residual_100y = 0;
   trk_residual_200x = 0;
   trk_residual_200y = 0;
   trk_residual_300x = 0;
   trk_residual_300y = 0;
   trk_chi2_x = 0;
   trk_chi2_y = 0;
   trk_tgt_z = 0;
   lg_mid = 0;
   lg_cid = 0;
   lg_lx = 0;
   lg_ly = 0;
   lg_adc = 0;
   lg_t = 0;
   lg_fflag = 0;
   lg_trg_mid = 0;
   lg_trg_cid = 0;
   lg_trg_t = 0;
   lg_trg = 0;
   lg_trg_trk = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run_id", &run_id, &b_run_id);
   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("spill_id", &spill_id, &b_spill_id);
   fChain->SetBranchAddress("n_tracks", &n_tracks, &b_n_tracks);
   fChain->SetBranchAddress("trk_initpos_x", &trk_initpos_x, &b_trk_initpos_x);
   fChain->SetBranchAddress("trk_initpos_y", &trk_initpos_y, &b_trk_initpos_y);
   fChain->SetBranchAddress("trk_initpos_z", &trk_initpos_z, &b_trk_initpos_z);
   fChain->SetBranchAddress("trk_initdir_x", &trk_initdir_x, &b_trk_initdir_x);
   fChain->SetBranchAddress("trk_initdir_y", &trk_initdir_y, &b_trk_initdir_y);
   fChain->SetBranchAddress("trk_initdir_z", &trk_initdir_z, &b_trk_initdir_z);
   fChain->SetBranchAddress("trk_mid", &trk_mid, &b_trk_mid);
   fChain->SetBranchAddress("trk_cid", &trk_cid, &b_trk_cid);
   fChain->SetBranchAddress("trk_lx", &trk_lx, &b_trk_lx);
   fChain->SetBranchAddress("trk_ly", &trk_ly, &b_trk_ly);
   fChain->SetBranchAddress("trk_timing_100x", &trk_timing_100x, &b_trk_timing_100x);
   fChain->SetBranchAddress("trk_timing_100y", &trk_timing_100y, &b_trk_timing_100y);
   fChain->SetBranchAddress("trk_timing_200x", &trk_timing_200x, &b_trk_timing_200x);
   fChain->SetBranchAddress("trk_timing_200y", &trk_timing_200y, &b_trk_timing_200y);
   fChain->SetBranchAddress("trk_timing_300x", &trk_timing_300x, &b_trk_timing_300x);
   fChain->SetBranchAddress("trk_timing_300y", &trk_timing_300y, &b_trk_timing_300y);
   fChain->SetBranchAddress("trk_timing2_100x", &trk_timing2_100x, &b_trk_timing2_100x);
   fChain->SetBranchAddress("trk_timing2_100y", &trk_timing2_100y, &b_trk_timing2_100y);
   fChain->SetBranchAddress("trk_timing2_200x", &trk_timing2_200x, &b_trk_timing2_200x);
   fChain->SetBranchAddress("trk_timing2_200y", &trk_timing2_200y, &b_trk_timing2_200y);
   fChain->SetBranchAddress("trk_timing2_300x", &trk_timing2_300x, &b_trk_timing2_300x);
   fChain->SetBranchAddress("trk_timing2_300y", &trk_timing2_300y, &b_trk_timing2_300y);
   fChain->SetBranchAddress("trk_residual_100x", &trk_residual_100x, &b_trk_residual_100x);
   fChain->SetBranchAddress("trk_residual_100y", &trk_residual_100y, &b_trk_residual_100y);
   fChain->SetBranchAddress("trk_residual_200x", &trk_residual_200x, &b_trk_residual_200x);
   fChain->SetBranchAddress("trk_residual_200y", &trk_residual_200y, &b_trk_residual_200y);
   fChain->SetBranchAddress("trk_residual_300x", &trk_residual_300x, &b_trk_residual_300x);
   fChain->SetBranchAddress("trk_residual_300y", &trk_residual_300y, &b_trk_residual_300y);
   fChain->SetBranchAddress("trk_chi2_x", &trk_chi2_x, &b_trk_chi2_x);
   fChain->SetBranchAddress("trk_chi2_y", &trk_chi2_y, &b_trk_chi2_y);
   fChain->SetBranchAddress("trk_tgt_z", &trk_tgt_z, &b_trk_tgt_z);
   fChain->SetBranchAddress("n_lg_hits", &n_lg_hits, &b_n_lg_hits);
   fChain->SetBranchAddress("lg_mid", &lg_mid, &b_lg_mid);
   fChain->SetBranchAddress("lg_cid", &lg_cid, &b_lg_cid);
   fChain->SetBranchAddress("lg_lx", &lg_lx, &b_lg_lx);
   fChain->SetBranchAddress("lg_ly", &lg_ly, &b_lg_ly);
   fChain->SetBranchAddress("lg_adc", &lg_adc, &b_lg_adc);
   fChain->SetBranchAddress("lg_t", &lg_t, &b_lg_t);
   fChain->SetBranchAddress("lg_fflag", &lg_fflag, &b_lg_fflag);
   fChain->SetBranchAddress("n_lg_trg_hits", &n_lg_trg_hits, &b_n_lg_trg_hits);
   fChain->SetBranchAddress("lg_trg_mid", &lg_trg_mid, &b_lg_trg_mid);
   fChain->SetBranchAddress("lg_trg_cid", &lg_trg_cid, &b_lg_trg_cid);
   fChain->SetBranchAddress("lg_trg_t", &lg_trg_t, &b_lg_trg_t);
   fChain->SetBranchAddress("lg_trg", &lg_trg, &b_lg_trg);
   fChain->SetBranchAddress("lg_trg_trk", &lg_trg_trk, &b_lg_trg_trk);
   Notify();
}

Bool_t E16ANA_LGStraightTrackRoot::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void E16ANA_LGStraightTrackRoot::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t E16ANA_LGStraightTrackRoot::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef E16ANA_LGStraightTrackRoot_cxx
