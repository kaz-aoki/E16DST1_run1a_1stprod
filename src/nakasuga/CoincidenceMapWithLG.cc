#include "CoincidenceMapWithLG.hh"
#include "E16ANA_HBDChannelManager.hh"

#include <vector>
#include <sstream>
#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>

CoincidenceMapWithLG::CoincidenceMapWithLG(char *_filename) : filename(_filename)
{//coincidence map must be sorted. LG module and LG block

  std::ifstream fin(filename);
  
  if( fin ){
    std::string buf_line;
    for(;;){
      if(fin.eof()) break;
      std::getline(fin, buf_line);
      
      if(buf_line[0] == '#' || buf_line[0] == '\0') continue;
      
      std::stringstream ss(buf_line);
      int hbd, lg;//hbd_module_id*100+hbd_triggertile_id, lg_module_id*100+lg_block_id
      while( ss >> hbd >> lg ){
	std::pair<int, int> p = std::make_pair(hbd, lg);
	coin.push_back(p);
      }
    }
  }
  else{
    std::cerr<<__func__<<" invalid filename"<<std::endl;
  }
}

CoincidenceMapWithLG::~CoincidenceMapWithLG()
{
}

std::vector<int> CoincidenceMapWithLG::GetLGCoincidenceChannelsWithHBD(int hbd_module_id, int hbd_tile_id)
{
  
  std::vector<int> ch;
  
  if(!E16ANA_HBDChannelManager::IsValidModuleID(hbd_module_id)){
    std::cerr<<"invalid module ID"<<std::endl;
    return ch;
  }
  if(!E16ANA_HBDChannelManager::IsValidTileID(hbd_tile_id)){
    std::cerr<<"invalid tile ID"<<std::endl;
    return ch;
  }
  
  auto itr = coin.begin();
  
  for(;;){
    itr = std::find_if(itr, coin.end(), SearchLGCh(hbd_module_id*100+hbd_tile_id));
    if(itr == coin.end()) break;
    ch.push_back((*itr).second);
    itr++;
  }
  
  
  return ch;
}

std::vector<int> CoincidenceMapWithLG::GetHBDCoincidenceChannelsWithLG(int lg_module_id, int lg_block_id)
{
  
  std::vector<int> ch;
  
  if(!E16ANA_HBDChannelManager::IsValidModuleID(lg_module_id)){
    std::cerr<<"invalid module ID"<<std::endl;
    return ch;
  }
  
  auto itr = coin.begin();
  
  for(;;){
    itr = std::find_if(itr, coin.end(), SearchHBDCh(lg_module_id*100+lg_block_id));
    if(itr == coin.end()) break;
    ch.push_back((*itr).first);
    itr++;
  }
  
  return ch;
}
