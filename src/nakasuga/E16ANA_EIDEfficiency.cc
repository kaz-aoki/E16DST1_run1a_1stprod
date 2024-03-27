#define E16ANA_EIDEfficiency_cxx
#include "E16ANA_EIDEfficiency.hh"
#include "E16ANA_EIDSingleTrackAnalyzer.hh"
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

#define LGWFHit // <=> LGTrgHit

double CalcBinomialError(int all, int hit){
  double value = (double)hit/(double)all;
  double rerr = 1./sqrt((double)hit);
  return rerr*value;
}
double GetLarger(double x1, double x2){
  if(x1>=x2){ return x1;}
  else{return x2;}
}
double GetSmaller(double x1, double x2){
  if(x1<x2){ return x1;}
  else{return x2;}
}
bool ChExist(int cid){
  if( (cid%10>=0&&cid%10<=5&&cid>=0&&cid<=55) || cid==26 || cid==36 ){return true;}
  else{return false;}
}
int HbdTrgCid(double lx, double ly){
  double cidx = (lx+300)/600.*6.;
  double cidy = (ly+300)/600.*6.;
  return (int)cidx+((int)cidy*10);
}

void DC1DForeMixFM(char* str, TCanvas* c, TCanvas* csub, TH1F** h, TH1F** hd, TH1F** hsub, int mixevent){

   c->Divide(2,2);
   csub->Divide(2,2);
   for(int i=0;i<4;i++){
     gStyle->SetOptStat(1111);
     c->cd(i+1);
     h[(i+3)%5]->Draw("hist");
     hd[(i+3)%5]->Scale(1./(double)mixevent);
     hd[(i+3)%5]->SetLineColor(2);
     hd[(i+3)%5]->Draw("hist&&sames");
     c->cd(i+1)->Update();
     TPaveStats *st1 = (TPaveStats*)hd[(i+3)%5]->FindObject("stats");
     st1->SetLineColor(2);
     st1->SetX1NDC(0.58);
     st1->SetX2NDC(0.78);
     st1->SetY1NDC(0.75);
     st1->SetY2NDC(0.935);
     c->cd(i+1)->Modified();
     csub->cd(i+1)->SetGridy();
     hsub[i] = (TH1F*)h[(i+3)%5]->Clone();
     hsub[i]->SetName(Form("h%ssub%d",str,(i+3)%5));
     hsub[i]->Add(hd[(i+3)%5],-1);
     hsub[i]->Draw("hist e");
   }
}
void DC2DForeMixFM(TCanvas* c, TCanvas* cd, TCanvas* csub, TH2F** h, TH2F** hd, TH2F** hsub, int mixevent){

   c->Divide(2,2);
   cd->Divide(2,2);
   csub->Divide(2,2);
   for(int i=0;i<4;i++){
     c->cd(i+1)->SetGrid();
     h[(i+3)%5]->Draw("colz");
     cd->cd(i+1)->SetGrid();
     hd[(i+3)%5]->Scale(1./(double)mixevent);
     hd[(i+3)%5]->Draw("colz");
     csub->cd(i+1)->SetGrid();
     hsub[i] = (TH2F*)h[(i+3)%5]->Clone();
     hsub[i]->Add(hd[(i+3)%5],-1);
     hsub[i]->SetMinimum(0);
     hsub[i]->Draw("colz");
   }
}
void DC1DForeMix(TCanvas* c, TH1F** h, TH1F** hd, int mixevent){

  c->Divide(2,2);
  for(int i=0;i<4;i++){
    c->cd(i+1);
    h[(i+3)%5]->Draw("hist");
    hd[(i+3)%5]->Scale(1./(double)mixevent);
    hd[(i+3)%5]->SetLineColor(6);
    hd[(i+3)%5]->Draw("hist&&sames");
    c->cd(i+1)->Update();
    TPaveStats *st1 = (TPaveStats*)hd[(i+3)%5]->FindObject("stats");
    st1->SetLineColor(6);
    st1->SetX1NDC(0.58);
    st1->SetX2NDC(0.78);
    st1->SetY1NDC(0.495);
    st1->SetY2NDC(0.935);
    c->cd(i+1)->Modified();
  }
}
void DC2DForeMix(TCanvas* c, TCanvas* cd, TH2F** h, TH2F** hd, int mixevent){

   c->Divide(2,2);
   cd->Divide(2,2);
   for(int i=0;i<4;i++){
     c->cd(i+1)->SetGrid();
     h[(i+3)%5]->Draw("colz");
     cd->cd(i+1)->SetGrid();
     hd[(i+3)%5]->Scale(1./(double)mixevent);
     hd[(i+3)%5]->Draw("colz");
   }
}

double ExpectedE(double p){

  const double sr_pi = 24.;//[mV]
  const double ratio_e_pi = 3.3;
  // const double sr_pi = 26.3;//[mV]
  // const double ratio_e_pi = 6784.4/2434.9;
  double ref_mean = sr_pi*ratio_e_pi;//0.4GeV e
  double ref_sigma = ref_mean*35./148.;//0.4GeV e
  double slope = ref_mean/0.4;//mean = slope * ene
  double alpha = ref_sigma/sqrt(0.4);//sigma = alpha * sqrt(ene)

  double e = sqrt(p*p+0.000511*0.000511);
  double mean = slope*e;
  double sigma = alpha*sqrt(e);
  // double r_mean = gRandom->Gaus(mean,mean*0.3);

  double res = gRandom->Gaus(mean,sigma);
  // double res = gRandom->Gaus(r_mean,sigma);
  return res;
}

double E16ANA_EIDEfficiency::CalcADCNearHit(int condition, std::vector<hitset>& lgnear, double ssdt, lgcls& lgcluster){

  double ssdoffset = 51.;
  double ssdregion = 6.;

  if(condition==0){//return maxadc

  sort(lgnear.begin(),lgnear.end());
  double maxadc=-10000.;
  double adc=lgnear.at(0).adc;
  std::vector<lgcls> lgclss;
  lgcls tmp;
  tmp.cids.push_back(lgnear.at(0).mid);
  tmp.resxs.push_back(lgnear.at(0).lx);
  tmp.resys.push_back(lgnear.at(0).ly);
  tmp.adcs.push_back(lgnear.at(0).adc);
  tmp.tdcs.push_back(lgnear.at(0).tdc);
  // if(lgnear.size()>2){std::cout<<0<<" "<<lgnear.at(0).adc<<" "<<lgnear.at(0).tdc<<std::endl;}

  for(int i=1;i<lgnear.size();i++){
    // if(lgnear.size()>2){std::cout<<i<<" "<<lgnear.at(i).adc<<" "<<lgnear.at(i).tdc<<std::endl;}
    if((lgnear.at(i).tdc-lgnear.at(i-1).tdc)<3.){
      adc += lgnear.at(i).adc;
      tmp.cids.push_back(lgnear.at(i).mid);
      tmp.resxs.push_back(lgnear.at(i).lx);
      tmp.resys.push_back(lgnear.at(i).ly);
      tmp.adcs.push_back(lgnear.at(i).adc);
      tmp.tdcs.push_back(lgnear.at(i).tdc);
    }
    else{
      if(adc>maxadc){
	maxadc=adc;
	lgclss.clear();
	lgclss.push_back(tmp);
      }
      adc = lgnear.at(i).adc;
      tmp.cids.clear();
      tmp.resxs.clear();
      tmp.resys.clear();
      tmp.adcs.clear();
      tmp.tdcs.clear();
      tmp.cids.push_back(lgnear.at(i).mid);
      tmp.resxs.push_back(lgnear.at(i).lx);
      tmp.resys.push_back(lgnear.at(i).ly);
      tmp.adcs.push_back(lgnear.at(i).adc);
      tmp.tdcs.push_back(lgnear.at(i).tdc);
    }
  }
  if(adc>maxadc){
    maxadc=adc;
    lgclss.clear();
    lgclss.push_back(tmp);
  }
  // if(lgnear.size()>2){std::cout<<"------"<<lgnear.size()<<" "<<maxadc<<"-------"<<std::endl;}

  lgcluster = lgclss.at(0);
  int nadc = lgcluster.cids.size();
  double adcsum = 0;
  double cogx = 0;
  double cogy = 0;
  double maxadc_incls = -10000.;
  int maxadcch = -10000;
  for(int i=0;i<nadc;i++){
    adcsum += lgcluster.adcs.at(i);
    cogx += lgcluster.resxs.at(i)*lgcluster.adcs.at(i);
    cogy += lgcluster.resys.at(i)*lgcluster.adcs.at(i);
    if(lgcluster.adcs.at(i) > maxadc_incls){
      maxadc_incls = lgcluster.adcs.at(i);
      maxadcch = lgcluster.cids.at(i);
    }
  }
  cogx = cogx/adcsum;
  cogy = cogy/adcsum;
  double timediff = lgcluster.tdcs.at(nadc-1) - lgcluster.tdcs.at(0);
  lgcluster.adcsum = adcsum;
  lgcluster.timediff = timediff;
  lgcluster.cogx = cogx;
  lgcluster.cogy = cogy;
  lgcluster.maxadcch = maxadcch;

  // std::cout<<(maxadc-lgcluster.adcsum)<<std::endl;

  return maxadc;

  }
  else if(condition==1){//return maxadc w/ SSD timing cut

  sort(lgnear.begin(),lgnear.end());
  double maxadc=-10000.;
  double adc=lgnear.at(0).adc;
  std::vector<lgcls> lgclss;
  lgcls tmp;
  tmp.cids.push_back(lgnear.at(0).mid);
  tmp.resxs.push_back(lgnear.at(0).lx);
  tmp.resys.push_back(lgnear.at(0).ly);
  tmp.adcs.push_back(lgnear.at(0).adc);
  tmp.tdcs.push_back(lgnear.at(0).tdc);
  // if(lgnear.size()>2){std::cout<<0<<" "<<lgnear.at(0).adc<<" "<<lgnear.at(0).tdc<<std::endl;}

  for(int i=1;i<lgnear.size();i++){
    // if(lgnear.size()>2){std::cout<<i<<" "<<lgnear.at(i).adc<<" "<<lgnear.at(i).tdc<<std::endl;}
    if((lgnear.at(i).tdc-lgnear.at(i-1).tdc)<3.){
      adc += lgnear.at(i).adc;
      tmp.cids.push_back(lgnear.at(i).mid);
      tmp.resxs.push_back(lgnear.at(i).lx);
      tmp.resys.push_back(lgnear.at(i).ly);
      tmp.adcs.push_back(lgnear.at(i).adc);
      tmp.tdcs.push_back(lgnear.at(i).tdc);
    }
    else{
      if(adc>maxadc&&fabs(ssdt+ssdoffset-tmp.tdcs.at(0))<ssdregion){
	maxadc=adc;
	lgclss.clear();
	lgclss.push_back(tmp);
      }
      adc = lgnear.at(i).adc;
      tmp.cids.clear();
      tmp.resxs.clear();
      tmp.resys.clear();
      tmp.adcs.clear();
      tmp.tdcs.clear();
      tmp.cids.push_back(lgnear.at(i).mid);
      tmp.resxs.push_back(lgnear.at(i).lx);
      tmp.resys.push_back(lgnear.at(i).ly);
      tmp.adcs.push_back(lgnear.at(i).adc);
      tmp.tdcs.push_back(lgnear.at(i).tdc);
    }
  }
  if(adc>maxadc&&fabs(ssdt+ssdoffset-tmp.tdcs.at(0))<ssdregion){
    maxadc=adc;
    lgclss.clear();
    lgclss.push_back(tmp);
  }
  // if(lgnear.size()>2){std::cout<<"------"<<lgnear.size()<<" "<<maxadc<<"-------"<<std::endl;}

  if(lgclss.size()==1){
    lgcluster = lgclss.at(0);
    int nadc = lgcluster.cids.size();
    double adcsum = 0;
    double cogx = 0;
    double cogy = 0;
    double maxadc_incls = -10000.;
    int maxadcch = -10000;
    for(int i=0;i<nadc;i++){
      adcsum += lgcluster.adcs.at(i);
      cogx += lgcluster.resxs.at(i)*lgcluster.adcs.at(i);
      cogy += lgcluster.resys.at(i)*lgcluster.adcs.at(i);
      if(lgcluster.adcs.at(i) > maxadc_incls){
	maxadc_incls = lgcluster.adcs.at(i);
	maxadcch = lgcluster.cids.at(i);
      }
    }
    cogx = cogx/adcsum;
    cogy = cogy/adcsum;
    double timediff = lgcluster.tdcs.at(nadc-1) - lgcluster.tdcs.at(0);
    lgcluster.adcsum = adcsum;
    lgcluster.timediff = timediff;
    lgcluster.cogx = cogx;
    lgcluster.cogy = cogy;
    lgcluster.maxadcch = maxadcch;
  }

  // std::cout<<(maxadc-lgcluster.adcsum)<<std::endl;

  return maxadc;

  }
  else if(condition==2){//return adc around SSD timing

  sort(lgnear.begin(),lgnear.end());
  double mintdcdiff=10000.;
  double tdc=lgnear.at(0).tdc;
  std::vector<lgcls> lgclss;
  lgcls tmp;
  tmp.cids.push_back(lgnear.at(0).mid);
  tmp.resxs.push_back(lgnear.at(0).lx);
  tmp.resys.push_back(lgnear.at(0).ly);
  tmp.adcs.push_back(lgnear.at(0).adc);
  tmp.tdcs.push_back(lgnear.at(0).tdc);
  // if(lgnear.size()>2){std::cout<<0<<" "<<lgnear.at(0).adc<<" "<<lgnear.at(0).tdc<<std::endl;}

  for(int i=1;i<lgnear.size();i++){
    // if(lgnear.size()>2){std::cout<<i<<" "<<lgnear.at(i).adc<<" "<<lgnear.at(i).tdc<<std::endl;}
    if((lgnear.at(i).tdc-lgnear.at(i-1).tdc)<3.){
      tmp.cids.push_back(lgnear.at(i).mid);
      tmp.resxs.push_back(lgnear.at(i).lx);
      tmp.resys.push_back(lgnear.at(i).ly);
      tmp.adcs.push_back(lgnear.at(i).adc);
      tmp.tdcs.push_back(lgnear.at(i).tdc);
    }
    else{
      if( fabs(ssdt+ssdoffset-tdc)<mintdcdiff && fabs(ssdt+ssdoffset-tmp.tdcs.at(0))<ssdregion ){
	mintdcdiff=fabs(ssdt+ssdoffset-tdc);
	lgclss.clear();
	lgclss.push_back(tmp);
      }
      tdc = lgnear.at(i).tdc;
      tmp.cids.clear();
      tmp.resxs.clear();
      tmp.resys.clear();
      tmp.adcs.clear();
      tmp.tdcs.clear();
      tmp.cids.push_back(lgnear.at(i).mid);
      tmp.resxs.push_back(lgnear.at(i).lx);
      tmp.resys.push_back(lgnear.at(i).ly);
      tmp.adcs.push_back(lgnear.at(i).adc);
      tmp.tdcs.push_back(lgnear.at(i).tdc);
    }
  }
  if( fabs(ssdt+ssdoffset-tdc)<mintdcdiff && fabs(ssdt+ssdoffset-tmp.tdcs.at(0))<ssdregion ){
    mintdcdiff=fabs(ssdt+ssdoffset-tdc);
    lgclss.clear();
    lgclss.push_back(tmp);
  }
  // if(lgnear.size()>2){std::cout<<"------"<<lgnear.size()<<" "<<maxadc<<"-------"<<std::endl;}

  double maxadc=-10000.;
  if(lgclss.size()==1){
    lgcluster = lgclss.at(0);
    int nadc = lgcluster.cids.size();
    double adcsum = 0;
    double cogx = 0;
    double cogy = 0;
    double maxadc_incls = -10000.;
    int maxadcch = -10000;
    for(int i=0;i<nadc;i++){
      adcsum += lgcluster.adcs.at(i);
      cogx += lgcluster.resxs.at(i)*lgcluster.adcs.at(i);
      cogy += lgcluster.resys.at(i)*lgcluster.adcs.at(i);
      if(lgcluster.adcs.at(i) > maxadc_incls){
	maxadc_incls = lgcluster.adcs.at(i);
	maxadcch = lgcluster.cids.at(i);
      }
    }
    cogx = cogx/adcsum;
    cogy = cogy/adcsum;
    double timediff = lgcluster.tdcs.at(nadc-1) - lgcluster.tdcs.at(0);
    lgcluster.adcsum = adcsum;
    lgcluster.timediff = timediff;
    lgcluster.cogx = cogx;
    lgcluster.cogy = cogy;
    lgcluster.maxadcch = maxadcch;
    maxadc = adcsum;
  }
  // std::cout<<(maxadc-lgcluster.adcsum)<<std::endl;

  return maxadc;

  }
  else{
    return -10000.;
  }

}

void CalcClusterCand(E16ANA_GeometryV2& geometry, std::vector<int>& trk_ass_cids, int blockch, double position_block_lx, double position_block_ly, double angle_lx){

  double r_moliere = 14.;//mm
  double block_depth = 135.;//mm

  trk_ass_cids.push_back(blockch);
  double inner_proj_x[3];
  inner_proj_x[1] = position_block_lx;
  inner_proj_x[0] = position_block_lx - r_moliere/cos(angle_lx);
  inner_proj_x[2] = position_block_lx + r_moliere/cos(angle_lx);
  double outer_proj_x[3];
  outer_proj_x[1] = position_block_lx + block_depth*tan(angle_lx);
  outer_proj_x[0] = outer_proj_x[1] - r_moliere/cos(angle_lx);
  outer_proj_x[2] = outer_proj_x[1] + r_moliere/cos(angle_lx);
  double max_lx = GetLarger(inner_proj_x[2],outer_proj_x[2]);
  double min_lx = GetSmaller(inner_proj_x[0],outer_proj_x[0]);
  max_lx = max_lx+62.;
  min_lx = min_lx-62.;
  int add_plus = max_lx/124;
  int add_minus = min_lx/124;
  if(add_plus!=0){
    for(int i=1;i<=add_plus;i++){
      if(ChExist(blockch+i)){
	trk_ass_cids.push_back(blockch+i);
      }
    }
  }
  if(add_minus!=0){
    for(int i=1;i<=-add_minus;i++){
      if(ChExist(blockch-i)){
	trk_ass_cids.push_back(blockch-i);
      }
    }
  }
}

TVector2 CalcCrossPoint(TVector2 a, TVector2 b, TVector2 p){

  double s = p.Y()/p.X();
  double q = (b.Y()-a.Y())/(b.X()-a.X());
  double cr_r = (a.Y()-q*a.X())/(s-q);
  TVector2 cr(cr_r,s*cr_r);
  return cr;
}

double CalibFunction(double x){

  double t = x*0.01;
  return (-92.9*t*t*t*t +304.*t*t*t -294.*t*t +38.*t +102.42)/62.256;

}

double E16ANA_EIDEfficiency::CalcCalibPar(double proj_y, int blockch, double& dist){

  int bly = blockch/10;
  TVector2 bpos_pmt(bpos_pmt_r[bly],bpos_pmt_y[bly]);
  TVector2 bpos_cut(bpos_cut_r[bly],bpos_cut_y[bly]);
  TVector2 proj(plane_r[bly],proj_y);
  TVector2 cs = CalcCrossPoint(bpos_pmt,bpos_cut,proj);
  dist = sqrt( (cs.X()-bpos_pmt.X())*(cs.X()-bpos_pmt.X()) + (cs.Y()-bpos_pmt.Y())*(cs.Y()-bpos_pmt.Y()) );
  return 1./CalibFunction(dist);
}

double CalibFunction(double bx, double by){

  TF1 *fc = new TF1("fc","[0]+ ( -39.56E-4*x*x + 41.71E-6*fabs(x)*x*x + 1E-8*x*x*x*x )*[1]",-65.,65.);
  fc->FixParameter(0,1.857 -1.143*by*0.01);
  fc->FixParameter(1,0.2755-0.334*by*0.01);

  return fc->Eval(bx);

}

double E16ANA_EIDEfficiency::CalcCalibPar(double lx, double ly, double theta_lx, int blockch, double &tbx, double& tby){

  double block_pitch_x = 124.;
  tbx = 0; tby = 0;

  // local coordinate (in module) --> block coordinale
  // y
  int chy = blockch/10;
  TVector2 bpos_pmt(bpos_pmt_r[chy],bpos_pmt_y[chy]);
  TVector2 bpos_cut(bpos_cut_r[chy],bpos_cut_y[chy]);
  TVector2 proj(plane_r[chy],ly);
  TVector2 cs = CalcCrossPoint(bpos_pmt,bpos_cut,proj);
  double by = sqrt( (cs.X()-bpos_pmt.X())*(cs.X()-bpos_pmt.X()) + (cs.Y()-bpos_pmt.Y())*(cs.Y()-bpos_pmt.Y()) );
  tby = by;
  if(by>75.){return 1.;}
  if(by<10.){return -10000.;}
  // x
  double lxd = lx + 135./2.*tan(theta_lx);
  int chx;
  double bx;
  if(chy==2||chy==3){
    chx = (int)((lxd-(-4.5*block_pitch_x))/block_pitch_x) - 1;
    if(chx<0||chx>6){std::cout<<"out of region"<<std::endl;return -10000.;}
    bx = lxd - ((double)chx-3.)*block_pitch_x;
  }
  else{
    chx = (int)((lxd-(-4.*block_pitch_x))/block_pitch_x) - 1;
    if(chx<0||chx>5){std::cout<<"out of region"<<std::endl;return -10000.;}
    bx = lxd - ((double)chx-2.5)*block_pitch_x;
  }
  bx = bx*cos(theta_lx);
  bx = (-theta_lx/fabs(theta_lx))*bx;
  bx = bx/cos(theta_lx);
  tbx = bx;

  return 1./CalibFunction(bx, by);
}

double E16ANA_EIDEfficiency::Get2DHistSquareIntegral(TH2F* h2d, TH2F* h2dcopy, double originx, double originy, double sigmax, double sigmay){

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
      if(i>=x0&&i<=x1&&j>=y0&&j<=y1){
  	double content = h2d->GetBinContent(i,j);
  	h2dcopy->SetBinContent(i,j,content);
      }
    }
  }

  return h2d->Integral(x0,x1,y0,y1);

}

double E16ANA_EIDEfficiency::Get2DHistSquareIntegral(TH2F* h2d, double originx, double originy, double sigmax, double sigmay){

  TH2F* h2dcopy;
  h2dcopy  = (TH2F*)h2d->Clone();

  return Get2DHistSquareIntegral(h2d,h2dcopy,originx,originy,sigmax,sigmay);

}

void E16ANA_EIDEfficiency::Loop()
{
//   In a ROOT session, you can do:
//      root> .L E16ANA_EIDEfficiency.C
//      root> E16ANA_EIDEfficiency t
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

void E16ANA_EIDEfficiency::ResidualandEfficiency(int runoption, int maxevent, char* out_file_name, char* out_root_name, double hbdthr, int hbdclthr)
{
   // std::ofstream wfout[5];
   // for(int i=0;i<5;i++){
   //   std::string mod = to_string(i+103);
   //   std::string wfoutname = "wf" + mod + ".txt";
   //   wfout[i].open(wfoutname);
   // }
   if (fChain == 0) return;

   // std::ofstream hbdwf("hbdwf.txt");//240317

   TFile *fouthist = new TFile(out_root_name,"recreate");
   auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
   // std::ofstream evspout[5];
   // std::ofstream evspdout[5];
   // for(int i=0;i<5;i++){
   //   std::string mod = to_string(i+103);
   //   // std::string evspoutname = "evsp" + mod + ".txt";
   //   std::string evspoutname = "tsvsl" + mod + ".txt";
   //   std::string evspdoutname = "tsvsld" + mod + ".txt";
   //   evspout[i].open(evspoutname);
   //   evspdout[i].open(evspdoutname);
   // }
   TGraph2D *g = new TGraph2D();
   g->SetName("g");
   g->SetTitle("g");
   int ig = 0;

   int bene = 0;
   double enepar[4] = {1.,40.,80.,1.};
   int ienepar[4] = {1,40,80,1};
   // double enepar[4] = {1.,40.,80.,198.};
   // int ienepar[4] = {1,40,80,200};

   bool gaincalib = false;
   bool fwdonly = false;
   bool hbdass_in_dst1 = false;
   bool new_cluster_method = true;//221006
   bool w_calib_pos_dep = true;//calib parameter w/ position dependence
   if(runoption==0){w_calib_pos_dep=false;}
   int w_ssd_timing_match = 0;// 0: not required, 1: required but return maxadc, 2: required
   int searchx = 100;//for lg cluster
   int searchy = 100;//for lg cluster
   // int searchx = 100;//for lg cluster
   // int searchy = 60;//for lg cluster
   // int searchx = 100;//for lg cluster
   // int searchy = 80;//for lg cluster
   int mixevent = 50;
   // double lgthr[4] = {20.,50.,80.,100.};
   double lgthr[4] = {10.,20.,50.,80.};
   double lgresthr = 50.;
   if(runoption==0){lgresthr = 10.;}
   if(runoption==3){lgresthr = 10.;}
   // if(runoption==1){lgresthr = 10.;}
   double lgcon[4] = {240.,250.,260.,270.};
   // double hbdthr = 7.;
   // if(runoption==3){hbdthr = 4.;}
   // if(runoption==4){hbdthr = 0.;}
   // int hbdclthr = 1;
   double ssdoffset = 51.;
   // double ssdregion = 11.;
   double ssdregion = 6.;
   if(runoption==3){ssdregion = 60.;}
   if(runoption==4){ssdregion = 60.;}
   if(runoption==0){ssdregion = 60.;}
   // if(runoption==3){ssdregion = 11.;}
   // if(runoption==4){ssdregion = 11.;}

   const int ndet=2;
   char det[ndet][20] = {"HBD","LGHit"};
   const int ntrktype=6;
   char trktype[ntrktype][20] = {"w/o_HBD&LG_kgs","w/HBD_kgs","w/LG_kgs","w/HBDLG_kgs","w/HBD_kh","w/HBDf&m_kh"};
   int eptype = 4;
   int roughbin[ndet] = {200,50};
   // if(runoption==0){
   //   roughbin[0] = 400;
   //   roughbin[1] = 100;
   // }
   double originx[5][ndet];
   double originy[5][ndet];
   double widthx[5][ndet];
   double widthy[5][ndet];
   for(int i=0;i<5;i++){
     originx[i][0]=0.;
     originy[i][0]=0.;
     widthx[i][0]=25.;
     widthy[i][0]=25.;
     if(runoption==3){widthx[i][0]=35.;widthy[i][0]=35.;}
     // if(runoption==3){widthx[i][0]=20.;widthy[i][0]=20.;}//240317
     if(runoption==4){widthx[i][0]=35.;widthy[i][0]=35.;}
     originx[i][1]=0.;
     originy[i][1]=0.;
     // widthx[i][1]=150.;//220720
     widthx[i][1]=100.;
     widthy[i][1]=100.;
   }
   if(runoption==1){
     //HBD
     originx[0][0]= 6.0;//103
     originy[0][0]=-1.1;
     originx[1][0]= 4.8;//104
     originy[1][0]= 0. ;
     originx[3][0]=-5.7;//106
     originy[3][0]=-1.6;
     originx[4][0]= 2.2;//107
     originy[4][0]= 1.3;
     //LG
     // originx[0][1]=- 52.;//103
     // originx[1][1]=-100.;//104
     // originx[3][1]=  40.;//106
     // originx[4][1]=  21.;//107
   }
   if(runoption==3){
     //HBD
     originx[1][0]=  5.;//104
     originx[3][0]=-10.;//106
   }
   if(runoption==0){
     //HBD
     originx[0][0]=  6.0;//103
     widthx[0][0]=15.;
     originy[0][0]=- 2.8;
     widthy[0][0]=15.;
     originx[1][0]=- 3.4;//104
     widthx[1][0]=15.;
     originy[1][0]=  0. ;
     widthy[1][0]=15.;
     originx[3][0]=-11.4;//106
     widthx[3][0]=15.;
     originy[3][0]=- 2.2;
     widthy[3][0]=15.;
     originx[4][0]=  4.3;//107
     widthx[4][0]=25.;
     originy[4][0]=- 0.6;
     widthy[4][0]=20.;
     for(int i=0;i<5;i++){
       widthx[i][0] = 20.;
       widthy[i][0] = 15.;
       // originx[i][0] += 20.;
     }
   }

   int ex_2d[ndet] = {50,200};
   double fitregion[ndet] = {30,100};// half width
   int tbinw[ndet] = {800,200};
   int tbin0[ndet] = {-150,0};
   int tbin[ndet] = {600,200};

   TH1F *hnt[5][ntrktype];
   TH1F *hn[5][ndet][ntrktype];
   TH1F *hnd[5][ndet][ntrktype];
   const int nopt=4;
   char opt[nopt][25] = {"nocut","resy(x)cut","plus_charge","minus_charge"};
   TH1F *haresx[5][nopt][ndet][ntrktype];
   TH1F *haresy[5][nopt][ndet][ntrktype];
   TH1F *haresxd[5][nopt][ndet][ntrktype];
   TH1F *haresyd[5][nopt][ndet][ntrktype];
   int ntrack[5][ntrktype];
   int ntrackass[5][ndet][ntrktype];
   TH1F* hntrackass[5][ndet][ntrktype];
   TH1F* hntrackassd[5][ndet][ntrktype];
   for(int i=0;i<5;i++){
     for(int j=0;j<ntrktype;j++){
       ntrack[i][j]=0;
       for(int k=0;k<ndet;k++){
       ntrackass[i][k][j]=0;
       hntrackass[i][k][j] = new TH1F(Form("hntrackass%d%d%d",i,k,j),Form("ntrack_%sassoc_mod%d_%s",det[k],103+i,trktype[j]),10,0,10);
       hntrackassd[i][k][j] = new TH1F(Form("hntrackassd%d%d%d",i,k,j),Form("ntrack_%sassoc_mix_mod%d_%s",det[k],103+i,trktype[j]),10,0,10);
       }
     }
   }
   TH2F *hares[5][ndet][ntrktype];
   TH2F *haresd[5][ndet][ntrktype];
   TH1F *ht[ndet][ntrktype][5];
   TH1F *htd[ndet][ntrktype][5];
   TH1F *haresxd_hmix[5][nopt][ndet];//+HBDmix
   TH1F *haresyd_hmix[5][nopt][ndet];//+HBDmix
   for(int l=0;l<ntrktype;l++){
     for(int k=0;k<ndet;k++){
       for(int i=0;i<5;i++){
	 if(k==0){hnt[i][l] = new TH1F(Form("hnt%d%d",i,l),Form("ntracks_in_event_mod%d_%s",103+i,trktype[l]),20,0,20);}
	 hn[i][k][l] = new TH1F(Form("hn%d%d%d",i,k,l),Form("%s_multiplicity_mod%d_%s",det[k],103+i,trktype[l]),50,0,50);
	 hnd[i][k][l] = new TH1F(Form("hnd%d%d%d",i,k,l),Form("%s_multiplicity_dummy_mod%d_%s",det[k],103+i,trktype[l]),50,0,50);
	 for(int j=0;j<nopt;j++){
	   haresx[i][j][k][l] = new TH1F(Form("haresx%d%d%d%d",i,j,k,l),Form("%s_allhit_residual_x_mod%d_%s_%s",det[k],103+i,opt[j],trktype[l]),roughbin[k],-800,800);
	   haresy[i][j][k][l] = new TH1F(Form("haresy%d%d%d%d",i,j,k,l),Form("%s_allhit_residual_y_mod%d_%s_%s",det[k],103+i,opt[j],trktype[l]),roughbin[k],-800,800);
	   haresxd[i][j][k][l] = new TH1F(Form("haresxd%d%d%d%d",i,j,k,l),Form("%s_allhit_residual_x_dummy_mod%d_%s_%s",det[k],103+i,opt[j],trktype[l]),roughbin[k],-800,800);
	   haresyd[i][j][k][l] = new TH1F(Form("haresyd%d%d%d%d",i,j,k,l),Form("%s_allhit_residual_y_dummy_mod%d_%s_%s",det[k],103+i,opt[j],trktype[l]),roughbin[k],-800,800);
	   if(l==0){
	     haresxd_hmix[i][j][k] = new TH1F(Form("haresxd_hmix%d%d%d",i,j,k),Form("%s_allhit_residual_x_dummy_mod%d_%s_hmix",det[k],103+i,opt[j]),roughbin[k],-800,800);
	     haresyd_hmix[i][j][k] = new TH1F(Form("haresyd_hmix%d%d%d",i,j,k),Form("%s_allhit_residual_y_dummy_mod%d_%s_hmix",det[k],103+i,opt[j]),roughbin[k],-800,800);
	   }
	 }
	 hares[i][k][l] = new TH2F(Form("hares%d%d%d",i,k,l),Form("%s_allhit_residual_mod%d_%s",det[k],103+i,trktype[l]),roughbin[k],-800,800,roughbin[k],-800,800);
	 haresd[i][k][l] = new TH2F(Form("haresd%d%d%d",i,k,l),Form("%s_allhit_residual_dummy_mod%d_%s",det[k],103+i,trktype[l]),roughbin[k],-800,800,roughbin[k],-800,800);
	 ht[k][l][i] = new TH1F(Form("ht%d%d%d",k,l,i),Form("%s_fastest_time_mod%d_%s",det[k],103+i,trktype[l]),tbinw[k],tbin0[k],tbin[k]);
	 htd[k][l][i] = new TH1F(Form("htd%d%d%d",k,l,i),Form("%s_fastest_time_dummy_mod%d_%s",det[k],103+i,trktype[l]),tbinw[k],tbin0[k],tbin[k]);
       }
     }
   }
   TH2F* hbdhitmap[5];
   TH1F* hbdadcwot[5];
   TH1F* hbdadcwotd[5];
   TH1F* hbdadcwt[5];
   TH1F* hbdadcwtd[5];
   TH1F* hexp[5];
   TH1F* hadc[5];
   TH1F* hadcd[5];
   TH2F* hevsp[5];
   TH2F* hevspd[5];
   TH2F* hevspr[5];
   TH2F* hevsprd[5];
   TH2F* hevspe[5][42];
   TH2F* hevsped[5][42];
   TH2F* heovpvsp[5];
   TH2F* heovpvspd[5];
   TH1F* hedivp[4][5];
   TH1F* hedivpd[4][5];
   TH1F* hedivpe[5][42];
   TH1F* hedivped[5][42];
   TH1F* hassp[4][5];
   TH1F* hasspd[4][5];
   TH1F* hasse[4][5];
   TH1F* hassed[4][5];
   TH1F* hesubp[4][5];
   TH1F* hesubpd[4][5];
   TH1F* hnclscand[5];//221215
   TH1F* hnlghitwtc[5];//clutser
   TH1F* hnlghitwtcd[5];//clutser
   TH2F* hhitmapc[4][5];//clutser
   TH2F* hhitmapcd[4][5];//clutser
   TH2F* htsvslc[5];//clutser
   TH2F* htsvslcd[5];//clutser
   TH1F* htsslc[5];//clutser
   TH1F* htsslcd[5];//clutser
   TH1F* htdiffc[5];//clutser
   TH1F* htdiffcd[5];//clutser
   TH1F* hcogxc[5];//clutser
   TH1F* hcogxcd[5];//clutser
   TH1F* hcogyc[5];//clutser
   TH1F* hcogycd[5];//clutser
   TH1F* hcogxcl[5][4];//clutser
   TH1F* hcogycl[5][4];//clutser
   TH2F* hthvsp[5];
   TH2F* hthvspd[5];
   TH1F* htheta[5][3];
   TH2F* hevsprd_hmix[5];//+HBDmix
   TH2F* heovpvspd_hmix[5];//+HBDmix
   TH1F* hedivpd_hmix[4][5];//+HBDmix
   TH1F* hasspd_hmix[4][5];//+HBDmix
   TH1F* hassed_hmix[4][5];//+HBDmix
   TH1F* hnlghitwtcd_hmix[5];//clutser//+HBDmix
   TH2F* hhitmapcd_hmix[4][5];//clutser//+HBDmix
   TH1F* htdiffcd_hmix[5];//clutser//+HBDmix
   TH1F* hcogxcd_hmix[5];//clutser//+HBDmix
   TH1F* hcogycd_hmix[5];//clutser//+HBDmix
   TH1F* heffe[5][42];
   TH1F* hmome[5][42];
   TH1F* hange[5][42];
   TH1F* heffem[5][7];
   TH2F* heffemvstrg[5][7];
   TH1F* trkmom[6];
   TH1F* hmomwlg[6];
   TH1F* hmomwolg[6];
   TH1F* hmomwtrg[6];
   TH1F* hmomwotrg[6];
   TH1I* hresxtrg[6];
   TH1I* hresytrg[6];
   TH2F* hbdadcvsmom[6];
   TH2F* ssdadcvsmom[6][3];
   TH2F* ssdadcvsmom_pil[6][3];
   TH2F* ssdadcvsmom_pl[6][3];
   for(int i=0;i<6;i++){
     trkmom[i] = new TH1F(Form("trkmom%d",i),Form("mom_w/HBDHit_mod%d",103+i),50,0,5);
     hmomwlg[i] = new TH1F(Form("hmomwlg%d",i),Form("mom_w/LGHit_mod%d",103+i),50,0,5);
     hmomwolg[i] = new TH1F(Form("hmomwolg%d",i),Form("mom_w/oLGHit_mod%d",103+i),50,0,5);
     hmomwtrg[i] = new TH1F(Form("hmomwtrg%d",i),Form("mom_w/TrgBias_mod%d",103+i),50,0,5);
     hmomwotrg[i] = new TH1F(Form("hmomwotrg%d",i),Form("mom_w/oTrgBias_mod%d",103+i),50,0,5);
     hresxtrg[i] = new TH1I(Form("hresxtrg%d",i),Form("Residualx_bw_HBD&LG_trg_mod%d",103+i),15,-7.5,7.5);
     hresytrg[i] = new TH1I(Form("hresytrg%d",i),Form("Residualy_bw_HBD&LG_trg_mod%d",103+i),15,-7.5,7.5);
     hbdadcvsmom[i] = new TH2F(Form("hbdadcvsmom%d",i),Form("mom_vs_HBDadc_mod%d",103+i),50,0,5,100,0,4000);
     for(int j=0;j<3;j++){
       int jd = j+((j+2)/3);
       ssdadcvsmom[i][j] = new TH2F(Form("ssdadcvsmom%d%d",i,j),Form("mom_vs_SSDadc_%s_mod%d",opt[jd],103+i),60,0,3,100,0,1000);
       ssdadcvsmom_pil[i][j] = new TH2F(Form("ssdadcvsmom_pil%d%d",i,j),Form("mom_vs_SSDadc_%s_PiLike_mod%d",opt[jd],103+i),60,0,3,100,0,1000);
       ssdadcvsmom_pl[i][j] = new TH2F(Form("ssdadcvsmom_pl%d%d",i,j),Form("mom_vs_SSDadc_%s_Protonlike_mod%d",opt[jd],103+i),60,0,3,100,0,1000);
     }
     if(i==2){
       trkmom[i]->SetTitle("mom_w/HBDHit_modR");
       hmomwlg[i]->SetTitle("mom_w/LGHit_modR");
       hmomwolg[i]->SetTitle("mom_w/oLGHit_modR");
       hmomwtrg[i]->SetTitle("mom_w/TrgBias_modR");
       hmomwotrg[i]->SetTitle("mom_w/oTrgBias_modR");
       hresxtrg[i]->SetTitle("Residualx_bw_HBD&LG_trg_modR");
       hresytrg[i]->SetTitle("Residualy_bw_HBD&LG_trg_modR");
       hbdadcvsmom[i]->SetTitle("mom_vs_HBDadc_modR");
       for(int j=0;j<3;j++){
	 int jd = j+((j+2)/3);
	 ssdadcvsmom[i][j]->SetTitle(Form("mom_vs_SSDadc_%s_modR",opt[jd]));
	 ssdadcvsmom_pil[i][j]->SetTitle(Form("mom_vs_SSDadc_%s_PiLike_modR",opt[jd]));
	 ssdadcvsmom_pl[i][j]->SetTitle(Form("mom_vs_SSDadc_%s_ProtonLike_modR",opt[jd]));
       }
     }
     if(i==5){
       trkmom[i]->SetTitle("mom_w/HBDHit_modL");
       hmomwlg[i]->SetTitle("mom_w/LGHit_modL");
       hmomwolg[i]->SetTitle("mom_w/oLGHit_modL");
       hmomwtrg[i]->SetTitle("mom_w/TrgBias_modL");
       hmomwotrg[i]->SetTitle("mom_w/oTrgBias_modL");
       hresxtrg[i]->SetTitle("Residualx_bw_HBD&LG_trg_modL");
       hresytrg[i]->SetTitle("Residualy_bw_HBD&LG_trg_modL");
       hbdadcvsmom[i]->SetTitle("mom_vs_HBDadc_modL");
       for(int j=0;j<3;j++){
	 int jd = j+((j+2)/3);
	 ssdadcvsmom[i][j]->SetTitle(Form("mom_vs_SSDadc_%s_modL",opt[jd]));
	 ssdadcvsmom_pil[i][j]->SetTitle(Form("mom_vs_SSDadc_%s_PiLike_modL",opt[jd]));
	 ssdadcvsmom_pl[i][j]->SetTitle(Form("mom_vs_SSDadc_%s_ProtonLike_modL",opt[jd]));
       }
     }
   }
   for(int i=0;i<5;i++){
     hbdhitmap[i] = new TH2F(Form("hbdhitmap%d",i),Form("HBDhitmap_mod%d_Fore",103+i),50,-300,300,50,-300,300);
     hbdadcwot[i] = new TH1F(Form("hbdadcwot%d",i),Form("HBDadc_TrackAssoc_wotrg_mod%d_Fore",103+i),100,0,20);
     hbdadcwotd[i] = new TH1F(Form("hbdadcwotd%d",i),Form("HBDadc_TrackAssoc_wotrg_mod%d_Mix",103+i),100,0,20);
     hbdadcwt[i] = new TH1F(Form("hbdadcwt%d",i),Form("HBDadc_TrackAssoc_wtrg_mod%d_Fore",103+i),100,0,20);
     hbdadcwtd[i] = new TH1F(Form("hbdadcwtd%d",i),Form("HBDadc_TrackAssoc_wtrg_mod%d_Mix",103+i),100,0,20);
     hexp[i] = new TH1F(Form("hexp%d",i),Form("expected_LG_AdcSum/Mom_TrackAssoc_mod%d",103+i),32,0,800/ienepar[bene]);
     hadc[i] = new TH1F(Form("hadc%d",i),Form("LG_AdcSum_Fore_TrackAssoc_mod%d",103+i),128,0,800/ienepar[bene]);
     hadcd[i] = new TH1F(Form("hadcd%d",i),Form("LG_AdcSum_Mix_TrackAssoc_mod%d",103+i),128,0,800/ienepar[bene]);
     hevsp[i] = new TH2F(Form("hevsp%d",i),Form("LG_AdcSumVsMom_Fore_TrackAssoc_mod%d",103+i),25,0,1.5,40,0,240/ienepar[bene]);
     hevspd[i] = new TH2F(Form("hevspd%d",i),Form("LG_AdcSumVsMom_Mix_TrackAssoc_mod%d",103+i),25,0,1.5,40,0,240/ienepar[bene]);
     hevspr[i] = new TH2F(Form("hevspr%d",i),Form("LG_AdcSumVsMom_Fore_TrackAssoc_mod%d",103+i),25,0,3,50,0,600/ienepar[bene]);
     hevsprd[i] = new TH2F(Form("hevsprd%d",i),Form("LG_AdcSumVsMom_Mix_TrackAssoc_mod%d",103+i),25,0,3,50,0,600/ienepar[bene]);
     // hevspr[i] = new TH2F(Form("hevspr%d",i),Form("LG_AdcSumVsMom_Fore_TrackAssoc_mod%d",103+i),50,0,3,200,0,600/ienepar[bene]);
     // hevsprd[i] = new TH2F(Form("hevsprd%d",i),Form("LG_AdcSumVsMom_Mix_TrackAssoc_mod%d",103+i),50,0,3,200,0,600/ienepar[bene]);
     for(int j=0;j<42;j++){
       hevspe[i][j] = new TH2F(Form("hevspe%d%d",i,j),Form("LG_AdcSumVsMom_Fore_TrackAssoc_mod%d_blk%d",103+i,(int)j/7*10+j%7),25,0,3,50,0,600/ienepar[bene]);
       hevsped[i][j] = new TH2F(Form("hevsped%d%d",i,j),Form("LG_AdcSumVsMom_Mix_TrackAssoc_mod%d_blk%d",103+i,(int)j/7*10+j%7),25,0,3,50,0,600/ienepar[bene]);
       hedivpe[i][j] = new TH1F(Form("hedivpe%d%d",i,j),Form("LG_AdcSum/Mom_Fore_TrackAssoc_%1.0fmV_mod%d_blk%d",lgthr[0],103+i,(int)j/7*10+j%7),16,0,800/ienepar[bene]);
       hedivped[i][j] = new TH1F(Form("hedivped%d%d",i,j),Form("LG_AdcSum/Mom_Mix_TrackAssoc_%1.0fmV_mod%d_blk%d",lgthr[0],103+i,(int)j/7*10+j%7),16,0,800/ienepar[bene]);
       heffe[i][j] = new TH1F(Form("heffe%d%d",i,j),Form("LG_Efficiency_TrackAssoc_%1.0fmV_mod%d_blk%d",lgthr[0],103+i,(int)j/7*10+j%7),3,0,3);
       hmome[i][j] = new TH1F(Form("hmome%d%d",i,j),Form("LG_Mom_TrackAssoc_%1.0fmV_mod%d_blk%d",lgthr[0],103+i,(int)j/7*10+j%7),40,0,5);
       hange[i][j] = new TH1F(Form("hange%d%d",i,j),Form("LG_IncidentAngleX_TrackAssoc_%1.0fmV_mod%d_blk%d",lgthr[0],103+i,(int)j/7*10+j%7),40,-40,40);
     }
     for(int j=0;j<7;j++){
       heffem[i][j] = new TH1F(Form("heffem%d%d",i,j),Form("LG_Efficiency_TrackAssoc_mod%d_blk%d",103+i,j),3,0,3);
       heffemvstrg[i][j] = new TH2F(Form("heffemvstrg%d%d",i,j),Form("TrgBias_vs_LG_Efficiency_TrackAssoc_mod%d_blk%d",103+i,j),3,0,3,3,0,3);
     }
     heovpvsp[i] = new TH2F(Form("heovpvsp%d",i),Form("LG_E/pVsMom_Fore_TrackAssoc_mod%d",103+i),25,0,3,50,0,600/ienepar[bene]);
     heovpvspd[i] = new TH2F(Form("heovpovspd%d",i),Form("LG_E/pVsMom_Mix_TrackAssoc_mod%d",103+i),25,0,3,50,0,600/ienepar[bene]);
     for(int j=0;j<4;j++){
       hedivp[j][i] = new TH1F(Form("hedivp%d%d",j,i),Form("LG_AdcSum/Mom_Fore_TrackAssoc_%1.0fmV_mod%d",lgthr[j],103+i),32,0,800/ienepar[bene]);
       hedivpd[j][i] = new TH1F(Form("hedivpd%d%d",j,i),Form("LG_AdcSum/Mom_Mix_TrackAssoc_%1.0fmV_mod%d",lgthr[j],103+i),32,0,800/ienepar[bene]);
       hassp[j][i] = new TH1F(Form("hassp%d%d",j,i),Form("Mom_Fore_TrackAssoc_%1.0fmV_mod%d",lgthr[j],103+i),50,0,5);
       hasspd[j][i] = new TH1F(Form("hasspd%d%d",j,i),Form("Mom_Mix_TrackAssoc_%1.0fmV_mod%d",lgthr[j],103+i),50,0,5);
       hasse[j][i] = new TH1F(Form("hasse%d%d",j,i),Form("AdcSum_Fore_TrackAssoc_%1.0fmV_mod%d",lgthr[j],103+i),128,0,400/ienepar[bene]);
       hassed[j][i] = new TH1F(Form("hassed%d%d",j,i),Form("AdcSum_Mix_TrackAssoc_%1.0fmV_mod%d",lgthr[j],103+i),128,0,400/ienepar[bene]);

       hesubp[j][i] = new TH1F(Form("hesubp%d%d",j,i),Form("LG_AdcSum-%1.0f*Mom_Fore_TrackAssoc_mod%d",lgcon[j],103+i),16,-200,200);
       hesubpd[j][i] = new TH1F(Form("hesubpd%d%d",j,i),Form("LG_AdcSum-%1.0f*Mom_Mix_TrackAssoc_mod%d",lgcon[j],103+i),16,-200,200);
       hedivpd_hmix[j][i] = new TH1F(Form("hedivpd_hmix%d%d",j,i),Form("LG_AdcSum/Mom_Mix_TrackAssoc_%1.0fmV_mod%d_hmix",lgthr[j],103+i),32,0,800/ienepar[bene]);
       hasspd_hmix[j][i] = new TH1F(Form("hasspd_hmix%d%d",j,i),Form("Mom_Mix_TrackAssoc_%1.0fmV_mod%d_hmix",lgthr[j],103+i),50,0,5);
       hassed_hmix[j][i] = new TH1F(Form("hassed_hmix%d%d",j,i),Form("AdcSum_Mix_TrackAssoc_%1.0fmV_mod%d_hmix",lgthr[j],103+i),128,0,400/ienepar[bene]);
     }
     hnclscand[i] = new TH1F(Form("hnclscand%d",i),Form("N_ClusterCands_TrackAssoc_Fore_mod%d",103+i),10,0,10);
     hnlghitwtc[i] = new TH1F(Form("hnlghitwtc%d",i),Form("N_LGHits_TrackAssoc_inCluster_Fore_mod%d",103+i),10,0,10);
     hnlghitwtcd[i] = new TH1F(Form("hnlghitwtcd%d",i),Form("N_LGHits_TrackAssoc_inCluster_Mix_mod%d",103+i),10,0,10);
     for(int j=0;j<4;j++){
       hhitmapc[j][i] = new TH2F(Form("hhitmapc%d%d",j,i),Form("LGhitmap_mod%d_E/pcut%d_Fore",103+i,j),7,-0.5,6.5,6,-0.5,5.5);
       hhitmapcd[j][i] = new TH2F(Form("hhitmapcd%d%d",j,i),Form("LGhitmap_mod%d_E/pcut%d_Mix",103+i,j),7,-0.5,6.5,6,-0.5,5.5);
       hhitmapcd_hmix[j][i] = new TH2F(Form("hhitmapcd_hmix%d%d",j,i),Form("LGhitmap_mod%d_E/pcut%d_Mix_hmix",103+i,j),7,-0.5,6.5,6,-0.5,5.5);
     }
     htsvslc[i] = new TH2F(Form("htsvslc%d",i),Form("Timing_SSDvsLG_TrackAssoc_inCluster_Fore_mod%d",103+i),50,50,150,50,-10,90);
     htsvslcd[i] = new TH2F(Form("htsvslcd%d",i),Form("Timing_SSDvsLG_TrackAssoc_inCluster_Mix_mod%d",103+i),50,50,150,50,-10,90);
     htsslc[i] = new TH1F(Form("htsslc%d",i),Form("Timing_SSD-LG_TrackAssoc_inCluster_Fore_mod%d",103+i),100,-100,100);
     htsslcd[i] = new TH1F(Form("htsslcd%d",i),Form("Timing_SSD-LG_TrackAssoc_inCluster_Mix_mod%d",103+i),100,-100,100);
     htdiffc[i] = new TH1F(Form("htdiffc%d",i),Form("MaxTimeDifference_TrackAssoc_inCluster_Fore_mod%d",103+i),100,0,20);
     htdiffcd[i] = new TH1F(Form("htdiffcd%d",i),Form("MaxTimeDifference_TrackAssoc_inCluster_Mix_mod%d",103+i),100,0,20);
     hcogxc[i] = new TH1F(Form("hcogxc%d",i),Form("COGx_residual_TrackAssoc_inCluster_Fore_mod%d",103+i),100,-150,150);
     hcogxcd[i] = new TH1F(Form("hcogxcd%d",i),Form("COGx_residual_TrackAssoc_inCluster_Mix_mod%d",103+i),100,-150,150);
     hcogyc[i] = new TH1F(Form("hcogyc%d",i),Form("COGy_residual_TrackAssoc_inCluster_Fore_mod%d",103+i),100,-150,150);
     hcogycd[i] = new TH1F(Form("hcogycd%d",i),Form("COGy_residual_TrackAssoc_inCluster_Mix_mod%d",103+i),100,-150,150);
     for(int j=0;j<4;j++){
       hcogxcl[i][j] = new TH1F(Form("hcogxcl%d%d",i,j),Form("COGx_residual_TrackAssoc_inCluster_mod%d_l%d",103+i,j),100,-150,150);
       hcogycl[i][j] = new TH1F(Form("hcogycl%d%d",i,j),Form("COGy_residual_TrackAssoc_inCluster_mod%d_l%d",103+i,j),100,-150,150);
     }
     hthvsp[i] = new TH2F(Form("hthvsp%d",i),Form("theta(deg)_vs_mom_TrackAssoc_Fore_mod%d",103+i),50,0,5,80,-40,40);
     hthvspd[i] = new TH2F(Form("hthvspd%d",i),Form("theta(deg)_vs_mom_TrackAssoc_Mix_mod%d",103+i),50,0,5,80,-40,40);
     for(int j=0;j<3;j++){
       htheta[i][j] = new TH1F(Form("htheta%d%d",i,j),Form("theta(deg)_TrackAssoc_Fore_mod%d_over%dGeV/c",103+i,j),40,-40,40);
     }
     hevsprd_hmix[i] = new TH2F(Form("hevsprd_hmix%d",i),Form("LG_AdcSumVsMom_Mix_TrackAssoc_mod%d_hmix",103+i),25,0,3,50,0,600/ienepar[bene]);
     // hevsprd_hmix[i] = new TH2F(Form("hevsprd_hmix%d",i),Form("LG_AdcSumVsMom_Mix_TrackAssoc_mod%d_hmix",103+i),50,0,3,100,0,600/ienepar[bene]);
     heovpvspd_hmix[i] = new TH2F(Form("heovpovspd_hmix%d",i),Form("LG_E/pVsMom_Mix_TrackAssoc_mod%d_hmix",103+i),25,0,3,50,0,600/ienepar[bene]);
     hnlghitwtcd_hmix[i] = new TH1F(Form("hnlghitwtcd_hmix%d",i),Form("N_LGHits_TrackAssoc_inCluster_Mix_mod%d_hmix",103+i),10,0,10);
     htdiffcd_hmix[i] = new TH1F(Form("htdiffcd_hmix%d",i),Form("MaxTimeDifference_TrackAssoc_inCluster_Mix_mod%d_hmix",103+i),100,0,20);
     hcogxcd_hmix[i] = new TH1F(Form("hcogxcd_hmix%d",i),Form("COGx_residual_TrackAssoc_inCluster_Mix_mod%d_hmix",103+i),100,-150,150);
     hcogycd_hmix[i] = new TH1F(Form("hcogycd_hmix%d",i),Form("COGy_residual_TrackAssoc_inCluster_Mix_mod%d_hmix",103+i),100,-150,150);
   }
   TH1F* hlgmulti = new TH1F("hlgmulti","lg_event_multiplicity",100,0,100);
   TH1F* htrgmulti = new TH1F("htrgmulti","lg_trg_event_multiplicity",100,0,100);
   TH1F* hsingle = new TH1F("hsingle","single_ratio",60,0,1.2);


   //for mixing
   std::vector<std::vector<hitset>> hbdmixhits[5][ntrktype];
   std::vector<std::vector<hitset>> lgmixhits[5][ntrktype];

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
     // int ntmp = 0;
     // for(int ihbd=0;ihbd<track_hbd_multiplicity->at(0);ihbd++){
     //   if(track_hbd_allhit_adc->at(0).at(ihbd)<hbdthr||track_hbd_allhit_size->at(0).at(ihbd)<hbdclthr) continue;
     //   ntmp++;
     // }
     int ntrk[5][ntrktype]={0};
     bool alfill[2][5][ntrktype]={false};//for mixing
     std::vector<hitset> hbdhits[5][ntrktype];//for mixing
     std::vector<hitset> lghits[5][ntrktype];//for mixing
     std::vector<trackset> tracksets[ntrktype];//kill dup
     std::vector<trackset> tracksets_hmix;//kill dup

     int ntrk_acc = 0;
     for(int itrack=0;itrack<n_tracks;itrack++){//track loop

       if (TrackSelection(ientry,itrack,runoption) < 0) continue;

       //Search near HBD hit
       int hmide = track_hbd_mid->at(itrack)-103;
       int lmide = track_lg_mid->at(itrack)-103;
       double resx_min = 10000.;
       double resy_min = 10000.;
       double adc_max = -10000.;
       for(int ihbd=0;ihbd<track_hbd_multiplicity->at(itrack);ihbd++){
	 double resx = track_hbd_allhit_resx->at(itrack).at(ihbd)-originx[hmide][0];
	 double resy = track_hbd_allhit_resy->at(itrack).at(ihbd)-originy[hmide][0];
	 if(track_hbd_allhit_adc->at(itrack).at(ihbd)<hbdthr||track_hbd_allhit_size->at(itrack).at(ihbd)<hbdclthr) continue;
	 // if(track_hbd_allhit_adc->at(itrack).at(ihbd)<0||track_hbd_allhit_size->at(itrack).at(ihbd)!=1||track_hbd_allhit_adc->at(itrack).at(ihbd)>3) continue;//220512
	 if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	   resx_min=resx;
	   resy_min=resy;
	 }
	 if(fabs(resx)<widthx[hmide][0]&&fabs(resy)<widthy[hmide][0]){
	   if(adc_max<track_hbd_allhit_adc->at(itrack).at(ihbd)){
	     adc_max = track_hbd_allhit_adc->at(itrack).at(ihbd);
	   }
	 }
       }
       bool HBDhit=false;
       if( fabs(resx_min)<widthx[hmide][0] && fabs(resy_min)<widthy[hmide][0] ){
	 HBDhit=true;
       }
       //Search near LG hit
       resx_min = -10000.;
       resy_min = -10000.;
       int cid_min = -10000;
       double adc_min = -10000.;//240317
       int nlgh=0;
       for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){
	 double resx = track_lg_allhit_resx->at(itrack).at(ilg)-originx[lmide][1];
	 double resy = track_lg_allhit_resy->at(itrack).at(ilg)-originy[lmide][1];
	 double tmptdc = track_lg_allhit_ftime->at(itrack).at(ilg);
	 int cid = E16ANA_EIDSingleTrackAnalyzer::LocaltoCh(resx+track_lg_lx->at(itrack),resy+track_lg_ly->at(itrack));
#ifdef LGWFHit
	 if(track_lg_allhit_adc->at(itrack).at(ilg)<lgresthr||tmptdc<(ssdoffset-ssdregion)+track_ssd_t->at(itrack)||tmptdc>(ssdoffset+ssdregion)+track_ssd_t->at(itrack)) continue;//220418
#else
	 if(track_lg_allhit_adc->at(itrack).at(ilg)<lgresthr||tmptdc<-10.||tmptdc>10.) continue;//230906
#endif
	 if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	   resx_min=resx;
	   resy_min=resy;
	   cid_min=cid;
	   adc_min=track_lg_allhit_adc->at(itrack).at(ilg);//240317
	 }
	 nlgh++;
       }
       bool LGhit=false;
       if(fabs(resx_min)<widthx[lmide][1] && fabs(resy_min)<widthy[lmide][1]){
	 LGhit=true;
       }
       else{//240317
	 adc_min = -10000.;
       }

       //Check projection position
       bool ly23 = false;
       bool ly1234 = false;
       if( fabs(track_lg_ly->at(itrack))<160.7 ){ly23=true;}
       if( fabs(track_lg_ly->at(itrack))<281.0 ){ly1234=true;}
       if( (bene==1||bene==2)&&gaincalib&&!ly1234 ) continue;

       //Search near HBD mix hit
       resx_min = 10000.;
       resy_min = 10000.;
       double mix_adc_max = -10000.;
       int pre_event=-10000;
       bool HBDmixhit=false;
       if(hbdmixhits[hmide][4].size()!=lgmixhits[lmide][4].size()){std::cout<<"***event mis-match in HBDmix***"<<std::endl;}
       if(hbdmixhits[hmide][4].size()>0){
	 for(int ihbd=0;ihbd<hbdmixhits[hmide][4].size();ihbd++){
	   for(int jhbd=0;jhbd<hbdmixhits[hmide][4].at(ihbd).size();jhbd++){
	     double resx = hbdmixhits[hmide][4].at(ihbd).at(jhbd).lx-track_hbd_lx->at(itrack) - originx[hmide][0];
	     double resy = hbdmixhits[hmide][4].at(ihbd).at(jhbd).ly-track_hbd_ly->at(itrack) - originy[hmide][0];
	     if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	       resx_min=resx;
	       resy_min=resy;
	     }
	     if(fabs(resx)<widthx[hmide][0]&&fabs(resy)<widthy[hmide][0]){
	       if(mix_adc_max<hbdmixhits[hmide][4].at(ihbd).at(jhbd).adc){
		 mix_adc_max = hbdmixhits[hmide][4].at(ihbd).at(jhbd).adc;
	       }
	     }
	   }
	   if( fabs(resx_min)<widthx[hmide][0] && fabs(resy_min)<widthy[hmide][0] ){
	     HBDmixhit=true;
	     pre_event=ihbd;
	     break;
	   }
	 }
       }

       int btrktype[ntrktype]={-1,-1,-1,-1,-1,-1};
       btrktype[0]=IsGoodTrack(ientry,itrack,tracksets[0]);
       if(HBDhit){
	 btrktype[1]=IsGoodTrack(ientry,itrack,tracksets[1]);
	 //
	 // if(btrktype[1]>=0){
	 //   wfout[lmide]<<run_id<<" "<<event_id<<" "<<track_lg_mid->at(itrack)<<" "<<track_lg_blockch->at(itrack)<<" "<<track_position_block_lx->at(itrack)<<" "<<track_position_block_ly->at(itrack)<<" "<<track_angle_lx->at(itrack)<<" "<<track_angle_ly->at(itrack)<<" "<<track_mom->at(itrack)<<" "<<track_ssd_t->at(itrack)+ssdoffset<<" "<<rk_charge->at(itrack);
	 //   std::vector<int> tmp_cids(0);
	 //   CalcClusterCand(*geometry, tmp_cids, track_lg_blockch->at(itrack), track_position_block_lx->at(itrack), track_position_block_ly->at(itrack), track_angle_lx->at(itrack));
	 //   wfout[lmide]<<" "<<tmp_cids.size();
	 //   for(int icc=0;icc<tmp_cids.size();icc++){
	 //     wfout[lmide]<<" "<<tmp_cids.at(icc);
	 //   }
	 //   wfout[lmide]<<std::endl;
	 // }
	 //
       }
       if(LGhit){
	 btrktype[2]=IsGoodTrack(ientry,itrack,tracksets[2]);
       }
       if(HBDhit&&LGhit){
	 btrktype[3]=IsGoodTrack(ientry,itrack,tracksets[3]);
       }
       if(HBDhit){
	 // if((track_lg_mid->at(itrack)==106&&cid_min==41)||(track_lg_mid->at(itrack)==107&&cid_min==10)||(track_lg_mid->at(itrack)==103&&cid_min==35)||(track_lg_mid->at(itrack)==104&&cid_min==44)) continue;
	 if(hbdass_in_dst1==true&&(runoption==3||runoption==4)){
	   btrktype[4]=IsGoodTrackWHBD(ientry,itrack,tracksets[4],track_select_hbd_adc->at(itrack));
	 }
	 else{
	   btrktype[4]=IsGoodTrackWHBD(ientry,itrack,tracksets[4],adc_max);
	 }
       }
       if(HBDmixhit){
	 // if((track_lg_mid->at(itrack)==106&&cid_min==41)||(track_lg_mid->at(itrack)==107&&cid_min==10)||(track_lg_mid->at(itrack)==103&&cid_min==35)||(track_lg_mid->at(itrack)==104&&cid_min==44)) continue;
	 btrktype[5]=IsGoodTrackWHBD(ientry,itrack,tracksets_hmix,adc_max);
	 if(!HBDhit){
	   btrktype[5]=-3;
	 }
       }

       for(int itype=0;itype<ntrktype;itype++){//trktype loop
	 if(btrktype[itype]<0) continue;
	 ntrack[hmide][itype]++;

       //HBD Fill
       int nhbdc = 0;
       double hbdmaxadc=-10000.;
       int nhbdtrkass = 0;
       for(int ihbd=0;ihbd<track_hbd_multiplicity->at(itrack);ihbd++){// hbdcluster loop
	 double resx = track_hbd_allhit_resx->at(itrack).at(ihbd);
	 double resy = track_hbd_allhit_resy->at(itrack).at(ihbd);
	 double rxs = resx-originx[hmide][0];
	 double rys = resy-originy[hmide][0];
	 if(track_hbd_allhit_adc->at(itrack).at(ihbd)<hbdthr||track_hbd_allhit_size->at(itrack).at(ihbd)<hbdclthr) continue;
	 // if(track_hbd_allhit_adc->at(itrack).at(ihbd)<0||track_hbd_allhit_size->at(itrack).at(ihbd)!=1||track_hbd_allhit_adc->at(itrack).at(ihbd)>3) continue;//220512
	 haresx[hmide][0][0][itype]->Fill(resx);
	 haresx[2][0][0][itype]->Fill(resx);
	 haresy[hmide][0][0][itype]->Fill(resy);
	 haresy[2][0][0][itype]->Fill(resy);
	 if(fabs(rys)<widthy[hmide][0]){
	   haresx[hmide][1][0][itype]->Fill(resx);
	   haresx[2][1][0][itype]->Fill(resx);
	   if(rk_charge->at(itrack)==1){haresx[hmide][2][0][itype]->Fill(resx);haresx[2][2][0][itype]->Fill(resx);}
	   if(rk_charge->at(itrack)==-1){haresx[hmide][3][0][itype]->Fill(resx);haresx[2][3][0][itype]->Fill(resx);}
	 }
	 if(fabs(rxs)<widthx[hmide][0]){
	   haresy[hmide][1][0][itype]->Fill(resy);
	   haresy[2][1][0][itype]->Fill(resy);
	   if(rk_charge->at(itrack)==1){haresy[hmide][2][0][itype]->Fill(resy);haresy[2][2][0][itype]->Fill(resy);}
	   if(rk_charge->at(itrack)==-1){haresy[hmide][3][0][itype]->Fill(resy);haresy[2][3][0][itype]->Fill(resy);}
	 }
	 hares[hmide][0][itype]->Fill(resx,resy);
	 hares[2][0][itype]->Fill(resx,resy);
	 if( fabs(rxs)<widthx[hmide][0] && fabs(rys)<widthy[hmide][0] ){
	   ht[0][itype][hmide]->Fill(track_hbd_allhit_ftime->at(itrack).at(ihbd));
	   ht[0][itype][2]->Fill(track_hbd_allhit_ftime->at(itrack).at(ihbd));
	   if(hbdmaxadc < track_hbd_allhit_adc->at(itrack).at(ihbd)){
	     hbdmaxadc = track_hbd_allhit_adc->at(itrack).at(ihbd);
	   }
	   nhbdtrkass++;
	   //240317
	   // if(itype==1){
	   //   double px = resx + track_hbd_lx->at(itrack);
	   //   double py = resy + track_hbd_ly->at(itrack);
	   //   hbdwf<<ientry<<" "<<itrack<<" "<<ihbd<<" "<<event_id<<" "<<track_id->at(itrack)<<" "<<px<<" "<<py<<" "<<adc_min<<std::endl;
	   // }
	   //
	 }
	 nhbdc++;
       }// hbdcluster loop
       hn[hmide][0][itype]->Fill(nhbdc);
       hn[2][0][itype]->Fill(nhbdc);
       hntrackass[hmide][0][itype]->Fill(nhbdtrkass);
       hntrackass[2][0][itype]->Fill(nhbdtrkass);
       if(itype==eptype){
	 hbdhitmap[hmide]->Fill(track_hbd_lx->at(itrack),track_hbd_ly->at(itrack));
	 hbdhitmap[2]->Fill(track_hbd_lx->at(itrack),track_hbd_ly->at(itrack));
	 if(track_w_trg_hbd->at(itrack)&&track_w_trg_gtr->at(itrack)&&track_w_trg_lg->at(itrack)>-1000){
	   hbdadcwt[hmide]->Fill(hbdmaxadc);
	   hbdadcwt[2]->Fill(hbdmaxadc);
	 }
	 else{
	   hbdadcwot[hmide]->Fill(hbdmaxadc);
	   hbdadcwot[2]->Fill(hbdmaxadc);
	 }
	 hbdadcvsmom[hmide]->Fill(track_mom->at(itrack),hbdmaxadc);
	 if(lmide==0||lmide==1){hbdadcvsmom[2]->Fill(track_mom->at(itrack),hbdmaxadc);}
	 if(lmide==3||lmide==4){hbdadcvsmom[5]->Fill(track_mom->at(itrack),hbdmaxadc);}
	 ssdadcvsmom[hmide][0]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));
	 if(lmide==0||lmide==1){ssdadcvsmom[2][0]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	 if(lmide==3||lmide==4){ssdadcvsmom[5][0]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	 if(rk_charge->at(itrack)==1){
	   ssdadcvsmom[hmide][1]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));
	   if(lmide==0||lmide==1){ssdadcvsmom[2][1]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	   if(lmide==3||lmide==4){ssdadcvsmom[5][1]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	 }
	 if(rk_charge->at(itrack)==-1){
	   ssdadcvsmom[hmide][2]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));
	   if(lmide==0||lmide==1){ssdadcvsmom[2][2]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	   if(lmide==3||lmide==4){ssdadcvsmom[5][2]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	 }
       }

       if(hbdmixhits[hmide][itype].size()!=0){//calc mix
	 for(int ihbd=0;ihbd<hbdmixhits[hmide][itype].size();ihbd++){
	   int nhbdc_dum = 0;
	   double hbdmaxadc_dum=-10000.;
	   for(int jhbd=0;jhbd<hbdmixhits[hmide][itype].at(ihbd).size();jhbd++){
	     double tmpresx = hbdmixhits[hmide][itype].at(ihbd).at(jhbd).lx-track_hbd_lx->at(itrack);
	     double tmpresy = hbdmixhits[hmide][itype].at(ihbd).at(jhbd).ly-track_hbd_ly->at(itrack);
	     double tmprxs = tmpresx - originx[hmide][0];
	     double tmprys = tmpresy - originy[hmide][0];
	     haresxd[hmide][0][0][itype]->Fill(tmpresx);
	     haresxd[2][0][0][itype]->Fill(tmpresx);
	     haresyd[hmide][0][0][itype]->Fill(tmpresy);
	     haresyd[2][0][0][itype]->Fill(tmpresy);
	     if(fabs(tmprys)<widthy[hmide][0]){
	       haresxd[hmide][1][0][itype]->Fill(tmpresx);
	       haresxd[2][1][0][itype]->Fill(tmpresx);
	       if(rk_charge->at(itrack)==1){haresxd[hmide][2][0][itype]->Fill(tmpresx);haresxd[2][2][0][itype]->Fill(tmpresx);}
	       if(rk_charge->at(itrack)==-1){haresxd[hmide][3][0][itype]->Fill(tmpresx);haresxd[2][3][0][itype]->Fill(tmpresx);}
	     }
	     if(fabs(tmprxs)<widthx[hmide][0]){
	       haresyd[hmide][1][0][itype]->Fill(tmpresy);
	       haresyd[2][1][0][itype]->Fill(tmpresy);
	       if(rk_charge->at(itrack)==1){haresyd[hmide][2][0][itype]->Fill(tmpresy);haresyd[2][2][0][itype]->Fill(tmpresy);}
	       if(rk_charge->at(itrack)==-1){haresyd[hmide][3][0][itype]->Fill(tmpresy);haresyd[2][3][0][itype]->Fill(tmpresy);}
	     }
	     haresd[hmide][0][itype]->Fill(tmpresx,tmpresy);
	     haresd[2][0][itype]->Fill(tmpresx,tmpresy);
	     if( fabs(tmprxs)<widthx[hmide][0] && fabs(tmprys)<widthy[hmide][0] ){
	       htd[0][itype][hmide]->Fill(hbdmixhits[hmide][itype].at(ihbd).at(jhbd).tdc);
	       htd[0][itype][2]->Fill(hbdmixhits[hmide][itype].at(ihbd).at(jhbd).tdc);
	       if(hbdmaxadc_dum < hbdmixhits[hmide][itype].at(ihbd).at(jhbd).adc){
		 hbdmaxadc_dum = hbdmixhits[hmide][itype].at(ihbd).at(jhbd).adc;
	       }
	     }
	     nhbdc_dum++;
	   }
	   hnd[hmide][0][itype]->Fill(nhbdc_dum);
	   hnd[2][0][itype]->Fill(nhbdc_dum);
	   if(itype==eptype){
	     if(track_w_trg_hbd->at(itrack)&&track_w_trg_gtr->at(itrack)&&track_w_trg_lg->at(itrack)>-1000){
	       hbdadcwtd[hmide]->Fill(hbdmaxadc_dum);
	       hbdadcwtd[2]->Fill(hbdmaxadc_dum);
	     }
	     else{
	       hbdadcwotd[hmide]->Fill(hbdmaxadc_dum);
	       hbdadcwotd[2]->Fill(hbdmaxadc_dum);
	     }
	   }
	 }
       }//calc mix


       //LG Fill
       std::vector<hitset> lgnear;
       lgcls lgcluster;
       double adcsum = 0;
       std::vector<int> trk_ass_cids(0);
       CalcClusterCand(*geometry, trk_ass_cids, track_lg_blockch->at(itrack), track_position_block_lx->at(itrack), track_position_block_ly->at(itrack), track_angle_lx->at(itrack));//
       hnclscand[lmide]->Fill(trk_ass_cids.size());
       hnclscand[2]->Fill(trk_ass_cids.size());
       int nlgtrkass = 0;
       for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){//lgfore
	 double resx = track_lg_allhit_resx->at(itrack).at(ilg);
	 double resy = track_lg_allhit_resy->at(itrack).at(ilg);
	 double rxs = resx-originx[lmide][1];
	 double rys = resy-originy[lmide][1];
	 double tmpadc = track_lg_allhit_adc->at(itrack).at(ilg);
	 double tmptdc = track_lg_allhit_ftime->at(itrack).at(ilg);
	 double gain=1.;
	 int cid = E16ANA_EIDSingleTrackAnalyzer::LocaltoCh(resx+track_lg_lx->at(itrack),resy+track_lg_ly->at(itrack));
	 if(cid>=0&&cid<56){gain=relg[bene][lmide][cid/10][cid%10]*enepar[bene];}
	 if(gaincalib){tmpadc = tmpadc*gain;}
#ifdef LGWFHit
	 if(tmpadc<lgresthr||tmptdc<(ssdoffset-ssdregion)+track_ssd_t->at(itrack)||tmptdc>(ssdoffset+ssdregion)+track_ssd_t->at(itrack)) continue;//220418
#else
	 if(tmpadc<lgresthr||tmptdc<-10.||tmptdc>10.) continue;//230906
#endif
	 haresx[lmide][0][1][itype]->Fill(resx);
	 haresx[2][0][1][itype]->Fill(resx);
	 haresy[lmide][0][1][itype]->Fill(resy);
	 haresy[2][0][1][itype]->Fill(resy);
	 if(fabs(rys)<widthy[lmide][1]){
	   haresx[lmide][1][1][itype]->Fill(resx);
	   haresx[2][1][1][itype]->Fill(resx);
	   if(rk_charge->at(itrack)==1){haresx[lmide][2][1][itype]->Fill(resx);haresx[2][2][1][itype]->Fill(resx);}
	   if(rk_charge->at(itrack)==-1){haresx[lmide][3][1][itype]->Fill(resx);haresx[2][3][1][itype]->Fill(resx);}
	 }
	 if(fabs(rxs)<widthx[lmide][1]){
	   haresy[lmide][1][1][itype]->Fill(resy);
	   haresy[2][1][1][itype]->Fill(resy);
	   if(rk_charge->at(itrack)==1){haresy[lmide][2][1][itype]->Fill(resy);haresy[2][2][1][itype]->Fill(resy);}
	   if(rk_charge->at(itrack)==-1){haresy[lmide][3][1][itype]->Fill(resy);haresy[2][3][1][itype]->Fill(resy);}
	 }
	 if(fabs(rxs)<widthx[lmide][1]&&fabs(rys)<widthy[lmide][1]){
	   ht[1][itype][lmide]->Fill(track_lg_allhit_ftime->at(itrack).at(ilg));
	   ht[1][itype][2]->Fill(track_lg_allhit_ftime->at(itrack).at(ilg));
	 }
	 hares[lmide][1][itype]->Fill(resx,resy);
	 hares[2][1][itype]->Fill(resx,resy);
	 bool bclscand=false;
	 for(int itmp=0;itmp<trk_ass_cids.size();itmp++){
	   if(cid==trk_ass_cids.at(itmp)){
	     bclscand=true;
	     nlgtrkass++;
	     break;
	   }
	 }
	 if( itype==eptype ){
	   hitset tmphit;
	   tmphit.adc = tmpadc;
	   tmphit.tdc = tmptdc;
	   tmphit.lx = resx;
	   tmphit.ly = resy;
	   tmphit.mid = cid;
	   if( new_cluster_method==false && fabs(rxs)<searchx && fabs(rys)<searchy ){
	     lgnear.push_back(tmphit);
	   }
	   if( new_cluster_method==true ){
	     if(bclscand){
	       lgnear.push_back(tmphit);
	     }
	   }
	 }
       }//lgfore
       hn[lmide][1][itype]->Fill(nlgh);
       hn[2][1][itype]->Fill(nlgh);
       hntrackass[hmide][1][itype]->Fill(nlgtrkass);
       hntrackass[2][1][itype]->Fill(nlgtrkass);
       if(itype==eptype){
	 if(lgnear.size()>0){
	   hexp[lmide]->Fill(ExpectedE(track_mom->at(itrack))/enepar[bene]/track_mom->at(itrack));
	   hexp[2]->Fill(ExpectedE(track_mom->at(itrack))/enepar[bene]/track_mom->at(itrack));
	   adcsum=CalcADCNearHit(w_ssd_timing_match,lgnear,track_ssd_t->at(itrack),lgcluster);
	   if(w_calib_pos_dep){
	     double tbx, tby;
	     double calib_pos_dep = CalcCalibPar(track_lg_lx->at(itrack),track_lg_ly->at(itrack),track_angle_lx->at(itrack),track_lg_blockch->at(itrack),tbx, tby);
	     // double calib_pos_dep = CalcCalibPar(track_lg_ly->at(itrack),track_lg_blockch->at(itrack),tbx);
	     g->SetPoint(ig,tbx,tby,1./calib_pos_dep);
	     ig++;
	     adcsum=adcsum*calib_pos_dep;
	   }
	 }
	 trkmom[lmide]->Fill(track_mom->at(itrack));
	 if(lmide==0||lmide==1){trkmom[2]->Fill(track_mom->at(itrack));}
	 if(lmide==3||lmide==4){trkmom[5]->Fill(track_mom->at(itrack));}
	 if(adcsum>25&&adcsum<50){
	   ssdadcvsmom_pil[hmide][0]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));
	   if(lmide==0||lmide==1){ssdadcvsmom_pil[2][0]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	   if(lmide==3||lmide==4){ssdadcvsmom_pil[5][0]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	   if(rk_charge->at(itrack)==1){
	     ssdadcvsmom_pil[hmide][1]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));
	     if(lmide==0||lmide==1){ssdadcvsmom_pil[2][1]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	     if(lmide==3||lmide==4){ssdadcvsmom_pil[5][1]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	   }
	   if(rk_charge->at(itrack)==-1){
	     ssdadcvsmom_pil[hmide][2]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));
	     if(lmide==0||lmide==1){ssdadcvsmom_pil[2][2]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	     if(lmide==3||lmide==4){ssdadcvsmom_pil[5][2]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	   }
	 }
	 if(adcsum<15){
	   ssdadcvsmom_pl[hmide][0]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));
	   if(lmide==0||lmide==1){ssdadcvsmom_pl[2][0]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	   if(lmide==3||lmide==4){ssdadcvsmom_pl[5][0]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	   if(rk_charge->at(itrack)==1){
	     ssdadcvsmom_pl[hmide][1]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));
	     if(lmide==0||lmide==1){ssdadcvsmom_pl[2][1]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	     if(lmide==3||lmide==4){ssdadcvsmom_pl[5][1]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	   }
	   if(rk_charge->at(itrack)==-1){
	     ssdadcvsmom_pl[hmide][2]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));
	     if(lmide==0||lmide==1){ssdadcvsmom_pl[2][2]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	     if(lmide==3||lmide==4){ssdadcvsmom_pl[5][2]->Fill(track_mom->at(itrack),track_ssd_adc->at(itrack));}
	   }
	 }
	 bool bclstrk = false;
	 for(int ia=0;ia<trk_ass_cids.size();ia++){
	   int cidtmp = trk_ass_cids.at(ia);
	   int eltmp = (cidtmp/10)*7 + cidtmp%10;
	   bool bcls = false;
	   double adctmp = 0.;
	   for(int ib=0;ib<lgcluster.cids.size();ib++){
	     if(lgcluster.cids.at(ib)==cidtmp){bcls=true;adctmp=lgcluster.adcs.at(ib);break;}
	   }
	   if(!bcls){
	     heffe[lmide][eltmp]->Fill(0);
	     heffem[lmide][eltmp%7]->Fill(0);
	     if( runoption==0 && E16ANA_EIDSingleTrackAnalyzer::IsInTrgRun(run_id,track_hbd_mid->at(itrack)) ){
	     // if(track_w_trg_bias->at(itrack)){
	     // if(track_w_trg_trk->at(itrack)){
	       heffemvstrg[lmide][eltmp%7]->Fill(0.,1.);
	     }
	     else{
	       heffemvstrg[lmide][eltmp%7]->Fill(0.,0.);
	     }
	   }
	   else{
	     heffe[lmide][eltmp]->Fill(1);
	     heffem[lmide][eltmp%7]->Fill(1);
	     if( runoption==0 && E16ANA_EIDSingleTrackAnalyzer::IsInTrgRun(run_id,track_hbd_mid->at(itrack)) ){
	     // if(track_w_trg_bias->at(itrack)){
	     // if(track_w_trg_trk->at(itrack)){
	       heffemvstrg[lmide][eltmp%7]->Fill(1.,1.);
	     }
	     else{
	       heffemvstrg[lmide][eltmp%7]->Fill(1.,0.);
	     }
	     bclstrk = true;
	   }
	   hmome[lmide][eltmp]->Fill(track_mom->at(itrack));
	   hange[lmide][eltmp]->Fill(track_angle_lx->at(itrack)*180./acos(-1));
	 }
	 if(!bclstrk){
	   hmomwolg[lmide]->Fill(track_mom->at(itrack));
	   if(lmide==0||lmide==1){hmomwolg[2]->Fill(track_mom->at(itrack));}
	   if(lmide==3||lmide==4){hmomwolg[5]->Fill(track_mom->at(itrack));}
	 }
	 else{
	   hmomwlg[lmide]->Fill(track_mom->at(itrack));
	   if(lmide==0||lmide==1){hmomwlg[2]->Fill(track_mom->at(itrack));}
	   if(lmide==3||lmide==4){hmomwlg[5]->Fill(track_mom->at(itrack));}
	 }
	 if( runoption==0 && !E16ANA_EIDSingleTrackAnalyzer::IsInTrgRun(run_id,track_hbd_mid->at(itrack))){
	   hmomwotrg[lmide]->Fill(track_mom->at(itrack));
	   if(lmide==0||lmide==1){hmomwotrg[2]->Fill(track_mom->at(itrack));}
	   if(lmide==3||lmide==4){hmomwotrg[5]->Fill(track_mom->at(itrack));}
	 }
	 else{
	   hmomwtrg[lmide]->Fill(track_mom->at(itrack));
	   if(lmide==0||lmide==1){hmomwtrg[2]->Fill(track_mom->at(itrack));}
	   if(lmide==3||lmide==4){hmomwtrg[5]->Fill(track_mom->at(itrack));}
	 }
	 int lgtrgcid = track_lg_blockch->at(itrack);
	 int hbdtrgcid = HbdTrgCid(track_hbd_lx->at(itrack),track_hbd_ly->at(itrack));
	 hresxtrg[lmide]->Fill( lgtrgcid%10 - hbdtrgcid%10 );
	 hresytrg[lmide]->Fill( (int)lgtrgcid/10 - (int)hbdtrgcid/10 );
	 if(lmide==0||lmide==1){
	   hresxtrg[2]->Fill( lgtrgcid%10 - hbdtrgcid%10 );
	   hresytrg[2]->Fill( (int)lgtrgcid/10 - (int)hbdtrgcid/10 );
	 }
	 if(lmide==3||lmide==4){
	   hresxtrg[5]->Fill( lgtrgcid%10 - hbdtrgcid%10 );
	   hresytrg[5]->Fill( (int)lgtrgcid/10 - (int)hbdtrgcid/10 );
	 }
	 // std::cout<<trk_ass_cids.size()<<" "<<lgnear.size()<<" "<<lgcluster.cids.size()<<std::endl;
	 // if(lgcluster.cids.size()>0){//select 4d-isolate-cluster
	 //   for(int ict=0;ict<lgcluster.cids.size();ict++){//cls loop
	 //     for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){//hit loop
	 //       double resx = track_lg_allhit_resx->at(itrack).at(ilg)-originx[lmide][1];
	 //       double resy = track_lg_allhit_resy->at(itrack).at(ilg)-originy[lmide][1];
	 //       double tmptdc = track_lg_allhit_ftime->at(itrack).at(ilg);
	 //       int cid = E16ANA_EIDSingleTrackAnalyzer::LocaltoCh(resx+track_lg_lx->at(itrack),resy+track_lg_ly->at(itrack));
	 //       if(track_lg_allhit_adc->at(itrack).at(ilg)<lgresthr||tmptdc<(ssdoffset-ssdregion)+track_ssd_t->at(itrack)||tmptdc>(ssdoffset+ssdregion)+track_ssd_t->at(itrack)) continue;
	 //       bool hitincls = false;
	 //       for(int ict2=0;ict2<lgcluster.cids.size();ict2++){
	 // 	 if(cid==lgcluster.cids.at(ict2)&&tmptdc==lgcluster.tdcs.at(ict2)){
	 // 	   hitincls = true;
	 // 	   break;
	 // 	 }
	 //       }
	 //       if(!hitincls&&fabs(lgcluster.tdcs.at(ict)-tmptdc)<10&&E16ANA_EIDSingleTrackAnalyzer::IsNeighborBlock(*geometry,cid,lgcluster.cids.at(ict))){
	 // 	 adcsum=-10000.;
	 // 	 break;
	 //       }
	 //     }//hit loop
	 //   }//cls loop
	 // }//select 4d-isolate-cluster
	 // if(lgnear.size()!=1){adcsum=-10000.;}//select 4d-isolate-cluster
	 hnlghitwtc[lmide]->Fill(lgcluster.cids.size());
	 hnlghitwtc[2]->Fill(lgcluster.cids.size());
	 for(int ict=0;ict<lgcluster.cids.size();ict++){
	   htsvslc[lmide]->Fill(lgcluster.tdcs.at(ict),track_ssd_t->at(itrack));
	   htsvslc[2]->Fill(lgcluster.tdcs.at(ict),track_ssd_t->at(itrack));
	   // evspout[lmide]<<lgcluster.tdcs.at(ict)<<" "<<track_ssd_t->at(itrack)<<std::endl;
	   // evspout[2]<<lgcluster.tdcs.at(ict)<<" "<<track_ssd_t->at(itrack)<<std::endl;
	   htsslc[lmide]->Fill( track_ssd_t->at(itrack) - (lgcluster.tdcs.at(ict)-51.) );
	   htsslc[2]->Fill( track_ssd_t->at(itrack) - (lgcluster.tdcs.at(ict)-51.) );
	 }
	 if(lgcluster.cids.size()>1){
	   htdiffc[lmide]->Fill(lgcluster.timediff);
	   htdiffc[2]->Fill(lgcluster.timediff);
	   hcogxc[lmide]->Fill(lgcluster.cogx);
	   hcogxc[2]->Fill(lgcluster.cogx);
	   hcogyc[lmide]->Fill(lgcluster.cogy);
	   hcogyc[2]->Fill(lgcluster.cogy);
	   if(track_lg_lx->at(itrack)>0){
	     if(track_lg_ly->at(itrack)>0){
	       hcogxcl[lmide][0]->Fill(lgcluster.cogx);
	       hcogxcl[2][0]->Fill(lgcluster.cogx);
	       hcogycl[lmide][0]->Fill(lgcluster.cogy);
	       hcogycl[2][0]->Fill(lgcluster.cogy);
	     }
	     else{
	       hcogxcl[lmide][1]->Fill(lgcluster.cogx);
	       hcogxcl[2][1]->Fill(lgcluster.cogx);
	       hcogycl[lmide][1]->Fill(lgcluster.cogy);
	       hcogycl[2][1]->Fill(lgcluster.cogy);
	     }
	   }
	   else{
	     if(track_lg_ly->at(itrack)>0){
	       hcogxcl[lmide][2]->Fill(lgcluster.cogx);
	       hcogxcl[2][2]->Fill(lgcluster.cogx);
	       hcogycl[lmide][2]->Fill(lgcluster.cogy);
	       hcogycl[2][2]->Fill(lgcluster.cogy);
	     }
	     else{
	       hcogxcl[lmide][3]->Fill(lgcluster.cogx);
	       hcogxcl[2][3]->Fill(lgcluster.cogx);
	       hcogycl[lmide][3]->Fill(lgcluster.cogy);
	       hcogycl[2][3]->Fill(lgcluster.cogy);
	     }
	   }
	   hthvsp[lmide]->Fill(track_mom->at(itrack),track_angle_lx->at(itrack)*180./acos(-1));
	   hthvsp[2]->Fill(track_mom->at(itrack),track_angle_lx->at(itrack)*180./acos(-1));
	   if(track_mom->at(itrack)>2.){
	     htheta[lmide][2]->Fill(track_angle_lx->at(itrack)*180./acos(-1));
	     htheta[2][2]->Fill(track_angle_lx->at(itrack)*180./acos(-1));
	   }
	   else if(track_mom->at(itrack)>1.){
	     htheta[lmide][1]->Fill(track_angle_lx->at(itrack)*180./acos(-1));
	     htheta[2][1]->Fill(track_angle_lx->at(itrack)*180./acos(-1));
	   }
	   else{
	     htheta[lmide][0]->Fill(track_angle_lx->at(itrack)*180./acos(-1));
	     htheta[2][0]->Fill(track_angle_lx->at(itrack)*180./acos(-1));
	   }
	 }
	 for(int ilc=0;ilc<lgcluster.cids.size();ilc++){
	   hhitmapc[0][lmide]->Fill((double)((lgcluster.cids.at(ilc))%10),(double)((lgcluster.cids.at(ilc))/10));
	   hhitmapc[0][2]->Fill((double)((lgcluster.cids.at(ilc))%10),(double)((lgcluster.cids.at(ilc))/10));
	   if( (adcsum/enepar[bene]) < 160./enepar[bene]*(track_mom->at(itrack)-0.5) ){
	     hhitmapc[1][lmide]->Fill((double)((lgcluster.cids.at(ilc))%10),(double)((lgcluster.cids.at(ilc))/10));
	     hhitmapc[1][2]->Fill((double)((lgcluster.cids.at(ilc))%10),(double)((lgcluster.cids.at(ilc))/10));
	   }
	   else if( (adcsum/enepar[bene]) > 160./enepar[bene]*(track_mom->at(itrack)+0.1) ){
	     hhitmapc[3][lmide]->Fill((double)((lgcluster.cids.at(ilc))%10),(double)((lgcluster.cids.at(ilc))/10));
	     hhitmapc[3][2]->Fill((double)((lgcluster.cids.at(ilc))%10),(double)((lgcluster.cids.at(ilc))/10));
	   }
	   else{
	     hhitmapc[2][lmide]->Fill((double)((lgcluster.cids.at(ilc))%10),(double)((lgcluster.cids.at(ilc))/10));
	     hhitmapc[2][2]->Fill((double)((lgcluster.cids.at(ilc))%10),(double)((lgcluster.cids.at(ilc))/10));
	   }
	 }
	 int maxcid = lgcluster.maxadcch;
	 int maxcidel = ((int)maxcid/10)*7 + (int)maxcid%10;
	 if(adcsum>0){
	   hevsp[lmide]->Fill(track_mom->at(itrack),adcsum/enepar[bene]);
	   hevsp[2]->Fill(track_mom->at(itrack),adcsum/enepar[bene]);
	   hevspr[lmide]->Fill(track_mom->at(itrack),adcsum/enepar[bene]);
	   hevspr[2]->Fill(track_mom->at(itrack),adcsum/enepar[bene]);
	   hevspe[lmide][maxcidel]->Fill(track_mom->at(itrack),adcsum/enepar[bene]);
	   // evspout[lmide]<<track_mom->at(itrack)<<" "<<adcsum/enepar[bene]<<std::endl;
	   // evspout[2]<<track_mom->at(itrack)<<" "<<adcsum/enepar[bene]<<std::endl;
	   heovpvsp[lmide]->Fill(track_mom->at(itrack),adcsum/enepar[bene]/track_mom->at(itrack));
	   heovpvsp[2]->Fill(track_mom->at(itrack),adcsum/enepar[bene]/track_mom->at(itrack));
	   hadc[lmide]->Fill(adcsum/enepar[bene]);
	   hadc[2]->Fill(adcsum/enepar[bene]);
	 }
	 for(int j=0;j<4;j++){
	   if(adcsum>lgthr[j]){
	     hedivp[j][lmide]->Fill(adcsum/enepar[bene]/track_mom->at(itrack));
	     hassp[j][lmide]->Fill(track_mom->at(itrack));
	     hasse[j][lmide]->Fill(adcsum/enepar[bene]);
	     if(fwdonly){
	       if(lmide==1||lmide==3){
		 hedivp[j][2]->Fill(adcsum/enepar[bene]/track_mom->at(itrack));
		 hassp[j][2]->Fill(track_mom->at(itrack));
		 hasse[j][2]->Fill(adcsum/enepar[bene]);
	       }
	     }
	     else{
	       hedivp[j][2]->Fill(adcsum/enepar[bene]/track_mom->at(itrack));
	       hassp[j][2]->Fill(track_mom->at(itrack));
	       hasse[j][2]->Fill(adcsum/enepar[bene]);
	     }
	   }
	   if(adcsum>lgresthr){
	     hesubp[j][lmide]->Fill(adcsum-lgcon[j]*track_mom->at(itrack));
	     hesubp[j][2]->Fill(adcsum-lgcon[j]*track_mom->at(itrack));
	   }
	 }
	 if(adcsum>lgthr[0]){
	   hedivpe[lmide][maxcidel]->Fill(adcsum/enepar[bene]/track_mom->at(itrack));
	 }
       }

       if(lgmixhits[lmide][itype].size()!=0){//calc mix
	 for(int ilg=0;ilg<lgmixhits[lmide][itype].size();ilg++){//lghit loop
	   std::vector<hitset> lgneard;
	   lgcls lgclusterd;
	   double adcsumd = 0;
	   int nlgh_dum = 0;
	   int nlgtrkass_dum = 0;
	   for(int jlg=0;jlg<lgmixhits[lmide][itype].at(ilg).size();jlg++){
	     double tmpresx = lgmixhits[lmide][itype].at(ilg).at(jlg).lx-track_lg_lx->at(itrack);
	     double tmpresy = lgmixhits[lmide][itype].at(ilg).at(jlg).ly-track_lg_ly->at(itrack);
	     double tmprxs = tmpresx - originx[lmide][1];
	     double tmprys = tmpresy - originy[lmide][1];
	     double tmpt = lgmixhits[lmide][itype].at(ilg).at(jlg).tdc;
	     double tmpa = lgmixhits[lmide][itype].at(ilg).at(jlg).adc;
	     int tmpcid = E16ANA_EIDSingleTrackAnalyzer::LocaltoCh(tmpresx+track_lg_lx->at(itrack),tmpresy+track_lg_ly->at(itrack));
	     haresxd[lmide][0][1][itype]->Fill(tmpresx);
	     haresxd[2][0][1][itype]->Fill(tmpresx);
	     haresyd[lmide][0][1][itype]->Fill(tmpresy);
	     haresyd[2][0][1][itype]->Fill(tmpresy);
	     if(fabs(tmprys)<widthy[lmide][1]){
	       haresxd[lmide][1][1][itype]->Fill(tmpresx);
	       haresxd[2][1][1][itype]->Fill(tmpresx);
	       if(rk_charge->at(itrack)==1){haresxd[lmide][2][1][itype]->Fill(tmpresx);haresxd[2][2][1][itype]->Fill(tmpresx);}
	       if(rk_charge->at(itrack)==-1){haresxd[lmide][3][1][itype]->Fill(tmpresx);haresxd[2][3][1][itype]->Fill(tmpresx);}
	     }
	     if(fabs(tmprxs)<widthx[lmide][1]){
	       haresyd[lmide][1][1][itype]->Fill(tmpresy);
	       haresyd[2][1][1][itype]->Fill(tmpresy);
	       if(rk_charge->at(itrack)==1){haresyd[lmide][2][1][itype]->Fill(tmpresy);haresyd[2][2][1][itype]->Fill(tmpresy);}
	       if(rk_charge->at(itrack)==-1){haresyd[lmide][3][1][itype]->Fill(tmpresy);haresyd[2][3][1][itype]->Fill(tmpresy);}
	       if(fabs(tmprys)<widthy[lmide][1]){
		 htd[1][itype][lmide]->Fill(tmpt);
		 htd[1][itype][2]->Fill(tmpt);
	       }
	     }
	     haresd[lmide][1][itype]->Fill(tmpresx,tmpresy);
	     haresd[2][1][itype]->Fill(tmpresx,tmpresy);
	     bool bclscand=false;
	     for(int itmp=0;itmp<trk_ass_cids.size();itmp++){
	       if(tmpcid==trk_ass_cids.at(itmp)){
		 bclscand=true;
		 nlgtrkass_dum++;
		 break;
	       }
	     }
	     if( itype==eptype ){
	       hitset tmphit;
	       tmphit.adc = tmpa;
	       tmphit.tdc = tmpt;
	       tmphit.lx = tmpresx;
	       tmphit.ly = tmpresy;
	       tmphit.mid = tmpcid;
	       if( new_cluster_method==false && fabs(tmprxs)<searchx && fabs(tmprys)<searchy ){
		 lgneard.push_back(tmphit);
	       }
	       if( new_cluster_method==true ){
		 if(bclscand){
		   lgneard.push_back(tmphit);
		 }
	       }
	     }
	     nlgh_dum++;
	   }
	   hnd[lmide][1][itype]->Fill(nlgh_dum);
	   hnd[2][1][itype]->Fill(nlgh_dum);
	   hntrackassd[hmide][1][itype]->Fill(nlgtrkass_dum);
	   hntrackassd[2][1][itype]->Fill(nlgtrkass_dum);
	   if(itype==eptype){
	     if(lgneard.size()>0){
	       adcsumd=CalcADCNearHit(w_ssd_timing_match,lgneard,track_ssd_t->at(itrack),lgclusterd);
	       if(w_calib_pos_dep){
		 double tbx, tby;
		 double calib_pos_dep = CalcCalibPar(track_lg_lx->at(itrack),track_lg_ly->at(itrack),track_angle_lx->at(itrack),track_lg_blockch->at(itrack),tbx,tby);
		 // double calib_pos_dep = CalcCalibPar(track_lg_ly->at(itrack),track_lg_blockch->at(itrack),tbx);
		 adcsumd=adcsumd*calib_pos_dep;
	       }
	     }
	     hnlghitwtcd[lmide]->Fill(lgclusterd.cids.size());
	     hnlghitwtcd[2]->Fill(lgclusterd.cids.size());
	     for(int ict=0;ict<lgclusterd.cids.size();ict++){
	       htsvslcd[lmide]->Fill(lgclusterd.tdcs.at(ict),track_ssd_t->at(itrack));
	       htsvslcd[2]->Fill(lgclusterd.tdcs.at(ict),track_ssd_t->at(itrack));
	       // evspdout[lmide]<<lgclusterd.tdcs.at(ict)<<" "<<track_ssd_t->at(itrack)<<std::endl;
	       // evspdout[2]<<lgclusterd.tdcs.at(ict)<<" "<<track_ssd_t->at(itrack)<<std::endl;
	       htsslcd[lmide]->Fill( track_ssd_t->at(itrack) - (lgclusterd.tdcs.at(ict)-51.) );
	       htsslcd[2]->Fill( track_ssd_t->at(itrack) - (lgclusterd.tdcs.at(ict)-51.) );
	     }
	     if(lgclusterd.cids.size()>1){
	       htdiffcd[lmide]->Fill(lgclusterd.timediff);
	       htdiffcd[2]->Fill(lgclusterd.timediff);
	       hcogxcd[lmide]->Fill(lgclusterd.cogx);
	       hcogxcd[2]->Fill(lgclusterd.cogx);
	       hcogycd[lmide]->Fill(lgclusterd.cogy);
	       hcogycd[2]->Fill(lgclusterd.cogy);
	       hthvspd[lmide]->Fill(track_mom->at(itrack),track_angle_lx->at(itrack)*180./acos(-1));
	       hthvspd[2]->Fill(track_mom->at(itrack),track_angle_lx->at(itrack)*180./acos(-1));
	     }
	     for(int ilc=0;ilc<lgclusterd.cids.size();ilc++){
	       hhitmapcd[0][lmide]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
	       hhitmapcd[0][2]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
	       if( (adcsumd/enepar[bene]) < 160./enepar[bene]*(track_mom->at(itrack)-0.5) ){
		 hhitmapcd[1][lmide]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
		 hhitmapcd[1][2]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
	       }
	       else if( (adcsumd/enepar[bene]) > 160./enepar[bene]*(track_mom->at(itrack)+0.1) ){
		 hhitmapcd[3][lmide]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
		 hhitmapcd[3][2]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
	       }
	       else{
		 hhitmapcd[2][lmide]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
		 hhitmapcd[2][2]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
	       }
	     }
	     int maxcid = lgclusterd.maxadcch;
	     int maxcidel = ((int)maxcid/10)*7 + (int)maxcid%10;
	     if(adcsumd>0){
	       hevspd[lmide]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]);
	       hevspd[2]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]);
	       hevsprd[lmide]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]);
	       hevsprd[2]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]);
	       hevsped[lmide][maxcidel]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]);
	       heovpvspd[lmide]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]/track_mom->at(itrack));
	       heovpvspd[2]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]/track_mom->at(itrack));
	       hadcd[lmide]->Fill(adcsumd/enepar[bene]);
	       hadcd[2]->Fill(adcsumd/enepar[bene]);
	     }
	     for(int j=0;j<4;j++){
	       if(adcsumd>lgthr[j]){
		 hedivpd[j][lmide]->Fill(adcsumd/enepar[bene]/track_mom->at(itrack));
		 hasspd[j][lmide]->Fill(track_mom->at(itrack));
		 hassed[j][lmide]->Fill(adcsumd/enepar[bene]);
		 if(fwdonly){
		   if(lmide==1||lmide==3){
		     hedivpd[j][2]->Fill(adcsumd/enepar[bene]/track_mom->at(itrack));
		     hasspd[j][2]->Fill(track_mom->at(itrack));
		     hassed[j][2]->Fill(adcsumd/enepar[bene]);
		   }
		 }
		 else{
		   hedivpd[j][2]->Fill(adcsumd/enepar[bene]/track_mom->at(itrack));
		   hasspd[j][2]->Fill(track_mom->at(itrack));
		   hassed[j][2]->Fill(adcsumd/enepar[bene]);
		 }
	       }
	       if(adcsumd>lgresthr){
		 hesubpd[j][lmide]->Fill(adcsumd-lgcon[j]*track_mom->at(itrack));
		 hesubpd[j][2]->Fill(adcsumd-lgcon[j]*track_mom->at(itrack));
	       }
	     }
	     if(adcsumd>lgthr[0]){
	       hedivped[lmide][maxcidel]->Fill(adcsumd/enepar[bene]/track_mom->at(itrack));
	     }
	   }
	 }//lghit loop
       }//calc mix

	//fill mixing hit
       if(alfill[0][hmide][itype]!=alfill[1][lmide][itype]){std::cout<<"***Uncorrect alfill***"<<std::endl;}
       if(alfill[0][hmide][itype]==false){
	 alfill[0][hmide][itype]=true;
	 for(int ihbd=0;ihbd<track_hbd_multiplicity->at(itrack);ihbd++){
	   hitset hbdhit;
	   if(track_hbd_allhit_adc->at(itrack).at(ihbd)<hbdthr||track_hbd_allhit_size->at(itrack).at(ihbd)<hbdclthr) continue;
	   // if(track_hbd_allhit_adc->at(itrack).at(ihbd)<0||track_hbd_allhit_size->at(itrack).at(ihbd)!=1||track_hbd_allhit_adc->at(itrack).at(ihbd)>3) continue;//220512
	   hbdhit.mid=track_hbd_mid->at(itrack);
	   hbdhit.lx=track_hbd_allhit_resx->at(itrack).at(ihbd)+track_hbd_lx->at(itrack);
	   hbdhit.ly=track_hbd_allhit_resy->at(itrack).at(ihbd)+track_hbd_ly->at(itrack);
	   hbdhit.adc=track_hbd_allhit_adc->at(itrack).at(ihbd);
	   hbdhit.tdc=track_hbd_allhit_ftime->at(itrack).at(ihbd);
	   hbdhits[hmide][itype].push_back(hbdhit);
	 }
       }
       if(alfill[1][lmide][itype]==false){
	 alfill[1][lmide][itype]=true;
	 for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){
	   double tmplx = track_lg_allhit_resx->at(itrack).at(ilg)+track_lg_lx->at(itrack);
	   double tmply = track_lg_allhit_resy->at(itrack).at(ilg)+track_lg_ly->at(itrack);
	   double tmpt = track_lg_allhit_ftime->at(itrack).at(ilg);
	   double tmpa = track_lg_allhit_adc->at(itrack).at(ilg);
	   double gain=1.;
	   int cid = E16ANA_EIDSingleTrackAnalyzer::LocaltoCh(tmplx,tmply);
	   if(cid>=0&&cid<56){gain=relg[bene][lmide][cid/10][cid%10]*enepar[bene];}
	   if(gaincalib){tmpa=tmpa*gain;}
	   if(tmpa<lgresthr||tmpt<(ssdoffset-ssdregion)+track_ssd_t->at(itrack)||tmpt>(ssdoffset+ssdregion)+track_ssd_t->at(itrack)) continue;
	   hitset lghit;
	   lghit.mid=track_lg_mid->at(itrack);
	   lghit.lx=tmplx;
	   lghit.ly=tmply;
	   lghit.adc=tmpa;
	   lghit.tdc=tmpt;
	   lghits[lmide][itype].push_back(lghit);
	 }
       }
       //fill mixing hit

       ntrk[hmide][itype]++;

       }//trktype loop

       //trktype_hmix
       if(btrktype[5]<0) continue;
       for(int jhbd=0;jhbd<hbdmixhits[hmide][4].at(pre_event).size();jhbd++){
	 double tmpresx = hbdmixhits[hmide][4].at(pre_event).at(jhbd).lx-track_hbd_lx->at(itrack);
	 double tmpresy = hbdmixhits[hmide][4].at(pre_event).at(jhbd).ly-track_hbd_ly->at(itrack);
	 double tmprxs = tmpresx - originx[hmide][0];
	 double tmprys = tmpresy - originy[hmide][0];
	 haresxd_hmix[hmide][0][0]->Fill(tmpresx);
	 haresxd_hmix[2][0][0]->Fill(tmpresx);
	 haresyd_hmix[hmide][0][0]->Fill(tmpresy);
	 haresyd_hmix[2][0][0]->Fill(tmpresy);
	 if(fabs(tmprys)<widthy[hmide][0]){
	   haresxd_hmix[hmide][1][0]->Fill(tmpresx);
	   haresxd_hmix[2][1][0]->Fill(tmpresx);
	   if(rk_charge->at(itrack)==1){haresxd_hmix[hmide][2][0]->Fill(tmpresx);haresxd_hmix[2][2][0]->Fill(tmpresx);}
	   if(rk_charge->at(itrack)==-1){haresxd_hmix[hmide][3][0]->Fill(tmpresx);haresxd_hmix[2][3][0]->Fill(tmpresx);}
	 }
	 if(fabs(tmprxs)<widthx[hmide][0]){
	   haresyd_hmix[hmide][1][0]->Fill(tmpresy);
	   haresyd_hmix[2][1][0]->Fill(tmpresy);
	   if(rk_charge->at(itrack)==1){haresyd_hmix[hmide][2][0]->Fill(tmpresy);haresyd_hmix[2][2][0]->Fill(tmpresy);}
	   if(rk_charge->at(itrack)==-1){haresyd_hmix[hmide][3][0]->Fill(tmpresy);haresyd_hmix[2][3][0]->Fill(tmpresy);}
	 }
       }
       std::vector<hitset> lgneard;
       lgcls lgclusterd;
       double adcsumd = 0;
       for(int jlg=0;jlg<lgmixhits[lmide][4].at(pre_event).size();jlg++){
	 double tmpresx = lgmixhits[lmide][4].at(pre_event).at(jlg).lx-track_lg_lx->at(itrack);
	 double tmpresy = lgmixhits[lmide][4].at(pre_event).at(jlg).ly-track_lg_ly->at(itrack);
	 double tmprxs = tmpresx - originx[lmide][1];
	 double tmprys = tmpresy - originy[lmide][1];
	 double tmpt = lgmixhits[lmide][4].at(pre_event).at(jlg).tdc;
	 double tmpa = lgmixhits[lmide][4].at(pre_event).at(jlg).adc;
	 int tmpcid = E16ANA_EIDSingleTrackAnalyzer::LocaltoCh(tmpresx+track_lg_lx->at(itrack),tmpresy+track_lg_ly->at(itrack));
	 haresxd_hmix[lmide][0][1]->Fill(tmpresx);
	 haresxd_hmix[2][0][1]->Fill(tmpresx);
	 haresyd_hmix[lmide][0][1]->Fill(tmpresy);
	 haresyd_hmix[2][0][1]->Fill(tmpresy);
	 if(fabs(tmprys)<widthy[lmide][1]){
	   haresxd_hmix[lmide][1][1]->Fill(tmpresx);
	   haresxd_hmix[2][1][1]->Fill(tmpresx);
	   if(rk_charge->at(itrack)==1){haresxd_hmix[lmide][2][1]->Fill(tmpresx);haresxd_hmix[2][2][1]->Fill(tmpresx);}
	   if(rk_charge->at(itrack)==-1){haresxd_hmix[lmide][3][1]->Fill(tmpresx);haresxd_hmix[2][3][1]->Fill(tmpresx);}
	 }
	 if(fabs(tmprxs)<widthx[lmide][1]){
	   haresyd_hmix[lmide][1][1]->Fill(tmpresy);
	   haresyd_hmix[2][1][1]->Fill(tmpresy);
	   if(rk_charge->at(itrack)==1){haresyd_hmix[lmide][2][1]->Fill(tmpresy);haresyd_hmix[2][2][1]->Fill(tmpresy);}
	   if(rk_charge->at(itrack)==-1){haresyd_hmix[lmide][3][1]->Fill(tmpresy);haresyd_hmix[2][3][1]->Fill(tmpresy);}
	 }
	 if( fabs(tmprxs)<searchx && fabs(tmprys)<searchy ){
	   hitset tmphit;
	   tmphit.adc = tmpa;
	   tmphit.tdc = tmpt;
	   tmphit.lx = tmpresx;
	   tmphit.ly = tmpresy;
	   tmphit.mid = tmpcid;
	   lgneard.push_back(tmphit);
	 }
       }
       if(lgneard.size()>0){
	 adcsumd=CalcADCNearHit(w_ssd_timing_match,lgneard,track_ssd_t->at(itrack),lgclusterd);
	 if(w_calib_pos_dep){
	   double tbx, tby;
	   double calib_pos_dep = CalcCalibPar(track_lg_lx->at(itrack),track_lg_ly->at(itrack),track_angle_lx->at(itrack),track_lg_blockch->at(itrack),tbx,tby);
	   // double calib_pos_dep = CalcCalibPar(track_lg_ly->at(itrack),track_lg_blockch->at(itrack),tbx);
	   adcsumd=adcsumd*calib_pos_dep;
	 }
       }
       hnlghitwtcd_hmix[lmide]->Fill(lgclusterd.cids.size());
       hnlghitwtcd_hmix[2]->Fill(lgclusterd.cids.size());
       if(lgclusterd.cids.size()>1){
	 htdiffcd_hmix[lmide]->Fill(lgclusterd.timediff);
	 htdiffcd_hmix[2]->Fill(lgclusterd.timediff);
	 hcogxcd_hmix[lmide]->Fill(lgclusterd.cogx);
	 hcogxcd_hmix[2]->Fill(lgclusterd.cogx);
	 hcogycd_hmix[lmide]->Fill(lgclusterd.cogy);
	 hcogycd_hmix[2]->Fill(lgclusterd.cogy);
       }
       for(int ilc=0;ilc<lgclusterd.cids.size();ilc++){
	 hhitmapcd_hmix[0][lmide]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
	 hhitmapcd_hmix[0][2]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
	 if( (adcsumd/enepar[bene]) < 160./enepar[bene]*(track_mom->at(itrack)-0.5) ){
	   hhitmapcd_hmix[1][lmide]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
	   hhitmapcd_hmix[1][2]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
	 }
	 else if( (adcsumd/enepar[bene]) > 160./enepar[bene]*(track_mom->at(itrack)+0.1) ){
	   hhitmapcd_hmix[3][lmide]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
	   hhitmapcd_hmix[3][2]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
	 }
	 else{
	   hhitmapcd_hmix[2][lmide]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
	   hhitmapcd_hmix[2][2]->Fill((double)((lgclusterd.cids.at(ilc))%10),(double)((lgclusterd.cids.at(ilc))/10));
	 }
       }
       if(adcsumd>0){
	 hevsprd_hmix[lmide]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]);
	 hevsprd_hmix[2]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]);
	 heovpvspd_hmix[lmide]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]/track_mom->at(itrack));
	 heovpvspd_hmix[2]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]/track_mom->at(itrack));
       }
       for(int j=0;j<4;j++){
	 if(adcsumd>lgthr[j]){
	   hedivpd_hmix[j][lmide]->Fill(adcsumd/enepar[bene]/track_mom->at(itrack));
	   hasspd_hmix[j][lmide]->Fill(track_mom->at(itrack));
	   hassed_hmix[j][lmide]->Fill(adcsumd/enepar[bene]);
	   hedivpd_hmix[j][2]->Fill(adcsumd/enepar[bene]/track_mom->at(itrack));
	   hasspd_hmix[j][2]->Fill(track_mom->at(itrack));
	   hassed_hmix[j][2]->Fill(adcsumd/enepar[bene]);
	 }
       }
       //trktype_hmix

       ntrk_acc++;

     }//track loop

     if(ntrk_acc>0){
       hlgmulti->Fill(lg_event_multiplicity);
       htrgmulti->Fill(trg_event_multiplicity);
       hsingle->Fill(single_ratio);
     }

     for(int it=0;it<ntrktype;it++){
       for(int im=0;im<5;im++){
	 if(alfill[0][im][it]==true){
	   hbdmixhits[im][it].push_back(hbdhits[im][it]);
	   if(hbdmixhits[im][it].size()>mixevent){
	     hbdmixhits[im][it].erase(hbdmixhits[im][it].begin());
	   }
	 }
	 if(alfill[1][im][it]==true){
	   lgmixhits[im][it].push_back(lghits[im][it]);
	   if(lgmixhits[im][it].size()>mixevent){
	     lgmixhits[im][it].erase(lgmixhits[im][it].begin());
	   }
	 }
	 hnt[im][it]->Fill(ntrk[im][it]);
       }
     }
     nevent++;

   }//event loop


   //draw canvas
   TString outfile = Form("%s",out_file_name);

   gStyle->SetOptStat(11111111);
   gStyle->SetOptFit(11111111);
   TCanvas* cnt[ntrktype];
   TCanvas* cn[ndet][ntrktype];
   TCanvas* cnd[ndet][ntrktype];
   for(int l=0;l<ntrktype;l++){
     cnt[l] = new TCanvas(Form("cnt%d",l),Form("cnt",l),700,500);
     cnt[l]->Divide(2,2);
     for(int i=0;i<4;i++){
       cnt[l]->cd(i+1);
       hnt[(i+3)%5][l]->Draw();
     }
     for(int k=0;k<ndet;k++){
       cn[k][l] = new TCanvas(Form("cn%d%d",k,l),Form("cn%d%d",k,l),700,500);
       cn[k][l]->Divide(2,2);
       cnd[k][l] = new TCanvas(Form("cnd%d%d",k,l),Form("cnd%d%d",k,l),700,500);
       cnd[k][l]->Divide(2,2);
       for(int i=0;i<4;i++){
	 cn[k][l]->cd(i+1);
	 hn[(i+3)%5][k][l]->Draw();
	 cnd[k][l]->cd(i+1);
	 hnd[(i+3)%5][k][l]->Draw();
       }
     }
   }
   TCanvas* ct[ndet][ntrktype];
   for(int l=0;l<ntrktype;l++){
     for(int k=0;k<ndet;k++){
       ct[k][l] = new TCanvas(Form("ct%d%d",k,l),Form("ct%d%d",k,l),700,500);
       DC1DForeMix(ct[k][l],ht[k][l],htd[k][l],mixevent);
     }
   }
   TCanvas* chbdhitmap = new TCanvas("chbdhitmap","chbdhitmap",700,500);
   chbdhitmap->Divide(2,2);
   for(int i=0;i<4;i++){
     chbdhitmap->cd(i+1);
     hbdhitmap[(i+3)%5]->Draw("colz");
   }
   TCanvas* ctsvslc = new TCanvas("ctsvslc","ctsvslc",700,500);
   TCanvas* ctsvslcd = new TCanvas("ctsvslcd","ctsvslcd",700,500);
   DC2DForeMix(ctsvslc,ctsvslcd,htsvslc,htsvslcd,mixevent);
   // TCanvas* cexp = new TCanvas("cexp","cexp",700,500);
   // cexp->Divide(2,2);
   // for(int i=0;i<4;i++){
   //   cexp->cd(i+1);
   //   hexp[(i+3)%5]->Draw();
   // }
   // TH2F* hevspsub[5];
   // TCanvas* cevsp = new TCanvas("cevsp","cevsp",700,500);
   // TCanvas* cevspd = new TCanvas("cevspd","cevspd",700,500);
   // TCanvas* cevspsub = new TCanvas("cevspsub","cevspsub",700,500);
   // DC2DForeMixFM(cevsp,cevspd,cevspsub,hevsp,hevspd,hevspsub,mixevent);
   TH2F* hevsprsub[5];
   TCanvas* cevspr = new TCanvas("cevspr","cevspr",700,500);
   TCanvas* cevsprd = new TCanvas("cevsprd","cevsprd",700,500);
   TCanvas* cevsprsub = new TCanvas("cevsprsub","cevsprsub",700,500);
   DC2DForeMixFM(cevspr,cevsprd,cevsprsub,hevspr,hevsprd,hevsprsub,mixevent);
   for(int i=0;i<4;i++){
     hevsprsub[i]->SetName(Form("hevsprsub%d",(i+3)%5));
     hevsprsub[i]->SetTitle(Form("LG_AdcSumVsMom_Fore-Mix_TrackAssoc_mod%d",103+((i+3)%5)));
     // if(runoption==3&&i==2){
     //   TLine *l1 = new TLine(-0.1,0,1.9,2.*160./enepar[bene]);
     //   TLine *l2 = new TLine( 0.5,0,2.5,2.*160./enepar[bene]);
     //   l1->SetLineColor(2);
     //   l2->SetLineColor(2);
     //   l1->Draw("sames");
     //   l2->Draw("sames");
     // }
   }
   TH2F* heovpvspsub[5];
   TCanvas* ceovpvsp = new TCanvas("ceovpvsp","ceovpvsp",700,500);
   TCanvas* ceovpvspd = new TCanvas("ceovpvspd","ceovpvspd",700,500);
   TCanvas* ceovpvspsub = new TCanvas("ceovpvspsub","ceovpvspsub",700,500);
   DC2DForeMixFM(ceovpvsp,ceovpvspd,ceovpvspsub,heovpvsp,heovpvspd,heovpvspsub,mixevent);
   for(int i=0;i<4;i++){
     heovpvspsub[i]->SetName(Form("heovpvspsub%d",(i+3)%5));
     heovpvspsub[i]->SetTitle(Form("LG_E/pVsMom_Fore-Mix_TrackAssoc_mod%d",103+((i+3)%5)));
   }
   TH1F* htsslcsub[4];
   TCanvas* ctsslc = new TCanvas("ctsslc","ctsslc",700,500);
   TCanvas* ctsslcsub = new TCanvas("ctsslcsub","ctsslcsub",700,500);
   DC1DForeMixFM("tsslc",ctsslc,ctsslcsub,htsslc,htsslcd,htsslcsub,mixevent);
   TH1F* hbdadcwotsub[4];
   TCanvas* chbdadcwot = new TCanvas("chbdadcwot","chbdadcwot",700,500);
   TCanvas* chbdadcwotsub = new TCanvas("chbdadcwotsub","chbdadcwotsub",700,500);
   DC1DForeMixFM("hbdadcwot",chbdadcwot,chbdadcwotsub,hbdadcwot,hbdadcwotd,hbdadcwotsub,mixevent);
   TH1F* hbdadcwtsub[4];
   TCanvas* chbdadcwt = new TCanvas("chbdadcwt","chbdadcwt",700,500);
   TCanvas* chbdadcwtsub = new TCanvas("chbdadcwtsub","chbdadcwtsub",700,500);
   DC1DForeMixFM("hbdadcwt",chbdadcwt,chbdadcwtsub,hbdadcwt,hbdadcwtd,hbdadcwtsub,mixevent);
   // TH1F* hadcsub[4];
   // TCanvas* cadc = new TCanvas("cadc","cadc",700,500);
   // TCanvas* cadcsub = new TCanvas("cadcsub","cadcsub",700,500);
   // DC1DForeMixFM("adc",cadc,cadcsub,hadc,hadcd,hadcsub,mixevent);
   TH1F* hedivpsub[4][4];
   TCanvas* cedivp[4];
   TCanvas* cedivpsub[4];
   TH1F* hasspsub[4][4];
   TCanvas* cassp[4];
   TCanvas* casspsub[4];
   TH1F* hassesub[4][4];
   TCanvas* casse[4];
   TCanvas* cassesub[4];
   // TH1F* hesubpsub[4][4];
   // TCanvas* cesubp[4];
   // TCanvas* cesubpsub[4];
   for(int j=0;j<4;j++){
     cedivp[j] = new TCanvas(Form("cedivp%d",j),Form("cedivp%d",j),700,500);
     cedivpsub[j] = new TCanvas(Form("cedivpsub%d",j),Form("cedivpsub%d",j),700,500);
     DC1DForeMixFM(Form("edivp%d",j),cedivp[j],cedivpsub[j],hedivp[j],hedivpd[j],hedivpsub[j],mixevent);
     cassp[j] = new TCanvas(Form("cassp%d",j),Form("cassp%d",j),700,500);
     casspsub[j] = new TCanvas(Form("casspsub%d",j),Form("casspsub%d",j),700,500);
     DC1DForeMixFM(Form("assp%d",j),cassp[j],casspsub[j],hassp[j],hasspd[j],hasspsub[j],mixevent);
     casse[j] = new TCanvas(Form("casse%d",j),Form("casse%d",j),700,500);
     cassesub[j] = new TCanvas(Form("cassesub%d",j),Form("cassesub%d",j),700,500);
     DC1DForeMixFM(Form("asse%d",j),casse[j],cassesub[j],hasse[j],hassed[j],hassesub[j],mixevent);
     // cesubp[j] = new TCanvas(Form("cesubp%d",j),Form("cesubp%d",j),700,500);
     // cesubpsub[j] = new TCanvas(Form("cesubpsub%d",j),Form("cesubpsub%d",j),700,500);
     // DC1DForeMixFM(Form("esubp%d",j),cesubp[j],cesubpsub[j],hesubp[j],hesubpd[j],hesubpsub[j],mixevent);
   }
   TCanvas* cnlghitwtc = new TCanvas("cnlghitwtc","cnlghitwtc",700,500);
   TCanvas* cnlghitwtcd = new TCanvas("cnlghitwtcd","cnlghitwtcd",700,500);
   cnlghitwtc->Divide(2,2);
   cnlghitwtcd->Divide(2,2);
   for(int i=0;i<4;i++){
     cnlghitwtc->cd(i+1)->SetLogy();
     hnlghitwtc[(i+3)%5]->Draw();
     cnlghitwtcd->cd(i+1)->SetLogy();
     hnlghitwtcd[(i+3)%5]->Draw();
   }
   TCanvas* ctdiffc = new TCanvas("ctdiffc","ctdiffc",700,500);
   DC1DForeMix(ctdiffc,htdiffc,htdiffcd,mixevent);
   TCanvas* ccogxc = new TCanvas("ccogxc","ccogxc",700,500);
   DC1DForeMix(ccogxc,hcogxc,hcogxcd,mixevent);
   TCanvas* ccogyc = new TCanvas("ccogyc","ccogyc",700,500);
   DC1DForeMix(ccogyc,hcogyc,hcogycd,mixevent);
   TCanvas* ccogxcl[4];
   TCanvas* ccogycl[4];
   for(int j=0;j<4;j++){
     ccogxcl[j] = new TCanvas(Form("ccogxcl%d",j),Form("ccogxcl%d",j),700,500);
     ccogxcl[j]->Divide(2,2);
     ccogycl[j] = new TCanvas(Form("ccogycl%d",j),Form("ccogycl%d",j),700,500);
     ccogycl[j]->Divide(2,2);
     for(int i=0;i<4;i++){
       ccogxcl[j]->cd(i+1);
       hcogxcl[(i+3)%5][j]->Draw();
       ccogycl[j]->cd(i+1);
       hcogycl[(i+3)%5][j]->Draw();
     }
   }
   TH2F* hhitmapcsub[4][5];
   TCanvas* chitmapc[4];
   TCanvas* chitmapcd[4];
   TCanvas* chitmapcsub[4];
   for(int j=0;j<4;j++){
     chitmapc[j] = new TCanvas(Form("chitmapc%d",j),Form("chitmapc",j),700,500);
     chitmapcd[j] = new TCanvas(Form("chitmapcd%d",j),Form("chitmapcd%d",j),700,500);
     chitmapcsub[j] = new TCanvas(Form("chitmapcsub%d",j),Form("chitmapcsub%d",j),700,500);
     DC2DForeMixFM(chitmapc[j],chitmapcd[j],chitmapcsub[j],hhitmapc[j],hhitmapcd[j],hhitmapcsub[j],mixevent);
     for(int i=0;i<4;i++){
       hhitmapcsub[j][i]->SetName(Form("hhitmapcsub%d%d",j,(i+3)%5));
       hhitmapcsub[j][i]->SetTitle(Form("LGhitmap_mod%d_E/pcut%d_Fore-Mix",103+((i+3)%5),j));
     }
   }
   TH2F* hthvspsub[5];
   TCanvas* cthvsp = new TCanvas("cthvsp","cthvsp",700,500);
   TCanvas* cthvspd = new TCanvas("cthvspd","cthvspd",700,500);
   TCanvas* cthvspsub = new TCanvas("cthvspsub","cthvspsub",700,500);
   DC2DForeMixFM(cthvsp,cthvspd,cthvspsub,hthvsp,hthvspd,hthvspsub,mixevent);
   for(int i=0;i<4;i++){
     hthvspsub[i]->SetName(Form("hthvspsub%d",(i+3)%5));
     hthvspsub[i]->SetTitle(Form("theta(deg)_vs_mom_TrackAssoc_mod%d_Fore-Mix",103+((i+3)%5)));
   }
   TCanvas* ctheta = new TCanvas("ctheta","ctheta",700,500);
   ctheta->Divide(2,2);
   for(int i=0;i<4;i++){
     ctheta->cd(i+1);
     htheta[(i+3)%5][0]->SetLineColor(1);
     htheta[(i+3)%5][0]->Draw("hist");
     htheta[(i+3)%5][1]->SetLineColor(2);
     htheta[(i+3)%5][1]->Draw("hist sames");
     htheta[(i+3)%5][2]->SetLineColor(4);
     htheta[(i+3)%5][2]->Draw("hist sames");
   }

   TCanvas* cevspe[4];
   TCanvas* cevsped[4];
   TCanvas* cedivpe[4];
   for(int i=0;i<4;i++){
     cevspe[i] = new TCanvas(Form("cevspe%d",i),Form("cevspe%d",i),700,500);
     cevsped[i] = new TCanvas(Form("cevsped%d",i),Form("cevsped%d",i),700,500);
     cedivpe[i] = new TCanvas(Form("cedivpe%d",i),Form("cedivpe%d",i),700,500);
     cevspe[i]->Divide(7,6);
     cevsped[i]->Divide(7,6);
     cedivpe[i]->Divide(7,6);
     for(int j=0;j<42;j++){
       cevspe[i]->cd(j+1);
       hevspe[(i+3)%5][41-j]->Draw("colz");
       cevsped[i]->cd(j+1);
       hevsped[(i+3)%5][41-j]->Draw("colz");
       cedivpe[i]->cd(j+1);
       hedivpe[(i+3)%5][41-j]->Draw("hist");
       hedivped[(i+3)%5][41-j]->SetLineColor(2);
       hedivped[(i+3)%5][41-j]->Scale(1./(double)mixevent);
       hedivped[(i+3)%5][41-j]->Draw("hist sames");
     }
   }
   TCanvas* ceffe[4];
   TCanvas* cmome[4];
   TCanvas* cange[4];
   TGraphErrors* geffe[4];
   double veffex[4][42];
   double veffey[4][42];
   double veffex_err[4][42];
   double veffey_err[4][42];
   for(int i=0;i<4;i++){
     ceffe[i] = new TCanvas(Form("ceffe%d",i),Form("ceffe%d",i),700,500);
     ceffe[i]->Divide(7,6);
     cmome[i] = new TCanvas(Form("cmome%d",i),Form("cmome%d",i),700,500);
     cmome[i]->Divide(7,6);
     cange[i] = new TCanvas(Form("cange%d",i),Form("cange%d",i),700,500);
     cange[i]->Divide(7,6);
     for(int j=0;j<42;j++){
       ceffe[i]->cd(j+1);
       heffe[(i+3)%5][41-j]->Draw();
       cmome[i]->cd(j+1);
       hmome[(i+3)%5][41-j]->Draw();
       cange[i]->cd(j+1);
       hange[(i+3)%5][41-j]->Draw();
       veffex[i][j] = (int)j/7*10+j%7;
       veffey[i][j] = heffe[(i+3)%5][j]->GetMean();
       veffex_err[i][j] = 0.;
       veffey_err[i][j] = CalcBinomialError(heffe[(i+3)%5][j]->GetEntries(),heffe[(i+3)%5][j]->GetBinContent(2));
     }
   }
   TCanvas* ceffeg = new TCanvas("ceffeg","ceffeg",700,500);
   ceffeg->Divide(2,2);
   for(int i=0;i<4;i++){
     ceffeg->cd(i+1)->SetGrid();
     geffe[i] = new TGraphErrors(42,veffex[i],veffey[i],veffex_err[i],veffey_err[i]);
     geffe[i]->SetMaximum(1.);
     geffe[i]->Draw("A*");
   }
   TGraphErrors* geffem[4];
   double veffemx[4][7];
   double veffemy[4][7];
   double veffemx_err[4][7];
   double veffemy_err[4][7];
   for(int i=0;i<4;i++){
     for(int j=0;j<7;j++){
       veffemx[i][j] = (double)j;
       veffemy[i][j] = heffem[(i+3)%5][j]->GetMean();
       veffemx_err[i][j] = 0.;
       veffemy_err[i][j] = CalcBinomialError(heffem[(i+3)%5][j]->GetEntries(),heffem[(i+3)%5][j]->GetBinContent(2));
     }
   }
   TCanvas* ceffemg = new TCanvas("ceffemg","ceffemg",700,500);
   ceffemg->Divide(2,2);
   for(int i=0;i<4;i++){
     ceffemg->cd(i+1)->SetGrid();
     geffem[i] = new TGraphErrors(7,veffemx[i],veffemy[i],veffemx_err[i],veffemy_err[i]);
     geffem[i]->SetMaximum(1.);
     geffem[i]->SetMinimum(0.);
     geffem[i]->Draw("A*");
   }

   //draw canvas HBD-LG mix
   TH2F* hevsprsub_hmix[5];
   TCanvas* cevspr_hmix = new TCanvas("cevspr_hmix","cevspr_hmix",700,500);
   TCanvas* cevsprd_hmix = new TCanvas("cevsprd_hmix","cevsprd_hmix",700,500);
   TCanvas* cevsprsub_hmix = new TCanvas("cevsprsub_hmix","cevsprsub_hmix",700,500);
   DC2DForeMixFM(cevspr_hmix,cevsprd_hmix,cevsprsub_hmix,hevspr,hevsprd_hmix,hevsprsub_hmix,1);
   for(int i=0;i<4;i++){
     hevsprsub_hmix[i]->SetName(Form("hevsprsub_hmix%d",(i+3)%5));
     hevsprsub_hmix[i]->SetTitle(Form("LG_AdcSumVsMom_Fore-Mix_TrackAssoc_mod%d_hmix",103+((i+3)%5)));
   }
   TH2F* heovpvspsub_hmix[5];
   TCanvas* ceovpvsp_hmix = new TCanvas("ceovpvsp_hmix","ceovpvsp_hmix",700,500);
   TCanvas* ceovpvspd_hmix = new TCanvas("ceovpvspd_hmix","ceovpvspd_hmix",700,500);
   TCanvas* ceovpvspsub_hmix = new TCanvas("ceovpvspsub_hmix","ceovpvspsub_hmix",700,500);
   DC2DForeMixFM(ceovpvsp_hmix,ceovpvspd_hmix,ceovpvspsub_hmix,heovpvsp,heovpvspd_hmix,heovpvspsub_hmix,1);
   for(int i=0;i<4;i++){
     heovpvspsub_hmix[i]->SetName(Form("heovpvspsub_hmix%d",(i+3)%5));
     heovpvspsub_hmix[i]->SetTitle(Form("LG_E/pVsMom_Fore-Mix_TrackAssoc_mod%d_hmix",103+((i+3)%5)));
   }
   TH1F* hedivpsub_hmix[4][4];
   TCanvas* cedivp_hmix[4];
   TCanvas* cedivpsub_hmix[4];
   TH1F* hasspsub_hmix[4][4];
   TCanvas* cassp_hmix[4];
   TCanvas* casspsub_hmix[4];
   TH1F* hassesub_hmix[4][4];
   TCanvas* casse_hmix[4];
   TCanvas* cassesub_hmix[4];
   for(int j=0;j<4;j++){
     cedivp_hmix[j] = new TCanvas(Form("cedivp_hmix%d",j),Form("cedivp_hmix%d",j),700,500);
     cedivpsub_hmix[j] = new TCanvas(Form("cedivpsub_hmix%d",j),Form("cedivpsub_hmix%d",j),700,500);
     DC1DForeMixFM(Form("edivp_hmix%d",j),cedivp_hmix[j],cedivpsub_hmix[j],hedivp[j],hedivpd_hmix[j],hedivpsub_hmix[j],1);
     cassp_hmix[j] = new TCanvas(Form("cassp_hmix%d",j),Form("cassp_hmix%d",j),700,500);
     casspsub_hmix[j] = new TCanvas(Form("casspsub_hmix%d",j),Form("casspsub_hmix%d",j),700,500);
     DC1DForeMixFM(Form("assp_hmix%d",j),cassp_hmix[j],casspsub_hmix[j],hassp[j],hasspd_hmix[j],hasspsub_hmix[j],1);
     casse_hmix[j] = new TCanvas(Form("casse_hmix%d",j),Form("casse_hmix%d",j),700,500);
     cassesub_hmix[j] = new TCanvas(Form("cassesub_hmix%d",j),Form("cassesub_hmix%d",j),700,500);
     DC1DForeMixFM(Form("asse_hmix%d",j),casse_hmix[j],cassesub_hmix[j],hasse[j],hassed_hmix[j],hassesub_hmix[j],1);
   }
   TCanvas* cnlghitwtc_hmix = new TCanvas("cnlghitwtc_hmix","cnlghitwtc_hmix",700,500);
   TCanvas* cnlghitwtcd_hmix = new TCanvas("cnlghitwtcd_hmix","cnlghitwtcd_hmix",700,500);
   cnlghitwtc_hmix->Divide(2,2);
   cnlghitwtcd_hmix->Divide(2,2);
   for(int i=0;i<4;i++){
     cnlghitwtc_hmix->cd(i+1)->SetLogy();
     hnlghitwtc[(i+3)%5]->Draw();
     cnlghitwtcd_hmix->cd(i+1)->SetLogy();
     hnlghitwtcd_hmix[(i+3)%5]->Draw();
   }
   TCanvas* ctdiffc_hmix = new TCanvas("ctdiffc_hmix","ctdiffc_hmix",700,500);
   DC1DForeMix(ctdiffc_hmix,htdiffc,htdiffcd_hmix,1);
   TCanvas* ccogxc_hmix = new TCanvas("ccogxc_hmix","ccogxc_hmix",700,500);
   DC1DForeMix(ccogxc_hmix,hcogxc,hcogxcd_hmix,1);
   TCanvas* ccogyc_hmix = new TCanvas("ccogyc_hmix","ccogyc_hmix",700,500);
   DC1DForeMix(ccogyc_hmix,hcogyc,hcogycd_hmix,1);
   TH2F* hhitmapcsub_hmix[4][5];
   TCanvas* chitmapc_hmix[4];
   TCanvas* chitmapcd_hmix[4];
   TCanvas* chitmapcsub_hmix[4];
   for(int j=0;j<4;j++){
     chitmapc_hmix[j] = new TCanvas(Form("chitmapc_hmix%d",j),Form("chitmapc_hmix%d",j),700,500);
     chitmapcd_hmix[j] = new TCanvas(Form("chitmapcd_hmix%d",j),Form("chitmapcd_hmix%d",j),700,500);
     chitmapcsub_hmix[j] = new TCanvas(Form("chitmapcsub_hmix%d",j),Form("chitmapcsub_hmix%d",j),700,500);
     DC2DForeMixFM(chitmapc_hmix[j],chitmapcd_hmix[j],chitmapcsub_hmix[j],hhitmapc[j],hhitmapcd_hmix[j],hhitmapcsub_hmix[j],1);
     for(int i=0;i<4;i++){
       hhitmapcsub_hmix[j][i]->SetName(Form("hhitmapcsub_hmix%d%d",j,(i+3)%5));
       hhitmapcsub_hmix[j][i]->SetTitle(Form("LGhitmap_mod%d_E/pcut%d_Fore-Mix_hmix",103+((i+3)%5),j));
     }
   }

   //draw residual
   TCanvas* casubd[4][nopt][ndet][ntrktype];
   TH1F* hasubd[4][2][nopt][ndet][ntrktype];
   TF1* fasubd[4][2][nopt][ndet][ntrktype];
   TLegend* lasubd[4][2][nopt][ndet][ntrktype];
   int vasubd[4][2][nopt][ndet][ntrktype];
   TLine* l1[4][2][2][nopt][ndet][ntrktype];
   TLine* l2[4][2][2][nopt][ndet][ntrktype];
   for(int l=0;l<ntrktype;l++){
     for(int k=0;k<ndet;k++){
       for(int j=0;j<nopt;j++){
	 for(int i=0;i<4;i++){
	   casubd[i][j][k][l] = new TCanvas(Form("casubd%d%d%d%d",i,j,k,l),Form("casubd%d%d%d%d",i,j,k,l),700,500);
	   casubd[i][j][k][l]->Divide(2,2);
	   casubd[i][j][k][l]->cd(1);
	   haresx[(i+3)%5][j][k][l]->Draw("hist");
	   int reg[4] = {haresx[(i+3)%5][j][k][l]->FindBin(-800.),haresx[(i+3)%5][j][k][l]->FindBin(-100.),haresx[(i+3)%5][j][k][l]->FindBin(100.),haresx[(i+3)%5][j][k][l]->FindBin(800.)};
	   haresxd[(i+3)%5][j][k][l]->Scale(1./(double)mixevent);
	   haresxd[(i+3)%5][j][k][l]->SetLineColor(6);
	   haresxd[(i+3)%5][j][k][l]->Draw("hist&&same");
	   gPad->Update();
	   l1[i][0][0][j][k][l] = new TLine(originx[(i+3)%5][k]-widthx[(i+3)%5][k],gPad->GetUymin(),originx[(i+3)%5][k]-widthx[(i+3)%5][k],gPad->GetUymax());
	   l2[i][0][0][j][k][l] = new TLine(originx[(i+3)%5][k]+widthx[(i+3)%5][k],gPad->GetUymin(),originx[(i+3)%5][k]+widthx[(i+3)%5][k],gPad->GetUymax());
	   l1[i][0][0][j][k][l]->SetLineColor(2);
	   l2[i][0][0][j][k][l]->SetLineColor(2);
	   l1[i][0][0][j][k][l]->Draw("same");
	   l2[i][0][0][j][k][l]->Draw("same");
	   casubd[i][j][k][l]->cd(2);
	   haresy[(i+3)%5][j][k][l]->Draw("hist");
	   haresyd[(i+3)%5][j][k][l]->Scale(1./(double)mixevent);
	   haresyd[(i+3)%5][j][k][l]->SetLineColor(6);
	   haresyd[(i+3)%5][j][k][l]->Draw("hist&&same");
	   gPad->Update();
	   l1[i][1][0][j][k][l] = new TLine(originy[(i+3)%5][k]-widthy[(i+3)%5][k],gPad->GetUymin(),originy[(i+3)%5][k]-widthy[(i+3)%5][k],gPad->GetUymax());
	   l2[i][1][0][j][k][l] = new TLine(originy[(i+3)%5][k]+widthy[(i+3)%5][k],gPad->GetUymin(),originy[(i+3)%5][k]+widthy[(i+3)%5][k],gPad->GetUymax());
	   l1[i][1][0][j][k][l]->SetLineColor(2);
	   l2[i][1][0][j][k][l]->SetLineColor(2);
	   l1[i][1][0][j][k][l]->Draw("same");
	   l2[i][1][0][j][k][l]->Draw("same");
	   casubd[i][j][k][l]->cd(3);
	   hasubd[i][0][j][k][l] = (TH1F*)haresx[(i+3)%5][j][k][l]->Clone();
	   hasubd[i][0][j][k][l]->SetName(Form("haresxcp%d%d%d%d",(i+3)%5,j,k,l));
	   hasubd[i][0][j][k][l]->Add(haresxd[(i+3)%5][j][k][l],-1);
	   hasubd[i][0][j][k][l]->Draw("hist");
	   fasubd[i][0][j][k][l] = new TF1(Form("fasubd%dx%d%d%d",i,j,k,l),"gaus",-800,800);
	   hasubd[i][0][j][k][l]->Fit(Form("fasubd%dx%d%d%d",i,j,k,l),"","",-fitregion[k],fitregion[k]);
	   lasubd[i][0][j][k][l] = new TLegend(0.1,0.75,0.4,0.9);
	   vasubd[i][0][j][k][l] = hasubd[i][0][j][k][l]->Integral(roughbin[k]/2-(int)widthx[(i+3)%5][k]*roughbin[k]/1600,roughbin[k]/2+(int)widthy[(i+3)%5][k]*roughbin[k]/1600);
	   lasubd[i][0][j][k][l]->AddEntry(hasubd[i][0][j][k][l],Form("%d<Integral<%d, %d",-(int)widthx[(i+3)%5][k],(int)widthx[(i+3)%5][k],vasubd[i][0][j][k][l]),"l");
	   lasubd[i][0][j][k][l]->AddEntry((TObject*)0,Form("n_track: %d",ntrack[(i+3)%5][l]),"");
	   lasubd[i][0][j][k][l]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasubd[i][0][j][k][l]/(double)ntrack[(i+3)%5][l]),"");
	   lasubd[i][0][j][k][l]->Draw();
	   gPad->Update();
	   l1[i][0][1][j][k][l] = new TLine(originx[(i+3)%5][k]-widthx[(i+3)%5][k],gPad->GetUymin(),originx[(i+3)%5][k]-widthx[(i+3)%5][k],gPad->GetUymax());
	   l2[i][0][1][j][k][l] = new TLine(originx[(i+3)%5][k]+widthx[(i+3)%5][k],gPad->GetUymin(),originx[(i+3)%5][k]+widthx[(i+3)%5][k],gPad->GetUymax());
	   l1[i][0][1][j][k][l]->SetLineColor(2);
	   l2[i][0][1][j][k][l]->SetLineColor(2);
	   l1[i][0][1][j][k][l]->Draw("same");
	   l2[i][0][1][j][k][l]->Draw("same");
	   casubd[i][j][k][l]->cd(4);
	   hasubd[i][1][j][k][l] = (TH1F*)haresy[(i+3)%5][j][k][l]->Clone();
	   hasubd[i][1][j][k][l]->SetName(Form("haresycp%d%d%d%d",(i+3)%5,j,k,l));
	   hasubd[i][1][j][k][l]->Add(haresyd[(i+3)%5][j][k][l],-1);
	   hasubd[i][1][j][k][l]->Draw("hist");
	   fasubd[i][1][j][k][l] = new TF1(Form("fasubd%dy%d%d%d",i,j,k,l),"gaus",-800,800);
	   hasubd[i][1][j][k][l]->Fit(Form("fasubd%dy%d%d%d",i,j,k,l),"","",-fitregion[k],fitregion[k]);
	   lasubd[i][1][j][k][l] = new TLegend(0.1,0.75,0.4,0.9);
	   vasubd[i][1][j][k][l] = hasubd[i][1][j][k][l]->Integral(roughbin[k]/2-(int)widthx[(i+3)%5][k]*roughbin[k]/1600,roughbin[k]/2+(int)widthy[(i+3)%5][k]*roughbin[k]/1600);
	   lasubd[i][1][j][k][l]->AddEntry(hasubd[i][1][j][k][l],Form("%d<Integral<%d, %d",-(int)widthx[(i+3)%5][k],(int)widthx[(i+3)%5][k],vasubd[i][1][j][k][l]),"l");
	   lasubd[i][1][j][k][l]->AddEntry((TObject*)0,Form("n_track: %d",ntrack[(i+3)%5][l]),"");
	   lasubd[i][1][j][k][l]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasubd[i][1][j][k][l]/(double)ntrack[(i+3)%5][l]),"");
	   lasubd[i][1][j][k][l]->Draw();
	   gPad->Update();
	   l1[i][1][1][j][k][l] = new TLine(originy[(i+3)%5][k]-widthy[(i+3)%5][k],gPad->GetUymin(),originy[(i+3)%5][k]-widthy[(i+3)%5][k],gPad->GetUymax());
	   l2[i][1][1][j][k][l] = new TLine(originy[(i+3)%5][k]+widthy[(i+3)%5][k],gPad->GetUymin(),originy[(i+3)%5][k]+widthy[(i+3)%5][k],gPad->GetUymax());
	   l1[i][1][1][j][k][l]->SetLineColor(2);
	   l2[i][1][1][j][k][l]->SetLineColor(2);
	   l1[i][1][1][j][k][l]->Draw("same");
	   l2[i][1][1][j][k][l]->Draw("same");
	 }
       }
     }
   }
   TCanvas* casub2d[4][ndet][ntrktype];
   TH2F* hasub2d[4][ndet][ntrktype];
   TH2F* hasub2dcopy[4][ndet][ntrktype];
   TLegend* lasub2d[3][4][ndet][ntrktype];
   int vasub2d[3][4][ndet][ntrktype];
   double voriginx[4][ndet]={0.};
   double voriginy[4][ndet]={0.};
   double vsigmax[4][ndet]={0.};
   double vsigmay[4][ndet]={0.};
   double missurv[4][ndet][ntrktype]={0.};
   double effxtrkp[4][ndet][ntrktype]={0.};
   for(int l=0;l<ntrktype;l++){
     for(int k=0;k<ndet;k++){
       for(int i=0;i<4;i++){
	 casub2d[i][k][l] = new TCanvas(Form("casub2d%d%d%d",i,k,l),Form("casub2d%d%d%d",i,k,l),700,700);
	 casub2d[i][k][l]->Divide(2,2);
	 // voriginx[i][k] = fasubd[i][0][1][k]->GetParameter(1);
	 // voriginy[i][k] = fasubd[i][1][1][k]->GetParameter(1);
	 // vsigmax[i][k] = fasubd[i][0][1][k]->GetParameter(2);
	 // vsigmay[i][k] = fasubd[i][1][1][k]->GetParameter(2);
	 voriginx[i][k]=originx[(i+3)%5][k];
	 voriginy[i][k]=originy[(i+3)%5][k];
	 vsigmax[i][k]=widthx[(i+3)%5][k];
	 vsigmay[i][k]=widthy[(i+3)%5][k];
	 casub2d[i][k][l]->cd(1);
	 hares[(i+3)%5][k][l]->Draw("colz");
	 lasub2d[0][i][k][l] = new TLegend(0.1,0.8,0.45,0.9);
	 vasub2d[0][i][k][l] = Get2DHistSquareIntegral(hares[(i+3)%5][k][l],voriginx[i][k],voriginy[i][k],vsigmax[i][k],vsigmay[i][k]);
	 lasub2d[0][i][k][l]->AddEntry(hares[(i+3)%5][k][l],Form("Integral, %d",vasub2d[0][i][k][l]),"l");
	 lasub2d[0][i][k][l]->AddEntry((TObject*)0,Form("int/ntrack: %1.3f",(double)vasub2d[0][i][k][l]/(double)ntrack[(i+3)%5][l]),"");
	 lasub2d[0][i][k][l]->Draw();
	 casub2d[i][k][l]->cd(2);
	 int x0 = haresd[(i+3)%5][k][l]->GetXaxis()->FindBin(-100.);
	 int x1 = haresd[(i+3)%5][k][l]->GetXaxis()->FindBin(100.);
	 int y0 = haresd[(i+3)%5][k][l]->GetYaxis()->FindBin(-100.);
	 int y1 = haresd[(i+3)%5][k][l]->GetYaxis()->FindBin(100.);
	 haresd[(i+3)%5][k][l]->Scale(1./(double)mixevent);
	 haresd[(i+3)%5][k][l]->Draw("colz");
	 lasub2d[1][i][k][l] = new TLegend(0.1,0.8,0.7,0.9);
	 vasub2d[1][i][k][l] = Get2DHistSquareIntegral(haresd[(i+3)%5][k][l],voriginx[i][k],voriginy[i][k],vsigmax[i][k],vsigmay[i][k]);
	 lasub2d[1][i][k][l]->AddEntry(haresd[(i+3)%5][k][l],Form("Integral, %d",vasub2d[1][i][k][l]),"l");
	 lasub2d[1][i][k][l]->AddEntry((TObject*)0,Form("int/ntrack (mis-track survival): %1.3f",(double)vasub2d[1][i][k][l]/(double)ntrack[(i+3)%5][l]),"");
	 lasub2d[1][i][k][l]->Draw();
	 missurv[i][k][l] = (double)vasub2d[1][i][k][l]/(double)ntrack[(i+3)%5][l];
	 casub2d[i][k][l]->cd(3);
	 hasub2d[i][k][l] = (TH2F*)hares[(i+3)%5][k][l]->Clone();
	 hasub2d[i][k][l]->SetName(Form("hasub2d%d%d%d",(i+3)%5,k,l));
	 hasub2d[i][k][l]->Add(haresd[(i+3)%5][k][l],-1);
	 hasub2d[i][k][l]->Draw("colz");
	 lasub2d[2][i][k][l] = new TLegend(0.1,0.75,0.6,0.9);
	 hasub2dcopy[i][k][l] = (TH2F*)hasub2d[i][k][l]->Clone();
	 vasub2d[2][i][k][l] = Get2DHistSquareIntegral(hasub2d[i][k][l],hasub2dcopy[i][k][l],voriginx[i][k],voriginy[i][k],vsigmax[i][k],vsigmay[i][k]);
	 lasub2d[2][i][k][l]->AddEntry(hasub2d[i][k][l],Form("Integral(sx:%dmm,sy:%dmm), %d",(int)vsigmax[i][k],(int)vsigmay[i][k],vasub2d[2][i][k][l]),"l");
	 lasub2d[2][i][k][l]->AddEntry((TObject*)0,Form("n_track: %d",ntrack[(i+3)%5][l]),"");
	 lasub2d[2][i][k][l]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasub2d[2][i][k][l]/(double)ntrack[(i+3)%5][l]),"");
	 lasub2d[2][i][k][l]->Draw();
	 effxtrkp[i][k][l] = (double)vasub2d[2][i][k][l]/(double)ntrack[(i+3)%5][l];
	 casub2d[i][k][l]->cd(4)->DrawFrame(-ex_2d[k],-ex_2d[k],ex_2d[k],ex_2d[k]);
	 // hasub2dcopy[i][k][l]->Draw("colz sames");//230205
	 hasub2d[i][k][l]->Draw("colz sames");
       }
     }
   }

   // n_tracks associated LG hits
   for(int i=0;i<5;i++){
     for(int j=0;j<ntrktype;j++){
       int all = 0;
       int woass = 0;
       for(int l=0;l<10;l++){
	 int n_current = hntrackass[i][1][j]->GetBinContent(l+1);
	 double ratio_woass = (double)hntrackassd[i][1][j]->Integral(l+1,10)/(double)hntrackassd[i][1][j]->Integral(1,10);
	 int n_current_woass = (double)n_current*ratio_woass;
	 all += n_current;
	 woass += n_current_woass;
       }
       std::cout<<woass<<" "<<all<<std::endl;
       ntrackass[i][1][j] = all - woass;
     }
   }
   for(int i=0;i<4;i++){
     vasub2d[2][i][1][0] = ntrackass[(i+3)%5][1][0];
     vasub2d[2][i][1][1] = ntrackass[(i+3)%5][1][1];
     effxtrkp[i][1][0] = (double)ntrackass[(i+3)%5][1][0]/(double)ntrack[(i+3)%5][0];
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
       graphx[st] = effxtrkp[i][0][0] + st*(1.-effxtrkp[i][0][0])/((double)step-1.) ;
       veffh[st] = (double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][0][0];
       veffh_err[st] = veffh[st]/sqrt((double)vasub2d[2][i][1][1]);
       veffc[st] = (double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][0][0];
       veffc_err[st] = veffc[st]/sqrt((double)vasub2d[2][i][1][1]);
       vtrkp[st] = (double)vasub2d[2][i][0][0]/(double)ntrack[(i+3)%5][1];
       vtrkp_err[st] = vtrkp[st]/sqrt((double)vasub2d[2][i][0][0]);
       vtrkp2[st] = (double)vasub2d[2][i][1][0]/(double)ntrack[(i+3)%5][2];
       vtrkp2_err[st] = vtrkp[st]/sqrt((double)vasub2d[2][i][1][0]);
       vtrkpa[st] = (double)vasub2d[2][i][1][1]/(double)ntrack[(i+3)%5][3];
       vtrkpb[st] = effxtrkp[i][0][0]/graphx[st];
       veffhb[st] = effxtrkp[i][1][0]/vtrkpb[st];
       veffcb[st] = effxtrkp[i][1][0]/vtrkpb[st];
     }
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
     // gtrkp2[i]->SetMarkerColor(5);
     // gtrkp2[i]->SetLineColor(5);
     // gtrkp2[i]->Draw("LP");
     // gtrkpa[i]->SetMarkerColor(1);
     // gtrkpa[i]->SetLineColor(1);
     // gtrkpa[i]->Draw("LP");
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
       // leff->AddEntry(gtrkp2[2],"TrackPurity w/LG","l");
       // leff->AddEntry(gtrkpa[2],"TrackPurity w/ALL","l");
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

     leff2[i]->AddEntry((TObject*)0,Form("E_HBD(Hit): %d/%d=%1.3f +/- %1.3f",
	 vasub2d[2][i][1][1],vasub2d[2][i][1][0],(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][1][0],
	 sqrt((double)vasub2d[2][i][1][1])/(double)vasub2d[2][i][1][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_HBD(Cls): %d/%d=%1.3f +/- %1.3f",
	 vasub2d[2][i][1][1],vasub2d[2][i][1][0],(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][1][0],
	 sqrt((double)vasub2d[2][i][1][1])/(double)vasub2d[2][i][1][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_LGHit: %d/%d=%1.3f +/- %1.3f",
	 vasub2d[2][i][1][1],vasub2d[2][i][0][0],(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][0][0],
	 sqrt((double)vasub2d[2][i][1][1])/(double)vasub2d[2][i][0][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_LGCls: %d/%d=%1.3f +/- %1.3f",
	 vasub2d[2][i][1][1],vasub2d[2][i][0][0],(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][0][0],
	 sqrt((double)vasub2d[2][i][1][1])/(double)vasub2d[2][i][0][0]),"");

     leff2[i]->AddEntry((TObject*)0,Form("TrkPurity w/HBD: %d/%d=%1.3f +/- %1.3f",
	 vasub2d[2][i][0][0],ntrack[(i+3)%5][1],(double)vasub2d[2][i][0][0]/(double)ntrack[(i+3)%5][1],
	 sqrt((double)vasub2d[2][i][0][0])/(double)ntrack[(i+3)%5][1]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurityB: %d/%d/E_HBD=%1.3f +/- %1.3f",
	 vasub2d[2][i][0][0],ntrack[(i+3)%5][0],(double)vasub2d[2][i][0][0]/(double)ntrack[(i+3)%5][0]/(double)vasub2d[2][i][1][1]*(double)vasub2d[2][i][1][0],
	 sqrt((double)vasub2d[2][i][0][0])/(double)ntrack[(i+3)%5][0]),"");
     // leff2[i]->AddEntry((TObject*)0,Form("TrkPurity w/LG: %d/%d=%1.3f +/- %1.3f",
     // 	 vasub2d[2][i][1][0],ntrack[(i+3)%5][2],(double)vasub2d[2][i][1][0]/(double)ntrack[(i+3)%5][2],
     // 	 sqrt((double)vasub2d[2][i][1][0])/(double)ntrack[(i+3)%5][2]),"");
     // leff2[i]->AddEntry((TObject*)0,Form("TrkPurity w/ALL: %d/%d=%1.3f +/- %1.3f",
     // 	 vasub2d[2][i][1][1],ntrack[(i+3)%5][3],(double)vasub2d[2][i][1][1]/(double)ntrack[(i+3)%5][3],
     // 	 sqrt((double)vasub2d[2][i][1][1])/(double)ntrack[(i+3)%5][3]),"");

     leff2[i]->Draw();
   }
   // if(hbdclthr==1){
   //   std::ofstream psum("purity_wocsa.txt",ios::app);
   //   psum<<hbdthr<<" ";
   //   for(int i=0;i<4;i++){
   //     psum<<(double)vasub2d[2][i][0][0]/(double)ntrack[(i+3)%5][1]<<" "<<sqrt((double)vasub2d[2][i][0][0])/(double)ntrack[(i+3)%5][1]<<" ";
   //   }
   //   psum<<std::endl;
   //   std::ofstream esum("lgeff_wocsa.txt",ios::app);
   //   esum<<hbdthr<<" ";
   //   for(int i=0;i<4;i++){
   //     esum<<(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][0][0]<<" "<<sqrt((double)vasub2d[2][i][1][1])/(double)vasub2d[2][i][0][0]<<" ";
   //   }
   //   esum<<std::endl;
   //   std::ofstream pbsum("purity_wohbd_wocsa.txt",ios::app);
   //   pbsum<<hbdthr<<" ";
   //   for(int i=0;i<4;i++){
   //     pbsum<<(double)vasub2d[2][i][0][0]/(double)ntrack[(i+3)%5][0]/(double)vasub2d[2][i][1][1]*(double)vasub2d[2][i][1][0]<<" "<<sqrt((double)vasub2d[2][i][0][0])/(double)ntrack[(i+3)%5][0]<<" ";
   //   }
   //   pbsum<<std::endl;
   //   std::ofstream hesum("hbdeff_wocsa.txt",ios::app);
   //   hesum<<hbdthr<<" ";
   //   for(int i=0;i<4;i++){
   //     hesum<<(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][1][0]<<" "<<sqrt((double)vasub2d[2][i][1][1])/(double)vasub2d[2][i][1][0]<<" ";
   //   }
   //   hesum<<std::endl;
   // }
   // if(hbdclthr==2){
   //   std::ofstream psum("purity_wcsa.txt",ios::app);
   //   psum<<hbdthr<<" ";
   //   for(int i=0;i<4;i++){
   //     psum<<(double)vasub2d[2][i][0][0]/(double)ntrack[(i+3)%5][1]<<" "<<sqrt((double)vasub2d[2][i][0][0])/(double)ntrack[(i+3)%5][1]<<" ";
   //   }
   //   psum<<std::endl;
   //   std::ofstream esum("lgeff_wcsa.txt",ios::app);
   //   esum<<hbdthr<<" ";
   //   for(int i=0;i<4;i++){
   //     esum<<(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][0][0]<<" "<<sqrt((double)vasub2d[2][i][1][1])/(double)vasub2d[2][i][0][0]<<" ";
   //   }
   //   esum<<std::endl;
   // }
   // Efficiency Summary   
   // std::ofstream fcounts("test.txt",ios::app);
   // for(int i=0;i<4;i++){
   //   fcounts<<ntrack[(i+3)%5][0]<<" "<<ntrack[(i+3)%5][1]<<" "<<ntrack[(i+3)%5][2]<<" "<<vasub2d[2][i][0][0]<<" "<<vasub2d[2][i][1][0]<<std::endl;
   // }

   //draw residual HBD-LG mix
   TCanvas* casubd_hmix[4][nopt][ndet];
   TH1F* hasubd_hmix[4][2][nopt][ndet];
   TF1* fasubd_hmix[4][2][nopt][ndet];
   TLegend* lasubd_hmix[4][2][nopt][ndet];
   int vasubd_hmix[4][2][nopt][ndet];
   for(int k=0;k<ndet;k++){
     for(int j=0;j<nopt;j++){
       for(int i=0;i<4;i++){
	 casubd_hmix[i][j][k] = new TCanvas(Form("casubd%d%d%d",i,j,k),Form("casubd%d%d%d",i,j,k),700,500);
	 casubd_hmix[i][j][k]->Divide(2,2);
	 casubd_hmix[i][j][k]->cd(1);
	 haresx[(i+3)%5][j][k][5]->Draw("hist");
	 haresxd_hmix[(i+3)%5][j][k]->SetLineColor(8);
	 haresxd_hmix[(i+3)%5][j][k]->Draw("hist&&same");
	 haresxd[(i+3)%5][j][k][5]->Draw("hist&&same");
	 gPad->Update();
	 l1[i][0][0][j][k][0]->Draw("same");
	 l2[i][0][0][j][k][0]->Draw("same");
	 casubd_hmix[i][j][k]->cd(2);
	 haresy[(i+3)%5][j][k][5]->Draw("hist");
	 haresyd_hmix[(i+3)%5][j][k]->SetLineColor(8);
	 haresyd_hmix[(i+3)%5][j][k]->Draw("hist&&same");
	 haresyd[(i+3)%5][j][k][5]->Draw("hist&&same");
	 gPad->Update();
	 l1[i][1][0][j][k][0]->Draw("same");
	 l2[i][1][0][j][k][0]->Draw("same");
	 casubd_hmix[i][j][k]->cd(3);
	 hasubd_hmix[i][0][j][k] = (TH1F*)haresx[(i+3)%5][j][k][5]->Clone();
	 hasubd_hmix[i][0][j][k]->SetName(Form("haresxcp%d%d%d",(i+3)%5,j,k));
	 hasubd_hmix[i][0][j][k]->Add(haresxd_hmix[(i+3)%5][j][k],-1);
	 hasubd_hmix[i][0][j][k]->Draw("hist");
	 fasubd_hmix[i][0][j][k] = new TF1(Form("fasubd%dx%d%d",i,j,k),"gaus",-800,800);
	 hasubd_hmix[i][0][j][k]->Fit(Form("fasubd%dx%d%d",i,j,k),"","",-fitregion[k],fitregion[k]);
	 lasubd_hmix[i][0][j][k] = new TLegend(0.1,0.75,0.4,0.9);
	 vasubd_hmix[i][0][j][k] = hasubd_hmix[i][0][j][k]->Integral(roughbin[k]/2-(int)widthx[(i+3)%5][k]*roughbin[k]/1600,roughbin[k]/2+(int)widthy[(i+3)%5][k]*roughbin[k]/1600);
	 lasubd_hmix[i][0][j][k]->AddEntry(hasubd_hmix[i][0][j][k],Form("%d<Integral<%d, %d",-(int)widthx[(i+3)%5][k],(int)widthx[(i+3)%5][k],vasubd_hmix[i][0][j][k]),"l");
	 lasubd_hmix[i][0][j][k]->AddEntry((TObject*)0,Form("n_track: %d",ntrack[(i+3)%5][5]),"");
	 lasubd_hmix[i][0][j][k]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasubd_hmix[i][0][j][k]/(double)ntrack[(i+3)%5][5]),"");
	 lasubd_hmix[i][0][j][k]->Draw();
	 gPad->Update();
	 l1[i][0][1][j][k][0]->Draw("same");
	 l2[i][0][1][j][k][0]->Draw("same");
	 casubd_hmix[i][j][k]->cd(4);
	 hasubd_hmix[i][1][j][k] = (TH1F*)haresy[(i+3)%5][j][k][5]->Clone();
	 hasubd_hmix[i][1][j][k]->SetName(Form("haresycp%d%d%d",(i+3)%5,j,k));
	 hasubd_hmix[i][1][j][k]->Add(haresyd_hmix[(i+3)%5][j][k],-1);
	 hasubd_hmix[i][1][j][k]->Draw("hist");
	 fasubd_hmix[i][1][j][k] = new TF1(Form("fasubd%dy%d%d",i,j,k),"gaus",-800,800);
	 hasubd_hmix[i][1][j][k]->Fit(Form("fasubd%dy%d%d",i,j,k),"","",-fitregion[k],fitregion[k]);
	 lasubd_hmix[i][1][j][k] = new TLegend(0.1,0.75,0.4,0.9);
	 vasubd_hmix[i][1][j][k] = hasubd_hmix[i][1][j][k]->Integral(roughbin[k]/2-(int)widthx[(i+3)%5][k]*roughbin[k]/1600,roughbin[k]/2+(int)widthy[(i+3)%5][k]*roughbin[k]/1600);
	 lasubd_hmix[i][1][j][k]->AddEntry(hasubd_hmix[i][1][j][k],Form("%d<Integral<%d, %d",-(int)widthx[(i+3)%5][k],(int)widthx[(i+3)%5][k],vasubd_hmix[i][1][j][k]),"l");
	 lasubd_hmix[i][1][j][k]->AddEntry((TObject*)0,Form("n_track: %d",ntrack[(i+3)%5][5]),"");
	 lasubd_hmix[i][1][j][k]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasubd_hmix[i][1][j][k]/(double)ntrack[(i+3)%5][5]),"");
	 lasubd_hmix[i][1][j][k]->Draw();
	 gPad->Update();
	 l1[i][1][1][j][k][0]->Draw("same");
	 l2[i][1][1][j][k][0]->Draw("same");
       }
     }
   }

   TCanvas* cdef = new TCanvas("cdef","cdef",700,500);
   cdef->SaveAs(outfile+"[","pdf");
   ceff->SaveAs(outfile,"pdf");
   ceff2->SaveAs(outfile,"pdf");
   chbdhitmap->SaveAs(outfile,"pdf");
   for(int i=0;i<1;i++){
     chitmapc[i]->SaveAs(outfile,"pdf");
     chitmapcd[i]->SaveAs(outfile,"pdf");
     chitmapcsub[i]->SaveAs(outfile,"pdf");
   }
   for(int i=0;i<4;i++){
     cevspe[i]->SaveAs(outfile,"pdf");
     cedivpe[i]->SaveAs(outfile,"pdf");
     ceffe[i]->SaveAs(outfile,"pdf");
     cmome[i]->SaveAs(outfile,"pdf");
     cange[i]->SaveAs(outfile,"pdf");
   }
   ceffeg->SaveAs(outfile,"pdf");
   ceffemg->SaveAs(outfile,"pdf");
   // chbdadcwot->SaveAs(outfile,"pdf");
   // chbdadcwotsub->SaveAs(outfile,"pdf");
   // chbdadcwt->SaveAs(outfile,"pdf");
   // chbdadcwtsub->SaveAs(outfile,"pdf");
   cnlghitwtc->SaveAs(outfile,"pdf");
   cnlghitwtcd->SaveAs(outfile,"pdf");
   ctsvslc->SaveAs(outfile,"pdf");
   ctsvslcd->SaveAs(outfile,"pdf");
   ctsslc->SaveAs(outfile,"pdf");
   ctsslcsub->SaveAs(outfile,"pdf");
   ctdiffc->SaveAs(outfile,"pdf");
   ccogxc->SaveAs(outfile,"pdf");
   ccogyc->SaveAs(outfile,"pdf");
   cthvsp->SaveAs(outfile,"pdf");
   cthvspd->SaveAs(outfile,"pdf");
   cthvspsub->SaveAs(outfile,"pdf");
   ctheta->SaveAs(outfile,"pdf");
   // for(int i=0;i<4;i++){
   //   ccogxcl[i]->SaveAs(outfile,"pdf");
   //   ccogycl[i]->SaveAs(outfile,"pdf");
   // }
   // cevsp->SaveAs(outfile,"pdf");
   // cevspd->SaveAs(outfile,"pdf");
   // cevspsub->SaveAs(outfile,"pdf");
   cevspr->SaveAs(outfile,"pdf");
   cevsprd->SaveAs(outfile,"pdf");
   cevsprsub->SaveAs(outfile,"pdf");
   ceovpvsp->SaveAs(outfile,"pdf");
   ceovpvspd->SaveAs(outfile,"pdf");
   ceovpvspsub->SaveAs(outfile,"pdf");
   // cadc->SaveAs(outfile,"pdf");
   // cadcsub->SaveAs(outfile,"pdf");
   for(int j=0;j<4;j++){
     cedivp[j]->SaveAs(outfile,"pdf");
     cedivpsub[j]->SaveAs(outfile,"pdf");
     cassp[j]->SaveAs(outfile,"pdf");
     casspsub[j]->SaveAs(outfile,"pdf");
     casse[j]->SaveAs(outfile,"pdf");
     cassesub[j]->SaveAs(outfile,"pdf");
   }
   // for(int j=0;j<4;j++){
   //   cesubp[j]->SaveAs(outfile,"pdf");
   // }
   // cexp->SaveAs(outfile,"pdf");
   for(int l=0;l<ntrktype;l++){
     if(l==1||l==2||l==3) continue;
     cnt[l]->SaveAs(outfile,"pdf");
     for(int k=0;k<ndet;k++){
       cn[k][l]->SaveAs(outfile,"pdf");
       cnd[k][l]->SaveAs(outfile,"pdf");
       for(int i=0;i<4;i++){
	 for(int j=0;j<nopt;j++){
	   casubd[i][j][k][l]->SaveAs(outfile,"pdf");
	 }
	 casub2d[i][k][l]->SaveAs(outfile,"pdf");
       }
       ct[k][l]->SaveAs(outfile,"pdf");
       std::cout<<det[k]<<" "<<trktype[l]<<"end"<<std::endl;
     }
   }
   for(int i=0;i<4;i++){
     for(int j=0;j<nopt;j++){
       casubd_hmix[i][j][1]->SaveAs(outfile,"pdf");
     }
   }
   cnlghitwtc_hmix->SaveAs(outfile,"pdf");
   cnlghitwtcd_hmix->SaveAs(outfile,"pdf");
   ctdiffc_hmix->SaveAs(outfile,"pdf");
   ccogxc_hmix->SaveAs(outfile,"pdf");
   ccogyc_hmix->SaveAs(outfile,"pdf");
   cevspr_hmix->SaveAs(outfile,"pdf");
   cevsprd_hmix->SaveAs(outfile,"pdf");
   cevsprsub_hmix->SaveAs(outfile,"pdf");
   ceovpvsp_hmix->SaveAs(outfile,"pdf");
   ceovpvspd_hmix->SaveAs(outfile,"pdf");
   ceovpvspsub_hmix->SaveAs(outfile,"pdf");
   for(int j=0;j<4;j++){
     cedivp_hmix[j]->SaveAs(outfile,"pdf");
     cedivpsub_hmix[j]->SaveAs(outfile,"pdf");
     cassp_hmix[j]->SaveAs(outfile,"pdf");
     casspsub_hmix[j]->SaveAs(outfile,"pdf");
     casse_hmix[j]->SaveAs(outfile,"pdf");
     cassesub_hmix[j]->SaveAs(outfile,"pdf");
   }

   cdef->SaveAs(outfile+"]","pdf");

   g->Write();
   fouthist->Write();
   fouthist->Close();
   delete geometry;

}

void E16ANA_EIDEfficiency::LGGainCalibwTrack(int runoption, int maxevent, char* out_file_name, char* out_root_name)
{

   if (fChain == 0) return;

   bool gaincalib = false;

   TFile *fout = new TFile(out_root_name,"recreate");
   TTree* tree = new TTree("tree","tree");
   int out_run_id;
   int out_run_purpose;
   int out_event_id;
   //block
   int out_mid; 
   int out_cid;
   double out_adc;
   double out_resx;
   //track
   double out_posx;
   double out_anglex;
   double out_length;
   double out_rk_charge;
   double out_mom;
   bool out_w_trg;
   bool out_w_trg_gtr;
   bool out_w_trg_hbd;
   int out_w_trg_lg;
   bool out_w_trg_trk;
   double out_hbd_adc;
   int out_hbd_csize;

   tree->Branch("run_id",&out_run_id,"run_id/I");
   tree->Branch("run_purpose",&out_run_purpose,"run_purpose/I");
   tree->Branch("event_id",&out_event_id,"event_id/I");
   tree->Branch("mid",&out_mid,"mid/I");
   tree->Branch("cid",&out_cid,"cid/I");
   tree->Branch("adc",&out_adc,"adc/D");
   tree->Branch("resx",&out_resx,"resx/D");
   tree->Branch("posx",&out_posx,"posx/D");
   tree->Branch("anglex",&out_anglex,"anglex/D");
   tree->Branch("length",&out_length,"length/D");
   tree->Branch("rk_charge",&out_rk_charge,"rk_charge/D");
   tree->Branch("mom",&out_mom,"mom/D");
   tree->Branch("w_trg",&out_w_trg,"w_trg/O");
   tree->Branch("w_trg_gtr",&out_w_trg_gtr,"w_trg_gtr/O");
   tree->Branch("w_trg_hbd",&out_w_trg_hbd,"w_trg_hbd/O");
   tree->Branch("w_trg_lg",&out_w_trg_lg,"w_trg_lg/I");
   tree->Branch("w_trg_trk",&out_w_trg_trk,"w_trg_trk/O");
   tree->Branch("hbd_adc",&out_hbd_adc,"hbd_adc/D");
   tree->Branch("hbd_csize",&out_hbd_csize,"hbd_csize/I");

   TH1F* hadc[7][60];
   TH1F* hadcd[7][60];
   TH1F* hresx[7];
   TH1F* hresy[7];
   TH1F* hresxd[7];
   TH1F* hresyd[7];
   int ass_hit[7]={0};
   int ass_hitd[7]={0};
   int ass_track[7]={0};
   for(int i=0;i<7;i++){
     hresx[i] = new TH1F(Form("hresx%d",i),Form("LGresidualX_mid%d",i+102),100,-800,800);
     hresy[i] = new TH1F(Form("hresy%d",i),Form("LGresidualY_mid%d",i+102),100,-800,800);
     hresxd[i] = new TH1F(Form("hresxd%d",i),Form("LGresidualX_dummy_mid%d",i+102),100,-800,800);
     hresyd[i] = new TH1F(Form("hresyd%d",i),Form("LGresidualY_dummy_mid%d",i+102),100,-800,800);
     for(int j=0;j<60;j++){
       hadc[i][j] = new TH1F(Form("hadc%d%d",i,j),Form("LGadc_mid%d_cid%d",i+102,j),100,0,200);
       hadcd[i][j] = new TH1F(Form("hadcd%d%d",i,j),Form("LGadc_dummy_mid%d_cid%d",i+102,j),100,0,200);
     }
   }

   int mixevent = 50;
   double ssdoffset = 51.;
   double ssdregion = 11.;

   const int ndet=2;
   char det[ndet][20] = {"HBD","LGHit"};
   double originx[5][ndet];
   double originy[5][ndet];
   double widthx[5][ndet];
   double widthy[5][ndet];
   for(int i=0;i<5;i++){
     originx[i][0]=0.;
     originy[i][0]=0.;
     widthx[i][0]=25.;
     widthy[i][0]=25.;
     originx[i][1]=0.;
     originy[i][1]=0.;
     widthx[i][1]=100.;
     widthy[i][1]=50.;
   }
   if(runoption==1){
     //HBD
     originx[0][0]= 6.0;//103
     originy[0][0]=-1.1;
     originx[1][0]= 4.8;//104
     originy[1][0]= 0. ;
     originx[3][0]=-5.7;//106
     originy[3][0]=-1.6;
     originx[4][0]= 2.2;//107
     originy[4][0]= 1.3;
   }

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

     int ntrk[5]={0};
     bool alfill[2][5]={false};//for mixing
     std::vector<hitset> hbdhits[5];//for mixing
     std::vector<hitset> lghits[5];//for mixing
     std::vector<trackset> tracksets;//kill dup

     for(int itrack=0;itrack<n_tracks;itrack++){//track loop

       if (TrackSelection(ientry,itrack,runoption) < 0) continue;
       int runp = E16ANA_EIDSingleTrackAnalyzer::KsRunPurpose(run_id);
       // if( (int)runp/10!=1 ) continue;

       //Search near HBD hit
       int hmide = track_hbd_mid->at(itrack)-103;
       int lmide = track_lg_mid->at(itrack)-103;
       double resx_min = 10000.;
       double resy_min = 10000.;
       double adc_max = -10000.;
       int csize = -10000;
       for(int ihbd=0;ihbd<track_hbd_multiplicity->at(itrack);ihbd++){
	 double resx = track_hbd_allhit_resx->at(itrack).at(ihbd)-originx[hmide][0];
	 double resy = track_hbd_allhit_resy->at(itrack).at(ihbd)-originy[hmide][0];
	 if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	   resx_min=resx;
	   resy_min=resy;
	 }
	 if(fabs(resx)<widthx[hmide][0]&&fabs(resy)<widthy[hmide][0]){
	   if(adc_max<track_hbd_allhit_adc->at(itrack).at(ihbd)){
	     adc_max = track_hbd_allhit_adc->at(itrack).at(ihbd);
	     csize = track_hbd_allhit_size->at(itrack).at(ihbd);
	   }
	 }
       }
       bool HBDhit=false;
       if( fabs(resx_min)<widthx[hmide][0] && fabs(resy_min)<widthy[hmide][0] ){
	 HBDhit=true;
       }
       //Search near LG hit
       bool LGhit=false;
       int nlgh=0;
       for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){
	 double resx = track_lg_allhit_resx->at(itrack).at(ilg)-originx[lmide][1];
	 double resy = track_lg_allhit_resy->at(itrack).at(ilg)-originy[lmide][1];
	 double tmptdc = track_lg_allhit_ftime->at(itrack).at(ilg);
	 if(tmptdc<(ssdoffset-ssdregion)+track_ssd_t->at(itrack)||tmptdc>(ssdoffset+ssdregion)+track_ssd_t->at(itrack)) continue;//220418
	 if( fabs(resx)<widthx[lmide][1] && fabs(resy)<widthy[lmide][1] ){
	   LGhit=true;
	 }
	 nlgh++;
       }

       int btrktype=-1;
       if(HBDhit){//240322
       	 // btrktype=IsGoodTrack(ientry,itrack,tracksets);
       	 btrktype=IsGoodTrackWHBD(ientry,itrack,tracksets,adc_max);
       }
       // btrktype=IsGoodTrack(ientry,itrack,tracksets);//220825

       if(btrktype<0) continue;

       //LG Fill
       out_run_id = run_id;
       out_run_purpose = E16ANA_EIDSingleTrackAnalyzer::KsRunPurpose(out_run_id);
       out_event_id = event_id;
       out_mid = track_lg_mid->at(itrack);
       out_hbd_adc = adc_max;
       out_hbd_csize = csize;
       int ass_track_flag = 0;
       for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){//lgfore
	 double resx = track_lg_allhit_resx->at(itrack).at(ilg);
	 double resy = track_lg_allhit_resy->at(itrack).at(ilg);
	 double rxs = resx-originx[lmide][1];
	 double rys = resy-originy[lmide][1];
	 double tmpadc = track_lg_allhit_adc->at(itrack).at(ilg);
	 double tmptdc = track_lg_allhit_ftime->at(itrack).at(ilg);
	 int cid = E16ANA_EIDSingleTrackAnalyzer::LocaltoCh(resx+track_lg_lx->at(itrack),resy+track_lg_ly->at(itrack));
	 double gain=1.;
	 if(cid>=0&&cid<56){gain=relg[1][lmide][cid/10][cid%10]*40;}
	 if(gaincalib){tmpadc=tmpadc*gain;}
	 if(tmptdc<(ssdoffset-ssdregion)+track_ssd_t->at(itrack)||tmptdc>(ssdoffset+ssdregion)+track_ssd_t->at(itrack)) continue;//220418
	 if(fabs(rys)<widthy[lmide][1]){
	   hresx[out_mid-102]->Fill(resx);
	   hresx[3]->Fill(resx);
	 }
	 if(fabs(rxs)<widthx[lmide][1]){
	   hresy[out_mid-102]->Fill(resx);
	   hresy[3]->Fill(resx);
	 }
	 if( fabs(resx)<widthx[lmide][1] && fabs(resy)<widthy[lmide][1] ){
	   ass_track_flag = 1;
	   ass_hit[out_mid-102]++;
	   out_cid = cid;
	   out_adc = tmpadc;
	   out_resx = resx;
	   out_posx = track_position_block_lx->at(itrack);
	   out_anglex = track_angle_lx->at(itrack);
	   //y=tt*x+b
	   double tt = tan(out_anglex);
	   double b = -resx;
	   double y135 = tt*135.+b;
	   double p[2]={0.};
	   double q[2]={0.};
	   if(b>61){
	     if(y135>61){
	       //not cross
	     }
	     else if(y135>-61&&y135<=61){
	       p[0]=(61.-b)/tt;p[1]=61.;
	       q[0]=135.;q[1]=y135;
	     }
	     else{
	       p[0]=(61.-b)/tt;p[1]=61.;
	       q[0]=(-61.-b)/tt;q[1]=-61.;
	     }
	   }
	   else if(b>-61&&b<=61){
	     p[0]=0.;p[1]=b;
	     if(y135>61){
	       q[0]=(61.-b)/tt;q[1]=61.;
	     }
	     else if(y135>-61&&y135<=61){
	       q[0]=135.;q[1]=y135;
	     }
	     else{
	       q[0]=(-61.-b)/tt;q[1]=-61.;
	     }
	   }
	   else{
	     if(y135>61){
	       p[0]=(-61.-b)/tt;p[1]=-61.;
	       q[0]=(61.-b)/tt;q[1]=61.;
	     }
	     else if(y135>-61&&y135<=61){
	       p[0]=(-61.-b)/tt;p[1]=-61.;
	       q[0]=135.;q[1]=y135;
	     }
	     else{
	       //not cross
	     }
	   }
	   out_length = sqrt((q[0]-p[0])*(q[0]-p[0])+(q[1]-p[1])*(q[1]-p[1]));
	   out_rk_charge = rk_charge->at(itrack);
	   out_mom = track_mom->at(itrack);
	   out_w_trg = track_w_trg_bias->at(itrack);
	   out_w_trg_gtr = track_w_trg_gtr->at(itrack);
	   out_w_trg_hbd = track_w_trg_hbd->at(itrack);
	   out_w_trg_lg = track_w_trg_lg->at(itrack);
	   out_w_trg_trk = track_w_trg_trk->at(itrack);

	   tree->Fill();
	   hadc[out_mid-102][cid]->Fill(tmpadc);
	 }
       }//lgfore
       ass_track[out_mid-102]+=ass_track_flag;

       if(lgmixhits[lmide].size()!=0){//calc mix
       	 for(int ilg=0;ilg<lgmixhits[lmide].size();ilg++){//lghit loop
       	   int nlgh_dum = 0;
       	   for(int jlg=0;jlg<lgmixhits[lmide].at(ilg).size();jlg++){
       	     double tmpresx = lgmixhits[lmide].at(ilg).at(jlg).lx-track_lg_lx->at(itrack);
       	     double tmpresy = lgmixhits[lmide].at(ilg).at(jlg).ly-track_lg_ly->at(itrack);
       	     double tmprxs = tmpresx - originx[lmide][1];
       	     double tmprys = tmpresy - originy[lmide][1];
       	     double tmpt = lgmixhits[lmide].at(ilg).at(jlg).tdc;
       	     double tmpa = lgmixhits[lmide].at(ilg).at(jlg).adc;
	     int cid = E16ANA_EIDSingleTrackAnalyzer::LocaltoCh(lgmixhits[lmide].at(ilg).at(jlg).lx,lgmixhits[lmide].at(ilg).at(jlg).ly);
	     double gain=1.;
	     if(cid>=0&&cid<56){gain=relg[1][lmide][cid/10][cid%10]*40;}
	     if(gaincalib){tmpa=tmpa*gain;}
	     if( fabs(tmpresy)<widthy[lmide][1] ){
	       hresxd[lmide+103-102]->Fill(tmpresx);
	     }
	     if( fabs(tmpresx)<widthx[lmide][1] ){
	       hresyd[lmide+103-102]->Fill(tmpresy);
	     }
	     if( fabs(tmpresx)<widthx[lmide][1] && fabs(tmpresy)<widthy[lmide][1] ){
	       ass_hitd[lmide+103-102]++;
	       hadcd[lmide+103-102][cid]->Fill(tmpa);
	     }
       	     nlgh_dum++;
       	   }
       	 }//lghit loop
       }//calc mix

	//fill mixing hit
       if(alfill[0][hmide]==false){
	 alfill[0][hmide]=true;
	 for(int ihbd=0;ihbd<track_hbd_multiplicity->at(itrack);ihbd++){
	   hitset hbdhit;
	   hbdhit.mid=track_hbd_mid->at(itrack);
	   hbdhit.lx=track_hbd_allhit_resx->at(itrack).at(ihbd)+track_hbd_lx->at(itrack);
	   hbdhit.ly=track_hbd_allhit_resy->at(itrack).at(ihbd)+track_hbd_ly->at(itrack);
	   hbdhit.adc=track_hbd_allhit_adc->at(itrack).at(ihbd);
	   hbdhit.tdc=track_hbd_allhit_ftime->at(itrack).at(ihbd);
	   hbdhits[hmide].push_back(hbdhit);
	 }
       }
       if(alfill[1][lmide]==false){


	 alfill[1][lmide]=true;
	 for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){
	   double tmpt = track_lg_allhit_ftime->at(itrack).at(ilg);
	   if(tmpt<(ssdoffset-ssdregion)+track_ssd_t->at(itrack)||tmpt>(ssdoffset+ssdregion)+track_ssd_t->at(itrack)) continue;
	   hitset lghit;
	   lghit.mid=track_lg_mid->at(itrack);
	   lghit.lx=track_lg_allhit_resx->at(itrack).at(ilg)+track_lg_lx->at(itrack);
	   lghit.ly=track_lg_allhit_resy->at(itrack).at(ilg)+track_lg_ly->at(itrack);
	   lghit.adc=track_lg_allhit_adc->at(itrack).at(ilg);
	   lghit.tdc=tmpt;
	   lghits[lmide].push_back(lghit);
	 }
       }
       //fill mixing hit

       ntrk[hmide]++;

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
     }
     nevent++;

   }//event loop


   //Draw canvas
   TString outfile = Form("%s",out_file_name);
   TCanvas* c[7];
   TLine* l[7][42];
   for(int i=0;i<7;i++){
     c[i] = new TCanvas(Form("c%d",i),Form("c%d",i),1400,1000);
     c[i]->Divide(7,6);
     for(int j=0;j<42;j++){
       c[i]->cd(42-j);
       int tmpch = (j/7)*10 + j%7;
       hadc[i][tmpch]->Draw();
       hadcd[i][tmpch]->Scale(1./(double)mixevent);
       hadcd[i][tmpch]->SetLineColor(6);
       hadcd[i][tmpch]->SetMarkerColor(6);
       hadcd[i][tmpch]->Draw("hist&&sames");
       if(i==2||i==4){
         gPad->Update();
         l[i][j] = new TLine(98.,gPad->GetUymin(),98.,gPad->GetUymax());
       }
       else{
         gPad->Update();
         l[i][j] = new TLine(49.,gPad->GetUymin(),49.,gPad->GetUymax());
       }
       l[i][j]->SetLineColor(2);
       l[i][j]->Draw("sames");
     }
   }
   TCanvas* cresx = new TCanvas("cresx","cresx",1400,700);
   cresx->Divide(3,2);
   for(int i=0;i<7;i++){
     if(i==3) continue;
     cresx->cd(i+1-(i/4));
     hresx[i]->Draw();
     hresxd[i]->Scale(1./(double)mixevent);
     hresxd[i]->SetLineColor(6);
     hresxd[i]->SetMarkerColor(6);
     hresxd[i]->Draw("hist&&sames");
     double purity = (double)(ass_hit[i]-ass_hitd[i]/50)/(double)ass_track[i];
     std::cout<<i<<" "<<i+1-(i/4)<<" "<<ass_hit[i]<<" "<<ass_hitd[i]/50<<" "<<ass_track[i]<<" "<<purity<<std::endl;
   }

   TCanvas* cdef = new TCanvas("cdef","cdef",700,500);
   cdef->SaveAs(outfile+"[","pdf");
   for(int i=0;i<7;i++){
     c[i]->SaveAs(outfile,"pdf");
   }
   cresx->SaveAs(outfile,"pdf");
   cdef->SaveAs(outfile+"]","pdf");

   fout->Write();
   fout->Close();

}
