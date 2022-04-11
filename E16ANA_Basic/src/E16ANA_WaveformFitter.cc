//2016-05-02, uploaded by nakai
//2016-04-01, uploaded by nakai
//2015-11-14, uploaded by nakai

#include "E16ANA_WaveformFitter.hh"

#include <iostream>
#include <algorithm>

#include <TH1F.h>
#include <TF1.h>
//#include <Math/Factory.h>

int E16ANA_WaveformFitter::n_instances = 0;

E16ANA_WaveformFitter::E16ANA_WaveformFitter(const std::string &file_name) :
  n_wave(2), clock_period(25.0), noise_sigma(5.0), n_sigma(5.0),
  instance_id(E16ANA_WaveformFitter::n_instances)
{
  //pars_time.reserve(10);
  //pars_peak.reserve(10);
  fit_params.reserve(10);
  //wf_temp = new E16ANA_WaveformTemplate("./waveform_template.dat");
  wf_temp = new E16ANA_WaveformTemplate(file_name.c_str());
  n_instances++;
}

E16ANA_WaveformFitter::~E16ANA_WaveformFitter(){
   delete wf_temp;
}

//double E16ANA_WaveformFitter::MinuitFunction(const std::vector<double> &pars){
double E16ANA_WaveformFitter::MinuitFunction(const double *pars){
   double chi2 = 0.0;
   double x[1];
   double *par_temp = new double[n_cands*2];
   for(int i=0; i<n_cands*2; i++){
     par_temp[i] = pars[i];
   }
   for(int i=0; i<(int)waveform.size(); i++){
     x[0] = i*clock_period;
     // Template fitting
     double temp = FitFuncTemplate(x, par_temp)-waveform[i];
     chi2 += (temp*temp)/(noise_sigma*noise_sigma);
   }
   delete [] par_temp;
   return chi2;
}

double E16ANA_WaveformFitter::FitFuncTemplate(double *x, double *par){
  double xx = x[0];
  double result = 0.0;
  for(int i=0; i<n_cands; i++){
    result += par[i*2]*(wf_temp->GetValue(xx-par[i*2+1]));
  }
  return result;
}

//void E16ANA_WaveformFitter::PrintFitCheck(){
void E16ANA_WaveformFitter::PrintFitCheck(TH1F *h, TGraph *g){
   double x[1];
   double *par_temp = new double[n_cands*2];
   for(int i=0; i<n_cands; i++){
      par_temp[i*2] = fit_params[i].peak;
      par_temp[i*2+1] = fit_params[i].time;
   }
   for(int i=0; i<(int)waveform.size(); i++){
      x[0] = i*clock_period;
      double wf_val = waveform[i];
      double ff_val = FitFuncTemplate(x, par_temp);
      //std::cout << i << "th sample : waveform = " << wf_val
      //   << ", Fitted func = " << ff_val << std::endl;
      h->Fill(i*clock_period, wf_val);
      h->SetBinError(h->FindBin(i*clock_period), noise_sigma);
   }
   for(int i=0; i<(int)waveform.size()*10; i++){
     x[0] = (i-0.5)*clock_period/10.0;
     double ff_val = FitFuncTemplate(x, par_temp);
     g->SetPoint(i, x[0], ff_val);
   }
}

double E16ANA_WaveformFitter::GetTimeOverThreshold(const int ith_wave, const double rel_height){
  double f = 0.;
  if(0. <= rel_height && rel_height <= 1){
    double t0 = this->GetWaveformTime(ith_wave);
    for(int i=0; i<100; i++){// nsec
      double x = wf_temp->GetValue(-i);
      if(x <= rel_height){
	f = t0 - i;
	break;
      }
    }
  }
  return f;
}

void E16ANA_WaveformFitter::SetWaveform(const double *_fadc, int size){
   waveform.clear();
   waveform.resize(size);
   for(int i=0; i<size; i++){
      waveform[i] = (double)_fadc[i];
   }
}

void E16ANA_WaveformFitter::SetWaveform(const float *_fadc, int size){
   waveform.clear();
   waveform.resize(size);
   for(int i=0; i<size; i++){
     waveform[i] = (double)_fadc[i];
   }
}

void E16ANA_WaveformFitter::SetWaveform(const std::vector<int> &_fadc){
//void E16ANA_WaveformFitter::SetWaveform(const std::vector<double> &_fadc){
   waveform.clear();
   waveform.resize(_fadc.size());
   for(int i=0; i<(int)_fadc.size(); i++){
      waveform[i] = (double)_fadc[i];
   }
}

//void E16ANA_WaveformFitter::Clear(){
//   h_fit->Reset();
//}
/*
void E16ANA_WaveformFitter::Fit(){
   if((int)waveform.size()==0){
      std::cout << "E16ANA_WaveformFitter::Fit() : Data is empty." << std::endl;
      return;
   }
   //TemplateFit();
   //TMinuitMinimizer *minuit = new TMinuitMinimizer(ROOT::Minuit::kMigradImproved);
   TMinuitMinimizer *minuit = new TMinuitMinimizer(ROOT::Minuit::kSimplex);
   //TMinuitMinimizer *minuit = new TMinuitMinimizer(ROOT::Minuit::kMigrad, n_wave*2);
   //ROOT::Math::Minimizer *minuit = ROOT::Math::Factory::CreateMinimizer("Minuit","");
   E16ANA_WaveformFitterFCN fcn(this);
   //minuit->SetFunction(static_cast<ROOT::Math::IMultiGenFunction*>(&fcn));
   minuit->SetFunction(fcn);
   minuit->SetPrintLevel(-1);
   //minuit->SetPrintLevel(3);
   minuit->SetStrategy(2);
   //minuit->SetStrategy(0);
   minuit->SetMaxFunctionCalls(100000);
   minuit->SetTolerance(0.001);
   
   double init_peak = 100.0;
   double step_peak = 10.0;
   double lower_peak = 0.0;
   double upper_peak = 2000.0;
   double init_time = 0.;
   double step_time = clock_period;
   double lower_time = (-0.5-5.0)*clock_period;
   double upper_time = (waveform.size()-0.5-2.0)*clock_period;
   
   for(int i=0; i<n_wave; i++){
      minuit->SetLimitedVariable(i*2  , Form("Peak_%d",i), init_peak, step_peak, lower_peak, upper_peak);
      init_time = (upper_time-lower_time)/((double)n_wave+1.0)*(i+1.0)+lower_time;
      minuit->SetLimitedVariable(i*2+1, Form("Time_%d",i), init_time, step_time, lower_time, upper_time);
      //minuit->SetVariable(i*2+1, Form("Time_%d",i), init_time, step_time);
   }
   bool iret = minuit->Minimize();
   //std::cout << "MinValue = " << minuit->MinValue() << std::endl;
   //if(!iret){
   //   std::cout << "E16ANA_WaveformFitter::Fit() : Minimize error." << std::endl;
   //   //return;
   //}
   //minuit->PrintResults();
   //pars_peak.clear();
   //pars_time.clear();
   fit_params.clear();
   for(int i=0; i<n_wave; i++){
      //pars_peak.push_back(minuit->X()[i*2]);
      //pars_time.push_back(minuit->X()[i*2+1]);
      fit_params.push_back(fit_param_t(minuit->X()[i*2], minuit->X()[i*2+1]));
   }
   std::sort(fit_params.begin(), fit_params.end());
   
   delete minuit;
}
*/
void E16ANA_WaveformFitter::Fit(){
  if((int)waveform.size()==0){
    std::cout << "E16ANA_WaveformFitter::Fit() : Data is empty." << std::endl;
    return;
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
    if((int) cand_index.size() >= n_wave) break;
  }
  //--- search for candidates ---//
  
  double init_peak;
  double step_peak = 10.0;
  double lower_peak = 0.0;
  double upper_peak = 2000.0;
  double init_time;
  double step_time = clock_period;
  double lower_time = -2.*clock_period;
  //double lower_time = -1.*clock_period;
  double upper_time = (waveform.size()-2.)*clock_period;
  
  n_cands = cand_index.size();
  //TMinuitMinimizer *minuit = new TMinuitMinimizer(ROOT::Minuit::kMigradImproved);
  TMinuitMinimizer *minuit = new TMinuitMinimizer(ROOT::Minuit::kSimplex);
  //TMinuitMinimizer *minuit = new TMinuitMinimizer(ROOT::Minuit::kMigrad, n_wave*2);
  //ROOT::Math::Minimizer *minuit = ROOT::Math::Factory::CreateMinimizer("Minuit","");
  E16ANA_WaveformFitterFCN fcn(this);
  //minuit->SetFunction(static_cast<ROOT::Math::IMultiGenFunction*>(&fcn));
  minuit->SetFunction(fcn);
  minuit->SetPrintLevel(-1);
  //minuit->SetPrintLevel(3);
  minuit->SetStrategy(2);
  //minuit->SetStrategy(0);
  minuit->SetMaxFunctionCalls(100000);
  minuit->SetTolerance(0.001);

  if(n_cands >= 1.){
    for(int i=0; i<n_cands; i++){
      init_peak = waveform.at(cand_index.at(i));
      minuit->SetLimitedVariable(i*2, Form("Peak_%d",i), init_peak, step_peak, lower_peak, upper_peak);
      
      init_time = cand_index.at(i)*clock_period;
      if(i==0 && n_cands ==1) minuit->SetLimitedVariable(i*2+1, Form("Time_%d",i), init_time, step_time, lower_time, upper_time);
      if(i==0 && n_cands >=2) minuit->SetLimitedVariable(i*2+1, Form("Time_%d",i), init_time, step_time, lower_time, cand_index.at(i+1)*clock_period);
      if(i>=1) minuit->SetLimitedVariable(i*2+1, Form("Time_%d",i), init_time, step_time, cand_index.at(i-1)*clock_period, upper_time);
    }
    bool iret = minuit->Minimize();
    fit_params.clear();
    for(int i=0; i<n_cands; i++){
      fit_params.push_back(fit_param_t(minuit->X()[i*2], minuit->X()[i*2+1]));
    }
    bool second_fit_flag = false;
    std::vector<int> re_cand_index;
    for(int i=0; i<n_cands; i++){
      if(fit_params[i].peak > n_sigma*noise_sigma){
        re_cand_index.push_back(cand_index.at(i));
      }else{
        second_fit_flag = true;
      }
    }
    
    if(second_fit_flag){
      n_cands = re_cand_index.size();
      if(n_cands >= 1){
	TMinuitMinimizer *minuit2 = new TMinuitMinimizer(ROOT::Minuit::kSimplex);
	E16ANA_WaveformFitterFCN fcn2(this);
	minuit2->SetFunction(fcn2);
	minuit2->SetPrintLevel(-1);
	minuit2->SetStrategy(2);
	minuit2->SetMaxFunctionCalls(100000);
	minuit2->SetTolerance(0.001);
	
	for(int i=0; i<n_cands; i++){
	  init_peak = waveform.at(re_cand_index.at(i));
	  minuit2->SetLimitedVariable(i*2, Form("Peak_%d",i), init_peak, step_peak, lower_peak, upper_peak);
	  init_time = re_cand_index.at(i)*clock_period;
	  if(i==0 && n_cands ==1) minuit2->SetLimitedVariable(i*2+1, Form("Time_%d",i), init_time, step_time, lower_time, upper_time);
	  if(i==0 && n_cands >=2) minuit2->SetLimitedVariable(i*2+1, Form("Time_%d",i), init_time, step_time, lower_time, re_cand_index.at(i+1)*clock_period);
	  if(i>=1) minuit2->SetLimitedVariable(i*2+1, Form("Time_%d",i), init_time, step_time, re_cand_index.at(i-1)*clock_period, upper_time);
	}
	iret = minuit2->Minimize();
	fit_params.clear();
	for(int i=0; i<n_cands; i++){
	  fit_params.push_back(fit_param_t(minuit2->X()[i*2], minuit2->X()[i*2+1]));
	}
	delete minuit2;
      }
    }
    else{
      fit_params.clear();
      for(int i=0; i<n_cands; i++){
	fit_params.push_back(fit_param_t(minuit->X()[i*2], minuit->X()[i*2+1]));
      }
    }
  }

  std::sort(fit_params.begin(), fit_params.end());
  
  delete minuit;
}

ROOT::Math::IMultiGenFunction* E16ANA_WaveformFitterFCN::Clone() const {
  return new E16ANA_WaveformFitterFCN(this->fitter);
}

