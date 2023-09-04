#define E16ANA_EIDSingleTrackAnalyzer_cxx
#include "E16ANA_EIDSingleTrackAnalyzer.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_TrackAnalyzerFromTree.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_LGClustering.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDDeadChannel.hh"
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

int E16ANA_EIDSingleTrackAnalyzer::CalcAngleOnLGPlane(Long64_t entry, Int_t itrack, E16ANA_GeometryV2* geometry, E16ANA_MultiTrack* pair_fitter, double hbdmid, double lgmid, int ytype, double& lg_angle_lx, double& lg_angle_ly, double& lg_position_block_lx, double& lg_position_block_ly, TVector3& vertex, TVector3& mom)
{
  double charge=rk_charge->at(itrack);
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

void E16ANA_EIDSingleTrackAnalyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L E16ANA_EIDSingleTrackAnalyzer.C
//      root> E16ANA_EIDSingleTrackAnalyzer t
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

void E16ANA_EIDSingleTrackAnalyzer::MakeTree_EIDEfficiency(int runoption, int maxevent, char* out_file_name, int hbd_track_module, int track_charge, double max_chi_square)
{
   if (fChain == 0) return;

   TFile* fout = new TFile(out_file_name,"recreate");
   TTree* tree = new TTree("tree","tree");

   Int_t           out_run_id;
   Int_t           out_event_id;
   Int_t           out_spill_id;
   Int_t out_lg_event_multiplicity;
   Int_t out_trg_event_multiplicity; // +/- 30 ns around 0 in trg_t
   double out_single_ratio;
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
   vector<int> out_track_ssd_multiplicity;
   vector<double> out_track_gtr100x_t;
   vector<double> out_track_gtr100x_adc;
   vector<int> out_track_gtr100x_multiplicity;
   vector<double> out_track_gtr100y_t;
   vector<double> out_track_gtr100y_adc;
   vector<int> out_track_gtr100y_multiplicity;
   vector<double> out_track_gtr200x_t;
   vector<double> out_track_gtr200x_adc;
   vector<int> out_track_gtr200x_multiplicity;
   vector<double> out_track_gtr200y_t;
   vector<double> out_track_gtr200y_adc;
   vector<int> out_track_gtr200y_multiplicity;
   vector<double> out_track_gtr300x_t;
   vector<double> out_track_gtr300x_adc;
   vector<int> out_track_gtr300x_multiplicity;
   vector<double> out_track_gtr300y_t;
   vector<double> out_track_gtr300y_adc;
   vector<int> out_track_gtr300y_multiplicity;
   vector<bool> out_track_w_trg_bias;
   vector<bool> out_track_w_trg_gtr;
   vector<bool> out_track_w_trg_hbd;
   vector<int>  out_track_w_trg_lg;
   vector<bool> out_track_w_trg_trk;
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
   tree->Branch("spill_id",&out_spill_id,"spill_id/I");
   tree->Branch("lg_event_multiplicity",&out_lg_event_multiplicity,"lg_event_multiplicity/I");
   tree->Branch("trg_event_multiplicity",&out_trg_event_multiplicity,"trg_event_multiplicity/I");
   tree->Branch("single_ratio",&out_single_ratio,"single_ratio/D");
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
   tree->Branch("track_ssd_multiplicity", &out_track_ssd_multiplicity);
   tree->Branch("track_gtr100x_t", &out_track_gtr100x_t);
   tree->Branch("track_gtr100x_adc", &out_track_gtr100x_adc);
   tree->Branch("track_gtr100x_multiplicity", &out_track_gtr100x_multiplicity);
   tree->Branch("track_gtr100y_t", &out_track_gtr100y_t);
   tree->Branch("track_gtr100y_adc", &out_track_gtr100y_adc);
   tree->Branch("track_gtr100y_multiplicity", &out_track_gtr100y_multiplicity);
   tree->Branch("track_gtr200x_t", &out_track_gtr200x_t);
   tree->Branch("track_gtr200x_adc", &out_track_gtr200x_adc);
   tree->Branch("track_gtr200x_multiplicity", &out_track_gtr200x_multiplicity);
   tree->Branch("track_gtr200y_t", &out_track_gtr200y_t);
   tree->Branch("track_gtr200y_adc", &out_track_gtr200y_adc);
   tree->Branch("track_gtr200y_multiplicity", &out_track_gtr200y_multiplicity);
   tree->Branch("track_gtr300x_t", &out_track_gtr300x_t);
   tree->Branch("track_gtr300x_adc", &out_track_gtr300x_adc);
   tree->Branch("track_gtr300x_multiplicity", &out_track_gtr300x_multiplicity);
   tree->Branch("track_gtr300y_t", &out_track_gtr300y_t);
   tree->Branch("track_gtr300y_adc", &out_track_gtr300y_adc);
   tree->Branch("track_gtr300y_multiplicity", &out_track_gtr300y_multiplicity);
   tree->Branch("track_w_trg_bias", &out_track_w_trg_bias);
   tree->Branch("track_w_trg_gtr", &out_track_w_trg_gtr);
   tree->Branch("track_w_trg_hbd", &out_track_w_trg_hbd);
   tree->Branch("track_w_trg_lg", &out_track_w_trg_lg);
   tree->Branch("track_w_trg_trk", &out_track_w_trg_trk);
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
      out_track_ssd_multiplicity.clear();
      out_track_gtr100x_t.clear();
      out_track_gtr100x_adc.clear();
      out_track_gtr100x_multiplicity.clear();
      out_track_gtr100y_t.clear();
      out_track_gtr100y_adc.clear();
      out_track_gtr100y_multiplicity.clear();
      out_track_gtr200x_t.clear();
      out_track_gtr200x_adc.clear();
      out_track_gtr200x_multiplicity.clear();
      out_track_gtr200y_t.clear();
      out_track_gtr200y_adc.clear();
      out_track_gtr200y_multiplicity.clear();
      out_track_gtr300x_t.clear();
      out_track_gtr300x_adc.clear();
      out_track_gtr300x_multiplicity.clear();
      out_track_gtr300y_t.clear();
      out_track_gtr300y_adc.clear();
      out_track_gtr300y_multiplicity.clear();
      out_track_w_trg_bias.clear();
      out_track_w_trg_gtr.clear();
      out_track_w_trg_hbd.clear();
      out_track_w_trg_lg.clear();
      out_track_w_trg_trk.clear();
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
	double trk_momx = rk_fit_init_mom_gx->at(itrack);
	double trk_momy = rk_fit_init_mom_gy->at(itrack);
	double trk_momz = rk_fit_init_mom_gz->at(itrack);
	double trk_mom  = sqrt(trk_momx*trk_momx+trk_momy*trk_momy+trk_momz*trk_momz);
	if (chi_square->at(itrack)>100) continue;
	if (chi_square->at(itrack)>max_chi_square) continue;
	double trk_hbd_lx = -10000;
	double trk_hbd_ly = -10000;
      	int trk_hbd_mid = TrackInHBDAcceptance(ientry,itrack,trk_hbd_lx,trk_hbd_ly);
      	if (trk_hbd_mid < 0) continue;
      	double cog[2] = {trk_hbd_lx,trk_hbd_ly};
      	int hbd_padid = E16ANA_HBDGeometry::GetPadIDWLocalCoordinate(trk_hbd_mid,cog);
      	if( hbddch.Status(trk_hbd_mid,hbd_padid) != 0 ) continue;
	double trk_lg_lx = -10000;
	double trk_lg_ly = -10000;
	int ytype = -10000;
      	int trk_lg_mid = TrackInLGAcceptance(ientry,itrack,trk_lg_lx,trk_lg_ly,ytype);
      	if (trk_lg_mid < 0) continue;
	if (hbd_track_module!=-1&&trk_hbd_mid!=hbd_track_module) continue;
	if (track_charge!=0&&rk_charge->at(itrack)==-track_charge) continue;

	int hbdise = 5;
	int lgise = 0;
	// if ( runoption==3 && CutByMorino(ientry,itrack) < 0) continue;//220208
	// if ( runoption==1 && CutByMorino(ientry,itrack) < 0) continue;//220208
	double track_angle_lx = -10000.;
	double track_angle_ly = -10000.;
	double track_position_block_lx = -10000;
	double track_position_block_ly = -10000;
	TVector3 vertex(rk_fit_init_pos_gx->at(itrack),rk_fit_init_pos_gy->at(itrack),rk_fit_init_pos_gz->at(itrack));
	TVector3 mom(rk_fit_init_mom_gx->at(itrack),rk_fit_init_mom_gy->at(itrack),rk_fit_init_mom_gz->at(itrack));
	CalcAngleOnLGPlane(ientry,itrack,geometry,&pair_fitter,trk_hbd_mid,trk_lg_mid,ytype,track_angle_lx,track_angle_ly,track_position_block_lx,track_position_block_ly,vertex,mom);
	// int lgmulti=0;
	// for(int ilgmulti=0;ilgmulti<n_lg_hits;ilgmulti++){
	//   if(lg_hit_mid->at(ilgmulti)==trk_lg_mid&&lg_hit_fflag->at(ilgmulti)!=2){lgmulti++;}
	// }
	// if ( runoption==3 && lgmulti>5 ) continue;//220310
	// if ( runoption==0 && lgmulti>4 ) continue;//220310
	// int hbdmulti=0;
	// for(int ihbdmulti=0;ihbdmulti<n_hbd_clusters;ihbdmulti++){
	//   if(hbd_cluster_mid->at(ihbdmulti)==trk_hbd_mid){hbdmulti++;}
	// }
	// if ( runoption==3 && hbdmulti>8 ) continue;//220310
	double tgtth = 5.;
	int tgtid = -10000;
	double tgtdist = -10000.;
	// if(runoption==0){
	//   tgtdist = TargetAssociation(ientry,itrack,tgtth);// for the production in 220418(etc)
	// }
	// else{
	  tgtdist = TargetAssociation(ientry,itrack,tgtid);//220725 for the production in 220707
	// }
	if( tgtdist<0 || tgtdist>100 ) continue;//220725 for the production in 220707

	//SSD&GTR loop
	int midtmp, nssd, ngtr100x, ngtr100y, ngtr200x, ngtr200y, ngtr300x, ngtr300y;
	midtmp = rk_fit_ssd_mid->at(itrack);
	nssd=0;
	for(int igtr=0;igtr<n_ssd_clusters;igtr++){
	  if(ssd_cluster_mid->at(igtr)!=midtmp) continue;
	  nssd++;
	}
	midtmp = rk_fit_gtr100_mid->at(itrack);
	ngtr100x=0;
	for(int igtr=0;igtr<n_gtr100x_clusters;igtr++){
	  if(gtr100x_cluster_adc->at(igtr)<100) continue;
	  if(gtr100x_cluster_mid->at(igtr)!=midtmp) continue;
	  ngtr100x++;
	}
	ngtr100y=0;
	for(int igtr=0;igtr<n_gtr100y_clusters;igtr++){
	  if(gtr100y_cluster_adc->at(igtr)<50) continue;
	  if(gtr100y_cluster_mid->at(igtr)!=midtmp) continue;
	  ngtr100y++;
	}
	midtmp = rk_fit_gtr200_mid->at(itrack);
	ngtr200x=0;
	for(int igtr=0;igtr<n_gtr200x_clusters;igtr++){
	  if(gtr200x_cluster_adc->at(igtr)<100) continue;
	  if(gtr200x_cluster_mid->at(igtr)!=midtmp) continue;
	  ngtr200x++;
	}
	ngtr200y=0;
	for(int igtr=0;igtr<n_gtr200y_clusters;igtr++){
	  if(gtr200y_cluster_adc->at(igtr)<50) continue;
	  if(gtr200y_cluster_mid->at(igtr)!=midtmp) continue;
	  ngtr200y++;
	}
	midtmp = rk_fit_gtr300_mid->at(itrack);
	ngtr300x=0;
	for(int igtr=0;igtr<n_gtr300x_clusters;igtr++){
	  if(gtr300x_cluster_adc->at(igtr)<100) continue;
	  if(gtr300x_cluster_mid->at(igtr)!=midtmp) continue;
	  ngtr300x++;
	}
	ngtr300y=0;
	for(int igtr=0;igtr<n_gtr300y_clusters;igtr++){
	  if(gtr300y_cluster_adc->at(igtr)<50) continue;
	  if(gtr300y_cluster_mid->at(igtr)!=midtmp) continue;
	  ngtr300y++;
	}


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
	out_track_ssd_multiplicity.push_back(nssd);
	out_track_gtr100x_t.push_back(rk_hit_gtr100_xt->at(itrack));
	out_track_gtr100x_adc.push_back(rk_hit_gtr100_xadc->at(itrack));
	out_track_gtr100x_multiplicity.push_back(ngtr100x);
	out_track_gtr100y_t.push_back(rk_hit_gtr100_yt->at(itrack));
	out_track_gtr100y_adc.push_back(rk_hit_gtr100_yadc->at(itrack));
	out_track_gtr100y_multiplicity.push_back(ngtr100y);
	out_track_gtr200x_t.push_back(rk_hit_gtr200_xt->at(itrack));
	out_track_gtr200x_adc.push_back(rk_hit_gtr200_xadc->at(itrack));
	out_track_gtr200x_multiplicity.push_back(ngtr200x);
	out_track_gtr200y_t.push_back(rk_hit_gtr200_yt->at(itrack));
	out_track_gtr200y_adc.push_back(rk_hit_gtr200_yadc->at(itrack));
	out_track_gtr200y_multiplicity.push_back(ngtr200y);
	out_track_gtr300x_t.push_back(rk_hit_gtr300_xt->at(itrack));
	out_track_gtr300x_adc.push_back(rk_hit_gtr300_xadc->at(itrack));
	out_track_gtr300x_multiplicity.push_back(ngtr300x);
	out_track_gtr300y_t.push_back(rk_hit_gtr300_yt->at(itrack));
	out_track_gtr300y_adc.push_back(rk_hit_gtr300_yadc->at(itrack));
	out_track_gtr300y_multiplicity.push_back(ngtr300y);
	/////////
        int blockchx = (trk_lg_lx)-(track_position_block_lx);
        int blockchy = (trk_lg_ly/fabs(trk_lg_ly))*(fabs(trk_lg_ly)+track_position_block_ly);
        int blockch = LocaltoCh(blockchx,blockchy);
	bool wtrggtr = false;
	bool wtrghbd = false;
	int  wtrglg = -10000;
	bool wtrgtrk = false;
	bool trg_bias = wTrgBias(ientry,itrack,trk_lg_mid,blockch,TrigAWmin,TrigAWmax,TrigTW,wtrggtr,wtrghbd,wtrglg,wtrgtrk);
	out_track_w_trg_bias.push_back(trg_bias);
	out_track_w_trg_gtr.push_back(wtrggtr);
	out_track_w_trg_hbd.push_back(wtrghbd);
	out_track_w_trg_lg.push_back(wtrglg);
	out_track_w_trg_trk.push_back(wtrgtrk);
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
	int nlgev = 0;
	for(int i=0;i<n_lg_hits;i++){
	  if( lg_hit_fflag->at(i)==2 ) continue;
	  nlgev++;
	}
	out_lg_event_multiplicity = nlgev;
	int ntrgev = 0;
	TH1F* htrgev = new TH1F("htrgev","htrgev",20,-50,50);
	for(int i=0;i<n_trg_lg_hits;i++){
	  if( trg_lg_hit_t->at(i)<-30 || trg_lg_hit_t->at(i)>30 ) continue;
	  ntrgev++;
	  htrgev->Fill(trg_lg_hit_t->at(i));
	}
	out_trg_event_multiplicity = ntrgev;
	int maxbin = htrgev->GetMaximumBin();
	out_single_ratio = ( htrgev->GetBinContent(maxbin-1) + htrgev->GetBinContent(maxbin) + htrgev->GetBinContent(maxbin+1) ) / ((double)htrgev->Integral());
	delete htrgev;

	tree->Fill();
      }
      nevent++;
   }//event loop

   fout->Write();
   fout->Close();

}

void E16ANA_EIDSingleTrackAnalyzer::MakeTree_EIDEfficiency_woY(int runoption, int maxevent, char* out_file_name, int hbd_track_module, int track_charge, double max_chi_square)
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
	double tgtdist = TargetAssociation(ientry,itrack,5);
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
	    int trk_lg_mid = TrackInLGAcceptance(ientry,itrack,trk_lg_lx,trk_lg_ly,ytype,slope);
	    hdead->Fill(trk_hbd_mid,trk_lg_mid);
	    if (trk_lg_mid < 0) continue;
	    double track_angle_lx = -10000.;
	    double track_angle_ly = -10000.;
	    double track_position_block_lx = -10000;
	    double track_position_block_ly = -10000;
	    TVector3 vertex(rk_fit_init_pos_gx->at(itrack),0.,rk_fit_init_pos_gz->at(itrack));
	    TVector3 mom(rk_fit_init_mom_gx->at(itrack),trk_momy,rk_fit_init_mom_gz->at(itrack));
	    CalcAngleOnLGPlane(ientry,itrack,geometry,&pair_fitter,trk_hbd_mid,trk_lg_mid,ytype,track_angle_lx,track_angle_ly,track_position_block_lx,track_position_block_ly,vertex,mom);

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
	    // double trg_bias = CalcTrgBias(ientry,itrack,trk_lg_mid);//220825
	    // out_track_w_trg_bias.push_back(trg_bias);
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

void E16ANA_EIDSingleTrackAnalyzer::WaveformEfficiency(int runnum, int maxevent, double wfthrh, double wfthrl)
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

void E16ANA_EIDSingleTrackAnalyzer::LGHitADC(int maxevent, char* out_pdf_file, char* out_root_file)
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

int IDchange(int ret){
  if(ret==10){return 0;}
  else if(ret==15){return 1;}
  else if(ret==16){return 2;}
  else if(ret==17){return 3;}
  else if(ret==50){return 4;}
  else if(ret==56){return 6;}
  else if(ret==57){return 7;}
}

// void E16ANA_EIDSingleTrackAnalyzer::KsRunAnalysis(int maxevent, char* out_file_name)
// {

//    TH1F* hacc = new TH1F();

//    Long64_t n_entries = fChain->GetEntries();
//    Long64_t nentries = fChain->GetEntriesFast();
//    Long64_t nbytes = 0, nb = 0;

//    fChain->GetEntry(0);
//    auto& calib = E16ANA_CalibDBManager::Instance();
//    calib.SetRunID(run_id);
//    auto trigger_param = new E16ANA_TriggerCalibParam();
//    trigger_param->ReadConstantData(calib.CurrentRunID());
//    bool TrigIsAWmax = trigger_param->IsMaximumWidth();
//    int TrigAWmax = trigger_param->MaximumWidth();
//    int TrigAWmin = trigger_param->MinimumWidth();
//    int TrigTW = trigger_param->TimeWidth();
//    if(!TrigIsAWmax){TrigAWmax=10000;}
//    std::cout<<"Trig:"<<run_id<<" "<<TrigAWmin<<" "<<TrigAWmax<<" "<<TrigTW<<std::endl;

//    int nevent=0;
//    for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
//       Long64_t ientry = LoadTree(jentry);
//       if (ientry < 0) break;
//       nb = fChain->GetEntry(jentry);   nbytes += nb;

//       if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
//       if( maxevent!=-1&&nevent>maxevent ){break;}





//       nevent++;
//    }//event loop

// }
