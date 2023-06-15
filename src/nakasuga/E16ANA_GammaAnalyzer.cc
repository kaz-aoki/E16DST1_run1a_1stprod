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

  ClearMixEvent();
  ClearMixAll();

  char name[2][5] = {"fore","mix"};
  for(int l=0;l<2;l++){
    for(int i=0;i<4;i++){
      for(int j=0;j<2;j++){
	hp[l][i][j] = new TH1F(Form("hp%d%d%d",l,i,j),Form("mom%d_%d_%s",j+1,decaypos[i],name[l]),100,0,2.5);
	hpx[l][i][j] = new TH1F(Form("hpx%d%d%d",l,i,j),Form("mom%dx_%d_%s",j+1,decaypos[i],name[l]),100,-2.5,2.5);
	hpy[l][i][j] = new TH1F(Form("hpy%d%d%d",l,i,j),Form("mom%dy_%d_%s",j+1,decaypos[i],name[l]),100,-2.5,2.5);
	hpz[l][i][j] = new TH1F(Form("hpz%d%d%d",l,i,j),Form("mom%dz_%d_%s",j+1,decaypos[i],name[l]),100,-2.5,2.5);
	hpt[l][i][j] = new TH1F(Form("hpt%d%d%d",l,i,j),Form("mom%dtheta_%d_%s",j+1,decaypos[i],name[l]),100,-2.5,2.5);
	hpp[l][i][j] = new TH1F(Form("hpp%d%d%d",l,i,j),Form("mom%dphi_%d_%s",j+1,decaypos[i],name[l]),100,-2.5,2.5);
      }
      hps[l][i] = new TH1F(Form("hps%d%d",l,i),Form("momsum_%d_%s",decaypos[i],name[l]),100,0,2.5);
      hpsx[l][i] = new TH1F(Form("hpsx%d%d",l,i),Form("momsum_x_%d_%s",decaypos[i],name[l]),100,-2.5,2.5);
      hpsy[l][i] = new TH1F(Form("hpsy%d%d",l,i),Form("momsum_y_%d_%s",decaypos[i],name[l]),100,-2.5,2.5);
      hpsz[l][i] = new TH1F(Form("hpsz%d%d",l,i),Form("momsum_z_%d_%s",decaypos[i],name[l]),100,-2.5,2.5);
      hdist[l][i] = new TH1F(Form("hdist%d%d",l,i),Form("2gamma_distance@LG_%d_%s",decaypos[i],name[l]),100,0,5000);
      hpzpx[l][i] = new TH2F(Form("hpzpx%d%d",l,i),Form("mom_zvsx_%d_%s",decaypos[i],name[l]),100,-2.5,2.5,100,-2.5,2.5);
      hm[l][i] = new TH1F(Form("hm%d%d",l,i),Form("IM_%d_%s",decaypos[i],name[l]),100,0,1.5);
    }
  }
}
E16ANA_GammaAnalyzer::~E16ANA_GammaAnalyzer(){
  for(int l=0;l<2;l++){
    for(int i=0;i<4;i++){
      for(int j=0;j<2;j++){
	delete hp[l][i][j];
	delete hpx[l][i][j];
	delete hpy[l][i][j];
	delete hpz[l][i][j];
	delete hpt[l][i][j];
	delete hpp[l][i][j];
      }
      delete hps[l][i];
      delete hpsx[l][i];
      delete hpsy[l][i];
      delete hpsz[l][i];
      delete hdist[l][i];
      delete hpzpx[l][i];
      delete hm[l][i];
    }
  }
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
void E16ANA_GammaAnalyzer::SetHit0(int _id, int _mid, int _cid, double _x, double _y, double _z, double _gx, double _gy, double _gz, float _adc, float _t, int _fflag){
  SetHit(hit0, _id, _mid, _cid, _x, _y, _z, _gx, _gy, _gz, _adc, _t, _fflag);
}
void E16ANA_GammaAnalyzer::SetHit1(int _id, int _mid, int _cid, double _x, double _y, double _z, double _gx, double _gy, double _gz, float _adc, float _t, int _fflag){
  SetHit(hit1, _id, _mid, _cid, _x, _y, _z, _gx, _gy, _gz, _adc, _t, _fflag);
}
void E16ANA_GammaAnalyzer::SetHit(hitset& hit, int _id, int _mid, int _cid, double _x, double _y, double _z, double _gx, double _gy, double _gz, float _adc, float _t, int _fflag){
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
}
bool E16ANA_GammaAnalyzer::Hit0isInvalid(){
  return HitisInvalid(hit0);
}
bool E16ANA_GammaAnalyzer::Hit1isInvalid(){
  return HitisInvalid(hit1);
}
bool E16ANA_GammaAnalyzer::HitisInvalid(hitset& hit){
  if( hit.fflag>=2 ) {return true;}
  else if( hit.adc<30 ) {return true;}
  else {return false;}
}
bool E16ANA_GammaAnalyzer::HitsareInvalid(){
  return HitsareInvalid(hit0,hit1);
}
bool E16ANA_GammaAnalyzer::HitsareInvalid(hitset& _hit0, hitset& _hit1){
  if( fabs( _hit0.t - _hit1.t ) > 4. ) {return true;}
  else if( _hit0.mid == _hit1.mid && IsNeighborBlock(_hit0, _hit1) ) {return true;}
  else {return false;}
}
bool E16ANA_GammaAnalyzer::IsNeighborBlock(hitset& _hit0, hitset& _hit1){
  if( fabs(_hit0.x-_hit0.x)<150 && fabs(_hit0.y-_hit0.y)<170 ){
    return true;
  }
  return false;
}
void E16ANA_GammaAnalyzer::FillForeHist(){
  FillHist(0,hit0,hit1);
}
void E16ANA_GammaAnalyzer::FillMixHist(){

  std::vector<hitset> mixhitcands(0);
  int ifore = gRandom->Uniform(0.5, 1.5);
  // int imix  = (ifore+1)%2;
  hitset forehit;
  hitset mixhit;
  if(ifore==0){
    SetHit(forehit,hit0);
    SetHit(mixhit,hit1);
  }
  else{
    SetHit(forehit,hit1);
    SetHit(mixhit,hit0);
  }
  int mixmid = ModuleToIndex(mixhit.mid);
  for(int imix1=0; imix1<allmixhits[mixmid].size(); imix1++){
    for(int imix2=0; imix2<allmixhits[mixmid].at(imix1).size(); imix2++){
      hitset tmphit = allmixhits[mixmid].at(imix1).at(imix2);
      if( HitsareInvalid( forehit, tmphit ) ) continue;
      mixhitcands.push_back(tmphit);
    }
  }
  if( mixhitcands.size()==0 ){return;}

  int imixhit = gRandom->Uniform(0.5, (float)mixhitcands.size()-0.5);
  for(int imix1=0; imix1<mixhitcands.size(); imix1++){
    if( imix1==imixhit ){
      ClearHit(mixhit);
      SetHit(mixhit,mixhitcands.at(imix1));
    }
  }
  FillHist(1,forehit,mixhit);

}
void E16ANA_GammaAnalyzer::FillHist(int type, hitset& _hit0, hitset& _hit1){
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
      hp[type][idp][ig]->Fill(mom[idp][ig].Mag());
      hpx[type][idp][ig]->Fill(mom[idp][ig].X());
      hpy[type][idp][ig]->Fill(mom[idp][ig].Y());
      hpz[type][idp][ig]->Fill(mom[idp][ig].Z());
      hpzpx[type][idp]->Fill(mom[idp][ig].Z(),mom[idp][ig].X());
      TVector3 rot(mom[idp][ig].Z(),mom[idp][ig].X(),mom[idp][ig].Y());
      hpt[type][idp][ig]->Fill(rot.Theta());
      hpp[type][idp][ig]->Fill(rot.Phi());
    }
    momsum[idp] = mom[idp][0] + mom[idp][1];
    hps[type][idp]->Fill(momsum[idp].Mag());
    hpsx[type][idp]->Fill(momsum[idp].X());
    hpsy[type][idp]->Fill(momsum[idp].Y());
    hpsz[type][idp]->Fill(momsum[idp].Z());
    double angle = mom[idp][0].Angle(mom[idp][1]);
    hdist[type][idp]->Fill(angle*1500.);
    im[idp] = sqrt( enesum*enesum - momsum[idp].Mag2() );
    hm[type][idp]->Fill( im[idp] );
  }
}
void E16ANA_GammaAnalyzer::ClearMixEvent(){
  for(int i=0;i<9;i++){
    eventmixhits[i].clear();
  }
}
void E16ANA_GammaAnalyzer::ClearMixAll(){
  for(int i=0;i<9;i++){
    allmixhits[i].clear();
  }
}
void E16ANA_GammaAnalyzer::PushBackMixHit(hitset& hit){
  int imid = ModuleToIndex(hit.mid);
  eventmixhits[imid].push_back(hit);
}
void E16ANA_GammaAnalyzer::PushBackMixEvent(){
  for(int i=0;i<9;i++){
    // if( eventmixhits[i].size()==0 ) continue;
    allmixhits[i].push_back(eventmixhits[i]);
    if( allmixhits[i].size() > mixevent ){
      allmixhits[i].erase(allmixhits[i].begin());
    }
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
void E16ANA_GammaAnalyzer::Draw(TString& fout, TCanvas* c){
  for(int idp=0;idp<4;idp++){
    for(int ifm=0;ifm<2;ifm++){
      for(int ig=0;ig<2;ig++){
	DrawTH1FCanvas(c,fout,hp[ifm][idp][ig],hpx[ifm][idp][ig],hpy[ifm][idp][ig],hpz[ifm][idp][ig]);
	DrawTH1FCanvas(c,fout,hp[ifm][idp][ig],hp[ifm][idp][ig], hpt[ifm][idp][ig],hpp[ifm][idp][ig]);
      }
      DrawTH1FCanvas(c,fout,hps[ifm][idp],hpsx[ifm][idp],hpsy[ifm][idp],hpsz[ifm][idp]);
      c->Clear();
      c->cd()->SetGrid();
      hpzpx[ifm][idp]->Draw("colz");
      c->SaveAs(fout,"pdf");
      c->Clear();
      hdist[ifm][idp]->Draw();
      c->SaveAs(fout,"pdf");
    }
    c->Clear();
    hm[0][idp]->Draw();
    hm[1][idp]->SetLineColor(2);
    hm[1][idp]->Draw("sames");
    c->SaveAs(fout,"pdf");
  }
}
void E16ANA_GammaAnalyzer::SetRootFile(char* fin_name){
  fin = new TFile(Form("%s",fin_name));
}
void E16ANA_GammaAnalyzer::DeleteRootFile(){
  delete fin;
}
void E16ANA_GammaAnalyzer::SetHists(){
  for(int l=0;l<2;l++){
    for(int i=0;i<4;i++){
      for(int j=0;j<2;j++){
	hp[l][i][j]->Reset();
	hpx[l][i][j]->Reset();
	hpy[l][i][j]->Reset();
	hpz[l][i][j]->Reset();
	hpt[l][i][j]->Reset();
	hpp[l][i][j]->Reset();
      }
      hps[l][i]->Reset();
      hpsx[l][i]->Reset();
      hpsy[l][i]->Reset();
      hpsz[l][i]->Reset();
      hdist[l][i]->Reset();
      hpzpx[l][i]->Reset();
      hm[l][i]->Reset();
    }
  }

  for(int l=0;l<2;l++){
    for(int i=0;i<4;i++){
      for(int j=0;j<2;j++){
	hp[l][i][j] = (TH1F*)fin->Get(Form("hp%d%d%d",l,i,j));
	hpx[l][i][j] = (TH1F*)fin->Get(Form("hpx%d%d%d",l,i,j));
	hpy[l][i][j] = (TH1F*)fin->Get(Form("hpy%d%d%d",l,i,j));
	hpz[l][i][j] = (TH1F*)fin->Get(Form("hpz%d%d%d",l,i,j));
	hpt[l][i][j] = (TH1F*)fin->Get(Form("hpt%d%d%d",l,i,j));
	hpp[l][i][j] = (TH1F*)fin->Get(Form("hpp%d%d%d",l,i,j));
      }
      hps[l][i] = (TH1F*)fin->Get(Form("hps%d%d",l,i));
      hpsx[l][i] = (TH1F*)fin->Get(Form("hpsx%d%d",l,i));
      hpsy[l][i] = (TH1F*)fin->Get(Form("hpsy%d%d",l,i));
      hpsz[l][i] = (TH1F*)fin->Get(Form("hpsz%d%d",l,i));
      hdist[l][i] = (TH1F*)fin->Get(Form("hdist%d%d",l,i));
      hpzpx[l][i] = (TH2F*)fin->Get(Form("hpzpx%d%d",l,i));
      hm[l][i] = (TH1F*)fin->Get(Form("hm%d%d",l,i));
    }
  }

}
