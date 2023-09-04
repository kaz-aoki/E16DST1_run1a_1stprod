#define E16ANA_LGOnlineAnalyzer_cxx
#include "E16ANA_LGOnlineAnalyzer.hh"
#include "E16ANA_EIDSingleTrackAnalyzer.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGCheckHist.hh"
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
#include <stdlib.h>
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
// #ifdef TUNE_ON
      // double ph = h[hvch]->GetMean();
      // TuneHVValue(FMstate, ph, thvval, newhvval);
      // std::cout<<hvch<<" ph:"<<ph<<"=>"<<standard_phmean<<", HV:"<<thvval<<"=>"<<newhvval<<std::endl;
      // if(hvch==111){//107-2
      // 	newhvval = 1328.26;
      // }
// #else
      double gain = 1.5;
      ScaleHVValue(FMstate, gain, thvval, newhvval);
// #endif
      fout <<"u"<< thvch <<" "<< tname <<" "<< newhvval <<" "<< tlimit <<" "<< tid <<std::endl;
    }
  }

  froot->Write();
  froot->Close();
}

void E16ANA_LGOnlineAnalyzer::LEDHist(int FMstate, int run_id, double scale, TH1F* (&h)[8], TH1F* (&hs)[8], TH1F* (&hoff)[8], TH1F* (&hsoff)[8], int maxevent)
{
  if (fChain == 0) return;

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  E16ANA_LGBasic lgbasic;
  lgbasic.SetMap();

  int ledmid[8] = {104,104,103,103,102,102,106,107};
  int ledcid[8] = {  5,  2,  5,  2,  5,  2,  0,  0};
  int maxbin[8] = {300,150,400,500,500,1000,200,600};
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
    h[i] = new TH1F(Form("h%d",i),Form("%d-%d IP%d upto%1.0fmV",ledmid[i],ledcid[i],ip,wf_type),100,0,1500);
    hs[i] = new TH1F(Form("hs%d",i),Form("%d-%d IP%d upto%1.0fmV",ledmid[i],ledcid[i],ip,wf_type),maxbin[i]/2,0,maxbin[i]);
    hoff[i] = new TH1F(Form("hoff%d",i),Form("%d-%d beamOFF IP%d upto%1.0fmV",ledmid[i],ledcid[i],ip,wf_type),100,0,1500);
    hsoff[i] = new TH1F(Form("hsoff%d",i),Form("%d-%d beamOFF IP%d upto%1.0fmV",ledmid[i],ledcid[i],ip,wf_type),maxbin[i]/2,0,maxbin[i]);
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
      if(Module==ledmid[iled]&&Block==ledcid[iled]&&PeakTime>=115&&PeakTime<=130){
	// std::cout<<"***"<<TimeStampInSpill<<"***"<<std::endl;
	if(TimeStampInSpill>3.e8/8.&&TimeStampInSpill<2.e9/8.){
	  // std::cout<<"spillON"<<std::endl;
	  h[iled]->Fill(PeakHeight);
	  hs[iled]->Fill(PeakHeight/scale);
	}
	else if(TimeStampInSpill>3.e8){
	  // std::cout<<"spillOFF"<<std::endl;
	  hoff[iled]->Fill(PeakHeight);
	  hsoff[iled]->Fill(PeakHeight/scale);
	}
	else{
	  // std::cout<<"other"<<std::endl;
	}
      }
    }
  }

}

void E16ANA_LGOnlineAnalyzer::MakePDF(int run_id, char* outfile, int maxevent)
{
  if (fChain == 0) return;

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  E16ANA_LGBasic lgbasic;
  lgbasic.SetMap();

  auto *lghists = new E16ANA_LGCheckHist();

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

    if(PeakHeight>20&&TrgTiming>3050&&TrgTiming<3200){
    // if(Trg){
    // if(TrgTiming>3120&&TrgTiming<3150){
    // if(TrgTiming>3120&&TrgTiming<3150&&PeakHeight>25&&PeakHeight<180){
      lghists->Fill(Module,Block,PeakHeight,PeakTime,Timing,Baseline,BaselineRms,Integral,Dst1Flag);
    }

  }

  TString pdfout = Form("%s",outfile);
  TCanvas* c = new TCanvas("c","c",1400,700);
  c->SaveAs(pdfout+"[","pdf");
  lghists->Draw(pdfout,c);
  lghists->Draw2D(pdfout,c);
  lghists->DrawEach(pdfout,c);
  c->SaveAs(pdfout+"]","pdf");

  lghists->MakeT0CalibFile();

}

void E16ANA_LGOnlineAnalyzer::CheckWaveform(int run_id, char* outfile, int maxevent)
{
  if (fChain == 0) return;

  int nwfs = maxevent;
  maxevent = maxevent*304;

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  E16ANA_LGBasic lgbasic;
  lgbasic.SetMap();

  Long64_t n_entries = fChain->GetEntries();
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  int wfcount[8][42] = {0};
  // double wf[8][42][nwfs][200] = {0.};
  double**** wf = NULL;
  wf = (double****)malloc(8*sizeof(double));
  if(wf==NULL){std::cerr<<"err0"<<std::endl;return;}
  for(int i=0;i<8;i++){
    wf[i] = (double***)malloc(42*sizeof(double));
    if(wf[i]==NULL){std::cerr<<"err1 "<<i<<std::endl;return;}
    for(int j=0;j<42;j++){
      wf[i][j] = (double**)malloc(nwfs*sizeof(double));
      if(wf[i][j]==NULL){std::cerr<<"err2 "<<i<<" "<<j<<std::endl;return;}
      for(int k=0;k<nwfs;k++){
  	wf[i][j][k] = (double*)malloc(200*sizeof(double));
  	if(wf[i][j][k]==NULL){std::cerr<<"err3 "<<i<<" "<<j<<" "<<k<<std::endl;return;}
      }
    }
  }

  int nevent=0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if (ientry%304000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
    if( maxevent!=-1&&nevent>maxevent ){break;}
    nevent++;

    int ii = E16ANA_LGCheckHist::ModuleToIndex(Module);
    int ij = E16ANA_LGCheckHist::BlockToIndex(Block);
    if( wfcount[ii][ij]>=0 && wfcount[ii][ij]<nwfs ){
      for(int cell=0;cell<200;cell++){
    	wf[ii][ij][wfcount[ii][ij]][cell] = Waveform[cell];
      }
      wfcount[ii][ij]++;
    }

  }

  for(int i=0;i<8;i++){
    for(int j=0;j<42;j++){
      std::cout<<wf[i][j][nwfs-1][100]<<" ";
    }
    std::cout<<std::endl;
  }

  // TGraph* gwf[8][42][nwfs];
  TGraph**** gwf = NULL;
  gwf = (TGraph****)malloc(8*sizeof(TGraph*));
  if(gwf==NULL){std::cerr<<"err0"<<std::endl;return;}
  for(int i=0;i<8;i++){
    gwf[i] = (TGraph***)malloc(42*sizeof(TGraph*));
    if(gwf[i]==NULL){std::cerr<<"err1 "<<i<<std::endl;return;}
    for(int j=0;j<42;j++){
      gwf[i][j] = (TGraph**)malloc(nwfs*sizeof(TGraph*));
      if(gwf[i][j]==NULL){std::cerr<<"err2 "<<i<<" "<<j<<std::endl;return;}
    }
  }
  double x[200];
  for(int cell=0;cell<200;cell++){
    x[cell] = (double)cell;
  }
  TString pdfout = Form("%s",outfile);
  TCanvas* c = new TCanvas("c","c",1400,700);
  c->SaveAs(pdfout+"[","pdf");
  for(int i=0;i<8;i++){
    c->Clear();
    c->Divide(7,6);
    int module = E16ANA_LGCheckHist::IndexToModule(i);
    for(int j=0;j<42;j++){
      c->cd(j+1);
      int block = E16ANA_LGCheckHist::IndexToBlock(j);
      if(!E16ANA_LGCheckHist::IsValidBlockId(block)) continue;
      for(int k=0;k<nwfs;k++){
  	auto spec = lgbasic.GetSpec(module,block);
  	int ip = spec->IP;
  	int drs4ch = spec->DRS4CH;
  	gwf[i][j][k] = new TGraph(200,x,wf[i][j][k]);
  	gwf[i][j][k]->SetTitle(Form("%d-%d %d-%d",module,block,ip,drs4ch));
  	if(k==0){
  	  gwf[i][j][k]->SetMaximum(1400);
  	  gwf[i][j][k]->SetMinimum(-30);
  	  gwf[i][j][k]->Draw("AL");
  	}
  	else{
  	  gwf[i][j][k]->Draw("L");
  	}
      }
    }
    c->cd(1);
    TLegend *leg = new TLegend(0,0,1,1);
    leg->AddEntry((TObject*)0,Form("%d",module),"");
    leg->Draw("sames");
    c->SaveAs(pdfout,"pdf");
    delete leg;
  }
  c->SaveAs(pdfout+"]","pdf");

  free(wf);

}

// void E16ANA_LGOnlineAnalyzer::CheckWaveform(int run_id, char* outfile, int maxevent)
// {
//   if (fChain == 0) return;

//   maxevent = maxevent*304;

//   auto& calib = E16ANA_CalibDBManager::Instance();
//   calib.SetRunID(run_id);
//   E16ANA_LGBasic lgbasic;
//   lgbasic.SetMap();

//   TFile* f = new TFile(Form("%s",outfile),"recreate");
//   TH1F* h = new TH1F("h","h",3000,-1500,1500);
//   TH2F* hh = new TH2F("hh","hh",3000,-1500,1500,2000,-500,1500);

//   Long64_t n_entries = fChain->GetEntries();
//   Long64_t nentries = fChain->GetEntriesFast();
//   Long64_t nbytes = 0, nb = 0;

//   int nevent=0;
//   for (Long64_t jentry=0; jentry<nentries;jentry++) {
//     Long64_t ientry = LoadTree(jentry);
//     if (ientry < 0) break;
//     nb = fChain->GetEntry(jentry);   nbytes += nb;

//     if (ientry%304000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
//     if( maxevent!=-1&&nevent>maxevent ){break;}
//     nevent++;

//     if(Module==101&&Block==32){
//       for(int i=1;i<200;i++){
// 	h->Fill(Waveform[i]-Waveform[i-1]);
// 	hh->Fill(Waveform[i]-Waveform[i-1],Waveform[i]);
//       }
//     }

//   }

//   f->Write();

// }


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
