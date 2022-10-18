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
#include <TRandom.h>

#include <TH1.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "TROOT.h"

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

// double AnalyzerTrackSelection::CalcADCNearHit(std::vector<hitset>& lgnear, double ssdt){
//   sort(lgnear.begin(),lgnear.end());
//   double diffmin=10000;
//   double adc1=0;
//   double adc2=0;
//   for(int i=0;i<lgnear.size();i++){
//     if(i=lgnear.size()-1) break;
//     if((lgnear.at(i+1).tdc-lgnear.at(i).tdc)<diffmin){
//       adc1 = lgnear.at(i).adc;
//       adc2 = lgnear.at(i+1).adc;
//       diffmin=lgnear.at(i+1).tdc-lgnear.at(i).tdc;
//     }
//   }
//   return adc1+adc2;
// }

double AnalyzerTrackSelection::CalcADCNearHit(std::vector<hitset>& lgnear, double ssdt, lgcls& lgcluster){
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
  for(int i=0;i<nadc;i++){
    adcsum += lgcluster.adcs.at(i);
    cogx += lgcluster.resxs.at(i)*lgcluster.adcs.at(i);
    cogy += lgcluster.resys.at(i)*lgcluster.adcs.at(i);
  }
  cogx = cogx/adcsum;
  cogy = cogy/adcsum;
  double timediff = lgcluster.tdcs.at(nadc-1) - lgcluster.tdcs.at(0);
  lgcluster.adcsum = adcsum;
  lgcluster.timediff = timediff;
  lgcluster.cogx = cogx;
  lgcluster.cogy = cogy;

  // std::cout<<(maxadc-lgcluster.adcsum)<<std::endl;

  return maxadc;
}

double AnalyzerTrackSelection::CalcADCNearHitV2(std::vector<hitset>& lgnear, double ssdt, lgcls& lgcluster){

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
      if(adc>maxadc&&fabs(ssdt+51.-tmp.tdcs.at(0))<11.){
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
  if(adc>maxadc&&fabs(ssdt+51.-tmp.tdcs.at(0))<11.){
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
    for(int i=0;i<nadc;i++){
      adcsum += lgcluster.adcs.at(i);
      cogx += lgcluster.resxs.at(i)*lgcluster.adcs.at(i);
      cogy += lgcluster.resys.at(i)*lgcluster.adcs.at(i);
    }
    cogx = cogx/adcsum;
    cogy = cogy/adcsum;
    double timediff = lgcluster.tdcs.at(nadc-1) - lgcluster.tdcs.at(0);
    lgcluster.adcsum = adcsum;
    lgcluster.timediff = timediff;
    lgcluster.cogx = cogx;
    lgcluster.cogy = cogy;
  }

  // std::cout<<(maxadc-lgcluster.adcsum)<<std::endl;

  return maxadc;
}

double AnalyzerTrackSelection::CalcADCNearHitV3(std::vector<hitset>& lgnear, double ssdt, lgcls& lgcluster){
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
      if( fabs(ssdt+51.-tdc)<mintdcdiff && fabs(ssdt+51.-tmp.tdcs.at(0))<11. ){
	mintdcdiff=fabs(ssdt+51.-tdc);
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
  if( fabs(ssdt+51.-tdc)<mintdcdiff && fabs(ssdt+51.-tmp.tdcs.at(0))<11. ){
    mintdcdiff=fabs(ssdt+51.-tdc);
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
    for(int i=0;i<nadc;i++){
      adcsum += lgcluster.adcs.at(i);
      cogx += lgcluster.resxs.at(i)*lgcluster.adcs.at(i);
      cogy += lgcluster.resys.at(i)*lgcluster.adcs.at(i);
    }
    cogx = cogx/adcsum;
    cogy = cogy/adcsum;
    double timediff = lgcluster.tdcs.at(nadc-1) - lgcluster.tdcs.at(0);
    lgcluster.adcsum = adcsum;
    lgcluster.timediff = timediff;
    lgcluster.cogx = cogx;
    lgcluster.cogy = cogy;
    maxadc = adcsum;
  }
  // std::cout<<(maxadc-lgcluster.adcsum)<<std::endl;

  return maxadc;
}

double AnalyzerTrackSelection::CalcMaxADCNearHit(std::vector<hitset>& lgnear, double ssdt){
  double adc=-10000.;
  for(int i=0;i<lgnear.size();i++){
    if(adc<lgnear.at(i).adc){
      adc = lgnear.at(i).adc;
    }
  }
  return adc;
}

double AnalyzerTrackSelection::CalcSumADCNearHit(std::vector<hitset>& lgnear, double ssdt){
  double adc=0;
  for(int i=0;i<lgnear.size();i++){
    if(fabs(lgnear.at(i).tdc-(ssdt+51.))<11.){
      adc += lgnear.at(i).adc;
    }
  }
  return adc;
}

bool IsNeighborBlock(E16ANA_GeometryV2& geometry, int cid, int cent_cid){

  // std::cout<<"cid:"<<cid<<" cent:"<<cent_cid<<" ";
  TVector3 gpos = {-10000.,-10000.,-10000.};
  TVector3 lpos = {-10000.,-10000.,-10000.};
  gpos = geometry.LG( 0, cid )->GetDetectorCenter();
  lpos = geometry.LGVD( 0 )->GetLPos(gpos);
  TVector3 gposc = {-10000.,-10000.,-10000.};
  TVector3 lposc = {-10000.,-10000.,-10000.};
  gposc = geometry.LG( 0, cent_cid )->GetDetectorCenter();
  lposc = geometry.LGVD( 0 )->GetLPos(gposc);
  if( fabs(lpos.X()-lposc.X())<150 && fabs(lpos.Y()-lposc.Y())<170 ){
    // std::cout<<"o"<<std::endl;
    return true;
  }
  // std::cout<<"x"<<std::endl;
  return false;
}

void CalcClusterCand(E16ANA_GeometryV2& geometry, std::vector<int>& trk_ass_cids, int blockch, double position_block_lx, double position_block_ly, double angle_lx){

  double r_moliere = 28.;//mm
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

  //
  // if(fabs(position_block_ly)>60){
  //   int chx = blockch%10;
  //   int chy = blockch/10;
  //   for(int i=chx-1;i<=chx+1;i++){
  //     int tmpcid = (chy+1)*10+i;
  //     if( ChExist(tmpcid) && IsNeighborBlock(geometry,tmpcid,blockch) ){
  // 	trk_ass_cids.push_back(tmpcid);
  //     }
  //     tmpcid = (chy-1)*10+i;
  //     if( ChExist(tmpcid) && IsNeighborBlock(geometry,tmpcid,blockch) ){
  // 	trk_ass_cids.push_back(tmpcid);
  //     }
  //   }
  // }
  //

  // if(trk_ass_cids.size()>2){
  //   std::cout<<trk_ass_cids.size()<<" "<<position_block_lx<<" "<<angle_lx<<" "<<position_block_ly<<" :: ";
  //   for(int i=0;i<trk_ass_cids.size();i++){
  //     std::cout<<trk_ass_cids.at(i)<<" ";
  //   }
  //   std::cout<<std::endl;
  // }

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

double CalcCalibPar(double proj_y, int blockch, double& dist){

  double bpos_pmt_r[6] = {1417.4, 1587.0, 1748.2, 1748.2, 1587.0, 1417.4};
  double bpos_pmt_y[6] = {-363.6, -278.6, -159.9,  159.9,  278.6,  363.6};
  double bpos_cut_r[6] = {1455.4, 1614.4, 1765.4, 1765.4, 1614.4, 1455.4};
  double bpos_cut_y[6] = {-246.4, -138.9,   -6.5,    6.5,  138.9,  246.4};
  double plane_r[6]    = {1436.4, 1600.7, 1756.8, 1756.8, 1600.7, 1436.4};

  int bly = blockch/10;
  TVector2 bpos_pmt(bpos_pmt_r[bly],bpos_pmt_y[bly]);
  TVector2 bpos_cut(bpos_cut_r[bly],bpos_cut_y[bly]);
  TVector2 proj(plane_r[bly],proj_y);
  TVector2 cs = CalcCrossPoint(bpos_pmt,bpos_cut,proj);
  dist = sqrt( (cs.X()-bpos_pmt.X())*(cs.X()-bpos_pmt.X()) + (cs.Y()-bpos_pmt.Y())*(cs.Y()-bpos_pmt.Y()) );
  return 1./CalibFunction(dist);
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
      if (SelectGoodTrack(ientry,goodtracks,hbd_voriginx,hbd_voriginy,hbd_vsigmax,hbd_vsigmay) < 0) continue;
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

// void AnalyzerTrackSelection::MkMixingHist(int runoption, int maxevent)
// {

//    if (fChain == 0) return;

//    TFile *fouthist = new TFile("mixing.root","recreate");

//    struct hitset{
//      int mid;
//      double lx;
//      double ly;
//      double adc;
//      double tdc;
//    };

//    std::vector<hitset> hbdmixhits[5];
//    std::vector<hitset> lgmixhits[5];
//    int roughbin[5] = {800,100,100,100,100};//bin
//    TH1F *hbdresxmix[5];
//    TH1F *hbdresymix[5];
//    TH1F *lgresxmix[5];
//    TH1F *lgresymix[5];
//    for(int i=0;i<5;i++){
//      hbdresxmix[i] = new TH1F(Form("hbdresxmix%d",i),Form("hbd_resx_mix_mod%d",103+i),roughbin[0],-800,800);
//      hbdresymix[i] = new TH1F(Form("hbdresymix%d",i),Form("hbd_resy_mix_mod%d",103+i),roughbin[0],-800,800);
//      lgresxmix[i] = new TH1F(Form("lgresxmix%d",i),Form("lg_resx_mix_mod%d",103+i),roughbin[1],-800,800);
//      lgresymix[i] = new TH1F(Form("lgresymix%d",i),Form("lg_resy_mix_mod%d",103+i),roughbin[1],-800,800);
//    }

//    double track_select_sigma = 2.;
//    double hbd_voriginx[4]={0.};
//    double hbd_voriginy[4]={0.};
//    double hbd_vsigmax[4]={25.,25.,25.,25.};
//    double hbd_vsigmay[4]={25.,25.,25.,25.};

//    Long64_t n_entries = fChain->GetEntries();
//    Long64_t nentries = fChain->GetEntriesFast();
//    Long64_t nbytes = 0, nb = 0;

//    int nevent=0;
//    for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
//       Long64_t ientry = LoadTree(jentry);
//       if (ientry < 0) break;
//       nb = fChain->GetEntry(jentry);   nbytes += nb;

//       if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
//       if( maxevent!=-1&&nevent>maxevent ){break;}

//       std::vector<int> goodtracks;
//       if (SelectGoodTrack(ientry,goodtracks,hbd_voriginx,hbd_voriginy,hbd_vsigmax,hbd_vsigmay) < 0) continue;
//       // if (Cut(ientry) < 0) continue;//220407

//       bool alfill[5]={false};

//       for(int itrack=0;itrack<n_tracks;itrack++){//track loop

//       	if (CutOfTrack(ientry,itrack,goodtracks) < 0) continue;
//       	// if (CutOfTrack(ientry,itrack,runoption) < 0) continue;//220407

//       	int mide = track_hbd_mid->at(itrack)-103;
//       	if(alfill[mide]==false){//hit fill
//       	  alfill[mide]=true;
//       	  for(int ihbd=0;ihbd<track_hbd_multiplicity->at(itrack);ihbd++){
//       	    hitset hbdhit;
//       	    hbdhit.mid=track_hbd_mid->at(itrack);
//       	    hbdhit.lx=track_hbd_allhit_resx->at(itrack).at(ihbd)+track_hbd_lx->at(itrack);
//       	    hbdhit.ly=track_hbd_allhit_resy->at(itrack).at(ihbd)+track_hbd_ly->at(itrack);
//       	    hbdhit.adc=track_hbd_allhit_adc->at(itrack).at(ihbd);
//       	    hbdhit.tdc=track_hbd_allhit_ftime->at(itrack).at(ihbd);
//       	    hbdmixhits[mide].push_back(hbdhit);
//       	  }
//       	  for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){
//       	    hitset lghit;
//       	    lghit.mid=track_lg_mid->at(itrack);
//       	    lghit.lx=track_lg_allhit_resx->at(itrack).at(ilg)+track_lg_lx->at(itrack);
//       	    lghit.ly=track_lg_allhit_resy->at(itrack).at(ilg)+track_lg_ly->at(itrack);
//       	    lghit.adc=track_lg_allhit_adc->at(itrack).at(ilg);
//       	    lghit.tdc=track_lg_allhit_ftime->at(itrack).at(ilg);
//       	    lgmixhits[mide].push_back(lghit);
//       	  }
//       	}//hit fill
//       	if(hbdmixhits[mide].size()==0||lgmixhits[mide].size()==0) continue;
//       	for(int ihbd=0;ihbd<hbdmixhits[mide].size();ihbd++){
//       	  hbdresxmix[mide]->Fill(hbdmixhits[mide].at(ihbd).lx-track_hbd_lx->at(itrack));
//       	  hbdresymix[mide]->Fill(hbdmixhits[mide].at(ihbd).ly-track_hbd_ly->at(itrack));
//       	}
//       	for(int ilg=0;ilg<lgmixhits[mide].size();ilg++){
//       	  lgresxmix[mide]->Fill(lgmixhits[mide].at(ilg).lx-track_lg_lx->at(itrack));
//       	  lgresymix[mide]->Fill(lgmixhits[mide].at(ilg).ly-track_lg_ly->at(itrack));
//       	}
// 	if(hbdmixhits[mide].size()>500){
// 	  hbdmixhits[mide].clear();
// 	}
// 	if(lgmixhits[mide].size()>500){
// 	  lgmixhits[mide].clear();
// 	}

//       }//track loop

//       nevent++;

//    }//event loop

//    // TString outfile = Form("%s",out_file_name);

//    // gStyle->SetOptStat(11111111);
//    // gStyle->SetOptFit(11111111);

//    // TCanvas* cdef = new TCanvas("cdef","cdef",700,500);
//    // cdef->SaveAs(outfile+"[","pdf");
//    // cdef->SaveAs(outfile+"]","pdf");

//    fouthist->Write();
//    fouthist->Close();

// }

void AnalyzerTrackSelection::DrawForLGEfficiency(int runoption, int maxevent, char* out_file_name, char* out_root_name, double hbdthr, int hbdclthr)
{

   if (fChain == 0) return;

   TFile *fouthist = new TFile(out_root_name,"recreate");
   auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
   // std::ofstream evspout[5];
   // for(int i=0;i<5;i++){
   //   std::string mod = to_string(i+103);
   //   std::string evspoutname = "evsp" + mod + ".txt";
   //   evspout[i].open(evspoutname);
   // }

   int bene = 0;
   double enepar[4] = {1.,40.,80.,198.};
   int ienepar[4] = {1,40,80,200};

   bool gaincalib = false;
   bool fwdonly = false;
   bool hbdass_in_dst1 = false;
   bool new_cluster_method = true;//221006
   bool w_calib_pos_dep = false;//ashikaga masters thesis paramter
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
   int roughbin[ndet] = {200,50};//bin;
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
     if(runoption==4){widthx[i][0]=35.;widthy[i][0]=35.;}
     if(runoption==0){widthx[i][0]=35.;widthy[i][0]=35.;}
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
   for(int i=0;i<5;i++){
     for(int j=0;j<ntrktype;j++){
       ntrack[i][j]=0;
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
   TH1F* trkmom[5];
   TH1F* hexp[5];
   TH1F* hadc[5];
   TH1F* hadcd[5];
   TH2F* hevsp[5];
   TH2F* hevspd[5];
   TH2F* hevspr[5];
   TH2F* hevsprd[5];
   TH2F* heovpvsp[5];
   TH2F* heovpvspd[5];
   TH1F* hedivp[4][5];
   TH1F* hedivpd[4][5];
   TH1F* hassp[4][5];
   TH1F* hasspd[4][5];
   TH1F* hasse[4][5];
   TH1F* hassed[4][5];
   TH1F* hesubp[4][5];
   TH1F* hesubpd[4][5];
   TH1F* hnlghitwtc[5];//clutser
   TH1F* hnlghitwtcd[5];//clutser
   TH2F* hhitmapc[4][5];//clutser
   TH2F* hhitmapcd[4][5];//clutser
   TH2F* htsvslc[5];//clutser
   TH2F* htsvslcd[5];//clutser
   TH1F* htdiffc[5];//clutser
   TH1F* htdiffcd[5];//clutser
   TH1F* hcogxc[5];//clutser
   TH1F* hcogxcd[5];//clutser
   TH1F* hcogyc[5];//clutser
   TH1F* hcogycd[5];//clutser
   TH1F* hcogxcl[5][4];//clutser
   TH1F* hcogycl[5][4];//clutser
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
   for(int i=0;i<5;i++){
     hbdhitmap[i] = new TH2F(Form("hbdhitmap%d",i),Form("HBDhitmap_mod%d_Fore",103+i),50,-300,300,50,-300,300);
     trkmom[i] = new TH1F(Form("trkmom%d",i),Form("Track_mom_w/HBDHit_mod%d",103+i),50,0,5);
     hexp[i] = new TH1F(Form("hexp%d",i),Form("expected_LG_AdcSum/Mom_TrackAss_mod%d",103+i),32,0,800/ienepar[bene]);
     hadc[i] = new TH1F(Form("hadc%d",i),Form("LG_AdcSum_Fore_TrackAss_mod%d",103+i),128,0,800/ienepar[bene]);
     hadcd[i] = new TH1F(Form("hadcd%d",i),Form("LG_AdcSum_Mix_TrackAss_mod%d",103+i),128,0,800/ienepar[bene]);
     hevsp[i] = new TH2F(Form("hevsp%d",i),Form("LG_AdcSumVsMom_Fore_TrackAss_mod%d",103+i),100,0,6,100,0,600/ienepar[bene]);
     hevspd[i] = new TH2F(Form("hevspd%d",i),Form("LG_AdcSumVsMom_Mix_TrackAss_mod%d",103+i),100,0,6,100,0,600/ienepar[bene]);
     hevspr[i] = new TH2F(Form("hevspr%d",i),Form("LG_AdcSumVsMom_Fore_TrackAss_mod%d",103+i),25,0,3,50,0,600/ienepar[bene]);
     hevsprd[i] = new TH2F(Form("hevsprd%d",i),Form("LG_AdcSumVsMom_Mix_TrackAss_mod%d",103+i),25,0,3,50,0,600/ienepar[bene]);
     // hevspr[i] = new TH2F(Form("hevspr%d",i),Form("LG_AdcSumVsMom_Fore_TrackAss_mod%d",103+i),50,0,3,100,0,600/ienepar[bene]);
     // hevsprd[i] = new TH2F(Form("hevsprd%d",i),Form("LG_AdcSumVsMom_Mix_TrackAss_mod%d",103+i),50,0,3,100,0,600/ienepar[bene]);
     heovpvsp[i] = new TH2F(Form("heovpvsp%d",i),Form("LG_E/pVsMom_Fore_TrackAss_mod%d",103+i),25,0,3,50,0,600/ienepar[bene]);
     heovpvspd[i] = new TH2F(Form("heovpovspd%d",i),Form("LG_E/pVsMom_Mix_TrackAss_mod%d",103+i),25,0,3,50,0,600/ienepar[bene]);
     for(int j=0;j<4;j++){
       hedivp[j][i] = new TH1F(Form("hedivp%d%d",j,i),Form("LG_AdcSum/Mom_Fore_TrackAss_%1.0fmV_mod%d",lgthr[j],103+i),32,0,800/ienepar[bene]);
       hedivpd[j][i] = new TH1F(Form("hedivpd%d%d",j,i),Form("LG_AdcSum/Mom_Mix_TrackAss_%1.0fmV_mod%d",lgthr[j],103+i),32,0,800/ienepar[bene]);
       hassp[j][i] = new TH1F(Form("hassp%d%d",j,i),Form("Mom_Fore_TrackAss_%1.0fmV_mod%d",lgthr[j],103+i),50,0,5);
       hasspd[j][i] = new TH1F(Form("hasspd%d%d",j,i),Form("Mom_Mix_TrackAss_%1.0fmV_mod%d",lgthr[j],103+i),50,0,5);
       hasse[j][i] = new TH1F(Form("hasse%d%d",j,i),Form("AdcSum_Fore_TrackAss_%1.0fmV_mod%d",lgthr[j],103+i),128,0,800/ienepar[bene]);
       hassed[j][i] = new TH1F(Form("hassed%d%d",j,i),Form("AdcSum_Mix_TrackAss_%1.0fmV_mod%d",lgthr[j],103+i),128,0,800/ienepar[bene]);

       hesubp[j][i] = new TH1F(Form("hesubp%d%d",j,i),Form("LG_AdcSum-%1.0f*Mom_Fore_TrackAss_mod%d",lgcon[j],103+i),16,-200,200);
       hesubpd[j][i] = new TH1F(Form("hesubpd%d%d",j,i),Form("LG_AdcSum-%1.0f*Mom_Mix_TrackAss_mod%d",lgcon[j],103+i),16,-200,200);
       hedivpd_hmix[j][i] = new TH1F(Form("hedivpd_hmix%d%d",j,i),Form("LG_AdcSum/Mom_Mix_TrackAss_%1.0fmV_mod%d_hmix",lgthr[j],103+i),32,0,800/ienepar[bene]);
       hasspd_hmix[j][i] = new TH1F(Form("hasspd_hmix%d%d",j,i),Form("Mom_Mix_TrackAss_%1.0fmV_mod%d_hmix",lgthr[j],103+i),50,0,5);
       hassed_hmix[j][i] = new TH1F(Form("hassed_hmix%d%d",j,i),Form("AdcSum_Mix_TrackAss_%1.0fmV_mod%d_hmix",lgthr[j],103+i),128,0,800/ienepar[bene]);
     }
     hnlghitwtc[i] = new TH1F(Form("hnlghitwtc%d",i),Form("N_LGHits_TrackAss_inCluster_Fore_mod%d",103+i),10,0,10);
     hnlghitwtcd[i] = new TH1F(Form("hnlghitwtcd%d",i),Form("N_LGHits_TrackAss_inCluster_Mix_mod%d",103+i),10,0,10);
     for(int j=0;j<4;j++){
       hhitmapc[j][i] = new TH2F(Form("hhitmapc%d%d",j,i),Form("LGhitmap_mod%d_E/pcut%d_Fore",103+i,j),7,-0.5,6.5,6,-0.5,5.5);
       hhitmapcd[j][i] = new TH2F(Form("hhitmapcd%d%d",j,i),Form("LGhitmap_mod%d_E/pcut%d_Mix",103+i,j),7,-0.5,6.5,6,-0.5,5.5);
       hhitmapcd_hmix[j][i] = new TH2F(Form("hhitmapcd_hmix%d%d",j,i),Form("LGhitmap_mod%d_E/pcut%d_Mix_hmix",103+i,j),7,-0.5,6.5,6,-0.5,5.5);
     }
     htsvslc[i] = new TH2F(Form("htsvslc%d",i),Form("Timing_SSDvsLG_TrackAss_inCluster_Fore_mod%d",103+i),50,50,150,50,-10,90);
     htsvslcd[i] = new TH2F(Form("htsvslcd%d",i),Form("Timing_SSDvsLG_TrackAss_inCluster_Mix_mod%d",103+i),50,50,150,50,-10,90);
     htdiffc[i] = new TH1F(Form("htdiffc%d",i),Form("MaxTimeDifference_TrackAss_inCluster_Fore_mod%d",103+i),100,0,20);
     htdiffcd[i] = new TH1F(Form("htdiffcd%d",i),Form("MaxTimeDifference_TrackAss_inCluster_Mix_mod%d",103+i),100,0,20);
     hcogxc[i] = new TH1F(Form("hcogxc%d",i),Form("COGx_residual_TrackAss_inCluster_Fore_mod%d",103+i),100,-150,150);
     hcogxcd[i] = new TH1F(Form("hcogxcd%d",i),Form("COGx_residual_TrackAss_inCluster_Mix_mod%d",103+i),100,-150,150);
     hcogyc[i] = new TH1F(Form("hcogyc%d",i),Form("COGy_residual_TrackAss_inCluster_Fore_mod%d",103+i),100,-150,150);
     hcogycd[i] = new TH1F(Form("hcogycd%d",i),Form("COGy_residual_TrackAss_inCluster_Mix_mod%d",103+i),100,-150,150);

     for(int j=0;j<4;j++){
       hcogxcl[i][j] = new TH1F(Form("hcogxcl%d%d",i,j),Form("COGx_residual_TrackAss_inCluster_mod%d_l%d",103+i,j),100,-150,150);
       hcogycl[i][j] = new TH1F(Form("hcogycl%d%d",i,j),Form("COGy_residual_TrackAss_inCluster_mod%d_l%d",103+i,j),100,-150,150);
     }
     hevsprd_hmix[i] = new TH2F(Form("hevsprd_hmix%d",i),Form("LG_AdcSumVsMom_Mix_TrackAss_mod%d_hmix",103+i),25,0,3,50,0,600/ienepar[bene]);
     // hevsprd_hmix[i] = new TH2F(Form("hevsprd_hmix%d",i),Form("LG_AdcSumVsMom_Mix_TrackAss_mod%d_hmix",103+i),50,0,3,100,0,600/ienepar[bene]);
     heovpvspd_hmix[i] = new TH2F(Form("heovpovspd_hmix%d",i),Form("LG_E/pVsMom_Mix_TrackAss_mod%d_hmix",103+i),25,0,3,50,0,600/ienepar[bene]);
     hnlghitwtcd_hmix[i] = new TH1F(Form("hnlghitwtcd_hmix%d",i),Form("N_LGHits_TrackAss_inCluster_Mix_mod%d_hmix",103+i),10,0,10);
     htdiffcd_hmix[i] = new TH1F(Form("htdiffcd_hmix%d",i),Form("MaxTimeDifference_TrackAss_inCluster_Mix_mod%d_hmix",103+i),100,0,20);
     hcogxcd_hmix[i] = new TH1F(Form("hcogxcd_hmix%d",i),Form("COGx_residual_TrackAss_inCluster_Mix_mod%d_hmix",103+i),100,-150,150);
     hcogycd_hmix[i] = new TH1F(Form("hcogycd_hmix%d",i),Form("COGy_residual_TrackAss_inCluster_Mix_mod%d_hmix",103+i),100,-150,150);
   }


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

     for(int itrack=0;itrack<n_tracks;itrack++){//track loop

       if (CutOfTrack(ientry,itrack,runoption) < 0) continue;

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
       int nlgh=0;
       for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){
	 double resx = track_lg_allhit_resx->at(itrack).at(ilg)-originx[lmide][1];
	 double resy = track_lg_allhit_resy->at(itrack).at(ilg)-originy[lmide][1];
	 double tmptdc = track_lg_allhit_ftime->at(itrack).at(ilg);
	 int cid = SingleTrackAnalyzerForRes::LocaltoCh(resx+track_lg_lx->at(itrack),resy+track_lg_ly->at(itrack));
	 if(track_lg_allhit_adc->at(itrack).at(ilg)<lgresthr||tmptdc<(ssdoffset-ssdregion)+track_ssd_t->at(itrack)||tmptdc>(ssdoffset+ssdregion)+track_ssd_t->at(itrack)) continue;//220418
	 if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	   resx_min=resx;
	   resy_min=resy;
	   cid_min=cid;
	 }
	 nlgh++;
       }
       bool LGhit=false;
       if(fabs(resx_min)<widthx[lmide][1] && fabs(resy_min)<widthy[lmide][1]){
	 LGhit=true;
       }

       //Check projection position
       bool ly23 = false;
       bool ly1234 = false;
       if( fabs(track_lg_ly->at(itrack))<160.7 ){ly23=true;}
       if( fabs(track_lg_ly->at(itrack))<281.0 ){ly1234=true;}
       // if( !ly1234 ) continue;

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
	 }
	 nhbdc++;
       }// hbdcluster loop
       hn[hmide][0][itype]->Fill(nhbdc);
       hn[2][0][itype]->Fill(nhbdc);
       if(itype==eptype){
	 hbdhitmap[hmide]->Fill(track_hbd_lx->at(itrack),track_hbd_ly->at(itrack));
	 hbdhitmap[2]->Fill(track_hbd_lx->at(itrack),track_hbd_ly->at(itrack));
       }

       if(hbdmixhits[hmide][itype].size()!=0){//calc mix
	 for(int ihbd=0;ihbd<hbdmixhits[hmide][itype].size();ihbd++){
	   int nhbdc_dum = 0;
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
	     }
	     nhbdc_dum++;
	   }
	   hnd[hmide][0][itype]->Fill(nhbdc_dum);
	   hnd[2][0][itype]->Fill(nhbdc_dum);
	 }
       }//calc mix


       //LG Fill
       std::vector<hitset> lgnear;
       lgcls lgcluster;
       double adcsum = 0;
       std::vector<int> trk_ass_cids(0);
       CalcClusterCand(*geometry, trk_ass_cids, track_lg_blockch->at(itrack), track_position_block_lx->at(itrack), track_position_block_ly->at(itrack), track_angle_lx->at(itrack));//
       for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){//lgfore
	 double resx = track_lg_allhit_resx->at(itrack).at(ilg);
	 double resy = track_lg_allhit_resy->at(itrack).at(ilg);
	 double rxs = resx-originx[lmide][1];
	 double rys = resy-originy[lmide][1];
	 double tmpadc = track_lg_allhit_adc->at(itrack).at(ilg);
	 double tmptdc = track_lg_allhit_ftime->at(itrack).at(ilg);
	 double gain=1.;
	 int cid = SingleTrackAnalyzerForRes::LocaltoCh(resx+track_lg_lx->at(itrack),resy+track_lg_ly->at(itrack));
	 if(cid>=0&&cid<56){gain=relg[bene][lmide][cid/10][cid%10]*enepar[bene];}
	 if(gaincalib){tmpadc = tmpadc*gain;}
	 if(tmpadc<lgresthr||tmptdc<(ssdoffset-ssdregion)+track_ssd_t->at(itrack)||tmptdc>(ssdoffset+ssdregion)+track_ssd_t->at(itrack)) continue;//220418
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
	     bool bclscand=false;
	     for(int itmp=0;itmp<trk_ass_cids.size();itmp++){
	       if(cid==trk_ass_cids.at(itmp)){bclscand=true;break;}
	     }
	     if(bclscand){
	       lgnear.push_back(tmphit);
	     }
	   }
	 }
       }//lgfore
       hn[lmide][1][itype]->Fill(nlgh);
       hn[2][1][itype]->Fill(nlgh);
       if(itype==eptype){
	 trkmom[lmide]->Fill(track_mom->at(itrack));
	 trkmom[2]->Fill(track_mom->at(itrack));
	 if(lgnear.size()>0){
	   hexp[lmide]->Fill(ExpectedE(track_mom->at(itrack))/enepar[bene]/track_mom->at(itrack));
	   hexp[2]->Fill(ExpectedE(track_mom->at(itrack))/enepar[bene]/track_mom->at(itrack));
	   adcsum=CalcADCNearHitV3(lgnear,track_ssd_t->at(itrack),lgcluster);
	   if(w_calib_pos_dep){
	     double calib_x;
	     double calib_pos_dep = CalcCalibPar(track_lg_ly->at(itrack),track_lg_blockch->at(itrack),calib_x);
	     adcsum=adcsum*calib_pos_dep;
	   }
	 }
	 // if(lgcluster.cids.size()>0){//select 4d-isolate-cluster
	 //   for(int ict=0;ict<lgcluster.cids.size();ict++){//cls loop
	 //     for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){//hit loop
	 //       double resx = track_lg_allhit_resx->at(itrack).at(ilg)-originx[lmide][1];
	 //       double resy = track_lg_allhit_resy->at(itrack).at(ilg)-originy[lmide][1];
	 //       double tmptdc = track_lg_allhit_ftime->at(itrack).at(ilg);
	 //       int cid = SingleTrackAnalyzerForRes::LocaltoCh(resx+track_lg_lx->at(itrack),resy+track_lg_ly->at(itrack));
	 //       if(track_lg_allhit_adc->at(itrack).at(ilg)<lgresthr||tmptdc<(ssdoffset-ssdregion)+track_ssd_t->at(itrack)||tmptdc>(ssdoffset+ssdregion)+track_ssd_t->at(itrack)) continue;
	 //       bool hitincls = false;
	 //       for(int ict2=0;ict2<lgcluster.cids.size();ict2++){
	 // 	 if(cid==lgcluster.cids.at(ict2)&&tmptdc==lgcluster.tdcs.at(ict2)){
	 // 	   hitincls = true;
	 // 	   break;
	 // 	 }
	 //       }
	 //       if(!hitincls&&fabs(lgcluster.tdcs.at(ict)-tmptdc)<10&&IsNeighborBlock(*geometry,cid,lgcluster.cids.at(ict))){
	 // 	 adcsum=-10000.;
	 // 	 break;
	 //       }
	 //     }//hit loop
	 //   }//cls loop
	 // }//select 4d-isolate-cluster
	 hnlghitwtc[lmide]->Fill(lgcluster.cids.size());
	 hnlghitwtc[2]->Fill(lgcluster.cids.size());
	 for(int ict=0;ict<lgcluster.cids.size();ict++){
	   htsvslc[lmide]->Fill(lgcluster.tdcs.at(ict),track_ssd_t->at(itrack));
	   htsvslc[2]->Fill(lgcluster.tdcs.at(ict),track_ssd_t->at(itrack));
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
	 hevsp[lmide]->Fill(track_mom->at(itrack),adcsum/enepar[bene]);
	 hevsp[2]->Fill(track_mom->at(itrack),adcsum/enepar[bene]);
	 if(adcsum>0){
	   hevspr[lmide]->Fill(track_mom->at(itrack),adcsum/enepar[bene]);
	   hevspr[2]->Fill(track_mom->at(itrack),adcsum/enepar[bene]);
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
       }

       if(lgmixhits[lmide][itype].size()!=0){//calc mix
	 for(int ilg=0;ilg<lgmixhits[lmide][itype].size();ilg++){//lghit loop
	   std::vector<hitset> lgneard;
	   lgcls lgclusterd;
	   double adcsumd = 0;
	   int nlgh_dum = 0;
	   for(int jlg=0;jlg<lgmixhits[lmide][itype].at(ilg).size();jlg++){
	     double tmpresx = lgmixhits[lmide][itype].at(ilg).at(jlg).lx-track_lg_lx->at(itrack);
	     double tmpresy = lgmixhits[lmide][itype].at(ilg).at(jlg).ly-track_lg_ly->at(itrack);
	     double tmprxs = tmpresx - originx[lmide][1];
	     double tmprys = tmpresy - originy[lmide][1];
	     double tmpt = lgmixhits[lmide][itype].at(ilg).at(jlg).tdc;
	     double tmpa = lgmixhits[lmide][itype].at(ilg).at(jlg).adc;
	     int tmpcid = SingleTrackAnalyzerForRes::LocaltoCh(tmpresx+track_lg_lx->at(itrack),tmpresy+track_lg_ly->at(itrack));
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
		 bool bclscand=false;
		 for(int itmp=0;itmp<trk_ass_cids.size();itmp++){
		   if(tmpcid==trk_ass_cids.at(itmp)){bclscand=true;break;}
		 }
		 if(bclscand){
		   lgneard.push_back(tmphit);
		 }
	       }
	     }
	     nlgh_dum++;
	   }
	   hnd[lmide][1][itype]->Fill(nlgh_dum);
	   hnd[2][1][itype]->Fill(nlgh_dum);
	   if(itype==eptype){
	     if(lgneard.size()>0){
	       adcsumd=CalcADCNearHitV3(lgneard,track_ssd_t->at(itrack),lgclusterd);
	       if(w_calib_pos_dep){
		 double calib_x;
		 double calib_pos_dep = CalcCalibPar(track_lg_ly->at(itrack),track_lg_blockch->at(itrack),calib_x);
		 adcsumd=adcsumd*calib_pos_dep;
	       }
	     }
	     hnlghitwtcd[lmide]->Fill(lgclusterd.cids.size());
	     hnlghitwtcd[2]->Fill(lgclusterd.cids.size());
	     for(int ict=0;ict<lgclusterd.cids.size();ict++){
	       htsvslcd[lmide]->Fill(lgclusterd.tdcs.at(ict),track_ssd_t->at(itrack));
	       htsvslcd[2]->Fill(lgclusterd.tdcs.at(ict),track_ssd_t->at(itrack));
	     }
	     if(lgclusterd.cids.size()>1){
	       htdiffcd[lmide]->Fill(lgclusterd.timediff);
	       htdiffcd[2]->Fill(lgclusterd.timediff);
	       hcogxcd[lmide]->Fill(lgclusterd.cogx);
	       hcogxcd[2]->Fill(lgclusterd.cogx);
	       hcogycd[lmide]->Fill(lgclusterd.cogy);
	       hcogycd[2]->Fill(lgclusterd.cogy);
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
	     hevspd[lmide]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]);
	     hevspd[2]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]);
	     if(adcsumd>0){
	       hevsprd[lmide]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]);
	       hevsprd[2]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]);
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
	   int cid = SingleTrackAnalyzerForRes::LocaltoCh(tmplx,tmply);
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
	 int tmpcid = SingleTrackAnalyzerForRes::LocaltoCh(tmpresx+track_lg_lx->at(itrack),tmpresy+track_lg_ly->at(itrack));
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
	 adcsumd=CalcADCNearHitV3(lgneard,track_ssd_t->at(itrack),lgclusterd);
	 if(w_calib_pos_dep){
	   double calib_x;
	   double calib_pos_dep = CalcCalibPar(track_lg_ly->at(itrack),track_lg_blockch->at(itrack),calib_x);
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

     }//track loop

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
   // TCanvas* ctrkmom = new TCanvas("ctrkmom","ctrkmom",700,500);
   // ctrkmom->Divide(2,2);
   // for(int i=0;i<4;i++){
   //   ctrkmom->cd(i+1);
   //   trkmom[(i+3)%5]->Draw();
   // }
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
     hevsprsub[i]->SetTitle(Form("LG_AdcSumVsMom_Fore-Mix_TrackAss_mod%d",103+((i+3)%5)));
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
     heovpvspsub[i]->SetTitle(Form("LG_E/pVsMom_Fore-Mix_TrackAss_mod%d",103+((i+3)%5)));
   }
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

   //draw canvas HBD-LG mix
   TH2F* hevsprsub_hmix[5];
   TCanvas* cevspr_hmix = new TCanvas("cevspr_hmix","cevspr_hmix",700,500);
   TCanvas* cevsprd_hmix = new TCanvas("cevsprd_hmix","cevsprd_hmix",700,500);
   TCanvas* cevsprsub_hmix = new TCanvas("cevsprsub_hmix","cevsprsub_hmix",700,500);
   DC2DForeMixFM(cevspr_hmix,cevsprd_hmix,cevsprsub_hmix,hevspr,hevsprd_hmix,hevsprsub_hmix,1);
   for(int i=0;i<4;i++){
     hevsprsub_hmix[i]->SetName(Form("hevsprsub_hmix%d",(i+3)%5));
     hevsprsub_hmix[i]->SetTitle(Form("LG_AdcSumVsMom_Fore-Mix_TrackAss_mod%d_hmix",103+((i+3)%5)));
   }
   TH2F* heovpvspsub_hmix[5];
   TCanvas* ceovpvsp_hmix = new TCanvas("ceovpvsp_hmix","ceovpvsp_hmix",700,500);
   TCanvas* ceovpvspd_hmix = new TCanvas("ceovpvspd_hmix","ceovpvspd_hmix",700,500);
   TCanvas* ceovpvspsub_hmix = new TCanvas("ceovpvspsub_hmix","ceovpvspsub_hmix",700,500);
   DC2DForeMixFM(ceovpvsp_hmix,ceovpvspd_hmix,ceovpvspsub_hmix,heovpvsp,heovpvspd_hmix,heovpvspsub_hmix,1);
   for(int i=0;i<4;i++){
     heovpvspsub_hmix[i]->SetName(Form("heovpvspsub_hmix%d",(i+3)%5));
     heovpvspsub_hmix[i]->SetTitle(Form("LG_E/pVsMom_Fore-Mix_TrackAss_mod%d_hmix",103+((i+3)%5)));
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
	 vasub2d[0][i][k][l] = AnalyzerResidualHBD::Get2DHistSquareIntegral(hares[(i+3)%5][k][l],voriginx[i][k],voriginy[i][k],vsigmax[i][k],vsigmay[i][k]);
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
	 vasub2d[1][i][k][l] = AnalyzerResidualHBD::Get2DHistSquareIntegral(haresd[(i+3)%5][k][l],voriginx[i][k],voriginy[i][k],vsigmax[i][k],vsigmay[i][k]);
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
	 vasub2d[2][i][k][l] = AnalyzerResidualHBD::Get2DHistSquareIntegral(hasub2d[i][k][l],hasub2dcopy[i][k][l],voriginx[i][k],voriginy[i][k],vsigmax[i][k],vsigmay[i][k]);
	 lasub2d[2][i][k][l]->AddEntry(hasub2d[i][k][l],Form("Integral(sx:%dmm,sy:%dmm), %d",(int)vsigmax[i][k],(int)vsigmay[i][k],vasub2d[2][i][k][l]),"l");
	 lasub2d[2][i][k][l]->AddEntry((TObject*)0,Form("n_track: %d",ntrack[(i+3)%5][l]),"");
	 lasub2d[2][i][k][l]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasub2d[2][i][k][l]/(double)ntrack[(i+3)%5][l]),"");
	 lasub2d[2][i][k][l]->Draw();
	 effxtrkp[i][k][l] = (double)vasub2d[2][i][k][l]/(double)ntrack[(i+3)%5][l];
	 casub2d[i][k][l]->cd(4)->DrawFrame(-ex_2d[k],-ex_2d[k],ex_2d[k],ex_2d[k]);
	 hasub2dcopy[i][k][l]->Draw("colz sames");
       }
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
     leff2[i]->AddEntry((TObject*)0,Form("E_HBD(Hit): %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1][1],vasub2d[2][i][1][0],(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][1][0],sqrt((double)vasub2d[2][i][1][1])/(double)vasub2d[2][i][1][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_HBD(Cls): %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1][1],vasub2d[2][i][1][0],(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][1][0],sqrt((double)vasub2d[2][i][1][1])/(double)vasub2d[2][i][1][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_LGHit: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1][1],vasub2d[2][i][0][0],(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][0][0],sqrt((double)vasub2d[2][i][1][1])/(double)vasub2d[2][i][0][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_LGCls: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1][1],vasub2d[2][i][0][0],(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][0][0],sqrt((double)vasub2d[2][i][1][1])/(double)vasub2d[2][i][0][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurity w/HBD: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][0][0],ntrack[(i+3)%5][1],(double)vasub2d[2][i][0][0]/(double)ntrack[(i+3)%5][1],sqrt((double)vasub2d[2][i][0][0])/(double)ntrack[(i+3)%5][1]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurityB: %d/%d/E_HBD=%1.3f +/- %1.3f",vasub2d[2][i][0][0],ntrack[(i+3)%5][0],(double)vasub2d[2][i][0][0]/(double)ntrack[(i+3)%5][0]/(double)vasub2d[2][i][1][1]*(double)vasub2d[2][i][1][0],sqrt((double)vasub2d[2][i][0][0])/(double)ntrack[(i+3)%5][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurity w/LG: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1][0],ntrack[(i+3)%5][2],(double)vasub2d[2][i][1][0]/(double)ntrack[(i+3)%5][2],sqrt((double)vasub2d[2][i][1][0])/(double)ntrack[(i+3)%5][2]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurity w/ALL: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1][1],ntrack[(i+3)%5][3],(double)vasub2d[2][i][1][1]/(double)ntrack[(i+3)%5][3],sqrt((double)vasub2d[2][i][1][1])/(double)ntrack[(i+3)%5][3]),"");
     leff2[i]->Draw();
   }
   // if(hbdclthr==1){
   //   std::ofstream psum("purity_wocsa.txt",ios::app);
   //   psum<<hbdthr<<" ";
   //   for(int i=0;i<4;i++){
   //     psum<<(double)vasub2d[2][i][0][0]/(double)ntrack[(i+3)%5][1]<<" ";
   //   }
   //   psum<<std::endl;
   //   std::ofstream esum("lgeff_wocsa.txt",ios::app);
   //   esum<<hbdthr<<" ";
   //   for(int i=0;i<4;i++){
   //     esum<<(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][0][0]<<" ";
   //   }
   //   esum<<std::endl;
   // }
   // if(hbdclthr==2){
   //   std::ofstream psum("purity_wcsa.txt",ios::app);
   //   psum<<hbdthr<<" ";
   //   for(int i=0;i<4;i++){
   //     psum<<(double)vasub2d[2][i][0][0]/(double)ntrack[(i+3)%5][1]<<" ";
   //   }
   //   psum<<std::endl;
   //   std::ofstream esum("lgeff_wcsa.txt",ios::app);
   //   esum<<hbdthr<<" ";
   //   for(int i=0;i<4;i++){
   //     esum<<(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][0][0]<<" ";
   //   }
   //   esum<<std::endl;
   // }
   // Efficiency Summary   

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
   for(int i=0;i<4;i++){
     // chitmapc[i]->SaveAs(outfile,"pdf");
     // chitmapcd[i]->SaveAs(outfile,"pdf");
     chitmapcsub[i]->SaveAs(outfile,"pdf");
   }
   cnlghitwtc->SaveAs(outfile,"pdf");
   cnlghitwtcd->SaveAs(outfile,"pdf");
   ctsvslc->SaveAs(outfile,"pdf");
   ctsvslcd->SaveAs(outfile,"pdf");
   ctdiffc->SaveAs(outfile,"pdf");
   ccogxc->SaveAs(outfile,"pdf");
   ccogyc->SaveAs(outfile,"pdf");
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

   // outtext.close();
   fouthist->Write();
   fouthist->Close();
   delete geometry;

}

void AnalyzerTrackSelection::DrawForLGRejection(int runoption, int maxevent, char* out_file_name, char* out_root_name, int hbdoptype)
{

   if (fChain == 0) return;

   TFile *fouthist = new TFile(out_root_name,"recreate");

   int bene = 1;// 0 or 1
   bool gaincalib = true;
   bool leftonly = true;
   int searchx = 100;//for lg cluster
   int searchy = 60;//for lg cluster
   int mixevent = 50;
   double lgresthr = 20.;
   double ssdoffset = 51.;
   // double ssdregion = 11.;
   double ssdregion = 60.;

   double enepar[2] = {1.,198.};
   int ienepar[2] = {1,200};
   const int ndet=2;
   char det[ndet][20] = {"HBD","LGHit"};
   const int ntrktype=4;
   char trktype[ntrktype][20] = {"w/o_HBD&LG","w/HBD","w/LG","w/HBDLG"};
   int eptype = 1;
   int roughbin[ndet] = {400,50};//bin;
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
     if(runoption==0){widthx[i][0]=35.;widthy[i][0]=35.;}
     if(runoption==4){widthx[i][0]=35.;widthy[i][0]=35.;}
     originx[i][1]=0.;
     originy[i][1]=0.;
     // widthx[i][1]=150.;
     // widthy[i][1]=100.;
     widthx[i][1]=searchx;
     widthy[i][1]=searchy;
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
   double track_select_sigma = 2.0;
   if(runoption==0){
     //HBD
     originx[3][0]=-7.44;//106
     widthx[3][0]=5.78*track_select_sigma;
     originy[3][0]=-2.51;
     widthy[3][0]=5.14*track_select_sigma;
     originx[4][0]=1.22;//107
     widthx[4][0]=8.34*track_select_sigma;
     originy[4][0]=-0.73;
     widthy[4][0]=6.47*track_select_sigma;
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
   for(int i=0;i<5;i++){
     for(int j=0;j<ntrktype;j++){
       ntrack[i][j]=0;
     }
   }
   TH2F *hares[5][ndet][ntrktype];
   TH2F *haresd[5][ndet][ntrktype];
   TH1F *ht[5][ndet][ntrktype];
   TH1F *htd[5][ndet][ntrktype];
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
	 }
	 hares[i][k][l] = new TH2F(Form("hares%d%d%d",i,k,l),Form("%s_allhit_residual_mod%d_%s",det[k],103+i,trktype[l]),roughbin[k],-800,800,roughbin[k],-800,800);
	 haresd[i][k][l] = new TH2F(Form("haresd%d%d%d",i,k,l),Form("%s_allhit_residual_dummy_mod%d_%s",det[k],103+i,trktype[l]),roughbin[k],-800,800,roughbin[k],-800,800);
	 ht[i][k][l] = new TH1F(Form("ht%d%d%d",i,k,l),Form("%s_fastest_time_mod%d_%s",det[k],103+i,trktype[l]),tbinw[k],tbin0[k],tbin[k]);
	 htd[i][k][l] = new TH1F(Form("htd%d%d%d",i,k,l),Form("%s_fastest_time_dummy_mod%d_%s",det[k],103+i,trktype[l]),tbinw[k],tbin0[k],tbin[k]);
       }
     }
   }
   TH1F* hadc[5];
   TH1F* hadcd[5];
   TH1F* hmom[5];
   TH1F* hmomd[5];
   TH1F* hexrej1[5];
   TH1F* hexrej1d[5];
   TH1F* hexrej2[5];
   TH1F* hexrej2d[5];
   TH2F* hevsp[5];
   TH2F* hevspd[5];
   TH1F* hedivp[5];
   TH1F* hedivpd[5];
   TH1F* hnlghitwt[5];
   TH1F* hnlghitwtd[5];
   TH2F* hhitmap[5];
   for(int i=0;i<5;i++){
     hmom[i] = new TH1F(Form("hmom%d",i),Form("Track_mom_w/HBDHit_mod%d",103+i),50,0,5);
     hmomd[i] = new TH1F(Form("hmomd%d",i),Form("Track_mom_w/HBDHit_mod%d",103+i),50,0,5);
     hexrej1[i] = new TH1F(Form("hexrej1%d",i),Form("Track_expected_rejection1_w/HBDHit_mod%d",103+i),35,0,0.35);
     hexrej1d[i] = new TH1F(Form("hexrej1d%d",i),Form("Track_expected_rejection1_w/HBDHit_mod%d",103+i),35,0,0.35);
     hexrej2[i] = new TH1F(Form("hexrej2%d",i),Form("Track_expected_rejection2_w/HBDHit_mod%d",103+i),35,0,0.35);
     hexrej2d[i] = new TH1F(Form("hexrej2d%d",i),Form("Track_expected_rejection2_w/HBDHit_mod%d",103+i),35,0,0.35);
     hadc[i] = new TH1F(Form("hadc%d",i),Form("LG_HitAdc_TrackAssociate_mod%d",103+i),128,0,800/ienepar[bene]);
     hadcd[i] = new TH1F(Form("hadcd%d",i),Form("LG_HitAdc_dummy_TrackAssociate_mod%d",103+i),128,0,800/ienepar[bene]);
     hevsp[i] = new TH2F(Form("hevsp%d",i),Form("LG_HitAdcSumVsMom_TrackAssociate_mod%d",103+i),100,0,6,100,0,600/ienepar[bene]);
     hevspd[i] = new TH2F(Form("hevspd%d",i),Form("LG_HitAdcSumVsMom_dummy_TrackAssociate_mod%d",103+i),100,0,6,100,0,600/ienepar[bene]);
     hedivp[i] = new TH1F(Form("hedivp%d",i),Form("LG_HitAdc/Mom_TrackAssociate_mod%d",103+i),32,0,800/ienepar[bene]);
     hedivpd[i] = new TH1F(Form("hedivpd%d",i),Form("LG_HitAdc/Mom_dummy_TrackAssociate_mod%d",103+i),32,0,800/ienepar[bene]);
     hnlghitwt[i] = new TH1F(Form("hnlghitwt%d",i),Form("N_LGHits_TrackAssociate_mod%d",103+i),10,0,10);
     hnlghitwtd[i] = new TH1F(Form("hnlghitwtd%d",i),Form("N_LGHits_TrackAssociate_dummy_mod%d",103+i),10,0,10);
     hhitmap[i] = new TH2F(Form("hhitmap%d",i),Form("LGhitmap_mod%d",103+i),7,-0.5,6.5,6,-0.5,5.5);
   }


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

     int ntrk[5][ntrktype]={0};
     bool alfill[2][5][ntrktype]={false};//for mixing
     std::vector<hitset> hbdhits[5][ntrktype];//for mixing
     std::vector<hitset> lghits[5][ntrktype];//for mixing
     std::vector<trackset> tracksets[ntrktype];//kill dup

     for(int itrack=0;itrack<n_tracks;itrack++){//track loop

       if (CutOfTrack(ientry,itrack) < 0) continue;

       //Search near HBD hit
       int hmide = track_hbd_mid->at(itrack)-103;
       int lmide = track_lg_mid->at(itrack)-103;
       double resx_min = 10000.;
       double resy_min = 10000.;
       double adc_max = -10000.;
       for(int ihbd=0;ihbd<track_hbd_multiplicity->at(itrack);ihbd++){
	 double resx = track_hbd_allhit_resx->at(itrack).at(ihbd)-originx[hmide][0];
	 double resy = track_hbd_allhit_resy->at(itrack).at(ihbd)-originy[hmide][0];
	 // if(hbdoptype==0&&track_hbd_allhit_size->at(itrack).at(ihbd)!=1) continue;
	 if(hbdoptype==1&&(track_hbd_allhit_adc->at(itrack).at(ihbd)<0||track_hbd_allhit_size->at(itrack).at(ihbd)!=1||track_hbd_allhit_adc->at(itrack).at(ihbd)>3)) continue;
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
       int nlgh=0;
       for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){
	 double resx = track_lg_allhit_resx->at(itrack).at(ilg)-originx[lmide][1];
	 double resy = track_lg_allhit_resy->at(itrack).at(ilg)-originy[lmide][1];
	 double tmptdc = track_lg_allhit_ftime->at(itrack).at(ilg);
	 if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	   resx_min=resx;
	   resy_min=resy;
	 }
	 nlgh++;
       }
       bool LGhit=false;
       if(fabs(resx_min)<widthx[lmide][1] && fabs(resy_min)<widthy[lmide][1]){
	 LGhit=true;
       }

       int btrktype[ntrktype]={-1,-1,-1,-1};
       btrktype[0]=1;
       if(HBDhit){btrktype[1]=1;}
       if(LGhit){btrktype[2]=1;}
       if(HBDhit&&LGhit){btrktype[3]=1;}

       // btrktype[0]=IsGoodTrack(ientry,itrack,tracksets[0]);
       // btrktype[1]=IsGoodTrack(ientry,itrack,tracksets[1]);
       // btrktype[2]=IsGoodTrack(ientry,itrack,tracksets[2]);
       // btrktype[3]=IsGoodTrack(ientry,itrack,tracksets[3]);
       // if(!HBDhit){
       // 	 btrktype[1]=-2;
       // }
       // if(!LGhit){
       // 	 btrktype[2]=-2;
       // }
       // if(!HBDhit||!LGhit){
       // 	 btrktype[3]=-2;
       // }

       // btrktype[0]=IsGoodTrack(ientry,itrack,tracksets[0]);
       // if(HBDhit){
       // 	 btrktype[1]=IsGoodTrack(ientry,itrack,tracksets[1]);
       // }
       // if(LGhit){
       // 	 btrktype[2]=IsGoodTrack(ientry,itrack,tracksets[2]);
       // }
       // if(HBDhit&&LGhit){
       // 	 btrktype[3]=IsGoodTrack(ientry,itrack,tracksets[3]);
       // }

       for(int itype=0;itype<ntrktype;itype++){//trktype loop
	 if(btrktype[itype]<0) continue;
	 ntrack[hmide][itype]++;

       //HBD Fill
       int nhbdc = 0;
       for(int ihbd=0;ihbd<track_hbd_multiplicity->at(itrack);ihbd++){// hbdcluster loop
	 double resx = track_hbd_allhit_resx->at(itrack).at(ihbd);
	 double resy = track_hbd_allhit_resy->at(itrack).at(ihbd);
	 double rxs = resx-originx[hmide][0];
	 double rys = resy-originy[hmide][0];
	 // if(hbdoptype==0&&track_hbd_allhit_size->at(itrack).at(ihbd)!=1) continue;
	 if(hbdoptype==1&&(track_hbd_allhit_adc->at(itrack).at(ihbd)<0||track_hbd_allhit_size->at(itrack).at(ihbd)!=1||track_hbd_allhit_adc->at(itrack).at(ihbd)>3)) continue;
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
	   ht[hmide][0][itype]->Fill(track_hbd_allhit_ftime->at(itrack).at(ihbd));
	   ht[2][0][itype]->Fill(track_hbd_allhit_ftime->at(itrack).at(ihbd));
	 }
	 nhbdc++;
       }// hbdcluster loop
       hn[hmide][0][itype]->Fill(nhbdc);
       hn[2][0][itype]->Fill(nhbdc);

       if(hbdmixhits[hmide][itype].size()!=0){//calc mix
	 for(int ihbd=0;ihbd<hbdmixhits[hmide][itype].size();ihbd++){
	   int nhbdc_dum = 0;
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
	       htd[hmide][0][itype]->Fill(hbdmixhits[hmide][itype].at(ihbd).at(jhbd).tdc);
	       htd[2][0][itype]->Fill(hbdmixhits[hmide][itype].at(ihbd).at(jhbd).tdc);
	     }
	     nhbdc_dum++;
	   }
	   hnd[hmide][0][itype]->Fill(nhbdc_dum);
	   hnd[2][0][itype]->Fill(nhbdc_dum);
	 }
       }//calc mix


       //LG Fill
       std::vector<hitset> lgnear;
       lgcls lgcluster;
       double adcsum = 0;
       for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){//lgfore
	 double resx = track_lg_allhit_resx->at(itrack).at(ilg);
	 double resy = track_lg_allhit_resy->at(itrack).at(ilg);
	 double rxs = resx-originx[lmide][1];
	 double rys = resy-originy[lmide][1];
	 double tmpadc = track_lg_allhit_adc->at(itrack).at(ilg);
	 double tmptdc = track_lg_allhit_ftime->at(itrack).at(ilg);
	 double gain=1.;
	 int cid = SingleTrackAnalyzerForRes::LocaltoCh(resx+track_lg_lx->at(itrack),resy+track_lg_ly->at(itrack));
	 if(cid>=0&&cid<56){gain=relg[0][lmide][cid/10][cid%10];}
	 if(gaincalib){tmpadc = tmpadc*gain;}
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
	   ht[lmide][1][itype]->Fill(track_lg_allhit_ftime->at(itrack).at(ilg));
	   ht[2][1][itype]->Fill(track_lg_allhit_ftime->at(itrack).at(ilg));
	 }
	 hares[lmide][1][itype]->Fill(resx,resy);
	 hares[2][1][itype]->Fill(resx,resy);
	 if( itype==eptype && fabs(rxs)<searchx && fabs(rys)<searchy ){
	   hitset tmphit;
	   tmphit.adc = tmpadc;
	   tmphit.tdc = tmptdc;
	   tmphit.lx = resx;
	   tmphit.ly = resy;
	   lgnear.push_back(tmphit);
	   hhitmap[lmide]->Fill((double)(cid%10),(double)(cid/10));
	 }
       }//lgfore
       hn[lmide][1][itype]->Fill(nlgh);
       hn[2][1][itype]->Fill(nlgh);
       if(itype==eptype){
	 hnlghitwt[lmide]->Fill(lgnear.size());
	 hnlghitwt[2]->Fill(lgnear.size());
	 if(lgnear.size()>0){adcsum=CalcADCNearHit(lgnear,track_ssd_t->at(itrack),lgcluster);}
	 hmom[lmide]->Fill(track_mom->at(itrack));
	 hexrej1[lmide]->Fill(track_lg_pi_eff1->at(itrack));
	 hexrej2[lmide]->Fill(track_lg_pi_eff2->at(itrack));
	 hevsp[lmide]->Fill(track_mom->at(itrack),adcsum/enepar[bene]);
	 hadc[lmide]->Fill(adcsum/enepar[bene]);
	 hedivp[lmide]->Fill(adcsum/enepar[bene]/track_mom->at(itrack));
	 if(leftonly){
	   if(lmide==3||lmide==1){
	     hmom[2]->Fill(track_mom->at(itrack));
	     hexrej1[2]->Fill(track_lg_pi_eff1->at(itrack));
	     hexrej2[2]->Fill(track_lg_pi_eff2->at(itrack));
	     hevsp[2]->Fill(track_mom->at(itrack),adcsum/enepar[bene]);
	     hadc[2]->Fill(adcsum/enepar[bene]);
	     hedivp[2]->Fill(adcsum/enepar[bene]/track_mom->at(itrack));
	   }
	 }
	 else{
	   hmom[2]->Fill(track_mom->at(itrack));
	   hexrej1[2]->Fill(track_lg_pi_eff1->at(itrack));
	   hexrej2[2]->Fill(track_lg_pi_eff2->at(itrack));
	   hevsp[2]->Fill(track_mom->at(itrack),adcsum/enepar[bene]);
	   hadc[2]->Fill(adcsum/enepar[bene]);
	   hedivp[2]->Fill(adcsum/enepar[bene]/track_mom->at(itrack));
	 }
       }

       if(lgmixhits[lmide][itype].size()!=0){//calc mix
	 for(int ilg=0;ilg<lgmixhits[lmide][itype].size();ilg++){//lghit loop
	   std::vector<hitset> lgneard;
	   lgcls lgclusterd;
	   double adcsumd = 0;
	   int nlgh_dum = 0;
	   for(int jlg=0;jlg<lgmixhits[lmide][itype].at(ilg).size();jlg++){
	     double tmpresx = lgmixhits[lmide][itype].at(ilg).at(jlg).lx-track_lg_lx->at(itrack);
	     double tmpresy = lgmixhits[lmide][itype].at(ilg).at(jlg).ly-track_lg_ly->at(itrack);
	     double tmprxs = tmpresx - originx[lmide][1];
	     double tmprys = tmpresy - originy[lmide][1];
	     double tmpt = lgmixhits[lmide][itype].at(ilg).at(jlg).tdc;
	     double tmpa = lgmixhits[lmide][itype].at(ilg).at(jlg).adc;
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
		 htd[lmide][1][itype]->Fill(tmpt);
		 htd[2][1][itype]->Fill(tmpt);
	       }
	     }
	     haresd[lmide][1][itype]->Fill(tmpresx,tmpresy);
	     haresd[2][1][itype]->Fill(tmpresx,tmpresy);
	     if( itype==eptype && fabs(tmprxs)<searchx && fabs(tmprys)<searchy ){
	       hitset tmphit;
	       tmphit.adc = tmpa;
	       tmphit.tdc = tmpt;
	       lgneard.push_back(tmphit);
	     }
	     nlgh_dum++;
	   }
	   hnd[lmide][1][itype]->Fill(nlgh_dum);
	   hnd[2][1][itype]->Fill(nlgh_dum);
	   if(itype==eptype){
	     hnlghitwtd[lmide]->Fill(lgneard.size());
	     hnlghitwtd[2]->Fill(lgneard.size());
	     if(lgneard.size()>0){adcsumd=CalcADCNearHit(lgneard,track_ssd_t->at(itrack),lgclusterd);}
	     hmomd[lmide]->Fill(track_mom->at(itrack));
	     hexrej1d[lmide]->Fill(track_lg_pi_eff1->at(itrack));
	     hexrej2d[lmide]->Fill(track_lg_pi_eff2->at(itrack));
	     hevspd[lmide]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]);
	     hadcd[lmide]->Fill(adcsumd/enepar[bene]);
	     hedivpd[lmide]->Fill(adcsumd/enepar[bene]/track_mom->at(itrack));
	     if(leftonly){
	       if(lmide==3||lmide==1){
		 hmomd[2]->Fill(track_mom->at(itrack));
		 hexrej1d[2]->Fill(track_lg_pi_eff1->at(itrack));
		 hexrej2d[2]->Fill(track_lg_pi_eff2->at(itrack));
		 hevspd[2]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]);
		 hadcd[2]->Fill(adcsumd/enepar[bene]);
		 hedivpd[2]->Fill(adcsumd/enepar[bene]/track_mom->at(itrack));
	       }
	     }
	     else{
	       hmomd[2]->Fill(track_mom->at(itrack));
	       hexrej1d[2]->Fill(track_lg_pi_eff1->at(itrack));
	       hexrej2d[2]->Fill(track_lg_pi_eff2->at(itrack));
	       hevspd[2]->Fill(track_mom->at(itrack),adcsumd/enepar[bene]);
	       hadcd[2]->Fill(adcsumd/enepar[bene]);
	       hedivpd[2]->Fill(adcsumd/enepar[bene]/track_mom->at(itrack));
	     }
	   }
	 }//lghit loop
       }//calc mix

	//fill mixing hit
       if(alfill[0][hmide][itype]==false){
	 alfill[0][hmide][itype]=true;
	 for(int ihbd=0;ihbd<track_hbd_multiplicity->at(itrack);ihbd++){
	   hitset hbdhit;
	   // if(hbdoptype==0&&track_hbd_allhit_size->at(itrack).at(ihbd)!=1) continue;
	   if(hbdoptype==1&&(track_hbd_allhit_adc->at(itrack).at(ihbd)<0||track_hbd_allhit_size->at(itrack).at(ihbd)!=1||track_hbd_allhit_adc->at(itrack).at(ihbd)>3)) continue;
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
	   int cid = SingleTrackAnalyzerForRes::LocaltoCh(tmplx,tmply);
	   if(cid>=0&&cid<56){gain=relg[0][lmide][cid/10][cid%10];}
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

     }//track loop

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


   //Draw canvas
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
       ct[k][l]->Divide(2,2);
       for(int i=0;i<4;i++){
	 ct[k][l]->cd(i+1);
	 ht[(i+3)%5][k][l]->Draw("hist");
	 htd[(i+3)%5][k][l]->Scale(1./(double)mixevent);
	 htd[(i+3)%5][k][l]->SetLineColor(6);
	 htd[(i+3)%5][k][l]->Draw("hist&&sames");
	 ct[k][l]->cd(i+1)->Update();
	 TPaveStats *st1 = (TPaveStats*)htd[(i+3)%5][k][l]->FindObject("stats");
	 st1->SetLineColor(6);
	 st1->SetX1NDC(0.58);
	 st1->SetX2NDC(0.78);
	 st1->SetY1NDC(0.495);
	 st1->SetY2NDC(0.935);
	 ct[k][l]->cd(i+1)->Modified();
       }
     }
   }
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
	   // int norma = haresx[(i+3)%5][j][k][l]->Integral(reg[0],reg[1])+haresx[(i+3)%5][j][k][l]->Integral(reg[2],reg[3]);
	   // int normb = haresxd[(i+3)%5][j][k][l]->Integral(reg[0],reg[1])+haresxd[(i+3)%5][j][k][l]->Integral(reg[2],reg[3]);
	   // haresxd[(i+3)%5][j][k][l]->Scale((double)norma/(double)normb);
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
	   // norma = haresy[(i+3)%5][j][k][l]->Integral(reg[0],reg[1])+haresy[(i+3)%5][j][k][l]->Integral(reg[2],reg[3]);
	   // normb = haresyd[(i+3)%5][j][k][l]->Integral(reg[0],reg[1])+haresyd[(i+3)%5][j][k][l]->Integral(reg[2],reg[3]);
	   // haresyd[(i+3)%5][j][k][l]->Scale((double)norma/(double)normb);
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
	 vasub2d[0][i][k][l] = AnalyzerResidualHBD::Get2DHistSquareIntegral(hares[(i+3)%5][k][l],voriginx[i][k],voriginy[i][k],vsigmax[i][k],vsigmay[i][k]);
	 lasub2d[0][i][k][l]->AddEntry(hares[(i+3)%5][k][l],Form("Integral, %d",vasub2d[0][i][k][l]),"l");
	 lasub2d[0][i][k][l]->AddEntry((TObject*)0,Form("int/ntrack: %1.3f",(double)vasub2d[0][i][k][l]/(double)ntrack[(i+3)%5][l]),"");
	 lasub2d[0][i][k][l]->Draw();
	 casub2d[i][k][l]->cd(2);
	 int x0 = haresd[(i+3)%5][k][l]->GetXaxis()->FindBin(-100.);
	 int x1 = haresd[(i+3)%5][k][l]->GetXaxis()->FindBin(100.);
	 int y0 = haresd[(i+3)%5][k][l]->GetYaxis()->FindBin(-100.);
	 int y1 = haresd[(i+3)%5][k][l]->GetYaxis()->FindBin(100.);
	 // int norma = hares[(i+3)%5][k][l]->Integral()-hares[(i+3)%5][k][l]->Integral(x0,x1,y0,y1);
	 // int normb = haresd[(i+3)%5][k][l]->Integral()-haresd[(i+3)%5][k][l]->Integral(x0,x1,y0,y1);
	 // haresd[(i+3)%5][k][l]->Scale((double)norma/(double)normb);
	 haresd[(i+3)%5][k][l]->Scale(1./(double)mixevent);
	 haresd[(i+3)%5][k][l]->Draw("colz");
	 lasub2d[1][i][k][l] = new TLegend(0.1,0.8,0.7,0.9);
	 vasub2d[1][i][k][l] = AnalyzerResidualHBD::Get2DHistSquareIntegral(haresd[(i+3)%5][k][l],voriginx[i][k],voriginy[i][k],vsigmax[i][k],vsigmay[i][k]);
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
	 vasub2d[2][i][k][l] = AnalyzerResidualHBD::Get2DHistSquareIntegral(hasub2d[i][k][l],hasub2dcopy[i][k][l],voriginx[i][k],voriginy[i][k],vsigmax[i][k],vsigmay[i][k]);
	 lasub2d[2][i][k][l]->AddEntry(hasub2d[i][k][l],Form("Integral(sx:%dmm,sy:%dmm), %d",(int)vsigmax[i][k],(int)vsigmay[i][k],vasub2d[2][i][k][l]),"l");
	 lasub2d[2][i][k][l]->AddEntry((TObject*)0,Form("n_track: %d",ntrack[(i+3)%5][l]),"");
	 lasub2d[2][i][k][l]->AddEntry((TObject*)0,Form("ratio  : %1.3f",(double)vasub2d[2][i][k][l]/(double)ntrack[(i+3)%5][l]),"");
	 lasub2d[2][i][k][l]->Draw();
	 effxtrkp[i][k][l] = (double)vasub2d[2][i][k][l]/(double)ntrack[(i+3)%5][l];
	 casub2d[i][k][l]->cd(4)->DrawFrame(-ex_2d[k],-ex_2d[k],ex_2d[k],ex_2d[k]);
	 hasub2dcopy[i][k][l]->Draw("colz sames");
       }
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
     leff2[i]->AddEntry((TObject*)0,Form("E_HBD(Hit): %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1][1],vasub2d[2][i][1][0],(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][1][0],sqrt((double)vasub2d[2][i][1][1])/(double)vasub2d[2][i][1][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_HBD(Cls): %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1][1],vasub2d[2][i][1][0],(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][1][0],sqrt((double)vasub2d[2][i][1][1])/(double)vasub2d[2][i][1][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_LGHit: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1][1],vasub2d[2][i][0][0],(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][0][0],sqrt((double)vasub2d[2][i][1][1])/(double)vasub2d[2][i][0][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("E_LGCls: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1][1],vasub2d[2][i][0][0],(double)vasub2d[2][i][1][1]/(double)vasub2d[2][i][0][0],sqrt((double)vasub2d[2][i][1][1])/(double)vasub2d[2][i][0][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurity w/HBD: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][0][0],ntrack[(i+3)%5][1],(double)vasub2d[2][i][0][0]/(double)ntrack[(i+3)%5][1],sqrt((double)vasub2d[2][i][0][0])/(double)ntrack[(i+3)%5][1]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurityB: %d/%d/E_HBD=%1.3f +/- %1.3f",vasub2d[2][i][0][0],ntrack[(i+3)%5][0],(double)vasub2d[2][i][0][0]/(double)ntrack[(i+3)%5][0]/(double)vasub2d[2][i][1][1]*(double)vasub2d[2][i][1][0],sqrt((double)vasub2d[2][i][0][0])/(double)ntrack[(i+3)%5][0]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurity w/LG: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1][0],ntrack[(i+3)%5][2],(double)vasub2d[2][i][1][0]/(double)ntrack[(i+3)%5][2],sqrt((double)vasub2d[2][i][1][0])/(double)ntrack[(i+3)%5][2]),"");
     leff2[i]->AddEntry((TObject*)0,Form("TrkPurity w/ALL: %d/%d=%1.3f +/- %1.3f",vasub2d[2][i][1][1],ntrack[(i+3)%5][3],(double)vasub2d[2][i][1][1]/(double)ntrack[(i+3)%5][3],sqrt((double)vasub2d[2][i][1][1])/(double)ntrack[(i+3)%5][3]),"");
     leff2[i]->Draw();
   }
   // Efficiency Summary   

   TH2F* hevspsub[5];
   TCanvas* cevsp = new TCanvas("cevsp","cevsp",700,500);
   TCanvas* cevspd = new TCanvas("cevspd","cevspd",700,500);
   // TCanvas* cevspsub = new TCanvas("cadcsub","cadcsub",700,500);
   cevsp->Divide(2,2);
   cevspd->Divide(2,2);
   // cevspsub->Divide(2,2);
   for(int i=0;i<5;i++){
     cevsp->cd(i+1);
     hevsp[(i+3)%5]->Draw("colz");
     cevspd->cd(i+1);
     // hevspd[(i+3)%5]->Scale(1./(double)mixevent);
     hevspd[(i+3)%5]->Draw("colz");
     // cevspsub->cd(i+1);//->SetGridy();
     // hevspsub[i] = (TH2F*)hevsp[(i+3)%5]->Clone();
     // hevspsub[i]->SetName(Form("hevspsub%d",(i+3)%5));
     // hevspsub[i]->Add(hevspd[(i+3)%5],-1);
     // hevspsub[i]->Draw("hist e");
   }

   TH1F* hmomsub[4];
   TCanvas* cmom = new TCanvas("cmom","cmom",700,500);
   TCanvas* cmomsub = new TCanvas("cmomsub","cmomsub",700,500);
   cmom->Divide(2,2);
   cmomsub->Divide(2,2);
   TH1F* hexrej1sub[4];
   TCanvas* cexrej1 = new TCanvas("cexrej1","cexrej1",700,500);
   TCanvas* cexrej1sub = new TCanvas("cexrej1sub","cexrej1sub",700,500);
   cexrej1->Divide(2,2);
   cexrej1sub->Divide(2,2);
   TH1F* hexrej2sub[4];
   TCanvas* cexrej2 = new TCanvas("cexrej2","cexrej2",700,500);
   TCanvas* cexrej2sub = new TCanvas("cexrej2sub","cexrej2sub",700,500);
   cexrej2->Divide(2,2);
   cexrej2sub->Divide(2,2);
   TH1F* hadcsub[4];
   TLegend* legadc[4];
   TCanvas* cadc = new TCanvas("cadc","cadc",700,500);
   TCanvas* cadcsub = new TCanvas("cadcsub","cadcsub",700,500);
   cadc->Divide(2,2);
   cadcsub->Divide(2,2);
   TH1F* hedivpsub[4];
   TCanvas* cedivp = new TCanvas("cedivp","cedivp",700,500);
   TCanvas* cedivpsub = new TCanvas("cedivpsub","cedivpsub",700,500);
   cedivp->Divide(2,2);
   cedivpsub->Divide(2,2);
   for(int i=0;i<4;i++){
     gStyle->SetOptStat(1111);
     cadc->cd(i+1);
     hadc[(i+3)%5]->Draw("hist");
     if(hadcd[(i+3)%5]->Integral()!=0){hadcd[(i+3)%5]->Scale((double)hadc[(i+3)%5]->Integral()*(1.-trkpforlgrej[i])/(double)hadcd[(i+3)%5]->Integral());}
     hadcd[(i+3)%5]->SetLineColor(2);
     hadcd[(i+3)%5]->Draw("hist&&sames");
     cadc->cd(i+1)->Update();
     TPaveStats *st1 = (TPaveStats*)hadcd[(i+3)%5]->FindObject("stats");
     st1->SetLineColor(2);
     st1->SetX1NDC(0.58);
     st1->SetX2NDC(0.78);
     st1->SetY1NDC(0.75);
     st1->SetY2NDC(0.935);
     cadc->cd(i+1)->Modified();
     cadcsub->cd(i+1);//->SetGridy();
     hadcsub[i] = (TH1F*)hadc[(i+3)%5]->Clone();
     hadcsub[i]->SetName(Form("hadcsub%d",(i+3)%5));
     hadcsub[i]->Add(hadcd[(i+3)%5],-1);
     hadcsub[i]->Draw("hist e");
     //calc rej
     double thr1 = 55./enepar[bene];
     double thr2 = 100./enepar[bene];
     int all = hadcsub[i]->Integral(1,hadcsub[i]->GetNbinsX()+1);
     int sur1 = hadcsub[i]->Integral(hadcsub[i]->FindBin(thr1),hadcsub[i]->GetNbinsX()+1);
     int sur2 = hadcsub[i]->Integral(hadcsub[i]->FindBin(thr2),hadcsub[i]->GetNbinsX()+1);
     legadc[i] = new TLegend(0.50,0.45,0.9,0.65);
     legadc[i]->AddEntry((TObject*)0,Form("%d/%d=%1.3f+/-%1.3f @%1.2f",sur1,all,(double)sur1/(double)all,(double)sur1/(double)all/sqrt((double)sur1),thr1),"");
     legadc[i]->AddEntry((TObject*)0,Form("%d/%d=%1.3f+/-%1.3f @%1.2f",sur2,all,(double)sur2/(double)all,(double)sur2/(double)all/sqrt((double)sur2),thr2),"");
     legadc[i]->Draw("sames");
     //calc rej

     cmom->cd(i+1);
     hmom[(i+3)%5]->Draw("hist");
     if(hmomd[(i+3)%5]->Integral()!=0){hmomd[(i+3)%5]->Scale((double)hmom[(i+3)%5]->Integral()*(1.-trkpforlgrej[i])/(double)hmomd[(i+3)%5]->Integral());}
     hmomd[(i+3)%5]->SetLineColor(2);
     hmomd[(i+3)%5]->Draw("hist&&sames");
     cmom->cd(i+1)->Update();
     TPaveStats *st2 = (TPaveStats*)hmomd[(i+3)%5]->FindObject("stats");
     st2->SetLineColor(2);
     st2->SetX1NDC(0.58);
     st2->SetX2NDC(0.78);
     st2->SetY1NDC(0.75);
     st2->SetY2NDC(0.935);
     cmom->cd(i+1)->Modified();
     cmomsub->cd(i+1);//->SetGridy();
     hmomsub[i] = (TH1F*)hmom[(i+3)%5]->Clone();
     hmomsub[i]->SetName(Form("hmomsub%d",(i+3)%5));
     hmomsub[i]->Add(hmomd[(i+3)%5],-1);
     hmomsub[i]->Draw("hist e");

     cexrej1->cd(i+1);
     hexrej1[(i+3)%5]->Draw("hist");
     if(hexrej1d[(i+3)%5]->Integral()!=0){hexrej1d[(i+3)%5]->Scale((double)hexrej1[(i+3)%5]->Integral()*(1.-trkpforlgrej[i])/(double)hexrej1d[(i+3)%5]->Integral());}
     hexrej1d[(i+3)%5]->SetLineColor(2);
     hexrej1d[(i+3)%5]->Draw("hist&&sames");
     cexrej1->cd(i+1)->Update();
     TPaveStats *st4 = (TPaveStats*)hexrej1d[(i+3)%5]->FindObject("stats");
     st4->SetLineColor(2);
     st4->SetX1NDC(0.58);
     st4->SetX2NDC(0.78);
     st4->SetY1NDC(0.75);
     st4->SetY2NDC(0.935);
     cexrej1->cd(i+1)->Modified();
     cexrej1sub->cd(i+1);//->SetGridy();
     hexrej1sub[i] = (TH1F*)hexrej1[(i+3)%5]->Clone();
     hexrej1sub[i]->SetName(Form("hexrej1sub%d",(i+3)%5));
     hexrej1sub[i]->Add(hexrej1d[(i+3)%5],-1);
     hexrej1sub[i]->Draw("hist e");

     cexrej2->cd(i+1);
     hexrej2[(i+3)%5]->Draw("hist");
     if(hexrej2d[(i+3)%5]->Integral()!=0){hexrej2d[(i+3)%5]->Scale((double)hexrej2[(i+3)%5]->Integral()*(1.-trkpforlgrej[i])/(double)hexrej2d[(i+3)%5]->Integral());}
     hexrej2d[(i+3)%5]->SetLineColor(2);
     hexrej2d[(i+3)%5]->Draw("hist&&sames");
     cexrej2->cd(i+1)->Update();
     TPaveStats *st5 = (TPaveStats*)hexrej2d[(i+3)%5]->FindObject("stats");
     st5->SetLineColor(2);
     st5->SetX1NDC(0.58);
     st5->SetX2NDC(0.78);
     st5->SetY1NDC(0.75);
     st5->SetY2NDC(0.935);
     cexrej2->cd(i+1)->Modified();
     cexrej2sub->cd(i+1);//->SetGridy();
     hexrej2sub[i] = (TH1F*)hexrej2[(i+3)%5]->Clone();
     hexrej2sub[i]->SetName(Form("hexrej2sub%d",(i+3)%5));
     hexrej2sub[i]->Add(hexrej2d[(i+3)%5],-1);
     hexrej2sub[i]->Draw("hist e");

     cedivp->cd(i+1);
     hedivp[(i+3)%5]->Draw("hist");
     if(hedivpd[(i+3)%5]->Integral()!=0){hedivpd[(i+3)%5]->Scale((double)hedivp[(i+3)%5]->Integral()*(1.-trkpforlgrej[i])/(double)hedivpd[(i+3)%5]->Integral());}
     hedivpd[(i+3)%5]->SetLineColor(2);
     hedivpd[(i+3)%5]->Draw("hist&&sames");
     cedivp->cd(i+1)->Update();
     TPaveStats *st3 = (TPaveStats*)hedivpd[(i+3)%5]->FindObject("stats");
     st3->SetLineColor(2);
     st3->SetX1NDC(0.58);
     st3->SetX2NDC(0.78);
     st3->SetY1NDC(0.75);
     st3->SetY2NDC(0.935);
     cedivp->cd(i+1)->Modified();
     cedivpsub->cd(i+1)->SetGridy();
     hedivpsub[i] = (TH1F*)hedivp[(i+3)%5]->Clone();
     hedivpsub[i]->SetName(Form("hedivpsub%d",(i+3)%5));
     hedivpsub[i]->Add(hedivpd[(i+3)%5],-1);
     hedivpsub[i]->Draw("hist e");
   }
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
   TCanvas* chitmap = new TCanvas("chitmap","chitmap",700,700);
   chitmap->Divide(2,2);
   for(int i=0;i<4;i++){
     chitmap->cd(i+1);
     hhitmap[(i+3)%5]->Draw("colz text");
   }

   TCanvas* cdef = new TCanvas("cdef","cdef",700,500);
   cdef->SaveAs(outfile+"[","pdf");
   chitmap->SaveAs(outfile,"pdf");
   ceff->SaveAs(outfile,"pdf");
   ceff2->SaveAs(outfile,"pdf");
   cnlghitwt->SaveAs(outfile,"pdf");
   cnlghitwtd->SaveAs(outfile,"pdf");
   cevsp->SaveAs(outfile,"pdf");
   cevspd->SaveAs(outfile,"pdf");
   // cevspsub->SaveAs(outfile,"pdf");
   cadc->SaveAs(outfile,"pdf");
   cadcsub->SaveAs(outfile,"pdf");
   cmom->SaveAs(outfile,"pdf");
   cmomsub->SaveAs(outfile,"pdf");
   cexrej1->SaveAs(outfile,"pdf");
   cexrej2->SaveAs(outfile,"pdf");
   cedivp->SaveAs(outfile,"pdf");
   cedivpsub->SaveAs(outfile,"pdf");
   for(int l=0;l<ntrktype;l++){
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
   cdef->SaveAs(outfile+"]","pdf");

   std::cout<<ntrack[3][0]<<" "<<ntrack[3][1]<<" "<<ntrack[3][2]<<" "<<ntrack[3][3]<<std::endl;
   std::cout<<trkpforlgrej[0]<<" "<<trkpforlgrej[1]<<" "<<trkpforlgrej[2]<<" "<<trkpforlgrej[3]<<std::endl;

   fouthist->Write();
   fouthist->Close();

}

void AnalyzerTrackSelection::GainCalib(int runoption, int maxevent, char* out_file_name, char* out_root_name)
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

       if (CutOfTrack(ientry,itrack) < 0) continue;
       int runp = RunPurpose(run_id);
       if( (int)runp/10!=1 ) continue;

       //Search near HBD hit
       int hmide = track_hbd_mid->at(itrack)-103;
       int lmide = track_lg_mid->at(itrack)-103;
       double resx_min = 10000.;
       double resy_min = 10000.;
       double adc_max = -10000.;
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
       if(HBDhit){
       	 // btrktype=IsGoodTrack(ientry,itrack,tracksets);
       	 btrktype=IsGoodTrackWHBD(ientry,itrack,tracksets,adc_max);
       }
       // btrktype=IsGoodTrack(ientry,itrack,tracksets);//220825

       if(btrktype<0) continue;

       // //HBD Fill
       // int nhbdc = 0;
       // for(int ihbd=0;ihbd<track_hbd_multiplicity->at(itrack);ihbd++){// hbdcluster loop
       // 	 double resx = track_hbd_allhit_resx->at(itrack).at(ihbd);
       // 	 double resy = track_hbd_allhit_resy->at(itrack).at(ihbd);
       // 	 double rxs = resx-originx[hmide][0];
       // 	 double rys = resy-originy[hmide][0];
       // 	 nhbdc++;
       // }// hbdcluster loop

       // if(hbdmixhits[hmide].size()!=0){//calc mix
       // 	 for(int ihbd=0;ihbd<hbdmixhits[hmide].size();ihbd++){
       // 	   int nhbdc_dum = 0;
       // 	   for(int jhbd=0;jhbd<hbdmixhits[hmide].at(ihbd).size();jhbd++){
       // 	     double tmpresx = hbdmixhits[hmide].at(ihbd).at(jhbd).lx-track_hbd_lx->at(itrack);
       // 	     double tmpresy = hbdmixhits[hmide].at(ihbd).at(jhbd).ly-track_hbd_ly->at(itrack);
       // 	     double tmprxs = tmpresx - originx[hmide][0];
       // 	     double tmprys = tmpresy - originy[hmide][0];
       // 	     nhbdc_dum++;
       // 	   }
       // 	 }
       // }//calc mix

       //LG Fill
       out_run_id = run_id;
       out_run_purpose = RunPurpose(out_run_id);
       out_event_id = event_id;
       out_mid = track_lg_mid->at(itrack);
       int ass_track_flag = 0;
       for(int ilg=0;ilg<track_lg_multiplicity->at(itrack);ilg++){//lgfore
	 double resx = track_lg_allhit_resx->at(itrack).at(ilg);
	 double resy = track_lg_allhit_resy->at(itrack).at(ilg);
	 double rxs = resx-originx[lmide][1];
	 double rys = resy-originy[lmide][1];
	 double tmpadc = track_lg_allhit_adc->at(itrack).at(ilg);
	 double tmptdc = track_lg_allhit_ftime->at(itrack).at(ilg);
	 int cid = SingleTrackAnalyzerForRes::LocaltoCh(resx+track_lg_lx->at(itrack),resy+track_lg_ly->at(itrack));
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
	     int cid = SingleTrackAnalyzerForRes::LocaltoCh(lgmixhits[lmide].at(ilg).at(jlg).lx,lgmixhits[lmide].at(ilg).at(jlg).ly);
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
