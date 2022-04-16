#define AnalyzerResidualHBD_cxx
#include "AnalyzerResidualHBD.hh"
#include "SingleTrackAnalyzerForRes.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TLegend.h>

#include <TH1.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "TROOT.h"

double AnalyzerResidualHBD::Get2DHistSquareIntegral(TH2F* h2d, TH2F* h2dcopy, double originx, double originy, double sigmax, double sigmay){

  h2dcopy->Reset();
  int x0 = h2d->GetXaxis()->FindBin(originx-sigmax);
  int x1 = h2d->GetXaxis()->FindBin(originx+sigmax);
  int y0 = h2d->GetYaxis()->FindBin(originy-sigmay);
  int y1 = h2d->GetYaxis()->FindBin(originy+sigmay);

  int sx = x0-1;
  int ex = x1+1;
  int sy = y0-1;
  int ey = y1+1;
  for(int i=sx;i<ex;i++){
    for(int j=sy;j<ey;j++){
      if(i>=x0&&i<x1&&j>=y0&&j<=y1){
  	double content = h2d->GetBinContent(i,j);
  	h2dcopy->SetBinContent(i,j,content);
      }
    }
  }

  return h2d->Integral(x0,x1,y0,y1);

}

double AnalyzerResidualHBD::Get2DHistSquareIntegral(TH2F* h2d, double originx, double originy, double sigmax, double sigmay){

  TH2F* h2dcopy;
  h2dcopy  = (TH2F*)h2d->Clone();

  return Get2DHistSquareIntegral(h2d,h2dcopy,originx,originy,sigmax,sigmay);

}

double AnalyzerResidualHBD::Get2DHistIntegral(TH2F* h2d, int radius, TH2F* h2dcopy, double originx, double originy){

  h2dcopy->Reset();
  int nbinx = h2d->GetNbinsX();
  int nbiny = h2d->GetNbinsY();
  int x0 = h2d->GetXaxis()->FindBin(originx);
  int x1 = h2d->GetXaxis()->FindBin(originx+100.);
  int y0 = h2d->GetYaxis()->FindBin(originy);
  int y1 = h2d->GetYaxis()->FindBin(originy+100.);
  double xw = 100./(x1-x0);
  double yw = 100./(y1-y0);

  int integral=0;
  int xr = h2d->GetXaxis()->FindBin((double)radius) - x0;
  int sx = x0-xr-1;
  int ex = x0+xr+1;
  int yr = h2d->GetYaxis()->FindBin((double)radius) - y0;
  int sy = y0-yr-1;
  int ey = y0+yr+1;
  for(int i=sx;i<ex;i++){
    for(int j=sy;j<ey;j++){
      double x = (i-x0)*xw;
     double y = (j-y0)*yw;
      if(x*x+y*y<=radius*radius){
	double content = h2d->GetBinContent(i,j);
	//std::cout<<x<<" "<<y<<" "<<content<<std::endl;
	integral += content;
	h2dcopy->SetBinContent(i,j,content);
	//h2dcopy->Fill(x,y);
      }
    }
  }

  return integral;

}

double AnalyzerResidualHBD::Get2DHistIntegral(TH2F* h2d, int radius, double originx, double originy){

  TH2F* h2dcopy;
  h2dcopy  = (TH2F*)h2d->Clone();

  return Get2DHistIntegral(h2d,radius,h2dcopy,originx,originy);

}

double AnalyzerResidualHBD::Get2DHistIntegral(TH2F* h2d, int radius, TH2F* h2dcopy){

  double originx = 0.;
  double originy = 0.;

  return Get2DHistIntegral(h2d,radius,h2dcopy,originx,originy);

}

void AnalyzerResidualHBD::Loop()
{
//   In a ROOT session, you can do:
//      root> .L AnalyzerResidualHBD.C
//      root> AnalyzerResidualHBD t
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

void AnalyzerResidualHBD::DrawPDF(int runoption, int maxevent, char* out_file_name)
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
   TH2F *htlg[5];
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
     htlg[i] = new TH2F(Form("htlg%d",i),Form("lg_time:fastest_time_mod%d",103+i),800,-150,650,100,50,150);
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
   TH1F* hlgadc[42];
   for(int i=0;i<42;i++){
     hlgadc[i] = new TH1F(Form("hlgadc%d",i),Form("lg_adc_ch%d",(i/7)*10+i%7),50,0,200);
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

	int trk_mid = track_mid->at(itrack);
	double trk_mom = track_mom->at(itrack);
	float trk_lg_adc = track_lg_adc->at(itrack);
	int trk_lg_ch = track_lg_cid->at(itrack);

	double resx_min = track_nearx->at(itrack);
	double resy_min = track_neary->at(itrack);
	int nhbdc = track_multiplicity->at(itrack);
	for(int ihbd=0;ihbd<nhbdc;ihbd++){// hbdcluster loop
	  double resx = track_allhit_resx->at(itrack).at(ihbd);
	  double resy = track_allhit_resy->at(itrack).at(ihbd);
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
	  if(trk_lg_adc>100){
	    haresx[trk_mid-103][2]->Fill(resx);
	    haresy[trk_mid-103][2]->Fill(resy);
	    if(fabs(resy)<hw_int){
	      haresx[trk_mid-103][3]->Fill(resx);
	    }
	    if(fabs(resx)<hw_int){
	      haresy[trk_mid-103][3]->Fill(resy);
	    }
	  }
	  hares[trk_mid-103]->Fill(resx,resy);
	  if( resx*resx+resy*resy < hw_int*hw_int ){
	    double ftime = track_allhit_ftime->at(itrack).at(ihbd);
	    ht[trk_mid-103]->Fill(ftime);
	    htlg[trk_mid-103]->Fill(ftime,track_lg_t->at(itrack));
	    hadc[trk_mid-103]->Fill(track_allhit_adc->at(itrack).at(ihbd));
	    if(trk_lg_ch>-1000&&track_lg_mid->at(itrack)==106){hlgadc[(trk_lg_ch/10)*7+(trk_lg_ch%10)]->Fill(track_lg_adc->at(itrack));}
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
	if(trk_lg_adc>100){
	  ntrack[trk_mid-103][2]++;
	  ntrack[trk_mid-103][3]++;
	}
	h1->Fill(resx_min);
	hx[trk_mid-103]->Fill(resx_min);
	h2->Fill(resy_min);
	hy[trk_mid-103]->Fill(resy_min);
	hn->Fill(nhbdc);
	hxn[trk_mid-103]->Fill(nhbdc);

	double resx_dam_min = track_dum_nearx->at(itrack);
	double resy_dam_min = track_dum_neary->at(itrack);
	int nhbdc_dam = track_dum_multiplicity->at(itrack);
	for(int ihbd=0;ihbd<nhbdc_dam;ihbd++){// hbdcluster loop
	  double resx_dam = track_allhit_dum_resx->at(itrack).at(ihbd);
	  double resy_dam = track_allhit_dum_resy->at(itrack).at(ihbd);
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
	    hadcd[trk_mid-103]->Fill(track_allhit_dum_adc->at(itrack).at(ihbd));
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

   TCanvas* c[13];
   for(int i=0;i<13;i++){
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
   c[12]->Divide(2,2);
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
     htlg[(i+3)%5]->Draw("colz");
     c[12]->cd(i+1);
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
     vasub2d[i] = Get2DHistIntegral(hasub2d[i],hw_int,hasub2dcopy[i]);
     lasub2d[i]->AddEntry(hasub2d[i],Form("Integral(r:%dmm), %d",hw_int,vasub2d[i]),"l");
     int n_track = hx[(i+3)%5]->GetEntries();
     lasub2d[i]->AddEntry((TObject*)0,Form("n_track: %d",n_track),"");
     lasub2d[i]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasub2d[i]/(double)n_track),"");
     lasub2d[i]->Draw();
     casub2d[i]->cd(4)->DrawFrame(-50,-50,50,50);
     hasub2dcopy[i]->Draw("colz sames");
   }
   TCanvas* clgadc = new TCanvas("clgadc","clgadc",700,500);
   clgadc->Divide(7,6);
   for(int i=1;i<43;i++){
     clgadc->cd(i);
     hlgadc[42-i]->Draw();
   }

   TCanvas* cdef = new TCanvas("cdef","cdef",700,500);
   cdef->SaveAs(outfile+"[","pdf");
   ca1->SaveAs(outfile,"pdf");
   ca2->SaveAs(outfile,"pdf");
   csub1->SaveAs(outfile,"pdf");
   csub2->SaveAs(outfile,"pdf");
   cc1->SaveAs(outfile,"pdf");
   cc2->SaveAs(outfile,"pdf");
   for(int i=0;i<13;i++){
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
   clgadc->SaveAs(outfile,"pdf");
   cdef->SaveAs(outfile+"]","pdf");
}
