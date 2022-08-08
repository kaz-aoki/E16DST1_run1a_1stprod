#define SingleTrackAnalyzerForRes_cxx
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_TrackAnalyzerFromTree.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "SingleTrackAnalyzerForRes.hh"
#include "E16ANA_LGClustering.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDDeadChannel.hh"
#include "AnalyzerResidualHBD.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TLegend.h>

#include <TH1.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "TROOT.h"

//ichikawa function
#include <array>
#include <vector>
#include "E16ANA_StepTrack.hh"
#include "E16DST_DST1.hh"

double MomtoLGPieff1(double trk_mom){
  if(trk_mom<0.4){
    return 0.054;
  }
  else if(trk_mom>1.0){
    return 0.155;
  }
  else{
    return 0.101/0.6*(trk_mom-0.4)+0.054;
  }
}

double MomtoLGPieff2(double trk_mom){
  if(trk_mom<0.4){
    return 0.054;
  }
  else if(trk_mom>2.0){
    return 0.101/0.6*(2.0-0.4)+0.054;
  }
  else{
    return 0.101/0.6*(trk_mom-0.4)+0.054;
  }
}

void ProjectionHBDAndLG(E16ANA_GeometryV2* geometry, E16ANA_MultiTrack* pair_fitter, const TVector3& vertex, const TVector3& mom, double charge, int mid[], TVector3 out_lposs[], TVector3 out_gposs[], TVector3 out_lmoms[], TVector3 out_gmoms[]) {
  const int n_layers = E16ANA_TrackConstant::kNumDetectorLayers - E16ANA_TrackConstant::kHBD;
  const int tid = 0;
  const TVector3 lpos(0., 0., 0.);
  const TVector3 lsigma(0., 0., 0.);
  const int lid = 0; // only 1 layer in 1 RK
  const int hid = 0; // only 1 hit in 1 RK
  const int max_steps = 2000;
  const int tmp_lg_block_id[3] = {0, 10, 20};
  const TVector3 error_vector = {-10000., -10000., -10000.};

  std::vector<int> mids;
  std::vector<TVector3> lposs;
  std::vector<TVector3> lmoms;
  for (int l = 0; l < n_layers; ++l) {
    if (mid[l] < 0) {
      out_lposs[l] = error_vector;
      out_gposs[l] = error_vector;
      out_lmoms[l] = error_vector;
      out_gmoms[l] = error_vector;
      continue;
    }
    auto mid2013 = E16ANA_TrackConstant::ModuleID2020To2013_27(mid[l]);
    pair_fitter->Clear();
    if (l == 0) { // HBD
      auto tmp_geom = geometry->HBD(mid2013);
      pair_fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
    } else {
      auto tmp_geom = geometry->LG(mid2013, tmp_lg_block_id[l - 1]);
      pair_fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
    }
    pair_fitter->SetMaxSteps(max_steps);
    pair_fitter->RungeKuttaTracking(tid, vertex, mom, charge);
    pair_fitter->GetFitLPos(tid, lid, mids, lposs);
    pair_fitter->GetFitLMom(tid, lid, mids, lmoms);
    out_lmoms[l] = lmoms[hid];
    if (l == 0) {
      out_lposs[l] = lposs[hid];
      out_gposs[l] = geometry->HBD(mid2013)->GetGPos(lposs[hid]);
      out_gmoms[l] = geometry->HBD(mid2013)->GetGMom(lmoms[hid]);
    } else {
      out_gposs[l] = geometry->LG(mid2013, tmp_lg_block_id[l - 1])->GetGPos(lposs[hid]);
      out_lposs[l] = geometry->LGVD(mid2013)->GetLPos(out_gposs[l]);
      out_gmoms[l] = geometry->LG(mid2013, tmp_lg_block_id[l - 1])->GetGMom(lmoms[hid]);
    }
  }
  return;
}
//ichikawa function

Int_t SingleTrackAnalyzerForRes::CalcAngleOnLGPlane(Long64_t entry, Int_t elem, E16ANA_GeometryV2* geometry, E16ANA_MultiTrack* pair_fitter, double hbdmid, double lgmid, int ytype, double& lg_angle_lx, double& lg_angle_ly, double& lg_position_block_lx, double& lg_position_block_ly)
{

  TVector3 vertex={rk_fit_init_pos_gx->at(elem),rk_fit_init_pos_gy->at(elem),rk_fit_init_pos_gz->at(elem)};
  TVector3 mom={rk_fit_init_mom_gx->at(elem),rk_fit_init_mom_gy->at(elem),rk_fit_init_mom_gz->at(elem)};
  double charge=rk_charge->at(elem);
  int mid[4]={hbdmid,lgmid,lgmid,lgmid};
  TVector3 out_lposs[4];
  TVector3 out_gposs[4];
  TVector3 out_lmoms[4];
  TVector3 out_gmoms[4];
  const double PI = acos(-1.);
  double pmtangle[4]={0.,14.0*PI/180.,9.6*PI/180.,4.9*PI/180.};//0,c,b,a
  double ycenter[4]={0.,(243.2+388.7)/2.,(137.7+281.0)/2.,(6.5+160.7)/2.};//0,c,b,a

  ProjectionHBDAndLG(geometry, pair_fitter, vertex, mom,charge,mid,out_lposs,out_gposs,out_lmoms,out_gmoms);

  if(ytype==0||ytype==5){
    lg_angle_lx = atan(out_lmoms[1].X()/out_lmoms[1].Z());
    lg_position_block_lx = ((int)out_lposs[1].X()+124*10)%124-62;
    if(ytype==5){
      lg_angle_ly = atan(out_lmoms[1].Y()/out_lmoms[1].Z())-pmtangle[1];
      lg_position_block_ly = -(out_lposs[1].Y()-ycenter[1]);
    }
    else{
      lg_angle_ly = -(atan(out_lmoms[1].Y()/out_lmoms[1].Z())+pmtangle[1]);
      lg_position_block_ly = out_lposs[1].Y()+ycenter[1];
    }
    return ytype;
  }
  else if(ytype==1||ytype==4){
    lg_angle_lx = tan(out_lmoms[2].X()/out_lmoms[2].Z());
    lg_position_block_lx = ((int)out_lposs[2].X()+124*10)%124-62;
    if(ytype==4){
      lg_angle_ly = atan(out_lmoms[2].Y()/out_lmoms[2].Z())-pmtangle[2];
      lg_position_block_ly = -(out_lposs[2].Y()-ycenter[2]);
    }
    else{
      lg_angle_ly = -(atan(out_lmoms[2].Y()/out_lmoms[2].Z())+pmtangle[2]);
      lg_position_block_ly = out_lposs[2].Y()+ycenter[2];
    }
    return ytype;
  }
  else if(ytype==2||ytype==3){
    lg_angle_lx = tan(out_lmoms[3].X()/out_lmoms[3].Z());
    lg_position_block_lx = ((int)out_lposs[3].X()+124*10+62)%124-62;
    if(ytype==3){
      lg_angle_ly = atan(out_lmoms[3].Y()/out_lmoms[3].Z())-pmtangle[3];
      lg_position_block_ly = -(out_lposs[3].Y()-ycenter[3]);
    }
    else{
      lg_angle_ly = -(atan(out_lmoms[3].Y()/out_lmoms[3].Z())+pmtangle[3]);
      lg_position_block_ly = out_lposs[3].Y()+ycenter[3];
    }
    return ytype;
  }
  else{
    return -1;
  }
}

Int_t SingleTrackAnalyzerForRes::CalcAngleOnLGPlane(Long64_t entry, Int_t elem, E16ANA_GeometryV2* geometry, E16ANA_MultiTrack* pair_fitter, double hbdmid, double lgmid, int ytype, double trk_momy, double& lg_angle_lx, double& lg_angle_ly, double& lg_position_block_lx, double& lg_position_block_ly)
{

  TVector3 vertex={rk_fit_init_pos_gx->at(elem),0.,rk_fit_init_pos_gz->at(elem)};
  TVector3 mom={rk_fit_init_mom_gx->at(elem),trk_momy,rk_fit_init_mom_gz->at(elem)};
  double charge=rk_charge->at(elem);
  int mid[4]={hbdmid,lgmid,lgmid,lgmid};
  TVector3 out_lposs[4];
  TVector3 out_gposs[4];
  TVector3 out_lmoms[4];
  TVector3 out_gmoms[4];
  const double PI = acos(-1.);
  double pmtangle[4]={0.,14.0*PI/180.,9.6*PI/180.,4.9*PI/180.};//0,c,b,a
  double ycenter[4]={0.,(243.2+388.7)/2.,(137.7+281.0)/2.,(6.5+160.7)/2.};//0,c,b,a

  ProjectionHBDAndLG(geometry, pair_fitter, vertex, mom,charge,mid,out_lposs,out_gposs,out_lmoms,out_gmoms);

  if(ytype==0||ytype==5){
    lg_angle_lx = atan(out_lmoms[1].X()/out_lmoms[1].Z());
    lg_position_block_lx = ((int)out_lposs[1].X()+124*10)%124-62;
    if(ytype==5){
      lg_angle_ly = atan(out_lmoms[1].Y()/out_lmoms[1].Z())-pmtangle[1];
      lg_position_block_ly = -(out_lposs[1].Y()-ycenter[1]);
    }
    else{
      lg_angle_ly = -(atan(out_lmoms[1].Y()/out_lmoms[1].Z())+pmtangle[1]);
      lg_position_block_ly = out_lposs[1].Y()+ycenter[1];
    }
    return ytype;
  }
  else if(ytype==1||ytype==4){
    lg_angle_lx = tan(out_lmoms[2].X()/out_lmoms[2].Z());
    lg_position_block_lx = ((int)out_lposs[2].X()+124*10)%124-62;
    if(ytype==4){
      lg_angle_ly = atan(out_lmoms[2].Y()/out_lmoms[2].Z())-pmtangle[2];
      lg_position_block_ly = -(out_lposs[2].Y()-ycenter[2]);
    }
    else{
      lg_angle_ly = -(atan(out_lmoms[2].Y()/out_lmoms[2].Z())+pmtangle[2]);
      lg_position_block_ly = out_lposs[2].Y()+ycenter[2];
    }
    return ytype;
  }
  else if(ytype==2||ytype==3){
    lg_angle_lx = tan(out_lmoms[3].X()/out_lmoms[3].Z());
    lg_position_block_lx = ((int)out_lposs[3].X()+124*10+62)%124-62;
    if(ytype==3){
      lg_angle_ly = atan(out_lmoms[3].Y()/out_lmoms[3].Z())-pmtangle[3];
      lg_position_block_ly = -(out_lposs[3].Y()-ycenter[3]);
    }
    else{
      lg_angle_ly = -(atan(out_lmoms[3].Y()/out_lmoms[3].Z())+pmtangle[3]);
      lg_position_block_ly = out_lposs[3].Y()+ycenter[3];
    }
    return ytype;
  }
  else{
    return -1;
  }
}

int SingleTrackAnalyzerForRes::LocaltoCh(double lx, double ly){
  int y_ch = (ly+400)/130;
  int x_ch = (lx+500)/120-1;
  return y_ch*10 + x_ch;
}

float SingleTrackAnalyzerForRes::LGHitIsE(double p, float _fitpeak){
  const double sr_pi = 26.3;//[mV]
  const double ratio_e_pi = 6784.4/2434.9;// 0.4GeVe/1.4GeVpi. from masters thesis by ashikaga
  double ref_mean = sr_pi*ratio_e_pi;//0.4GeV e
  double ref_sigma = ref_mean*35./148.;//0.4GeV e
  double slope = ref_mean/0.4;//mean = slope * ene
  double alpha = ref_sigma/sqrt(0.4);//sigma = alpha * sqrt(ene)

  double e = sqrt(p*p+0.000511*0.000511);
  double mean = slope*e;
  double sigma = alpha*sqrt(e);
  double threshold = mean - 1.282*sigma; // 90% efficiency

  if(_fitpeak<threshold){ return 0; }
  else{ return 1; }

}

// double Get2DHistIntegral(TH2F* h2d, int radius, TH2F* h2dcopy){

//   h2dcopy->Reset();
//   int nbinx = h2d->GetNbinsX();
//   int nbiny = h2d->GetNbinsY();
//   int x0 = h2d->GetXaxis()->FindBin(0.);
//   int x1 = h2d->GetXaxis()->FindBin(100.);
//   int y0 = h2d->GetYaxis()->FindBin(0.);
//   int y1 = h2d->GetYaxis()->FindBin(100.);
//   double xw = 100./(x1-x0);
//   double yw = 100./(y1-y0);

//   int integral=0;
//   int xr = h2d->GetXaxis()->FindBin((double)radius) - x0;
//   int sx = x0-xr;
//   int ex = x0+xr;
//   int yr = h2d->GetYaxis()->FindBin((double)radius) - y0;
//   int sy = y0-yr;
//   int ey = y0+yr;
//   for(int i=sx;i<ex;i++){
//     for(int j=sy;j<ey;j++){
//       double x = (i-x0)*xw;
//       double y = (j-y0)*yw;
//       if(x*x+y*y<radius*radius){
// 	double content = h2d->GetBinContent(i,j);
// 	//std::cout<<x<<" "<<y<<" "<<content<<std::endl;
// 	integral += content;
// 	h2dcopy->SetBinContent(i,j,content);
// 	//h2dcopy->Fill(x,y);
//       }
//     }
//   }

//   return integral;

// }


void SingleTrackAnalyzerForRes::Loop()
{
//   In a ROOT session, you can do:
//      root> .L SingleTrackAnalyzerForRes.C
//      root> SingleTrackAnalyzerForRes t
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
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<"Loop "<<ientry<<std::endl;}

      int ntracks = track_id->size();

      for(int itrack=0;itrack<ntracks;itrack++){//track loop

	if (Cut(ientry) < 0) continue;

      }//track loop

   }//event loop


}

void SingleTrackAnalyzerForRes::Evsp()
{
   if (fChain == 0) return;

   TH1F *h = new TH1F("h","abs_mom",1000,0,10);
   TH2F *hh = new TH2F("hh","abs_mom:lg_adc",500,0,500,1000,0,10);

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<"Loop "<<ientry<<std::endl;}

      int ntracks = track_id->size();

      for(int itrack=0;itrack<ntracks;itrack++){//track loop

	if (CutOfTrackForEvsp(ientry,itrack) < 0) continue;

	double abs_mom = sqrt(rk_proj_tgt0_mom_gx->at(itrack)*rk_proj_tgt0_mom_gx->at(itrack)+rk_proj_tgt0_mom_gy->at(itrack)*rk_proj_tgt0_mom_gy->at(itrack)+rk_proj_tgt0_mom_gz->at(itrack)*rk_proj_tgt0_mom_gz->at(itrack));
	h->Fill(abs_mom);
	hh->Fill(rk_proj_lg0_adc->at(itrack),abs_mom);
	hh->Fill(rk_proj_lg1_adc->at(itrack),abs_mom);
	hh->Fill(rk_proj_lg2_adc->at(itrack),abs_mom);
	hh->Fill(rk_proj_lg3_adc->at(itrack),abs_mom);

      }//track loop

   }//event loop

   TString outfile = "./evsp.pdf";

   TCanvas* c1 = new TCanvas("c1","c1",700,500);
   h->Draw();
   TCanvas* c2 = new TCanvas("c2","c2",700,700);
   hh->Draw();
   c1->Print(outfile+"[","pdf");
   c1->Print(outfile,"pdf");
   c2->Print(outfile,"pdf");
   c2->Print(outfile+"]","pdf");

}

void SingleTrackAnalyzerForRes::EvsPwCluster()
{
   if (fChain == 0) return;

   TH1F *h1 = new TH1F("h1","residual_x",2000,-1000,1000);
   TH1F *h3 = new TH1F("h3","residual_y",2000,-1000,1000);
   TH1F *hn = new TH1F("hn","multiplicity",50,0,50);
   TH1F *ha = new TH1F("ha","cluster_peaksum",1100,-100,1000);
   TH1F *hp = new TH1F("hp","momentum",100,0,10);
   TH2F *hh = new TH2F("hh","lg_adc:abs_mom;[GeV/c];[mV]",100,0,5,100,0,1000);
   gStyle->SetOptStat(11111111);

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t n_entries = fChain->GetEntries();
   Long64_t nbytes = 0, nb = 0;

   E16ANA_HBDDeadChannel hbddch;
   std::string hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0c-220114.dat";
   hbddch.ReadFile(hbd_deadch_file.c_str());

   int nevent=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}

      //clustering
      E16ANA_LGClustering clustering;
      for (int idst1hit = 0; idst1hit < n_lg_hits; idst1hit++) {//dst1hit loop
	if(lg_hit_fflag->at(idst1hit)<2){
	  clustering.SetHitData(
	    idst1hit,
	    lg_hit_mid->at(idst1hit),
	    LocaltoCh(lg_hit_x->at(idst1hit),lg_hit_y->at(idst1hit)),
	    lg_hit_adc->at(idst1hit),
	    lg_hit_t->at(idst1hit),
	    lg_hit_adc->at(idst1hit),
	    lg_hit_x->at(idst1hit),
	    lg_hit_y->at(idst1hit),
	    0.);
	}
      }//dst1hit loop
      clustering.Clustering();
      int n_clusters = clustering.LGClusterSize();
      std::vector<int> lg_cluster_mid(n_clusters);
      std::vector<double> lg_cluster_x(n_clusters);
      std::vector<double> lg_cluster_y(n_clusters);
      std::vector<float> lg_cluster_adc(n_clusters);
      std::vector<float> lg_cluster_t(n_clusters);
      for(int icluster=0;icluster<n_clusters;icluster++){
	E16ANA_LGClustering::lgcluster cith = clustering.LGClusterIth(icluster);
	lg_cluster_mid.at(icluster) = cith.mid;
	lg_cluster_x.at(icluster) = cith.lx;
	lg_cluster_y.at(icluster) = cith.ly;
	lg_cluster_adc.at(icluster) = cith.peaksum;
	lg_cluster_t.at(icluster) = cith.fasttiming;
      }
      //clustering

      int ntracks = track_id->size();
      for(int itrack=0;itrack<ntracks;itrack++){//track loop
	double trk_lx = -10000;
	double trk_ly = -10000;
	int ytype = -10000;
	int trk_mid = CutOfTrackForEvsPwCluster(ientry,itrack,&hbddch,trk_lx,trk_ly,ytype);
	if (trk_mid < 0) {continue;}

	double resx = 0;
	double resy = 0;
	double resx_min = 10000;
	double resy_min = 10000;
	double peaksum = -10000;
	int nlghit=0;
	for(int ilg=0;ilg<n_clusters;ilg++){// lgcluster loop
	  if( lg_cluster_mid.at(ilg) == trk_mid ){
	  //if( lg_cluster_mid.at(ilg) == trk_mid && (lg_cluster_t.at(ilg)-95)<10 ){
	    resx = lg_cluster_x.at(ilg) - trk_lx;
	    resy = lg_cluster_y.at(ilg) - trk_ly;
	    if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	      resx_min = resx;
	      resy_min = resy;
	      peaksum = lg_cluster_adc.at(ilg);
	    }
	    nlghit++;
	  }	    
	}// lgcluster loop
	h1->Fill(resx_min);
	h3->Fill(resy_min);
	hn->Fill(nlghit);
	ha->Fill(peaksum);

	//LG matching
	if( resx_min*resx_min+resy_min*resy_min > 10000. ){continue;}

	double momgx, momgy, momgz;
	if(rk_fit_init_pos_gz->at(itrack)==-20){
	  momgx = rk_proj_tgt0_mom_gx->at(itrack);
	  momgy = rk_proj_tgt0_mom_gy->at(itrack);
	  momgz = rk_proj_tgt0_mom_gz->at(itrack);
	}
	else if(rk_fit_init_pos_gz->at(itrack)==0){
	  momgx = rk_proj_tgt1_mom_gx->at(itrack);
	  momgy = rk_proj_tgt1_mom_gy->at(itrack);
	  momgz = rk_proj_tgt1_mom_gz->at(itrack);
	}
	else if(rk_fit_init_pos_gz->at(itrack)==20){
	  momgx = rk_proj_tgt2_mom_gx->at(itrack);
	  momgy = rk_proj_tgt2_mom_gy->at(itrack);
	  momgz = rk_proj_tgt2_mom_gz->at(itrack);
	}
	double mom = sqrt(momgx*momgx+momgy*momgy+momgz*momgz);

	hp->Fill(mom);
	hh->Fill(mom,peaksum);

      }//track loop
      nevent++;
   }//event loop

   TString outfile = "./EvsP_lg_cluster.pdf";

   gStyle->SetOptStat(11111111);
   TCanvas* c1 = new TCanvas("c1","c1",700,500);
   h1->Draw();
   TCanvas* c3 = new TCanvas("c3","c3",700,500);
   h3->Draw();
   TCanvas* c5 = new TCanvas("c5","c5",700,500);
   hn->Draw();
   TCanvas* c4 = new TCanvas("c4","c4",700,500);
   ha->Draw();
   TCanvas* c2 = new TCanvas("c2","c2",1000,500);
   c2->Divide(2,1);
   c2->cd(1);
   hh->Draw();
   c2->cd(2);
   hh->Draw();
   TLine *l = new TLine(0,0,5,1090);
   l->Draw("same");

   c1->Print(outfile+"[","pdf");
   c1->Print(outfile,"pdf");
   c3->Print(outfile,"pdf");
   c5->Print(outfile,"pdf");
   c4->Print(outfile,"pdf");
   c2->Print(outfile,"pdf");
   c2->Print(outfile+"]","pdf");

}

void SingleTrackAnalyzerForRes::HBDADC()
{
   if (fChain == 0) return;

   TH1F *hhbd = new TH1F("hhbd","HBDadc",40,0,40);
   TH1F *hhbdp = new TH1F("hhbdp","HBDadc_LGisPi",40,0,40);
   TH1F *hhbde = new TH1F("hhbde","HBDadc_LGisE",40,0,40);
   TH1F *hhbdnc = new TH1F("hhbdnc","Ncluster_inHBDadc",20,-0.5,19.5);
   TH1F *hhbdncp = new TH1F("hhbdncp","Ncluster_inHBDadc_LGisPi",20,-0.5,19.5);
   TH1F *hhbdnce = new TH1F("hhbdnce","Ncluster_inHBDadc_LGisE",20,-0.5,19.5);
   TH1F *hhbdhp = new TH1F("hhbdhp","HBDisHit_LGisPi",3,-1.5,1.5);
   TH1F *hhbdhe = new TH1F("hhbdhe","HBDisHit_LGisE",3,-1.5,1.5);

   TH1F *hp[5];
   TH1F *he[5];
   TH1F *hncp[5];
   TH1F *hnce[5];
   TH1F *hhp[5];
   TH1F *hhe[5];
   TH2F *htdc[5];
   for(int i=0;i<5;i++){
     hp[i] = new TH1F(Form("hp%d",i),Form("HBDadc_LGisPi_Mod%d",i+103),40,0,40);
     he[i] = new TH1F(Form("he%d",i),Form("HBDadc_LGisE_Mod%d",i+103),40,0,40);
     hncp[i] = new TH1F(Form("hncp%d",i),Form("NCluster_inHBDadc_LGisPi_Mod%d",i+103),20,-0.5,19.5);
     hnce[i] = new TH1F(Form("hnce%d",i),Form("NCluster_inHBDadc_LGisE_Mod%d",i+103),20,-0.5,19.5);
     hhp[i] = new TH1F(Form("hhp%d",i),Form("HBDisHit_LGisPi_Mod%d",i+103),3,-1.5,1.5);
     hhe[i] = new TH1F(Form("hhe%d",i),Form("HBDisHit_LGisE_Mod%d",i+103),3,-1.5,1.5);
     htdc[i] = new TH2F(Form("htdc%d",i),Form("Mod%d_LGtiming:HBDtiming",i+103),400,-150,250,100,50,150);
   }

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t n_entries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;

   E16ANA_HBDDeadChannel hbddch;
   std::string hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0c-220114.dat";
   hbddch.ReadFile(hbd_deadch_file.c_str());

   int nevent=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}

      int ntracks = track_id->size();

      std::vector<float>* lg_adc[4] = {rk_proj_lg0_adc,rk_proj_lg1_adc,rk_proj_lg2_adc,rk_proj_lg3_adc};
      std::vector<float>* lg_t[4] = {rk_proj_lg0_t,rk_proj_lg1_t,rk_proj_lg2_t,rk_proj_lg3_t};
      std::vector<int>* lg_fflag[4] = {rk_proj_lg0_fflag,rk_proj_lg1_fflag,rk_proj_lg2_fflag,rk_proj_lg3_fflag};
      std::vector<double>* lg_x[4] = {rk_proj_lg0_x,rk_proj_lg1_x,rk_proj_lg2_x,rk_proj_lg3_x};
      std::vector<double>* lg_y[4] = {rk_proj_lg0_y,rk_proj_lg1_y,rk_proj_lg2_y,rk_proj_lg3_y};

      for(int itrack=0;itrack<ntracks;itrack++){//track loop

	if (CutOfTrackForHBDADC(ientry,itrack) < 0) continue;

	// int hbdhit=-1;
	// if(rk_proj_hbd0_id->at(itrack)<-1000){
	//   hbdhit = 0;
	// }
	// else{
	//   hbdhit = 1;
	// }

	double trk_lx = -10000;
	double trk_ly = -10000;
	int trk_mid = CutOfTrackForResidualHBD(ientry,itrack,trk_lx,trk_ly);
	if (trk_mid < 0) continue;
	double cog[2] = {trk_lx,trk_ly};
	int hbd_padid = E16ANA_HBDGeometry::GetPadIDWLocalCoordinate(trk_mid,cog);
	int hbd_status = hbddch.Status(trk_mid,hbd_padid);
	if(hbd_status!=0) continue;

	float lgadc=-10000;
	float lgt=-10000;
	double lglx=-10000;
	double lgly=-10000;
	int lgfflag=-10000;
	double dislx;
	double disly;
	double dislx_min=10000;
	double disly_min=10000;
	for(int i=0;i<4;i++){
	  if( lg_fflag[i]->at(itrack)==2 || lg_fflag[i]->at(itrack)==-10000 ){continue;}
	  if( (int)(lg_y[i]->at(itrack)+400)/130==0 || (int)(lg_y[i]->at(itrack)+400)/130==5 ){
	    dislx = lg_x[i]->at(itrack) - rk_fit_lg_c_x->at(itrack);
	    disly = lg_y[i]->at(itrack) - rk_fit_lg_c_y->at(itrack);	  
	  }
	  else if( (int)(lg_y[i]->at(itrack)+400)/130==1 || (int)(lg_y[i]->at(itrack)+400)/130==4 ){
	    dislx = lg_x[i]->at(itrack) - rk_fit_lg_b_x->at(itrack);
	    disly = lg_y[i]->at(itrack) - rk_fit_lg_b_y->at(itrack);	  
	  }
	  else if( (int)(lg_y[i]->at(itrack)+400)/130==2 || (int)(lg_y[i]->at(itrack)+400)/130==3 ){
	    dislx = lg_x[i]->at(itrack) - rk_fit_lg_a_x->at(itrack);
	    disly = lg_y[i]->at(itrack) - rk_fit_lg_a_y->at(itrack);	  
	  }
	  else{ continue; }	    
	  if( dislx*dislx+disly*disly < dislx_min*dislx_min+disly_min*disly_min ){
	    lgadc = lg_adc[i]->at(itrack);
	    lgt = lg_t[i]->at(itrack);
	    lglx = lg_x[i]->at(itrack);
	    lgly = lg_y[i]->at(itrack);
	  }
	}

	double resx = 0;
	double resy = 0;
	int nhbdc = 0;
	int hbdhit=0;
	float hbdadcsum = 0.;
	for(int ihbd=0;ihbd<n_hbd_clusters;ihbd++){// hbdcluster loop
	  if ( hbd_cluster_t->at(ihbd)>200 ) continue;
	  if(  hbd_cluster_mid->at(ihbd) == trk_mid ){
	    resx = hbd_cluster_x->at(ihbd) - trk_lx;
	    resy = hbd_cluster_y->at(ihbd) - trk_ly;
	    if( resx*resx+resy*resy < 1600. ){
	      hbdadcsum+=hbd_cluster_adc->at(ihbd);
	      hbdhit=1;
	      nhbdc++;
	      htdc[trk_mid-103]->Fill(hbd_cluster_t->at(ihbd),lgt);
	    }
	  }	    
	}// hbdcluster loop
	hhbd->Fill(hbdadcsum);
	hhbdnc->Fill(nhbdc);


	if(lgadc<50&&lgadc>20&&fabs(lgt-95)<10){//isPi
	  hhbdp->Fill(hbdadcsum);
	  hp[trk_mid-103]->Fill(hbdadcsum);
	  hhbdncp->Fill(nhbdc);
	  hncp[trk_mid-103]->Fill(nhbdc);
	  hhbdhp->Fill(hbdhit);
	  hhp[trk_mid-103]->Fill(hbdhit);
	}
	double m0[3] = {rk_proj_tgt0_mom_gx->at(itrack),rk_proj_tgt0_mom_gy->at(itrack),rk_proj_tgt0_mom_gz->at(itrack)};
	double m1[3] = {rk_proj_tgt1_mom_gx->at(itrack),rk_proj_tgt1_mom_gy->at(itrack),rk_proj_tgt1_mom_gz->at(itrack)};
	double m2[3] = {rk_proj_tgt2_mom_gx->at(itrack),rk_proj_tgt2_mom_gy->at(itrack),rk_proj_tgt2_mom_gz->at(itrack)};
	double mom = sqrt(m0[0]*m0[0]+m0[1]*m0[1]+m0[2]*m0[2]);
	float ise = LGHitIsE(mom,lgadc);
	//std::cout<<mom<<" "<<ise<<std::endl;
	//if(lgadc>100&&fabs(lgt-95)<10){//isE
	if(lgadc>100&&ise==1&&fabs(lgt-95)<10){//isE
	  hhbde->Fill(hbdadcsum);
	  he[trk_mid-103]->Fill(hbdadcsum);
	  hhbdnce->Fill(nhbdc);
	  hnce[trk_mid-103]->Fill(nhbdc);
	  hhbdhe->Fill(hbdhit);
	  hhe[trk_mid-103]->Fill(hbdhit);
	}
      }//track loop
      nevent++;
   }//event loop

   TString outfile = "./hbdadc.pdf";

   TCanvas* c1 = new TCanvas("c1","c1",700,500);
   hhbd->Draw();
   TCanvas* c2 = new TCanvas("c2","c2",700,500);
   // c2->SetLogy();
   // hhbde->SetLineColor(2);
   // hhbdp->SetLineColor(1);
   // hhbde->DrawNormalized();
   // hhbdp->DrawNormalized("hist sames");
   c2->Divide(2,2);
   for(int i=0;i<4;i++){
     c2->cd(i+1)->SetLogy();
     he[(i+3)%5]->SetLineColor(2);
     hp[(i+3)%5]->SetLineColor(1);
     he[(i+3)%5]->DrawNormalized("hist e");
     hp[(i+3)%5]->DrawNormalized("hist e sames");
   }
   TCanvas *c3 = new TCanvas("c3","c3",700,500);
   //   hhbdncp->Draw();
   c3->Divide(2,2);
   TCanvas *c4 = new TCanvas("c4","c4",700,500);
   //   hhbdnce->Draw();
   c4->Divide(2,2);
   TCanvas* c5 = new TCanvas("c5","c5",700,500);
   //   hhbdhp->Draw();
   c5->Divide(2,2);
   TCanvas* c6 = new TCanvas("c6","c6",700,500);
   //   hhbdhe->Draw();
   c6->Divide(2,2);
   TCanvas* c7 = new TCanvas("c7","c7",700,500);
   //   htdc->Draw();
   c7->Divide(2,2);
   for(int i=0;i<4;i++){
     c3->cd(i+1);
     hncp[(i+3)%5]->Draw();
     c4->cd(i+1);
     hnce[(i+3)%5]->Draw();
     c5->cd(i+1);
     hhp[(i+3)%5]->Draw();
     c6->cd(i+1);
     hhe[(i+3)%5]->Draw();
     c7->cd(i+1);
     htdc[(i+3)%5]->Draw();
   }



   c1->Print(outfile+"[","pdf");
   c1->Print(outfile,"pdf");
   c2->Print(outfile,"pdf");
   c3->Print(outfile,"pdf");
   c4->Print(outfile,"pdf");
   c5->Print(outfile,"pdf");
   c6->Print(outfile,"pdf");
   c7->Print(outfile,"pdf");
   c7->Print(outfile+"]","pdf");

}


void SingleTrackAnalyzerForRes::ResidualLGwCluster()
{
   if (fChain == 0) return;

   TH1F *h1 = new TH1F("h1","residual_x",500,-1000,1000);
   TH1F *h2 = new TH1F("h2","residual_x_dummy",500,-1000,1000);
   TH1F *h3 = new TH1F("h3","residual_y",500,-1000,1000);
   TH1F *h4 = new TH1F("h4","residual_y_dummy",500,-1000,1000);
   TH1F *hn = new TH1F("hn","multiplicity",50,0,50);
   TH1F *hn2 = new TH1F("hn2","multiplicity_dummy",50,0,50);
   TH1F *res0x = new TH1F("res0x","SSD_x_residual",100,-10,10);
   TH1F *res1x = new TH1F("res1x","GTR100_x_residual",200,-20,20);
   TH1F *res2x = new TH1F("res2x","GTR200_x_residual",200,-20,20);
   TH1F *res3x = new TH1F("res3x","GTR300_x_residual",200,-20,20);
   TH1F *res1y = new TH1F("res1y","GTR100_y_residual",200,-20,20);
   TH1F *res2y = new TH1F("res2y","GTR200_y_residual",200,-20,20);
   TH1F *res3y = new TH1F("res3y","GTR300_y_residual",200,-20,20);
   TH1F *he = new TH1F("he","ntracks_in_one_event",100,0,100);
   std::srand( time(NULL) );

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t n_entries = fChain->GetEntries();
   Long64_t nbytes = 0, nb = 0;

   E16ANA_HBDDeadChannel hbddch;
   std::string hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0c-220114.dat";
   hbddch.ReadFile(hbd_deadch_file.c_str());

   Int_t n_clusters_tmp = 100000;
   std::vector<int> lg_cluster_mid_tmp(0);
   std::vector<double> lg_cluster_x_tmp(0);
   std::vector<double> lg_cluster_y_tmp(0);
   std::vector<float> lg_cluster_t_tmp(0);

   int nevent=0;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}

      if (Cut(ientry) < 0) continue;

      //clustering
      E16ANA_LGClustering clustering;
      for (int idst1hit = 0; idst1hit < n_lg_hits; idst1hit++) {//dst1hit loop
	if(lg_hit_fflag->at(idst1hit)<2){
	  clustering.SetHitData(
	    idst1hit,
	    lg_hit_mid->at(idst1hit),
	    LocaltoCh(lg_hit_x->at(idst1hit),lg_hit_y->at(idst1hit)),
	    lg_hit_adc->at(idst1hit),
	    lg_hit_t->at(idst1hit),
	    lg_hit_adc->at(idst1hit),
	    lg_hit_x->at(idst1hit),
	    lg_hit_y->at(idst1hit),
	    0.);
	}
      }//dst1hit loop
      clustering.Clustering();
      int n_clusters = clustering.LGClusterSize();
      std::vector<int> lg_cluster_mid(n_clusters);
      std::vector<double> lg_cluster_x(n_clusters);
      std::vector<double> lg_cluster_y(n_clusters);
      std::vector<float> lg_cluster_t(n_clusters);
      for(int icluster=0;icluster<n_clusters;icluster++){
	E16ANA_LGClustering::lgcluster cith = clustering.LGClusterIth(icluster);
	lg_cluster_mid.at(icluster) = cith.mid;
	lg_cluster_x.at(icluster) = cith.lx;
	lg_cluster_y.at(icluster) = cith.ly;
	lg_cluster_t.at(icluster) = cith.fasttiming;
      }
      //clustering

      int ntrkacc=0;
      int ntracks = track_id->size();
      for(int itrack=0;itrack<ntracks;itrack++){//track loop
	double trk_lx = -10000;
	double trk_ly = -10000;
	int ytype = -10000;
	int trk_mid = CutOfTrackForResidualLG(ientry,itrack,&hbddch,trk_lx,trk_ly,ytype);
	//
        //double rand1 = (rand() %80000)/100. - 400.;
        //double rand2 = (rand() %80000)/100. - 400.;
	//trk_lx = rand1;
	//trk_ly = rand2;
	//
	if (trk_mid < 0) {continue;}

	double resx = 0;
	double resy = 0;
	double resx_min = 10000;
	double resy_min = 10000;
	int nlghit=0;
	for(int ilg=0;ilg<n_clusters;ilg++){// lghit loop
	  if( lg_cluster_mid.at(ilg) == trk_mid ){
	  //if( lg_cluster_mid.at(ilg) == trk_mid && fabs(lg_cluster_t.at(ilg)-95.)<10. ){
	    resx = lg_cluster_x.at(ilg) - trk_lx;
	    resy = lg_cluster_y.at(ilg) - trk_ly;
	    if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	      resx_min = resx;
	      resy_min = resy;
	    }
	    nlghit++;
	  }	    
	}// lghit loop
	h1->Fill(resx_min);
	h3->Fill(resy_min);
	hn->Fill(nlghit);
	res0x->Fill(rk_res_ssd_x->at(itrack));
	res1x->Fill(rk_res_gtr100_x->at(itrack));
	res1y->Fill(rk_res_gtr100_y->at(itrack));
	res2x->Fill(rk_res_gtr200_x->at(itrack));
	res2y->Fill(rk_res_gtr200_y->at(itrack));
	res3x->Fill(rk_res_gtr300_x->at(itrack));
	res3y->Fill(rk_res_gtr300_y->at(itrack));

	if( n_clusters_tmp!=100000 ){//dammy
	  double resx_dam = 0;
	  double resy_dam = 0;
	  double resx_dam_min = 10000;
	  double resy_dam_min = 10000;
	  int nlghit_dam=0;
	  for(int ilg=0;ilg<n_clusters_tmp;ilg++){// lghit loop
	    if(  lg_cluster_mid_tmp.at(ilg) == trk_mid ){
	      //if( lg_cluster_mid_tmp.at(ilg) == trk_mid && fabs(lg_cluster_t_tmp.at(ilg)-95)<10 ){
	      resx_dam = lg_cluster_x_tmp.at(ilg) - trk_lx;
	      resy_dam = lg_cluster_y_tmp.at(ilg) - trk_ly;
	      if( resx_dam*resx_dam+resy_dam*resy_dam < resx_dam_min*resx_dam_min+resy_dam_min*resy_dam_min ){
		resx_dam_min = resx_dam;
		resy_dam_min = resy_dam;
	      }
	      nlghit_dam++;
	    }	    
	  }// lghit loop
	  h2->Fill(resx_dam_min);
	  h4->Fill(resy_dam_min);
	  hn2->Fill(nlghit_dam);
	}//dammy

	ntrkacc++;
      }//track loop

      n_clusters_tmp = n_clusters;
      lg_cluster_mid_tmp.resize(n_clusters);
      lg_cluster_x_tmp.resize(n_clusters);
      lg_cluster_y_tmp.resize(n_clusters);
      lg_cluster_t_tmp.resize(n_clusters);
      for(int i=0;i<n_clusters;i++){
	lg_cluster_mid_tmp.at(i) = lg_cluster_mid.at(i);
	lg_cluster_x_tmp.at(i) = lg_cluster_x.at(i);
	lg_cluster_y_tmp.at(i) = lg_cluster_y.at(i);
	lg_cluster_t_tmp.at(i) = lg_cluster_t.at(i);
      }

      if(ntrkacc!=0){he->Fill(ntrkacc);}
      nevent++;
   }//event loop

   TString outfile = "./residual_lg_cluster.pdf";

   gStyle->SetOptStat(11111111);
   TCanvas* c1 = new TCanvas("c1","c1",700,500);
   h1->Draw();
   TCanvas* c2 = new TCanvas("c2","c2",700,500);
   h2->Draw();
   TCanvas* c3 = new TCanvas("c3","c3",700,500);
   h3->Draw();
   TCanvas* c4 = new TCanvas("c4","c4",700,500);
   h4->Draw();
   TCanvas* c5 = new TCanvas("c5","c5",700,500);
   hn->Draw();
   TCanvas* c52 = new TCanvas("c52","c52",700,500);
   hn2->Draw();
   TCanvas* c6 = new TCanvas("c6","c6",700,1000);
   c6->Divide(2,5);
   c6->cd(1);
   res0x->Draw();
   c6->cd(3);
   res1x->Draw();
   c6->cd(4);
   res1y->Draw();
   c6->cd(5);
   res2x->Draw();
   c6->cd(6);
   res2y->Draw();
   c6->cd(7);
   res3x->Draw();
   c6->cd(8);
   res3y->Draw();
   TCanvas* c7 = new TCanvas("c7","c7",700,500);
   he->Draw();

   c1->Print(outfile+"[","pdf");
   c1->Print(outfile,"pdf");
   c2->Print(outfile,"pdf");
   c3->Print(outfile,"pdf");
   c4->Print(outfile,"pdf");
   c5->Print(outfile,"pdf");
   c52->Print(outfile,"pdf");
   c6->Print(outfile,"pdf");
   c7->Print(outfile,"pdf");
   c7->Print(outfile+"]","pdf");

}


void SingleTrackAnalyzerForRes::ResidualLG()
{
   if (fChain == 0) return;

   TH1F *h1 = new TH1F("h1","residual_x",2000,-1000,1000);
   TH1F *h2 = new TH1F("h2","residual_x_dammy",2000,-1000,1000);
   TH1F *h3 = new TH1F("h3","residual_y",2000,-1000,1000);
   TH1F *h4 = new TH1F("h4","residual_y_dammy",2000,-1000,1000);
   TH1F *hn = new TH1F("hn","multiplicity",50,0,50);
   TH1F *hd1[7];
   TH1F *hd2[7];
   TH1F *hd3[7];
   TH1F *hd4[7];
   for(int nmod=0;nmod<7;nmod++){
     hd1[nmod] = new TH1F(Form("hd1%d",nmod+102),Form("residual_x_%d",nmod+102),2000,-1000,1000);
     hd2[nmod] = new TH1F(Form("hd2%d",nmod+102),Form("residual_x_dammy_%d",nmod+102),2000,-1000,1000);
     hd3[nmod] = new TH1F(Form("hd3%d",nmod+102),Form("residual_y_%d",nmod+102),2000,-1000,1000);
     hd4[nmod] = new TH1F(Form("hd4%d",nmod+102),Form("residual_y_dammy_%d",nmod+102),2000,-1000,1000);
   }
   TH2F *hh = new TH2F("hh","hh",900,-450,450,2000,-1000,1000);
   TH2F *hh2 = new TH2F("hh2","hh2",900,-450,450,2000,-1000,1000);

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   E16ANA_HBDDeadChannel hbddch;
   std::string hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0c-220114.dat";
   hbddch.ReadFile(hbd_deadch_file.c_str());

   Int_t n_lg_hits_tmp = 100000;
   std::vector<int> lg_hit_mid_tmp(0);
   std::vector<double> lg_hit_x_tmp(0);
   std::vector<double> lg_hit_y_tmp(0);

   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<ientry<<" / "<<nentries<<std::endl;}

      int ntracks = track_id->size();

      //std::cout<<"ntracks: "<<ntracks<<std::endl;
      //std::cout<<"n_lg_hits: "<<n_lg_hits<<std::endl;
      for(int itrack=0;itrack<ntracks;itrack++){//track loop
	int ytype = -10000;
	double trk_lx = -10000;
	double trk_ly = -10000;
	int trk_mid = CutOfTrackForResidualLG(ientry,itrack,&hbddch,trk_lx,trk_ly,ytype);
	if (trk_mid < 0) continue;

	//hh->Fill(trk_lx,trk_ly);

	double resx = 0;
	double resy = 0;
	double resx_min = 10000;
	double resy_min = 10000;
	int nlghit=0;
	for(int ilg=0;ilg<n_lg_hits;ilg++){// lghit loop
	  if( lg_hit_mid->at(ilg) == trk_mid ){
	    //hh->Fill(lg_hit_x->at(ilg),lg_hit_y->at(ilg));
	    resx = lg_hit_x->at(ilg) - trk_lx;
	    resy = lg_hit_y->at(ilg) - trk_ly;
	    if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	      resx_min = resx;
	      resy_min = resy;
	    }
	    nlghit++;
	  }	    
	}// lghit loop
	h1->Fill(resx_min);
	//if(resx_min>1000){std::cout<<"resx:"<<ientry<<" "<<itrack<<" "<<resx_min<<" "<<resy_min<<std::endl;}
	h2->Fill(resy_min);
	hd1[trk_mid-102]->Fill(resx_min);
	hd2[trk_mid-102]->Fill(resy_min);
	hh2->Fill(trk_lx,resx_min);

	//if( n_lg_hits_tmp!=100000 && lg_hit_mid_tmp.size()!=0 && lg_hit_x_tmp.size()!=0 && lg_hit_y_tmp.size()!=0 ){
	if( n_lg_hits_tmp!=100000 ){
	  //std::cout<<"dam_process: "<<n_lg_hits_tmp<<" "<<lg_hit_mid_tmp.size()<<" "<<lg_hit_x_tmp.size()<<" "<<lg_hit_y_tmp.size()<<std::endl;
	  double resx_dam = 0;
	  double resy_dam = 0;
	  double resx_dam_min = 10000;
	  double resy_dam_min = 10000;
	  for(int ilg=0;ilg<n_lg_hits_tmp;ilg++){// lghit loop
	    if(  lg_hit_mid_tmp.at(ilg) == trk_mid ){
	      resx_dam = lg_hit_x_tmp.at(ilg) - trk_lx;
	      resy_dam = lg_hit_y_tmp.at(ilg) - trk_ly;
	      if( resx_dam*resx_dam+resy_dam*resy_dam < resx_dam_min*resx_dam_min+resy_dam_min*resy_dam_min ){
		resx_dam_min = resx_dam;
		resy_dam_min = resy_dam;
	      }
	    }	    
	  }// lghit loop
	  h3->Fill(resx_dam_min);
	  h4->Fill(resy_dam_min);
	  //if(resx_dam_min>1000){std::cout<<"resx_dam:"<<ientry<<" "<<itrack<<" "<<resx_dam_min<<" "<<resy_dam_min<<std::endl;}
	  hd3[trk_mid-102]->Fill(resx_dam_min);
	  hd4[trk_mid-102]->Fill(resy_dam_min);
	  hh->Fill(trk_lx,resx_dam_min);
	}//dammy

	hn->Fill(nlghit);

      }//track loop

      n_lg_hits_tmp = n_lg_hits;
      lg_hit_mid_tmp.resize(n_lg_hits);
      lg_hit_x_tmp.resize(n_lg_hits);
      lg_hit_y_tmp.resize(n_lg_hits);
      copy( lg_hit_mid->begin(), lg_hit_mid->end(), lg_hit_mid_tmp.begin() );
      copy( lg_hit_x->begin(), lg_hit_x->end(), lg_hit_x_tmp.begin() );
      copy( lg_hit_y->begin(), lg_hit_y->end(), lg_hit_y_tmp.begin() );
      //std::cout<<n_lg_hits_tmp<<" "<<lg_hit_mid_tmp.size()<<" "<<lg_hit_x_tmp.size()<<" "<<lg_hit_y_tmp.size()<<std::endl;
      //std::cout<<"*******************"<<std::endl;

   }//event loop

   TString outfile = "./residual_lg.pdf";

   gStyle->SetOptStat(11111111);
   TCanvas* c1 = new TCanvas("c1","c1",700,500);
   h1->Draw();
   TCanvas* c2 = new TCanvas("c2","c2",700,500);
   h2->Draw();
   TCanvas* c3 = new TCanvas("c3","c3",700,500);
   h3->Draw();
   TCanvas* c4 = new TCanvas("c4","c4",700,500);
   h4->Draw();
   TCanvas* c5 = new TCanvas("c5","c5",700,500);
   hn->Draw();
   TCanvas* c6 = new TCanvas("c6","c6",1500,700);
   c6->Divide(7,4);
   for(int nmod=0;nmod<7;nmod++){
     c6->cd(nmod+1);
     hd1[nmod]->Draw();
     c6->cd(nmod+8);
     hd2[nmod]->Draw();
     c6->cd(nmod+15);
     hd3[nmod]->Draw();
     c6->cd(nmod+22);
     hd4[nmod]->Draw();
   }
   TCanvas* c7 = new TCanvas("c7","c7",700,500);
   hh->Draw();
   TCanvas* c8 = new TCanvas("c8","c8",700,500);
   hh2->Draw();
   c1->Print(outfile+"[","pdf");
   c1->Print(outfile,"pdf");
   c2->Print(outfile,"pdf");
   c3->Print(outfile,"pdf");
   c4->Print(outfile,"pdf");
   c5->Print(outfile,"pdf");
   c6->Print(outfile,"pdf");
   c7->Print(outfile,"pdf");
   c8->Print(outfile,"pdf");
   c8->Print(outfile+"]","pdf");
}

void SingleTrackAnalyzerForRes::MkTreeForResidualHBD(int runoption, int maxevent, char* out_file_name)
{
   if (fChain == 0) return;

   TFile* fout = new TFile(out_file_name,"recreate");
   TTree* tree = new TTree("tree","tree");

   Int_t           out_run_id;
   Int_t           out_event_id;
   Int_t           out_spill_id;
   Int_t           out_n_hbd_clusters;
   vector<int>     out_hbd_cluster_id;
   vector<int>     out_hbd_cluster_mid;
   vector<double>  out_hbd_cluster_x;
   vector<double>  out_hbd_cluster_y;
   vector<double>  out_hbd_cluster_gx;
   vector<double>  out_hbd_cluster_gy;
   vector<double>  out_hbd_cluster_gz;
   vector<float>   out_hbd_cluster_adc;
   vector<double>  out_hbd_cluster_t;
   vector<float>   out_hbd_cluster_ftime;
   vector<float>   out_hbd_cluster_tdiff;
   vector<int>     out_hbd_cluster_size;
   vector<float>   out_hbd_cluster_eprob;
   vector<float>   out_hbd_cluster_cprob;
   Int_t           out_n_lg_hits;
   vector<int>     out_lg_hit_id;
   vector<int>     out_lg_hit_mid;
   vector<double>  out_lg_hit_x;
   vector<double>  out_lg_hit_y;
   vector<double>  out_lg_hit_gx;
   vector<double>  out_lg_hit_gy;
   vector<double>  out_lg_hit_gz;
   vector<float>   out_lg_hit_adc;
   vector<float>   out_lg_hit_t;
   vector<int>     out_lg_hit_npeaks;
   vector<int>     out_lg_hit_fflag;
   Int_t           out_n_lg_clusters;
   vector<int>     out_lg_cluster_id;
   vector<int>     out_lg_cluster_mid;
   vector<double>  out_lg_cluster_x;
   vector<double>  out_lg_cluster_y;
   vector<float>   out_lg_cluster_adc;
   vector<float>   out_lg_cluster_ftime;
   vector<float>   out_lg_cluster_tdiff;
   vector<int>     out_lg_cluster_mpcid;
   vector<float>   out_lg_cluster_mp;
   vector<int>     out_lg_cluster_size;
   Int_t out_n_tracks;
   vector<int> out_track_id;
   vector<double> out_chi_square;
   vector<int> out_rk_charge;
   vector<int> out_is_selected;
   vector<int> out_track_mid;
   vector<double> out_track_lx;
   vector<double> out_track_ly;
   vector<double> out_track_mom;
   vector<double> out_track_mom_x;
   vector<double> out_track_mom_y;
   vector<double> out_track_mom_z;
   vector<float> out_track_lg_t;
   vector<float> out_track_lg_adc;
   vector<int> out_track_lg_mid;
   vector<int> out_track_lg_cid;
   vector<double> out_track_nearx;
   vector<double> out_track_neary;
   vector<int> out_track_multiplicity;
   vector<double> out_track_dum_nearx;
   vector<double> out_track_dum_neary;
   vector<int> out_track_dum_multiplicity;
   vector<vector<double>> out_track_allhit_resx;
   vector<vector<double>> out_track_allhit_resy;
   vector<vector<double>> out_track_allhit_ftime;
   vector<vector<double>> out_track_allhit_adc;
   vector<vector<double>> out_track_allhit_dum_resx;
   vector<vector<double>> out_track_allhit_dum_resy;
   vector<vector<double>> out_track_allhit_dum_ftime;
   vector<vector<double>> out_track_allhit_dum_adc;

   tree->Branch("run_id",&out_run_id,"run_id/I");
   tree->Branch("event_id",&out_event_id,"event_id/I");
   tree->Branch("spill_id",&out_run_id,"spill_id/I");
   tree->Branch("n_hbd_clusters",&out_n_hbd_clusters,"n_hbd_clusters/I");
   tree->Branch("hbd_cluster_id", &out_hbd_cluster_id);
   tree->Branch("hbd_cluster_mid", &out_hbd_cluster_mid);
   tree->Branch("hbd_cluster_x", &out_hbd_cluster_x);
   tree->Branch("hbd_cluster_y", &out_hbd_cluster_y);
   tree->Branch("hbd_cluster_gx", &out_hbd_cluster_gx);
   tree->Branch("hbd_cluster_gy", &out_hbd_cluster_gy);
   tree->Branch("hbd_cluster_gz", &out_hbd_cluster_gz);
   tree->Branch("hbd_cluster_adc", &out_hbd_cluster_adc);
   tree->Branch("hbd_cluster_t", &out_hbd_cluster_t);
   tree->Branch("hbd_cluster_ftime", &out_hbd_cluster_ftime);
   tree->Branch("hbd_cluster_tdiff", &out_hbd_cluster_tdiff);
   tree->Branch("hbd_cluster_size", &out_hbd_cluster_size);
   tree->Branch("hbd_cluster_eprob", &out_hbd_cluster_eprob);
   tree->Branch("hbd_cluster_cprob", &out_hbd_cluster_cprob);
   tree->Branch("n_lg_hits",&out_n_lg_hits,"n_lg_hits/I");
   tree->Branch("lg_hit_id", &out_lg_hit_id);
   tree->Branch("lg_hit_mid", &out_lg_hit_mid);
   tree->Branch("lg_hit_x", &out_lg_hit_x);
   tree->Branch("lg_hit_y", &out_lg_hit_y);
   tree->Branch("lg_hit_gx", &out_lg_hit_gx);
   tree->Branch("lg_hit_gy", &out_lg_hit_gy);
   tree->Branch("lg_hit_gz", &out_lg_hit_gz);
   tree->Branch("lg_hit_adc", &out_lg_hit_adc);
   tree->Branch("lg_hit_t", &out_lg_hit_t);
   tree->Branch("lg_hit_npeaks", &out_lg_hit_npeaks);
   tree->Branch("lg_hit_fflag", &out_lg_hit_fflag);
   tree->Branch("n_lg_clusters",&out_n_lg_clusters,"n_lg_clusters/I");
   tree->Branch("lg_cluster_id", &out_lg_cluster_id);
   tree->Branch("lg_cluster_mid", &out_lg_cluster_mid);
   tree->Branch("lg_cluster_x", &out_lg_cluster_x);
   tree->Branch("lg_cluster_y", &out_lg_cluster_y);
   tree->Branch("lg_cluster_adc", &out_lg_cluster_adc);
   tree->Branch("lg_cluster_ftime", &out_lg_cluster_ftime);
   tree->Branch("lg_cluster_tdiff", &out_lg_cluster_tdiff);
   tree->Branch("lg_cluster_mpcid", &out_lg_cluster_mpcid);
   tree->Branch("lg_cluster_mp", &out_lg_cluster_mp);
   tree->Branch("lg_cluster_size", &out_lg_cluster_size);
   tree->Branch("n_tracks",&out_n_tracks,"n_tracks/I");
   tree->Branch("track_id", &out_track_id);
   tree->Branch("chi_square", &out_chi_square);
   tree->Branch("rk_charge", &out_rk_charge);
   tree->Branch("is_selected", &out_is_selected);
   tree->Branch("track_mid", &out_track_mid);
   tree->Branch("track_lx", &out_track_lx);
   tree->Branch("track_ly", &out_track_ly);
   tree->Branch("track_mom", &out_track_mom);
   tree->Branch("track_mom_x", &out_track_mom_x);
   tree->Branch("track_mom_y", &out_track_mom_y);
   tree->Branch("track_mom_z", &out_track_mom_z);
   tree->Branch("track_lg_t", &out_track_lg_t);
   tree->Branch("track_lg_adc", &out_track_lg_adc);
   tree->Branch("track_lg_mid", &out_track_lg_mid);
   tree->Branch("track_lg_cid", &out_track_lg_cid);
   tree->Branch("track_nearx", &out_track_nearx);
   tree->Branch("track_neary", &out_track_neary);
   tree->Branch("track_multiplicity", &out_track_multiplicity);
   tree->Branch("track_dum_nearx", &out_track_dum_nearx);
   tree->Branch("track_dum_neary", &out_track_dum_neary);
   tree->Branch("track_dum_multiplicity", &out_track_dum_multiplicity);
   tree->Branch("track_allhit_resx", &out_track_allhit_resx);
   tree->Branch("track_allhit_resy", &out_track_allhit_resy);
   tree->Branch("track_allhit_ftime", &out_track_allhit_ftime);
   tree->Branch("track_allhit_adc", &out_track_allhit_adc);
   tree->Branch("track_allhit_dum_resx", &out_track_allhit_dum_resx);
   tree->Branch("track_allhit_dum_resy", &out_track_allhit_dum_resy);
   tree->Branch("track_allhit_dum_ftime", &out_track_allhit_dum_ftime);
   tree->Branch("track_allhit_dum_adc", &out_track_allhit_dum_adc);

   E16ANA_HBDDeadChannel hbddch;
   std::string hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0c-220114.dat";
   if(runoption==0){
     hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0b-220114.dat";
   }
   hbddch.ReadFile(hbd_deadch_file.c_str());

   Long64_t n_entries = fChain->GetEntries();
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   Int_t n_hbd_clusters_tmp = 100000;
   std::vector<int> hbd_cluster_mid_tmp(0);
   std::vector<double> hbd_cluster_x_tmp(0);
   std::vector<double> hbd_cluster_y_tmp(0);
   std::vector<double> hbd_cluster_adc_tmp(0);
   std::vector<double> hbd_cluster_eprob_tmp(0);
   std::vector<double> hbd_cluster_t_tmp(0);
   std::vector<double> hbd_cluster_ftime_tmp(0);

   int nevent=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
      if( maxevent!=-1&&nevent>maxevent ){break;}

      out_track_id.clear();
      out_chi_square.clear();
      out_rk_charge.clear();
      out_is_selected.clear();
      out_track_mid.clear();
      out_track_lx.clear();
      out_track_ly.clear();
      out_track_mom.clear();
      out_track_mom_x.clear();
      out_track_mom_y.clear();
      out_track_mom_z.clear();
      out_track_lg_t.clear();
      out_track_lg_adc.clear();
      out_track_lg_mid.clear();
      out_track_lg_cid.clear();
      out_track_nearx.clear();
      out_track_neary.clear();
      out_track_multiplicity.clear();
      out_track_dum_nearx.clear();
      out_track_dum_neary.clear();
      out_track_dum_multiplicity.clear();
      out_track_allhit_resx.clear();
      out_track_allhit_resy.clear();
      out_track_allhit_ftime.clear();
      out_track_allhit_adc.clear();
      out_track_allhit_dum_resx.clear();
      out_track_allhit_dum_resy.clear();
      out_track_allhit_dum_ftime.clear();
      out_track_allhit_dum_adc.clear();

      int ntrkacc = 0;
      int ntracks = track_id->size();
      double chisq_plus_min = 10000;
      double chisq_minus_min = 10000;
      int plus_index = -10000;
      int minus_index = -10000;
      for(int itrack=0;itrack<ntracks;itrack++){//track loop
	double trk_lx = -10000;
	double trk_ly = -10000;
	double trk_mom = -10000;
	double trk_momx = -10000;
	double trk_momy = -10000;
	double trk_momz = -10000;
	float trk_lg_time = -10000;
	float trk_lg_adc = -10000;
	int trk_lg_mod = -10000;
	int trk_lg_ch = -10000;
      	int trk_mid = CutOfTrackForResidualHBD(ientry,itrack,trk_lx,trk_ly,trk_mom,trk_momx,trk_momy,trk_momz,trk_lg_time,trk_lg_adc,trk_lg_mod,trk_lg_ch);
      	if (trk_mid < 0) continue;
      	double cog[2] = {trk_lx,trk_ly};
      	int hbd_padid = E16ANA_HBDGeometry::GetPadIDWLocalCoordinate(trk_mid,cog);
      	if( hbddch.Status(trk_mid,hbd_padid) != 0 ) continue;
	out_track_id.push_back(track_id->at(itrack));
	out_chi_square.push_back(chi_square->at(itrack));
	out_rk_charge.push_back(rk_charge->at(itrack));
	out_is_selected.push_back(0);
	out_track_mid.push_back(trk_mid);
	out_track_lx.push_back(trk_lx);
	out_track_ly.push_back(trk_ly);
	out_track_mom.push_back(trk_mom);
	out_track_mom_x.push_back(trk_mom);
	out_track_mom_y.push_back(trk_mom);
	out_track_mom_z.push_back(trk_mom);
	out_track_lg_t.push_back(trk_lg_time);
	out_track_lg_adc.push_back(trk_lg_adc);
	out_track_lg_mid.push_back(trk_lg_mod);
	out_track_lg_cid.push_back(trk_lg_ch);
      	if(rk_charge->at(itrack)==1){
      	  if(chi_square->at(itrack)<chisq_plus_min){
      	    chisq_plus_min = chi_square->at(itrack);
      	    plus_index = ntrkacc;
      	  }	  
      	}
      	if(rk_charge->at(itrack)==-1){
      	  if(chi_square->at(itrack)<chisq_minus_min){
      	    chisq_minus_min = chi_square->at(itrack);
      	    minus_index = ntrkacc;
      	  }	  
      	}

	double resx = 0;
	double resy = 0;
	double resx_min = 10000;
	double resy_min = 10000;
	out_track_allhit_resx.push_back(vector<double>());
	out_track_allhit_resy.push_back(vector<double>());
	out_track_allhit_ftime.push_back(vector<double>());
	out_track_allhit_adc.push_back(vector<double>());
	int nhbdc = 0;
	for(int ihbd=0;ihbd<n_hbd_clusters;ihbd++){// hbdcluster loop
	  if ( hbd_cluster_t->at(ihbd)>200 ) continue;
	  if(  hbd_cluster_mid->at(ihbd) == trk_mid ){
	    resx = hbd_cluster_x->at(ihbd) - trk_lx;
	    resy = hbd_cluster_y->at(ihbd) - trk_ly;
	    out_track_allhit_resx[ntrkacc].push_back(resx);
	    out_track_allhit_resy[ntrkacc].push_back(resy);
	    out_track_allhit_ftime[ntrkacc].push_back(hbd_cluster_ftime->at(ihbd));
	    out_track_allhit_adc[ntrkacc].push_back(hbd_cluster_adc->at(ihbd));
	    if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	      resx_min = resx;
	      resy_min = resy;
	    }
	    nhbdc++;
	  }	    
	}// hbdcluster loop
	out_track_nearx.push_back(resx_min);
	out_track_neary.push_back(resy_min);
	out_track_multiplicity.push_back(nhbdc);

	out_track_allhit_dum_resx.push_back(vector<double>());
	out_track_allhit_dum_resy.push_back(vector<double>());
	out_track_allhit_dum_ftime.push_back(vector<double>());
	out_track_allhit_dum_adc.push_back(vector<double>());
	double resx_dam = 0;
	double resy_dam = 0;
	double resx_dam_min = 10000;
	double resy_dam_min = 10000;
	int nhbdc_dam = 0;
	if( n_hbd_clusters_tmp!=100000 && hbd_cluster_mid_tmp.size()!=0 && hbd_cluster_x_tmp.size()!=0 && hbd_cluster_y_tmp.size()!=0 ){
	  for(int ihbd=0;ihbd<n_hbd_clusters_tmp;ihbd++){// hbdcluster loop
	    if ( hbd_cluster_t_tmp.at(ihbd)>200 ) continue;
	    if(  hbd_cluster_mid_tmp.at(ihbd) == trk_mid ){
	      resx_dam = hbd_cluster_x_tmp.at(ihbd) - trk_lx;
	      resy_dam = hbd_cluster_y_tmp.at(ihbd) - trk_ly;
	      out_track_allhit_dum_resx[ntrkacc].push_back(resx_dam);
	      out_track_allhit_dum_resy[ntrkacc].push_back(resy_dam);
	      out_track_allhit_dum_ftime[ntrkacc].push_back(hbd_cluster_ftime_tmp.at(ihbd));
	      out_track_allhit_dum_adc[ntrkacc].push_back(hbd_cluster_adc_tmp.at(ihbd));
	      if( resx_dam*resx_dam+resy_dam*resy_dam < resx_dam_min*resx_dam_min+resy_dam_min*resy_dam_min ){
		resx_dam_min = resx_dam;
		resy_dam_min = resy_dam;
	      }
	      nhbdc_dam++;
	    }	    
	  }// hbdcluster loop
	}//dammy
	out_track_dum_nearx.push_back(resx_dam_min);
	out_track_dum_neary.push_back(resy_dam_min);
	out_track_dum_multiplicity.push_back(nhbdc_dam);
	ntrkacc++;
      }//track loop
      if(plus_index!=-10000){out_is_selected.at(plus_index)=1;}
      if(minus_index!=-10000){out_is_selected.at(minus_index)=1;}

      if(ntrkacc!=0){
	n_hbd_clusters_tmp = n_hbd_clusters;
	hbd_cluster_mid_tmp.resize(n_hbd_clusters);
	hbd_cluster_x_tmp.resize(n_hbd_clusters);
	hbd_cluster_y_tmp.resize(n_hbd_clusters);
	hbd_cluster_adc_tmp.resize(n_hbd_clusters);
	hbd_cluster_eprob_tmp.resize(n_hbd_clusters);
	hbd_cluster_t_tmp.resize(n_hbd_clusters);
	hbd_cluster_ftime_tmp.resize(n_hbd_clusters);
	copy( hbd_cluster_mid->begin(), hbd_cluster_mid->end(), hbd_cluster_mid_tmp.begin() );
	copy( hbd_cluster_x->begin(), hbd_cluster_x->end(), hbd_cluster_x_tmp.begin() );
	copy( hbd_cluster_y->begin(), hbd_cluster_y->end(), hbd_cluster_y_tmp.begin() );
	copy( hbd_cluster_adc->begin(), hbd_cluster_adc->end(), hbd_cluster_adc_tmp.begin() );
	copy( hbd_cluster_eprob->begin(), hbd_cluster_eprob->end(), hbd_cluster_eprob_tmp.begin() );
	copy( hbd_cluster_t->begin(), hbd_cluster_t->end(), hbd_cluster_t_tmp.begin() );
	copy( hbd_cluster_ftime->begin(), hbd_cluster_ftime->end(), hbd_cluster_ftime_tmp.begin() );

	//Get Hits & Clusters
	out_n_tracks = ntrkacc;
	out_run_id = run_id;
	out_event_id = event_id;
	out_spill_id = spill_id;
	out_n_hbd_clusters = n_hbd_clusters;
	out_n_lg_hits = n_lg_hits;
	out_hbd_cluster_id.resize(n_hbd_clusters*2);
	out_hbd_cluster_mid.resize(n_hbd_clusters);
	out_hbd_cluster_x.resize(n_hbd_clusters);
	out_hbd_cluster_y.resize(n_hbd_clusters);
	out_hbd_cluster_gx.resize(n_hbd_clusters);
	out_hbd_cluster_gy.resize(n_hbd_clusters);
	out_hbd_cluster_gz.resize(n_hbd_clusters);
	out_hbd_cluster_adc.resize(n_hbd_clusters);
	out_hbd_cluster_t.resize(n_hbd_clusters);
	out_hbd_cluster_ftime.resize(n_hbd_clusters);
	out_hbd_cluster_tdiff.resize(n_hbd_clusters);
	out_hbd_cluster_size.resize(n_hbd_clusters);
	out_hbd_cluster_eprob.resize(n_hbd_clusters);
	out_hbd_cluster_cprob.resize(n_hbd_clusters);
	out_lg_hit_id.resize(n_lg_hits);
	out_lg_hit_mid.resize(n_lg_hits);
	out_lg_hit_x.resize(n_lg_hits);
	out_lg_hit_y.resize(n_lg_hits);
	out_lg_hit_gx.resize(n_lg_hits);
	out_lg_hit_gy.resize(n_lg_hits);
	out_lg_hit_gz.resize(n_lg_hits);
	out_lg_hit_adc.resize(n_lg_hits);
	out_lg_hit_t.resize(n_lg_hits);
	out_lg_hit_npeaks.resize(n_lg_hits);
	out_lg_hit_fflag.resize(n_lg_hits);
	copy( hbd_cluster_id->begin(), hbd_cluster_id->end(), out_hbd_cluster_id.begin() );
	copy( hbd_cluster_mid->begin(), hbd_cluster_mid->end(), out_hbd_cluster_mid.begin() );
	copy( hbd_cluster_x->begin(), hbd_cluster_x->end(), out_hbd_cluster_x.begin() );
	copy( hbd_cluster_y->begin(), hbd_cluster_y->end(), out_hbd_cluster_y.begin() );
	copy( hbd_cluster_gx->begin(), hbd_cluster_gx->end(), out_hbd_cluster_gx.begin() );
	copy( hbd_cluster_gy->begin(), hbd_cluster_gy->end(), out_hbd_cluster_gy.begin() );
	copy( hbd_cluster_gz->begin(), hbd_cluster_gz->end(), out_hbd_cluster_gz.begin() );
	copy( hbd_cluster_adc->begin(), hbd_cluster_adc->end(), out_hbd_cluster_adc.begin() );
	copy( hbd_cluster_t->begin(), hbd_cluster_t->end(), out_hbd_cluster_t.begin() );
	copy( hbd_cluster_ftime->begin(), hbd_cluster_ftime->end(), out_hbd_cluster_ftime.begin() );
	copy( hbd_cluster_tdiff->begin(), hbd_cluster_tdiff->end(), out_hbd_cluster_tdiff.begin() );
	copy( hbd_cluster_size->begin(), hbd_cluster_size->end(), out_hbd_cluster_size.begin() );
	copy( hbd_cluster_eprob->begin(), hbd_cluster_eprob->end(), out_hbd_cluster_eprob.begin() );
	copy( hbd_cluster_cprob->begin(), hbd_cluster_cprob->end(), out_hbd_cluster_cprob.begin() );
	copy( lg_hit_id->begin(), lg_hit_id->end(), out_lg_hit_id.begin() );
	copy( lg_hit_mid->begin(), lg_hit_mid->end(), out_lg_hit_mid.begin() );
	copy( lg_hit_x->begin(), lg_hit_x->end(), out_lg_hit_x.begin() );
	copy( lg_hit_y->begin(), lg_hit_y->end(), out_lg_hit_y.begin() );
	copy( lg_hit_gx->begin(), lg_hit_gx->end(), out_lg_hit_gx.begin() );
	copy( lg_hit_gy->begin(), lg_hit_gy->end(), out_lg_hit_gy.begin() );
	copy( lg_hit_gz->begin(), lg_hit_gz->end(), out_lg_hit_gz.begin() );
	copy( lg_hit_adc->begin(), lg_hit_adc->end(), out_lg_hit_adc.begin() );
	copy( lg_hit_t->begin(), lg_hit_t->end(), out_lg_hit_t.begin() );
	copy( lg_hit_npeaks->begin(), lg_hit_npeaks->end(), out_lg_hit_npeaks.begin() );
	copy( lg_hit_fflag->begin(), lg_hit_fflag->end(), out_lg_hit_fflag.begin() );

	//LG clustering
	E16ANA_LGClustering clustering;
	for (int idst1hit = 0; idst1hit < n_lg_hits; idst1hit++) {//dst1hit loop
	  if(lg_hit_fflag->at(idst1hit)<2){
	    clustering.SetHitData(
	      idst1hit,
	      lg_hit_mid->at(idst1hit),
	      LocaltoCh(lg_hit_x->at(idst1hit),lg_hit_y->at(idst1hit)),
	      lg_hit_adc->at(idst1hit),
	      lg_hit_t->at(idst1hit),
	      lg_hit_adc->at(idst1hit),
	      lg_hit_x->at(idst1hit),
	      lg_hit_y->at(idst1hit),
	      0.);
	  }
	}//dst1hit loop
	clustering.Clustering();
	out_n_lg_clusters = clustering.LGClusterSize();
	out_lg_cluster_id.resize(out_n_lg_clusters);
	out_lg_cluster_mid.resize(out_n_lg_clusters);
	out_lg_cluster_x.resize(out_n_lg_clusters);
	out_lg_cluster_y.resize(out_n_lg_clusters);
	out_lg_cluster_adc.resize(out_n_lg_clusters);
	out_lg_cluster_ftime.resize(out_n_lg_clusters);
	out_lg_cluster_tdiff.resize(out_n_lg_clusters);
	out_lg_cluster_mpcid.resize(out_n_lg_clusters);
	out_lg_cluster_mp.resize(out_n_lg_clusters);
	out_lg_cluster_size.resize(out_n_lg_clusters);
	for(int icluster=0;icluster<out_n_lg_clusters;icluster++){
	  E16ANA_LGClustering::lgcluster cith = clustering.LGClusterIth(icluster);
	  out_lg_cluster_id.at(icluster) = icluster;
	  out_lg_cluster_mid.at(icluster) = cith.mid;
	  out_lg_cluster_x.at(icluster) = cith.lx;
	  out_lg_cluster_y.at(icluster) = cith.ly;
	  out_lg_cluster_adc.at(icluster) = cith.peaksum;
	  out_lg_cluster_ftime.at(icluster) = cith.fasttiming;
	  out_lg_cluster_tdiff.at(icluster) = cith.timediff;
	  out_lg_cluster_mpcid.at(icluster) = cith.maxcid;
	  out_lg_cluster_mp.at(icluster) = cith.maxpeak;
	  out_lg_cluster_size.at(icluster) = cith.hids.size();
	}

	tree->Fill();
      }
      nevent++;
   }//event loop

   fout->Write();
   fout->Close();

}

void SingleTrackAnalyzerForRes::ResidualHBD(int runoption, int maxevent)
{

   if (fChain == 0) return;

   const int bin = 1600;
   int roughbin = 800;
   const int halfwidth = 50; //for calcuration of normalized factor
   int hw_int = 15;
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
   TH1F *haresx[5][3];//0:all, 1:low-p, 2:high-p
   TH1F *haresy[5][3];
   TH1F *haresxd[5][3];
   TH1F *haresyd[5][3];
   int ntrack[5][3]={0};
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
     for(int j=0;j<3;j++){
       haresx[i][j] = new TH1F(Form("haresx%d%d",i,j),Form("allhit_residual_x_mod%d_mom%d",103+i,j),roughbin,-800,800);
       haresy[i][j] = new TH1F(Form("haresy%d%d",i,j),Form("allhit_residual_y_mod%d_mom%d",103+i,j),roughbin,-800,800);
       haresxd[i][j] = new TH1F(Form("haresxd%d%d",i,j),Form("allhit_residual_x_dummy_mod%d_mom%d",103+i,j),roughbin,-800,800);
       haresyd[i][j] = new TH1F(Form("haresyd%d%d",i,j),Form("allhit_residual_y_dummy_mod%d_mom%d",103+i,j),roughbin,-800,800);
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

   E16ANA_HBDDeadChannel hbddch;
   std::string hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0c-220114.dat";
   if(runoption==0){
     hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0b-220114.dat";
   }
   hbddch.ReadFile(hbd_deadch_file.c_str());

   Long64_t n_entries = fChain->GetEntries();
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   Int_t n_hbd_clusters_tmp = 100000;
   std::vector<int> hbd_cluster_mid_tmp(0);
   std::vector<double> hbd_cluster_x_tmp(0);
   std::vector<double> hbd_cluster_y_tmp(0);
   std::vector<double> hbd_cluster_adc_tmp(0);
   std::vector<double> hbd_cluster_eprob_tmp(0);
   std::vector<double> hbd_cluster_t_tmp(0);

   int nevent=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
      if( maxevent!=-1&&nevent>maxevent ){break;}

      if (Cut(ientry) < 0) continue;

      int ntrkacc = 0;
      int ntracks = track_id->size();

      ////////One Track
      double chisq_plus_min = 10000;
      double chisq_minus_min = 10000;
      int plus_id = -10000;
      int minus_id = -10000;
      for(int itrack=0;itrack<ntracks;itrack++){//pre track loop
	double trk_lx = -10000;
	double trk_ly = -10000;
	int trk_mid = CutOfTrackForResidualHBD(ientry,itrack,trk_lx,trk_ly);
	if (trk_mid < 0) continue;
	double cog[2] = {trk_lx,trk_ly};
	int hbd_padid = E16ANA_HBDGeometry::GetPadIDWLocalCoordinate(trk_mid,cog);
	if( hbddch.Status(trk_mid,hbd_padid) != 0 ) continue;

	if(rk_charge->at(itrack)==1){
	  if(chi_square->at(itrack)<chisq_plus_min){
	    chisq_plus_min = chi_square->at(itrack);
	    plus_id = track_id->at(itrack);
	  }	  
	}
	if(rk_charge->at(itrack)==-1){
	  if(chi_square->at(itrack)<chisq_minus_min){
	    chisq_minus_min = chi_square->at(itrack);
	    minus_id = track_id->at(itrack);
	  }	  
	}
      }//pre track loop
      std::vector<int> good_trk_id(0);
      if(plus_id!=-10000){good_trk_id.push_back(plus_id);}
      if(minus_id!=-10000){good_trk_id.push_back(minus_id);}
      ////////One Track

      for(int itrack=0;itrack<ntracks;itrack++){//track loop

	double trk_lx = -10000;
	double trk_ly = -10000;
	double trk_mom = -10000;
	double trk_momx = -10000;
	double trk_momy = -10000;
	double trk_momz = -10000;
	float trk_lg_time = -10000;
	float trk_lg_adc = -10000;
	int trk_lg_mod = -10000;
	int trk_lg_ch = -10000;
	int trk_mid = CutOfTrackForResidualHBD(ientry,itrack,trk_lx,trk_ly,trk_mom,trk_momx,trk_momy,trk_momz,trk_lg_time,trk_lg_adc,trk_lg_mod,trk_lg_ch);
	//
        //double rand1 = (rand() %60600)/100. - 303.;
        //double rand2 = (rand() %60600)/100. - 303.;
	//trk_lx = rand1;
	//trk_ly = rand2;
	//
	if (trk_mid < 0) continue;
	double cog[2] = {trk_lx,trk_ly};
	int hbd_padid = E16ANA_HBDGeometry::GetPadIDWLocalCoordinate(trk_mid,cog);
	int hbd_status = hbddch.Status(trk_mid,hbd_padid);
	//std::cout<<trk_mid<<" "<<trk_lx<<" "<<trk_ly<<" "<<hbd_padid<<" "<<hbd_status<<std::endl;
	if(hbd_status!=0) continue;

	////////Check One Track
	bool OneTrackFlag=false;
	for(int i=0;i<good_trk_id.size();i++){
	  if(track_id->at(itrack)==good_trk_id.at(i)){ OneTrackFlag=true; break; }
	}
	if(OneTrackFlag==false) continue;
	////////Check One Track

	double resx = 0;
	double resy = 0;
	double resx_min = 10000;
	double resy_min = 10000;
	int nhbdc = 0;
	double ftime = -10000;
	for(int ihbd=0;ihbd<n_hbd_clusters;ihbd++){// hbdcluster loop
	  if ( hbd_cluster_t->at(ihbd)>200 ) continue;
	  if(  hbd_cluster_mid->at(ihbd) == trk_mid ){
	    resx = hbd_cluster_x->at(ihbd) - trk_lx;
	    resy = hbd_cluster_y->at(ihbd) - trk_ly;
	    haresx[trk_mid-103][0]->Fill(resx);
	    haresy[trk_mid-103][0]->Fill(resy);
	    if(trk_mom!=-10000&&trk_mom<2){
	      haresx[trk_mid-103][1]->Fill(resx);
	      haresy[trk_mid-103][1]->Fill(resy);
	    }
	    if(trk_mom!=-10000&&trk_mom>=2){
	      haresx[trk_mid-103][2]->Fill(resx);
	      haresy[trk_mid-103][2]->Fill(resy);
	    }
	    hares[trk_mid-103]->Fill(resx,resy);
	    if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	      resx_min = resx;
	      resy_min = resy;
	    }
	    if( resx*resx+resy*resy < hw_int*hw_int ){
	      ftime = hbd_cluster_ftime->at(ihbd);
	      ht[trk_mid-103]->Fill(ftime);
	      htlg[trk_mid-103]->Fill(ftime,trk_lg_time);
	      hadc[trk_mid-103]->Fill(hbd_cluster_adc->at(ihbd));
	      if(trk_lg_ch!=-10000&&trk_lg_mod==106){hlgadc[(trk_lg_ch/10)*7+(trk_lg_ch%10)]->Fill(trk_lg_adc);}
	    }
	    nhbdc++;
	  }	    
	}// hbdcluster loop
	ntrack[trk_mid-103][0]++;
	if(trk_mom!=-10000&&trk_mom<2){
	  ntrack[trk_mid-103][1]++;
	}
	if(trk_mom!=-10000&&trk_mom>=2){
	  ntrack[trk_mid-103][2]++;
	}
	h1->Fill(resx_min);
	hx[trk_mid-103]->Fill(resx_min);
	h2->Fill(resy_min);
	hy[trk_mid-103]->Fill(resy_min);
	hn->Fill(nhbdc);
	hxn[trk_mid-103]->Fill(nhbdc);


	if( n_hbd_clusters_tmp!=100000 && hbd_cluster_mid_tmp.size()!=0 && hbd_cluster_x_tmp.size()!=0 && hbd_cluster_y_tmp.size()!=0 ){
	  double resx_dam = 0;
	  double resy_dam = 0;
	  double resx_dam_min = 10000;
	  double resy_dam_min = 10000;
	  int nhbdc_dam = 0;
	  for(int ihbd=0;ihbd<n_hbd_clusters_tmp;ihbd++){// hbdcluster loop
	    if ( hbd_cluster_t_tmp.at(ihbd)>200 ) continue;
	    if(  hbd_cluster_mid_tmp.at(ihbd) == trk_mid ){
	      resx_dam = hbd_cluster_x_tmp.at(ihbd) - trk_lx;
	      resy_dam = hbd_cluster_y_tmp.at(ihbd) - trk_ly;
	      haresxd[trk_mid-103][0]->Fill(resx_dam);
	      haresyd[trk_mid-103][0]->Fill(resy_dam);
	      if(trk_mom!=-10000&&trk_mom<2){
		haresxd[trk_mid-103][1]->Fill(resx_dam);
		haresyd[trk_mid-103][1]->Fill(resy_dam);
	      }
	      if(trk_mom!=-10000&&trk_mom>=2){
		haresxd[trk_mid-103][2]->Fill(resx_dam);
		haresyd[trk_mid-103][2]->Fill(resy_dam);
	      }
	      haresd[trk_mid-103]->Fill(resx_dam,resy_dam);
	      if( resx_dam*resx_dam+resy_dam*resy_dam < resx_dam_min*resx_dam_min+resy_dam_min*resy_dam_min ){
		resx_dam_min = resx_dam;
		resy_dam_min = resy_dam;
	      }
	      if( resx*resx+resy*resy < hw_int*hw_int ){
		hadcd[trk_mid-103]->Fill(hbd_cluster_adc_tmp.at(ihbd));
	      }
	      nhbdc_dam++;
	    }	    
	  }// hbdcluster loop
	  h3->Fill(resx_dam_min);
	  hxd[trk_mid-103]->Fill(resx_dam_min);
	  h4->Fill(resy_dam_min);
	  hyd[trk_mid-103]->Fill(resy_dam_min);
	  hn2->Fill(nhbdc_dam);
	}//dammy

	ntrkacc++;
      }//track loop

      if(ntrkacc!=0){
	he->Fill(ntrkacc);
	n_hbd_clusters_tmp = n_hbd_clusters;
	hbd_cluster_mid_tmp.resize(n_hbd_clusters);
	hbd_cluster_x_tmp.resize(n_hbd_clusters);
	hbd_cluster_y_tmp.resize(n_hbd_clusters);
	hbd_cluster_adc_tmp.resize(n_hbd_clusters);
	hbd_cluster_eprob_tmp.resize(n_hbd_clusters);
	hbd_cluster_t_tmp.resize(n_hbd_clusters);
	copy( hbd_cluster_mid->begin(), hbd_cluster_mid->end(), hbd_cluster_mid_tmp.begin() );
	copy( hbd_cluster_x->begin(), hbd_cluster_x->end(), hbd_cluster_x_tmp.begin() );
	copy( hbd_cluster_y->begin(), hbd_cluster_y->end(), hbd_cluster_y_tmp.begin() );
	copy( hbd_cluster_adc->begin(), hbd_cluster_adc->end(), hbd_cluster_adc_tmp.begin() );
	copy( hbd_cluster_eprob->begin(), hbd_cluster_eprob->end(), hbd_cluster_eprob_tmp.begin() );
	copy( hbd_cluster_t->begin(), hbd_cluster_t->end(), hbd_cluster_t_tmp.begin() );
      }
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

   TString outfile = "./residual_hbd.pdf";

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
   TCanvas* csubdnn[4];
   TH1F* hsubdnn[4][2];
   for(int i=0;i<4;i++){
     csubdnn[i] = new TCanvas(Form("csubdnn%d",i),Form("csubdnn%d",i),700,500);
     csubdnn[i]->Divide(2,2);
     csubdnn[i]->cd(1);
     hx[(i+3)%5]->Draw("hist e");
     hxd[(i+3)%5]->SetLineColor(6);
     hxd[(i+3)%5]->Draw("hist e same");
     csubdnn[i]->cd(2);
     hy[(i+3)%5]->Draw("hist e");
     hyd[(i+3)%5]->SetLineColor(6);
     hyd[(i+3)%5]->Draw("hist e same");
     csubdnn[i]->cd(3);
     hsubdnn[i][0] = (TH1F*)hx[(i+3)%5]->Clone();
     hsubdnn[i][0]->Add(hxd[(i+3)%5],-1);
     hsubdnn[i][0]->Draw();
     hsubdnn[i][0]->Fit("gaus","","",-30,30);
     csubdnn[i]->cd(4);
     hsubdnn[i][1] = (TH1F*)hy[(i+3)%5]->Clone();
     hsubdnn[i][1]->Add(hyd[(i+3)%5],-1);
     hsubdnn[i][1]->Draw();
     hsubdnn[i][1]->Fit("gaus","","",-30,30);
   }
   TCanvas* casubd[4][3];
   TH1F* hasubd[4][2][3];
   TLegend* lasubd[4][2][3];
   int vasubd[4][2][3];
   for(int j=0;j<3;j++){
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
   for(int i=0;i<4;i++){
     csubdnn[i]->SaveAs(outfile,"pdf");
   }
   for(int i=0;i<4;i++){
     for(int j=0;j<3;j++){
       casubd[i][j]->SaveAs(outfile,"pdf");
     }
     casub2d[i]->SaveAs(outfile,"pdf");
   }
   clgadc->SaveAs(outfile,"pdf");
   cdef->SaveAs(outfile+"]","pdf");
}

void SingleTrackAnalyzerForRes::MkTreeForTrackSelection(int runoption, int maxevent, char* out_file_name, int hbd_track_module, int track_charge, double max_chi_square)
{
   if (fChain == 0) return;

   TFile* fout = new TFile(out_file_name,"recreate");
   TTree* tree = new TTree("tree","tree");

   Int_t           out_run_id;
   Int_t           out_event_id;
   Int_t           out_spill_id;
   // Int_t           out_n_hbd_clusters;
   // vector<int>     out_hbd_cluster_id;
   // vector<int>     out_hbd_cluster_mid;
   // vector<double>  out_hbd_cluster_x;
   // vector<double>  out_hbd_cluster_y;
   // vector<double>  out_hbd_cluster_gx;
   // vector<double>  out_hbd_cluster_gy;
   // vector<double>  out_hbd_cluster_gz;
   // vector<float>   out_hbd_cluster_adc;
   // vector<double>  out_hbd_cluster_t;
   // vector<float>   out_hbd_cluster_ftime;
   // vector<float>   out_hbd_cluster_tdiff;
   // vector<int>     out_hbd_cluster_size;
   // vector<float>   out_hbd_cluster_eprob;
   // vector<float>   out_hbd_cluster_cprob;
   // Int_t           out_n_lg_hits;
   // vector<int>     out_lg_hit_id;
   // vector<int>     out_lg_hit_mid;
   // vector<double>  out_lg_hit_x;
   // vector<double>  out_lg_hit_y;
   // vector<double>  out_lg_hit_gx;
   // vector<double>  out_lg_hit_gy;
   // vector<double>  out_lg_hit_gz;
   // vector<float>   out_lg_hit_adc;
   // vector<float>   out_lg_hit_t;
   // vector<int>     out_lg_hit_npeaks;
   // vector<int>     out_lg_hit_fflag;
   // // Int_t           out_n_lg_clusters;
   // // vector<int>     out_lg_cluster_id;
   // // vector<int>     out_lg_cluster_mid;
   // // vector<double>  out_lg_cluster_x;
   // // vector<double>  out_lg_cluster_y;
   // // vector<float>   out_lg_cluster_adc;
   // // vector<float>   out_lg_cluster_ftime;
   // // vector<float>   out_lg_cluster_tdiff;
   // // vector<int>     out_lg_cluster_mpcid;
   // // vector<float>   out_lg_cluster_mp;
   // // vector<int>     out_lg_cluster_size;
   Int_t out_n_tracks;
   vector<int> out_track_id;
   vector<double> out_chi_square;
   vector<int> out_rk_charge;
   vector<int> out_is_selected;
   vector<double> out_track_mom;
   vector<double> out_track_mom_x;
   vector<double> out_track_mom_y;
   vector<double> out_track_mom_z;
   vector<double> out_track_tgt_dist;
   vector<int> out_track_tgt_id;
   vector<double> out_track_lg_pi_eff1;
   vector<double> out_track_lg_pi_eff2;
   vector<double> out_track_angle_lx;
   vector<double> out_track_angle_ly;
   vector<double> out_track_position_block_lx;
   vector<double> out_track_position_block_ly;
   vector<double> out_track_ssd_t;
   vector<double> out_track_ssd_adc;
   vector<double> out_track_gtr100x_t;
   vector<double> out_track_gtr100x_adc;
   vector<double> out_track_gtr100y_t;
   vector<double> out_track_gtr100y_adc;
   vector<double> out_track_gtr200x_t;
   vector<double> out_track_gtr200x_adc;
   vector<double> out_track_gtr200y_t;
   vector<double> out_track_gtr200y_adc;
   vector<double> out_track_gtr300x_t;
   vector<double> out_track_gtr300x_adc;
   vector<double> out_track_gtr300y_t;
   vector<double> out_track_gtr300y_adc;
   vector<double> out_track_w_trg_bias;
   vector<int> out_track_hbd_mid;
   vector<double> out_track_hbd_lx;
   vector<double> out_track_hbd_ly;
   vector<double> out_track_hbd_nearx;
   vector<double> out_track_hbd_neary;
   vector<int> out_track_hbd_multiplicity;
   vector<double> out_track_hbd_dum_nearx;
   vector<double> out_track_hbd_dum_neary;
   vector<int> out_track_hbd_dum_multiplicity;
   vector<int> out_track_lg_mid;
   vector<double> out_track_lg_lx;
   vector<double> out_track_lg_ly;
   vector<int> out_track_lg_blockch;
   vector<double> out_track_lg_nearx;
   vector<double> out_track_lg_neary;
   vector<int> out_track_lg_multiplicity;
   vector<double> out_track_lg_dum_nearx;
   vector<double> out_track_lg_dum_neary;
   vector<int> out_track_lg_dum_multiplicity;
   vector<double> out_track_lg_cl_nearx;
   vector<double> out_track_lg_cl_neary;
   vector<int> out_track_lg_cl_multiplicity;
   vector<double> out_track_lg_cl_dum_nearx;
   vector<double> out_track_lg_cl_dum_neary;
   vector<int> out_track_lg_cl_dum_multiplicity;
   vector<vector<double>> out_track_hbd_allhit_resx;
   vector<vector<double>> out_track_hbd_allhit_resy;
   vector<vector<double>> out_track_hbd_allhit_ftime;
   vector<vector<double>> out_track_hbd_allhit_adc;
   vector<vector<double>> out_track_hbd_allhit_size;
   vector<vector<double>> out_track_hbd_allhit_eprob;
   vector<vector<double>> out_track_hbd_allhit_cprob;
   vector<vector<double>> out_track_hbd_allhit_dum_resx;
   vector<vector<double>> out_track_hbd_allhit_dum_resy;
   vector<vector<double>> out_track_hbd_allhit_dum_ftime;
   vector<vector<double>> out_track_hbd_allhit_dum_adc;
   vector<vector<double>> out_track_hbd_allhit_dum_size;
   vector<vector<double>> out_track_hbd_allhit_dum_eprob;
   vector<vector<double>> out_track_hbd_allhit_dum_cprob;
   vector<vector<double>> out_track_lg_allhit_resx;
   vector<vector<double>> out_track_lg_allhit_resy;
   vector<vector<double>> out_track_lg_allhit_ftime;
   vector<vector<double>> out_track_lg_allhit_adc;
   vector<vector<double>> out_track_lg_allhit_trgt;
   vector<vector<double>> out_track_lg_allhit_dum_resx;
   vector<vector<double>> out_track_lg_allhit_dum_resy;
   vector<vector<double>> out_track_lg_allhit_dum_ftime;
   vector<vector<double>> out_track_lg_allhit_dum_adc;
   vector<vector<double>> out_track_lg_cl_allhit_resx;
   vector<vector<double>> out_track_lg_cl_allhit_resy;
   vector<vector<double>> out_track_lg_cl_allhit_ftime;
   vector<vector<double>> out_track_lg_cl_allhit_adc;
   vector<vector<double>> out_track_lg_cl_allhit_maxpeak;
   vector<vector<double>> out_track_lg_cl_allhit_maxcid;
   vector<vector<double>> out_track_lg_cl_allhit_dum_resx;
   vector<vector<double>> out_track_lg_cl_allhit_dum_resy;
   vector<vector<double>> out_track_lg_cl_allhit_dum_ftime;
   vector<vector<double>> out_track_lg_cl_allhit_dum_adc;
   vector<vector<double>> out_track_lg_cl_allhit_dum_maxpeak;
   vector<vector<double>> out_track_lg_cl_allhit_dum_maxcid;

   tree->Branch("run_id",&out_run_id,"run_id/I");
   tree->Branch("event_id",&out_event_id,"event_id/I");
   tree->Branch("spill_id",&out_run_id,"spill_id/I");
   // tree->Branch("n_hbd_clusters",&out_n_hbd_clusters,"n_hbd_clusters/I");
   // tree->Branch("hbd_cluster_id", &out_hbd_cluster_id);
   // tree->Branch("hbd_cluster_mid", &out_hbd_cluster_mid);
   // tree->Branch("hbd_cluster_x", &out_hbd_cluster_x);
   // tree->Branch("hbd_cluster_y", &out_hbd_cluster_y);
   // tree->Branch("hbd_cluster_gx", &out_hbd_cluster_gx);
   // tree->Branch("hbd_cluster_gy", &out_hbd_cluster_gy);
   // tree->Branch("hbd_cluster_gz", &out_hbd_cluster_gz);
   // tree->Branch("hbd_cluster_adc", &out_hbd_cluster_adc);
   // tree->Branch("hbd_cluster_t", &out_hbd_cluster_t);
   // tree->Branch("hbd_cluster_ftime", &out_hbd_cluster_ftime);
   // tree->Branch("hbd_cluster_tdiff", &out_hbd_cluster_tdiff);
   // tree->Branch("hbd_cluster_size", &out_hbd_cluster_size);
   // tree->Branch("hbd_cluster_eprob", &out_hbd_cluster_eprob);
   // tree->Branch("hbd_cluster_cprob", &out_hbd_cluster_cprob);
   // tree->Branch("n_lg_hits",&out_n_lg_hits,"n_lg_hits/I");
   // tree->Branch("lg_hit_id", &out_lg_hit_id);
   // tree->Branch("lg_hit_mid", &out_lg_hit_mid);
   // tree->Branch("lg_hit_x", &out_lg_hit_x);
   // tree->Branch("lg_hit_y", &out_lg_hit_y);
   // tree->Branch("lg_hit_gx", &out_lg_hit_gx);
   // tree->Branch("lg_hit_gy", &out_lg_hit_gy);
   // tree->Branch("lg_hit_gz", &out_lg_hit_gz);
   // tree->Branch("lg_hit_adc", &out_lg_hit_adc);
   // tree->Branch("lg_hit_t", &out_lg_hit_t);
   // tree->Branch("lg_hit_npeaks", &out_lg_hit_npeaks);
   // tree->Branch("lg_hit_fflag", &out_lg_hit_fflag);
   // tree->Branch("n_lg_clusters",&out_n_lg_clusters,"n_lg_clusters/I");
   // tree->Branch("lg_cluster_id", &out_lg_cluster_id);
   // tree->Branch("lg_cluster_mid", &out_lg_cluster_mid);
   // tree->Branch("lg_cluster_x", &out_lg_cluster_x);
   // tree->Branch("lg_cluster_y", &out_lg_cluster_y);
   // tree->Branch("lg_cluster_adc", &out_lg_cluster_adc);
   // tree->Branch("lg_cluster_ftime", &out_lg_cluster_ftime);
   // tree->Branch("lg_cluster_tdiff", &out_lg_cluster_tdiff);
   // tree->Branch("lg_cluster_mpcid", &out_lg_cluster_mpcid);
   // tree->Branch("lg_cluster_mp", &out_lg_cluster_mp);
   // tree->Branch("lg_cluster_size", &out_lg_cluster_size);
   tree->Branch("n_tracks",&out_n_tracks,"n_tracks/I");
   tree->Branch("track_id", &out_track_id);
   tree->Branch("chi_square", &out_chi_square);
   tree->Branch("rk_charge", &out_rk_charge);
   tree->Branch("is_selected", &out_is_selected);
   tree->Branch("track_mom", &out_track_mom);
   tree->Branch("track_mom_x", &out_track_mom_x);
   tree->Branch("track_mom_y", &out_track_mom_y);
   tree->Branch("track_mom_z", &out_track_mom_z);
   tree->Branch("track_tgt_dist", &out_track_tgt_dist);
   tree->Branch("track_tgt_id", &out_track_tgt_id);
   tree->Branch("track_lg_pi_eff1", &out_track_lg_pi_eff1);
   tree->Branch("track_lg_pi_eff2", &out_track_lg_pi_eff2);
   tree->Branch("track_angle_lx", &out_track_angle_lx);
   tree->Branch("track_angle_ly", &out_track_angle_ly);
   tree->Branch("track_position_block_lx", &out_track_position_block_lx);
   tree->Branch("track_position_block_ly", &out_track_position_block_ly);
   tree->Branch("track_ssd_t", &out_track_ssd_t);
   tree->Branch("track_ssd_adc", &out_track_ssd_adc);
   tree->Branch("track_gtr100x_t", &out_track_gtr100x_t);
   tree->Branch("track_gtr100x_adc", &out_track_gtr100x_adc);
   tree->Branch("track_gtr100y_t", &out_track_gtr100y_t);
   tree->Branch("track_gtr100y_adc", &out_track_gtr100y_adc);
   tree->Branch("track_gtr200x_t", &out_track_gtr200x_t);
   tree->Branch("track_gtr200x_adc", &out_track_gtr200x_adc);
   tree->Branch("track_gtr200y_t", &out_track_gtr200y_t);
   tree->Branch("track_gtr200y_adc", &out_track_gtr200y_adc);
   tree->Branch("track_gtr300x_t", &out_track_gtr300x_t);
   tree->Branch("track_gtr300x_adc", &out_track_gtr300x_adc);
   tree->Branch("track_gtr300y_t", &out_track_gtr300y_t);
   tree->Branch("track_gtr300y_adc", &out_track_gtr300y_adc);
   tree->Branch("track_w_trg_bias", &out_track_w_trg_bias);
   tree->Branch("track_hbd_mid", &out_track_hbd_mid);
   tree->Branch("track_hbd_lx", &out_track_hbd_lx);
   tree->Branch("track_hbd_ly", &out_track_hbd_ly);
   tree->Branch("track_hbd_nearx", &out_track_hbd_nearx);
   tree->Branch("track_hbd_neary", &out_track_hbd_neary);
   tree->Branch("track_hbd_multiplicity", &out_track_hbd_multiplicity);
   tree->Branch("track_hbd_dum_nearx", &out_track_hbd_dum_nearx);
   tree->Branch("track_hbd_dum_neary", &out_track_hbd_dum_neary);
   tree->Branch("track_hbd_dum_multiplicity", &out_track_hbd_dum_multiplicity);
   tree->Branch("track_lg_mid", &out_track_lg_mid);
   tree->Branch("track_lg_lx", &out_track_lg_lx);
   tree->Branch("track_lg_ly", &out_track_lg_ly);
   tree->Branch("track_lg_blockch", &out_track_lg_blockch);
   tree->Branch("track_lg_nearx", &out_track_lg_nearx);
   tree->Branch("track_lg_neary", &out_track_lg_neary);
   tree->Branch("track_lg_multiplicity", &out_track_lg_multiplicity);
   tree->Branch("track_lg_dum_nearx", &out_track_lg_dum_nearx);
   tree->Branch("track_lg_dum_neary", &out_track_lg_dum_neary);
   tree->Branch("track_lg_dum_multiplicity", &out_track_lg_dum_multiplicity);
   tree->Branch("track_lg_cl_nearx", &out_track_lg_cl_nearx);
   tree->Branch("track_lg_cl_neary", &out_track_lg_cl_neary);
   tree->Branch("track_lg_cl_multiplicity", &out_track_lg_cl_multiplicity);
   tree->Branch("track_lg_cl_dum_nearx", &out_track_lg_cl_dum_nearx);
   tree->Branch("track_lg_cl_dum_neary", &out_track_lg_cl_dum_neary);
   tree->Branch("track_lg_cl_dum_multiplicity", &out_track_lg_cl_dum_multiplicity);
   tree->Branch("track_hbd_allhit_resx", &out_track_hbd_allhit_resx);
   tree->Branch("track_hbd_allhit_resy", &out_track_hbd_allhit_resy);
   tree->Branch("track_hbd_allhit_ftime", &out_track_hbd_allhit_ftime);
   tree->Branch("track_hbd_allhit_adc", &out_track_hbd_allhit_adc);
   tree->Branch("track_hbd_allhit_size", &out_track_hbd_allhit_size);
   tree->Branch("track_hbd_allhit_eprob", &out_track_hbd_allhit_eprob);
   tree->Branch("track_hbd_allhit_cprob", &out_track_hbd_allhit_cprob);
   tree->Branch("track_hbd_allhit_dum_resx", &out_track_hbd_allhit_dum_resx);
   tree->Branch("track_hbd_allhit_dum_resy", &out_track_hbd_allhit_dum_resy);
   tree->Branch("track_hbd_allhit_dum_ftime", &out_track_hbd_allhit_dum_ftime);
   tree->Branch("track_hbd_allhit_dum_adc", &out_track_hbd_allhit_dum_adc);
   tree->Branch("track_hbd_allhit_dum_size", &out_track_hbd_allhit_dum_size);
   tree->Branch("track_hbd_allhit_dum_eprob", &out_track_hbd_allhit_dum_eprob);
   tree->Branch("track_hbd_allhit_dum_cprob", &out_track_hbd_allhit_dum_cprob);
   tree->Branch("track_lg_allhit_resx", &out_track_lg_allhit_resx);
   tree->Branch("track_lg_allhit_resy", &out_track_lg_allhit_resy);
   tree->Branch("track_lg_allhit_ftime", &out_track_lg_allhit_ftime);
   tree->Branch("track_lg_allhit_adc", &out_track_lg_allhit_adc);
   tree->Branch("track_lg_allhit_trgt", &out_track_lg_allhit_trgt);
   tree->Branch("track_lg_allhit_dum_resx", &out_track_lg_allhit_dum_resx);
   tree->Branch("track_lg_allhit_dum_resy", &out_track_lg_allhit_dum_resy);
   tree->Branch("track_lg_allhit_dum_ftime", &out_track_lg_allhit_dum_ftime);
   tree->Branch("track_lg_allhit_dum_adc", &out_track_lg_allhit_dum_adc);
   tree->Branch("track_lg_cl_allhit_resx", &out_track_lg_cl_allhit_resx);
   tree->Branch("track_lg_cl_allhit_resy", &out_track_lg_cl_allhit_resy);
   tree->Branch("track_lg_cl_allhit_ftime", &out_track_lg_cl_allhit_ftime);
   tree->Branch("track_lg_cl_allhit_adc", &out_track_lg_cl_allhit_adc);
   tree->Branch("track_lg_cl_allhit_maxpeak", &out_track_lg_cl_allhit_maxpeak);
   tree->Branch("track_lg_cl_allhit_maxcid", &out_track_lg_cl_allhit_maxcid);
   tree->Branch("track_lg_cl_allhit_dum_resx", &out_track_lg_cl_allhit_dum_resx);
   tree->Branch("track_lg_cl_allhit_dum_resy", &out_track_lg_cl_allhit_dum_resy);
   tree->Branch("track_lg_cl_allhit_dum_ftime", &out_track_lg_cl_allhit_dum_ftime);
   tree->Branch("track_lg_cl_allhit_dum_adc", &out_track_lg_cl_allhit_dum_adc);
   tree->Branch("track_lg_cl_allhit_dum_maxpeak", &out_track_lg_cl_allhit_dum_maxpeak);
   tree->Branch("track_lg_cl_allhit_dum_maxcid", &out_track_lg_cl_allhit_dum_maxcid);

   E16ANA_HBDDeadChannel hbddch;
   std::string hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0c-220114.dat";
   if(runoption==0){
     hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0b-220114.dat";
   }
   hbddch.ReadFile(hbd_deadch_file.c_str());

   auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
   E16ANA_GeometryV2::SetGlobalPointer(geometry);
   auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
   bfield_map->Initialize_binary();
   E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
   E16ANA_MultiTrack pair_fitter(bfield_map, geometry, 2);

   Long64_t n_entries = fChain->GetEntries();
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   Int_t n_hbd_clusters_tmp = 100000;
   std::vector<int> hbd_cluster_mid_tmp(0);
   std::vector<double> hbd_cluster_x_tmp(0);
   std::vector<double> hbd_cluster_y_tmp(0);
   std::vector<double> hbd_cluster_adc_tmp(0);
   std::vector<double> hbd_cluster_eprob_tmp(0);
   std::vector<double> hbd_cluster_cprob_tmp(0);
   std::vector<int> hbd_cluster_size_tmp(0);
   std::vector<double> hbd_cluster_t_tmp(0);
   std::vector<double> hbd_cluster_ftime_tmp(0);
   Int_t n_lg_hits_tmp = 100000;
   std::vector<int> lg_hit_mid_tmp(0);
   std::vector<double> lg_hit_x_tmp(0);
   std::vector<double> lg_hit_y_tmp(0);
   std::vector<float> lg_hit_adc_tmp(0);
   std::vector<float> lg_hit_t_tmp(0);
   std::vector<int> lg_hit_fflag_tmp(0);
   Int_t n_lg_clusters_tmp = 100000;
   std::vector<int> lg_cluster_mid_tmp(0);
   std::vector<double> lg_cluster_x_tmp(0);
   std::vector<double> lg_cluster_y_tmp(0);
   std::vector<float> lg_cluster_adc_tmp(0);
   std::vector<float> lg_cluster_t_tmp(0);
   std::vector<float> lg_cluster_maxpeak_tmp(0);
   std::vector<int> lg_cluster_maxcid_tmp(0);

   fChain->GetEntry(0);
   auto& calib = E16ANA_CalibDBManager::Instance();
   calib.SetRunID(run_id);
   auto trigger_param = new E16ANA_TriggerCalibParam();
   trigger_param->ReadConstantData(calib.CurrentRunID());
   bool TrigIsAWmax = trigger_param->IsMaximumWidth();
   int TrigAWmax = trigger_param->MaximumWidth();
   int TrigAWmin = trigger_param->MinimumWidth();
   int TrigTW = trigger_param->TimeWidth();
   if(!TrigIsAWmax){TrigAWmax=10000;}
   std::cout<<"Trig:"<<run_id<<" "<<TrigAWmin<<" "<<TrigAWmax<<" "<<TrigTW<<std::endl;

   int nevent=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
      if( maxevent!=-1&&nevent>maxevent ){break;}

      out_track_id.clear();
      out_chi_square.clear();
      out_rk_charge.clear();
      out_is_selected.clear();
      out_track_mom.clear();
      out_track_mom_x.clear();
      out_track_mom_y.clear();
      out_track_mom_z.clear();
      out_track_tgt_dist.clear();
      out_track_tgt_id.clear();
      out_track_lg_pi_eff1.clear();
      out_track_lg_pi_eff2.clear();
      out_track_angle_lx.clear();
      out_track_angle_ly.clear();
      out_track_position_block_lx.clear();
      out_track_position_block_ly.clear();
      out_track_ssd_t.clear();
      out_track_ssd_adc.clear();
      out_track_gtr100x_t.clear();
      out_track_gtr100x_adc.clear();
      out_track_gtr100y_t.clear();
      out_track_gtr100y_adc.clear();
      out_track_gtr200x_t.clear();
      out_track_gtr200x_adc.clear();
      out_track_gtr200y_t.clear();
      out_track_gtr200y_adc.clear();
      out_track_gtr300x_t.clear();
      out_track_gtr300x_adc.clear();
      out_track_gtr300y_t.clear();
      out_track_gtr300y_adc.clear();
      out_track_w_trg_bias.clear();
      out_track_hbd_mid.clear();
      out_track_hbd_lx.clear();
      out_track_hbd_ly.clear();
      out_track_hbd_nearx.clear();
      out_track_hbd_neary.clear();
      out_track_hbd_multiplicity.clear();
      out_track_hbd_dum_nearx.clear();
      out_track_hbd_dum_neary.clear();
      out_track_hbd_dum_multiplicity.clear();
      out_track_lg_mid.clear();
      out_track_lg_lx.clear();
      out_track_lg_ly.clear();
      out_track_lg_blockch.clear();
      out_track_lg_nearx.clear();
      out_track_lg_neary.clear();
      out_track_lg_multiplicity.clear();
      out_track_lg_dum_nearx.clear();
      out_track_lg_dum_neary.clear();
      out_track_lg_dum_multiplicity.clear();
      out_track_lg_cl_nearx.clear();
      out_track_lg_cl_neary.clear();
      out_track_lg_cl_multiplicity.clear();
      out_track_lg_cl_dum_nearx.clear();
      out_track_lg_cl_dum_neary.clear();
      out_track_lg_cl_dum_multiplicity.clear();
      out_track_hbd_allhit_resx.clear();
      out_track_hbd_allhit_resy.clear();
      out_track_hbd_allhit_ftime.clear();
      out_track_hbd_allhit_adc.clear();
      out_track_hbd_allhit_size.clear();
      out_track_hbd_allhit_eprob.clear();
      out_track_hbd_allhit_cprob.clear();
      out_track_hbd_allhit_dum_resx.clear();
      out_track_hbd_allhit_dum_resy.clear();
      out_track_hbd_allhit_dum_ftime.clear();
      out_track_hbd_allhit_dum_adc.clear();
      out_track_hbd_allhit_dum_size.clear();
      out_track_hbd_allhit_dum_eprob.clear();
      out_track_hbd_allhit_dum_cprob.clear();
      out_track_lg_allhit_resx.clear();
      out_track_lg_allhit_resy.clear();
      out_track_lg_allhit_ftime.clear();
      out_track_lg_allhit_adc.clear();
      out_track_lg_allhit_trgt.clear();
      out_track_lg_allhit_dum_resx.clear();
      out_track_lg_allhit_dum_resy.clear();
      out_track_lg_allhit_dum_ftime.clear();
      out_track_lg_allhit_dum_adc.clear();
      out_track_lg_cl_allhit_resx.clear();
      out_track_lg_cl_allhit_resy.clear();
      out_track_lg_cl_allhit_ftime.clear();
      out_track_lg_cl_allhit_adc.clear();
      out_track_lg_cl_allhit_maxpeak.clear();
      out_track_lg_cl_allhit_maxcid.clear();
      out_track_lg_cl_allhit_dum_resx.clear();
      out_track_lg_cl_allhit_dum_resy.clear();
      out_track_lg_cl_allhit_dum_ftime.clear();
      out_track_lg_cl_allhit_dum_adc.clear();
      out_track_lg_cl_allhit_dum_maxpeak.clear();
      out_track_lg_cl_allhit_dum_maxcid.clear();

      //LG clustering
      E16ANA_LGClustering clustering;
      for (int idst1hit = 0; idst1hit < n_lg_hits; idst1hit++) {
	if(lg_hit_fflag->at(idst1hit)<2){
	  clustering.SetHitData(
	    idst1hit,
	    lg_hit_mid->at(idst1hit),
	    LocaltoCh(lg_hit_x->at(idst1hit),lg_hit_y->at(idst1hit)),
	    lg_hit_adc->at(idst1hit),
	    lg_hit_t->at(idst1hit),
	    lg_hit_adc->at(idst1hit),
	    lg_hit_x->at(idst1hit),
	    lg_hit_y->at(idst1hit),
	    0.);
	}
      }
      // clustering.Clustering();
      clustering.ClusteringXY();//220303
      int n_lg_clusters = clustering.LGClusterSize();
      std::vector<int> lg_cluster_mid(n_lg_clusters);
      std::vector<double> lg_cluster_x(n_lg_clusters);
      std::vector<double> lg_cluster_y(n_lg_clusters);
      std::vector<float> lg_cluster_adc(n_lg_clusters);
      std::vector<float> lg_cluster_t(n_lg_clusters);
      std::vector<float> lg_cluster_maxpeak(n_lg_clusters);
      std::vector<int> lg_cluster_maxcid(n_lg_clusters);
      for(int icluster=0;icluster<n_lg_clusters;icluster++){
	E16ANA_LGClustering::lgcluster cith = clustering.LGClusterIth(icluster);
	lg_cluster_mid.at(icluster) = cith.mid;
	lg_cluster_x.at(icluster) = cith.lx;
	lg_cluster_y.at(icluster) = cith.ly;
	lg_cluster_adc.at(icluster) = cith.peaksum;
	lg_cluster_t.at(icluster) = cith.fasttiming;
	lg_cluster_maxpeak.at(icluster) = cith.maxpeak;
	lg_cluster_maxcid.at(icluster) = cith.maxcid;
      }

      int ntrkacc = 0;
      int ntracks = track_id->size();
      double chisq_plus_min = 10000;
      double chisq_minus_min = 10000;
      int plus_index = -10000;
      int minus_index = -10000;
      for(int itrack=0;itrack<ntracks;itrack++){//track loop
	// if ( runoption==1 && n_gtr100x_clusters>100 ) continue;//220224
	double trk_mom = -10000;
	double trk_momx = -10000;
	double trk_momy = -10000;
	double trk_momz = -10000;
	double trk_hbd_lx = -10000;
	double trk_hbd_ly = -10000;
	if (chi_square->at(itrack)>max_chi_square) continue;
      	int trk_hbd_mid = CutOfTrackForResidualHBD(ientry,itrack,trk_hbd_lx,trk_hbd_ly,trk_mom,trk_momx,trk_momy,trk_momz);
      	if (trk_hbd_mid < 0) continue;
      	double cog[2] = {trk_hbd_lx,trk_hbd_ly};
      	int hbd_padid = E16ANA_HBDGeometry::GetPadIDWLocalCoordinate(trk_hbd_mid,cog);
      	if( hbddch.Status(trk_hbd_mid,hbd_padid) != 0 ) continue;
	double trk_lg_lx = -10000;
	double trk_lg_ly = -10000;
	int ytype = -10000;
      	int trk_lg_mid = CutOfTrackForResidualLG(ientry,itrack,trk_lg_lx,trk_lg_ly,ytype);
      	if (trk_lg_mid < 0) continue;
	if (hbd_track_module!=-1&&trk_hbd_mid!=hbd_track_module) continue;
	if (track_charge!=0&&rk_charge->at(itrack)==-track_charge) continue;
	double trk_momxz = sqrt(trk_momx*trk_momx+trk_momz*trk_momz);//220213
	int hbdise = 2;
	int lgise = 0;
	// if ( runoption==0 && trk_momxz<1.0 ) continue;//220213
	if ( runoption==0 && (rk_hit_ssd_t->at(itrack)<40||rk_hit_ssd_t->at(itrack)>55) ) continue;//220213
	// if ( runoption==3 && trk_momxz<1.0 ) continue;//220213;
	// if ( runoption==3 && (rk_hit_ssd_t->at(itrack)<41||rk_hit_ssd_t->at(itrack)>56) ) continue;//220213
	// if ( runoption==3 && CutOfTrackByMorino(ientry,itrack) < 0) continue;//220208
	if ( runoption==1 && (rk_hit_ssd_t->at(itrack)<38||rk_hit_ssd_t->at(itrack)>54) ) continue;//220213
	if ( runoption==1 && CutOfTrackByMorino(ientry,itrack) < 0) continue;//220208
	double track_angle_lx = -10000.;
	double track_angle_ly = -10000.;
	double track_position_block_lx = -10000;
	double track_position_block_ly = -10000;
	int ret = CalcAngleOnLGPlane(ientry,itrack,geometry,&pair_fitter,trk_hbd_mid,trk_lg_mid,ytype,track_angle_lx,track_angle_ly,track_position_block_lx,track_position_block_ly);
	// if ( runoption==0 && fabs(track_angle_lx)>0.2 ) continue;//220224
	// if ( runoption==1 && fabs(track_angle_lx)>0.2 ) continue;//220224
	int lgmulti=0;
	for(int ilgmulti=0;ilgmulti<n_lg_hits;ilgmulti++){
	  if(lg_hit_mid->at(ilgmulti)==trk_lg_mid&&lg_hit_fflag->at(ilgmulti)!=2){lgmulti++;}
	}
	// if ( runoption==3 && lgmulti>5 ) continue;//220310
	// if ( runoption==0 && lgmulti>4 ) continue;//220310
	int hbdmulti=0;
	for(int ihbdmulti=0;ihbdmulti<n_hbd_clusters;ihbdmulti++){
	  if(hbd_cluster_mid->at(ihbdmulti)==trk_hbd_mid){hbdmulti++;}
	}
	// if ( runoption==3 && hbdmulti>8 ) continue;//220310
	double tgtth = 5.;
	int tgtid = -10000;
	double tgtdist = -10000.;
	if(runoption==0){
	  tgtdist = CutOfTrackTGT(ientry,itrack,tgtth);// for the production in 220418(etc)
	}
	else{
	  tgtdist = CutOfTrackTGT(ientry,itrack,tgtid);//220725 for the production in 220707
	}
	if( tgtdist<0 || tgtdist>100 ) continue;//220725 for the production in 220707

	out_track_id.push_back(track_id->at(itrack));
	out_chi_square.push_back(chi_square->at(itrack));
	out_rk_charge.push_back(rk_charge->at(itrack));
	out_is_selected.push_back(0);
	out_track_mom.push_back(trk_mom);
	out_track_mom_x.push_back(trk_momx);
	out_track_mom_y.push_back(trk_momy);
	out_track_mom_z.push_back(trk_momz);
	out_track_tgt_dist.push_back(tgtdist);
	out_track_tgt_id.push_back(tgtid);
	out_track_lg_pi_eff1.push_back(MomtoLGPieff1(trk_mom));
	out_track_lg_pi_eff2.push_back(MomtoLGPieff2(trk_mom));
	out_track_angle_lx.push_back(track_angle_lx);
	out_track_angle_ly.push_back(track_angle_ly);
	out_track_position_block_lx.push_back(track_position_block_lx);
	out_track_position_block_ly.push_back(track_position_block_ly);
	out_track_ssd_t.push_back(rk_hit_ssd_t->at(itrack));
	// out_track_ssd_t.push_back(rk_hit_ssd_t->at(itrack)-trigger_fine_time);
	out_track_ssd_adc.push_back(rk_hit_ssd_adc->at(itrack));
	out_track_gtr100x_t.push_back(rk_hit_gtr100_xt->at(itrack));
	out_track_gtr100x_adc.push_back(rk_hit_gtr100_xadc->at(itrack));
	out_track_gtr100y_t.push_back(rk_hit_gtr100_yt->at(itrack));
	out_track_gtr100y_adc.push_back(rk_hit_gtr100_yadc->at(itrack));
	out_track_gtr200x_t.push_back(rk_hit_gtr200_xt->at(itrack));
	out_track_gtr200x_adc.push_back(rk_hit_gtr200_xadc->at(itrack));
	out_track_gtr200y_t.push_back(rk_hit_gtr200_yt->at(itrack));
	out_track_gtr200y_adc.push_back(rk_hit_gtr200_yadc->at(itrack));
	out_track_gtr300x_t.push_back(rk_hit_gtr300_xt->at(itrack));
	out_track_gtr300x_adc.push_back(rk_hit_gtr300_xadc->at(itrack));
	out_track_gtr300y_t.push_back(rk_hit_gtr300_yt->at(itrack));
	out_track_gtr300y_adc.push_back(rk_hit_gtr300_yadc->at(itrack));
	/////////
        int blockchx = (trk_lg_lx)-(track_position_block_lx);
        int blockchy = (trk_lg_ly/fabs(trk_lg_ly))*(fabs(trk_lg_ly)+track_position_block_ly);
        int blockch = LocaltoCh(blockchx,blockchy);
	double trg_bias = wTrgBias_Single(ientry,itrack,trk_lg_mid,blockch,TrigAWmin,TrigAWmax,TrigTW);
	out_track_w_trg_bias.push_back(trg_bias);
	out_track_lg_blockch.push_back(blockch);
	/////////
	out_track_hbd_mid.push_back(trk_hbd_mid);
	out_track_hbd_lx.push_back(trk_hbd_lx);
	out_track_hbd_ly.push_back(trk_hbd_ly);
	out_track_lg_mid.push_back(trk_lg_mid);
	out_track_lg_lx.push_back(trk_lg_lx);
	out_track_lg_ly.push_back(trk_lg_ly);
      	if(rk_charge->at(itrack)==1){
      	  if(chi_square->at(itrack)<chisq_plus_min){
      	    chisq_plus_min = chi_square->at(itrack);
      	    plus_index = ntrkacc;
      	  }	  
      	}
      	if(rk_charge->at(itrack)==-1){
      	  if(chi_square->at(itrack)<chisq_minus_min){
      	    chisq_minus_min = chi_square->at(itrack);
      	    minus_index = ntrkacc;
      	  }	  
      	}

	//HBD loop
	double resx = 0;
	double resy = 0;
	double resx_min = 10000;
	double resy_min = 10000;
	out_track_hbd_allhit_resx.push_back(vector<double>());
	out_track_hbd_allhit_resy.push_back(vector<double>());
	out_track_hbd_allhit_ftime.push_back(vector<double>());
	out_track_hbd_allhit_adc.push_back(vector<double>());
	out_track_hbd_allhit_size.push_back(vector<double>());
	out_track_hbd_allhit_eprob.push_back(vector<double>());
	out_track_hbd_allhit_cprob.push_back(vector<double>());
	int nhbdc = 0;
	for(int ihbd=0;ihbd<n_hbd_clusters;ihbd++){
	  if ( hbd_cluster_t->at(ihbd)>200 ) continue;
	  if ( runoption==3 && hbdise==1 && hbd_cluster_eprob->at(ihbd)<1 ) continue;//220213;
	  // if ( runoption==3 && hbdise==1 && (hbd_cluster_size->at(ihbd)<2||hbd_cluster_adc->at(ihbd)<7*60) ) continue;//220407;
	  if ( runoption==3 && hbdise==2 && (hbd_cluster_size->at(ihbd)!=1||hbd_cluster_adc->at(ihbd)>3) ) continue;//220213;
	  if ( runoption==3 && hbdise==3 && (hbd_cluster_size->at(ihbd)<2||hbd_cluster_adc->at(ihbd)<10) ) continue;//220307;
	  if ( runoption==3 && hbdise==4 && (hbd_cluster_size->at(ihbd)<1||hbd_cluster_adc->at(ihbd)<4) ) continue;
	  if ( runoption==3 && hbdise==5 && (hbd_cluster_size->at(ihbd)<1||hbd_cluster_adc->at(ihbd)<2) ) continue;//220721;
	  if ( runoption==0 && hbdise==2 && (hbd_cluster_size->at(ihbd)!=1) ) continue;//220213;
	  // if ( hbd_cluster_t->at(ihbd)>80 || hbd_cluster_t->at(ihbd)<20 ) continue;//220212
	  if(  hbd_cluster_mid->at(ihbd) == trk_hbd_mid ){
	    resx = hbd_cluster_x->at(ihbd) - trk_hbd_lx;
	    resy = hbd_cluster_y->at(ihbd) - trk_hbd_ly;
	    out_track_hbd_allhit_resx[ntrkacc].push_back(resx);
	    out_track_hbd_allhit_resy[ntrkacc].push_back(resy);
	    out_track_hbd_allhit_ftime[ntrkacc].push_back(hbd_cluster_ftime->at(ihbd));
	    out_track_hbd_allhit_adc[ntrkacc].push_back(hbd_cluster_adc->at(ihbd));
	    out_track_hbd_allhit_size[ntrkacc].push_back(hbd_cluster_size->at(ihbd));
	    out_track_hbd_allhit_eprob[ntrkacc].push_back(hbd_cluster_eprob->at(ihbd));
	    out_track_hbd_allhit_cprob[ntrkacc].push_back(hbd_cluster_cprob->at(ihbd));
	    if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	      resx_min = resx;
	      resy_min = resy;
	    }
	    nhbdc++;
	  }
	}
	out_track_hbd_nearx.push_back(resx_min);
	out_track_hbd_neary.push_back(resy_min);
	out_track_hbd_multiplicity.push_back(nhbdc);

	out_track_hbd_allhit_dum_resx.push_back(vector<double>());
	out_track_hbd_allhit_dum_resy.push_back(vector<double>());
	out_track_hbd_allhit_dum_ftime.push_back(vector<double>());
	out_track_hbd_allhit_dum_adc.push_back(vector<double>());
	out_track_hbd_allhit_dum_eprob.push_back(vector<double>());
	out_track_hbd_allhit_dum_cprob.push_back(vector<double>());
	out_track_hbd_allhit_dum_size.push_back(vector<double>());
	double resx_dam = 0;
	double resy_dam = 0;
	double resx_dam_min = 10000;
	double resy_dam_min = 10000;
	int nhbdc_dam = 0;
	if( n_hbd_clusters_tmp!=100000 ){//dummy
	  for(int ihbd=0;ihbd<n_hbd_clusters_tmp;ihbd++){
	    if ( hbd_cluster_t_tmp.at(ihbd)>200 ) continue;
	    if ( runoption==3 && hbdise==1 && hbd_cluster_eprob_tmp.at(ihbd)<1 ) continue;//220213
	    // if ( runoption==3 && hbdise==1 && (hbd_cluster_size_tmp.at(ihbd)<2||hbd_cluster_adc_tmp.at(ihbd)<7*60) ) continue;//220407;
	    if ( runoption==3 && hbdise==2 && (hbd_cluster_size_tmp.at(ihbd)!=1||hbd_cluster_adc_tmp.at(ihbd)>3) ) continue;//220213;
	    if ( runoption==3 && hbdise==3 && (hbd_cluster_size_tmp.at(ihbd)<2||hbd_cluster_adc_tmp.at(ihbd)<10) ) continue;//220307
	    if ( runoption==3 && hbdise==4 && (hbd_cluster_size_tmp.at(ihbd)<1||hbd_cluster_adc_tmp.at(ihbd)<4) ) continue;
	    if ( runoption==3 && hbdise==5 && (hbd_cluster_size_tmp.at(ihbd)<1||hbd_cluster_adc_tmp.at(ihbd)<2) ) continue;//220721
	    if ( runoption==0 && hbdise==2 && (hbd_cluster_size_tmp.at(ihbd)!=1) ) continue;
	    //if ( hbd_cluster_t_tmp.at(ihbd)>80 || hbd_cluster_t_tmp.at(ihbd)<20 ) continue;//220212
	    if(  hbd_cluster_mid_tmp.at(ihbd) == trk_hbd_mid ){
	      resx_dam = hbd_cluster_x_tmp.at(ihbd) - trk_hbd_lx;
	      resy_dam = hbd_cluster_y_tmp.at(ihbd) - trk_hbd_ly;
	      out_track_hbd_allhit_dum_resx[ntrkacc].push_back(resx_dam);
	      out_track_hbd_allhit_dum_resy[ntrkacc].push_back(resy_dam);
	      out_track_hbd_allhit_dum_ftime[ntrkacc].push_back(hbd_cluster_ftime_tmp.at(ihbd));
	      out_track_hbd_allhit_dum_adc[ntrkacc].push_back(hbd_cluster_adc_tmp.at(ihbd));
	      out_track_hbd_allhit_dum_size[ntrkacc].push_back(hbd_cluster_size_tmp.at(ihbd));
	      out_track_hbd_allhit_dum_eprob[ntrkacc].push_back(hbd_cluster_eprob_tmp.at(ihbd));
	      out_track_hbd_allhit_dum_cprob[ntrkacc].push_back(hbd_cluster_cprob_tmp.at(ihbd));
	      if( resx_dam*resx_dam+resy_dam*resy_dam < resx_dam_min*resx_dam_min+resy_dam_min*resy_dam_min ){
		resx_dam_min = resx_dam;
		resy_dam_min = resy_dam;
	      }
	      nhbdc_dam++;
	    }	    
	  }
	}//dummy
	out_track_hbd_dum_nearx.push_back(resx_dam_min);
	out_track_hbd_dum_neary.push_back(resy_dam_min);
	out_track_hbd_dum_multiplicity.push_back(nhbdc_dam);


	//LG Hit loop
	resx = 0;
	resy = 0;
	resx_min = 10000;
	resy_min = 10000;
	out_track_lg_allhit_resx.push_back(vector<double>());
	out_track_lg_allhit_resy.push_back(vector<double>());
	out_track_lg_allhit_ftime.push_back(vector<double>());
	out_track_lg_allhit_adc.push_back(vector<double>());
	out_track_lg_allhit_trgt.push_back(vector<double>());
	int nlgh = 0;
	for(int ilg=0;ilg<n_lg_hits;ilg++){
	  if ( runoption==3 && lgise==2 && (lg_hit_adc->at(ilg)<20||lg_hit_adc->at(ilg)>50) ) continue;
	  if(  lg_hit_mid->at(ilg) == trk_lg_mid && lg_hit_fflag->at(ilg)!=2 ){
	    resx = lg_hit_x->at(ilg) - trk_lg_lx;
	    resy = lg_hit_y->at(ilg) - trk_lg_ly;
	    out_track_lg_allhit_resx[ntrkacc].push_back(resx);
	    out_track_lg_allhit_resy[ntrkacc].push_back(resy);
	    out_track_lg_allhit_ftime[ntrkacc].push_back(lg_hit_t->at(ilg));
	    out_track_lg_allhit_adc[ntrkacc].push_back(lg_hit_adc->at(ilg));
	    double trgt_tmp=-10000;
	    for(int itlg=0;itlg<n_trg_tracks;itlg++){
	      if(trg_track_lg_mid->at(itlg)!=lg_hit_mid->at(ilg)||trg_track_lg_cid->at(itlg)!=lg_hit_cid->at(ilg)) continue;
	      if(fabs(trg_track_lg_t->at(itlg))<11){
		trgt_tmp=trg_track_lg_t->at(itlg);
		break;
	      }
	    }
	    out_track_lg_allhit_trgt[ntrkacc].push_back(trgt_tmp);
	    if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	      resx_min = resx;
	      resy_min = resy;
	    }
	    nlgh++;
	  }
	}
	out_track_lg_nearx.push_back(resx_min);
	out_track_lg_neary.push_back(resy_min);
	out_track_lg_multiplicity.push_back(nlgh);

	out_track_lg_allhit_dum_resx.push_back(vector<double>());
	out_track_lg_allhit_dum_resy.push_back(vector<double>());
	out_track_lg_allhit_dum_ftime.push_back(vector<double>());
	out_track_lg_allhit_dum_adc.push_back(vector<double>());
	resx_dam = 0;
	resy_dam = 0;
	resx_dam_min = 10000;
	resy_dam_min = 10000;
	int nlgh_dam = 0;
	if( n_lg_hits_tmp!=100000 ){//dummy
	  for(int ilg=0;ilg<n_lg_hits_tmp;ilg++){
	    if ( runoption==3 && lgise==2 && (lg_hit_adc_tmp.at(ilg)<20||lg_hit_adc_tmp.at(ilg)>50) ) continue;
	    if(  lg_hit_mid_tmp.at(ilg) == trk_lg_mid && lg_hit_fflag_tmp.at(ilg)!=2 ){
	      resx_dam = lg_hit_x_tmp.at(ilg) - trk_lg_lx;
	      resy_dam = lg_hit_y_tmp.at(ilg) - trk_lg_ly;
	      out_track_lg_allhit_dum_resx[ntrkacc].push_back(resx_dam);
	      out_track_lg_allhit_dum_resy[ntrkacc].push_back(resy_dam);
	      out_track_lg_allhit_dum_ftime[ntrkacc].push_back(lg_hit_t_tmp.at(ilg));
	      out_track_lg_allhit_dum_adc[ntrkacc].push_back(lg_hit_adc_tmp.at(ilg));
	      if( resx_dam*resx_dam+resy_dam*resy_dam < resx_dam_min*resx_dam_min+resy_dam_min*resy_dam_min ){
		resx_dam_min = resx_dam;
		resy_dam_min = resy_dam;
	      }
	      nlgh_dam++;
	    }	    
	  }
	}//dummy
	out_track_lg_dum_nearx.push_back(resx_dam_min);
	out_track_lg_dum_neary.push_back(resy_dam_min);
	out_track_lg_dum_multiplicity.push_back(nlgh_dam);


	//LG Cluster loop
	resx = 0;
	resy = 0;
	resx_min = 10000;
	resy_min = 10000;
	out_track_lg_cl_allhit_resx.push_back(vector<double>());
	out_track_lg_cl_allhit_resy.push_back(vector<double>());
	out_track_lg_cl_allhit_ftime.push_back(vector<double>());
	out_track_lg_cl_allhit_adc.push_back(vector<double>());
	out_track_lg_cl_allhit_maxpeak.push_back(vector<double>());
	out_track_lg_cl_allhit_maxcid.push_back(vector<double>());
	int nlgc = 0;
	for(int ilg=0;ilg<n_lg_clusters;ilg++){
	  if(  lg_cluster_mid.at(ilg) == trk_lg_mid ){
	    resx = lg_cluster_x.at(ilg) - trk_lg_lx;
	    resy = lg_cluster_y.at(ilg) - trk_lg_ly;
	    out_track_lg_cl_allhit_resx[ntrkacc].push_back(resx);
	    out_track_lg_cl_allhit_resy[ntrkacc].push_back(resy);
	    out_track_lg_cl_allhit_ftime[ntrkacc].push_back(lg_cluster_t.at(ilg));
	    out_track_lg_cl_allhit_adc[ntrkacc].push_back(lg_cluster_adc.at(ilg));
	    out_track_lg_cl_allhit_maxpeak[ntrkacc].push_back(lg_cluster_maxpeak.at(ilg));
	    out_track_lg_cl_allhit_maxcid[ntrkacc].push_back(lg_cluster_maxcid.at(ilg));
	    if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	      resx_min = resx;
	      resy_min = resy;
	    }
	    nlgc++;
	  }
	}
	out_track_lg_cl_nearx.push_back(resx_min);
	out_track_lg_cl_neary.push_back(resy_min);
	out_track_lg_cl_multiplicity.push_back(nlgc);

	out_track_lg_cl_allhit_dum_resx.push_back(vector<double>());
	out_track_lg_cl_allhit_dum_resy.push_back(vector<double>());
	out_track_lg_cl_allhit_dum_ftime.push_back(vector<double>());
	out_track_lg_cl_allhit_dum_adc.push_back(vector<double>());
	out_track_lg_cl_allhit_dum_maxpeak.push_back(vector<double>());
	out_track_lg_cl_allhit_dum_maxcid.push_back(vector<double>());
	resx_dam = 0;
	resy_dam = 0;
	resx_dam_min = 10000;
	resy_dam_min = 10000;
	int nlgc_dam = 0;
	if( n_lg_clusters_tmp!=100000 ){//dummy
	  for(int ilg=0;ilg<n_lg_clusters_tmp;ilg++){
	    if(  lg_cluster_mid_tmp.at(ilg) == trk_lg_mid ){
	      resx_dam = lg_cluster_x_tmp.at(ilg) - trk_lg_lx;
	      resy_dam = lg_cluster_y_tmp.at(ilg) - trk_lg_ly;
	      out_track_lg_cl_allhit_dum_resx[ntrkacc].push_back(resx_dam);
	      out_track_lg_cl_allhit_dum_resy[ntrkacc].push_back(resy_dam);
	      out_track_lg_cl_allhit_dum_ftime[ntrkacc].push_back(lg_cluster_t_tmp.at(ilg));
	      out_track_lg_cl_allhit_dum_adc[ntrkacc].push_back(lg_cluster_adc_tmp.at(ilg));
	      out_track_lg_cl_allhit_dum_maxpeak[ntrkacc].push_back(lg_cluster_maxpeak_tmp.at(ilg));
	      out_track_lg_cl_allhit_dum_maxcid[ntrkacc].push_back(lg_cluster_maxcid_tmp.at(ilg));
	      if( resx_dam*resx_dam+resy_dam*resy_dam < resx_dam_min*resx_dam_min+resy_dam_min*resy_dam_min ){
		resx_dam_min = resx_dam;
		resy_dam_min = resy_dam;
	      }
	      nlgc_dam++;
	    }	    
	  }
	}//dummy
	out_track_lg_cl_dum_nearx.push_back(resx_dam_min);
	out_track_lg_cl_dum_neary.push_back(resy_dam_min);
	out_track_lg_cl_dum_multiplicity.push_back(nlgc_dam);


	ntrkacc++;

      }//track loop

      if(plus_index!=-10000){out_is_selected.at(plus_index)=1;}
      if(minus_index!=-10000){out_is_selected.at(minus_index)=1;}

      if(ntrkacc!=0){
	n_hbd_clusters_tmp = n_hbd_clusters;
	hbd_cluster_mid_tmp.resize(n_hbd_clusters);
	hbd_cluster_x_tmp.resize(n_hbd_clusters);
	hbd_cluster_y_tmp.resize(n_hbd_clusters);
	hbd_cluster_adc_tmp.resize(n_hbd_clusters);
	hbd_cluster_eprob_tmp.resize(n_hbd_clusters);
	hbd_cluster_cprob_tmp.resize(n_hbd_clusters);
	hbd_cluster_size_tmp.resize(n_hbd_clusters);
	hbd_cluster_t_tmp.resize(n_hbd_clusters);
	hbd_cluster_ftime_tmp.resize(n_hbd_clusters);
	copy( hbd_cluster_mid->begin(), hbd_cluster_mid->end(), hbd_cluster_mid_tmp.begin() );
	copy( hbd_cluster_x->begin(), hbd_cluster_x->end(), hbd_cluster_x_tmp.begin() );
	copy( hbd_cluster_y->begin(), hbd_cluster_y->end(), hbd_cluster_y_tmp.begin() );
	copy( hbd_cluster_adc->begin(), hbd_cluster_adc->end(), hbd_cluster_adc_tmp.begin() );
	copy( hbd_cluster_eprob->begin(), hbd_cluster_eprob->end(), hbd_cluster_eprob_tmp.begin() );
	copy( hbd_cluster_cprob->begin(), hbd_cluster_cprob->end(), hbd_cluster_cprob_tmp.begin() );
	copy( hbd_cluster_size->begin(), hbd_cluster_size->end(), hbd_cluster_size_tmp.begin() );
	copy( hbd_cluster_t->begin(), hbd_cluster_t->end(), hbd_cluster_t_tmp.begin() );
	copy( hbd_cluster_ftime->begin(), hbd_cluster_ftime->end(), hbd_cluster_ftime_tmp.begin() );
	n_lg_hits_tmp = n_lg_hits;
	lg_hit_mid_tmp.resize(n_lg_hits);
	lg_hit_x_tmp.resize(n_lg_hits);
	lg_hit_y_tmp.resize(n_lg_hits);
	lg_hit_adc_tmp.resize(n_lg_hits);
	lg_hit_t_tmp.resize(n_lg_hits);
	lg_hit_fflag_tmp.resize(n_lg_hits);
	copy( lg_hit_mid->begin(), lg_hit_mid->end(), lg_hit_mid_tmp.begin() );
	copy( lg_hit_x->begin(), lg_hit_x->end(), lg_hit_x_tmp.begin() );
	copy( lg_hit_y->begin(), lg_hit_y->end(), lg_hit_y_tmp.begin() );
	copy( lg_hit_adc->begin(), lg_hit_adc->end(), lg_hit_adc_tmp.begin() );
	copy( lg_hit_t->begin(), lg_hit_t->end(), lg_hit_t_tmp.begin() );
	copy( lg_hit_fflag->begin(), lg_hit_fflag->end(), lg_hit_fflag_tmp.begin() );
	n_lg_clusters_tmp = n_lg_clusters;
	lg_cluster_mid_tmp.resize(n_lg_clusters);
	lg_cluster_x_tmp.resize(n_lg_clusters);
	lg_cluster_y_tmp.resize(n_lg_clusters);
	lg_cluster_t_tmp.resize(n_lg_clusters);
	lg_cluster_adc_tmp.resize(n_lg_clusters);
	lg_cluster_maxpeak_tmp.resize(n_lg_clusters);
	lg_cluster_maxcid_tmp.resize(n_lg_clusters);
	for(int i=0;i<n_lg_clusters;i++){
	  lg_cluster_mid_tmp.at(i) = lg_cluster_mid.at(i);
	  lg_cluster_x_tmp.at(i) = lg_cluster_x.at(i);
	  lg_cluster_y_tmp.at(i) = lg_cluster_y.at(i);
	  lg_cluster_t_tmp.at(i) = lg_cluster_t.at(i);
	  lg_cluster_adc_tmp.at(i) = lg_cluster_adc.at(i);
	  lg_cluster_maxpeak_tmp.at(i) = lg_cluster_maxpeak.at(i);
	  lg_cluster_maxcid_tmp.at(i) = lg_cluster_maxcid.at(i);
	}

	//Get Hits & Clusters
	out_n_tracks = ntrkacc;
	out_run_id = run_id;
	out_event_id = event_id;
	out_spill_id = spill_id;
	// out_n_hbd_clusters = n_hbd_clusters;
	// out_n_lg_hits = n_lg_hits;
	// out_hbd_cluster_id.resize(n_hbd_clusters*2);
	// out_hbd_cluster_mid.resize(n_hbd_clusters);
	// out_hbd_cluster_x.resize(n_hbd_clusters);
	// out_hbd_cluster_y.resize(n_hbd_clusters);
	// out_hbd_cluster_gx.resize(n_hbd_clusters);
	// out_hbd_cluster_gy.resize(n_hbd_clusters);
	// out_hbd_cluster_gz.resize(n_hbd_clusters);
	// out_hbd_cluster_adc.resize(n_hbd_clusters);
	// out_hbd_cluster_t.resize(n_hbd_clusters);
	// out_hbd_cluster_ftime.resize(n_hbd_clusters);
	// out_hbd_cluster_tdiff.resize(n_hbd_clusters);
	// out_hbd_cluster_size.resize(n_hbd_clusters);
	// out_hbd_cluster_eprob.resize(n_hbd_clusters);
	// out_hbd_cluster_cprob.resize(n_hbd_clusters);
	// out_lg_hit_id.resize(n_lg_hits);
	// out_lg_hit_mid.resize(n_lg_hits);
	// out_lg_hit_x.resize(n_lg_hits);
	// out_lg_hit_y.resize(n_lg_hits);
	// out_lg_hit_gx.resize(n_lg_hits);
	// out_lg_hit_gy.resize(n_lg_hits);
	// out_lg_hit_gz.resize(n_lg_hits);
	// out_lg_hit_adc.resize(n_lg_hits);
	// out_lg_hit_t.resize(n_lg_hits);
	// out_lg_hit_npeaks.resize(n_lg_hits);
	// out_lg_hit_fflag.resize(n_lg_hits);
	// copy( hbd_cluster_id->begin(), hbd_cluster_id->end(), out_hbd_cluster_id.begin() );
	// copy( hbd_cluster_mid->begin(), hbd_cluster_mid->end(), out_hbd_cluster_mid.begin() );
	// copy( hbd_cluster_x->begin(), hbd_cluster_x->end(), out_hbd_cluster_x.begin() );
	// copy( hbd_cluster_y->begin(), hbd_cluster_y->end(), out_hbd_cluster_y.begin() );
	// copy( hbd_cluster_gx->begin(), hbd_cluster_gx->end(), out_hbd_cluster_gx.begin() );
	// copy( hbd_cluster_gy->begin(), hbd_cluster_gy->end(), out_hbd_cluster_gy.begin() );
	// copy( hbd_cluster_gz->begin(), hbd_cluster_gz->end(), out_hbd_cluster_gz.begin() );
	// copy( hbd_cluster_adc->begin(), hbd_cluster_adc->end(), out_hbd_cluster_adc.begin() );
	// copy( hbd_cluster_t->begin(), hbd_cluster_t->end(), out_hbd_cluster_t.begin() );
	// copy( hbd_cluster_ftime->begin(), hbd_cluster_ftime->end(), out_hbd_cluster_ftime.begin() );
	// copy( hbd_cluster_tdiff->begin(), hbd_cluster_tdiff->end(), out_hbd_cluster_tdiff.begin() );
	// copy( hbd_cluster_size->begin(), hbd_cluster_size->end(), out_hbd_cluster_size.begin() );
	// copy( hbd_cluster_eprob->begin(), hbd_cluster_eprob->end(), out_hbd_cluster_eprob.begin() );
	// copy( hbd_cluster_cprob->begin(), hbd_cluster_cprob->end(), out_hbd_cluster_cprob.begin() );
	// copy( lg_hit_id->begin(), lg_hit_id->end(), out_lg_hit_id.begin() );
	// copy( lg_hit_mid->begin(), lg_hit_mid->end(), out_lg_hit_mid.begin() );
	// copy( lg_hit_x->begin(), lg_hit_x->end(), out_lg_hit_x.begin() );
	// copy( lg_hit_y->begin(), lg_hit_y->end(), out_lg_hit_y.begin() );
	// copy( lg_hit_gx->begin(), lg_hit_gx->end(), out_lg_hit_gx.begin() );
	// copy( lg_hit_gy->begin(), lg_hit_gy->end(), out_lg_hit_gy.begin() );
	// copy( lg_hit_gz->begin(), lg_hit_gz->end(), out_lg_hit_gz.begin() );
	// copy( lg_hit_adc->begin(), lg_hit_adc->end(), out_lg_hit_adc.begin() );
	// copy( lg_hit_t->begin(), lg_hit_t->end(), out_lg_hit_t.begin() );
	// copy( lg_hit_npeaks->begin(), lg_hit_npeaks->end(), out_lg_hit_npeaks.begin() );
	// copy( lg_hit_fflag->begin(), lg_hit_fflag->end(), out_lg_hit_fflag.begin() );

	// wTrgBias_Pair(out_track_w_trg_bias,out_track_lg_mid,out_track_lg_blockch);

	tree->Fill();
      }
      nevent++;
   }//event loop

   fout->Write();
   fout->Close();

}

void SingleTrackAnalyzerForRes::MkTreeWYass(int runoption, int maxevent, char* out_file_name, int hbd_track_module, int track_charge, double max_chi_square)
{
   if (fChain == 0) return;

   int count = 0;
   TFile* fout = new TFile(out_file_name,"recreate");
   TTree* tree = new TTree("tree","tree");

   TH2F* hdead = new TH2F("hdead","hdead",135,-25,110,135,-25,110);
   TH1F* htrglg = new TH1F("htrglg","htrglg",200,0,200);
   TH1F* xzchisq = new TH1F("xzchisq","xzchisq",100,0,100);
   double originx[5] = {0.,5.,0.,-10.,0.};
   if(runoption==0){originx[1]=0.;originx[3]=0.;}
   TH1F* htrkmom = new TH1F("htrkmom","htrkmom",100,0,10);
   TH1F* htrkacc = new TH1F("htrkacc","htrkacc",3,0,3);
   TH1F* htrkacc2 = new TH1F("htrkacc2","htrkacc2",3,0,3);
   TH2F* gtr2d = new TH2F("gtr2d","gtr2d",4000,-2000,2000,400,-200,200);
   TH1F* hhbdxres[5];
   TH1F* gtr1yres[9];
   TH1F* gtr2yres[9];
   TH1F* gtr3yres[9];
   TH1F* gtr1ytim[9];
   TH1F* gtr2ytim[9];
   TH1F* gtr3ytim[9];
   for(int i=0;i<5;i++){
     hhbdxres[i] = new TH1F(Form("hhbdxres%d",i+103),Form("hhbdxres%d",i+103),200,-800,800);
   }
   for(int i=0;i<9;i++){
     gtr1yres[i] = new TH1F(Form("gtr1yres%d",i+101),Form("gtr1yres%d",i+101),200,-100,100);
     gtr2yres[i] = new TH1F(Form("gtr2yres%d",i+101),Form("gtr2yres%d",i+101),200,-200,200);
     gtr3yres[i] = new TH1F(Form("gtr3yres%d",i+101),Form("gtr3yres%d",i+101),200,-300,300);
     gtr1ytim[i] = new TH1F(Form("gtr1ytim%d",i+101),Form("gtr1ytim%d",i+101),200,-100,100);
     gtr2ytim[i] = new TH1F(Form("gtr2ytim%d",i+101),Form("gtr2ytim%d",i+101),200,-200,200);
     gtr3ytim[i] = new TH1F(Form("gtr3ytim%d",i+101),Form("gtr3ytim%d",i+101),200,-300,300);
   }
   TH1F* ychisq = new TH1F("ychisq","ychisq",10000,0,10000);


   Int_t           out_run_id;
   Int_t           out_event_id;
   Int_t           out_spill_id;
   Int_t out_n_tracks;
   vector<int> out_track_id;
   vector<double> out_chi_square;
   vector<int> out_rk_charge;
   vector<int> out_is_selected;
   vector<double> out_track_mom;
   vector<double> out_track_mom_x;
   vector<double> out_track_mom_y;
   vector<double> out_track_mom_z;
   vector<double> out_track_tgt_dist;
   vector<double> out_track_lg_pi_eff1;
   vector<double> out_track_lg_pi_eff2;
   vector<double> out_track_angle_lx;
   vector<double> out_track_angle_ly;
   vector<double> out_track_position_block_lx;
   vector<double> out_track_position_block_ly;
   vector<double> out_track_ssd_t;
   vector<double> out_track_ssd_adc;
   vector<double> out_track_gtr100x_t;
   vector<double> out_track_gtr100x_adc;
   vector<double> out_track_gtr100y_t;
   vector<double> out_track_gtr100y_adc;
   vector<double> out_track_gtr200x_t;
   vector<double> out_track_gtr200x_adc;
   vector<double> out_track_gtr200y_t;
   vector<double> out_track_gtr200y_adc;
   vector<double> out_track_gtr300x_t;
   vector<double> out_track_gtr300x_adc;
   vector<double> out_track_gtr300y_t;
   vector<double> out_track_gtr300y_adc;
   vector<double> out_track_w_trg_bias;
   vector<double> out_track_select_hbd_resx;//
   vector<double> out_track_select_hbd_adc;//
   vector<int> out_track_select_gtr_nass;//
   vector<double> out_track_select_gtr100y_res;//
   vector<double> out_track_select_gtr200y_res;//
   vector<double> out_track_select_gtr300y_res;//
   vector<double> out_track_select_gtr_chisq;//
   vector<int> out_track_hbd_mid;
   vector<double> out_track_hbd_lx;
   vector<double> out_track_hbd_ly;
   vector<double> out_track_hbd_nearx;
   vector<double> out_track_hbd_neary;
   vector<int> out_track_hbd_multiplicity;
   vector<double> out_track_hbd_dum_nearx;
   vector<double> out_track_hbd_dum_neary;
   vector<int> out_track_hbd_dum_multiplicity;
   vector<int> out_track_lg_mid;
   vector<double> out_track_lg_lx;
   vector<double> out_track_lg_ly;
   vector<double> out_track_lg_nearx;
   vector<double> out_track_lg_neary;
   vector<int> out_track_lg_multiplicity;
   vector<double> out_track_lg_dum_nearx;
   vector<double> out_track_lg_dum_neary;
   vector<int> out_track_lg_dum_multiplicity;
   vector<double> out_track_lg_cl_nearx;
   vector<double> out_track_lg_cl_neary;
   vector<int> out_track_lg_cl_multiplicity;
   vector<double> out_track_lg_cl_dum_nearx;
   vector<double> out_track_lg_cl_dum_neary;
   vector<int> out_track_lg_cl_dum_multiplicity;
   vector<vector<double>> out_track_hbd_allhit_resx;
   vector<vector<double>> out_track_hbd_allhit_resy;
   vector<vector<double>> out_track_hbd_allhit_ftime;
   vector<vector<double>> out_track_hbd_allhit_adc;
   vector<vector<double>> out_track_hbd_allhit_size;
   vector<vector<double>> out_track_hbd_allhit_eprob;
   vector<vector<double>> out_track_hbd_allhit_cprob;
   vector<vector<double>> out_track_hbd_allhit_dum_resx;
   vector<vector<double>> out_track_hbd_allhit_dum_resy;
   vector<vector<double>> out_track_hbd_allhit_dum_ftime;
   vector<vector<double>> out_track_hbd_allhit_dum_adc;
   vector<vector<double>> out_track_hbd_allhit_dum_size;
   vector<vector<double>> out_track_hbd_allhit_dum_eprob;
   vector<vector<double>> out_track_hbd_allhit_dum_cprob;
   vector<vector<double>> out_track_lg_allhit_resx;
   vector<vector<double>> out_track_lg_allhit_resy;
   vector<vector<double>> out_track_lg_allhit_ftime;
   vector<vector<double>> out_track_lg_allhit_adc;
   vector<vector<double>> out_track_lg_allhit_trgt;
   vector<vector<double>> out_track_lg_allhit_dum_resx;
   vector<vector<double>> out_track_lg_allhit_dum_resy;
   vector<vector<double>> out_track_lg_allhit_dum_ftime;
   vector<vector<double>> out_track_lg_allhit_dum_adc;
   vector<vector<double>> out_track_lg_cl_allhit_resx;
   vector<vector<double>> out_track_lg_cl_allhit_resy;
   vector<vector<double>> out_track_lg_cl_allhit_ftime;
   vector<vector<double>> out_track_lg_cl_allhit_adc;
   vector<vector<double>> out_track_lg_cl_allhit_maxpeak;
   vector<vector<double>> out_track_lg_cl_allhit_maxcid;
   vector<vector<double>> out_track_lg_cl_allhit_dum_resx;
   vector<vector<double>> out_track_lg_cl_allhit_dum_resy;
   vector<vector<double>> out_track_lg_cl_allhit_dum_ftime;
   vector<vector<double>> out_track_lg_cl_allhit_dum_adc;
   vector<vector<double>> out_track_lg_cl_allhit_dum_maxpeak;
   vector<vector<double>> out_track_lg_cl_allhit_dum_maxcid;

   tree->Branch("run_id",&out_run_id,"run_id/I");
   tree->Branch("event_id",&out_event_id,"event_id/I");
   tree->Branch("spill_id",&out_run_id,"spill_id/I");
   tree->Branch("n_tracks",&out_n_tracks,"n_tracks/I");
   tree->Branch("track_id", &out_track_id);
   tree->Branch("chi_square", &out_chi_square);
   tree->Branch("rk_charge", &out_rk_charge);
   tree->Branch("is_selected", &out_is_selected);
   tree->Branch("track_mom", &out_track_mom);
   tree->Branch("track_mom_x", &out_track_mom_x);
   tree->Branch("track_mom_y", &out_track_mom_y);
   tree->Branch("track_mom_z", &out_track_mom_z);
   tree->Branch("track_tgt_dist", &out_track_tgt_dist);
   tree->Branch("track_lg_pi_eff1", &out_track_lg_pi_eff1);
   tree->Branch("track_lg_pi_eff2", &out_track_lg_pi_eff2);
   tree->Branch("track_angle_lx", &out_track_angle_lx);
   tree->Branch("track_angle_ly", &out_track_angle_ly);
   tree->Branch("track_position_block_lx", &out_track_position_block_lx);
   tree->Branch("track_position_block_ly", &out_track_position_block_ly);
   tree->Branch("track_ssd_t", &out_track_ssd_t);
   tree->Branch("track_ssd_adc", &out_track_ssd_adc);
   tree->Branch("track_gtr100x_t", &out_track_gtr100x_t);
   tree->Branch("track_gtr100x_adc", &out_track_gtr100x_adc);
   tree->Branch("track_gtr100y_t", &out_track_gtr100y_t);
   tree->Branch("track_gtr100y_adc", &out_track_gtr100y_adc);
   tree->Branch("track_gtr200x_t", &out_track_gtr200x_t);
   tree->Branch("track_gtr200x_adc", &out_track_gtr200x_adc);
   tree->Branch("track_gtr200y_t", &out_track_gtr200y_t);
   tree->Branch("track_gtr200y_adc", &out_track_gtr200y_adc);
   tree->Branch("track_gtr300x_t", &out_track_gtr300x_t);
   tree->Branch("track_gtr300x_adc", &out_track_gtr300x_adc);
   tree->Branch("track_gtr300y_t", &out_track_gtr300y_t);
   tree->Branch("track_gtr300y_adc", &out_track_gtr300y_adc);
   tree->Branch("track_w_trg_bias", &out_track_w_trg_bias);
   tree->Branch("track_select_hbd_resx", &out_track_select_hbd_resx);//
   tree->Branch("track_select_hbd_adc", &out_track_select_hbd_adc);//
   tree->Branch("track_select_gtr_nass", &out_track_select_gtr_nass);//
   tree->Branch("track_select_gtr100y_res", &out_track_select_gtr100y_res);//
   tree->Branch("track_select_gtr200y_res", &out_track_select_gtr200y_res);//
   tree->Branch("track_select_gtr300y_res", &out_track_select_gtr300y_res);//
   tree->Branch("track_select_gtr_chisq", &out_track_select_gtr_chisq);//
   tree->Branch("track_hbd_mid", &out_track_hbd_mid);
   tree->Branch("track_hbd_lx", &out_track_hbd_lx);
   tree->Branch("track_hbd_ly", &out_track_hbd_ly);
   tree->Branch("track_hbd_nearx", &out_track_hbd_nearx);
   tree->Branch("track_hbd_neary", &out_track_hbd_neary);
   tree->Branch("track_hbd_multiplicity", &out_track_hbd_multiplicity);
   tree->Branch("track_hbd_dum_nearx", &out_track_hbd_dum_nearx);
   tree->Branch("track_hbd_dum_neary", &out_track_hbd_dum_neary);
   tree->Branch("track_hbd_dum_multiplicity", &out_track_hbd_dum_multiplicity);
   tree->Branch("track_lg_mid", &out_track_lg_mid);
   tree->Branch("track_lg_lx", &out_track_lg_lx);
   tree->Branch("track_lg_ly", &out_track_lg_ly);
   tree->Branch("track_lg_nearx", &out_track_lg_nearx);
   tree->Branch("track_lg_neary", &out_track_lg_neary);
   tree->Branch("track_lg_multiplicity", &out_track_lg_multiplicity);
   tree->Branch("track_lg_dum_nearx", &out_track_lg_dum_nearx);
   tree->Branch("track_lg_dum_neary", &out_track_lg_dum_neary);
   tree->Branch("track_lg_dum_multiplicity", &out_track_lg_dum_multiplicity);
   tree->Branch("track_lg_cl_nearx", &out_track_lg_cl_nearx);
   tree->Branch("track_lg_cl_neary", &out_track_lg_cl_neary);
   tree->Branch("track_lg_cl_multiplicity", &out_track_lg_cl_multiplicity);
   tree->Branch("track_lg_cl_dum_nearx", &out_track_lg_cl_dum_nearx);
   tree->Branch("track_lg_cl_dum_neary", &out_track_lg_cl_dum_neary);
   tree->Branch("track_lg_cl_dum_multiplicity", &out_track_lg_cl_dum_multiplicity);
   tree->Branch("track_hbd_allhit_resx", &out_track_hbd_allhit_resx);
   tree->Branch("track_hbd_allhit_resy", &out_track_hbd_allhit_resy);
   tree->Branch("track_hbd_allhit_ftime", &out_track_hbd_allhit_ftime);
   tree->Branch("track_hbd_allhit_adc", &out_track_hbd_allhit_adc);
   tree->Branch("track_hbd_allhit_size", &out_track_hbd_allhit_size);
   tree->Branch("track_hbd_allhit_eprob", &out_track_hbd_allhit_eprob);
   tree->Branch("track_hbd_allhit_cprob", &out_track_hbd_allhit_cprob);
   tree->Branch("track_hbd_allhit_dum_resx", &out_track_hbd_allhit_dum_resx);
   tree->Branch("track_hbd_allhit_dum_resy", &out_track_hbd_allhit_dum_resy);
   tree->Branch("track_hbd_allhit_dum_ftime", &out_track_hbd_allhit_dum_ftime);
   tree->Branch("track_hbd_allhit_dum_adc", &out_track_hbd_allhit_dum_adc);
   tree->Branch("track_hbd_allhit_dum_size", &out_track_hbd_allhit_dum_size);
   tree->Branch("track_hbd_allhit_dum_eprob", &out_track_hbd_allhit_dum_eprob);
   tree->Branch("track_hbd_allhit_dum_cprob", &out_track_hbd_allhit_dum_cprob);
   tree->Branch("track_lg_allhit_resx", &out_track_lg_allhit_resx);
   tree->Branch("track_lg_allhit_resy", &out_track_lg_allhit_resy);
   tree->Branch("track_lg_allhit_ftime", &out_track_lg_allhit_ftime);
   tree->Branch("track_lg_allhit_adc", &out_track_lg_allhit_adc);
   tree->Branch("track_lg_allhit_trgt", &out_track_lg_allhit_trgt);
   tree->Branch("track_lg_allhit_dum_resx", &out_track_lg_allhit_dum_resx);
   tree->Branch("track_lg_allhit_dum_resy", &out_track_lg_allhit_dum_resy);
   tree->Branch("track_lg_allhit_dum_ftime", &out_track_lg_allhit_dum_ftime);
   tree->Branch("track_lg_allhit_dum_adc", &out_track_lg_allhit_dum_adc);
   tree->Branch("track_lg_cl_allhit_resx", &out_track_lg_cl_allhit_resx);
   tree->Branch("track_lg_cl_allhit_resy", &out_track_lg_cl_allhit_resy);
   tree->Branch("track_lg_cl_allhit_ftime", &out_track_lg_cl_allhit_ftime);
   tree->Branch("track_lg_cl_allhit_adc", &out_track_lg_cl_allhit_adc);
   tree->Branch("track_lg_cl_allhit_maxpeak", &out_track_lg_cl_allhit_maxpeak);
   tree->Branch("track_lg_cl_allhit_maxcid", &out_track_lg_cl_allhit_maxcid);
   tree->Branch("track_lg_cl_allhit_dum_resx", &out_track_lg_cl_allhit_dum_resx);
   tree->Branch("track_lg_cl_allhit_dum_resy", &out_track_lg_cl_allhit_dum_resy);
   tree->Branch("track_lg_cl_allhit_dum_ftime", &out_track_lg_cl_allhit_dum_ftime);
   tree->Branch("track_lg_cl_allhit_dum_adc", &out_track_lg_cl_allhit_dum_adc);
   tree->Branch("track_lg_cl_allhit_dum_maxpeak", &out_track_lg_cl_allhit_dum_maxpeak);
   tree->Branch("track_lg_cl_allhit_dum_maxcid", &out_track_lg_cl_allhit_dum_maxcid);

   E16ANA_HBDDeadChannel hbddch;
   std::string hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0c-220114.dat";
   // if(runoption==0){
   //   hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0b-220114.dat";
   // }
   hbddch.ReadFile(hbd_deadch_file.c_str());

   auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
   E16ANA_GeometryV2::SetGlobalPointer(geometry);
   auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
   bfield_map->Initialize_binary();
   E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
   E16ANA_MultiTrack pair_fitter(bfield_map, geometry, 2);

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

      out_track_id.clear();
      out_chi_square.clear();
      out_rk_charge.clear();
      out_is_selected.clear();
      out_track_mom.clear();
      out_track_mom_x.clear();
      out_track_mom_y.clear();
      out_track_mom_z.clear();
      out_track_tgt_dist.clear();
      out_track_lg_pi_eff1.clear();
      out_track_lg_pi_eff2.clear();
      out_track_angle_lx.clear();
      out_track_angle_ly.clear();
      out_track_position_block_lx.clear();
      out_track_position_block_ly.clear();
      out_track_ssd_t.clear();
      out_track_ssd_adc.clear();
      out_track_gtr100x_t.clear();
      out_track_gtr100x_adc.clear();
      out_track_gtr100y_t.clear();
      out_track_gtr100y_adc.clear();
      out_track_gtr200x_t.clear();
      out_track_gtr200x_adc.clear();
      out_track_gtr200y_t.clear();
      out_track_gtr200y_adc.clear();
      out_track_gtr300x_t.clear();
      out_track_gtr300x_adc.clear();
      out_track_gtr300y_t.clear();
      out_track_gtr300y_adc.clear();
      out_track_w_trg_bias.clear();
      out_track_select_hbd_resx.clear();//
      out_track_select_hbd_adc.clear();//
      out_track_select_gtr_nass.clear();//
      out_track_select_gtr100y_res.clear();//
      out_track_select_gtr200y_res.clear();//
      out_track_select_gtr300y_res.clear();//
      out_track_select_gtr_chisq.clear();//
      out_track_hbd_mid.clear();
      out_track_hbd_lx.clear();
      out_track_hbd_ly.clear();
      out_track_hbd_nearx.clear();
      out_track_hbd_neary.clear();
      out_track_hbd_multiplicity.clear();
      out_track_hbd_dum_nearx.clear();
      out_track_hbd_dum_neary.clear();
      out_track_hbd_dum_multiplicity.clear();
      out_track_lg_mid.clear();
      out_track_lg_lx.clear();
      out_track_lg_ly.clear();
      out_track_lg_nearx.clear();
      out_track_lg_neary.clear();
      out_track_lg_multiplicity.clear();
      out_track_lg_dum_nearx.clear();
      out_track_lg_dum_neary.clear();
      out_track_lg_dum_multiplicity.clear();
      out_track_lg_cl_nearx.clear();
      out_track_lg_cl_neary.clear();
      out_track_lg_cl_multiplicity.clear();
      out_track_lg_cl_dum_nearx.clear();
      out_track_lg_cl_dum_neary.clear();
      out_track_lg_cl_dum_multiplicity.clear();
      out_track_hbd_allhit_resx.clear();
      out_track_hbd_allhit_resy.clear();
      out_track_hbd_allhit_ftime.clear();
      out_track_hbd_allhit_adc.clear();
      out_track_hbd_allhit_size.clear();
      out_track_hbd_allhit_eprob.clear();
      out_track_hbd_allhit_cprob.clear();
      out_track_hbd_allhit_dum_resx.clear();
      out_track_hbd_allhit_dum_resy.clear();
      out_track_hbd_allhit_dum_ftime.clear();
      out_track_hbd_allhit_dum_adc.clear();
      out_track_hbd_allhit_dum_size.clear();
      out_track_hbd_allhit_dum_eprob.clear();
      out_track_hbd_allhit_dum_cprob.clear();
      out_track_lg_allhit_resx.clear();
      out_track_lg_allhit_resy.clear();
      out_track_lg_allhit_ftime.clear();
      out_track_lg_allhit_adc.clear();
      out_track_lg_allhit_trgt.clear();
      out_track_lg_allhit_dum_resx.clear();
      out_track_lg_allhit_dum_resy.clear();
      out_track_lg_allhit_dum_ftime.clear();
      out_track_lg_allhit_dum_adc.clear();
      out_track_lg_cl_allhit_resx.clear();
      out_track_lg_cl_allhit_resy.clear();
      out_track_lg_cl_allhit_ftime.clear();
      out_track_lg_cl_allhit_adc.clear();
      out_track_lg_cl_allhit_maxpeak.clear();
      out_track_lg_cl_allhit_maxcid.clear();
      out_track_lg_cl_allhit_dum_resx.clear();
      out_track_lg_cl_allhit_dum_resy.clear();
      out_track_lg_cl_allhit_dum_ftime.clear();
      out_track_lg_cl_allhit_dum_adc.clear();
      out_track_lg_cl_allhit_dum_maxpeak.clear();
      out_track_lg_cl_allhit_dum_maxcid.clear();

      int ntrkacc = 0;
      int ntracks = track_id->size();
      double chisq_plus_min = 10000;
      double chisq_minus_min = 10000;
      int plus_index = -10000;
      int minus_index = -10000;

      for(int itrack=0;itrack<ntracks;itrack++){//track loop
	int hbdise = 0;// e or pi
	int lgise = 0;// e or pi
	double hbdtimthr = 200.;
	double hbdposthr = 35.;
	double gtrposthr[3] = {11.,12.,15.};
	double gtrtimthr[3] = {75.,95.,100.};
	int hbdmatch = 0;
	int gtrymatch = 0;
	int ntrglg = 0;
	for(int itrg=0;itrg<n_trg_lg_hits;itrg++){
	  if(fabs(trg_lg_hit_t->at(itrg))>10&&fabs(trg_lg_hit_t->at(itrg))<150){ntrglg++;}
	}
	if(itrack==0){htrglg->Fill(ntrglg);}
	if ( ntrglg>20 ) continue;
	if (chi_square->at(itrack)>max_chi_square) continue;
	xzchisq->Fill(chi_square->at(itrack));
	if (hbd_track_module!=-1&&rk_fit_gtr300_mid->at(itrack)!=hbd_track_module) continue;
	if (track_charge!=0&&rk_charge->at(itrack)==-track_charge) continue;
	double tgtdist = CutOfTrackTGT(ientry,itrack,5);
	// if( tgtdist<0 ) continue;
	double trk_momx = rk_fit_init_mom_gx->at(itrack);
	double trk_momz = rk_fit_init_mom_gz->at(itrack);
	double trk_mom = sqrt(trk_momx*trk_momx+trk_momz*trk_momz);
	if (trk_mom<0.4||trk_mom>2.4) continue;
	htrkmom->Fill(trk_mom);

	//matching with HBD hit
	int trk_gtr_mid = rk_fit_gtr300_mid->at(itrack);
	double dgx[3] = {rk_fit_gtr100_gx->at(itrack),rk_fit_gtr200_gx->at(itrack),rk_fit_gtr300_gx->at(itrack)};
	double dgz[3] = {rk_fit_gtr100_gz->at(itrack)-rk_fit_init_pos_gz->at(itrack),rk_fit_gtr200_gz->at(itrack)-rk_fit_init_pos_gz->at(itrack),rk_fit_gtr300_gz->at(itrack)-rk_fit_init_pos_gz->at(itrack)};

	for(int ihbd=0;ihbd<n_hbd_clusters;ihbd++){//hbdcluster loop
	  // if ( fabs(hbd_cluster_mid->at(ihbd) - trk_gtr_mid)>0 ) continue;
	  if ( fabs(hbd_cluster_mid->at(ihbd) - trk_gtr_mid)>1 ) continue;
	  if ( hbd_cluster_t->at(ihbd)>hbdtimthr ) continue;
	  if ( runoption==3 && hbdise==1 && hbd_cluster_eprob->at(ihbd)<1 ) continue;//220213;
	  // if(runoption==3&&hbdise==1&&(hbd_cluster_size->at(ihbd)<2||hbd_cluster_adc->at(ihbd)<7*60)) continue;//220407;
	  if ( runoption==3 && hbdise==2 && (hbd_cluster_size->at(ihbd)!=1||hbd_cluster_adc->at(ihbd)>3) ) continue;//220213;
	  if ( runoption==3 && hbdise==3 && (hbd_cluster_size->at(ihbd)<2||hbd_cluster_adc->at(ihbd)<10) ) continue;//220307;
	  if ( runoption==3 && hbdise==4 && (hbd_cluster_size->at(ihbd)<2||hbd_cluster_adc->at(ihbd)<4) ) continue;//220213;
	  if ( runoption==0 && hbdise==2 && (hbd_cluster_size->at(ihbd)!=1) ) continue;//220213;
	  // double hbdxres = hbd_cluster_x->at(ihbd) - rk_fit_hbd_x->at(itrack);
	  double dx = hbd_cluster_gx->at(ihbd)-rk_fit_hbd_gx->at(itrack);
	  double dz = hbd_cluster_gz->at(ihbd)-rk_fit_hbd_gz->at(itrack);
	  double hbdxres = sqrt(dx*dx+dz*dz)*dx/fabs(dx);
	  hhbdxres[hbd_cluster_mid->at(ihbd)-103]->Fill(hbdxres);
	  if(fabs(hbdxres-originx[hbd_cluster_mid->at(ihbd)-103])>hbdposthr) continue;
	  //HBD Y associated
	  hbdmatch = 1;
	  double dhx = hbd_cluster_gx->at(ihbd);
	  double dhz = hbd_cluster_gz->at(ihbd)-rk_fit_init_pos_gz->at(itrack);
	  double slope = hbd_cluster_gy->at(ihbd) / sqrt(dhx*dhx+dhz*dhz);
	  double crs_gy[3];
	  for(int i=0;i<3;i++){
	    crs_gy[i] = slope * sqrt(dgx[i]*dgx[i]+dgz[i]*dgz[i]);
	  }
	  //Search GTR Y Hit
	  int ncrs=0;
	  int gy_id_min[3]={-10000,-10000,-10000};
	  bool gy_ishit[3]={false,false,false};
	  double gy_res_min[3]={10000.,10000.,10000.};
	  double gy_tim_min[3]={10000.,10000.,10000.};
	  double gy_adc_min[3]={10000.,10000.,10000.};
	  TVector3 g1local = geometry->GTR(E16ANA_TrackConstant::ModuleID2020To2013(rk_fit_gtr100_mid->at(itrack)),0)->GetLPos(TVector3(rk_fit_gtr100_gx->at(itrack),0,rk_fit_gtr100_gz->at(itrack)));
	  gtr2d->Fill(rk_fit_gtr100_gx->at(itrack),g1local.X());
	  if(g1local.X()>0){//-------------100
	    for(int i=0;i<n_gtr100y_clusters;i++){
	      if(gtr100y_cluster_mid->at(i)!=rk_fit_gtr100_mid->at(itrack)) continue;
	      // double res = gtr100y_cluster_y->at(i)-crs_gy[0];
	      double res = -gtr100y_cluster_y->at(i)-crs_gy[0];
	      gtr1yres[rk_fit_gtr100_mid->at(itrack)-101]->Fill(res);
	      gtr1ytim[rk_fit_gtr100_mid->at(itrack)-101]->Fill(gtr100y_cluster_t->at(i)-rk_hit_gtr100_xt->at(itrack));
	      if(fabs(res)<gtrposthr[0] && fabs(gtr100y_cluster_t->at(i)-rk_hit_gtr100_xt->at(itrack))<gtrtimthr[0]){
		gy_ishit[0]=true;
		if( fabs(res)<gy_res_min[0] ){
		  gy_res_min[0] = res;
		  gy_id_min[0] = gtr100y_cluster_id->at(i);
		  gy_tim_min[0] = gtr100y_cluster_t->at(i);
		  gy_adc_min[0] = gtr100y_cluster_adc->at(i);
		}
	      }
	    }
	    if(gy_ishit[0]==true){
	      ncrs++;
	    }
	  }
	  else{
	    for(int i=0;i<n_gtr100yb_clusters;i++){
	      if(gtr100yb_cluster_mid->at(i)!=rk_fit_gtr100_mid->at(itrack)) continue;
	      // double res = gtr100yb_cluster_y->at(i)-crs_gy[0];
	      double res = -gtr100yb_cluster_y->at(i)-crs_gy[0];
	      gtr1yres[rk_fit_gtr100_mid->at(itrack)-101]->Fill(res);
	      gtr1ytim[rk_fit_gtr100_mid->at(itrack)-101]->Fill(gtr100yb_cluster_t->at(i)-rk_hit_gtr100_xt->at(itrack));
	      if(fabs(res)<gtrposthr[0] && fabs(gtr100yb_cluster_t->at(i)-rk_hit_gtr100_xt->at(itrack))<gtrtimthr[0]){
		gy_ishit[0]=true;
		if( fabs(res)<gy_res_min[0] ){
		  gy_res_min[0] = res;
		  gy_id_min[0] = gtr100yb_cluster_id->at(i);
		  gy_tim_min[0] = gtr100yb_cluster_t->at(i);
		  gy_adc_min[0] = gtr100yb_cluster_adc->at(i);
		}
	      }
	    }
	    if(gy_ishit[0]==true){
	      ncrs++;
	    }
	  }
	  for(int i=0;i<n_gtr200y_clusters;i++){//-------------200
	    if(gtr200y_cluster_mid->at(i)!=rk_fit_gtr200_mid->at(itrack)) continue;
	    double res = gtr200y_cluster_y->at(i)-crs_gy[1];
	    gtr2yres[rk_fit_gtr200_mid->at(itrack)-101]->Fill(res);
	    gtr2ytim[rk_fit_gtr200_mid->at(itrack)-101]->Fill(gtr200y_cluster_t->at(i)-rk_hit_gtr200_xt->at(itrack));
	    if(fabs(res)<gtrposthr[1] && fabs(gtr200y_cluster_t->at(i)-rk_hit_gtr200_xt->at(itrack))<gtrtimthr[1]){
	      gy_ishit[1]=true;
	      if( fabs(res)<gy_res_min[1] ){
		gy_res_min[1] = res;
		gy_id_min[1] = gtr200y_cluster_id->at(i);
		gy_tim_min[1] = gtr200y_cluster_t->at(i);
		gy_adc_min[1] = gtr200y_cluster_adc->at(i);
	      }
	    }
	  }
	  if(gy_ishit[1]==true){
	    ncrs++;
	  }
	  for(int i=0;i<n_gtr300y_clusters;i++){//-------------300
	    if(gtr300y_cluster_mid->at(i)!=rk_fit_gtr300_mid->at(itrack)) continue;
	    double res = gtr300y_cluster_y->at(i)-crs_gy[2];
	    gtr3yres[rk_fit_gtr300_mid->at(itrack)-101]->Fill(res);
	    gtr3ytim[rk_fit_gtr300_mid->at(itrack)-101]->Fill(gtr300y_cluster_t->at(i)-rk_hit_gtr300_xt->at(itrack));
	    if(fabs(res)<gtrposthr[2] && fabs(gtr300y_cluster_t->at(i)-rk_hit_gtr300_xt->at(itrack))<gtrtimthr[2]){
	      gy_ishit[2]=true;
	      if( fabs(res)<gy_res_min[2] ){
		gy_res_min[2] = res;
		gy_id_min[2] = gtr300y_cluster_id->at(i);
		gy_tim_min[2] = gtr300y_cluster_t->at(i);
	      }
	    }
	  }
	  if(gy_ishit[2]==true){
	    ncrs++;
	  }
	  if(ncrs>1){//GTR y associated
	    gtrymatch = 1;
	    double gy_chisq = gy_res_min[0]*gy_res_min[0]/1.+gy_res_min[1]*gy_res_min[1]/1.+gy_res_min[2]*gy_res_min[2]/1.;
	    ychisq->Fill(gy_chisq);

	    //fill to branch
	    double trk_momy = slope*trk_mom;
	    int trk_hbd_mid = hbd_cluster_mid->at(ihbd);
	    double trk_hbd_lx = rk_fit_hbd_x->at(itrack);
	    double trk_hbd_ly = hbd_cluster_y->at(ihbd);
	    double trk_lg_lx = -10000;
	    double trk_lg_ly = -10000;
	    int ytype = -10000;
	    int trk_lg_mid = ExLGDeadRegion(ientry,itrack,slope,trk_lg_lx,trk_lg_ly,ytype);
	    hdead->Fill(trk_hbd_mid,trk_lg_mid);
	    if (trk_lg_mid < 0) continue;
	    double track_angle_lx = -10000.;
	    double track_angle_ly = -10000.;
	    double track_position_block_lx = -10000;
	    double track_position_block_ly = -10000;
	    int ret = CalcAngleOnLGPlane(ientry,itrack,geometry,&pair_fitter,trk_hbd_mid,trk_lg_mid,ytype,trk_momy,track_angle_lx,track_angle_ly,track_position_block_lx,track_position_block_ly);

	    out_track_id.push_back(track_id->at(itrack));
	    out_chi_square.push_back(chi_square->at(itrack));
	    out_rk_charge.push_back(rk_charge->at(itrack));
	    out_is_selected.push_back(0);
	    out_track_mom.push_back(trk_mom);
	    out_track_mom_x.push_back(trk_momx);
	    out_track_mom_y.push_back(trk_momy);
	    out_track_mom_z.push_back(trk_momz);
	    out_track_tgt_dist.push_back(tgtdist);
	    out_track_lg_pi_eff1.push_back(MomtoLGPieff1(trk_mom));
	    out_track_lg_pi_eff2.push_back(MomtoLGPieff2(trk_mom));
	    out_track_angle_lx.push_back(track_angle_lx);
	    out_track_angle_ly.push_back(track_angle_ly);
	    out_track_position_block_lx.push_back(track_position_block_lx);
	    out_track_position_block_ly.push_back(track_position_block_ly);
	    out_track_ssd_t.push_back(rk_hit_ssd_t->at(itrack));
	    out_track_ssd_adc.push_back(rk_hit_ssd_adc->at(itrack));
	    out_track_gtr100x_t.push_back(rk_hit_gtr100_xt->at(itrack));
	    out_track_gtr100x_adc.push_back(rk_hit_gtr100_xadc->at(itrack));
	    out_track_gtr100y_t.push_back(gy_tim_min[0]);
	    out_track_gtr100y_adc.push_back(gy_adc_min[0]);
	    out_track_gtr200x_t.push_back(rk_hit_gtr200_xt->at(itrack));
	    out_track_gtr200x_adc.push_back(rk_hit_gtr200_xadc->at(itrack));
	    out_track_gtr200y_t.push_back(gy_tim_min[1]);
	    out_track_gtr200y_adc.push_back(gy_adc_min[1]);
	    out_track_gtr300x_t.push_back(rk_hit_gtr300_xt->at(itrack));
	    out_track_gtr300x_adc.push_back(rk_hit_gtr300_xadc->at(itrack));
	    out_track_gtr300y_t.push_back(gy_tim_min[2]);
	    out_track_gtr300y_adc.push_back(gy_adc_min[2]);
	    out_track_select_hbd_resx.push_back(hbdxres);//
	    out_track_select_hbd_adc.push_back(hbd_cluster_adc->at(ihbd));//
	    out_track_select_gtr_nass.push_back(ncrs);//
	    out_track_select_gtr100y_res.push_back(gy_res_min[0]);//
	    out_track_select_gtr200y_res.push_back(gy_res_min[1]);//
	    out_track_select_gtr300y_res.push_back(gy_res_min[2]);//
	    out_track_select_gtr_chisq.push_back(gy_chisq);//
	    double trg_bias = CalcTrgBias(ientry,itrack,trk_lg_mid);
	    out_track_w_trg_bias.push_back(trg_bias);
	    out_track_hbd_mid.push_back(trk_hbd_mid);
	    out_track_hbd_lx.push_back(trk_hbd_lx);
	    out_track_hbd_ly.push_back(trk_hbd_ly);
	    out_track_lg_mid.push_back(trk_lg_mid);
	    out_track_lg_lx.push_back(trk_lg_lx);
	    out_track_lg_ly.push_back(trk_lg_ly);
	    if(rk_charge->at(itrack)==1){
	      if(chi_square->at(itrack)<chisq_plus_min){
		chisq_plus_min = chi_square->at(itrack);
		plus_index = ntrkacc;
	      }	  
	    }
	    if(rk_charge->at(itrack)==-1){
	      if(chi_square->at(itrack)<chisq_minus_min){
		chisq_minus_min = chi_square->at(itrack);
		minus_index = ntrkacc;
	      }	  
	    }

	    //HBD loop
	    double resx = 0;
	    double resy = 0;
	    double resx_min = 10000;
	    double resy_min = 10000;
	    out_track_hbd_allhit_resx.push_back(vector<double>());
	    out_track_hbd_allhit_resy.push_back(vector<double>());
	    out_track_hbd_allhit_ftime.push_back(vector<double>());
	    out_track_hbd_allhit_adc.push_back(vector<double>());
	    out_track_hbd_allhit_size.push_back(vector<double>());
	    out_track_hbd_allhit_eprob.push_back(vector<double>());
	    out_track_hbd_allhit_cprob.push_back(vector<double>());
	    int nhbdc = 0;
	    for(int jhbd=0;jhbd<n_hbd_clusters;jhbd++){
	      if ( hbd_cluster_t->at(jhbd)>hbdtimthr ) continue;
	      if ( runoption==3 && hbdise==1 && hbd_cluster_eprob->at(jhbd)<1 ) continue;//220213;
	      // if ( runoption==3 && hbdise==1 && (hbd_cluster_size->at(jhbd)<2||hbd_cluster_adc->at(jhbd)<7*60) ) continue;//220407;
	      if ( runoption==3 && hbdise==2 && (hbd_cluster_size->at(jhbd)!=1||hbd_cluster_adc->at(jhbd)>3) ) continue;//220213;
	      if ( runoption==3 && hbdise==3 && (hbd_cluster_size->at(jhbd)<2||hbd_cluster_adc->at(jhbd)<10) ) continue;//220307;
	      if ( runoption==3 && hbdise==4 && (hbd_cluster_size->at(jhbd)<2||hbd_cluster_adc->at(jhbd)<4) ) continue;//220213;
	      if ( runoption==0 && hbdise==2 && (hbd_cluster_size->at(jhbd)!=1) ) continue;//220213;
	      if(  hbd_cluster_mid->at(jhbd) == trk_hbd_mid ){
		resx = hbd_cluster_x->at(jhbd) - trk_hbd_lx;
		resy = hbd_cluster_y->at(jhbd) - trk_hbd_ly;
		out_track_hbd_allhit_resx[ntrkacc].push_back(resx);
		out_track_hbd_allhit_resy[ntrkacc].push_back(resy);
		out_track_hbd_allhit_ftime[ntrkacc].push_back(hbd_cluster_ftime->at(jhbd));
		out_track_hbd_allhit_adc[ntrkacc].push_back(hbd_cluster_adc->at(jhbd));
		out_track_hbd_allhit_size[ntrkacc].push_back(hbd_cluster_size->at(jhbd));
		out_track_hbd_allhit_eprob[ntrkacc].push_back(hbd_cluster_eprob->at(jhbd));
		out_track_hbd_allhit_cprob[ntrkacc].push_back(hbd_cluster_cprob->at(jhbd));
		if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
		  resx_min = resx;
		  resy_min = resy;
		}
		nhbdc++;
	      }
	    }
	    out_track_hbd_nearx.push_back(resx_min);
	    out_track_hbd_neary.push_back(resy_min);
	    out_track_hbd_multiplicity.push_back(nhbdc);


	    //LG Hit loop
	    resx = 0;
	    resy = 0;
	    resx_min = 10000;
	    resy_min = 10000;
	    out_track_lg_allhit_resx.push_back(vector<double>());
	    out_track_lg_allhit_resy.push_back(vector<double>());
	    out_track_lg_allhit_ftime.push_back(vector<double>());
	    out_track_lg_allhit_adc.push_back(vector<double>());
	    out_track_lg_allhit_trgt.push_back(vector<double>());
	    int nlgh = 0;
	    for(int ilg=0;ilg<n_lg_hits;ilg++){
	      if ( runoption==3 && lgise==2 && (lg_hit_adc->at(ilg)<20||lg_hit_adc->at(ilg)>50) ) continue;
	      if(  lg_hit_mid->at(ilg) == trk_lg_mid && lg_hit_fflag->at(ilg)!=2 ){
		resx = lg_hit_x->at(ilg) - trk_lg_lx;
		resy = lg_hit_y->at(ilg) - trk_lg_ly;
		out_track_lg_allhit_resx[ntrkacc].push_back(resx);
		out_track_lg_allhit_resy[ntrkacc].push_back(resy);
		out_track_lg_allhit_ftime[ntrkacc].push_back(lg_hit_t->at(ilg));
		out_track_lg_allhit_adc[ntrkacc].push_back(lg_hit_adc->at(ilg));
		double trgt_tmp=-10000;
		for(int itlg=0;itlg<n_trg_tracks;itlg++){
		  if(trg_track_lg_mid->at(itlg)!=lg_hit_mid->at(ilg)||trg_track_lg_cid->at(itlg)!=lg_hit_cid->at(ilg)) continue;
		  if(fabs(trg_track_lg_t->at(itlg))<11){
		    trgt_tmp=trg_track_lg_t->at(itlg);
		    break;
		  }
		}
		out_track_lg_allhit_trgt[ntrkacc].push_back(trgt_tmp);
		if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
		  resx_min = resx;
		  resy_min = resy;
		}
		nlgh++;
	      }
	    }
	    out_track_lg_nearx.push_back(resx_min);
	    out_track_lg_neary.push_back(resy_min);
	    out_track_lg_multiplicity.push_back(nlgh);

	    ntrkacc++;
	    count++;

	  }//GTR y associated

	}//hbdcluster loop

	htrkacc->Fill(hbdmatch);
	htrkacc2->Fill(gtrymatch);

      }//track loop

      if(plus_index!=-10000){out_is_selected.at(plus_index)=1;}
      if(minus_index!=-10000){out_is_selected.at(minus_index)=1;}

      if(ntrkacc!=0){
	//Get Hits & Clusters
	out_n_tracks = ntrkacc;
	out_run_id = run_id;
	out_event_id = event_id;
	out_spill_id = spill_id;

	tree->Fill();
      }
      nevent++;

   }//event loop

   fout->Write();
   fout->Close();

   std::cout<<count<<std::endl;

}

void SingleTrackAnalyzerForRes::CalcLGWFefficiency(int runnum, int maxevent, double wfthrh, double wfthrl)
{

  TFile* froot = new TFile(Form("wfeff%06d.root",runnum),"recreate");
  TString fout = Form("wfeff%06d.pdf",runnum);
  // std::ofstream ftext;
  // std::string ftextname = "" + runnum + ".txt";
  // ftext.open(ftextname);

  TH1F* ht[7];
  TF1* ft[7];
  double param[7]={94.,94.5,95.,94.5,93.5,94.5,95.5};
  TCanvas* ct = new TCanvas("ct","ct",1400,500);
  ct->Divide(4,2);
  gStyle->SetOptFit(1111);
  // for(int i=0;i<7;i++){
  //   ht[i] = new TH1F(Form("ht%d",i+102),Form("ht%d",i+102),100,50,150);
  //   ft[i] = new TF1(Form("ft%d",i),"gaus",0,200);
  //   if(i==3) continue;
  //   ct->cd(i+1);
  //   fChain->Draw(Form("lg_hit_t>>ht%d",i+102),Form("lg_hit_mid==%d",i+102));
  //   ht[i]->Fit(Form("ft%d",i),"","",90,110);
  //   param[i] = ft[i]->GetParameter(1);
  // }

  double reg_trg_t = 10.;
  double reg_wf_t = 10.;

  TH1F* heffav[7];
  TH1F* htav[7];
  TH1F* htavwo[7];
  TH1F* htdiffav[7];
  TH2F* ht2dav[7];
  TH2F* henter[7];
  TH2F* hhit[7];
  TH1F* hnwfhits[7];
  TH1F* heff1d[7];
  TH1F* hwfadc[7];
  for(int i=0;i<7;i++){
    heffav[i] = new TH1F(Form("heffav%d",i+102),Form("WaveformEff_mod%d",i+102),5,-0.5,4.5);
    htav[i] = new TH1F(Form("htav%d",i+102),Form("WF_t_mod%d",i+102),100,50,150);
    htavwo[i] = new TH1F(Form("htavwo%d",i+102),Form("WF_t_NotCalibrated_mod%d",i+102),100,50,150);
    htdiffav[i] = new TH1F(Form("htdiffav%d",i+102),Form("Discri_t-WF_t_mod%d",i+102),40,-20,20);
    ht2dav[i] = new TH2F(Form("ht2dav%d",i+102),Form("Discri_t_vs_WF_t_mod%d",102+i),80,-40,40,80,-40,40);
    henter[i] = new TH2F(Form("henter%d",i+102),Form("DiscriOut_block_mod%d",102+i),7,-0.5,6.5,6,-0.5,5.5);
    hhit[i] = new TH2F(Form("hhit%d",i+102),Form("DST1Hit_block_mod%d",102+i),7,-0.5,6.5,6,-0.5,5.5);
    hnwfhits[i] = new TH1F(Form("hnwfhits%d",i+102),Form("N_WFhits_mod%d",i+102),200,0,200);
    heff1d[i] = new TH1F(Form("heff1d%d",i+102),Form("WFefficiency_block_mod%d",i+102),60,0.5,1.1);
    hwfadc[i] = new TH1F(Form("hwfadc%d",i+102),Form("WF_adc_mod%d",i+102),100,0,200);
  }

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<"Loop "<<ientry<<std::endl;}
      if( maxevent!=-1&&ientry>maxevent ){break;}

      int nwfhit[7]={0};
      for(int ilg=0;ilg<n_lg_hits;ilg++){
	int mide = lg_hit_mid->at(ilg)-102;
	if(fabs(lg_hit_t->at(ilg)-trigger_fine_time-param[mide])>10.) continue;
	nwfhit[mide]++;
	nwfhit[3]++;
      }
      for(int imod=0;imod<7;imod++){
	hnwfhits[imod]->Fill(nwfhit[imod]);
      }

      for(int itrg=0;itrg<n_trg_lg_hits;itrg++){//trg loop
	if(fabs(trg_lg_hit_t->at(itrg))>reg_trg_t) continue;
	int mide = trg_lg_hit_mid->at(itrg)-102;
	int mid = trg_lg_hit_mid->at(itrg);
	int cid = trg_lg_hit_cid->at(itrg);
	henter[mide]->Fill((double)(cid%10),(double)(cid/10));
	henter[3]->Fill((double)(cid%10),(double)(cid/10));
	int nLGhit = 0;
	for(int ilg=0;ilg<n_lg_hits;ilg++){
	  if(lg_hit_mid->at(ilg)!=mid||lg_hit_cid->at(ilg)!=cid) continue;
	  if(fabs(trg_lg_hit_t->at(itrg)-(lg_hit_t->at(ilg)-trigger_fine_time-param[mide]))>reg_wf_t) continue;
	  if((mid==106||mid==104)&&lg_hit_adc->at(ilg)<wfthrh) continue;
	  if((mid==102||mid==103||mid==107||mid==108)&&lg_hit_adc->at(ilg)<wfthrl) continue;
	  hhit[mide]->Fill((double)(cid%10),(double)(cid/10));
	  hhit[3]->Fill((double)(cid%10),(double)(cid/10));
	  htav[mide]->Fill((lg_hit_t->at(ilg)-trigger_fine_time));
	  htav[3]->Fill((lg_hit_t->at(ilg)-trigger_fine_time));
	  htavwo[mide]->Fill(lg_hit_t->at(ilg));
	  htavwo[3]->Fill(lg_hit_t->at(ilg));
	  htdiffav[mide]->Fill(trg_lg_hit_t->at(itrg)-(lg_hit_t->at(ilg)-trigger_fine_time-param[mide]));
	  htdiffav[3]->Fill(trg_lg_hit_t->at(itrg)-(lg_hit_t->at(ilg)-trigger_fine_time-param[mide]));
	  ht2dav[mide]->Fill(lg_hit_t->at(ilg)-trigger_fine_time-param[mide],trg_lg_hit_t->at(itrg));
	  ht2dav[3]->Fill(lg_hit_t->at(ilg)-trigger_fine_time-param[mide],trg_lg_hit_t->at(itrg));
	  hwfadc[mide]->Fill(lg_hit_adc->at(ilg));
	  if(mid==103||mid==104||mid==106||mid==107){hwfadc[3]->Fill(lg_hit_adc->at(ilg));}
	  nLGhit++;
	}
	heffav[mide]->Fill(nLGhit);
	heffav[3]->Fill(nLGhit);
      }//trg loop

   }//event loop


   TH2F* heff[7];
   for(int i=0;i<7;i++){
     heff[i] = (TH2F*)hhit[i]->Clone();
     heff[i]->SetName(Form("heff%d",i+102));
     heff[i]->Divide(henter[i]);
   }

   double venter[7][6][7]={0.};
   double vhit[7][6][7]={0.};
   double vcid[7][57]={0.};
   double veff[7][57]={0.};
   double zero[7][57]={0.};
   double veff_err[7][57]={0.};
   for(int m=0;m<7;m++){//mod
     for(int i=0;i<6;i++){//y
       for(int j=0;j<7;j++){//x
	 int xbin = henter[m]->GetXaxis()->FindBin(j);
	 int ybin = henter[m]->GetYaxis()->FindBin(i);
	 venter[m][i][j] = henter[m]->GetBinContent(xbin,ybin);
	 vhit[m][i][j] = hhit[m]->GetBinContent(xbin,ybin);
       	 vcid[m][i*10+j] = (double)i*10.+(double)j;
       	 veff[m][i*10+j] = vhit[m][i][j]/venter[m][i][j];
       	 veff_err[m][i*10+j] = sqrt(veff[m][i*10+j]*(1.-veff[m][i*10+j])/venter[m][i][j]);
	 if(m!=3){heff1d[m]->Fill(veff[m][i*10+j]);}
	 if(m==1||m==2||m==4||m==5){
	   heff1d[3]->Fill(veff[m][i*10+j]);
	 }
       }
     }
   }
   TGraphErrors* geff[7];
   TCanvas* cgeff = new TCanvas("cgeff","cgeff",1400,500);
   cgeff->Divide(4,2);
   for(int m=0;m<7;m++){
     geff[m] = new TGraphErrors(57,vcid[m],veff[m],zero[m],veff_err[m]);
     cgeff->cd(m+1)->SetGridy();
     geff[m]->Draw("AP");
   }


   //draw
   TCanvas* ceffav = new TCanvas("ceffav","ceffav",1400,500);
   ceffav->Divide(4,2);
   for(int i=0;i<7;i++){
     ceffav->cd(i+1);
     heffav[i]->Draw("hist text");
   }
   TCanvas* ctav = new TCanvas("ctav","ctav",1400,500);
   ctav->Divide(4,2);
   for(int i=0;i<7;i++){
     ctav->cd(i+1);
     htav[i]->Draw();
   }
   TCanvas* ctavwo = new TCanvas("ctavwo","ctavwo",1400,500);
   ctavwo->Divide(4,2);
   for(int i=0;i<7;i++){
     ctavwo->cd(i+1);
     htavwo[i]->Draw();
   }
   TCanvas* ctdiffav = new TCanvas("ctdiffav","ctdiffav",1400,500);
   ctdiffav->Divide(4,2);
   for(int i=0;i<7;i++){
     ctdiffav->cd(i+1);
     htdiffav[i]->Draw();
   }
   TCanvas* center = new TCanvas("center","center",1000,500);
   center->Divide(4,2);
   for(int i=0;i<7;i++){
     center->cd(i+1);
     henter[i]->Draw("colz text");
   }
   TCanvas* chit = new TCanvas("chit","chit",1000,500);
   chit->Divide(4,2);
   for(int i=0;i<7;i++){
     chit->cd(i+1);
     hhit[i]->Draw("colz text");
   }
   TCanvas* ceff = new TCanvas("ceff","ceff",1000,500);
   ceff->Divide(4,2);
   for(int i=0;i<7;i++){
     ceff->cd(i+1);
     heff[i]->Draw("colz text");
   }
   TCanvas* cnwfhits = new TCanvas("cnwfhits","cnwfhits",1000,500);
   cnwfhits->Divide(4,2);
   for(int i=0;i<7;i++){
     cnwfhits->cd(i+1);
     hnwfhits[i]->Draw();
   }
   TCanvas* ceff1d = new TCanvas("ceff1d","ceff1d",1000,500);
   ceff1d->Divide(4,2);
   for(int i=0;i<7;i++){
     ceff1d->cd(i+1);
     heff1d[i]->Draw();
   }
   TCanvas* cwfadc = new TCanvas("cwfadc","cwfadc",1000,500);
   cwfadc->Divide(4,2);
   for(int i=0;i<7;i++){
     cwfadc->cd(i+1);
     hwfadc[i]->Draw();
   }

   TCanvas* cc = new TCanvas("cc","cc",1400,500);
   cc->SaveAs(fout+"[","pdf");
   cgeff->SaveAs(fout,"pdf");
   ceff1d->SaveAs(fout,"pdf");
   cwfadc->SaveAs(fout,"pdf");
   ceffav->SaveAs(fout,"pdf");
   ctdiffav->SaveAs(fout,"pdf");
   ctavwo->SaveAs(fout,"pdf");
   ctav->SaveAs(fout,"pdf");
   center->SaveAs(fout,"pdf");
   chit->SaveAs(fout,"pdf");
   ceff->SaveAs(fout,"pdf");
   cnwfhits->SaveAs(fout,"pdf");
   ct->SaveAs(fout,"pdf");
   cc->SaveAs(fout+"]","pdf");

   // ftext << wfthrh << " " << wfthrl << std::endl;

   froot->Write();
   froot->Close();

}

void SingleTrackAnalyzerForRes::LGHitADC(int maxevent, char* out_pdf_file, char* out_root_file)
{

  TFile *fout = new TFile(out_root_file,"recreate");

  TH1F* adc[7][60];
  for(int i=0;i<7;i++){
    for(int j=0;j<60;j++){
      adc[i][j] = new TH1F(Form("adc%d%d",i,j),Form("LGadc_mid%d_cid%d",i+102,j),200,0,200);
    }
  }

   if (fChain == 0) return;
   Long64_t n_entries = fChain->GetEntries();
   Long64_t nentries = fChain->GetEntriesFast();
   int nevent=0;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
      if( maxevent!=-1&&nevent>maxevent ){break;}

      if (Cut(ientry) < 0) continue;

      for(int ilg=0;ilg<n_lg_hits;ilg++){//lghit loop
	if(lg_hit_fflag->at(ilg)>1) continue;
	int mid = lg_hit_mid->at(ilg)-102;
	int cid = lg_hit_cid->at(ilg);
	if(mid<0||mid>6||cid<0||cid>59) continue;
	adc[mid][cid]->Fill(lg_hit_adc->at(ilg));
      }//lghit loop
      nevent++;
   }//event loop

   TString outfile = Form("%s",out_pdf_file);
   TCanvas* c[7];
   TLine* l[7][42];
   for(int i=0;i<7;i++){
     c[i] = new TCanvas(Form("c%d",i),Form("c%d",i),1400,1000);
     c[i]->Divide(7,6);
     for(int j=0;j<42;j++){
       c[i]->cd(42-j);
       int tmpch = (j/7)*10 + j%7;
       adc[i][tmpch]->Draw("colz");
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

   TCanvas* cdef = new TCanvas("cdef","cdef",700,500);
   cdef->SaveAs(outfile+"[","pdf");
   for(int i=0;i<7;i++){
     c[i]->SaveAs(outfile,"pdf");
   }
   cdef->SaveAs(outfile+"]","pdf");

   fout->Write();
   fout->Close();

}
