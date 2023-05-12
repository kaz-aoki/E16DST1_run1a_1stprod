#define E16ANA_Massw2Gamma_cxx
#include "E16ANA_Massw2Gamma.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_TrackAnalyzerFromTree.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_LGClustering.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDDeadChannel.hh"
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

void E16ANA_Massw2Gamma::MakeHist(int runoption, int maxevent, char* out_file_name)
{
   if (fChain == 0) return;

   TFile* fout = new TFile(out_file_name,"recreate");
   // TTree* tree = new TTree("tree","tree");

   TH1F* hm[4];
   TH1F* hmm[4];
   // TH1F* hmd[4];
   for(int i=0;i<4;i++){
     hm[i] = new TH1F(Form("hm%d",i),Form("IM%d",i),100,0,1.5);
     hmm[i] = new TH1F(Form("hmm%d",i),Form("IM_mix%d",i),100,0,1.5);
     // hmd[i] = new TH1F(Form("hmd%d",i),Form("hmd%d",i),100,-0.2,0.2);
   }

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

   // int active_mid[6] = {102,103,104,106,107,108};
   // int active_cid[38];
   // for(int i=0;i<6;i++){
   //   for(int j=0;j<6;j++){
   //     active_cid[i*6+j] = i*10+j;
   //   }
   // }
   // active_cid[36] = 26;
   // active_cid[37] = 36;

   int nevent=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
      if( maxevent!=-1&&nevent>maxevent ){break;}

      for(int i1=0;i1<n_lg_hits;i1++){
	if( InvalidLGhit(ientry,i1) ) continue;

	for(int i2=i1+1;i2<n_lg_hits;i2++){
	  if( InvalidLGhit(ientry,i2) ) continue;

	  int cid1 = lg_hit_cid->at(i1);
	  int cid2 = lg_hit_cid->at(i1);
	  if( fabs( lg_hit_t->at(i1) - lg_hit_t->at(i2) ) > 4. ) continue;
	  if( lg_hit_mid->at(i1)==lg_hit_mid->at(i2) && IsNeighborBlock(*geometry, cid1, cid2) ) continue;

	  TVector3 g1[4];
	  TVector3 g2[4];
	  g1[0].SetXYZ(lg_hit_gx->at(i1), lg_hit_gy->at(i1), lg_hit_gz->at(i1)+260);// maku (-260)
	  g2[0].SetXYZ(lg_hit_gx->at(i2), lg_hit_gy->at(i2), lg_hit_gz->at(i2)+260);
	  g1[1].SetXYZ(lg_hit_gx->at(i1), lg_hit_gy->at(i1), lg_hit_gz->at(i1)+20);// tgt0 (-20)
	  g2[1].SetXYZ(lg_hit_gx->at(i2), lg_hit_gy->at(i2), lg_hit_gz->at(i2)+20);
	  g1[2].SetXYZ(lg_hit_gx->at(i1), lg_hit_gy->at(i1), lg_hit_gz->at(i1));// tgt1 (0)
	  g2[2].SetXYZ(lg_hit_gx->at(i2), lg_hit_gy->at(i2), lg_hit_gz->at(i2));
	  g1[3].SetXYZ(lg_hit_gx->at(i1), lg_hit_gy->at(i1), lg_hit_gz->at(i1)-20);// tgt2 (+20)
	  g2[3].SetXYZ(lg_hit_gx->at(i2), lg_hit_gy->at(i2), lg_hit_gz->at(i2)-20);

	  double e1 = lg_hit_adc->at(i1)*mvtoe;
	  double e2 = lg_hit_adc->at(i2)*mvtoe;
	  double e12 = e1+e2;
	  TVector3 p1[4];
	  TVector3 p2[4];
	  TVector3 p12[4];
	  double im[4];
	  for(int i=0;i<4;i++){
	    p1[i].SetXYZ(g1[i].X()/g1[i].Mag()*e1, g1[i].Y()/g1[i].Mag()*e1, g1[i].Z()/g1[i].Mag()*e1);
	    p2[i].SetXYZ(g2[i].X()/g2[i].Mag()*e1, g2[i].Y()/g2[i].Mag()*e1, g2[i].Z()/g2[i].Mag()*e1);
	    p12[i] = p1[i]+p2[i];
	    im[i] = sqrt( e12*e12 - p12[i].Mag2() );
	    hm[i]->Fill(im[i]);
	  }
	  // for(int i=0;i<4;i++){
	  //   hmd[i]->Fill(im[i]-im[2]);
	  // }

	}
      }

      nevent++;

   }//event loop

   fout->Write();
   fout->Close();

}
