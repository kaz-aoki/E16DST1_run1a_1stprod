#ifndef E16ANA_GTRChannelManager_h
#define E16ANA_GTRChannelManager_h

#include "E16DST_DST1Constant.hh"

class E16ANA_GTRChannelManager {
public:
	E16ANA_GTRChannelManager();
	~E16ANA_GTRChannelManager();
	static bool IsValidModuleID(const int module_id);	
	static bool IsValidASDID(const int m, const int c);
	static int ConvMIDE16ToK(const int m);
private:
	enum {
		n_ychs = E16DST_DST1Constant::n_gtr_asd_chs
		};

};







#endif 
