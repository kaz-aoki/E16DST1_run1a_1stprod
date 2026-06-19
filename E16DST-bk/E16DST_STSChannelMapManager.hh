#ifndef E16DST_STSCHANNELMAP_MAN_HH
#define E16DST_STSCHANNELMAP_MAN_HH

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class E16DST_STSRunmapElement{
public:
  int runnumber_from{-1};
  int runnumber_to{-1};
  std::string filename;
  void show() {
    std::cout << runnumber_from << " to " << runnumber_to << " : " << filename << std::endl;
  }
};

class E16DST_STSChannelMapManager{
public:
  void set_runnumber(int _runnumber);
  
  std::string get_sts_gbt_file()   const { return sts_gbt_file; }
  std::string get_sts_elink_file() const { return sts_elink_file; }
  int get_runnumber() const { return runnumber; }

  static E16DST_STSChannelMapManager* get_instance(const std::string_view sts_runmap_filename);
  
 private:
  E16DST_STSChannelMapManager(std::string_view sts_runmap_filename);
  std::string sts_gbt_file;
  std::string sts_elink_file;
  std::string sts_runmap_filename;

  std::vector<E16DST_STSRunmapElement> vec_runmap;
  
  int runnumber{-1};
  static E16DST_STSChannelMapManager *instance;
};


#endif

