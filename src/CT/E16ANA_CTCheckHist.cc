#include "E16ANA_CTCheckHist.hh"
#include "E16DST_Constant.hh"
#include <TH1.h>
#include <TLegend.h>
#include <TGraph.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

E16ANA_CTCheckHist::E16ANA_CTCheckHist(){
  for(int i=0;i<NMOD;i++){
    for(int j=0;j<NCH;j++){
      hpeak[i][j] = new TH1F(Form("hpeak%d%02d",i,j),Form("peak_%d_%d",IndexToModule(i),IndexToBlock(i,j)),300,0,300);
      hpeaktime[i][j] = new TH1F(Form("hpeaktime%d%02d",i,j),Form("peaktime_%d_%d",IndexToModule(i),IndexToBlock(i,j)),200,0,200);
      htiming[i][j] = new TH1F(Form("htiming%d%02d",i,j),Form("timing_%d_%d",IndexToModule(i),IndexToBlock(i,j)),200,0,200);
      hbaseline[i][j] = new TH1F(Form("hbaseline%d%02d",i,j),Form("baseline_%d_%d",IndexToModule(i),IndexToBlock(i,j)),100,-50,50);
      hbaselinerms[i][j] = new TH1F(Form("hbaselinerms%d%02d",i,j),Form("baselinerms_%d_%d",IndexToModule(i),IndexToBlock(i,j)),100,-20,20);
      hintegral[i][j] = new TH1F(Form("hintegral%d%02d",i,j),Form("integral_%d_%d",IndexToModule(i),IndexToBlock(i,j)),100,0,100);
      hnhits[i][j] = new TH1F(Form("hnhits%d%02d",i,j),Form("nhits_%d_%d",IndexToModule(i),IndexToBlock(i,j)),2,-0.5,1.5);
      htimcor[i][j] = new TH2F(Form("htimcor%d%02d",i,j),Form("WFTime_vs_TrgTime_%d_%d",IndexToModule(i),IndexToBlock(i,j)),300,3000,3300,200,0,200);
      ftiming[i][j] = new TF1(Form("ftiming%d%02d",i,j),"gaus",0,200);
    }
  }
  for(int i=0;i<NMOD;i++){
    for(int j=0;j<NCH;j++){
      wfcount[i][j] = 0;
      for(int k=0;k<3;k++){
	for(int l=0;l<E16DST_Constant::NSamplesCT;l++){
	  wf[i][j][k][l] = -10000.;
	}
      }
    }
  }
}
E16ANA_CTCheckHist::~E16ANA_CTCheckHist(){
  for(int i=0;i<NMOD;i++){
    for(int j=0;j<NCH;j++){
      delete hpeak[i][j];
      delete hpeaktime[i][j];
      delete htiming[i][j];
      delete hbaseline[i][j];
      delete hbaselinerms[i][j];
      delete hintegral[i][j];
      delete hnhits[i][j];
    }
  }
}
bool E16ANA_CTCheckHist::IsValidModuleId(int module){ // for run0e CT
  if( module==104 || module==106 ){
    return true;
  }
  else{
    // std::cout<<"invalid module id"<<std::endl;
    return false;
  }
}
bool E16ANA_CTCheckHist::IsValidBlockId(int module, int block){
  int x = block%10;
  int y = block/10;
  if(!IsValidModuleId(module)){
    return false;
  }
  if(module==106){
    if( (block>=0 && block<=7) || (x>=0 && x<=3 && y>=1 && y<=5) ){
      return true;
    }
    else{
      return false;
    }
  }
  else if(module==104){
    if( (block>=0 && block<=5) || block==14 || block==15 || (x>=5 && x<=6 && y>=2 && y<=3) || (x>=4 && x<=5 && y>=4 && y<=5) ){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    // std::cout<<"invalid block id"<<std::endl;
    return false;
  }
}
int E16ANA_CTCheckHist::ModuleToIndex(int module){
  if(!IsValidModuleId(module)){
    return -1;
  }
  else if( module==106 ){
    return 0;
  }
  else if( module==104 ){
    return 1;
  }
  else{
    return -1;
  }
}
int E16ANA_CTCheckHist::IndexToModule(int index){
  if( index!=0 && index!=1 ){
    return -1;
  }
  else if( index==0 ){
    return 106;
  }
  else if( index==1 ){
    return 104;
  }
  else{
    return -1;
  }
}
int E16ANA_CTCheckHist::BlockToIndex(int module, int block){
  int x = block%10;
  int y = block/10;
  if(!IsValidModuleId(module)){
    return -1;
  }
  if(!IsValidBlockId(module,block)){
    return -1;
  }
  for(int j=0;j<NCH;j++){
    if( block==blocklist[ModuleToIndex(module)][j] ){
      return j;
    }
  }
  return -1;
}
int E16ANA_CTCheckHist::IndexToBlock(int index_m, int index_b){
  if( index_m!=0 && index_m!=1 ){
    return -1;
  }
  if( index_b<0 || index_b>=NCH ){
    return -1;
  }
  return blocklist[index_m][index_b];
}
bool E16ANA_CTCheckHist::LGwCT(int lgmodule, int lgblock){
  if(lgmodule==104){
    return IsValidBlockId(lgmodule, lgblock);
  }
  else if(lgmodule==106){
    if( lgblock%10==0 || lgblock%10==1 ){
      return true;
    }
    else if( lgblock>=2 && lgblock<=5 ){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}
int E16ANA_CTCheckHist::LGToCT0Module(int lgmodule){
  return lgmodule;
}
int E16ANA_CTCheckHist::LGToCT1Module(int lgmodule){
  return lgmodule;
}
int E16ANA_CTCheckHist::LGToCT0Block(int lgmodule, int lgblock){
  if(lgmodule==104){
    return lgblock;
  }
  else if(lgmodule==106){
    if(lgblock%10==0){
      return lgblock;
    }
    else if(lgblock%10==1){
      return lgblock+1;
    }
    else if( lgblock>=2 && lgblock<=5 ){
      return lgblock+2;
    }
    else{
      return -10000;
    }
  }
  else{
    return -10000;
  }
}
int E16ANA_CTCheckHist::LGToCT1Block(int lgmodule, int lgblock){
  if(lgmodule==104){
    return -10000;
  }
  else if(lgmodule==106){
    if(lgblock%10==0){
      return lgblock+1;
    }
    else if(lgblock%10==1){
      return lgblock+2;
    }
    else{
      return -10000;
    }
  }
  else{
    return -10000;
  }
}
//////////////////////////////////////////////////////////////////////////
void E16ANA_CTCheckHist::Fill(int module, int block, double peak, int peaktime, double timing, double baseline, double baselinerms, double integral, int nhits){
  FillPeak(module,block,peak);
  FillPeakTime(module,block,peaktime);
  FillTiming(module,block,timing);
  FillBaseline(module,block,baseline);
  FillBaselineRms(module,block,baselinerms);
  FillIntegral(module,block,integral);
  FillNhits(module,block,nhits);
}
void E16ANA_CTCheckHist::FillPeak(int module, int block, double peak){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(module,block);
  hpeak[ii][ij]->Fill(peak);
}
void E16ANA_CTCheckHist::FillPeakTime(int module, int block, int peaktime){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(module,block);
  hpeaktime[ii][ij]->Fill(peaktime);
}
void E16ANA_CTCheckHist::FillTiming(int module, int block, double timing){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(module,block);
  htiming[ii][ij]->Fill(timing);
}
void E16ANA_CTCheckHist::FillBaseline(int module, int block, double baseline){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(module,block);
  hbaseline[ii][ij]->Fill(baseline);
}
void E16ANA_CTCheckHist::FillBaselineRms(int module, int block, double baselinerms){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(module,block);
  hbaselinerms[ii][ij]->Fill(baselinerms);
}
void E16ANA_CTCheckHist::FillIntegral(int module, int block, double integral){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(module,block);
  hintegral[ii][ij]->Fill(integral);
}
void E16ANA_CTCheckHist::FillNhits(int module, int block, bool nhits){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(module,block);
  hnhits[ii][ij]->Fill(nhits);
}
void E16ANA_CTCheckHist::FillTimeCorrelation(int module, int block, int peaktime, int trgtiming){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(module,block);
  htimcor[ii][ij]->Fill(trgtiming,peaktime);
}
//////////////////////////////////////////////////////////////////////////
void E16ANA_CTCheckHist::DrawEach(TString& fpdf, TCanvas* c){
  DrawEachPeak(fpdf,c);
  DrawEachPeakTime(fpdf,c);
  DrawEachTiming(fpdf,c);
  DrawEachBaseline(fpdf,c);
  DrawEachBaselineRms(fpdf,c);
  DrawEachIntegral(fpdf,c);
  DrawEachNhits(fpdf,c);
}
void E16ANA_CTCheckHist::DrawEachPeak(TString& fpdf, TCanvas* c){
  DrawEachHist(fpdf,c,hpeak);
}
void E16ANA_CTCheckHist::DrawEachPeakTime(TString& fpdf, TCanvas* c){
  DrawEachHist(fpdf,c,hpeaktime);
}
void E16ANA_CTCheckHist::DrawEachTiming(TString& fpdf, TCanvas* c){
  DrawEachHist(fpdf,c,htiming);
}
void E16ANA_CTCheckHist::DrawEachBaseline(TString& fpdf, TCanvas* c){
  DrawEachHist(fpdf,c,hbaseline);
}
void E16ANA_CTCheckHist::DrawEachBaselineRms(TString& fpdf, TCanvas* c){
  DrawEachHist(fpdf,c,hbaselinerms);
}
void E16ANA_CTCheckHist::DrawEachIntegral(TString& fpdf, TCanvas* c){
  DrawEachHist(fpdf,c,hintegral);
}
void E16ANA_CTCheckHist::DrawEachNhits(TString& fpdf, TCanvas* c){
  DrawEachHist(fpdf,c,hnhits);
}
void E16ANA_CTCheckHist::DrawEachHist(TString& fpdf, TCanvas* c, TH1F* h[NMOD][NCH]){
  for(int i=0;i<NMOD;i++){
    c->Clear();
    c->Divide(4+4*(1-i),4);
    for(int j=0;j<NCH;j++){
      if(i==1&&j>=16) continue;
      c->cd(j+1);
      h[i][j]->Draw("hist");
    }
    // c->cd(1);
    // TLegend *leg = new TLegend(0,0,1,1);
    // leg->AddEntry((TObject*)0,Form("%d",IndexToModule(i)),"");
    // leg->Draw("sames");
    c->SaveAs(fpdf,"pdf");
    // delete leg;
  }
}
void E16ANA_CTCheckHist::DrawEachTimeCorrelation(TString& fpdf, TCanvas* c){
  for(int i=0;i<NMOD;i++){
    c->Clear();
    c->Divide(4+4*(1-i),4);
    for(int j=0;j<NCH;j++){
      if(i==1&&j>=16) continue;
      c->cd(j+1);
      htimcor[i][j]->Draw("colz");
    }
    // c->cd(1);
    // TLegend *leg = new TLegend(0,0,1,1);
    // leg->AddEntry((TObject*)0,Form("%d",IndexToModule(i)),"");
    // leg->Draw("sames");
    c->SaveAs(fpdf,"pdf");
    // delete leg;
  }
}
//////////////////////////////////////////////////////////////////////////
void E16ANA_CTCheckHist::Draw(TString& fpdf, TCanvas* c){
  DrawPeak(fpdf,c);
  DrawPeakTime(fpdf,c);
  DrawTiming(fpdf,c);
  DrawBaseline(fpdf,c);
  DrawBaselineRms(fpdf,c);
  DrawIntegral(fpdf,c);
  DrawNhits(fpdf,c);
}
void E16ANA_CTCheckHist::DrawPeak(TString& fpdf, TCanvas* c){
  DrawGraph(fpdf,c,"PeakHeight",hpeak,gpeak);
}
void E16ANA_CTCheckHist::DrawPeakTime(TString& fpdf, TCanvas* c){
  DrawGraph(fpdf,c,"PeakTime",hpeaktime,gpeaktime);
}
void E16ANA_CTCheckHist::DrawTiming(TString& fpdf, TCanvas* c){
  DrawGraph(fpdf,c,"Timing",htiming,gtiming);
}
void E16ANA_CTCheckHist::DrawBaseline(TString& fpdf, TCanvas* c){
  DrawGraph(fpdf,c,"Baseline",hbaseline,gbaseline);
}
void E16ANA_CTCheckHist::DrawBaselineRms(TString& fpdf, TCanvas* c){
  DrawGraph(fpdf,c,"BaselineRms",hbaselinerms,gbaselinerms);
}
void E16ANA_CTCheckHist::DrawIntegral(TString& fpdf, TCanvas* c){
  DrawGraph(fpdf,c,"Integral",hintegral,gintegral);
}
void E16ANA_CTCheckHist::DrawNhits(TString& fpdf, TCanvas* c){
  DrawGraph(fpdf,c,"Nhits",hnhits,gnhits);
}
void E16ANA_CTCheckHist::DrawGraph(TString& fpdf, TCanvas* c, char* name, TH1F* h[NMOD][NCH], TGraph* g[NMOD]){
  double min = (h[0][0]->GetXaxis()->GetBinCenter(0)+h[0][0]->GetXaxis()->GetBinCenter(1))/2.;
  double max = min + (h[0][0]->GetBinWidth(1))*(h[0][0]->GetNbinsX());
  c->Clear();
  c->cd()->SetGrid();
  for(int i=0;i<NMOD;i++){
    double x[NCH];
    double y[NCH];
    for(int j=0;j<NCH;j++){
      int cid = IndexToBlock(i,j);
      // if(!IsValidBlockId(IndexToModule(i),cid)) continue;
      x[j] = double(cid + i*60);
      y[j] = h[i][j]->GetMean();
    }
    g[i] = new TGraph(NCH,x,y);
    g[i]->SetLineColor(i+1);
    g[i]->SetMarkerColor(i+1);
    g[i]->SetMarkerStyle(i+24);
    if(i==0){
      g[i]->GetXaxis()->SetLimits(0,double(NMOD)*60.+10.);
      g[i]->SetMinimum(min);
      g[i]->SetMaximum(max);
      g[i]->SetTitle(Form("%s",name));
      g[i]->Draw("AP");
    }
    else{
      g[i]->Draw("P");
    }
  }
  c->SaveAs(fpdf,"pdf");
}
//////////////////////////////////////////////////////////////////////////
void E16ANA_CTCheckHist::Draw2D(TString& fpdf, TCanvas* c){
  Draw2DPeak(fpdf,c);
  Draw2DPeakTime(fpdf,c);
  Draw2DTiming(fpdf,c);
  Draw2DBaseline(fpdf,c);
  Draw2DBaselineRms(fpdf,c);
  Draw2DIntegral(fpdf,c);
  Draw2DNhits(fpdf,c);
}
void E16ANA_CTCheckHist::Draw2DPeak(TString& fpdf, TCanvas* c){
  Draw2DHist(fpdf,c,"PeakHeight",hpeak,hhpeak);
}
void E16ANA_CTCheckHist::Draw2DPeakTime(TString& fpdf, TCanvas* c){
  Draw2DHist(fpdf,c,"PeakTime",hpeaktime,hhpeaktime);
}
void E16ANA_CTCheckHist::Draw2DTiming(TString& fpdf, TCanvas* c){
  Draw2DHist(fpdf,c,"Timing",htiming,hhtiming);
}
void E16ANA_CTCheckHist::Draw2DBaseline(TString& fpdf, TCanvas* c){
  Draw2DHist(fpdf,c,"Baseline",hbaseline,hhbaseline);
}
void E16ANA_CTCheckHist::Draw2DBaselineRms(TString& fpdf, TCanvas* c){
  Draw2DHist(fpdf,c,"BaselineRms",hbaselinerms,hhbaselinerms);
}
void E16ANA_CTCheckHist::Draw2DIntegral(TString& fpdf, TCanvas* c){
  Draw2DHist(fpdf,c,"Integral",hintegral,hhintegral);
}
void E16ANA_CTCheckHist::Draw2DNhits(TString& fpdf, TCanvas* c){
  Draw2DHist(fpdf,c,"Nhits",hnhits,hhnhits);
}
void E16ANA_CTCheckHist::Draw2DHist(TString& fpdf, TCanvas* c, char* name, TH1F* h[NMOD][NCH], TH2F* hh[NMOD]){
  c->Clear();
  c->Divide(2,1);
  for(int i=0;i<NMOD;i++){
    if(i==1){
      hh[i] = new TH2F(Form("hh%d",i),Form("%s_%d",name,IndexToModule(i)),7,-0.5,6.5,6,-0.5,5.5);
    }
    else{
      hh[i] = new TH2F(Form("hh%d",i),Form("%s_%d",name,IndexToModule(i)),12,-0.5,11.5,6,-0.5,5.5);
    }
    for(int j=0;j<NCH;j++){
      int cid = IndexToBlock(i,j);
      int x = cid%10;
      int y = cid/10;
      hh[i]->SetBinContent(hh[i]->GetXaxis()->FindBin(x),hh[i]->GetXaxis()->FindBin(y),h[i][j]->GetMean());
    }
    c->cd(i+1);
    hh[i]->Draw("colz");
  }
  c->SaveAs(fpdf,"pdf");
}
//////////////////////////////////////////////////////////////////////////
// void E16ANA_CTCheckHist::MakeT0CalibFile(){
//   std::ofstream fout("t0calib.txt");
//   for(int i=0;i<NMOD;i++){
//     int module = IndexToModule(i);
//     for(int j=0;j<NCH;j++){
//       int block = IndexToBlock(i,j);
//       if(!IsValidBlockId(module,block)) continue;
//       // double hmean = htiming[i][j]->GetMean();
//       int maxbin = htiming[i][j]->GetMaximumBin();
//       int centerbin = htiming[i][j]->FindBin(100);
//       double binwidth = htiming[i][j]->GetBinWidth(100);
//       double hmean = (maxbin-centerbin)*binwidth+100.;
//       htiming[i][j]->Fit(Form("ftiming%d%02d",i,j),"","",hmean-10.,hmean+10.);
//       double mean = ftiming[i][j]->GetParameter(1);
//       double sigma = ftiming[i][j]->GetParameter(2);
//       fout << module <<" "<< block <<" "<< mean <<" "<< sigma <<std::endl;
//     }
//   }
// }
void E16ANA_CTCheckHist::SetWaveform(int module, int block, double waveform[E16DST_Constant::NSamplesCT]){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(module,block);
  if( wfcount[ii][ij]>=0 && wfcount[ii][ij]<=2 ){
    for(int cell=0;cell<E16DST_Constant::NSamplesCT;cell++){
      wf[ii][ij][wfcount[ii][ij]][cell] = waveform[cell];
    }
    wfcount[ii][ij]++;
  }
}
void E16ANA_CTCheckHist::DrawWaveform(TString& fpdf){
  double x[E16DST_Constant::NSamplesCT];
  for(int cell=0;cell<E16DST_Constant::NSamplesCT;cell++){
    x[cell] = (double)cell;
  }
  TCanvas* c = new TCanvas("c","c",700,500);
  c->SaveAs(fpdf+"[","pdf");
  for(int i=0;i<NMOD;i++){
    int module = IndexToModule(i);
    for(int j=0;j<NCH;j++){
      int block = IndexToBlock(i,j);
      if(!IsValidBlockId(module,block)) continue;
      for(int k=0;k<3;k++){
	TGraph* g = new TGraph(E16DST_Constant::NSamplesCT,x,wf[i][j][k]);
	g->SetTitle(Form("%d-%d ",module,block));
	g->Draw("A*L");
	c->SaveAs(fpdf,"pdf");
	delete g;
      }
    }
  }
  c->SaveAs(fpdf+"]","pdf");
  delete c;
}
