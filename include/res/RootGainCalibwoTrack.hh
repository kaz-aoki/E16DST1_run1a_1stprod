//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Feb 21 22:12:18 2023 by ROOT version 6.18/04
// from TTree tree/tree
// found on file: /ccj/w/r01/nakasuga/output/dst1ana/wotrack/lsf/calibwotrack_run020908.root
//////////////////////////////////////////////////////////

#ifndef RootGainCalibwoTrack_h
#define RootGainCalibwoTrack_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
using namespace std;

// Header file for the classes stored in the TTree if any.
#include "vector"

class RootGainCalibwoTrack {
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

   RootGainCalibwoTrack(TTree *tree=0);
   virtual ~RootGainCalibwoTrack();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    TrackSelection(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual void     Residual();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef RootGainCalibwoTrack_cxx
RootGainCalibwoTrack::RootGainCalibwoTrack(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/ccj/w/r01/nakasuga/output/dst1ana/wotrack/lsf/calibwotrack_run020908.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/ccj/w/r01/nakasuga/output/dst1ana/wotrack/lsf/calibwotrack_run020908.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

RootGainCalibwoTrack::~RootGainCalibwoTrack()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t RootGainCalibwoTrack::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t RootGainCalibwoTrack::LoadTree(Long64_t entry)
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

void RootGainCalibwoTrack::Init(TTree *tree)
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
   Notify();
}

Bool_t RootGainCalibwoTrack::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void RootGainCalibwoTrack::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t RootGainCalibwoTrack::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
Int_t RootGainCalibwoTrack::TrackSelection(Long64_t entry)
{
  if( lg_trg_run ){return -1;}
  if( n_hbds==0 ){return -1;}
  // if( (lg_mid-105)<0 && lg_rightside_adc>-100 ){return -1;}
  // if( (lg_mid-105)>0 && lg_leftside_adc>-100 ){return -1;}
  if( n_gtr300xs<0 || n_gtr300ys<0 ){return -1;}
  else{return 1;}
}
#endif // #ifdef RootGainCalibwoTrack_cxx
