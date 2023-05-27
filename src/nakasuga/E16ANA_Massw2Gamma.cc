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
#include <TRandom.h>

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

   gRandom->SetSeed( time(NULL) );

   TFile* fout = new TFile(out_file_name,"recreate");
   // TTree* tree = new TTree("tree","tree");

   TH1F* hm[4];
   TH1F* hmm[4];
   int decaypos[4] = {-260,-20,0,+20};
   for(int i=0;i<4;i++){
     hm[i] = new TH1F(Form("hm%d",i),Form("IM_%d",decaypos[i]),100,0,1.5);
     hmm[i] = new TH1F(Form("hmm%d",i),Form("IM_mix_%d",decaypos[i]),100,0,1.5);
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

   int mixevent = 5;
   std::vector<std::vector<hitset>> mixhits[9];

   int nevent=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event loop
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (ientry%1000==0) {std::cout<<nevent<<" / "<<n_entries<<std::endl;}
      if( maxevent!=-1&&nevent>maxevent ){break;}

      std::vector<hitset> hits[9];

      int ihit[2] = {0, 0};
      for(ihit[0]=0; ihit[0]<n_lg_hits; ihit[0]++){
	if( InvalidLGhit(ientry, ihit[0]) ) continue;
	hitset hit[2];
	SetHit(ientry, ihit[0], hit[0]);
	int index = hit[0].mid - 101;
	hits[index].push_back(hit[0]);

	for(ihit[1]=ihit[0]+1; ihit[1]<n_lg_hits; ihit[1]++){
	  if( InvalidLGhit(ientry, ihit[1]) ) continue;
	  SetHit(ientry, ihit[1], hit[1]);

	  // if( fabs( hit[0].t - hit[1].t ) > 4. ) continue;
	  // if( hit[0].mid==hit[1].mid && IsNeighborBlock(*geometry, hit[0].cid, hit[1].cid) ) continue;
	  if( InvalidLGPair(*geometry, ientry, hit[0], hit[1]) ) continue;

	  //calc im
	  double ene[2] = {hit[0].adc*mvtoe, hit[1].adc*mvtoe};
	  double enesum = ene[0] + ene[1];
	  TVector3 gpos[4][2];
	  TVector3 mom[4][2];
	  TVector3 momsum[4];
	  double im[4];
	  for(int idp=0;idp<4;idp++){
	    gpos[idp][0].SetXYZ(hit[0].gx, hit[0].gy, hit[0].gz - decaypos[idp]);
	    gpos[idp][1].SetXYZ(hit[1].gx, hit[1].gy, hit[1].gz - decaypos[idp]);
	    mom[idp][0].SetXYZ(gpos[idp][0].X()/gpos[idp][0].Mag()*ene[0], 
	                       gpos[idp][0].Y()/gpos[idp][0].Mag()*ene[0], 
	                       gpos[idp][0].Z()/gpos[idp][0].Mag()*ene[0]);
	    mom[idp][1].SetXYZ(gpos[idp][1].X()/gpos[idp][1].Mag()*ene[1], 
	                       gpos[idp][1].Y()/gpos[idp][1].Mag()*ene[1], 
	                       gpos[idp][1].Z()/gpos[idp][1].Mag()*ene[1]);
	    momsum[idp] = mom[idp][0] + mom[idp][1];
	    im[idp] = sqrt( enesum*enesum - momsum[idp].Mag2() );
	    hm[idp]->Fill( im[idp] );
	  }

	  //calc mix im
	  std::vector<hitset> mixhitcands(0);
	  int ifore = gRandom->Uniform(0.5, 1.5);
	  int imix  = (ifore+1)%2;
	  int mixmid = hit[imix].mid - 101;
	  for(int imix1=0; imix1<mixhits[mixmid].size(); imix1++){
	    for(int imix2=0; imix2<mixhits[mixmid].at(imix1).size(); imix2++){
	      hitset mixhit = mixhits[mixmid].at(imix1).at(imix2);
	      if( InvalidLGPair(*geometry, ientry, hit[ifore], mixhit) ) continue;
	      mixhitcands.push_back(mixhit);
	    }
	  }
	  if( mixhitcands.size()==0 ){
	  }
	  else{
	    int imixhit = gRandom->Uniform(0.5, (float)mixhitcands.size()-0.5);
	    hitset mixhit;
	    for(int imix1=0; imix1<mixhitcands.size(); imix1++){
	      if( imix1==imixhit ){
		mixhit = mixhitcands.at(imix1);
	      }
	    }
	    double enem[2] = {hit[ifore].adc*mvtoe, mixhit.adc*mvtoe};
	    double enesumm = enem[0] + enem[1];
	    TVector3 gposm[4][2];
	    TVector3 momm[4][2];
	    TVector3 momsumm[4];
	    double imm[4];
	    for(int idp=0;idp<4;idp++){
	      gposm[idp][0].SetXYZ(hit[ifore].gx, hit[ifore].gy, hit[ifore].gz - decaypos[idp]);
	      gposm[idp][1].SetXYZ(mixhit.gx, mixhit.gy, mixhit.gz - decaypos[idp]);
	      momm[idp][0].SetXYZ(gposm[idp][0].X()/gposm[idp][0].Mag()*enem[0], 
		                  gposm[idp][0].Y()/gposm[idp][0].Mag()*enem[0], 
		                  gposm[idp][0].Z()/gposm[idp][0].Mag()*enem[0]);
	      momm[idp][1].SetXYZ(gposm[idp][1].X()/gposm[idp][1].Mag()*enem[1], 
		                  gposm[idp][1].Y()/gposm[idp][1].Mag()*enem[1], 
		                  gposm[idp][1].Z()/gposm[idp][1].Mag()*enem[1]);
	      momsumm[idp] = momm[idp][0] + momm[idp][1];
	      imm[idp] = sqrt( enesumm*enesumm - momsumm[idp].Mag2() );
	      hmm[idp]->Fill( imm[idp] );
	    }
	  }

	}
      }

      //fill mixhits
      for(int imod=0;imod<9;imod++){
	mixhits[imod].push_back(hits[imod]);
	if( mixhits[imod].size() > mixevent ){
	  mixhits[imod].erase(mixhits[imod].begin());
	}
      }

      nevent++;

   }//event loop

   fout->Write();
   fout->Close();

}
