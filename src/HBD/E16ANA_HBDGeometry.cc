#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDChannelManager.hh"
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
  E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
  std::string hbd_GEMgeometry_file = calib.CalibFileName("HBD-GEMgeometry", 1);//do not change run by run
  
  flag_GEMgeometryfile_read = false;
  ReadGEMGeometryFile(hbd_GEMgeometry_file.c_str());
}

E16ANA_HBDGeometry::~E16ANA_HBDGeometry()
{
}

bool E16ANA_HBDGeometry::ReadGEMGeometryFile(const char *_GEMgeometryfilename){  
  std::ifstream fin(_GEMgeometryfilename);
  
  if( fin ){
    for(int i=0; i<n_GEMs; i++){
      GEM_sensitive_area_vx[i].clear();
      GEM_sensitive_area_vy[i].clear();
    }
    for(int i=0; i<n_tiles/n_GEMs; i++){
      GEM_triggertile_area_vx[i].clear();
      GEM_triggertile_area_vy[i].clear();
    }
    std::string buf_line;
    
    for(;;){
      if(fin.eof()) break;
      std::getline(fin, buf_line);
      if(buf_line[0] == '#' || buf_line[0] == '\0') continue;
      
      std::stringstream ss(buf_line);
      std::string type;
      double buf_vx;
      double buf_vy;
      ss>>type>>buf_vx>>buf_vy;
      if(type == "g0"){//GEMID 0
	GEM_sensitive_area_vx[0].push_back(buf_vx);
	GEM_sensitive_area_vy[0].push_back(buf_vy);
      }
      if(type.substr(0, 1) == "t"){
	std::string tile = type.substr(1, 2);
	int index = atoi(tile.c_str());
	int kid = E16ANA_HBDChannelManager::ConvTIDE16ToK(index);
	GEM_triggertile_area_vx[kid].push_back(buf_vx);
	GEM_triggertile_area_vy[kid].push_back(buf_vy);
      }
    }
    SetOtherGEMGeometry();
    SetAssociation();
    flag_GEMgeometryfile_read = true;
    return true;
  }
  else{
    std::cerr<<__func__<<" invalid geometry filename"<<std::endl;
    return false;
  }
}

void E16ANA_HBDGeometry::SetOtherGEMGeometry()
{
  if(GEM_sensitive_area_vx[0].size() != 0){
    //--- GEMID 1 ---//
    for(auto p : GEM_sensitive_area_vx[0]){
      GEM_sensitive_area_vx[1].push_back(p+HBD_Board_Constant::GEM_spacing_x);
    }
    for(auto p : GEM_sensitive_area_vy[0]){
      GEM_sensitive_area_vy[1].push_back(p);
    }
    //--- GEMID 1 ---//
    //--- GEMID 10 ---//
    for(auto p : GEM_sensitive_area_vx[1]){
      GEM_sensitive_area_vx[2].push_back(-p);
    }
    for(auto p : GEM_sensitive_area_vy[1]){
      GEM_sensitive_area_vy[2].push_back(-p);
    }
    //--- GEMID 10 ---//
    //--- GEMID 11 ---//
    for(auto p : GEM_sensitive_area_vx[0]){
      GEM_sensitive_area_vx[3].push_back(-p);
    }
    for(auto p : GEM_sensitive_area_vy[0]){
      GEM_sensitive_area_vy[3].push_back(-p);
    }
    //--- GEMID 11 ---//
    //--- GEMID 1, tileID 3, 4, 5, 13, 14, 15, 23, 24, 25 ---//
    for(auto tile : GetGEMAssociatedTriggerTileID_(0, 0)){
      for(auto p : GEM_triggertile_area_vx[E16ANA_HBDChannelManager::ConvTIDE16ToK(tile)]){
	int kid = E16ANA_HBDChannelManager::ConvTIDE16ToK(tile+HBD_Module_Constant::n_tiles_x_in_GEM);
	GEM_triggertile_area_vx[kid].push_back(p+HBD_Board_Constant::GEM_spacing_x);
      }
      for(auto p : GEM_triggertile_area_vy[E16ANA_HBDChannelManager::ConvTIDE16ToK(tile)]){
	int kid = E16ANA_HBDChannelManager::ConvTIDE16ToK(tile+HBD_Module_Constant::n_tiles_x_in_GEM);
	GEM_triggertile_area_vy[kid].push_back(p);
      }
    }
    //--- GEMID 1, tileID 3, 4, 5, 13, 14, 15, 23, 24, 25 ---//
    //--- GEMID 10, tileID 30, 31, 32, 40, 41, 42, 50, 51, 52 ---//
    for(auto tile : GetGEMAssociatedTriggerTileID_(0, 1)){
      for(auto p : GEM_triggertile_area_vx[E16ANA_HBDChannelManager::ConvTIDE16ToK(tile)]){
	int kid = E16ANA_HBDChannelManager::ConvTIDE16ToK(55-tile);//3->52, 4->51, ..., 24->31, 25->30
	GEM_triggertile_area_vx[kid].push_back(-p);
      }
      for(auto p : GEM_triggertile_area_vy[E16ANA_HBDChannelManager::ConvTIDE16ToK(tile)]){
	int kid = E16ANA_HBDChannelManager::ConvTIDE16ToK(55-tile);
	GEM_triggertile_area_vy[kid].push_back(-p);
      }
    }
    //--- GEMID 10, tileID 30, 31, 32, 40, 41, 42, 50, 51, 52 ---//
    //--- GEMID 11, tileID 33, 34, 35, 43, 44, 45, 53, 54, 55 ---//
    for(auto tile : GetGEMAssociatedTriggerTileID_(0, 0)){
      for(auto p : GEM_triggertile_area_vx[E16ANA_HBDChannelManager::ConvTIDE16ToK(tile)]){
	int kid = E16ANA_HBDChannelManager::ConvTIDE16ToK(55-tile);//0->55, 1->54, ..., 21->34, 22->33
	GEM_triggertile_area_vx[kid].push_back(-p);
      }
      for(auto p : GEM_triggertile_area_vy[E16ANA_HBDChannelManager::ConvTIDE16ToK(tile)]){
	int kid = E16ANA_HBDChannelManager::ConvTIDE16ToK(55-tile);
	GEM_triggertile_area_vy[kid].push_back(-p);
      }
    }
    //--- GEMID 11, tileID 33, 34, 35, 43, 44, 45, 53, 54, 55 ---//
  }
  for(int i=0; i<n_GEMs; i++) GEM_area[i].SetArea(GEM_sensitive_area_vx[i], GEM_sensitive_area_vy[i]);
  for(int i=0; i<n_tiles; i++) triggertile_area[i].SetArea(GEM_triggertile_area_vx[i], GEM_triggertile_area_vy[i]);
  
}

void E16ANA_HBDGeometry::SetAssociation()
{
  for(int i=0; i<n_modules; i++){
    int mid = HBD_Module_Constant::module_ids[i];
    for(int j=0; j<n_GEMs; j++){
      std::vector<int> buf_tid = GetGEMAssociatedTriggerTileID_(mid, E16ANA_HBDChannelManager::ConvGIDKToE16(j));
      std::vector<int> buf_pid = GetGEMAssociatedPadID_(mid, E16ANA_HBDChannelManager::ConvGIDKToE16(j));
      for(auto t : buf_tid) GEM_associated_tile[j].push_back(t);
      for(auto p : buf_pid) GEM_associated_pad[i][j].push_back(p);
    }
    for(int j=0; j<n_tiles; j++){
      tile_associated_GEM[j] = GetTriggerTileAssociatedGEMID_(mid, E16ANA_HBDChannelManager::ConvTIDKToE16(j));
      std::vector<int> buf_pid = GetTriggerTileAssociatedPadID_(mid, E16ANA_HBDChannelManager::ConvTIDKToE16(j));
      for(auto p : buf_pid) tile_associated_pad[i][j].push_back(p);
    }
    for(int j=0; j<n_pads; j++){
      std::vector<int> buf_gid = GetPadAssociatedGEMID_(mid, j);
      std::vector<int> buf_tid = GetPadAssociatedTriggerTileID_(mid, j);
      for(auto g : buf_gid) pad_associated_GEM[i][j].push_back(g);
      for(auto t : buf_tid) pad_associated_tile[i][j].push_back(t);
    }
  }
}

bool E16ANA_HBDGeometry::CheckIfGEMGeometryFile(){
  return flag_GEMgeometryfile_read ? true : false;
}

void E16ANA_HBDGeometry::ShowGEMGeometryParameters(){
  if(CheckIfGEMGeometryFile()){
  }
  else{
    std::cerr<<"geometry file is not set"<<std::endl;
  }
}

/*
std::vector<double> E16ANA_HBDGeometry::GetGlobalPosition(const int module_id, const double *lpos)
{//[lpos: xy]
 
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
*/

void E16ANA_HBDGeometry::GetGEMSensitiveArea(const int GEMID, std::vector<double> &_vx, std::vector<double> &_vy)
{
  if(GEMID == 0){
    _vx = GEM_sensitive_area_vx[0];
    _vy = GEM_sensitive_area_vy[0];
  }
  if(GEMID == 1){
    _vx = GEM_sensitive_area_vx[1];
    _vy = GEM_sensitive_area_vy[1];
  }
  if(GEMID == 10){
    _vx = GEM_sensitive_area_vx[2];
    _vy = GEM_sensitive_area_vy[2];
  }
  if(GEMID == 11){
    _vx = GEM_sensitive_area_vx[3];
    _vy = GEM_sensitive_area_vy[3];
  }
}

void E16ANA_HBDGeometry::GetGEMTriggerTileArea(const int tileID, std::vector<double> &_vx, std::vector<double> &_vy)
{
  int kid = E16ANA_HBDChannelManager::ConvTIDE16ToK(tileID);
  _vx = GEM_triggertile_area_vx[kid];
  _vy = GEM_triggertile_area_vy[kid];
}

bool E16ANA_HBDGeometry::GetPadLocalCOG(const int module_id, const int pad_id, double *cog)
{//cog[2]: 0: local x, 1: local y
  int n_pad_x = HBD_Board_Constant::n_pad_x;
  int n_pad_y = HBD_Board_Constant::n_pad_y;
  int n_pad = E16DST_Constant::NPadsHBD;
  double a = HBD_Board_Constant::hex_pad_length;
  
  cog[0] = -10000.;//local x
  cog[1] = -10000.;//local y
  
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
}

TVector3 E16ANA_HBDGeometry::GetPadLocalCOG(const int module_id, const int pad_id)
{
  double cog[2];
  GetPadLocalCOG(module_id, pad_id, cog);
  TVector3 lpos(cog[0], cog[1], 0.);
  return lpos;
}

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

int E16ANA_HBDGeometry::GetGEMIDWLocalCoordinate(const double *cog)
{
  double x = cog[0];
  double y = cog[1];
  
  for(int i=0; i<n_GEMs; i++){
    bool flag = GEM_area[i].IsWithin2DArea(x, y);
    if(flag) return E16ANA_HBDChannelManager::ConvGIDKToE16(i);
  }
  
  return -1;
}

int E16ANA_HBDGeometry::GetTriggerTileIDWLocalCoordinate(const double *cog)
{
  double x = cog[0];
  double y = cog[1];
  int GEM_id = GetGEMIDWLocalCoordinate(cog);
  std::vector<int> tile_id = GetGEMAssociatedTriggerTileID_V2(0, GEM_id);
  for(auto p : tile_id){
    bool flag = triggertile_area[E16ANA_HBDChannelManager::ConvTIDE16ToK(p)].IsWithin2DArea(x, y);
    if(flag) return p;
  }
  
  return -1;
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

std::vector<int> E16ANA_HBDGeometry::GetGEMAssociatedTriggerTileID(const int GEM_id)
{
  std::vector<int> triggertiles;
  
  if(GEM_id == 0) triggertiles = {0, 1, 2, 10, 11, 12, 20, 21, 22};
  if(GEM_id == 1) triggertiles = {3, 4, 5, 13, 14, 15, 23, 24, 25};
  if(GEM_id == 10) triggertiles = {30, 31, 32, 40, 41, 42, 50, 51, 52};
  if(GEM_id == 11) triggertiles = {33, 34, 35, 43, 44, 45, 53, 54, 55};
  
  return triggertiles;
}

std::vector<int> E16ANA_HBDGeometry::GetGEMAssociatedPadID(const int module_id, const int GEM_id){
  
  std::vector<int> triggertiles = E16ANA_HBDGeometry::GetGEMAssociatedTriggerTileID(GEM_id);
  std::vector<int> pads;
  pads.reserve(E16DST_Constant::NPadsHBD);
  
  for(auto t : triggertiles){
    std::vector<int> t_pads = E16ANA_HBDGeometry::GetTriggerTileAssociatedPadID(module_id, t);
    for(auto p : t_pads){
      pads.push_back(p);
    }
  }
  pads.shrink_to_fit();
  
  return pads;
}

int E16ANA_HBDGeometry::GetTriggerTileAssociatedGEMID(const int triggertile_id)
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

std::vector<int> E16ANA_HBDGeometry::GetTriggerTileAssociatedPadID(const int module_id, const int triggertile_id)
{//rough. correct triggertile size should be implemented
  //triggertile ID: 0, 1, 2, 3, 4, 5, 10, 11, ..., 55
  const int n_pads = E16DST_Constant::NPadsHBD;
  std::vector<int> pads;
  pads.reserve(n_pads);//without this statement, std::vector<int> pads is allocated too much capacity,
  //resulting in segmentation violation
  
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
   if( 0 <= triggertile_id%10 && triggertile_id%10 <= 5 ){
      for(int i=0; i<n_pads; i++){
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
  pads.shrink_to_fit();
  
  return pads;
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


std::vector<int> E16ANA_HBDGeometry::GetGEMAssociatedTriggerTileID_V2(const int module_id, const int gem_id)
{
  int k_gid = E16ANA_HBDChannelManager::ConvGIDE16ToK(gem_id);
  return GEM_associated_tile[k_gid];
}

std::vector<int> E16ANA_HBDGeometry::GetGEMAssociatedPadID_V2(const int module_id, const int gem_id)
{
  int k_mid = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
  int k_gid = E16ANA_HBDChannelManager::ConvGIDE16ToK(gem_id);
  return GEM_associated_pad[k_mid][k_gid];
}

int E16ANA_HBDGeometry::GetTriggerTileAssociatedGEMID_V2(const int module_id, const int tile_id)
{
  int k_tid = E16ANA_HBDChannelManager::ConvTIDE16ToK(tile_id);
  return tile_associated_GEM[k_tid];
}

std::vector<int> E16ANA_HBDGeometry::GetTriggerTileAssociatedPadID_V2(const int module_id, const int tile_id)
{
  int k_mid = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
  int k_tid = E16ANA_HBDChannelManager::ConvTIDE16ToK(tile_id);
  return tile_associated_pad[k_mid][k_tid];
}

std::vector<int> E16ANA_HBDGeometry::GetPadAssociatedGEMID_V2(const int module_id, const int pad_id)
{
  int k_mid = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
  return pad_associated_GEM[k_mid][pad_id];
}

std::vector<int> E16ANA_HBDGeometry::GetPadAssociatedTriggerTileID_V2(const int module_id, const int pad_id)
{
  int k_mid = E16ANA_HBDChannelManager::ConvMIDE16ToK(module_id);
  return pad_associated_tile[k_mid][pad_id];
}

std::vector<int> E16ANA_HBDGeometry::GetGEMAssociatedTriggerTileID_(const int module_id, const int GEM_id)
{
  std::vector<int> triggertiles;
  
  if(GEM_id == 0) triggertiles = {0, 1, 2, 10, 11, 12, 20, 21, 22};
  if(GEM_id == 1) triggertiles = {3, 4, 5, 13, 14, 15, 23, 24, 25};
  if(GEM_id == 10) triggertiles = {30, 31, 32, 40, 41, 42, 50, 51, 52};
  if(GEM_id == 11) triggertiles = {33, 34, 35, 43, 44, 45, 53, 54, 55};
  
  return triggertiles;
}

std::vector<int> E16ANA_HBDGeometry::GetGEMAssociatedPadID_(const int module_id, const int gem_id)
{
  std::vector<int> pads;
  std::vector<int> tile_id = GetGEMAssociatedTriggerTileID_(module_id, gem_id);

  for(auto t : tile_id){
    std::vector<int> buf_pads = GetTriggerTileAssociatedPadID_(module_id, t);
    for(auto p : buf_pads){
      pads.push_back(p);
    }
  }
  std::sort(pads.begin(), pads.end());
  pads.erase(std::unique(pads.begin(), pads.end()), pads.end());
  
  return pads;
}

int E16ANA_HBDGeometry::GetTriggerTileAssociatedGEMID_(const int module_id, const int tile_id)
{
  int gem_id = -1;
  
  if((tile_id%10 == 0 ||
      tile_id%10 == 1 ||
      tile_id%10 == 2 ) &&
     tile_id/10 <= 2 &&
     0<= tile_id && tile_id <=55) gem_id = 0;
  
  if((tile_id%10 == 3 ||
      tile_id%10 == 4 ||
      tile_id%10 == 5 ) &&
     tile_id/10 <= 2 &&
     0<= tile_id && tile_id <=55) gem_id = 1;

  if((tile_id%10 == 0 ||
      tile_id%10 == 1 ||
      tile_id%10 == 2 ) &&
     tile_id/10 >= 3 &&
     0<= tile_id && tile_id <=55) gem_id = 10;
  
  if((tile_id%10 == 3 ||
      tile_id%10 == 4 ||
      tile_id%10 == 5 ) &&
     tile_id/10 >= 3 &&
     0<= tile_id && tile_id <=55) gem_id = 11;
  
  return gem_id;
}

std::vector<int> E16ANA_HBDGeometry::GetTriggerTileAssociatedPadID_(const int module_id, const int tile_id)
{
  std::vector<int> pads;
  for(int i=0 ;i<n_pads; i++){
    std::vector<int> buf_tile_id = GetPadAssociatedTriggerTileID_(module_id, i);
    for(auto t : buf_tile_id){
      if(t == tile_id) pads.push_back(i);
    }
  }
  return pads;
}

std::vector<int> E16ANA_HBDGeometry::GetPadAssociatedGEMID_(const int module_id, const int pad_id)
{
  std::vector<int> gem_id;
  
  double a = HBD_Board_Constant::hex_pad_length;
  double cog_lpos[2];
  GetPadLocalCOG(module_id, pad_id, cog_lpos);
  double v_lpos[6][2];//hex pad vertices
  v_lpos[0][0] = cog_lpos[0]-a;//local x
  v_lpos[1][0] = cog_lpos[0]-a/2.;
  v_lpos[2][0] = cog_lpos[0]+a/2.;
  v_lpos[3][0] = cog_lpos[0]+a;
  v_lpos[4][0] = cog_lpos[0]+a/2.;
  v_lpos[5][0] = cog_lpos[0]-a/2.;
  
  v_lpos[0][1] = cog_lpos[1];//local y
  v_lpos[1][1] = cog_lpos[1]+a*std::sqrt(3.)/2.;
  v_lpos[2][1] = cog_lpos[1]+a*std::sqrt(3.)/2.;
  v_lpos[3][1] = cog_lpos[1];
  v_lpos[4][1] = cog_lpos[1]-a*std::sqrt(3.)/2.;
  v_lpos[5][1] = cog_lpos[1]-a*std::sqrt(3.)/2.;

  for(int i=0; i<n_GEMs; i++){
    bool f_within = false;
    for(int j=0; j<6; j++){
      if(GEM_area[i].IsWithin2DArea(v_lpos[j][0], v_lpos[j][1])){
	f_within = true;
      }
    }
    if(f_within) gem_id.push_back(E16ANA_HBDChannelManager::ConvGIDKToE16(i));
  }
  return gem_id;
}

std::vector<int> E16ANA_HBDGeometry::GetPadAssociatedTriggerTileID_(const int module_id, const int pad_id)
{
  std::vector<int> tile_id;

  double a = HBD_Board_Constant::hex_pad_length;
  double cog_lpos[2];
  GetPadLocalCOG(module_id, pad_id, cog_lpos);
  double v_lpos[6][2];//hex pad vertices
  v_lpos[0][0] = cog_lpos[0]-a;
  v_lpos[1][0] = cog_lpos[0]-a/2.;
  v_lpos[2][0] = cog_lpos[0]+a/2.;
  v_lpos[3][0] = cog_lpos[0]+a;
  v_lpos[4][0] = cog_lpos[0]+a/2.;
  v_lpos[5][0] = cog_lpos[0]-a/2.;
  
  v_lpos[0][1] = cog_lpos[1];
  v_lpos[1][1] = cog_lpos[1]+a*std::sqrt(3.)/2.;
  v_lpos[2][1] = cog_lpos[1]+a*std::sqrt(3.)/2.;
  v_lpos[3][1] = cog_lpos[1];
  v_lpos[4][1] = cog_lpos[1]-a*std::sqrt(3.)/2.;
  v_lpos[5][1] = cog_lpos[1]-a*std::sqrt(3.)/2.;

  std::vector<int> gem_id = GetPadAssociatedGEMID_(module_id, pad_id);
  for(auto g : gem_id){
    for(auto t : GetGEMAssociatedTriggerTileID_(module_id, g)){
      bool f_within = false;
      for(int i=0; i<6; i++){
	if(triggertile_area[E16ANA_HBDChannelManager::ConvTIDE16ToK(t)].IsWithin2DArea(v_lpos[i][0], v_lpos[i][1])){
	  f_within = true;
	}
      }
      if(f_within) tile_id.push_back(t);
    }
  }
  return tile_id;
}
