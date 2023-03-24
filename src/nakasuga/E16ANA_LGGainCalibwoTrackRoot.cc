#define E16ANA_LGGainCalibwoTrackRoot_cxx
#include "E16ANA_LGGainCalibwoTrackRoot.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <stdio.h>
#include <iostream>

void E16ANA_LGGainCalibwoTrackRoot::Loop()
{
//   In a ROOT session, you can do:
//      root> .L E16ANA_LGGainCalibwoTrackRoot.C
//      root> E16ANA_LGGainCalibwoTrackRoot t
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

void E16ANA_LGGainCalibwoTrackRoot::ResidualforLGmix(char* out_file_name, int maxevent)
{

   if (fChain == 0) return;

   int mixevent = 50;

   //hist
   int mid[4] = {106,107,103,104};
   TH1I* hresx[2][4];
   TH1I* hresy[2][4];
   TH1I* hresxd[2][4];
   TH1I* hresyd[2][4];
   TH2I* hres[4];
   for(int j=0;j<2;j++){
     for(int i=0;i<4;i++){
       hresx[j][i] = new TH1I(Form("hresx%d%d",j,i),Form("resx_%d",mid[i]),15,-7.5,7.5);
       hresy[j][i] = new TH1I(Form("hresy%d%d",j,i),Form("resy_%d",mid[i]),15,-7.5,7.5);
       hresxd[j][i] = new TH1I(Form("hresxd%d%d",j,i),Form("resx_mix_%d",mid[i]),15,-7.5,7.5);
       hresyd[j][i] = new TH1I(Form("hresyd%d%d",j,i),Form("resy_mix_%d",mid[i]),15,-7.5,7.5);
     }
   }
   for(int i=0;i<4;i++){
     hres[i] = new TH2I(Form("hres%d",i),Form("resx_%d",mid[i]),15,-7.5,7.5,15,-7.5,7.5);
   }

   //loop
   std::vector<int> trkcids[4];//w HBD hit
   std::vector<int> lgcids[4];
   bool trackexist[4] = {false, false, false, false};
   std::vector<std::vector<int>> pre_lgcids[4];
   int pre_eventid = -10000;
   Long64_t nentries = fChain->GetEntriesFast();
   std::cout<<"nentries: "<<nentries<<std::endl;
   Long64_t nbytes = 0, nb = 0;

   int nevent = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;

     if(ientry%100000==0){std::cout<<"loop: "<<ientry<<std::endl;}
     if(maxevent!=-1&&nevent>maxevent) break;

     if(lg_mid==102||lg_mid==108) continue;
     int midel = (lg_mid-103+2)%5;

     if(TrackSelection(ientry)<0) continue;

     if(event_id==pre_eventid){
       trackexist[midel] = true;
       trkcids[midel].push_back(lg_cid);
       lgcids[midel].resize( lg_cids->size() );
       copy( lg_cids->begin(), lg_cids->end(), lgcids[midel].begin() );
     }
     else{
       //calc residual
       for(int imod=0;imod<4;imod++){
	 for(int itrk=0;itrk<trkcids[imod].size();itrk++){
	   int trklx = (trkcids[imod].at(itrk))%10;
	   int trkly = (trkcids[imod].at(itrk))/10;
	   for(int ilg=0;ilg<lgcids[imod].size();ilg++){
	     int lglx = (lgcids[imod].at(ilg))%10;
	     int lgly = (lgcids[imod].at(ilg))/10;
	     hresx[0][imod]->Fill( lglx - trklx );
	     hresy[0][imod]->Fill( lgly - trkly );
	     hres[imod]->Fill( lglx-trklx, lgly-trkly );
	     if( lgly == trkly ){
	       hresx[1][imod]->Fill( lglx - trklx );
	     }
	     if( lglx == trklx ){
	       hresy[1][imod]->Fill( lgly - trkly );
	     }
	   }//lg hit loop
	   if(pre_lgcids[imod].size()!=0){//mix
	     for(int ilgm=0;ilgm<pre_lgcids[imod].size();ilgm++){
	       for(int ilg=0;ilg<pre_lgcids[imod].at(ilgm).size();ilg++){
		 int lglx = pre_lgcids[imod].at(ilgm).at(ilg)%10;
		 int lgly = pre_lgcids[imod].at(ilgm).at(ilg)/10;
		 hresxd[0][imod]->Fill( lglx - trklx );
		 hresyd[0][imod]->Fill( lgly - trkly );
		 if( lgly == trkly ){
		   hresxd[1][imod]->Fill( lglx - trklx );
		 }
		 if( lglx == trklx ){
		   hresyd[1][imod]->Fill( lgly - trkly );
		 }
	       }
	     }
	   }//mix
	 }// track loop

	 if( trackexist[imod] ){
	   pre_lgcids[imod].push_back( lgcids[imod] );
	   if( pre_lgcids[imod].size()>mixevent ){
	     pre_lgcids[imod].erase(pre_lgcids[imod].begin());
	   }
	 }
	 trackexist[imod] = false;
	 trkcids[imod].clear();
	 lgcids[imod].clear();

       }
       //calc residual

       trackexist[midel] = true;
       trkcids[midel].push_back(lg_cid);
       lgcids[midel].resize( lg_cids->size() );
       copy( lg_cids->begin(), lg_cids->end(), lgcids[midel].begin() );
     }

     pre_eventid = event_id;

     nevent++;

   }//event loop

   //Draw
   TCanvas* c[4];
   TH1F* hresxsub[4];
   TH1F* hresysub[4];
   for(int j=0;j<4;j++){
     c[j] = new TCanvas(Form("c%d",j),Form("c%d",j),1000,700);
     c[j]->Divide(2,2);
   }
   for(int i=0;i<4;i++){
     c[i]->cd(1);
     hresx[1][i]->Draw();
     hresxd[1][i]->SetLineColor(6);
     hresxd[1][i]->Scale(1./(double)mixevent);
     hresxd[1][i]->Draw("hist sames");
     c[i]->cd(2);
     hresy[1][i]->Draw();
     hresyd[1][i]->SetLineColor(6);
     hresyd[1][i]->Scale(1./(double)mixevent);
     hresyd[1][i]->Draw("hist sames");
     c[i]->cd(3);
     hresxsub[i] = (TH1F*)hresx[1][i]->Clone();
     hresxsub[i]->Add(hresxd[1][i],-1);
     hresxsub[i]->Draw("hist");
     c[i]->cd(4);
     hresysub[i] = (TH1F*)hresy[1][i]->Clone();
     hresysub[i]->Add(hresyd[1][i],-1);
     hresysub[i]->Draw("hist");
   }
   TCanvas* c2d = new TCanvas("c2d","c2d",1000,700);
   c2d->Divide(2,2);
   for(int i=0;i<4;i++){
     c2d->cd(i+1);
     hres[i]->Draw("colz");
   }

   TString fout = Form("%s", out_file_name);
   TCanvas* cdef = new TCanvas("cdef","cdef",700,500);
   cdef->SaveAs(fout+"[","pdf");
   for(int j=0;j<4;j++){
     c[j]->SaveAs(fout,"pdf");
   }
   c2d->SaveAs(fout,"pdf");
   cdef->SaveAs(fout+"]","pdf");
}

void E16ANA_LGGainCalibwoTrackRoot::ResidualforGTRymix(int lid, char* out_file_name, int maxevent)
{
   if( lid<0 || lid>2 ) return;

   if (fChain == 0) return;

   int mixevent = 50;

   //hist
   int mid[6] = {106,107,108,102,103,104};
   TH1F* hresx[2][6];
   TH1F* hresy[2][6];
   TH1F* hresxd[2][6];
   TH1F* hresyd[2][6];
   int detresmax[3] = { 150, 300, 400};
   int detresmin[3] = {-150,-300,-400};
   for(int j=0;j<2;j++){
     for(int i=0;i<6;i++){
       hresx[j][i] = new TH1F(Form("hresx%d%d",j,i),Form("resx_%d",mid[i]),100,detresmin[lid],detresmax[lid]);
       hresy[j][i] = new TH1F(Form("hresy%d%d",j,i),Form("resy_%d",mid[i]),100,detresmin[lid],detresmax[lid]);
       hresxd[j][i] = new TH1F(Form("hresxd%d%d",j,i),Form("resx_mix_%d",mid[i]),100,detresmin[lid],detresmax[lid]);
       hresyd[j][i] = new TH1F(Form("hresyd%d%d",j,i),Form("resy_mix_%d",mid[i]),100,detresmin[lid],detresmax[lid]);
     }
   }

   //loop
   std::vector<double> trklxs[6];// @ GTR plane
   std::vector<double> trklys[6];// @ GTR plane
   std::vector<double> gtrlxs[6];
   std::vector<double> gtrlys[6];
   bool trackexist[6] = {false, false, false, false, false, false};
   std::vector<std::vector<double>> pre_gtrlxs[6];
   std::vector<std::vector<double>> pre_gtrlys[6];
   int pre_eventid = -10000;
   Long64_t nentries = fChain->GetEntriesFast();
   std::cout<<"nentries: "<<nentries<<std::endl;
   Long64_t nbytes = 0, nb = 0;

   int nevent = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;

     if(ientry%100000==0){std::cout<<"loop: "<<ientry<<std::endl;}
     if(maxevent!=-1&&nevent>maxevent) break;

     // if(lg_mid==102||lg_mid==108) continue;
     int midel = (gtr_mid-102+3)%7;

     if(TrackSelection(ientry)<0) continue;

     if(event_id==pre_eventid){
       trackexist[midel] = true;
       double cx, cy;
       std::vector<double> lxs;
       std::vector<double> lys;
       SetAllCls(ientry,lid,cx,cy,lxs,lys);
       trklxs[midel].push_back(cx);
       trklys[midel].push_back(cy);
       gtrlxs[midel].resize( lxs.size() );
       copy( lxs.begin(), lxs.end(), gtrlxs[midel].begin() );
       gtrlys[midel].resize( lys.size() );
       copy( lys.begin(), lys.end(), gtrlys[midel].begin() );
     }
     else{
       //calc residual
       for(int imod=0;imod<6;imod++){
	 for(int itrk=0;itrk<trklxs[imod].size();itrk++){
	   int trklx = trklxs[imod].at(itrk);
	   int trkly = trklys[imod].at(itrk);
	   for(int igtr=0;igtr<gtrlxs[imod].size();igtr++){
	     int gtrlx = gtrlxs[imod].at(igtr);
	     hresx[0][imod]->Fill( gtrlx - trklx );
	   }
	   for(int igtr=0;igtr<gtrlys[imod].size();igtr++){
	     int gtrly = gtrlys[imod].at(igtr);
	     hresy[0][imod]->Fill( gtrly - trkly );
	   }
	   if(pre_gtrlxs[imod].size()!=0){//mix
	     for(int igtrm=0;igtrm<pre_gtrlxs[imod].size();igtrm++){
	       for(int igtr=0;igtr<pre_gtrlxs[imod].at(igtrm).size();igtr++){
		 int gtrlx = pre_gtrlxs[imod].at(igtrm).at(igtr);
		 hresxd[0][imod]->Fill( gtrlx - trklx );
	       }
	     }
	   }//mix
	   if(pre_gtrlys[imod].size()!=0){//mix
	     for(int igtrm=0;igtrm<pre_gtrlys[imod].size();igtrm++){
	       for(int igtr=0;igtr<pre_gtrlys[imod].at(igtrm).size();igtr++){
		 int gtrly = pre_gtrlys[imod].at(igtrm).at(igtr);
		 hresyd[0][imod]->Fill( gtrly - trkly );
	       }
	     }
	   }//mix
	 }// track loop

	 if( trackexist[imod] ){
	   pre_gtrlxs[imod].push_back( gtrlxs[imod] );
	   if( pre_gtrlxs[imod].size()>mixevent ){
	     pre_gtrlxs[imod].erase(pre_gtrlxs[imod].begin());
	   }
	   pre_gtrlys[imod].push_back( gtrlys[imod] );
	   if( pre_gtrlys[imod].size()>mixevent ){
	     pre_gtrlys[imod].erase(pre_gtrlys[imod].begin());
	   }
	 }
	 trackexist[imod] = false;
	 trklxs[imod].clear();
	 trklys[imod].clear();
	 gtrlxs[imod].clear();
	 gtrlys[imod].clear();

       }
       //calc residual

       trackexist[midel] = true;
       double cx, cy;
       std::vector<double> lxs;
       std::vector<double> lys;
       SetAllCls(ientry,lid,cx,cy,lxs,lys);
       trklxs[midel].push_back(cx);
       trklys[midel].push_back(cy);
       gtrlxs[midel].resize( lxs.size() );
       copy( lxs.begin(), lxs.end(), gtrlxs[midel].begin() );
       gtrlys[midel].resize( lys.size() );
       copy( lys.begin(), lys.end(), gtrlys[midel].begin() );
     }

     pre_eventid = event_id;

     nevent++;

   }//event loop

   //Draw
   TCanvas* c[6];
   TH1F* hresxsub[6];
   TH1F* hresysub[6];
   TLine* lx1[6];
   TLine* lx2[6];
   TLine* ly1[6];
   TLine* ly2[6];
   int linex[3] = {30,40,40};
   for(int j=0;j<6;j++){
     c[j] = new TCanvas(Form("c%d",j),Form("c%d",j),1000,700);
     c[j]->Divide(2,2);
   }
   for(int i=0;i<6;i++){
     c[i]->cd(1);
     hresx[0][i]->Draw();
     hresxd[0][i]->SetLineColor(6);
     hresxd[0][i]->Scale(1./(double)mixevent);
     hresxd[0][i]->Draw("hist sames");
     c[i]->cd(2);
     hresy[0][i]->Draw();
     hresyd[0][i]->SetLineColor(6);
     hresyd[0][i]->Scale(1./(double)mixevent);
     hresyd[0][i]->Draw("hist sames");
     c[i]->cd(3)->SetGridx();
     hresxsub[i] = (TH1F*)hresx[0][i]->Clone();
     hresxsub[i]->Add(hresxd[0][i],-1);
     hresxsub[i]->Draw("hist");
     gPad->Update();
     lx1[i] = new TLine(-linex[lid],gPad->GetUymin(),-linex[lid],gPad->GetUymax());
     lx2[i] = new TLine( linex[lid],gPad->GetUymin(), linex[lid],gPad->GetUymax());
     lx1[i]->SetLineColor(2);
     lx2[i]->SetLineColor(2);
     lx1[i]->Draw("same");
     lx2[i]->Draw("same");
     c[i]->cd(4)->SetGridx();
     hresysub[i] = (TH1F*)hresy[0][i]->Clone();
     hresysub[i]->Add(hresyd[0][i],-1);
     hresysub[i]->Draw("hist");
     gPad->Update();
     ly1[i] = new TLine(-10,gPad->GetUymin(),-10,gPad->GetUymax());
     ly2[i] = new TLine( 10,gPad->GetUymin(), 10,gPad->GetUymax());
     ly1[i]->SetLineColor(2);
     ly2[i]->SetLineColor(2);
     ly1[i]->Draw("same");
     ly2[i]->Draw("same");
   }

   TString fout = Form("%s", out_file_name);
   TCanvas* cdef = new TCanvas("cdef","cdef",700,500);
   cdef->SaveAs(fout+"[","pdf");
   for(int j=0;j<6;j++){
     c[j]->SaveAs(fout,"pdf");
   }
   cdef->SaveAs(fout+"]","pdf");
}

void E16ANA_LGGainCalibwoTrackRoot::LGADCLGmix(char* out_file_name, int maxevent)
{
   if (fChain == 0) return;

   int mixevent = 50;

   int mid[4] = {106,107,103,104};
   int cid[42];
   for(int i=0;i<7;i++){
     for(int j=0;j<6;j++){
       cid[i+j*7] = i+j*10;
     }
   }
   TH1F* h[3][4][42];
   for(int k=0;k<3;k++){
     for(int i=0;i<4;i++){
       for(int j=0;j<42;j++){
	 h[k][i][j] = new TH1F(Form("h%d%d%d",k,i,j),Form("lgadc_%d_%d-%d",k,mid[i],cid[j]),25,0,200);
       }
     }
   }

   //loop
   std::vector<int> trkcids[4];//w HBD hit
   std::vector<int> lgcids[4];
   std::vector<int> lgadcs[4];
   bool trackexist[4] = {false, false, false, false};
   std::vector<std::vector<int>> pre_lgcids[4];
   std::vector<std::vector<int>> pre_lgadcs[4];
   int pre_eventid = -10000;
   Long64_t nentries = fChain->GetEntriesFast();
   std::cout<<"nentries: "<<nentries<<std::endl;
   Long64_t nbytes = 0, nb = 0;

   int nevent = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;

     if(ientry%100000==0){std::cout<<"loop: "<<ientry<<std::endl;}
     if(maxevent!=-1&&nevent>maxevent) break;

     if(lg_mid==102||lg_mid==108) continue;
     int midel = (lg_mid-103+2)%5;

     if(TrackSelection(ientry)<0) continue;

     if(event_id==pre_eventid){
       trackexist[midel] = true;
       trkcids[midel].push_back(lg_cid);
       lgcids[midel].resize( lg_cids->size() );
       copy( lg_cids->begin(), lg_cids->end(), lgcids[midel].begin() );
       lgadcs[midel].resize( lg_adcs->size() );
       copy( lg_adcs->begin(), lg_adcs->end(), lgadcs[midel].begin() );
     }
     else{
       //calc residual
       for(int imod=0;imod<4;imod++){
	 for(int itrk=0;itrk<trkcids[imod].size();itrk++){
	   int trklx = (trkcids[imod].at(itrk))%10;
	   int trkly = (trkcids[imod].at(itrk))/10;
	   for(int ilg=0;ilg<lgcids[imod].size();ilg++){
	     int lglx = (lgcids[imod].at(ilg))%10;
	     int lgly = (lgcids[imod].at(ilg))/10;
	     int cidel = lgly*7 + lglx;
	     if( lglx == trklx && lgly == trkly ){
	       h[0][midel][cidel]->Fill(lgadcs[imod].at(ilg));
	     }
	   }//lg hit loop
	   if(pre_lgcids[imod].size()!=0){//mix
	     for(int ilgm=0;ilgm<pre_lgcids[imod].size();ilgm++){
	       for(int ilg=0;ilg<pre_lgcids[imod].at(ilgm).size();ilg++){
		 int lglx = pre_lgcids[imod].at(ilgm).at(ilg)%10;
		 int lgly = pre_lgcids[imod].at(ilgm).at(ilg)/10;
		 int cidel = lgly*7 + lglx;
		 if( lglx == trklx && lgly == trkly ){
		   h[1][midel][cidel]->Fill(pre_lgadcs[imod].at(ilgm).at(ilg));
		 }
	       }
	     }
	   }//mix
	 }// track loop

	 if( trackexist[imod] ){
	   pre_lgcids[imod].push_back( lgcids[imod] );
	   pre_lgadcs[imod].push_back( lgadcs[imod] );
	   if( pre_lgcids[imod].size()>mixevent ){
	     pre_lgcids[imod].erase(pre_lgcids[imod].begin());
	     pre_lgadcs[imod].erase(pre_lgadcs[imod].begin());
	   }
	 }
	 trackexist[imod] = false;
	 trkcids[imod].clear();
	 lgcids[imod].clear();
	 lgadcs[imod].clear();

       }
       //calc residual

       trackexist[midel] = true;
       trkcids[midel].push_back(lg_cid);
       lgcids[midel].resize( lg_cids->size() );
       copy( lg_cids->begin(), lg_cids->end(), lgcids[midel].begin() );
       lgadcs[midel].resize( lg_adcs->size() );
       copy( lg_adcs->begin(), lg_adcs->end(), lgadcs[midel].begin() );
     }

     pre_eventid = event_id;

     nevent++;

   }//entry loop

   //Draw
   TCanvas* c[2][4];
   for(int k=0;k<2;k++){
     for(int j=0;j<4;j++){
       c[k][j] = new TCanvas(Form("c%d%d",k,j),Form("c%d%d",k,j),1000,700);
       c[k][j]->Divide(7,6);
     }
   }
   for(int j=0;j<4;j++){
     for(int i=0;i<42;i++){
       c[0][j]->cd(i+1);
       h[0][j][41-i]->Draw();
       h[1][j][41-i]->Scale(1./(double)mixevent);
       h[1][j][41-i]->SetLineColor(6);
       h[1][j][41-i]->Draw("hist same");
     }
   }
   TH1F* hsub[4][42];
   for(int j=0;j<4;j++){
     for(int i=0;i<42;i++){
       c[1][j]->cd(i+1);
       hsub[j][41-i] = (TH1F*)h[0][j][41-i]->Clone();
       hsub[j][41-i]->Add(h[1][j][41-i],-1);
       hsub[j][41-i]->Draw("hist");
     }
   }

   TString fout = Form("%s", out_file_name);
   c[0][0]->SaveAs(fout+"[","pdf");
   for(int k=0;k<2;k++){
     for(int j=0;j<4;j++){
       c[k][j]->SaveAs(fout,"pdf");
     }
   }
   c[1][3]->SaveAs(fout+"]","pdf");

}

void E16ANA_LGGainCalibwoTrackRoot::LGADCGTRymix(int lid, char* out_file_name, int maxevent)
{
   if (fChain == 0) return;

   int mixevent = 50;

   int mid[4] = {106,107,103,104};
   int cid[42];
   for(int i=0;i<7;i++){
     for(int j=0;j<6;j++){
       cid[i+j*7] = i+j*10;
     }
   }
   TH1F* h[3][4][42];
   for(int k=0;k<3;k++){
     for(int i=0;i<4;i++){
       for(int j=0;j<42;j++){
	 h[k][i][j] = new TH1F(Form("h%d%d%d",k,i,j),Form("lgadc_%d_%d-%d",k,mid[i],cid[j]),25,0,200);
       }
     }
   }

   //loop
   std::vector<int> trkcids[4];//w HBD hit
   std::vector<double> lgadcs[4];
   std::vector<int> gtrmids[4];
   std::vector<double> gtrcys[4];// @ GTR plane
   bool trackexist[6] = {false, false, false, false, false, false};
   std::vector<double> gtrlys[6];
   std::vector<std::vector<double>> pre_gtrlys[6];
   int pre_eventid = -10000;
   Long64_t nentries = fChain->GetEntriesFast();
   std::cout<<"nentries: "<<nentries<<std::endl;
   Long64_t nbytes = 0, nb = 0;

   int nevent = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;

     if(ientry%100000==0){std::cout<<"loop: "<<ientry<<std::endl;}
     if(maxevent!=-1&&nevent>maxevent) break;

     if(lg_mid==102||lg_mid==108) continue;
     int mideltrk = (lg_mid-103+2)%5;
     int midelgtr = (gtr_mid-102+3)%7;

     if(TrackSelection(ientry)<0) continue;

     if(event_id==pre_eventid){
       trackexist[midelgtr] = true;
       trkcids[mideltrk].push_back(lg_cid);
       lgadcs[mideltrk].push_back(lg_adc);
       gtrmids[mideltrk].push_back(gtr_mid);
       double cy;
       std::vector<double> lys;
       SetAllCls(ientry,lid,cy,lys);
       gtrcys[mideltrk].push_back(cy);
       gtrlys[midelgtr].resize( lys.size() );
       copy( lys.begin(), lys.end(), gtrlys[midelgtr].begin() );
     }
     else{
       for(int imod=0;imod<4;imod++){
	 for(int itrk=0;itrk<trkcids[imod].size();itrk++){
	   int trkcid  = trkcids[imod].at(itrk);
	   int itrkcid = (int)(trkcid/10)*7 + trkcid%10;
	   int gtrmid  = gtrmids[imod].at(itrk);
	   int igtrmid = (gtrmid-102+3)%7;
	   double gtrcy = gtrcys[imod].at(itrk);
	   for(int igtr=0;igtr<gtrlys[igtrmid].size();igtr++){
	     double gtrly = gtrlys[igtrmid].at(igtr);
	     if( fabs(gtrly-gtrcy)<10 ){
	       h[0][imod][itrkcid]->Fill(lgadcs[imod].at(itrk));
	     }
	   }
	   if(pre_gtrlys[igtrmid].size()!=0){//mix
	     for(int igtrm=0;igtrm<pre_gtrlys[igtrmid].size();igtrm++){
	       for(int igtr=0;igtr<pre_gtrlys[igtrmid].at(igtrm).size();igtr++){
		 double gtrly = pre_gtrlys[igtrmid].at(igtrm).at(igtr);
		 if( fabs(gtrly-gtrcy)<10 ){
		   h[1][imod][itrkcid]->Fill(lgadcs[imod].at(itrk));
		 }
	       }
	     }
	   }//mix
	 }// track loop

   	 trkcids[imod].clear();
   	 lgadcs[imod].clear();
   	 gtrmids[imod].clear();
	 gtrcys[imod].clear();
       }
       for(int igtrmid=0;igtrmid<6;igtrmid++){
	 if( trackexist[igtrmid] ){
	   pre_gtrlys[igtrmid].push_back( gtrlys[igtrmid] );
	   if( pre_gtrlys[igtrmid].size()>mixevent ){
	     pre_gtrlys[igtrmid].erase(pre_gtrlys[igtrmid].begin());
	   }
	 }
	 trackexist[igtrmid] = false;
	 gtrlys[igtrmid].clear();
       }
       //calc residual

       trackexist[midelgtr] = true;
       trkcids[mideltrk].push_back(lg_cid);
       lgadcs[mideltrk].push_back(lg_adc);
       gtrmids[mideltrk].push_back(gtr_mid);
       double cy;
       std::vector<double> lys;
       SetAllCls(ientry,lid,cy,lys);
       gtrcys[mideltrk].push_back(cy);
       gtrlys[midelgtr].resize( lys.size() );
       copy( lys.begin(), lys.end(), gtrlys[midelgtr].begin() );
     }

     pre_eventid = event_id;

     nevent++;
   }//event loop

   //Draw
   TCanvas* c[2][4];
   for(int k=0;k<2;k++){
     for(int j=0;j<4;j++){
       c[k][j] = new TCanvas(Form("c%d%d",k,j),Form("c%d%d",k,j),1000,700);
       c[k][j]->Divide(7,6);
     }
   }
   for(int j=0;j<4;j++){
     for(int i=0;i<42;i++){
       c[0][j]->cd(i+1);
       h[0][j][41-i]->Draw();
       h[1][j][41-i]->Scale(1./(double)mixevent);
       h[1][j][41-i]->SetLineColor(6);
       h[1][j][41-i]->Draw("hist same");
     }
   }
   TH1F* hsub[4][42];
   for(int j=0;j<4;j++){
     for(int i=0;i<42;i++){
       c[1][j]->cd(i+1);
       hsub[j][41-i] = (TH1F*)h[0][j][41-i]->Clone();
       hsub[j][41-i]->Add(h[1][j][41-i],-1);
       hsub[j][41-i]->Draw("hist");
     }
   }

   TString fout = Form("%s", out_file_name);
   c[0][0]->SaveAs(fout+"[","pdf");
   for(int k=0;k<2;k++){
     for(int j=0;j<4;j++){
       c[k][j]->SaveAs(fout,"pdf");
     }
   }
   c[1][3]->SaveAs(fout+"]","pdf");

}
