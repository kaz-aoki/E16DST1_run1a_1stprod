#include "HBD_ChannelManager.hh"

#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

HBD_ChannelManager::HBD_ChannelManager(const std::string &_tablename) :
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

HBD_ChannelManager::~HBD_ChannelManager()
{
}

const char* HBD_ChannelManager::GetTableName() const
{
  return tablename.data();
}

void HBD_ChannelManager::GetAllIPs(std::vector<char *> &ips) const
{
  for(const auto &i : ch_forward){
    bool flag = false;
    if(ips.size() == 0 ) ips.push_back(const_cast<char*>(i.ip));
    for(auto &j : ips){
      if( std::strcmp(i.ip, j) == 0){
	flag = true;
      }
    }
    if( !flag ){
      ips.push_back(const_cast<char*>(i.ip));
    }
  }
}

bool HBD_ChannelManager::GetDetectorID(const char *ip, const int apv_chip_id, const int apv_pad_id, int &module_id, int &hbd_pad_id) const
{
  module_id = -1;
  hbd_pad_id = -1;

  //if(apv_chip_id < 0 || apv_chip_id > n_apv-1) return false;
  
  std::vector<id_pack>::const_iterator low, up;
  low = std::lower_bound(ch_forward.cbegin(), ch_forward.cend(), apv_pad_id, comp_apv_pad_search_low_index);
  up =  std::upper_bound(ch_forward.cbegin(), ch_forward.cend(), apv_pad_id, comp_apv_pad_search_up_index);
  
  for(std::vector<id_pack>::const_iterator it = low; it != up; it++){
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

bool HBD_ChannelManager::GetCircuitID(const int module_id, const int hbd_pad_id, char *ip, int &apv_chip_id, int &apv_pad_id) const
{
  apv_chip_id = -1;
  apv_pad_id = -1;
  sprintf(ip, "0.0.0.0");
  
  if(module_id < 0) return false;
  if(hbd_pad_id < 0 || hbd_pad_id > n_pad-1) return false;
  
  std::vector<id_pack>::const_iterator low, up;
  low = std::lower_bound(ch_reverse.cbegin(), ch_reverse.cend(), hbd_pad_id, comp_hbd_pad_search_low_index);
  up =  std::upper_bound(ch_reverse.cbegin(), ch_reverse.cend(), hbd_pad_id, comp_hbd_pad_search_up_index);
  
  for(std::vector<id_pack>::const_iterator it = low; it != up; it++){
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

int HBD_ChannelManager::GetModuleID(const char *ip, const int apv_chip_id, const int apv_pad_id) const
{
  int module_id, hbd_pad_id;
  this->GetDetectorID(ip, apv_chip_id, apv_pad_id, module_id, hbd_pad_id);

  return module_id;
}

int HBD_ChannelManager::GetPadID(const char *ip, const int apv_chip_id, const int apv_pad_id) const
{
  int module_id, hbd_pad_id;
  this->GetDetectorID(ip, apv_chip_id, apv_pad_id, module_id, hbd_pad_id);

  return hbd_pad_id;
}

void HBD_ChannelManager::GetIPAddress(const int module_id, const int hbd_pad_id, char *ip) const
{
  int apv_chip_id, apv_pad_id;
  this->GetCircuitID(module_id, hbd_pad_id, ip, apv_chip_id, apv_pad_id);
}

int HBD_ChannelManager::GetChipID(const int module_id, const int hbd_pad_id) const
{
  char *ip = new char;
  int apv_chip_id, apv_pad_id;
  this->GetCircuitID(module_id, hbd_pad_id, ip, apv_chip_id, apv_pad_id);
  delete ip;

  return apv_chip_id;
}

int HBD_ChannelManager::GetAPVPadID(const int module_id, const int hbd_pad_id) const
{
  char *ip = new char;
  int apv_chip_id, apv_pad_id;
  this->GetCircuitID(module_id, hbd_pad_id, ip, apv_chip_id, apv_pad_id);
  delete ip;
  
  return apv_pad_id;
}

bool HBD_ChannelManager::GetNeighboringPadID(const int hbd_pad_id, std::vector<int> &neighboring_id) 
{
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
    if( 0 <= (hbd_pad_id + e) && (hbd_pad_id + e) < n_pad ) neighboring_id.push_back(hbd_pad_id + e);
  }
  
  return neighboring_id.size() != 0 ? true : false;
}

inline bool HBD_ChannelManager::comp_hbd_pad_sort(const id_pack& left, const id_pack& right)
{
  return left.hbd_pad_id < right.hbd_pad_id;
}

inline bool HBD_ChannelManager::comp_apv_pad_sort(const id_pack& left, const id_pack& right)
{
  return left.apv_pad_id < right.apv_pad_id;
}

inline bool HBD_ChannelManager::comp_hbd_pad_search_low_index(const id_pack& obj, const int& key)
{
  return obj.hbd_pad_id < key;
}

inline bool HBD_ChannelManager::comp_hbd_pad_search_up_index(const int &key, const id_pack& obj)
{
  return key < obj.hbd_pad_id;
}

inline bool HBD_ChannelManager::comp_apv_pad_search_low_index(const id_pack& obj, const int& key)
{
  return obj.apv_pad_id < key;
}

inline bool HBD_ChannelManager::comp_apv_pad_search_up_index(const int& key, const id_pack& obj)
{
  return key < obj.apv_pad_id;
}
