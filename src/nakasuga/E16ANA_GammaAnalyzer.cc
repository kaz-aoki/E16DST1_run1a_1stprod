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
  else if( hit.adc<30 ) {return true;}
  else if( hit.width<5 || hit.width>20 ) {return true;}
  else {return false;}
}
bool E16ANA_GammaAnalyzer::HitsareInvalid(){
  return HitsareInvalid(hit0,hit1);
}
bool E16ANA_GammaAnalyzer::HitsareInvalid(hitset& _hit0, hitset& _hit1){
  if( fabs( _hit0.t - _hit1.t ) > 4. ) {return true;}
  else if( _hit0.mid == _hit1.mid && IsNeighborBlock(_hit0, _hit1) ) {return true;}
  // else if( _hit0.mid != _hit1.mid ) {return true;}
  else if( fabs( _hit0.mid -  _hit1.mid ) > 1 ) {return true;}
  else {return false;}
}
bool E16ANA_GammaAnalyzer::IsNeighborBlock(hitset& _hit0, hitset& _hit1){
  if( fabs(_hit0.x-_hit1.x)<150 && fabs(_hit0.y-_hit1.y)<170 ){
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
      hp[ifm][idp][ig]->Fill(mom[idp][ig].Mag());
      hpx[ifm][idp][ig]->Fill(mom[idp][ig].X());
      hpy[ifm][idp][ig]->Fill(mom[idp][ig].Y());
      hpz[ifm][idp][ig]->Fill(mom[idp][ig].Z());
      hpzpx[ifm][idp]->Fill(mom[idp][ig].Z(),mom[idp][ig].X());
      TVector3 rot(mom[idp][ig].Z(),mom[idp][ig].X(),mom[idp][ig].Y());
      hpt[ifm][idp][ig]->Fill(rot.Theta());
      hpp[ifm][idp][ig]->Fill(rot.Phi());
      if(idp==2){
	brp[ifm][ig] = mom[idp][ig].Mag();
	brpx[ifm][ig] = mom[idp][ig].X();
	brpy[ifm][ig] = mom[idp][ig].Y();
	brpz[ifm][ig] = mom[idp][ig].Z();
	brpt[ifm][ig] = rot.Theta();
	brpp[ifm][ig] = rot.Phi();
      }
    }
    momsum[idp] = mom[idp][0] + mom[idp][1];
    hps[ifm][idp]->Fill(momsum[idp].Mag());
    hpsx[ifm][idp]->Fill(momsum[idp].X());
    hpsy[ifm][idp]->Fill(momsum[idp].Y());
    hpsz[ifm][idp]->Fill(momsum[idp].Z());
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
  DrawTH1FCanvas(c,fout,hmid[0],hmid[1],hcid[0],hcid[1]);
  DrawTH1FCanvas(c,fout,hx[0],hx[1],hy[0],hy[1]);
  DrawTH1FCanvas(c,fout,hz[0],hz[1],hgx[0],hgx[1]);
  DrawTH1FCanvas(c,fout,hgy[0],hgy[1],hgz[0],hgz[1]);
  DrawTH1FCanvas(c,fout,hadc[0],hadc[1],ht[0],ht[1]);
  DrawTH1FCanvas(c,fout,hfflag[0],hfflag[1],hfflag[0],hfflag[1]);
  DrawTH1FCanvas(c,fout,hwidth[0],hwidth[1],hwidth[0],hwidth[1]);
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
