#ifndef E16ANA_HBDGeometry_h
#define E16ANA_HBDGeometry_h

#include "E16ANA_HBDTH2Hex.hh"
#include "E16ANA_HBDConstant.hh"
#include "E16ANA_Within2DArea.hh"

#include "TVector3.h"

#include <string>
#include <vector>
#include <utility>

class E16ANA_HBDGeometry
{

public:
  E16ANA_HBDGeometry();
  ~E16ANA_HBDGeometry();
  bool ReadGEMGeometryFile(const char *_GEMgeometryfilename);
  bool CheckIfGEMGeometryFile();
  void ShowGEMGeometryParameters();
  //std::vector<double> GetGlobalPosition(const int module_id, const double *lpos);
  void GetGEMSensitiveArea(const int GEMID, std::vector<double> &_vx, std::vector<double> &_vy);
  void GetGEMTriggerTileArea(const int tileID, std::vector<double> &_vx, std::vector<double> &_vy);
  
  static bool GetPadLocalCOG(const int module_id, const int pad_id, double *cog);
  static TVector3 GetPadLocalCOG(const int module_id, const int pad_id);
  
  static bool BoardToLocalCoordinate(const int module_id, double *v);
  static bool LocalToBoardCoordinate(const int module_id, double *v);  
  static bool IsRotated(const int module_id);
  
  int GetGEMIDWLocalCoordinate(const double *cog);
  int GetTriggerTileIDWLocalCoordinate(const double *cog);
  static int GetPadIDWLocalCoordinate(const int module_id, const double *cog);
  
  //--- obsolete from 220426---// 
  static std::vector<int> GetGEMAssociatedTriggerTileID(const int GEM_id);
  static std::vector<int> GetGEMAssociatedPadID(const int module_id, const int GEM_id);
  static int GetTriggerTileAssociatedGEMID(const int triggertile_id);
  static std::vector<int> GetTriggerTileAssociatedPadID(const int module_id, const int triggertile_id);
  static int GetPadAssociatedTriggerTileID(const int module_id, const int pad_id);
  //--- obsolete from 220426---// 
  //--- new from 220426 ---//
  std::vector<int> GetGEMAssociatedTriggerTileID_V2(const int module_id, const int gem_id);
  std::vector<int> GetGEMAssociatedPadID_V2(const int module_id, const int gem_id);
  int GetTriggerTileAssociatedGEMID_V2(const int module_id, const int tile_id);
  std::vector<int> GetTriggerTileAssociatedPadID_V2(const int module_id, const int tile_id);
  std::vector<int> GetPadAssociatedGEMID_V2(const int module_id, const int pad_id);
  std::vector<int> GetPadAssociatedTriggerTileID_V2(const int module_id, const int pad_id);
  //--- new from 220426 ---//
  
  static E16ANA_HBDTH2Hex h_hexpad_board_normal;
  static E16ANA_HBDTH2Hex h_hexpad_board_rotate;

private:
  void SetOtherGEMGeometry();
  void SetAssociation();
  std::vector<int> GetGEMAssociatedTriggerTileID_(const int module_id, const int gem_id);
  std::vector<int> GetGEMAssociatedPadID_(const int module_id, const int gem_id);
  int GetTriggerTileAssociatedGEMID_(const int module_id, const int tile_id);
  std::vector<int> GetTriggerTileAssociatedPadID_(const int module_id, const int tile_id);
  std::vector<int> GetPadAssociatedGEMID_(const int module_id, const int pad_id);
  std::vector<int> GetPadAssociatedTriggerTileID_(const int module_id, const int pad_id);
  
  enum {
    n_modules = HBD_Module_Constant::n_modules,
    n_GEMs = HBD_Module_Constant::n_GEMs,
    n_tiles = HBD_Module_Constant::n_tiles,
    n_pads = HBD_Module_Constant::n_pads
  };

  std::vector<int> GEM_associated_tile[n_GEMs];
  std::vector<int> GEM_associated_pad[n_modules][n_GEMs];
  int tile_associated_GEM[n_tiles];
  std::vector<int> tile_associated_pad[n_modules][n_tiles]; 
  std::vector<int> pad_associated_GEM[n_modules][n_pads];
  std::vector<int> pad_associated_tile[n_modules][n_pads];
  
  bool flag_GEMgeometryfile_read;  
  std::vector<double> GEM_sensitive_area_vx[n_GEMs], GEM_sensitive_area_vy[n_GEMs];
  std::vector<double> GEM_triggertile_area_vx[n_tiles], GEM_triggertile_area_vy[n_tiles];
  E16ANA_Within2DArea GEM_area[n_GEMs];
  E16ANA_Within2DArea triggertile_area[n_tiles];
  
  // origin of the board coordinate. board coordinate origin is "sticked" to pad$
  // While local coordinate is defined with respect to the board center.
  //
  //         pad ID 0
  //         _________
  //        /         \     * is the origin of the board
  //       /           \              /|\y
  //      /             \              |
  //      ---------------*      x <----|
  //            2a

};

#endif // E16ANA_HBDGeometry_h
