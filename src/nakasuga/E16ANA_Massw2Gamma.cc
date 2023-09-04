#define E16ANA_Massw2Gamma_cxx
#include "E16ANA_Massw2Gamma.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_TrackAnalyzerFromTreeV2.hh"
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

void DrawTH1FCanvas(TCanvas* c, TString& fout, TH1F* h1, TH1F* h2, TH1F *h3, TH1F *h4){
  c->Clear();
  c->Divide(2,2);
  c->cd(1);
  h1->Draw();
  c->cd(2);
  h2->Draw();
  c->cd(3);
  h3->Draw();
  c->cd(4);
  h4->Draw();
  c->SaveAs(fout,"pdf");
}

void E16ANA_Massw2Gamma::MakeHist(int runoption, int maxevent, char* out_file_name)
{
   if (fChain == 0) return;

   gRandom->SetSeed( time(NULL) );

   TFile* fout = new TFile(out_file_name,"recreate");
   // TTree* tree = new TTree("tree","tree");

   TH1F* hp[4][2];
   TH1F* hpx[4][2];
   TH1F* hpy[4][2];
   TH1F* hpz[4][2];
   TH1F* hpt[4][2];
   TH1F* hpp[4][2];
   TH1F* hps[4];
   TH1F* hpsx[4];
   TH1F* hpsy[4];
   TH1F* hpsz[4];
   TH1F* hdist[4];
   TH2F* hpzpx[4];
   TH1F* hm[4];
   TH1F* hpm[4][2];
   TH1F* hpxm[4][2];
   TH1F* hpym[4][2];
   TH1F* hpzm[4][2];
   TH1F* hptm[4][2];
   TH1F* hppm[4][2];
   TH1F* hpsm[4];
   TH1F* hpsxm[4];
   TH1F* hpsym[4];
   TH1F* hpszm[4];
   TH1F* hdistm[4];
   TH2F* hpzpxm[4];
   TH1F* hmm[4];
   int decaypos[4] = {-260,-20,0,+20};
   for(int i=0;i<4;i++){
     for(int j=0;j<2;j++){
       hp[i][j] = new TH1F(Form("hp%d%d",i,j),Form("mom%d_%d",j+1,decaypos[i]),100,0,2.5);
       hpx[i][j] = new TH1F(Form("hpx%d%d",i,j),Form("mom%dx_%d",j+1,decaypos[i]),100,-2.5,2.5);
       hpy[i][j] = new TH1F(Form("hpy%d%d",i,j),Form("mom%dy_%d",j+1,decaypos[i]),100,-2.5,2.5);
       hpz[i][j] = new TH1F(Form("hpz%d%d",i,j),Form("mom%dz_%d",j+1,decaypos[i]),100,-2.5,2.5);
       hpt[i][j] = new TH1F(Form("hpt%d%d",i,j),Form("mom%dtheta_%d",j+1,decaypos[i]),100,-2.5,2.5);
       hpp[i][j] = new TH1F(Form("hpp%d%d",i,j),Form("mom%dphi_%d",j+1,decaypos[i]),100,-2.5,2.5);
       hpm[i][j] = new TH1F(Form("hpm%d%d",i,j),Form("mix_mom%d_%d",j+1,decaypos[i]),100,0,2.5);
       hpxm[i][j] = new TH1F(Form("hpxm%d%d",i,j),Form("mix_mom%dx_%d",j+1,decaypos[i]),100,-2.5,2.5);
       hpym[i][j] = new TH1F(Form("hpym%d%d",i,j),Form("mix_mom%dy_%d",j+1,decaypos[i]),100,-2.5,2.5);
       hpzm[i][j] = new TH1F(Form("hpzm%d%d",i,j),Form("mix_mom%dz_%d",j+1,decaypos[i]),100,-2.5,2.5);
       hptm[i][j] = new TH1F(Form("hptm%d%d",i,j),Form("mix_mom%dtheta_%d",j+1,decaypos[i]),100,-2.5,2.5);
       hppm[i][j] = new TH1F(Form("hppm%d%d",i,j),Form("mix_mom%dphi_%d",j+1,decaypos[i]),100,-2.5,2.5);
     }
     hps[i] = new TH1F(Form("hps%d",i),Form("momsum_%d",decaypos[i]),100,0,2.5);
     hpsx[i] = new TH1F(Form("hpsx%d",i),Form("momsum_x_%d",decaypos[i]),100,-2.5,2.5);
     hpsy[i] = new TH1F(Form("hpsy%d",i),Form("momsum_y_%d",decaypos[i]),100,-2.5,2.5);
     hpsz[i] = new TH1F(Form("hpsz%d",i),Form("momsum_z_%d",decaypos[i]),100,-2.5,2.5);
     hdist[i] = new TH1F(Form("hdist%d",i),Form("2gamma_distance@LG_%d",decaypos[i]),100,0,5000);
     hpzpx[i] = new TH2F(Form("hpzpx%d",i),Form("mom_zvsx_%d",decaypos[i]),100,-2.5,2.5,100,-2.5,2.5);
     hm[i] = new TH1F(Form("hm%d",i),Form("IM_%d",decaypos[i]),100,0,1.5);
     hpsm[i] = new TH1F(Form("hpsm%d",i),Form("mix_momsum_%d",decaypos[i]),100,0,2.5);
     hpsxm[i] = new TH1F(Form("hpsxm%d",i),Form("mix_momsum_x_%d",decaypos[i]),100,-2.5,2.5);
     hpsym[i] = new TH1F(Form("hpsym%d",i),Form("mix_momsum_y_%d",decaypos[i]),100,-2.5,2.5);
     hpszm[i] = new TH1F(Form("hpszm%d",i),Form("mix_momsum_z_%d",decaypos[i]),100,-2.5,2.5);
     hdistm[i] = new TH1F(Form("hdistm%d",i),Form("mix_2gamma_distance@LG_%d",decaypos[i]),100,0,5000);
     hpzpxm[i] = new TH2F(Form("hpzpxm%d",i),Form("mix_mom_zvsx_%d",decaypos[i]),100,-2.5,2.5,100,-2.5,2.5);
     hmm[i] = new TH1F(Form("hmm%d",i),Form("mix_IM_%d",decaypos[i]),100,0,1.5);
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

   int mixevent = 100;
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

	// int jpair = 0;
	// for(ihit[1]=ihit[0]+1; ihit[1]<n_lg_hits; ihit[1]++){
	//   if( InvalidLGhit(ientry, ihit[1]) ) continue;
	//   jpair++;
	// }
	// if(jpair>15) continue;
	for(ihit[1]=ihit[0]+1; ihit[1]<n_lg_hits; ihit[1]++){
	  if( InvalidLGhit(ientry, ihit[1]) ) continue;
	  SetHit(ientry, ihit[1], hit[1]);

	  if( InvalidLGPair(*geometry, ientry, hit[0], hit[1]) ) continue;

	  //calc im
	  double ene[2] = {hit[0].adc*mvtoe, hit[1].adc*mvtoe};
	  double enesum = ene[0] + ene[1];
	  TVector3 gpos[4][2];
	  TVector3 mom[4][2];
	  TVector3 momsum[4];
	  double im[4];
	  for(int idp=0;idp<4;idp++){
	    for(int ig=0;ig<2;ig++){
	      gpos[idp][ig].SetXYZ(hit[ig].gx, hit[ig].gy, hit[ig].gz - decaypos[idp]);
	      mom[idp][ig].SetXYZ(gpos[idp][ig].X()/gpos[idp][ig].Mag()*ene[ig], 
		                  gpos[idp][ig].Y()/gpos[idp][ig].Mag()*ene[ig], 
		                  gpos[idp][ig].Z()/gpos[idp][ig].Mag()*ene[ig]);
	      hp[idp][ig]->Fill(mom[idp][ig].Mag());
	      hpx[idp][ig]->Fill(mom[idp][ig].X());
	      hpy[idp][ig]->Fill(mom[idp][ig].Y());
	      hpz[idp][ig]->Fill(mom[idp][ig].Z());
	      hpzpx[idp]->Fill(mom[idp][ig].Z(),mom[idp][ig].X());
	      TVector3 rot(mom[idp][ig].Z(),mom[idp][ig].X(),mom[idp][ig].Y());
	      hpt[idp][ig]->Fill(rot.Theta());
	      hpp[idp][ig]->Fill(rot.Phi());
	    }
	    momsum[idp] = mom[idp][0] + mom[idp][1];
	    hps[idp]->Fill(momsum[idp].Mag());
	    hpsx[idp]->Fill(momsum[idp].X());
	    hpsy[idp]->Fill(momsum[idp].Y());
	    hpsz[idp]->Fill(momsum[idp].Z());
	    double angle = mom[idp][0].Angle(mom[idp][1]);
	    hdist[idp]->Fill(angle*1500.);
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
	      for(int ig=0;ig<2;ig++){
		momm[idp][ig].SetXYZ(gposm[idp][ig].X()/gposm[idp][ig].Mag()*enem[ig], 
		                     gposm[idp][ig].Y()/gposm[idp][ig].Mag()*enem[ig], 
		                     gposm[idp][ig].Z()/gposm[idp][ig].Mag()*enem[ig]);
		hpm[idp][ig]->Fill(momm[idp][ig].Mag());
		hpxm[idp][ig]->Fill(momm[idp][ig].X());
		hpym[idp][ig]->Fill(momm[idp][ig].Y());
		hpzm[idp][ig]->Fill(momm[idp][ig].Z());
		hpzpxm[idp]->Fill(momm[idp][ig].Z(),momm[idp][ig].X());
		TVector3 rot(momm[idp][ig].Z(),momm[idp][ig].X(),momm[idp][ig].Y());
		hptm[idp][ig]->Fill(rot.Theta());
		hppm[idp][ig]->Fill(rot.Phi());
	      }
	      momsumm[idp] = momm[idp][0] + momm[idp][1];
	      hpsm[idp]->Fill(momsumm[idp].Mag());
	      hpsxm[idp]->Fill(momsumm[idp].X());
	      hpsym[idp]->Fill(momsumm[idp].Y());
	      hpszm[idp]->Fill(momsumm[idp].Z());
	      double anglem = momm[idp][0].Angle(momm[idp][1]);
	      hdistm[idp]->Fill(anglem*1500.);
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

   TCanvas* c = new TCanvas("c","c",1000,700);
   TString fsout = "./test.pdf";
   c->SaveAs(fsout+"[","pdf");
   for(int idp=0;idp<4;idp++){
     for(int ig=0;ig<2;ig++){
       DrawTH1FCanvas(c,fsout,hp[idp][ig],hpx[idp][ig],hpy[idp][ig],hpz[idp][ig]);
       DrawTH1FCanvas(c,fsout,hp[idp][ig],hp[idp][ig], hpt[idp][ig],hpp[idp][ig]);
     }
     DrawTH1FCanvas(c,fsout,hps[idp],hpsx[idp],hpsy[idp],hpsz[idp]);
     c->Clear();
     c->cd()->SetGrid();
     hpzpx[idp]->Draw("colz");
     c->SaveAs(fsout,"pdf");
     c->Clear();
     hdist[idp]->Draw();
     c->SaveAs(fsout,"pdf");
     c->Clear();
     hm[idp]->Draw();
     c->SaveAs(fsout,"pdf");
     //mix
     for(int ig=0;ig<2;ig++){
       DrawTH1FCanvas(c,fsout,hpm[idp][ig],hpxm[idp][ig],hpym[idp][ig],hpzm[idp][ig]);
       DrawTH1FCanvas(c,fsout,hpm[idp][ig],hpm[idp][ig], hptm[idp][ig],hppm[idp][ig]);
     }
     DrawTH1FCanvas(c,fsout,hpsm[idp],hpsxm[idp],hpsym[idp],hpszm[idp]);
     c->Clear();
     c->cd()->SetGrid();
     hpzpxm[idp]->Draw("colz");
     c->SaveAs(fsout,"pdf");
     c->Clear();
     hdistm[idp]->Draw();
     c->SaveAs(fsout,"pdf");
     c->Clear();
     hm[idp]->Draw();
     hmm[idp]->SetLineColor(2);
     hmm[idp]->Draw("sames");
     c->SaveAs(fsout,"pdf");
     //mix
   }
   c->SaveAs(fsout+"]","pdf");

   fout->Write();
   fout->Close();

}
