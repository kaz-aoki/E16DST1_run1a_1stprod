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

#include "E16DST_DST1Constant.hh"
#include "E16ANA_CTConstant.hh"
#include "E16ANA_CTWaveform.hh"

// #include <algorithm>
// #include <unordered_map>   

using namespace E16ANA_CTConstant;

E16ANA_CTWaveform::E16ANA_CTWaveform()
    : peak(E16DST_DST1Constant::kInvalidValue),
      peakx(E16DST_DST1Constant::kInvalidValue),
      timing(E16DST_DST1Constant::kInvalidValue),
      baseline(E16DST_DST1Constant::kInvalidValue),
      baselinerms(E16DST_DST1Constant::kInvalidValue),
      integral(E16DST_DST1Constant::kInvalidValue) {

    for(int i=0;i<E16DST_Constant::NSamplesCT;i++){
      wf[i] = E16DST_DST1Constant::kInvalidValue;
    }
}

void E16ANA_CTWaveform::SimpleMethod(double* _wf){

  SetWaveform(_wf);
  CalcPeak();
  CalcTiming();
  CalcBaseline();
  peak = peak - baseline;
  CalcIntegral();

}

void E16ANA_CTWaveform::CalcPeak(){

  for(int cell=E16ANA_CTConstant::kPeakSearchStart; cell<E16ANA_CTConstant::kPeakSearchEnd; cell++){
    if(wf[cell]>peak){
      peak = wf[cell];
      peakx = cell;
    }
  }

}

void E16ANA_CTWaveform::CalcTiming(){

  for(int i=0;i<E16ANA_CTConstant::kTimingSearchRegion;i++){
    int cell = peakx - i;
    double peakhalf = peak/2.;
    if( InvalidCell(cell) ){
      timing=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if( wf[cell] > peak ){
      timing=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if( cell!=peakx && wf[cell]<peakhalf ){
      timing=(peakhalf-wf[cell])*(1./E16ANA_CTConstant::kTimeScale)/(wf[cell+1]-wf[cell])+cell*(1./E16ANA_CTConstant::kTimeScale);
      // if(cell==(peakx-1)){//remove the event like spike noise
      // 	spikeflag = true;
      // 	// timing=-10000;
      // }
      break;
    }
    else{
      timing=peakx/E16ANA_CTConstant::kTimeScale;
    }
  }

}

void E16ANA_CTWaveform::CalcBaseline(){

  double baseline_sum = 0.;
  double baseline_sq_sum = 0.;
  int nb=0;
  for(int cell=(peakx+E16ANA_CTConstant::kBaselineStart); cell<(peakx+E16ANA_CTConstant::kBaselineEnd); cell++){
    if( InvalidCell(cell) ){
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

void E16ANA_CTWaveform::CalcIntegral(){

  double integral_sum = 0.;
  for(int cell=(peakx+E16ANA_CTConstant::kIntegralStart); cell<(peakx+E16ANA_CTConstant::kIntegralEnd); cell++){
    if( InvalidCell(cell) ){
      integral_sum = E16DST_DST1Constant::kInvalidValue;
      integral = E16DST_DST1Constant::kInvalidValue;
      return;
    }
    integral_sum += wf[cell]-baseline;
  }
  integral = integral_sum/50./E16ANA_CTConstant::kTimeScale;//[pC]

}
