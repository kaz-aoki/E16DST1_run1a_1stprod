#include "E16ANA_LGCheckHist.hh"
#include "E16DST_Constant.hh"
#include <TH1.h>
#include <TLegend.h>
#include <TGraph.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

E16ANA_LGCheckHist::E16ANA_LGCheckHist(){
  double nsampled = (double)E16DST_Constant::NSamplesLG;
  for(int i=0;i<NMOD;i++){
    for(int j=0;j<NCH;j++){
      hpeak[i][j] = new TH1F(Form("hpeak%d%02d",i,j),Form("peak_%d_%d",IndexToModule(i),IndexToBlock(j)),300,0,300);
      hpeaktime[i][j] = new TH1F(Form("hpeaktime%d%02d",i,j),Form("peaktime_%d_%d",IndexToModule(i),IndexToBlock(j)),nsampled,0,nsampled);
      htiming[i][j] = new TH1F(Form("htiming%d%02d",i,j),Form("timing_%d_%d",IndexToModule(i),IndexToBlock(j)),nsampled,0,nsampled);
      hbaseline[i][j] = new TH1F(Form("hbaseline%d%02d",i,j),Form("baseline_%d_%d",IndexToModule(i),IndexToBlock(j)),100,-50,50);
      hbaselinerms[i][j] = new TH1F(Form("hbaselinerms%d%02d",i,j),Form("baselinerms_%d_%d",IndexToModule(i),IndexToBlock(j)),100,-20,20);
      hintegral[i][j] = new TH1F(Form("hintegral%d%02d",i,j),Form("integral_%d_%d",IndexToModule(i),IndexToBlock(j)),100,0,100);
      hnhits[i][j] = new TH1F(Form("hnhits%d%02d",i,j),Form("nhits_%d_%d",IndexToModule(i),IndexToBlock(j)),2,-0.5,1.5);
      // htimcor[i][j] = new TH2F(Form("htimcor%d%02d",i,j),Form("WFTime_vs_TrgTime_%d_%d",IndexToModule(i),IndexToBlock(j)),300,3000,3300,nsampled,0,nsampled);
      htimcor[i][j] = new TH2F(Form("htimcor%d%02d",i,j),Form("WFTime_vs_TrgTime_%d_%d",IndexToModule(i),IndexToBlock(j)),nsampled,-(nsampled/2.),nsampled/2.,nsampled,0,nsampled);
      ftiming[i][j] = new TF1(Form("ftiming%d%02d",i,j),"gaus",0,nsampled);
    }
  }
  for(int i=0;i<NMOD;i++){
    for(int j=0;j<NCH;j++){
      wfcount[i][j] = 0;
      for(int k=0;k<3;k++){
	for(int l=0;l<E16DST_Constant::NSamplesLG;l++){
	  wf[i][j][k][l] = -10000.;
	}
      }
    }
  }
}
E16ANA_LGCheckHist::~E16ANA_LGCheckHist(){
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
bool E16ANA_LGCheckHist::IsValidModuleId(int module){
  if( (module>=101 && module<=104) || (module>=106 && module<=109) ){
    return true;
  }
  else{
    std::cout<<"invalid module id"<<std::endl;
    return false;
  }
}
bool E16ANA_LGCheckHist::IsValidBlockId(int block){
  int x = block%10;
  int y = block/10;
  if( x>=0 && x<=5 && y>=0 && y<=5 ){
    return true;
  }
  else if( block==26 || block==36 ){
    return true;
  }
  else{
    // std::cout<<"invalid block id"<<std::endl;
    return false;
  }
}
int E16ANA_LGCheckHist::ModuleToIndex(int module){
  if(!IsValidModuleId(module)){
    return -1;
  }
  else if( module>=101 && module<=104 ){
    return module - 101;
  }
  else if( module>=106 && module<=109 ){
    return module - 102;
  }
  else{
    return -1;
  }
}
int E16ANA_LGCheckHist::IndexToModule(int index){
  if( index<0 || index>7 ){
    return -1;
  }
  else if( index>=0 && index<=3 ){
    return index + 101;
  }
  else if( index>=4 && index<=7 ){
    return index + 102;
  }
  else{
    return -1;
  }
}
int E16ANA_LGCheckHist::BlockToIndex(int block){
  if(!IsValidBlockId(block)){
    return -1;
  }
  int x = block%10;
  int y = block/10;
  int index = x+y*7;
  index = 41 - index;
  return index;
}
int E16ANA_LGCheckHist::IndexToBlock(int index){
  if( index<0 || index>41 ){
    return -1;
  }
  index = 41 - index;
  int x = index%7;
  int y = index/7;
  return x+y*10;
}
//////////////////////////////////////////////////////////////////////////
void E16ANA_LGCheckHist::Fill(int module, int block, double peak, int peaktime, double timing, double baseline, double baselinerms, double integral, int nhits){
  FillPeak(module,block,peak);
  FillPeakTime(module,block,peaktime);
  FillTiming(module,block,timing);
  FillBaseline(module,block,baseline);
  FillBaselineRms(module,block,baselinerms);
  FillIntegral(module,block,integral);
  FillNhits(module,block,nhits);
}
void E16ANA_LGCheckHist::FillPeak(int module, int block, double peak){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(block);
  hpeak[ii][ij]->Fill(peak);
}
void E16ANA_LGCheckHist::FillPeakTime(int module, int block, int peaktime){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(block);
  hpeaktime[ii][ij]->Fill(peaktime);
}
void E16ANA_LGCheckHist::FillTiming(int module, int block, double timing){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(block);
  htiming[ii][ij]->Fill(timing);
}
void E16ANA_LGCheckHist::FillBaseline(int module, int block, double baseline){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(block);
  hbaseline[ii][ij]->Fill(baseline);
}
void E16ANA_LGCheckHist::FillBaselineRms(int module, int block, double baselinerms){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(block);
  hbaselinerms[ii][ij]->Fill(baselinerms);
}
void E16ANA_LGCheckHist::FillIntegral(int module, int block, double integral){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(block);
  hintegral[ii][ij]->Fill(integral);
}
void E16ANA_LGCheckHist::FillNhits(int module, int block, bool nhits){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(block);
  hnhits[ii][ij]->Fill(nhits);
}
void E16ANA_LGCheckHist::FillTimeCorrelation(int module, int block, int peaktime, int trgtiming){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(block);
  htimcor[ii][ij]->Fill(trgtiming,peaktime);
}
//////////////////////////////////////////////////////////////////////////
void E16ANA_LGCheckHist::DrawEach(TString& fpdf, TCanvas* c){
  DrawEachPeak(fpdf,c);
  DrawEachPeakTime(fpdf,c);
  DrawEachTiming(fpdf,c);
  DrawEachBaseline(fpdf,c);
  DrawEachBaselineRms(fpdf,c);
  DrawEachIntegral(fpdf,c);
  DrawEachNhits(fpdf,c);
}
void E16ANA_LGCheckHist::DrawEachPeak(TString& fpdf, TCanvas* c){
  DrawEachHist(fpdf,c,hpeak);
}
void E16ANA_LGCheckHist::DrawEachPeakTime(TString& fpdf, TCanvas* c){
  DrawEachHist(fpdf,c,hpeaktime);
}
void E16ANA_LGCheckHist::DrawEachTiming(TString& fpdf, TCanvas* c){
  DrawEachHist(fpdf,c,htiming);
}
void E16ANA_LGCheckHist::DrawEachBaseline(TString& fpdf, TCanvas* c){
  DrawEachHist(fpdf,c,hbaseline);
}
void E16ANA_LGCheckHist::DrawEachBaselineRms(TString& fpdf, TCanvas* c){
  DrawEachHist(fpdf,c,hbaselinerms);
}
void E16ANA_LGCheckHist::DrawEachIntegral(TString& fpdf, TCanvas* c){
  DrawEachHist(fpdf,c,hintegral);
}
void E16ANA_LGCheckHist::DrawEachNhits(TString& fpdf, TCanvas* c){
  DrawEachHist(fpdf,c,hnhits);
}
void E16ANA_LGCheckHist::DrawEachHist(TString& fpdf, TCanvas* c, TH1F* h[NMOD][NCH]){
  for(int i=0;i<NMOD;i++){
    c->Clear();
    c->Divide(7,6);
    for(int j=0;j<NCH;j++){
      c->cd(j+1);
      h[i][j]->Draw("hist");
    }
    c->cd(1);
    TLegend *leg = new TLegend(0,0,1,1);
    leg->AddEntry((TObject*)0,Form("%d",IndexToModule(i)),"");
    leg->Draw("sames");
    c->SaveAs(fpdf,"pdf");
    delete leg;
  }
}
void E16ANA_LGCheckHist::DrawEachTimeCorrelation(TString& fpdf, TCanvas* c){
  for(int i=0;i<NMOD;i++){
    c->Clear();
    c->Divide(7,6);
    for(int j=0;j<NCH;j++){
      c->cd(j+1);
      htimcor[i][j]->Draw("colz");
    }
    c->cd(1);
    TLegend *leg = new TLegend(0,0,1,1);
    leg->AddEntry((TObject*)0,Form("%d",IndexToModule(i)),"");
    leg->Draw("sames");
    c->SaveAs(fpdf,"pdf");
    delete leg;
  }
}
//////////////////////////////////////////////////////////////////////////
void E16ANA_LGCheckHist::Draw(TString& fpdf, TCanvas* c){
  DrawPeak(fpdf,c);
  DrawPeakTime(fpdf,c);
  DrawTiming(fpdf,c);
  DrawBaseline(fpdf,c);
  DrawBaselineRms(fpdf,c);
  DrawIntegral(fpdf,c);
  DrawNhits(fpdf,c);
}
void E16ANA_LGCheckHist::DrawPeak(TString& fpdf, TCanvas* c){
  DrawGraph(fpdf,c,"PeakHeight",hpeak,gpeak);
}
void E16ANA_LGCheckHist::DrawPeakTime(TString& fpdf, TCanvas* c){
  DrawGraph(fpdf,c,"PeakTime",hpeaktime,gpeaktime);
}
void E16ANA_LGCheckHist::DrawTiming(TString& fpdf, TCanvas* c){
  DrawGraph(fpdf,c,"Timing",htiming,gtiming);
}
void E16ANA_LGCheckHist::DrawBaseline(TString& fpdf, TCanvas* c){
  DrawGraph(fpdf,c,"Baseline",hbaseline,gbaseline);
}
void E16ANA_LGCheckHist::DrawBaselineRms(TString& fpdf, TCanvas* c){
  DrawGraph(fpdf,c,"BaselineRms",hbaselinerms,gbaselinerms);
}
void E16ANA_LGCheckHist::DrawIntegral(TString& fpdf, TCanvas* c){
  DrawGraph(fpdf,c,"Integral",hintegral,gintegral);
}
void E16ANA_LGCheckHist::DrawNhits(TString& fpdf, TCanvas* c){
  DrawGraph(fpdf,c,"Nhits",hnhits,gnhits);
}
void E16ANA_LGCheckHist::DrawGraph(TString& fpdf, TCanvas* c, char* name, TH1F* h[NMOD][NCH], TGraph* g[NMOD]){
  double min = (h[0][0]->GetXaxis()->GetBinCenter(0)+h[0][0]->GetXaxis()->GetBinCenter(1))/2.;
  double max = min + (h[0][0]->GetBinWidth(1))*(h[0][0]->GetNbinsX());
  c->Clear();
  c->cd()->SetGrid();
  for(int i=0;i<NMOD;i++){
    double x[38];
    double y[38];
    int l=0;
    for(int j=0;j<NCH;j++){
      // int k = 41-j;
      int cid = IndexToBlock(j);
      if(!IsValidBlockId(cid)) continue;
      x[l] = double(cid + i*60);
      y[l] = h[i][j]->GetMean();
      l++;
    }
    g[i] = new TGraph(38,x,y);
    g[i]->SetLineColor(i+1);
    g[i]->SetMarkerColor(i+1);
    g[i]->SetMarkerStyle(i+24);
    if(i==0){
      g[i]->GetXaxis()->SetLimits(0,500);
      g[i]->SetMinimum(min);
      g[i]->SetMaximum(max);
      g[i]->SetTitle(Form("%s",name));
      g[i]->Draw("APL");
    }
    else{
      g[i]->Draw("PL");
    }
  }
  c->SaveAs(fpdf,"pdf");
}
//////////////////////////////////////////////////////////////////////////
void E16ANA_LGCheckHist::Draw2D(TString& fpdf, TCanvas* c){
  Draw2DPeak(fpdf,c);
  Draw2DPeakTime(fpdf,c);
  Draw2DTiming(fpdf,c);
  Draw2DBaseline(fpdf,c);
  Draw2DBaselineRms(fpdf,c);
  Draw2DIntegral(fpdf,c);
  Draw2DNhits(fpdf,c);
}
void E16ANA_LGCheckHist::Draw2DPeak(TString& fpdf, TCanvas* c){
  Draw2DHist(fpdf,c,"PeakHeight",hpeak,hhpeak);
}
void E16ANA_LGCheckHist::Draw2DPeakTime(TString& fpdf, TCanvas* c){
  Draw2DHist(fpdf,c,"PeakTime",hpeaktime,hhpeaktime);
}
void E16ANA_LGCheckHist::Draw2DTiming(TString& fpdf, TCanvas* c){
  Draw2DHist(fpdf,c,"Timing",htiming,hhtiming);
}
void E16ANA_LGCheckHist::Draw2DBaseline(TString& fpdf, TCanvas* c){
  Draw2DHist(fpdf,c,"Baseline",hbaseline,hhbaseline);
}
void E16ANA_LGCheckHist::Draw2DBaselineRms(TString& fpdf, TCanvas* c){
  Draw2DHist(fpdf,c,"BaselineRms",hbaselinerms,hhbaselinerms);
}
void E16ANA_LGCheckHist::Draw2DIntegral(TString& fpdf, TCanvas* c){
  Draw2DHist(fpdf,c,"Integral",hintegral,hhintegral);
}
void E16ANA_LGCheckHist::Draw2DNhits(TString& fpdf, TCanvas* c){
  Draw2DHist(fpdf,c,"Nhits",hnhits,hhnhits);
}
void E16ANA_LGCheckHist::Draw2DHist(TString& fpdf, TCanvas* c, char* name, TH1F* h[NMOD][NCH], TH2F* hh[NMOD]){
  c->Clear();
  c->Divide(4,2);
  for(int i=0;i<NMOD;i++){
    hh[i] = new TH2F(Form("hh%d",i),Form("%s_%d",name,IndexToModule(i)),7,-0.5,6.5,6,-0.5,5.5);
    for(int j=0;j<NCH;j++){
      int cid = IndexToBlock(j);
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
void E16ANA_LGCheckHist::MakeT0CalibFile(){
  std::ofstream fout("t0calib.txt");
  for(int i=0;i<NMOD;i++){
    int module = IndexToModule(i);
    for(int j=0;j<NCH;j++){
      int block = IndexToBlock(j);
      if(!IsValidBlockId(block)) continue;
      // double hmean = htiming[i][j]->GetMean();
      int maxbin = htiming[i][j]->GetMaximumBin();
      int centerbin = htiming[i][j]->FindBin(100);
      double binwidth = htiming[i][j]->GetBinWidth(100);
      double hmean = (maxbin-centerbin)*binwidth+100.;
      htiming[i][j]->Fit(Form("ftiming%d%02d",i,j),"","",hmean-10.,hmean+10.);
      double mean = ftiming[i][j]->GetParameter(1);
      double sigma = ftiming[i][j]->GetParameter(2);
      fout << module <<" "<< block <<" "<< mean <<" "<< sigma <<std::endl;
    }
  }
}
void E16ANA_LGCheckHist::SetWaveform(int module, int block, double waveform[E16DST_Constant::NSamplesLG]){
  int ii = ModuleToIndex(module);
  int ij = BlockToIndex(block);
  if( wfcount[ii][ij]>=0 && wfcount[ii][ij]<=2 ){
    for(int cell=0;cell<E16DST_Constant::NSamplesLG;cell++){
      wf[ii][ij][wfcount[ii][ij]][cell] = waveform[cell];
    }
    wfcount[ii][ij]++;
  }
}
void E16ANA_LGCheckHist::DrawWaveform(TString& fpdf){
  double x[E16DST_Constant::NSamplesLG];
  for(int cell=0;cell<E16DST_Constant::NSamplesLG;cell++){
    x[cell] = (double)cell;
  }
  TCanvas* c = new TCanvas("c","c",700,500);
  c->SaveAs(fpdf+"[","pdf");
  for(int i=0;i<NMOD;i++){
    int module = IndexToModule(i);
    for(int j=0;j<NCH;j++){
      int block = IndexToBlock(j);
      if(!IsValidBlockId(block)) continue;
      for(int k=0;k<3;k++){
	TGraph* g = new TGraph(E16DST_Constant::NSamplesLG,x,wf[i][j][k]);
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
