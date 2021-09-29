#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_HBDDeadChannel.hh"
#include "E16ANA_HBDChannelManager.hh"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

E16ANA_HBDDeadChannel::E16ANA_HBDDeadChannel()
{
}

E16ANA_HBDDeadChannel::~E16ANA_HBDDeadChannel()
{
}

bool E16ANA_HBDDeadChannel::ReadFile(const char *filename){
  Init();
  
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
      int buf_status;
      int k_module_id;
      ss>>module_id>>pad_id>>buf_status;
      
      if(E16ANA_HBDChannelManager::IsValidID(module_id, pad_id)){
	k_module_id = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
	status[k_module_id][pad_id] = buf_status;
      }     
    }
    return true;
  }
  else{
    std::cerr<<__func__<<" invalid dead channel filename"<<std::endl;
    return false;
  }
}

bool E16ANA_HBDDeadChannel::ReadDeadChannelData(const int runID){
  E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
  
  std::string hbd_dead_channel_file = calib.CalibFileName("HBD-dead-ch", runID);
  
  this->ReadFile(hbd_dead_channel_file.c_str());
}

bool E16ANA_HBDDeadChannel::IsOK(const int module_id, const int pad_id){
  bool flag = false;
  if(E16ANA_HBDChannelManager::IsValidID(module_id, pad_id)){
    int k_module_id = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
    if(status[k_module_id][pad_id] == ok_flag) flag = true;
  }
  
  return flag;
}

bool E16ANA_HBDDeadChannel::IsDead(const int module_id, const int pad_id){
  bool flag = false;
  if(E16ANA_HBDChannelManager::IsValidID(module_id, pad_id)){
    int k_module_id = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
    if(status[k_module_id][pad_id] == dead_flag) flag = true;
  }
  
  return flag;
}

bool E16ANA_HBDDeadChannel::IsNoisy(const int module_id, const int pad_id){
  bool flag = false;
  if(E16ANA_HBDChannelManager::IsValidID(module_id, pad_id)){
    int k_module_id = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
    if(status[k_module_id][pad_id] == noisy_flag) flag = true;
  }
  
  return flag;
}

bool E16ANA_HBDDeadChannel::IsHot(const int module_id, const int pad_id){
  bool flag = false;
  if(E16ANA_HBDChannelManager::IsValidID(module_id, pad_id)){
    int k_module_id = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
    if(status[k_module_id][pad_id] == hot_flag) flag = true;
  }
  
  return flag;
}

int E16ANA_HBDDeadChannel::Status(const int module_id, const int pad_id){
  if(E16ANA_HBDChannelManager::IsValidID(module_id, pad_id)){
    int k_module_id = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
    return status[k_module_id][pad_id];
  }else{
    return -1;
  }
}

void E16ANA_HBDDeadChannel::GetOKChannels(const int module_id, std::vector<int> &ok_chs){
  ok_chs.clear();
  if(E16ANA_HBDChannelManager::IsValidModuleID(module_id)){
    for(int i=0; i<n_pads; i++){
      if(IsOK(module_id, i)){
	ok_chs.push_back(i);
      }
    }
  }
}

void E16ANA_HBDDeadChannel::Init(){
  for(int i=0; i<n_modules; i++){
    for(int j=0; j<n_pads; j++){
      status[i][j] = -1;
    }
  }
}
