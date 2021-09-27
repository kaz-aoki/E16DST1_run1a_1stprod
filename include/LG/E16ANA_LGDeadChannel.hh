#ifndef E16ANA_LGDeadChannel_h
#define E16ANA_LGDeadChannel_h

#include "E16DST_DST0.hh"
#include "E16ANA_LGConstant.hh"

#include <vector>

class E16ANA_LGDeadChannel {
  
public:
  E16ANA_LGDeadChannel();
  ~E16ANA_LGDeadChannel();
  bool ReadFile(const char* filename);
  //bool ReadDeadChannelData(const int runID);
  bool ReadDeadChannelData();
  bool IsOK(const int module_id, const int block_id);
  bool IsDead(const int module_id, const int block_id);
  bool IsNoisy(const int module_id, const int block_id);
  bool IsHot(const int module_id, const int block_id);
  int Status(const int module_id, const int block_id);
  void GetOKChannels(const int module_id, std::vector<int> &ok_chs);
  
private:
  enum {
    //n_modules = E16DST_Constant::NModules,
    //n_blocks = E16ANA_LGConstant::n_blocks,
    n_modules = 110,
    n_blocks = 60,
    ok_flag = 0,
    dead_flag = 1,
    noisy_flag = 2,
    hot_flag = 3
  };
  int status[n_modules][n_blocks];
  void Init();
 
};

#endif // E16ANA_LGDeadChannel_h
