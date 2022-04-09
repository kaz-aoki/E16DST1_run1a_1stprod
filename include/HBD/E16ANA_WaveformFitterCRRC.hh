#ifndef E16ANA_WaveformFitterCRRC_h
#define E16ANA_WaveformFitterCRRC_h

#include "TGraph.h"
#include "TGraphErrors.h"

#include "E16ANA_WaveformFitterCRRC.hh"

class E16ANA_WaveformFitterCRRC {
  
public:
  E16ANA_WaveformFitterCRRC();
  ~E16ANA_WaveformFitterCRRC();
  void SetNWaves(const int n_waves_){ n_waves = n_waves_; };
  void SetNSigma(const double n_sigma_){ n_sigma = n_sigma_; };
  void SetNoiseSigma(const double noise_sigma_){ noise_sigma = noise_sigma_; };
  void SetClockPeriod(const int clock_period_){ clock_period = clock_period_; };
  void SetTimeConstant(const int tau_){ tau = tau_; };
  void SetWaveform(const double *waveform_, int size);
  void SetWaveform(const float *waveform_, int size);
  void SetWaveform(const std::vector<double> &waveform_){ waveform = waveform_;};
  int GetNWaves(){ return n_waves; };
  int GetNCandidates(){ return n_cands; };
  double GetNSigma(){ return n_sigma; };
  double GetNoiseADC(){ return noise_sigma; };
  int GetClockPeriod(){ return clock_period; };
  int GetTimeConstant(){ return tau; };
  double GetChisquare(){ return chi2; };
  double GetNDF(){ return ndf; };
  double FitWithCRRC(double *x, double *par);
  void Fit();
  double GetWaveformPeak(const int i);
  double GetWaveformTime(const int i);
  void PrintFitCheck(TGraphErrors *gr, TGraph *gr_func);
  
private:
  std::vector<double> waveform;
  int n_waves;
  double n_sigma;
  double noise_sigma;
  double clock_period;
  double tau;
  int n_cands;
  double chi2;
  int ndf;
  
  std::vector<double> fit_result;
};

#endif // E16ANA_WaveformFitterCRRC_h
