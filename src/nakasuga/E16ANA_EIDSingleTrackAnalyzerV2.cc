#define E16ANA_EIDSingleTrackAnalyzerV2_cxx
#include "E16ANA_EIDSingleTrackAnalyzerV2.hh"
#include "E16ANA_EIDSingleTrackAnalyzer.hh"
#include "E16ANA_LGProjection.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_TrackAnalyzerFromTreeV2.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_TrackConstant.hh"
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

double GTRTrgPosY(int cid){
  return (double)cid*300./24.-150.+6.25;
}
double HBDTrgPosX(int cid){
  int cidx = cid%10;
  return (double)cidx*600./6.-300.+50.;
}
double HBDTrgPosY(int cid){
  int cidy = cid/10;
  return (double)cidy*600./6.-300.+50.;
}

void E16ANA_EIDSingleTrackAnalyzerV2::Loop()
{
//   In a ROOT session, you can do:
//      root> .L E16ANA_EIDSingleTrackAnalyzerV2.C
//      root> E16ANA_EIDSingleTrackAnalyzerV2 t
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

void E16ANA_EIDSingleTrackAnalyzerV2::TrackMatchOnlineOffline(int maxevent, char* out_file_name)
{
   if (fChain == 0) return;

   TFile* fout = new TFile(out_file_name,"recreate");
   TTree* tree = new TTree("tree","tree");

   Int_t           out_run_id;
   Int_t           out_event_id;
   Int_t           out_spill_id;
   Int_t out_n_tracks;
   vector<int> out_track_id;
   vector<double> out_chi_square;
   vector<int> out_rk_charge;
   vector<double> out_track_mom;
   vector<double> out_track_mom_x;
   vector<double> out_track_mom_y;
   vector<double> out_track_mom_z;
   vector<int> out_track_tgt_id;
   vector<double> out_track_vtx_x;
   vector<double> out_track_vtx_y;
   vector<double> out_track_vtx_z;
   vector<int> out_track_lg_is_crossed;
   vector<int> out_track_lg_mid;
   vector<int> out_track_lg_cid;
   vector<bool> out_track_lg_trghit;
   vector<vector<double>> out_track_lg_trghit_t;
   vector<bool> out_track_lg_trgtrack;
   vector<bool> out_track_lg_hit;
   vector<vector<double>> out_track_lg_hit_t;
   vector<vector<double>> out_track_lg_resx;
   vector<vector<double>> out_track_lg_resy;
   vector<int> out_track_hbd_is_crossed;
   vector<int> out_track_hbd_mid;
   vector<int> out_track_hbd_cid;
   vector<bool> out_track_hbd_trghit;
   vector<vector<double>> out_track_hbd_trghit_t;
   vector<bool> out_track_hbd_trgtrack;
   vector<bool> out_track_hbd_hit;
   vector<vector<double>> out_track_hbd_hit_t;
   vector<vector<double>> out_track_hbd_resx;
   vector<vector<double>> out_track_hbd_resy;
   vector<int> out_track_gtr_is_crossed;
   vector<int> out_track_gtr_mid;
   vector<int> out_track_gtr_cid;
   vector<bool> out_track_gtr_trghit;
   vector<vector<double>> out_track_gtr_trghit_t;
   vector<bool> out_track_gtr_trgtrack;
   vector<double> out_track_gtr_hit_xt;
   vector<double> out_track_gtr_hit_yt;

   tree->Branch("run_id",&out_run_id,"run_id/I");
   tree->Branch("event_id",&out_event_id,"event_id/I");
   tree->Branch("spill_id",&out_spill_id,"spill_id/I");
   tree->Branch("n_tracks",&out_n_tracks,"n_tracks/I");
   tree->Branch("track_id", &out_track_id);
   tree->Branch("chi_square", &out_chi_square);
   tree->Branch("rk_charge", &out_rk_charge);
   tree->Branch("track_mom", &out_track_mom);
   tree->Branch("track_mom_x", &out_track_mom_x);
   tree->Branch("track_mom_y", &out_track_mom_y);
   tree->Branch("track_mom_z", &out_track_mom_z);
   tree->Branch("track_tgt_id", &out_track_tgt_id);
   tree->Branch("track_vtx_x", &out_track_vtx_x);
   tree->Branch("track_vtx_y", &out_track_vtx_y);
   tree->Branch("track_vtx_z", &out_track_vtx_z);
   tree->Branch("track_lg_is_crossed", &out_track_lg_is_crossed);
   tree->Branch("track_lg_mid", &out_track_lg_mid);
   tree->Branch("track_lg_cid", &out_track_lg_cid);
   tree->Branch("track_lg_trghit", &out_track_lg_trghit);
   tree->Branch("track_lg_trghit_t", &out_track_lg_trghit_t);
   tree->Branch("track_lg_trgtrack", &out_track_lg_trgtrack);
   tree->Branch("track_lg_hit", &out_track_lg_hit);
   tree->Branch("track_lg_hit_t", &out_track_lg_hit_t);
   tree->Branch("track_lg_resx", &out_track_lg_resx);
   tree->Branch("track_lg_resy", &out_track_lg_resy);
   tree->Branch("track_hbd_is_crossed", &out_track_hbd_is_crossed);
   tree->Branch("track_hbd_mid", &out_track_hbd_mid);
   tree->Branch("track_hbd_cid", &out_track_hbd_cid);
   tree->Branch("track_hbd_trghit", &out_track_hbd_trghit);
   tree->Branch("track_hbd_trghit_t", &out_track_hbd_trghit_t);
   tree->Branch("track_hbd_trgtrack", &out_track_hbd_trgtrack);
   tree->Branch("track_hbd_hit", &out_track_hbd_hit);
   tree->Branch("track_hbd_hit_t", &out_track_hbd_hit_t);
   tree->Branch("track_hbd_resx", &out_track_hbd_resx);
   tree->Branch("track_hbd_resy", &out_track_hbd_resy);
   tree->Branch("track_gtr_is_crossed", &out_track_gtr_is_crossed);
   tree->Branch("track_gtr_mid", &out_track_gtr_mid);
   tree->Branch("track_gtr_cid", &out_track_gtr_cid);
   tree->Branch("track_gtr_trghit", &out_track_gtr_trghit);
   tree->Branch("track_gtr_trghit_t", &out_track_gtr_trghit_t);
   tree->Branch("track_gtr_trgtrack", &out_track_gtr_trgtrack);
   tree->Branch("track_gtr_hit_xt", &out_track_gtr_hit_xt);
   tree->Branch("track_gtr_hit_yt", &out_track_gtr_hit_yt);

   // E16ANA_HBDDeadChannel hbddch;
   // std::string hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0c-220114.dat";
   // if(runoption==0){
   //   hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0b-220114.dat";
   // }
   // hbddch.ReadFile(hbd_deadch_file.c_str());

   // auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
   // E16ANA_GeometryV2::SetGlobalPointer(geometry);
   // auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
   // bfield_map->Initialize_binary();
   // E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
   // E16ANA_MultiTrack pair_fitter(bfield_map, geometry, 2);

   Long64_t n_entries = fChain->GetEntries();
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

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

   E16ANA_LGProjection proj;

   int nevent=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if( E16ANA_EIDSingleTrackAnalyzer::KsRunPurpose(run_id) != 16 ) continue;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
      if( maxevent!=-1&&nevent>maxevent ){break;}

      out_track_id.clear();
      out_chi_square.clear();
      out_rk_charge.clear();
      out_track_mom.clear();
      out_track_mom_x.clear();
      out_track_mom_y.clear();
      out_track_mom_z.clear();
      out_track_tgt_id.clear();
      out_track_vtx_x.clear();
      out_track_vtx_y.clear();
      out_track_vtx_z.clear();
      out_track_lg_is_crossed.clear();
      out_track_lg_mid.clear();
      out_track_lg_cid.clear();
      out_track_lg_trghit.clear();
      out_track_lg_trghit_t.clear();
      out_track_lg_trgtrack.clear();
      out_track_lg_hit.clear();
      out_track_lg_hit_t.clear();
      out_track_lg_resx.clear();
      out_track_lg_resy.clear();
      out_track_hbd_is_crossed.clear();
      out_track_hbd_mid.clear();
      out_track_hbd_cid.clear();
      out_track_hbd_trghit.clear();
      out_track_hbd_trghit_t.clear();
      out_track_hbd_trgtrack.clear();
      out_track_hbd_hit.clear();
      out_track_hbd_hit_t.clear();
      out_track_hbd_resx.clear();
      out_track_hbd_resy.clear();
      out_track_gtr_is_crossed.clear();
      out_track_gtr_mid.clear();
      out_track_gtr_cid.clear();
      out_track_gtr_trghit.clear();
      out_track_gtr_trghit_t.clear();
      out_track_gtr_trgtrack.clear();
      out_track_gtr_hit_xt.clear();
      out_track_gtr_hit_yt.clear();

      int ntrkacc = 0;
      int ntracks = track_id->size();
      for(int itrack=0;itrack<ntracks;itrack++){
	TVector3 initvtx;
	TVector3 initmom;
	int tgtid = CalcTargetId(itrack, initvtx, initmom);
	proj.SetInitInfo(initvtx, initmom, rk_charge->at(itrack));
	bool ll = proj.CalcCrossInfo();
	int lmid = proj.Module();
	int lcid = proj.Block();
	bool gg = proj.TrgGTR();
	int gmid = proj.TrgGTRMid();
	int gcid = proj.TrgGTRCid();
	bool hh = proj.TrgHBD();
	int hmid = proj.TrgHBDMid();
	int hcid = proj.TrgHBDCid();

      	// double cog[2] = {trk_hbd_lx,trk_hbd_ly};
      	// int hbd_padid = E16ANA_HBDGeometry::GetPadIDWLocalCoordinate(trk_hbd_mid,cog);
      	// if( hbddch.Status(trk_hbd_mid,hbd_padid) != 0 ) continue;

	if( chi_square->at(itrack)>10 ) continue;
	if( !ll || !hh || !gg ) continue;

	bool ltrghit = false;
	bool htrghit = false;
	bool gtrghit = false;
	out_track_lg_trghit_t.push_back(vector<double>());
	for(int il=0;il<n_trg_lg_hits;il++){
	  if( trg_lg_hit_mid->at(il)==lmid && trg_lg_hit_cid->at(il)==lcid ){
	    ltrghit = true;
	    out_track_lg_trghit_t[ntrkacc].push_back( trg_lg_hit_t->at(il) );
	  }
	}
	out_track_hbd_trghit_t.push_back(vector<double>());
	for(int ih=0;ih<n_trg_hbd_hits;ih++){
	  if( trg_hbd_hit_mid->at(ih)==hmid && trg_hbd_hit_cid->at(ih)==hcid ){
	    htrghit = true;
	    out_track_hbd_trghit_t[ntrkacc].push_back( trg_hbd_hit_t->at(ih) );
	  }
	}
	out_track_gtr_trghit_t.push_back(vector<double>());
	for(int ig=0;ig<n_trg_gtr_hits;ig++){
	  if( trg_gtr_hit_mid->at(ig)==gmid && trg_gtr_hit_cid->at(ig)==gcid ){
	    gtrghit = true;
	    out_track_gtr_trghit_t[ntrkacc].push_back( trg_gtr_hit_t->at(ig) );
	  }
	}

	bool ltrk = false;
	bool htrk = false;
	bool gtrk = false;
	for(int it=0;it<n_trg_tracks;it++){
	  if( trg_track_lg_mid->at(it)==lmid && trg_track_lg_cid->at(it)==lcid ){
	    ltrk = true;
	  }
	  for(int ih=0;ih<trg_track_n_hbd_hits->at(it);ih++){
	    if( trg_track_hbd_mid->at(it).at(ih)==hmid && trg_track_hbd_cid->at(it).at(ih)==hcid ){
	      htrk = true;
	      break;
	    }
	  }
	  for(int ig=0;ig<trg_track_n_gtr_hits->at(it);ig++){
	    if( trg_track_gtr_mid->at(it).at(ig)==gmid && trg_track_gtr_cid->at(it).at(ig)==gcid ){
	      gtrk = true;
	      break;
	    }
	  }
	}

	bool lhit = false;
	double widthlg = 100.;
	out_track_lg_hit_t.push_back(vector<double>());
	out_track_lg_resx.push_back(vector<double>());
	out_track_lg_resy.push_back(vector<double>());
	for(int il=0;il<n_lg_hits;il++){
	  if( lg_hit_fflag->at(il)>1 ) continue;
	  if( lg_hit_mid->at(il) != lmid ) continue;
	  double resx = lg_hit_x->at(il) - proj.LCross1_x();
	  double resy = lg_hit_y->at(il) - proj.LCross1_y();
	  if( fabs(resx)<widthlg ){
	    out_track_lg_resy[ntrkacc].push_back( resy );
	  }
	  if( fabs(resy)<widthlg ){
	    out_track_lg_resx[ntrkacc].push_back( resx );
	  }
	  if( fabs(resx)<widthlg && fabs(resy)<widthlg ){
	    lhit = true;
	    out_track_lg_hit_t[ntrkacc].push_back( lg_hit_t->at(il) );
	  }
	}
	bool hhit = false;
	double widthhbd = 25.;
	out_track_hbd_hit_t.push_back(vector<double>());
	out_track_hbd_resx.push_back(vector<double>());
	out_track_hbd_resy.push_back(vector<double>());
	for(int ih=0;ih<n_hbd_clusters;ih++){
	  if( hbd_cluster_t->at(ih)>200 ) continue;
	  if( hbd_cluster_mid->at(ih) != hmid ) continue;
	  double resx = hbd_cluster_x->at(ih) - proj.HBDLCross_x();
	  double resy = hbd_cluster_y->at(ih) - proj.HBDLCross_y();
	  if( fabs(resx)<widthhbd ){
	    out_track_hbd_resy[ntrkacc].push_back( resy );
	  }
	  if( fabs(resy)<widthhbd ){
	    out_track_hbd_resx[ntrkacc].push_back( resx );
	  }
	  if( fabs(resx)<widthhbd && fabs(resy)<widthhbd ){
	    hhit = true;
	    out_track_hbd_hit_t[ntrkacc].push_back( hbd_cluster_t->at(ih) );
	  }
	}

	double gtrxt = rk_hit_gtr300_xt->at(itrack);
	double gtryt = rk_hit_gtr300_yt->at(itrack);

	out_track_id.push_back(track_id->at(itrack));
	out_chi_square.push_back(chi_square->at(itrack));
	out_rk_charge.push_back(rk_charge->at(itrack));
	out_track_mom.push_back(initmom.Mag());
	out_track_mom_x.push_back(initmom.X());
	out_track_mom_y.push_back(initmom.Y());
	out_track_mom_z.push_back(initmom.Z());
	out_track_tgt_id.push_back(tgtid);
	out_track_vtx_x.push_back(initvtx.X());
	out_track_vtx_y.push_back(initvtx.Y());
	out_track_vtx_z.push_back(initvtx.Z());

	out_track_lg_is_crossed.push_back(ll);
	out_track_lg_mid.push_back(lmid);
	out_track_lg_cid.push_back(lcid);
	out_track_lg_trghit.push_back(ltrghit);
	out_track_lg_trgtrack.push_back(ltrk);
	out_track_lg_hit.push_back(lhit);
	out_track_hbd_is_crossed.push_back(hh);
	out_track_hbd_mid.push_back(hmid);
	out_track_hbd_cid.push_back(hcid);
	out_track_hbd_trghit.push_back(htrghit);
	out_track_hbd_trgtrack.push_back(htrk);
	out_track_hbd_hit.push_back(hhit);
	out_track_gtr_is_crossed.push_back(gg);
	out_track_gtr_mid.push_back(gmid);
	out_track_gtr_cid.push_back(gcid);
	out_track_gtr_trghit.push_back(gtrghit);
	out_track_gtr_trgtrack.push_back(gtrk);
	out_track_gtr_hit_xt.push_back(gtrxt);
	out_track_gtr_hit_yt.push_back(gtryt);

	ntrkacc++;

      }//track loop


      //Get Hits & Clusters
      out_n_tracks = ntrkacc;
      out_run_id = run_id;
      out_event_id = event_id;
      out_spill_id = spill_id;

      tree->Fill();

      nevent++;
   }//event loop

   fout->Write();
   fout->Close();

}

void E16ANA_EIDSingleTrackAnalyzerV2::TrackMatchOfflineOnline(int maxevent, char* out_file_name)
{
   if (fChain == 0) return;

   TFile* fout = new TFile(out_file_name,"recreate");
   TTree* tree = new TTree("tree","tree");

   Int_t           out_run_id;
   Int_t           out_event_id;
   Int_t           out_spill_id;
   Int_t out_n_trg_tracks;
   Int_t out_n_trg_tracks_wgtroff;
   Int_t out_n_trg_tracks_whbdoff;
   Int_t out_n_trg_tracks_wlgoff;
   Int_t out_n_trg_tracks_walloff;
   Int_t out_n_ssd_clusters_cand;
   Int_t out_n_gtr100x_clusters_cand;
   Int_t out_n_gtr100y_clusters_cand;
   Int_t out_n_gtr200x_clusters_cand;
   Int_t out_n_gtr200y_clusters_cand;
   Int_t out_n_gtr300x_clusters_cand;
   Int_t out_n_gtr300y_clusters_cand;
   vector<int> out_trg_track_id;
   vector<int> out_trg_track_lg_mid;
   vector<int> out_trg_track_lg_cid;
   vector<double> out_trg_track_lg_x;// not in branch
   vector<double> out_trg_track_lg_y;// not in branch
   vector<double> out_trg_track_lg_t;
   vector<int> out_trg_track_hbd_mid;
   vector<int> out_trg_track_hbd_cid;
   vector<double> out_trg_track_hbd_t;
   vector<int> out_trg_track_gtr_mid;
   vector<int> out_trg_track_gtr_cid;
   vector<double> out_trg_track_gtr_t;
   vector<int> out_trg_track_inc_n_lg_hits;
   vector<vector<double>> out_trg_track_inc_lg_lx;
   vector<vector<double>> out_trg_track_inc_lg_ly;
   vector<vector<double>> out_trg_track_inc_lg_t;
   vector<int> out_trg_track_inc_n_hbd_hits;
   vector<vector<double>> out_trg_track_inc_hbd_lx;
   vector<vector<double>> out_trg_track_inc_hbd_ly;
   vector<vector<double>> out_trg_track_inc_hbd_t;
   vector<int> out_trg_track_inc_n_gtr_hits;
   vector<vector<double>> out_trg_track_inc_gtr_lx;
   vector<vector<double>> out_trg_track_inc_gtr_ly;
   vector<vector<double>> out_trg_track_inc_gtr_t;
   vector<int> out_trg_track_n_match_gtr;
   vector<int> out_trg_track_n_match_hbd;
   vector<int> out_trg_track_n_match_lg;
   vector<int> out_trg_track_n_match;
   vector<vector<double>> out_trg_track_match_id;
   Int_t out_n_tracks;
   Int_t out_n_tracks_whbd;
   Int_t out_n_tracks_wlg;
   Int_t out_n_tracks_wall;
   vector<int> out_track_id;
   vector<int> out_track_index;
   vector<double> out_chi_square;
   vector<int> out_rk_charge;
   vector<double> out_track_mom;
   vector<double> out_track_mom_x;
   vector<double> out_track_mom_y;
   vector<double> out_track_mom_z;
   vector<int> out_track_tgt_id;
   vector<double> out_track_vtx_x;
   vector<double> out_track_vtx_y;
   vector<double> out_track_vtx_z;
   vector<int> out_track_gtr_mid;
   vector<int> out_track_gtr_cid;
   vector<double> out_track_gtr_lx;
   vector<double> out_track_gtr_ly;
   vector<double> out_track_gtr_xt;
   vector<double> out_track_gtr_yt;
   vector<double> out_track_gtr_adc;
   vector<int> out_track_hbd_mid;
   vector<int> out_track_hbd_cid;
   vector<double> out_track_hbd_lx;
   vector<double> out_track_hbd_ly;
   vector<double> out_track_hbd_nearx;
   vector<double> out_track_hbd_neary;
   vector<vector<double>> out_track_inc_hbd_lx;
   vector<vector<double>> out_track_inc_hbd_ly;
   vector<vector<double>> out_track_inc_hbd_t;
   vector<vector<double>> out_track_inc_hbd_adc;
   vector<int> out_track_lg_mid;
   vector<int> out_track_lg_cid;
   vector<double> out_track_lg_lx;
   vector<double> out_track_lg_ly;
   vector<double> out_track_lg_nearx;
   vector<double> out_track_lg_neary;
   vector<vector<double>> out_track_inc_lg_lx;
   vector<vector<double>> out_track_inc_lg_ly;
   vector<vector<double>> out_track_inc_lg_t;
   vector<vector<double>> out_track_inc_lg_adc;

   tree->Branch("run_id",&out_run_id,"run_id/I");
   tree->Branch("event_id",&out_event_id,"event_id/I");
   tree->Branch("spill_id",&out_spill_id,"spill_id/I");
   tree->Branch("n_trg_tracks",&out_n_trg_tracks,"n_trg_tracks/I");
   tree->Branch("n_trg_tracks_wgtroff",&out_n_trg_tracks_wgtroff,"n_trg_tracks_wgtroff/I");
   tree->Branch("n_trg_tracks_whbdoff",&out_n_trg_tracks_whbdoff,"n_trg_tracks_whbdoff/I");
   tree->Branch("n_trg_tracks_wlgoff",&out_n_trg_tracks_wlgoff,"n_trg_tracks_wlgoff/I");
   tree->Branch("n_trg_tracks_walloff",&out_n_trg_tracks_walloff,"n_trg_tracks_walloff/I");
   tree->Branch("n_ssd_clusters_cand",&out_n_ssd_clusters_cand,"n_ssd_clusters_cand/I");
   tree->Branch("n_gtr100x_clusters_cand",&out_n_gtr100x_clusters_cand,"n_gtr100x_clusters_cand/I");
   tree->Branch("n_gtr100y_clusters_cand",&out_n_gtr100y_clusters_cand,"n_gtr100y_clusters_cand/I");
   tree->Branch("n_gtr200x_clusters_cand",&out_n_gtr200x_clusters_cand,"n_gtr200x_clusters_cand/I");
   tree->Branch("n_gtr200y_clusters_cand",&out_n_gtr200y_clusters_cand,"n_gtr200y_clusters_cand/I");
   tree->Branch("n_gtr300x_clusters_cand",&out_n_gtr300x_clusters_cand,"n_gtr300x_clusters_cand/I");
   tree->Branch("n_gtr300y_clusters_cand",&out_n_gtr300y_clusters_cand,"n_gtr300y_clusters_cand/I");
   tree->Branch("trg_track_id", &out_trg_track_id);
   tree->Branch("trg_track_lg_mid", &out_trg_track_lg_mid);
   tree->Branch("trg_track_lg_cid", &out_trg_track_lg_cid);
   tree->Branch("trg_track_lg_t", &out_trg_track_lg_t);
   tree->Branch("trg_track_hbd_mid", &out_trg_track_hbd_mid);
   tree->Branch("trg_track_hbd_cid", &out_trg_track_hbd_cid);
   tree->Branch("trg_track_hbd_t", &out_trg_track_hbd_t);
   tree->Branch("trg_track_gtr_mid", &out_trg_track_gtr_mid);
   tree->Branch("trg_track_gtr_cid", &out_trg_track_gtr_cid);
   tree->Branch("trg_track_gtr_t", &out_trg_track_gtr_t);
   tree->Branch("trg_track_inc_n_lg_hits", &out_trg_track_inc_n_lg_hits);
   tree->Branch("trg_track_inc_lg_lx", &out_trg_track_inc_lg_lx);
   tree->Branch("trg_track_inc_lg_ly", &out_trg_track_inc_lg_ly);
   tree->Branch("trg_track_inc_lg_t", &out_trg_track_inc_lg_t);
   tree->Branch("trg_track_inc_n_hbd_hits", &out_trg_track_inc_n_hbd_hits);
   tree->Branch("trg_track_inc_hbd_lx", &out_trg_track_inc_hbd_lx);
   tree->Branch("trg_track_inc_hbd_ly", &out_trg_track_inc_hbd_ly);
   tree->Branch("trg_track_inc_hbd_t", &out_trg_track_inc_hbd_t);
   tree->Branch("trg_track_inc_n_gtr_hits", &out_trg_track_inc_n_gtr_hits);
   tree->Branch("trg_track_inc_gtr_lx", &out_trg_track_inc_gtr_lx);
   tree->Branch("trg_track_inc_gtr_ly", &out_trg_track_inc_gtr_ly);
   tree->Branch("trg_track_inc_gtr_t", &out_trg_track_inc_gtr_t);
   tree->Branch("trg_track_n_match_gtr", &out_trg_track_n_match_gtr);
   tree->Branch("trg_track_n_match_hbd", &out_trg_track_n_match_hbd);
   tree->Branch("trg_track_n_match_lg", &out_trg_track_n_match_lg);
   tree->Branch("trg_track_n_match", &out_trg_track_n_match);
   tree->Branch("trg_track_match_id", &out_trg_track_match_id);
   tree->Branch("n_tracks",&out_n_tracks,"n_tracks/I");
   tree->Branch("n_tracks_whbd",&out_n_tracks_whbd,"n_tracks_whbd/I");
   tree->Branch("n_tracks_wlg",&out_n_tracks_wlg,"n_tracks_wlg/I");
   tree->Branch("n_tracks_wall",&out_n_tracks_wall,"n_tracks_wall/I");
   tree->Branch("track_id", &out_track_id);
   tree->Branch("track_index", &out_track_index);
   tree->Branch("chi_square", &out_chi_square);
   tree->Branch("rk_charge", &out_rk_charge);
   tree->Branch("track_mom", &out_track_mom);
   tree->Branch("track_mom_x", &out_track_mom_x);
   tree->Branch("track_mom_y", &out_track_mom_y);
   tree->Branch("track_mom_z", &out_track_mom_z);
   tree->Branch("track_tgt_id", &out_track_tgt_id);
   tree->Branch("track_vtx_x", &out_track_vtx_x);
   tree->Branch("track_vtx_y", &out_track_vtx_y);
   tree->Branch("track_vtx_z", &out_track_vtx_z);
   tree->Branch("track_gtr_mid", &out_track_gtr_mid);
   tree->Branch("track_gtr_cid", &out_track_gtr_cid);
   tree->Branch("track_gtr_lx", &out_track_gtr_lx);
   tree->Branch("track_gtr_ly", &out_track_gtr_ly);
   tree->Branch("track_gtr_xt", &out_track_gtr_xt);
   tree->Branch("track_gtr_yt", &out_track_gtr_yt);
   tree->Branch("track_gtr_adc", &out_track_gtr_adc);
   tree->Branch("track_hbd_mid", &out_track_hbd_mid);
   tree->Branch("track_hbd_cid", &out_track_hbd_cid);
   tree->Branch("track_hbd_lx", &out_track_hbd_lx);
   tree->Branch("track_hbd_ly", &out_track_hbd_ly);
   tree->Branch("track_hbd_nearx", &out_track_hbd_nearx);
   tree->Branch("track_hbd_neary", &out_track_hbd_neary);
   tree->Branch("track_inc_hbd_lx", &out_track_inc_hbd_lx);
   tree->Branch("track_inc_hbd_ly", &out_track_inc_hbd_ly);
   tree->Branch("track_inc_hbd_t", &out_track_inc_hbd_t);
   tree->Branch("track_inc_hbd_adc", &out_track_inc_hbd_adc);
   tree->Branch("track_lg_mid", &out_track_lg_mid);
   tree->Branch("track_lg_cid", &out_track_lg_cid);
   tree->Branch("track_lg_lx", &out_track_lg_lx);
   tree->Branch("track_lg_ly", &out_track_lg_ly);
   tree->Branch("track_lg_nearx", &out_track_lg_nearx);
   tree->Branch("track_lg_neary", &out_track_lg_neary);
   tree->Branch("track_inc_lg_lx", &out_track_inc_lg_lx);
   tree->Branch("track_inc_lg_ly", &out_track_inc_lg_ly);
   tree->Branch("track_inc_lg_t", &out_track_inc_lg_t);
   tree->Branch("track_inc_lg_adc", &out_track_inc_lg_adc);

   TH1F* hgtry = new TH1F("hgtry","hgtry",100,-400,400);
   TH1F* hhbdx = new TH1F("hhbdx","hhbdx",100,-600,600);
   TH1F* hhbdy = new TH1F("hhbdy","hhbdy",100,-600,600);
   TH1F* hlgx  = new TH1F("hlgx" ,"hlgx" ,100,-800,800);
   TH1F* hlgy  = new TH1F("hlgy" ,"hlgy" ,100,-800,800);
   TH1F* hgtrym = new TH1F("hgtrym","hgtrym",100,-400,400);
   TH1F* hhbdxm = new TH1F("hhbdxm","hhbdxm",100,-600,600);
   TH1F* hhbdym = new TH1F("hhbdym","hhbdym",100,-600,600);
   TH1F* hlgxm  = new TH1F("hlgxm" ,"hlgxm" ,100,-800,800);
   TH1F* hlgym  = new TH1F("hlgym" ,"hlgym" ,100,-800,800);
   std::vector<double> gtr300y_cluster_y_before;
   std::vector<double> hbd_cluster_x_before;
   std::vector<double> hbd_cluster_y_before;
   std::vector<double> lg_hit_x_before;
   std::vector<double> lg_hit_y_before;
   int n_all_trg_tracks[5] = {0};
   int n_asc_trg_tracks[5] = {0};
   int n_asc_trg_tracks_alldet = 0;
   // double width[5] = {8., 50., 50., 40., 40.};//half
   double width[5] = {32., 80., 80., 40., 40.};//half

   // E16ANA_HBDDeadChannel hbddch;
   // std::string hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0c-220114.dat";
   // if(runoption==0){
   //   hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0b-220114.dat";
   // }
   // hbddch.ReadFile(hbd_deadch_file.c_str());

   auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
   // E16ANA_GeometryV2::SetGlobalPointer(geometry);
   // auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
   // bfield_map->Initialize_binary();
   // E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
   // E16ANA_MultiTrack pair_fitter(bfield_map, geometry, 2);

   Long64_t n_entries = fChain->GetEntries();
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

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

   E16ANA_LGProjection proj;

   int nevent=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if( E16ANA_EIDSingleTrackAnalyzer::KsRunPurpose(run_id) != 16 ) continue;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
      if( maxevent!=-1&&nevent>maxevent ){break;}

      out_trg_track_id.clear();
      out_trg_track_lg_mid.clear();
      out_trg_track_lg_cid.clear();
      out_trg_track_lg_x.clear();//
      out_trg_track_lg_y.clear();//
      out_trg_track_lg_t.clear();
      out_trg_track_hbd_mid.clear();
      out_trg_track_hbd_cid.clear();
      out_trg_track_hbd_t.clear();
      out_trg_track_gtr_mid.clear();
      out_trg_track_gtr_cid.clear();
      out_trg_track_gtr_t.clear();
      out_trg_track_inc_n_lg_hits.clear();
      out_trg_track_inc_lg_lx.clear();
      out_trg_track_inc_lg_ly.clear();
      out_trg_track_inc_lg_t.clear();
      out_trg_track_inc_n_hbd_hits.clear();
      out_trg_track_inc_hbd_lx.clear();
      out_trg_track_inc_hbd_ly.clear();
      out_trg_track_inc_hbd_t.clear();
      out_trg_track_inc_n_gtr_hits.clear();
      out_trg_track_inc_gtr_lx.clear();
      out_trg_track_inc_gtr_ly.clear();
      out_trg_track_inc_gtr_t.clear();
      out_trg_track_n_match_gtr.clear();
      out_trg_track_n_match_hbd.clear();
      out_trg_track_n_match_lg.clear();
      out_trg_track_n_match.clear();
      out_trg_track_match_id.clear();
      out_track_id.clear();
      out_track_index.clear();
      out_chi_square.clear();
      out_rk_charge.clear();
      out_track_mom.clear();
      out_track_mom_x.clear();
      out_track_mom_y.clear();
      out_track_mom_z.clear();
      out_track_tgt_id.clear();
      out_track_vtx_x.clear();
      out_track_vtx_y.clear();
      out_track_vtx_z.clear();
      out_track_gtr_mid.clear();
      out_track_gtr_cid.clear();
      out_track_gtr_lx.clear();
      out_track_gtr_ly.clear();
      out_track_gtr_xt.clear();
      out_track_gtr_yt.clear();
      out_track_gtr_adc.clear();
      out_track_hbd_mid.clear();
      out_track_hbd_cid.clear();
      out_track_hbd_lx.clear();
      out_track_hbd_ly.clear();
      out_track_hbd_nearx.clear();
      out_track_hbd_neary.clear();
      out_track_inc_hbd_lx.clear();
      out_track_inc_hbd_ly.clear();
      out_track_inc_hbd_t.clear();
      out_track_inc_hbd_adc.clear();
      out_track_lg_mid.clear();
      out_track_lg_cid.clear();
      out_track_lg_lx.clear();
      out_track_lg_ly.clear();
      out_track_lg_nearx.clear();
      out_track_lg_neary.clear();
      out_track_inc_lg_lx.clear();
      out_track_inc_lg_ly.clear();
      out_track_inc_lg_t.clear();
      out_track_inc_lg_adc.clear();

      //offline
      int ntrkacc = 0;
      int ntrkacc_whbd = 0;
      int ntrkacc_wlg = 0;
      int ntrkacc_wall = 0;
      int ntracks = track_id->size();
      for(int itrack=0;itrack<ntracks;itrack++){
	TVector3 initvtx;
	TVector3 initmom;
	int tgtid = CalcTargetId(itrack, initvtx, initmom);
	proj.SetInitInfo(initvtx, initmom, rk_charge->at(itrack));
	bool ll = proj.CalcCrossInfo();
	int lmid = proj.Module();
	int lcid = proj.Block();
	bool gg = proj.TrgGTR();
	int gmid = proj.TrgGTRMid();
	int gcid = proj.TrgGTRCid();
	bool hh = proj.TrgHBD();
	int hmid = proj.TrgHBDMid();
	int hcid = proj.TrgHBDCid();

	// if( chi_square->at(itrack)>50 ) continue;
	// if( !ll || !hh || !gg ) continue;

	bool hhit = false;
	double widthhbd = 25.;
	double resxhbd = -10000.;
	double resyhbd = -10000.;
	out_track_inc_hbd_lx.push_back(vector<double>());
	out_track_inc_hbd_ly.push_back(vector<double>());
	out_track_inc_hbd_t.push_back(vector<double>());
	out_track_inc_hbd_adc.push_back(vector<double>());
	for(int ih=0;ih<n_hbd_clusters;ih++){
	  if( hbd_cluster_t->at(ih)>200 ) continue;
	  if( hbd_cluster_mid->at(ih) != hmid ) continue;
	  double resx = hbd_cluster_x->at(ih) - proj.HBDLCross_x();
	  double resy = hbd_cluster_y->at(ih) - proj.HBDLCross_y();
	  if( fabs(resx)<widthhbd && fabs(resy)<widthhbd ){
	    hhit = true;
	    out_track_inc_hbd_lx[ntrkacc].push_back( hbd_cluster_x->at(ih) );
	    out_track_inc_hbd_ly[ntrkacc].push_back( hbd_cluster_y->at(ih) );
	    out_track_inc_hbd_t[ntrkacc].push_back( hbd_cluster_t->at(ih) );
	    out_track_inc_hbd_adc[ntrkacc].push_back( hbd_cluster_adc->at(ih) );
	    if( resx*resx+resy*resy < resxhbd*resxhbd+resyhbd*resyhbd ){
	      resxhbd = resx;
	      resyhbd = resy;
	    }
	  }
	}

	bool lhit = false;
	double widthlg = 100.;
	double resxlg = -10000.;
	double resylg = -10000.;
	out_track_inc_lg_lx.push_back(vector<double>());
	out_track_inc_lg_ly.push_back(vector<double>());
	out_track_inc_lg_t.push_back(vector<double>());
	out_track_inc_lg_adc.push_back(vector<double>());
	for(int il=0;il<n_lg_hits;il++){
	  if( lg_hit_fflag->at(il)>1 ) continue;
	  if( lg_hit_mid->at(il) != lmid ) continue;
	  double resx = lg_hit_x->at(il) - proj.LCross1_x();
	  double resy = lg_hit_y->at(il) - proj.LCross1_y();
	  if( fabs(resx)<widthlg && fabs(resy)<widthlg ){
	    lhit = true;
	    out_track_inc_lg_lx[ntrkacc].push_back( lg_hit_x->at(il) );
	    out_track_inc_lg_ly[ntrkacc].push_back( lg_hit_y->at(il) );
	    out_track_inc_lg_t[ntrkacc].push_back( lg_hit_t->at(il) );
	    out_track_inc_lg_adc[ntrkacc].push_back( lg_hit_adc->at(il) );
	    if( resx*resx+resy*resy < resxlg*resxlg+resylg*resylg ){
	      resxlg = resx;
	      resylg = resy;
	    }
	  }
	}

	out_track_id.push_back(track_id->at(itrack));
	out_track_index.push_back(itrack);
	out_chi_square.push_back(chi_square->at(itrack));
	out_rk_charge.push_back(rk_charge->at(itrack));
	out_track_mom.push_back(initmom.Mag());
	out_track_mom_x.push_back(initmom.X());
	out_track_mom_y.push_back(initmom.Y());
	out_track_mom_z.push_back(initmom.Z());
	out_track_tgt_id.push_back(tgtid);
	out_track_vtx_x.push_back(initvtx.X());
	out_track_vtx_y.push_back(initvtx.Y());
	out_track_vtx_z.push_back(initvtx.Z());
	out_track_gtr_mid.push_back( gmid );
	out_track_gtr_cid.push_back( gcid );
	out_track_gtr_lx.push_back( proj.GTRLCross_x() );
	out_track_gtr_ly.push_back( proj.GTRLCross_y() );
	out_track_gtr_xt.push_back( rk_hit_gtr300_xt->at(itrack) );
	out_track_gtr_yt.push_back( rk_hit_gtr300_yt->at(itrack) );
	out_track_hbd_mid.push_back( hmid );
	out_track_hbd_cid.push_back( hcid );
	out_track_hbd_lx.push_back( proj.HBDLCross_x() );
	out_track_hbd_ly.push_back( proj.HBDLCross_y() );
	if(hhit){
	  out_track_hbd_nearx.push_back( resxhbd + proj.HBDLCross_x() );
	  out_track_hbd_neary.push_back( resyhbd + proj.HBDLCross_y() );
	}
	else{
	  out_track_hbd_nearx.push_back( resxhbd );
	  out_track_hbd_neary.push_back( resyhbd );
	}
	out_track_lg_mid.push_back( lmid );
	out_track_lg_cid.push_back( lcid );
	out_track_lg_lx.push_back( proj.LCross1_x() );
	out_track_lg_ly.push_back( proj.LCross1_y() );
	if(lhit){
	  out_track_lg_nearx.push_back( resxlg + proj.LCross1_x() );
	  out_track_lg_neary.push_back( resylg + proj.LCross1_y() );
	}
	else{
	  out_track_lg_nearx.push_back( resxlg );
	  out_track_lg_neary.push_back( resylg );
	}

	ntrkacc++;
	if(hhit){ntrkacc_whbd++;}
	if(lhit){ntrkacc_wlg++;}
	if(hhit && lhit){ntrkacc_wall++;}

      }//track loop

      //offline hits
      int nssdcand = 0;
      for(int i=0;i<n_ssd_clusters;i++){
	if( ssd_cluster_mid->at(i)<105 ) continue;
	nssdcand++;
      }
      out_n_ssd_clusters_cand = nssdcand;
      int ng100xcand = 0;
      for(int i=0;i<n_gtr100x_clusters;i++){
	if( gtr100x_cluster_mid->at(i)<105 ) continue;
	if( gtr100x_cluster_size->at(i)<2 ) continue;
	if( gtr100x_cluster_adc->at(i)<100 ) continue;
	ng100xcand++;
      }
      out_n_gtr100x_clusters_cand = ng100xcand;
      int ng200xcand = 0;
      for(int i=0;i<n_gtr200x_clusters;i++){
	if( gtr200x_cluster_mid->at(i)<105 ) continue;
	if( gtr200x_cluster_size->at(i)<2 ) continue;
	if( gtr200x_cluster_adc->at(i)<100 ) continue;
	ng200xcand++;
      }
      out_n_gtr200x_clusters_cand = ng200xcand;
      int ng300xcand = 0;
      for(int i=0;i<n_gtr300x_clusters;i++){
	if( gtr300x_cluster_mid->at(i)<105 ) continue;
	if( gtr300x_cluster_size->at(i)<2 ) continue;
	if( gtr300x_cluster_adc->at(i)<100 ) continue;
	ng300xcand++;
      }
      out_n_gtr300x_clusters_cand = ng300xcand;
      int ng100ycand = 0;
      for(int i=0;i<n_gtr100y_clusters;i++){
	if( gtr100y_cluster_mid->at(i)<105 ) continue;
	if( gtr100y_cluster_adc->at(i)<50 ) continue;
	ng100ycand++;
      }
      out_n_gtr100y_clusters_cand = ng100ycand;
      int ng200ycand = 0;
      for(int i=0;i<n_gtr200y_clusters;i++){
	if( gtr200y_cluster_mid->at(i)<105 ) continue;
	if( gtr200y_cluster_adc->at(i)<50 ) continue;
	ng200ycand++;
      }
      out_n_gtr200y_clusters_cand = ng200ycand;
      int ng300ycand = 0;
      for(int i=0;i<n_gtr300y_clusters;i++){
	if( gtr300y_cluster_mid->at(i)<105 ) continue;
	if( gtr300y_cluster_adc->at(i)<50 ) continue;
	ng300ycand++;
      }
      out_n_gtr300y_clusters_cand = ng300ycand;

      //online
      // bug? MRPC?
      // int ntest2 = 0;
      // for(int il=0;il<n_trg_tracks;il++){
      // 	for(int ig=0;ig<trg_track_n_gtr_hits->at(il);ig++){
      // 	  if( trg_track_gtr_is_t_match->at(il).at(ig)==0 ) continue;
      // 	  for(int ih=0;ih<trg_track_n_hbd_hits->at(il);ih++){
      // 	    if( trg_track_hbd_is_t_match->at(il).at(ih)==0 ) continue;
      // 	    ntest2++;
      // 	  }
      // 	}
      // }
      // if(ntest2<2){
      // 	std::cout<<"hgmatch: "<<event_id<<" "<<ntest2<<std::endl;
      // }
      vector<bool> trgpair(n_trg_tracks, false);
      for(int i=0;i<n_trg_tracks;i++){
	for(int j=i+1;j<n_trg_tracks;j++){
	  bool istrgpair = IsTrgPair( 
	    trg_track_lg_mid->at(i), trg_track_lg_cid->at(i), trg_track_lg_t->at(i),
	    trg_track_lg_mid->at(j), trg_track_lg_cid->at(j), trg_track_lg_t->at(j),
	    TrigAWmin, TrigAWmax, TrigTW
	  );
	  if( istrgpair ){
	    trgpair.at(i)=true;
	    trgpair.at(j)=true;
	  }
	}
      }
      int ntrgtrkacc = 0;
      for(int il=0;il<n_trg_tracks;il++){
	if( !trgpair.at(il) ) continue;
	for(int ig=0;ig<trg_track_n_gtr_hits->at(il);ig++){
	  if( trg_track_gtr_is_t_match->at(il).at(ig)==0 ) continue;
	  for(int ih=0;ih<trg_track_n_hbd_hits->at(il);ih++){
	    if( trg_track_hbd_is_t_match->at(il).at(ih)==0 ) continue;
	    out_trg_track_lg_mid.push_back( trg_track_lg_mid->at(il) );
	    out_trg_track_lg_cid.push_back( trg_track_lg_cid->at(il) );
	    out_trg_track_lg_x.push_back( trg_track_lg_x->at(il) );
	    out_trg_track_lg_y.push_back( trg_track_lg_y->at(il) );
	    out_trg_track_lg_t.push_back( trg_track_lg_t->at(il) );
	    out_trg_track_hbd_mid.push_back( trg_track_hbd_mid->at(il).at(ih) );
	    out_trg_track_hbd_cid.push_back( trg_track_hbd_cid->at(il).at(ih) );
	    out_trg_track_hbd_t.push_back( trg_track_hbd_t->at(il).at(ih) );
	    out_trg_track_gtr_mid.push_back( trg_track_gtr_mid->at(il).at(ig) );
	    out_trg_track_gtr_cid.push_back( trg_track_gtr_cid->at(il).at(ig) );
	    out_trg_track_gtr_t.push_back( trg_track_gtr_t->at(il).at(ig) );
	    out_trg_track_id.push_back(ntrgtrkacc);
	    int nm = 0;
	    int nmg = 0;
	    int nmh = 0;
	    int nml = 0;
	    out_trg_track_match_id.push_back(vector<double>());
	    for(int it=0;it<out_track_id.size();it++){
	      // if( trg_track_lg_mid->at(il) == out_track_lg_mid.at(it) && 
	      // 	  trg_track_lg_cid->at(il) == out_track_lg_cid.at(it) && 
	      // 	  trg_track_hbd_mid->at(il).at(ih) == out_track_hbd_mid.at(it) && 
	      // 	  trg_track_hbd_cid->at(il).at(ih) == out_track_hbd_cid.at(it) && 
	      // 	  trg_track_gtr_mid->at(il).at(ig) == out_track_gtr_mid.at(it) && 
	      // 	  trg_track_gtr_cid->at(il).at(ig) == out_track_gtr_cid.at(it) ){
	      // 	out_trg_track_match_id[nm].push_back( out_track_id.at(it) );
	      // 	nm++;
	      // }
	      bool bgtr = false;
	      if( trg_track_gtr_mid->at(il).at(ig) == out_track_gtr_mid.at(it) ){
	      	TVector3 gtmp(rk_hit_gtr300_gx->at(out_track_index.at(it)), rk_hit_gtr300_gy->at(out_track_index.at(it)), rk_hit_gtr300_gz->at(out_track_index.at(it)));
	      	TVector3 ltmp = geometry->GTR( E16ANA_TrackConstant::ModuleID2020To2013(out_track_gtr_mid.at(it)) ,2 )->GetLPos( gtmp );
	      	double resy = ltmp.Y() - GTRTrgPosY(trg_track_gtr_cid->at(il).at(ig));
	      	if( fabs(resy)<width[0] ){
	      	  bgtr = true;
	      	  nmg++;
	      	}
	      }
	      bool bhbd = false;
	      if( trg_track_hbd_mid->at(il).at(ih) == out_track_hbd_mid.at(it) ){
	      	if( out_track_hbd_nearx.at(it) > -10000 ){
	      	  double resx = out_track_hbd_nearx.at(it) - HBDTrgPosX(trg_track_hbd_cid->at(il).at(ih));
	      	  double resy = out_track_hbd_neary.at(it) - HBDTrgPosY(trg_track_hbd_cid->at(il).at(ih));
	      	  if( fabs(resx)<width[1] && fabs(resy)<width[2] ){
	      	    bhbd = true;
	      	    nmh++;
	      	  }
	      	}
	      }
	      bool blg = false;
	      if( trg_track_lg_mid->at(il) == out_track_lg_mid.at(it) ){
		if( out_track_lg_nearx.at(it) > -10000 ){
		  double resx = out_track_lg_nearx.at(it) - trg_track_lg_x->at(il);
		  double resy = out_track_lg_neary.at(it) - trg_track_lg_y->at(il);
		  if( fabs(resx)<width[3] && fabs(resy)<width[4] ){
		    blg = true;
		    nml++;
		  }
		}
	      }
	      if(bgtr&&bhbd&&blg){
	      	out_trg_track_match_id[nm].push_back( out_track_id.at(it) );
		nm++;
	      }
	    }
	    out_trg_track_n_match.push_back(nm);
	    out_trg_track_n_match_gtr.push_back(nmg);
	    out_trg_track_n_match_hbd.push_back(nmh);
	    out_trg_track_n_match_lg.push_back(nml);
	    ntrgtrkacc++;
	  }
	}
      }
      // std::cout<<ntrgtrkacc<<std::endl;
      int n_wgtroff = 0;
      int n_whbdoff = 0;
      int n_wlgoff = 0;
      int n_walloff = 0;
      for(int i=0;i<ntrgtrkacc;i++){
	//GTR
	bool gtrisasc = false;
      	int nascgtr = 0;
      	for(int ig=0;ig<n_gtr300y_clusters;ig++){
	  out_trg_track_inc_gtr_ly.push_back(vector<double>());
	  out_trg_track_inc_gtr_t.push_back(vector<double>());
      	  if( gtr300y_cluster_adc->at(ig)<150 ) continue;
      	  if( gtr300y_cluster_mid->at(ig) != out_trg_track_gtr_mid.at(i) ) continue;
      	  // int tcid = E16ANA_EIDSingleTrackAnalyzer::GTRTrgCid( gtr300y_cluster_y->at(ig) );
	  if( gtr300y_cluster_mid->at(ig)==106 ){
	    double resy = gtr300y_cluster_y->at(ig) - GTRTrgPosY(out_trg_track_gtr_cid.at(i));
	    hgtry->Fill(resy);
	    if( fabs(resy)<width[0] ){
	      gtrisasc = true;
	      out_trg_track_inc_gtr_ly[nascgtr].push_back( gtr300y_cluster_y->at(ig) );
	      out_trg_track_inc_gtr_t[nascgtr].push_back( gtr300y_cluster_t->at(ig) );
	      nascgtr++;
	    }
	  }
      	}
      	out_trg_track_inc_n_gtr_hits.push_back(nascgtr);
	for(int ig=0;ig<gtr300y_cluster_y_before.size();ig++){
	  double resy = gtr300y_cluster_y_before.at(ig) - GTRTrgPosY(out_trg_track_gtr_cid.at(i));
	  hgtrym->Fill(resy);
	}
	if( out_trg_track_gtr_mid.at(i)==106 ){
	  n_all_trg_tracks[0]++;
	  if(gtrisasc){
	    n_asc_trg_tracks[0]++;
	    n_wgtroff++;
	  }
	}
	//HBD
	bool hbdisasc = false;
      	int naschbd = 0;
      	for(int ih=0;ih<n_hbd_clusters;ih++){
	  out_trg_track_inc_hbd_lx.push_back(vector<double>());
	  out_trg_track_inc_hbd_ly.push_back(vector<double>());
	  out_trg_track_inc_hbd_t.push_back(vector<double>());
      	  if( hbd_cluster_t->at(ih)>200 ) continue;
      	  if( hbd_cluster_mid->at(ih) != out_trg_track_hbd_mid.at(i) ) continue;
      	  // int tcid = E16ANA_EIDSingleTrackAnalyzer::HBDTrgCid( hbd_cluster_x->at(ih), hbd_cluster_y->at(ih) );
	  if( hbd_cluster_mid->at(ih)==106 ){
	    double resx = hbd_cluster_x->at(ih) - HBDTrgPosX(out_trg_track_hbd_cid.at(i));
	    double resy = hbd_cluster_y->at(ih) - HBDTrgPosY(out_trg_track_hbd_cid.at(i));
	    if( fabs(resy)<width[2] ){hhbdx->Fill(resx);}
	    if( fabs(resx)<width[1] ){hhbdy->Fill(resy);}
	    if( fabs(resx)<width[1] && fabs(resy)<width[2] ){
	      hbdisasc = true;
	      out_trg_track_inc_hbd_lx[naschbd].push_back( hbd_cluster_x->at(ih) );
	      out_trg_track_inc_hbd_ly[naschbd].push_back( hbd_cluster_y->at(ih) );
	      out_trg_track_inc_hbd_t[naschbd].push_back( hbd_cluster_t->at(ih) );
	      naschbd++;
	    }
	  }
      	}
      	out_trg_track_inc_n_hbd_hits.push_back(naschbd);
      	for(int ih=0;ih<hbd_cluster_x_before.size();ih++){
	  double resx = hbd_cluster_x_before.at(ih) - HBDTrgPosX(out_trg_track_hbd_cid.at(i));
	  double resy = hbd_cluster_y_before.at(ih) - HBDTrgPosY(out_trg_track_hbd_cid.at(i));
	  if( fabs(resy)<width[2] ){hhbdxm->Fill(resx);}
	  if( fabs(resx)<width[1] ){hhbdym->Fill(resy);}
      	}
	if( out_trg_track_hbd_mid.at(i)==106 ){
	  n_all_trg_tracks[1]++;
	  n_all_trg_tracks[2]++;
	  if(hbdisasc){
	    n_asc_trg_tracks[1]++;
	    n_asc_trg_tracks[2]++;
	    n_whbdoff++;
	  }
	}
	//LG
	bool lgisasc = false;
      	int nasclg = 0;
      	for(int il=0;il<n_lg_hits;il++){
	  out_trg_track_inc_lg_lx.push_back(vector<double>());
	  out_trg_track_inc_lg_ly.push_back(vector<double>());
	  out_trg_track_inc_lg_t.push_back(vector<double>());
      	  if( lg_hit_fflag->at(il)>1 ) continue;
      	  if( lg_hit_mid->at(il) != out_trg_track_lg_mid.at(i) ) continue;
      	  // int tcid = lg_hit_cid->at(il);
	  if( lg_hit_mid->at(il)==106 ){
	    double resx = lg_hit_x->at(il) - out_trg_track_lg_x.at(i);
	    double resy = lg_hit_y->at(il) - out_trg_track_lg_y.at(i);
	    if( fabs(resy)<width[4] ){hlgx->Fill(resx);}
	    if( fabs(resx)<width[3] ){hlgy->Fill(resy);}
	    if( fabs(resx)<width[3] && fabs(resy)<width[4] ){
	      lgisasc = true;
	      out_trg_track_inc_lg_lx[nasclg].push_back( lg_hit_x->at(il) );
	      out_trg_track_inc_lg_ly[nasclg].push_back( lg_hit_y->at(il) );
	      out_trg_track_inc_lg_t[nasclg].push_back( lg_hit_t->at(il) );
	      nasclg++;
	    }
	  }
      	}
      	out_trg_track_inc_n_lg_hits.push_back(nasclg);
      	for(int il=0;il<lg_hit_x_before.size();il++){
	  double resx = lg_hit_x_before.at(il) - out_trg_track_lg_x.at(i);
	  double resy = lg_hit_y_before.at(il) - out_trg_track_lg_y.at(i);
	  if( fabs(resy)<width[4] ){hlgxm->Fill(resx);}
	  if( fabs(resx)<width[3] ){hlgym->Fill(resy);}
      	}
	if( out_trg_track_lg_mid.at(i)==106 ){
	  n_all_trg_tracks[3]++;
	  n_all_trg_tracks[4]++;
	  if(lgisasc){
	    n_asc_trg_tracks[3]++;
	    n_asc_trg_tracks[4]++;
	    n_wlgoff++;
	  }
	  if( gtrisasc && hbdisasc && lgisasc ){
	    n_asc_trg_tracks_alldet++;
	    n_walloff++;
	  }
	}
      }

      //Fill before infos
      gtr300y_cluster_y_before.clear();
      for(int ig=0;ig<n_gtr300y_clusters;ig++){
	if( gtr300y_cluster_adc->at(ig)<150 ) continue;
	if( gtr300y_cluster_mid->at(ig) != 106 ) continue;
	gtr300y_cluster_y_before.push_back( gtr300y_cluster_y->at(ig) );
      }
      hbd_cluster_x_before.clear();
      hbd_cluster_y_before.clear();
      for(int ih=0;ih<n_hbd_clusters;ih++){
	if( hbd_cluster_t->at(ih)>200 ) continue;
	if( hbd_cluster_mid->at(ih) != 106 ) continue;
	hbd_cluster_x_before.push_back( hbd_cluster_x->at(ih) );
	hbd_cluster_y_before.push_back( hbd_cluster_y->at(ih) );
      }
      lg_hit_x_before.clear();
      lg_hit_y_before.clear();
      for(int il=0;il<n_lg_hits;il++){
	if( lg_hit_fflag->at(il)>1 ) continue;
	if( lg_hit_mid->at(il) != 106 ) continue;
	lg_hit_x_before.push_back( lg_hit_x->at(il) );
	lg_hit_y_before.push_back( lg_hit_y->at(il) );
      }

      //Get Hits & Clusters
      out_n_tracks = ntrkacc;
      out_n_tracks_whbd = ntrkacc_whbd;
      out_n_tracks_wlg = ntrkacc_wlg;
      out_n_tracks_wall = ntrkacc_wall;
      out_n_trg_tracks = ntrgtrkacc;
      out_n_trg_tracks_wgtroff = n_wgtroff;
      out_n_trg_tracks_whbdoff = n_whbdoff;
      out_n_trg_tracks_wlgoff = n_wlgoff;
      out_n_trg_tracks_walloff = n_walloff;
      out_run_id = run_id;
      out_event_id = event_id;
      out_spill_id = spill_id;

      tree->Fill();

      nevent++;
   }//event loop

   TH1F* hgtrys = (TH1F*)hgtry->Clone("hgtrys");
   hgtrys->Add(hgtrym,-1);
   TH1F* hhbdxs = (TH1F*)hhbdx->Clone("hhbdxs");
   hhbdxs->Add(hhbdxm,-1);
   TH1F* hhbdys = (TH1F*)hhbdy->Clone("hhbdys");
   hhbdys->Add(hhbdym,-1);
   TH1F* hlgxs = (TH1F*)hlgx->Clone("hlgxs");
   hlgxs->Add(hlgxm,-1);
   TH1F* hlgys = (TH1F*)hlgy->Clone("hlgys");
   hlgys->Add(hlgym,-1);

   int ncor[5][3];//det, f/m/sub
   ncor[0][0] = hgtry->Integral( hgtry->FindBin(-width[0]), hgtry->FindBin(width[0]) );
   ncor[0][1] = hgtrym->Integral( hgtrym->FindBin(-width[0]), hgtrym->FindBin(width[0]) );
   ncor[1][0] = hhbdx->Integral( hhbdx->FindBin(-width[1]), hhbdx->FindBin(width[1]) );
   ncor[1][1] = hhbdxm->Integral( hhbdxm->FindBin(-width[1]), hhbdxm->FindBin(width[1]) );
   ncor[2][0] = hhbdy->Integral( hhbdy->FindBin(-width[2]), hhbdy->FindBin(width[2]) );
   ncor[2][1] = hhbdym->Integral( hhbdym->FindBin(-width[2]), hhbdym->FindBin(width[2]) );
   ncor[3][0] = hlgx->Integral( hlgx->FindBin(-width[3]), hlgx->FindBin(width[3]) );
   ncor[3][1] = hlgxm->Integral( hlgxm->FindBin(-width[3]), hlgxm->FindBin(width[3]) );
   ncor[4][0] = hlgy->Integral( hlgy->FindBin(-width[4]), hlgy->FindBin(width[4]) );
   ncor[4][1] = hlgym->Integral( hlgym->FindBin(-width[4]), hlgym->FindBin(width[4]) );

   for(int i=0;i<5;i++){
     ncor[i][2] = ncor[i][0] - ncor[i][1];
     // std::cout<<"lower: "<<ncor[i][2]<<" / "<<n_all_trg_tracks[i]<<" = "<<(double)ncor[i][2]/(double)n_all_trg_tracks[i]<<std::endl;
     std::cout<<"upper: "<<n_asc_trg_tracks[i]<<" / "<<n_all_trg_tracks[i]<<" = "<<(double)n_asc_trg_tracks[i]/(double)n_all_trg_tracks[i]<<std::endl;
   }
   // std::cout<<"lower all: "<<(double)ncor[0][2]/(double)n_all_trg_tracks[0]*(double)ncor[2][2]/(double)n_all_trg_tracks[2]*(double)ncor[4][2]/(double)n_all_trg_tracks[4]<<std::endl;
   std::cout<<"upper all: "<<(double)n_asc_trg_tracks_alldet/(double)n_all_trg_tracks[0]<<std::endl;

   TString pdfout = "out.pdf";
   TCanvas* c = new TCanvas("c","c",1000,2000);
   TLine *ll[5][2];
   TLegend *leg[5];
   c->Divide(2,5);
   c->cd(1);
   hgtry->Draw();
   hgtrym->SetLineColor(6);
   hgtrym->Draw("sames");
   c->cd(3);
   hhbdx->Draw();
   hhbdxm->SetLineColor(6);
   hhbdxm->Draw("sames");
   c->cd(5);
   hhbdy->Draw();
   hhbdym->SetLineColor(6);
   hhbdym->Draw("sames");
   c->cd(7);
   hlgx->Draw();
   hlgxm->SetLineColor(6);
   hlgxm->Draw("sames");
   c->cd(9);
   hlgy->Draw();
   hlgym->SetLineColor(6);
   hlgym->Draw("sames");
   for(int i=0;i<5;i++){
     c->cd((i+1)*2)->SetGridy();
     if(i==0){hgtrys->Draw();}
     if(i==1){hhbdxs->Draw();}
     if(i==2){hhbdys->Draw();}
     if(i==3){hlgxs->Draw();}
     if(i==4){hlgys->Draw();}
     gPad->Update();
     ll[i][0] = new TLine(-width[i],gPad->GetUymin(),-width[i],gPad->GetUymax());
     ll[i][1] = new TLine( width[i],gPad->GetUymin(), width[i],gPad->GetUymax());
     ll[i][0]->SetLineColor(2);
     ll[i][1]->SetLineColor(2);
     ll[i][0]->Draw("same");
     ll[i][1]->Draw("same");
     leg[i] = new TLegend(0.1,0.62,0.43,0.9);
     leg[i]->AddEntry((TObject*)0,Form("%d - %d = %d",ncor[i][0],ncor[i][1],ncor[i][2]),"");
     leg[i]->AddEntry((TObject*)0,Form("%d / %d = %1.3f",ncor[i][2],n_all_trg_tracks[i],(double)ncor[i][2]/(double)n_all_trg_tracks[i]),"");
     leg[i]->AddEntry((TObject*)0,Form("%d / %d = %1.3f",n_asc_trg_tracks[i],n_all_trg_tracks[i],(double)n_asc_trg_tracks[i]/(double)n_all_trg_tracks[i]),"");
     leg[i]->Draw("sames");
   }
   c->SaveAs(pdfout,"pdf");

   fout->Write();
   fout->Close();

}
