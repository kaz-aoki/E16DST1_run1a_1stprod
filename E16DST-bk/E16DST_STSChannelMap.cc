#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "E16DST_STSChannelMap.hh"
#include <sstream>
#include <cassert>


E16DST_STSChannelMap::E16DST_STSChannelMap(std::string_view sts_gbt_file, std::string_view sts_elink_file)
{
  MakeMap(sts_gbt_file, sts_elink_file);
}

void E16DST_STSChannelMap::MakeMap(std::string_view sts_gbt_file, std::string_view sts_elink_file)
{
  if ( verbosity > 9 ){
    std::cout << "sts_channel_map diagostics[e16sts][gbt][ig]" << std::endl;
    std::cout << "sts_channel_map[" << sts_channel_map.size() << "][" << sts_channel_map[0].size() << "][" << sts_channel_map[0][0].size()
	      << "]" << std::endl;
  }

  std::ifstream ifs_gbt(std::string(sts_gbt_file).c_str());

  if (!ifs_gbt.good()) {
    std::cerr << "failed to open file: " << sts_gbt_file << std::endl;
    exit(1);
  }
   // std::vector<std::vector<int>> ip_pp_map;
  if ( verbosity > 0 ) {
    std::cout << "Reading " << sts_gbt_file << ". Reading code is not robust. Need update." << std::endl;
  }
  char buf[1024];
   while (!ifs_gbt.eof()) {
     ifs_gbt.getline(buf,1024);
     if ( buf[0] == '#' ) continue;
     int e16sts,gbt,gtype,gi,mod,pn,papb;
     std::stringstream ss(buf);
     if ( verbosity > 9 ) {
       std::cout << "analyzing " << buf << std::endl;
     }
     ss >> e16sts >> gbt >> gtype >> gi >> mod >> pn >> papb;
     auto func_set = [e16sts,gbt,gtype,gi,mod,pn,papb](STSChannel& a){
       a.e16sts = e16sts;
       a.gbt = gbt;
       a.gtype = gi;
       a.mod = mod;
       a.pn = pn;
       a.papb = papb;
       assert(gtype ==0 || gtype==2);
       assert(pn == 0 || pn == 1);
       assert(papb == 0 || papb == 1);
     };
     func_set(sts_channel_map[e16sts][gbt][gi]);
   }


   std::ifstream ifs_elink(std::string(sts_elink_file).c_str());

   if (!ifs_elink.good()) {
     std::cerr << "failed to open file: " << sts_elink_file << std::endl;
     exit(1);
   }
   if ( verbosity > 0 ) {
     std::cout << "Reading " << sts_elink_file << ". Reading code is not robust. Need update." << std::endl;
   }
   while (!ifs_elink.eof()) {
     ifs_elink.getline(buf,1024);
     if ( buf[0] == '#' ) continue;
     int ab,elink,asic;
     std::stringstream ss(buf);
     if ( verbosity > 0 ) {
       std::cout << "Analyzing GENERAL MAP " << buf << std::endl;
     }
     ss >> ab >> elink >> asic;
     assert(ab==0 || ab==1);
     assert(elink>=0 && elink<8);
     assert(asic>=0 && asic<8);
     sts_elink_general_map[ab][elink] = asic;
     if ( verbosity > 9 ) {
       std::cout << "ab=" << ab << " elink=" << elink << "  --> asic=" << asic << std::endl;
     }
   }
}

int E16DST_STSChannelMap::GetModule(int e16sts, int gbt, int elink) const{
  auto& stsc = sts_channel_map[e16sts][gbt][0];
  assert(stsc.gtype == 0 || stsc.gtype == 2);
  if ( elink < 16 ) {
    return stsc.mod;
  }else{
    return sts_channel_map[e16sts][gbt][1].mod;
  }
  std::cerr << "E16DST_STSChannelMap::GetModule() : unexpected happened." << std::endl;
}

int E16DST_STSChannelMap::GetPN(int e16sts, int gbt, int elink) const{
  auto& stsc = sts_channel_map[e16sts][gbt][Getig(e16sts,gbt,elink)];
  return stsc.pn;
}

int E16DST_STSChannelMap::GetAsic(int e16sts, int gbt, int elink) const{
  int ig = Getig(e16sts,gbt,elink);
  auto& stsc = sts_channel_map[e16sts][gbt][ig];
  // papb pn ab
  // 0    0  = 0
  // 0    1  = 1
  // 1    0  = 1
  // 1    1  = 0

  int tmp = stsc.papb + stsc.pn;
  
  
  //std::cout << "Inside get asic tmp = " << tmp << std::endl;
  //std::cout << "looking for " << e16sts << " " << gbt << " " << elink << std::endl;
  if ( tmp == 1 ) {
    // Type B
    //std::cout << "TypeB" << std::endl;
    return GetAsicSub(1,elink);
  }else if ( tmp == 0 || tmp == 2 ) {
    // Type A
    //std::cout << "TypeA" << std::endl;
    return GetAsicSub(0,elink);
  }
  std::cout << "GetAsic(): Cannot get ASIC# ; e16sts=" << e16sts << ", gbt=" << gbt << ", elink=" << elink << std::endl;
  //std::cout << "need work on GetAsic" << std::endl;
  return -1;
}

int E16DST_STSChannelMap::Getig(int e16sts,int gbt, int elink) const{
  if ( elink < 16 ) return 0;
  if ( elink >= 16 ) return 1;

  /*
  if (elink < 8 ) return 0;
  auto& stsc = sts_channel_map[e16sts][gbt][0];
  if (elink < 16 && stsc.gtype == 0 ) return 0;
  if (elink >= 16 && stsc.gtype == 2 ) return 1;
  std::cerr << "E16DST_STSChannelMap::Getig() Unknown ig number." << std::endl;
  exit(1);
  */
}

int E16DST_STSChannelMap::GetAsicSub(int ab, int elink) const {
  assert(elink>=0 && elink<32);
  int reduced_elink = elink % 8; // print output
  int tmp = sts_elink_general_map[ab][reduced_elink];  
  //std::cout << "GetAsicSub : ask for ab=" << ab << ", elink="<<elink << " answer=" << tmp << std::endl;
  return tmp;
}
