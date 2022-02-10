#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRStatus.h"
#include "E16ANA_GTRChannelManager.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

E16ANA_GTRStatus::E16ANA_GTRStatus(const int runID){
	asd_dead = new E16ANA_GTRASDDeadChannel();
	gem_dead = new E16ANA_GTRGEMDeadArea();
    asd_dead->ReadDeadChannelData(runID);
    gem_dead->ReadDeadChannelData(runID);
	
}

E16ANA_GTRStatus::~E16ANA_GTRStatus()
{
	delete asd_dead;
}

E16ANA_GTRASDDeadChannel::E16ANA_GTRASDDeadChannel(){

}
E16ANA_GTRASDDeadChannel::~E16ANA_GTRASDDeadChannel(){
}


E16ANA_GTRGEMDeadArea::E16ANA_GTRGEMDeadArea(){

}
E16ANA_GTRGEMDeadArea::~E16ANA_GTRGEMDeadArea(){
}



bool E16ANA_GTRASDDeadChannel::ReadFile(const char *filename){
  Init();
  std::ifstream fin(filename);
  if( fin ){
    std::string buf_line;
    for(;;){
      if(fin.eof()){
//			fin.close();
	   break;
	  }
      std::getline(fin, buf_line);

      if(buf_line[0] == '#' || buf_line[0] == '\0') continue;

      std::stringstream ss(buf_line);
      int module_id;
      int ch;
      int buf_status;
      ss>>module_id>>ch>>buf_status;
	  std::cout << "module" << module_id << "ch " << ch << ", " << buf_status << std::endl;
      if(E16ANA_GTRChannelManager::IsValidASDID(module_id, ch)){
		int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
		status_asd[k_module][ch] = buf_status;
      }
    }
    return true;
  }
  else{
    std::cerr<<__func__<<" invalid dead channel filename"<<std::endl;
    return false;
  }
}

	



bool E16ANA_GTRStatus::Is300YOK(const int module_id, const int ch){
  bool flag = false;
  if(E16ANA_GTRChannelManager::IsValidASDID(module_id, ch)){
	int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
  	if(asd_dead->IsOK(module_id, ch)){
		if(gem_dead->Is300YOK(module_id, ch)){
			flag = true;
		}
	} 
   }
   return flag;
}

int E16ANA_GTRStatus::StatusYch(const int module_id, const int ch){
	int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
	return status_ych[k_module][ch];	
}


bool E16ANA_GTRASDDeadChannel::ReadDeadChannelData(const int runID){
  E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
  std::string gtr_asd_dead_channel_file = calib.CalibFileName("GTR-asdch-status", runID);
  this->ReadFile(gtr_asd_dead_channel_file.c_str());
  return true;
}

bool E16ANA_GTRASDDeadChannel::IsOK(const int module_id, const int ch){
  bool flag = false;
  if(E16ANA_GTRChannelManager::IsValidASDID(module_id, ch)){
	int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
  	if(status_asd[k_module][ch] == ok_flag) {
		flag = true;
	}
   }
   return flag;
}

bool E16ANA_GTRASDDeadChannel::IsDead(const int module_id, const int ch){
  bool flag = false;
  if(E16ANA_GTRChannelManager::IsValidASDID(module_id, ch)){
	int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
  	if(status_asd[k_module][ch] == dead_flag) {
		flag = true;
	}
   }
   return flag;
}

bool E16ANA_GTRASDDeadChannel::IsNoisy(const int module_id, const int ch){
  bool flag = false;
  if(E16ANA_GTRChannelManager::IsValidASDID(module_id, ch)){
	int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
  	if(status_asd[k_module][ch] == noisy_flag) {
		flag = true;
	}
   }
   return flag;
}

bool E16ANA_GTRASDDeadChannel::IsHot(const int module_id, const int ch){
  bool flag = false;
  if(E16ANA_GTRChannelManager::IsValidASDID(module_id, ch)){
	int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
  	if(status_asd[k_module][ch] == hot_flag) {
		flag = true;
	}
   }
   return flag;
}

int E16ANA_GTRASDDeadChannel::Status(const int module_id, const int ch){
	int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
    return status_asd[k_module][ch];
}

//void E16ANA_GTRASDDeadChannel::GetOKChannels(const int module_id, std::vector<int> &ok_chs){
//  ok_chs.clear();
//  if(E16ANA_GTRASDChannelManager::IsValidModuleID(module_id)){
//    for(int i=0; i<n_pads; i++){
//      if(IsOK(module_id, i)){
//	ok_chs.push_back(i);
//      }
//    }
//  }
//}
void E16ANA_GTRStatus::Init(){
  for(int i=0; i<n_modules; i++){
    for(int j=0; j<n_ychs; j++){
      status_ych[i][j] = -1;
    }
  }
}
void E16ANA_GTRASDDeadChannel::Init(){
  for(int i=0; i<n_modules; i++){
    for(int j=0; j<n_ychs; j++){
      status_asd[i][j] = -1;
    }
  }
}
void E16ANA_GTRGEMDeadArea::Init(){
  for(int i=0; i<n_modules; i++){
    for(int j=0; j<n_ychs; j++){
      status_300gem_y[i][j] = -1;
    }
  }
}


bool E16ANA_GTRGEMDeadArea::ReadFile(const char *filename){
  Init();
  std::ifstream fin(filename);
  if( fin ){
    std::string buf_line;
    for(;;){
      if(fin.eof()){
//			fin.close();
	   break;
	  }
      std::getline(fin, buf_line);

      if(buf_line[0] == '#' || buf_line[0] == '\0') continue;

      std::stringstream ss(buf_line);
      int module_id;
      int ch;
      int buf_status;
      ss>>module_id>>ch>>buf_status;
	  std::cout << "module" << module_id << "ch " << ch << ", " << buf_status << std::endl;
      if(E16ANA_GTRChannelManager::IsValidASDID(module_id, ch)){
		int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
		status_300gem_y[k_module][ch] = buf_status;
      }
    }
    return true;
  }
  else{
    std::cerr<<__func__<<" invalid dead channel filename"<<std::endl;
    return false;
  }
}

bool E16ANA_GTRGEMDeadArea::ReadDeadChannelData(const int runID){
  E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
  std::string gtr_300gem_dead_channel_file = calib.CalibFileName("GTR-300gemy-status", runID);
  this->ReadFile(gtr_300gem_dead_channel_file.c_str());
  return true;
}

bool E16ANA_GTRGEMDeadArea::Is300YOK(const int module_id, const int ch){
  bool flag = false;
  if(E16ANA_GTRChannelManager::IsValidASDID(module_id, ch)){
	int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
  	if(status_300gem_y[k_module][ch] == ok_flag) {
		flag = true;
	}
   }
   return flag;
}


