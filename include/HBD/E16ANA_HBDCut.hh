#ifndef E16ANA_HBDCut_h
#define E16ANA_HBDCut_h

#include "E16ANA_HBDCut.hh"

class E16ANA_HBDCut {
  
public:
  E16ANA_HBDCut();
  ~E16ANA_HBDCut();
  bool ReadCutData(const int runID);
  bool ReadFile(const char* filename);
  double GetNSigmaWfDST1(){ return n_sigma_wf_dst1; };
  int GetNWavesDST1(){ return n_waves_dst1; };
  int GetThCSizeDST1(){ return th_csize_dst1; };
  double GetThCChargeDST1(){ return th_ccharge_dst1; };
  
private:
  double n_sigma_wf_dst1;
  int n_waves_dst1;
  int th_csize_dst1;
  double th_ccharge_dst1;
};

#endif // E16ANA_HBDCut_h
