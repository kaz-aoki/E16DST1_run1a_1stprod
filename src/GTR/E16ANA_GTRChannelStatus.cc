#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRChannelStatus.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

E16ANA_GTRChannelStatus::E16ANA_GTRChannelStatus()
{
}

E16ANA_GTRChannelStatus::~E16ANA_GTRChannelStatus()
{
}

void E16ANA_GTRChannelStatus::ReadASDChannelStatusData(){
  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
  FILE* fp_dc = calib.CalibFileOpenBinary("GTR-asdch-status", calib.CurrentRunID() );
  if ( fp_dc==NULL ) {
    std::cout<<"[Error] asd channel status map file is not found !"<<std::endl;
    exit(1);
  }
  int module, ch;
  int ch_status;
  while( feof(fp_dc)==0 ){
    fscanf(fp_dc, "%d %d %d", &module, &ch, &ch_status );
    if(!(100<=module&&module<110&&0<=ch&ch<24)){
      std::cerr<<"read invalid ID in dead channel map file"<<std::endl;
      exit(1);
    }
    else{
      asd_status[module][ch] = ch_status;
    }
  }
  fclose(fp_dc);
}

bool E16ANA_GTRChannelStatus::IsASDOK(const int module, const int ch){
  bool flag = false;
  if(100<=module&&module<110 && 0<=ch&&ch<24){
    if(asd_status[module][ch] == ok_flag) flag = true;
  }
  
  return flag;
}

bool E16ANA_GTRChannelStatus::IsASDDead(const int module, const int ch){
  bool flag = false;
  if(100<=module&&module<110 && 0<=ch&&ch<24){
    if(asd_status[module][ch] == dead_flag) flag = true;
  }
  
  return flag;
}

//bool E16ANA_GTRChannelStatus::IsNoisy(const int module, const int block){
//  bool flag = false;
//  if(0<=module&&module<110&&0<=block&&block<60){
//    if(status[module][block] == noisy_flag) flag = true;
//  }
//  
//  return flag;
//}
//
//bool E16ANA_GTRChannelStatus::IsHot(const int module, const int block){
//  bool flag = false;
//  if(0<=module&&module<110&&0<=block&&block<60){
//    if(status[module][block] == hot_flag) flag = true;
//  }
//  
//  return flag;
//}

int E16ANA_GTRChannelStatus::ASDStatus(const int module, const int ch){
  if(100<=module&&module<110 && 0<=ch&&ch<24){
    return asd_status[module][ch];
  }else{
    return -1;
  }
}

/*
void E16ANA_GTRChannelStatus::GetOKChannels(const int module_id, std::vector<int> &ok_chs){
  ok_chs.clear();
  if(E16ANA_GTRChannelManager::IsValidModuleID(module_id)){
    for(int i=0; i<n_blocks; i++){
      if(IsOK(module_id, i)){
	ok_chs.push_back(i);
      }
    }
  }
}
*/

void E16ANA_GTRChannelStatus::Init(){
  for(int i=0; i<n_modules; i++){
    for(int j=0; j<n_asd_chs; j++){
      asd_status[i][j] = -1;
    }
  }
}
