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

  void CalcPointOnPlane(int mod,double* global0, double* global1, double* global_out);

 private:
  void Prepare();
  static E16ANA_STSGlobalGeometry* pInstance;
  void PrepareMatrix(E16ANA_STSGlobalSensorGeom& sensor);
  std::map<int,E16ANA_STSGlobalSensorGeom> map_sensor;
  std::map<int,TGeoHMatrix> map_mat;
};


#endif
