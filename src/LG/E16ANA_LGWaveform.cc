#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <sys/time.h>
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

int E16ANA_LGWaveform::n_call = 0;
int E16ANA_LGWaveform::n_fit0 = 0;
int E16ANA_LGWaveform::n_fit1[3] = {0};
int E16ANA_LGWaveform::n_fit2[3] = {0};
int E16ANA_LGWaveform::n_fit3[3] = {0};
int E16ANA_LGWaveform::n_fit4 = 0;
//TGraph* E16ANA_LGWaveform::gtmpl = nullptr;

E16ANA_LGWaveform::E16ANA_LGWaveform()
    : peak(E16DST_DST1Constant::kInvalidValue),
      peakx(E16DST_DST1Constant::kInvalidValue),
      timing(E16DST_DST1Constant::kInvalidValue),
      baseline(E16DST_DST1Constant::kInvalidValue),
      baselinerms(E16DST_DST1Constant::kInvalidValue),
      integral(E16DST_DST1Constant::kInvalidValue),
      falltime(E16DST_DST1Constant::kInvalidValue),
      // hitflag(E16DST_DST1Constant::kInvalidValue),
      offset(E16DST_DST1Constant::kInvalidValue),
      pxmin(E16DST_DST1Constant::kInvalidValue),
      pxmax(E16DST_DST1Constant::kInvalidValue),
      nps_full(E16DST_DST1Constant::kInvalidValue),
      nps_short(E16DST_DST1Constant::kInvalidValue),
      nps_fit(E16DST_DST1Constant::kInvalidValue),
      npeaks(E16DST_DST1Constant::kInvalidValue),
      fitOK(0) {

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
      peaks[i] = E16DST_DST1Constant::kInvalidValue;
      peakxs[i] = E16DST_DST1Constant::kInvalidValue;
      widths[i] = E16DST_DST1Constant::kInvalidValue;
      timings[i] = E16DST_DST1Constant::kInvalidValue;
      chi2s[i] = E16DST_DST1Constant::kInvalidValue;
    }
    n_call++;
}

// int PrintTime(char* mes, int prevtime){
//   struct timeval measuretime;
//   gettimeofday(&measuretime, NULL);
//   int thistime = measuretime.tv_usec;
//   std::cerr << "PT " << mes << " " << thistime << " [us] " ;
//   std::cerr << thistime-prevtime << " [us]" << std::endl;
//   return thistime;
// }


void E16ANA_LGWaveform::SimpleMethod(double* _wf){

  spikeflag = false;
  SetWaveform(_wf);
  CalcPeak();
  CalcTiming();
  CalcBaseline();
  peak = peak - baseline;
  CalcIntegral();

  if(falltime-peakx<5){
    spikeflag = true;
  }

  npeaks = 1;

}

// void E16ANA_LGWaveform::MethodForTrack(double* _wf, double t0){

//   SimpleMethod(_wf);
//   SetT0(t0);

//   if(peak>8&&spikeflag==false){
//     CalcWaveforms();
//     PeakSearch();
//     if(nps_short==1){
//       hitflag = 1;
//       peak = ps_short[0];
//       peakx = pxs_short[0];
//       CalcTiming();
//     }
//     else if(nps_short>1){
//       hitflag = 1;
//       peak = ps_short[1];
//       peakx = pxs_short[2];
//       CalcTiming();
//     }
//     else{
//       hitflag = 0;
//     }
//   }
//   else{
//     fitOK = 0;
//     nps_fit = 0;
//     npeaks = 1;
//     peakxs[0] = peakx;
//     peaks[0] = peak;
//     timings[0] = timing+100.-t0;
//   }

//   npeaks = 1;

// }

void E16ANA_LGWaveform::FitMethod(double* _wf, double t0){

  SimpleMethod(_wf);
  SetT0(t0);

  if(peak>8){//modified in 211027
  //  if(peak>8&&spikeflag==false){
  //  if(spikeflag==false){
    CalcWaveforms();
    PeakSearch();
    Fit();
    // AllFit();
  }
  else{
    fitOK = 0;
    nps_fit = 0;
    npeaks = 1;
    peakxs[0] = peakx;
    peaks[0] = peak;
    timings[0] = timing+100.-t0;
  }

}

// void E16ANA_LGWaveform::FitMethod(double* _wf, double t0){

//   int thistime = 0;
//   thistime = PrintTime("init SimpleMethod", thistime);
//   SimpleMethod(_wf);
//   SetT0(t0);
//   CalcWaveforms();
//   //CalcPeaks();
//   thistime = PrintTime("init PeakSearch", thistime);
//   PeakSearch();
//   //AllFit();
//   thistime = PrintTime("init Fit", thistime);
//   Fit();
//   thistime = PrintTime("end Fit", thistime);

// }

void E16ANA_LGWaveform::woFitMethod(double* _wf, double t0){

  SimpleMethod(_wf);
  SetT0(t0);

  if(peak>15){
    CalcWaveform_woFit();
    PeakSearch_woFit();
  }
  else{
    fitOK = 0;
    nps_fit = 0;
    npeaks = 0;
  }

}

void E16ANA_LGWaveform::CalcPeak(){

  // for(int cell=5; cell<E16DST_Constant::NSamplesLG; cell++){
  for(int cell=50; cell<150; cell++){
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
    if((cell!=peakx)&&wf[cell]<peakhalf){
      timing=(peakhalf-wf[cell])*(1./E16ANA_LGConstant::kTimeScale)/(wf[cell+1]-wf[cell])+cell*(1./E16ANA_LGConstant::kTimeScale);
      if(cell==(peakx-1)){//remove the event like spike noise
	spikeflag = true;
	// timing=-10000;
      }
      break;
    }
    else{
      timing=peakx/E16ANA_LGConstant::kTimeScale;
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
  if(nb>3){
    baseline = baseline_sum/(double)nb;
    baselinerms = sqrt( baseline_sq_sum/(double)nb - baseline*baseline );
  }
  else{
    baseline = 0;
    baselinerms = 0;
  }


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

void E16ANA_LGWaveform::CalcWaveform_woFit(){

  for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
    wf[cell] = wf[cell] - baseline;
  }

  hwf = new TH1F("hwf","hwf",200,0.5,200.5);

  for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
    if(cell==0){ dwf[cell] = wf[cell]; }
    else{ dwf[cell] = wf[cell] - wf[cell-1]; }
    mwf[cell] = wf[cell];
    if( cell>1&&cell<(E16DST_Constant::NSamplesLG-1) ){
      if((wf[cell-1]+wf[cell+1])/2.*2<wf[cell] || (wf[cell-1]+wf[cell+1])/2.*0.3>wf[cell] ){//remove spike
	mwf[cell]=(wf[cell-1]+wf[cell+1])/2.;
      }
    }
    hwf->SetBinContent(cell,mwf[cell]);
  }

}

void E16ANA_LGWaveform::PeakSearch(){

  nps_full = PeakSearchFull(pxs_full, ps_full);
  nps_short = PeakSearchShort(pxs_short, ps_short);

}

void E16ANA_LGWaveform::Fit(){

  //if(nps_short==1){
  //if(BaselineCorrect()&&nps_full<2&&spikeflag==false){
  //fitOK = 0;
  //}
  //else{//incorrect baseline
  //CalcOffset();
  //nps_fit = FitTmpl1(pxs_fit, ps_fit);
  //npeaks = nps_fit;
  //}
  //}
  if(nps_short==1){
    if(BaselineCorrect()&&fabs(peakx-pxs_short[0])<5&&spikeflag==false){
      fitOK = 0;
    }
    else{//incorrect baseline
      CalcOffset();
      nps_fit = FitTmpl1(pxs_fit, ps_fit);
      npeaks = nps_fit;
    }
  }
  else if(nps_short==2){
    CalcOffset();
    nps_fit = FitTmpl2(pxs_fit, ps_fit);
    npeaks = nps_fit;
  }
  else if(nps_short==3){
    CalcOffset();
    nps_fit = FitTmpl3(pxs_fit, ps_fit);
    npeaks = nps_fit;
  }
  else if(nps_short==0){
    fitOK = 0;
  }
  else{
    fitOK = 0;
  }


  if(fitOK==0){
    nps_fit = nps_short;
    npeaks = 1;
    peakxs[0] = peakx;
    peaks[0] = peak;
    timings[0] = timing+100.-t0;
  }


  if(fitOK==2){
    npeaks = nps_short;
  }


}

int E16ANA_LGWaveform::PeakSearchFull(double* pxs, double* ps){

  //N peaks search
  TSpectrum* s = new TSpectrum(30);
  //int nps = s->Search(hwf, 2, "new", 0.1);
  int nps = s->Search(hwf, 2, "nodraw", 0.1);

  for(int i=0; i<nps; i++){
    pxs[i] = s->GetPositionX()[i];
    ps[i] = s->GetPositionY()[i];
  }

  //my peaksearch
  int mynps = 0;
  //std::vector<double> peakxs;
  //std::vector<double> peaks;
  double mypxs[30];
  double myps[30];
  for(int j=5; j<(E16DST_Constant::NSamplesLG-5); j++){
    //int th = mwf[j]*0.1;
    if( dwf[j-4]>=0&&dwf[j-3]>=0&&dwf[j-2]>=0&&dwf[j-1]>=0&&dwf[j]>0 &&
        dwf[j+1]<=0&&dwf[j+2]<=0&&dwf[j+3]<=0&&dwf[j+4]<=0 &&
      mwf[j]>10 ){
      //peakxs.push_back((double)j);
      //peaks.push_back(mwf[j]);
      mypxs[mynps] = (double)j;
      myps[mynps] = mwf[j];
      mynps++;
    }
  }

  int pstype = 0;//peak search type. 0: use TSpectrum, 1: my algorithm
  if(nps>3){
    pstype = 1;
    nps = mynps;
    for(int i=0; i<nps; i++){
      pxs[i] = mypxs[i];
      ps[i] = myps[i];
    }
  }

  delete hwf;
  delete s;

  // static int ctemp0 = 0;
  // static int ctemp1 = 0;
  // static int ctemp2 = 0;
  // static int ctemp3 = 0;
  // static int ctemp4 = 0;
  // static int ctemp5 = 0;
  // if(nps==0){ ctemp0++; std::cout<<"**0** "<<ctemp0<<std::endl;}
  // if(nps==1){ ctemp1++; std::cout<<"**1** "<<ctemp1<<std::endl;}
  // if(nps==2){ ctemp2++; std::cout<<"**2** "<<ctemp2<<std::endl;}
  // if(nps==3){ ctemp3++; std::cout<<"**3** "<<ctemp3<<std::endl;}
  // if(nps==4){ ctemp4++; std::cout<<"**4** "<<ctemp4<<std::endl;}
  // if(nps==5){ ctemp5++; std::cout<<"**5** "<<ctemp5<<std::endl;}

  return nps;

}

int E16ANA_LGWaveform::PeakSearchShort(double* pxs, double* ps){

  //get N peaks around trigger timing
  int nps = 0;
  double t0cell = nstocell(t0);
  for(int i=0; i<nps_full; i++){
    if( t0cell-20<pxs_full[i] && pxs_full[i]<t0cell+35 ){
      pxs[nps] = pxs_full[i];
      ps[nps] = ps_full[i];
      nps++;
    }
  }

  return nps;

}

void E16ANA_LGWaveform::PeakSearch_woFit(){

  //N peaks search
  TSpectrum* s = new TSpectrum(30);
  //int nps = s->Search(hwf, 2, "new", 0.1);
  int tnps = s->Search(hwf, 3, "nodraw", 0.1);
  int nps = 0;
  for(int i=0; i<tnps; i++){
    if(s->GetPositionY()[i]>15){
      pxs_full[nps] = s->GetPositionX()[i];
      ps_full[nps] = s->GetPositionY()[i];
      nps++;
    }
  }

  nps_full = nps;
  npeaks = nps;
  for(int i=0;i<nps;i++){
    peaks[i] = ps_full[i];
    peakxs[i] = pxs_full[i];
    chi2s[i] = 100;
    double ttiming = -10000.;
    bool tspikeflag = false;
    CalcRiseTiming(peaks[i], peakxs[i], ttiming, tspikeflag);
    timings[i] = ttiming+100.-t0;
    chi2s[i] = 0.;
    if(tspikeflag==true){
      timings[i] = -10000;
      chi2s[i] = 1000;
    }
    double tlatetiming;
    CalcFallTiming(peaks[i], peakxs[i], tlatetiming, tspikeflag);
    widths[i] = tlatetiming - ttiming;
    if(tspikeflag==true){
      widths[i] = -10000;
      chi2s[i] = 1000;
    }
  }

  delete hwf;
  delete s;

  // return nps;

}

void E16ANA_LGWaveform::CalcRiseTiming(double tpeak, int tpeakx, double& ttiming, bool& tspikeflag){

  for(int i=0;i<E16ANA_LGConstant::kTimingSearchRegion;i++){
    int cell = tpeakx - i;
    double peakhalf = tpeak/2.;
    if(cell<0||cell>E16DST_Constant::NSamplesLG){
      ttiming=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if(wf[cell]>tpeak){
      ttiming=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if((cell!=tpeakx)&&wf[cell]<peakhalf){
      ttiming=(peakhalf-wf[cell])*(1./E16ANA_LGConstant::kTimeScale)/(wf[cell+1]-wf[cell])+cell*(1./E16ANA_LGConstant::kTimeScale);
      if(cell==(tpeakx-1)){//remove the event like spike noise
	tspikeflag = true;
	// ttiming=-10000;
      }
      break;
    }
    else{
      ttiming=tpeakx/E16ANA_LGConstant::kTimeScale;
    }
  }

}

void E16ANA_LGWaveform::CalcFallTiming(double tpeak, int tpeakx, double& ttiming, bool& tspikeflag){

  for(int i=0;i<E16ANA_LGConstant::kTimingSearchRegion*3;i++){
    int cell = tpeakx + i;
    double peakhalf = tpeak/2.;
    if(cell<0||cell>E16DST_Constant::NSamplesLG){
      ttiming=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if(wf[cell]>tpeak){
      ttiming=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if((cell!=tpeakx)&&wf[cell]<peakhalf){
      ttiming=(peakhalf-wf[cell])*(1./E16ANA_LGConstant::kTimeScale)/(wf[cell-1]-wf[cell])+cell*(1./E16ANA_LGConstant::kTimeScale);
      if(cell==(tpeakx+1)){//remove the event like spike noise
	tspikeflag = true;
	// ttiming=-10000;
      }
      break;
    }
    else{
      ttiming=tpeakx/E16ANA_LGConstant::kTimeScale;
    }
  }

}

bool E16ANA_LGWaveform::BaselineCorrect(){

  bool flag = true;
  double t0cell = nstocell(t0);
  for(int j=0;j<nps_short;j++){
    for(int i=0; i<nps_full; i++){
      if( pxs_short[j]+E16ANA_LGConstant::kBaselineStart<pxs_full[i] && pxs_full[i]<pxs_short[j]+E16ANA_LGConstant::kBaselineEnd ){
	flag = false;
      }
  }
  }
  //for(int i=0; i<nps_full; i++){
  //if( t0cell+E16ANA_LGConstant::kBaselineStart<pxs_full[i] && pxs_full[i]<t0cell+E16ANA_LGConstant::kBaselineEnd ){
  //flag = false;
  //}
  //}

  return flag;

}

void E16ANA_LGWaveform::CalcOffset(){

  double ibg = 0;
  int nbg = 0;
  pxmin = 200;
  pxmax = 0;
  /*
  for(int p=0; p<nps_full; p++){
    if(pxs_full[p]<pxmin){
      pxmin=pxs_full[p];
    }
    if(pxs_full[p]>pxmax){
      pxmax=pxs_full[p];
    }
  }
  */
  for(int p=0; p<nps_short; p++){
    if(pxs_short[p]<pxmin){
      pxmin=pxs_short[p];
    }
    if(pxs_short[p]>pxmax){
      pxmax=pxs_short[p];
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
/*
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
*/

/*
double E16ANA_LGWaveform::Template1(double* x, double* par){

  return (gtmpl->Eval((x[0]-par[0])*par[1]))*par[2]/140.+par[3];

}

double E16ANA_LGWaveform::Template2(double* x, double* par){

  return (gtmpl->Eval((x[0]-par[0])*par[1]))*par[2]/140.+(gtmpl->Eval((x[0]-par[3])*par[4]))*par[5]/140.+par[6];

}

double E16ANA_LGWaveform::Template3(double* x, double* par){

  return (gtmpl->Eval((x[0]-par[0])*par[1]))*par[2]/140. + (gtmpl->Eval((x[0]-par[3])*par[4]))*par[5]/140. + (gtmpl->Eval((x[0]-par[6])*par[7]))*par[8]/140.+par[9];

}
*/

double E16ANA_LGWaveform::Template1(double* x, double* par){

  double xt = (x[0]-par[0])*par[1];
  double x1, x2;
  double y1, y2;
  for(int i=0;i<ngtmpl;i++){
    if(gtmplx[i]>xt){
      x1 = gtmplx[i-1];
      x2 = gtmplx[i];
      y1 = gtmply[i-1];
      y2 = gtmply[i];
      break;
    }
  }
  double yt = y1 + (y2-y1)/(x2-x1)*(xt-x1);

  return yt*par[2]/140.+par[3];

}

double E16ANA_LGWaveform::Template2(double* x, double* par){

  double xt[2];
  xt[0] = (x[0]-par[0])*par[1];
  xt[1] = (x[0]-par[3])*par[4];
  double x1[2];
  double x2[2];
  double y1[2];
  double y2[2];
  bool isfirst[2] = {false};
  for(int i=0;i<ngtmpl;i++){
    if(isfirst[0]==false&&gtmplx[i]>xt[0]){
      x1[0] = gtmplx[i-1];
      x2[0] = gtmplx[i];
      y1[0] = gtmply[i-1];
      y2[0] = gtmply[i];
      isfirst[0] = true;
    }
    if(isfirst[1]==false&&gtmplx[i]>xt[1]){
      x1[1] = gtmplx[i-1];
      x2[1] = gtmplx[i];
      y1[1] = gtmply[i-1];
      y2[1] = gtmply[i];
      isfirst[1] = true;
    }
    if(isfirst[0]==true&&isfirst[1]==true){
      break;
    }
  }
  double yt[2];
  yt[0] = y1[0] + (y2[0]-y1[0])/(x2[0]-x1[0])*(xt[0]-x1[0]);
  yt[1] = y1[1] + (y2[1]-y1[1])/(x2[1]-x1[1])*(xt[1]-x1[1]);


  return yt[0]*par[2]/140.+yt[1]*par[5]/140.+par[6];
  //return (gtmpl->Eval((x[0]-par[0])*par[1]))*par[2]/140.+(gtmpl->Eval((x[0]-par[3])*par[4]))*par[5]/140.+par[6];

}

double E16ANA_LGWaveform::Template3(double* x, double* par){

  double xt[3];
  xt[0] = (x[0]-par[0])*par[1];
  xt[1] = (x[0]-par[3])*par[4];
  xt[1] = (x[0]-par[6])*par[7];
  double x1[3];
  double x2[3];
  double y1[3];
  double y2[3];
  bool isfirst[3] = {false};
  for(int i=0;i<ngtmpl;i++){
    if(isfirst[0]==false&&gtmplx[i]>xt[0]){
      x1[0] = gtmplx[i-1];
      x2[0] = gtmplx[i];
      y1[0] = gtmply[i-1];
      y2[0] = gtmply[i];
      isfirst[0] = true;
    }
    if(isfirst[1]==false&&gtmplx[i]>xt[1]){
      x1[1] = gtmplx[i-1];
      x2[1] = gtmplx[i];
      y1[1] = gtmply[i-1];
      y2[1] = gtmply[i];
      isfirst[1] = true;
    }
    if(isfirst[2]==false&&gtmplx[i]>xt[2]){
      x1[2] = gtmplx[i-1];
      x2[2] = gtmplx[i];
      y1[2] = gtmply[i-1];
      y2[2] = gtmply[i];
      isfirst[2] = true;
    }
    if(isfirst[0]==true&&isfirst[1]==true&&isfirst[2]==true){
      break;
    }
  }
  double yt[3];
  yt[0] = y1[0] + (y2[0]-y1[0])/(x2[0]-x1[0])*(xt[0]-x1[0]);
  yt[1] = y1[1] + (y2[1]-y1[1])/(x2[1]-x1[1])*(xt[1]-x1[1]);
  yt[2] = y1[2] + (y2[2]-y1[2])/(x2[2]-x1[2])*(xt[2]-x1[2]);

  return yt[0]*par[2]/140. + yt[1]*par[5]/140. + yt[2]*par[8]/140.+par[9];
  //return (gtmpl->Eval((x[0]-par[0])*par[1]))*par[2]/140. + (gtmpl->Eval((x[0]-par[3])*par[4]))*par[5]/140. + (gtmpl->Eval((x[0]-par[6])*par[7]))*par[8]/140.+par[9];

}

int E16ANA_LGWaveform::FitTmpl1(double* pxs, double* ps){

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
  Double_t chi2,Ndof,baseline;
  Double_t m, s, v;

  TF1* tmpl1 = new TF1("tmpl1",Template1,0,200,4);
  tmpl1->SetParameters(pxs_short[0],0.95,ps_short[0]-offset,offset);		
  //tmpl1->SetParLimits(2,ps_short[0]-15,ps_short[0]+15);
  tmpl1->SetParLimits(1,0,2);
  //tmpl1->SetParLimits(3,offset-2,offset+2);
  wf->Fit("tmpl1","Q","Q",pxmin-20,pxmax+30);
  chi2 = tmpl1->GetChisquare();
  Ndof = tmpl1->GetNDF();
  m = tmpl1->GetParameter(0);
  s = tmpl1->GetParameter(1);
  v = tmpl1->GetParameter(2);
  baseline = tmpl1->GetParameter(3);
  n_fit1[0]++;

  if(chi2/Ndof<2&&0.5<s&&s<1.5&&0<v&&ps_short[0]-30<v&&v<ps_short[0]+30){
    nps = 1;
    pxs[0] = pxs_short[0];
    ps[0] = ps_short[0];
    fitOK = 1;
    peaks[0] = v;
    peakxs[0] = m;
    widths[0] = s;
    timings[0] = (m + tmplwidth*s)*(1./E16ANA_LGConstant::kTimeScale);
    chi2s[0] = chi2/Ndof;

    // draw
    // if(n_fit1[1]<100){
    //   c1s[n_fit1[1]] = new TCanvas(Form("c1s%d",n_fit1[1]),Form("c1s%d",n_fit1[1]),700,500);
    //   wf->Draw("AL*");
    //   wf->SetTitle(Form("CHI2:%f, M:%f, S:%f, V:%f, T0:%f",chi2/Ndof, m, s, v, t0));
    //   if(n_fit1[1]==0){
    // 	c1s[n_fit1[1]]->SaveAs(outfit1suc + "[", "pdf");
    //   }
    //   c1s[n_fit1[1]]->SaveAs(outfit1suc,"pdf");
    //   if(n_fit1[1]==99){
    // 	c1s[n_fit1[1]]->SaveAs(outfit1suc + "]", "pdf");
    //   }
    //   delete c1s[n_fit1[1]];
    // }


    n_fit1[1]++;
  }

  else{
    nps = 0;
    pxs[0] = pxs_short[0];
    ps[0] = ps_short[0];
    fitOK = 2;
    peaks[0] = ps_short[0] - offset;
    peakxs[0] = pxs_short[0];
    widths[0] = s;
    timings[0] = (pxs_short[0] + tmplwidth)*(1./E16ANA_LGConstant::kTimeScale);
    chi2s[0] = chi2/Ndof;

    // draw
    // if(n_fit1[2]<100){
    //   c1f[n_fit1[2]] = new TCanvas(Form("c1f%d",n_fit1[2]),Form("c1f%d",n_fit1[2]),700,500);
    //   wf->Draw("AL*");
    //   wf->SetTitle(Form("CHI2:%f, M:%f, S:%f, V:%f, T0:%f",chi2/Ndof, m, s, v, t0));
    //   if(n_fit1[2]==0){
    // 	c1f[n_fit1[2]]->SaveAs(outfit1fail + "[", "pdf");
    //   }
    //   c1f[n_fit1[2]]->SaveAs(outfit1fail,"pdf");
    //   if(n_fit1[2]==99){
    // 	c1f[n_fit1[2]]->SaveAs(outfit1fail + "]", "pdf");
    //   }
    //   delete c1f[n_fit1[2]];
    // }

    n_fit1[2]++;
  }

  delete tmpl1;
  delete wf;

  return nps;

}

int E16ANA_LGWaveform::FitTmpl2(double* pxs, double* ps){

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
  Double_t chi2,Ndof,baseline;
  Double_t m[2];
  Double_t s[2];
  Double_t v[2];

  TF1* tmpl2 = new TF1("tmpl2",Template2,0,200,7);
  tmpl2->SetParameters(pxs_short[0],0.95,ps_short[0]-offset, pxs_short[1],0.95,ps_short[1]-offset,offset);
  tmpl2->SetParLimits(0,pxs_short[0]-15,pxs_short[0]+15);
  tmpl2->SetParLimits(1,0,2);
  tmpl2->SetParLimits(2,ps_short[0]-50,ps_short[0]+50);
  tmpl2->SetParLimits(3,pxs_short[1]-15,pxs_short[1]+15);
  tmpl2->SetParLimits(4,0,2);
  tmpl2->SetParLimits(5,ps_short[1]-50,ps_short[1]+50);
  //tmpl2->SetParLimits(6,offset-2,offset+2);
  wf->Fit("tmpl2","Q","Q",pxs_short[0]-20,pxs_short[0]+30);//why?
  //wf->Fit("tmpl2","Q","Q",pxmin-20,pxmax+30);
  chi2 = tmpl2->GetChisquare();
  Ndof = tmpl2->GetNDF();
  for(int i=0;i<2;i++){
    m[i] = tmpl2->GetParameter(0+i*3);
    s[i] = tmpl2->GetParameter(1+i*3);
    v[i] = tmpl2->GetParameter(2+i*3);
  }
  offset = tmpl2->GetParameter(6);
  n_fit2[0]++;

  if(chi2/Ndof<2&&0.5<s[0]&&s[0]<1.5&&0<v[0]&&ps_short[0]-30<v[0]&&v[0]<ps_short[0]+30){
    fitOK = 1;
    pxs[nps] = pxs_short[0];
    ps[nps] = ps_short[0];
    peaks[nps] = v[0];
    peakxs[nps] = m[0];
    widths[nps] = s[0];
    timings[nps] = (m[0] + tmplwidth*s[0])*(1./E16ANA_LGConstant::kTimeScale);
    chi2s[nps] = chi2/Ndof;
    nps++;
  }
  if(chi2/Ndof<2&&0.5<s[1]&&s[1]<1.5&&0<v[1]&&ps_short[1]-30<v[1]&&v[1]<ps_short[1]+30){
    fitOK = 1;
    pxs[nps] = pxs_short[1];
    ps[nps] = ps_short[1];
    peaks[nps] = v[1];
    peakxs[nps] = m[1];
    widths[nps] = s[1];
    timings[nps] = (m[1] + tmplwidth*s[1])*(1./E16ANA_LGConstant::kTimeScale);
    chi2s[nps] = chi2/Ndof;
    nps++;
  }

  // draw
  // if(nps==2||nps==1){
  //   if(n_fit2[1]<100){
  //     c2s[n_fit2[1]] = new TCanvas(Form("c2s%d",n_fit2[1]),Form("c2s%d",n_fit2[1]),700,500);
  //     wf->Draw("AL*");
  //     wf->SetTitle(Form("<%dPULSE> CHI2:%1.1f, S:%2.1f, %1.1f, %3.1f, D:%2.1f, %1.1f, %3.1f, T0:%2.1f",nps, chi2/Ndof, m[0], s[0], v[0], m[1], s[1], v[1], t0));
  //     if(n_fit2[1]==0){
  // 	c2s[n_fit2[1]]->SaveAs(outfit2suc + "[", "pdf");
  //     }
  //     c2s[n_fit2[1]]->SaveAs(outfit2suc,"pdf");
  //     if(n_fit2[1]==99){
  // 	c2s[n_fit2[1]]->SaveAs(outfit2suc + "]", "pdf");
  //     }
  //     delete c2s[n_fit2[1]];
  //   }
  //   n_fit2[1]++;
  // }

  if(nps==0){
    fitOK = 2;
    pxs[0] = pxs_short[0];
    ps[0] = ps_short[0];
    peaks[0] = ps_short[0] - offset;
    peakxs[0] = pxs_short[0];
    widths[0] = s[0];
    timings[0] = (pxs_short[0] + tmplwidth)*(1./E16ANA_LGConstant::kTimeScale);
    chi2s[0] = chi2/Ndof;
    pxs[1] = pxs_short[1];
    ps[1] = ps_short[1];
    peaks[1] = ps_short[1];
    peakxs[1] = pxs_short[1];
    widths[1] = s[1];
    timings[1] = (pxs_short[1] + tmplwidth)*(1./E16ANA_LGConstant::kTimeScale);
    chi2s[1] = chi2/Ndof;

    // draw
    // if(n_fit2[2]<30){
    //   c2f[n_fit2[2]] = new TCanvas(Form("c2f%d",n_fit2[2]),Form("c2f%d",n_fit2[2]),700,500);
    //   wf->Draw("AL*");
    //   wf->SetTitle(Form("<%dPULSE> CHI2:%1.1f, S:%2.1f, %1.1f, %3.1f, D:%2.1f, %1.1f, %3.1f, T0:%2.1f",nps, chi2/Ndof, m[0], s[0], v[0], m[1], s[1], v[1], t0));
    //   if(n_fit2[2]==0){
    // 	c2f[n_fit2[2]]->SaveAs(outfit2fail + "[", "pdf");
    //   }
    //   c2f[n_fit2[2]]->SaveAs(outfit2fail,"pdf");
    //   if(n_fit2[2]==29){
    // 	c2f[n_fit2[2]]->SaveAs(outfit2fail + "]", "pdf");
    //   }
    //   delete c2f[n_fit2[2]];
    // }

    n_fit2[2]++;
  }

  delete tmpl2;
  delete wf;

  return nps;

}

int E16ANA_LGWaveform::FitTmpl3(double* pxs, double* ps){

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
  Double_t chi2,Ndof,baseline;
  Double_t m[3];
  Double_t s[3];
  Double_t v[3];

  TF1* tmpl3 = new TF1("tmpl3",Template3,0,200,10);
  tmpl3->SetParameters(pxs_short[0],0.95,ps_short[0]-offset, pxs_short[1],0.95,ps_short[1]-offset, pxs_short[2],0.95,ps_short[2]-offset, offset);
  tmpl3->SetParLimits(0,pxs_short[0]-15,pxs_short[0]+15);
  //tmpl3->SetParLimits(2,ps_short[0]-15,ps_short[0]+15);
  tmpl3->SetParLimits(1,0,2);
  tmpl3->SetParLimits(3,pxs_short[1]-15,pxs_short[1]+15);
  //tmpl3->SetParLimits(5,ps_short[1]-15,ps_short[1]+15);
  tmpl3->SetParLimits(4,0,2);
  tmpl3->SetParLimits(6,pxs_short[2]-15,pxs_short[2]+15);
  //tmpl3->SetParLimits(8,ps_short[2]-15,ps_short[2]+15);
  tmpl3->SetParLimits(7,0,2);
  //tmpl3->SetParLimits(9,offset-2,offset+2);
  wf->Fit("tmpl3","Q","Q",pxs_short[0]-20,pxs_short[0]+30);//why?
  //wf->Fit("tmpl3","Q","Q",pxmin-20,pxmax+30);
  chi2 = tmpl3->GetChisquare();
  Ndof = tmpl3->GetNDF();
  for(int i=0;i<3;i++){
    m[i] = tmpl3->GetParameter(0+i*3);
    s[i] = tmpl3->GetParameter(1+i*3);
    v[i] = tmpl3->GetParameter(2+i*3);
  }
  offset = tmpl3->GetParameter(9);
  n_fit3[0]++;

  for(int i=0;i<3;i++){
    if(chi2/Ndof<2&&0.5<s[i]&&s[i]<1.5&&0<v[i]&&ps_short[i]-30<v[i]&&v[i]<ps_short[i]+30){
      fitOK = 1;
      pxs[nps] = pxs_short[i];
      ps[nps] = ps_short[i];
      peaks[nps] = v[i];
      peakxs[nps] = m[i];
      widths[nps] = s[i];
      //timings[nps] = m[i];
      timings[nps] = (m[i] + tmplwidth*s[i])*(1./E16ANA_LGConstant::kTimeScale);
      chi2s[nps] = chi2/Ndof;
      nps++;
    }
  }

  // draw
  // if(nps==3||nps==2||nps==1){
  //   //    std::cout<<"FIT3 SUCCESS: "<<n_fit3[1]<<" "<<nps<<std::endl;
  //   fitOK = 1;
  //   if(n_fit3[1]<10){
  //     c3s[n_fit3[1]] = new TCanvas(Form("c3s%d",n_fit3[1]),Form("c3s%d",n_fit3[1]),700,500);
  //     wf->Draw("AL*");
  //     wf->SetTitle(Form("<%dPULSE> CHI2:%1.1f, S:%2.1f, %1.1f, %3.1f, D:%2.1f, %1.1f, %3.1f, T:%2.1f, %1.1f, %3.1f, T0:%2.1f",nps, chi2/Ndof, m[0], s[0], v[0], m[1], s[1], v[1], m[2], s[2], v[2], t0));
  //     if(n_fit3[1]==0){
  // 	c3s[n_fit3[1]]->SaveAs(outfit3suc + "[", "pdf");
  //     }
  //     c3s[n_fit3[1]]->SaveAs(outfit3suc,"pdf");
  //     if(n_fit3[1]==9){
  // 	c3s[n_fit3[1]]->SaveAs(outfit3suc + "]", "pdf");
  //     }
  //     delete c3s[n_fit3[1]];
  //   }
  //   n_fit3[1]++;
  // }

  if(nps==0){
    fitOK = 2;
    for(int i=0;i<3;i++){
      peaks[i] = ps_short[i] - offset;
      peakxs[i] = pxs_short[i];
      widths[i] = s[i];
      timings[i] = (pxs_short[0] + tmplwidth)*(1./E16ANA_LGConstant::kTimeScale);
      chi2s[i] = chi2/Ndof;
    }
    //peaks[0] = peak;
    //peakxs[0] = peakx;
    //widths[0] = E16DST_DST1Constant::kInvalidValue;
    //timings[0] = timing+100.-t0;
    //chi2s[0] = chi2/Ndof;
    // draw
    // if(n_fit3[2]<10){
    //   c3f[n_fit3[2]] = new TCanvas(Form("c3f%d",n_fit3[2]),Form("c3f%d",n_fit3[2]),700,500);
    //   wf->Draw("AL*");
    //   wf->SetTitle(Form("<%dPULSE> CHI2:%1.1f, S:%2.1f, %1.1f, %3.1f, D:%2.1f, %1.1f, %3.1f, T:%2.1f, %1.1f, %3.1f, T0:%2.1f",nps, chi2/Ndof, m[0], s[0], v[0], m[1], s[1], v[1], m[2], s[2], v[2], t0));
    //   if(n_fit3[2]==0){
    // 	c3f[n_fit3[2]]->SaveAs(outfit3fail + "[", "pdf");
    //   }
    //   c3f[n_fit3[2]]->SaveAs(outfit3fail,"pdf");
    //   if(n_fit3[2]==9){
    // 	c3f[n_fit3[2]]->SaveAs(outfit3fail + "]", "pdf");
    //   }
    //   delete c3f[n_fit3[2]];
    // }

    n_fit3[2]++;
  }

  delete tmpl3;
  delete wf;

  return nps;

}


void E16ANA_LGWaveform::DrawWf(){

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

  if(n_fit0<100){
    c0[n_fit0] = new TCanvas(Form("c0%d",n_fit0),Form("c0%d",n_fit0),700,500);
    wf->Draw("AL*");
    if(n_fit0==0){
      c0[n_fit0]->SaveAs(outfit0 + "[", "pdf");
    }
    c0[n_fit0]->SaveAs(outfit0,"pdf");
    if(n_fit0==99){
      c0[n_fit0]->SaveAs(outfit0 + "]", "pdf");
    }
    delete c0[n_fit0];
  }

  delete wf;

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

    TF1* tmpl1 = new TF1("tmpl1",Template1,0,200,4);
    tmpl1->SetParameters(pxs_short[0],0.95,ps_short[0]-offset,offset);		
    //tmpl1->SetParLimits(2,ps_short[0]-15,ps_short[0]+15);
    tmpl1->SetParLimits(1,0,2);
    //tmpl1->SetParLimits(3,offset-2,offset+2);

    // TString outtmpl = "./outtmpl.pdf";
    // TCanvas *c = new TCanvas("c","c",700,500);
    // tmpl1->Draw("L*");
    // c->SaveAs(outtmpl,"pdf");

    wf->Fit("tmpl1","Q","Q",pxmin-20,pxmax+30);
    chi2 = tmpl1->GetChisquare();
    Ndof = tmpl1->GetNDF();
    m1 = tmpl1->GetParameter(0);
    s1 = tmpl1->GetParameter(1);
    v1 = tmpl1->GetParameter(2);
    baseline = tmpl1->GetParameter(3);
    delete tmpl1;

  }
  else if(nps_short==2){

    TF1* tmpl2 = new TF1("tmpl2",Template2,0,200,7);
    tmpl2->SetParameters(pxs_short[0],0.95,ps_short[0]-offset, pxs_short[1],0.95,ps_short[1]-offset,offset);                            
    tmpl2->SetParLimits(0,pxs_short[0]-15,pxs_short[0]+15);
    tmpl2->SetParLimits(1,0,2);
    tmpl2->SetParLimits(2,ps_short[0]-50,ps_short[0]+50);
    tmpl2->SetParLimits(3,pxs_short[1]-15,pxs_short[1]+15);
    tmpl2->SetParLimits(4,0,2);
    tmpl2->SetParLimits(5,ps_short[1]-50,ps_short[1]+50);
    //tmpl2->SetParLimits(6,offset-2,offset+2);
    wf->Fit("tmpl2","Q","Q",pxs_short[0]-20,pxs_short[0]+30);
    chi2 = tmpl2->GetChisquare();
    Ndof = tmpl2->GetNDF();
    m1 = tmpl2->GetParameter(0);
    s1 = tmpl2->GetParameter(1);
    v1 = tmpl2->GetParameter(2);
    m2 = tmpl2->GetParameter(3);
    s2 = tmpl2->GetParameter(4);
    v2 = tmpl2->GetParameter(5);
    baseline = tmpl2->GetParameter(6);
    delete tmpl2;

  }
  else if(nps_short==3){

    TF1* tmpl3 = new TF1("tmpl3",Template3,0,200,10);
    tmpl3->SetParameters(pxs_short[0],0.95,ps_short[0]-offset, pxs_short[1],0.95,ps_short[1]-offset, pxs_short[2],0.95,ps_short[2]-offset, offset);
    tmpl3->SetParLimits(0,pxs_short[0]-15,pxs_short[0]+15);
    //tmpl3->SetParLimits(2,ps_short[0]-15,ps_short[0]+15);
    tmpl3->SetParLimits(1,0,2);
    tmpl3->SetParLimits(3,pxs_short[1]-15,pxs_short[1]+15);
    //tmpl3->SetParLimits(5,ps_short[1]-15,ps_short[1]+15);
    tmpl3->SetParLimits(4,0,2);
    tmpl3->SetParLimits(6,pxs_short[2]-15,pxs_short[2]+15);
    //tmpl3->SetParLimits(8,ps_short[2]-15,ps_short[2]+15);
    tmpl3->SetParLimits(7,0,2);
    //tmpl3->SetParLimits(9,offset-2,offset+2);
    wf->Fit("tmpl3","Q","Q",pxs_short[0]-20,pxs_short[0]+30);
    chi2 = tmpl3->GetChisquare();
    Ndof = tmpl3->GetNDF();
    m1 = tmpl3->GetParameter(0);
    s1 = tmpl3->GetParameter(1);
    v1 = tmpl3->GetParameter(2);
    m2 = tmpl3->GetParameter(3);
    s2 = tmpl3->GetParameter(4);
    v2 = tmpl3->GetParameter(5);
    m3 = tmpl3->GetParameter(6);
    s3 = tmpl3->GetParameter(7);
    v3 = tmpl3->GetParameter(8);
    baseline = tmpl3->GetParameter(9);
    delete tmpl3;

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

void E16ANA_LGWaveform::RemoveSpike(double* dat){

  //spike search
  std::vector<int> spike_end;
  std::vector<double> adc;
  for( int cell=5; cell<E16DST_Constant::NSamplesLG; cell++){
    adc.push_back(dat[cell]);
    if(adc.size()>5){
      adc.erase(adc.begin());
    }
    if(adc.size()==5){
      int val[4];
      for(int j=0;j<4;j++){
	val[j] = adc.at(j+1) - adc.at(j);
      }
      if(val[0]>=14&&val[0]<=22&&val[1]>=14&&val[1]<=22&&val[2]>=14&&val[2]<=22&&val[3]>=-60&&val[3]<=-45){
	spike_end.push_back(cell);
      }
    }
  }

  //modify waveform
  for( int isp=0; isp<spike_end.size(); isp++){
    double fval = dat[spike_end[isp]];
    double ival = dat[spike_end[isp]-4];
    double diff = (fval-ival)/4.;
    dat[spike_end[isp]-3] = ival+1*diff;
    dat[spike_end[isp]-2] = ival+2*diff;
    dat[spike_end[isp]-1] = ival+3*diff;
  }


  //jump cell search for DRS4 with -1L FPGA
  int thrraw = 2060;
  std::vector<std::vector<int>> jump_cell(0);
  int cell = 5;
  while( cell<E16DST_Constant::NSamplesLG-1 ){
    if( (dat[cell]-dat[cell-1])>1700 && dat[cell]>thrraw ){
      std::vector<int> tmp(0);
      tmp.push_back(cell);
      cell++;
      while( cell<E16DST_Constant::NSamplesLG-1 ){
	if( dat[cell]>thrraw ){
	  tmp.push_back(cell);
	  cell++;
	}
	else{
	  jump_cell.push_back(tmp);
	  break;
	}
      }
    }
    else{
      cell++;
    }
  }

  //modify waveform for DRS4 with -1L FPGA
  for(int i=0;i<jump_cell.size();i++){
    int size = jump_cell.at(i).size();
    int scell = jump_cell.at(i).at(0);
    if(size==1){
      dat[scell] = (dat[scell-1]+dat[scell+1])/2.;
    }
    else{
      double offset = dat[scell] - ( (dat[scell-1]-dat[scell-2])+dat[scell-1] );
      for(int j=0;j<size;j++){
	int ccell = jump_cell.at(i).at(j);
	dat[ccell] = dat[ccell] - offset;
      }
    }
  }

}

void E16ANA_LGWaveform::AllFit(){

  CalcOffset();
  if(nps_short==1){
    nps_fit = FitTmpl1(pxs_fit, ps_fit);
    npeaks = nps_fit;
  }
  else if(nps_short==2){
    nps_fit = FitTmpl2(pxs_fit, ps_fit);
    npeaks = nps_fit;
  }
  else if(nps_short==3){
    nps_fit = FitTmpl3(pxs_fit, ps_fit);
    npeaks = nps_fit;
  }
  else if(nps_short==0){
    fitOK = 0;
  }
  else{
    fitOK = 0;
  }

  if(fitOK==0){
    nps_fit = nps_short;
    npeaks = 1;
    peakxs[0] = peakx;
    peaks[0] = peak;
    timings[0] = timing+100.-t0;
  }

  if(fitOK==2){
    npeaks = nps_short;
  }

}

// void E16ANA_LGWaveform::CalcPeaks(){

//   nps_full = PeakSearchFull(pxs_full, ps_full);
//   nps_short = PeakSearchShort(pxs_short, ps_short);
//   CalcOffset();
//   if(nps_short==1){
//     nps_fit = FitTmpl1(pxs_fit, ps_fit);
//     npeaks = nps_fit;
//   }
//   else if(nps_short==2){
//     nps_fit = FitTmpl2(pxs_fit, ps_fit);
//     npeaks = nps_fit;
//   }
//   else if(nps_short==3){
//     nps_fit = FitTmpl3(pxs_fit, ps_fit);
//     npeaks = nps_fit;
//   }
//   else if(nps_short==0){
//     fitOK = 0;
//     nps_fit = nps_short;
//     npeaks = 1;
//     peakxs[0] = peakx;
//     peaks[0] = peak;
//     //    DrawWf();
//     n_fit0++;
//   }
//   else{
//     fitOK = 0;
//     nps_fit = nps_short;
//     npeaks = 1;
//     peakxs[0] = peakx;
//     peaks[0] = peak;
//     n_fit4++;
//   }

//   if(nps_fit==0&&npeaks==0){
//     npeaks = 1;
//   }

// }

