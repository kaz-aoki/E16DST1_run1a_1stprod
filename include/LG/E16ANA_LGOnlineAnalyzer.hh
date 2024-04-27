//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun  8 20:20:37 2023 by ROOT version 6.18/04
// from TTree tree/tree
// found on file: root/run040034.root
//////////////////////////////////////////////////////////

#ifndef E16ANA_LGOnlineAnalyzer_h
#define E16ANA_LGOnlineAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TCanvas.h>

#include <stdio.h>
#include <iostream>
#include "E16DST_Constant.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_EIDSingleTrackAnalyzer.hh"

// Header file for the classes stored in the TTree if any.

class E16ANA_LGOnlineAnalyzer {
private :

  // int FMstate = 0;// 0: FMOFF, 1: FMON
  double gain_index[2] = {9.28, 7.638};// 0: FMOFF, 1: FMON
  double standard_phmean = 60.;//[mV] 

public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           Run;
   Int_t           Event;
   Int_t           Spill;
   Int_t           TimeStampInSpill;
   Int_t           Multi;
   Int_t           TrgMulti;
   Bool_t          SL;
   Bool_t          SR;
   Bool_t          SL2;
   Bool_t          SR2;
   Bool_t          IM3;
   Bool_t          IM2;
   UShort_t        Module;
   UShort_t        Block;
   Float_t         PeakHeight;
   Int_t           PeakTime;
   Float_t         Timing;
   Float_t         Baseline;
   Float_t         BaselineRms;
   Float_t         Integral;
   Float_t         Falltime;
   Bool_t          SpikeFlag;
   Float_t         CalibTiming;
   Float_t         EnergyDeposit;
   Bool_t          Dst1Flag;
   Double_t        Gpos[3];
   Double_t        Lpos[3];
   Double_t        Waveform[E16DST_Constant::NSamplesLG];
   Float_t         TrgTiming;
   Bool_t          Trg;
   Bool_t          TrgwTRK;

   // List of branches
   TBranch        *b_Run;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_Spill;   //!
   TBranch        *b_TimeStampInSpill;   //!
   TBranch        *b_Multi;   //!
   TBranch        *b_TrgMulti;   //!
   TBranch        *b_SL;   //!
   TBranch        *b_SR;   //!
   TBranch        *b_SL2;   //!
   TBranch        *b_SR2;   //!
   TBranch        *b_IM3;   //!
   TBranch        *b_IM2;   //!
   TBranch        *b_Module;   //!
   TBranch        *b_Block;   //!
   TBranch        *b_PeakHeight;   //!
   TBranch        *b_PeakTime;   //!
   TBranch        *b_timing;   //!
   TBranch        *b_Baseline;   //!
   TBranch        *b_BaselineRms;   //!
   TBranch        *b_Integral;   //!
   TBranch        *b_Falltime;   //!
   TBranch        *b_SpikeFlag;   //!
   TBranch        *b_CalibTiming;   //!
   TBranch        *b_EnergyDeposit;   //!
   TBranch        *b_Dst1Flag;   //!
   TBranch        *b_Gpos;   //!
   TBranch        *b_Lpos;   //!
   TBranch        *b_Waveform;   //!
   TBranch        *b_TrgTiming;   //!
   TBranch        *b_Trg;   //!
   TBranch        *b_TrgwTRK;   //!

   E16ANA_LGOnlineAnalyzer(TTree *tree=0);
   virtual ~E16ANA_LGOnlineAnalyzer();
   virtual Int_t    CutData(Long64_t entry);
   virtual Int_t    CutLED(Long64_t entry);
   virtual int      IDtoModule(int id);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual void     MakeHVTable(int FMstate, int run_id, char* prefile, char* newfile_prefix, int maxevent);
   virtual void     TuneHVValue(int FMstate, double ph, double oldhv, double& newhv);
   virtual void     ScaleHVValue(int FMstate, double gain, double oldhv, double& newhv);
   virtual void     DrawPDF(TString& f, TH1F** h);
   virtual void     LEDHist(int FMstate, int run_id, double scale, TH1F* (&h)[8], TH1F* (&hs)[8], TH1F* (&hoff)[8], TH1F* (&hsoff)[8], int maxevent);
   virtual void     MakePDF(int run_id, char* outfile, int maxevent);
   virtual void     CheckWaveform(int run_id, char* outfile, int maxevent);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef E16ANA_LGOnlineAnalyzer_cxx
E16ANA_LGOnlineAnalyzer::E16ANA_LGOnlineAnalyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("root/run040034.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("root/run040034.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

E16ANA_LGOnlineAnalyzer::~E16ANA_LGOnlineAnalyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t E16ANA_LGOnlineAnalyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t E16ANA_LGOnlineAnalyzer::LoadTree(Long64_t entry)
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

void E16ANA_LGOnlineAnalyzer::Init(TTree *tree)
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
   fChain->SetBranchAddress("Multi", &Multi, &b_Multi);
   fChain->SetBranchAddress("TrgMulti", &TrgMulti, &b_TrgMulti);
   fChain->SetBranchAddress("SL", &SL, &b_SL);
   fChain->SetBranchAddress("SR", &SR, &b_SR);
   fChain->SetBranchAddress("SL2", &SL2, &b_SL2);
   fChain->SetBranchAddress("SR2", &SR2, &b_SR2);
   fChain->SetBranchAddress("IM3", &IM3, &b_IM3);
   fChain->SetBranchAddress("IM2", &IM2, &b_IM2);
   fChain->SetBranchAddress("Module", &Module, &b_Module);
   fChain->SetBranchAddress("Block", &Block, &b_Block);
   fChain->SetBranchAddress("PeakHeight", &PeakHeight, &b_PeakHeight);
   fChain->SetBranchAddress("PeakTime", &PeakTime, &b_PeakTime);
   fChain->SetBranchAddress("Timing", &Timing, &b_timing);
   fChain->SetBranchAddress("Baseline", &Baseline, &b_Baseline);
   fChain->SetBranchAddress("BaselineRms", &BaselineRms, &b_BaselineRms);
   fChain->SetBranchAddress("Integral", &Integral, &b_Integral);
   fChain->SetBranchAddress("Falltime", &Falltime, &b_Falltime);
   fChain->SetBranchAddress("SpikeFlag", &SpikeFlag, &b_SpikeFlag);
   fChain->SetBranchAddress("CalibTiming", &CalibTiming, &b_CalibTiming);
   fChain->SetBranchAddress("EnergyDeposit", &EnergyDeposit, &b_EnergyDeposit);
   fChain->SetBranchAddress("Dst1Flag", &Dst1Flag, &b_Dst1Flag);
   fChain->SetBranchAddress("Gpos", Gpos, &b_Gpos);
   fChain->SetBranchAddress("Lpos", Lpos, &b_Lpos);
   fChain->SetBranchAddress("Waveform", Waveform, &b_Waveform);
   fChain->SetBranchAddress("TrgTiming", &TrgTiming, &b_TrgTiming);
   fChain->SetBranchAddress("Trg", &Trg, &b_Trg);
   fChain->SetBranchAddress("TrgwTRK", &TrgwTRK, &b_TrgwTRK);
   Notify();
}

Bool_t E16ANA_LGOnlineAnalyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void E16ANA_LGOnlineAnalyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t E16ANA_LGOnlineAnalyzer::CutData(Long64_t entry)
{
  if( PeakHeight<25 || PeakHeight>180 ){return -1;}
  // else if( PeakTime<90 && PeakTime>110 ){return -1;}
  else if( TrgTiming<3120 || TrgTiming>3150 ){return -1;}
  // else if( fabs(TrgTiming)>15 ){return -1;}// 20mV thr
  // else if( Trg ){return -1;}// 200mV thr
  else{return 1;}
}
Int_t E16ANA_LGOnlineAnalyzer::CutLED(Long64_t entry)
{
  return 1;
}
int E16ANA_LGOnlineAnalyzer::IDtoModule(int id)
{
  if(id>=1000){
    return -1;
  }
  int tmp = (id-1)/38;
  if(tmp==0){return 106;}
  else if(tmp==1){return 107;}
  else if(tmp==2){return 108;}
  else if(tmp==3){return 104;}
  else if(tmp==4){return 103;}
  else if(tmp==5){return 102;}
  else if(tmp==6){return 109;}
  else if(tmp==7){return 101;}
  else{
    std::cout<<"invalid ID"<<std::endl;
    return -100;
  }
}
void E16ANA_LGOnlineAnalyzer::TuneHVValue(int FMstate, double ph, double oldhv, double& newhv)
{
  newhv = oldhv*pow(standard_phmean/ph,1./gain_index[FMstate]);
}
void E16ANA_LGOnlineAnalyzer::ScaleHVValue(int FMstate, double gain, double oldhv, double& newhv)
{
  newhv = oldhv*pow(gain,1./gain_index[FMstate]);
}
void E16ANA_LGOnlineAnalyzer::DrawPDF(TString& fpdf, TH1F** h)
{
  TCanvas* c = new TCanvas("c","c",1000,700);
  c->SaveAs(fpdf+"[","pdf");
  for(int i=0;i<10;i++){
    c->Clear();
    c->Divide(10,10);
    for(int j=0;j<100;j++){
      c->cd(j+1);
      h[i*100+j]->Draw("hist");
    }
    c->SaveAs(fpdf,"pdf");
  }
  c->SaveAs(fpdf+"]","pdf");
}
#endif // #ifdef E16ANA_LGOnlineAnalyzer_cxx
