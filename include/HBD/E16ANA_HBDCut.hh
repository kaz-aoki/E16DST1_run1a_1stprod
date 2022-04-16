#ifndef E16ANA_HBDCut_h
#define E16ANA_HBDCut_h

#include "E16ANA_HBDCut.hh"

class E16ANA_HBDCut {
  
public:
  E16ANA_HBDCut();
  ~E16ANA_HBDCut();
  bool ReadCutData(const int runID);
  bool ReadFile(const char* filename);
  void SetCut(const char* cut_keyword, const double value);
  double GetCut(const char* cut_keyword);
  double GetNSigmaWfDST1(){ return n_sigma_wf_dst1; };
  int GetNWavesDST1(){ return n_waves_dst1; };
  double GetThWaveformChi2(){ return th_wf_chi2; };
  int GetThCSizeDST1(){ return th_csize_dst1; };
  double GetThCChargeDST1(){ return th_ccharge_dst1; };
  double GetNSigmaCADCDST1(){ return n_sigma_cadc;};
  double *GetClusteringTimeWindow(){return clustering_time_window;};

private:
  double n_sigma_wf_dst1;
  int n_waves_dst1;
  double tdc_range_upper;
  double tdc_range_lower;
  double th_wf_chi2;
  int th_csize_dst1;
  double th_ccharge_dst1;
  double n_sigma_cadc;
  double clustering_time_window[2];
};

#endif // E16ANA_HBDCut_h
