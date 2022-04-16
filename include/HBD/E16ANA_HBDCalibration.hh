#ifndef E16ANA_HBDCalibration_h
#define E16ANA_HBDCalibration_h

#include <iostream>
#include <vector>

#include "E16DST_Constant.hh"

#include "E16ANA_HBDConstant.hh"
#include "E16ANA_HBDChannelManager.hh"
#include "E16ANA_HBDDeadChannel.hh"

class E16ANA_HBDCalibration {
  
public:
  E16ANA_HBDCalibration();
  ~E16ANA_HBDCalibration();
  bool ReadCalibrationData(const int runID);
  bool ReadPedestalAndNoiseFile(const char *filename);
  bool ReadGainFile(const char *filename);
  bool ReadGainCalibrationStatusFile(const char *filename);
  bool ReadTrgThresholdFile(const char *filename);
  bool HitDecision(const int module_id, const int pad_id, const double *waveform, const double n_sigma);
  bool GetCalibratedSignal(const int module_id, const int pad_id, const int16_t *in_waveform, double *out_waveform);
  double GetPedestal(const int module_id, const int pad_id);
  double GetNoise(const int module_id, const int pad_id);
  double GetGain(const int module_id, const int pad_id);
  double GetTriggerTileGain(const int module_id, const int pad_id);
  double GetTriggerTileThresholdmV(const int module_id, const int tile_id);
  double GetTriggerTileThreshold(const int module_id, const int tile_id);
  bool GetGainCalibrationStatus(){return gain_calibration_status;};
  E16ANA_HBDDeadChannel *GetDeadChannel(){return hbd_dead;};
  
private:
  enum {
    n_modules = E16DST_Constant::NModules,
    n_pads = HBD_Module_Constant::n_pads,
    n_samples = E16DST_Constant::NSamplesHBD,
    n_tiles = HBD_Module_Constant::n_tiles
  };
  
  std::vector<double> pedestal[n_modules][n_pads];
  std::vector<double> noise[n_modules][n_pads];
  double adc_to_pe[n_modules][n_pads];
  double trg_threshold[n_modules][n_tiles];
  bool gain_calibration_status;
  E16ANA_HBDDeadChannel *hbd_dead;
};

#endif // E16ANA_HBDCalibration_h
