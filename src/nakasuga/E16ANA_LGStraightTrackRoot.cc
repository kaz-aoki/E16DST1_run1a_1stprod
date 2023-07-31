#define E16ANA_LGStraightTrackRoot_cxx
#include "E16ANA_LGStraightTrackRoot.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void E16ANA_LGStraightTrackRoot::Loop()
{
//   In a ROOT session, you can do:
//      root> .L E16ANA_LGStraightTrackRoot.C
//      root> E16ANA_LGStraightTrackRoot t
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

void E16ANA_LGStraightTrackRoot::Residual()
{
   if (fChain == 0) return;

   TFile* outfile = new TFile("hist.root","recreate");

   TH1F* hresx[9];
   TH1F* hresy[9];
   for(int i=0;i<9;i++){
     hresx[i] = new TH1F(Form("hresx%d",i),Form("hresx%d",i),100,-800,800);
     hresy[i] = new TH1F(Form("hresy%d",i),Form("hresy%d",i),100,-800,800);
   }


   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      for(int itrack=0; itrack<n_tracks; itrack++){
	int module = trk_mid->at(itrack);
	for(int ilg=0; ilg<n_lg_hits; ilg++){
	  double t = lg_t->at(ilg);
	  double adc = lg_adc->at(ilg);
	  int mid = lg_mid->at(ilg);
	  if( t>90 && t<110 && adc>20 && mid==module ){
	    double resx = lg_lx->at(ilg) - trk_lx->at(itrack);
	    double resy = lg_ly->at(ilg) - trk_ly->at(itrack);
	    hresx[mid-101]->Fill(resx);
	    hresy[mid-101]->Fill(resy);
	  }
	}
      }

   }

   outfile->Write();
   outfile->Close();

}
