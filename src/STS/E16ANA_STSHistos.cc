#include "STS/E16ANA_STSHistos.hh"
#include <cassert>
#include <iostream>

E16ANA_STSHistos::E16ANA_STSHistos():modules{101,102,103,104,106,107,108,109,207},pn{0,1},pn_str{"P","N"}{
}

void E16ANA_STSHistos::create(){
  assert( modules.size() > 0 && pn.size() > 0 );
  for ( auto mod : modules ) {
    for ( auto ipn : pn ) {
      TString str;
      std::string name;

      /////// histo multiplicity
      name = "multiplicity";
      auto ind = stsindex(mod,ipn,name);
      str.Form("%s_%d%s",name.c_str(),mod,pn_str[ipn].c_str());
      hist_map[ind] = new TH1D(str,str,100,0,100);
      counter_map[ind] = 0;
    }
  }
}

TH1* E16ANA_STSHistos::get(int mod, int ipn,const std::string& name){
  try{
    auto ind = stsindex(mod,ipn,name);
    return hist_map.at(ind);
  }catch(...){
    std::cout << "cannot find histos" << std::endl;
    return nullptr;
  }
}

int E16ANA_STSHistos::get_count(int mod, int ipn, const std::string& name){
  try{
    auto ind = stsindex(mod,ipn,name);
    return counter_map.at(ind);
  }catch(...){
    std::cout << "get_count: unknwon counter." << std::endl;
    return 0;
  }
}

void E16ANA_STSHistos::set_count(int mod,int ipn, const std::string& name,int var){
  try{
    auto ind = stsindex(mod,ipn,name);
    counter_map.at(ind) = var;
  }catch(...){
    std::cout << "set_count: unknown counter." << std::endl;
  }
}

void E16ANA_STSHistos::inc_count(int mod,int ipn, const std::string& name){
  try{
    auto ind = stsindex(mod,ipn,name);
    counter_map.at(ind)++;
  }catch(...){
    std::cout << "inc_count: unknown counter." << std::endl;
  }
}

void E16ANA_STSHistos::fill_counters() {
  if ( counter_map.size() == 0 ) return;
  for ( auto& counter: counter_map ) {
    try{
      hist_map.at(counter.first)->Fill(counter.second);
    }catch(...){
    }
  }
}
