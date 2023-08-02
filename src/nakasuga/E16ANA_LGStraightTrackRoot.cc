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

void E16ANA_LGStraightTrackRoot::Residual(char* out_pdf_name, char* out_root_name, int maxevent)
{
   if (fChain == 0) return;

   TFile* outfile = new TFile(out_root_name,"recreate");
   TString fout = Form("%s",out_pdf_name);
   TCanvas* c = new TCanvas("c","c",1000,700);

   HistInit();

   std::vector<std::vector<hitset>> mixevents[9];

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if( jentry%10000==0 ) {std::cout<<jentry<<std::endl;}
      if( maxevent!=-1 && jentry>maxevent ){break;}
      if( !EventSelection() ) continue;

      //calc residual
      for(int itrack=0; itrack<n_tracks; itrack++){
	int trkmid = trk_mid->at(itrack)-101;
	if( !TrackSelection(itrack) ) continue;
	FillTrack(itrack);

	//fore
	for(int ilg=0; ilg<n_lg_hits; ilg++){
	  int lgmid = lg_mid->at(ilg)-101;
	  if( lgmid != trkmid ) continue;
	  if( !HitSelection(ilg) ) continue;
	  FillResidualFore(hres, itrack, ilg);
	}

	//mix
	for(int ilg=0; ilg<mixevents[trkmid].size(); ilg++){
	  for(int jlg=0; jlg<mixevents[trkmid].at(ilg).size(); jlg++){
	    hitset tmphit = mixevents[trkmid].at(ilg).at(jlg);
	    FillResidualMix(hres, itrack, tmphit);
	  }
	}

      }//track loop

      FillNotAssociateHit();

      //add mix
      std::vector<hitset> mixhits[9];
      for(int ilg=0; ilg<n_lg_hits; ilg++){
	int lgmid = lg_mid->at(ilg)-101;
	hitset tmphit;
	SetHitset(ilg,tmphit);
	if( !HitSelection(tmphit) ) continue;
	mixhits[lgmid].push_back(tmphit);
      }
      for(int im=0; im<9; im++){
	mixevents[im].push_back(mixhits[im]);
	if( mixevents[im].size() > mixeventmax ){
	  mixevents[im].erase( mixevents[im].begin() );
	}
      }

   }//event loop

   c->SaveAs(fout+"[","pdf");
   DrawNotAssociateHit(fout, c);
   DrawTrack(fout, c);
   DrawResidual(fout, c, hres);
   DrawAssociateHit(fout, c);
   c->SaveAs(fout+"]","pdf");

   outfile->Write();
   outfile->Close();

}
