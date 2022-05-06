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

int E16ANA_GTRChannelManager::ConvLocalXToGEMch(const int n_gem_strip_x, const double lx_mm){
	int gem_ch = -1;
	if(n_gem_strip_x == 1){//100GEM
		gem_ch = 0;
	}
	else if(n_gem_strip_x == 4){//200GEM
		double conv_lx = lx_mm + 100;
		gem_ch = conv_lx/50;
	}
	else if(n_gem_strip_x == 12){//300GEM
		double conv_lx = lx_mm + 150;
		gem_ch  = conv_lx/25; 
	}
	return gem_ch;
}

int E16ANA_GTRChannelManager::ConvLocalYToGEMch(const int n_gem_strip_y, const double ly_mm){
	int gem_ch = -1;
	if(n_gem_strip_y == 1){//100GEM
		gem_ch = 0;
	}
	else if(n_gem_strip_y == 4){//200GEM
		double conv_ly = ly_mm + 100;
		gem_ch = conv_ly/50;
	}
	else if(n_gem_strip_y == 24){//300GEM
		double conv_ly = ly_mm + 150;
		gem_ch  = conv_ly/12.5; 
	}
	return gem_ch;
}

int E16ANA_GTRChannelManager::ConvLocalXToAPVch(const int gtr_size, const double lx_mm){//
	int n_strips_100 = E16DST_DST1Constant::nstrips_100x;
	int n_strips_200 = E16DST_DST1Constant::nstrips_200x;
	int n_strips_300 = E16DST_DST1Constant::nstrips_300x;
	int n_strips = -1;
	if(gtr_size == 0) {n_strips = n_strips_100;}
	else if(gtr_size == 1) {n_strips = n_strips_200;}
	else if(gtr_size == 2) {n_strips = n_strips_200;}
	else {return -1;}
    int apv_ch = -1;
    if(signbit(lx_mm)){//MINUS
		apv_ch = (n_strips/2 - 1) + (int)lx_mm/E16DST_DST1Constant::gtr_strip_pitch_x;
	}
    else {
		apv_ch = n_strips/2  + (int)lx_mm/E16DST_DST1Constant::gtr_strip_pitch_x;
	}
	return apv_ch;
}

int E16ANA_GTRChannelManager::ConvLocalYToAPVch(const int gtr_size, const double ly_mm){//
	int n_strips_100 = E16DST_DST1Constant::nstrips_100y;
	int n_strips_200 = E16DST_DST1Constant::nstrips_200y;
	int n_strips_300 = E16DST_DST1Constant::nstrips_300y;
	int n_strips = -1;
	if(gtr_size == 0) {n_strips = n_strips_100;}
	else if(gtr_size == 1) {n_strips = n_strips_200;}
	else if(gtr_size == 2) {n_strips = n_strips_200;}
	else {return -1;}
    int apv_ch = -1;
    if(signbit(ly_mm)){//MINUS
		apv_ch = (n_strips/2 - 1) + (int)ly_mm/E16DST_DST1Constant::gtr_strip_pitch_y;
	}
    else {
		apv_ch = n_strips/2  + (int)ly_mm/E16DST_DST1Constant::gtr_strip_pitch_y;
	}
	return apv_ch;
}
