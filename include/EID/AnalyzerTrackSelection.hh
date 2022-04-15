//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb  3 22:10:48 2022 by ROOT version 6.18/04
// from TTree tree/tree
// found on file: out/root03a/trackselection_chisq30_unlinklg.root
//////////////////////////////////////////////////////////

#ifndef AnalyzerTrackSelection_h
#define AnalyzerTrackSelection_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>

#include <stdio.h>
#include <iostream>
using namespace std;

// Header file for the classes stored in the TTree if any.
#include "SingleTrackAnalyzerForRes.hh"
#include "vector"
#include "vector"
#include "vector"
#include "vector"

class AnalyzerTrackSelection {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run_id;
   Int_t           event_id;
   Int_t           spill_id;
   Int_t           n_tracks;
   vector<int>     *track_id;
   vector<double>  *chi_square;
   vector<int>     *rk_charge;
   vector<int>     *is_selected;
   vector<double>  *track_mom;
   vector<double>  *track_mom_x;
   vector<double>  *track_mom_y;
   vector<double>  *track_mom_z;
   vector<double>  *track_tgt_dist;
   vector<double>  *track_lg_pi_eff1;
   vector<double>  *track_lg_pi_eff2;
   vector<double>  *track_angle_lx;
   vector<double>  *track_angle_ly;
   vector<double>  *track_position_block_lx;
   vector<double>  *track_position_block_ly;
   vector<double>  *track_ssd_t;
   vector<double>  *track_ssd_adc;
   vector<double>  *track_gtr100x_t;
   vector<double>  *track_gtr100x_adc;
   vector<double>  *track_gtr100y_t;
   vector<double>  *track_gtr100y_adc;
   vector<double>  *track_gtr200x_t;
   vector<double>  *track_gtr200x_adc;
   vector<double>  *track_gtr200y_t;
   vector<double>  *track_gtr200y_adc;
   vector<double>  *track_gtr300x_t;
   vector<double>  *track_gtr300x_adc;
   vector<double>  *track_gtr300y_t;
   vector<double>  *track_gtr300y_adc;
   vector<int>     *track_hbd_mid;
   vector<double>  *track_hbd_lx;
   vector<double>  *track_hbd_ly;
   vector<double>  *track_hbd_nearx;
   vector<double>  *track_hbd_neary;
   vector<int>     *track_hbd_multiplicity;
   vector<double>  *track_hbd_dum_nearx;
   vector<double>  *track_hbd_dum_neary;
   vector<int>     *track_hbd_dum_multiplicity;
   vector<int>     *track_lg_mid;
   vector<double>  *track_lg_lx;
   vector<double>  *track_lg_ly;
   vector<double>  *track_lg_nearx;
   vector<double>  *track_lg_neary;
   vector<int>     *track_lg_multiplicity;
   vector<double>  *track_lg_dum_nearx;
   vector<double>  *track_lg_dum_neary;
   vector<int>     *track_lg_dum_multiplicity;
   vector<double>  *track_lg_cl_nearx;
   vector<double>  *track_lg_cl_neary;
   vector<int>     *track_lg_cl_multiplicity;
   vector<double>  *track_lg_cl_dum_nearx;
   vector<double>  *track_lg_cl_dum_neary;
   vector<int>     *track_lg_cl_dum_multiplicity;
   vector<vector<double> > *track_hbd_allhit_resx;
   vector<vector<double> > *track_hbd_allhit_resy;
   vector<vector<double> > *track_hbd_allhit_ftime;
   vector<vector<double> > *track_hbd_allhit_adc;
   vector<vector<double> > *track_hbd_allhit_size;
   vector<vector<double> > *track_hbd_allhit_eprob;
   vector<vector<double> > *track_hbd_allhit_cprob;
   vector<vector<double> > *track_hbd_allhit_dum_resx;
   vector<vector<double> > *track_hbd_allhit_dum_resy;
   vector<vector<double> > *track_hbd_allhit_dum_ftime;
   vector<vector<double> > *track_hbd_allhit_dum_adc;
   vector<vector<double> > *track_hbd_allhit_dum_size;
   vector<vector<double> > *track_hbd_allhit_dum_eprob;
   vector<vector<double> > *track_hbd_allhit_dum_cprob;
   vector<vector<double> > *track_lg_allhit_resx;
   vector<vector<double> > *track_lg_allhit_resy;
   vector<vector<double> > *track_lg_allhit_ftime;
   vector<vector<double> > *track_lg_allhit_adc;
   vector<vector<double> > *track_lg_allhit_dum_resx;
   vector<vector<double> > *track_lg_allhit_dum_resy;
   vector<vector<double> > *track_lg_allhit_dum_ftime;
   vector<vector<double> > *track_lg_allhit_dum_adc;
   vector<vector<double> > *track_lg_cl_allhit_resx;
   vector<vector<double> > *track_lg_cl_allhit_resy;
   vector<vector<double> > *track_lg_cl_allhit_ftime;
   vector<vector<double> > *track_lg_cl_allhit_adc;
   vector<vector<double> > *track_lg_cl_allhit_maxpeak;
   vector<vector<double> > *track_lg_cl_allhit_maxcid;
   vector<vector<double> > *track_lg_cl_allhit_dum_resx;
   vector<vector<double> > *track_lg_cl_allhit_dum_resy;
   vector<vector<double> > *track_lg_cl_allhit_dum_ftime;
   vector<vector<double> > *track_lg_cl_allhit_dum_adc;
   vector<vector<double> > *track_lg_cl_allhit_dum_maxpeak;
   vector<vector<double> > *track_lg_cl_allhit_dum_maxcid;

   // List of branches
   TBranch        *b_run_id;   //!
   TBranch        *b_event_id;   //!
   TBranch        *b_spill_id;   //!
   TBranch        *b_n_tracks;   //!
   TBranch        *b_track_id;   //!
   TBranch        *b_chi_square;   //!
   TBranch        *b_rk_charge;   //!
   TBranch        *b_is_selected;   //!
   TBranch        *b_track_mom;   //!
   TBranch        *b_track_mom_x;   //!
   TBranch        *b_track_mom_y;   //!
   TBranch        *b_track_mom_z;   //!
   TBranch        *b_track_tgt_dist;   //!
   TBranch        *b_track_lg_pi_eff1;   //!
   TBranch        *b_track_lg_pi_eff2;   //!
   TBranch        *b_track_angle_lx;   //!
   TBranch        *b_track_angle_ly;   //!
   TBranch        *b_track_position_block_lx;   //!
   TBranch        *b_track_position_block_ly;   //!
   TBranch        *b_track_ssd_t;   //!
   TBranch        *b_track_ssd_adc;   //!
   TBranch        *b_track_gtr100x_t;   //!
   TBranch        *b_track_gtr100x_adc;   //!
   TBranch        *b_track_gtr100y_t;   //!
   TBranch        *b_track_gtr100y_adc;   //!
   TBranch        *b_track_gtr200x_t;   //!
   TBranch        *b_track_gtr200x_adc;   //!
   TBranch        *b_track_gtr200y_t;   //!
   TBranch        *b_track_gtr200y_adc;   //!
   TBranch        *b_track_gtr300x_t;   //!
   TBranch        *b_track_gtr300x_adc;   //!
   TBranch        *b_track_gtr300y_t;   //!
   TBranch        *b_track_gtr300y_adc;   //!
   TBranch        *b_track_hbd_mid;   //!
   TBranch        *b_track_hbd_lx;   //!
   TBranch        *b_track_hbd_ly;   //!
   TBranch        *b_track_hbd_nearx;   //!
   TBranch        *b_track_hbd_neary;   //!
   TBranch        *b_track_hbd_multiplicity;   //!
   TBranch        *b_track_hbd_dum_nearx;   //!
   TBranch        *b_track_hbd_dum_neary;   //!
   TBranch        *b_track_hbd_dum_multiplicity;   //!
   TBranch        *b_track_lg_mid;   //!
   TBranch        *b_track_lg_lx;   //!
   TBranch        *b_track_lg_ly;   //!
   TBranch        *b_track_lg_nearx;   //!
   TBranch        *b_track_lg_neary;   //!
   TBranch        *b_track_lg_multiplicity;   //!
   TBranch        *b_track_lg_dum_nearx;   //!
   TBranch        *b_track_lg_dum_neary;   //!
   TBranch        *b_track_lg_dum_multiplicity;   //!
   TBranch        *b_track_lg_cl_nearx;   //!
   TBranch        *b_track_lg_cl_neary;   //!
   TBranch        *b_track_lg_cl_multiplicity;   //!
   TBranch        *b_track_lg_cl_dum_nearx;   //!
   TBranch        *b_track_lg_cl_dum_neary;   //!
   TBranch        *b_track_lg_cl_dum_multiplicity;   //!
   TBranch        *b_track_hbd_allhit_resx;   //!
   TBranch        *b_track_hbd_allhit_resy;   //!
   TBranch        *b_track_hbd_allhit_ftime;   //!
   TBranch        *b_track_hbd_allhit_adc;   //!
   TBranch        *b_track_hbd_allhit_size;   //!
   TBranch        *b_track_hbd_allhit_eprob;   //!
   TBranch        *b_track_hbd_allhit_cprob;   //!
   TBranch        *b_track_hbd_allhit_dum_resx;   //!
   TBranch        *b_track_hbd_allhit_dum_resy;   //!
   TBranch        *b_track_hbd_allhit_dum_ftime;   //!
   TBranch        *b_track_hbd_allhit_dum_adc;   //!
   TBranch        *b_track_hbd_allhit_dum_size;   //!
   TBranch        *b_track_hbd_allhit_dum_eprob;   //!
   TBranch        *b_track_hbd_allhit_dum_cprob;   //!
   TBranch        *b_track_lg_allhit_resx;   //!
   TBranch        *b_track_lg_allhit_resy;   //!
   TBranch        *b_track_lg_allhit_ftime;   //!
   TBranch        *b_track_lg_allhit_adc;   //!
   TBranch        *b_track_lg_allhit_dum_resx;   //!
   TBranch        *b_track_lg_allhit_dum_resy;   //!
   TBranch        *b_track_lg_allhit_dum_ftime;   //!
   TBranch        *b_track_lg_allhit_dum_adc;   //!
   TBranch        *b_track_lg_cl_allhit_resx;   //!
   TBranch        *b_track_lg_cl_allhit_resy;   //!
   TBranch        *b_track_lg_cl_allhit_ftime;   //!
   TBranch        *b_track_lg_cl_allhit_adc;   //!
   TBranch        *b_track_lg_cl_allhit_maxpeak;   //!
   TBranch        *b_track_lg_cl_allhit_maxcid;   //!
   TBranch        *b_track_lg_cl_allhit_dum_resx;   //!
   TBranch        *b_track_lg_cl_allhit_dum_resy;   //!
   TBranch        *b_track_lg_cl_allhit_dum_ftime;   //!
   TBranch        *b_track_lg_cl_allhit_dum_adc;   //!
   TBranch        *b_track_lg_cl_allhit_dum_maxpeak;   //!
   TBranch        *b_track_lg_cl_allhit_dum_maxcid;   //!

   AnalyzerTrackSelection(TTree *tree=0);
   virtual ~AnalyzerTrackSelection();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    Cut(Long64_t entry, std::vector<int>& goodtracks);
   virtual Int_t    CutOfTrack(Long64_t entry, int itrack, std::vector<int>& goodtracks);
   virtual Int_t    CutOfTrack(Long64_t entry, int itrack, int runoption );
   virtual Int_t    CutOfTrack(Long64_t entry, int itrack );
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual void     DrawForResidualHBD(int runtype, int maxevent, char* out_file_name);
   virtual void     DrawForTrackSelection(int runtype, int maxevent, char* out_file_name);
   virtual void     CalcLGEfficiency(int runtype, int maxevent, char* out_file_name);
   virtual void     MkMixingHist(int runoption, int maxevent, int moduleid);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef AnalyzerTrackSelection_cxx
AnalyzerTrackSelection::AnalyzerTrackSelection(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("out/root03a/trackselection_chisq30_unlinklg.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("out/root03a/trackselection_chisq30_unlinklg.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

AnalyzerTrackSelection::~AnalyzerTrackSelection()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AnalyzerTrackSelection::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AnalyzerTrackSelection::LoadTree(Long64_t entry)
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

void AnalyzerTrackSelection::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   track_id = 0;
   chi_square = 0;
   rk_charge = 0;
   is_selected = 0;
   track_mom = 0;
   track_mom_x = 0;
   track_mom_y = 0;
   track_mom_z = 0;
   track_tgt_dist = 0;
   track_lg_pi_eff1 = 0;
   track_lg_pi_eff2 = 0;
   track_angle_lx = 0;
   track_angle_ly = 0;
   track_position_block_lx = 0;
   track_position_block_ly = 0;
   track_ssd_t = 0;
   track_ssd_adc = 0;
   track_gtr100x_t = 0;
   track_gtr100x_adc = 0;
   track_gtr100y_t = 0;
   track_gtr100y_adc = 0;
   track_gtr200x_t = 0;
   track_gtr200x_adc = 0;
   track_gtr200y_t = 0;
   track_gtr200y_adc = 0;
   track_gtr300x_t = 0;
   track_gtr300x_adc = 0;
   track_gtr300y_t = 0;
   track_gtr300y_adc = 0;
   track_hbd_mid = 0;
   track_hbd_lx = 0;
   track_hbd_ly = 0;
   track_hbd_nearx = 0;
   track_hbd_neary = 0;
   track_hbd_multiplicity = 0;
   track_hbd_dum_nearx = 0;
   track_hbd_dum_neary = 0;
   track_hbd_dum_multiplicity = 0;
   track_lg_mid = 0;
   track_lg_lx = 0;
   track_lg_ly = 0;
   track_lg_nearx = 0;
   track_lg_neary = 0;
   track_lg_multiplicity = 0;
   track_lg_dum_nearx = 0;
   track_lg_dum_neary = 0;
   track_lg_dum_multiplicity = 0;
   track_lg_cl_nearx = 0;
   track_lg_cl_neary = 0;
   track_lg_cl_multiplicity = 0;
   track_lg_cl_dum_nearx = 0;
   track_lg_cl_dum_neary = 0;
   track_lg_cl_dum_multiplicity = 0;
   track_hbd_allhit_resx = 0;
   track_hbd_allhit_resy = 0;
   track_hbd_allhit_ftime = 0;
   track_hbd_allhit_adc = 0;
   track_hbd_allhit_size = 0;
   track_hbd_allhit_eprob = 0;
   track_hbd_allhit_cprob = 0;
   track_hbd_allhit_dum_resx = 0;
   track_hbd_allhit_dum_resy = 0;
   track_hbd_allhit_dum_ftime = 0;
   track_hbd_allhit_dum_adc = 0;
   track_hbd_allhit_dum_size = 0;
   track_hbd_allhit_dum_eprob = 0;
   track_hbd_allhit_dum_cprob = 0;
   track_lg_allhit_resx = 0;
   track_lg_allhit_resy = 0;
   track_lg_allhit_ftime = 0;
   track_lg_allhit_adc = 0;
   track_lg_allhit_dum_resx = 0;
   track_lg_allhit_dum_resy = 0;
   track_lg_allhit_dum_ftime = 0;
   track_lg_allhit_dum_adc = 0;
   track_lg_cl_allhit_resx = 0;
   track_lg_cl_allhit_resy = 0;
   track_lg_cl_allhit_ftime = 0;
   track_lg_cl_allhit_adc = 0;
   track_lg_cl_allhit_maxpeak = 0;
   track_lg_cl_allhit_maxcid = 0;
   track_lg_cl_allhit_dum_resx = 0;
   track_lg_cl_allhit_dum_resy = 0;
   track_lg_cl_allhit_dum_ftime = 0;
   track_lg_cl_allhit_dum_adc = 0;
   track_lg_cl_allhit_dum_maxpeak = 0;
   track_lg_cl_allhit_dum_maxcid = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run_id", &run_id, &b_run_id);
   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("spill_id", &spill_id, &b_spill_id);
   fChain->SetBranchAddress("n_tracks", &n_tracks, &b_n_tracks);
   fChain->SetBranchAddress("track_id", &track_id, &b_track_id);
   fChain->SetBranchAddress("chi_square", &chi_square, &b_chi_square);
   fChain->SetBranchAddress("rk_charge", &rk_charge, &b_rk_charge);
   fChain->SetBranchAddress("is_selected", &is_selected, &b_is_selected);
   fChain->SetBranchAddress("track_mom", &track_mom, &b_track_mom);
   fChain->SetBranchAddress("track_mom_x", &track_mom_x, &b_track_mom_x);
   fChain->SetBranchAddress("track_mom_y", &track_mom_y, &b_track_mom_y);
   fChain->SetBranchAddress("track_mom_z", &track_mom_z, &b_track_mom_z);
   fChain->SetBranchAddress("track_tgt_dist", &track_tgt_dist, &b_track_tgt_dist);
   fChain->SetBranchAddress("track_lg_pi_eff1", &track_lg_pi_eff1, &b_track_lg_pi_eff1);
   fChain->SetBranchAddress("track_lg_pi_eff2", &track_lg_pi_eff2, &b_track_lg_pi_eff2);
   fChain->SetBranchAddress("track_angle_lx", &track_angle_lx, &b_track_angle_lx);
   fChain->SetBranchAddress("track_angle_ly", &track_angle_ly, &b_track_angle_ly);
   fChain->SetBranchAddress("track_position_block_lx", &track_position_block_lx, &b_track_position_block_lx);
   fChain->SetBranchAddress("track_position_block_ly", &track_position_block_ly, &b_track_position_block_ly);
   fChain->SetBranchAddress("track_ssd_t", &track_ssd_t, &b_track_ssd_t);
   fChain->SetBranchAddress("track_ssd_adc", &track_ssd_adc, &b_track_ssd_adc);
   fChain->SetBranchAddress("track_gtr100x_t", &track_gtr100x_t, &b_track_gtr100x_t);
   fChain->SetBranchAddress("track_gtr100x_adc", &track_gtr100x_adc, &b_track_gtr100x_adc);
   fChain->SetBranchAddress("track_gtr100y_t", &track_gtr100y_t, &b_track_gtr100y_t);
   fChain->SetBranchAddress("track_gtr100y_adc", &track_gtr100y_adc, &b_track_gtr100y_adc);
   fChain->SetBranchAddress("track_gtr200x_t", &track_gtr200x_t, &b_track_gtr200x_t);
   fChain->SetBranchAddress("track_gtr200x_adc", &track_gtr200x_adc, &b_track_gtr200x_adc);
   fChain->SetBranchAddress("track_gtr200y_t", &track_gtr200y_t, &b_track_gtr200y_t);
   fChain->SetBranchAddress("track_gtr200y_adc", &track_gtr200y_adc, &b_track_gtr200y_adc);
   fChain->SetBranchAddress("track_gtr300x_t", &track_gtr300x_t, &b_track_gtr300x_t);
   fChain->SetBranchAddress("track_gtr300x_adc", &track_gtr300x_adc, &b_track_gtr300x_adc);
   fChain->SetBranchAddress("track_gtr300y_t", &track_gtr300y_t, &b_track_gtr300y_t);
   fChain->SetBranchAddress("track_gtr300y_adc", &track_gtr300y_adc, &b_track_gtr300y_adc);
   fChain->SetBranchAddress("track_hbd_mid", &track_hbd_mid, &b_track_hbd_mid);
   fChain->SetBranchAddress("track_hbd_lx", &track_hbd_lx, &b_track_hbd_lx);
   fChain->SetBranchAddress("track_hbd_ly", &track_hbd_ly, &b_track_hbd_ly);
   fChain->SetBranchAddress("track_hbd_nearx", &track_hbd_nearx, &b_track_hbd_nearx);
   fChain->SetBranchAddress("track_hbd_neary", &track_hbd_neary, &b_track_hbd_neary);
   fChain->SetBranchAddress("track_hbd_multiplicity", &track_hbd_multiplicity, &b_track_hbd_multiplicity);
   fChain->SetBranchAddress("track_hbd_dum_nearx", &track_hbd_dum_nearx, &b_track_hbd_dum_nearx);
   fChain->SetBranchAddress("track_hbd_dum_neary", &track_hbd_dum_neary, &b_track_hbd_dum_neary);
   fChain->SetBranchAddress("track_hbd_dum_multiplicity", &track_hbd_dum_multiplicity, &b_track_hbd_dum_multiplicity);
   fChain->SetBranchAddress("track_lg_mid", &track_lg_mid, &b_track_lg_mid);
   fChain->SetBranchAddress("track_lg_lx", &track_lg_lx, &b_track_lg_lx);
   fChain->SetBranchAddress("track_lg_ly", &track_lg_ly, &b_track_lg_ly);
   fChain->SetBranchAddress("track_lg_nearx", &track_lg_nearx, &b_track_lg_nearx);
   fChain->SetBranchAddress("track_lg_neary", &track_lg_neary, &b_track_lg_neary);
   fChain->SetBranchAddress("track_lg_multiplicity", &track_lg_multiplicity, &b_track_lg_multiplicity);
   fChain->SetBranchAddress("track_lg_dum_nearx", &track_lg_dum_nearx, &b_track_lg_dum_nearx);
   fChain->SetBranchAddress("track_lg_dum_neary", &track_lg_dum_neary, &b_track_lg_dum_neary);
   fChain->SetBranchAddress("track_lg_dum_multiplicity", &track_lg_dum_multiplicity, &b_track_lg_dum_multiplicity);
   fChain->SetBranchAddress("track_lg_cl_nearx", &track_lg_cl_nearx, &b_track_lg_cl_nearx);
   fChain->SetBranchAddress("track_lg_cl_neary", &track_lg_cl_neary, &b_track_lg_cl_neary);
   fChain->SetBranchAddress("track_lg_cl_multiplicity", &track_lg_cl_multiplicity, &b_track_lg_cl_multiplicity);
   fChain->SetBranchAddress("track_lg_cl_dum_nearx", &track_lg_cl_dum_nearx, &b_track_lg_cl_dum_nearx);
   fChain->SetBranchAddress("track_lg_cl_dum_neary", &track_lg_cl_dum_neary, &b_track_lg_cl_dum_neary);
   fChain->SetBranchAddress("track_lg_cl_dum_multiplicity", &track_lg_cl_dum_multiplicity, &b_track_lg_cl_dum_multiplicity);
   fChain->SetBranchAddress("track_hbd_allhit_resx", &track_hbd_allhit_resx, &b_track_hbd_allhit_resx);
   fChain->SetBranchAddress("track_hbd_allhit_resy", &track_hbd_allhit_resy, &b_track_hbd_allhit_resy);
   fChain->SetBranchAddress("track_hbd_allhit_ftime", &track_hbd_allhit_ftime, &b_track_hbd_allhit_ftime);
   fChain->SetBranchAddress("track_hbd_allhit_adc", &track_hbd_allhit_adc, &b_track_hbd_allhit_adc);
   fChain->SetBranchAddress("track_hbd_allhit_size", &track_hbd_allhit_size, &b_track_hbd_allhit_size);
   fChain->SetBranchAddress("track_hbd_allhit_eprob", &track_hbd_allhit_eprob, &b_track_hbd_allhit_eprob);
   fChain->SetBranchAddress("track_hbd_allhit_cprob", &track_hbd_allhit_cprob, &b_track_hbd_allhit_cprob);
   fChain->SetBranchAddress("track_hbd_allhit_dum_resx", &track_hbd_allhit_dum_resx, &b_track_hbd_allhit_dum_resx);
   fChain->SetBranchAddress("track_hbd_allhit_dum_resy", &track_hbd_allhit_dum_resy, &b_track_hbd_allhit_dum_resy);
   fChain->SetBranchAddress("track_hbd_allhit_dum_ftime", &track_hbd_allhit_dum_ftime, &b_track_hbd_allhit_dum_ftime);
   fChain->SetBranchAddress("track_hbd_allhit_dum_adc", &track_hbd_allhit_dum_adc, &b_track_hbd_allhit_dum_adc);
   fChain->SetBranchAddress("track_hbd_allhit_dum_size", &track_hbd_allhit_dum_size, &b_track_hbd_allhit_dum_size);
   fChain->SetBranchAddress("track_hbd_allhit_dum_eprob", &track_hbd_allhit_dum_eprob, &b_track_hbd_allhit_dum_eprob);
   fChain->SetBranchAddress("track_hbd_allhit_dum_cprob", &track_hbd_allhit_dum_cprob, &b_track_hbd_allhit_dum_cprob);
   fChain->SetBranchAddress("track_lg_allhit_resx", &track_lg_allhit_resx, &b_track_lg_allhit_resx);
   fChain->SetBranchAddress("track_lg_allhit_resy", &track_lg_allhit_resy, &b_track_lg_allhit_resy);
   fChain->SetBranchAddress("track_lg_allhit_ftime", &track_lg_allhit_ftime, &b_track_lg_allhit_ftime);
   fChain->SetBranchAddress("track_lg_allhit_adc", &track_lg_allhit_adc, &b_track_lg_allhit_adc);
   fChain->SetBranchAddress("track_lg_allhit_dum_resx", &track_lg_allhit_dum_resx, &b_track_lg_allhit_dum_resx);
   fChain->SetBranchAddress("track_lg_allhit_dum_resy", &track_lg_allhit_dum_resy, &b_track_lg_allhit_dum_resy);
   fChain->SetBranchAddress("track_lg_allhit_dum_ftime", &track_lg_allhit_dum_ftime, &b_track_lg_allhit_dum_ftime);
   fChain->SetBranchAddress("track_lg_allhit_dum_adc", &track_lg_allhit_dum_adc, &b_track_lg_allhit_dum_adc);
   fChain->SetBranchAddress("track_lg_cl_allhit_resx", &track_lg_cl_allhit_resx, &b_track_lg_cl_allhit_resx);
   fChain->SetBranchAddress("track_lg_cl_allhit_resy", &track_lg_cl_allhit_resy, &b_track_lg_cl_allhit_resy);
   fChain->SetBranchAddress("track_lg_cl_allhit_ftime", &track_lg_cl_allhit_ftime, &b_track_lg_cl_allhit_ftime);
   fChain->SetBranchAddress("track_lg_cl_allhit_adc", &track_lg_cl_allhit_adc, &b_track_lg_cl_allhit_adc);
   fChain->SetBranchAddress("track_lg_cl_allhit_maxpeak", &track_lg_cl_allhit_maxpeak, &b_track_lg_cl_allhit_maxpeak);
   fChain->SetBranchAddress("track_lg_cl_allhit_maxcid", &track_lg_cl_allhit_maxcid, &b_track_lg_cl_allhit_maxcid);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_resx", &track_lg_cl_allhit_dum_resx, &b_track_lg_cl_allhit_dum_resx);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_resy", &track_lg_cl_allhit_dum_resy, &b_track_lg_cl_allhit_dum_resy);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_ftime", &track_lg_cl_allhit_dum_ftime, &b_track_lg_cl_allhit_dum_ftime);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_adc", &track_lg_cl_allhit_dum_adc, &b_track_lg_cl_allhit_dum_adc);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_maxpeak", &track_lg_cl_allhit_dum_maxpeak, &b_track_lg_cl_allhit_dum_maxpeak);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_maxcid", &track_lg_cl_allhit_dum_maxcid, &b_track_lg_cl_allhit_dum_maxcid);
   Notify();
}

Bool_t AnalyzerTrackSelection::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AnalyzerTrackSelection::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t AnalyzerTrackSelection::Cut(Long64_t entry)
{
  std::vector<int> goodtracks(1);
  return Cut(entry,goodtracks);
}
Int_t AnalyzerTrackSelection::Cut(Long64_t entry, std::vector<int>& goodtracks)
{
  if(goodtracks.size()==1){return 1;}
  else{

  struct set{
    int track_id;
    double chisq;
    double ssd;
    double gtr100x;
    double gtr100y;
    double gtr200x;
    double gtr200y;
    double gtr300x;
    double gtr300y;

    bool operator==(const set& another){
      if( ssd == another.ssd
    	|| gtr100x == another.gtr100x
    	|| gtr100y == another.gtr100y
    	|| gtr200x == another.gtr200x
    	|| gtr200y == another.gtr200y
    	|| gtr300x == another.gtr300x
    	|| gtr300y == another.gtr300y) return true;
      return false;
    }
  };

  std::vector<set> tracks(0);
  // std::cout<<n_tracks<<std::endl;
  //tracks are already sorted by chi_square in DST1
  for(int i=0;i<n_tracks;i++){ //track loop
    if(chi_square->at(i)>30.) continue;
    if(fabs(track_position_block_lx->at(i))>30) continue;
    if(fabs(track_position_block_ly->at(i))>30) continue;
    set settmp;
    settmp.track_id = track_id->at(i);
    settmp.chisq = chi_square->at(i);
    settmp.ssd = track_ssd_t->at(i);
    settmp.gtr100x = track_gtr100x_t->at(i);
    settmp.gtr100y = track_gtr100y_t->at(i);
    settmp.gtr200x = track_gtr200x_t->at(i);
    settmp.gtr200y = track_gtr200y_t->at(i);
    settmp.gtr300x = track_gtr300x_t->at(i);
    settmp.gtr300y = track_gtr300y_t->at(i);
    // std::cout<<settmp.chisq<<" "<<settmp.ssd<<" "<<settmp.gtr100x<<" "<<settmp.gtr100y<<" "<<settmp.gtr200x<<" "<<settmp.gtr200y<<" "<<settmp.gtr300x<<" "<<settmp.gtr300y<<std::endl;

    if(tracks.size()==0){
      tracks.push_back(settmp);
      goodtracks.push_back(settmp.track_id);
    }
    else{
      bool isgood = false;
      for(int j=0;j<tracks.size();j++){
	if(settmp==tracks.at(j)){
	  break;
	}
	if(j==tracks.size()-1){isgood=true;}
      }
      if(isgood==true){
	tracks.push_back(settmp);
	goodtracks.push_back(settmp.track_id);
      }
    }
  }//track loop

  // std::cout<<"************"<<tracks.size()<<" "<<goodtracks.size()<<std::endl;
  if(goodtracks.size()==0){return -1;}

  return 1;
  }
}
// Int_t AnalyzerTrackSelection::Cut(Long64_t entry, std::vector<int>& goodtracks)
// {
//   if(goodtracks.size()==1){return 1;}
//   else{

//   struct set{
//     int track_id;
//     double chisq;
//     int pos_id;
//     double tim;

//     bool operator<(const set& another){
//       if( pos_id != another.pos_id ){ return pos_id<another.pos_id; }
//       if( tim != another.tim ){ return tim<another.tim; }
//       return chisq < another.chisq;
//     }

//   };
//   std::vector<set> tracks(0);
//   // std::cout<<n_tracks<<std::endl;
//   for(int i=0;i<n_tracks;i++){
//     if(chi_square->at(i)>30.) continue;
//     if(fabs(track_position_block_lx->at(i))>30) continue;
//     if(fabs(track_position_block_ly->at(i))>30) continue;
//     set settmp;
//     settmp.track_id = track_id->at(i);
//     settmp.chisq = chi_square->at(i);
//     int mid = track_lg_mid->at(i);
//     int blockchx = (track_lg_lx->at(i))-(track_position_block_lx->at(i));
//     int blockchy = (track_lg_ly->at(i)/fabs(track_lg_ly->at(i)))*(fabs(track_lg_ly->at(i))+track_position_block_ly->at(i));
//     int cid = SingleTrackAnalyzerForRes::LocaltoCh(blockchx,blockchy);
//     settmp.pos_id = mid*100+cid;
//     settmp.tim = track_ssd_t->at(i);
//     // std::cout<<settmp.pos_id<<" "<<settmp.tim<<" "<<settmp.chisq<<std::endl;
//     tracks.push_back(settmp);
//   }

//   sort(tracks.begin(),tracks.end());

//   int tmp_pos_id=10000;
//   for(int i=0;i<tracks.size();i++){
//     // std::cout<<tracks.at(i).pos_id<<" "<<tracks.at(i).tim<<" "<<tracks.at(i).chisq<<std::endl;
//     if(tracks.at(i).pos_id!=tmp_pos_id){
//       goodtracks.push_back(tracks.at(i).track_id);
//       tmp_pos_id = tracks.at(i).pos_id;
//     }
//   }

//   return 1;
//   }
// }
Int_t AnalyzerTrackSelection::CutOfTrack(Long64_t entry, int itrack, std::vector<int> &goodtracks)
{
  for(int i=0;i<goodtracks.size();i++){
    if(track_id->at(itrack)==goodtracks.at(i)){return 1;}
  }
  return -1;
}
Int_t AnalyzerTrackSelection::CutOfTrack(Long64_t entry, int itrack, int runoption)
{
  double momxz = sqrt(track_mom_x->at(itrack)*track_mom_x->at(itrack)+track_mom_z->at(itrack)*track_mom_z->at(itrack));//220212
  if (track_hbd_mid->at(itrack)!=track_lg_mid->at(itrack)) {return -2;}
  // else if (momxz<1.0) {return -1;}//220212
  else if (chi_square->at(itrack)>30.) {return -1;}
  // else if (fabs(track_angle_lx->at(itrack))>0.2) {return -1;}//220222
  else if (fabs(track_position_block_lx->at(itrack))>30) {return -1;}//220222
  else if (fabs(track_position_block_ly->at(itrack))>30) {return -1;}//220222
  // else if ( runoption==0 && (track_ssd_t->at(itrack)<40||track_ssd_t->at(itrack)>55) ) {return -1;}//220213
  // else if ( runoption==3 && (track_ssd_t->at(itrack)<41||track_ssd_t->at(itrack)>56) ) {return -1;}//220213
  // else if ( runoption==1 && (track_ssd_t->at(itrack)<38||track_ssd_t->at(itrack)>54) ) {return -1;}//220213
  // else if ( is_selected->at(itrack)==0 ) {return -1;}
  // else if ( track_lg_multiplicity->at(itrack)>4 ) {return -1;}//220306
  // else if ( track_hbd_multiplicity->at(itrack)>5 ) {return -1;}//220306
  // else if ( track_tgt_dist->at(itrack)>5 ) {return -1;}
  // else if((track_gtr100x_t->at(itrack)-track_ssd_t->at(itrack))<10) {return -1;}
  // else if((track_gtr100x_t->at(itrack)-track_ssd_t->at(itrack))>250) {return -1;}
  // else if((track_gtr100y_t->at(itrack)-track_ssd_t->at(itrack))<10) {return -1;}
  // else if((track_gtr100y_t->at(itrack)-track_ssd_t->at(itrack))>250) {return -1;}
  // else if((track_gtr200x_t->at(itrack)-track_ssd_t->at(itrack))<10) {return -1;}
  // else if((track_gtr200x_t->at(itrack)-track_ssd_t->at(itrack))>250) {return -1;}
  // else if((track_gtr200y_t->at(itrack)-track_ssd_t->at(itrack))<10) {return -1;}
  // else if((track_gtr200y_t->at(itrack)-track_ssd_t->at(itrack))>250) {return -1;}
  // else if((track_gtr300x_t->at(itrack)-track_ssd_t->at(itrack))<10) {return -1;}
  // else if((track_gtr300x_t->at(itrack)-track_ssd_t->at(itrack))>250) {return -1;}
  // else if((track_gtr300y_t->at(itrack)-track_ssd_t->at(itrack))<10) {return -1;}
  // else if((track_gtr300y_t->at(itrack)-track_ssd_t->at(itrack))>250) {return -1;}
  // else if(track_gtr100y_adc->at(itrack)/track_gtr100x_adc->at(itrack)<0.25) {return -1;}
  // else if(track_gtr100y_adc->at(itrack)/track_gtr100x_adc->at(itrack)>1.5) {return -1;}
  // else if(track_gtr200y_adc->at(itrack)/track_gtr200x_adc->at(itrack)<0.25) {return -1;}
  // else if(track_gtr200y_adc->at(itrack)/track_gtr200x_adc->at(itrack)>1.5) {return -1;}
  // else if(track_gtr300y_adc->at(itrack)/track_gtr300x_adc->at(itrack)<0.25) {return -1;}
  // else if(track_gtr300y_adc->at(itrack)/track_gtr300x_adc->at(itrack)>1.5) {return -1;}
  // else if(  runoption==1 && (track_gtr100x_t->at(itrack)-track_gtr100y_t->at(itrack))<-20)  {return -1;}
  // else if(  runoption==1 && (track_gtr100x_t->at(itrack)-track_gtr100y_t->at(itrack))>30)  {return -1;}
  // else if(  runoption==1 && (track_gtr200x_t->at(itrack)-track_gtr200y_t->at(itrack))<-30)  {return -1;}
  // else if(  runoption==1 && (track_gtr200x_t->at(itrack)-track_gtr200y_t->at(itrack))>30)  {return -1;}
  // else if(  runoption==1 && (track_gtr300x_t->at(itrack)-track_gtr300y_t->at(itrack))<-30)  {return -1;}
  // else if(  runoption==1 && (track_gtr300x_t->at(itrack)-track_gtr300y_t->at(itrack))>30)  {return -1;}
  else{
    return 1;
  }
}
Int_t AnalyzerTrackSelection::CutOfTrack(Long64_t entry, int itrack)
{
  int runoption = 0;
  return CutOfTrack(entry,itrack,runoption);
}
#endif // #ifdef AnalyzerTrackSelection_cxx
