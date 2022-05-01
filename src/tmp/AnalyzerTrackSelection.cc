#define AnalyzerTrackSelection_cxx
#include "AnalyzerTrackSelection.hh"
#include "AnalyzerResidualHBD.hh"
#include "SingleTrackAnalyzerForRes.hh"
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

#include <TH1.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "TROOT.h"


double AnalyzerTrackSelection::CalcADCNearHit(std::vector<hitset>& lgnear, double ssdt){
  sort(lgnear.begin(),lgnear.end());
  double diffmin=10000;
  double adc1=0;
  double adc2=0;
  double ssddiffmin=10000;
  double adc=0;
  // std::cout<<lgnear.size()<<std::endl;
  for(int i=0;i<lgnear.size();i++){
    if(fabs(lgnear.at(i).tdc-ssdt)<fabs(ssddiffmin)){
      adc = lgnear.at(i).adc;
      ssddiffmin = lgnear.at(i).tdc-ssdt;
    }
    if(i=lgnear.size()-1) break;
    if((lgnear.at(i+1).tdc-lgnear.at(i).tdc)<diffmin){
      adc1 = lgnear.at(i).adc;
      adc2 = lgnear.at(i+1).adc;
      diffmin=lgnear.at(i+1).tdc-lgnear.at(i).tdc;
    }
  }
  return adc1+adc2;
  // return adc;
}

void AnalyzerTrackSelection::Loop()
{
//   In a ROOT session, you can do:
//      root> .L AnalyzerTrackSelection.C
//      root> AnalyzerTrackSelection t
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

void AnalyzerTrackSelection::DrawForResidualHBD(int runoption, int maxevent, char* out_file_name)
{

   if (fChain == 0) return;

   const int bin = 1600;
   int roughbin = 800;
   const int halfwidth = 50; //for calcuration of normalized factor
   int hw_int = 20;
   double mom_thr = 2.;
   if(runoption==1){
     roughbin = 200;
     hw_int = 30;
   }
   
   TH1F *h1 = new TH1F("h1","residual_hbd_x",bin,-800,800);
   TH1F *h2 = new TH1F("h2","residual_hbd_y",bin,-800,800);
   TH1F *h3 = new TH1F("h3","residual_hbd_x_dummy",bin,-800,800);
   TH1F *h4 = new TH1F("h4","residual_hbd_y_dummy",bin,-800,800);
   TH1F *hn = new TH1F("hn","multiplicity",200,0,200);
   TH1F *hn2 = new TH1F("hn2","multiplicity_dummy",200,0,200);
   TH1F *he = new TH1F("he","ntracks_in_one_event",100,0,100);
   TH1F *hx[5];
   TH1F *hxd[5];
   TH1F *hy[5];
   TH1F *hyd[5];
   TH1F *hxn[5];
   TH1F *ht[5];
   const int nopt=6;
   char opt[nopt][25] = {"nocut","resy(x)cut","TrackisE","resy(x)cut&TrackisE","mom<2","mom>2"};
   TH1F *haresx[5][nopt];
   TH1F *haresy[5][nopt];
   TH1F *haresxd[5][nopt];
   TH1F *haresyd[5][nopt];
   int ntrack[5][nopt]={0};
   TH2F *hares[5];
   TH2F *haresd[5];
   TH1F *hadc[5];
   TH1F *hadcd[5];
   int adcbin = 40;
   if(runoption==0){adcbin=4000;}
   for(int i=0;i<5;i++){
     hx[i] = new TH1F(Form("hx%d",i),Form("residual_x_mod%d",103+i),roughbin,-800,800);
     hxd[i] = new TH1F(Form("hxd%d",i),Form("residual_x_dummy_mod%d",103+i),roughbin,-800,800);
     hy[i] = new TH1F(Form("hy%d",i),Form("residual_y_mod%d",103+i),roughbin,-800,800);
     hyd[i] = new TH1F(Form("hyd%d",i),Form("residual_y_dummy_mod%d",103+i),roughbin,-800,800);
     hxn[i] = new TH1F(Form("hxn%d",i),Form("multiplicity_mod%d",103+i),200,0,200);
     ht[i] = new TH1F(Form("ht%d",i),Form("fastest_time_mod%d",103+i),800,-150,650);
     for(int j=0;j<nopt;j++){
       haresx[i][j] = new TH1F(Form("haresx%d%d",i,j),Form("allhit_residual_x_mod%d_%s",103+i,opt[j]),roughbin,-800,800);
       haresy[i][j] = new TH1F(Form("haresy%d%d",i,j),Form("allhit_residual_y_mod%d_%s",103+i,opt[j]),roughbin,-800,800);
       haresxd[i][j] = new TH1F(Form("haresxd%d%d",i,j),Form("allhit_residual_x_dummy_mod%d_%s",103+i,opt[j]),roughbin,-800,800);
       haresyd[i][j] = new TH1F(Form("haresyd%d%d",i,j),Form("allhit_residual_y_dummy_mod%d_%s",103+i,opt[j]),roughbin,-800,800);
     }
     hares[i] = new TH2F(Form("hares%d",i),Form("allhit_residual_mod%d",103+i),roughbin,-800,800,roughbin,-800,800);
     haresd[i] = new TH2F(Form("haresd%d",i),Form("allhit_residual_dummy_mod%d",103+i),roughbin,-800,800,roughbin,-800,800);
     hadc[i] = new TH1F(Form("hadc%d",i),Form("adc_nearhit_mod%d",103+i),adcbin,0,adcbin);
     hadcd[i] = new TH1F(Form("hadcd%d",i),Form("adc_nearhit_dummy_mod%d",103+i),adcbin,0,adcbin);
   }


   Long64_t n_entries = fChain->GetEntries();
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   int nevent=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
      if( maxevent!=-1&&nevent>maxevent ){break;}

      if (Cut(ientry) < 0) continue;


      for(int itrack=0;itrack<n_tracks;itrack++){//track loop

	if (CutOfTrack(ientry,itrack) < 0) continue;

	int trk_mid = track_hbd_mid->at(itrack);
	double trk_mom = track_mom->at(itrack);

	double resx_min = track_hbd_nearx->at(itrack);
	double resy_min = track_hbd_neary->at(itrack);
	int nhbdc = track_hbd_multiplicity->at(itrack);
	for(int ihbd=0;ihbd<nhbdc;ihbd++){// hbdcluster loop
	  double resx = track_hbd_allhit_resx->at(itrack).at(ihbd);
	  double resy = track_hbd_allhit_resy->at(itrack).at(ihbd);
	  haresx[trk_mid-103][0]->Fill(resx);
	  haresy[trk_mid-103][0]->Fill(resy);
	  if(trk_mom<mom_thr){
	    haresx[trk_mid-103][4]->Fill(resx);
	    haresy[trk_mid-103][4]->Fill(resy);
	  }
	  if(trk_mom>=mom_thr){
	    haresx[trk_mid-103][5]->Fill(resx);
	    haresy[trk_mid-103][5]->Fill(resy);
	  }
	  if(fabs(resy)<hw_int){
	    haresx[trk_mid-103][1]->Fill(resx);
	  }
	  if(fabs(resx)<hw_int){
	    haresy[trk_mid-103][1]->Fill(resy);
	  }
	  hares[trk_mid-103]->Fill(resx,resy);
	  if( resx*resx+resy*resy < hw_int*hw_int ){
	    double ftime = track_hbd_allhit_ftime->at(itrack).at(ihbd);
	    ht[trk_mid-103]->Fill(ftime);
	    hadc[trk_mid-103]->Fill(track_hbd_allhit_adc->at(itrack).at(ihbd));
	  }
	}// hbdcluster loop
	ntrack[trk_mid-103][0]++;
	ntrack[trk_mid-103][1]++;
	if(trk_mom<mom_thr){
	  ntrack[trk_mid-103][4]++;
	}
	if(trk_mom>=mom_thr){
	  ntrack[trk_mid-103][5]++;
	}
	h1->Fill(resx_min);
	hx[trk_mid-103]->Fill(resx_min);
	h2->Fill(resy_min);
	hy[trk_mid-103]->Fill(resy_min);
	hn->Fill(nhbdc);
	hxn[trk_mid-103]->Fill(nhbdc);

	double resx_dam_min = track_hbd_dum_nearx->at(itrack);
	double resy_dam_min = track_hbd_dum_neary->at(itrack);
	int nhbdc_dam = track_hbd_dum_multiplicity->at(itrack);
	for(int ihbd=0;ihbd<nhbdc_dam;ihbd++){// hbdcluster loop
	  double resx_dam = track_hbd_allhit_dum_resx->at(itrack).at(ihbd);
	  double resy_dam = track_hbd_allhit_dum_resy->at(itrack).at(ihbd);
	  haresxd[trk_mid-103][0]->Fill(resx_dam);
	  haresyd[trk_mid-103][0]->Fill(resy_dam);
	  if(trk_mom<mom_thr){
	    haresxd[trk_mid-103][4]->Fill(resx_dam);
	    haresyd[trk_mid-103][4]->Fill(resy_dam);
	  }
	  if(trk_mom>=mom_thr){
	    haresxd[trk_mid-103][5]->Fill(resx_dam);
	    haresyd[trk_mid-103][5]->Fill(resy_dam);
	  }
	  if(fabs(resy_dam)<hw_int){
	    haresxd[trk_mid-103][1]->Fill(resx_dam);
	  }
	  if(fabs(resx_dam)<hw_int){
	    haresyd[trk_mid-103][1]->Fill(resy_dam);
	  }
	  haresd[trk_mid-103]->Fill(resx_dam,resy_dam);
	  if( resx_dam*resx_dam+resy_dam*resy_dam < hw_int*hw_int ){
	    hadcd[trk_mid-103]->Fill(track_hbd_allhit_dum_adc->at(itrack).at(ihbd));
	  }
	}// hbdcluster loop
	h3->Fill(resx_dam_min);
	hxd[trk_mid-103]->Fill(resx_dam_min);
	h4->Fill(resy_dam_min);
	hyd[trk_mid-103]->Fill(resy_dam_min);
	hn2->Fill(nhbdc_dam);

      }//track loop

      he->Fill(n_tracks);

      nevent++;

   }//event loop

   int regm = bin/2-halfwidth*bin/1600;
   int regp = bin/2+halfwidth*bin/1600;
   TH1F* h3norm = (TH1F*)h3->Clone();
   TH1F* h4norm = (TH1F*)h4->Clone();
   int xint = h1->Integral(0,regm)+h1->Integral(regp,bin);
   int yint = h2->Integral(0,regm)+h2->Integral(regp,bin);
   int xdamint = h3->Integral(0,regm)+h3->Integral(regp,bin);
   int ydamint = h4->Integral(0,regm)+h4->Integral(regp,bin);
   h3norm->Scale((double)xint/(double)xdamint);
   h4norm->Scale((double)yint/(double)ydamint);
   TH1F* h1sub = (TH1F*)h1->Clone();
   TH1F* h2sub = (TH1F*)h2->Clone();
   h1sub->Add(h3norm,-1);
   h2sub->Add(h4norm,-1);

   regm = roughbin/2-halfwidth*roughbin/1600;
   regp = roughbin/2+halfwidth*roughbin/1600;
   TH1F* hsub[4][4];
   int hint[4][4];
   for(int j=0;j<4;j++){
     hsub[j][0] = (TH1F*)hx[(j+3)%5]->Clone();
     hsub[j][1] = (TH1F*)hy[(j+3)%5]->Clone();
     hsub[j][2] = (TH1F*)hxd[(j+3)%5]->Clone();
     hsub[j][3] = (TH1F*)hyd[(j+3)%5]->Clone();
     for(int i=0;i<4;i++){
       hint[j][i] = hsub[j][i]->Integral(0,regm)+hsub[j][i]->Integral(regp,roughbin);
     }
     hsub[j][2]->Scale((double)hint[j][0]/(double)hint[j][2]);
     hsub[j][3]->Scale((double)hint[j][1]/(double)hint[j][3]);
     hsub[j][0]->Add(hsub[j][2],-1);
     hsub[j][1]->Add(hsub[j][3],-1);
   }

   TString outfile = Form("%s",out_file_name);

   gStyle->SetOptStat(11111111);
   gStyle->SetOptFit(11111111);
   TCanvas* ca1 = new TCanvas("ca1","ca1",700,500);
   h1->Draw();
   h3norm->SetLineColor(2);
   h3norm->Draw("hist e same");
   int vh1 = h1->Integral(bin/2-hw_int*bin/1600,bin/2+hw_int*bin/1600);
   int vh3norm = h3norm->Integral(bin/2-hw_int*bin/1600,bin/2+hw_int*bin/1600);
   TLegend *lh1 = new TLegend(0.1,0.75,0.4,0.9);
   lh1->AddEntry(h1,Form("%d<Integral<%d, %d",-hw_int,hw_int,vh1),"l");
   lh1->AddEntry(h3norm,Form("%d<Integral<%d, %d",-hw_int,hw_int,vh3norm),"l");
   lh1->AddEntry((TObject*)0,Form("ratio: %1.3f",(double)vh3norm/(double)vh1),"");
   lh1->Draw();
   TCanvas* ca2 = new TCanvas("ca2","ca2",700,500);
   h2->Draw();
   h4norm->SetLineColor(2);
   h4norm->Draw("hist e same");
   int vh2 = h2->Integral(bin/2-hw_int*bin/1600,bin/2+hw_int*bin/1600);
   int vh4norm = h4norm->Integral(bin/2-hw_int*bin/1600,bin/2+hw_int*bin/1600);
   TLegend *lh2 = new TLegend(0.1,0.75,0.4,0.9);
   lh2->AddEntry(h2,Form("%d<Integral<%d, %d",-hw_int,hw_int,vh2),"l");
   lh2->AddEntry(h4norm,Form("%d<Integral<%d, %d",-hw_int,hw_int,vh4norm),"l");
   lh2->AddEntry((TObject*)0,Form("ratio: %1.3f",(double)vh4norm/(double)vh2),"");
   lh2->Draw();
   TCanvas* csub1 = new TCanvas("csub1","csub1",700,500);
   h1sub->Draw("hist e");
   h1sub->Fit("gaus","","",-30,30);
   TCanvas* csub2 = new TCanvas("csub2","csub2",700,500);
   h2sub->Draw("hist e");
   h2sub->Fit("gaus","","",-30,30);
   TCanvas* cc1 = new TCanvas("cc1","cc1",700,500);
   cc1->DrawFrame(-200,0,200,h1->GetMaximum()+100);
   cc1->SetGrid();
   h1->Draw("same");
   TCanvas* cc2 = new TCanvas("cc2","cc2",700,500);
   cc2->DrawFrame(-200,0,200,h2->GetMaximum()+100);
   cc2->SetGrid();
   h2->Draw("same");

   TCanvas* c[12];
   for(int i=0;i<12;i++){
     c[i] = new TCanvas(Form("c%d",i),Form("c%d",i),700,500);
   }
   c[0]->cd();
   h1->Draw();
   h3->SetLineColor(6);
   h3->Draw("same");
   c[1]->cd();
   h2->Draw();
   h4->SetLineColor(6);
   h4->Draw("same");
   c[2]->cd();
   h3->Draw();
   c[3]->cd();
   h4->Draw();
   c[4]->cd();
   hn->Draw();
   c[5]->cd();
   hn2->Draw();
   c[6]->cd()->SetLogy();
   c[6]->SetGrid();
   he->Draw();
   c[7]->Divide(2,2);
   c[8]->Divide(2,2);
   c[9]->Divide(2,2);
   c[10]->Divide(2,2);
   c[11]->Divide(2,2);
   for(int i=0;i<4;i++){
     c[7]->cd(i+1);
     hx[(i+3)%5]->Draw();
     c[8]->cd(i+1);
     hxd[(i+3)%5]->Draw();
     c[9]->cd(i+1);
     hxn[(i+3)%5]->Draw();
     c[10]->cd(i+1);
     ht[(i+3)%5]->Draw();
     c[11]->cd(i+1);
     hadc[(i+3)%5]->Draw();
     hadcd[(i+3)%5]->SetLineColor(2);
     hadcd[(i+3)%5]->Draw("same");
   }
   TCanvas* csubd[4];
   TLegend* lhsub[2][4];
   int vhsub0,vhsub1,vhsub2,vhsub3;
   for(int i=0;i<4;i++){
     csubd[i] = new TCanvas(Form("csubd%d",i),Form("csubd%d",i),700,500);
     csubd[i]->Divide(2,2);
     csubd[i]->cd(1);
     hx[(i+3)%5]->Draw("hist e");
     hsub[i][2]->SetLineColor(2);
     hsub[i][2]->Draw("hist e same");
     vhsub0 = hx[(i+3)%5]->Integral(roughbin/2-hw_int*roughbin/1600,roughbin/2+hw_int*roughbin/1600);
     vhsub2 = hsub[i][2]->Integral(roughbin/2-hw_int*roughbin/1600,roughbin/2+hw_int*roughbin/1600);
     lhsub[0][i] = new TLegend(0.1,0.75,0.4,0.9);
     lhsub[0][i]->AddEntry(hx[(i+3)%5],Form("%d<Integral<%d, %d",-hw_int,hw_int,vhsub0),"l");
     lhsub[0][i]->AddEntry(hsub[i][2],Form("%d<Integral<%d, %d",-hw_int,hw_int,vhsub2),"l");
     lhsub[0][i]->AddEntry((TObject*)0,Form("ratio: %1.3f",(double)vhsub2/(double)vhsub0),"");
     lhsub[0][i]->Draw();
     csubd[i]->cd(2);
     hy[(i+3)%5]->Draw("hist e");
     hsub[i][3]->SetLineColor(2);
     hsub[i][3]->Draw("hist e same");
     vhsub1 = hy[(i+3)%5]->Integral(roughbin/2-hw_int*roughbin/1600,roughbin/2+hw_int*roughbin/1600);
     vhsub3 = hsub[i][3]->Integral(roughbin/2-hw_int*roughbin/1600,roughbin/2+hw_int*roughbin/1600);
     lhsub[1][i] = new TLegend(0.1,0.75,0.4,0.9);
     lhsub[1][i]->AddEntry(hy[(i+3)%5],Form("%d<Integral<%d, %d",-hw_int,hw_int,vhsub1),"l");
     lhsub[1][i]->AddEntry(hsub[i][3],Form("%d<Integral<%d, %d",-hw_int,hw_int,vhsub3),"l");
     lhsub[1][i]->AddEntry((TObject*)0,Form("ratio: %1.3f",(double)vhsub3/(double)vhsub1),"");
     lhsub[1][i]->Draw();
     csubd[i]->cd(3);
     hsub[i][0]->Draw("hist e");
     hsub[i][0]->Fit("gaus","","",-30,30);
     csubd[i]->cd(4);
     hsub[i][1]->Draw("hist e");
     hsub[i][1]->Fit("gaus","","",-30,30);
   }
   // TCanvas* csubdnn[4];
   // TH1F* hsubdnn[4][2];
   // for(int i=0;i<4;i++){
   //   csubdnn[i] = new TCanvas(Form("csubdnn%d",i),Form("csubdnn%d",i),700,500);
   //   csubdnn[i]->Divide(2,2);
   //   csubdnn[i]->cd(1);
   //   hx[(i+3)%5]->Draw("hist e");
   //   hxd[(i+3)%5]->SetLineColor(6);
   //   hxd[(i+3)%5]->Draw("hist e same");
   //   csubdnn[i]->cd(2);
   //   hy[(i+3)%5]->Draw("hist e");
   //   hyd[(i+3)%5]->SetLineColor(6);
   //   hyd[(i+3)%5]->Draw("hist e same");
   //   csubdnn[i]->cd(3);
   //   hsubdnn[i][0] = (TH1F*)hx[(i+3)%5]->Clone();
   //   hsubdnn[i][0]->Add(hxd[(i+3)%5],-1);
   //   hsubdnn[i][0]->Draw();
   //   hsubdnn[i][0]->Fit("gaus","","",-30,30);
   //   csubdnn[i]->cd(4);
   //   hsubdnn[i][1] = (TH1F*)hy[(i+3)%5]->Clone();
   //   hsubdnn[i][1]->Add(hyd[(i+3)%5],-1);
   //   hsubdnn[i][1]->Draw();
   //   hsubdnn[i][1]->Fit("gaus","","",-30,30);
   // }
   TCanvas* casubd[4][nopt];
   TH1F* hasubd[4][2][nopt];
   TLegend* lasubd[4][2][nopt];
   int vasubd[4][2][nopt];
   for(int j=0;j<nopt;j++){
     for(int i=0;i<4;i++){
       casubd[i][j] = new TCanvas(Form("casubd%d%d",i,j),Form("casubd%d%d",i,j),700,500);
       casubd[i][j]->Divide(2,2);
       casubd[i][j]->cd(1);
       haresx[(i+3)%5][j]->Draw();
       haresxd[(i+3)%5][j]->SetLineColor(6);
       haresxd[(i+3)%5][j]->Draw("same");
       casubd[i][j]->cd(2);
       haresy[(i+3)%5][j]->Draw();
       haresyd[(i+3)%5][j]->SetLineColor(6);
       haresyd[(i+3)%5][j]->Draw("same");
       casubd[i][j]->cd(3);
       hasubd[i][0][j] = (TH1F*)haresx[(i+3)%5][j]->Clone();
       hasubd[i][0][j]->Add(haresxd[(i+3)%5][j],-1);
       hasubd[i][0][j]->Draw();
       hasubd[i][0][j]->Fit("gaus","","",-30,30);
       lasubd[i][0][j] = new TLegend(0.1,0.75,0.4,0.9);
       vasubd[i][0][j] = hasubd[i][0][j]->Integral(roughbin/2-hw_int*roughbin/1600,roughbin/2+hw_int*roughbin/1600);
       lasubd[i][0][j]->AddEntry(hasubd[i][0][j],Form("%d<Integral<%d, %d",-hw_int,hw_int,vasubd[i][0][j]),"l");
       lasubd[i][0][j]->AddEntry((TObject*)0,Form("n_track: %d",ntrack[(i+3)%5][j]),"");
       lasubd[i][0][j]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasubd[i][0][j]/(double)ntrack[(i+3)%5][j]),"");
       lasubd[i][0][j]->Draw();
       casubd[i][j]->cd(4);
       hasubd[i][1][j] = (TH1F*)haresy[(i+3)%5][j]->Clone();
       hasubd[i][1][j]->Add(haresyd[(i+3)%5][j],-1);
       hasubd[i][1][j]->Draw();
       hasubd[i][1][j]->Fit("gaus","","",-30,30);
       lasubd[i][1][j] = new TLegend(0.1,0.75,0.4,0.9);
       vasubd[i][1][j] = hasubd[i][1][j]->Integral(roughbin/2-hw_int*roughbin/1600,roughbin/2+hw_int*roughbin/1600);
       lasubd[i][1][j]->AddEntry(hasubd[i][1][j],Form("%d<Integral<%d, %d",-hw_int,hw_int,vasubd[i][1][j]),"l");
       lasubd[i][1][j]->AddEntry((TObject*)0,Form("n_track: %d",ntrack[(i+3)%5][j]),"");
       lasubd[i][1][j]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasubd[i][1][j]/(double)ntrack[(i+3)%5][j]),"");
       lasubd[i][1][j]->Draw();
     }
   }
   TCanvas* casub2d[4];
   TH2F* hasub2d[4];
   TH2F* hasub2dcopy[4];
   TLegend* lasub2d[4];
   int vasub2d[4];
   for(int i=0;i<4;i++){
     casub2d[i] = new TCanvas(Form("casub2d%d",i),Form("casub2d%d",i),700,700);
     casub2d[i]->Divide(2,2);
     casub2d[i]->cd(1);
     hares[(i+3)%5]->Draw("colz");
     casub2d[i]->cd(2);
     haresd[(i+3)%5]->Draw("colz");
     casub2d[i]->cd(3);
     hasub2d[i] = (TH2F*)hares[(i+3)%5]->Clone();
     hasub2d[i]->Add(haresd[(i+3)%5],-1);
     hasub2d[i]->Draw("colz");
     lasub2d[i] = new TLegend(0.1,0.75,0.4,0.9);
     hasub2dcopy[i] = (TH2F*)hasub2d[i]->Clone();
     vasub2d[i] = AnalyzerResidualHBD::Get2DHistIntegral(hasub2d[i],hw_int,hasub2dcopy[i]);
     lasub2d[i]->AddEntry(hasub2d[i],Form("Integral(r:%dmm), %d",hw_int,vasub2d[i]),"l");
     int n_track = hx[(i+3)%5]->GetEntries();
     lasub2d[i]->AddEntry((TObject*)0,Form("n_track: %d",n_track),"");
     lasub2d[i]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasub2d[i]/(double)n_track),"");
     lasub2d[i]->Draw();
     casub2d[i]->cd(4)->DrawFrame(-50,-50,50,50);
     hasub2dcopy[i]->Draw("colz sames");
   }

   TCanvas* cdef = new TCanvas("cdef","cdef",700,500);
   cdef->SaveAs(outfile+"[","pdf");
   ca1->SaveAs(outfile,"pdf");
   ca2->SaveAs(outfile,"pdf");
   csub1->SaveAs(outfile,"pdf");
   csub2->SaveAs(outfile,"pdf");
   cc1->SaveAs(outfile,"pdf");
   cc2->SaveAs(outfile,"pdf");
   for(int i=0;i<12;i++){
     c[i]->SaveAs(outfile,"pdf");
   }
   for(int i=0;i<4;i++){
     csubd[i]->SaveAs(outfile,"pdf");
   }
   // for(int i=0;i<4;i++){
   //   csubdnn[i]->SaveAs(outfile,"pdf");
   // }
   for(int i=0;i<4;i++){
     for(int j=0;j<nopt;j++){
       casubd[i][j]->SaveAs(outfile,"pdf");
     }
     casub2d[i]->SaveAs(outfile,"pdf");
   }
   cdef->SaveAs(outfile+"]","pdf");
}

void AnalyzerTrackSelection::DrawForTrackSelection(int runoption, int maxevent, char* out_file_name)
{

   if (fChain == 0) return;

   std::ofstream outtextfile("eventlist.txt");
   TFile *fouthist = new TFile("hist.root","recreate");

   const int ndet=5;
   char det[ndet][20] = {"HBD","LGHit","LGCluster","LGHit_woHBDhit","LGCluster_woHBDhit"};
   int roughbin[ndet] = {800,50,50,50,50};//bin
   int halfwidth[ndet] = {50,100,100,100,100};
   int hw_intx[ndet] = {20,80,80,80,80};
   int hw_inty[ndet] = {20,120,120,120,120};
   int ex_2d[ndet] = {50,200,200,200,200};
   double fitregion[ndet] = {30,100,100,100,100};
   if(runoption==1){
     roughbin[0] = 200;
     hw_intx[0] = 50;
     hw_inty[0] = 50;
   }
   int adcbinw[ndet] = {40,200,200,200,200};
   int adcbin[ndet] = {40,400,400,400,400};
   int tbinw[ndet] = {800,200,200,200,200};
   int tbin0[ndet] = {-150,0,0,0,0};
   int tbin[ndet] = {600,200,200,200,200};
   if(runoption==0){adcbin[0]=4000;}
   double ssdoffset = 51.;
   double ssdregion = 11.;
   
   TH1F *he = new TH1F("he","ntracks_in_one_event",100,0,100);
   TH1F *hx[5][ndet];
   TH1F *hxd[5][ndet];
   TH1F *hy[5][ndet];
   TH1F *hyd[5][ndet];
   TH1F *hn[5][ndet];
   TH1F *hnd[5][ndet];
   const int nopt=4;
   char opt[nopt][25] = {"nocut","resy(x)cut","plus_charge","minus_charge"};
   TH1F *haresx[5][nopt][ndet];
   TH1F *haresy[5][nopt][ndet];
   TH1F *haresxd[5][nopt][ndet];
   TH1F *haresyd[5][nopt][ndet];
   int ntrack[5][nopt][ndet]={0};
   TH2F *hares[5][ndet];
   TH2F *haresd[5][ndet];
   const int nsel=4;
   char sel[nsel][13] = {"All","HBDisE","HBDisPi","HBDisEtiming"};
   TH1F *ht[5][nsel][ndet];
   TH1F *htd[5][nsel][ndet];
   TH1F *hadc[5][nsel][ndet];
   TH1F *hadcd[5][nsel][ndet];
   TH2F *hadcp[5][nsel][ndet];
   TH1F *hadcp05[5][nsel][ndet];
   TH1F *hadcp07[5][nsel][ndet];
   TH1F *hadcp09[5][nsel][ndet];
   TH1F *hadcp11[5][nsel][ndet];
   TH1F *hadcop[5][nsel][ndet];
   TH1F *hadcopd[5][nsel][ndet];
   for(int k=0;k<ndet;k++){
     for(int i=0;i<5;i++){
       hx[i][k] = new TH1F(Form("hx%d%d",i,k),Form("%s_residual_x_mod%d",det[k],103+i),roughbin[k],-800,800);
       hxd[i][k] = new TH1F(Form("hxd%d%d",i,k),Form("%s_residual_x_dummy_mod%d",det[k],103+i),roughbin[k],-800,800);
       hy[i][k] = new TH1F(Form("hy%d%d",i,k),Form("%s_residual_y_mod%d",det[k],103+i),roughbin[k],-800,800);
       hyd[i][k] = new TH1F(Form("hyd%d%d",i,k),Form("%s_residual_y_dummy_mod%d",det[k],103+i),roughbin[k],-800,800);
       hn[i][k] = new TH1F(Form("hn%d%d",i,k),Form("%s_multiplicity_mod%d",det[k],103+i),200,0,200);
       hnd[i][k] = new TH1F(Form("hnd%d%d",i,k),Form("%s_multiplicity_dummy_mod%d",det[k],103+i),200,0,200);
       for(int j=0;j<nopt;j++){
	 haresx[i][j][k] = new TH1F(Form("haresx%d%d%d",i,j,k),Form("%s_allhit_residual_x_mod%d_%s",det[k],103+i,opt[j]),roughbin[k],-800,800);
	 haresy[i][j][k] = new TH1F(Form("haresy%d%d%d",i,j,k),Form("%s_allhit_residual_y_mod%d_%s",det[k],103+i,opt[j]),roughbin[k],-800,800);
	 haresxd[i][j][k] = new TH1F(Form("haresxd%d%d%d",i,j,k),Form("%s_allhit_residual_x_dummy_mod%d_%s",det[k],103+i,opt[j]),roughbin[k],-800,800);
	 haresyd[i][j][k] = new TH1F(Form("haresyd%d%d%d",i,j,k),Form("%s_allhit_residual_y_dummy_mod%d_%s",det[k],103+i,opt[j]),roughbin[k],-800,800);
       }
       hares[i][k] = new TH2F(Form("hares%d%d",i,k),Form("%s_allhit_residual_mod%d",det[k],103+i),roughbin[k],-800,800,roughbin[k],-800,800);
       haresd[i][k] = new TH2F(Form("haresd%d%d",i,k),Form("%s_allhit_residual_dummy_mod%d",det[k],103+i),roughbin[k],-800,800,roughbin[k],-800,800);
       for(int j=0;j<nsel;j++){
	 ht[i][j][k] = new TH1F(Form("ht%d%d%d",i,j,k),Form("%s_%s_fastest_time_mod%d",det[k],sel[j],103+i),tbinw[k],tbin0[k],tbin[k]);
	 htd[i][j][k] = new TH1F(Form("htd%d%d%d",i,j,k),Form("%s_%s_fastest_time_dummy_mod%d",det[k],sel[j],103+i),tbinw[k],tbin0[k],tbin[k]);
	 hadc[i][j][k] = new TH1F(Form("hadc%d%d%d",i,j,k),Form("%s_%s_adc_mod%d",det[k],sel[j],103+i),adcbinw[k],0,adcbin[k]);
	 hadcd[i][j][k] = new TH1F(Form("hadcd%d%d%d",i,j,k),Form("%s_%s_adc_dummy_mod%d",det[k],sel[j],103+i),adcbinw[k],0,adcbin[k]);
	 hadcp[i][j][k] = new TH2F(Form("hadcp%d%d%d",i,j,k),Form("%s_%s_adc_vs_mom_mod%d",det[k],sel[j],103+i),100,0,5,100,0,500);
	 hadcp05[i][j][k] = new TH1F(Form("hadcp05%d%d%d",i,j,k),Form("%s_%s_adc_0.5<p<0.7_mod%d",det[k],sel[j],103+i),adcbinw[k]/4,0,adcbin[k]);
	 hadcp07[i][j][k] = new TH1F(Form("hadcp07%d%d%d",i,j,k),Form("%s_%s_adc_0.7<p<0.9_mod%d",det[k],sel[j],103+i),adcbinw[k]/4,0,adcbin[k]);
	 hadcp09[i][j][k] = new TH1F(Form("hadcp09%d%d%d",i,j,k),Form("%s_%s_adc_0.9<p<1.1_mod%d",det[k],sel[j],103+i),adcbinw[k]/4,0,adcbin[k]);
	 hadcp11[i][j][k] = new TH1F(Form("hadcp11%d%d%d",i,j,k),Form("%s_%s_adc_1.1<p_mod%d",det[k],sel[j],103+i),adcbinw[k]/4,0,adcbin[k]);
	 hadcop[i][j][k] = new TH1F(Form("hadcop%d%d%d",i,j,k),Form("%s_%s_adc_E/p_mod%d",det[k],sel[j],103+i),adcbinw[k]/4,0,adcbin[k]);
	 hadcopd[i][j][k] = new TH1F(Form("hadcopd%d%d%d",i,j,k),Form("%s_%s_adc_dummy_E/p_mod%d",det[k],sel[j],103+i),adcbinw[k]/4,0,adcbin[k]);
	 // hadcop[i][j][k] = new TH1F(Form("hadcop%d%d%d",i,j,k),Form("%s_%s_adc_E/p_mod%d",det[k],sel[j],103+i),40,-4,4);
	 // hadcopd[i][j][k] = new TH1F(Form("hadcopd%d%d%d",i,j,k),Form("%s_%s_adc_dummy_E/p_mod%d",det[k],sel[j],103+i),40,-4,4);
       }
     }
   }
   TH1F* hbdadc[5];
   TH1F* hbdadcd[5];
   TH1F* lgadc[5];
   TH1F* lgadcd[5];
   TH1F* lgtrkmom[5];
   // TH1F* lgtrk1eff[5];
   // TH1F* lgtrk2eff[5];
   TH2F* hlghitsum[5];
   TH2F* hlghitsumd[5];
   TH1F* hlghitsum1d[5];
   TH1F* hlghitsum1dd[5];
   TH1F* hedivp[5];
   TH1F* hedivpd[5];
   TH1F* hesubp[5];
   TH1F* hesubpd[5];
   TH2F* htimssdlg[5];
   TH1F* htimssdlg1d[5];
   TH1F* hnlghitwt[5];
   TH1F* hlgblk[5];
   TH2F* hlgcor[5][60];
   for(int i=0;i<5;i++){
     hbdadc[i] = new TH1F(Form("hbdadc%d",i),Form("HBD_adc_w/LGHit_mod%d",103+i),54,-1.5,25.5);
     hbdadcd[i] = new TH1F(Form("hbdadcd%d",i),Form("HBD_adc_dummy_w/LGHit_mod%d",103+i),54,-1.5,25.5);
     lgadc[i] = new TH1F(Form("lgadc%d",i),Form("LG_adc_w/HBDHit_mod%d",103+i),100,-10,490);
     lgadcd[i] = new TH1F(Form("lgadcd%d",i),Form("LG_adc_dummy_w/HBDHit_mod%d",103+i),100,-10,490);
     lgtrkmom[i] = new TH1F(Form("lgtrkmom%d",i),Form("Track_mom_w/HBDHit_mod%d",103+i),50,0,5);
     // lgtrk1eff[i] = new TH1F(Form("lgtrk1eff%d",i),Form("Track_LGpiEff1_w/HBDHit_mod%d",103+i),50,0,0.5);
     // lgtrk2eff[i] = new TH1F(Form("lgtrk2eff%d",i),Form("Track_LGpiEff2_w/HBDHit_mod%d",103+i),50,0,0.5);
     hlghitsum[i] = new TH2F(Form("hlghitsum%d",i),Form("LG_HitAdcSumVsMom_TrackAssociate_mod%d",103+i),100,0,5,100,0,500);
     hlghitsumd[i] = new TH2F(Form("hlghitsumd%d",i),Form("LG_HitAdcSumVsMom_dummy_TrackAssociate_mod%d",103+i),100,0,5,100,0,500);
     hlghitsum1d[i] = new TH1F(Form("hlghitsum1d%d",i),Form("LG_HitAdcSum/Mom_TrackAssociate_mod%d",103+i),50,0,400);
     hlghitsum1dd[i] = new TH1F(Form("hlghitsum1dd%d",i),Form("LG_HitAdcSum/Mom_dummy_TrackAssociate_mod%d",103+i),50,0,400);
     hedivp[i] = new TH1F(Form("hedivp%d",i),Form("LG_HitAdc/Mom_TrackAssociate_mod%d",103+i),50,0,400);
     hedivpd[i] = new TH1F(Form("hedivpd%d",i),Form("LG_HitAdc/Mom_dummy_TrackAssociate_mod%d",103+i),50,0,400);
     hesubp[i] = new TH1F(Form("hesubp%d",i),Form("LG_HitAdc-250*Mom_TrackAssociate_mod%d",103+i),50,-200,200);
     hesubpd[i] = new TH1F(Form("hesubpd%d",i),Form("LG_HitAdc-250*Mom_dummy_TrackAssociate_mod%d",103+i),50,-200,200);
     htimssdlg[i] = new TH2F(Form("htimssdlg%d",i),Form("Timing_SSDvsLG_TrackAssociate_mod%d",103+i),60,60,120,60,10,70);
     htimssdlg1d[i] = new TH1F(Form("htimssdlg1d%d",i),Form("Timing_LG-SSD_TrackAssociate_mod%d",103+i),100,0,100);
     hnlghitwt[i] = new TH1F(Form("hnlghitwt%d",i),Form("N_LGHits_TrackAssociate_mod%d",103+i),10,0,10);
     hlgblk[i] = new TH1F(Form("hlgblk%d",i),Form("BlockID_TrackAssociate_mod%d",103+i),60,0,60);
     for(int j=0;j<60;j++){
       hlgcor[i][j] = new TH2F(Form("hlgcor%d%d",i,j),Form("LG_HitAdcSumVsMom_TrackAssociate_mod%d_blk%d",103+i,j),100,0,5,100,0,500);
     }
   }
   TH1F* lgadcene = new TH1F("lgadcene","lgadcene",80,0,2);
   TH1F* lgadcened = new TH1F("lgadcened","lgadcened",80,0,2);


   //HBD residual region for selecting tracks
   double track_select_sigma = 2.;
   double hbd_voriginx[4]={0.};
   double hbd_voriginy[4]={0.};
   double hbd_vsigmax[4]={25.,25.,25.,25.};
   double hbd_vsigmay[4]={25.,25.,25.,25.};
   if(runoption==3){
     hbd_voriginx[0]=-9.56;//106
     hbd_voriginy[0]=-4.5;
     hbd_vsigmax[0]=13.4*track_select_sigma;
     hbd_vsigmay[0]=7.43*track_select_sigma;
     // hbd_voriginxt[1]=1.371;//107
     // hbd_voriginyt[1]=-1.507;
     // hbd_vsigmaxt[1]=11.05*track_select_sigma;
     // hbd_vsigmayt[1]=9.007*track_select_sigma;
   }
   if(runoption==0){
     hbd_voriginx[0]=-7.52;//106
     hbd_voriginy[0]=-2.44;
     hbd_vsigmax[0]=5.93*track_select_sigma;
     hbd_vsigmay[0]=5.15*track_select_sigma;
     hbd_voriginx[1]=1.79;//107
     hbd_voriginy[1]=-0.70;
     hbd_vsigmax[1]=8.38*track_select_sigma;
     hbd_vsigmay[1]=6.64*track_select_sigma;
   }

   //for mixing
   std::vector<std::vector<hitset>> hbdmixhits[5];
   std::vector<std::vector<hitset>> lgmixhits[5];
   TH1F *hbdresxmix[5];
   TH1F *hbdresymix[5];
   TH1F *lgresxmix[5];
   TH1F *lgresymix[5];
   TH1F *lgadcmix[5];
   for(int i=0;i<5;i++){
     hbdresxmix[i] = new TH1F(Form("hbdresxmix%d",i),Form("hbd_resx_mix_mod%d",103+i),roughbin[0],-800,800);
     hbdresymix[i] = new TH1F(Form("hbdresymix%d",i),Form("hbd_resy_mix_mod%d",103+i),roughbin[0],-800,800);
     lgresxmix[i] = new TH1F(Form("lgresxmix%d",i),Form("lg_resx_mix_mod%d",103+i),roughbin[1],-800,800);
     lgresymix[i] = new TH1F(Form("lgresymix%d",i),Form("lg_resy_mix_mod%d",103+i),roughbin[1],-800,800);
     lgadcmix[i] = new TH1F(Form("lgadcmix%d",i),Form("lg_adc_mix_mod%d",103+i),50,0,400);
   }
   //for mixing

   Long64_t n_entries = fChain->GetEntries();
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   int nevent=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
      if( maxevent!=-1&&nevent>maxevent ){break;}

      std::vector<int> goodtracks;
      if (SelectGoodTrack(ientry,goodtracks) < 0) continue;
      // if (Cut(ientry) < 0) continue;//220407

      bool alfill[5]={false};

      for(int itrack=0;itrack<n_tracks;itrack++){//track loop

	if (CutOfTrack(ientry,itrack,goodtracks) < 0) continue;
	// if (CutOfTrack(ientry,itrack,runoption) < 0) continue;//220407
	int x = (track_lg_lx->at(itrack))-(track_position_block_lx->at(itrack));
	int y = (track_lg_ly->at(itrack)/fabs(track_lg_ly->at(itrack)))*(fabs(track_lg_ly->at(itrack))+track_position_block_ly->at(itrack));
	int ch = SingleTrackAnalyzerForRes::LocaltoCh(x,y);
	// if(ch!=25) continue;

	//HBD Fill
	int trk_mid = track_hbd_mid->at(itrack);
	double resx_min = track_hbd_nearx->at(itrack);
	double resy_min = track_hbd_neary->at(itrack);
	double ftime_min = -10000;
	double adc_min = -10000;
	int size_min = -10000;
	double eprob_min = -10000;
	int nhbdc = track_hbd_multiplicity->at(itrack);
	for(int ihbd=0;ihbd<nhbdc;ihbd++){// hbdcluster loop
	  double resx = track_hbd_allhit_resx->at(itrack).at(ihbd);
	  double resy = track_hbd_allhit_resy->at(itrack).at(ihbd);
	  double adc = track_hbd_allhit_adc->at(itrack).at(ihbd);
	  int size = track_hbd_allhit_size->at(itrack).at(ihbd);
	  haresx[trk_mid-103][0][0]->Fill(resx);
	  haresy[trk_mid-103][0][0]->Fill(resy);
	  if(resx==resx_min&&resy==resy_min){//220208
	    ftime_min = track_hbd_allhit_ftime->at(itrack).at(ihbd);//220208
	    adc_min = track_hbd_allhit_adc->at(itrack).at(ihbd);//220208
	    size_min = track_hbd_allhit_size->at(itrack).at(ihbd);//220208
	    eprob_min = track_hbd_allhit_eprob->at(itrack).at(ihbd);//220208
	  }//220208
	  if(fabs(resy)<hw_intx[0]){
	    haresx[trk_mid-103][1][0]->Fill(resx);
	    if(rk_charge->at(itrack)==1){haresx[trk_mid-103][2][0]->Fill(resx);}
	    if(rk_charge->at(itrack)==-1){haresx[trk_mid-103][3][0]->Fill(resx);}
	  }
	  if(fabs(resx)<hw_intx[0]){
	    haresy[trk_mid-103][1][0]->Fill(resy);
	    if(rk_charge->at(itrack)==1){haresy[trk_mid-103][2][0]->Fill(resy);}
	    if(rk_charge->at(itrack)==-1){haresy[trk_mid-103][3][0]->Fill(resy);}
	  }
	  hares[trk_mid-103][0]->Fill(resx,resy);
	  // if(adc<=3&&size==1){hares[trk_mid-103][0]->Fill(resx,resy);}//220218tmp;
	  if( resx*resx+resy*resy < hw_intx[0]*hw_intx[0] ){
	    ht[trk_mid-103][0][0]->Fill(track_hbd_allhit_ftime->at(itrack).at(ihbd));
	    hadc[trk_mid-103][0][0]->Fill(track_hbd_allhit_adc->at(itrack).at(ihbd));
	  }
	}// hbdcluster loop
	ntrack[trk_mid-103][0][0]++;
	ntrack[trk_mid-103][1][0]++;
	ntrack[trk_mid-103][2][0]++;
	ntrack[trk_mid-103][3][0]++;
	hx[trk_mid-103][0]->Fill(resx_min);
	hy[trk_mid-103][0]->Fill(resy_min);
	hn[trk_mid-103][0]->Fill(nhbdc);

	double resx_dam_min = track_hbd_dum_nearx->at(itrack);
	double resy_dam_min = track_hbd_dum_neary->at(itrack);
	double ftime_dam_min = -10000;
	double adc_dam_min = -10000;
	int size_dam_min = -10000;
	int nhbdc_dam = track_hbd_dum_multiplicity->at(itrack);
	for(int ihbd=0;ihbd<nhbdc_dam;ihbd++){// hbdcluster loop
	  double resx_dam = track_hbd_allhit_dum_resx->at(itrack).at(ihbd);
	  double resy_dam = track_hbd_allhit_dum_resy->at(itrack).at(ihbd);
	  double adc_dam = track_hbd_allhit_dum_adc->at(itrack).at(ihbd);
	  int size_dam = track_hbd_allhit_dum_size->at(itrack).at(ihbd);
	  haresxd[trk_mid-103][0][0]->Fill(resx_dam);
	  haresyd[trk_mid-103][0][0]->Fill(resy_dam);
	  if(resx_dam==resx_dam_min&&resy_dam==resy_dam_min){//220218
	    ftime_dam_min = track_hbd_allhit_dum_ftime->at(itrack).at(ihbd);
	    adc_dam_min = track_hbd_allhit_dum_adc->at(itrack).at(ihbd);
	    size_dam_min = track_hbd_allhit_dum_size->at(itrack).at(ihbd);
	  }
	  if(fabs(resy_dam)<hw_intx[0]){
	    haresxd[trk_mid-103][1][0]->Fill(resx_dam);
	    if(rk_charge->at(itrack)==1){haresxd[trk_mid-103][2][0]->Fill(resx_dam);}
	    if(rk_charge->at(itrack)==-1){haresxd[trk_mid-103][3][0]->Fill(resx_dam);}
	  }
	  if(fabs(resx_dam)<hw_intx[0]){
	    haresyd[trk_mid-103][1][0]->Fill(resy_dam);
	    if(rk_charge->at(itrack)==1){haresyd[trk_mid-103][2][0]->Fill(resy_dam);}
	    if(rk_charge->at(itrack)==-1){haresyd[trk_mid-103][3][0]->Fill(resy_dam);}
	  }
	  haresd[trk_mid-103][0]->Fill(resx_dam,resy_dam);
	  // if(adc_dam<=3&&size_dam==1){haresd[trk_mid-103][0]->Fill(resx_dam,resy_dam);}//220218tmp
	  if( resx_dam*resx_dam+resy_dam*resy_dam < hw_intx[0]*hw_intx[0] ){
	    htd[trk_mid-103][0][0]->Fill(track_hbd_allhit_dum_ftime->at(itrack).at(ihbd));
	    hadcd[trk_mid-103][0][0]->Fill(track_hbd_allhit_dum_adc->at(itrack).at(ihbd));
	  }
	}// hbdcluster loop
	hxd[trk_mid-103][0]->Fill(resx_dam_min);
	hyd[trk_mid-103][0]->Fill(resy_dam_min);
	hnd[trk_mid-103][0]->Fill(nhbdc_dam);

	bool HBDhit=false;
	int Particle=0;
	int ETiming=0;
	double rxt = resx_min-hbd_voriginx[(trk_mid-103+2)%5];
	double ryt = resy_min-hbd_voriginy[(trk_mid-103+2)%5];
	//double rr = vradiust[(trk_mid-103+2)%5][0]*vradiust[(trk_mid-103+2)%5][0];
	//if(rxt*rxt+ryt*ryt<rr){HBDhit=true;}
	if( fabs(rxt)<hbd_vsigmax[(trk_mid-103+2)%5] && fabs(ryt)<hbd_vsigmay[(trk_mid-103+2)%5] ){
	  // if(adc_min>=7&&size_min>1){//220306
	  HBDhit=true;
	  // }
	  // if(eprob_min==1){Particle=1;}
	  if(adc_min>=7&&size_min>1){Particle=1;}
	  if(adc_min<=3&&size_min==1){Particle=2;}
	  if(ftime_min>10&&ftime_min<60){ETiming=3;}
	}

	//make event list
	int blockchx = (track_lg_lx->at(itrack))-(track_position_block_lx->at(itrack));
	int blockchy = (track_lg_ly->at(itrack)/fabs(track_lg_ly->at(itrack)))*(fabs(track_lg_ly->at(itrack))+track_position_block_ly->at(itrack));
	int blockch = SingleTrackAnalyzerForRes::LocaltoCh(blockchx,blockchy);
	if(HBDhit){
	  outtextfile<<run_id<<" "<<event_id<<" "<<trk_mid<<" "<<blockch<<" "<<track_position_block_lx->at(itrack)<<" "<<-(track_lg_ly->at(itrack)/fabs(track_lg_ly->at(itrack)))*(track_position_block_ly->at(itrack))<<" "<<track_mom->at(itrack)<<" "<<track_ssd_t->at(itrack)+54.<<" "<<rk_charge->at(itrack);
	  hlgblk[trk_mid-103]->Fill(blockch);
	}


	//LG Fill
	trk_mid = track_lg_mid->at(itrack);
	double phtext[9]={-10000.,-10000.,-10000.,-10000.,-10000.,-10000.,-10000.,-10000.,-10000.};
	for(int trktype=0;trktype<2;trktype++){
	  if(trktype==0&&(!HBDhit||trk_mid<103||trk_mid>107)){continue;}
	  if(trktype==1&&(trk_mid<103||trk_mid>107)){continue;}
	  double resx_min = track_lg_nearx->at(itrack);
	  double resy_min = track_lg_neary->at(itrack);
	  double tmptrkm = track_mom->at(itrack);
	  double adc_near = 10000;
	  int nlgh = track_lg_multiplicity->at(itrack);
	  int nlghitwt=0;
	  double tmpadcsum=0;
	  double tmptdiff=10000;
	  for(int ilg=0;ilg<nlgh;ilg++){
	    //if(track_lg_allhit_adc->at(itrack).at(ilg)>50) continue;//220208
	    double resx = track_lg_allhit_resx->at(itrack).at(ilg);
	    double resy = track_lg_allhit_resy->at(itrack).at(ilg);
	    double tmpadc = track_lg_allhit_adc->at(itrack).at(ilg);
	    double tmptdc = track_lg_allhit_ftime->at(itrack).at(ilg);
	    if(track_lg_allhit_adc->at(itrack).at(ilg)<50||tmptdc<(ssdoffset-ssdregion)+track_ssd_t->at(itrack)||tmptdc>(ssdoffset+ssdregion)+track_ssd_t->at(itrack)) continue;//220418
	    int cid = SingleTrackAnalyzerForRes::LocaltoCh(resx+track_lg_lx->at(itrack),resy+track_lg_ly->at(itrack));
	    if(cid==blockch+11&&tmpadc>phtext[0]){phtext[0]=tmpadc;}
	    if(cid==blockch+10&&tmpadc>phtext[1]){phtext[1]=tmpadc;}
	    if(cid==blockch+9 &&tmpadc>phtext[2]){phtext[2]=tmpadc;}
	    if(cid==blockch+1 &&tmpadc>phtext[3]){phtext[3]=tmpadc;}
	    if(cid==blockch   &&tmpadc>phtext[4]){phtext[4]=tmpadc;}
	    if(cid==blockch-1 &&tmpadc>phtext[5]){phtext[5]=tmpadc;}
	    if(cid==blockch-9 &&tmpadc>phtext[6]){phtext[6]=tmpadc;}
	    if(cid==blockch-10&&tmpadc>phtext[7]){phtext[7]=tmpadc;}
	    if(cid==blockch-11&&tmpadc>phtext[8]){phtext[8]=tmpadc;}
	    haresx[trk_mid-103][0][1+trktype*2]->Fill(resx);
	    haresy[trk_mid-103][0][1+trktype*2]->Fill(resy);
	    if(fabs(resy)<hw_inty[1+trktype*2]){
	      haresx[trk_mid-103][1][1+trktype*2]->Fill(resx);
	      if(rk_charge->at(itrack)==1){haresx[trk_mid-103][2][1+trktype*2]->Fill(resx);}
	      if(rk_charge->at(itrack)==-1){haresx[trk_mid-103][3][1+trktype*2]->Fill(resx);}
	    }
	    if(fabs(resx)<hw_intx[1+trktype*2]){
	      haresy[trk_mid-103][1][1+trktype*2]->Fill(resy);
	      if(rk_charge->at(itrack)==1){haresy[trk_mid-103][2][1+trktype*2]->Fill(resy);}
	      if(rk_charge->at(itrack)==-1){haresy[trk_mid-103][3][1+trktype*2]->Fill(resy);}
	    }
	    if(fabs(resx)<hw_intx[1+trktype*2]&&fabs(resy)<hw_inty[1+trktype*2]){
	      hadc[trk_mid-103][0][1+trktype*2]->Fill(track_lg_allhit_adc->at(itrack).at(ilg));
	      hadcp[trk_mid-103][0][1+trktype*2]->Fill(track_mom->at(itrack),track_lg_allhit_adc->at(itrack).at(ilg));
	      hadcop[trk_mid-103][0][1+trktype*2]->Fill(tmpadc/tmptrkm);
	      ht[trk_mid-103][0][1+trktype*2]->Fill(track_lg_allhit_ftime->at(itrack).at(ilg));
	      if(0.5<tmptrkm&&tmptrkm<0.7){hadcp05[trk_mid-103][0][1+trktype*2]->Fill(tmpadc);}
	      if(0.7<tmptrkm&&tmptrkm<0.9){hadcp07[trk_mid-103][0][1+trktype*2]->Fill(tmpadc);}
	      if(0.9<tmptrkm&&tmptrkm<1.1){hadcp09[trk_mid-103][0][1+trktype*2]->Fill(tmpadc);}
	      if(1.1<tmptrkm){hadcp11[trk_mid-103][0][1+trktype*2]->Fill(tmpadc);}
	      if(Particle==1){
		hadc[trk_mid-103][Particle][1+trktype*2]->Fill(track_lg_allhit_adc->at(itrack).at(ilg));
		hadcp[trk_mid-103][Particle][1+trktype*2]->Fill(track_mom->at(itrack),track_lg_allhit_adc->at(itrack).at(ilg));
		// if(tmpadc>50&&tmptrkm>0.5){hadcop[trk_mid-103][Particle][1+trktype*2]->Fill(tmptrkm-tmpadc/90.);}//220221
		if(tmpadc>50&&tmptrkm>0.5){hadcop[trk_mid-103][Particle][1+trktype*2]->Fill(tmpadc/tmptrkm);}//220221
		ht[trk_mid-103][Particle][1+trktype*2]->Fill(track_lg_allhit_ftime->at(itrack).at(ilg));
		if(0.5<tmptrkm&&tmptrkm<0.7){hadcp05[trk_mid-103][Particle][1+trktype*2]->Fill(tmpadc);}
		if(0.7<tmptrkm&&tmptrkm<0.9){hadcp07[trk_mid-103][Particle][1+trktype*2]->Fill(tmpadc);}
		if(0.9<tmptrkm&&tmptrkm<1.1){hadcp09[trk_mid-103][Particle][1+trktype*2]->Fill(tmpadc);}
		if(01.1<tmptrkm){hadcp11[trk_mid-103][Particle][1+trktype*2]->Fill(tmpadc);}
	      }
	      if(Particle==2){
		hadc[trk_mid-103][Particle][1+trktype*2]->Fill(track_lg_allhit_adc->at(itrack).at(ilg));
		hadcp[trk_mid-103][Particle][1+trktype*2]->Fill(track_mom->at(itrack),track_lg_allhit_adc->at(itrack).at(ilg));
		hadcop[trk_mid-103][Particle][1+trktype*2]->Fill(tmpadc/tmptrkm);
		ht[trk_mid-103][Particle][1+trktype*2]->Fill(track_lg_allhit_ftime->at(itrack).at(ilg));
		if(0.5<tmptrkm&&tmptrkm<0.7){hadcp05[trk_mid-103][Particle][1+trktype*2]->Fill(tmpadc);}
		if(0.7<tmptrkm&&tmptrkm<0.9){hadcp07[trk_mid-103][Particle][1+trktype*2]->Fill(tmpadc);}
		if(0.9<tmptrkm&&tmptrkm<1.1){hadcp09[trk_mid-103][Particle][1+trktype*2]->Fill(tmpadc);}
		if(1.1<tmptrkm){hadcp11[trk_mid-103][Particle][1+trktype*2]->Fill(tmpadc);}
	      }
	      if(ETiming==3){
		hadc[trk_mid-103][ETiming][1+trktype*2]->Fill(track_lg_allhit_adc->at(itrack).at(ilg));
		hadcp[trk_mid-103][ETiming][1+trktype*2]->Fill(track_mom->at(itrack),track_lg_allhit_adc->at(itrack).at(ilg));
		hadcop[trk_mid-103][ETiming][1+trktype*2]->Fill(tmpadc/tmptrkm);
		ht[trk_mid-103][ETiming][1+trktype*2]->Fill(track_lg_allhit_ftime->at(itrack).at(ilg));
		if(0.5<tmptrkm&&tmptrkm<0.7){hadcp05[trk_mid-103][ETiming][1+trktype*2]->Fill(tmpadc);}
		if(0.7<tmptrkm&&tmptrkm<0.9){hadcp07[trk_mid-103][ETiming][1+trktype*2]->Fill(tmpadc);}
		if(0.9<tmptrkm&&tmptrkm<1.1){hadcp09[trk_mid-103][ETiming][1+trktype*2]->Fill(tmpadc);}
		if(1.1<tmptrkm){hadcp11[trk_mid-103][ETiming][1+trktype*2]->Fill(tmpadc);}
	      }
	    }
	    if(resx==resx_min&&resy==resy_min){
	      adc_near = track_lg_allhit_adc->at(itrack).at(ilg);
	    }
	    hares[trk_mid-103][1+trktype*2]->Fill(resx,resy);
	    // if(tmpadc>20&&tmpadc<50){hares[trk_mid-103][1+trktype*2]->Fill(resx,resy);}//220216tmp
	    // if( trktype==0 && fabs(resx)<80 && fabs(resy)<100 ){
	    if( trktype==0 && fabs(resx)<50 && fabs(resy)<50 ){
	    // if( trktype==0 && fabs(resx)<80 && fabs(resy)<80 ){//220410
	      htimssdlg[trk_mid-103]->Fill(tmptdc,track_ssd_t->at(itrack));
	      htimssdlg1d[trk_mid-103]->Fill(tmptdc-track_ssd_t->at(itrack));
	      if( tmptdc>(ssdoffset-ssdregion)+track_ssd_t->at(itrack) && tmptdc<(ssdoffset+ssdregion)+track_ssd_t->at(itrack) ){
		if( fabs(tmptdc-track_ssd_t->at(itrack)-ssdoffset)<tmptdiff ){
		  tmpadcsum = tmpadc;
		  tmptdiff = fabs(tmptdc-track_ssd_t->at(itrack)-ssdoffset);
		}
		// tmpadcsum += tmpadc;//220410
	      	// nlghitwt++;//220410
	      }
	      // if( fabs( (track_ssd_t->at(itrack)+54.)-tmptdc )<10 ){//220405
	      // 	tmpadcsum+=tmpadc;
	      // 	nlghitwt++;
	      // 	//std::cout<<"ch:"<<cid<<", adc:"<<tmpadc<<", tim:"<<tmptdc<<std::endl;
	      // }//220405
	    }
	  }//lghit loop
	  // if(tmpadcsum!=0){
	  //   std::cout<<"ch:"<<blockch<<", lx:"<<track_position_block_lx->at(itrack)<<", ly:"<<track_position_block_ly->at(itrack)<<", mom:"<<track_mom->at(itrack)<<", adcsum:"<<tmpadcsum<<", tim:"<<track_ssd_t->at(itrack)+54.<<std::endl;
	  //   std::cout<<"********************************"<<std::endl;
	  // }
	  if(trktype==0){
	    ntrack[trk_mid-103][0][1+trktype*2]++;
	    ntrack[trk_mid-103][1][1+trktype*2]++;
	    hlghitsum[trk_mid-103]->Fill(track_mom->at(itrack),tmpadcsum);
	    hlgcor[trk_mid-103][blockch]->Fill(track_mom->at(itrack),tmpadcsum);
	    if(tmpadcsum>50){hedivp[trk_mid-103]->Fill(tmpadcsum/track_mom->at(itrack));}
	    // if(tmpadcsum>50){hedivp[trk_mid-103]->Fill((tmpadcsum-30)/track_mom->at(itrack));}
	    if(tmpadcsum>50){hesubp[trk_mid-103]->Fill(tmpadcsum-250*track_mom->at(itrack));}
	    hnlghitwt[trk_mid-103]->Fill(nlghitwt);
	  }
	  hx[trk_mid-103][1+trktype*2]->Fill(resx_min);
	  hy[trk_mid-103][1+trktype*2]->Fill(resy_min);
	  hn[trk_mid-103][1+trktype*2]->Fill(nlgh);

	  resx_dam_min = track_lg_dum_nearx->at(itrack);
	  resy_dam_min = track_lg_dum_neary->at(itrack);
	  double adc_dam_near = 10000;
	  int nlgh_dam = track_lg_dum_multiplicity->at(itrack);
	  double tmpadcsumd=0;
	  double tmptdiffd=10000;
	  for(int ilg=0;ilg<nlgh_dam;ilg++){
	    //if(track_lg_allhit_dum_adc->at(itrack).at(ilg)>50) continue;//220208
	    double resx_dam = track_lg_allhit_dum_resx->at(itrack).at(ilg);
	    double resy_dam = track_lg_allhit_dum_resy->at(itrack).at(ilg);
	    double adc_dam = track_lg_allhit_dum_adc->at(itrack).at(ilg);;
	    haresxd[trk_mid-103][0][1+trktype*2]->Fill(resx_dam);
	    haresyd[trk_mid-103][0][1+trktype*2]->Fill(resy_dam);
	    if(fabs(resy_dam)<hw_inty[1+trktype*2]){
	      haresxd[trk_mid-103][1][1+trktype*2]->Fill(resx_dam);
	      if(rk_charge->at(itrack)==1){haresxd[trk_mid-103][2][1+trktype*2]->Fill(resx_dam);}
	      if(rk_charge->at(itrack)==-1){haresxd[trk_mid-103][3][1+trktype*2]->Fill(resx_dam);}
	    }
	    if(fabs(resx_dam)<hw_intx[1+trktype*2]){
	      haresyd[trk_mid-103][1][1+trktype*2]->Fill(resy_dam);
	      if(rk_charge->at(itrack)==1){haresyd[trk_mid-103][2][1+trktype*2]->Fill(resy_dam);}
	      if(rk_charge->at(itrack)==-1){haresyd[trk_mid-103][3][1+trktype*2]->Fill(resy_dam);}
	      if(fabs(resy_dam)<hw_inty[1+trktype*2]){
		hadcd[trk_mid-103][0][1+trktype*2]->Fill(track_lg_allhit_dum_adc->at(itrack).at(ilg));
		hadcopd[trk_mid-103][0][1+trktype*2]->Fill(adc_dam/tmptrkm);
		htd[trk_mid-103][0][1+trktype*2]->Fill(track_lg_allhit_dum_ftime->at(itrack).at(ilg));
		if(Particle==1){
		  hadcd[trk_mid-103][Particle][1+trktype*2]->Fill(track_lg_allhit_dum_adc->at(itrack).at(ilg));
		  // if(adc_dam>50&&tmptrkm>0.5){hadcopd[trk_mid-103][Particle][1+trktype*2]->Fill(tmptrkm-adc_dam/90.);}//220221
		  if(adc_dam>50&&tmptrkm>0.5){hadcopd[trk_mid-103][Particle][1+trktype*2]->Fill(adc_dam/tmptrkm);}//220221
		  htd[trk_mid-103][Particle][1+trktype*2]->Fill(track_lg_allhit_dum_ftime->at(itrack).at(ilg));
		}
		if(Particle==2){
		  hadcd[trk_mid-103][Particle][1+trktype*2]->Fill(track_lg_allhit_dum_adc->at(itrack).at(ilg));
		  hadcopd[trk_mid-103][Particle][1+trktype*2]->Fill(adc_dam/tmptrkm);
		  htd[trk_mid-103][Particle][1+trktype*2]->Fill(track_lg_allhit_dum_ftime->at(itrack).at(ilg));
		}
		if(ETiming==3){
		  hadcd[trk_mid-103][ETiming][1+trktype*2]->Fill(track_lg_allhit_dum_adc->at(itrack).at(ilg));
		  hadcopd[trk_mid-103][ETiming][1+trktype*2]->Fill(adc_dam/tmptrkm);
		  htd[trk_mid-103][ETiming][1+trktype*2]->Fill(track_lg_allhit_dum_ftime->at(itrack).at(ilg));
		}
	      }
	    }
	    if(resx_dam==resx_dam_min&&resy_dam==resy_dam_min){
	      adc_dam_near = track_lg_allhit_dum_adc->at(itrack).at(ilg);
	    }
	    haresd[trk_mid-103][1+trktype*2]->Fill(resx_dam,resy_dam);
	    // if(adc_dam>20&&adc_dam<50){haresd[trk_mid-103][1+trktype*2]->Fill(resx_dam,resy_dam);}//220216tmp
	    double tmptdcd = track_lg_allhit_dum_ftime->at(itrack).at(ilg);
	    if( trktype==0 && fabs(resx_dam)<50 && fabs(resy_dam)<50 ){
	    // if( trktype==0 && fabs(resx_dam)<80 && fabs(resy_dam)<80 ){//220410
	      // tmpadcsumd+=adc_dam;
	      if( tmptdcd>(ssdoffset-ssdregion)+track_ssd_t->at(itrack) && tmptdcd<(ssdoffset+ssdregion)+track_ssd_t->at(itrack) ){
		if( fabs(tmptdcd-track_ssd_t->at(itrack)-ssdoffset)<tmptdiffd ){
		  tmpadcsumd = adc_dam;
		  tmptdiffd = fabs(tmptdcd-track_ssd_t->at(itrack)-ssdoffset);
		}
		// tmpadcsumd += adc_dam;//220410
	      }
	    }
	  }
	  if(trktype==0){
	    hlghitsumd[trk_mid-103]->Fill(track_mom->at(itrack),tmpadcsumd);
	    if(tmpadcsumd>50){hedivpd[trk_mid-103]->Fill(tmpadcsumd/track_mom->at(itrack));}
	    // if(tmpadcsumd>50){hedivpd[trk_mid-103]->Fill((tmpadcsumd-30)/track_mom->at(itrack));}
	    if(tmpadcsumd>50){hesubpd[trk_mid-103]->Fill(tmpadcsumd-250*track_mom->at(itrack));}
	  }
	  hxd[trk_mid-103][1+trktype*2]->Fill(resx_dam_min);
	  hyd[trk_mid-103][1+trktype*2]->Fill(resy_dam_min);
	  hnd[trk_mid-103][1+trktype*2]->Fill(nlgh_dam);

	  //rejection
	  // if(trktype==0&&Particle==2){//HBDHit&isPi
	  if(trktype==0){//HBDHit
	    ntrack[trk_mid-103][2][1+trktype*2]++;//220218tmp
	    ntrack[trk_mid-103][3][1+trktype*2]++;//220218tmp
	    lgtrkmom[trk_mid-103]->Fill(track_mom->at(itrack));
	    // lgtrk1eff[trk_mid-103]->Fill(track_lg_pi_eff1->at(itrack));
	    // lgtrk2eff[trk_mid-103]->Fill(track_lg_pi_eff2->at(itrack));
	    if(fabs(resx_min)<hw_intx[1]&&fabs(resy_min)<hw_inty[1]){lgadc[trk_mid-103]->Fill(adc_near);}//220312
	    else{lgadc[trk_mid-103]->Fill(0.);}//220312
	    // if(trk_mid==106){//220219
	    //   if(fabs(resx_min)<hw_intx[1]&&fabs(resy_min)<hw_inty[1]){lgadcene->Fill(adc_near/198.);}//220219
	    //   else{lgadcene->Fill(0.);}//220219
	    // }//220219
	    if(fabs(resx_dam_min)<hw_intx[1]&&fabs(resy_dam_min)<hw_inty[1]){lgadcd[trk_mid-103]->Fill(adc_dam_near);}//220312
	    else{lgadcd[trk_mid-103]->Fill(0.);}//220312
	    // if(trk_mid==106){//220219
	    //   if(fabs(resx_dam_min)<hw_intx[1]&&fabs(resy_dam_min)<hw_inty[1]){lgadcened->Fill(adc_dam_near/198.);}//220219
	    //   else{lgadcened->Fill(0.);}//220219
	    // }//220219
	  }//220216
	  if(trktype==1&&fabs(resx_min)<hw_intx[1]&&fabs(resy_min)<hw_inty[1]){//LGHit w/oHBDHit
	    ntrack[trk_mid-103][0][1+trktype*2]++;
	    ntrack[trk_mid-103][1][1+trktype*2]++;
	    // if(adc_near<50&&adc_near>20){//LGisPi
	      ntrack[trk_mid-103][2][1+trktype*2]++;//220216tmp
	      ntrack[trk_mid-103][3][1+trktype*2]++;//220216tmp
	      if(fabs(track_hbd_nearx->at(itrack))<hw_intx[0]&&fabs(track_hbd_neary->at(itrack))<hw_intx[0]){
	  	hbdadc[trk_mid-103]->Fill(adc_min);
	      }
	      else{
	  	hbdadc[trk_mid-103]->Fill(0.);
	      }
	      if(fabs(track_hbd_dum_nearx->at(itrack))<hw_intx[0]&&fabs(track_hbd_dum_neary->at(itrack))<hw_intx[0]){
	  	hbdadcd[trk_mid-103]->Fill(adc_dam_min);
	      }
	      else{
	  	hbdadcd[trk_mid-103]->Fill(0.);
	      }
	    // }
	  }//220215
	  //rejection

	  //LG Cluster Fill
	  resx_min = track_lg_cl_nearx->at(itrack);
	  resy_min = track_lg_cl_neary->at(itrack);
	  int nlgc = track_lg_cl_multiplicity->at(itrack);
	  for(int ilg=0;ilg<nlgc;ilg++){
	    //if(track_lg_cl_allhit_adc->at(itrack).at(ilg)>50) continue;//220208
	    double resx = track_lg_cl_allhit_resx->at(itrack).at(ilg);
	    double resy = track_lg_cl_allhit_resy->at(itrack).at(ilg);
	    double tmptrkm = track_mom->at(itrack);
	    double tmpadc = track_lg_allhit_adc->at(itrack).at(ilg);
	    haresx[trk_mid-103][0][2+trktype*2]->Fill(resx);
	    haresy[trk_mid-103][0][2+trktype*2]->Fill(resy);
	    if(resx==resx_min&&resy==resy_min){
	      adc_near = track_lg_cl_allhit_adc->at(itrack).at(ilg);
	    }
	    if(fabs(resy)<hw_inty[2+trktype*2]){
	      haresx[trk_mid-103][1][2+trktype*2]->Fill(resx);
	      if(rk_charge->at(itrack)==1){haresx[trk_mid-103][2][2+trktype*2]->Fill(resx);}
	      if(rk_charge->at(itrack)==-1){haresx[trk_mid-103][3][2+trktype*2]->Fill(resx);}
	    }
	    if(fabs(resx)<hw_intx[2+trktype*2]){
	      haresy[trk_mid-103][1][2+trktype*2]->Fill(resy);
	      if(rk_charge->at(itrack)==1){haresy[trk_mid-103][2][2+trktype*2]->Fill(resy);}
	      if(rk_charge->at(itrack)==-1){haresy[trk_mid-103][3][2+trktype*2]->Fill(resy);}
	      if(fabs(resy)<hw_inty[2+trktype*2]){
		hadc[trk_mid-103][0][2+trktype*2]->Fill(track_lg_cl_allhit_adc->at(itrack).at(ilg));
		hadcp[trk_mid-103][0][2+trktype*2]->Fill(track_mom->at(itrack),track_lg_cl_allhit_adc->at(itrack).at(ilg));
		hadcop[trk_mid-103][0][2+trktype*2]->Fill(tmpadc/tmptrkm);
		ht[trk_mid-103][0][2+trktype*2]->Fill(track_lg_cl_allhit_ftime->at(itrack).at(ilg));
		if(0.5<tmptrkm&&tmptrkm<0.7){hadcp05[trk_mid-103][0][2+trktype*2]->Fill(tmpadc);}
		if(0.7<tmptrkm&&tmptrkm<0.9){hadcp07[trk_mid-103][0][2+trktype*2]->Fill(tmpadc);}
		if(0.9<tmptrkm&&tmptrkm<1.1){hadcp09[trk_mid-103][0][2+trktype*2]->Fill(tmpadc);}
		if(01.1<tmptrkm){hadcp11[trk_mid-103][0][2+trktype*2]->Fill(tmpadc);}
		if(Particle==1){
		  hadc[trk_mid-103][Particle][2+trktype*2]->Fill(track_lg_cl_allhit_adc->at(itrack).at(ilg));
		  hadcp[trk_mid-103][Particle][2+trktype*2]->Fill(track_mom->at(itrack),track_lg_cl_allhit_adc->at(itrack).at(ilg));
		  // if(tmpadc>50&&tmptrkm>0.5){hadcop[trk_mid-103][Particle][2+trktype*2]->Fill(tmptrkm-tmpadc/90.);}//220221
		  if(tmpadc>50&&tmptrkm>0.5){hadcop[trk_mid-103][Particle][2+trktype*2]->Fill(tmpadc/tmptrkm);}//220221
		  ht[trk_mid-103][Particle][2+trktype*2]->Fill(track_lg_cl_allhit_ftime->at(itrack).at(ilg));
		  if(0.5<tmptrkm&&tmptrkm<0.7){hadcp05[trk_mid-103][Particle][2+trktype*2]->Fill(tmpadc);}
		  if(0.7<tmptrkm&&tmptrkm<0.9){hadcp07[trk_mid-103][Particle][2+trktype*2]->Fill(tmpadc);}
		  if(0.9<tmptrkm&&tmptrkm<1.1){hadcp09[trk_mid-103][Particle][2+trktype*2]->Fill(tmpadc);}
		  if(01.1<tmptrkm){hadcp11[trk_mid-103][Particle][2+trktype*2]->Fill(tmpadc);}
		}
		if(Particle==2){
		  hadc[trk_mid-103][Particle][2+trktype*2]->Fill(track_lg_cl_allhit_adc->at(itrack).at(ilg));
		  hadcp[trk_mid-103][Particle][2+trktype*2]->Fill(track_mom->at(itrack),track_lg_cl_allhit_adc->at(itrack).at(ilg));
		  hadcop[trk_mid-103][Particle][2+trktype*2]->Fill(tmpadc/tmptrkm);
		  ht[trk_mid-103][Particle][2+trktype*2]->Fill(track_lg_cl_allhit_ftime->at(itrack).at(ilg));
		  if(0.5<tmptrkm&&tmptrkm<0.7){hadcp05[trk_mid-103][Particle][2+trktype*2]->Fill(tmpadc);}
		  if(0.7<tmptrkm&&tmptrkm<0.9){hadcp07[trk_mid-103][Particle][2+trktype*2]->Fill(tmpadc);}
		  if(0.9<tmptrkm&&tmptrkm<1.1){hadcp09[trk_mid-103][Particle][2+trktype*2]->Fill(tmpadc);}
		  if(01.1<tmptrkm){hadcp11[trk_mid-103][Particle][2+trktype*2]->Fill(tmpadc);}
		}
		if(ETiming==3){
		  hadc[trk_mid-103][ETiming][2+trktype*2]->Fill(track_lg_cl_allhit_adc->at(itrack).at(ilg));
		  hadcp[trk_mid-103][ETiming][2+trktype*2]->Fill(track_mom->at(itrack),track_lg_cl_allhit_adc->at(itrack).at(ilg));
		  hadcop[trk_mid-103][ETiming][2+trktype*2]->Fill(tmpadc/tmptrkm);
		  ht[trk_mid-103][ETiming][2+trktype*2]->Fill(track_lg_cl_allhit_ftime->at(itrack).at(ilg));
		  if(0.5<tmptrkm&&tmptrkm<0.7){hadcp05[trk_mid-103][ETiming][2+trktype*2]->Fill(tmpadc);}
		  if(0.7<tmptrkm&&tmptrkm<0.9){hadcp07[trk_mid-103][ETiming][2+trktype*2]->Fill(tmpadc);}
		  if(0.9<tmptrkm&&tmptrkm<1.1){hadcp09[trk_mid-103][ETiming][2+trktype*2]->Fill(tmpadc);}
		  if(01.1<tmptrkm){hadcp11[trk_mid-103][ETiming][2+trktype*2]->Fill(tmpadc);}
		}
	      }
	    }
	    hares[trk_mid-103][2+trktype*2]->Fill(resx,resy);
	  }
	  ntrack[trk_mid-103][0][2+trktype*2]++;
	  ntrack[trk_mid-103][1][2+trktype*2]++;
	  hx[trk_mid-103][2+trktype*2]->Fill(resx_min);
	  hy[trk_mid-103][2+trktype*2]->Fill(resy_min);
	  hn[trk_mid-103][2+trktype*2]->Fill(nlgc);

	  resx_dam_min = track_lg_cl_dum_nearx->at(itrack);
	  resy_dam_min = track_lg_cl_dum_neary->at(itrack);
	  int nlgc_dam = track_lg_cl_dum_multiplicity->at(itrack);
	  for(int ilg=0;ilg<nlgc_dam;ilg++){
	    //if(track_lg_cl_allhit_dum_adc->at(itrack).at(ilg)>50) continue;//220208
	    double resx_dam = track_lg_cl_allhit_dum_resx->at(itrack).at(ilg);
	    double resy_dam = track_lg_cl_allhit_dum_resy->at(itrack).at(ilg);
	    double adc_dam = track_lg_cl_allhit_dum_adc->at(itrack).at(ilg);
	    haresxd[trk_mid-103][0][2+trktype*2]->Fill(resx_dam);
	    haresyd[trk_mid-103][0][2+trktype*2]->Fill(resy_dam);
	    if(fabs(resy_dam)<hw_inty[2+trktype*2]){
	      haresxd[trk_mid-103][1][2+trktype*2]->Fill(resx_dam);
	      if(rk_charge->at(itrack)==1){haresxd[trk_mid-103][2][2+trktype*2]->Fill(resx_dam);}
	      if(rk_charge->at(itrack)==-1){haresxd[trk_mid-103][3][2+trktype*2]->Fill(resx_dam);}
	    }
	    if(fabs(resx_dam)<hw_intx[2+trktype*2]){
	      haresyd[trk_mid-103][1][2+trktype*2]->Fill(resy_dam);
	      if(rk_charge->at(itrack)==1){haresyd[trk_mid-103][2][2+trktype*2]->Fill(resy_dam);}
	      if(rk_charge->at(itrack)==-1){haresyd[trk_mid-103][3][2+trktype*2]->Fill(resy_dam);}
	      if(fabs(resy_dam)<hw_inty[2+trktype*2]){
		hadcd[trk_mid-103][0][2+trktype*2]->Fill(track_lg_cl_allhit_dum_adc->at(itrack).at(ilg));
		hadcopd[trk_mid-103][0][2+trktype*2]->Fill(adc_dam/tmptrkm);
		htd[trk_mid-103][0][2+trktype*2]->Fill(track_lg_cl_allhit_dum_ftime->at(itrack).at(ilg));
		if(Particle==1){
		  hadcd[trk_mid-103][Particle][2+trktype*2]->Fill(track_lg_cl_allhit_dum_adc->at(itrack).at(ilg));
		  // if(adc_dam>50&&tmptrkm>0.5){hadcopd[trk_mid-103][Particle][2+trktype*2]->Fill(tmptrkm-adc_dam/90.);}//220221
		  if(adc_dam>50&&tmptrkm>0.5){hadcopd[trk_mid-103][Particle][2+trktype*2]->Fill(adc_dam/tmptrkm);}//220221
		  htd[trk_mid-103][Particle][2+trktype*2]->Fill(track_lg_cl_allhit_dum_ftime->at(itrack).at(ilg));
		}
		if(Particle==2){
		  hadcd[trk_mid-103][Particle][2+trktype*2]->Fill(track_lg_cl_allhit_dum_adc->at(itrack).at(ilg));
		  hadcopd[trk_mid-103][Particle][2+trktype*2]->Fill(adc_dam/tmptrkm);
		  htd[trk_mid-103][Particle][2+trktype*2]->Fill(track_lg_cl_allhit_dum_ftime->at(itrack).at(ilg));
		}
		if(ETiming==3){
		  hadcd[trk_mid-103][ETiming][2+trktype*2]->Fill(track_lg_cl_allhit_dum_adc->at(itrack).at(ilg));
		  hadcopd[trk_mid-103][ETiming][2+trktype*2]->Fill(adc_dam/tmptrkm);
		  htd[trk_mid-103][ETiming][2+trktype*2]->Fill(track_lg_cl_allhit_dum_ftime->at(itrack).at(ilg));
		}
	      }
	    }
	    haresd[trk_mid-103][2+trktype*2]->Fill(resx_dam,resy_dam);
	  }
	  hxd[trk_mid-103][2+trktype*2]->Fill(resx_dam_min);
	  hyd[trk_mid-103][2+trktype*2]->Fill(resy_dam_min);
	  hnd[trk_mid-103][2+trktype*2]->Fill(nlgc_dam);

	}

	//make event list
	if(HBDhit){
	  outtextfile<<" "<<phtext[0]<<" "<<phtext[1]<<" "<<phtext[2]<<" "<<phtext[3]<<" "<<phtext[4]<<" "<<phtext[5]<<" "<<phtext[6]<<" "<<phtext[7]<<" "<<phtext[8]<<std::endl;
	}


	//make mixing
      	int mide = track_hbd_mid->at(itrack)-103;
      	if(hbdmixhits[mide].size()!=0&&lgmixhits[mide].size()!=0){//calc res
	  for(int ihbd=0;ihbd<hbdmixhits[mide].size();ihbd++){
	    for(int jhbd=0;jhbd<hbdmixhits[mide].at(ihbd).size();jhbd++){
	      double tmpresx = hbdmixhits[mide].at(ihbd).at(jhbd).lx-track_hbd_lx->at(itrack);
	      double tmpresy = hbdmixhits[mide].at(ihbd).at(jhbd).ly-track_hbd_ly->at(itrack);
	      if(fabs(tmpresy)<hw_intx[0]){
		hbdresxmix[mide]->Fill(hbdmixhits[mide].at(ihbd).at(jhbd).lx-track_hbd_lx->at(itrack));
	      }
	      if(fabs(tmpresx)<hw_intx[0]){
		hbdresymix[mide]->Fill(hbdmixhits[mide].at(ihbd).at(jhbd).ly-track_hbd_ly->at(itrack));
	      }
	    }
	  }
	  for(int ilg=0;ilg<lgmixhits[mide].size();ilg++){
	    for(int jlg=0;jlg<lgmixhits[mide].at(ilg).size();jlg++){
	      double tmpresx = lgmixhits[mide].at(ilg).at(jlg).lx-track_lg_lx->at(itrack);
	      double tmpresy = lgmixhits[mide].at(ilg).at(jlg).ly-track_lg_ly->at(itrack);
	      double tmpt = lgmixhits[mide].at(ilg).at(jlg).tdc;
	      double tmpa = lgmixhits[mide].at(ilg).at(jlg).adc;
	      if(tmpa<50||tmpt<(ssdoffset-ssdregion)+track_ssd_t->at(itrack)||tmpt>(ssdoffset+ssdregion)+track_ssd_t->at(itrack)) continue;//220418
	      if(HBDhit && fabs(tmpresy)<hw_inty[1]){
		lgresxmix[mide]->Fill(tmpresx);
	      }
	      if(HBDhit && fabs(tmpresx)<hw_intx[1]){
		lgresymix[mide]->Fill(tmpresy);
	      }
	      if(HBDhit && fabs(tmpresx)<50 && fabs(tmpresy)<50 &&
		tmpt>(ssdoffset-ssdregion)+track_ssd_t->at(itrack) &&
		tmpt<(ssdoffset+ssdregion)+track_ssd_t->at(itrack)){
		if(tmpa>50){lgadcmix[mide]->Fill(tmpa/track_mom->at(itrack));}
	      }
	    }
	  }
	}//calc res
      	if(alfill[mide]==false){//hit fill
      	  alfill[mide]=true;
	  std::vector<hitset> hbdhits;
      	  for(int ihbd=0;ihbd<track_hbd_multiplicity->at(itrack);ihbd++){
      	    hitset hbdhit;
      	    hbdhit.mid=track_hbd_mid->at(itrack);
      	    hbdhit.lx=track_hbd_allhit_resx->at(itrack).at(ihbd)+track_hbd_lx->at(itrack);
      	    hbdhit.ly=track_hbd_allhit_resy->at(itrack).at(ihbd)+track_hbd_ly->at(itrack);
      	    hbdhit.adc=track_hbd_allhit_adc->at(itrack).at(ihbd);
      	    hbdhit.tdc=track_hbd_allhit_ftime->at(itrack).at(ihbd);
      	    hbdhits.push_back(hbdhit);
      	  }
	  hbdmixhits[mide].push_back(hbdhits);
	  std::vector<hitset> lghits;
      	  for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){
      	    hitset lghit;
      	    lghit.mid=track_lg_mid->at(itrack);
      	    lghit.lx=track_lg_allhit_resx->at(itrack).at(ilg)+track_lg_lx->at(itrack);
      	    lghit.ly=track_lg_allhit_resy->at(itrack).at(ilg)+track_lg_ly->at(itrack);
      	    lghit.adc=track_lg_allhit_adc->at(itrack).at(ilg);
      	    lghit.tdc=track_lg_allhit_ftime->at(itrack).at(ilg);
      	    lghits.push_back(lghit);
      	  }
	  lgmixhits[mide].push_back(lghits);
	  if(hbdmixhits[mide].size()>50){
	    hbdmixhits[mide].erase(hbdmixhits[mide].begin());
	  }
	  if(lgmixhits[mide].size()>50){
	    lgmixhits[mide].erase(lgmixhits[mide].begin());
	  }
      	}//hit fill
	//make mixing

      }//track loop

      he->Fill(n_tracks);

      nevent++;

   }//event loop

   TH1F* hsub[4][4][ndet];
   int hint[4][4][ndet];
   for(int k=0;k<ndet;k++){
     int regm = roughbin[k]/2-halfwidth[k]*roughbin[k]/1600;
     int regp = roughbin[k]/2+halfwidth[k]*roughbin[k]/1600;
     for(int j=0;j<4;j++){
       hsub[j][0][k] = (TH1F*)hx[(j+3)%5][k]->Clone();
       hsub[j][1][k] = (TH1F*)hy[(j+3)%5][k]->Clone();
       hsub[j][2][k] = (TH1F*)hxd[(j+3)%5][k]->Clone();
       hsub[j][3][k] = (TH1F*)hyd[(j+3)%5][k]->Clone();
       for(int i=0;i<4;i++){
	 hint[j][i][k] = hsub[j][i][k]->Integral(0,regm)+hsub[j][i][k]->Integral(regp,roughbin[k]);
       }
       hsub[j][2][k]->Scale((double)hint[j][0][k]/(double)hint[j][2][k]);
       hsub[j][3][k]->Scale((double)hint[j][1][k]/(double)hint[j][3][k]);
       hsub[j][0][k]->Add(hsub[j][2][k],-1);
       hsub[j][1][k]->Add(hsub[j][3][k],-1);
     }
   }

   TString outfile = Form("%s",out_file_name);

   gStyle->SetOptStat(11111111);
   gStyle->SetOptFit(11111111);
   TCanvas* ce = new TCanvas("ce","ce",700,500);
   ce->cd()->SetLogy();
   ce->SetGrid();
   he->Draw();
   TCanvas* c[8][ndet];
   for(int k=0;k<ndet;k++){
     for(int i=0;i<8;i++){
       c[i][k] = new TCanvas(Form("c%d%d",i,k),Form("c%d%d",i,k),700,500);
       c[i][k]->Divide(2,2);
     }
     for(int i=0;i<4;i++){
       c[0][k]->cd(i+1);
       hx[(i+3)%5][k]->Draw();
       c[1][k]->cd(i+1);
       hxd[(i+3)%5][k]->Draw();
       c[2][k]->cd(i+1);
       hy[(i+3)%5][k]->Draw();
       c[3][k]->cd(i+1);
       hyd[(i+3)%5][k]->Draw();
       c[4][k]->cd(i+1);
       hn[(i+3)%5][k]->Draw();
       c[5][k]->cd(i+1);
       hnd[(i+3)%5][k]->Draw();
       c[6][k]->cd(i+1)->DrawFrame(-200,0,200,(hx[(i+3)%5][k]->GetMaximum())*1.1);
       c[6][k]->cd(i+1)->SetGrid();
       hx[(i+3)%5][k]->Draw("same");
       c[7][k]->cd(i+1)->DrawFrame(-200,0,200,(hy[(i+3)%5][k]->GetMaximum())*1.1);
       c[7][k]->cd(i+1)->SetGrid();
       hy[(i+3)%5][k]->Draw("same");
     }
   }
   TCanvas* clgod[2];
   for(int j=0;j<2;j++){
     clgod[j] = new TCanvas(Form("clgod%d",j),Form("clgod%d",j),700,500);
     clgod[j]->Divide(2,2);
   }
   for(int i=0;i<4;i++){
     for(int j=0;j<2;j++){
       clgod[j]->cd(i+1);
       hadcop[(i+3)%5][1][1+j]->Draw("hist");
       hadcopd[(i+3)%5][1][1+j]->SetLineColor(6);
       hadcopd[(i+3)%5][1][1+j]->Draw("hist same");
     }
   }
   // TCanvas* clgod[10];
   // for(int j=0;j<10;j++){
   //   clgod[j] = new TCanvas(Form("clgod%d",j),Form("clgod%d",j),700,500);
   //   clgod[j]->Divide(2,2);
   // }
   // for(int i=0;i<4;i++){
   //   for(int j=0;j<2;j++){
   //     clgod[0+5*j]->cd(i+1);
   //     hadcp05[(i+3)%5][2][1+j]->DrawNormalized("hist");
   //     hadcp05[(i+3)%5][1][1+j]->SetLineColor(2);
   //     hadcp05[(i+3)%5][1][1+j]->DrawNormalized("hist same");
   //     clgod[1+5*j]->cd(i+1);
   //     hadcp07[(i+3)%5][2][1+j]->DrawNormalized("hist");
   //     hadcp07[(i+3)%5][1][1+j]->SetLineColor(2);
   //     hadcp07[(i+3)%5][1][1+j]->DrawNormalized("hist same");
   //     clgod[2+5*j]->cd(i+1);
   //     hadcp09[(i+3)%5][2][1+j]->DrawNormalized("hist");
   //     hadcp09[(i+3)%5][1][1+j]->SetLineColor(2);
   //     hadcp09[(i+3)%5][1][1+j]->DrawNormalized("hist same");
   //     clgod[3+5*j]->cd(i+1);
   //     hadcp11[(i+3)%5][2][1+j]->DrawNormalized("hist");
   //     hadcp11[(i+3)%5][1][1+j]->SetLineColor(2);
   //     hadcp11[(i+3)%5][1][1+j]->DrawNormalized("hist same");
   //     clgod[4+5*j]->cd(i+1);
   //     hadcop[(i+3)%5][2][1+j]->DrawNormalized("hist");
   //     hadcop[(i+3)%5][1][1+j]->SetLineColor(2);
   //     hadcop[(i+3)%5][1][1+j]->DrawNormalized("hist same");
   //   }
   // }
   TCanvas* chbd[8][nsel][ndet];
   for(int k=0;k<ndet;k++){
     for(int j=0;j<nsel;j++){
       for(int i=0;i<8;i++){
	 chbd[i][j][k] = new TCanvas(Form("chbd%d%d%d",i,j,k),Form("chbd%d%d%d",i,j,k),700,500);
	 chbd[i][j][k]->Divide(2,2);
       }
       for(int i=0;i<4;i++){
	 chbd[0][j][k]->cd(i+1);
	 ht[(i+3)%5][j][k]->Draw();
	 htd[(i+3)%5][j][k]->SetLineColor(6);
	 htd[(i+3)%5][j][k]->Draw("sames");
	 chbd[0][j][k]->cd(i+1)->Update();
	 TPaveStats *st1 = (TPaveStats*)htd[(i+3)%5][j][k]->FindObject("stats");
	 st1->SetLineColor(6);
	 st1->SetX1NDC(0.58);
	 st1->SetX2NDC(0.78);
	 st1->SetY1NDC(0.495);
	 st1->SetY2NDC(0.935);
	 chbd[0][j][k]->cd(i+1)->Modified();
	 chbd[1][j][k]->cd(i+1);
	 hadc[(i+3)%5][j][k]->Draw();
	 hadcd[(i+3)%5][j][k]->SetLineColor(6);
	 hadcd[(i+3)%5][j][k]->Draw("sames");
	 chbd[1][j][k]->cd(i+1)->Update();
	 TPaveStats *st2 = (TPaveStats*)hadcd[(i+3)%5][j][k]->FindObject("stats");
	 st2->SetLineColor(6);
	 st2->SetX1NDC(0.58);
	 st2->SetX2NDC(0.78);
	 st2->SetY1NDC(0.495);
	 st2->SetY2NDC(0.935);
	 chbd[1][j][k]->cd(i+1)->Modified();
	 chbd[2][j][k]->cd(i+1);
	 hadcp[(i+3)%5][j][k]->Draw("colz");
	 chbd[3][j][k]->cd(i+1);
	 hadcp05[(i+3)%5][j][k]->Draw();
	 chbd[4][j][k]->cd(i+1);
	 hadcp07[(i+3)%5][j][k]->Draw();
	 chbd[5][j][k]->cd(i+1);
	 hadcp09[(i+3)%5][j][k]->Draw();
	 chbd[6][j][k]->cd(i+1);
	 hadcp11[(i+3)%5][j][k]->Draw();
	 chbd[7][j][k]->cd(i+1);
	 hadcop[(i+3)%5][j][k]->Draw();
       }
     }
   }
   TCanvas* csubd[4][ndet];
   TLegend* lhsub[2][4][ndet];
   int vhsub[4][ndet];
   for(int k=0;k<ndet;k++){
     for(int i=0;i<4;i++){
       csubd[i][k] = new TCanvas(Form("csubd%d%d",i,k),Form("csubd%d%d",i,k),700,500);
       csubd[i][k]->Divide(2,2);
       csubd[i][k]->cd(1);
       hx[(i+3)%5][k]->Draw("hist e");
       hsub[i][2][k]->SetLineColor(2);
       hsub[i][2][k]->Draw("hist e same");
       vhsub[0][k] = hx[(i+3)%5][k]->Integral(roughbin[k]/2-hw_intx[k]*roughbin[k]/1600,roughbin[k]/2+hw_inty[k]*roughbin[k]/1600);
       vhsub[2][k] = hsub[i][2][k]->Integral(roughbin[k]/2-hw_intx[k]*roughbin[k]/1600,roughbin[k]/2+hw_inty[k]*roughbin[k]/1600);
       lhsub[0][i][k] = new TLegend(0.1,0.75,0.4,0.9);
       lhsub[0][i][k]->AddEntry(hx[(i+3)%5][k],Form("%d<Integral<%d, %d",-hw_intx[k],hw_intx[k],vhsub[0][k]),"l");
       lhsub[0][i][k]->AddEntry(hsub[i][2][k],Form("%d<Integral<%d, %d",-hw_intx[k],hw_intx[k],vhsub[2][k]),"l");
       lhsub[0][i][k]->AddEntry((TObject*)0,Form("ratio: %1.3f",(double)vhsub[2][k]/(double)vhsub[0][k]),"");
       lhsub[0][i][k]->Draw();
       csubd[i][k]->cd(2);
       hy[(i+3)%5][k]->Draw("hist e");
       hsub[i][3][k]->SetLineColor(2);
       hsub[i][3][k]->Draw("hist e same");
       vhsub[1][k] = hy[(i+3)%5][k]->Integral(roughbin[k]/2-hw_inty[k]*roughbin[k]/1600,roughbin[k]/2+hw_inty[k]*roughbin[k]/1600);
       vhsub[3][k] = hsub[i][3][k]->Integral(roughbin[k]/2-hw_inty[k]*roughbin[k]/1600,roughbin[k]/2+hw_inty[k]*roughbin[k]/1600);
       lhsub[1][i][k] = new TLegend(0.1,0.75,0.4,0.9);
       lhsub[1][i][k]->AddEntry(hy[(i+3)%5][k],Form("%d<Integral<%d, %d",-hw_inty[k],hw_inty[k],vhsub[1][k]),"l");
       lhsub[1][i][k]->AddEntry(hsub[i][3][k],Form("%d<Integral<%d, %d",-hw_inty[k],hw_inty[k],vhsub[3][k]),"l");
       lhsub[1][i][k]->AddEntry((TObject*)0,Form("ratio: %1.3f",(double)vhsub[3][k]/(double)vhsub[1][k]),"");
       lhsub[1][i][k]->Draw();
       csubd[i][k]->cd(3);
       hsub[i][0][k]->Draw("hist e");
       hsub[i][0][k]->Fit("gaus","","",-fitregion[k],fitregion[k]);
       csubd[i][k]->cd(4);
       hsub[i][1][k]->Draw("hist e");
       hsub[i][1][k]->Fit("gaus","","",-fitregion[k],fitregion[k]);
     }
   }
   TCanvas* casubd[4][nopt][ndet];
   TH1F* hasubd[4][2][nopt][ndet];
   TF1* fasubd[4][2][nopt][ndet];
   TLegend* lasubd[4][2][nopt][ndet];
   int vasubd[4][2][nopt][ndet];
   for(int k=0;k<ndet;k++){
     for(int j=0;j<nopt;j++){
       for(int i=0;i<4;i++){
	 casubd[i][j][k] = new TCanvas(Form("casubd%d%d%d",i,j,k),Form("casubd%d%d%d",i,j,k),700,500);
	 casubd[i][j][k]->Divide(2,2);
	 casubd[i][j][k]->cd(1);
	 haresx[(i+3)%5][j][k]->Draw();
	 haresxd[(i+3)%5][j][k]->SetLineColor(6);
	 haresxd[(i+3)%5][j][k]->Draw("same");
	 casubd[i][j][k]->cd(2);
	 haresy[(i+3)%5][j][k]->Draw();
	 haresyd[(i+3)%5][j][k]->SetLineColor(6);
	 haresyd[(i+3)%5][j][k]->Draw("same");
	 casubd[i][j][k]->cd(3);
	 hasubd[i][0][j][k] = (TH1F*)haresx[(i+3)%5][j][k]->Clone();
	 hasubd[i][0][j][k]->SetName(Form("haresxcp%d%d%d",(i+3)%5,j,k));
	 hasubd[i][0][j][k]->Add(haresxd[(i+3)%5][j][k],-1);
	 hasubd[i][0][j][k]->Draw();
	 fasubd[i][0][j][k] = new TF1(Form("fasubd%dx%d%d",i,j,k),"gaus",-800,800);
	 hasubd[i][0][j][k]->Fit(Form("fasubd%dx%d%d",i,j,k),"","",-fitregion[k],fitregion[k]);
	 lasubd[i][0][j][k] = new TLegend(0.1,0.75,0.4,0.9);
	 vasubd[i][0][j][k] = hasubd[i][0][j][k]->Integral(roughbin[k]/2-hw_intx[k]*roughbin[k]/1600,roughbin[k]/2+hw_inty[k]*roughbin[k]/1600);
	 lasubd[i][0][j][k]->AddEntry(hasubd[i][0][j][k],Form("%d<Integral<%d, %d",-hw_intx[k],hw_intx[k],vasubd[i][0][j][k]),"l");
	 lasubd[i][0][j][k]->AddEntry((TObject*)0,Form("n_track: %d",ntrack[(i+3)%5][j][k]),"");
	 lasubd[i][0][j][k]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasubd[i][0][j][k]/(double)ntrack[(i+3)%5][j][k]),"");
	 lasubd[i][0][j][k]->Draw();
	 casubd[i][j][k]->cd(4);
	 hasubd[i][1][j][k] = (TH1F*)haresy[(i+3)%5][j][k]->Clone();
	 hasubd[i][1][j][k]->SetName(Form("haresycp%d%d%d",(i+3)%5,j,k));
	 hasubd[i][1][j][k]->Add(haresyd[(i+3)%5][j][k],-1);
	 hasubd[i][1][j][k]->Draw();
	 fasubd[i][1][j][k] = new TF1(Form("fasubd%dy%d%d",i,j,k),"gaus",-800,800);
	 hasubd[i][1][j][k]->Fit(Form("fasubd%dy%d%d",i,j,k),"","",-fitregion[k],fitregion[k]);
	 lasubd[i][1][j][k] = new TLegend(0.1,0.75,0.4,0.9);
	 vasubd[i][1][j][k] = hasubd[i][1][j][k]->Integral(roughbin[k]/2-hw_intx[k]*roughbin[k]/1600,roughbin[k]/2+hw_inty[k]*roughbin[k]/1600);
	 lasubd[i][1][j][k]->AddEntry(hasubd[i][1][j][k],Form("%d<Integral<%d, %d",-hw_intx[k],hw_intx[k],vasubd[i][1][j][k]),"l");
	 lasubd[i][1][j][k]->AddEntry((TObject*)0,Form("n_track: %d",ntrack[(i+3)%5][j][k]),"");
	 lasubd[i][1][j][k]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasubd[i][1][j][k]/(double)ntrack[(i+3)%5][j][k]),"");
	 lasubd[i][1][j][k]->Draw();
       }
     }
   }
   TCanvas* casub2d[4][ndet];
   TH2F* hasub2d[4][ndet];
   TH2F* hasub2dcopy[4][ndet];
   TLegend* lasub2d[3][4][ndet];
   int vasub2d[3][4][ndet];
   double voriginx[4][ndet]={0.};
   double voriginy[4][ndet]={0.};
   double vsigmax[4][ndet]={0.};
   double vsigmay[4][ndet]={0.};
   int ntracks[4][ndet]={0};
   double missurv[4][ndet]={0.};
   double effxtrkp[4][ndet]={0.};
   for(int k=0;k<ndet;k++){
     for(int i=0;i<4;i++){
       casub2d[i][k] = new TCanvas(Form("casub2d%d%d",i,k),Form("casub2d%d%d",i,k),700,700);
       casub2d[i][k]->Divide(2,2);
       voriginx[i][k] = fasubd[i][0][1][k]->GetParameter(1);
       voriginy[i][k] = fasubd[i][1][1][k]->GetParameter(1);
       vsigmax[i][k] = fasubd[i][0][1][k]->GetParameter(2)*track_select_sigma;
       vsigmay[i][k] = fasubd[i][1][1][k]->GetParameter(2)*track_select_sigma;
       if(k==0){voriginx[i][k]=hbd_voriginx[i];voriginy[i][k]=hbd_voriginy[i];vsigmax[i][k]=hbd_vsigmax[i];vsigmay[i][k]=hbd_vsigmay[i];}
       if(k==1||k==3){voriginx[i][k]=0;voriginy[i][k]=0;vsigmax[i][k]=hw_intx[1];vsigmay[i][k]=hw_inty[1];}
       if(k==2||k==4){voriginy[i][k]=0;vsigmay[i][k]=hw_inty[1];}
       int n_track = hx[(i+3)%5][k]->GetEntries();
       ntracks[i][k] = n_track;
       casub2d[i][k]->cd(1);
       hares[(i+3)%5][k]->Draw("colz");
       lasub2d[0][i][k] = new TLegend(0.1,0.8,0.45,0.9);
       //vasub2d[0][i][k] = AnalyzerResidualHBD::Get2DHistIntegral(hares[(i+3)%5][k],vradius[i][k],voriginx[i][k],voriginy[i][k]);
       vasub2d[0][i][k] = AnalyzerResidualHBD::Get2DHistSquareIntegral(hares[(i+3)%5][k],voriginx[i][k],voriginy[i][k],vsigmax[i][k],vsigmay[i][k]);
       lasub2d[0][i][k]->AddEntry(hares[(i+3)%5][k],Form("Integral, %d",vasub2d[0][i][k]),"l");
       lasub2d[0][i][k]->AddEntry((TObject*)0,Form("int/ntrack: %1.3f",(double)vasub2d[0][i][k]/(double)n_track),"");
       lasub2d[0][i][k]->Draw();
       casub2d[i][k]->cd(2);
       haresd[(i+3)%5][k]->Draw("colz");
       lasub2d[1][i][k] = new TLegend(0.1,0.8,0.7,0.9);
       //vasub2d[1][i][k] = AnalyzerResidualHBD::Get2DHistIntegral(haresd[(i+3)%5][k],vradius[i][k],voriginx[i][k],voriginy[i][k]);
       vasub2d[1][i][k] = AnalyzerResidualHBD::Get2DHistSquareIntegral(haresd[(i+3)%5][k],voriginx[i][k],voriginy[i][k],vsigmax[i][k],vsigmay[i][k]);
       lasub2d[1][i][k]->AddEntry(haresd[(i+3)%5][k],Form("Integral, %d",vasub2d[1][i][k]),"l");
       lasub2d[1][i][k]->AddEntry((TObject*)0,Form("int/ntrack (mis-track survival): %1.3f",(double)vasub2d[1][i][k]/(double)n_track),"");
       lasub2d[1][i][k]->Draw();
       missurv[i][k] = (double)vasub2d[1][i][k]/(double)n_track;
       casub2d[i][k]->cd(3);
       hasub2d[i][k] = (TH2F*)hares[(i+3)%5][k]->Clone();
       hasub2d[i][k]->Add(haresd[(i+3)%5][k],-1);
       hasub2d[i][k]->Draw("colz");
       lasub2d[2][i][k] = new TLegend(0.1,0.75,0.6,0.9);
       hasub2dcopy[i][k] = (TH2F*)hasub2d[i][k]->Clone();
       //vasub2d[2][i][k] = AnalyzerResidualHBD::Get2DHistIntegral(hasub2d[i][k],vsigmax[i][k],hasub2dcopy[i][k],voriginx[i][k],voriginy[i][k]);
       vasub2d[2][i][k] = AnalyzerResidualHBD::Get2DHistSquareIntegral(hasub2d[i][k],hasub2dcopy[i][k],voriginx[i][k],voriginy[i][k],vsigmax[i][k],vsigmay[i][k]);
       lasub2d[2][i][k]->AddEntry(hasub2d[i][k],Form("Integral(sx:%dmm,sy:%dmm), %d",(int)vsigmax[i][k],(int)vsigmay[i][k],vasub2d[2][i][k]),"l");
       lasub2d[2][i][k]->AddEntry((TObject*)0,Form("n_track: %d",n_track),"");
       lasub2d[2][i][k]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasub2d[2][i][k]/(double)n_track),"");
       lasub2d[2][i][k]->Draw();
       effxtrkp[i][k] = (double)vasub2d[2][i][k]/(double)n_track;
       casub2d[i][k]->cd(4)->DrawFrame(-ex_2d[k],-ex_2d[k],ex_2d[k],ex_2d[k]);
       hasub2dcopy[i][k]->Draw("colz sames");
     }
   }


   // Efficiency Summary
   const int step = 10;
   double trkpforhbdrej[4]={0.};
   double trkpforlgrej[4]={0.};
   TGraphErrors* geffh[4];
   TGraphErrors* geffc[4];
   TGraphErrors* geffhb[4];
   TGraphErrors* geffcb[4];
   TGraphErrors* gtrkp[4];
   TGraphErrors* gtrkpb[4];
   TGraphErrors* gtrkp2[4];
   TCanvas *ceff = new TCanvas("ceff","ceff",700,500);
   TLegend* leff = new TLegend(0.1,0.1,0.5,0.5);
   ceff->Divide(2,2);
   for(int i=0;i<4;i++){
     double graphx[step]={0.};
     double veffh[step]={0.};
     double veffc[step]={0.};
     double veffhb[step]={0.};
     double veffcb[step]={0.};
     double vtrkp[step]={0.};
     double vtrkpb[step]={0.};
     double vtrkp2[step]={0.};
     double zero[step]={0.};
     double veffh_err[step]={0.};
     double veffc_err[step]={0.};
     double veffhb_err[step]={0.};
     double veffcb_err[step]={0.};
     double vtrkp_err[step]={0.};
     double vtrkpb_err[step]={0.};
     double vtrkp2_err[step]={0.};
     for(int st=0;st<step;st++){
       graphx[st] = effxtrkp[i][0] + st*(1.-effxtrkp[i][0])/((double)step-1.) ;
       veffh[st] = (double)vasub2d[2][i][1]/(double)vasub2d[2][i][0];
       // veffh[st] = (double)vasub2d[2][i][1]/(double)ntracks[i][1];
       veffh_err[st] = veffh[st]/sqrt((double)vasub2d[2][i][1]);
       veffc[st] = (double)vasub2d[2][i][2]/(double)vasub2d[2][i][0];
       // veffc[st] = (double)vasub2d[2][i][2]/(double)ntracks[i][1];
       veffc_err[st] = veffc[st]/sqrt((double)vasub2d[2][i][2]);
       vtrkp[st] = (double)vasub2d[2][i][0]/(double)ntracks[i][1];
       // vtrkp[st] = (double)vasub2d[2][i][0]/(double)ntrack[(i+3)%5][2][1];//220218tmp
       vtrkp_err[st] = vtrkp[st]/sqrt((double)vasub2d[2][i][0]);
       vtrkp2[st] = (double)vasub2d[2][i][3]/(double)ntrack[(i+3)%5][0][3];
       // vtrkp2[st] = (double)vasub2d[2][i][3]/(double)ntrack[(i+3)%5][2][3];//220216tmp
       vtrkp2_err[st] = vtrkp[st]/sqrt((double)vasub2d[2][i][3]);
       vtrkpb[st] = effxtrkp[i][0]/graphx[st];
       veffhb[st] = effxtrkp[i][3]/vtrkpb[st];
       veffcb[st] = effxtrkp[i][4]/vtrkpb[st];
     }
     trkpforhbdrej[i] = vtrkp2[0];
     trkpforlgrej[i] = vtrkp[0];
     geffh[i] = new TGraphErrors(step,graphx,veffh,zero,veffh_err);
     geffc[i] = new TGraphErrors(step,graphx,veffc,zero,veffc_err);
     gtrkp[i] = new TGraphErrors(step,graphx,vtrkp,zero,vtrkp_err);
     gtrkpb[i] = new TGraphErrors(step,graphx,vtrkpb,zero,vtrkpb_err);
     gtrkp2[i] = new TGraphErrors(step,graphx,vtrkp2,zero,vtrkp2_err);
     geffhb[i] = new TGraphErrors(step,graphx,veffhb,zero,veffhb_err);
     geffcb[i] = new TGraphErrors(step,graphx,veffcb,zero,veffcb_err);
     ceff->cd(i+1)->SetGrid();
     gtrkp[i]->SetTitle(Form("Efficiency&TrackPurity_Module%d;HBDefficiency;",(i+3)%5+103));
     gtrkp[i]->SetMaximum(1.);
     gtrkp[i]->SetMinimum(0.);
     gtrkp[i]->GetXaxis()->SetLimits(0,1);
     gtrkp[i]->Draw("ALP");
     gtrkp2[i]->SetMarkerColor(3);
     gtrkp2[i]->SetLineColor(3);
     gtrkp2[i]->Draw("LP");
     geffh[i]->SetMarkerColor(2);
     geffh[i]->SetLineColor(2);
     geffh[i]->Draw("LP");
     geffc[i]->SetMarkerColor(4);
     geffc[i]->SetLineColor(4);
     geffc[i]->Draw("LP");
     geffhb[i]->SetMarkerColor(6);
     geffhb[i]->SetLineColor(6);
     geffhb[i]->Draw("LP");
     geffcb[i]->SetMarkerColor(7);
     geffcb[i]->SetLineColor(7);
     geffcb[i]->Draw("LP");
     gtrkpb[i]->SetMarkerColor(8);
     gtrkpb[i]->SetLineColor(8);
     gtrkpb[i]->Draw("LP");
     if(i==2){
       leff->AddEntry(gtrkp[2],"TrackPurity w/HBD","l");
       leff->AddEntry(gtrkpb[2],"TrackPurityBefore","l");
       leff->AddEntry(gtrkp2[2],"TrackPurity w/LG","l");
       leff->AddEntry(geffh[2],"LGHitEff byTrackw/HBD","l");
       leff->AddEntry(geffc[2],"LGClsEff byTrackw/HBD","l");
       leff->AddEntry(geffhb[2],"LGHitEff byTrackw/oHBD","l");
       leff->AddEntry(geffcb[2],"LGClsEff byTrackw/oHBD","l");
       leff->Draw();
     }
   }
   TCanvas *ceff2 = new TCanvas("ceff2","ceff2",700,500);
   ceff2->Divide(2,2);
   TLegend* leff2[4];
   for(int i=0;i<4;i++){
     ceff2->cd(i+1);
     leff2[i] = new TLegend(0.1,0.1,0.9,0.9);
     leff2[i]->AddEntry((TObject*)0,Form("Module%d",(i+3)%5+103),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_HBD(Hit): %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1],vasub2d[2][i][3],(double)vasub2d[2][i][1]/(double)vasub2d[2][i][3],sqrt((double)vasub2d[2][i][1])/(double)vasub2d[2][i][3]),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_HBD(Cls): %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][2],vasub2d[2][i][4],(double)vasub2d[2][i][2]/(double)vasub2d[2][i][4],sqrt((double)vasub2d[2][i][2])/(double)vasub2d[2][i][4]),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_LGHit: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1],vasub2d[2][i][0],(double)vasub2d[2][i][1]/(double)vasub2d[2][i][0],sqrt((double)vasub2d[2][i][1])/(double)vasub2d[2][i][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_LGCls: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][2],vasub2d[2][i][0],(double)vasub2d[2][i][2]/(double)vasub2d[2][i][0],sqrt((double)vasub2d[2][i][2])/(double)vasub2d[2][i][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurity w/HBD: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][0],ntracks[i][1],(double)vasub2d[2][i][0]/(double)ntracks[i][1],sqrt((double)vasub2d[2][i][0])/(double)ntracks[i][1]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurityB: %d/%dx1./E_HBD=%1.3f +/- %1.3f",vasub2d[2][i][0],ntracks[i][0],(double)vasub2d[2][i][0]/(double)ntracks[i][0]/(double)vasub2d[2][i][1]*(double)vasub2d[2][i][3],sqrt((double)vasub2d[2][i][0])/(double)ntracks[i][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurity w/LG: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][3],ntrack[(i+3)%5][0][3],(double)vasub2d[2][i][3]/(double)ntrack[(i+3)%5][0][3],sqrt((double)vasub2d[2][i][3])/(double)ntrack[(i+3)%5][0][3]),"");
     leff2[i]->Draw();
   }


   TCanvas* chbdadc = new TCanvas("chbdadc","chbdadc",700,500);
   chbdadc->Divide(2,2);
   int vhbdrejint[4];
   int vhbdrejintd[4];
   int vhbdrejxmin[4];
   int vhbdrejxmax[4];
   TLegend* lhbdrej[4];
   for(int i=0;i<4;i++){
     chbdadc->cd(i+1);
     hbdadc[(i+3)%5]->Draw();
     hbdadcd[(i+3)%5]->SetLineColor(6);
     hbdadcd[(i+3)%5]->Draw("sames");
     chbdadc->cd(i+1)->Update();
     TPaveStats *st1 = (TPaveStats*)hbdadcd[(i+3)%5]->FindObject("stats");
     st1->SetLineColor(6);
     st1->SetX1NDC(0.58);
     st1->SetX2NDC(0.78);
     st1->SetY1NDC(0.495);
     st1->SetY2NDC(0.935);
     chbdadc->cd(i+1)->Modified();
     vhbdrejxmin[i] = hbdadc[(i+3)%5]->FindBin(7.);
     vhbdrejxmax[i] = hbdadc[(i+3)%5]->GetNbinsX();
     vhbdrejint[i] = hbdadc[(i+3)%5]->Integral(vhbdrejxmin[i],vhbdrejxmax[i]+1);
     vhbdrejintd[i] = hbdadcd[(i+3)%5]->Integral(vhbdrejxmin[i],vhbdrejxmax[i]+1);
     lhbdrej[i] = new TLegend(0.4,0.35,0.9,0.5);
     int n_track = hbdadc[(i+3)%5]->GetEntries();
     double hbdrej = (double)vhbdrejint[i]/(double)n_track/trkpforhbdrej[i];
     lhbdrej[i]->AddEntry((TObject*)0,Form("Simple Eff: %d/%d/%1.2f=%1.3f +/- %1.3f",vhbdrejint[i],n_track,trkpforhbdrej[i],hbdrej,hbdrej/sqrt((double)vhbdrejint[i])),"");
     lhbdrej[i]->AddEntry((TObject*)0,Form("Strict Efficiency: %1.3f",((double)vhbdrejint[i]-(double)vhbdrejintd[i]*(1.-trkpforhbdrej[i]))/((double)n_track*trkpforhbdrej[i])),"");
     lhbdrej[i]->Draw();
   }
   TCanvas* chbdadc2 = new TCanvas("chbdadc2","chbdadc2",700,500);
   chbdadc2->Divide(2,2);
   TH1F* hbdrejsub[4];
   TLegend* lhbdrej2[4];
   for(int i=0;i<4;i++){
     chbdadc2->cd(i+1);
     hbdrejsub[i] = (TH1F*)hbdadc[(i+3)%5]->Clone();
     hbdrejsub[i]->SetName(Form("hbdrejsub%d",(i+3)%5+103));
     hbdrejsub[i]->Add(hbdadcd[(i+3)%5],-(1.-trkpforhbdrej[i]));
     std::cout<<hbdadc[(i+3)%5]->GetEntries()<<" "<<hbdadcd[(i+3)%5]->GetEntries()<<" "<<trkpforhbdrej[i]<<" "<<(double)hbdadc[(i+3)%5]->GetEntries()-((double)hbdadcd[(i+3)%5]->GetEntries()*(1.-trkpforhbdrej[i]))<<std::endl;
     hbdrejsub[i]->Draw();
     lhbdrej2[i] = new TLegend(0.4,0.35,0.9,0.5);
     int total = hbdrejsub[i]->GetEntries();
     int integral = hbdrejsub[i]->Integral(vhbdrejxmin[i],vhbdrejxmax[i]+1);
     lhbdrej2[i]->AddEntry((TObject*)0,Form("Efficiency: %d/%d=%1.3f +/- %1.3f",integral,total,(double)integral/(double)total,sqrt((double)integral)/(double)total),"");
     lhbdrej2[i]->Draw();
   }
   TCanvas* clgadc = new TCanvas("clgadc","clgadc",700,500);
   clgadc->Divide(2,2);
   int vlgrejint[4];
   int vlgrejintd[4];
   int vlgrejxmin[4];
   int vlgrejxmax[4];
   TLegend* llgrej[4];
   for(int i=0;i<4;i++){
     clgadc->cd(i+1);
     lgadc[(i+3)%5]->Draw();
     lgadcd[(i+3)%5]->SetLineColor(6);
     lgadcd[(i+3)%5]->Draw("sames");
     clgadc->cd(i+1)->Update();
     TPaveStats *st1 = (TPaveStats*)lgadcd[(i+3)%5]->FindObject("stats");
     st1->SetLineColor(6);
     st1->SetX1NDC(0.58);
     st1->SetX2NDC(0.78);
     st1->SetY1NDC(0.495);
     st1->SetY2NDC(0.935);
     clgadc->cd(i+1)->Modified();
     vlgrejxmin[i] = lgadc[(i+3)%5]->FindBin(98.);
     vlgrejxmax[i] = lgadc[(i+3)%5]->GetNbinsX();
     vlgrejint[i] = lgadc[(i+3)%5]->Integral(vlgrejxmin[i],vlgrejxmax[i]+1);
     vlgrejintd[i] = lgadcd[(i+3)%5]->Integral(vlgrejxmin[i],vlgrejxmax[i]+1);
     llgrej[i] = new TLegend(0.4,0.35,0.9,0.5);
     int n_track = lgadc[(i+3)%5]->GetEntries();
     double lgrej = (double)vlgrejint[i]/(double)n_track/trkpforlgrej[i];
     llgrej[i]->AddEntry((TObject*)0,Form("Simple Eff: %d/%d/%1.2f=%1.3f +/- %1.3f",vlgrejint[i],n_track,trkpforlgrej[i],lgrej,lgrej/sqrt((double)vlgrejint[i])),"");
     llgrej[i]->AddEntry((TObject*)0,Form("Strict Efficiency: %1.3f",((double)vlgrejint[i]-(double)vlgrejintd[i]*(1.-trkpforlgrej[i]))/((double)n_track*trkpforlgrej[i])),"");
     llgrej[i]->Draw();
   }
   TCanvas* clgadc2 = new TCanvas("clgadc2","clgadc2",700,500);
   clgadc2->Divide(2,2);
   TH1F* lgrejsub[4];
   TLegend* llgrej2[4];
   for(int i=0;i<4;i++){
     clgadc2->cd(i+1);
     lgrejsub[i] = (TH1F*)lgadc[(i+3)%5]->Clone();
     lgrejsub[i]->SetName(Form("lgrejsub%d",(i+3)%5+103));
     lgrejsub[i]->Add(lgadcd[(i+3)%5],-(1.-trkpforlgrej[i]));
     lgrejsub[i]->Draw();
     llgrej2[i] = new TLegend(0.4,0.35,0.9,0.5);
     int total = lgrejsub[i]->GetEntries();
     int integral = lgrejsub[i]->Integral(vlgrejxmin[i],vlgrejxmax[i]+1);
     llgrej2[i]->AddEntry((TObject*)0,Form("Efficiency: %d/%d=%1.3f +/- %1.3f",integral,total,(double)integral/(double)total,sqrt((double)integral)/(double)total),"");
     llgrej2[i]->Draw();
   }
   TH1F* lgenerejsub = (TH1F*)lgadcene->Clone();
   lgenerejsub->SetName("lgenerejsub");
   lgenerejsub->Add(lgadcened,-(1.-trkpforlgrej[0]));
   TCanvas* clgtrkmom = new TCanvas("clgtrkmom","clgtrkmom",700,500);
   clgtrkmom->Divide(2,2);
   for(int i=0;i<4;i++){
     clgtrkmom->cd(i+1);
     lgtrkmom[(i+3)%5]->Draw();
   }
   // TCanvas* clgtrk1eff = new TCanvas("clgtrk1eff","clgtrk1eff",700,500);
   // clgtrk1eff->Divide(2,2);
   // for(int i=0;i<4;i++){
   //   clgtrk1eff->cd(i+1);
   //   lgtrk1eff[(i+3)%5]->Draw();
   // }
   // TCanvas* clgtrk2eff = new TCanvas("clgtrk2eff","clgtrk2eff",700,500);
   // clgtrk2eff->Divide(2,2);
   // for(int i=0;i<4;i++){
   //   clgtrk2eff->cd(i+1);
   //   lgtrk2eff[(i+3)%5]->Draw();
   // }

   TCanvas* clghitsum = new TCanvas("clghitsum","clghitsum",700,500);
   clghitsum->Divide(2,2);
   for(int i=0;i<4;i++){
     clghitsum->cd(i+1);
     hlghitsum[(i+3)%5]->Draw("colz");
   }
   TCanvas* clghitsumd = new TCanvas("clghitsumd","clghitsumd",700,500);
   clghitsumd->Divide(2,2);
   for(int i=0;i<4;i++){
     clghitsumd->cd(i+1);
     hlghitsumd[(i+3)%5]->Draw("colz");
   }
   TCanvas* clghitsumsub = new TCanvas("clghitsumsub","clghitsumsub",700,500);
   clghitsumsub->Divide(2,2);
   TH2F* hlghitsumsub[4];
   for(int i=0;i<4;i++){
     clghitsumsub->cd(i+1);
     hlghitsumsub[i] = (TH2F*)hlghitsum[(i+3)%5]->Clone();
     hlghitsumsub[i]->SetName(Form("hlghitsumsub%d",(i+3)%5+103));
     hlghitsumsub[i]->Add(hlghitsumd[(i+3)%5],-1);
     hlghitsumsub[i]->Draw("colz");
   }
   TCanvas* cedivp = new TCanvas("cedivp","cedivp",700,500);
   cedivp->Divide(2,2);
   for(int i=0;i<4;i++){
     cedivp->cd(i+1)->SetLogy();
     hedivp[(i+3)%5]->Draw();
     hedivpd[(i+3)%5]->SetLineColor(6);
     hedivpd[(i+3)%5]->Draw("sames");
     cedivp->cd(i+1)->Update();
     TPaveStats *st1 = (TPaveStats*)hedivpd[(i+3)%5]->FindObject("stats");
     st1->SetLineColor(6);
     st1->SetX1NDC(0.58);
     st1->SetX2NDC(0.78);
     st1->SetY1NDC(0.495);
     st1->SetY2NDC(0.935);
     cedivp->cd(i+1)->Modified();
   }
   TCanvas* cesubp = new TCanvas("cesubp","cesubp",700,500);
   cesubp->Divide(2,2);
   for(int i=0;i<4;i++){
     cesubp->cd(i+1);
     hesubp[(i+3)%5]->Draw();
     hesubpd[(i+3)%5]->SetLineColor(6);
     hesubpd[(i+3)%5]->Draw("sames");
   }
   TCanvas* ctimssdlg = new TCanvas("ctimssdlg","ctimssdlg",700,700);
   ctimssdlg->Divide(2,2);
   for(int i=0;i<4;i++){
     ctimssdlg->cd(i+1);
     htimssdlg[(i+3)%5]->Draw("colz");
   }
   TCanvas* ctimssdlg1d = new TCanvas("ctimssdlg1d","ctimssdlg1d",700,500);
   ctimssdlg1d->Divide(2,2);
   for(int i=0;i<4;i++){
     ctimssdlg1d->cd(i+1);
     htimssdlg1d[(i+3)%5]->Draw();
   }
   TCanvas* cnlghitwt = new TCanvas("cnlghitwt","cnlghitwt",700,500);
   cnlghitwt->Divide(2,2);
   for(int i=0;i<4;i++){
     cnlghitwt->cd(i+1);
     hnlghitwt[(i+3)%5]->Draw();
   }
   TCanvas* clgblk = new TCanvas("clgblk","clgblk",700,500);
   clgblk->Divide(2,2);
   for(int i=0;i<4;i++){
     clgblk->cd(i+1);
     hlgblk[(i+3)%5]->Draw();
   }
   TCanvas* clgcor[4];
   for(int i=0;i<4;i++){
     clgcor[i] = new TCanvas(Form("clgcor%d",i),Form("clgcor%d",i),700,500);
     clgcor[i]->Divide(7,6);
     for(int j=0;j<42;j++){
       clgcor[i]->cd(42-j);
       int tmpch = (j/7)*10 + j%7;
       hlgcor[(i+3)%5][tmpch]->Draw("colz");
     }
   }
   TCanvas* chbdresxmix = new TCanvas("chbdresxmix","chbdresxmix",700,500);
   chbdresxmix->Divide(2,2);
   for(int i=0;i<4;i++){
     chbdresxmix->cd(i+1);
     int norma = haresx[(i+3)%5][1][0]->Integral(haresx[(i+3)%5][1][0]->FindBin(-600.),haresx[(i+3)%5][1][0]->FindBin(-100.))+haresx[(i+3)%5][1][0]->Integral(haresx[(i+3)%5][1][0]->FindBin(100.),haresx[(i+3)%5][1][0]->FindBin(600.));
     int normb = hbdresxmix[(i+3)%5]->Integral(hbdresxmix[(i+3)%5]->FindBin(-600.),hbdresxmix[(i+3)%5]->FindBin(-100.))+hbdresxmix[(i+3)%5]->Integral(hbdresxmix[(i+3)%5]->FindBin(100.),hbdresxmix[(i+3)%5]->FindBin(600.));
     haresx[(i+3)%5][1][0]->Draw("hist");
     hbdresxmix[(i+3)%5]->SetLineColor(2);
     hbdresxmix[(i+3)%5]->Scale((double)norma/(double)normb);
     hbdresxmix[(i+3)%5]->Draw("hist&&sames");
   }
   TCanvas* chbdresymix = new TCanvas("chbdresymix","chbdresymix",700,500);
   chbdresymix->Divide(2,2);
   for(int i=0;i<4;i++){
     chbdresymix->cd(i+1);
     int norma = haresy[(i+3)%5][1][0]->Integral(haresy[(i+3)%5][1][0]->FindBin(-600.),haresy[(i+3)%5][1][0]->FindBin(-100.))+haresy[(i+3)%5][1][0]->Integral(haresy[(i+3)%5][1][0]->FindBin(100.),haresy[(i+3)%5][1][0]->FindBin(600.));
     int normb = hbdresymix[(i+3)%5]->Integral(hbdresymix[(i+3)%5]->FindBin(-600.),hbdresymix[(i+3)%5]->FindBin(-100.))+hbdresymix[(i+3)%5]->Integral(hbdresymix[(i+3)%5]->FindBin(100.),hbdresymix[(i+3)%5]->FindBin(600.));
     haresy[(i+3)%5][1][0]->Draw("hist");
     hbdresymix[(i+3)%5]->SetLineColor(2);
     hbdresymix[(i+3)%5]->Scale((double)norma/(double)normb);
     hbdresymix[(i+3)%5]->Draw("hist&&sames");
   }
   TCanvas* clgresxmix = new TCanvas("clgresxmix","clgresxmix",700,500);
   clgresxmix->Divide(2,2);
   for(int i=0;i<4;i++){
     clgresxmix->cd(i+1);
     int norma = haresx[(i+3)%5][1][1]->Integral(haresx[(i+3)%5][1][1]->FindBin(-600.),haresx[(i+3)%5][1][1]->FindBin(-100.))+haresx[(i+3)%5][1][1]->Integral(haresx[(i+3)%5][1][1]->FindBin(100.),haresx[(i+3)%5][1][1]->FindBin(600.));
     int normb = lgresxmix[(i+3)%5]->Integral(lgresxmix[(i+3)%5]->FindBin(-600.),lgresxmix[(i+3)%5]->FindBin(-100.))+lgresxmix[(i+3)%5]->Integral(lgresxmix[(i+3)%5]->FindBin(100.),lgresxmix[(i+3)%5]->FindBin(600.));
     haresx[(i+3)%5][1][1]->Draw("hist");
     lgresxmix[(i+3)%5]->SetLineColor(2);
     lgresxmix[(i+3)%5]->Scale((double)norma/(double)normb);
     lgresxmix[(i+3)%5]->Draw("hist&&sames");
   }
   TCanvas* clgresymix = new TCanvas("clgresymix","clgresymix",700,500);
   clgresymix->Divide(2,2);
   for(int i=0;i<4;i++){
     clgresymix->cd(i+1);
     int norma = haresy[(i+3)%5][1][1]->Integral(haresy[(i+3)%5][1][1]->FindBin(-600.),haresy[(i+3)%5][1][1]->FindBin(-100.))+haresy[(i+3)%5][1][1]->Integral(haresy[(i+3)%5][1][1]->FindBin(100.),haresy[(i+3)%5][1][1]->FindBin(600.));
     int normb = lgresymix[(i+3)%5]->Integral(lgresymix[(i+3)%5]->FindBin(-600.),lgresymix[(i+3)%5]->FindBin(-100.))+lgresymix[(i+3)%5]->Integral(lgresymix[(i+3)%5]->FindBin(100.),lgresymix[(i+3)%5]->FindBin(600.));
     haresy[(i+3)%5][1][1]->Draw("hist");
     lgresymix[(i+3)%5]->SetLineColor(2);
     lgresymix[(i+3)%5]->Scale((double)norma/(double)normb);
     lgresymix[(i+3)%5]->Draw("hist&&sames");
   }
   TCanvas* clgadcmix = new TCanvas("clgadcmix","clgadcmix",700,500);
   clgadcmix->Divide(2,2);
   for(int i=0;i<4;i++){
     clgadcmix->cd(i+1);
     int norma = hedivp[(i+3)%5]->Integral();
     int normb = lgadcmix[(i+3)%5]->Integral();
     hedivp[(i+3)%5]->Draw("hist");
     lgadcmix[(i+3)%5]->SetLineColor(2);
     lgadcmix[(i+3)%5]->Scale((double)norma/(double)normb);
     lgadcmix[(i+3)%5]->Draw("hist&&sames");
   }



   TCanvas* cdef = new TCanvas("cdef","cdef",700,500);
   cdef->SaveAs(outfile+"[","pdf");
   ce->SaveAs(outfile,"pdf");
   ceff->SaveAs(outfile,"pdf");
   ceff2->SaveAs(outfile,"pdf");
   chbdresxmix->SaveAs(outfile,"pdf");
   chbdresymix->SaveAs(outfile,"pdf");
   clgresxmix->SaveAs(outfile,"pdf");
   clgresymix->SaveAs(outfile,"pdf");
   clgadcmix->SaveAs(outfile,"pdf");
   // chbdadc->SaveAs(outfile,"pdf");//pi
   // chbdadc2->SaveAs(outfile,"pdf");//pi
   // clgadc->SaveAs(outfile,"pdf");//pi
   // clgadc2->SaveAs(outfile,"pdf");//pi
   clgtrkmom->SaveAs(outfile,"pdf");
   clgblk->SaveAs(outfile,"pdf");
   // clgtrk1eff->SaveAs(outfile,"pdf");
   // clgtrk2eff->SaveAs(outfile,"pdf");
   clghitsum->SaveAs(outfile,"pdf");
   clghitsumd->SaveAs(outfile,"pdf");
   clghitsumsub->SaveAs(outfile,"pdf");
   cedivp->SaveAs(outfile,"pdf");
   cesubp->SaveAs(outfile,"pdf");
   for(int i=0;i<4;i++){
     clgcor[i]->SaveAs(outfile,"pdf");
   }
   // ctimssdlg->SaveAs(outfile,"pdf");
   // ctimssdlg1d->SaveAs(outfile,"pdf");
   cnlghitwt->SaveAs(outfile,"pdf");
   for(int i=0;i<2;i++){
     clgod[i]->SaveAs(outfile,"pdf");
   }
   // for(int i=0;i<4;i++){
   //   casubdt[i][0]->SaveAs(outfile,"pdf");
   // }
   for(int k=0;k<ndet;k++){
     for(int i=0;i<8;i++){
       c[i][k]->SaveAs(outfile,"pdf");
     }
     // for(int i=0;i<4;i++){
     //   csubd[i][k]->SaveAs(outfile,"pdf");
     // }
     for(int i=0;i<4;i++){
       for(int j=0;j<nopt;j++){
	 casubd[i][j][k]->SaveAs(outfile,"pdf");
       }
       casub2d[i][k]->SaveAs(outfile,"pdf");
     }
     for(int i=0;i<8;i++){
       for(int j=0;j<nsel;j++){
	 chbd[i][j][k]->SaveAs(outfile,"pdf");
       }
     }
     std::cout<<det[k]<<"end"<<std::endl;
   }
   cdef->SaveAs(outfile+"]","pdf");

   std::cout<<voriginx[0][0]<<std::endl;
   std::cout<<voriginy[0][0]<<std::endl;
   std::cout<<voriginx[1][0]<<std::endl;
   std::cout<<voriginy[1][0]<<std::endl;
   std::cout<<ntrack[0][0][0]<<" "<<ntrack[0][0][1]<<" "<<ntrack[0][0][2]<<" "<<ntrack[0][0][3]<<" "<<ntrack[0][0][4]<<std::endl;
   std::cout<<ntrack[1][0][0]<<" "<<ntrack[1][0][1]<<" "<<ntrack[1][0][2]<<" "<<ntrack[1][0][3]<<" "<<ntrack[1][0][4]<<std::endl;

   outtextfile.close();
   fouthist->Write();
   fouthist->Close();

   // TFile *foutrej = new TFile("rejection.root","recreate");
   // hbdadc[3]->Write();//106
   // lgadc[3]->Write();
   // hbdrejsub[0]->Write();//106
   // lgrejsub[0]->Write();
   // hasubd[0][0][1][0]->Write();
   // hasubd[0][1][1][0]->Write();
   // hasubd[0][0][1][1]->Write();
   // hasubd[0][1][1][1]->Write();
   // hasubd[0][0][1][2]->Write();
   // hasubd[0][1][1][2]->Write();
   // lgadcene->Write();
   // lgadcened->Write();
   // lgenerejsub->Write();
}

void AnalyzerTrackSelection::MkMixingHist(int runoption, int maxevent)
{

   if (fChain == 0) return;

   TFile *fouthist = new TFile("mixing.root","recreate");

   struct hitset{
     int mid;
     double lx;
     double ly;
     double adc;
     double tdc;
   };

   std::vector<hitset> hbdmixhits[5];
   std::vector<hitset> lgmixhits[5];
   int roughbin[5] = {800,100,100,100,100};//bin
   TH1F *hbdresxmix[5];
   TH1F *hbdresymix[5];
   TH1F *lgresxmix[5];
   TH1F *lgresymix[5];
   for(int i=0;i<5;i++){
     hbdresxmix[i] = new TH1F(Form("hbdresxmix%d",i),Form("hbd_resx_mix_mod%d",103+i),roughbin[0],-800,800);
     hbdresymix[i] = new TH1F(Form("hbdresymix%d",i),Form("hbd_resy_mix_mod%d",103+i),roughbin[0],-800,800);
     lgresxmix[i] = new TH1F(Form("lgresxmix%d",i),Form("lg_resx_mix_mod%d",103+i),roughbin[1],-800,800);
     lgresymix[i] = new TH1F(Form("lgresymix%d",i),Form("lg_resy_mix_mod%d",103+i),roughbin[1],-800,800);
   }

   Long64_t n_entries = fChain->GetEntries();
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   int nevent=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
      if( maxevent!=-1&&nevent>maxevent ){break;}

      std::vector<int> goodtracks;
      if (SelectGoodTrack(ientry,goodtracks) < 0) continue;
      // if (Cut(ientry) < 0) continue;//220407

      bool alfill[5]={false};

      for(int itrack=0;itrack<n_tracks;itrack++){//track loop

      	if (CutOfTrack(ientry,itrack,goodtracks) < 0) continue;
      	// if (CutOfTrack(ientry,itrack,runoption) < 0) continue;//220407

      	int mide = track_hbd_mid->at(itrack)-103;
      	if(alfill[mide]==false){//hit fill
      	  alfill[mide]=true;
      	  for(int ihbd=0;ihbd<track_hbd_multiplicity->at(itrack);ihbd++){
      	    hitset hbdhit;
      	    hbdhit.mid=track_hbd_mid->at(itrack);
      	    hbdhit.lx=track_hbd_allhit_resx->at(itrack).at(ihbd)+track_hbd_lx->at(itrack);
      	    hbdhit.ly=track_hbd_allhit_resy->at(itrack).at(ihbd)+track_hbd_ly->at(itrack);
      	    hbdhit.adc=track_hbd_allhit_adc->at(itrack).at(ihbd);
      	    hbdhit.tdc=track_hbd_allhit_ftime->at(itrack).at(ihbd);
      	    hbdmixhits[mide].push_back(hbdhit);
      	  }
      	  for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){
      	    hitset lghit;
      	    lghit.mid=track_lg_mid->at(itrack);
      	    lghit.lx=track_lg_allhit_resx->at(itrack).at(ilg)+track_lg_lx->at(itrack);
      	    lghit.ly=track_lg_allhit_resy->at(itrack).at(ilg)+track_lg_ly->at(itrack);
      	    lghit.adc=track_lg_allhit_adc->at(itrack).at(ilg);
      	    lghit.tdc=track_lg_allhit_ftime->at(itrack).at(ilg);
      	    lgmixhits[mide].push_back(lghit);
      	  }
      	}//hit fill
      	if(hbdmixhits[mide].size()==0||lgmixhits[mide].size()==0) continue;
      	for(int ihbd=0;ihbd<hbdmixhits[mide].size();ihbd++){
      	  hbdresxmix[mide]->Fill(hbdmixhits[mide].at(ihbd).lx-track_hbd_lx->at(itrack));
      	  hbdresymix[mide]->Fill(hbdmixhits[mide].at(ihbd).ly-track_hbd_ly->at(itrack));
      	}
      	for(int ilg=0;ilg<lgmixhits[mide].size();ilg++){
      	  lgresxmix[mide]->Fill(lgmixhits[mide].at(ilg).lx-track_lg_lx->at(itrack));
      	  lgresymix[mide]->Fill(lgmixhits[mide].at(ilg).ly-track_lg_ly->at(itrack));
      	}
	if(hbdmixhits[mide].size()>500){
	  hbdmixhits[mide].clear();
	}
	if(lgmixhits[mide].size()>500){
	  lgmixhits[mide].clear();
	}

      }//track loop

      nevent++;

   }//event loop

   // TString outfile = Form("%s",out_file_name);

   // gStyle->SetOptStat(11111111);
   // gStyle->SetOptFit(11111111);

   // TCanvas* cdef = new TCanvas("cdef","cdef",700,500);
   // cdef->SaveAs(outfile+"[","pdf");
   // cdef->SaveAs(outfile+"]","pdf");

   fouthist->Write();
   fouthist->Close();

}

void AnalyzerTrackSelection::DrawForLGEfficiency(int runoption, int maxevent, char* out_file_name)
{

   if (fChain == 0) return;

   TFile *fouthist = new TFile("hist.root","recreate");

   int searchx = 80;//lghit integral
   int searchy = 100;//lghit integral
   // int searchx = 50;//lghit integral
   // int searchy = 50;//lghit integral
   int mixevent = 50;
   double lgthr[4] = {50.,60.,70.,80.};
   double lgresthr = lgthr[3];
   double lgcon[4] = {240.,250.,260.,270.};
   double hbdthr = 7.;
   const int ndet=5;
   char det[ndet][20] = {"HBD","LGHit","LGCluster","LGHit_woHBDhit","LGCluster_woHBDhit"};
   int roughbin[ndet] = {200,50,50,50,200};//bin;
   // int roughbin[ndet] = {200,400,400,400,400};//bin
   int halfwidth[ndet] = {50,100,100,100,100};
   int hw_intx[ndet] = {25,80,80,80,80};
   int hw_inty[ndet] = {25,100,100,100,100};
   int ex_2d[ndet] = {50,200,200,200,200};
   double fitregion[ndet] = {30,100,100,100,100};
   int adcbinw[ndet] = {40,200,200,200,200};
   int adcbin[ndet] = {40,400,400,400,400};
   int tbinw[ndet] = {800,200,200,200,200};
   int tbin0[ndet] = {-150,0,0,0,0};
   int tbin[ndet] = {600,200,200,200,200};
   double ssdoffset = 51.;
   double ssdregion = 11.;
   // double ssdregion = 6.;
   
   TH1F *hnt[5];
   TH1F *hn[5][ndet];
   TH1F *hnd[5][ndet];
   const int nopt=4;
   char opt[nopt][25] = {"nocut","resy(x)cut","plus_charge","minus_charge"};
   TH1F *haresx[5][nopt][ndet];
   TH1F *haresy[5][nopt][ndet];
   TH1F *haresxd[5][nopt][ndet];
   TH1F *haresyd[5][nopt][ndet];
   int ntrack[5][9];
   for(int i=0;i<5;i++){
     for(int j=0;j<9;j++){
       ntrack[i][j]=0;
     }
   }
   TH2F *hares[5][ndet];
   TH2F *haresd[5][ndet];
   TH1F *ht[5][ndet];
   TH1F *htd[5][ndet];
   for(int k=0;k<ndet;k++){
     for(int i=0;i<5;i++){
       if(k==0){hnt[i] = new TH1F(Form("hnt%d",i),Form("ntracks_in_event_mod%d",103+i),20,0,20);}
       hn[i][k] = new TH1F(Form("hn%d%d",i,k),Form("%s_multiplicity_mod%d",det[k],103+i),50,0,50);
       hnd[i][k] = new TH1F(Form("hnd%d%d",i,k),Form("%s_multiplicity_dummy_mod%d",det[k],103+i),50,0,50);
       for(int j=0;j<nopt;j++){
	 haresx[i][j][k] = new TH1F(Form("haresx%d%d%d",i,j,k),Form("%s_allhit_residual_x_mod%d_%s",det[k],103+i,opt[j]),roughbin[k],-800,800);
	 haresy[i][j][k] = new TH1F(Form("haresy%d%d%d",i,j,k),Form("%s_allhit_residual_y_mod%d_%s",det[k],103+i,opt[j]),roughbin[k],-800,800);
	 haresxd[i][j][k] = new TH1F(Form("haresxd%d%d%d",i,j,k),Form("%s_allhit_residual_x_dummy_mod%d_%s",det[k],103+i,opt[j]),roughbin[k],-800,800);
	 haresyd[i][j][k] = new TH1F(Form("haresyd%d%d%d",i,j,k),Form("%s_allhit_residual_y_dummy_mod%d_%s",det[k],103+i,opt[j]),roughbin[k],-800,800);
       }
       hares[i][k] = new TH2F(Form("hares%d%d",i,k),Form("%s_allhit_residual_mod%d",det[k],103+i),roughbin[k],-800,800,roughbin[k],-800,800);
       haresd[i][k] = new TH2F(Form("haresd%d%d",i,k),Form("%s_allhit_residual_dummy_mod%d",det[k],103+i),roughbin[k],-800,800,roughbin[k],-800,800);
       ht[i][k] = new TH1F(Form("ht%d%d",i,k),Form("%s_fastest_time_mod%d",det[k],103+i),tbinw[k],tbin0[k],tbin[k]);
       htd[i][k] = new TH1F(Form("htd%d%d",i,k),Form("%s_fastest_time_dummy_mod%d",det[k],103+i),tbinw[k],tbin0[k],tbin[k]);
     }
   }
   TH1F* trkmom[5];
   TH2F* hevsp[5];
   TH2F* hevspd[5];
   TH1F* hedivp[5][4];
   TH1F* hedivpd[5][4];
   TH1F* hesubp[5][4];
   TH1F* hesubpd[5][4];
   TH1F* hnlghitwt[5];
   TH1F* hnlghitwtd[5];
   for(int i=0;i<5;i++){
     trkmom[i] = new TH1F(Form("trkmom%d",i),Form("Track_mom_w/HBDHit_mod%d",103+i),50,0,5);
     hevsp[i] = new TH2F(Form("hevsp%d",i),Form("LG_HitAdcSumVsMom_TrackAssociate_mod%d",103+i),100,0,5,100,0,500);
     hevspd[i] = new TH2F(Form("hevspd%d",i),Form("LG_HitAdcSumVsMom_dummy_TrackAssociate_mod%d",103+i),100,0,5,100,0,500);
     for(int j=0;j<4;j++){
       hedivp[i][j] = new TH1F(Form("hedivp%d%d",i,j),Form("LG_HitAdc/Mom_TrackAssociate_%1.0fmV_mod%d",lgthr[j],103+i),50,0,400);
       hedivpd[i][j] = new TH1F(Form("hedivpd%d%d",i,j),Form("LG_HitAdc/Mom_dummy_TrackAssociate_%1.0fmV_mod%d",lgthr[j],103+i),50,0,400);
       hesubp[i][j] = new TH1F(Form("hesubp%d%d",i,j),Form("LG_HitAdc-%1.0f*Mom_TrackAssociate_mod%d",lgcon[j],103+i),50,-200,200);
       hesubpd[i][j] = new TH1F(Form("hesubpd%d%d",i,j),Form("LG_HitAdc-%1.0f*Mom_dummy_TrackAssociate_mod%d",lgcon[j],103+i),50,-200,200);
     }
     hnlghitwt[i] = new TH1F(Form("hnlghitwt%d",i),Form("N_LGHits_TrackAssociate_mod%d",103+i),10,0,10);
     hnlghitwtd[i] = new TH1F(Form("hnlghitwtd%d",i),Form("N_LGHits_TrackAssociate_dummy_mod%d",103+i),10,0,10);
   }
   TH1F *testt = new TH1F("testt","testt",80,-40,40);
   TH1F *testa = new TH1F("testa","testa",500,0,500);

   //for mixing
   std::vector<std::vector<hitset>> hbdmixhits[5];
   std::vector<std::vector<hitset>> lgmixhits[5];

   Long64_t n_entries = fChain->GetEntries();
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   int nevent=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
      if( maxevent!=-1&&nevent>maxevent ){break;}

      // std::vector<int> goodtracks;
      // SelectGoodTrack(ientry,goodtracks);
      std::vector<trackset> tracksets(0);
      std::vector<trackset> forhbd(0);

      int ntrk[5]={0};
      bool alfill[2][5]={false};
      std::vector<hitset> hbdhits[5];
      std::vector<hitset> lghits[5];
      for(int itrack=0;itrack<n_tracks;itrack++){//track loop

	if (CutOfTrack(ientry,itrack) < 0) continue;
	// if (CutOfTrack(ientry,itrack,goodtracks) < 0) continue;

	//HBD Fill
	// int trkflag = IsGoodTrack(ientry,itrack,forhbd);// not associated HBDhit
	int trk_mid = track_hbd_mid->at(itrack);
	int mide = trk_mid-103;
	double resx_min = 10000.;
	double resy_min = 10000.;
	// if(trkflag>0){
	  int nhbdc = 0;
	  for(int ihbd=0;ihbd<track_hbd_multiplicity->at(itrack);ihbd++){// hbdcluster loop
	    double resx = track_hbd_allhit_resx->at(itrack).at(ihbd);
	    double resy = track_hbd_allhit_resy->at(itrack).at(ihbd);
	    if(track_hbd_allhit_adc->at(itrack).at(ihbd)<hbdthr) continue;
	    if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	      resx_min=resx;
	      resy_min=resy;
	    }
	    haresx[trk_mid-103][0][0]->Fill(resx);
	    haresy[trk_mid-103][0][0]->Fill(resy);
	    if(fabs(resy)<hw_intx[0]){
	      haresx[trk_mid-103][1][0]->Fill(resx);
	      if(rk_charge->at(itrack)==1){haresx[trk_mid-103][2][0]->Fill(resx);}
	      if(rk_charge->at(itrack)==-1){haresx[trk_mid-103][3][0]->Fill(resx);}
	    }
	    if(fabs(resx)<hw_intx[0]){
	      haresy[trk_mid-103][1][0]->Fill(resy);
	      if(rk_charge->at(itrack)==1){haresy[trk_mid-103][2][0]->Fill(resy);}
	      if(rk_charge->at(itrack)==-1){haresy[trk_mid-103][3][0]->Fill(resy);}
	    }
	    hares[trk_mid-103][0]->Fill(resx,resy);
	    if( resx*resx+resy*resy < hw_intx[0]*hw_intx[0] ){
	      ht[trk_mid-103][0]->Fill(track_hbd_allhit_ftime->at(itrack).at(ihbd));
	    }
	    nhbdc++;
	  }// hbdcluster loop
	  ntrack[trk_mid-103][0]++;
	  hn[trk_mid-103][0]->Fill(nhbdc);

	  if(hbdmixhits[mide].size()!=0){//calc mix
	    for(int ihbd=0;ihbd<hbdmixhits[mide].size();ihbd++){
	      int nhbdc_dum = 0;
	      for(int jhbd=0;jhbd<hbdmixhits[mide].at(ihbd).size();jhbd++){
		double tmpresx = hbdmixhits[mide].at(ihbd).at(jhbd).lx-track_hbd_lx->at(itrack);
		double tmpresy = hbdmixhits[mide].at(ihbd).at(jhbd).ly-track_hbd_ly->at(itrack);
		haresxd[mide][0][0]->Fill(tmpresx);
		haresyd[mide][0][0]->Fill(tmpresy);
		if(fabs(tmpresy)<hw_intx[0]){
		  haresxd[mide][1][0]->Fill(tmpresx);
		  if(rk_charge->at(itrack)==1){haresxd[mide][2][0]->Fill(tmpresx);}
		  if(rk_charge->at(itrack)==-1){haresxd[mide][3][0]->Fill(tmpresx);}
		}
		if(fabs(tmpresx)<hw_intx[0]){
		  haresyd[mide][1][0]->Fill(tmpresy);
		  if(rk_charge->at(itrack)==1){haresyd[mide][2][0]->Fill(tmpresy);}
		  if(rk_charge->at(itrack)==-1){haresyd[mide][3][0]->Fill(tmpresy);}
		}
		haresd[mide][0]->Fill(tmpresx,tmpresy);
		if( tmpresx*tmpresx+tmpresy*tmpresy < hw_intx[0]*hw_intx[0] ){
		  htd[mide][0]->Fill(hbdmixhits[mide].at(ihbd).at(jhbd).tdc);
		}
		nhbdc_dum++;
	      }
	      hnd[mide][0]->Fill(nhbdc_dum);
	    }
	  }//calc mix
	// }//trk type

	//HBD is Hit
	bool HBDhit=false;
	double rxt = resx_min-hbd_voriginx[(trk_mid-103+2)%5];
	double ryt = resy_min-hbd_voriginy[(trk_mid-103+2)%5];
	if( fabs(rxt)<hbd_vsigmax[(trk_mid-103+2)%5] && fabs(ryt)<hbd_vsigmay[(trk_mid-103+2)%5] ){
	  if( IsGoodTrack(ientry,itrack,tracksets)>0 ){// remove tracks w/ duplicated hits
	    HBDhit=true;
	  }
	}

	//LG Fill
	trk_mid = track_lg_mid->at(itrack);
	for(int trktype=0;trktype<2;trktype++){
	  if(trktype==0&&(!HBDhit||trk_mid<103||trk_mid>107)){continue;}
	  if(trktype==1&&(trk_mid<103||trk_mid>107)){continue;}
	  // if(trktype==1&&(trkflag<0||trk_mid<103||trk_mid>107)){continue;}
	  double resx_min = -10000.;
	  double resy_min = -10000.;
	  int nlgh=0;
	  std::vector<hitset> lgnear;
	  double adcsum = 0;
	  for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){//lghit fore
	    double resx = track_lg_allhit_resx->at(itrack).at(ilg);
	    double resy = track_lg_allhit_resy->at(itrack).at(ilg);
	    double tmpadc = track_lg_allhit_adc->at(itrack).at(ilg);
	    double tmptdc = track_lg_allhit_ftime->at(itrack).at(ilg);
	    if(track_lg_allhit_adc->at(itrack).at(ilg)<lgresthr||tmptdc<(ssdoffset-ssdregion)+track_ssd_t->at(itrack)||tmptdc>(ssdoffset+ssdregion)+track_ssd_t->at(itrack)) continue;//220418
	    if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	      resx_min=resx;
	      resy_min=resy;
	    }
	    haresx[trk_mid-103][0][1+trktype*2]->Fill(resx);
	    haresy[trk_mid-103][0][1+trktype*2]->Fill(resy);
	    if(fabs(resy)<hw_inty[1+trktype*2]){
	      haresx[trk_mid-103][1][1+trktype*2]->Fill(resx);
	      if(rk_charge->at(itrack)==1){haresx[trk_mid-103][2][1+trktype*2]->Fill(resx);}
	      if(rk_charge->at(itrack)==-1){haresx[trk_mid-103][3][1+trktype*2]->Fill(resx);}
	    }
	    if(fabs(resx)<hw_intx[1+trktype*2]){
	      haresy[trk_mid-103][1][1+trktype*2]->Fill(resy);
	      if(rk_charge->at(itrack)==1){haresy[trk_mid-103][2][1+trktype*2]->Fill(resy);}
	      if(rk_charge->at(itrack)==-1){haresy[trk_mid-103][3][1+trktype*2]->Fill(resy);}
	    }
	    if(fabs(resx)<hw_intx[1+trktype*2]&&fabs(resy)<hw_inty[1+trktype*2]){
	      ht[trk_mid-103][1+trktype*2]->Fill(track_lg_allhit_ftime->at(itrack).at(ilg));
	    }
	    hares[trk_mid-103][1+trktype*2]->Fill(resx,resy);
	    if( trktype==0 && fabs(resx)<searchx && fabs(resy)<searchy ){
	      testt->Fill(tmptdc-track_ssd_t->at(itrack)-ssdoffset);
	      testa->Fill(tmpadc);
	      hitset tmphit;
	      tmphit.adc = tmpadc;
	      tmphit.tdc = tmptdc;
	      lgnear.push_back(tmphit);
	    }
	    nlgh++;
	  }//lghit fore
	  hn[trk_mid-103][1+trktype*2]->Fill(nlgh);
	  if(trktype==0){
	    ntrack[trk_mid-103][1]++;//track_after_hbd
	    ntrack[trk_mid-103][2]++;//track_after_hbd(clutser)
	    trkmom[trk_mid-103]->Fill(track_mom->at(itrack));
	    hnlghitwt[trk_mid-103]->Fill(lgnear.size());
	    if(lgnear.size()==1){adcsum=lgnear.at(0).adc;}
	    if(lgnear.size()>1){adcsum=CalcADCNearHit(lgnear,track_ssd_t->at(itrack));}
	    hevsp[trk_mid-103]->Fill(track_mom->at(itrack),adcsum);
	    for(int j=0;j<4;j++){
	      if(adcsum>lgthr[j]){hedivp[trk_mid-103][j]->Fill(adcsum/track_mom->at(itrack));}
	      if(adcsum>lgresthr){hesubp[trk_mid-103][j]->Fill(adcsum-lgcon[j]*track_mom->at(itrack));}
	    }
	    if(fabs(resx_min)<hw_intx[1]&&fabs(resy_min)<hw_inty[1]){
	      ntrack[trk_mid-103][7]++;//track_after_hbdlg
	      ntrack[trk_mid-103][8]++;//track_after_hbdlg
	    }
	  }
	  if(trktype==1){
	    ntrack[trk_mid-103][3]++;//track_before_lg
	    ntrack[trk_mid-103][4]++;//track_before_lg
	    if(fabs(resx_min)<hw_intx[1]&&fabs(resy_min)<hw_inty[1]){
	      ntrack[trk_mid-103][5]++;//track_after_lg
	      ntrack[trk_mid-103][6]++;//track_after_lg
	      for(int ihbd=0;ihbd<track_hbd_multiplicity->at(itrack);ihbd++){// hbdcluster loop
	      	double resx = track_hbd_allhit_resx->at(itrack).at(ihbd);
	      	double resy = track_hbd_allhit_resy->at(itrack).at(ihbd);
	      	haresx[trk_mid-103][0][4]->Fill(resx);
	      	haresy[trk_mid-103][0][4]->Fill(resy);
	      	if(fabs(resy)<hw_intx[0]){
	      	  haresx[trk_mid-103][1][4]->Fill(resx);
	      	}
	      	if(fabs(resx)<hw_intx[0]){
	      	  haresy[trk_mid-103][1][4]->Fill(resy);
	      	}
	      }// hbdcluster loop
	    }
	  }

	  if(lgmixhits[mide].size()!=0){//calc mix
	    for(int ilg=0;ilg<lgmixhits[mide].size();ilg++){//lghit loop
	      std::vector<hitset> lgneard;
	      double adcsumd = 0;
	      int nlgh_dum = 0;
	      for(int jlg=0;jlg<lgmixhits[mide].at(ilg).size();jlg++){
		double tmpresx = lgmixhits[mide].at(ilg).at(jlg).lx-track_lg_lx->at(itrack);
		double tmpresy = lgmixhits[mide].at(ilg).at(jlg).ly-track_lg_ly->at(itrack);
		double tmpt = lgmixhits[mide].at(ilg).at(jlg).tdc;
		double tmpa = lgmixhits[mide].at(ilg).at(jlg).adc;
		haresxd[mide][0][1+trktype*2]->Fill(tmpresx);
		haresyd[mide][0][1+trktype*2]->Fill(tmpresy);
		if(fabs(tmpresy)<hw_inty[1+trktype*2]){
		  haresxd[mide][1][1+trktype*2]->Fill(tmpresx);
		  if(rk_charge->at(itrack)==1){haresxd[mide][2][1+trktype*2]->Fill(tmpresx);}
		  if(rk_charge->at(itrack)==-1){haresxd[mide][3][1+trktype*2]->Fill(tmpresx);}
		}
		if(fabs(tmpresx)<hw_intx[1+trktype*2]){
		  haresyd[mide][1][1+trktype*2]->Fill(tmpresy);
		  if(rk_charge->at(itrack)==1){haresyd[mide][2][1+trktype*2]->Fill(tmpresy);}
		  if(rk_charge->at(itrack)==-1){haresyd[mide][3][1+trktype*2]->Fill(tmpresy);}
		  if(fabs(tmpresy)<hw_inty[1+trktype*2]){
		    htd[mide][1+trktype*2]->Fill(tmpt);
		  }
		}
		haresd[mide][1+trktype*2]->Fill(tmpresx,tmpresy);
		if( trktype==0 && fabs(tmpresx)<searchx && fabs(tmpresy)<searchy ){
		  hitset tmphit;
		  tmphit.adc = tmpa;
		  tmphit.tdc = tmpt;
		  lgneard.push_back(tmphit);
		}
		nlgh_dum++;
	      }
	      hnd[mide][1+trktype*2]->Fill(nlgh_dum);
	      if(trktype==0){
		hnlghitwtd[trk_mid-103]->Fill(lgneard.size());
		if(lgneard.size()==1){adcsumd=lgneard.at(0).adc;}
		if(lgneard.size()>1){adcsumd=CalcADCNearHit(lgneard,track_ssd_t->at(itrack));}
		hevspd[mide]->Fill(track_mom->at(itrack),adcsumd);
		for(int j=0;j<4;j++){
		  if(adcsumd>lgthr[j]){hedivpd[mide][j]->Fill(adcsumd/track_mom->at(itrack));}
		  if(adcsumd>lgresthr){hesubpd[mide][j]->Fill(adcsumd-lgcon[j]*track_mom->at(itrack));}
		}
	      }
	    }//lghit loop
	  }//calc mix

	}//trk type

	//fill mixing hit
	// if(trkflag>0){
	  if(alfill[0][mide]==false){
	    alfill[0][mide]=true;
	    for(int ihbd=0;ihbd<track_hbd_multiplicity->at(itrack);ihbd++){
	      hitset hbdhit;
	      if(track_hbd_allhit_adc->at(itrack).at(ihbd)<hbdthr) continue;
	      hbdhit.mid=track_hbd_mid->at(itrack);
	      hbdhit.lx=track_hbd_allhit_resx->at(itrack).at(ihbd)+track_hbd_lx->at(itrack);
	      hbdhit.ly=track_hbd_allhit_resy->at(itrack).at(ihbd)+track_hbd_ly->at(itrack);
	      hbdhit.adc=track_hbd_allhit_adc->at(itrack).at(ihbd);
	      hbdhit.tdc=track_hbd_allhit_ftime->at(itrack).at(ihbd);
	      hbdhits[mide].push_back(hbdhit);
	    }
	  }
	// }
	if(HBDhit){
	  if(alfill[1][mide]==false){
	    alfill[1][mide]=true;
	    for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){
	      double tmpt = track_lg_allhit_ftime->at(itrack).at(ilg);
	      double tmpa = track_lg_allhit_adc->at(itrack).at(ilg);
	      if(tmpa<lgresthr||tmpt<(ssdoffset-ssdregion)+track_ssd_t->at(itrack)||tmpt>(ssdoffset+ssdregion)+track_ssd_t->at(itrack)) continue;
	      hitset lghit;
	      lghit.mid=track_lg_mid->at(itrack);
	      lghit.lx=track_lg_allhit_resx->at(itrack).at(ilg)+track_lg_lx->at(itrack);
	      lghit.ly=track_lg_allhit_resy->at(itrack).at(ilg)+track_lg_ly->at(itrack);
	      lghit.adc=track_lg_allhit_adc->at(itrack).at(ilg);
	      lghit.tdc=track_lg_allhit_ftime->at(itrack).at(ilg);
	      lghits[mide].push_back(lghit);
	    }
	  }
	}
	//fill mixing hit

	ntrk[mide]++;

      }//track loop

      for(int im=0;im<5;im++){
	if(alfill[0][im]==true){
	  hbdmixhits[im].push_back(hbdhits[im]);
	  if(hbdmixhits[im].size()>mixevent){
	    hbdmixhits[im].erase(hbdmixhits[im].begin());
	  }
	}
	if(alfill[1][im]==true){
	  lgmixhits[im].push_back(lghits[im]);
	  if(lgmixhits[im].size()>mixevent){
	    lgmixhits[im].erase(lgmixhits[im].begin());
	  }
	}
	hnt[im]->Fill(ntrk[im]);
      }
      nevent++;

   }//event loop


   TString outfile = Form("%s",out_file_name);

   gStyle->SetOptStat(11111111);
   gStyle->SetOptFit(11111111);
   TCanvas* cnt = new TCanvas("cnt","cnt",700,500);
   cnt->Divide(2,2);
   for(int i=0;i<4;i++){
     cnt->cd(i+1);
     hnt[(i+3)%5]->Draw();
   }
   TCanvas* cn[ndet];
   TCanvas* cnd[ndet];
   for(int k=0;k<ndet;k++){
     cn[k] = new TCanvas(Form("cn%d",k),Form("cn%d",k),700,500);
     cn[k]->Divide(2,2);
     cnd[k] = new TCanvas(Form("cnd%d",k),Form("cnd%d",k),700,500);
     cnd[k]->Divide(2,2);
     for(int i=0;i<4;i++){
       cn[k]->cd(i+1);
       hn[(i+3)%5][k]->Draw();
       cnd[k]->cd(i+1);
       hnd[(i+3)%5][k]->Draw();
     }
   }
   TCanvas* ct[ndet];
   for(int k=0;k<ndet;k++){
     ct[k] = new TCanvas(Form("ct%d",k),Form("ct%d",k),700,500);
     ct[k]->Divide(2,2);
     for(int i=0;i<4;i++){
       ct[k]->cd(i+1);
       ht[(i+3)%5][k]->Draw("hist");
       // int norma = ht[(i+3)%5][k]->Integral();
       // int normb = htd[(i+3)%5][k]->Integral();
       // htd[(i+3)%5][k]->Scale((double)norma/(double)normb);
       htd[(i+3)%5][k]->Scale(1./(double)mixevent);
       htd[(i+3)%5][k]->SetLineColor(6);
       htd[(i+3)%5][k]->Draw("hist&&sames");
       ct[k]->cd(i+1)->Update();
       TPaveStats *st1 = (TPaveStats*)htd[(i+3)%5][k]->FindObject("stats");
       st1->SetLineColor(6);
       st1->SetX1NDC(0.58);
       st1->SetX2NDC(0.78);
       st1->SetY1NDC(0.495);
       st1->SetY2NDC(0.935);
       ct[k]->cd(i+1)->Modified();
     }
   }
   TCanvas* casubd[4][nopt][ndet];
   TH1F* hasubd[4][2][nopt][ndet];
   TF1* fasubd[4][2][nopt][ndet];
   TLegend* lasubd[4][2][nopt][ndet];
   int vasubd[4][2][nopt][ndet];
   for(int k=0;k<ndet;k++){
     for(int j=0;j<nopt;j++){
       for(int i=0;i<4;i++){
	 casubd[i][j][k] = new TCanvas(Form("casubd%d%d%d",i,j,k),Form("casubd%d%d%d",i,j,k),700,500);
	 casubd[i][j][k]->Divide(2,2);
	 casubd[i][j][k]->cd(1);
	 haresx[(i+3)%5][j][k]->Draw("hist");
	 int reg[4] = {haresx[(i+3)%5][j][k]->FindBin(-800.),haresx[(i+3)%5][j][k]->FindBin(-100.),haresx[(i+3)%5][j][k]->FindBin(100.),haresx[(i+3)%5][j][k]->FindBin(800.)};
	 // int norma = haresx[(i+3)%5][j][k]->Integral(reg[0],reg[1])+haresx[(i+3)%5][j][k]->Integral(reg[2],reg[3]);
	 // int normb = haresxd[(i+3)%5][j][k]->Integral(reg[0],reg[1])+haresxd[(i+3)%5][j][k]->Integral(reg[2],reg[3]);
	 // haresxd[(i+3)%5][j][k]->Scale((double)norma/(double)normb);
	 haresxd[(i+3)%5][j][k]->Scale(1./(double)mixevent);
	 haresxd[(i+3)%5][j][k]->SetLineColor(6);
	 haresxd[(i+3)%5][j][k]->Draw("hist&&same");
	 casubd[i][j][k]->cd(2);
	 haresy[(i+3)%5][j][k]->Draw("hist");
	 // norma = haresy[(i+3)%5][j][k]->Integral(reg[0],reg[1])+haresy[(i+3)%5][j][k]->Integral(reg[2],reg[3]);
	 // normb = haresyd[(i+3)%5][j][k]->Integral(reg[0],reg[1])+haresyd[(i+3)%5][j][k]->Integral(reg[2],reg[3]);
	 // haresyd[(i+3)%5][j][k]->Scale((double)norma/(double)normb);
	 haresyd[(i+3)%5][j][k]->Scale(1./(double)mixevent);
	 haresyd[(i+3)%5][j][k]->SetLineColor(6);
	 haresyd[(i+3)%5][j][k]->Draw("hist&&same");
	 casubd[i][j][k]->cd(3);
	 hasubd[i][0][j][k] = (TH1F*)haresx[(i+3)%5][j][k]->Clone();
	 hasubd[i][0][j][k]->SetName(Form("haresxcp%d%d%d",(i+3)%5,j,k));
	 hasubd[i][0][j][k]->Add(haresxd[(i+3)%5][j][k],-1);
	 hasubd[i][0][j][k]->Draw("hist");
	 fasubd[i][0][j][k] = new TF1(Form("fasubd%dx%d%d",i,j,k),"gaus",-800,800);
	 hasubd[i][0][j][k]->Fit(Form("fasubd%dx%d%d",i,j,k),"","",-fitregion[k],fitregion[k]);
	 lasubd[i][0][j][k] = new TLegend(0.1,0.75,0.4,0.9);
	 vasubd[i][0][j][k] = hasubd[i][0][j][k]->Integral(roughbin[k]/2-hw_intx[k]*roughbin[k]/1600,roughbin[k]/2+hw_inty[k]*roughbin[k]/1600);
	 lasubd[i][0][j][k]->AddEntry(hasubd[i][0][j][k],Form("%d<Integral<%d, %d",-hw_intx[k],hw_intx[k],vasubd[i][0][j][k]),"l");
	 lasubd[i][0][j][k]->AddEntry((TObject*)0,Form("n_track: %d",ntrack[(i+3)%5][k]),"");
	 lasubd[i][0][j][k]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasubd[i][0][j][k]/(double)ntrack[(i+3)%5][k]),"");
	 lasubd[i][0][j][k]->Draw();
	 casubd[i][j][k]->cd(4);
	 hasubd[i][1][j][k] = (TH1F*)haresy[(i+3)%5][j][k]->Clone();
	 hasubd[i][1][j][k]->SetName(Form("haresycp%d%d%d",(i+3)%5,j,k));
	 hasubd[i][1][j][k]->Add(haresyd[(i+3)%5][j][k],-1);
	 hasubd[i][1][j][k]->Draw("hist");
	 fasubd[i][1][j][k] = new TF1(Form("fasubd%dy%d%d",i,j,k),"gaus",-800,800);
	 hasubd[i][1][j][k]->Fit(Form("fasubd%dy%d%d",i,j,k),"","",-fitregion[k],fitregion[k]);
	 lasubd[i][1][j][k] = new TLegend(0.1,0.75,0.4,0.9);
	 vasubd[i][1][j][k] = hasubd[i][1][j][k]->Integral(roughbin[k]/2-hw_intx[k]*roughbin[k]/1600,roughbin[k]/2+hw_inty[k]*roughbin[k]/1600);
	 lasubd[i][1][j][k]->AddEntry(hasubd[i][1][j][k],Form("%d<Integral<%d, %d",-hw_intx[k],hw_intx[k],vasubd[i][1][j][k]),"l");
	 lasubd[i][1][j][k]->AddEntry((TObject*)0,Form("n_track: %d",ntrack[(i+3)%5][k]),"");
	 lasubd[i][1][j][k]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasubd[i][1][j][k]/(double)ntrack[(i+3)%5][k]),"");
	 lasubd[i][1][j][k]->Draw();
       }
     }
   }
   TCanvas* casub2d[4][ndet];
   TH2F* hasub2d[4][ndet];
   TH2F* hasub2dcopy[4][ndet];
   TLegend* lasub2d[3][4][ndet];
   int vasub2d[3][4][ndet];
   double voriginx[4][ndet]={0.};
   double voriginy[4][ndet]={0.};
   double vsigmax[4][ndet]={0.};
   double vsigmay[4][ndet]={0.};
   double missurv[4][ndet]={0.};
   double effxtrkp[4][ndet]={0.};
   for(int k=0;k<ndet;k++){
     for(int i=0;i<4;i++){
       casub2d[i][k] = new TCanvas(Form("casub2d%d%d",i,k),Form("casub2d%d%d",i,k),700,700);
       casub2d[i][k]->Divide(2,2);
       voriginx[i][k] = fasubd[i][0][1][k]->GetParameter(1);
       voriginy[i][k] = fasubd[i][1][1][k]->GetParameter(1);
       vsigmax[i][k] = fasubd[i][0][1][k]->GetParameter(2)*track_select_sigma;
       vsigmay[i][k] = fasubd[i][1][1][k]->GetParameter(2)*track_select_sigma;
       if(k==0){voriginx[i][k]=hbd_voriginx[i];voriginy[i][k]=hbd_voriginy[i];vsigmax[i][k]=hbd_vsigmax[i];vsigmay[i][k]=hbd_vsigmay[i];}
       if(k==1||k==3){voriginx[i][k]=0;voriginy[i][k]=0;vsigmax[i][k]=hw_intx[1];vsigmay[i][k]=hw_inty[1];}
       if(k==2||k==4){voriginy[i][k]=0;vsigmay[i][k]=hw_inty[1];}
       casub2d[i][k]->cd(1);
       hares[(i+3)%5][k]->Draw("colz");
       lasub2d[0][i][k] = new TLegend(0.1,0.8,0.45,0.9);
       vasub2d[0][i][k] = AnalyzerResidualHBD::Get2DHistSquareIntegral(hares[(i+3)%5][k],voriginx[i][k],voriginy[i][k],vsigmax[i][k],vsigmay[i][k]);
       lasub2d[0][i][k]->AddEntry(hares[(i+3)%5][k],Form("Integral, %d",vasub2d[0][i][k]),"l");
       lasub2d[0][i][k]->AddEntry((TObject*)0,Form("int/ntrack: %1.3f",(double)vasub2d[0][i][k]/(double)ntrack[(i+3)%5][k]),"");
       lasub2d[0][i][k]->Draw();
       casub2d[i][k]->cd(2);
       int x0 = haresd[(i+3)%5][k]->GetXaxis()->FindBin(-100.);
       int x1 = haresd[(i+3)%5][k]->GetXaxis()->FindBin(100.);
       int y0 = haresd[(i+3)%5][k]->GetYaxis()->FindBin(-100.);
       int y1 = haresd[(i+3)%5][k]->GetYaxis()->FindBin(100.);
       // int norma = hares[(i+3)%5][k]->Integral()-hares[(i+3)%5][k]->Integral(x0,x1,y0,y1);
       // int normb = haresd[(i+3)%5][k]->Integral()-haresd[(i+3)%5][k]->Integral(x0,x1,y0,y1);
       // haresd[(i+3)%5][k]->Scale((double)norma/(double)normb);
       haresd[(i+3)%5][k]->Scale(1./(double)mixevent);
       haresd[(i+3)%5][k]->Draw("colz");
       lasub2d[1][i][k] = new TLegend(0.1,0.8,0.7,0.9);
       vasub2d[1][i][k] = AnalyzerResidualHBD::Get2DHistSquareIntegral(haresd[(i+3)%5][k],voriginx[i][k],voriginy[i][k],vsigmax[i][k],vsigmay[i][k]);
       lasub2d[1][i][k]->AddEntry(haresd[(i+3)%5][k],Form("Integral, %d",vasub2d[1][i][k]),"l");
       lasub2d[1][i][k]->AddEntry((TObject*)0,Form("int/ntrack (mis-track survival): %1.3f",(double)vasub2d[1][i][k]/(double)ntrack[(i+3)%5][k]),"");
       lasub2d[1][i][k]->Draw();
       missurv[i][k] = (double)vasub2d[1][i][k]/(double)ntrack[(i+3)%5][k];
       casub2d[i][k]->cd(3);
       hasub2d[i][k] = (TH2F*)hares[(i+3)%5][k]->Clone();
       hasub2d[i][k]->SetName(Form("hasub2d%d%d",(i+3)%5,k));
       hasub2d[i][k]->Add(haresd[(i+3)%5][k],-1);
       hasub2d[i][k]->Draw("colz");
       lasub2d[2][i][k] = new TLegend(0.1,0.75,0.6,0.9);
       hasub2dcopy[i][k] = (TH2F*)hasub2d[i][k]->Clone();
       vasub2d[2][i][k] = AnalyzerResidualHBD::Get2DHistSquareIntegral(hasub2d[i][k],hasub2dcopy[i][k],voriginx[i][k],voriginy[i][k],vsigmax[i][k],vsigmay[i][k]);
       lasub2d[2][i][k]->AddEntry(hasub2d[i][k],Form("Integral(sx:%dmm,sy:%dmm), %d",(int)vsigmax[i][k],(int)vsigmay[i][k],vasub2d[2][i][k]),"l");
       lasub2d[2][i][k]->AddEntry((TObject*)0,Form("n_track: %d",ntrack[(i+3)%5][k]),"");
       lasub2d[2][i][k]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasub2d[2][i][k]/(double)ntrack[(i+3)%5][k]),"");
       lasub2d[2][i][k]->Draw();
       effxtrkp[i][k] = (double)vasub2d[2][i][k]/(double)ntrack[(i+3)%5][k];
       casub2d[i][k]->cd(4)->DrawFrame(-ex_2d[k],-ex_2d[k],ex_2d[k],ex_2d[k]);
       hasub2dcopy[i][k]->Draw("colz sames");
     }
   }

   // Efficiency Summary
   const int step = 50;
   double trkpforhbdrej[4]={0.};
   double trkpforlgrej[4]={0.};
   TGraphErrors* geffh[4];
   TGraphErrors* geffc[4];
   TGraphErrors* geffhb[4];
   TGraphErrors* geffcb[4];
   TGraphErrors* gtrkp[4];
   TGraphErrors* gtrkpb[4];
   TGraphErrors* gtrkp2[4];
   TGraphErrors* gtrkpa[4];
   TCanvas *ceff = new TCanvas("ceff","ceff",700,500);
   TLegend* leff = new TLegend(0.5,0.5,0.9,0.9);
   ceff->Divide(2,2);
   for(int i=0;i<4;i++){
     double graphx[step]={0.};
     double veffh[step]={0.};
     double veffc[step]={0.};
     double veffhb[step]={0.};
     double veffcb[step]={0.};
     double vtrkp[step]={0.};
     double vtrkpb[step]={0.};
     double vtrkp2[step]={0.};
     double vtrkpa[step]={0.};
     double zero[step]={0.};
     double veffh_err[step]={0.};
     double veffc_err[step]={0.};
     double veffhb_err[step]={0.};
     double veffcb_err[step]={0.};
     double vtrkp_err[step]={0.};
     double vtrkpb_err[step]={0.};
     double vtrkp2_err[step]={0.};
     double vtrkpa_err[step]={0.};
     for(int st=0;st<step;st++){
       graphx[st] = effxtrkp[i][0] + st*(1.-effxtrkp[i][0])/((double)step-1.) ;
       veffh[st] = (double)vasub2d[2][i][1]/(double)vasub2d[2][i][0];
       veffh_err[st] = veffh[st]/sqrt((double)vasub2d[2][i][1]);
       veffc[st] = (double)vasub2d[2][i][2]/(double)vasub2d[2][i][0];
       veffc_err[st] = veffc[st]/sqrt((double)vasub2d[2][i][2]);
       vtrkp[st] = (double)vasub2d[2][i][0]/(double)ntrack[(i+3)%5][1];
       vtrkp_err[st] = vtrkp[st]/sqrt((double)vasub2d[2][i][0]);
       vtrkp2[st] = (double)vasub2d[2][i][3]/(double)ntrack[(i+3)%5][5];
       vtrkp2_err[st] = vtrkp[st]/sqrt((double)vasub2d[2][i][3]);
       vtrkpa[st] = (double)vasub2d[2][i][1]/(double)ntrack[(i+3)%5][7];
       vtrkpb[st] = effxtrkp[i][0]/graphx[st];
       veffhb[st] = effxtrkp[i][3]/vtrkpb[st];
       veffcb[st] = effxtrkp[i][4]/vtrkpb[st];
     }
     // for(int n=0;n<9;n++){
     //   std::cout<<ntrack[(i+3)%5][n]<<std::endl;
     // }
     trkpforhbdrej[i] = vtrkp2[0];
     trkpforlgrej[i] = vtrkp[0];
     geffh[i] = new TGraphErrors(step,graphx,veffh,zero,veffh_err);
     geffc[i] = new TGraphErrors(step,graphx,veffc,zero,veffc_err);
     gtrkp[i] = new TGraphErrors(step,graphx,vtrkp,zero,vtrkp_err);
     gtrkpb[i] = new TGraphErrors(step,graphx,vtrkpb,zero,vtrkpb_err);
     gtrkp2[i] = new TGraphErrors(step,graphx,vtrkp2,zero,vtrkp2_err);
     gtrkpa[i] = new TGraphErrors(step,graphx,vtrkpa,zero,vtrkpa_err);
     geffhb[i] = new TGraphErrors(step,graphx,veffhb,zero,veffhb_err);
     geffcb[i] = new TGraphErrors(step,graphx,veffcb,zero,veffcb_err);
     ceff->cd(i+1)->SetGrid();
     gtrkp[i]->SetTitle(Form("Efficiency&TrackPurity_Module%d;HBDefficiency;",(i+3)%5+103));
     gtrkp[i]->SetMaximum(1.);
     gtrkp[i]->SetMinimum(0.);
     gtrkp[i]->GetXaxis()->SetLimits(0,1);
     gtrkp[i]->SetMarkerColor(3);
     gtrkp[i]->SetLineColor(3);
     gtrkp[i]->Draw("ALP");
     gtrkp2[i]->SetMarkerColor(5);
     gtrkp2[i]->SetLineColor(5);
     gtrkp2[i]->Draw("LP");
     gtrkpa[i]->SetMarkerColor(1);
     gtrkpa[i]->SetLineColor(1);
     gtrkpa[i]->Draw("LP");
     geffh[i]->SetMarkerColor(2);
     geffh[i]->SetLineColor(2);
     geffh[i]->Draw("LP");
     geffc[i]->SetMarkerColor(4);
     geffc[i]->SetLineColor(4);
     geffc[i]->Draw("LP");
     geffhb[i]->SetMarkerColor(6);
     geffhb[i]->SetLineColor(6);
     geffhb[i]->Draw("LP");
     geffcb[i]->SetMarkerColor(7);
     geffcb[i]->SetLineColor(7);
     geffcb[i]->Draw("LP");
     gtrkpb[i]->SetMarkerColor(8);
     gtrkpb[i]->SetLineColor(8);
     gtrkpb[i]->Draw("LP");
     if(i==2){
       leff->AddEntry(gtrkp[2],"TrackPurity w/HBD","l");
       leff->AddEntry(gtrkpb[2],"TrackPurityBefore","l");
       leff->AddEntry(gtrkp2[2],"TrackPurity w/LG","l");
       leff->AddEntry(gtrkpa[2],"TrackPurity w/ALL","l");
       leff->AddEntry(geffh[2],"LGHitEff byTrackw/HBD","l");
       leff->AddEntry(geffc[2],"LGClsEff byTrackw/HBD","l");
       leff->AddEntry(geffhb[2],"LGHitEff byTrackw/oHBD","l");
       leff->AddEntry(geffcb[2],"LGClsEff byTrackw/oHBD","l");
       leff->Draw();
     }
   }
   TCanvas *ceff2 = new TCanvas("ceff2","ceff2",700,500);
   ceff2->Divide(2,2);
   TLegend* leff2[4];
   for(int i=0;i<4;i++){
     ceff2->cd(i+1);
     leff2[i] = new TLegend(0.1,0.1,0.9,0.9);
     leff2[i]->AddEntry((TObject*)0,Form("Module%d",(i+3)%5+103),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_HBD(Hit): %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1],vasub2d[2][i][3],(double)vasub2d[2][i][1]/(double)vasub2d[2][i][3],sqrt((double)vasub2d[2][i][1])/(double)vasub2d[2][i][3]),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_HBD(Cls): %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][2],vasub2d[2][i][4],(double)vasub2d[2][i][2]/(double)vasub2d[2][i][4],sqrt((double)vasub2d[2][i][2])/(double)vasub2d[2][i][4]),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_LGHit: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1],vasub2d[2][i][0],(double)vasub2d[2][i][1]/(double)vasub2d[2][i][0],sqrt((double)vasub2d[2][i][1])/(double)vasub2d[2][i][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_LGCls: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][2],vasub2d[2][i][0],(double)vasub2d[2][i][2]/(double)vasub2d[2][i][0],sqrt((double)vasub2d[2][i][2])/(double)vasub2d[2][i][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurity w/HBD: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][0],ntrack[(i+3)/5][1],(double)vasub2d[2][i][0]/(double)ntrack[(i+3)/5][1],sqrt((double)vasub2d[2][i][0])/(double)ntrack[(i+3)/5][1]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurityB: %d/%d/E_HBD=%1.3f +/- %1.3f",vasub2d[2][i][0],ntrack[(i+3)%5][0],(double)vasub2d[2][i][0]/(double)ntrack[(i+3)%5][0]/(double)vasub2d[2][i][1]*(double)vasub2d[2][i][3],sqrt((double)vasub2d[2][i][0])/(double)ntrack[(i+3)%5][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurity w/LG: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][3],ntrack[(i+3)%5][5],(double)vasub2d[2][i][3]/(double)ntrack[(i+3)%5][5],sqrt((double)vasub2d[2][i][3])/(double)ntrack[(i+3)%5][5]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurity w/ALL: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1],ntrack[(i+3)%5][7],(double)vasub2d[2][i][1]/(double)ntrack[(i+3)%5][7],sqrt((double)vasub2d[2][i][1])/(double)ntrack[(i+3)%5][7]),"");
     leff2[i]->Draw();
   }
   // Efficiency Summary   


   TCanvas* ctrkmom = new TCanvas("ctrkmom","ctrkmom",700,500);
   ctrkmom->Divide(2,2);
   for(int i=0;i<4;i++){
     ctrkmom->cd(i+1);
     trkmom[(i+3)%5]->Draw();
   }
   TCanvas* cevsp = new TCanvas("cevsp","cevsp",700,500);
   cevsp->Divide(2,2);
   for(int i=0;i<4;i++){
     cevsp->cd(i+1);
     hevsp[(i+3)%5]->Draw("colz");
   }
   TCanvas* cevspd = new TCanvas("cevspd","cevspd",700,500);
   cevspd->Divide(2,2);
   for(int i=0;i<4;i++){
     cevspd->cd(i+1);
     hevspd[(i+3)%5]->Draw("colz");
   }
   TH1F* hedivpsub[4][4];
   TCanvas* cedivp[4];
   TCanvas* cedivpsub[4];
   TCanvas* cesubp[4];
   for(int j=0;j<4;j++){
     cedivp[j] = new TCanvas(Form("cedivp%d",j),Form("cedivp%d",j),700,500);
     cedivpsub[j] = new TCanvas(Form("cedivpsub%d",j),Form("cedivpsub%d",j),700,500);
     cesubp[j] = new TCanvas(Form("cesubp%d",j),Form("cesubp%d",j),700,500);
     cedivp[j]->Divide(2,2);
     cedivpsub[j]->Divide(2,2);
     cesubp[j]->Divide(2,2);
     for(int i=0;i<4;i++){
       gStyle->SetOptStat(1111);
       cedivp[j]->cd(i+1)->SetLogy();
       int norma = hedivp[(i+3)%5][j]->Integral(hedivp[(i+3)%5][j]->FindBin(0),hedivp[(i+3)%5][j]->FindBin(200));
       int normb = hedivpd[(i+3)%5][j]->Integral(hedivpd[(i+3)%5][j]->FindBin(0),hedivpd[(i+3)%5][j]->FindBin(200));
       hedivp[(i+3)%5][j]->Draw("hist");
       // hedivpd[(i+3)%5][j]->Scale((double)norma/(double)normb);
       hedivpd[(i+3)%5][j]->Scale(1./(double)mixevent);
       hedivpd[(i+3)%5][j]->SetLineColor(2);
       hedivpd[(i+3)%5][j]->Draw("hist&&sames");
       cedivp[j]->cd(i+1)->Update();
       TPaveStats *st1 = (TPaveStats*)hedivpd[(i+3)%5][j]->FindObject("stats");
       st1->SetLineColor(2);
       st1->SetX1NDC(0.58);
       st1->SetX2NDC(0.78);
       st1->SetY1NDC(0.75);
       st1->SetY2NDC(0.935);
       cedivp[j]->cd(i+1)->Modified();
       cedivpsub[j]->cd(i+1)->SetGridy();
       hedivpsub[i][j] = (TH1F*)hedivp[(i+3)%5][j]->Clone();
       hedivpsub[i][j]->SetName(Form("hedivpsub%d%d",(i+3)%5,j));
       hedivpsub[i][j]->Add(hedivpd[(i+3)%5][j],-1);
       hedivpsub[i][j]->Draw("hist e");
       cesubp[j]->cd(i+1);
       hesubp[(i+3)%5][j]->Draw("hist");
       hesubpd[(i+3)%5][j]->Scale(1./(double)mixevent);
       hesubpd[(i+3)%5][j]->SetLineColor(2);
       hesubpd[(i+3)%5][j]->Draw("hist&&sames");
     }
   }
   // TCanvas* cesubp = new TCanvas("cesubp","cesubp",700,500);
   // cesubp->Divide(2,2);
   // for(int i=0;i<4;i++){
   //   cesubp->cd(i+1);
   //   hesubp[(i+3)%5]->Draw("hist");
   //   hesubpd[(i+3)%5]->Scale(1./(double)mixevent);
   //   hesubpd[(i+3)%5]->SetLineColor(2);
   //   hesubpd[(i+3)%5]->Draw("hist&&sames");
   // }
   TCanvas* cnlghitwt = new TCanvas("cnlghitwt","cnlghitwt",700,500);
   cnlghitwt->Divide(2,2);
   for(int i=0;i<4;i++){
     cnlghitwt->cd(i+1)->SetLogy();
     hnlghitwt[(i+3)%5]->Draw();
   }
   TCanvas* cnlghitwtd = new TCanvas("cnlghitwtd","cnlghitwtd",700,500);
   cnlghitwtd->Divide(2,2);
   for(int i=0;i<4;i++){
     cnlghitwtd->cd(i+1)->SetLogy();
     hnlghitwtd[(i+3)%5]->Draw();
   }


   TCanvas* cdef = new TCanvas("cdef","cdef",700,500);
   cdef->SaveAs(outfile+"[","pdf");
   cnt->SaveAs(outfile,"pdf");
   ceff->SaveAs(outfile,"pdf");
   ceff2->SaveAs(outfile,"pdf");
   ctrkmom->SaveAs(outfile,"pdf");
   cnlghitwt->SaveAs(outfile,"pdf");
   cnlghitwtd->SaveAs(outfile,"pdf");
   cevsp->SaveAs(outfile,"pdf");
   cevspd->SaveAs(outfile,"pdf");
   for(int j=0;j<4;j++){
     cedivp[j]->SaveAs(outfile,"pdf");
     cedivpsub[j]->SaveAs(outfile,"pdf");
   }
   for(int j=0;j<4;j++){
     cesubp[j]->SaveAs(outfile,"pdf");
   }
   for(int k=0;k<ndet;k++){
     cn[k]->SaveAs(outfile,"pdf");
     cnd[k]->SaveAs(outfile,"pdf");
     for(int i=0;i<4;i++){
       for(int j=0;j<nopt;j++){
	 casubd[i][j][k]->SaveAs(outfile,"pdf");
       }
       casub2d[i][k]->SaveAs(outfile,"pdf");
     }
     ct[k]->SaveAs(outfile,"pdf");
     std::cout<<det[k]<<"end"<<std::endl;
   }
   cdef->SaveAs(outfile+"]","pdf");

   fouthist->Write();
   fouthist->Close();

}
