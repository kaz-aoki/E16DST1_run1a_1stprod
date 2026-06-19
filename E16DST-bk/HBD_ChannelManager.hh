#ifndef HBD_ChannelManager_h
#define HBD_ChannelManager_h

#include <iostream>
#include <string>
#include <vector>

#include "E16DST_Constant.hh"
//#include "unpacker/srs-atca/SRS_ATCASpec.h"

class HBD_ChannelManager {
  
 public:
  struct id_pack{
    char ip[16];
    int apv_chip_id;
    int apv_pad_id;
    int module_id;
    int pin_id;
    int hbd_pad_id;
    void Show(){std::cerr<<ip<<" "<<apv_chip_id<<" "<<apv_pad_id<<" "<<	\
	module_id<<" "<<pin_id<<" "<<hbd_pad_id<<std::endl;};
  };
  
  HBD_ChannelManager(const std::string &_tablename);
  ~HBD_ChannelManager();
  const char* GetTableName() const;
  void GetAllIPs(std::vector<char *> &ips) const;
  bool GetDetectorID(const char *ip, const int apv_chip_id, const int apv_phys_id, int &module_id, int &pad_id) const;
  bool GetCircuitID(const int module_id, const int pad_id, char *ip, int &apv_chip_id, int &apv_phys_id) const;
  int GetPadID(const char *ip, const int apv_chip_id, const int apv_phys_id) const;
  int GetModuleID(const char *ip, const int apv_chip_id, const int apv_phys_id) const;
  void GetIPAddress(const int module_id, const int pad_id, char *ip) const;
  int GetChipID(const int module_id, const int pad_id) const;
  int GetAPVPadID(const int module_id, const int pad_id) const;
  static bool GetNeighboringPadID(const int pad_id, std::vector<int> &neighboring_id);
  
  static bool comp_hbd_pad_sort(const id_pack& left, const id_pack& right);
  static bool comp_apv_pad_sort(const id_pack& left, const id_pack& right);
  static bool comp_hbd_pad_search_low_index(const id_pack& obj, const int& key);
  static bool comp_hbd_pad_search_up_index(const int &key, const id_pack& obj);
  static bool comp_apv_pad_search_low_index(const id_pack& obj, const int& key);
  static bool comp_apv_pad_search_up_index(const int& key, const id_pack& obj);
  
 private:
  enum {
    //n_apv = srs_atca::NofApv,
    //n_apv_ch = srs_atca::NofChPerApv,
    n_sample = E16DST_Constant::NSamplesHBD,
    n_pad = E16DST_Constant::NPadsHBD
  };
  std::string tablename;
  std::vector<id_pack> ch_forward;// for conversion of circuit ID to detector ID
  std::vector<id_pack> ch_reverse;// for conversion of detector ID to circuit ID
};

#endif // HBD_ChannelManager_h
