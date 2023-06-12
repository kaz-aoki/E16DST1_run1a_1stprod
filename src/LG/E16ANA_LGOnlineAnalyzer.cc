#define E16ANA_LGOnlineAnalyzer_cxx
#include "E16ANA_LGOnlineAnalyzer.hh"
#include "E16ANA_EIDSingleTrackAnalyzer.hh"
#include "E16ANA_LGBasic.hh"
#include <TH2.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TLegend.h>
#include <TCut.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TPaveStats.h>
#include <TRandom.h>
#include <TGraph2D.h>
#include <TH1.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "TROOT.h"

void E16ANA_LGOnlineAnalyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L E16ANA_LGOnlineAnalyzer.C
//      root> E16ANA_LGOnlineAnalyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

void E16ANA_LGOnlineAnalyzer::MakeHVTable(int FMstate, int run_id, char* prefile, char* newfile_prefix, int maxevent)
{
  if (fChain == 0) return;

  TFile* froot = new TFile(Form("%s.root",newfile_prefix),"recreate");
  TH1F* h[1000];
  for(int i=0;i<1000;i++){
    h[i] = new TH1F(Form("h%04d",i),Form("h%04d",i),200,0,200);
  }

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  E16ANA_LGBasic lgbasic;
  lgbasic.SetMap();

  Long64_t n_entries = fChain->GetEntries();
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  int nevent=0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
    if( maxevent!=-1&&nevent>maxevent ){break;}
    nevent++;

    if (CutData(ientry) < 0) continue;

    auto spec = lgbasic.GetSpec(Module,Block);
    int hvch = spec->HVCH;
    h[hvch]->Fill(PeakHeight);
  }

  TString fpdf = Form("%s.pdf",newfile_prefix);
  DrawPDF(fpdf,h);

  std::ifstream fin(prefile);
  char ext[] = ".txt";
  strcat(newfile_prefix,ext);
  std::ofstream fout(newfile_prefix);
  while(!fin.eof()){
    std::string thvch, tname;
    double thvval, tlimit;
    int tid;
    fin >> thvch >> tname >> thvval >> tlimit >> tid;
    if(fin.eof()) break;
    thvch.erase(0,1);
    int hvch = stoi(thvch);
    if( IDtoModule(tid)==-1 ){// vacant ch
      fout <<"u"<< thvch <<" "<< tname <<" "<< thvval <<" "<< tlimit <<" "<< tid <<std::endl;
    }
    // else if( IDtoModule(tid)>=102 && IDtoModule(tid)<=108 ){// for FMON
    //   fout <<"u"<< thvch <<" "<< tname <<" "<< thvval <<" "<< tlimit <<" "<< tid <<std::endl;
    // }
    else{
      double newhvval;
      // double ph = h[hvch]->GetMean();
      // TuneHVValue(FMstate, ph, thvval, newhvval);
      double gain = 2.;
      ScaleHVValue(FMstate, gain, thvval, newhvval);
      fout <<"u"<< thvch <<" "<< tname <<" "<< newhvval <<" "<< tlimit <<" "<< tid <<std::endl;
    }
  }

  froot->Write();
  froot->Close();
}

void E16ANA_LGOnlineAnalyzer::LEDHist(int FMstate, int run_id, double scale, TH1F* (&h)[8], TH1F* (&hs)[8], int maxevent)
{
  if (fChain == 0) return;

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  E16ANA_LGBasic lgbasic;
  lgbasic.SetMap();

  int ledmid[8] = {104,104,103,103,102,102,106,107};
  int ledcid[8] = {  5,  2,  5,  2,  5,  2,  0,  0};
  for(int i=0;i<8;i++){
    auto spec = lgbasic.GetSpec(ledmid[i],ledcid[i]);
    int ip = spec->IP;
    double wf_type = spec->WF_TYPE;
    std::cout<<wf_type<<std::endl;
    if(wf_type>0.4&&wf_type<0.5){
      wf_type = 1400.;
    }
    else if(wf_type>0.2&&wf_type<0.3){
      wf_type = 900;
    }
    h[i] = new TH1F(Form("h%d",i),Form("%d-%d IP%d upto%1.0fmV",ledmid[i],ledcid[i],ip,wf_type),1500,0,1500);
    hs[i] = new TH1F(Form("hs%d",i),Form("%d-%d IP%d upto%1.0fmV",ledmid[i],ledcid[i],ip,wf_type),1500,0,1500);
  }

  Long64_t n_entries = fChain->GetEntries();
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  int nevent=0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
    if( maxevent!=-1&&nevent>maxevent ){break;}
    nevent++;

    if (CutLED(ientry) < 0) continue;

    for(int iled=0;iled<8;iled++){
      if(Module==ledmid[iled]&&Block==ledcid[iled]){
	h[iled]->Fill(PeakHeight);
	hs[iled]->Fill(PeakHeight/scale);
      }
    }
  }

}

// void E16ANA_LGOnlineAnalyzer::MakeHVTableScale(std::string prefile, std::string newfile)
// {
//   std::ifstream fin(prefile);
//   std::vector<double> hvs[9];
//   while(!fin.eof()){
//     std::string thvch, tname;
//     double thvval, tlimit;
//     int tid;
//     fin >> thvch >> tname >> thvval >> tlimit >> tid;
//     if(fin.eof()) break;
//     for(int i=0;i<9;i++){
//       if( IDtoModule(tid)==i+101 ){
// 	hvs[i].push_back(thvval);
//       }
//     }
//   }
//   double hvmean[9] = {0.};
//   for(int i=0;i<9;i++){
//     if( hvs[i].size()!=38 ) continue;
//     for(int j=0;j<38;j++){
//       hvmean[i]+=hvs[i].at(j);
//     }
//     hvmean[i] = hvmean[i]/38.;
//   }

//   std::ofstream fout(newfile);
//   while(!fin.eof()){
//     std::string thvch, tname;
//     double thvval, tlimit;
//     int tid;
//     fin >> thvch >> tname >> thvval >> tlimit >> tid;
//     if(fin.eof()) break;
//     if( IDtoModule(tid)==-1 ){// vacant ch
//       fout <<"u"<< thvch <<" "<< tname <<" "<< thvval <<" "<< tlimit <<" "<< tid <<std::endl;
//     }
//     else{
//       double newhvval = thvval*p;
//       fout <<"u"<< thvch <<" "<< tname <<" "<< thvval <<" "<< tlimit <<" "<< tid <<std::endl;
//     }
//   }

// }
