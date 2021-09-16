#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <TH1.h>
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

int E16ANA_LGWaveform::PeakSearch(double* dat, double t0, double* peakxs, double* peakys){

  TH1F *h = new TH1F("h","h",200,0.5,200.5);
  TSpectrum* s = new TSpectrum(30);//max_npeaks
  double dwf[E16DST_Constant::NSamplesLG];
  double mwf[E16DST_Constant::NSamplesLG];//modified waveform
  double fr_peakxs[30];//full region
  double fr_peakys[30];//full region
  int nps;
  std::vector<double> pxs;
  std::vector<double> pys;
  int pstype = 0;//peak search type. 0: use TSpectrum, 1: my algorithm
  int npeaks;


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

  int fr_npeaks = s->Search(h, 2, "new", 0.1);

  for(int i=0; i<fr_npeaks; i++){
    fr_peakxs[i] = s->GetPositionX()[i];
    fr_peakys[i] = s->GetPositionY()[i];
  }

  //my peak search
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

  if(fr_npeaks>3){
    pstype = 1;
    fr_npeaks = nps;
    for(int i=0; i<fr_npeaks; i++){
      fr_peakxs[i] = pxs[i];
      fr_peakys[i] = pys[i];
    }
  }

  npeaks = 0;
  for(int i=0; i<fr_npeaks; i++){
    if( t0-20<fr_peakxs[i] && fr_peakxs[i]<t0+20 ){
      peakxs[npeaks] = fr_peakxs[i];
      peakys[npeaks] = fr_peakys[i];
      npeaks++;
    }
  }

  delete h;
  delete s;

  return npeaks;

}

/*
void E16ANA_LGWaveform::SetTemplate(){

  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
  FILE* fp_t0 = calib.CalibFileOpenBinary("LG-t0bych", calib.CurrentRunID() );
  if ( fp_t0==NULL ) {
    std::cout<<"[Error] t0 map file is not found !"<<std::endl;
    exit(1);
  }
  int module, block;
  double t0_mean;
  double t0_sigma;
  while( feof(fp_t0)==0 ){
    fscanf(fp_t0, "%d %d %lf %lf", &module, &block, &t0_mean, &t0_sigma );
    if(!(0<=module&&module<110&&0<=block&&block<60)){
      std::cerr<<"read invalid ID in t0map file"<<std::endl;
      exit(1);
    }
    else{
      t0map[module][block] = t0_mean;
    }
  }//while loop
  fclose(fp_t0);


}


int E16ANA_LGWaveform::Fit(double* dat, int npeaks, double* peakxs, double* peakys){

  return npeaks;

}
*/

