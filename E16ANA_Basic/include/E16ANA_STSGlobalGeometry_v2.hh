////////////////////////////////////////////////////////////////////////////////////
// class E16ANA_STSGlobalGeometry_v2
//                                            K. Aoki
//
// The class is a singleton. It manages global coordinate of STS.
//
// 
////////////////////////////////////////////////////////////////////////////////////

#ifndef E16ANA_STSGlobalGeometry_v2_h__
#define E16ANA_STSGlobalGeometry_v2_h__

#include <cmath>
#include <map>
#include "TGeoMatrix.h"
#include "TVector3.h"

#include "E16ANA_STSGlobalGeometry.hh"

class E16ANA_STSGlobalGeometryCalib;

class E16ANA_STSGlobalGeometry_v2 : public E16ANA_STSGlobalGeometry {
  friend class E16ANA_STSGlobalGeometryCalib;
public:
  E16ANA_STSGlobalGeometry_v2(); // Does not prohibit multiple instantiation. But use it with precaution.
  static E16ANA_STSGlobalGeometry* instance();
  void set_calib(E16ANA_STSGlobalGeometryCalib& calib);
private:
  void Prepare();
};


#endif
