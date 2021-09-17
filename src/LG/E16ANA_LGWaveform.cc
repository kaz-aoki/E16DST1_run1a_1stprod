#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <TH1.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TSpectrum.h>

#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"
#include "E16DST_DST1Constant.hh"
#include "E16ANA_LGConstant.hh"

#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1DefaultFilePath.hh"

#include <algorithm>
#include <unordered_map>   

using namespace E16ANA_LGConstant;

TGraph* E16ANA_LGWaveform::gtmpl = nullptr;

E16ANA_LGWaveform::E16ANA_LGWaveform()
    : peak(E16DST_DST1Constant::kInvalidValue),
      peakx(E16DST_DST1Constant::kInvalidValue),
      timing(E16DST_DST1Constant::kInvalidValue),
      baseline(E16DST_DST1Constant::kInvalidValue),
      baselinerms(E16DST_DST1Constant::kInvalidValue),
      integral(E16DST_DST1Constant::kInvalidValue),
      falltime(E16DST_DST1Constant::kInvalidValue),
      offset(E16DST_DST1Constant::kInvalidValue),
      nps_full(E16DST_DST1Constant::kInvalidValue),
      nps_short(E16DST_DST1Constant::kInvalidValue),
      nps_fit(E16DST_DST1Constant::kInvalidValue) {

    for(int i=0;i<E16DST_Constant::NSamplesLG;i++){
      wf[i] = E16DST_DST1Constant::kInvalidValue;
      dwf[i] = E16DST_DST1Constant::kInvalidValue;
      mwf[i] = E16DST_DST1Constant::kInvalidValue;
    }
    for(int i=0;i<30;i++){
      ps_full[i] = E16DST_DST1Constant::kInvalidValue;
      pxs_full[i] = E16DST_DST1Constant::kInvalidValue;
      ps_short[i] = E16DST_DST1Constant::kInvalidValue;
      pxs_short[i] = E16DST_DST1Constant::kInvalidValue;
      ps_fit[i] = E16DST_DST1Constant::kInvalidValue;
      pxs_fit[i] = E16DST_DST1Constant::kInvalidValue;
    }
  }

void E16ANA_LGWaveform::SimpleMethod(double* _wf){

  SetWaveform(_wf);
  CalcPeak();
  CalcTiming();
  CalcBaseline();
  peak = peak - baseline;
  CalcIntegral();

}

void E16ANA_LGWaveform::FitMethod(double* _wf, double t0){

  SimpleMethod(_wf);
  SetT0(t0);
  CalcWaveforms();
  CalcPeaks();

}

void E16ANA_LGWaveform::CalcPeak(){

  for(int cell=5; cell<E16DST_Constant::NSamplesLG; cell++){
    if(wf[cell]>peak){
      if( E16ANA_LGConstant::kPeakSearchStart<cell && cell<E16ANA_LGConstant::kPeakSearchEnd ){
	peak = wf[cell];
	peakx = cell;
      }
    }
  }

}

void E16ANA_LGWaveform::CalcTiming(){

  for(int i=0;i<E16ANA_LGConstant::kTimingSearchRegion;i++){
    int cell = peakx - i;
    double peakhalf = peak/2.;
    if(cell<0||cell>E16DST_Constant::NSamplesLG){
      timing=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if(wf[cell]>peak){
      timing=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if(!(cell==peakx)&&wf[cell]<peakhalf){
      timing=(peakhalf-wf[cell])*(1./E16ANA_LGConstant::kTimeScale)/(wf[cell+1]-wf[cell])+cell;
      if(cell==(peakx-1)){//remove the event like spike noise
	timing=-10000;
      }
      break;
    }
  }

}

void E16ANA_LGWaveform::CalcBaseline(){

  double baseline_sum = 0.;
  double baseline_sq_sum = 0.;
  int nb=0;
  for(int cell=(peakx+E16ANA_LGConstant::kBaselineStart); cell<(peakx+E16ANA_LGConstant::kBaselineEnd); cell++){
    if(cell<0||cell>E16DST_Constant::NSamplesLG){
      continue;
    }
    baseline_sum += wf[cell];
    baseline_sq_sum += wf[cell]*wf[cell];
    nb++;
  }
  baseline = baseline_sum/(double)nb;
  baselinerms = sqrt( baseline_sq_sum/(double)nb - baseline*baseline );

}

void E16ANA_LGWaveform::CalcIntegral(){

  double integral_sum = 0.;
  bool peakcheck = false;
  int fallcount = 0;
  falltime = peakx+E16ANA_LGConstant::kIntegralEnd;
  for(int cell=(peakx+E16ANA_LGConstant::kIntegralStart); cell<(peakx+E16ANA_LGConstant::kIntegralEnd); cell++){
    if(cell<0||cell>E16DST_Constant::NSamplesLG){
      integral_sum = E16DST_DST1Constant::kInvalidValue;
      integral = E16DST_DST1Constant::kInvalidValue;
      return;
    }
    integral_sum += wf[cell]-baseline;
    if((wf[cell]-baseline)<(wf[peakx]-baseline)*0.1&&peakcheck==false&&cell>peakx){//get decay_time
      if(fallcount>1){
	std::cout<<"FalltimeSearch is failed."<<std::endl;
	continue;
      }
      falltime = cell;
      fallcount += 1;
      if(fallcount>1){
	peakcheck=true;
      }
    }
  }//cell loop
  integral = integral_sum/50./E16ANA_LGConstant::kTimeScale;//[pC]

}

void E16ANA_LGWaveform::CalcWaveforms(){

  hwf = new TH1F("hwf","hwf",200,0.5,200.5);

  for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
    if(cell==0){ dwf[cell] = wf[cell]; }
    else{ dwf[cell] = wf[cell] - wf[cell-1]; }
    mwf[cell] = wf[cell];
    if( cell>1&&cell<(E16DST_Constant::NSamplesLG-1) ){
      if((wf[cell-1]+wf[cell+1])/2.*1.5<wf[cell] || (wf[cell-1]+wf[cell+1])/2.*0.5>wf[cell] ){//remove spike
	mwf[cell]=(wf[cell-2]+wf[cell+2])/2.;
      }
    }
    hwf->SetBinContent(cell,mwf[cell]);
  }

}

void E16ANA_LGWaveform::CalcPeaks(){

  nps_full = PeakSearchFull(pxs_full, ps_full);
  nps_short = PeakSearchShort(pxs_short, ps_short);
  CalcOffset();
  nps_fit = Fit(pxs_fit, ps_fit);

}

int E16ANA_LGWaveform::PeakSearchFull(double* pxs, double* ps){

  //N peaks search
  TSpectrum* s = new TSpectrum(30);
  int nps = s->Search(hwf, 2, "new", 0.1);

  for(int i=0; i<nps; i++){
    pxs[i] = s->GetPositionX()[i];
    ps[i] = s->GetPositionY()[i];
  }

  //my peaksearch
  int npeaks = 0;
  std::vector<double> peakxs;
  std::vector<double> peaks;
  for(int j=5; j<(E16DST_Constant::NSamplesLG-5); j++){
    int th = mwf[j]*0.1;
    if( dwf[j-4]>=0&&dwf[j-3]>=0&&dwf[j-2]>=0&&dwf[j-1]>=0&&dwf[j]>0 &&
        dwf[j+1]<=0&&dwf[j+2]<=0&&dwf[j+3]<=0&&dwf[j+4]<=0 &&
        mwf[j]>10 ){
      peakxs.push_back((double)j);
      peaks.push_back(mwf[j]);
      npeaks++;
    }
  }

  int pstype = 0;//peak search type. 0: use TSpectrum, 1: my algorithm
  if(nps>3){
    pstype = 1;
    nps = npeaks;
    for(int i=0; i<nps; i++){
      pxs[i] = peakxs[i];
      ps[i] = peaks[i];
    }
  }

  delete hwf;
  delete s;
  return nps;

}

int E16ANA_LGWaveform::PeakSearchShort(double* pxs, double* ps){

  //get N peaks around trigger timing
  int nps = 0;
  double t0cell = nstocell(t0);
  for(int i=0; i<nps_full; i++){
    if( t0cell-20<pxs_full[i] && pxs_full[i]<t0cell+20 ){
      pxs[nps] = pxs_full[i];
      ps[nps] = ps_full[i];
      nps++;
    }
  }

  return nps;

}

void E16ANA_LGWaveform::CalcOffset(){

  double ibg = 0;
  int nbg = 0;
  int pxmin = 200;
  int pxmax = 0;
  for(int p=0; p<nps_full; p++){
    if(pxs_full[p]<pxmin){
      pxmin=pxs_full[p];
    }
    if(pxs_full[p]>pxmax){
      pxmax=pxs_full[p];
    }
  }

  for(int p=pxmin-50; p<pxmax-10; p++){
    if(abs(p-pxs_full[0])<10||abs(p-pxs_full[1])<10||(abs(p-pxs_full[2]))<10){
      continue;
    }
    if(abs(dwf[p])<2){
      ibg+=mwf[p];
      nbg+=1;
    }
  }
  
  offset = ibg/double(nbg);

}

void E16ANA_LGWaveform::SetTemplate(){

  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
  FILE* fp_wf = calib.CalibFileOpenBinary("LG-WFtemplate", calib.CurrentRunID() );
  if ( fp_wf==NULL ) {
    std::cout<<"[Error] wf template file is not found !"<<std::endl;
    exit(1);
  }

  double xt, yt;
  std::vector<double> x;
  std::vector<double> y;
  while( feof(fp_wf)==0 ){
    fscanf(fp_wf, "%lf %lf", &xt, &yt );
    x.push_back(xt);
    y.push_back(yt);
  }

  gtmpl = new TGraph(110,&x[0],&y[0]);

  fclose(fp_wf);
}

double E16ANA_LGWaveform::Template1(double* x, double* par){

  return (gtmpl->Eval((x[0]-par[0])*par[1]))*par[2]/140.+par[3];

}

double E16ANA_LGWaveform::Template2(double* x, double* par){

  return (gtmpl->Eval((x[0]-par[0])*par[1]))*par[2]/140.+(gtmpl->Eval((x[0]-par[3])*par[4]))*par[5]/140.+par[6];

}

double E16ANA_LGWaveform::Template3(double* x, double* par){

  return (gtmpl->Eval((x[0]-par[0])*par[1]))*par[2]/140. + (gtmpl->Eval((x[0]-par[3])*par[4]))*par[5]/140. + (gtmpl->Eval((x[0]-par[6])*par[7]))*par[8]/140.+par[9];

}

int E16ANA_LGWaveform::Fit(double* pxs, double* ps){

  //set TGraph
  int nps = 0;
  double x[E16DST_Constant::NSamplesLG];
  double ex[E16DST_Constant::NSamplesLG] = {0.};
  double ey[E16DST_Constant::NSamplesLG];
  for(int i=0;i<E16DST_Constant::NSamplesLG;i++){
    x[i] = i;
    ey[i]=mwf[i]*0.05+1.2;
  }
  TGraphErrors* wf = new TGraphErrors(200,x,&mwf[0],ex,ey);


  //fit
  //  wf->Draw("APL");
  Double_t chi2,Ndof,baseline;
  Double_t m1,m2,m3,m4,m5;
  Double_t s1,s2,s3,s4,s5;
  Double_t v1,v2,v3,v4,v5;

  if(nps_short==1){

    TF1* temp1 = new TF1("temp1",Template1,0,200,4);
    temp1->SetParameters(pxs_short[0],0.95,ps_short[0]-offset,offset);		
    //temp1->SetParLimits(2,ps_short[0]-15,ps_short[0]+15);
    temp1->SetParLimits(1,0,2);
    //temp1->SetParLimits(3,offset-2,offset+2);

    /*
    TString outtemp = "./outtemp.pdf";
    TCanvas *c = new TCanvas("c","c",700,500);
    temp1->Draw("L*");
    c->SaveAs(outtemp,"pdf");
    */


    wf->Fit("temp1","Q","Q",pxmin-20,pxmax+30);
    chi2 = temp1->GetChisquare();
    Ndof = temp1->GetNDF();
    m1 = temp1->GetParameter(0);
    s1 = temp1->GetParameter(1);
    v1 = temp1->GetParameter(2);
    baseline = temp1->GetParameter(3);
    delete temp1;

  }
  else if(nps_short==2){

    TF1* temp2 = new TF1("temp2",Template2,0,200,7);
    temp2->SetParameters(pxs_short[0],0.95,ps_short[0]-offset, pxs_short[1],0.95,ps_short[1]-offset,offset);                            
    temp2->SetParLimits(0,pxs_short[0]-15,pxs_short[0]+15);
    temp2->SetParLimits(1,0,2);
    temp2->SetParLimits(2,ps_short[0]-50,ps_short[0]+50);
    temp2->SetParLimits(3,pxs_short[1]-15,pxs_short[1]+15);
    temp2->SetParLimits(4,0,2);
    temp2->SetParLimits(5,ps_short[1]-50,ps_short[1]+50);
    //temp2->SetParLimits(6,offset-2,offset+2);
    wf->Fit("temp2","Q","Q",pxs_short[0]-20,pxs_short[0]+30);
    chi2 = temp2->GetChisquare();
    Ndof = temp2->GetNDF();
    m1 = temp2->GetParameter(0);
    s1 = temp2->GetParameter(1);
    v1 = temp2->GetParameter(2);
    m2 = temp2->GetParameter(3);
    s2 = temp2->GetParameter(4);
    v2 = temp2->GetParameter(5);
    baseline = temp2->GetParameter(6);
    delete temp2;

  }
  else if(nps_short==3){

    TF1* temp3 = new TF1("temp3",Template3,0,200,10);
    temp3->SetParameters(pxs_short[0],0.95,ps_short[0]-offset, pxs_short[1],0.95,ps_short[1]-offset, pxs_short[2],0.95,ps_short[2]-offset, offset);
    temp3->SetParLimits(0,pxs_short[0]-15,pxs_short[0]+15);
    //temp3->SetParLimits(2,ps_short[0]-15,ps_short[0]+15);
    temp3->SetParLimits(1,0,2);
    temp3->SetParLimits(3,pxs_short[1]-15,pxs_short[1]+15);
    //temp3->SetParLimits(5,ps_short[1]-15,ps_short[1]+15);
    temp3->SetParLimits(4,0,2);
    temp3->SetParLimits(6,pxs_short[2]-15,pxs_short[2]+15);
    //temp3->SetParLimits(8,ps_short[2]-15,ps_short[2]+15);
    temp3->SetParLimits(7,0,2);
    //temp3->SetParLimits(9,offset-2,offset+2);
    wf->Fit("temp3","Q","Q",pxs_short[0]-20,pxs_short[0]+30);
    chi2 = temp3->GetChisquare();
    Ndof = temp3->GetNDF();
    m1 = temp3->GetParameter(0);
    s1 = temp3->GetParameter(1);
    v1 = temp3->GetParameter(2);
    m2 = temp3->GetParameter(3);
    s2 = temp3->GetParameter(4);
    v2 = temp3->GetParameter(5);
    m3 = temp3->GetParameter(6);
    s3 = temp3->GetParameter(7);
    v3 = temp3->GetParameter(8);
    baseline = temp3->GetParameter(9);
    delete temp3;

  }

  delete wf;
  return nps;

}

void E16ANA_LGWaveform::Peak(double* dat, double* peak, int* peakx, double* timing){

  for(int cell=5; cell<E16DST_Constant::NSamplesLG; cell++){//peak search
    if(dat[cell]>*peak){
      if( E16ANA_LGConstant::kPeakSearchStart<cell && cell<E16ANA_LGConstant::kPeakSearchEnd ){
	*peak = dat[cell];
	*peakx = cell;
      }
    }
  }//peak search

  for(int i=0;i<E16ANA_LGConstant::kTimingSearchRegion;i++){//timing search
    int cell = *peakx - i;
    double peakhalf = *peak/2.;
    if(cell<0||cell>E16DST_Constant::NSamplesLG){
      *timing=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if(dat[cell]>*peak){
      *timing=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if(!(cell==*peakx)&&dat[cell]<peakhalf){
      *timing=(peakhalf-dat[cell])*(1./E16ANA_LGConstant::kTimeScale)/(dat[cell+1]-dat[cell])+cell;
      if(cell==(*peakx-1)){//remove the event like spike noise
	*timing=-10000;
      }
      break;
    }
    }//timing search


}

void E16ANA_LGWaveform::Baseline(double* dat, int peakx, double* baseline, double* baselinerms){

  double baseline_sum = 0.;
  double baseline_sq_sum = 0.;
  int nb=0;
  for(int cell=(peakx+E16ANA_LGConstant::kBaselineStart); cell<(peakx+E16ANA_LGConstant::kBaselineEnd); cell++){
    if(cell<0||cell>E16DST_Constant::NSamplesLG){
      continue;
    }
    baseline_sum += dat[cell];
    baseline_sq_sum += dat[cell]*dat[cell];
    nb++;
  }
  *baseline = baseline_sum/(double)nb;
  *baselinerms = sqrt( baseline_sq_sum/(double)nb - (*baseline)*(*baseline) );

}

void E16ANA_LGWaveform::Integral(double* dat, int peakx, double baseline, double* integral, int* falltime){

  double integral_sum = 0.;
  bool peakcheck = false;
  int fallcount = 0;
  *falltime = peakx+E16ANA_LGConstant::kIntegralEnd;
  for(int cell=(peakx+E16ANA_LGConstant::kIntegralStart); cell<(peakx+E16ANA_LGConstant::kIntegralEnd); cell++){
    if(cell<0||cell>E16DST_Constant::NSamplesLG){
      integral_sum = E16DST_DST1Constant::kInvalidValue;
      *integral = E16DST_DST1Constant::kInvalidValue;
      return;
    }
    integral_sum += dat[cell]-baseline;
    if((dat[cell]-baseline)<(dat[peakx]-baseline)*0.1&&peakcheck==false&&cell>peakx){//get decay_time
      if(fallcount>1){
	std::cout<<"FalltimeSearch is failed."<<std::endl;
	continue;
      }
      *falltime = cell;
      fallcount += 1;
      if(fallcount>1){
	peakcheck=true;
      }
    }
  }//cell loop
  *integral = integral_sum/50./E16ANA_LGConstant::kTimeScale;//[pC]

}

int E16ANA_LGWaveform::PeakSearch(double* dat, double t0, double* mwf, double* peakxs, double* peakys){

  TH1F *h = new TH1F("h","h",200,0.5,200.5);
  TSpectrum* s = new TSpectrum(30);//max_npeaks
  double dwf[E16DST_Constant::NSamplesLG];
  double fr_peakxs[30];//full region
  double fr_peakys[30];//full region
  int nps;
  std::vector<double> pxs;
  std::vector<double> pys;

  //set waveform
  for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
    if(cell==0){ dwf[cell] = dat[cell]; }
    else{ dwf[cell] = dat[cell] - dat[cell-1]; }
    mwf[cell] = dat[cell];
    if( cell>1&&cell<(E16DST_Constant::NSamplesLG-1) ){
      if((dat[cell-1]+dat[cell+1])/2.*1.5<dat[cell] || (dat[cell-1]+dat[cell+1])/2.*0.5>dat[cell] ){//remove spike
	mwf[cell]=(dat[cell-2]+dat[cell+2])/2.;
      }
    }
    h->SetBinContent(cell,mwf[cell]);
  }

  //N peaks search
  int fr_npeaks = s->Search(h, 2, "new", 0.1);

  for(int i=0; i<fr_npeaks; i++){
    fr_peakxs[i] = s->GetPositionX()[i];
    fr_peakys[i] = s->GetPositionY()[i];
  }

  //+ my peaksearch
  nps = 0;
  pxs.clear();
  pys.clear();
  for(int j=5; j<(E16DST_Constant::NSamplesLG-5); j++){
    int th = dat[j]*0.1;
    if( dwf[j-4]>=0&&dwf[j-3]>=0&&dwf[j-2]>=0&&dwf[j-1]>=0&&dwf[j]>0 &&
        dwf[j+1]<=0&&dwf[j+2]<=0&&dwf[j+3]<=0&&dwf[j+4]<=0 &&
        dat[j]>10 ){
      pxs.push_back(j);
      pys.push_back(dat[j]);
      nps++;
    }
  }
  int pstype = 0;//peak search type. 0: use TSpectrum, 1: my algorithm
  if(fr_npeaks>3){
    pstype = 1;
    fr_npeaks = nps;
    for(int i=0; i<fr_npeaks; i++){
      fr_peakxs[i] = pxs[i];
      fr_peakys[i] = pys[i];
    }
  }

  //get N peaks at trigger timing
  int npeaks = 0;
  double t0cell = nstocell(t0);
  for(int i=0; i<fr_npeaks; i++){
    if( t0cell-20<fr_peakxs[i] && fr_peakxs[i]<t0cell+20 ){
      peakxs[npeaks] = fr_peakxs[i];
      peakys[npeaks] = fr_peakys[i];
      npeaks++;
    }
  }

  delete h;
  delete s;

  return npeaks;

}

int E16ANA_LGWaveform::Fit(double* dat, double* mwf, int npeaks, double* peakxs, double* peakys){

  return npeaks;

}

