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

void E16ANA_LGDeadChannel::ReadDeadChannelData(){

  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
  FILE* fp_dc = calib.CalibFileOpenBinary("LG-deadch", calib.CurrentRunID() );
  if ( fp_dc==NULL ) {
    std::cout<<"[Error] dead channel map file is not found !"<<std::endl;
    exit(1);
  }
  int module, block;
  int ch_status;
  while( feof(fp_dc)==0 ){
    fscanf(fp_dc, "%d %d %d", &module, &block, &ch_status );
    if(!(0<=module&&module<110&&0<=block&&block<60)){
      std::cerr<<"read invalid ID in dead channel map file"<<std::endl;
      exit(1);
    }
    else{
      status[module][block] = ch_status;
    }
  }
  fclose(fp_dc);

}

bool E16ANA_LGDeadChannel::IsOK(const int module, const int block){
  bool flag = false;
  if(0<=module&&module<110&&0<=block&&block<60){
    if(status[module][block] == ok_flag) flag = true;
  }
  
  return flag;
}

bool E16ANA_LGDeadChannel::IsDead(const int module, const int block){
  bool flag = false;
  if(0<=module&&module<110&&0<=block&&block<60){
    if(status[module][block] == dead_flag) flag = true;
  }
  
  return flag;
}

bool E16ANA_LGDeadChannel::IsNoisy(const int module, const int block){
  bool flag = false;
  if(0<=module&&module<110&&0<=block&&block<60){
    if(status[module][block] == noisy_flag) flag = true;
  }
  
  return flag;
}

bool E16ANA_LGDeadChannel::IsHot(const int module, const int block){
  bool flag = false;
  if(0<=module&&module<110&&0<=block&&block<60){
    if(status[module][block] == hot_flag) flag = true;
  }
  
  return flag;
}

int E16ANA_LGDeadChannel::Status(const int module, const int block){
  if(0<=module&&module<110&&0<=block&&block<60){
    return status[module][block];
  }else{
    return -1;
  }
}

/*
void E16ANA_LGDeadChannel::GetOKChannels(const int module_id, std::vector<int> &ok_chs){
  ok_chs.clear();
  if(E16ANA_LGChannelManager::IsValidModuleID(module_id)){
    for(int i=0; i<n_blocks; i++){
      if(IsOK(module_id, i)){
	ok_chs.push_back(i);
      }
    }
  }
}
*/

void E16ANA_LGDeadChannel::Init(){
  for(int i=0; i<n_modules; i++){
    for(int j=0; j<n_blocks; j++){
      status[i][j] = -1;
    }
  }
}
