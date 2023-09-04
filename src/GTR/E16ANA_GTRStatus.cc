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
//	apv_dead_100 = new E16ANA_GTR100APVDeadChannel();
//	apv_dead_200 = new E16ANA_GTR200APVDeadChannel();
//	apv_dead_300 = new E16ANA_GTR300APVDeadChannel();
	apv_dead = new E16ANA_GTRAPVDeadChannel();
    asd_dead->ReadDeadChannelData(runID);
	gem_dead_100->Init();
	gem_dead_200->Init();
	gem_dead_300->Init();
//	apv_dead_100->Init();
//	apv_dead_200->Init();
//	apv_dead_300->Init();
    gem_dead_100->ReadDeadChannelData(runID);
    gem_dead_200->ReadDeadChannelData(runID);
    gem_dead_300->ReadDeadChannelData(runID);
//	apv_dead_100->ReadDeadChannelData(runID);
//	apv_dead_200->ReadDeadChannelData(runID);
//	apv_dead_300->ReadDeadChannelData(runID);
	apv_dead->Init();
	apv_dead->ReadDeadChannelData(runID);
}

E16ANA_GTRStatus::~E16ANA_GTRStatus()
{
	delete asd_dead;
    delete gem_dead_100;
    delete gem_dead_200;
    delete gem_dead_300;
	delete apv_dead;
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

E16ANA_GTRAPVDeadChannel::E16ANA_GTRAPVDeadChannel(){
}
E16ANA_GTRAPVDeadChannel::~E16ANA_GTRAPVDeadChannel(){
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
void E16ANA_GTRAPVDeadChannel::Init(){
//status_apv resize 
  status_apv.resize(n_modules);
  int n_strips[n_layers][n_axes] = {{n_strips_100x, n_strips_100y},{n_strips_200x, n_strips_200y}, {n_strips_300x, n_strips_300y}};
  for(int m =0; m< n_modules;m++){
	status_apv[m].resize(n_layers);
	for(int l=0; l < n_layers; l++){
		status_apv[m][l].resize(n_axes);//two dimensional strips
		for(int a=0; a<n_axes; a++){
			status_apv[m][l][a].resize(n_strips[l][a]);
		}
  	}
  }
// status_apv initialize
  for(int m =0; m< n_modules;m++){
	for(int l=0; l < n_layers; l++){
		for(int a=0; a<n_axes; a++){
			for(int c=0; c < n_strips[l][a]; c++){
				status_apv[m][l][a][c] = -1;
			}
		}
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
bool E16ANA_GTRGEMDeadArea::IsXOK(const int module_id, const int gem_ch){
  	bool flag = false;
	if(E16ANA_GTRChannelManager::IsValidModuleID(module_id)){
		int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
  		if(status_gem_x[k_module][gem_ch] == ok_flag) {
			flag = true;
		}
   }
   return flag;
}

bool E16ANA_GTRGEMDeadArea::IsXOK(const int module_id, const double lx_mm){
	bool flag = false;	
	if(E16ANA_GTRChannelManager::IsValidModuleID(module_id)){
		int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
        int gem_ch = E16ANA_GTRChannelManager::ConvLocalXToGEMch(n_gem_strip_x, lx_mm);
  		if(status_gem_x[k_module][gem_ch] == ok_flag) {
			flag = true;
		}
  	}
   	return flag;
}

bool E16ANA_GTRGEMDeadArea::IsYOK(const int module_id, const int gem_ch){
  bool flag = false;
	if(E16ANA_GTRChannelManager::IsValidModuleID(module_id)){
	int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
  	if(status_gem_y[k_module][gem_ch] == ok_flag) {
		flag = true;
	}
   }
   return flag;
}
bool E16ANA_GTRGEMDeadArea::IsYOK(const int module_id, const double ly_mm){
  bool flag = false;
	if(E16ANA_GTRChannelManager::IsValidModuleID(module_id)){
		int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
        int gem_ch = E16ANA_GTRChannelManager::ConvLocalYToGEMch(n_gem_strip_y, ly_mm);
//		std::cout << "ly, gem ch  = " << ly_mm << ", " << gem_ch << std::endl;
//		std::cout << "status " << status_gem_y[k_module][gem_ch] << std::endl;
		
  	if(status_gem_y[k_module][gem_ch] == ok_flag) {
		flag = true;
//		std::cout  << "flag " << flag << std::endl;
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
		if(xy == 0) {status_gem_x[k_module][ch] = buf_status;}
		else if(xy == 1) {status_gem_y[k_module][ch] = buf_status;}
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
  if(this->ReadFile(gtr_100gem_dead_channel_file_x.c_str(), 0)){ 
//	return true;
	}
	else {std::cout << "failed to read 100x gem dead file " << std::endl;
 return false;
	}
  std::string gtr_100gem_dead_channel_file_y = calib.CalibFileName("GTR-100gemy-status", runID);
  if(this->ReadFile(gtr_100gem_dead_channel_file_y.c_str(), 1)){ 
	//return true;
	}
    else {
		std::cout << "failed to read 100y gem dead file " << std::endl;	
		return false;
		}
	return true;
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
//
bool E16ANA_GTRAPVDeadChannel::ReadDeadChannelData(const int runID){	
    E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
    std::string gtr_apv_dead_channel_file = calib.CalibFileName("GTR-apv-status", runID);
	if(this->ReadFile(gtr_apv_dead_channel_file.c_str())){ 
	}
	else {std::cout << "failed to read APV dead file " << std::endl;
		return false;
	}
	return true;
}

bool E16ANA_GTRAPVDeadChannel::ReadFile(const char *filename){
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
	  int size;
	  std::string axis;
      int ch;
      int buf_status;
      ss >> module_id >> size >> axis >> ch >> buf_status;
      if(E16ANA_GTRChannelManager::IsValidModuleID(module_id)){
		int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(module_id); 
		if     (axis == "X") {status_apv[k_module][size][0][ch] = buf_status;}
		else if(axis == "Y") {status_apv[k_module][size][1][ch] = buf_status;}//including Yb
      }
    }
    return true;
  }
  else{
    std::cerr<<__func__<<" invalid dead channel filename"<<std::endl;
    return false;
  }
}


int E16ANA_GTRAPVDeadChannel::Status(const int mid, const int lid, const int ch_x, const int ch_y){
	int flag = -1;
	if(E16ANA_GTRChannelManager::IsValidModuleID(mid)){
		int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(mid); 
//		std::cout << " xx " << status_apv[k_module][lid][0][ch_x] << " , y " << status_apv[k_module][lid][1][ch_y] << std::endl; 
  		if(      status_apv[k_module][lid][0][ch_x] == ok_flag 
		      && status_apv[k_module][lid][1][ch_y] == ok_flag) {
			flag = ok_flag;
		}
  		else if( status_apv[k_module][lid][0][ch_x] == dead_flag 
		      || status_apv[k_module][lid][1][ch_y] == dead_flag) {
			flag = dead_flag;
		}
  		else if( status_apv[k_module][lid][0][ch_x] == hot_flag 
		      || status_apv[k_module][lid][1][ch_y] == hot_flag) {
			flag = hot_flag;
		}
  		else if( status_apv[k_module][lid][0][ch_x] == noisy_flag 
		      || status_apv[k_module][lid][1][ch_y] == noisy_flag) {
			flag = noisy_flag;
		}
	}
	return flag;
}

int E16ANA_GTRAPVDeadChannel::XStatus(const int mid, const int lid, const int ch_x){
	int flag = -1;
	if(E16ANA_GTRChannelManager::IsValidModuleID(mid)){
		int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(mid); 
  		flag = status_apv[k_module][lid][0][ch_x]; 
	}
	return flag;
}

int E16ANA_GTRAPVDeadChannel::YStatus(const int mid, const int lid,  const int ch_y){
	int flag = -1;
	if(E16ANA_GTRChannelManager::IsValidModuleID(mid)){
		int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(mid); 
  		flag = status_apv[k_module][lid][1][ch_y]; 
	}
	return flag;
}

//bool E16ANA_GTRStatus::IsOK(const int mid, const int lid, const int ch_x, const int ch_y){
//	bool flag = false;
//	bool flag_gem = false;
//	bool flag_apv = false;
//	E16ANA_GTRGEMDeadArea * gem_dead[3] = {gem_dead_100, gem_dead_200, gem_dead_300};
//	if(E16ANA_GTRChannelManager::IsValidModuleID(mid)){
//		int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(mid); 
////		std::cout << "gem x " << gem_dead[lid]->IsXOK(mid, ch_x) << std::endl;
////		std::cout << "gem y " << gem_dead[lid]->IsYOK(mid, ch_y) << std::endl;
//		if(gem_dead[lid]->IsXOK(mid, ch_x)){
//		 if(gem_dead[lid]->IsYOK(mid, ch_y)){		
//			flag_gem = true;
//			}
//		}
//  		if( apv_dead->IsOK(mid, lid, ch_x, ch_y) == ok_flag ) {
//			flag_apv = true;
//		}
//   }
//	if(mid ==101 && lid ==2 && ch_x == 660 && ch_y ==20){
//   std::cout << "flag_apv " << flag_apv << std::endl;
//   std::cout << "flag_gem " << flag_gem << std::endl;
//	}
//   if (flag_gem){
//		if(flag_apv){
//   			flag = true;
//		}
//	}
//	return flag;
//}

int E16ANA_GTRStatus::GTRStatus(const int mid, const int lid, const double lx, const double ly){
	int gtr_flag = -1;
	int gem_flag = -1;
	int apv_flag = -1;
	E16ANA_GTRGEMDeadArea * gem_dead[3] = {gem_dead_100, gem_dead_200, gem_dead_300};
	int apv_ch_x = E16ANA_GTRChannelManager::ConvLocalXToAPVch(lid, lx);
	int apv_ch_y = E16ANA_GTRChannelManager::ConvLocalYToAPVch(lid, lx, ly);//if over 72, it is Yb
//		std::cout << "apv x ch " << apv_ch_x << std::endl;
	
//	if(mid ==101 && lid == 2 && apv_ch_x == 660 ){
//		std::cout << "apv x ch " << apv_ch_x << std::endl;
//		std::cout << "apv y ch " << apv_ch_y << std::endl;
//	}
	if(E16ANA_GTRChannelManager::IsValidModuleID(mid)){
		int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(mid); 
		if(gem_dead[lid]->IsXOK(mid, lx)){
		   if(gem_dead[lid]->IsYOK(mid, ly)){		
			  gem_flag = ok_flag;
		   }
		   else {gem_flag = dead_flag;}
		}
		else {gem_flag = dead_flag;}
  		apv_flag = apv_dead->Status(mid, lid, apv_ch_x, apv_ch_y); 
	}
	if(gem_flag == ok_flag){
     	gtr_flag = apv_flag ;
    }
    else {gtr_flag == dead_flag;}
	//	std::cout << "apv flag " << flag_apv << std::endl;
	return gtr_flag;
}

int E16ANA_GTRStatus::GTRXStatus(const int mid, const int lid, const double lx){
	int gtr_flag = -1;
	int gem_flag = -1;
	int apv_flag = -1;
	E16ANA_GTRGEMDeadArea * gem_dead[3] = {gem_dead_100, gem_dead_200, gem_dead_300};
	int apv_ch_x = E16ANA_GTRChannelManager::ConvLocalXToAPVch(lid, lx);
	if(E16ANA_GTRChannelManager::IsValidModuleID(mid)){
		int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(mid); 
		if(gem_dead[lid]->IsXOK(mid, lx)){
			gem_flag = ok_flag;
		}
		else {gem_flag = dead_flag;}
  		apv_flag = apv_dead->XStatus(mid, lid, apv_ch_x); 
	}
	if(gem_flag == ok_flag){
     	gtr_flag = apv_flag;
    }
    else {gtr_flag == dead_flag;}
	//	std::cout << "apv flag " << flag_apv << std::endl;
	return gtr_flag;
}

int E16ANA_GTRStatus::GTRYStatus(const int mid, const int lid, const double lx, const double ly){
	int gtr_flag = -1;
	int gem_flag = -1;
	int apv_flag = -1;
	E16ANA_GTRGEMDeadArea * gem_dead[3] = {gem_dead_100, gem_dead_200, gem_dead_300};
	int apv_ch_y = E16ANA_GTRChannelManager::ConvLocalYToAPVch(lid, lx, ly);
	if(E16ANA_GTRChannelManager::IsValidModuleID(mid)){
		int k_module = E16ANA_GTRChannelManager::ConvMIDE16ToK(mid); 
		if(gem_dead[lid]->IsYOK(mid, ly)){		
			gem_flag = ok_flag;
		}
		else {gem_flag = dead_flag;}
  		apv_flag = apv_dead->YStatus(mid, lid, apv_ch_y); 
	}
	if(gem_flag == ok_flag){
     	gtr_flag = apv_flag;
    }
    else {gtr_flag == dead_flag;}
	//	std::cout << "apv flag " << flag_apv << std::endl;
	return gtr_flag;
}

//bool E16ANA_GTR100APVDeadChannel::ReadDeadChannelData(const int runID){
//  E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
//  std::string gtr_100apv_dead_channel_file_x = calib.CalibFileName("GTR-100apvx-status", runID);
//  if(this->ReadFile(gtr_100apv_dead_channel_file_x.c_str(), 0)){ 
//	}
//	else {std::cout << "failed to read 100X APV dead file " << std::endl;
// return false;
//	}
//  std::string gtr_100apv_dead_channel_file_y = calib.CalibFileName("GTR-100apvy-status", runID);
//  if(this->ReadFile(gtr_100apv_dead_channel_file_y.c_str(), 1)){ 
//	}
//    else {
//		std::cout << "failed to read 100y apv dead file " << std::endl;	
//		return false;
//		}
//	return true;
//}
//
//bool E16ANA_GTR200APVDeadChannel::ReadDeadChannelData(const int runID){
//  E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
//  std::string gtr_200apv_dead_channel_file_x = calib.CalibFileName("GTR-200apvx-status", runID);
//  if(this->ReadFile(gtr_200apv_dead_channel_file_x.c_str(), 0)){ 
//	}
//	else {std::cout << "failed to read 200X APV dead file " << std::endl;
// return false;
//	}
//  std::string gtr_200apv_dead_channel_file_y = calib.CalibFileName("GTR-200apvy-status", runID);
//  if(this->ReadFile(gtr_200apv_dead_channel_file_y.c_str(), 1)){ 
//	}
//    else {
//		std::cout << "failed to read 200y apv dead file " << std::endl;	
//		return false;
//		}
//	return true;
//}
//
//bool E16ANA_GTR300APVDeadChannel::ReadDeadChannelData(const int runID){
//  E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
//  std::string gtr_300apv_dead_channel_file_x = calib.CalibFileName("GTR-300apvx-status", runID);
//  if(this->ReadFile(gtr_300apv_dead_channel_file_x.c_str(), 0)){ 
//	}
//	else {std::cout << "failed to read 300X APV dead file " << std::endl;
// return false;
//	}
//  std::string gtr_300apv_dead_channel_file_y = calib.CalibFileName("GTR-300apvy-status", runID);
//  if(this->ReadFile(gtr_300apv_dead_channel_file_y.c_str(), 1)){ 
//	}
//    else {
//		std::cout << "failed to read 300y apv dead file " << std::endl;	
//		return false;
//		}
//	return true;
//}
//
