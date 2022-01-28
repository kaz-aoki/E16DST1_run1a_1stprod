#ifndef E16ANA_GTRChannelStatus_h
#define E16ANA_GTRChannelStatus_h

#include "E16DST_DST0.hh"
//#include "E16ANA_GTRConstant.hh"

#include <vector>

class E16ANA_GTRChannelStatus {
  
public:
  E16ANA_GTRChannelStatus();
  ~E16ANA_GTRChannelStatus();
  //  bool ReadFile(const char* filename);
  //  bool ReadChannelStatusData(const int runID);
  void ReadASDChannelStatusData();
  bool IsASDOK(const int module_id, const int ch);
  bool IsASDDead(const int module_id, const int ch);
//  bool IsASDNoisy(const int module_id, const int ch);
//  bool IsASDHot(const int module_id, const int ch);
  int ASDStatus(const int module_id, const int ch);
  //  void GetOKChannels(const int module_id, std::vector<int> &ok_chs);
  
private:
  enum {
    //n_modules = E16DST_Constant::NModules,
    //n_chs = E16ANA_GTRConstant::n_chs,
    n_modules = 10,
    n_asd_chs = 24,
    ok_flag = 0,
    dead_flag = 1,
    noisy_flag = 2,
    hot_flag = 3
  };
  int asd_status[n_modules][n_asd_chs];
  void Init();
 
};

#endif // E16ANA_GTRChannelStatus_h
