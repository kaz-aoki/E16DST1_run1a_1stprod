#include "E16ANA_STSGlobalGeometryCalib.hh"
#include "E16ANA_STSGlobalGeometry_v2.hh"
#include "TGeoMatrix.h"
#include "TVector3.h"
#include <iostream>

//E16ANA_STSGlobalGeometry* E16ANA_STSGlobalGeometry::pInstance = NULL;

E16ANA_STSGlobalGeometry_v2::E16ANA_STSGlobalGeometry_v2(){
}

E16ANA_STSGlobalGeometry* E16ANA_STSGlobalGeometry_v2::instance(){
  if ( pInstance != nullptr ){
    // have a pointer already
    E16ANA_STSGlobalGeometry_v2* p = dynamic_cast<E16ANA_STSGlobalGeometry_v2*>(pInstance);
    if ( p == nullptr ){
      std::cout << "E16ANA_STSGlobalGeometry(v1) instance exists. Will be replaced by v2." << std::endl;
      delete pInstance;
      pInstance = nullptr;
    }
  }
  if ( pInstance == nullptr ) {
    E16ANA_STSGlobalGeometry_v2* p = new E16ANA_STSGlobalGeometry_v2;
    p->Prepare();
    pInstance = p;
  }
  return pInstance;
}

void E16ANA_STSGlobalGeometry_v2::Prepare(){
  std::cout << "E16ANA_STSGlobalGeometry_v2::Prepare()" << std::endl;
  // 201-209 // upper
  // 101-109 // middle
  // 001-009 // lower
  double r_inner = 117.386;
  double r_outer = 148.81;
  const double deg2rad = 3.141592/180.;
  double globalmis = 0;
  E16ANA_STSGlobalSensorGeom sensor101
    (101,
     r_inner,
     (-26.89 - 23.66*3+globalmis)/* *deg2rad */,
     0,
     true);
  E16ANA_STSGlobalSensorGeom sensor102
    (102,
     r_outer,
     (-26.89 - 23.66*2+globalmis) /* *deg2rad */,
     0,
     false);
  E16ANA_STSGlobalSensorGeom sensor103
    (103,
     r_inner,
     (-26.89 - 23.66*1+globalmis) /* *deg2rad */,
     0,
     true);
#if 0 // design value
  E16ANA_STSGlobalSensorGeom sensor104
    (104,
     r_outer,
     (-26.89+globalmis) /* *deg2rad */,
     0,
     false);
#endif
#if 1 // nakai value for 104 (2024-08-21)
  E16ANA_STSGlobalSensorGeom sensor104
    (104,
     r_outer,
     (-26.89+0.081+globalmis) /* *deg2rad */,
     0,
     false);
    /*
    (104,
     r_outer - 0.000577,
     (-26.89) + 0.221964 
     0,
     false);
  sensor104.dx = -0.346972;
  */
#endif
#if 0 // design value
  E16ANA_STSGlobalSensorGeom sensor106
    (106,
     r_outer,
     (+26.89+globalmis) /* *deg2rad */,
     0,
     false);
#endif
#if 1 // mtomoki value for 106
  E16ANA_STSGlobalSensorGeom sensor106
    (106,
     r_outer,
     (+26.89-0.056+globalmis) /* *deg2rad */,
     0,
     false);
#endif

  E16ANA_STSGlobalSensorGeom sensor107
    (107,
     r_inner,
     (+26.89 + 23.66+globalmis) /* *deg2rad */,
     0,
     true);

  E16ANA_STSGlobalSensorGeom sensor108
    (108,
     r_outer,
     (+26.89 + 23.66*2+globalmis) /* *deg2rad */,
     0,
     false);

  E16ANA_STSGlobalSensorGeom sensor109
    (109,
     r_inner,
     (+26.89 + 23.66*3+globalmis) /* *deg2rad */,
     0,
     true);

  E16ANA_STSGlobalSensorGeom sensor207
    (207,
     r_inner,
     (+26.89 + 23.66) /* *deg2rad */,
     0,
     true);

  map_sensor[sensor101.mod] = sensor101;
  map_sensor[sensor102.mod] = sensor102;
  map_sensor[sensor103.mod] = sensor103;
  map_sensor[sensor104.mod] = sensor104;
  map_sensor[sensor106.mod] = sensor106;
  map_sensor[sensor107.mod] = sensor107;
  map_sensor[sensor108.mod] = sensor108;
  map_sensor[sensor109.mod] = sensor109;
  map_sensor[sensor207.mod] = sensor207;

  PrepareMatrixAll();
}

void E16ANA_STSGlobalGeometry_v2::set_calib(E16ANA_STSGlobalGeometryCalib& calib){
  std::cout << "E16ANA_STSGlobalGeometry_v2::set_calib() calib updated for mod:";
  map_sensor.clear();
  for( auto x : calib.map_sg ){
    map_sensor[x.second.mod] = x.second;
    std::cout << x.second.mod << ",";
  }
  std::cout << std::endl;
  PrepareMatrixAll();
}
