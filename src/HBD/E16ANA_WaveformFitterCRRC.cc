#include "E16ANA_WaveformFitterCRRC.hh"
#include "E16ANA_HBDConstant.hh"

#include "TF1.h"
#include "TH1.h"
#include "TGraph.h"
#include "TGraphErrors.h"

#include <vector>
#include <iostream>
#include <algorithm>

E16ANA_WaveformFitterCRRC::E16ANA_WaveformFitterCRRC()
  : n_waves(2), n_sigma(4.0), noise_sigma(13.0),
    clock_period(HBD_Circuit_Constant::apv25_period),
    tau(HBD_Circuit_Constant::apv25_timeconstant)
{
  n_cands = 0;
}

E16ANA_WaveformFitterCRRC::~E16ANA_WaveformFitterCRRC()
{
}

void E16ANA_WaveformFitterCRRC::SetWaveform(const double *waveform_, int size){
  waveform.clear();
  waveform.resize(size);
  for(int i=0; i<size; i++){
    waveform[i] = (double)waveform_[i];
  }
}

void E16ANA_WaveformFitterCRRC::SetWaveform(const float *waveform_, int size){
  waveform.clear();
  waveform.resize(size);
  for(int i=0; i<size; i++){
    waveform[i] = (double)waveform_[i];
  }
}

double E16ANA_WaveformFitterCRRC::FitWithCRRC(double *x, double *par)
{
  double sum = 0.;
  double val = 0.;
  for(int i=0; i<n_cands; i++){
    if(x[0]-(par[2*i+1]-tau)<0.) val = 0.;
    else val = par[2*i]*(x[0]-(par[2*i+1]-tau))/tau*std::exp(1-(x[0]-(par[2*i+1]-tau))/tau);
    sum += val;
  }

  return sum;
}

void E16ANA_WaveformFitterCRRC::Fit()
{
  fit_result.clear();
    
  TGraphErrors *gr = new TGraphErrors();
  for(int i=0; i<waveform.size(); i++){
    gr->SetPoint(i, i*clock_period, waveform.at(i));
    gr->SetPointError(i, 0, noise_sigma);
  }
  //--- search for candidates ---//
  std::vector<int> cand_index;
  for(int i=0; i<(int) waveform.size()-1; i++){
    double diff_prev = -1.;
    if(i==0) diff_prev = 10000.;
    else diff_prev = waveform.at(i) - waveform.at(i-1);
    
    double diff_next = -1.;
    if(i==waveform.size()-1) diff_next = 10000.;
    else diff_next = waveform.at(i) - waveform.at(i+1);
    
    if(waveform.at(i) >= n_sigma*noise_sigma){
      if(diff_prev >= 0. && diff_next >= 0.){
	cand_index.push_back(i);
      }
    }
    if((int) cand_index.size() >= n_waves) break;
  }
  //--- search for candidates ---//
  
  double lower_time = -2.*clock_period;
  double upper_time = (waveform.size()-2)*clock_period;
  //--- first fit ---//
  n_cands = cand_index.size();
  if(n_cands >= 1){
    TF1 *f_func = new TF1("f_func", this, &E16ANA_WaveformFitterCRRC::FitWithCRRC, -200., 800., 2*n_cands);
    for(int i=0; i<n_cands; i++){
      f_func->SetParameter(2*i, waveform.at(cand_index.at(i)));
      f_func->SetParameter(2*i+1, cand_index.at(i)*clock_period);
      f_func->SetParLimits(2*i, 0., 3000.);
      if(i==0 && n_cands == 1) f_func->SetParLimits(2*i+1, lower_time, upper_time);
      if(i==0 && n_cands >= 2) f_func->SetParLimits(2*i+1, lower_time, cand_index.at(i+1)*clock_period);
      if(i>=1) f_func->SetParLimits(2*i+1, cand_index.at(i-1)*clock_period, upper_time);
    }
    gr->Fit("f_func", "Q");
    chi2 = f_func->GetChisquare();
    ndf = f_func->GetNDF();
    //--- first fit ---//
    //--- second fit (refit) ---//
    bool second_fit_flag = false;
    std::vector<int> re_cand_index;
    for(int i=0; i<n_cands; i++){
      if(f_func->GetParameter(2*i)>n_sigma*noise_sigma){
	re_cand_index.push_back(cand_index.at(i));
      }else{
	second_fit_flag = true;
      }
    }
    if(second_fit_flag){
      n_cands = re_cand_index.size();
      chi2 = 0.;
      ndf = 0;
      if(n_cands >= 1){
	TF1 *s_func = new TF1("s_func", this, &E16ANA_WaveformFitterCRRC::FitWithCRRC, -200., 800., 2*n_cands);
	for(int i=0; i<n_cands; i++){
	  s_func->SetParameter(2*i, waveform.at(re_cand_index.at(i)));
	  s_func->SetParameter(2*i+1, re_cand_index.at(i)*clock_period);
	  s_func->SetParLimits(2*i, 0., 3000.);
	  if(i==0 && n_cands == 1) s_func->SetParLimits(2*i+1, lower_time, upper_time);
	  if(i==0 && n_cands >= 2) s_func->SetParLimits(2*i+1, lower_time, re_cand_index.at(i+1)*clock_period);
	  if(i>=1) s_func->SetParLimits(2*i+1, re_cand_index.at(i-1)*clock_period, upper_time);
	}
	gr->Fit("s_func", "Q");
	chi2 = f_func->GetChisquare();
	ndf = f_func->GetNDF();
	
	for(int i=0; i<n_cands; i++){
	  fit_result.push_back(s_func->GetParameter(2*i));
	  fit_result.push_back(s_func->GetParameter(2*i+1));
	}
	delete s_func;
      }
    }
    //--- second fit (refit) ---//
    else{
      for(int i=0; i<n_cands; i++){
	fit_result.push_back(f_func->GetParameter(2*i));
	fit_result.push_back(f_func->GetParameter(2*i+1));
      }
      delete f_func;
    }
  }
  delete gr;
}

double E16ANA_WaveformFitterCRRC::GetWaveformPeak(const int ith_wave)
{
  if(n_cands > ith_wave){
    return fit_result.at(2*ith_wave);
  }else{
    return 0.;
  }
}

double E16ANA_WaveformFitterCRRC::GetWaveformTime(const int ith_wave)
{
  if(n_cands > ith_wave){
    TF1 *f = new TF1("f", this, &E16ANA_WaveformFitterCRRC::FitWithCRRC, -200., 800., 2);
    f->FixParameter(0, fit_result.at(2*ith_wave));
    f->FixParameter(1, fit_result.at(2*ith_wave+1));
    for(int i=0; i<100; i++){
      if(fit_result.at(2*ith_wave)*0.5 > f->Eval(fit_result.at(2*ith_wave+1)-i)){
	delete f;
	return fit_result.at(2*ith_wave+1)-i;
      }
    }
    delete f;
    return -10000.;
  }else{
    return -10000.;
  }
}

void E16ANA_WaveformFitterCRRC::PrintFitCheck(TGraphErrors *gr, TGraph *gr_func)
{
  for(int i=0; i<waveform.size(); i++){
    gr->SetPoint(i, i*clock_period, waveform.at(i));
    gr->SetPointError(i, 0, noise_sigma);
  }
  
  if(n_cands >= 1){
    TF1 *f = new TF1("f", this, &E16ANA_WaveformFitterCRRC::FitWithCRRC, -200., 800., 2*n_cands);
    for(int i=0; i<n_cands; i++){
      f->FixParameter(2*i, fit_result.at(2*i));
      f->FixParameter(2*i+1, fit_result.at(2*i+1));
    }
    
    for(int i=0; i<(waveform.size()+1)*clock_period; i++){
      gr_func->SetPoint(i, i, f->Eval(i));
    }
    delete f;
  }
}
