#include "E16ANA_HBDChannelManager.hh"
#include "E16ANA_HBDConstant.hh"

#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

E16ANA_HBDChannelManager::E16ANA_HBDChannelManager(char *_tablename) :
  tablename(_tablename)
{
  std::ifstream fin(tablename);
  
  if( fin ){
    std::string buf_line;
    for(;;){
      id_pack buf_ch;
      if(fin.eof()) break;
      std::getline(fin, buf_line);

      if(buf_line[0] == '#' || buf_line[0] == '\0') continue;
      
      std::stringstream ss(buf_line);
      ss>>buf_ch.ip>>buf_ch.apv_chip_id>>buf_ch.apv_pad_id>>buf_ch.module_id>>buf_ch.pin_id>>buf_ch.hbd_pad_id;
      //std::cerr<<buf_ch.ip<<" "<<buf_ch.apv_chip_id<<" "<<buf_ch.apv_phys_id<<" "<<buf_ch.module_id<<" "<<buf_ch.pin_id<<" "<<buf_ch.pad_id<<std::endl;
      ch_forward.push_back(buf_ch);
      ch_reverse.push_back(buf_ch);
    }
  }
  else{
    std::cerr<<__func__<<" invalid channel filename"<<std::endl;
  }
  std::sort(ch_forward.begin(), ch_forward.end(), comp_apv_pad_sort);
  std::sort(ch_reverse.begin(), ch_reverse.end(), comp_hbd_pad_sort);
}

E16ANA_HBDChannelManager::~E16ANA_HBDChannelManager()
{
}

void E16ANA_HBDChannelManager::GetTableName(char *_tablename)
{
  sprintf(_tablename, "%s", tablename);
}

void E16ANA_HBDChannelManager::GetAllIPs(std::vector<char *> &ips)
{
  for(auto &i : ch_forward){
    bool flag = false;
    if(ips.size() == 0 ) ips.push_back(i.ip);
    for(auto &j : ips){
      if( std::strcmp(i.ip, j) == 0){
	flag = true;
      }
    }
    if( !flag ){
      ips.push_back(i.ip);
    }
  }
}

bool E16ANA_HBDChannelManager::GetDetectorID(const char *ip, const int apv_chip_id, const int apv_pad_id, int &module_id, int &hbd_pad_id)
{
  module_id = -1;
  hbd_pad_id = -1;

  //if(apv_chip_id < 0 || apv_chip_id > n_apv-1) return false;
  
  std::vector<id_pack>::iterator low, up;
  low = std::lower_bound(ch_forward.begin(), ch_forward.end(), apv_pad_id, comp_apv_pad_search_low_index);
  up =  std::upper_bound(ch_forward.begin(), ch_forward.end(), apv_pad_id, comp_apv_pad_search_up_index);
  
  for(std::vector<id_pack>::iterator it = low; it != up; it++){
    //it->Show();
    if(std::strcmp(it->ip, ip) == 0){
      if(it->apv_chip_id == apv_chip_id){
	if(it->apv_pad_id == apv_pad_id){
	  module_id = it->module_id;
	  hbd_pad_id = it->hbd_pad_id;
	  if( module_id == -1 || hbd_pad_id == -1 ){
	    return false;
	  }
	  return true;
	}
      }
    }
  }

  return false;
}

bool E16ANA_HBDChannelManager::GetCircuitID(const int module_id, const int hbd_pad_id, char *ip, int &apv_chip_id, int &apv_pad_id)
{
  apv_chip_id = -1;
  apv_pad_id = -1;
  sprintf(ip, "0.0.0.0");
  
  if(module_id < 0) return false;
  if(hbd_pad_id < 0 || hbd_pad_id > n_pads-1) return false;
  
  std::vector<id_pack>::iterator low, up;
  low = std::lower_bound(ch_reverse.begin(), ch_reverse.end(), hbd_pad_id, comp_hbd_pad_search_low_index);
  up =  std::upper_bound(ch_reverse.begin(), ch_reverse.end(), hbd_pad_id, comp_hbd_pad_search_up_index);
  
  for(std::vector<id_pack>::iterator it = low; it != up; it++){
    //it->Show();
    if(it->module_id == module_id){
      if(it->hbd_pad_id == hbd_pad_id){
	sprintf(ip, "%s", it->ip);
	apv_chip_id = it->apv_chip_id;
	apv_pad_id = it->apv_pad_id;	
	return true;
      }
    }
  }
  
  return false;
}

int E16ANA_HBDChannelManager::GetModuleID(const char *ip, const int apv_chip_id, const int apv_pad_id)
{
  int module_id, hbd_pad_id;
  this->GetDetectorID(ip, apv_chip_id, apv_pad_id, module_id, hbd_pad_id);

  return module_id;
}

int E16ANA_HBDChannelManager::GetPadID(const char *ip, const int apv_chip_id, const int apv_pad_id)
{
  int module_id, hbd_pad_id;
  this->GetDetectorID(ip, apv_chip_id, apv_pad_id, module_id, hbd_pad_id);

  return hbd_pad_id;
}

void E16ANA_HBDChannelManager::GetIPAddress(const int module_id, const int hbd_pad_id, char *ip)
{
  int apv_chip_id, apv_pad_id;
  this->GetCircuitID(module_id, hbd_pad_id, ip, apv_chip_id, apv_pad_id);
}

int E16ANA_HBDChannelManager::GetChipID(const int module_id, const int hbd_pad_id)
{
  char *ip = new char;
  int apv_chip_id, apv_pad_id;
  this->GetCircuitID(module_id, hbd_pad_id, ip, apv_chip_id, apv_pad_id);
  delete ip;

  return apv_chip_id;
}

int E16ANA_HBDChannelManager::GetAPVPadID(const int module_id, const int hbd_pad_id)
{
  char *ip = new char;
  int apv_chip_id, apv_pad_id;
  this->GetCircuitID(module_id, hbd_pad_id, ip, apv_chip_id, apv_pad_id);
  delete ip;
  
  return apv_pad_id;
}

void E16ANA_HBDChannelManager::GetTriggerTileIDWithThresholdFile(const char *mid_gemid, const int asdid, int &mid, int &tileid)
{
  mid = -1;
  tileid = -1;
  int gemid = -1;
  if(std::strcmp(mid_gemid, "R1_1")==0){  mid = 104; gemid = 11;}
  if(std::strcmp(mid_gemid, "R1_2")==0){  mid = 104; gemid = 10;}
  if(std::strcmp(mid_gemid, "R1_3")==0){  mid = 104; gemid =  1;}
  if(std::strcmp(mid_gemid, "R1_4")==0){  mid = 104; gemid =  0;}
  if(std::strcmp(mid_gemid, "R2_1")==0){  mid = 103; gemid = 11;}
  if(std::strcmp(mid_gemid, "R2_2")==0){  mid = 103; gemid = 10;}
  if(std::strcmp(mid_gemid, "R2_3")==0){  mid = 103; gemid =  1;}
  if(std::strcmp(mid_gemid, "R2_4")==0){  mid = 103; gemid =  0;}
  if(std::strcmp(mid_gemid, "R3_1")==0){  mid = 102; gemid = 11;}
  if(std::strcmp(mid_gemid, "R3_2")==0){  mid = 102; gemid = 10;}
  if(std::strcmp(mid_gemid, "R3_3")==0){  mid = 102; gemid =  1;}
  if(std::strcmp(mid_gemid, "R3_4")==0){  mid = 102; gemid =  0;}
  if(std::strcmp(mid_gemid, "R4_1")==0){  mid = 101; gemid = 11;}
  if(std::strcmp(mid_gemid, "R4_2")==0){  mid = 101; gemid = 10;}
  if(std::strcmp(mid_gemid, "R4_3")==0){  mid = 101; gemid =  1;}
  if(std::strcmp(mid_gemid, "R4_4")==0){  mid = 101; gemid =  0;}
  
  if(std::strcmp(mid_gemid, "L1_1")==0){  mid = 106; gemid = 10;}
  if(std::strcmp(mid_gemid, "L1_2")==0){  mid = 106; gemid = 11;}
  if(std::strcmp(mid_gemid, "L1_3")==0){  mid = 106; gemid =  0;}
  if(std::strcmp(mid_gemid, "L1_4")==0){  mid = 106; gemid =  1;}
  if(std::strcmp(mid_gemid, "L2_1")==0){  mid = 107; gemid = 10;}
  if(std::strcmp(mid_gemid, "L2_2")==0){  mid = 107; gemid = 11;}
  if(std::strcmp(mid_gemid, "L2_3")==0){  mid = 107; gemid =  0;}
  if(std::strcmp(mid_gemid, "L2_4")==0){  mid = 107; gemid =  1;}
  if(std::strcmp(mid_gemid, "L3_1")==0){  mid = 108; gemid = 10;}
  if(std::strcmp(mid_gemid, "L3_2")==0){  mid = 108; gemid = 11;}
  if(std::strcmp(mid_gemid, "L3_3")==0){  mid = 108; gemid =  0;}
  if(std::strcmp(mid_gemid, "L3_4")==0){  mid = 108; gemid =  1;}
  if(std::strcmp(mid_gemid, "L4_1")==0){  mid = 109; gemid = 10;}
  if(std::strcmp(mid_gemid, "L4_2")==0){  mid = 109; gemid = 11;}
  if(std::strcmp(mid_gemid, "L4_3")==0){  mid = 109; gemid =  0;}
  if(std::strcmp(mid_gemid, "L4_4")==0){  mid = 109; gemid =  1;}
  
  if(gemid == 0){
    if(asdid == 1) tileid = 20;
    if(asdid == 2) tileid = 10;
    if(asdid == 3) tileid =  0;
    if(asdid == 4) tileid = 21;
    if(asdid == 5) tileid = 11;
    if(asdid == 6) tileid =  1;
    if(asdid == 7) tileid =  2;
    if(asdid == 8) tileid = 12;
    if(asdid == 9) tileid = 22;
  }
  if(gemid == 1){
    if(asdid == 1) tileid = 23;
    if(asdid == 2) tileid = 13;
    if(asdid == 3) tileid =  3;
    if(asdid == 4) tileid = 24;
    if(asdid == 5) tileid = 14;
    if(asdid == 6) tileid =  4;
    if(asdid == 7) tileid =  5;
    if(asdid == 8) tileid = 15;
    if(asdid == 9) tileid = 25;
  }
  if(gemid == 10){
    if(asdid == 1) tileid = 32;
    if(asdid == 2) tileid = 42;
    if(asdid == 3) tileid = 52;
    if(asdid == 4) tileid = 31;
    if(asdid == 5) tileid = 41;
    if(asdid == 6) tileid = 51;
    if(asdid == 7) tileid = 50;
    if(asdid == 8) tileid = 40;
    if(asdid == 9) tileid = 30;
  }
  if(gemid == 11){
    if(asdid == 1) tileid = 35;
    if(asdid == 2) tileid = 45;
    if(asdid == 3) tileid = 55;
    if(asdid == 4) tileid = 34;
    if(asdid == 5) tileid = 44;
    if(asdid == 6) tileid = 54;
    if(asdid == 7) tileid = 53;
    if(asdid == 8) tileid = 43;
    if(asdid == 9) tileid = 33;
  }
}

bool E16ANA_HBDChannelManager::GetNeighboringPadID(const int hbd_pad_id, std::vector<int> &neighboring_id)
{
  neighboring_id.resize(0);
  
  std::vector<int> candidate_id;
  if( hbd_pad_id == 640 ){                      candidate_id.assign({-40, -20, +20, +40, +60}); goto end;}
  else if( 641 <= hbd_pad_id && hbd_pad_id <= 659){ candidate_id.assign({-40, -21, -20, +19, +20, +40, +60}); goto end;}
  else if( 660 <= hbd_pad_id && hbd_pad_id <= 678){ candidate_id.assign({-40, -20, -19, +20, +21, +40, +41, +60}); goto end;}
  else if( hbd_pad_id == 679 ){                 candidate_id.assign({-40, -20, +20, +40, +60}); goto end;}
  else if( hbd_pad_id == 680 ){                 candidate_id.assign({-40, -20, +20, +40, +60}); goto end;}
  else if( 681 <= hbd_pad_id && hbd_pad_id <= 699){ candidate_id.assign({-40, -21, -20, +20, +39, +40, +60}); goto end;}
  else if( hbd_pad_id == 700 ){                 candidate_id.assign({-60, -40, -20, +20, +40}); goto end;}
  else if( 701 <= hbd_pad_id && hbd_pad_id <= 719){ candidate_id.assign({-60, -41, -40, -20, +19, +20, +40}); goto end;}
  else if( hbd_pad_id == 719 ){                 candidate_id.assign({-60, -41, -40, -20, +19, +20, +40}); goto end;}
  else if( 720 <= hbd_pad_id && hbd_pad_id <= 738){ candidate_id.assign({-60, -40, -39, -20, -19, +20, +21, +40}); goto end;}
  else if( hbd_pad_id == 739 ){                 candidate_id.assign({-60, -40, -20, +20, +40}); goto end;}
  else if( hbd_pad_id == 740 ){                 candidate_id.assign({-60, -40, -20, +20, +40}); goto end;}
  else if( 741 <= hbd_pad_id && hbd_pad_id <= 759){ candidate_id.assign({-60, -40, -21, -20, +19, +20, +40}); goto end;}
  
  if( 0<=hbd_pad_id && hbd_pad_id<=699){//lower pads
    if(hbd_pad_id%40 == 0 || hbd_pad_id%40 == 39){//right and left edge pads
      candidate_id.assign({-40, -20, +20, +40}); goto end;
    }
    if( (hbd_pad_id/20)%2 == 0 ){
      candidate_id.assign({-40, -21, -20, +19, +20, +40}); goto end;
    }
    else if( (hbd_pad_id/20)%2 == 1 ){
      candidate_id.assign({-40, -20, -19, +20, +21, +40}); goto end;
    }
  }
  else if( 700<=hbd_pad_id && hbd_pad_id<=1399 ){//upper pads
    if(hbd_pad_id%40 == 20 || hbd_pad_id%40 == 19){//right and left edge pads
      candidate_id.assign({-40, -20, +20, +40}); goto end;
    }
    if( (hbd_pad_id/20)%2 == 0 ){
      candidate_id.assign({-40, -20, -19, +20, +21, +40}); goto end;
    }
    else if( (hbd_pad_id/20)%2 == 1 ){
      candidate_id.assign({-40, -21, -20, +19, +20, +40}); goto end;
    }
  }

 end:;
  for(auto &e : candidate_id){
    if( 0 <= (hbd_pad_id + e) && (hbd_pad_id + e) < n_pads ) neighboring_id.push_back(hbd_pad_id + e);
  }
  
  return neighboring_id.size() != 0 ? true : false;
}

bool E16ANA_HBDChannelManager::IsValidModuleID(const int module_id)
{
  std::vector<int> v(std::begin(HBD_Module_Constant::module_ids),
		     std::end(HBD_Module_Constant::module_ids));
  
  auto module_exist = std::find(v.begin(), v.end(), module_id);
  if(module_exist == v.end()){
    //not found
    return false;
  }else{
    //found
    return true;
  }
}

bool E16ANA_HBDChannelManager::IsValidPadID(const int pad_id)
{
  if(0 <= pad_id && pad_id < n_pads){
    //found
    return true;
  }
  else{
    //not found
    return false;
  }
}

bool E16ANA_HBDChannelManager::IsValidTileID(const int tile_id)
{
  int kid = ConvTIDE16ToK(tile_id);
  if(0 <= kid && kid < n_tiles){
    //found
    return true;
  }
  else{
    //not found
    return false;
  }
}

bool E16ANA_HBDChannelManager::IsValidID(const int module_id, const int pad_id)
{
  if(IsValidModuleID(module_id)){
    if(IsValidPadID(pad_id)){
      return true;
    }
  }
  return false;
}

int E16ANA_HBDChannelManager::ConvMIDE16ToK(const int module_id)
{//101, 102, 103, ... to 0, 1, 2, for making arrays
  int index = -1;
  std::vector<int> v(std::begin(HBD_Module_Constant::module_ids),
		     std::end(HBD_Module_Constant::module_ids));
  
  auto module_exist = std::find(v.begin(), v.end(), module_id);
  if(module_exist != v.end()){
    //found
    index = std::distance(v.begin(), module_exist);
  }
  return index;
}

int E16ANA_HBDChannelManager::ConvMIDKToE16(const int module_id)
{
  int index = -1;
  if(0 <= module_id && module_id < sizeof(HBD_Module_Constant::module_ids)/sizeof(int)){
    index = HBD_Module_Constant::module_ids[module_id];
  }
  return index;
}

int E16ANA_HBDChannelManager::ConvTIDE16ToK(const int tid){
  int kid = tid%10+(tid/10)*6;
  return kid;
}

int E16ANA_HBDChannelManager::ConvTIDKToE16(const int kid){
  int tid = kid%6+(kid/6)*10;
  return tid;
}

inline bool E16ANA_HBDChannelManager::comp_hbd_pad_sort(const id_pack& left, const id_pack& right)
{
  return left.hbd_pad_id < right.hbd_pad_id;
}

inline bool E16ANA_HBDChannelManager::comp_apv_pad_sort(const id_pack& left, const id_pack& right)
{
  return left.apv_pad_id < right.apv_pad_id;
}

inline bool E16ANA_HBDChannelManager::comp_hbd_pad_search_low_index(const id_pack& obj, const int& key)
{
  return obj.hbd_pad_id < key;
}

inline bool E16ANA_HBDChannelManager::comp_hbd_pad_search_up_index(const int &key, const id_pack& obj)
{
  return key < obj.hbd_pad_id;
}

inline bool E16ANA_HBDChannelManager::comp_apv_pad_search_low_index(const id_pack& obj, const int& key)
{
  return obj.apv_pad_id < key;
}

inline bool E16ANA_HBDChannelManager::comp_apv_pad_search_up_index(const int& key, const id_pack& obj)
{
  return key < obj.apv_pad_id;
}
