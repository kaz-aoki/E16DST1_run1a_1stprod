#ifndef E16DST_LGCHANNELMAP_HH
#define E16DST_LGCHANNELMAP_HH

#include <map>
#include <string>
#include <vector>

class E16DST_LGChannelMap {
private:
   std::vector<std::vector<int>> ip_ch_map;
   const static int i_LorR = 0;
   const static int i_deg = 1;
   const static int i_blid = 2;
   const static int i_dst0_module = 3;
   const static int i_dst0_block = 4;
   const static int i_pp = 5;
   const static int i_ch = 6;
   const static int i_trig_id = 7;
   const static int i_HVch = 8;
   const static int i_ip = 9;
   const static int i_vth_type = 10;
   const static int i_wf_type = 11;

   const static int n_ip = 0;
   const static int n_pp = 1;
   const static int n_vth_type = 2;
   const static int n_wf_type = 3;

   std::vector<std::vector<int>> ip_pp_map;
   std::vector<std::vector<int>> ch_map;

   void MakeMap(const std::string &pp_map_file, const std::string &ch_pp_file);

public:
   E16DST_LGChannelMap(const std::string &pp_map_file, const std::string &ch_pp_file);
   ~E16DST_LGChannelMap() = default;
   int GetModule(int ip, int ch) const;
   int GetBlock(int ip, int ch) const;
   int GetHVch(int ip, int ch) const;
   int GetVthType(int ip, int ch) const;
   int GetWfType(int ip, int ch) const;
};

#endif // E16DST_LGCHANNELMAP_HH
