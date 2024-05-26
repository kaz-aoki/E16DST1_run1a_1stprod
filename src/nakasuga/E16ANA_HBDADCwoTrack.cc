#define E16ANA_HBDADCwoTrack_cxx
#include "E16ANA_HBDADCwoTrack.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_TrackAnalyzerFromTreeV2.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_LGClustering.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDDeadChannel.hh"
#include "CoincidenceMapWithLG.hh"
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

void E16ANA_HBDADCwoTrack::MakeHist(int maxevent, char* out_pdf_name, char* out_root_name)
{
   if (fChain == 0) return;

   TFile* fout = new TFile(out_root_name,"recreate");
   TTree* tree = new TTree("tree","tree");

   Int_t           out_run_id;
   Int_t           out_event_id;
   Int_t           out_spill_id;
   int out_n_lgs;
   std::vector<int> out_lg_mid;
   std::vector<int> out_lg_cid;
   std::vector<double> out_lg_adc;
   std::vector<double> out_lg_t;
   std::vector<int> out_n_hbds;
   std::vector<std::vector<double>> out_hbd_mid;
   std::vector<std::vector<double>> out_hbd_cid;
   std::vector<std::vector<double>> out_hbd_trgid;//not unique
   std::vector<std::vector<double>> out_hbd_padid;
   std::vector<std::vector<double>> out_hbd_adc;
   std::vector<std::vector<double>> out_hbd_t;

   tree->Branch("run_id",&out_run_id,"run_id/I");
   tree->Branch("event_id",&out_event_id,"event_id/I");
   tree->Branch("spill_id",&out_spill_id,"spill_id/I");
   tree->Branch("n_lgs",&out_n_lgs,"n_lgs/I");
   tree->Branch("lg_mid",&out_lg_mid);
   tree->Branch("lg_cid",&out_lg_cid);
   tree->Branch("lg_adc",&out_lg_adc);
   tree->Branch("lg_t",&out_lg_t);
   tree->Branch("n_hbds",&out_n_hbds);
   tree->Branch("hbd_mid",&out_hbd_mid);
   tree->Branch("hbd_cid",&out_hbd_cid);
   tree->Branch("hbd_trgid",&out_hbd_trgid);
   tree->Branch("hbd_padid",&out_hbd_padid);
   tree->Branch("hbd_adc",&out_hbd_adc);
   tree->Branch("hbd_t",&out_hbd_t);

   TH1F* hadc[8][4];
   for(int i=0;i<8;i++){
     for(int j=0;j<4;j++){
       hadc[i][j] = new TH1F(Form("hadc%d%d",i,j),Form("HBDadc_Mod%d_GEM%d",IndexToModule(i),IndexToGEM(j)),100,0,40);
     }
   }

   E16ANA_HBDDeadChannel hbddch;
   std::string hbd_deadch_file = "/ccj/u/E16/database/calib/HBD/dead_ch/240515/HBD-dead-ch-tmp-240515.dat";
   hbddch.ReadFile(hbd_deadch_file.c_str());

   CoincidenceMapWithLG *coinmap = new CoincidenceMapWithLG("/ccj/u/kkanno/e16/hbd/work/coinmap/MagCoinMapHBDRun0c.txt");
   E16ANA_HBDGeometry *hbd_geometry = new E16ANA_HBDGeometry(); 

   auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
   E16ANA_GeometryV2::SetGlobalPointer(geometry);
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

   int nevent=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
      if( maxevent!=-1&&nevent>maxevent ){break;}

      out_lg_mid.clear();
      out_lg_cid.clear();
      out_lg_adc.clear();
      out_lg_t.clear();
      out_n_hbds.clear();
      out_hbd_mid.clear();
      out_hbd_cid.clear();
      out_hbd_trgid.clear();
      out_hbd_padid.clear();
      out_hbd_adc.clear();
      out_hbd_t.clear();

      //Search tracks ( = lg trigger hits )
      hitset tmplghits[8];
      for(int i=0;i<8;i++){
	tmplghits[i].Init();
	// tmplghits[i].adc = 200.;
      }
      for(int ilg=0; ilg<n_lg_hits; ilg++){
	if(lg_hit_fflag->at(ilg)>=2) continue;
	int lmid = lg_hit_mid->at(ilg);
	int lcid = lg_hit_cid->at(ilg);
	double ladc = lg_hit_adc->at(ilg);
	double lt   = lg_hit_t->at(ilg);
	double lx   = lg_hit_x->at(ilg);
	double ly   = lg_hit_y->at(ilg);
	for(int itrg=0; itrg<n_trg_tracks; itrg++){
	  int tmid = trg_track_lg_mid->at(itrg);
	  int tcid = trg_track_lg_cid->at(itrg);
	  if( tmid==lmid && tcid==lcid ){
	    if( tmplghits[ ModuleToIndex(lmid) ].adc < ladc ){
	      tmplghits[ ModuleToIndex(lmid) ].Set(lmid, lcid, ladc, lt, lx, ly);
	    }
	    break;
	  }
	}
      }

      //Search associated hbd trigger tiles
      std::vector<hitset> lg_associated_trgids[8];
      bool is_lg_associated_module[8] = {false, false, false, false, false, false, false, false};
      for(int i=0;i<8;i++){
	if( tmplghits[i].mid<0 ) continue;
	std::vector<int> hbd_trgids = coinmap->GetHBDCoincidenceChannelsWithLG(tmplghits[i].mid, tmplghits[i].cid);
	for(auto pair : hbd_trgids) {
	  hitset hbdtrg;
	  hbdtrg.Set(pair/100, pair%100, -10000., -10000., -10000., -10000.);
	  lg_associated_trgids[i].push_back( hbdtrg );
	  is_lg_associated_module[ ModuleToIndex(hbdtrg.mid) ] = true;
	}
      }

      //Search hbd clusters
      std::vector<hitset> tmphbdclss[8];
      for(int ihbd=0; ihbd<n_hbd_clusters; ihbd++){
	int tmp_hbd_mid = hbd_cluster_mid->at(ihbd);
	int tmp_hbd_cid = hbd_cluster_max_cid->at(ihbd);
	double tmp_hbd_x = hbd_cluster_x->at(ihbd);
	double tmp_hbd_y = hbd_cluster_y->at(ihbd);
	double tmp_hbd_adc = hbd_cluster_adc->at(ihbd);
	double tmp_hbd_t = hbd_cluster_t->at(ihbd);
	if( tmp_hbd_t<120 || tmp_hbd_t>200 ) continue;
	if( !is_lg_associated_module[ ModuleToIndex(tmp_hbd_mid) ] ) continue;
	double tmp_cog[2] = {tmp_hbd_x, tmp_hbd_y};
	int cls_associated_trgid = hbd_geometry->GetTriggerTileIDWLocalCoordinate(tmp_cog);
	for(int i=0;i<8;i++){
	  for(auto hbdtrg : lg_associated_trgids[i]){
	    if( hbdtrg.mid != tmp_hbd_mid ) continue;
	    if( hbdtrg.cid == cls_associated_trgid ){
	      hitset hbdcls;
	      hbdcls.Set(tmp_hbd_mid, tmp_hbd_cid, tmp_hbd_adc, tmp_hbd_t, tmp_hbd_x, tmp_hbd_y);
	      tmphbdclss[i].push_back( hbdcls );
	    }
	  }// trg loop
	}// trg loop
      }// cls loop

      //Fill
      int tmp_n_lgs = 0;
      for(int i=0;i<8;i++){
	if( tmplghits[i].mid<0 ) continue;
	out_lg_mid.push_back( tmplghits[i].mid );
	out_lg_cid.push_back( tmplghits[i].cid );
	out_lg_adc.push_back( tmplghits[i].adc );
	out_lg_t.push_back( tmplghits[i].t );
	out_hbd_mid.push_back(std::vector<double>());
	out_hbd_cid.push_back(std::vector<double>());
	out_hbd_adc.push_back(std::vector<double>());
	out_hbd_t.push_back(std::vector<double>());
	int tmp_n_hbds = 0;
	for(auto hbdcls : tmphbdclss[i]){
	  out_hbd_mid[tmp_n_lgs].push_back( hbdcls.mid );
	  out_hbd_cid[tmp_n_lgs].push_back( hbdcls.cid );
	  out_hbd_adc[tmp_n_lgs].push_back( hbdcls.adc );
	  out_hbd_t[tmp_n_lgs].push_back( hbdcls.t );
	  double tmp_cog[2] = { hbdcls.x, hbdcls.y };
	  int GEMID = hbd_geometry->GetGEMIDWLocalCoordinate(tmp_cog);
	  hadc[ ModuleToIndex(hbdcls.mid) ][ GEMToIndex(GEMID) ]->Fill( hbdcls.adc );
	  tmp_n_hbds++;
	}
	out_n_hbds.push_back(tmp_n_hbds);
	tmp_n_lgs++;
      }
      out_n_lgs = tmp_n_lgs;

      out_run_id = run_id;
      out_event_id = event_id;
      out_spill_id = spill_id;

      tree->Fill();

      nevent++;

   }//event loop

   TString pdfout = Form("%s",out_pdf_name);
   TCanvas* c = new TCanvas("c","c",700,500);
   c->SaveAs(pdfout+"[","pdf");
   for(int i=0;i<8;i++){
     c->Clear();
     c->Divide(2,2);
     for(int j=0;j<4;j++){
       c->cd(j+1);
       hadc[i][j]->Draw("hist");
     }
     c->SaveAs(pdfout,"pdf");
   }
   c->SaveAs(pdfout+"]","pdf");

   fout->Write();
   fout->Close();

}
