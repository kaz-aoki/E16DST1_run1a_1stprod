//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar 20 10:12:57 2023 by ROOT version 6.18/04
// from TTree tree/tree
// found on file: test.root
//////////////////////////////////////////////////////////

#ifndef E16ANA_LGGainCalibwoTrackRoot_h
#define E16ANA_LGGainCalibwoTrackRoot_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
using namespace std;
#include <stdio.h>
#include <iostream>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class E16ANA_LGGainCalibwoTrackRoot {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run_id;
   Int_t           event_id;
   Int_t           spill_id;
   Int_t           run_purpose;
   Int_t           lg_mid;
   Int_t           lg_cid;
   Double_t        lg_adc;
   Double_t        lg_t;
   Double_t        lg_leftside_adc;
   Double_t        lg_leftside_t;
   Double_t        lg_rightside_adc;
   Double_t        lg_rightside_t;
   Int_t           lg_trg_hit;
   Bool_t          lg_trg_trk;
   Bool_t          lg_trg_run;
   Int_t           lg_multi_ev;
   Int_t           lg_multi_mod;
   Int_t           n_hbds;
   Double_t        hbd_cx;
   Double_t        hbd_cy;
   Double_t        hbd_nearest_adc;
   Double_t        hbd_nearest_t;
   Double_t        hbd_nearest_lx;
   Double_t        hbd_nearest_ly;
   vector<double>  *hbd_adc;
   vector<double>  *hbd_t;
   vector<double>  *hbd_lx;
   vector<double>  *hbd_ly;
   Int_t           n_ssds;
   Double_t        ssd_cx;
   Double_t        ssd_nearest_adc;
   Double_t        ssd_nearest_t;
   Double_t        ssd_nearest_lx;
   vector<double>  *ssd_adc;
   vector<double>  *ssd_t;
   vector<double>  *ssd_lx;
   Int_t           n_gtr100xs;
   Double_t        gtr100x_cx;
   Double_t        gtr100x_nearest_adc;
   Double_t        gtr100x_nearest_t;
   Double_t        gtr100x_nearest_lx;
   vector<double>  *gtr100x_adc;
   vector<double>  *gtr100x_t;
   vector<double>  *gtr100x_lx;
   Int_t           n_gtr200xs;
   Double_t        gtr200x_cx;
   Double_t        gtr200x_nearest_adc;
   Double_t        gtr200x_nearest_t;
   Double_t        gtr200x_nearest_lx;
   vector<double>  *gtr200x_adc;
   vector<double>  *gtr200x_t;
   vector<double>  *gtr200x_lx;
   Int_t           n_gtr300xs;
   Double_t        gtr300x_cx;
   Double_t        gtr300x_nearest_adc;
   Double_t        gtr300x_nearest_t;
   Double_t        gtr300x_nearest_lx;
   vector<double>  *gtr300x_adc;
   vector<double>  *gtr300x_t;
   vector<double>  *gtr300x_lx;
   Int_t           n_gtr100ys;
   Double_t        gtr100y_cy;
   Double_t        gtr100y_nearest_adc;
   Double_t        gtr100y_nearest_t;
   Double_t        gtr100y_nearest_ly;
   vector<double>  *gtr100y_adc;
   vector<double>  *gtr100y_t;
   vector<double>  *gtr100y_ly;
   Int_t           n_gtr200ys;
   Double_t        gtr200y_cy;
   Double_t        gtr200y_nearest_adc;
   Double_t        gtr200y_nearest_t;
   Double_t        gtr200y_nearest_ly;
   vector<double>  *gtr200y_adc;
   vector<double>  *gtr200y_t;
   vector<double>  *gtr200y_ly;
   Int_t           n_gtr300ys;
   Double_t        gtr300y_cy;
   Double_t        gtr300y_nearest_adc;
   Double_t        gtr300y_nearest_t;
   Double_t        gtr300y_nearest_ly;
   vector<double>  *gtr300y_adc;
   vector<double>  *gtr300y_t;
   vector<double>  *gtr300y_ly;
   Int_t           n_lg_cids;
   vector<int>     *lg_cids;
   vector<double>  *lg_adcs;
   Int_t           gtr_mid;
   Int_t           n_gtr300x_lxs;
   vector<double>  *gtr300x_lxs;
   Int_t           n_gtr300y_lys;
   vector<double>  *gtr300y_lys;
   Int_t           n_gtr200x_lxs;
   vector<double>  *gtr200x_lxs;
   Int_t           n_gtr200y_lys;
   vector<double>  *gtr200y_lys;
   Int_t           n_gtr100x_lxs;
   vector<double>  *gtr100x_lxs;
   Int_t           n_gtr100y_lys;
   vector<double>  *gtr100y_lys;

   // List of branches
   TBranch        *b_run_id;   //!
   TBranch        *b_event_id;   //!
   TBranch        *b_spill_id;   //!
   TBranch        *b_run_purpose;   //!
   TBranch        *b_lg_mid;   //!
   TBranch        *b_lg_cid;   //!
   TBranch        *b_lg_adc;   //!
   TBranch        *b_lg_t;   //!
   TBranch        *b_lg_leftside_adc;   //!
   TBranch        *b_lg_leftside_t;   //!
   TBranch        *b_lg_rightside_adc;   //!
   TBranch        *b_lg_rightside_t;   //!
   TBranch        *b_lg_trg_hit;   //!
   TBranch        *b_lg_trg_trk;   //!
   TBranch        *b_lg_trg_run;   //!
   TBranch        *b_lg_multi_ev;   //!
   TBranch        *b_lg_multi_mod;   //!
   TBranch        *b_n_hbds;   //!
   TBranch        *b_out_hbd_cx;   //!
   TBranch        *b_out_hbd_cy;   //!
   TBranch        *b_out_hbd_nearest_adc;   //!
   TBranch        *b_out_hbd_nearest_t;   //!
   TBranch        *b_out_hbd_nearest_lx;   //!
   TBranch        *b_out_hbd_nearest_ly;   //!
   TBranch        *b_hbd_adc;   //!
   TBranch        *b_hbd_t;   //!
   TBranch        *b_hbd_lx;   //!
   TBranch        *b_hbd_ly;   //!
   TBranch        *b_n_ssds;   //!
   TBranch        *b_out_ssd_cx;   //!
   TBranch        *b_out_ssd_nearest_adc;   //!
   TBranch        *b_out_ssd_nearest_t;   //!
   TBranch        *b_out_ssd_nearest_lx;   //!
   TBranch        *b_ssd_adc;   //!
   TBranch        *b_ssd_t;   //!
   TBranch        *b_ssd_lx;   //!
   TBranch        *b_n_gtr100xs;   //!
   TBranch        *b_out_gtr100x_cx;   //!
   TBranch        *b_out_gtr100x_nearest_adc;   //!
   TBranch        *b_out_gtr100x_nearest_t;   //!
   TBranch        *b_out_gtr100x_nearest_lx;   //!
   TBranch        *b_gtr100x_adc;   //!
   TBranch        *b_gtr100x_t;   //!
   TBranch        *b_gtr100x_lx;   //!
   TBranch        *b_n_gtr200xs;   //!
   TBranch        *b_out_gtr200x_cx;   //!
   TBranch        *b_out_gtr200x_nearest_adc;   //!
   TBranch        *b_out_gtr200x_nearest_t;   //!
   TBranch        *b_out_gtr200x_nearest_lx;   //!
   TBranch        *b_gtr200x_adc;   //!
   TBranch        *b_gtr200x_t;   //!
   TBranch        *b_gtr200x_lx;   //!
   TBranch        *b_n_gtr300xs;   //!
   TBranch        *b_out_gtr300x_cx;   //!
   TBranch        *b_out_gtr300x_nearest_adc;   //!
   TBranch        *b_out_gtr300x_nearest_t;   //!
   TBranch        *b_out_gtr300x_nearest_lx;   //!
   TBranch        *b_gtr300x_adc;   //!
   TBranch        *b_gtr300x_t;   //!
   TBranch        *b_gtr300x_lx;   //!
   TBranch        *b_n_gtr100ys;   //!
   TBranch        *b_out_gtr100y_cy;   //!
   TBranch        *b_out_gtr100y_nearest_adc;   //!
   TBranch        *b_out_gtr100y_nearest_t;   //!
   TBranch        *b_out_gtr100y_nearest_ly;   //!
   TBranch        *b_gtr100y_adc;   //!
   TBranch        *b_gtr100y_t;   //!
   TBranch        *b_gtr100y_ly;   //!
   TBranch        *b_n_gtr200ys;   //!
   TBranch        *b_out_gtr200y_cy;   //!
   TBranch        *b_out_gtr200y_nearest_adc;   //!
   TBranch        *b_out_gtr200y_nearest_t;   //!
   TBranch        *b_out_gtr200y_nearest_ly;   //!
   TBranch        *b_gtr200y_adc;   //!
   TBranch        *b_gtr200y_t;   //!
   TBranch        *b_gtr200y_ly;   //!
   TBranch        *b_n_gtr300ys;   //!
   TBranch        *b_out_gtr300y_cy;   //!
   TBranch        *b_out_gtr300y_nearest_adc;   //!
   TBranch        *b_out_gtr300y_nearest_t;   //!
   TBranch        *b_out_gtr300y_nearest_ly;   //!
   TBranch        *b_gtr300y_adc;   //!
   TBranch        *b_gtr300y_t;   //!
   TBranch        *b_gtr300y_ly;   //!
   TBranch        *b_n_lg_cids;   //!
   TBranch        *b_lg_cids;   //!
   TBranch        *b_lg_adcs;   //!
   TBranch        *b_gtr_mid;   //!
   TBranch        *b_n_gtr300x_lxs;   //!
   TBranch        *b_gtr300x_lxs;   //!
   TBranch        *b_n_gtr300y_lys;   //!
   TBranch        *b_gtr300y_lys;   //!
   TBranch        *b_n_gtr200x_lxs;   //!
   TBranch        *b_gtr200x_lxs;   //!
   TBranch        *b_n_gtr200y_lys;   //!
   TBranch        *b_gtr200y_lys;   //!
   TBranch        *b_n_gtr100x_lxs;   //!
   TBranch        *b_gtr100x_lxs;   //!
   TBranch        *b_n_gtr100y_lys;   //!
   TBranch        *b_gtr100y_lys;   //!

   E16ANA_LGGainCalibwoTrackRoot(TTree *tree=0);
   virtual ~E16ANA_LGGainCalibwoTrackRoot();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    TrackSelection(Long64_t entry);
   virtual bool     ClsMatchingGTR(Long64_t entry, int lid);
   virtual void     SetAllCls(Long64_t entry, int lid, double& cx, double& cy, std::vector<double>& lxs, std::vector<double>& lys);
   virtual void     SetAllCls(Long64_t entry, int lid, double& cy, std::vector<double>& lys);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual void     ResidualforLGmix(char* out_file_name, int maxevent);
   virtual void     ResidualforGTRymix(int lid, char* out_file_name, int maxevent);
   // virtual void     ResidualforGTRxmix(int lid, char* out_file_name, int maxevent);
   virtual void     LGADCLGmix(char* out_file_name, int maxevent);
   virtual void     LGADCGTRymix(int lid, char* out_file_name, int maxevent);
   // virtual void     LGADCGTRxmix(int lid, char* out_file_name, int maxevent);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef E16ANA_LGGainCalibwoTrackRoot_cxx
E16ANA_LGGainCalibwoTrackRoot::E16ANA_LGGainCalibwoTrackRoot(TTree *tree) : fChain(0) 
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

E16ANA_LGGainCalibwoTrackRoot::~E16ANA_LGGainCalibwoTrackRoot()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t E16ANA_LGGainCalibwoTrackRoot::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t E16ANA_LGGainCalibwoTrackRoot::LoadTree(Long64_t entry)
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

void E16ANA_LGGainCalibwoTrackRoot::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   hbd_adc = 0;
   hbd_t = 0;
   hbd_lx = 0;
   hbd_ly = 0;
   ssd_adc = 0;
   ssd_t = 0;
   ssd_lx = 0;
   gtr100x_adc = 0;
   gtr100x_t = 0;
   gtr100x_lx = 0;
   gtr200x_adc = 0;
   gtr200x_t = 0;
   gtr200x_lx = 0;
   gtr300x_adc = 0;
   gtr300x_t = 0;
   gtr300x_lx = 0;
   gtr100y_adc = 0;
   gtr100y_t = 0;
   gtr100y_ly = 0;
   gtr200y_adc = 0;
   gtr200y_t = 0;
   gtr200y_ly = 0;
   gtr300y_adc = 0;
   gtr300y_t = 0;
   gtr300y_ly = 0;
   lg_cids = 0;
   lg_adcs = 0;
   gtr300x_lxs = 0;
   gtr300y_lys = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run_id", &run_id, &b_run_id);
   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("spill_id", &spill_id, &b_spill_id);
   fChain->SetBranchAddress("run_purpose", &run_purpose, &b_run_purpose);
   fChain->SetBranchAddress("lg_mid", &lg_mid, &b_lg_mid);
   fChain->SetBranchAddress("lg_cid", &lg_cid, &b_lg_cid);
   fChain->SetBranchAddress("lg_adc", &lg_adc, &b_lg_adc);
   fChain->SetBranchAddress("lg_t", &lg_t, &b_lg_t);
   fChain->SetBranchAddress("lg_leftside_adc", &lg_leftside_adc, &b_lg_leftside_adc);
   fChain->SetBranchAddress("lg_leftside_t", &lg_leftside_t, &b_lg_leftside_t);
   fChain->SetBranchAddress("lg_rightside_adc", &lg_rightside_adc, &b_lg_rightside_adc);
   fChain->SetBranchAddress("lg_rightside_t", &lg_rightside_t, &b_lg_rightside_t);
   fChain->SetBranchAddress("lg_trg_hit", &lg_trg_hit, &b_lg_trg_hit);
   fChain->SetBranchAddress("lg_trg_trk", &lg_trg_trk, &b_lg_trg_trk);
   fChain->SetBranchAddress("lg_trg_run", &lg_trg_run, &b_lg_trg_run);
   fChain->SetBranchAddress("lg_multi_ev", &lg_multi_ev, &b_lg_multi_ev);
   fChain->SetBranchAddress("lg_multi_mod", &lg_multi_mod, &b_lg_multi_mod);
   fChain->SetBranchAddress("n_hbds", &n_hbds, &b_n_hbds);
   fChain->SetBranchAddress("hbd_cx", &hbd_cx, &b_out_hbd_cx);
   fChain->SetBranchAddress("hbd_cy", &hbd_cy, &b_out_hbd_cy);
   fChain->SetBranchAddress("hbd_nearest_adc", &hbd_nearest_adc, &b_out_hbd_nearest_adc);
   fChain->SetBranchAddress("hbd_nearest_t", &hbd_nearest_t, &b_out_hbd_nearest_t);
   fChain->SetBranchAddress("hbd_nearest_lx", &hbd_nearest_lx, &b_out_hbd_nearest_lx);
   fChain->SetBranchAddress("hbd_nearest_ly", &hbd_nearest_ly, &b_out_hbd_nearest_ly);
   fChain->SetBranchAddress("hbd_adc", &hbd_adc, &b_hbd_adc);
   fChain->SetBranchAddress("hbd_t", &hbd_t, &b_hbd_t);
   fChain->SetBranchAddress("hbd_lx", &hbd_lx, &b_hbd_lx);
   fChain->SetBranchAddress("hbd_ly", &hbd_ly, &b_hbd_ly);
   fChain->SetBranchAddress("n_ssds", &n_ssds, &b_n_ssds);
   fChain->SetBranchAddress("ssd_cx", &ssd_cx, &b_out_ssd_cx);
   fChain->SetBranchAddress("ssd_nearest_adc", &ssd_nearest_adc, &b_out_ssd_nearest_adc);
   fChain->SetBranchAddress("ssd_nearest_t", &ssd_nearest_t, &b_out_ssd_nearest_t);
   fChain->SetBranchAddress("ssd_nearest_lx", &ssd_nearest_lx, &b_out_ssd_nearest_lx);
   fChain->SetBranchAddress("ssd_adc", &ssd_adc, &b_ssd_adc);
   fChain->SetBranchAddress("ssd_t", &ssd_t, &b_ssd_t);
   fChain->SetBranchAddress("ssd_lx", &ssd_lx, &b_ssd_lx);
   fChain->SetBranchAddress("n_gtr100xs", &n_gtr100xs, &b_n_gtr100xs);
   fChain->SetBranchAddress("gtr100x_cx", &gtr100x_cx, &b_out_gtr100x_cx);
   fChain->SetBranchAddress("gtr100x_nearest_adc", &gtr100x_nearest_adc, &b_out_gtr100x_nearest_adc);
   fChain->SetBranchAddress("gtr100x_nearest_t", &gtr100x_nearest_t, &b_out_gtr100x_nearest_t);
   fChain->SetBranchAddress("gtr100x_nearest_lx", &gtr100x_nearest_lx, &b_out_gtr100x_nearest_lx);
   fChain->SetBranchAddress("gtr100x_adc", &gtr100x_adc, &b_gtr100x_adc);
   fChain->SetBranchAddress("gtr100x_t", &gtr100x_t, &b_gtr100x_t);
   fChain->SetBranchAddress("gtr100x_lx", &gtr100x_lx, &b_gtr100x_lx);
   fChain->SetBranchAddress("n_gtr200xs", &n_gtr200xs, &b_n_gtr200xs);
   fChain->SetBranchAddress("gtr200x_cx", &gtr200x_cx, &b_out_gtr200x_cx);
   fChain->SetBranchAddress("gtr200x_nearest_adc", &gtr200x_nearest_adc, &b_out_gtr200x_nearest_adc);
   fChain->SetBranchAddress("gtr200x_nearest_t", &gtr200x_nearest_t, &b_out_gtr200x_nearest_t);
   fChain->SetBranchAddress("gtr200x_nearest_lx", &gtr200x_nearest_lx, &b_out_gtr200x_nearest_lx);
   fChain->SetBranchAddress("gtr200x_adc", &gtr200x_adc, &b_gtr200x_adc);
   fChain->SetBranchAddress("gtr200x_t", &gtr200x_t, &b_gtr200x_t);
   fChain->SetBranchAddress("gtr200x_lx", &gtr200x_lx, &b_gtr200x_lx);
   fChain->SetBranchAddress("n_gtr300xs", &n_gtr300xs, &b_n_gtr300xs);
   fChain->SetBranchAddress("gtr300x_cx", &gtr300x_cx, &b_out_gtr300x_cx);
   fChain->SetBranchAddress("gtr300x_nearest_adc", &gtr300x_nearest_adc, &b_out_gtr300x_nearest_adc);
   fChain->SetBranchAddress("gtr300x_nearest_t", &gtr300x_nearest_t, &b_out_gtr300x_nearest_t);
   fChain->SetBranchAddress("gtr300x_nearest_lx", &gtr300x_nearest_lx, &b_out_gtr300x_nearest_lx);
   fChain->SetBranchAddress("gtr300x_adc", &gtr300x_adc, &b_gtr300x_adc);
   fChain->SetBranchAddress("gtr300x_t", &gtr300x_t, &b_gtr300x_t);
   fChain->SetBranchAddress("gtr300x_lx", &gtr300x_lx, &b_gtr300x_lx);
   fChain->SetBranchAddress("n_gtr100ys", &n_gtr100ys, &b_n_gtr100ys);
   fChain->SetBranchAddress("gtr100y_cy", &gtr100y_cy, &b_out_gtr100y_cy);
   fChain->SetBranchAddress("gtr100y_nearest_adc", &gtr100y_nearest_adc, &b_out_gtr100y_nearest_adc);
   fChain->SetBranchAddress("gtr100y_nearest_t", &gtr100y_nearest_t, &b_out_gtr100y_nearest_t);
   fChain->SetBranchAddress("gtr100y_nearest_ly", &gtr100y_nearest_ly, &b_out_gtr100y_nearest_ly);
   fChain->SetBranchAddress("gtr100y_adc", &gtr100y_adc, &b_gtr100y_adc);
   fChain->SetBranchAddress("gtr100y_t", &gtr100y_t, &b_gtr100y_t);
   fChain->SetBranchAddress("gtr100y_ly", &gtr100y_ly, &b_gtr100y_ly);
   fChain->SetBranchAddress("n_gtr200ys", &n_gtr200ys, &b_n_gtr200ys);
   fChain->SetBranchAddress("gtr200y_cy", &gtr200y_cy, &b_out_gtr200y_cy);
   fChain->SetBranchAddress("gtr200y_nearest_adc", &gtr200y_nearest_adc, &b_out_gtr200y_nearest_adc);
   fChain->SetBranchAddress("gtr200y_nearest_t", &gtr200y_nearest_t, &b_out_gtr200y_nearest_t);
   fChain->SetBranchAddress("gtr200y_nearest_ly", &gtr200y_nearest_ly, &b_out_gtr200y_nearest_ly);
   fChain->SetBranchAddress("gtr200y_adc", &gtr200y_adc, &b_gtr200y_adc);
   fChain->SetBranchAddress("gtr200y_t", &gtr200y_t, &b_gtr200y_t);
   fChain->SetBranchAddress("gtr200y_ly", &gtr200y_ly, &b_gtr200y_ly);
   fChain->SetBranchAddress("n_gtr300ys", &n_gtr300ys, &b_n_gtr300ys);
   fChain->SetBranchAddress("gtr300y_cy", &gtr300y_cy, &b_out_gtr300y_cy);
   fChain->SetBranchAddress("gtr300y_nearest_adc", &gtr300y_nearest_adc, &b_out_gtr300y_nearest_adc);
   fChain->SetBranchAddress("gtr300y_nearest_t", &gtr300y_nearest_t, &b_out_gtr300y_nearest_t);
   fChain->SetBranchAddress("gtr300y_nearest_ly", &gtr300y_nearest_ly, &b_out_gtr300y_nearest_ly);
   fChain->SetBranchAddress("gtr300y_adc", &gtr300y_adc, &b_gtr300y_adc);
   fChain->SetBranchAddress("gtr300y_t", &gtr300y_t, &b_gtr300y_t);
   fChain->SetBranchAddress("gtr300y_ly", &gtr300y_ly, &b_gtr300y_ly);
   fChain->SetBranchAddress("n_lg_cids", &n_lg_cids, &b_n_lg_cids);
   fChain->SetBranchAddress("lg_cids", &lg_cids, &b_lg_cids);
   fChain->SetBranchAddress("lg_adcs", &lg_adcs, &b_lg_adcs);
   fChain->SetBranchAddress("gtr_mid", &gtr_mid, &b_gtr_mid);
   fChain->SetBranchAddress("n_gtr300x_lxs", &n_gtr300x_lxs, &b_n_gtr300x_lxs);
   fChain->SetBranchAddress("gtr300x_lxs", &gtr300x_lxs, &b_gtr300x_lxs);
   fChain->SetBranchAddress("n_gtr300y_lys", &n_gtr300y_lys, &b_n_gtr300y_lys);
   fChain->SetBranchAddress("gtr300y_lys", &gtr300y_lys, &b_gtr300y_lys);
   fChain->SetBranchAddress("n_gtr200x_lxs", &n_gtr200x_lxs, &b_n_gtr200x_lxs);
   fChain->SetBranchAddress("gtr200x_lxs", &gtr200x_lxs, &b_gtr200x_lxs);
   fChain->SetBranchAddress("n_gtr200y_lys", &n_gtr200y_lys, &b_n_gtr200y_lys);
   fChain->SetBranchAddress("gtr200y_lys", &gtr200y_lys, &b_gtr200y_lys);
   fChain->SetBranchAddress("n_gtr100x_lxs", &n_gtr100x_lxs, &b_n_gtr100x_lxs);
   fChain->SetBranchAddress("gtr100x_lxs", &gtr100x_lxs, &b_gtr100x_lxs);
   fChain->SetBranchAddress("n_gtr100y_lys", &n_gtr100y_lys, &b_n_gtr100y_lys);
   fChain->SetBranchAddress("gtr100y_lys", &gtr100y_lys, &b_gtr100y_lys);
   Notify();
}

Bool_t E16ANA_LGGainCalibwoTrackRoot::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void E16ANA_LGGainCalibwoTrackRoot::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t E16ANA_LGGainCalibwoTrackRoot::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
Int_t E16ANA_LGGainCalibwoTrackRoot::TrackSelection(Long64_t entry)
{
  if( lg_trg_run ){return -1;}
  // if( (lg_mid-105)<0 && lg_rightside_adc>-100 ){return -1;}
  // if( (lg_mid-105)>0 && lg_leftside_adc>-100 ){return -1;}
  if( lg_adc<-100 ){return -1;}
  // if( !ClsMatchingGTR(entry,2) ){return -1;}
  // if( !ClsMatchingGTR(entry,1) ){return -1;}
  // if( !ClsMatchingGTR(entry,0) ){return -1;}
  // if( n_gtr300ys==0 ){return -1;}
  // if( n_gtr200ys==0 ){return -1;}
  // if( n_gtr100ys==0 ){return -1;}
  else{return 1;}
}
bool E16ANA_LGGainCalibwoTrackRoot::ClsMatchingGTR(Long64_t entry, int lid)
{
  bool ret = false;
  int nxs, nys;
  std::vector<double>* vxt;
  std::vector<double>* vxa;
  std::vector<double>* vyt;
  std::vector<double>* vya;
  if( lid==0 ){
    nxs = n_gtr100xs;
    nys = n_gtr100ys;
    vxt = gtr100x_t;
    vxa = gtr100x_adc;
    vyt = gtr100y_t;
    vya = gtr100y_adc;
  }
  else if( lid==1 ){
    nxs = n_gtr200xs;
    nys = n_gtr200ys;
    vxt = gtr200x_t;
    vxa = gtr200x_adc;
    vyt = gtr200y_t;
    vya = gtr200y_adc;
  }
  else if( lid==2 ){
    nxs = n_gtr300xs;
    nys = n_gtr300ys;
    vxt = gtr300x_t;
    vxa = gtr300x_adc;
    vyt = gtr300y_t;
    vya = gtr300y_adc;
  }

  for(int ix=0;ix<nxs;ix++){
    for(int iy=0;iy<nys;iy++){
      double xt = vxt->at(ix);
      double xa = vxa->at(ix);
      double yt = vyt->at(iy);
      double ya = vya->at(iy);
      if( fabs(xt-yt)<60 ){//timing match
	if( ya < 0.74*xa+1000. && ( ya > 0.74*xa-1000. || ya > 1200.) ){//adc linearity
	  ret = true;
	  break;
	}
      }
    }
  }
  return ret;
}
void E16ANA_LGGainCalibwoTrackRoot::SetAllCls(Long64_t entry, int lid, double& cx, double& cy, std::vector<double>& lxs, std::vector<double>& lys)
{
  if(lid==0){
    cx = gtr100x_cx;
    cy = gtr100y_cy;
    lxs.resize( gtr100x_lxs->size() );
    copy( gtr100x_lxs->begin(), gtr100x_lxs->end(), lxs.begin() );
    lys.resize( gtr100y_lys->size() );
    copy( gtr100y_lys->begin(), gtr100y_lys->end(), lys.begin() );
  }
  else if(lid==1){
    cx = gtr200x_cx;
    cy = gtr200y_cy;
    lxs.resize( gtr200x_lxs->size() );
    copy( gtr200x_lxs->begin(), gtr200x_lxs->end(), lxs.begin() );
    lys.resize( gtr200y_lys->size() );
    copy( gtr200y_lys->begin(), gtr200y_lys->end(), lys.begin() );
  }
  else if(lid==2){
    cx = gtr300x_cx;
    cy = gtr300y_cy;
    lxs.resize( gtr300x_lxs->size() );
    copy( gtr300x_lxs->begin(), gtr300x_lxs->end(), lxs.begin() );
    lys.resize( gtr300y_lys->size() );
    copy( gtr300y_lys->begin(), gtr300y_lys->end(), lys.begin() );
  }
}
void E16ANA_LGGainCalibwoTrackRoot::SetAllCls(Long64_t entry, int lid, double& cy, std::vector<double>& lys)
{
  if(lid==0){
    cy = gtr100y_cy;
    lys.resize( gtr100y_lys->size() );
    copy( gtr100y_lys->begin(), gtr100y_lys->end(), lys.begin() );
  }
  else if(lid==1){
    cy = gtr200y_cy;
    lys.resize( gtr200y_lys->size() );
    copy( gtr200y_lys->begin(), gtr200y_lys->end(), lys.begin() );
  }
  else if(lid==2){
    cy = gtr300y_cy;
    lys.resize( gtr300y_lys->size() );
    copy( gtr300y_lys->begin(), gtr300y_lys->end(), lys.begin() );
  }
}
#endif // #ifdef E16ANA_LGGainCalibwoTrackRoot_cxx
