#define GainCalibwoTrack_cxx
#include "GainCalibwoTrack.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_TrackAnalyzerFromTree.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "SingleTrackAnalyzerForRes.hh"
#include "E16ANA_LGClustering.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDDeadChannel.hh"
#include "AnalyzerResidualHBD.hh"
#include "AnalyzerTrackSelection.hh"
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

void GainCalibwoTrack::Loop()
{
//   In a ROOT session, you can do:
//      root> .L GainCalibwoTrack.C
//      root> GainCalibwoTrack t
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

void GainCalibwoTrack::MakeTree(int runoption, int maxevent, char* out_file_name)
{
   if (fChain == 0) return;

   TFile* fout = new TFile(out_file_name,"recreate");
   TTree* tree = new TTree("tree","tree");

   Int_t           out_run_id;
   Int_t           out_event_id;
   Int_t           out_spill_id;
   Int_t           out_run_purpose;
   int    out_lg_mid;
   int    out_lg_cid;
   double out_lg_adc;
   double out_lg_t;
   double out_lg_leftside_adc;
   double out_lg_leftside_t;
   double out_lg_rightside_adc;
   double out_lg_rightside_t;
   int    out_lg_trg_hit;
   bool    out_lg_trg_trk;
   bool   out_lg_trg_run;
   int    out_lg_multi_ev;
   int    out_lg_multi_mod;
   int    out_n_hbds;
   double out_hbd_cx;
   double out_hbd_cy;
   double out_hbd_nearest_adc;
   double out_hbd_nearest_t;
   double out_hbd_nearest_lx;
   double out_hbd_nearest_ly;
   vector<double> out_hbd_adc;
   vector<double> out_hbd_t;
   vector<double> out_hbd_lx;
   vector<double> out_hbd_ly;
   int    out_n_ssds;
   double out_ssd_cx;
   double out_ssd_nearest_adc;
   double out_ssd_nearest_t;
   double out_ssd_nearest_lx;
   vector<double> out_ssd_adc;
   vector<double> out_ssd_t;
   vector<double> out_ssd_lx;
   int    out_n_gtr100xs;
   double out_gtr100x_cx;
   double out_gtr100x_nearest_adc;
   double out_gtr100x_nearest_t;
   double out_gtr100x_nearest_lx;
   vector<double> out_gtr100x_adc;
   vector<double> out_gtr100x_t;
   vector<double> out_gtr100x_lx;
   int    out_n_gtr200xs;
   double out_gtr200x_cx;
   double out_gtr200x_nearest_adc;
   double out_gtr200x_nearest_t;
   double out_gtr200x_nearest_lx;
   vector<double> out_gtr200x_adc;
   vector<double> out_gtr200x_t;
   vector<double> out_gtr200x_lx;
   int    out_n_gtr300xs;
   double out_gtr300x_cx;
   double out_gtr300x_nearest_adc;
   double out_gtr300x_nearest_t;
   double out_gtr300x_nearest_lx;
   vector<double> out_gtr300x_adc;
   vector<double> out_gtr300x_t;
   vector<double> out_gtr300x_lx;
   int    out_n_gtr100ys;
   double out_gtr100y_cy;
   double out_gtr100y_nearest_adc;
   double out_gtr100y_nearest_t;
   double out_gtr100y_nearest_ly;
   vector<double> out_gtr100y_adc;
   vector<double> out_gtr100y_t;
   vector<double> out_gtr100y_ly;
   int    out_n_gtr200ys;
   double out_gtr200y_cy;
   double out_gtr200y_nearest_adc;
   double out_gtr200y_nearest_t;
   double out_gtr200y_nearest_ly;
   vector<double> out_gtr200y_adc;
   vector<double> out_gtr200y_t;
   vector<double> out_gtr200y_ly;
   int    out_n_gtr300ys;
   double out_gtr300y_cy;
   double out_gtr300y_nearest_adc;
   double out_gtr300y_nearest_t;
   double out_gtr300y_nearest_ly;
   vector<double> out_gtr300y_adc;
   vector<double> out_gtr300y_t;
   vector<double> out_gtr300y_ly;

   tree->Branch("run_id",&out_run_id,"run_id/I");
   tree->Branch("event_id",&out_event_id,"event_id/I");
   tree->Branch("spill_id",&out_spill_id,"spill_id/I");
   tree->Branch("run_purpose",&out_run_purpose,"run_purpose/I");
   tree->Branch("lg_mid",&out_lg_mid,"lg_mid/I");
   tree->Branch("lg_cid",&out_lg_cid,"lg_cid/I");
   tree->Branch("lg_adc",&out_lg_adc,"lg_adc/D");
   tree->Branch("lg_t",&out_lg_t,"lg_t/D");
   tree->Branch("lg_leftside_adc",&out_lg_leftside_adc,"lg_leftside_adc/D");
   tree->Branch("lg_leftside_t",&out_lg_leftside_t,"lg_leftside_t/D");
   tree->Branch("lg_rightside_adc",&out_lg_rightside_adc,"lg_rightside_adc/D");
   tree->Branch("lg_rightside_t",&out_lg_rightside_t,"lg_rightside_t/D");
   tree->Branch("lg_trg_hit",&out_lg_trg_hit,"lg_trg_hit/I");
   tree->Branch("lg_trg_trk",&out_lg_trg_trk,"lg_trg_trk/O");
   tree->Branch("lg_trg_run",&out_lg_trg_run,"lg_trg_run/O");
   tree->Branch("lg_multi_ev",&out_lg_multi_ev,"lg_multi_ev/I");
   tree->Branch("lg_multi_mod",&out_lg_multi_mod,"lg_multi_mod/I");
   tree->Branch("n_hbds",&out_n_hbds,"n_hbds/I");
   tree->Branch("hbd_cx", &out_hbd_cx, "out_hbd_cx/D");
   tree->Branch("hbd_cy", &out_hbd_cy, "out_hbd_cy/D");
   tree->Branch("hbd_nearest_adc", &out_hbd_nearest_adc, "out_hbd_nearest_adc/D");
   tree->Branch("hbd_nearest_t", &out_hbd_nearest_t, "out_hbd_nearest_t/D");
   tree->Branch("hbd_nearest_lx", &out_hbd_nearest_lx, "out_hbd_nearest_lx/D");
   tree->Branch("hbd_nearest_ly", &out_hbd_nearest_ly, "out_hbd_nearest_ly/D");
   tree->Branch("hbd_adc", &out_hbd_adc);
   tree->Branch("hbd_t", &out_hbd_t);
   tree->Branch("hbd_lx", &out_hbd_lx);
   tree->Branch("hbd_ly", &out_hbd_ly);
   tree->Branch("n_ssds",&out_n_ssds,"n_ssds/I");
   tree->Branch("ssd_cx", &out_ssd_cx, "out_ssd_cx/D");
   tree->Branch("ssd_nearest_adc", &out_ssd_nearest_adc, "out_ssd_nearest_adc/D");
   tree->Branch("ssd_nearest_t", &out_ssd_nearest_t, "out_ssd_nearest_t/D");
   tree->Branch("ssd_nearest_lx", &out_ssd_nearest_lx, "out_ssd_nearest_lx/D");
   tree->Branch("ssd_adc", &out_ssd_adc);
   tree->Branch("ssd_t", &out_ssd_t);
   tree->Branch("ssd_lx", &out_ssd_lx);
   tree->Branch("n_gtr100xs",&out_n_gtr100xs,"n_gtr100xs/I");
   tree->Branch("gtr100x_cx", &out_gtr100x_cx, "out_gtr100x_cx/D");
   tree->Branch("gtr100x_nearest_adc", &out_gtr100x_nearest_adc, "out_gtr100x_nearest_adc/D");
   tree->Branch("gtr100x_nearest_t", &out_gtr100x_nearest_t, "out_gtr100x_nearest_t/D");
   tree->Branch("gtr100x_nearest_lx", &out_gtr100x_nearest_lx, "out_gtr100x_nearest_lx/D");
   tree->Branch("gtr100x_adc", &out_gtr100x_adc);
   tree->Branch("gtr100x_t", &out_gtr100x_t);
   tree->Branch("gtr100x_lx", &out_gtr100x_lx);
   tree->Branch("n_gtr200xs",&out_n_gtr200xs,"n_gtr200xs/I");
   tree->Branch("gtr200x_cx", &out_gtr200x_cx, "out_gtr200x_cx/D");
   tree->Branch("gtr200x_nearest_adc", &out_gtr200x_nearest_adc, "out_gtr200x_nearest_adc/D");
   tree->Branch("gtr200x_nearest_t", &out_gtr200x_nearest_t, "out_gtr200x_nearest_t/D");
   tree->Branch("gtr200x_nearest_lx", &out_gtr200x_nearest_lx, "out_gtr200x_nearest_lx/D");
   tree->Branch("gtr200x_adc", &out_gtr200x_adc);
   tree->Branch("gtr200x_t", &out_gtr200x_t);
   tree->Branch("gtr200x_lx", &out_gtr200x_lx);
   tree->Branch("n_gtr300xs",&out_n_gtr300xs,"n_gtr300xs/I");
   tree->Branch("gtr300x_cx", &out_gtr300x_cx, "out_gtr300x_cx/D");
   tree->Branch("gtr300x_nearest_adc", &out_gtr300x_nearest_adc, "out_gtr300x_nearest_adc/D");
   tree->Branch("gtr300x_nearest_t", &out_gtr300x_nearest_t, "out_gtr300x_nearest_t/D");
   tree->Branch("gtr300x_nearest_lx", &out_gtr300x_nearest_lx, "out_gtr300x_nearest_lx/D");
   tree->Branch("gtr300x_adc", &out_gtr300x_adc);
   tree->Branch("gtr300x_t", &out_gtr300x_t);
   tree->Branch("gtr300x_lx", &out_gtr300x_lx);
   tree->Branch("n_gtr100ys",&out_n_gtr100ys,"n_gtr100ys/I");
   tree->Branch("gtr100y_cy", &out_gtr100y_cy, "out_gtr100y_cy/D");
   tree->Branch("gtr100y_nearest_adc", &out_gtr100y_nearest_adc, "out_gtr100y_nearest_adc/D");
   tree->Branch("gtr100y_nearest_t", &out_gtr100y_nearest_t, "out_gtr100y_nearest_t/D");
   tree->Branch("gtr100y_nearest_ly", &out_gtr100y_nearest_ly, "out_gtr100y_nearest_ly/D");
   tree->Branch("gtr100y_adc", &out_gtr100y_adc);
   tree->Branch("gtr100y_t", &out_gtr100y_t);
   tree->Branch("gtr100y_ly", &out_gtr100y_ly);
   tree->Branch("n_gtr200ys",&out_n_gtr200ys,"n_gtr200ys/I");
   tree->Branch("gtr200y_cy", &out_gtr200y_cy, "out_gtr200y_cy/D");
   tree->Branch("gtr200y_nearest_adc", &out_gtr200y_nearest_adc, "out_gtr200y_nearest_adc/D");
   tree->Branch("gtr200y_nearest_t", &out_gtr200y_nearest_t, "out_gtr200y_nearest_t/D");
   tree->Branch("gtr200y_nearest_ly", &out_gtr200y_nearest_ly, "out_gtr200y_nearest_ly/D");
   tree->Branch("gtr200y_adc", &out_gtr200y_adc);
   tree->Branch("gtr200y_t", &out_gtr200y_t);
   tree->Branch("gtr200y_ly", &out_gtr200y_ly);
   tree->Branch("n_gtr300ys",&out_n_gtr300ys,"n_gtr300ys/I");
   tree->Branch("gtr300y_cy", &out_gtr300y_cy, "out_gtr300y_cy/D");
   tree->Branch("gtr300y_nearest_adc", &out_gtr300y_nearest_adc, "out_gtr300y_nearest_adc/D");
   tree->Branch("gtr300y_nearest_t", &out_gtr300y_nearest_t, "out_gtr300y_nearest_t/D");
   tree->Branch("gtr300y_nearest_ly", &out_gtr300y_nearest_ly, "out_gtr300y_nearest_ly/D");
   tree->Branch("gtr300y_adc", &out_gtr300y_adc);
   tree->Branch("gtr300y_t", &out_gtr300y_t);
   tree->Branch("gtr300y_ly", &out_gtr300y_ly);


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

   int active_mid[4] = {103,104,106,107};
   int active_cid[38];
   for(int i=0;i<6;i++){
     for(int j=0;j<6;j++){
       active_cid[i*6+j] = i*10+j;
     }
   }
   active_cid[36] = 26;
   active_cid[37] = 36;

   int nevent=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      int run_purpose = AnalyzerTrackSelection::RunPurpose(run_id);
      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
      if( maxevent!=-1&&nevent>maxevent ){break;}

      int multiplicity[7]={0};//102,103,104,all,106,107,108
      bool invalid_run = false;
      for(int ilg=0;ilg<n_lg_hits;ilg++){
	if(lg_hit_fflag->at(ilg)>=2) continue;
	multiplicity[3]++;
	int midtmp = lg_hit_mid->at(ilg)-102;
	if(midtmp>=0&&midtmp<=6){
	  multiplicity[midtmp]++;
	}
	else{
	  std::cout<<"invalid module id"<<std::endl;
	  invalid_run = true;
	}
      }
      if(invalid_run) break;

      std::unordered_map<int, int> wlghit;
      for(int ilg=0;ilg<n_lg_hits;ilg++){//lg hit loop

	if(lg_hit_fflag->at(ilg)>=2) continue;
	int key = lg_hit_mid->at(ilg)*100 + lg_hit_cid->at(ilg);
	wlghit[key] = 1;
	int midtmp = lg_hit_mid->at(ilg)-102;
	int mid = lg_hit_mid->at(ilg);
	int cid = lg_hit_cid->at(ilg);
	out_run_id = run_id;
	out_event_id = event_id;
	out_spill_id = spill_id;
	out_run_purpose = run_purpose;
	out_lg_mid = lg_hit_mid->at(ilg);
	out_lg_cid = lg_hit_cid->at(ilg);
	out_lg_adc = lg_hit_adc->at(ilg);
	out_lg_t = lg_hit_t->at(ilg);
	out_lg_multi_ev = multiplicity[3];
	out_lg_multi_mod = multiplicity[midtmp];

	//Side-hit Search
	out_lg_leftside_adc = -10000.;
	out_lg_leftside_t = -10000.;
	LeftSideHit(ilg,out_lg_leftside_adc,out_lg_leftside_t);
	out_lg_rightside_adc = -10000.;
	out_lg_rightside_t = -10000.;
	RightSideHit(ilg,out_lg_rightside_adc,out_lg_rightside_t);

	//Trg ana
	int  wtrghit = -10000;
	bool wtrgtrk = false;
	bool trg_bias = wTrgBias(ientry,mid,cid,TrigAWmin,TrigAWmax,TrigTW,wtrghit,wtrgtrk);
	bool wtrgrun = AnalyzerTrackSelection::IsInTrgRun(run_id,ilg,mid);
	out_lg_trg_hit = wtrghit;
	out_lg_trg_trk = wtrgtrk;
	out_lg_trg_run = wtrgrun;

	//hits in other detectors
	out_hbd_adc.clear();
	out_hbd_t.clear();
	out_hbd_lx.clear();
	out_hbd_ly.clear();
	out_ssd_adc.clear();
	out_ssd_t.clear();
	out_ssd_lx.clear();
	out_gtr100x_adc.clear();
	out_gtr100x_t.clear();
	out_gtr100x_lx.clear();
	out_gtr200x_adc.clear();
	out_gtr200x_t.clear();
	out_gtr200x_lx.clear();
	out_gtr300x_adc.clear();
	out_gtr300x_t.clear();
	out_gtr300x_lx.clear();
	out_gtr100y_adc.clear();
	out_gtr100y_t.clear();
	out_gtr100y_ly.clear();
	out_gtr200y_adc.clear();
	out_gtr200y_t.clear();
	out_gtr200y_ly.clear();
	out_gtr300y_adc.clear();
	out_gtr300y_t.clear();
	out_gtr300y_ly.clear();

	TVector3 lcross[5];//SSD, GTR100, GTR200, GTR300, HBD
	int othermid[5];
	for(int il=0;il<5;il++){
	  CalcCrossPoint(geometry,mid,cid,il,othermid[il],lcross[il]);
	}
	out_ssd_cx = lcross[0].X();
	out_gtr100x_cx = lcross[1].X();
	out_gtr100y_cy = lcross[1].Y();
	out_gtr200x_cx = lcross[2].X();
	out_gtr200y_cy = lcross[2].Y();
	out_gtr300x_cx = lcross[3].X();
	out_gtr300y_cy = lcross[3].Y();
	out_hbd_cx = lcross[4].X();
	out_hbd_cy = lcross[4].Y();

	int n_hbds_assoc = 0;
	nearcls nch;
	nch.nearclsInit();
	for(int ihbd=0;ihbd<n_hbd_clusters;ihbd++){
	  if( hbd_cluster_mid->at(ihbd)!=othermid[4] ) continue;
	  TVector3 hbd_hit(hbd_cluster_x->at(ihbd), hbd_cluster_y->at(ihbd), 0.);
	  double dist = (hbd_hit-lcross[4]).Perp();
	  if(dist<search_d[4]){
	    out_hbd_adc.push_back(hbd_cluster_adc->at(ihbd));
	    out_hbd_t.push_back(hbd_cluster_t->at(ihbd));
	    out_hbd_lx.push_back(hbd_cluster_x->at(ihbd));
	    out_hbd_ly.push_back(hbd_cluster_y->at(ihbd));
	    n_hbds_assoc++;
	  }
	  if(dist<nch.dist){
	    nch.nearclsSet(hbd_cluster_adc->at(ihbd), hbd_cluster_t->at(ihbd), hbd_cluster_x->at(ihbd), hbd_cluster_y->at(ihbd), dist);
	  }
	}
	out_n_hbds = n_hbds_assoc;
	out_hbd_nearest_adc = nch.adc;
	out_hbd_nearest_t = nch.t;
	out_hbd_nearest_lx = nch.lx;
	out_hbd_nearest_ly = nch.ly;

	int n_assoc[4][2] = {0};//SSD, GTR100, GTR200, GTR300
	nearcls nc[4][2];
	OtherClsLoop(0, 0, othermid[0], lcross[0].X(), n_assoc[0][0], nc[0][0], out_ssd_adc, out_ssd_t, out_ssd_lx);
	out_n_ssds = n_assoc[0][0];
	out_ssd_nearest_adc = nc[0][0].adc;
	out_ssd_nearest_t = nc[0][0].t;
	out_ssd_nearest_lx = nc[0][0].lx;
	OtherClsLoop(1, 0, othermid[1], lcross[1].X(), n_assoc[1][0], nc[1][0], out_gtr100x_adc, out_gtr100x_t, out_gtr100x_lx);
	out_n_gtr100xs = n_assoc[1][0];
	out_gtr100x_nearest_adc = nc[1][0].adc;
	out_gtr100x_nearest_t = nc[1][0].t;
	out_gtr100x_nearest_lx = nc[1][0].lx;
	OtherClsLoop(1, 1, othermid[1], lcross[1].Y(), n_assoc[1][1], nc[1][1], out_gtr100y_adc, out_gtr100y_t, out_gtr100y_ly);
	out_n_gtr100ys = n_assoc[1][1];
	out_gtr100y_nearest_adc = nc[1][1].adc;
	out_gtr100y_nearest_t = nc[1][1].t;
	out_gtr100y_nearest_ly = nc[1][1].ly;
	OtherClsLoop(2, 0, othermid[2], lcross[2].X(), n_assoc[2][0], nc[2][0], out_gtr200x_adc, out_gtr200x_t, out_gtr200x_lx);
	out_n_gtr200xs = n_assoc[2][0];
	out_gtr200x_nearest_adc = nc[2][0].adc;
	out_gtr200x_nearest_t = nc[2][0].t;
	out_gtr200x_nearest_lx = nc[2][0].lx;
	OtherClsLoop(2, 1, othermid[2], lcross[2].Y(), n_assoc[2][1], nc[2][1], out_gtr200y_adc, out_gtr200y_t, out_gtr200y_ly);
	out_n_gtr200ys = n_assoc[2][1];
	out_gtr200y_nearest_adc = nc[2][1].adc;
	out_gtr200y_nearest_t = nc[2][1].t;
	out_gtr200y_nearest_ly = nc[2][1].ly;
	OtherClsLoop(3, 0, othermid[3], lcross[3].X(), n_assoc[3][0], nc[3][0], out_gtr300x_adc, out_gtr300x_t, out_gtr300x_lx);
	out_n_gtr300xs = n_assoc[3][0];
	out_gtr300x_nearest_adc = nc[3][0].adc;
	out_gtr300x_nearest_t = nc[3][0].t;
	out_gtr300x_nearest_lx = nc[3][0].lx;
	OtherClsLoop(3, 1, othermid[3], lcross[3].Y(), n_assoc[3][1], nc[3][1], out_gtr300y_adc, out_gtr300y_t, out_gtr300y_ly);
	out_n_gtr300ys = n_assoc[3][1];
	out_gtr300y_nearest_adc = nc[3][1].adc;
	out_gtr300y_nearest_t = nc[3][1].t;
	out_gtr300y_nearest_ly = nc[3][1].ly;

      	// double cog[2] = {trk_hbd_lx,trk_hbd_ly};
      	// int hbd_padid = E16ANA_HBDGeometry::GetPadIDWLocalCoordinate(trk_hbd_mid,cog);
      	// if( hbddch.Status(trk_hbd_mid,hbd_padid) != 0 ) continue;

	tree->Fill();

      }//lg hit loop

      //w/o lg hit
      for(int imod=0;imod<4;imod++){
	for(int ich=0;ich<38;ich++){

	  int tmid = active_mid[imod];
	  int tcid = active_cid[ich];
	  int key = tmid*100+tcid;
	  if(wlghit[key]==1){
	    continue;
	  }
	  out_run_id = run_id;
	  out_event_id = event_id;
	  out_spill_id = spill_id;
	  out_run_purpose = run_purpose;
	  out_lg_mid = tmid;
	  out_lg_cid = tcid;
	  out_lg_adc = -10000.;
	  out_lg_t = -10000.;
	  out_lg_multi_ev = -10000.;
	  out_lg_multi_mod = -10000.;
	  out_lg_leftside_adc = -10000.;
	  out_lg_leftside_t = -10000.;
	  out_lg_rightside_adc = -10000.;
	  out_lg_rightside_t = -10000.;
	  out_lg_trg_hit = -10000.;
	  out_lg_trg_trk = -10000.;
	  out_lg_trg_run = -10000.;

	  //hits in other detectors
	  out_hbd_adc.clear();
	  out_hbd_t.clear();
	  out_hbd_lx.clear();
	  out_hbd_ly.clear();
	  out_ssd_adc.clear();
	  out_ssd_t.clear();
	  out_ssd_lx.clear();
	  out_gtr100x_adc.clear();
	  out_gtr100x_t.clear();
	  out_gtr100x_lx.clear();
	  out_gtr200x_adc.clear();
	  out_gtr200x_t.clear();
	  out_gtr200x_lx.clear();
	  out_gtr300x_adc.clear();
	  out_gtr300x_t.clear();
	  out_gtr300x_lx.clear();
	  out_gtr100y_adc.clear();
	  out_gtr100y_t.clear();
	  out_gtr100y_ly.clear();
	  out_gtr200y_adc.clear();
	  out_gtr200y_t.clear();
	  out_gtr200y_ly.clear();
	  out_gtr300y_adc.clear();
	  out_gtr300y_t.clear();
	  out_gtr300y_ly.clear();

	  TVector3 lcross[5];//SSD, GTR100, GTR200, GTR300, HBD
	  int othermid[5];
	  for(int il=0;il<5;il++){
	    CalcCrossPoint(geometry,tmid,tcid,il,othermid[il],lcross[il]);
	  }
	  out_ssd_cx = lcross[0].X();
	  out_gtr100x_cx = lcross[1].X();
	  out_gtr100y_cy = lcross[1].Y();
	  out_gtr200x_cx = lcross[2].X();
	  out_gtr200y_cy = lcross[2].Y();
	  out_gtr300x_cx = lcross[3].X();
	  out_gtr300y_cy = lcross[3].Y();
	  out_hbd_cx = lcross[4].X();
	  out_hbd_cy = lcross[4].Y();

	  int n_hbds_assoc = 0;
	  nearcls nch;
	  nch.nearclsInit();
	  for(int ihbd=0;ihbd<n_hbd_clusters;ihbd++){
	    if( hbd_cluster_mid->at(ihbd)!=othermid[4] ) continue;
	    TVector3 hbd_hit(hbd_cluster_x->at(ihbd), hbd_cluster_y->at(ihbd), 0.);
	    double dist = (hbd_hit-lcross[4]).Perp();
	    if(dist<search_d[4]){
	      out_hbd_adc.push_back(hbd_cluster_adc->at(ihbd));
	      out_hbd_t.push_back(hbd_cluster_t->at(ihbd));
	      out_hbd_lx.push_back(hbd_cluster_x->at(ihbd));
	      out_hbd_ly.push_back(hbd_cluster_y->at(ihbd));
	      n_hbds_assoc++;
	    }
	    if(dist<nch.dist){
	      nch.nearclsSet(hbd_cluster_adc->at(ihbd), hbd_cluster_t->at(ihbd), hbd_cluster_x->at(ihbd), hbd_cluster_y->at(ihbd), dist);
	    }
	  }
	  if(n_hbds_assoc==0){continue;}
	  // std::cout<<event_id<<" "<<tmid<<" "<<tcid<<std::endl;
	  out_n_hbds = n_hbds_assoc;
	  out_hbd_nearest_adc = nch.adc;
	  out_hbd_nearest_t = nch.t;
	  out_hbd_nearest_lx = nch.lx;
	  out_hbd_nearest_ly = nch.ly;

	  int n_assoc[4][2] = {0};//SSD, GTR100, GTR200, GTR300
	  nearcls nc[4][2];
	  OtherClsLoop(0, 0, othermid[0], lcross[0].X(), n_assoc[0][0], nc[0][0], out_ssd_adc, out_ssd_t, out_ssd_lx);
	  out_n_ssds = n_assoc[0][0];
	  out_ssd_nearest_adc = nc[0][0].adc;
	  out_ssd_nearest_t = nc[0][0].t;
	  out_ssd_nearest_lx = nc[0][0].lx;
	  OtherClsLoop(1, 0, othermid[1], lcross[1].X(), n_assoc[1][0], nc[1][0], out_gtr100x_adc, out_gtr100x_t, out_gtr100x_lx);
	  out_n_gtr100xs = n_assoc[1][0];
	  out_gtr100x_nearest_adc = nc[1][0].adc;
	  out_gtr100x_nearest_t = nc[1][0].t;
	  out_gtr100x_nearest_lx = nc[1][0].lx;
	  OtherClsLoop(1, 1, othermid[1], lcross[1].Y(), n_assoc[1][1], nc[1][1], out_gtr100y_adc, out_gtr100y_t, out_gtr100y_ly);
	  out_n_gtr100ys = n_assoc[1][1];
	  out_gtr100y_nearest_adc = nc[1][1].adc;
	  out_gtr100y_nearest_t = nc[1][1].t;
	  out_gtr100y_nearest_ly = nc[1][1].ly;
	  OtherClsLoop(2, 0, othermid[2], lcross[2].X(), n_assoc[2][0], nc[2][0], out_gtr200x_adc, out_gtr200x_t, out_gtr200x_lx);
	  out_n_gtr200xs = n_assoc[2][0];
	  out_gtr200x_nearest_adc = nc[2][0].adc;
	  out_gtr200x_nearest_t = nc[2][0].t;
	  out_gtr200x_nearest_lx = nc[2][0].lx;
	  OtherClsLoop(2, 1, othermid[2], lcross[2].Y(), n_assoc[2][1], nc[2][1], out_gtr200y_adc, out_gtr200y_t, out_gtr200y_ly);
	  out_n_gtr200ys = n_assoc[2][1];
	  out_gtr200y_nearest_adc = nc[2][1].adc;
	  out_gtr200y_nearest_t = nc[2][1].t;
	  out_gtr200y_nearest_ly = nc[2][1].ly;
	  OtherClsLoop(3, 0, othermid[3], lcross[3].X(), n_assoc[3][0], nc[3][0], out_gtr300x_adc, out_gtr300x_t, out_gtr300x_lx);
	  out_n_gtr300xs = n_assoc[3][0];
	  out_gtr300x_nearest_adc = nc[3][0].adc;
	  out_gtr300x_nearest_t = nc[3][0].t;
	  out_gtr300x_nearest_lx = nc[3][0].lx;
	  OtherClsLoop(3, 1, othermid[3], lcross[3].Y(), n_assoc[3][1], nc[3][1], out_gtr300y_adc, out_gtr300y_t, out_gtr300y_ly);
	  out_n_gtr300ys = n_assoc[3][1];
	  out_gtr300y_nearest_adc = nc[3][1].adc;
	  out_gtr300y_nearest_t = nc[3][1].t;
	  out_gtr300y_nearest_ly = nc[3][1].ly;

	  tree->Fill();

	}//cid loop
      }//mid loop

      nevent++;

   }//event loop

   fout->Write();
   fout->Close();

}

// void GainCalibwoTrack::MomentumEachBlock()
// {
//    if (fChain == 0) return;

//    TFile* frout = new TFile("momentum.root","recreate");

//    int mid[4] = {103,104,106,107};
//    int cid[42];
//    for(int i=0;i<7;i++){
//      for(int j=0;j<6;j++){
//        cid[i+j*7] = i+j*10;
//      }
//    }
//    TH1F* hmom[5][4][42];
//    for(int k=0;k<5;k++){
//      for(int i=0;i<4;i++){
//        for(int j=0;j<42;j++){
// 	 hmom[k][i][j] = new TH1F(Form("h%d%d%d",k,i,j),Form("lgadc_%d_%d-%d",k,mid[i],cid[j]),25,0,5);
//        }
//      }
//    }

//    E16ANA_HBDDeadChannel hbddch;
//    std::string hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0c-220114.dat";
//    if(runoption==0){
//      hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/220114/HBD-dead-ch-run0b-220114.dat";
//    }
//    hbddch.ReadFile(hbd_deadch_file.c_str());

//    auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
//    E16ANA_GeometryV2::SetGlobalPointer(geometry);
//    auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
//    bfield_map->Initialize_binary();
//    E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
//    E16ANA_MultiTrack pair_fitter(bfield_map, geometry, 2);

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

//       int run_purpose = AnalyzerTrackSelection::RunPurpose(run_id);
//       if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
//       if( maxevent!=-1&&nevent>maxevent ){break;}

//       int ntracks = track_id->size();
//       for(int itrack=0;itrack<ntracks;itrack++){//track loop

// 	//cut condition for tracks
// 	if( chi_square->at(itrack)>2 ) continue;

// 	double trk_lg_lx = -10000;
// 	double trk_lg_ly = -10000;
// 	int ytype = -10000;
//       	int trk_lg_mid = CutOfTrackForResidualLG(ientry,itrack,trk_lg_lx,trk_lg_ly,ytype);
//         int blockchx = (trk_lg_lx)-(track_position_block_lx);
//         int blockchy = (trk_lg_ly/fabs(trk_lg_ly))*(fabs(trk_lg_ly)+track_position_block_ly);
//         int blockch = LocaltoCh(blockchx,blockchy);

//       	if (trk_lg_mid < 0) continue;
// 	int tgtid = -10000;
// 	double tgtdist = -10000.;
// 	tgtdist = CutAroundTarget(ientry,itrack,tgtid);
// 	if( tgtdist<0 || tgtdist>5 ) continue;

// 	double trk_momx = rk_fit_init_mom_gx->at(itrack);
// 	double trk_momy = rk_fit_init_mom_gy->at(itrack);
// 	double trk_momz = rk_fit_init_mom_gz->at(itrack);
// 	double trk_mom  = sqrt(trk_momx*trk_momx+trk_momy*trk_momy+trk_momz*trk_momz);

//       }

//       nevent++;

//    }//event loop

//    fout->Write();
//    fout->Close();

// }
