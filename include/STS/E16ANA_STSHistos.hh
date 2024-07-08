#ifndef E16ANA_STSHISTOS_HH_
#define E16ANA_STSHISTOS_HH_

#include <vector>
#include <map>

#include "TH1D.h"

class E16ANA_STSHistos{
public:
  E16ANA_STSHistos();
  TH1* get(int mod, int ipn,const std::string& name);
  void clear_counters() {
    if ( counter_map.size()>0 ) {
      for( auto& iter : counter_map ) {
	iter.second = 0;
      }
    }
  }
  int get_count(int mod,int ipn,const std::string& name);
  void set_count(int mod,int ipn,const std::string& name,int var);
  void inc_count(int mod,int ipn,const std::string& name);
  
  void create();
  void fill_counters();

  using stsindex = std::tuple<int,int,std::string>;

  std::map<stsindex,TH1D*> hist_map;
  std::map<stsindex,int> counter_map;

  std::vector<int> modules;
  std::vector<int> pn;
  std::vector<std::string> pn_str;

};


#endif
