#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDChannelManager.hh"

#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

E16ANA_HBDCalibration::E16ANA_HBDCalibration()
{
}

E16ANA_HBDCalibration::~E16ANA_HBDCalibration()
{
}

bool E16ANA_HBDCalibration::ReadCalibrationData(const int runID){
  E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
  
  std::string hbd_pedestal_file = calib.CalibFileName("HBD-pedestal", runID);
  std::string hbd_gain_file = calib.CalibFileName("HBD-gain", runID);
  std::string hbd_gain_calibration_status = calib.CalibFileName("HBD-calib-status", runID);
  
  this->ReadPedestalAndNoiseFile(hbd_pedestal_file.c_str());
  this->ReadGainFile(hbd_gain_file.c_str());
  this->ReadGainCalibrationStatusFile(hbd_gain_calibration_status.c_str());

  return true;

}

bool E16ANA_HBDCalibration::ReadPedestalAndNoiseFile(const char *filename){
  std::ifstream fin(filename);
  
  if( fin ){
    std::string buf_line;
    for(;;){
      if(fin.eof()) break;
      std::getline(fin, buf_line);

      if(buf_line[0] == '#' || buf_line[0] == '\0') continue;

      std::stringstream ss(buf_line);
      int module_id;
      int pad_id;
      int ith_sample;
      double buf_pedestal;
      double buf_noise;
      ss>>module_id>>pad_id>>ith_sample>>buf_pedestal>>buf_noise;
      if(E16ANA_HBDChannelManager::IsValidID(module_id, pad_id)){
	int index = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
	pedestal[index][pad_id].push_back(buf_pedestal);
	noise[index][pad_id].push_back(buf_noise);
      }      
    }
    return true;
  }
  else{
    std::cerr<<__func__<<" invalid calibration filename"<<std::endl;
    return false;
  }
}

bool E16ANA_HBDCalibration::ReadGainFile(const char *filename){
  std::ifstream fin(filename);
  
  if( fin ){
    std::string buf_line;
    for(;;){
      if(fin.eof()) break;
      std::getline(fin, buf_line);
      
      if(buf_line[0] == '#' || buf_line[0] == '\0') continue;

      std::stringstream ss(buf_line);
      int module_id;
      int pad_id;
      double buf_gain;
      double buf_polya;
      ss>>module_id>>pad_id>>buf_gain>>buf_polya;
      if(E16ANA_HBDChannelManager::IsValidID(module_id, pad_id)){
	int index = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
	adc_to_pe[index][pad_id] = -1./(buf_gain*(1.+buf_polya));//photoelectron per ADC
      }
    }
    return true;
  }
  else{
    std::cerr<<__func__<<" invalid calibration filename"<<std::endl;
    return false;
  }
}

bool E16ANA_HBDCalibration::ReadGainCalibrationStatusFile(const char *filename){
  std::ifstream fin(filename);
  
  int status;
  if( fin ){
    std::string buf_line;
    for(;;){
      if(fin.eof()) break;
      std::getline(fin, buf_line);
      
      if(buf_line[0] == '#' || buf_line[0] == '\0') continue;

      std::stringstream ss(buf_line);
      ss>>status;
      if(status == 0) gain_calibration_status = true;//normal operation (high)
      if(status == 1) gain_calibration_status = false;//low gain operation (default)
      return true;
    }    
  }
  else{
    std::cerr<<__func__<<" invalid calibration status filename"<<std::endl;
    return false;
  }
}

bool E16ANA_HBDCalibration::HitDecision(const int module_id, const int pad_id, const double *waveform, const double n_sigma)
{
  double cms = 0.; //TO DO
  if(E16ANA_HBDChannelManager::IsValidID(module_id, pad_id)){
    int index = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
    
    if(noise[index][pad_id].size() > 1){
      for(int i=0; i<n_samples; i++){
	if(waveform[i] > noise[index][pad_id].at(i)*n_sigma) return true;
      }
    }
    else{
      for(int i=0; i<n_samples; i++){
	if(waveform[i] > noise[index][pad_id].at(0)*n_sigma) return true;
      }
    }
  }
  return false;
}

bool E16ANA_HBDCalibration::GetCalibratedSignal(const int module_id, const int pad_id, const int16_t *in_waveform, double *out_waveform)
{
  double cms = 0.; //TO DO
  
  if(E16ANA_HBDChannelManager::IsValidID(module_id, pad_id)){
    int index = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
    
    if(pedestal[index][pad_id].size() > 1){
      for(int i=0; i<n_samples; i++){
	out_waveform[i] = in_waveform[i] - cms - pedestal[index][pad_id].at(i);
	return true;
      }
    }
    else{
      for(int i=0; i<n_samples; i++){
	out_waveform[i] = in_waveform[i] - cms - pedestal[index][pad_id].at(0);
	return true;
      }
    }
  }
  else{
    for(int i=0; i<n_samples; i++){
      out_waveform[i] = in_waveform[i] - cms;
    }
    return false;
  }
}

double E16ANA_HBDCalibration::GetPedestal(const int module_id, const int pad_id)
{
  double f = 10000.;
  if(E16ANA_HBDChannelManager::IsValidID(module_id, pad_id)){
    int index = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
    f = pedestal[index][pad_id].at(0);
  }
  return f;
}

double E16ANA_HBDCalibration::GetNoise(const int module_id, const int pad_id)
{
  double f = -1.;
  if(E16ANA_HBDChannelManager::IsValidID(module_id, pad_id)){
    int index = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
    f = noise[index][pad_id].at(0);
  }
  return f;
}

double E16ANA_HBDCalibration::GetGain(const int module_id, const int pad_id)
{
  double f = -1.;
  if(E16ANA_HBDChannelManager::IsValidID(module_id, pad_id)){
    int index = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
    f = adc_to_pe[index][pad_id];
  }
  return f;
}
