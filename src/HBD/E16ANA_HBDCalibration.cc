#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDChannelManager.hh"
#include "E16ANA_HBDDeadChannel.hh"

#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

E16ANA_HBDCalibration::E16ANA_HBDCalibration()
{
  hbd_dead = new E16ANA_HBDDeadChannel();
}

E16ANA_HBDCalibration::~E16ANA_HBDCalibration()
{
  delete hbd_dead;
}

bool E16ANA_HBDCalibration::ReadCalibrationData(const int runID){
  E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
  
  std::string hbd_pedestal_file = calib.CalibFileName("HBD-pedestal", runID);
  std::string hbd_gain_file = calib.CalibFileName("HBD-gain", runID);
  std::string hbd_gain_calibration_status = calib.CalibFileName("HBD-calib-status", runID);
  std::string hbd_dead_ch_file = calib.CalibFileName("HBD-dead-ch", runID);
  std::string hbd_trg_threshold_file = calib.CalibFileName("HBD-trg-threshold", runID);
  
  this->ReadPedestalAndNoiseFile(hbd_pedestal_file.c_str());
  this->ReadGainFile(hbd_gain_file.c_str());
  this->ReadGainCalibrationStatusFile(hbd_gain_calibration_status.c_str());
  hbd_dead->ReadFile(hbd_dead_ch_file.c_str());
  this->ReadTrgThresholdFile(hbd_trg_threshold_file.c_str());
  
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
	if(buf_gain < 0.){
	  adc_to_pe[index][pad_id] = -1./(buf_gain*(1.+buf_polya));//photoelectron per ADC
	}else{
	  adc_to_pe[index][pad_id] = 0.;
	}
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
      if(status == 0) {gain_calibration_status = true;}//normal operation (high)
      if(status == 1) {gain_calibration_status = false;}//low gain operation (default)
      return true;
    }    
  }
  else{
    std::cerr<<__func__<<" invalid calibration status filename"<<std::endl;
    return false;
  }
}

bool E16ANA_HBDCalibration::ReadTrgThresholdFile(const char *filename){
  std::ifstream fin(filename);
  
  double buf_trg[9];
  if( fin ){
    std::string buf_line;
    for(;;){
      if(fin.eof()) break;
      std::getline(fin, buf_line);
      
      if(buf_line[0] == '#' || buf_line[0] == '\0') continue;
      
      std::string buf_mid = buf_line.substr(0, 4);
      buf_line.erase(0, 6);
      int size = buf_line.size();
      buf_line.erase(size-1, 1);
      std::stringstream ss(buf_line);
      ss>>buf_trg[0]>>buf_trg[1]>>buf_trg[2]>>buf_trg[3]>>buf_trg[4]>>buf_trg[5]>>buf_trg[6]>>buf_trg[7]>>buf_trg[8];
      
      for(int i=1; i<10; i++){//asd id start with 1
	int mid;
	int tileid;
	int chid = i;
	E16ANA_HBDChannelManager::GetTriggerTileIDWithThresholdFile(buf_mid.c_str(), chid, mid, tileid);
	int index_mid = E16ANA_HBDChannelManager::ConvMIDE16ToK(mid);
	int index_tid = E16ANA_HBDChannelManager::ConvTIDE16ToK(tileid);
	trg_threshold[index_mid][index_tid] = buf_trg[i-1];
      }
    }
    return true;
  }
  else{
    std::cerr<<__func__<<" invalid trg threshold filename"<<std::endl;
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
      }
      return true;
    }
    else{
      for(int i=0; i<n_samples; i++){
	out_waveform[i] = in_waveform[i] - cms - pedestal[index][pad_id].at(0);
      }
      return true;
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

double E16ANA_HBDCalibration::GetTriggerTileGain(const int module_id, const int tile_id)
{
  double f = 0.;
  if(E16ANA_HBDChannelManager::IsValidModuleID(module_id)){
    if(E16ANA_HBDChannelManager::IsValidTileID(tile_id)){
      std::vector<int> pads = E16ANA_HBDGeometry::GetTriggerTileAssociatedPadID(module_id, tile_id);
      for(auto pad : pads){
	f += this->GetGain(module_id, pad)/(int) pads.size();
      }
    }
  }
  return f;
}

double E16ANA_HBDCalibration::GetTriggerTileThresholdmV(const int module_id, const int tile_id)
{
  if(E16ANA_HBDChannelManager::IsValidModuleID(module_id)){
    if(E16ANA_HBDChannelManager::IsValidTileID(tile_id)){
      int mid = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
      int tid = E16ANA_HBDChannelManager::ConvTIDE16ToK(tile_id);
      return trg_threshold[mid][tid];
    }
  }
  return -1.;
}

double E16ANA_HBDCalibration::GetTriggerTileThreshold(const int module_id, const int tile_id)
{
  double pe = -1.;
  // hard coding //
  double offset = 210.;//mV
  double mV_to_fc = 6.7/240.;// fc/mV
  double fc_to_adc = 1040./20.;// adc/fc
  // hard coding //
  
  if(E16ANA_HBDChannelManager::IsValidModuleID(module_id)){
    if(E16ANA_HBDChannelManager::IsValidTileID(tile_id)){
      int mid = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
      int tid = E16ANA_HBDChannelManager::ConvTIDE16ToK(tile_id);
      double gain = GetTriggerTileGain(module_id, tile_id);
      pe = trg_threshold[mid][tid]*mV_to_fc*fc_to_adc*gain;
    }
  }
  return pe;
}
