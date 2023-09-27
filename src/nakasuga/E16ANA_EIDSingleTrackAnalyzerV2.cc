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
