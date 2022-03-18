#ifndef E16ANA_HBDChannelManager_h
#define E16ANA_HBDChannelManager_h

#include <iostream>
#include <vector>

#include "E16ANA_HBDConstant.hh"

class E16ANA_HBDChannelManager {
  
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
  
  E16ANA_HBDChannelManager(char *_tablename);
  ~E16ANA_HBDChannelManager();
  void GetTableName(char *_tablename);
  void GetAllIPs(std::vector<char *> &ips);
  bool GetDetectorID(const char *ip, const int apv_chip_id, const int apv_phys_id, int &module_id, int &pad_id);
  bool GetCircuitID(const int module_id, const int pad_id, char *ip, int &apv_chip_id, int &apv_phys_id);
  int GetPadID(const char *ip, const int apv_chip_id, const int apv_phys_id);
  int GetModuleID(const char *ip, const int apv_chip_id, const int apv_phys_id);
  void GetIPAddress(const int module_id, const int pad_id, char *ip);
  int GetChipID(const int module_id, const int pad_id);
  int GetAPVPadID(const int module_id, const int pad_id);
  static bool GetNeighboringPadID(const int pad_id, std::vector<int> &neighboring_id);
  static bool IsValidModuleID(const int module_id);
  static bool IsValidPadID(const int pad_id);
  static bool IsValidTileID(const int tile_id);
  static bool IsValidID(const int module_id, const int pad_id);
  static int ConvMIDE16ToK(const int module_id);
  static int ConvMIDKToE16(const int module_id);
  static int ConvTIDE16ToK(const int tile_id);
  static int ConvTIDKToE16(const int tile_id);
  
  static bool comp_hbd_pad_sort(const id_pack& left, const id_pack& right);
  static bool comp_apv_pad_sort(const id_pack& left, const id_pack& right);
  static bool comp_hbd_pad_search_low_index(const id_pack& obj, const int& key);
  static bool comp_hbd_pad_search_up_index(const int &key, const id_pack& obj);
  static bool comp_apv_pad_search_low_index(const id_pack& obj, const int& key);
  static bool comp_apv_pad_search_up_index(const int& key, const id_pack& obj);
  
 private:
  enum {
    n_pads = HBD_Module_Constant::n_pads,
    n_tiles = HBD_Module_Constant::n_tiles
  };
  char *tablename;
  std::vector<id_pack> ch_forward;// for conversion of circuit ID to detector ID
  std::vector<id_pack> ch_reverse;// for conversion of detector ID to circuit ID
};

#endif // E16ANA_HBDChannelManager_h
