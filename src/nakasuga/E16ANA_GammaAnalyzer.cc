#include "E16ANA_GammaAnalyzer.hh"
#include "E16ANA_EIDSingleTrackAnalyzer.hh"
#include <TH1.h>
#include <TH2.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TRandom.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

E16ANA_GammaAnalyzer::E16ANA_GammaAnalyzer(){

  gRandom->SetSeed( time(NULL) );

  ClearMixHit();
  ClearMixEvent();

  char name[2][5] = {"fore","mix"};
  for(int l=0;l<2;l++){
    for(int i=0;i<4;i++){

      hp[l][i] = new TH1F(Form("hp%d%d",l,i),Form("mom_%d_%s",decaypos[i],name[l]),100,0,2.5);
      hpx[l][i] = new TH1F(Form("hpx%d%d",l,i),Form("momx_%d_%s",decaypos[i],name[l]),100,-2.5,2.5);
      hpy[l][i] = new TH1F(Form("hpy%d%d",l,i),Form("momy_%d_%s",decaypos[i],name[l]),100,-2.5,2.5);
      hpz[l][i] = new TH1F(Form("hpz%d%d",l,i),Form("momz_%d_%s",decaypos[i],name[l]),100,-2.5,2.5);
      hpxy[l][i] = new TH1F(Form("hpxy%d%d",l,i),Form("pT_%d_%s",decaypos[i],name[l]),100,0.,2.5);
      hpt[l][i] = new TH1F(Form("hpt%d%d",l,i),Form("momtheta_%d_%s",decaypos[i],name[l]),100,0.,4.);
      hpp[l][i] = new TH1F(Form("hpp%d%d",l,i),Form("momphi_%d_%s",decaypos[i],name[l]),100,-4.,4.);

      hpvs[l][i] = new TH2F(Form("hpvs%d%d",l,i),Form("mom1vs2_%d_%s",decaypos[i],name[l]),100,0,2.5,100,0,2.5);
      hpxvs[l][i] = new TH2F(Form("hpxvs%d%d",l,i),Form("momx1vs2_%d_%s",decaypos[i],name[l]),100,-2.5,2.5,100,-2.5,2.5);
      hpyvs[l][i] = new TH2F(Form("hpyvs%d%d",l,i),Form("momy1vs2_%d_%s",decaypos[i],name[l]),100,-2.5,2.5,100,-2.5,2.5);
      hpzvs[l][i] = new TH2F(Form("hpzvs%d%d",l,i),Form("momz1vs2_%d_%s",decaypos[i],name[l]),100,-2.5,2.5,100,-2.5,2.5);
      hpxyvs[l][i] = new TH2F(Form("hpxyvs%d%d",l,i),Form("pT1vs2_%d_%s",decaypos[i],name[l]),100,0.,2.5,100,0.,2.5);
      hptvs[l][i] = new TH2F(Form("hptvs%d%d",l,i),Form("momtheta1vs2_%d_%s",decaypos[i],name[l]),100,0.,4.,100,0.,4.);
      hppvs[l][i] = new TH2F(Form("hppvs%d%d",l,i),Form("momphi1vs2_%d_%s",decaypos[i],name[l]),100,-4.,4.,100,-4.,4.);

      hps[l][i] = new TH1F(Form("hps%d%d",l,i),Form("momsum_%d_%s",decaypos[i],name[l]),100,0,2.5);
      hpsx[l][i] = new TH1F(Form("hpsx%d%d",l,i),Form("momsum_x_%d_%s",decaypos[i],name[l]),100,-2.5,2.5);
      hpsy[l][i] = new TH1F(Form("hpsy%d%d",l,i),Form("momsum_y_%d_%s",decaypos[i],name[l]),100,-2.5,2.5);
      hpsz[l][i] = new TH1F(Form("hpsz%d%d",l,i),Form("momsum_z_%d_%s",decaypos[i],name[l]),100,-2.5,2.5);
      hpsxy[l][i] = new TH1F(Form("hpsxy%d%d",l,i),Form("parent_pT_%d_%s",decaypos[i],name[l]),100,0.,2.5);
      heneasy[l][i] = new TH1F(Form("heneasy%d%d",l,i),Form("energy_asymmetry_%d_%s",decaypos[i],name[l]),100,0.,1.);
      hptvsea[l][i] = new TH2F(Form("hptvsea%d%d",l,i),Form("pT_vs_energy_asymmetry_%d_%s",decaypos[i],name[l]),100,0.,1.,100,0.,2.5);
      hdist[l][i] = new TH1F(Form("hdist%d%d",l,i),Form("2gamma_distance@LG_%d_%s",decaypos[i],name[l]),100,0,5000);
      hpzpx[l][i] = new TH2F(Form("hpzpx%d%d",l,i),Form("mom_zvsx_%d_%s",decaypos[i],name[l]),100,-2.5,2.5,100,-2.5,2.5);
      hm[l][i] = new TH1F(Form("hm%d%d",l,i),Form("IM_%d_%s",decaypos[i],name[l]),150,0,1.5);
    }
  }

  for(int j=0;j<2;j++){
    hmid[j] = new TH1F(Form("hmid%d",j),Form("gamma%d_module",j+1),10,100,110);
    hcid[j] = new TH1F(Form("hcid%d",j),Form("gamma%d_block",j+1),60,0,60);
    hx[j] = new TH1F(Form("hx%d",j),Form("gamma%d_lx",j+1),200,-1000,1000);
    hy[j] = new TH1F(Form("hy%d",j),Form("gamma%d_ly",j+1),200,-1000,1000);
    hz[j] = new TH1F(Form("hz%d",j),Form("gamma%d_lz",j+1),200,-1000,1000);
    hgx[j] = new TH1F(Form("hgx%d",j),Form("gamma%d_gx",j+1),200,-2000,2000);
    hgy[j] = new TH1F(Form("hgy%d",j),Form("gamma%d_gy",j+1),200,-2000,2000);
    hgz[j] = new TH1F(Form("hgz%d",j),Form("gamma%d_gz",j+1),200,-2000,2000);
    hadc[j] = new TH1F(Form("hadc%d",j),Form("gamma%d_adc[mV]",j+1),400,0,400);
    ht[j] = new TH1F(Form("ht%d",j),Form("gamma%d_t",j+1),200,0,200);
    hfflag[j] = new TH1F(Form("hfflag%d",j),Form("gamma%d_fflag",j+1),4,0,4);
    hwidth[j] = new TH1F(Form("hwidth%d",j),Form("gamma%d_width",j+1),50,0,50);
  }

  for(int j=0;j<9;j++){
    heventmp[j] = new TH1F(Form("heventmp%d",j),Form("event_multiplicity_%d",j+101),20,0,20);
    hpairmp[j] = new TH1F(Form("hpairmp%d",j),Form("possible_pair_multiplicity_%d",j+101),20,0,20);
    hpairmpsame[j] = new TH1F(Form("hpairmpsame%d",j),Form("possible_pair_multiplicity_sameModule_%d",j+101),20,0,20);
    hpairmpsameratio[j] = new TH1F(Form("hpairmpsameratio%d",j),Form("possible_pair_multiplicity_sameModule_ratio_%d",j+101),100,0,1);
    hpairmpvssame[j] = new TH2F(Form("hpairmpvssame%d",j),Form("possible_pair_multiplicity_AllvsSameModule_%d",j+101),20,0,20,20,0,20);
  }

  tree = new TTree("tree","tree");
  tree->Branch("run_id",&run_id,"run_id/I");
  tree->Branch("event_id",&event_id,"event_id/I");
  tree->Branch("spill_id",&spill_id,"spill_id/I");
  tree->Branch("mom1f",&(brp[0][0]),"mom1f/D");
  tree->Branch("mom1m",&(brp[1][0]),"mom1m/D");
  tree->Branch("mom2f",&(brp[0][1]),"mom2f/D");
  tree->Branch("mom2m",&(brp[1][1]),"mom2m/D");
  tree->Branch("momx1f",&(brpx[0][0]),"momx1f/D");
  tree->Branch("momx1m",&(brpx[1][0]),"momx1m/D");
  tree->Branch("momx2f",&(brpx[0][1]),"momx2f/D");
  tree->Branch("momx2m",&(brpx[1][1]),"momx2m/D");
  tree->Branch("momy1f",&(brpy[0][0]),"momy1f/D");
  tree->Branch("momy1m",&(brpy[1][0]),"momy1m/D");
  tree->Branch("momy2f",&(brpy[0][1]),"momy2f/D");
  tree->Branch("momy2m",&(brpy[1][1]),"momy2m/D");
  tree->Branch("momz1f",&(brpz[0][0]),"momz1f/D");
  tree->Branch("momz1m",&(brpz[1][0]),"momz1m/D");
  tree->Branch("momz2f",&(brpz[0][1]),"momz2f/D");
  tree->Branch("momz2m",&(brpz[1][1]),"momz2m/D");
  tree->Branch("momt1f",&(brpt[0][0]),"momt1f/D");
  tree->Branch("momt1m",&(brpt[1][0]),"momt1m/D");
  tree->Branch("momt2f",&(brpt[0][1]),"momt2f/D");
  tree->Branch("momt2m",&(brpt[1][1]),"momt2m/D");
  tree->Branch("momp1f",&(brpp[0][0]),"momp1f/D");
  tree->Branch("momp1m",&(brpp[1][0]),"momp1m/D");
  tree->Branch("momp2f",&(brpp[0][1]),"momp2f/D");
  tree->Branch("momp2m",&(brpp[1][1]),"momp2m/D");
  tree->Branch("momsumf",&(brps[0]),"momsumf/D");
  tree->Branch("momsumm",&(brps[1]),"momsumm/D");
  tree->Branch("momxsumf",&(brpsx[0]),"momxsumf/D");
  tree->Branch("momxsumm",&(brpsx[1]),"momxsumm/D");
  tree->Branch("momysumf",&(brpsy[0]),"momysumf/D");
  tree->Branch("momysumm",&(brpsy[1]),"momysumm/D");
  tree->Branch("momzsumf",&(brpsz[0]),"momzsumf/D");
  tree->Branch("momzsumm",&(brpsz[1]),"momzsumm/D");
  tree->Branch("distf",&(brdist[0]),"distf/D");
  tree->Branch("distm",&(brdist[1]),"distm/D");
  tree->Branch("massf",&(brm[0]),"massf/D");
  tree->Branch("massm",&(brm[1]),"massm/D");
  tree->Branch("mid1",&(brmid[0]),"mid1/I");
  tree->Branch("mid2",&(brmid[1]),"mid2/I");
  tree->Branch("cid1",&(brcid[0]),"cid1/I");
  tree->Branch("cid2",&(brcid[1]),"cid2/I");
  tree->Branch("x1",&(brx[0]),"x1/D");
  tree->Branch("x2",&(brx[1]),"x2/D");
  tree->Branch("y1",&(bry[0]),"y1/D");
  tree->Branch("y2",&(bry[1]),"y2/D");
  tree->Branch("z1",&(brz[0]),"z1/D");
  tree->Branch("z2",&(brz[1]),"z2/D");
  tree->Branch("gx1",&(brgx[0]),"gx1/D");
  tree->Branch("gx2",&(brgx[1]),"gx2/D");
  tree->Branch("gy1",&(brgy[0]),"gy2/D");
  tree->Branch("gy2",&(brgy[1]),"gy2/D");
  tree->Branch("gz1",&(brgz[0]),"gz1/D");
  tree->Branch("gz2",&(brgz[1]),"gz2/D");
  tree->Branch("adc1",&(bradc[0]),"adc1/D");
  tree->Branch("adc2",&(bradc[1]),"adc2/D");
  tree->Branch("t1",&(brt[0]),"t1/D");
  tree->Branch("t2",&(brt[1]),"t2/D");
  tree->Branch("fflag1",&(brfflag[0]),"fflag1/I");
  tree->Branch("fflag2",&(brfflag[1]),"fflag2/I");
  tree->Branch("width1",&(brwidth[0]),"width1/I");
  tree->Branch("width2",&(brwidth[1]),"width2/I");
}
E16ANA_GammaAnalyzer::~E16ANA_GammaAnalyzer(){
  for(int l=0;l<2;l++){
    for(int i=0;i<4;i++){

      delete hp[l][i];
      delete hpx[l][i];
      delete hpy[l][i];
      delete hpz[l][i];
      delete hpxy[l][i];
      delete hpt[l][i];
      delete hpp[l][i];
      delete hpvs[l][i];
      delete hpxvs[l][i];
      delete hpyvs[l][i];
      delete hpzvs[l][i];
      delete hpxyvs[l][i];
      delete hptvs[l][i];
      delete hppvs[l][i];

      delete hps[l][i];
      delete hpsx[l][i];
      delete hpsy[l][i];
      delete hpsz[l][i];
      delete hpsxy[l][i];
      delete heneasy[l][i];
      delete hptvsea[l][i];
      delete hdist[l][i];
      delete hpzpx[l][i];
      delete hm[l][i];
    }
  }
  for(int j=0;j<2;j++){
    delete hmid[j];
    delete hcid[j];
    delete hx[j];
    delete hy[j];
    delete hz[j];
    delete hgx[j];
    delete hgy[j];
    delete hgz[j];
    delete hadc[j];
    delete ht[j];
    delete hfflag[j];
    delete hwidth[j];
  }
  for(int j=0;j<9;j++){
    delete heventmp[j];
    delete hpairmp[j];
    delete hpairmpsame[j];
    delete hpairmpsameratio[j];
    delete hpairmpvssame[j];
  }
  delete tree;
}

int E16ANA_GammaAnalyzer::ModuleToIndex(int module){
  return module - 101;
}
int E16ANA_GammaAnalyzer::IndexToModule(int index){
  return index + 101;
}
void E16ANA_GammaAnalyzer::ClearHits(){
  ClearHit0();
  ClearHit1();
}
void E16ANA_GammaAnalyzer::ClearHit0(){
  ClearHit(hit0);
}
void E16ANA_GammaAnalyzer::ClearHit1(){
  ClearHit(hit1);
}
void E16ANA_GammaAnalyzer::ClearHit(hitset& hit){
  hit.id = -10000;
  hit.mid = -10000;
  hit.cid = -10000;
  hit.x = -10000.;
  hit.y = -10000.;
  hit.z = -10000.;
  hit.gx = -10000.;
  hit.gy = -10000.;
  hit.gz = -10000.;
  hit.adc = -10000.;
  hit.t = -10000.;
}
void E16ANA_GammaAnalyzer::SetHit0(int _id, int _mid, int _cid, double _x, double _y, double _z, double _gx, double _gy, double _gz, float _adc, float _t, int _fflag, float _width){
  SetHit(hit0, _id, _mid, _cid, _x, _y, _z, _gx, _gy, _gz, _adc, _t, _fflag, _width);
}
void E16ANA_GammaAnalyzer::SetHit0(hitset& hit){
  SetHit(hit0, hit);
}
void E16ANA_GammaAnalyzer::SetHit1(int _id, int _mid, int _cid, double _x, double _y, double _z, double _gx, double _gy, double _gz, float _adc, float _t, int _fflag, float _width){
  SetHit(hit1, _id, _mid, _cid, _x, _y, _z, _gx, _gy, _gz, _adc, _t, _fflag, _width);
}
void E16ANA_GammaAnalyzer::SetHit1(hitset& hit){
  SetHit(hit1, hit);
}
void E16ANA_GammaAnalyzer::SetHit(hitset& hit, int _id, int _mid, int _cid, double _x, double _y, double _z, double _gx, double _gy, double _gz, float _adc, float _t, int _fflag, float _width){
  hit.id = _id;
  hit.mid = _mid;
  hit.cid = _cid;
  hit.x = _x;
  hit.y = _y;
  hit.z = _z;
  hit.gx = _gx;
  hit.gy = _gy;
  hit.gz = _gz;
  hit.adc = _adc;
  hit.t = _t;
  hit.fflag = _fflag;
  hit.width = _width;
}
void E16ANA_GammaAnalyzer::SetHit(hitset& hit_unset, hitset& hit_set){
  hit_unset.id = hit_set.id;
  hit_unset.mid = hit_set.mid;
  hit_unset.cid = hit_set.cid;
  hit_unset.x = hit_set.x;
  hit_unset.y = hit_set.y;
  hit_unset.z = hit_set.z;
  hit_unset.gx = hit_set.gx;
  hit_unset.gy = hit_set.gy;
  hit_unset.gz = hit_set.gz;
  hit_unset.adc = hit_set.adc;
  hit_unset.t = hit_set.t;
  hit_unset.fflag = hit_set.fflag;
  hit_unset.width = hit_set.width;
}
bool E16ANA_GammaAnalyzer::Hit0isInvalid(){
  return HitisInvalid(hit0);
}
bool E16ANA_GammaAnalyzer::Hit1isInvalid(){
  return HitisInvalid(hit1);
}
bool E16ANA_GammaAnalyzer::HitisInvalid(hitset& hit){
  if( hit.fflag>=2 ) {return true;}
  else if( hit.adc<50 ) {return true;}
  else if( hit.width<5 || hit.width>20 ) {return true;}
  else if( hit.mid!=104 && hit.mid!=106 ) {return true;}
  else {return false;}
}
bool E16ANA_GammaAnalyzer::HitsareInvalid(){
  return HitsareInvalid(hit0,hit1);
}
bool E16ANA_GammaAnalyzer::HitsareInvalid(hitset& _hit0, hitset& _hit1){
  if( fabs( _hit0.t - _hit1.t ) > 4. ) {return true;}
  else if( _hit0.mid == _hit1.mid && IsNeighborBlock(_hit0, _hit1) ) {return true;}
  // else if( _hit0.mid != _hit1.mid ) {return true;}
  // else if( fabs( _hit0.mid -  _hit1.mid ) > 1 ) {return true;}
  // else if( fabs( _hit0.mid-105 ) != fabs( _hit1.mid-105 ) ) {return true;}
  // else if( _hit0.mid == _hit1.mid ) {return true;}
  else if( _hit0.mid<105 && _hit1.mid<105 ) {return true;}
  else if( _hit0.mid>105 && _hit1.mid>105 ) {return true;}
  else {return false;}
}
bool E16ANA_GammaAnalyzer::IsNeighborBlock(hitset& _hit0, hitset& _hit1){
  if( fabs(_hit0.x-_hit1.x)<150 && fabs(_hit0.y-_hit1.y)<170 ){return true;}
  return false;
}
// bool E16ANA_GammaAnalyzer::IsNeighborBlock(hitset& _hit0, hitset& _hit1){
//   TVector3 v0(_hit0.gx,_hit0.gy,_hit0.gz);
//   TVector3 v1(_hit1.gx,_hit1.gy,_hit1.gz);
//   double angle = v0.Angle(v1);
//   if( angle*1500.<244. ){return true;}
//   return false;
// }
void E16ANA_GammaAnalyzer::FillForeHist(){
  FillHist(0,hit0,hit1);
}
// void E16ANA_GammaAnalyzer::FillMixHist(){

//   std::vector<hitset> mixhitcands(0);
//   int ifore = gRandom->Uniform(0.5, 1.5);
//   // int imix  = (ifore+1)%2;
//   hitset forehit;
//   hitset mixhit;
//   if(ifore==0){
//     SetHit(forehit,hit0);
//     SetHit(mixhit,hit1);
//   }
//   else{
//     SetHit(forehit,hit1);
//     SetHit(mixhit,hit0);
//   }
//   int mixmid = ModuleToIndex(mixhit.mid);
//   for(int imix1=0; imix1<allmixhits[mixmid].size(); imix1++){
//     for(int imix2=0; imix2<allmixhits[mixmid].at(imix1).size(); imix2++){
//       hitset tmphit = allmixhits[mixmid].at(imix1).at(imix2);
//       if( HitsareInvalid( forehit, tmphit ) ) continue;
//       mixhitcands.push_back(tmphit);
//     }
//   }
//   if( mixhitcands.size()==0 ){return;}

//   int imixhit = gRandom->Uniform(0.5, (float)mixhitcands.size()-0.5);
//   for(int imix1=0; imix1<mixhitcands.size(); imix1++){
//     if( imix1==imixhit ){
//       ClearHit(mixhit);
//       SetHit(mixhit,mixhitcands.at(imix1));
//     }
//   }
//   FillHist(1,forehit,mixhit);

// }
void E16ANA_GammaAnalyzer::FillMixHist(){

  int ifore = gRandom->Uniform(0.5, 1.5);
  // int imix  = (ifore+1)%2;
  hitset forehit;
  if(ifore==0){
    SetHit(forehit,hit0);
  }
  else{
    SetHit(forehit,hit1);
  }
  for(int imix1=0; imix1<Mixevents.size(); imix1++){
    for(int imix2=0; imix2<Mixevents.at(imix1).size(); imix2++){
      hitset mixhit = Mixevents.at(imix1).at(imix2);
      if( HitisInvalid( mixhit ) ) continue;
      if( HitsareInvalid( forehit, mixhit ) ) continue;
      FillHist(1,forehit,mixhit);
    }
  }

}
void E16ANA_GammaAnalyzer::FillHist(int ifm, hitset& _hit0, hitset& _hit1){
  hitset hit[2];
  SetHit(hit[0],_hit0);
  SetHit(hit[1],_hit1);
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
      hp[ifm][idp]->Fill(mom[idp][ig].Mag());
      hpx[ifm][idp]->Fill(mom[idp][ig].X());
      hpy[ifm][idp]->Fill(mom[idp][ig].Y());
      hpz[ifm][idp]->Fill(mom[idp][ig].Z());
      hpxy[ifm][idp]->Fill(mom[idp][ig].Perp());
      hpzpx[ifm][idp]->Fill(mom[idp][ig].Z(),mom[idp][ig].X());
      // TVector3 rot(mom[idp][ig].Z(),mom[idp][ig].X(),mom[idp][ig].Y());
      TVector3 rot(mom[idp][ig].X(),mom[idp][ig].Y(),mom[idp][ig].Z());
      hpt[ifm][idp]->Fill(rot.Theta());
      hpp[ifm][idp]->Fill(rot.Phi());
      if(idp==2){
	brp[ifm][ig] = mom[idp][ig].Mag();
	brpx[ifm][ig] = mom[idp][ig].X();
	brpy[ifm][ig] = mom[idp][ig].Y();
	brpz[ifm][ig] = mom[idp][ig].Z();
	brpt[ifm][ig] = rot.Theta();
	brpp[ifm][ig] = rot.Phi();
      }
    }
    hpvs[ifm][idp]->Fill(mom[idp][0].Mag(),mom[idp][1].Mag());
    hpxvs[ifm][idp]->Fill(mom[idp][0].X(), mom[idp][1].X());
    hpyvs[ifm][idp]->Fill(mom[idp][0].Y(), mom[idp][1].Y());
    hpzvs[ifm][idp]->Fill(mom[idp][0].Z(), mom[idp][1].Z());
    hpxyvs[ifm][idp]->Fill(mom[idp][0].Perp(), mom[idp][1].Perp());
    hptvs[ifm][idp]->Fill(mom[idp][0].Theta(), mom[idp][1].Theta());
    hppvs[ifm][idp]->Fill(mom[idp][0].Phi(), mom[idp][1].Phi());
    momsum[idp] = mom[idp][0] + mom[idp][1];
    // if(momsum[idp].Perp()>1.){//tmp
    hps[ifm][idp]->Fill(momsum[idp].Mag());
    hpsx[ifm][idp]->Fill(momsum[idp].X());
    hpsy[ifm][idp]->Fill(momsum[idp].Y());
    hpsz[ifm][idp]->Fill(momsum[idp].Z());
    hpsxy[ifm][idp]->Fill(momsum[idp].Perp());
    double eneasy = fabs(mom[idp][0].Mag()-mom[idp][1].Mag())/(mom[idp][0].Mag()+mom[idp][1].Mag());
    heneasy[ifm][idp]->Fill( eneasy );
    hptvsea[ifm][idp]->Fill(eneasy, momsum[idp].Perp());
    double angle = mom[idp][0].Angle(mom[idp][1]);
    hdist[ifm][idp]->Fill(angle*1500.);
    im[idp] = sqrt( enesum*enesum - momsum[idp].Mag2() );
    hm[ifm][idp]->Fill( im[idp] );
    if(idp==2){
      brps[ifm] = momsum[idp].Mag();
      brpsx[ifm] = momsum[idp].X();
      brpsy[ifm] = momsum[idp].Y();
      brpsz[ifm] = momsum[idp].Z();
      brdist[ifm] = angle*1500.;
      brm[ifm] =  im[idp];
    }
    // }//tmp
  }
}
void E16ANA_GammaAnalyzer::FillHit0(){
  FillHit(0,hit0);
}
void E16ANA_GammaAnalyzer::FillHit1(){
  FillHit(1,hit1);
}
void E16ANA_GammaAnalyzer::FillHit(int type, hitset hit){
  hmid[type]->Fill(hit.mid);
  hcid[type]->Fill(hit.cid);
  hx[type]->Fill(hit.x);
  hy[type]->Fill(hit.y);
  hz[type]->Fill(hit.z);
  hgx[type]->Fill(hit.gx);
  hgy[type]->Fill(hit.gy);
  hgz[type]->Fill(hit.gz);
  hadc[type]->Fill(hit.adc);
  ht[type]->Fill(hit.t);
  hfflag[type]->Fill(hit.fflag);
  hwidth[type]->Fill(hit.width);
  brmid[type] = hit.mid;
  brcid[type] = hit.cid;
  brx[type] = hit.x;
  bry[type] = hit.y;
  brz[type] = hit.z;
  brgx[type] = hit.gx;
  brgy[type] = hit.gy;
  brgz[type] = hit.gz;
  bradc[type] = hit.adc;
  brt[type] = hit.t;
  brfflag[type] = hit.fflag;
  brwidth[type] = hit.width;

}
void E16ANA_GammaAnalyzer::ClearMixHit(){
  for(int i=0;i<9;i++){
    mixhits[i].clear();
  }
  Mixhits.clear();
}
void E16ANA_GammaAnalyzer::ClearMixEvent(){
  for(int i=0;i<9;i++){
    mixevents[i].clear();
  }
  Mixevents.clear();
}
void E16ANA_GammaAnalyzer::PushBackMixHit(hitset& hit){
  int imid = ModuleToIndex(hit.mid);
  mixhits[imid].push_back(hit);
  Mixhits.push_back(hit);
}
void E16ANA_GammaAnalyzer::PushBackMixEvent(){
  for(int i=0;i<9;i++){
    // if( mixhits[i].size()==0 ) continue;
    mixevents[i].push_back(mixhits[i]);
    if( mixevents[i].size() > n_mixevent_max ){
      mixevents[i].erase(mixevents[i].begin());
    }
  }
  // if( Mixhits.size()==0 ) continue;
  Mixevents.push_back(Mixhits);
  if( Mixevents.size() > n_mixevent_max ){
    Mixevents.erase(Mixevents.begin());
  }
}
void E16ANA_GammaAnalyzer::DrawTH1FCanvas(TCanvas* c, TString& fout, TH1F* h1, TH1F* h2, TH1F *h3, TH1F *h4){
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
void E16ANA_GammaAnalyzer::DrawTH2FCanvas(TCanvas* c, TString& fout, TH2F* h1, TH2F* h2, TH2F *h3, TH2F *h4){
  c->Clear();
  c->Divide(2,2);
  c->cd(1)->SetGrid();
  h1->Draw("colz");
  c->cd(2)->SetGrid();
  h2->Draw("colz");
  c->cd(3)->SetGrid();
  h3->Draw("colz");
  c->cd(4)->SetGrid();
  h4->Draw("colz");
  c->SaveAs(fout,"pdf");
}
double E16ANA_GammaAnalyzer::CalcMixScale(TH1F* h1, TH1F* h2){
  double integ1 = h1->Integral(h1->FindBin(0.8),h1->FindBin(1.5));
  double integ2 = h2->Integral(h2->FindBin(0.8),h2->FindBin(1.5));
  return integ1/integ2;
}
void E16ANA_GammaAnalyzer::DrawSameTH1FCanvas(TCanvas* c, TString& fout, TH1F* h1, TH1F* h2, double scale){
  c->Clear();
  h1->Draw();
  if( h2->GetEntries() != 0 ){
    h2->SetLineColor(2);
    h2->Scale(scale);
    h2->Draw("hist same");
  }
  c->SaveAs(fout,"pdf");
  if( h2->GetEntries() != 0 ){
    c->Clear();
    TH1F* hsub = (TH1F*)h1->Clone("hsub");
    hsub->Add(h2,-1);
    hsub->Draw("hist e");
    c->SaveAs(fout,"pdf");
  }
}
void E16ANA_GammaAnalyzer::Draw(TString& fout, TCanvas* c){
  for(int idp=0;idp<4;idp++){
    for(int ifm=0;ifm<2;ifm++){
      DrawTH1FCanvas(c,fout,hp[ifm][idp],hpx[ifm][idp],hpy[ifm][idp],hpz[ifm][idp]);
      DrawTH1FCanvas(c,fout,hp[ifm][idp],hpxy[ifm][idp],hpt[ifm][idp],hpp[ifm][idp]);
      DrawTH2FCanvas(c,fout,hpvs[ifm][idp],hpxvs[ifm][idp],hpyvs[ifm][idp],hpzvs[ifm][idp]);
      DrawTH2FCanvas(c,fout,hpzpx[ifm][idp],hpxyvs[ifm][idp],hptvs[ifm][idp],hppvs[ifm][idp]);
      DrawTH1FCanvas(c,fout,hps[ifm][idp],hpsx[ifm][idp],hpsy[ifm][idp],hpsz[ifm][idp]);
      c->Clear();
      c->Divide(2,2);
      c->cd(1);
      hpsxy[ifm][idp]->Draw();
      c->cd(2);
      heneasy[ifm][idp]->Draw();
      c->cd(3);
      hptvsea[ifm][idp]->Draw("colz");
      c->SaveAs(fout,"pdf");
    }
    double scale = CalcMixScale(hm[0][idp],hm[1][idp]);
    DrawSameTH1FCanvas(c,fout,hdist[0][idp],hdist[1][idp],scale);
    DrawSameTH1FCanvas(c,fout,hm[0][idp],hm[1][idp],scale);
  }
  DrawTH1FCanvas(c,fout,hmid[0],hmid[1],hcid[0],hcid[1]);
  DrawTH1FCanvas(c,fout,hx[0],hx[1],hy[0],hy[1]);
  DrawTH1FCanvas(c,fout,hz[0],hz[1],hgx[0],hgx[1]);
  DrawTH1FCanvas(c,fout,hgy[0],hgy[1],hgz[0],hgz[1]);
  DrawTH1FCanvas(c,fout,hadc[0],hadc[1],ht[0],ht[1]);
  DrawTH1FCanvas(c,fout,hfflag[0],hfflag[1],hfflag[0],hfflag[1]);
  DrawTH1FCanvas(c,fout,hwidth[0],hwidth[1],hwidth[0],hwidth[1]);
  DrawCount(c,fout);
}
//multiplicity
void E16ANA_GammaAnalyzer::ClearEventCount(){
  for(int i=0;i<9;i++){
    neventmp[i] = 0;
  }
}
void E16ANA_GammaAnalyzer::IncreaseEventCount(hitset& hit){
  if( HitisInvalid(hit) ) return;
  int imid = ModuleToIndex(hit.mid);
  neventmp[imid]++;
  neventmp[4]++;
}
void E16ANA_GammaAnalyzer::FillEventCount(){
  for(int i=0;i<9;i++){
    heventmp[i]->Fill( neventmp[i] );
  }
}
void E16ANA_GammaAnalyzer::ClearPairCount(){
  for(int i=0;i<9;i++){
    npairmp[i] = 0;
    npairmpsame[i] = 0;
  }
}
void E16ANA_GammaAnalyzer::IncreasePairCount(hitset& hit0, hitset& hit1){
  if( HitisInvalid(hit0) ) return;
  if( HitisInvalid(hit1) ) return;
  if( HitsareInvalid(hit0, hit1) ) return;
  int imid = ModuleToIndex(hit0.mid);
  npairmp[imid]++;
  npairmp[4]++;
  if( hit1.mid == hit0.mid ){
    npairmpsame[imid]++;
    npairmpsame[4]++;
  }
}
void E16ANA_GammaAnalyzer::FillPairCount(){
  for(int i=0;i<9;i++){
    hpairmp[i]->Fill( npairmp[i] );
    hpairmpsame[i]->Fill( npairmpsame[i] );
    if( npairmp[i]!=0 ){
      hpairmpsameratio[i]->Fill( (double)npairmpsame[i]/(double)npairmp[i] );
      hpairmpvssame[i]->Fill( npairmp[i], npairmpsame[i] );
    }
  }
}
void E16ANA_GammaAnalyzer::DrawCount(TCanvas* c, TString& fout){
  DrawCountTH1FCanvas(c,fout,heventmp);
  DrawCountTH1FCanvas(c,fout,hpairmp);
  DrawCountTH1FCanvas(c,fout,hpairmpsame);
  DrawCountTH1FCanvas(c,fout,hpairmpsameratio);
  c->Clear();
  c->Divide(3,3);
  for(int i=0;i<9;i++){
    c->cd(i+1);
    hpairmpvssame[i]->Draw("colz text");
  }
  c->SaveAs(fout,"pdf");
}
void E16ANA_GammaAnalyzer::DrawCountTH1FCanvas(TCanvas* c, TString& fout, TH1F* h[9]){
  c->Clear();
  c->Divide(3,3);
  for(int i=0;i<9;i++){
    c->cd(i+1)->SetLogy();
    h[i]->Draw();
  }
  c->SaveAs(fout,"pdf");
}
//multiplicity
void E16ANA_GammaAnalyzer::SetRootFile(char* fin_name){
  fin = new TFile(Form("%s",fin_name));
}
void E16ANA_GammaAnalyzer::DeleteRootFile(){
  delete fin;
}
void E16ANA_GammaAnalyzer::SetHists(){
  for(int l=0;l<2;l++){
    for(int i=0;i<4;i++){

      hp[l][i]->Reset();
      hpx[l][i]->Reset();
      hpy[l][i]->Reset();
      hpz[l][i]->Reset();
      hpxy[l][i]->Reset();
      hpt[l][i]->Reset();
      hpp[l][i]->Reset();

      hpvs[l][i]->Reset();
      hpxvs[l][i]->Reset();
      hpyvs[l][i]->Reset();
      hpzvs[l][i]->Reset();
      hpxyvs[l][i]->Reset();
      hptvs[l][i]->Reset();
      hppvs[l][i]->Reset();

      hps[l][i]->Reset();
      hpsx[l][i]->Reset();
      hpsy[l][i]->Reset();
      hpsz[l][i]->Reset();
      hpsxy[l][i]->Reset();
      heneasy[l][i]->Reset();
      hptvsea[l][i]->Reset();
      hdist[l][i]->Reset();
      hpzpx[l][i]->Reset();
      hm[l][i]->Reset();
    }
  }
  for(int j=0;j<2;j++){
    hmid[j]->Reset();
    hcid[j]->Reset();
    hx[j]->Reset();
    hy[j]->Reset();
    hz[j]->Reset();
    hgx[j]->Reset();
    hgy[j]->Reset();
    hgz[j]->Reset();
    hadc[j]->Reset();
    ht[j]->Reset();
    hfflag[j]->Reset();
    hwidth[j]->Reset();
  }

  for(int l=0;l<2;l++){
    for(int i=0;i<4;i++){

      hp[l][i] = (TH1F*)fin->Get(Form("hp%d%d",l,i));
      hpx[l][i] = (TH1F*)fin->Get(Form("hpx%d%d",l,i));
      hpy[l][i] = (TH1F*)fin->Get(Form("hpy%d%d",l,i));
      hpz[l][i] = (TH1F*)fin->Get(Form("hpz%d%d",l,i));
      hpxy[l][i] = (TH1F*)fin->Get(Form("hpxy%d%d",l,i));
      hpt[l][i] = (TH1F*)fin->Get(Form("hpt%d%d",l,i));
      hpp[l][i] = (TH1F*)fin->Get(Form("hpp%d%d",l,i));

      hpvs[l][i] = (TH2F*)fin->Get(Form("hpvs%d%d",l,i));
      hpxvs[l][i] = (TH2F*)fin->Get(Form("hpxvs%d%d",l,i));
      hpyvs[l][i] = (TH2F*)fin->Get(Form("hpyvs%d%d",l,i));
      hpzvs[l][i] = (TH2F*)fin->Get(Form("hpzvs%d%d",l,i));
      hpxyvs[l][i] = (TH2F*)fin->Get(Form("hpxyvs%d%d",l,i));
      hptvs[l][i] = (TH2F*)fin->Get(Form("hptvs%d%d",l,i));
      hppvs[l][i] = (TH2F*)fin->Get(Form("hppvs%d%d",l,i));

      hps[l][i] = (TH1F*)fin->Get(Form("hps%d%d",l,i));
      hpsx[l][i] = (TH1F*)fin->Get(Form("hpsx%d%d",l,i));
      hpsy[l][i] = (TH1F*)fin->Get(Form("hpsy%d%d",l,i));
      hpsz[l][i] = (TH1F*)fin->Get(Form("hpsz%d%d",l,i));
      hpsxy[l][i] = (TH1F*)fin->Get(Form("hpsxy%d%d",l,i));
      heneasy[l][i] = (TH1F*)fin->Get(Form("heneasy%d%d",l,i));
      hptvsea[l][i] = (TH2F*)fin->Get(Form("hptvsea%d%d",l,i));
      hdist[l][i] = (TH1F*)fin->Get(Form("hdist%d%d",l,i));
      hpzpx[l][i] = (TH2F*)fin->Get(Form("hpzpx%d%d",l,i));
      hm[l][i] = (TH1F*)fin->Get(Form("hm%d%d",l,i));
    }
  }
  for(int j=0;j<2;j++){
    hmid[j] = (TH1F*)fin->Get(Form("hmid%d",j));
    hcid[j] = (TH1F*)fin->Get(Form("hcid%d",j));
    hx[j] = (TH1F*)fin->Get(Form("hx%d",j));
    hy[j] = (TH1F*)fin->Get(Form("hy%d",j));
    hz[j] = (TH1F*)fin->Get(Form("hz%d",j));
    hgx[j] = (TH1F*)fin->Get(Form("hgx%d",j));
    hgy[j] = (TH1F*)fin->Get(Form("hgy%d",j));
    hgz[j] = (TH1F*)fin->Get(Form("hgz%d",j));
    hadc[j] = (TH1F*)fin->Get(Form("hadc%d",j));
    ht[j] = (TH1F*)fin->Get(Form("ht%d",j));
    hfflag[j] = (TH1F*)fin->Get(Form("hfflag%d",j));
    hwidth[j] = (TH1F*)fin->Get(Form("hwidth%d",j));
  }

}
void E16ANA_GammaAnalyzer::ClearBranch(){
  run_id = -10000;
  event_id = -10000;
  spill_id = -10000;
  for(int i=0;i<2;i++){
    for(int j=0;j<2;j++){
      brp[i][j] = -10000.;
      brpx[i][j] = -10000.;
      brpy[i][j] = -10000.;
      brpz[i][j] = -10000.;
      brpt[i][j] = -10000.;
      brpp[i][j] = -10000.;
    }
    brps[i] = -10000.;
    brpsx[i] = -10000.;
    brpsy[i] = -10000.;
    brpsz[i] = -10000.;
    brdist[i] = -10000.;
    brm[i] = -10000.;
    brmid[i] = -10000;
    brcid[i] = -10000;
    brx[i] = -10000.;
    bry[i] = -10000.;
    brz[i] = -10000.;
    brgx[i] = -10000.;
    brgy[i] = -10000.;
    brgz[i] = -10000.;
    bradc[i] = -10000.;
    brt[i] = -10000.;
    brfflag[i] = -10000;
    brwidth[i] = -10000;
  }
}
void E16ANA_GammaAnalyzer::SetBranchIds(int _run_id, int _event_id, int _spill_id){
  run_id = _run_id;
  event_id = _event_id;
  spill_id = _spill_id;
}
void E16ANA_GammaAnalyzer::FillTree(){
  tree->Fill();
}
