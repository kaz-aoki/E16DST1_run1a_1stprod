//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun 16 16:05:28 2022 by ROOT version 6.18/04
// from TTree tree/tree
// found on file: /work22/ichikawa/lsf_file/22053000-v17/root/run030717.root
//////////////////////////////////////////////////////////

#ifndef tmp_fit_mock_pair_220616_h
#define tmp_fit_mock_pair_220616_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TVector3.h"

class tmp_fit_mock_pair_220616 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run_id;
   Int_t           event_id;
   Double_t        plus_chi2;
   TVector3        *plus_ssd_fit_gpos;
   TVector3        *plus_gtr100_fit_gpos;
   TVector3        *plus_gtr200_fit_gpos;
   TVector3        *plus_gtr300_fit_gpos;
   TVector3        *plus_init_gpos;
   TVector3        *plus_init_mom;
   Int_t           plus_ssd_mid;
   TVector3        *plus_ssd_gpos;
   Int_t           plus_gtr100_mid;
   TVector3        *plus_gtr100_gpos;
   Int_t           plus_gtr200_mid;
   TVector3        *plus_gtr200_gpos;
   Int_t           plus_gtr300_mid;
   TVector3        *plus_gtr300_gpos;
   Double_t        minus_chi2;
   TVector3        *minus_ssd_fit_gpos;
   TVector3        *minus_gtr100_fit_gpos;
   TVector3        *minus_gtr200_fit_gpos;
   TVector3        *minus_gtr300_fit_gpos;
   TVector3        *minus_init_gpos;
   TVector3        *minus_init_mom;
   Int_t           minus_ssd_mid;
   TVector3        *minus_ssd_gpos;
   Int_t           minus_gtr100_mid;
   TVector3        *minus_gtr100_gpos;
   Int_t           minus_gtr200_mid;
   TVector3        *minus_gtr200_gpos;
   Int_t           minus_gtr300_mid;
   TVector3        *minus_gtr300_gpos;
   TVector3        *mock_plus_init_mom;
   TVector3        *mock_plus_init_pos;
   Int_t           mock_plus_ssd_mid;
   TVector3        *mock_plus_ssd_lpos;
   Int_t           mock_plus_gtr100_mid;
   TVector3        *mock_plus_gtr100_lpos;
   Int_t           mock_plus_gtr200_mid;
   TVector3        *mock_plus_gtr200_lpos;
   Int_t           mock_plus_gtr300_mid;
   TVector3        *mock_plus_gtr300_lpos;
   TVector3        *mock_minus_init_mom;
   TVector3        *mock_minus_init_pos;
   Int_t           mock_minus_ssd_mid;
   TVector3        *mock_minus_ssd_lpos;
   Int_t           mock_minus_gtr100_mid;
   TVector3        *mock_minus_gtr100_lpos;
   Int_t           mock_minus_gtr200_mid;
   TVector3        *mock_minus_gtr200_lpos;
   Int_t           mock_minus_gtr300_mid;
   TVector3        *mock_minus_gtr300_lpos;

   // List of branches
   TBranch        *b_run_id;   //!
   TBranch        *b_event_id;   //!
   TBranch        *b_plus_chi2;   //!
   TBranch        *b_plus_ssd_fit_gpos;   //!
   TBranch        *b_plus_gtr100_fit_gpos;   //!
   TBranch        *b_plus_gtr200_fit_gpos;   //!
   TBranch        *b_plus_gtr300_fit_gpos;   //!
   TBranch        *b_plus_init_gpos;   //!
   TBranch        *b_plus_init_mom;   //!
   TBranch        *b_plus_ssd_mid;   //!
   TBranch        *b_plus_ssd_gpos;   //!
   TBranch        *b_plus_gtr100_mid;   //!
   TBranch        *b_plus_gtr100_gpos;   //!
   TBranch        *b_plus_gtr200_mid;   //!
   TBranch        *b_plus_gtr200_gpos;   //!
   TBranch        *b_plus_gtr300_mid;   //!
   TBranch        *b_plus_gtr300_gpos;   //!
   TBranch        *b_minus_chi2;   //!
   TBranch        *b_minus_ssd_fit_gpos;   //!
   TBranch        *b_minus_gtr100_fit_gpos;   //!
   TBranch        *b_minus_gtr200_fit_gpos;   //!
   TBranch        *b_minus_gtr300_fit_gpos;   //!
   TBranch        *b_minus_init_gpos;   //!
   TBranch        *b_minus_init_mom;   //!
   TBranch        *b_minus_ssd_mid;   //!
   TBranch        *b_minus_ssd_gpos;   //!
   TBranch        *b_minus_gtr100_mid;   //!
   TBranch        *b_minus_gtr100_gpos;   //!
   TBranch        *b_minus_gtr200_mid;   //!
   TBranch        *b_minus_gtr200_gpos;   //!
   TBranch        *b_minus_gtr300_mid;   //!
   TBranch        *b_minus_gtr300_gpos;   //!
   TBranch        *b_mock_plus_init_mom;   //!
   TBranch        *b_mock_plus_init_pos;   //!
   TBranch        *b_mock_plus_ssd_mid;   //!
   TBranch        *b_mock_plus_ssd_lpos;   //!
   TBranch        *b_mock_plus_gtr100_mid;   //!
   TBranch        *b_mock_plus_gtr100_lpos;   //!
   TBranch        *b_mock_plus_gtr200_mid;   //!
   TBranch        *b_mock_plus_gtr200_lpos;   //!
   TBranch        *b_mock_plus_gtr300_mid;   //!
   TBranch        *b_mock_plus_gtr300_lpos;   //!
   TBranch        *b_mock_minus_init_mom;   //!
   TBranch        *b_mock_minus_init_pos;   //!
   TBranch        *b_mock_minus_ssd_mid;   //!
   TBranch        *b_mock_minus_ssd_lpos;   //!
   TBranch        *b_mock_minus_gtr100_mid;   //!
   TBranch        *b_mock_minus_gtr100_lpos;   //!
   TBranch        *b_mock_minus_gtr200_mid;   //!
   TBranch        *b_mock_minus_gtr200_lpos;   //!
   TBranch        *b_mock_minus_gtr300_mid;   //!
   TBranch        *b_mock_minus_gtr300_lpos;   //!

   tmp_fit_mock_pair_220616(TTree *tree=0);
   virtual ~tmp_fit_mock_pair_220616();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(int max_events, const TString& out_name);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
 private:
  std::array<int, 4> ModuleIDs2020To2013(int cid);
  double CalcMass(const TVector3& mom0, const TVector3& mom1);
};

#endif

#ifdef tmp_fit_mock_pair_220616_cxx
tmp_fit_mock_pair_220616::tmp_fit_mock_pair_220616(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/work22/ichikawa/lsf_file/22053000-v17/root/run030717.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/work22/ichikawa/lsf_file/22053000-v17/root/run030717.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

tmp_fit_mock_pair_220616::~tmp_fit_mock_pair_220616()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tmp_fit_mock_pair_220616::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tmp_fit_mock_pair_220616::LoadTree(Long64_t entry)
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

void tmp_fit_mock_pair_220616::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   plus_ssd_fit_gpos = 0;
   plus_gtr100_fit_gpos = 0;
   plus_gtr200_fit_gpos = 0;
   plus_gtr300_fit_gpos = 0;
   plus_init_gpos = 0;
   plus_init_mom = 0;
   plus_ssd_gpos = 0;
   plus_gtr100_gpos = 0;
   plus_gtr200_gpos = 0;
   plus_gtr300_gpos = 0;
   minus_ssd_fit_gpos = 0;
   minus_gtr100_fit_gpos = 0;
   minus_gtr200_fit_gpos = 0;
   minus_gtr300_fit_gpos = 0;
   minus_init_gpos = 0;
   minus_init_mom = 0;
   minus_ssd_gpos = 0;
   minus_gtr100_gpos = 0;
   minus_gtr200_gpos = 0;
   minus_gtr300_gpos = 0;
   mock_plus_init_mom = 0;
   mock_plus_init_pos = 0;
   mock_plus_ssd_lpos = 0;
   mock_plus_gtr100_lpos = 0;
   mock_plus_gtr200_lpos = 0;
   mock_plus_gtr300_lpos = 0;
   mock_minus_init_mom = 0;
   mock_minus_init_pos = 0;
   mock_minus_ssd_lpos = 0;
   mock_minus_gtr100_lpos = 0;
   mock_minus_gtr200_lpos = 0;
   mock_minus_gtr300_lpos = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run_id", &run_id, &b_run_id);
   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("plus_chi2", &plus_chi2, &b_plus_chi2);
   fChain->SetBranchAddress("plus_ssd_fit_gpos", &plus_ssd_fit_gpos, &b_plus_ssd_fit_gpos);
   fChain->SetBranchAddress("plus_gtr100_fit_gpos", &plus_gtr100_fit_gpos, &b_plus_gtr100_fit_gpos);
   fChain->SetBranchAddress("plus_gtr200_fit_gpos", &plus_gtr200_fit_gpos, &b_plus_gtr200_fit_gpos);
   fChain->SetBranchAddress("plus_gtr300_fit_gpos", &plus_gtr300_fit_gpos, &b_plus_gtr300_fit_gpos);
   fChain->SetBranchAddress("plus_init_gpos", &plus_init_gpos, &b_plus_init_gpos);
   fChain->SetBranchAddress("plus_init_mom", &plus_init_mom, &b_plus_init_mom);
   fChain->SetBranchAddress("plus_ssd_mid", &plus_ssd_mid, &b_plus_ssd_mid);
   fChain->SetBranchAddress("plus_ssd_gpos", &plus_ssd_gpos, &b_plus_ssd_gpos);
   fChain->SetBranchAddress("plus_gtr100_mid", &plus_gtr100_mid, &b_plus_gtr100_mid);
   fChain->SetBranchAddress("plus_gtr100_gpos", &plus_gtr100_gpos, &b_plus_gtr100_gpos);
   fChain->SetBranchAddress("plus_gtr200_mid", &plus_gtr200_mid, &b_plus_gtr200_mid);
   fChain->SetBranchAddress("plus_gtr200_gpos", &plus_gtr200_gpos, &b_plus_gtr200_gpos);
   fChain->SetBranchAddress("plus_gtr300_mid", &plus_gtr300_mid, &b_plus_gtr300_mid);
   fChain->SetBranchAddress("plus_gtr300_gpos", &plus_gtr300_gpos, &b_plus_gtr300_gpos);
   fChain->SetBranchAddress("minus_chi2", &minus_chi2, &b_minus_chi2);
   fChain->SetBranchAddress("minus_ssd_fit_gpos", &minus_ssd_fit_gpos, &b_minus_ssd_fit_gpos);
   fChain->SetBranchAddress("minus_gtr100_fit_gpos", &minus_gtr100_fit_gpos, &b_minus_gtr100_fit_gpos);
   fChain->SetBranchAddress("minus_gtr200_fit_gpos", &minus_gtr200_fit_gpos, &b_minus_gtr200_fit_gpos);
   fChain->SetBranchAddress("minus_gtr300_fit_gpos", &minus_gtr300_fit_gpos, &b_minus_gtr300_fit_gpos);
   fChain->SetBranchAddress("minus_init_gpos", &minus_init_gpos, &b_minus_init_gpos);
   fChain->SetBranchAddress("minus_init_mom", &minus_init_mom, &b_minus_init_mom);
   fChain->SetBranchAddress("minus_ssd_mid", &minus_ssd_mid, &b_minus_ssd_mid);
   fChain->SetBranchAddress("minus_ssd_gpos", &minus_ssd_gpos, &b_minus_ssd_gpos);
   fChain->SetBranchAddress("minus_gtr100_mid", &minus_gtr100_mid, &b_minus_gtr100_mid);
   fChain->SetBranchAddress("minus_gtr100_gpos", &minus_gtr100_gpos, &b_minus_gtr100_gpos);
   fChain->SetBranchAddress("minus_gtr200_mid", &minus_gtr200_mid, &b_minus_gtr200_mid);
   fChain->SetBranchAddress("minus_gtr200_gpos", &minus_gtr200_gpos, &b_minus_gtr200_gpos);
   fChain->SetBranchAddress("minus_gtr300_mid", &minus_gtr300_mid, &b_minus_gtr300_mid);
   fChain->SetBranchAddress("minus_gtr300_gpos", &minus_gtr300_gpos, &b_minus_gtr300_gpos);
   fChain->SetBranchAddress("mock_plus_init_mom", &mock_plus_init_mom, &b_mock_plus_init_mom);
   fChain->SetBranchAddress("mock_plus_init_pos", &mock_plus_init_pos, &b_mock_plus_init_pos);
   fChain->SetBranchAddress("mock_plus_ssd_mid", &mock_plus_ssd_mid, &b_mock_plus_ssd_mid);
   fChain->SetBranchAddress("mock_plus_ssd_lpos", &mock_plus_ssd_lpos, &b_mock_plus_ssd_lpos);
   fChain->SetBranchAddress("mock_plus_gtr100_mid", &mock_plus_gtr100_mid, &b_mock_plus_gtr100_mid);
   fChain->SetBranchAddress("mock_plus_gtr100_lpos", &mock_plus_gtr100_lpos, &b_mock_plus_gtr100_lpos);
   fChain->SetBranchAddress("mock_plus_gtr200_mid", &mock_plus_gtr200_mid, &b_mock_plus_gtr200_mid);
   fChain->SetBranchAddress("mock_plus_gtr200_lpos", &mock_plus_gtr200_lpos, &b_mock_plus_gtr200_lpos);
   fChain->SetBranchAddress("mock_plus_gtr300_mid", &mock_plus_gtr300_mid, &b_mock_plus_gtr300_mid);
   fChain->SetBranchAddress("mock_plus_gtr300_lpos", &mock_plus_gtr300_lpos, &b_mock_plus_gtr300_lpos);
   fChain->SetBranchAddress("mock_minus_init_mom", &mock_minus_init_mom, &b_mock_minus_init_mom);
   fChain->SetBranchAddress("mock_minus_init_pos", &mock_minus_init_pos, &b_mock_minus_init_pos);
   fChain->SetBranchAddress("mock_minus_ssd_mid", &mock_minus_ssd_mid, &b_mock_minus_ssd_mid);
   fChain->SetBranchAddress("mock_minus_ssd_lpos", &mock_minus_ssd_lpos, &b_mock_minus_ssd_lpos);
   fChain->SetBranchAddress("mock_minus_gtr100_mid", &mock_minus_gtr100_mid, &b_mock_minus_gtr100_mid);
   fChain->SetBranchAddress("mock_minus_gtr100_lpos", &mock_minus_gtr100_lpos, &b_mock_minus_gtr100_lpos);
   fChain->SetBranchAddress("mock_minus_gtr200_mid", &mock_minus_gtr200_mid, &b_mock_minus_gtr200_mid);
   fChain->SetBranchAddress("mock_minus_gtr200_lpos", &mock_minus_gtr200_lpos, &b_mock_minus_gtr200_lpos);
   fChain->SetBranchAddress("mock_minus_gtr300_mid", &mock_minus_gtr300_mid, &b_mock_minus_gtr300_mid);
   fChain->SetBranchAddress("mock_minus_gtr300_lpos", &mock_minus_gtr300_lpos, &b_mock_minus_gtr300_lpos);
   Notify();
}

Bool_t tmp_fit_mock_pair_220616::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tmp_fit_mock_pair_220616::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tmp_fit_mock_pair_220616::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tmp_fit_mock_pair_220616_cxx
