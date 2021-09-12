#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDTH2Hex.hh"
#include "E16ANA_HBDConstant.hh"

#include "E16DST_Constant.hh"

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <utility>

#include "TVector3.h"

E16ANA_HBDTH2Hex E16ANA_HBDGeometry::h_hexpad_board_normal("normal");
E16ANA_HBDTH2Hex E16ANA_HBDGeometry::h_hexpad_board_rotate("rotated");

E16ANA_HBDGeometry::E16ANA_HBDGeometry()
{
  flag_geometryfile_read = false;
}

E16ANA_HBDGeometry::~E16ANA_HBDGeometry()
{
}

bool E16ANA_HBDGeometry::ReadGeometryFile(char *_geometryfilename){  
  std::ifstream fin(_geometryfilename);
  geometryfilename = _geometryfilename;
  
  if( fin ){
    flag_geometryfile_read = true;
    std::string buf_line;
    for(;;){
      if(fin.eof()) break;
      std::getline(fin, buf_line);

      if(buf_line[0] == '#' || buf_line[0] == '\0') continue;

      std::stringstream ss(buf_line);
      char key[64];
      ss>>key;
      if( std::strcmp(key, "origin_shift:")==0 ){
	int module_id;
	std::vector<double> buf(3);
	ss>>module_id>>buf[0]>>buf[1]>>buf[2];
	std::pair<int, std::vector<double>> p(module_id, buf);
	shift.push_back(p);
      }
      if( std::strcmp(key, "r:")==0 ) ss>>r;
      if( std::strcmp(key, "gap:")==0 ) ss>>gap[0]>>gap[1]>>gap[2];
      if( std::strcmp(key, "angle_xzplane:")==0 ){
	int module_id;
	double buf_angle;
	ss>>module_id>>buf_angle;
	std::pair<int, double> p(module_id, buf_angle/180.*M_PI);
	angle.push_back(p);
      }
    }
    return true;
  }
  else{
    std::cerr<<__func__<<" invalid geometry filename"<<std::endl;
    return false;
  }
}

bool E16ANA_HBDGeometry::CheckIfGeometryFile(){
  return flag_geometryfile_read ? true : false;
}

void E16ANA_HBDGeometry::ShowGeometryParameters(){
  if(CheckIfGeometryFile()){
    std::cerr<<"geometry filename: "<<geometryfilename<<std::endl;
  
    std::cerr<<"shift parameter: module ID xyz [mm]"<<std::endl;
    for(auto p : shift) std::cerr<<p.first<<" "<<p.second.at(0)<<p.second.at(1)<<p.second.at(2)<<std::endl;
    
    std::cerr<<"r: "<<r<<std::endl;
    
    std::cerr<<"gaps: "<<gap[0]<<" "<<gap[1]<<" "<<gap[2]<<std::endl;

    std::cerr<<"angle parameter: module ID radian"<<std::endl;
    for(auto p : angle) std::cerr<<p.first<<" "<<p.second<<std::endl;
  }

  else{
    std::cerr<<"geometry file is not set"<<std::endl;
  }
}

std::vector<double> E16ANA_HBDGeometry::GetGlobalPosition(const int module_id, const double *lpos){//[xy]
  double lx=lpos[0];
  double ly=lpos[1];
  double shift_x, shift_y, shift_z;
  double angle_rad;
  bool flag_shift = false;
  bool flag_angle = false;
  std::vector<double> v(3, 0.);//[global x, y, z]
  
  if(CheckIfGeometryFile()){
    for(auto p : shift){
      if(p.first == module_id){
	shift_x = p.second.at(0);
	shift_y = p.second.at(1);
	shift_z = p.second.at(2);
	flag_shift = true;
      }
    }
    for(auto p : angle){
      if(p.first == module_id){
	angle_rad = p.second;
	flag_angle = true;
      }
    }
    
    if(flag_shift && flag_angle){
      v[0] = shift_x - r*cos(angle_rad) + lx*sin(angle_rad);
      v[1] = shift_y + ly;
      v[2] = shift_z + r*sin(angle_rad) + lx*cos(angle_rad);
    }
  }
  
  return v;
}

int E16ANA_HBDGeometry::GetPadIDWLocalCoordinate(const int module_id, const double *cog)
{
  int pad = -1;
  
  if( E16ANA_HBDGeometry::IsRotated(module_id) ){
    pad = h_hexpad_board_rotate.FindBin(cog[0], cog[1]);
  }else{
    pad = h_hexpad_board_normal.FindBin(cog[0], cog[1]);
  }
  
  return pad;
}

TVector3 E16ANA_HBDGeometry::GetPadLocalCOG(const int module_id, const int pad_id)
{
  double cog[3];
  GetPadLocalCOG(module_id, pad_id, cog);
  TVector3 lpos(cog[0], cog[1], cog[2]);
  return lpos;
}

bool E16ANA_HBDGeometry::GetPadLocalCOG(const int module_id, const int pad_id, double *cog)
{//cog[3]: 0: local x, 1: local y, 2: local z
  int n_pad_x = HBD_Board_Constant::n_pad_x;
  int n_pad_y = HBD_Board_Constant::n_pad_y;
  int n_pad = E16DST_Constant::NPadsHBD;
  double a = HBD_Board_Constant::hex_pad_length;
  
  cog[0] = -10000.;//local x
  cog[1] = -10000.;//local y
  cog[2] = 0.;//local z
  
  std::vector<int> v;
  for(int i=0; i<E16DST_Constant::NModules; i++) v.push_back(HBD_Module_Constant::module_ids[i]);
  
  auto module_exist = std::find(v.begin(), v.end(), module_id);
  if(module_exist == v.end()) return false;
  
  if(pad_id < 0 || n_pad <= pad_id) return false;
  
  //----------------- calc. board coordinate
  int long_cycle = n_pad_x;
  int short_cycle = long_cycle/2;
  
  //------- lower panel
  if(0 <= pad_id && pad_id <= 19){
    cog[0] = (pad_id%short_cycle)*3.*a + (pad_id%long_cycle)/short_cycle*3./2.*a;
    cog[1] = std::sqrt(3.)/2.*a/3.;
  }
  else if(20 <= pad_id && pad_id <= 679){
    cog[0] = (pad_id%short_cycle)*3.*a + (pad_id%long_cycle)/short_cycle*3./2.*a;
    cog[1] = (pad_id/short_cycle)*std::sqrt(3.)/2.*a;
  }
  else if(680 <= pad_id && pad_id <= 699){
    cog[0] = (pad_id%short_cycle)*3.*a + (pad_id%long_cycle)/short_cycle*3./2.*a;
    cog[1] = (pad_id/short_cycle)*std::sqrt(3.)/2.*a - std::sqrt(3.)/2.*a/3.;
  }
  //------- lower panel
  //------- upper panel
  else if(700 <= pad_id && pad_id <= 719){
    cog[0] = ((pad_id-700)%short_cycle)*3.*a + ((pad_id-700)%long_cycle)/short_cycle*3./2.*a;
    cog[1] = std::sqrt(3.)/2.*a/3. + n_pad_y/2*std::sqrt(3.)*a;
  }
  else if(720 <= pad_id && pad_id <= 1379){
    cog[0] = ((pad_id-700)%short_cycle)*3.*a + ((pad_id-700)%long_cycle)/short_cycle*3./2.*a;
    cog[1] = ((pad_id-700)/short_cycle)*std::sqrt(3.)/2.*a + n_pad_y/2*std::sqrt(3.)*a;
  }
  else if(1380 <= pad_id && pad_id <= 1399){
    cog[0] = ((pad_id-700)%short_cycle)*3.*a + ((pad_id-700)%long_cycle)/short_cycle*3./2.*a;
    cog[1] = ((pad_id-700)/short_cycle)*std::sqrt(3.)/2.*a - std::sqrt(3.)/2.*a/3. + n_pad_y/2*std::sqrt(3.)*a;
  }
  //------- upper panel
  //------- right & left column
  if(pad_id%40 == 39 && 0 <= pad_id && pad_id <= 699){
    cog[0] = (pad_id%short_cycle)*3.*a + (pad_id%long_cycle)/short_cycle*3./2.*a - a/6. - 17./66.*a;//17., 66., hajikko no kazuawase
    cog[1] = (pad_id/short_cycle)*std::sqrt(3.)/2.*a;
  }
  if(pad_id%40 == 19 && 700 <= pad_id && pad_id <= 1399){
    cog[0] = ((pad_id-700)%short_cycle)*3.*a + ((pad_id-700)%long_cycle)/short_cycle*3./2.*a - a/6. - 17./66.*a;//17., 66., hajikko no kazuawase
    cog[1] = ((pad_id-700)/short_cycle)*std::sqrt(3.)/2.*a + n_pad_y/2*std::sqrt(3.)*a;
  }
  //------- right & left column
  
  cog[0] += a;
  //----------------- calc. board coordinate
  
  //------- board coordinate to local coordinate
  E16ANA_HBDGeometry::BoardToLocalCoordinate(module_id, cog);
  //------- board coordinate to local coordinate
  
  return true;
}//GetPadLocalCOG()

bool E16ANA_HBDGeometry::BoardToLocalCoordinate(const int module_id, double *b)
{
  std::vector<int> v;
  for(int i=0; i<E16DST_Constant::NModules; i++) v.push_back(HBD_Module_Constant::module_ids[i]);
  
  auto module_exist = std::find(v.begin(), v.end(), module_id);
  if(module_exist == v.end()) return false;
  
  //------- board coordinate to local coordinate
  if( IsRotated(module_id) ){
    b[0] = -b[0] + HBD_Board_Constant::x_board_center;
    b[1] = -b[1] + HBD_Board_Constant::y_board_center;
  }
  else{
    b[0] -= HBD_Board_Constant::x_board_center;
    b[1] -= HBD_Board_Constant::y_board_center;
  }
  //------- board coordinate to local coordinate
  return true;
}

bool E16ANA_HBDGeometry::LocalToBoardCoordinate(const int module_id, double *l)
{
  std::vector<int> v;
  for(int i=0; i<E16DST_Constant::NModules; i++) v.push_back(HBD_Module_Constant::module_ids[i]);
  
  auto module_exist = std::find(v.begin(), v.end(), module_id);
  if(module_exist == v.end()) return false;
  
  //------- local coordinate to board coordinate
  if( IsRotated(module_id) ){
    l[0] = -l[0] + HBD_Board_Constant::x_board_center;
    l[1] = -l[1] + HBD_Board_Constant::y_board_center;
  }
  else{
    l[0] += HBD_Board_Constant::x_board_center;
    l[1] += HBD_Board_Constant::y_board_center;
  }
  //------- local coordinate to board coordinate
  return true;
}


std::vector<int> E16ANA_HBDGeometry::GetTriggerTileAssociatedPadID(const int module_id, int triggertile_id)
{//rough. correct triggertile size should be implemented 
  //triggertile ID: 0, 1, 2, 3, 4, 5, 10, 11, ..., 55
  int n_pad = E16DST_Constant::NPadsHBD;
  std::vector<int> pads;
    
  double x_triggertile_width = (HBD_Board_Constant::x_board_center)/3.;
  double y_triggertile_width = (HBD_Board_Constant::y_board_center)/3.;
  
  double x_triggertile[2] = {triggertile_id%10*x_triggertile_width,
			     (triggertile_id%10+1)*x_triggertile_width};
  double y_triggertile[2] = {triggertile_id/10*y_triggertile_width,
			     (triggertile_id/10+1)*y_triggertile_width};
  for(int i=0; i<2; i++){
    x_triggertile[i] -= HBD_Board_Constant::x_board_center;
    y_triggertile[i] -= HBD_Board_Constant::y_board_center;
  }

  double cog[2];
  if(0 <= triggertile_id/10 && triggertile_id/10 <= 5){
    if( 0 <= triggertile_id%10 && triggertile_id%10 <=5 ){
      for(int i=0; i<n_pad; i++){
	if( GetPadLocalCOG(module_id, i, cog) ){
	  if(x_triggertile[0] <= cog[0] && cog[0] <= x_triggertile[1]){
	    if(y_triggertile[0] <= cog[1] && cog[1] <= y_triggertile[1]){
	      pads.push_back(i);
	    }
	  }
	}
      }
    }
  }
  
  return pads;
}

std::vector<int> E16ANA_HBDGeometry::GetGEMAssociatedTriggerTileID(int GEM_id)
{
  std::vector<int> triggertiles;
  
  if(GEM_id == 0) triggertiles = {0, 1, 2, 10, 11, 12, 20, 21, 22};
  if(GEM_id == 1) triggertiles = {3, 4, 5, 13, 14, 15, 23, 24, 25};
  if(GEM_id == 10) triggertiles = {30, 31, 32, 40, 41, 42, 50, 51, 52};
  if(GEM_id == 11) triggertiles = {33, 34, 35, 43, 44, 45, 53, 54, 55};
  
  double x_GEM_width = (HBD_Board_Constant::x_board_center)/2.;
  double y_GEM_width = (HBD_Board_Constant::y_board_center)/2.;
  
  double x_GEM[2] = {GEM_id%10*x_GEM_width,
		     (GEM_id%10+1)*x_GEM_width};
  double y_GEM[2] = {GEM_id/10*y_GEM_width,
		     (GEM_id/10+1)*y_GEM_width};
  
  return triggertiles;
}

std::vector<int> E16ANA_HBDGeometry::GetGEMAssociatedPadID(int module_id, int GEM_id){
  
  std::vector<int> triggertiles = E16ANA_HBDGeometry::GetGEMAssociatedTriggerTileID(GEM_id);
  std::vector<int> pads;
  
  for(auto t : triggertiles){
    std::vector<int> t_pads = E16ANA_HBDGeometry::GetTriggerTileAssociatedPadID(module_id, t);
    for(auto p : t_pads){
      pads.push_back(p);
    }
  }
  
  return pads;
}

int E16ANA_HBDGeometry::GetTriggerTileAssociatedGEMID(int triggertile_id)
{
  int GEMs;
  
  if((triggertile_id%10 == 0 ||
      triggertile_id%10 == 1 ||
      triggertile_id%10 == 2 ) &&
     triggertile_id/10 <= 2 &&
     0<= triggertile_id && triggertile_id <=55) GEMs = 0;
  
  if((triggertile_id%10 == 3 ||
      triggertile_id%10 == 4 ||
      triggertile_id%10 == 5 ) &&
     triggertile_id/10 <= 2 &&
     0<= triggertile_id && triggertile_id <=55) GEMs = 1;

  if((triggertile_id%10 == 0 ||
      triggertile_id%10 == 1 ||
      triggertile_id%10 == 2 ) &&
     triggertile_id/10 >= 3 &&
     0<= triggertile_id && triggertile_id <=55) GEMs = 10;
  
  if((triggertile_id%10 == 3 ||
      triggertile_id%10 == 4 ||
      triggertile_id%10 == 5 ) &&
     triggertile_id/10 >= 3 &&
     0<= triggertile_id && triggertile_id <=55) GEMs = 11;
  
  return GEMs;
}

 int E16ANA_HBDGeometry::GetPadAssociatedTriggerTileID(const int module_id, const int pad_id)
{

  double cog[2];
  int triggertileID = -1;
  GetPadLocalCOG(module_id, pad_id, cog);
  
  double x_triggertile_width = (HBD_Board_Constant::x_board_center)/3.;
  double y_triggertile_width = (HBD_Board_Constant::y_board_center)/3.;
  
  std::vector<int> list_triggertileID = {0, 1, 2, 3, 4, 5,
					 10, 11, 12, 13, 14, 15,
					 20, 21, 22, 23, 24, 25,
					 30, 31, 32, 33, 34, 35,
					 40, 41, 42, 43, 44, 45,
					 50, 51, 52, 53, 54, 55};
  
  double x_triggertile[2];
  double y_triggertile[2];
  for(auto id : list_triggertileID){
    for(int i=0; i<2; i++){
      x_triggertile[i] = (id%10+i)*x_triggertile_width - HBD_Board_Constant::x_board_center;
      y_triggertile[i] = (id/10+i)*y_triggertile_width - HBD_Board_Constant::y_board_center;
    }
      
    if(x_triggertile[0] <= cog[0] && cog[0] <=x_triggertile[1]){
      if(y_triggertile[0] <= cog[1] && cog[1] <=y_triggertile[1]){
	triggertileID = id;
      }
    }
  }
  
  return triggertileID;
}

bool E16ANA_HBDGeometry::IsRotated(const int module_id)
{
  std::vector<int> v(std::begin(HBD_Module_Constant::rotated_module_ids), std::end(HBD_Module_Constant::rotated_module_ids));
  
  auto module_exist = std::find(v.begin(), v.end(), module_id);
  if(module_exist == v.end()){
    //not found
    return false;
  }else{
    //found
    return true;
  }
}
