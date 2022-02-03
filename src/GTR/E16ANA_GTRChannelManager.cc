#include "E16ANA_GTRChannelManager.h"
#include "E16DST_DST1.hh"


#include <vector>

E16ANA_GTRChannelManager::E16ANA_GTRChannelManager() {
}
E16ANA_GTRChannelManager::~E16ANA_GTRChannelManager() {
}


bool E16ANA_GTRChannelManager::IsValidModuleID(const int module_id){
	std::vector<int> v(std::begin(E16DST_DST1Constant::gtr_module_ids), std::end(E16DST_DST1Constant::gtr_module_ids));
	auto module_exist  = std::find(v.begin(), v.end(), module_id);
	if(module_exist == v.end()) { 
		return false;	
	}
	else{
		return true;	
	}
}


bool E16ANA_GTRChannelManager::IsValidASDID(const int module_id, const int ch){
	bool isValidch = false;
	if( -1 < ch && ch < n_ychs) isValidch = true;
	if(IsValidModuleID(module_id)){
		if(isValidch){
			return true;
		}
	}
	return false;
}

int E16ANA_GTRChannelManager::ConvMIDE16ToK(const int module_id){
//conversion 101, 102,  to 0, 1, 
	int index = -1;
	std::vector<int> v(std::begin(E16DST_DST1Constant::gtr_module_ids), std::end(E16DST_DST1Constant::gtr_module_ids));
	auto module_exist  = std::find(v.begin(), v.end(), module_id);
	if(module_exist != v.end()){
		index = std::distance(v.begin(), module_exist);
	}
	return index;
}

