////////////////////////////////////////////////////////////////////////////////////
// class E16ANA_STSGlobalGeometry
//                                            K. Aoki
//
// The class is a singleton. It manages global coordinate of STS.
//
// 
////////////////////////////////////////////////////////////////////////////////////

#ifndef E16ANA_STSGlobalGeometry_h__
#define E16ANA_STSGlobalGeometry_h__

#include <cmath>
#include <map>
#include "TGeoMatrix.h"
#include "TVector3.h"

class E16ANA_STSGlobalSensorGeom{
 public:
  int mod = 0;
  double radius = 0;
  double angle = 0;
  double dy = 0;
  bool bSpin = false;
  E16ANA_STSGlobalSensorGeom() {;}
 E16ANA_STSGlobalSensorGeom(int _mod, double _radius, double _angle, double _dy, bool _bSpin)
   :mod(_mod),radius(_radius),angle(_angle),dy(_dy),bSpin(_bSpin){;}
};

class E16ANA_STSGlobalGeometry{
 public:
  E16ANA_STSGlobalGeometry(); // Does not prohibit multiple instantiation. But use it with precaution.
  static E16ANA_STSGlobalGeometry* instance();
  void Local2Global(int mod,const double* local, double* global);
  void Global2Local(int mod,const double* global, double* local);
  void Local2Global_wotrans(int mod,const double* local, double* global);
  void Global2Local_wotrans(int mod,const double* global, double* local);
  void Local2Global(int mod,const TVector3& local, TVector3& global){
    double tmp_local[3] = { local.X(), local.Y(), local.Z() };
    double tmp_global[3];
    Local2Global(mod,tmp_local,tmp_global);
    global.SetXYZ(tmp_global[0],tmp_global[1],tmp_global[2]);
  }
  void Global2Local(int mod,const TVector3& global, TVector3& local){
    double tmp_global[3] = {global.X(),global.Y(),global.Z()};
    double tmp_local[3];
    Global2Local(mod,tmp_global,tmp_local);
    local.SetXYZ(tmp_local[0],tmp_local[1],tmp_local[2]);
  }

  void CalcPointOnPlane(int mod,double* global0, double* global1, double* global_out);

 private:
  void Prepare();
  static E16ANA_STSGlobalGeometry* pInstance;
  void PrepareMatrix(E16ANA_STSGlobalSensorGeom& sensor);
  std::map<int,E16ANA_STSGlobalSensorGeom> map_sensor;
  std::map<int,TGeoHMatrix> map_mat;
  std::map<int,TGeoHMatrix> map_mat_wotrans;
};


#endif
