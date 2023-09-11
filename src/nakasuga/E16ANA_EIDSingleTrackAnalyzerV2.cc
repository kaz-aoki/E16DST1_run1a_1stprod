#define E16ANA_EIDSingleTrackAnalyzerV2_cxx
#include "E16ANA_EIDSingleTrackAnalyzerV2.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_TrackAnalyzerFromTreeV2.hh"
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

void E16ANA_EIDSingleTrackAnalyzerV2::EIDEfficiency(int runoption, int maxevent, char* out_file_name)
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
   vector<double> out_track_tgt_dist;
   vector<int> out_track_tgt_id;
   vector<double> out_track_ssd_t;
   vector<double> out_track_ssd_adc;
   vector<bool> out_track_w_trg_bias;
   vector<int> out_track_hbd_mid;
   vector<double> out_track_hbd_lx;
   vector<double> out_track_hbd_ly;
   vector<int> out_track_lg_mid;
   vector<double> out_track_lg_lx;
   vector<double> out_track_lg_ly;

   vector<int>    out_hbdhit_mid;
   vector<double> out_hbdhit_lx;
   vector<double> out_hbdhit_ly;
   vector<double> out_hbdhit_t;
   vector<double> out_hbdhit_adc;
   vector<int>    out_hbdhit_size;
   vector<double> out_hbdhit_eprob;
   vector<int>    out_lghit_mid;
   vector<int>    out_lghit_cid;
   vector<double> out_lghit_lx;
   vector<double> out_lghit_ly;
   vector<double> out_lghit_t;
   vector<double> out_lghit_adc;
   vector<int>    out_lgtrghit_mid;
   vector<int>    out_lgtrghit_cid;
   vector<double> out_lgtrghit_lx;
   vector<double> out_lgtrghit_ly;
   vector<double> out_lgtrghit_t;

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
   tree->Branch("track_tgt_dist", &out_track_tgt_dist);
   tree->Branch("track_tgt_id", &out_track_tgt_id);
   tree->Branch("track_ssd_t", &out_track_ssd_t);
   tree->Branch("track_ssd_adc", &out_track_ssd_adc);
   tree->Branch("track_w_trg_bias", &out_track_w_trg_bias);
   tree->Branch("track_hbd_mid", &out_track_hbd_mid);
   tree->Branch("track_hbd_lx", &out_track_hbd_lx);
   tree->Branch("track_hbd_ly", &out_track_hbd_ly);
   tree->Branch("track_lg_mid", &out_track_lg_mid);
   tree->Branch("track_lg_lx", &out_track_lg_lx);
   tree->Branch("track_lg_ly", &out_track_lg_ly);

   tree->Branch("hbdhit_mid", &out_hbdhit_mid);
   tree->Branch("hbdhit_lx", &out_hbdhit_lx);
   tree->Branch("hbdhit_ly", &out_hbdhit_ly);
   tree->Branch("hbdhit_t", &out_hbdhit_t);
   tree->Branch("hbdhit_adc", &out_hbdhit_adc);
   tree->Branch("hbdhit_size", &out_hbdhit_size);
   tree->Branch("hbdhit_eprob", &out_hbdhit_eprob);
   tree->Branch("lghit_mid", &out_lghit_mid);
   tree->Branch("lghit_cid", &out_lghit_cid);
   tree->Branch("lghit_lx", &out_lghit_lx);
   tree->Branch("lghit_ly", &out_lghit_ly);
   tree->Branch("lghit_t", &out_lghit_t);
   tree->Branch("lghit_adc", &out_lghit_adc);
   tree->Branch("lgtrghit_mid", &out_lgtrghit_mid);
   tree->Branch("lgtrghit_cid", &out_lgtrghit_cid);
   tree->Branch("lgtrghit_lx", &out_lgtrghit_lx);
   tree->Branch("lgtrghit_ly", &out_lgtrghit_ly);
   tree->Branch("lgtrghit_t", &out_lgtrghit_t);


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
      out_track_mom.clear();
      out_track_mom_x.clear();
      out_track_mom_y.clear();
      out_track_mom_z.clear();
      out_track_tgt_dist.clear();
      out_track_tgt_id.clear();
      out_track_ssd_t.clear();
      out_track_ssd_adc.clear();
      out_track_w_trg_bias.clear();
      out_track_hbd_mid.clear();
      out_track_hbd_lx.clear();
      out_track_hbd_ly.clear();
      out_track_lg_mid.clear();
      out_track_lg_lx.clear();
      out_track_lg_ly.clear();

      out_hbdhit_mid.clear();
      out_hbdhit_lx.clear();
      out_hbdhit_ly.clear();
      out_hbdhit_t.clear();
      out_hbdhit_adc.clear();
      out_hbdhit_size.clear();
      out_hbdhit_eprob.clear();
      out_lghit_mid.clear();
      out_lghit_cid.clear();
      out_lghit_lx.clear();
      out_lghit_ly.clear();
      out_lghit_t.clear();
      out_lghit_adc.clear();
      out_lgtrghit_mid.clear();
      out_lgtrghit_cid.clear();
      out_lgtrghit_lx.clear();
      out_lgtrghit_ly.clear();
      out_lgtrghit_t.clear();


      int ntrkacc = 0;
      int ntracks = track_id->size();
      for(int itrack=0;itrack<ntracks;itrack++){//track loop
	double trk_momx = rk_fit_init_mom_gx->at(itrack);
	double trk_momy = rk_fit_init_mom_gy->at(itrack);
	double trk_momz = rk_fit_init_mom_gz->at(itrack);
	double trk_mom  = sqrt(trk_momx*trk_momx+trk_momy*trk_momy+trk_momz*trk_momz);
	if (chi_square->at(itrack)>100) continue;
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

	int tgtid = -10000;
	double tgtdist = -10000.;
	tgtdist = TargetAssociation(ientry,itrack,tgtid);//220725 for the production in 220707
	if( tgtdist<0 || tgtdist>100 ) continue;//220725 for the production in 220707

	if( trk_hbd_mid != trk_lg_mid ) continue;
	if( chi_square->at(itrack)>10 ) continue;

	bool trg_bias = false;
	if( trk_hbd_mid==106 ){
	  if( TriggerType(run_id)%10 != 0 ){
	    trg_bias = true;
	  }
	}
	if( trk_hbd_mid==107 ){
	  if( TriggerType(run_id)%10==7 || TriggerType(run_id)%10==5 ){
	    trg_bias = true;
	  }
	}
	if( trk_hbd_mid==104 ){
	  if( TriggerType(run_id)%10==5 ){
	    trg_bias = true;
	  }
	}

	out_track_id.push_back(track_id->at(itrack));
	out_chi_square.push_back(chi_square->at(itrack));
	out_rk_charge.push_back(rk_charge->at(itrack));
	out_track_mom.push_back(trk_mom);
	out_track_mom_x.push_back(trk_momx);
	out_track_mom_y.push_back(trk_momy);
	out_track_mom_z.push_back(trk_momz);
	out_track_tgt_dist.push_back(tgtdist);
	out_track_tgt_id.push_back(tgtid);
	out_track_ssd_t.push_back(rk_hit_ssd_t->at(itrack));
	out_track_ssd_adc.push_back(rk_hit_ssd_adc->at(itrack));
	out_track_hbd_mid.push_back(trk_hbd_mid);
	out_track_hbd_lx.push_back(trk_hbd_lx);
	out_track_hbd_ly.push_back(trk_hbd_ly);
	out_track_lg_mid.push_back(trk_lg_mid);
	out_track_lg_lx.push_back(trk_lg_lx);
	out_track_lg_ly.push_back(trk_lg_ly);
	out_track_w_trg_bias.push_back(trg_bias);

	int mid = trk_hbd_mid - 103;
	//HBD loop
	// double resx_min = 10000;
	// double resy_min = 10000;
	// int nhbdc = 0;
	// for(int ihbd=0;ihbd<n_hbd_clusters;ihbd++){
	//   if ( hbd_cluster_t->at(ihbd)>200 ) continue;
	//   if ( runoption==0 && hbd_cluster_size->at(ihbd)!=1 ) continue;//220213;
	//   if ( hbd_cluster_mid->at(ihbd) == trk_hbd_mid ) {
	//     double resx = hbd_cluster_x->at(ihbd) - trk_hbd_lx - originx[mid][0];
	//     double resy = hbd_cluster_y->at(ihbd) - trk_hbd_ly - originy[mid][0];
	//     if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	//       resx_min = resx;
	//       resy_min = resy;
	//     }
	//     nhbdc++;
	//   }
	// }
	// bool HBDhit = false;
	// if( fabs(resx_min)<widthx[mid][0] && fabs(resy_min)<widthy[mid][0] ){
	//   HBDhit = true;
	// }

	//LG loop
	// resx_min = 10000;
	// resy_min = 10000;
	// int nlgh = 0;
	// for(int ilg=0;ilg<n_lg_hits;ilg++){
	//   if( lg_hit_fflag->at(ilg)>=2 ) continue;
	//   if( lg_hit_mid->at(ilg) == trk_lg_mid ){
	//     double resx = lg_hit_x->at(ilg) - trk_lg_lx - originx[mid][1];
	//     double resy = lg_hit_y->at(ilg) - trk_lg_ly - originy[mid][1];
	//     if( resx*resx+resy*resy < resx_min*resx_min+resy_min*resy_min ){
	//       resx_min = resx;
	//       resy_min = resy;
	//     }
	//     nlgh++;
	//   }
	// }
	// bool LGhit = false;
	// if( fabs(resx_min)<widthx[mid][1] && fabs(resy_min)<widthy[mid][1] ){
	//   LGhit = true;
	// }

	ntrkacc++;

      }//track loop

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

}
