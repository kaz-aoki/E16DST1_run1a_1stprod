//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Feb  2 23:05:51 2022 by ROOT version 6.18/04
// from TTree tree/tree
// found on file: test.root
//////////////////////////////////////////////////////////

#ifndef AnalyzerResidualHBD_h
#define AnalyzerResidualHBD_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>

#include <stdio.h>
#include <iostream>
using namespace std;

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"

class AnalyzerResidualHBD {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run_id;
   Int_t           event_id;
   Int_t           spill_id;
   Int_t           n_hbd_clusters;
   vector<int>     *hbd_cluster_id;
   vector<int>     *hbd_cluster_mid;
   vector<double>  *hbd_cluster_x;
   vector<double>  *hbd_cluster_y;
   vector<double>  *hbd_cluster_gx;
   vector<double>  *hbd_cluster_gy;
   vector<double>  *hbd_cluster_gz;
   vector<float>   *hbd_cluster_adc;
   vector<double>  *hbd_cluster_t;
   vector<float>   *hbd_cluster_ftime;
   vector<float>   *hbd_cluster_tdiff;
   vector<int>     *hbd_cluster_size;
   vector<float>   *hbd_cluster_eprob;
   vector<float>   *hbd_cluster_cprob;
   Int_t           n_lg_hits;
   vector<int>     *lg_hit_id;
   vector<int>     *lg_hit_mid;
   vector<double>  *lg_hit_x;
   vector<double>  *lg_hit_y;
   vector<double>  *lg_hit_gx;
   vector<double>  *lg_hit_gy;
   vector<double>  *lg_hit_gz;
   vector<float>   *lg_hit_adc;
   vector<float>   *lg_hit_t;
   vector<int>     *lg_hit_npeaks;
   vector<int>     *lg_hit_fflag;
   Int_t           n_lg_clusters;
   vector<int>     *lg_cluster_id;
   vector<int>     *lg_cluster_mid;
   vector<double>  *lg_cluster_x;
   vector<double>  *lg_cluster_y;
   vector<float>   *lg_cluster_adc;
   vector<float>   *lg_cluster_ftime;
   vector<float>   *lg_cluster_tdiff;
   vector<int>     *lg_cluster_mpcid;
   vector<float>   *lg_cluster_mp;
   vector<int>     *lg_cluster_size;
   Int_t           n_tracks;
   vector<int>     *track_id;
   vector<double>  *chi_square;
   vector<int>     *rk_charge;
   vector<int>     *is_selected;
   vector<int>     *track_mid;
   vector<double>  *track_lx;
   vector<double>  *track_ly;
   vector<double>  *track_mom;
   vector<double>  *track_mom_x;
   vector<double>  *track_mom_y;
   vector<double>  *track_mom_z;
   vector<float>   *track_lg_t;
   vector<float>   *track_lg_adc;
   vector<int>     *track_lg_mid;
   vector<int>     *track_lg_cid;
   vector<double>  *track_nearx;
   vector<double>  *track_neary;
   vector<int>     *track_multiplicity;
   vector<double>  *track_dum_nearx;
   vector<double>  *track_dum_neary;
   vector<int>     *track_dum_multiplicity;
   vector<vector<double> > *track_allhit_resx;
   vector<vector<double> > *track_allhit_resy;
   vector<vector<double> > *track_allhit_ftime;
   vector<vector<double> > *track_allhit_adc;
   vector<vector<double> > *track_allhit_dum_resx;
   vector<vector<double> > *track_allhit_dum_resy;
   vector<vector<double> > *track_allhit_dum_ftime;
   vector<vector<double> > *track_allhit_dum_adc;

   // List of branches
   TBranch        *b_run_id;   //!
   TBranch        *b_event_id;   //!
   TBranch        *b_spill_id;   //!
   TBranch        *b_n_hbd_clusters;   //!
   TBranch        *b_hbd_cluster_id;   //!
   TBranch        *b_hbd_cluster_mid;   //!
   TBranch        *b_hbd_cluster_x;   //!
   TBranch        *b_hbd_cluster_y;   //!
   TBranch        *b_hbd_cluster_gx;   //!
   TBranch        *b_hbd_cluster_gy;   //!
   TBranch        *b_hbd_cluster_gz;   //!
   TBranch        *b_hbd_cluster_adc;   //!
   TBranch        *b_hbd_cluster_t;   //!
   TBranch        *b_hbd_cluster_ftime;   //!
   TBranch        *b_hbd_cluster_tdiff;   //!
   TBranch        *b_hbd_cluster_size;   //!
   TBranch        *b_hbd_cluster_eprob;   //!
   TBranch        *b_hbd_cluster_cprob;   //!
   TBranch        *b_n_lg_hits;   //!
   TBranch        *b_lg_hit_id;   //!
   TBranch        *b_lg_hit_mid;   //!
   TBranch        *b_lg_hit_x;   //!
   TBranch        *b_lg_hit_y;   //!
   TBranch        *b_lg_hit_gx;   //!
   TBranch        *b_lg_hit_gy;   //!
   TBranch        *b_lg_hit_gz;   //!
   TBranch        *b_lg_hit_adc;   //!
   TBranch        *b_lg_hit_t;   //!
   TBranch        *b_lg_hit_npeaks;   //!
   TBranch        *b_lg_hit_fflag;   //!
   TBranch        *b_n_lg_clusters;   //!
   TBranch        *b_lg_cluster_id;   //!
   TBranch        *b_lg_cluster_mid;   //!
   TBranch        *b_lg_cluster_x;   //!
   TBranch        *b_lg_cluster_y;   //!
   TBranch        *b_lg_cluster_adc;   //!
   TBranch        *b_lg_cluster_ftime;   //!
   TBranch        *b_lg_cluster_tdiff;   //!
   TBranch        *b_lg_cluster_mpcid;   //!
   TBranch        *b_lg_cluster_mp;   //!
   TBranch        *b_lg_cluster_size;   //!
   TBranch        *b_n_tracks;   //!
   TBranch        *b_track_id;   //!
   TBranch        *b_chi_square;   //!
   TBranch        *b_rk_charge;   //!
   TBranch        *b_is_selected;   //!
   TBranch        *b_track_mid;   //!
   TBranch        *b_track_lx;   //!
   TBranch        *b_track_ly;   //!
   TBranch        *b_track_mom;   //!
   TBranch        *b_track_mom_x;   //!
   TBranch        *b_track_mom_y;   //!
   TBranch        *b_track_mom_z;   //!
   TBranch        *b_track_lg_t;   //!
   TBranch        *b_track_lg_adc;   //!
   TBranch        *b_track_lg_mid;   //!
   TBranch        *b_track_lg_cid;   //!
   TBranch        *b_track_nearx;   //!
   TBranch        *b_track_neary;   //!
   TBranch        *b_track_multiplicity;   //!
   TBranch        *b_track_dum_nearx;   //!
   TBranch        *b_track_dum_neary;   //!
   TBranch        *b_track_dum_multiplicity;   //!
   TBranch        *b_track_allhit_resx;   //!
   TBranch        *b_track_allhit_resy;   //!
   TBranch        *b_track_allhit_ftime;   //!
   TBranch        *b_track_allhit_adc;   //!
   TBranch        *b_track_allhit_dum_resx;   //!
   TBranch        *b_track_allhit_dum_resy;   //!
   TBranch        *b_track_allhit_dum_ftime;   //!
   TBranch        *b_track_allhit_dum_adc;   //!

   AnalyzerResidualHBD(TTree *tree=0);
   virtual ~AnalyzerResidualHBD();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    CutOfTrack(Long64_t entry, int itrack );
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   static double Get2DHistIntegral(TH2F* h2d, int radius, TH2F* h2dcopy, double originx, double originy);
   static double Get2DHistIntegral(TH2F* h2d, int radius, double originx, double originy);
   static double Get2DHistIntegral(TH2F* h2d, int radius, TH2F* h2dcopy);
   static double Get2DHistSquareIntegral(TH2F* h2d, TH2F* h2dcopy, double originx, double originy, double sigmax, double sigmay);
   static double Get2DHistSquareIntegral(TH2F* h2d, double originx, double originy, double sigmax, double sigmay);
   virtual void     DrawPDF(int runtype, int maxevent, char* out_file_name);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef AnalyzerResidualHBD_cxx
AnalyzerResidualHBD::AnalyzerResidualHBD(TTree *tree) : fChain(0) 
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

AnalyzerResidualHBD::~AnalyzerResidualHBD()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AnalyzerResidualHBD::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AnalyzerResidualHBD::LoadTree(Long64_t entry)
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

void AnalyzerResidualHBD::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   hbd_cluster_id = 0;
   hbd_cluster_mid = 0;
   hbd_cluster_x = 0;
   hbd_cluster_y = 0;
   hbd_cluster_gx = 0;
   hbd_cluster_gy = 0;
   hbd_cluster_gz = 0;
   hbd_cluster_adc = 0;
   hbd_cluster_t = 0;
   hbd_cluster_ftime = 0;
   hbd_cluster_tdiff = 0;
   hbd_cluster_size = 0;
   hbd_cluster_eprob = 0;
   hbd_cluster_cprob = 0;
   lg_hit_id = 0;
   lg_hit_mid = 0;
   lg_hit_x = 0;
   lg_hit_y = 0;
   lg_hit_gx = 0;
   lg_hit_gy = 0;
   lg_hit_gz = 0;
   lg_hit_adc = 0;
   lg_hit_t = 0;
   lg_hit_npeaks = 0;
   lg_hit_fflag = 0;
   lg_cluster_id = 0;
   lg_cluster_mid = 0;
   lg_cluster_x = 0;
   lg_cluster_y = 0;
   lg_cluster_adc = 0;
   lg_cluster_ftime = 0;
   lg_cluster_tdiff = 0;
   lg_cluster_mpcid = 0;
   lg_cluster_mp = 0;
   lg_cluster_size = 0;
   track_id = 0;
   chi_square = 0;
   rk_charge = 0;
   is_selected = 0;
   track_mid = 0;
   track_lx = 0;
   track_ly = 0;
   track_mom = 0;
   track_mom_x = 0;
   track_mom_y = 0;
   track_mom_z = 0;
   track_lg_t = 0;
   track_lg_adc = 0;
   track_lg_mid = 0;
   track_lg_cid = 0;
   track_nearx = 0;
   track_neary = 0;
   track_multiplicity = 0;
   track_dum_nearx = 0;
   track_dum_neary = 0;
   track_dum_multiplicity = 0;
   track_allhit_resx = 0;
   track_allhit_resy = 0;
   track_allhit_ftime = 0;
   track_allhit_adc = 0;
   track_allhit_dum_resx = 0;
   track_allhit_dum_resy = 0;
   track_allhit_dum_ftime = 0;
   track_allhit_dum_adc = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run_id", &run_id, &b_run_id);
   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("spill_id", &spill_id, &b_spill_id);
   fChain->SetBranchAddress("n_hbd_clusters", &n_hbd_clusters, &b_n_hbd_clusters);
   fChain->SetBranchAddress("hbd_cluster_id", &hbd_cluster_id, &b_hbd_cluster_id);
   fChain->SetBranchAddress("hbd_cluster_mid", &hbd_cluster_mid, &b_hbd_cluster_mid);
   fChain->SetBranchAddress("hbd_cluster_x", &hbd_cluster_x, &b_hbd_cluster_x);
   fChain->SetBranchAddress("hbd_cluster_y", &hbd_cluster_y, &b_hbd_cluster_y);
   fChain->SetBranchAddress("hbd_cluster_gx", &hbd_cluster_gx, &b_hbd_cluster_gx);
   fChain->SetBranchAddress("hbd_cluster_gy", &hbd_cluster_gy, &b_hbd_cluster_gy);
   fChain->SetBranchAddress("hbd_cluster_gz", &hbd_cluster_gz, &b_hbd_cluster_gz);
   fChain->SetBranchAddress("hbd_cluster_adc", &hbd_cluster_adc, &b_hbd_cluster_adc);
   fChain->SetBranchAddress("hbd_cluster_t", &hbd_cluster_t, &b_hbd_cluster_t);
   fChain->SetBranchAddress("hbd_cluster_ftime", &hbd_cluster_ftime, &b_hbd_cluster_ftime);
   fChain->SetBranchAddress("hbd_cluster_tdiff", &hbd_cluster_tdiff, &b_hbd_cluster_tdiff);
   fChain->SetBranchAddress("hbd_cluster_size", &hbd_cluster_size, &b_hbd_cluster_size);
   fChain->SetBranchAddress("hbd_cluster_eprob", &hbd_cluster_eprob, &b_hbd_cluster_eprob);
   fChain->SetBranchAddress("hbd_cluster_cprob", &hbd_cluster_cprob, &b_hbd_cluster_cprob);
   fChain->SetBranchAddress("n_lg_hits", &n_lg_hits, &b_n_lg_hits);
   fChain->SetBranchAddress("lg_hit_id", &lg_hit_id, &b_lg_hit_id);
   fChain->SetBranchAddress("lg_hit_mid", &lg_hit_mid, &b_lg_hit_mid);
   fChain->SetBranchAddress("lg_hit_x", &lg_hit_x, &b_lg_hit_x);
   fChain->SetBranchAddress("lg_hit_y", &lg_hit_y, &b_lg_hit_y);
   fChain->SetBranchAddress("lg_hit_gx", &lg_hit_gx, &b_lg_hit_gx);
   fChain->SetBranchAddress("lg_hit_gy", &lg_hit_gy, &b_lg_hit_gy);
   fChain->SetBranchAddress("lg_hit_gz", &lg_hit_gz, &b_lg_hit_gz);
   fChain->SetBranchAddress("lg_hit_adc", &lg_hit_adc, &b_lg_hit_adc);
   fChain->SetBranchAddress("lg_hit_t", &lg_hit_t, &b_lg_hit_t);
   fChain->SetBranchAddress("lg_hit_npeaks", &lg_hit_npeaks, &b_lg_hit_npeaks);
   fChain->SetBranchAddress("lg_hit_fflag", &lg_hit_fflag, &b_lg_hit_fflag);
   fChain->SetBranchAddress("n_tracks", &n_tracks, &b_n_tracks);
   fChain->SetBranchAddress("n_lg_clusters", &n_lg_clusters, &b_n_lg_clusters);
   fChain->SetBranchAddress("lg_cluster_id", &lg_cluster_id, &b_lg_cluster_id);
   fChain->SetBranchAddress("lg_cluster_mid", &lg_cluster_mid, &b_lg_cluster_mid);
   fChain->SetBranchAddress("lg_cluster_x", &lg_cluster_x, &b_lg_cluster_x);
   fChain->SetBranchAddress("lg_cluster_y", &lg_cluster_y, &b_lg_cluster_y);
   fChain->SetBranchAddress("lg_cluster_adc", &lg_cluster_adc, &b_lg_cluster_adc);
   fChain->SetBranchAddress("lg_cluster_ftime", &lg_cluster_ftime, &b_lg_cluster_ftime);
   fChain->SetBranchAddress("lg_cluster_tdiff", &lg_cluster_tdiff, &b_lg_cluster_tdiff);
   fChain->SetBranchAddress("lg_cluster_mpcid", &lg_cluster_mpcid, &b_lg_cluster_mpcid);
   fChain->SetBranchAddress("lg_cluster_mp", &lg_cluster_mp, &b_lg_cluster_mp);
   fChain->SetBranchAddress("lg_cluster_size", &lg_cluster_size, &b_lg_cluster_size);
   fChain->SetBranchAddress("track_id", &track_id, &b_track_id);
   fChain->SetBranchAddress("chi_square", &chi_square, &b_chi_square);
   fChain->SetBranchAddress("rk_charge", &rk_charge, &b_rk_charge);
   fChain->SetBranchAddress("is_selected", &is_selected, &b_is_selected);
   fChain->SetBranchAddress("track_mid", &track_mid, &b_track_mid);
   fChain->SetBranchAddress("track_lx", &track_lx, &b_track_lx);
   fChain->SetBranchAddress("track_ly", &track_ly, &b_track_ly);
   fChain->SetBranchAddress("track_mom", &track_mom, &b_track_mom);
   fChain->SetBranchAddress("track_mom_x", &track_mom_x, &b_track_mom_x);
   fChain->SetBranchAddress("track_mom_y", &track_mom_y, &b_track_mom_y);
   fChain->SetBranchAddress("track_mom_z", &track_mom_z, &b_track_mom_z);
   fChain->SetBranchAddress("track_lg_t", &track_lg_t, &b_track_lg_t);
   fChain->SetBranchAddress("track_lg_adc", &track_lg_adc, &b_track_lg_adc);
   fChain->SetBranchAddress("track_lg_mid", &track_lg_mid, &b_track_lg_mid);
   fChain->SetBranchAddress("track_lg_cid", &track_lg_cid, &b_track_lg_cid);
   fChain->SetBranchAddress("track_nearx", &track_nearx, &b_track_nearx);
   fChain->SetBranchAddress("track_neary", &track_neary, &b_track_neary);
   fChain->SetBranchAddress("track_multiplicity", &track_multiplicity, &b_track_multiplicity);
   fChain->SetBranchAddress("track_dum_nearx", &track_dum_nearx, &b_track_dum_nearx);
   fChain->SetBranchAddress("track_dum_neary", &track_dum_neary, &b_track_dum_neary);
   fChain->SetBranchAddress("track_dum_multiplicity", &track_dum_multiplicity, &b_track_dum_multiplicity);
   fChain->SetBranchAddress("track_allhit_resx", &track_allhit_resx, &b_track_allhit_resx);
   fChain->SetBranchAddress("track_allhit_resy", &track_allhit_resy, &b_track_allhit_resy);
   fChain->SetBranchAddress("track_allhit_ftime", &track_allhit_ftime, &b_track_allhit_ftime);
   fChain->SetBranchAddress("track_allhit_adc", &track_allhit_adc, &b_track_allhit_adc);
   fChain->SetBranchAddress("track_allhit_dum_resx", &track_allhit_dum_resx, &b_track_allhit_dum_resx);
   fChain->SetBranchAddress("track_allhit_dum_resy", &track_allhit_dum_resy, &b_track_allhit_dum_resy);
   fChain->SetBranchAddress("track_allhit_dum_ftime", &track_allhit_dum_ftime, &b_track_allhit_dum_ftime);
   fChain->SetBranchAddress("track_allhit_dum_adc", &track_allhit_dum_adc, &b_track_allhit_dum_adc);
   Notify();
}

Bool_t AnalyzerResidualHBD::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AnalyzerResidualHBD::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t AnalyzerResidualHBD::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

Int_t AnalyzerResidualHBD::CutOfTrack(Long64_t entry, int itrack)
{
  if(chi_square->at(itrack)>50){
    return -1;
  }
  else if(is_selected->at(itrack)==0){
    return -1;
  }
  else{
    return 1;
  }
}
#endif // #ifdef AnalyzerResidualHBD_cxx
