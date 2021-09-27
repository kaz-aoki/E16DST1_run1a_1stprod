#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_LGDeadChannel.hh"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

E16ANA_LGDeadChannel::E16ANA_LGDeadChannel()
{
}

E16ANA_LGDeadChannel::~E16ANA_LGDeadChannel()
{
}

bool E16ANA_LGDeadChannel::ReadFile(const char *filename){
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
      int block_id;
      int buf_status;
      //int k_module_id;
      ss>>module_id>>block_id>>buf_status;
      
      status[module_id][block_id] = buf_status;
      //if(E16ANA_LGChannelManager::IsValidID(module_id, block_id)){
      //k_module_id = E16ANA_LGChannelManager::ConvMIDE16ToK(module_id);
      //status[k_module_id][block_id] = buf_status;
      //}     
    }
    return true;
  }
  else{
    std::cerr<<__func__<<" invalid dead channel filename"<<std::endl;
    return false;
  }
}

bool E16ANA_LGDeadChannel::ReadDeadChannelData(){
  E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
  
  std::string lg_dead_channel_file = calib.CalibFileName("LG-deadch", calib.CurrentRunID() );
  
  this->ReadFile(lg_dead_channel_file.c_str());
}

bool E16ANA_LGDeadChannel::IsOK(const int module_id, const int block_id){
  bool flag = false;
  //if(E16ANA_LGChannelManager::IsValidID(module_id, block_id)){
  //int k_module_id = E16ANA_LGChannelManager::ConvMIDE16ToK(module_id);
    if(status[module_id][block_id] == ok_flag) flag = true;
    //}
  
  return flag;
}

bool E16ANA_LGDeadChannel::IsDead(const int module_id, const int block_id){
  bool flag = false;
  //if(E16ANA_LGChannelManager::IsValidID(module_id, block_id)){
  //int k_module_id = E16ANA_LGChannelManager::ConvMIDE16ToK(module_id);
    if(status[module_id][block_id] == dead_flag) flag = true;
    //}
  
  return flag;
}

bool E16ANA_LGDeadChannel::IsNoisy(const int module_id, const int block_id){
  bool flag = false;
  //if(E16ANA_LGChannelManager::IsValidID(module_id, block_id)){
  //int k_module_id = E16ANA_LGChannelManager::ConvMIDE16ToK(module_id);
    if(status[module_id][block_id] == noisy_flag) flag = true;
    //}
  
  return flag;
}

bool E16ANA_LGDeadChannel::IsHot(const int module_id, const int block_id){
  bool flag = false;
  //if(E16ANA_LGChannelManager::IsValidID(module_id, block_id)){
  //int k_module_id = E16ANA_LGChannelManager::ConvMIDE16ToK(module_id);
    if(status[module_id][block_id] == hot_flag) flag = true;
    //}
  
  return flag;
}

int E16ANA_LGDeadChannel::Status(const int module_id, const int block_id){
  //if(E16ANA_LGChannelManager::IsValidID(module_id, block_id)){
  //int k_module_id = E16ANA_LGChannelManager::ConvMIDE16ToK(module_id);
    return status[module_id][block_id];
    //}else{
    //return -1;
    //}
}

void E16ANA_LGDeadChannel::GetOKChannels(const int module_id, std::vector<int> &ok_chs){
  ok_chs.clear();
  //if(E16ANA_LGChannelManager::IsValidModuleID(module_id)){
    for(int i=0; i<n_blocks; i++){
      if(IsOK(module_id, i)){
	ok_chs.push_back(i);
      }
    }
    //}
}

void E16ANA_LGDeadChannel::Init(){
  for(int i=0; i<n_modules; i++){
    for(int j=0; j<n_blocks; j++){
      status[i][j] = -1;
    }
  }
}
