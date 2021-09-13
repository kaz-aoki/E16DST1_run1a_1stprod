#ifndef E16ANA_HBDGeometry_h
#define E16ANA_HBDGeometry_h

#include "E16ANA_HBDTH2Hex.hh"

#include "TVector3.h"

#include <string>
#include <vector>
#include <utility>

class E16ANA_HBDGeometry
{

public:
  E16ANA_HBDGeometry();
  ~E16ANA_HBDGeometry();
  bool ReadGeometryFile(char *_geometryfilename);
  bool CheckIfGeometryFile();
  void ShowGeometryParameters();
  std::vector<double> GetGlobalPosition(const int module_id, const double *lpos);
  static int GetPadIDWLocalCoordinate(const int module_id, const double *cog);
  static bool GetPadLocalCOG(const int module_id, const int pad_id, double *cog);
  static TVector3 GetPadLocalCOG(const int module_id, const int pad_id);
  static bool BoardToLocalCoordinate(const int module_id, double *v);
  static bool LocalToBoardCoordinate(const int module_id, double *v);
  
  static std::vector<int> GetTriggerTileAssociatedPadID(const int module_id, const int triggertile_id);
  static std::vector<int> GetGEMAssociatedTriggerTileID(const int GEM_id);
  static std::vector<int> GetGEMAssociatedPadID(const int module_id, const int GEM_id);
  static int GetTriggerTileAssociatedGEMID(const int triggertile_id);
  static int GetPadAssociatedTriggerTileID(const int module_id, const int pad_id);
  static bool IsRotated(const int module_id);

  static E16ANA_HBDTH2Hex h_hexpad_board_normal;
  static E16ANA_HBDTH2Hex h_hexpad_board_rotate;

private:
  char *geometryfilename;
  bool flag_geometryfile_read;
  std::vector<std::pair<int, std::vector<double>>> shift; //module ID, xyz [mm]
  double r; // distance from the center of the HBD to the board center mm
  double gap[3];//[pad<->mesh, pad<->CsI, pad<->triggertile] mm
  std::vector<std::pair<int, double>> angle;//degree
  
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
