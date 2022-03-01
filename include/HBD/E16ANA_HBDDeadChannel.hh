#ifndef E16ANA_HBDDeadChannel_h
#define E16ANA_HBDDeadChannel_h

#include "E16DST_DST0.hh"
#include "E16ANA_HBDConstant.hh"

#include <vector>

class E16ANA_HBDDeadChannel {
  
public:
  E16ANA_HBDDeadChannel();
  ~E16ANA_HBDDeadChannel();
  bool ReadFile(const char* filename);
  bool ReadDeadChannelData(const int runID);
  bool IsOK(const int module_id, const int pad_id);
  bool IsDead(const int module_id, const int pad_id);
  bool IsNoisy(const int module_id, const int pad_id);
  bool IsHot(const int module_id, const int pad_id);
  int Status(const int module_id, const int pad_id);
  void GetOKChannels(const int module_id, std::vector<int> &ok_chs);
  
  bool IsOKTile(const int module_id, const int tile_id);
  bool IsDeadTile(const int module_id, const int tile_id);
  bool IsNoisyTile(const int module_id, const int tile_id);
  bool IsHotTile(const int module_id, const int tile_id);
  int StatusTile(const int module_id, const int tile_id);
  void GetOKChannelsTile(const int module_id, std::vector<int> &ok_chs);
  
  int GetOKFlag(){return ok_flag;};
  int GetDeadFlag(){return dead_flag;};
  int GetNoisyFlag(){return noisy_flag;};
  int GetHotFlag(){return hot_flag;};
  
private:
  enum {
    n_modules = E16DST_Constant::NModules,
    n_pads = HBD_Module_Constant::n_pads,
    n_tiles = HBD_Module_Constant::n_tiles,
    ok_flag = 0,
    dead_flag = 1,
    noisy_flag = 2,
    hot_flag = 3
  };
  
  int status[n_modules][n_pads];
  int status_tile[n_modules][n_tiles];
  void Init();
 
};

#endif // E16ANA_HBDDeadChannel_h
