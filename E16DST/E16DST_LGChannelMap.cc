#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "E16DST_LGChannelMap.hh"

E16DST_LGChannelMap::E16DST_LGChannelMap(const std::string &pp_map_file, const std::string &ch_pp_file)
{
   MakeMap(pp_map_file, ch_pp_file);
}

void E16DST_LGChannelMap::MakeMap(const std::string &pp_map_file, const std::string &ch_pp_file)
{
   std::ifstream ifs_ip_pp(pp_map_file);
   if (!ifs_ip_pp.good()) {
      std::cerr << "failed to open file: " << pp_map_file << std::endl;
      return;
   }
   // std::vector<std::vector<int>> ip_pp_map;

   while (!ifs_ip_pp.eof()) {
      int ip, pp, vth_type, wf_type;
      ifs_ip_pp >> ip >> pp >> vth_type >> wf_type;
      std::vector<int> pp_map_data;
      pp_map_data.push_back(ip);
      pp_map_data.push_back(pp);
      pp_map_data.push_back(vth_type);
      pp_map_data.push_back(wf_type);
      ip_pp_map.push_back(pp_map_data);
      // std::cout<<"making map  "<<pp<<std::endl;
   }

   std::ifstream ifs_ip_ch(ch_pp_file);
   if (!ifs_ip_ch.good()) {
      std::cerr << "failed to open file: " << ch_pp_file << std::endl;
      return;
   }

   while (!ifs_ip_ch.eof()) {
      std::vector<int> ip_map_data;
      char LorR = 0;
      int deg = 0, blid = 0, dst0_module = 0, dst0_block = 0, pp = 0, ch = 0, trig_id = 0, HV_ch = 0;
      ifs_ip_ch >> LorR >> deg >> blid >> dst0_module >> dst0_block >> pp >> ch >> trig_id >> HV_ch;
      // std::cout<<"ip	"<<deg<<"  blid"<<blid<<" pp "<<pp<<std::endl;

      auto ip_pp_vector = std::find_if(std::begin(ip_pp_map), std::end(ip_pp_map),
                                       [pp](const std::vector<int> &val) { return (val.at(n_pp) == pp); });
      if (!(ip_pp_vector == ip_pp_map.end())) {
         int ip = ip_pp_vector->at(n_ip);
         int vth_type = ip_pp_vector->at(n_vth_type);
         int wf_type = ip_pp_vector->at(n_wf_type);

         ip_map_data.push_back(LorR);        // 0
         ip_map_data.push_back(deg);         // 1
         ip_map_data.push_back(blid);        // 2
         ip_map_data.push_back(dst0_module); // 3
         ip_map_data.push_back(dst0_block);  // 4
         ip_map_data.push_back(pp);          // 5
         ip_map_data.push_back(ch);          // 6
         ip_map_data.push_back(trig_id);     // 7
         ip_map_data.push_back(HV_ch);       // 8
         ip_map_data.push_back(ip);          // 9
         ip_map_data.push_back(vth_type);    // 10
         ip_map_data.push_back(wf_type);     // 11

         ip_ch_map.push_back(ip_map_data);
      }
   }

   //	return ip_ch_map;
}

int E16DST_LGChannelMap::GetModule(int ip, int ch) const
{

   auto selected_ch_vector =
      std::find_if(std::begin(ip_ch_map), std::end(ip_ch_map),
                   [ip, ch](const std::vector<int> &val) { return (val.at(i_ip) == ip && val.at(i_ch) == ch); });

   if (selected_ch_vector->empty()) {
      return -10000;
   }

   int moduleid = selected_ch_vector->at(i_dst0_module);

   return moduleid;
}

int E16DST_LGChannelMap::GetBlock(int ip, int ch) const
{

   auto selected_ch_vector =
      std::find_if(std::begin(ip_ch_map), std::end(ip_ch_map),
                   [ip, ch](const std::vector<int> &val) { return (val.at(i_ip) == ip && val.at(i_ch) == ch); });

   if (selected_ch_vector->empty()) {
      return -10000;
   }

   int blockid = selected_ch_vector->at(i_dst0_block);

   return blockid;
}

int E16DST_LGChannelMap::GetHVch(int ip, int ch) const
{

   auto selected_ch_vector =
      std::find_if(std::begin(ip_ch_map), std::end(ip_ch_map),
                   [ip, ch](const std::vector<int> &val) { return (val.at(i_ip) == ip && val.at(i_ch) == ch); });

   if (selected_ch_vector->empty()) {
      return -10000;
   }

   int HVch = selected_ch_vector->at(i_HVch);

   return HVch;
}

int E16DST_LGChannelMap::GetWfType(int ip, int ch) const
{

   auto selected_ch_vector =
      std::find_if(std::begin(ip_ch_map), std::end(ip_ch_map),
                   [ip, ch](const std::vector<int> &val) { return (val.at(i_ip) == ip && val.at(i_ch) == ch); });

   if (selected_ch_vector->empty()) {
      return -10000;
   }

   int wf_type = selected_ch_vector->at(i_wf_type);

   return wf_type;
}

int E16DST_LGChannelMap::GetVthType(int ip, int ch) const
{

   auto selected_ch_vector =
      std::find_if(std::begin(ip_ch_map), std::end(ip_ch_map),
                   [ip, ch](const std::vector<int> &val) { return (val.at(i_ip) == ip && val.at(i_ch) == ch); });

   if (selected_ch_vector->empty()) {
      return -10000;
   }

   int vth_type = selected_ch_vector->at(i_vth_type);

   return vth_type;
}
