#ifndef E16ANA_HBDCalibration_h
#define E16ANA_HBDCalibration_h

#include <iostream>
#include <vector>

#include "E16DST_Constant.hh"

#include "E16ANA_HBDConstant.hh"
#include "E16ANA_HBDChannelManager.hh"

class E16ANA_HBDCalibration {
  
public:
  E16ANA_HBDCalibration();
  ~E16ANA_HBDCalibration();
  bool ReadCalibrationData(const int runID);
  bool ReadPedestalAndNoiseFile(const char *filename);
  bool ReadGainFile(const char *filename);
  bool ReadGainCalibrationStatusFile(const char *filename);
  bool HitDecision(const int module_id, const int pad_id, const double *waveform, const double n_sigma);
  bool GetCalibratedSignal(const int module_id, const int pad_id, const int16_t *in_waveform, double *out_waveform);
  double GetPedestal(const int module_id, const int pad_id);
  double GetNoise(const int module_id, const int pad_id);
  double GetGain(const int module_id, const int pad_id);
  bool GetGainCalibrationStatus(){return gain_calibration_status;};

private:
  enum {
    n_modules = E16DST_Constant::NModules,
    n_pads = HBD_Module_Constant::n_pads,
    n_samples = E16DST_Constant::NSamplesHBD
  };
  
  std::vector<double> pedestal[n_modules][n_pads];
  std::vector<double> noise[n_modules][n_pads];
  double adc_to_pe[n_modules][n_pads];
  bool gain_calibration_status;
};

#endif // E16ANA_HBDCalibration_h
