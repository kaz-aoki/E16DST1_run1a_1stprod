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
	gem_dead_100 = new E16ANA_GTR100GEMDeadArea();
	gem_dead_200 = new E16ANA_GTR200GEMDeadArea();
	gem_dead_300 = new E16ANA_GTR300GEMDeadArea();
    asd_dead->ReadDeadChannelData(runID);
	gem_dead_100->Init();
	gem_dead_200->Init();
	gem_dead_300->Init();
    gem_dead_100->ReadDeadChannelData(runID);
    gem_dead_200->ReadDeadChannelData(runID);
    gem_dead_300->ReadDeadChannelData(runID);
}

E16ANA_GTRStatus::~E16ANA_GTRStatus()
{
	delete asd_dead;
    delete gem_dead_100;
    delete gem_dead_200;
    delete gem_dead_300;
}

E16ANA_GTRASDDeadChannel::E16ANA_GTRASDDeadChannel(){

}
E16ANA_GTRASDDeadChannel::~E16ANA_GTRASDDeadChannel(){
}


E16ANA_GTRGEMDeadArea::E16ANA_GTRGEMDeadArea(int _n_strip_gem_x, int _n_strip_gem_y)
	: n_gem_strip_x(_n_strip_gem_x), n_gem_strip_y(_n_strip_gem_y){
	
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
	 // std::cout << "reading file :: module" << module_id << "ch " << ch << ", " << buf_status << std::endl;
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
		//if(gem_dead->Is300YOK(module_id, ch)){
		//	flag = true;
		//}
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
  status_gem_x.resize(n_modules);
  status_gem_y.resize(n_modules); 
  for(int i =0; i< n_modules; i++){
  	status_gem_x[i].resize(n_gem_strip_x);
  	status_gem_y[i].resize(n_gem_strip_y);
  }
  for(int i=0; i<n_modules; i++){
    for(int j=0; j<n_gem_strip_x; j++){
      status_gem_x[i][j] = -1;
    }
    for(int j=0; j<n_gem_strip_y; j++){
      status_gem_y[i][j] = -1;
    }
  }
}
//void E16ANA_GTR100GEMDeadArea::Init(){
//  for(int i=0; i<n_modules; i++){
//    for(int j=0; j<n_gem_strip_x; j++){
//      status_gem_x[i][j] = -1;
//    }
//    for(int j=0; j<n_gem_strip_y; j++){
//      status_gem_y[i][j] = -1;
//    }
//  }
//}
//void E16ANA_GTR200GEMDeadArea::Init(){
//  for(int i=0; i<n_modules; i++){
//    for(int j=0; j<n_gem_strip_x; j++){
//      status_gem_x[i][j] = -1;
//    }
//    for(int j=0; j<n_gem_strip_y; j++){
//      status_gem_y[i][j] = -1;
//    }
//  }
//}
//void E16ANA_GTR300GEMDeadArea::Init(){
//  for(int i=0; i<n_modules; i++){
//    for(int j=0; j<n_gem_strip_x; j++){
//      status_gem_x[i][j] = -1;
//    }
//    for(int j=0; j<n_gem_strip_y; j++){
//      status_gem_y[i][j] = -1;
//    }
//  }
//}
bool E16ANA_GTRGEMDeadArea::IsXOK(const int module_id, const int ch){
  bool flag = false;
	if(E16ANA_GTRChannelManager::IsValidModuleID(module_id)){
	int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
  	if(status_gem_x[k_module][ch] == ok_flag) {
		flag = true;
	}
   }
   return flag;
}

bool E16ANA_GTRGEMDeadArea::IsYOK(const int module_id, const int ch){
  bool flag = false;
	if(E16ANA_GTRChannelManager::IsValidModuleID(module_id)){
	int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
  	if(status_gem_y[k_module][ch] == ok_flag) {
		flag = true;
	}
   }
   return flag;
}

bool E16ANA_GTRGEMDeadArea::ReadFile(const char *filename, int xy){//x == 0 , y == 1
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
//	  std::cout << "reading GEM dead file : module" << module_id << "ch " << ch << ", " << buf_status << std::endl;
      if(E16ANA_GTRChannelManager::IsValidModuleID(module_id)){
		int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
		if(xy == 0) status_gem_x[k_module][ch] = buf_status;
		else if(xy == 1) status_gem_y[k_module][ch] = buf_status;
      }
    }
    return true;
  }
  else{
    std::cerr<<__func__<<" invalid dead channel filename"<<std::endl;
    return false;
  }
}
bool E16ANA_GTR100GEMDeadArea::ReadDeadChannelData(const int runID){
  E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
  std::string gtr_100gem_dead_channel_file_x = calib.CalibFileName("GTR-100gemx-status", runID);
  if(this->ReadFile(gtr_100gem_dead_channel_file_x.c_str(), 0)){ return true;}
	else {std::cout << "failed to read 100x gem dead file " << std::endl; return false;}
  std::string gtr_100gem_dead_channel_file_y = calib.CalibFileName("GTR-100gemy-status", runID);
  if(this->ReadFile(gtr_100gem_dead_channel_file_y.c_str(), 1)){ return true;}
    else {return false;}
}
bool E16ANA_GTR200GEMDeadArea::ReadDeadChannelData(const int runID){
  E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
  std::string gtr_200gem_dead_channel_file_x = calib.CalibFileName("GTR-200gemx-status", runID);
  this->ReadFile(gtr_200gem_dead_channel_file_x.c_str(), 0);
  std::string gtr_200gem_dead_channel_file_y = calib.CalibFileName("GTR-200gemy-status", runID);
  this->ReadFile(gtr_200gem_dead_channel_file_y.c_str(), 1);
  return true;
}

bool E16ANA_GTR300GEMDeadArea::ReadDeadChannelData(const int runID){
  E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
  std::string gtr_300gem_dead_channel_file_x = calib.CalibFileName("GTR-300gemx-status", runID);
  this->ReadFile(gtr_300gem_dead_channel_file_x.c_str(), 0);
  std::string gtr_300gem_dead_channel_file_y = calib.CalibFileName("GTR-300gemy-status", runID);
  this->ReadFile(gtr_300gem_dead_channel_file_y.c_str(), 1);
  return true;
}

//bool E16ANA_GTRGEMDeadArea::Is300YOK(const int module_id, const int ch){
//  bool flag = false;
//  if(E16ANA_GTRChannelManager::IsValidASDID(module_id, ch)){
//	int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
//  	if(status_300gem_y[k_module][ch] == ok_flag) {
//		flag = true;
//	}
//   }
//   return flag;
//}


