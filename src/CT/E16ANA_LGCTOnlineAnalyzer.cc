#define E16ANA_LGCTOnlineAnalyzer_cxx
#include "E16ANA_LGCTOnlineAnalyzer.hh"
#include "E16ANA_CTBasic.hh"
#include "E16ANA_CTCheckHist.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGCheckHist.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void E16ANA_LGCTOnlineAnalyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L E16ANA_LGCTOnlineAnalyzer.C
//      root> E16ANA_LGCTOnlineAnalyzer t
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
void E16ANA_LGCTOnlineAnalyzer::MakeCTPDF(int run_id, char* outfile, int maxevent)
{
  if (fChain == 0) return;

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  E16ANA_CTBasic ctbasic;
  ctbasic.SetMap();

  auto *cthists = new E16ANA_CTCheckHist();

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

    if(LGTrgTiming==0&&CT0PeakHeight>30.){
      cthists->Fill(CT0Module,CT0Block,CT0PeakHeight,CT0PeakTime,CT0Timing,CT0Baseline,CT0BaselineRms,0.,0);
    }
    if(LGTrgTiming==0&&CT1PeakHeight>30.){
      cthists->Fill(CT1Module,CT1Block,CT1PeakHeight,CT1PeakTime,CT1Timing,CT1Baseline,CT1BaselineRms,0.,0);
    }

  }

  TString pdfout = Form("%s",outfile);
  TCanvas* c = new TCanvas("c","c",1400,700);
  c->SaveAs(pdfout+"[","pdf");
  cthists->Draw(pdfout,c);
  cthists->Draw2D(pdfout,c);
  cthists->DrawEach(pdfout,c);
  c->SaveAs(pdfout+"]","pdf");

}
void E16ANA_LGCTOnlineAnalyzer::MakeLGPDF(int run_id, char* outfile, int maxevent)
{
  if (fChain == 0) return;

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);

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

    if( (CT0PeakHeight>20.&&CT0PeakTime>120&&CT0PeakTime<160) || (CT1PeakHeight>20.&&CT1PeakTime>120&&CT1PeakTime<160) ){
      lghists->Fill(LGModule,LGBlock,LGPeakHeight,LGPeakTime,LGTiming,LGBaseline,LGBaselineRms,0.,0);
    }

  }

  TString pdfout = Form("%s",outfile);
  TCanvas* c = new TCanvas("c","c",1400,700);
  c->SaveAs(pdfout+"[","pdf");
  lghists->Draw(pdfout,c);
  lghists->Draw2D(pdfout,c);
  lghists->DrawEach(pdfout,c);
  c->SaveAs(pdfout+"]","pdf");

}
