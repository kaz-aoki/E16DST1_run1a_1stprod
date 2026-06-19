#include "E16DST_STSChannelMapManager.hh"
#include <stdexcept>
#include <string>
#include <fstream>
#include <cstring>

E16DST_STSChannelMapManager* E16DST_STSChannelMapManager::instance = nullptr;

using stsman=E16DST_STSChannelMapManager;

stsman* stsman::get_instance(const std::string_view sts_runmap_filename) {
  if ( instance == nullptr ) {
    instance = new stsman(sts_runmap_filename);
  }
  return instance;  
}

E16DST_STSChannelMapManager::E16DST_STSChannelMapManager(const std::string_view sts_runmap) {
  const std::string filename(sts_runmap); // To ensure that it ends with null.
  std::string filepath = filename;
  size_t pos=  filepath.find_last_of('/');
  if ( pos != std::string::npos) {
    filepath.erase(pos);
  }
  std::ifstream in(filename);
  if (! in ) {
    std::cout << "E16DST_STSChannelMapManager: cannot open " << sts_runmap << std::endl;
    throw std::runtime_error("E16DST_STSChannelMapManager: cannot open runmap.");
  }
  char buf[1024];
  while(in.getline(buf,1024) ) {
    if ( buf[0]=='#' ) continue;
    if ( strlen(buf) < 1 ) continue;
    int var1,var2;
    char str[100];
    int result = sscanf(buf,"%d %d %s",&var1,&var2,str);
    if ( result == 3 ) {
      vec_runmap.emplace_back();
      vec_runmap.back().runnumber_from = var1;
      vec_runmap.back().runnumber_to = var2;
      vec_runmap.back().filename = filepath + "/" + str;
      //vec_runmap.back().show();
    }
  }
}

void stsman::set_runnumber(int _runnumber) {
  runnumber = _runnumber;
  auto match_run = [&](auto &el) {
    return ( el.runnumber_from <= runnumber && runnumber <= el.runnumber_to);
  };
  auto iter = std::find_if(vec_runmap.begin(),vec_runmap.end(),match_run);

  if ( iter == vec_runmap.end() ) {
    std::cout << "E16DST_STSChannelMapManager: I don't know run " << runnumber << std::endl;
    return;
  }
  sts_gbt_file = iter->filename;
  std::cout << "E16DST_STSChannelMapManager : gbt_map = " << sts_gbt_file << std::endl;
}
