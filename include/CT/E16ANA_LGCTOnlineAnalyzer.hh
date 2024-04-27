//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Apr 20 11:29:55 2024 by ROOT version 6.18/04
// from TTree tree/tree
// found on file: root/run050087_lgct.root
//////////////////////////////////////////////////////////

#ifndef E16ANA_LGCTOnlineAnalyzer_h
#define E16ANA_LGCTOnlineAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class E16ANA_LGCTOnlineAnalyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           Run;
   Int_t           Event;
   Int_t           Spill;
   Int_t           TimeStampInSpill;
   Bool_t          SL;
   Bool_t          SR;
   Bool_t          SL2;
   Bool_t          SR2;
   Bool_t          IM3;
   Bool_t          IM2;
   UShort_t        LGModule;
   UShort_t        LGBlock;
   Float_t         LGPeakHeight;
   Int_t           LGPeakTime;
   Float_t         LGTiming;
   Float_t         LGBaseline;
   Float_t         LGBaselineRms;
   Int_t           CT0Module;
   Int_t           CT0Block;
   Float_t         CT0PeakHeight;
   Int_t           CT0PeakTime;
   Float_t         CT0Timing;
   Float_t         CT0Baseline;
   Float_t         CT0BaselineRms;
   Int_t           CT1Module;
   Int_t           CT1Block;
   Float_t         CT1PeakHeight;
   Int_t           CT1PeakTime;
   Float_t         CT1Timing;
   Float_t         CT1Baseline;
   Float_t         CT1BaselineRms;
   Double_t        LGWaveform[200];
   Double_t        CT0Waveform[200];
   Double_t        CT1Waveform[200];
   Bool_t          LGDst1Flag;
   Float_t         LGTrgTiming;
   Bool_t          LGTrg;
   Bool_t          LGTrgwTRK;

   // List of branches
   TBranch        *b_Run;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_Spill;   //!
   TBranch        *b_TimeStampInSpill;   //!
   TBranch        *b_SL;   //!
   TBranch        *b_SR;   //!
   TBranch        *b_SL2;   //!
   TBranch        *b_SR2;   //!
   TBranch        *b_IM3;   //!
   TBranch        *b_IM2;   //!
   TBranch        *b_LGModule;   //!
   TBranch        *b_LGBlock;   //!
   TBranch        *b_LGPeakHeight;   //!
   TBranch        *b_LGPeakTime;   //!
   TBranch        *b_LGTiming;   //!
   TBranch        *b_LGBaseline;   //!
   TBranch        *b_LGBaselineRms;   //!
   TBranch        *b_CT0Module;   //!
   TBranch        *b_CT0Block;   //!
   TBranch        *b_CT0PeakHeight;   //!
   TBranch        *b_CT0PeakTime;   //!
   TBranch        *b_CT0Timing;   //!
   TBranch        *b_CT0Baseline;   //!
   TBranch        *b_CT0BaselineRms;   //!
   TBranch        *b_CT1Module;   //!
   TBranch        *b_CT1Block;   //!
   TBranch        *b_CT1PeakHeight;   //!
   TBranch        *b_CT1PeakTime;   //!
   TBranch        *b_CT1Timing;   //!
   TBranch        *b_CT1Baseline;   //!
   TBranch        *b_CT1BaselineRms;   //!
   TBranch        *b_LGWaveform;   //!
   TBranch        *b_CT0Waveform;   //!
   TBranch        *b_CT1Waveform;   //!
   TBranch        *b_LGDst1Flag;   //!
   TBranch        *b_LGTrgTiming;   //!
   TBranch        *b_LGTrg;   //!
   TBranch        *b_LGTrgwTRK;   //!

   E16ANA_LGCTOnlineAnalyzer(TTree *tree=0);
   virtual ~E16ANA_LGCTOnlineAnalyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual void     MakeCTPDF(int run_id, char* outfile, int maxevent);
   virtual void     MakeLGPDF(int run_id, char* outfile, int maxevent);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef E16ANA_LGCTOnlineAnalyzer_cxx
E16ANA_LGCTOnlineAnalyzer::E16ANA_LGCTOnlineAnalyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("root/run050087_lgct.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("root/run050087_lgct.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

E16ANA_LGCTOnlineAnalyzer::~E16ANA_LGCTOnlineAnalyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t E16ANA_LGCTOnlineAnalyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t E16ANA_LGCTOnlineAnalyzer::LoadTree(Long64_t entry)
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

void E16ANA_LGCTOnlineAnalyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("Spill", &Spill, &b_Spill);
   fChain->SetBranchAddress("TimeStampInSpill", &TimeStampInSpill, &b_TimeStampInSpill);
   fChain->SetBranchAddress("SL", &SL, &b_SL);
   fChain->SetBranchAddress("SR", &SR, &b_SR);
   fChain->SetBranchAddress("SL2", &SL2, &b_SL2);
   fChain->SetBranchAddress("SR2", &SR2, &b_SR2);
   fChain->SetBranchAddress("IM3", &IM3, &b_IM3);
   fChain->SetBranchAddress("IM2", &IM2, &b_IM2);
   fChain->SetBranchAddress("LGModule", &LGModule, &b_LGModule);
   fChain->SetBranchAddress("LGBlock", &LGBlock, &b_LGBlock);
   fChain->SetBranchAddress("LGPeakHeight", &LGPeakHeight, &b_LGPeakHeight);
   fChain->SetBranchAddress("LGPeakTime", &LGPeakTime, &b_LGPeakTime);
   fChain->SetBranchAddress("LGTiming", &LGTiming, &b_LGTiming);
   fChain->SetBranchAddress("LGBaseline", &LGBaseline, &b_LGBaseline);
   fChain->SetBranchAddress("LGBaselineRms", &LGBaselineRms, &b_LGBaselineRms);
   fChain->SetBranchAddress("CT0Module", &CT0Module, &b_CT0Module);
   fChain->SetBranchAddress("CT0Block", &CT0Block, &b_CT0Block);
   fChain->SetBranchAddress("CT0PeakHeight", &CT0PeakHeight, &b_CT0PeakHeight);
   fChain->SetBranchAddress("CT0PeakTime", &CT0PeakTime, &b_CT0PeakTime);
   fChain->SetBranchAddress("CT0Timing", &CT0Timing, &b_CT0Timing);
   fChain->SetBranchAddress("CT0Baseline", &CT0Baseline, &b_CT0Baseline);
   fChain->SetBranchAddress("CT0BaselineRms", &CT0BaselineRms, &b_CT0BaselineRms);
   fChain->SetBranchAddress("CT1Module", &CT1Module, &b_CT1Module);
   fChain->SetBranchAddress("CT1Block", &CT1Block, &b_CT1Block);
   fChain->SetBranchAddress("CT1PeakHeight", &CT1PeakHeight, &b_CT1PeakHeight);
   fChain->SetBranchAddress("CT1PeakTime", &CT1PeakTime, &b_CT1PeakTime);
   fChain->SetBranchAddress("CT1Timing", &CT1Timing, &b_CT1Timing);
   fChain->SetBranchAddress("CT1Baseline", &CT1Baseline, &b_CT1Baseline);
   fChain->SetBranchAddress("CT1BaselineRms", &CT1BaselineRms, &b_CT1BaselineRms);
   fChain->SetBranchAddress("LGWaveform", LGWaveform, &b_LGWaveform);
   fChain->SetBranchAddress("CT0Waveform", CT0Waveform, &b_CT0Waveform);
   fChain->SetBranchAddress("CT1Waveform", CT1Waveform, &b_CT1Waveform);
   fChain->SetBranchAddress("LGDst1Flag", &LGDst1Flag, &b_LGDst1Flag);
   fChain->SetBranchAddress("LGTrgTiming", &LGTrgTiming, &b_LGTrgTiming);
   fChain->SetBranchAddress("LGTrg", &LGTrg, &b_LGTrg);
   fChain->SetBranchAddress("LGTrgwTRK", &LGTrgwTRK, &b_LGTrgwTRK);
   Notify();
}

Bool_t E16ANA_LGCTOnlineAnalyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void E16ANA_LGCTOnlineAnalyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t E16ANA_LGCTOnlineAnalyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef E16ANA_LGCTOnlineAnalyzer_cxx
