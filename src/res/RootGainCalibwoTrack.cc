#define RootGainCalibwoTrack_cxx
#include "RootGainCalibwoTrack.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <stdio.h>
#include <iostream>

void RootGainCalibwoTrack::Loop()
{
//   In a ROOT session, you can do:
//      root> .L RootGainCalibwoTrack.C
//      root> RootGainCalibwoTrack t
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

   int mid[4] = {106,107,103,104};
   int cid[42];
   for(int i=0;i<7;i++){
     for(int j=0;j<6;j++){
       cid[i+j*7] = i+j*10;
     }
   }
   TCanvas* c[3][4];
   for(int k=0;k<3;k++){
     for(int j=0;j<4;j++){
       c[k][j] = new TCanvas(Form("c%d%d",k,j),Form("c%d%d",k,j),1000,700);
       c[k][j]->Divide(7,6);
     }
   }
   TH1F* h[3][4][42];
   for(int k=0;k<3;k++){
     for(int i=0;i<4;i++){
       for(int j=0;j<42;j++){
	 h[k][i][j] = new TH1F(Form("h%d%d%d",k,i,j),Form("lgadc_%d_%d-%d",k,mid[i],cid[j]),50,0,200);
       }
     }
   }

   Long64_t nentries = fChain->GetEntriesFast();
   std::cout<<"nentries: "<<nentries<<std::endl;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if(ientry%100000==0){std::cout<<"loop: "<<ientry<<std::endl;}

      if(lg_mid==102||lg_mid==108) continue;
      int midel = (lg_mid-103+2)%5;
      int cidel = (lg_cid/10)*7 + lg_cid%10;
      if(midel<0||midel>3){
	std::cout<<"invalid mid"<<std::endl;
	continue;
      }
      if(cidel<0||cidel>41){
	std::cout<<"invalid cid"<<std::endl;
	continue;
      }
      if( !lg_trg_run && n_hbds>0 ){
	h[0][midel][cidel]->Fill(lg_adc);
	if( (lg_mid-105)>0 && lg_leftside_adc<-100 ){
	  h[1][midel][cidel]->Fill(lg_adc);
	}
	if( (lg_mid-105)<0 && lg_rightside_adc<-100 ){
	  h[1][midel][cidel]->Fill(lg_adc);
	}
	if( n_gtr300xs>0 && n_gtr300ys>0 ){
	  h[2][midel][cidel]->Fill(lg_adc);
	}
      }
   }

   //Draw
   for(int k=0;k<3;k++){
     for(int j=0;j<4;j++){
       for(int i=0;i<42;i++){
	 c[k][j]->cd(i+1);
	 h[k][j][41-i]->Draw();
       }
     }
   }

   TString fout = "block.pdf";
   c[0][0]->SaveAs(fout+"[","pdf");
   for(int k=0;k<3;k++){
     for(int j=0;j<4;j++){
       c[k][j]->SaveAs(fout,"pdf");
     }
   }
   c[2][3]->SaveAs(fout+"]","pdf");

}

void RootGainCalibwoTrack::Residual(){

   if (fChain == 0) return;

   //hist
   int mid[4] = {106,107,103,104};
   TCanvas* c[4];
   for(int j=0;j<4;j++){
     c[j] = new TCanvas(Form("c%d",j),Form("c%d",j),1000,700);
     c[j]->Divide(2,2);
   }
   TH1F* hresx[4];
   TH1F* hresy[4];
   for(int i=0;i<4;i++){
     hresx[i] = new TH1F(Form("hresx%d",i),Form("resx_%d",mid[i]),15,-7.5,7.5);
     hresy[i] = new TH1F(Form("hresy%d",i),Form("resy_%d",mid[i]),15,-7.5,7.5);
   }

   //loop
   std::vector<int> lglx[4];
   std::vector<int> lgly[4];
   std::vector<int> trklx[4];
   std::vector<int> trkly[4];
   int pre_eventid = -10000;
   Long64_t nentries = fChain->GetEntriesFast();
   std::cout<<"nentries: "<<nentries<<std::endl;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;

     if(ientry%100000==0){std::cout<<"loop: "<<ientry<<std::endl;}

     if(lg_mid==102||lg_mid==108) continue;
     int midel = (lg_mid-103+2)%5;

     if(event_id==pre_eventid){
       lglx[midel].push_back(lg_cid%10);
       lgly[midel].push_back(lg_cid/10);
       if( TrackSelection(ientry)>0 ){
	 trklx[midel].push_back(lg_cid%10);
	 trkly[midel].push_back(lg_cid/10);
       }
     }
     else{
       for(int imod=0;imod<4;imod++){
	 for(int itrk=0;itrk<trklx[imod].size();itrk++){
	   for(int ilg=0;ilg<lglx[imod].size();ilg++){
	     hresx[imod]->Fill(lglx[imod].at(ilg)-trklx[imod].at(itrk));
	     hresy[imod]->Fill(lgly[imod].at(ilg)-trkly[imod].at(itrk));
	   }
	 }
	 lglx[imod].clear();
	 lgly[imod].clear();
	 trklx[imod].clear();
	 trkly[imod].clear();
       }
     }

     pre_eventid = event_id;

   }//loop

   //Draw

   // TString fout = "block.pdf";
   // c[0][0]->SaveAs(fout+"[","pdf");
   // for(int k=0;k<3;k++){
   //   for(int j=0;j<4;j++){
   //     c[k][j]->SaveAs(fout,"pdf");
   //   }
   // }
   // c[2][3]->SaveAs(fout+"]","pdf");

}
