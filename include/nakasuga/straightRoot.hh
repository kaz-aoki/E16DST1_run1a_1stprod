//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul 27 15:40:01 2023 by ROOT version 6.18/04
// from TTree tree/tree
// found on file: /work24/E16/Run0d/srs/dst1/out_all_nakasuga.root
//////////////////////////////////////////////////////////

#ifndef straightRoot_h
#define straightRoot_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
using namespace std;
#include <stdio.h>
#include <iostream>
#include <unordered_map>

// Header file for the classes stored in the TTree if any.
#include "TVector3.h"
#include "vector"
#include "vector"
#include "vector"

class straightRoot {
private :
  std::unordered_map<int, std::vector<int>> map;

  int ntracks;
  std::vector<TVector3> initposs;
  std::vector<TVector3> initdirs;
  std::vector<double> timing_100xs;
  std::vector<double> timing_100ys;
  std::vector<double> timing_200xs;
  std::vector<double> timing_200ys;
  std::vector<double> timing_300xs;
  std::vector<double> timing_300ys;
  std::vector<double> timing2_100xs;
  std::vector<double> timing2_100ys;
  std::vector<double> timing2_200xs;
  std::vector<double> timing2_200ys;
  std::vector<double> timing2_300xs;
  std::vector<double> timing2_300ys;
  std::vector<double> residual_100xs;
  std::vector<double> residual_100ys;
  std::vector<double> residual_200xs;
  std::vector<double> residual_200ys;
  std::vector<double> residual_300xs;
  std::vector<double> residual_300ys;
  std::vector<double> chi2_xs;
  std::vector<double> chi2_ys;
  std::vector<double> tgt_zs;

public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run_id;
   Int_t           event_id;
   Int_t           mod_id;
   // Int_t           hitid_ssdx;//duplicate
   // Int_t           hitid_100x;
   // Int_t           hitid_200x;
   // Int_t           hitid_300x;
   // Int_t           hitid_100y;
   // Int_t           hitid_200y;
   // Int_t           hitid_300y;
   Double_t        g_xssd;
   Double_t        g_zssd;
   Double_t        gc_x100;
   Double_t        gc_y100;
   Double_t        gc_z100;
   Double_t        gc_x200;
   Double_t        gc_y200;
   Double_t        gc_z200;
   Double_t        gc_x300;
   Double_t        gc_y300;
   Double_t        gc_z300;
   Double_t        gt_x100;
   Double_t        gt_y100;
   Double_t        gt_z100;
   Double_t        gt_x200;
   Double_t        gt_y200;
   Double_t        gt_z200;
   Double_t        gt_x300;
   Double_t        gt_y300;
   Double_t        gt_z300;
   Double_t        lxssd;
   Double_t        lx100;
   Double_t        ly100;
   Double_t        lx200;
   Double_t        ly200;
   Double_t        lx300;
   Double_t        ly300;
   Double_t        clc_xssd;
   Double_t        clc_x100;
   Double_t        clc_x200;
   Double_t        clc_x300;
   Double_t        clc_y100;
   Double_t        clc_y200;
   Double_t        clc_y300;
   Double_t        timing_xssd;
   Double_t        timing_x100;
   Double_t        timing_x200;
   Double_t        timing_x300;
   Double_t        timing_y100;
   Double_t        timing_y200;
   Double_t        timing_y300;
   Double_t        timing2_x100;
   Double_t        timing2_x200;
   Double_t        timing2_x300;
   Double_t        timing2_y100;
   Double_t        timing2_y200;
   Double_t        timing2_y300;
   Double_t        timing3_x100;
   Double_t        timing3_x200;
   Double_t        timing3_x300;
   Double_t        timing3_y100;
   Double_t        timing3_y200;
   Double_t        timing3_y300;
   Double_t        timing4_x100;
   Double_t        timing4_x200;
   Double_t        timing4_x300;
   Double_t        timing4_y100;
   Double_t        timing4_y200;
   Double_t        timing4_y300;
   Double_t        timing5_x100;
   Double_t        timing5_x200;
   Double_t        timing5_x300;
   Double_t        timing5_y100;
   Double_t        timing5_y200;
   Double_t        timing5_y300;
   Double_t        residual_100x;
   Double_t        residual_200x;
   Double_t        residual_300x;
   Double_t        residual_100y;
   Double_t        residual_200y;
   Double_t        residual_300y;
   Double_t        residual_ssdx;
   Double_t        fitresidual_100x;
   Double_t        fitresidual_200x;
   Double_t        fitresidual_300x;
   Double_t        fitresidual_100y;
   Double_t        fitresidual_200y;
   Double_t        fitresidual_300y;
   Double_t        fitresidual_ssdx;
   Double_t        chi2_x;
   Double_t        chi2_y;
   Double_t        tgt_z;
   Double_t        fit_a_x;
   Double_t        fit_b_x;
   Double_t        fit_a_y;
   Double_t        fit_b_y;
   Double_t        distance_x;
   Double_t        distance_fromtgt_y;
   Double_t        distance_fromupwire_y;
   Double_t        distance_fromdownwire_y;
   Double_t        fit_g100x;
   Double_t        fit_g100y;
   Double_t        fit_g100z;
   Double_t        fit_g200x;
   Double_t        fit_g200y;
   Double_t        fit_g200z;
   Double_t        fit_g300x;
   Double_t        fit_g300y;
   Double_t        fit_g300z;
   Int_t           hasMatchedASDHit;
   Int_t           x_trk_used_times;
   Int_t           trkid_x;
   Int_t           trkid_y;
   Int_t           hitid_ssdx;
   Int_t           hitid_100x;
   Int_t           hitid_200x;
   Int_t           hitid_300x;
   Int_t           hitid_100y;
   Int_t           hitid_200y;
   Int_t           hitid_300y;
   Int_t           cluster_size_ssd;
   Int_t           cluster_size_g100x;
   Int_t           cluster_size_g200x;
   Int_t           cluster_size_g300x;
   Int_t           cluster_size_g100y;
   Int_t           cluster_size_g200y;
   Int_t           cluster_size_g300y;
   Int_t           asd_hit;
   Int_t           lg_hit;
   TVector3        *lg_cross_pos;
   Int_t           lg_module_id;
   Int_t           lg_channel_id;
   Double_t        timediff_in_cluster_100x;
   Double_t        timediff_in_cluster_200x;
   Double_t        timediff_in_cluster_300x;
   vector<double>  *timings_100x;
   vector<double>  *timings_200x;
   vector<double>  *timings_300x;
   vector<double>  *positions_100x;
   vector<double>  *positions_200x;
   vector<double>  *positions_300x;
   vector<double>  *asd_hits;
   vector<vector<double> > *fadc_100x;
   vector<vector<double> > *fadc_200x;
   vector<vector<double> > *fadc_300x;
   vector<vector<double> > *fadc_100y;
   vector<vector<double> > *fadc_200y;
   vector<vector<double> > *fadc_300y;
   vector<int>     *sid_100x;
   vector<int>     *sid_200x;
   vector<int>     *sid_300x;
   vector<int>     *sid_100y;
   vector<int>     *sid_200y;
   vector<int>     *sid_300y;
   vector<double>  *tot_100x;
   vector<double>  *tot_200x;
   vector<double>  *tot_300x;
   vector<double>  *tot_100y;
   vector<double>  *tot_200y;
   vector<double>  *tot_300y;
   vector<double>  *htime_100x;
   vector<double>  *htime_200x;
   vector<double>  *htime_300x;
   vector<double>  *htime_100y;
   vector<double>  *htime_200y;
   vector<double>  *htime_300y;
   vector<double>  *ph_100x;
   vector<double>  *ph_200x;
   vector<double>  *ph_300x;
   vector<double>  *ph_100y;
   vector<double>  *ph_200y;
   vector<double>  *ph_300y;
   vector<int>     *hsid_rlx;
   vector<double>  *hph_rlx;
   vector<vector<double> > *fadc_rlx;
   vector<double>  *clc_rlx;
   vector<double>  *clcog_rlx;
   vector<double>  *clt_rlx;

   // List of branches
   TBranch        *b_run_id;   //!
   TBranch        *b_event_id;   //!
   TBranch        *b_mod_id;   //!
   // TBranch        *b_hitid_ssdx;   //!
   // TBranch        *b_hitid_100x;   //!
   // TBranch        *b_hitid_200x;   //!
   // TBranch        *b_hitid_300x;   //!
   // TBranch        *b_hitid_100y;   //!
   // TBranch        *b_hitid_200y;   //!
   // TBranch        *b_hitid_300y;   //!
   TBranch        *b_g_xssd;   //!
   TBranch        *b_g_zssd;   //!
   TBranch        *b_gc_x100;   //!
   TBranch        *b_gc_y100;   //!
   TBranch        *b_gc_z100;   //!
   TBranch        *b_gc_x200;   //!
   TBranch        *b_gc_y200;   //!
   TBranch        *b_gc_z200;   //!
   TBranch        *b_gc_x300;   //!
   TBranch        *b_gc_y300;   //!
   TBranch        *b_gc_z300;   //!
   TBranch        *b_gt_x100;   //!
   TBranch        *b_gt_y100;   //!
   TBranch        *b_gt_z100;   //!
   TBranch        *b_gt_x200;   //!
   TBranch        *b_gt_y200;   //!
   TBranch        *b_gt_z200;   //!
   TBranch        *b_gt_x300;   //!
   TBranch        *b_gt_y300;   //!
   TBranch        *b_gt_z300;   //!
   TBranch        *b_lxssd;   //!
   TBranch        *b_lx100;   //!
   TBranch        *b_ly100;   //!
   TBranch        *b_lx200;   //!
   TBranch        *b_ly200;   //!
   TBranch        *b_lx300;   //!
   TBranch        *b_ly300;   //!
   TBranch        *b_clc_xssd;   //!
   TBranch        *b_clc_x100;   //!
   TBranch        *b_clc_x200;   //!
   TBranch        *b_clc_x300;   //!
   TBranch        *b_clc_y100;   //!
   TBranch        *b_clc_y200;   //!
   TBranch        *b_clc_y300;   //!
   TBranch        *b_timing_xssd;   //!
   TBranch        *b_timing_x100;   //!
   TBranch        *b_timing_x200;   //!
   TBranch        *b_timing_x300;   //!
   TBranch        *b_timing_y100;   //!
   TBranch        *b_timing_y200;   //!
   TBranch        *b_timing_y300;   //!
   TBranch        *b_timing2_x100;   //!
   TBranch        *b_timing2_x200;   //!
   TBranch        *b_timing2_x300;   //!
   TBranch        *b_timing2_y100;   //!
   TBranch        *b_timing2_y200;   //!
   TBranch        *b_timing2_y300;   //!
   TBranch        *b_timing3_x100;   //!
   TBranch        *b_timing3_x200;   //!
   TBranch        *b_timing3_x300;   //!
   TBranch        *b_timing3_y100;   //!
   TBranch        *b_timing3_y200;   //!
   TBranch        *b_timing3_y300;   //!
   TBranch        *b_timing4_x100;   //!
   TBranch        *b_timing4_x200;   //!
   TBranch        *b_timing4_x300;   //!
   TBranch        *b_timing4_y100;   //!
   TBranch        *b_timing4_y200;   //!
   TBranch        *b_timing4_y300;   //!
   TBranch        *b_timing5_x100;   //!
   TBranch        *b_timing5_x200;   //!
   TBranch        *b_timing5_x300;   //!
   TBranch        *b_timing5_y100;   //!
   TBranch        *b_timing5_y200;   //!
   TBranch        *b_timing5_y300;   //!
   TBranch        *b_residual_100x;   //!
   TBranch        *b_residual_200x;   //!
   TBranch        *b_residual_300x;   //!
   TBranch        *b_residual_100y;   //!
   TBranch        *b_residual_200y;   //!
   TBranch        *b_residual_300y;   //!
   TBranch        *b_residual_ssdx;   //!
   TBranch        *b_fitresidual_100x;   //!
   TBranch        *b_fitresidual_200x;   //!
   TBranch        *b_fitresidual_300x;   //!
   TBranch        *b_fitresidual_100y;   //!
   TBranch        *b_fitresidual_200y;   //!
   TBranch        *b_fitresidual_300y;   //!
   TBranch        *b_fitresidual_ssdx;   //!
   TBranch        *b_chi2_x;   //!
   TBranch        *b_chi2_y;   //!
   TBranch        *b_tgt_z;   //!
   TBranch        *b_fit_a_x;   //!
   TBranch        *b_fit_b_x;   //!
   TBranch        *b_fit_a_y;   //!
   TBranch        *b_fit_b_y;   //!
   TBranch        *b_distance_x;   //!
   TBranch        *b_distance_fromtgt_y;   //!
   TBranch        *b_distance_fromupwire_y;   //!
   TBranch        *b_distance_fromdownwire_y;   //!
   TBranch        *b_fit_g100x;   //!
   TBranch        *b_fit_g100y;   //!
   TBranch        *b_fit_g100z;   //!
   TBranch        *b_fit_g200x;   //!
   TBranch        *b_fit_g200y;   //!
   TBranch        *b_fit_g200z;   //!
   TBranch        *b_fit_g300x;   //!
   TBranch        *b_fit_g300y;   //!
   TBranch        *b_fit_g300z;   //!
   TBranch        *b_hasMatchedASDHit;   //!
   TBranch        *b_x_trk_used_times;   //!
   TBranch        *b_trkid_x;   //!
   TBranch        *b_trkid_y;   //!
   TBranch        *b_hitid_ssdx;   //!
   TBranch        *b_hitid_100x;   //!
   TBranch        *b_hitid_200x;   //!
   TBranch        *b_hitid_300x;   //!
   TBranch        *b_hitid_100y;   //!
   TBranch        *b_hitid_200y;   //!
   TBranch        *b_hitid_300y;   //!
   TBranch        *b_cluster_size_ssd;   //!
   TBranch        *b_cluster_size_g100x;   //!
   TBranch        *b_cluster_size_g200x;   //!
   TBranch        *b_cluster_size_g300x;   //!
   TBranch        *b_cluster_size_g100y;   //!
   TBranch        *b_cluster_size_g200y;   //!
   TBranch        *b_cluster_size_g300y;   //!
   TBranch        *b_asd_hit;   //!
   TBranch        *b_lg_hit;   //!
   TBranch        *b_lg_cross_pos;   //!
   TBranch        *b_lg_module_id;   //!
   TBranch        *b_lg_channel_id;   //!
   TBranch        *b_timediff_in_cluster_100x;   //!
   TBranch        *b_timediff_in_cluster_200x;   //!
   TBranch        *b_timediff_in_cluster_300x;   //!
   TBranch        *b_timings_100x;   //!
   TBranch        *b_timings_200x;   //!
   TBranch        *b_timings_300x;   //!
   TBranch        *b_positions_100x;   //!
   TBranch        *b_positions_200x;   //!
   TBranch        *b_positions_300x;   //!
   TBranch        *b_asd_hits;   //!
   TBranch        *b_fadc_100x;   //!
   TBranch        *b_fadc_200x;   //!
   TBranch        *b_fadc_300x;   //!
   TBranch        *b_fadc_100y;   //!
   TBranch        *b_fadc_200y;   //!
   TBranch        *b_fadc_300y;   //!
   TBranch        *b_sid_100x;   //!
   TBranch        *b_sid_200x;   //!
   TBranch        *b_sid_300x;   //!
   TBranch        *b_sid_100y;   //!
   TBranch        *b_sid_200y;   //!
   TBranch        *b_sid_300y;   //!
   TBranch        *b_tot_100x;   //!
   TBranch        *b_tot_200x;   //!
   TBranch        *b_tot_300x;   //!
   TBranch        *b_tot_100y;   //!
   TBranch        *b_tot_200y;   //!
   TBranch        *b_tot_300y;   //!
   TBranch        *b_htime_100x;   //!
   TBranch        *b_htime_200x;   //!
   TBranch        *b_htime_300x;   //!
   TBranch        *b_htime_100y;   //!
   TBranch        *b_htime_200y;   //!
   TBranch        *b_htime_300y;   //!
   TBranch        *b_ph_100x;   //!
   TBranch        *b_ph_200x;   //!
   TBranch        *b_ph_300x;   //!
   TBranch        *b_ph_100y;   //!
   TBranch        *b_ph_200y;   //!
   TBranch        *b_ph_300y;   //!
   TBranch        *b_hsid_rlx;   //!
   TBranch        *b_hph_rlx;   //!
   TBranch        *b_fadc_rlx;   //!
   TBranch        *b_clc_rlx;   //!
   TBranch        *b_clcog_rlx;   //!
   TBranch        *b_clt_rlx;   //!

   straightRoot(TTree *tree=0);
   virtual ~straightRoot();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(int run);
   virtual void     ClearEntry();
   virtual void     MakeMap(int in_run_id, int maxevent);
   virtual void     SetEntry(int in_event_id);
   virtual void     CalcInitInfo(TVector3& g1, TVector3& g2, TVector3& _initpos, TVector3& _initdir);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   int Ntracks(){return ntracks;}
   void CopyVecTVector3(std::vector<TVector3>& original, std::vector<TVector3>& copy){
     for( int i=0; i<original.size(); i++ ){ copy.push_back(original.at(i)); }
   }
   void CopyVecDouble(std::vector<double>& original, std::vector<double>& copy){
     for( int i=0; i<original.size(); i++ ){ copy.push_back(original.at(i)); }
   }
   void GetInitPos(std::vector<TVector3>& vec){CopyVecTVector3(initposs,vec);}
   void GetInitDir(std::vector<TVector3>& vec){CopyVecTVector3(initdirs,vec);}
   void GetTiming100X(std::vector<double>& vec){CopyVecDouble(timing_100xs,vec);}
   void GetTiming100Y(std::vector<double>& vec){CopyVecDouble(timing_100ys,vec);}
   void GetTiming200X(std::vector<double>& vec){CopyVecDouble(timing_200xs,vec);}
   void GetTiming200Y(std::vector<double>& vec){CopyVecDouble(timing_200ys,vec);}
   void GetTiming300X(std::vector<double>& vec){CopyVecDouble(timing_300xs,vec);}
   void GetTiming300Y(std::vector<double>& vec){CopyVecDouble(timing_300ys,vec);}
   void GetTiming2100X(std::vector<double>& vec){CopyVecDouble(timing2_100xs,vec);}
   void GetTiming2100Y(std::vector<double>& vec){CopyVecDouble(timing2_100ys,vec);}
   void GetTiming2200X(std::vector<double>& vec){CopyVecDouble(timing2_200xs,vec);}
   void GetTiming2200Y(std::vector<double>& vec){CopyVecDouble(timing2_200ys,vec);}
   void GetTiming2300X(std::vector<double>& vec){CopyVecDouble(timing2_300xs,vec);}
   void GetTiming2300Y(std::vector<double>& vec){CopyVecDouble(timing2_300ys,vec);}
   void GetResidual100X(std::vector<double>& vec){CopyVecDouble(residual_100xs,vec);}
   void GetResidual100Y(std::vector<double>& vec){CopyVecDouble(residual_100ys,vec);}
   void GetResidual200X(std::vector<double>& vec){CopyVecDouble(residual_200xs,vec);}
   void GetResidual200Y(std::vector<double>& vec){CopyVecDouble(residual_200ys,vec);}
   void GetResidual300X(std::vector<double>& vec){CopyVecDouble(residual_300xs,vec);}
   void GetResidual300Y(std::vector<double>& vec){CopyVecDouble(residual_300ys,vec);}
   void GetChi2X(std::vector<double>& vec){CopyVecDouble(chi2_xs,vec);}
   void GetChi2Y(std::vector<double>& vec){CopyVecDouble(chi2_ys,vec);}
   void GetTgtZ(std::vector<double>& vec){CopyVecDouble(tgt_zs,vec);}
};

#endif

#ifdef straightRoot_cxx
straightRoot::straightRoot(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/work24/E16/Run0d/srs/dst1/out_all_nakasuga.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/work24/E16/Run0d/srs/dst1/out_all_nakasuga.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
   ClearEntry();
}

straightRoot::~straightRoot()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t straightRoot::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t straightRoot::LoadTree(Long64_t entry)
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

void straightRoot::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   lg_cross_pos = 0;
   timings_100x = 0;
   timings_200x = 0;
   timings_300x = 0;
   positions_100x = 0;
   positions_200x = 0;
   positions_300x = 0;
   asd_hits = 0;
   fadc_100x = 0;
   fadc_200x = 0;
   fadc_300x = 0;
   fadc_100y = 0;
   fadc_200y = 0;
   fadc_300y = 0;
   sid_100x = 0;
   sid_200x = 0;
   sid_300x = 0;
   sid_100y = 0;
   sid_200y = 0;
   sid_300y = 0;
   tot_100x = 0;
   tot_200x = 0;
   tot_300x = 0;
   tot_100y = 0;
   tot_200y = 0;
   tot_300y = 0;
   htime_100x = 0;
   htime_200x = 0;
   htime_300x = 0;
   htime_100y = 0;
   htime_200y = 0;
   htime_300y = 0;
   ph_100x = 0;
   ph_200x = 0;
   ph_300x = 0;
   ph_100y = 0;
   ph_200y = 0;
   ph_300y = 0;
   hsid_rlx = 0;
   hph_rlx = 0;
   fadc_rlx = 0;
   clc_rlx = 0;
   clcog_rlx = 0;
   clt_rlx = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run_id", &run_id, &b_run_id);
   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("mod_id", &mod_id, &b_mod_id);
   fChain->SetBranchAddress("hitid_ssdx", &hitid_ssdx, &b_hitid_ssdx);
   fChain->SetBranchAddress("hitid_100x", &hitid_100x, &b_hitid_100x);
   fChain->SetBranchAddress("hitid_200x", &hitid_200x, &b_hitid_200x);
   fChain->SetBranchAddress("hitid_300x", &hitid_300x, &b_hitid_300x);
   fChain->SetBranchAddress("hitid_100y", &hitid_100y, &b_hitid_100y);
   fChain->SetBranchAddress("hitid_200y", &hitid_200y, &b_hitid_200y);
   fChain->SetBranchAddress("hitid_300y", &hitid_300y, &b_hitid_300y);
   fChain->SetBranchAddress("g_xssd", &g_xssd, &b_g_xssd);
   fChain->SetBranchAddress("g_zssd", &g_zssd, &b_g_zssd);
   fChain->SetBranchAddress("gc_x100", &gc_x100, &b_gc_x100);
   fChain->SetBranchAddress("gc_y100", &gc_y100, &b_gc_y100);
   fChain->SetBranchAddress("gc_z100", &gc_z100, &b_gc_z100);
   fChain->SetBranchAddress("gc_x200", &gc_x200, &b_gc_x200);
   fChain->SetBranchAddress("gc_y200", &gc_y200, &b_gc_y200);
   fChain->SetBranchAddress("gc_z200", &gc_z200, &b_gc_z200);
   fChain->SetBranchAddress("gc_x300", &gc_x300, &b_gc_x300);
   fChain->SetBranchAddress("gc_y300", &gc_y300, &b_gc_y300);
   fChain->SetBranchAddress("gc_z300", &gc_z300, &b_gc_z300);
   fChain->SetBranchAddress("gt_x100", &gt_x100, &b_gt_x100);
   fChain->SetBranchAddress("gt_y100", &gt_y100, &b_gt_y100);
   fChain->SetBranchAddress("gt_z100", &gt_z100, &b_gt_z100);
   fChain->SetBranchAddress("gt_x200", &gt_x200, &b_gt_x200);
   fChain->SetBranchAddress("gt_y200", &gt_y200, &b_gt_y200);
   fChain->SetBranchAddress("gt_z200", &gt_z200, &b_gt_z200);
   fChain->SetBranchAddress("gt_x300", &gt_x300, &b_gt_x300);
   fChain->SetBranchAddress("gt_y300", &gt_y300, &b_gt_y300);
   fChain->SetBranchAddress("gt_z300", &gt_z300, &b_gt_z300);
   fChain->SetBranchAddress("lxssd", &lxssd, &b_lxssd);
   fChain->SetBranchAddress("lx100", &lx100, &b_lx100);
   fChain->SetBranchAddress("ly100", &ly100, &b_ly100);
   fChain->SetBranchAddress("lx200", &lx200, &b_lx200);
   fChain->SetBranchAddress("ly200", &ly200, &b_ly200);
   fChain->SetBranchAddress("lx300", &lx300, &b_lx300);
   fChain->SetBranchAddress("ly300", &ly300, &b_ly300);
   fChain->SetBranchAddress("clc_xssd", &clc_xssd, &b_clc_xssd);
   fChain->SetBranchAddress("clc_x100", &clc_x100, &b_clc_x100);
   fChain->SetBranchAddress("clc_x200", &clc_x200, &b_clc_x200);
   fChain->SetBranchAddress("clc_x300", &clc_x300, &b_clc_x300);
   fChain->SetBranchAddress("clc_y100", &clc_y100, &b_clc_y100);
   fChain->SetBranchAddress("clc_y200", &clc_y200, &b_clc_y200);
   fChain->SetBranchAddress("clc_y300", &clc_y300, &b_clc_y300);
   fChain->SetBranchAddress("timing_xssd", &timing_xssd, &b_timing_xssd);
   fChain->SetBranchAddress("timing_x100", &timing_x100, &b_timing_x100);
   fChain->SetBranchAddress("timing_x200", &timing_x200, &b_timing_x200);
   fChain->SetBranchAddress("timing_x300", &timing_x300, &b_timing_x300);
   fChain->SetBranchAddress("timing_y100", &timing_y100, &b_timing_y100);
   fChain->SetBranchAddress("timing_y200", &timing_y200, &b_timing_y200);
   fChain->SetBranchAddress("timing_y300", &timing_y300, &b_timing_y300);
   fChain->SetBranchAddress("timing2_x100", &timing2_x100, &b_timing2_x100);
   fChain->SetBranchAddress("timing2_x200", &timing2_x200, &b_timing2_x200);
   fChain->SetBranchAddress("timing2_x300", &timing2_x300, &b_timing2_x300);
   fChain->SetBranchAddress("timing2_y100", &timing2_y100, &b_timing2_y100);
   fChain->SetBranchAddress("timing2_y200", &timing2_y200, &b_timing2_y200);
   fChain->SetBranchAddress("timing2_y300", &timing2_y300, &b_timing2_y300);
   fChain->SetBranchAddress("timing3_x100", &timing3_x100, &b_timing3_x100);
   fChain->SetBranchAddress("timing3_x200", &timing3_x200, &b_timing3_x200);
   fChain->SetBranchAddress("timing3_x300", &timing3_x300, &b_timing3_x300);
   fChain->SetBranchAddress("timing3_y100", &timing3_y100, &b_timing3_y100);
   fChain->SetBranchAddress("timing3_y200", &timing3_y200, &b_timing3_y200);
   fChain->SetBranchAddress("timing3_y300", &timing3_y300, &b_timing3_y300);
   fChain->SetBranchAddress("timing4_x100", &timing4_x100, &b_timing4_x100);
   fChain->SetBranchAddress("timing4_x200", &timing4_x200, &b_timing4_x200);
   fChain->SetBranchAddress("timing4_x300", &timing4_x300, &b_timing4_x300);
   fChain->SetBranchAddress("timing4_y100", &timing4_y100, &b_timing4_y100);
   fChain->SetBranchAddress("timing4_y200", &timing4_y200, &b_timing4_y200);
   fChain->SetBranchAddress("timing4_y300", &timing4_y300, &b_timing4_y300);
   fChain->SetBranchAddress("timing5_x100", &timing5_x100, &b_timing5_x100);
   fChain->SetBranchAddress("timing5_x200", &timing5_x200, &b_timing5_x200);
   fChain->SetBranchAddress("timing5_x300", &timing5_x300, &b_timing5_x300);
   fChain->SetBranchAddress("timing5_y100", &timing5_y100, &b_timing5_y100);
   fChain->SetBranchAddress("timing5_y200", &timing5_y200, &b_timing5_y200);
   fChain->SetBranchAddress("timing5_y300", &timing5_y300, &b_timing5_y300);
   fChain->SetBranchAddress("residual_100x", &residual_100x, &b_residual_100x);
   fChain->SetBranchAddress("residual_200x", &residual_200x, &b_residual_200x);
   fChain->SetBranchAddress("residual_300x", &residual_300x, &b_residual_300x);
   fChain->SetBranchAddress("residual_100y", &residual_100y, &b_residual_100y);
   fChain->SetBranchAddress("residual_200y", &residual_200y, &b_residual_200y);
   fChain->SetBranchAddress("residual_300y", &residual_300y, &b_residual_300y);
   fChain->SetBranchAddress("residual_ssdx", &residual_ssdx, &b_residual_ssdx);
   fChain->SetBranchAddress("fitresidual_100x", &fitresidual_100x, &b_fitresidual_100x);
   fChain->SetBranchAddress("fitresidual_200x", &fitresidual_200x, &b_fitresidual_200x);
   fChain->SetBranchAddress("fitresidual_300x", &fitresidual_300x, &b_fitresidual_300x);
   fChain->SetBranchAddress("fitresidual_100y", &fitresidual_100y, &b_fitresidual_100y);
   fChain->SetBranchAddress("fitresidual_200y", &fitresidual_200y, &b_fitresidual_200y);
   fChain->SetBranchAddress("fitresidual_300y", &fitresidual_300y, &b_fitresidual_300y);
   fChain->SetBranchAddress("fitresidual_ssdx", &fitresidual_ssdx, &b_fitresidual_ssdx);
   fChain->SetBranchAddress("chi2_x", &chi2_x, &b_chi2_x);
   fChain->SetBranchAddress("chi2_y", &chi2_y, &b_chi2_y);
   fChain->SetBranchAddress("tgt_z", &tgt_z, &b_tgt_z);
   fChain->SetBranchAddress("fit_a_x", &fit_a_x, &b_fit_a_x);
   fChain->SetBranchAddress("fit_b_x", &fit_b_x, &b_fit_b_x);
   fChain->SetBranchAddress("fit_a_y", &fit_a_y, &b_fit_a_y);
   fChain->SetBranchAddress("fit_b_y", &fit_b_y, &b_fit_b_y);
   fChain->SetBranchAddress("distance_x", &distance_x, &b_distance_x);
   fChain->SetBranchAddress("distance_fromtgt_y", &distance_fromtgt_y, &b_distance_fromtgt_y);
   fChain->SetBranchAddress("distance_fromupwire_y", &distance_fromupwire_y, &b_distance_fromupwire_y);
   fChain->SetBranchAddress("distance_fromdownwire_y", &distance_fromdownwire_y, &b_distance_fromdownwire_y);
   fChain->SetBranchAddress("fit_g100x", &fit_g100x, &b_fit_g100x);
   fChain->SetBranchAddress("fit_g100y", &fit_g100y, &b_fit_g100y);
   fChain->SetBranchAddress("fit_g100z", &fit_g100z, &b_fit_g100z);
   fChain->SetBranchAddress("fit_g200x", &fit_g200x, &b_fit_g200x);
   fChain->SetBranchAddress("fit_g200y", &fit_g200y, &b_fit_g200y);
   fChain->SetBranchAddress("fit_g200z", &fit_g200z, &b_fit_g200z);
   fChain->SetBranchAddress("fit_g300x", &fit_g300x, &b_fit_g300x);
   fChain->SetBranchAddress("fit_g300y", &fit_g300y, &b_fit_g300y);
   fChain->SetBranchAddress("fit_g300z", &fit_g300z, &b_fit_g300z);
   fChain->SetBranchAddress("hasMatchedASDHit", &hasMatchedASDHit, &b_hasMatchedASDHit);
   fChain->SetBranchAddress("x_trk_used_times", &x_trk_used_times, &b_x_trk_used_times);
   fChain->SetBranchAddress("trkid_x", &trkid_x, &b_trkid_x);
   fChain->SetBranchAddress("trkid_y", &trkid_y, &b_trkid_y);
//    fChain->SetBranchAddress("hitid_ssdx", &hitid_ssdx, &b_hitid_ssdx);
//    fChain->SetBranchAddress("hitid_100x", &hitid_100x, &b_hitid_100x);
//    fChain->SetBranchAddress("hitid_200x", &hitid_200x, &b_hitid_200x);
//    fChain->SetBranchAddress("hitid_300x", &hitid_300x, &b_hitid_300x);
//    fChain->SetBranchAddress("hitid_100y", &hitid_100y, &b_hitid_100y);
//    fChain->SetBranchAddress("hitid_200y", &hitid_200y, &b_hitid_200y);
//    fChain->SetBranchAddress("hitid_300y", &hitid_300y, &b_hitid_300y);
   fChain->SetBranchAddress("cluster_size_ssd", &cluster_size_ssd, &b_cluster_size_ssd);
   fChain->SetBranchAddress("cluster_size_g100x", &cluster_size_g100x, &b_cluster_size_g100x);
   fChain->SetBranchAddress("cluster_size_g200x", &cluster_size_g200x, &b_cluster_size_g200x);
   fChain->SetBranchAddress("cluster_size_g300x", &cluster_size_g300x, &b_cluster_size_g300x);
   fChain->SetBranchAddress("cluster_size_g100y", &cluster_size_g100y, &b_cluster_size_g100y);
   fChain->SetBranchAddress("cluster_size_g200y", &cluster_size_g200y, &b_cluster_size_g200y);
   fChain->SetBranchAddress("cluster_size_g300y", &cluster_size_g300y, &b_cluster_size_g300y);
   fChain->SetBranchAddress("asd_hit", &asd_hit, &b_asd_hit);
   fChain->SetBranchAddress("lg_hit", &lg_hit, &b_lg_hit);
   fChain->SetBranchAddress("lg_cross_pos", &lg_cross_pos, &b_lg_cross_pos);
   fChain->SetBranchAddress("lg_module_id", &lg_module_id, &b_lg_module_id);
   fChain->SetBranchAddress("lg_channel_id", &lg_channel_id, &b_lg_channel_id);
   fChain->SetBranchAddress("timediff_in_cluster_100x", &timediff_in_cluster_100x, &b_timediff_in_cluster_100x);
   fChain->SetBranchAddress("timediff_in_cluster_200x", &timediff_in_cluster_200x, &b_timediff_in_cluster_200x);
   fChain->SetBranchAddress("timediff_in_cluster_300x", &timediff_in_cluster_300x, &b_timediff_in_cluster_300x);
   fChain->SetBranchAddress("timings_100x", &timings_100x, &b_timings_100x);
   fChain->SetBranchAddress("timings_200x", &timings_200x, &b_timings_200x);
   fChain->SetBranchAddress("timings_300x", &timings_300x, &b_timings_300x);
   fChain->SetBranchAddress("positions_100x", &positions_100x, &b_positions_100x);
   fChain->SetBranchAddress("positions_200x", &positions_200x, &b_positions_200x);
   fChain->SetBranchAddress("positions_300x", &positions_300x, &b_positions_300x);
   fChain->SetBranchAddress("asd_hits", &asd_hits, &b_asd_hits);
   fChain->SetBranchAddress("fadc_100x", &fadc_100x, &b_fadc_100x);
   fChain->SetBranchAddress("fadc_200x", &fadc_200x, &b_fadc_200x);
   fChain->SetBranchAddress("fadc_300x", &fadc_300x, &b_fadc_300x);
   fChain->SetBranchAddress("fadc_100y", &fadc_100y, &b_fadc_100y);
   fChain->SetBranchAddress("fadc_200y", &fadc_200y, &b_fadc_200y);
   fChain->SetBranchAddress("fadc_300y", &fadc_300y, &b_fadc_300y);
   fChain->SetBranchAddress("sid_100x", &sid_100x, &b_sid_100x);
   fChain->SetBranchAddress("sid_200x", &sid_200x, &b_sid_200x);
   fChain->SetBranchAddress("sid_300x", &sid_300x, &b_sid_300x);
   fChain->SetBranchAddress("sid_100y", &sid_100y, &b_sid_100y);
   fChain->SetBranchAddress("sid_200y", &sid_200y, &b_sid_200y);
   fChain->SetBranchAddress("sid_300y", &sid_300y, &b_sid_300y);
   fChain->SetBranchAddress("tot_100x", &tot_100x, &b_tot_100x);
   fChain->SetBranchAddress("tot_200x", &tot_200x, &b_tot_200x);
   fChain->SetBranchAddress("tot_300x", &tot_300x, &b_tot_300x);
   fChain->SetBranchAddress("tot_100y", &tot_100y, &b_tot_100y);
   fChain->SetBranchAddress("tot_200y", &tot_200y, &b_tot_200y);
   fChain->SetBranchAddress("tot_300y", &tot_300y, &b_tot_300y);
   fChain->SetBranchAddress("htime_100x", &htime_100x, &b_htime_100x);
   fChain->SetBranchAddress("htime_200x", &htime_200x, &b_htime_200x);
   fChain->SetBranchAddress("htime_300x", &htime_300x, &b_htime_300x);
   fChain->SetBranchAddress("htime_100y", &htime_100y, &b_htime_100y);
   fChain->SetBranchAddress("htime_200y", &htime_200y, &b_htime_200y);
   fChain->SetBranchAddress("htime_300y", &htime_300y, &b_htime_300y);
   fChain->SetBranchAddress("ph_100x", &ph_100x, &b_ph_100x);
   fChain->SetBranchAddress("ph_200x", &ph_200x, &b_ph_200x);
   fChain->SetBranchAddress("ph_300x", &ph_300x, &b_ph_300x);
   fChain->SetBranchAddress("ph_100y", &ph_100y, &b_ph_100y);
   fChain->SetBranchAddress("ph_200y", &ph_200y, &b_ph_200y);
   fChain->SetBranchAddress("ph_300y", &ph_300y, &b_ph_300y);
   fChain->SetBranchAddress("hsid_rlx", &hsid_rlx, &b_hsid_rlx);
   fChain->SetBranchAddress("hph_rlx", &hph_rlx, &b_hph_rlx);
   fChain->SetBranchAddress("fadc_rlx", &fadc_rlx, &b_fadc_rlx);
   fChain->SetBranchAddress("clc_rlx", &clc_rlx, &b_clc_rlx);
   fChain->SetBranchAddress("clcog_rlx", &clcog_rlx, &b_clcog_rlx);
   fChain->SetBranchAddress("clt_rlx", &clt_rlx, &b_clt_rlx);
   Notify();
}

Bool_t straightRoot::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void straightRoot::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t straightRoot::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef straightRoot_cxx
