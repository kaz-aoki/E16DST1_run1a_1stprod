//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jun 20 16:40:34 2022 by ROOT version 6.18/04
// from TTree tree/tree
// found on file: /ccj/w/data06a/E16/user/ichikawa/tmp/tmpmock2000.root
//////////////////////////////////////////////////////////

#ifndef tmp_fit_mock_pair_from_dst1_drawer_220620_h
#define tmp_fit_mock_pair_from_dst1_drawer_220620_h

#include <array>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>

// Header file for the classes stored in the TTree if any.
#include "TVector3.h"
#include "TH2.h"

class tmp_fit_mock_pair_from_dst1_drawer_220620 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run_id;
   Int_t           event_id;
   Int_t           plus_ssd_mid;
   Int_t           plus_gtr100_mid;
   Int_t           plus_gtr200_mid;
   Int_t           plus_gtr300_mid;
   TVector3        *plus_ssd_lpos;
   TVector3        *plus_gtr100_lpos;
   TVector3        *plus_gtr200_lpos;
   TVector3        *plus_gtr300_lpos;
   Int_t           minus_ssd_mid;
   Int_t           minus_gtr100_mid;
   Int_t           minus_gtr200_mid;
   Int_t           minus_gtr300_mid;
   TVector3        *minus_ssd_lpos;
   TVector3        *minus_gtr100_lpos;
   TVector3        *minus_gtr200_lpos;
   TVector3        *minus_gtr300_lpos;
   TVector3        *mock_vtx;
   TVector3        *mock_plus_init_mom;
   TVector3        *mock_plus_ssd_lpos;
   TVector3        *mock_plus_gtr100_lpos;
   TVector3        *mock_plus_gtr200_lpos;
   TVector3        *mock_plus_gtr300_lpos;
   TVector3        *mock_minus_init_mom;
   TVector3        *mock_minus_ssd_lpos;
   TVector3        *mock_minus_gtr100_lpos;
   TVector3        *mock_minus_gtr200_lpos;
   TVector3        *mock_minus_gtr300_lpos;
   Double_t        mock_mass;
   Double_t        pre_fit_plus_chi2;
   TVector3        *pre_fit_plus_init_mom;
   TVector3        *pre_fit_plus_init_pos;
   TVector3        *pre_fit_plus_ssd_lpos;
   TVector3        *pre_fit_plus_gtr100_lpos;
   TVector3        *pre_fit_plus_gtr200_lpos;
   TVector3        *pre_fit_plus_gtr300_lpos;
   Double_t        pre_fit_minus_chi2;
   TVector3        *pre_fit_minus_init_mom;
   TVector3        *pre_fit_minus_init_pos;
   TVector3        *pre_fit_minus_ssd_lpos;
   TVector3        *pre_fit_minus_gtr100_lpos;
   TVector3        *pre_fit_minus_gtr200_lpos;
   TVector3        *pre_fit_minus_gtr300_lpos;
   Double_t        pre_fit_mass;
   Double_t        fit_plus_chi2;
   TVector3        *fit_plus_init_mom;
   TVector3        *fit_plus_init_pos;
   TVector3        *fit_plus_ssd_lpos;
   TVector3        *fit_plus_gtr100_lpos;
   TVector3        *fit_plus_gtr200_lpos;
   TVector3        *fit_plus_gtr300_lpos;
   Double_t        fit_minus_chi2;
   TVector3        *fit_minus_init_mom;
   TVector3        *fit_minus_init_pos;
   TVector3        *fit_minus_ssd_lpos;
   TVector3        *fit_minus_gtr100_lpos;
   TVector3        *fit_minus_gtr200_lpos;
   TVector3        *fit_minus_gtr300_lpos;
   Double_t        fit_mass;
   Double_t        pair_fit_chi2;
   TVector3        *pair_fit_vtx;
   TVector3        *pair_fit_plus_init_mom;
   TVector3        *pair_fit_plus_ssd_lpos;
   TVector3        *pair_fit_plus_gtr100_lpos;
   TVector3        *pair_fit_plus_gtr200_lpos;
   TVector3        *pair_fit_plus_gtr300_lpos;
   TVector3        *pair_fit_minus_init_mom;
   TVector3        *pair_fit_minus_ssd_lpos;
   TVector3        *pair_fit_minus_gtr100_lpos;
   TVector3        *pair_fit_minus_gtr200_lpos;
   TVector3        *pair_fit_minus_gtr300_lpos;
   Double_t        pair_fit_mass;
   Int_t           wo_fit_flag;
   Double_t        wo_fit_distance;
   TVector3        *wo_fit_vtx;
   TVector3        *wo_fit_plus_init_mom;
   TVector3        *wo_fit_minus_init_mom;
   Double_t        wo_fit_mass;

   // List of branches
   TBranch        *b_run_id;   //!
   TBranch        *b_event_id;   //!
   TBranch        *b_plus_ssd_mid;   //!
   TBranch        *b_plus_gtr100_mid;   //!
   TBranch        *b_plus_gtr200_mid;   //!
   TBranch        *b_plus_gtr300_mid;   //!
   TBranch        *b_plus_ssd_lpos;   //!
   TBranch        *b_plus_gtr100_lpos;   //!
   TBranch        *b_plus_gtr200_lpos;   //!
   TBranch        *b_plus_gtr300_lpos;   //!
   TBranch        *b_minus_ssd_mid;   //!
   TBranch        *b_minus_gtr100_mid;   //!
   TBranch        *b_minus_gtr200_mid;   //!
   TBranch        *b_minus_gtr300_mid;   //!
   TBranch        *b_minus_ssd_lpos;   //!
   TBranch        *b_minus_gtr100_lpos;   //!
   TBranch        *b_minus_gtr200_lpos;   //!
   TBranch        *b_minus_gtr300_lpos;   //!
   TBranch        *b_mock_vtx;   //!
   TBranch        *b_mock_plus_init_mom;   //!
   TBranch        *b_mock_plus_ssd_lpos;   //!
   TBranch        *b_mock_plus_gtr100_lpos;   //!
   TBranch        *b_mock_plus_gtr200_lpos;   //!
   TBranch        *b_mock_plus_gtr300_lpos;   //!
   TBranch        *b_mock_minus_init_mom;   //!
   TBranch        *b_mock_minus_ssd_lpos;   //!
   TBranch        *b_mock_minus_gtr100_lpos;   //!
   TBranch        *b_mock_minus_gtr200_lpos;   //!
   TBranch        *b_mock_minus_gtr300_lpos;   //!
   TBranch        *b_mock_mass;   //!
   TBranch        *b_pre_fit_plus_chi2;   //!
   TBranch        *b_pre_fit_plus_init_mom;   //!
   TBranch        *b_pre_fit_plus_init_pos;   //!
   TBranch        *b_pre_fit_plus_ssd_lpos;   //!
   TBranch        *b_pre_fit_plus_gtr100_lpos;   //!
   TBranch        *b_pre_fit_plus_gtr200_lpos;   //!
   TBranch        *b_pre_fit_plus_gtr300_lpos;   //!
   TBranch        *b_pre_fit_minus_chi2;   //!
   TBranch        *b_pre_fit_minus_init_mom;   //!
   TBranch        *b_pre_fit_minus_init_pos;   //!
   TBranch        *b_pre_fit_minus_ssd_lpos;   //!
   TBranch        *b_pre_fit_minus_gtr100_lpos;   //!
   TBranch        *b_pre_fit_minus_gtr200_lpos;   //!
   TBranch        *b_pre_fit_minus_gtr300_lpos;   //!
   TBranch        *b_pre_fit_mass;   //!
   TBranch        *b_fit_plus_chi2;   //!
   TBranch        *b_fit_plus_init_mom;   //!
   TBranch        *b_fit_plus_init_pos;   //!
   TBranch        *b_fit_plus_ssd_lpos;   //!
   TBranch        *b_fit_plus_gtr100_lpos;   //!
   TBranch        *b_fit_plus_gtr200_lpos;   //!
   TBranch        *b_fit_plus_gtr300_lpos;   //!
   TBranch        *b_fit_minus_chi2;   //!
   TBranch        *b_fit_minus_init_mom;   //!
   TBranch        *b_fit_minus_init_pos;   //!
   TBranch        *b_fit_minus_ssd_lpos;   //!
   TBranch        *b_fit_minus_gtr100_lpos;   //!
   TBranch        *b_fit_minus_gtr200_lpos;   //!
   TBranch        *b_fit_minus_gtr300_lpos;   //!
   TBranch        *b_fit_mass;   //!
   TBranch        *b_pair_fit_chi2;   //!
   TBranch        *b_pair_fit_vtx;   //!
   TBranch        *b_pair_fit_plus_init_mom;   //!
   TBranch        *b_pair_fit_plus_ssd_lpos;   //!
   TBranch        *b_pair_fit_plus_gtr100_lpos;   //!
   TBranch        *b_pair_fit_plus_gtr200_lpos;   //!
   TBranch        *b_pair_fit_plus_gtr300_lpos;   //!
   TBranch        *b_pair_fit_minus_init_mom;   //!
   TBranch        *b_pair_fit_minus_ssd_lpos;   //!
   TBranch        *b_pair_fit_minus_gtr100_lpos;   //!
   TBranch        *b_pair_fit_minus_gtr200_lpos;   //!
   TBranch        *b_pair_fit_minus_gtr300_lpos;   //!
   TBranch        *b_pair_fit_mass;   //!
   TBranch        *b_wo_fit_flag;   //!
   TBranch        *b_wo_fit_distance;   //!
   TBranch        *b_wo_fit_vtx;   //!
   TBranch        *b_wo_fit_plus_init_mom;   //!
   TBranch        *b_wo_fit_minus_init_mom;   //!
   TBranch        *b_wo_fit_mass;   //!

   tmp_fit_mock_pair_from_dst1_drawer_220620(TTree *tree=0);
   virtual ~tmp_fit_mock_pair_from_dst1_drawer_220620();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(const TString& out_name);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
 private:
  int DirID();
  void Draw(const TString& name, std::array<std::array<TH1F, 2>, 4>* hists, TCanvas* canvas);
  void Draw(const TString& name, std::array<std::array<TH1F*, 3>, 5>* hists, TCanvas* canvas);
  void Draw(const TString& name, std::array<std::array<TH2F*, 3>, 5>* hists, TCanvas* canvas);
  void Draw(const TString& name, std::array<std::array<TH1F*, 2>, 5>* hists, TCanvas* canvas);
};

#endif

#ifdef tmp_fit_mock_pair_from_dst1_drawer_220620_cxx
tmp_fit_mock_pair_from_dst1_drawer_220620::tmp_fit_mock_pair_from_dst1_drawer_220620(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/ccj/w/data06a/E16/user/ichikawa/tmp/tmpmock2000.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/ccj/w/data06a/E16/user/ichikawa/tmp/tmpmock2000.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

tmp_fit_mock_pair_from_dst1_drawer_220620::~tmp_fit_mock_pair_from_dst1_drawer_220620()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tmp_fit_mock_pair_from_dst1_drawer_220620::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tmp_fit_mock_pair_from_dst1_drawer_220620::LoadTree(Long64_t entry)
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

void tmp_fit_mock_pair_from_dst1_drawer_220620::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   plus_ssd_lpos = 0;
   plus_gtr100_lpos = 0;
   plus_gtr200_lpos = 0;
   plus_gtr300_lpos = 0;
   minus_ssd_lpos = 0;
   minus_gtr100_lpos = 0;
   minus_gtr200_lpos = 0;
   minus_gtr300_lpos = 0;
   mock_vtx = 0;
   mock_plus_init_mom = 0;
   mock_plus_ssd_lpos = 0;
   mock_plus_gtr100_lpos = 0;
   mock_plus_gtr200_lpos = 0;
   mock_plus_gtr300_lpos = 0;
   mock_minus_init_mom = 0;
   mock_minus_ssd_lpos = 0;
   mock_minus_gtr100_lpos = 0;
   mock_minus_gtr200_lpos = 0;
   mock_minus_gtr300_lpos = 0;
   pre_fit_plus_init_mom = 0;
   pre_fit_plus_init_pos = 0;
   pre_fit_plus_ssd_lpos = 0;
   pre_fit_plus_gtr100_lpos = 0;
   pre_fit_plus_gtr200_lpos = 0;
   pre_fit_plus_gtr300_lpos = 0;
   pre_fit_minus_init_mom = 0;
   pre_fit_minus_init_pos = 0;
   pre_fit_minus_ssd_lpos = 0;
   pre_fit_minus_gtr100_lpos = 0;
   pre_fit_minus_gtr200_lpos = 0;
   pre_fit_minus_gtr300_lpos = 0;
   fit_plus_init_mom = 0;
   fit_plus_init_pos = 0;
   fit_plus_ssd_lpos = 0;
   fit_plus_gtr100_lpos = 0;
   fit_plus_gtr200_lpos = 0;
   fit_plus_gtr300_lpos = 0;
   fit_minus_init_mom = 0;
   fit_minus_init_pos = 0;
   fit_minus_ssd_lpos = 0;
   fit_minus_gtr100_lpos = 0;
   fit_minus_gtr200_lpos = 0;
   fit_minus_gtr300_lpos = 0;
   pair_fit_vtx = 0;
   pair_fit_plus_init_mom = 0;
   pair_fit_plus_ssd_lpos = 0;
   pair_fit_plus_gtr100_lpos = 0;
   pair_fit_plus_gtr200_lpos = 0;
   pair_fit_plus_gtr300_lpos = 0;
   pair_fit_minus_init_mom = 0;
   pair_fit_minus_ssd_lpos = 0;
   pair_fit_minus_gtr100_lpos = 0;
   pair_fit_minus_gtr200_lpos = 0;
   pair_fit_minus_gtr300_lpos = 0;
   wo_fit_vtx = 0;
   wo_fit_plus_init_mom = 0;
   wo_fit_minus_init_mom = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run_id", &run_id, &b_run_id);
   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("plus_ssd_mid", &plus_ssd_mid, &b_plus_ssd_mid);
   fChain->SetBranchAddress("plus_gtr100_mid", &plus_gtr100_mid, &b_plus_gtr100_mid);
   fChain->SetBranchAddress("plus_gtr200_mid", &plus_gtr200_mid, &b_plus_gtr200_mid);
   fChain->SetBranchAddress("plus_gtr300_mid", &plus_gtr300_mid, &b_plus_gtr300_mid);
   fChain->SetBranchAddress("plus_ssd_lpos", &plus_ssd_lpos, &b_plus_ssd_lpos);
   fChain->SetBranchAddress("plus_gtr100_lpos", &plus_gtr100_lpos, &b_plus_gtr100_lpos);
   fChain->SetBranchAddress("plus_gtr200_lpos", &plus_gtr200_lpos, &b_plus_gtr200_lpos);
   fChain->SetBranchAddress("plus_gtr300_lpos", &plus_gtr300_lpos, &b_plus_gtr300_lpos);
   fChain->SetBranchAddress("minus_ssd_mid", &minus_ssd_mid, &b_minus_ssd_mid);
   fChain->SetBranchAddress("minus_gtr100_mid", &minus_gtr100_mid, &b_minus_gtr100_mid);
   fChain->SetBranchAddress("minus_gtr200_mid", &minus_gtr200_mid, &b_minus_gtr200_mid);
   fChain->SetBranchAddress("minus_gtr300_mid", &minus_gtr300_mid, &b_minus_gtr300_mid);
   fChain->SetBranchAddress("minus_ssd_lpos", &minus_ssd_lpos, &b_minus_ssd_lpos);
   fChain->SetBranchAddress("minus_gtr100_lpos", &minus_gtr100_lpos, &b_minus_gtr100_lpos);
   fChain->SetBranchAddress("minus_gtr200_lpos", &minus_gtr200_lpos, &b_minus_gtr200_lpos);
   fChain->SetBranchAddress("minus_gtr300_lpos", &minus_gtr300_lpos, &b_minus_gtr300_lpos);
   fChain->SetBranchAddress("mock_vtx", &mock_vtx, &b_mock_vtx);
   fChain->SetBranchAddress("mock_plus_init_mom", &mock_plus_init_mom, &b_mock_plus_init_mom);
   fChain->SetBranchAddress("mock_plus_ssd_lpos", &mock_plus_ssd_lpos, &b_mock_plus_ssd_lpos);
   fChain->SetBranchAddress("mock_plus_gtr100_lpos", &mock_plus_gtr100_lpos, &b_mock_plus_gtr100_lpos);
   fChain->SetBranchAddress("mock_plus_gtr200_lpos", &mock_plus_gtr200_lpos, &b_mock_plus_gtr200_lpos);
   fChain->SetBranchAddress("mock_plus_gtr300_lpos", &mock_plus_gtr300_lpos, &b_mock_plus_gtr300_lpos);
   fChain->SetBranchAddress("mock_minus_init_mom", &mock_minus_init_mom, &b_mock_minus_init_mom);
   fChain->SetBranchAddress("mock_minus_ssd_lpos", &mock_minus_ssd_lpos, &b_mock_minus_ssd_lpos);
   fChain->SetBranchAddress("mock_minus_gtr100_lpos", &mock_minus_gtr100_lpos, &b_mock_minus_gtr100_lpos);
   fChain->SetBranchAddress("mock_minus_gtr200_lpos", &mock_minus_gtr200_lpos, &b_mock_minus_gtr200_lpos);
   fChain->SetBranchAddress("mock_minus_gtr300_lpos", &mock_minus_gtr300_lpos, &b_mock_minus_gtr300_lpos);
   fChain->SetBranchAddress("mock_mass", &mock_mass, &b_mock_mass);
   fChain->SetBranchAddress("pre_fit_plus_chi2", &pre_fit_plus_chi2, &b_pre_fit_plus_chi2);
   fChain->SetBranchAddress("pre_fit_plus_init_mom", &pre_fit_plus_init_mom, &b_pre_fit_plus_init_mom);
   fChain->SetBranchAddress("pre_fit_plus_init_pos", &pre_fit_plus_init_pos, &b_pre_fit_plus_init_pos);
   fChain->SetBranchAddress("pre_fit_plus_ssd_lpos", &pre_fit_plus_ssd_lpos, &b_pre_fit_plus_ssd_lpos);
   fChain->SetBranchAddress("pre_fit_plus_gtr100_lpos", &pre_fit_plus_gtr100_lpos, &b_pre_fit_plus_gtr100_lpos);
   fChain->SetBranchAddress("pre_fit_plus_gtr200_lpos", &pre_fit_plus_gtr200_lpos, &b_pre_fit_plus_gtr200_lpos);
   fChain->SetBranchAddress("pre_fit_plus_gtr300_lpos", &pre_fit_plus_gtr300_lpos, &b_pre_fit_plus_gtr300_lpos);
   fChain->SetBranchAddress("pre_fit_minus_chi2", &pre_fit_minus_chi2, &b_pre_fit_minus_chi2);
   fChain->SetBranchAddress("pre_fit_minus_init_mom", &pre_fit_minus_init_mom, &b_pre_fit_minus_init_mom);
   fChain->SetBranchAddress("pre_fit_minus_init_pos", &pre_fit_minus_init_pos, &b_pre_fit_minus_init_pos);
   fChain->SetBranchAddress("pre_fit_minus_ssd_lpos", &pre_fit_minus_ssd_lpos, &b_pre_fit_minus_ssd_lpos);
   fChain->SetBranchAddress("pre_fit_minus_gtr100_lpos", &pre_fit_minus_gtr100_lpos, &b_pre_fit_minus_gtr100_lpos);
   fChain->SetBranchAddress("pre_fit_minus_gtr200_lpos", &pre_fit_minus_gtr200_lpos, &b_pre_fit_minus_gtr200_lpos);
   fChain->SetBranchAddress("pre_fit_minus_gtr300_lpos", &pre_fit_minus_gtr300_lpos, &b_pre_fit_minus_gtr300_lpos);
   fChain->SetBranchAddress("pre_fit_mass", &pre_fit_mass, &b_pre_fit_mass);
   fChain->SetBranchAddress("fit_plus_chi2", &fit_plus_chi2, &b_fit_plus_chi2);
   fChain->SetBranchAddress("fit_plus_init_mom", &fit_plus_init_mom, &b_fit_plus_init_mom);
   fChain->SetBranchAddress("fit_plus_init_pos", &fit_plus_init_pos, &b_fit_plus_init_pos);
   fChain->SetBranchAddress("fit_plus_ssd_lpos", &fit_plus_ssd_lpos, &b_fit_plus_ssd_lpos);
   fChain->SetBranchAddress("fit_plus_gtr100_lpos", &fit_plus_gtr100_lpos, &b_fit_plus_gtr100_lpos);
   fChain->SetBranchAddress("fit_plus_gtr200_lpos", &fit_plus_gtr200_lpos, &b_fit_plus_gtr200_lpos);
   fChain->SetBranchAddress("fit_plus_gtr300_lpos", &fit_plus_gtr300_lpos, &b_fit_plus_gtr300_lpos);
   fChain->SetBranchAddress("fit_minus_chi2", &fit_minus_chi2, &b_fit_minus_chi2);
   fChain->SetBranchAddress("fit_minus_init_mom", &fit_minus_init_mom, &b_fit_minus_init_mom);
   fChain->SetBranchAddress("fit_minus_init_pos", &fit_minus_init_pos, &b_fit_minus_init_pos);
   fChain->SetBranchAddress("fit_minus_ssd_lpos", &fit_minus_ssd_lpos, &b_fit_minus_ssd_lpos);
   fChain->SetBranchAddress("fit_minus_gtr100_lpos", &fit_minus_gtr100_lpos, &b_fit_minus_gtr100_lpos);
   fChain->SetBranchAddress("fit_minus_gtr200_lpos", &fit_minus_gtr200_lpos, &b_fit_minus_gtr200_lpos);
   fChain->SetBranchAddress("fit_minus_gtr300_lpos", &fit_minus_gtr300_lpos, &b_fit_minus_gtr300_lpos);
   fChain->SetBranchAddress("fit_mass", &fit_mass, &b_fit_mass);
   fChain->SetBranchAddress("pair_fit_chi2", &pair_fit_chi2, &b_pair_fit_chi2);
   fChain->SetBranchAddress("pair_fit_vtx", &pair_fit_vtx, &b_pair_fit_vtx);
   fChain->SetBranchAddress("pair_fit_plus_init_mom", &pair_fit_plus_init_mom, &b_pair_fit_plus_init_mom);
   fChain->SetBranchAddress("pair_fit_plus_ssd_lpos", &pair_fit_plus_ssd_lpos, &b_pair_fit_plus_ssd_lpos);
   fChain->SetBranchAddress("pair_fit_plus_gtr100_lpos", &pair_fit_plus_gtr100_lpos, &b_pair_fit_plus_gtr100_lpos);
   fChain->SetBranchAddress("pair_fit_plus_gtr200_lpos", &pair_fit_plus_gtr200_lpos, &b_pair_fit_plus_gtr200_lpos);
   fChain->SetBranchAddress("pair_fit_plus_gtr300_lpos", &pair_fit_plus_gtr300_lpos, &b_pair_fit_plus_gtr300_lpos);
   fChain->SetBranchAddress("pair_fit_minus_init_mom", &pair_fit_minus_init_mom, &b_pair_fit_minus_init_mom);
   fChain->SetBranchAddress("pair_fit_minus_ssd_lpos", &pair_fit_minus_ssd_lpos, &b_pair_fit_minus_ssd_lpos);
   fChain->SetBranchAddress("pair_fit_minus_gtr100_lpos", &pair_fit_minus_gtr100_lpos, &b_pair_fit_minus_gtr100_lpos);
   fChain->SetBranchAddress("pair_fit_minus_gtr200_lpos", &pair_fit_minus_gtr200_lpos, &b_pair_fit_minus_gtr200_lpos);
   fChain->SetBranchAddress("pair_fit_minus_gtr300_lpos", &pair_fit_minus_gtr300_lpos, &b_pair_fit_minus_gtr300_lpos);
   fChain->SetBranchAddress("pair_fit_mass", &pair_fit_mass, &b_pair_fit_mass);
   fChain->SetBranchAddress("wo_fit_flag", &wo_fit_flag, &b_wo_fit_flag);
   fChain->SetBranchAddress("wo_fit_distance", &wo_fit_distance, &b_wo_fit_distance);
   fChain->SetBranchAddress("wo_fit_vtx", &wo_fit_vtx, &b_wo_fit_vtx);
   fChain->SetBranchAddress("wo_fit_plus_init_mom", &wo_fit_plus_init_mom, &b_wo_fit_plus_init_mom);
   fChain->SetBranchAddress("wo_fit_minus_init_mom", &wo_fit_minus_init_mom, &b_wo_fit_minus_init_mom);
   fChain->SetBranchAddress("wo_fit_mass", &wo_fit_mass, &b_wo_fit_mass);
   Notify();
}

Bool_t tmp_fit_mock_pair_from_dst1_drawer_220620::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tmp_fit_mock_pair_from_dst1_drawer_220620::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tmp_fit_mock_pair_from_dst1_drawer_220620::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tmp_fit_mock_pair_from_dst1_drawer_220620_cxx
