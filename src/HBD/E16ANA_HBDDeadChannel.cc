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
      char type;//p: pad, t: triggertile
      int module_id;
      int ch_id;//pad_id or triggertile_id
      int buf_status;
      int k_module_id;
      ss>>type>>module_id>>ch_id>>buf_status;
      
      if(type != 'p' || type != 't'){//for backward compatibility
	ss.str("");
	ss.clear(std::stringstream::goodbit);
	ss<<buf_line;
	ss>>module_id>>ch_id>>buf_status;
	if(E16ANA_HBDChannelManager::IsValidID(module_id, ch_id)){
	  k_module_id = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
	  status[k_module_id][ch_id] = buf_status;
	}
      }
      else{
	if(E16ANA_HBDChannelManager::IsValidModuleID(module_id)){
	  if(type == 'p' && E16ANA_HBDChannelManager::IsValidPadID(ch_id)){
	    k_module_id = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
	    status[k_module_id][ch_id] = buf_status;
	  }
	  else if(type == 't' && E16ANA_HBDChannelManager::IsValidTileID(ch_id)){
	    k_module_id = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
	    int tile_id_0to35 = E16ANA_HBDChannelManager::ConvTIDE16ToK(ch_id);
	    status_tile[k_module_id][tile_id_0to35] = buf_status;
	  }
	}
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

  return true;
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

bool E16ANA_HBDDeadChannel::IsOKTile(const int module_id, const int tile_id){
  bool flag = false;
  if(E16ANA_HBDChannelManager::IsValidModuleID(module_id)){
    if(E16ANA_HBDChannelManager::IsValidTileID(tile_id)){
      int k_module_id = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
      int kid = E16ANA_HBDChannelManager::ConvTIDE16ToK(tile_id);
      if(status_tile[k_module_id][kid] == ok_flag) flag = true;
    }
  }
  
  return flag;
}

bool E16ANA_HBDDeadChannel::IsDeadTile(const int module_id, const int tile_id){
  bool flag = false;
  if(E16ANA_HBDChannelManager::IsValidModuleID(module_id)){
    if(E16ANA_HBDChannelManager::IsValidTileID(tile_id)){
      int k_module_id = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
      int kid = E16ANA_HBDChannelManager::ConvTIDE16ToK(tile_id);
      if(status_tile[k_module_id][kid] == dead_flag) flag = true;
    }
  }
  
  return flag;
}

bool E16ANA_HBDDeadChannel::IsNoisyTile(const int module_id, const int tile_id){
  bool flag = false;
  if(E16ANA_HBDChannelManager::IsValidModuleID(module_id)){
    if(E16ANA_HBDChannelManager::IsValidTileID(tile_id)){
      int k_module_id = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
      int kid = E16ANA_HBDChannelManager::ConvTIDE16ToK(tile_id);
      if(status_tile[k_module_id][kid] == noisy_flag) flag = true;
    }
  }
  
  return flag;
}

bool E16ANA_HBDDeadChannel::IsHotTile(const int module_id, const int tile_id){
  bool flag = false;
  if(E16ANA_HBDChannelManager::IsValidModuleID(module_id)){
    if(E16ANA_HBDChannelManager::IsValidTileID(tile_id)){
      int k_module_id = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
      int kid = E16ANA_HBDChannelManager::ConvTIDE16ToK(tile_id);
      if(status_tile[k_module_id][kid] == hot_flag) flag = true;
    }
  }
  
  return flag;
}

int E16ANA_HBDDeadChannel::StatusTile(const int module_id, const int tile_id){
  
  if(E16ANA_HBDChannelManager::IsValidModuleID(module_id)){
    if(E16ANA_HBDChannelManager::IsValidTileID(tile_id)){
      int k_module_id = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
      int kid = E16ANA_HBDChannelManager::ConvTIDE16ToK(tile_id);
      return status_tile[k_module_id][kid];
    }
  }
  return -1;
}

void E16ANA_HBDDeadChannel::GetOKChannelsTile(const int module_id, std::vector<int> &ok_chs){
  ok_chs.clear();
  if(E16ANA_HBDChannelManager::IsValidModuleID(module_id)){
    for(int i=0; i<n_tiles; i++){
      int tile_id = E16ANA_HBDChannelManager::ConvTIDKToE16(i);
      if(IsOKTile(module_id, tile_id)){
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
    for(int j=0; j<n_tiles; j++){
      status_tile[i][j] = -1;
    }
  }
  
}
