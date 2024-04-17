#include "STS/E16ANA_STSGlobalGeometry.hh"
#include "TGeoMatrix.h"
#include "TVector3.h"
#include <iostream>

E16ANA_STSGlobalGeometry* E16ANA_STSGlobalGeometry::pInstance = NULL;

E16ANA_STSGlobalGeometry::E16ANA_STSGlobalGeometry(){
}

E16ANA_STSGlobalGeometry* E16ANA_STSGlobalGeometry::instance(){
  if ( pInstance == NULL ) {
    pInstance = new E16ANA_STSGlobalGeometry;
    pInstance->Prepare();
  }
  return pInstance;
}

void E16ANA_STSGlobalGeometry::Prepare(){
  // 201-209 // upper
  // 101-109 // middle
  // 001-009 // lower
  double r_inner = 117.386;
  double r_outer = 148.81;
  const double deg2rad = 3.141592/180.;
  E16ANA_STSGlobalSensorGeom sensor101
    (101,
     r_inner,
     (-26.89 - 23.66*3)/* *deg2rad */,
     0,
     false);
  E16ANA_STSGlobalSensorGeom sensor102
    (102,
     r_outer,
     (-26.89 - 23.66*2) /* *deg2rad */,
     0,
     true);
  E16ANA_STSGlobalSensorGeom sensor103
    (103,
     r_inner,
     (-26.89 - 23.66*1) /* *deg2rad */,
     0,
     false);

  E16ANA_STSGlobalSensorGeom sensor104
    (104,
     r_outer,
     (-26.89) /* *deg2rad */,
     0,
     true);
  E16ANA_STSGlobalSensorGeom sensor106
    (106,
     r_outer,
     (+26.89) /* *deg2rad */,
     0,
     true);

  E16ANA_STSGlobalSensorGeom sensor107
    (107,
     r_inner,
     (+26.89 + 23.66) /* *deg2rad */,
     0,
     false);

  E16ANA_STSGlobalSensorGeom sensor108
    (108,
     r_outer,
     (+26.89 + 23.66*2) /* *deg2rad */,
     0,
     true);

  E16ANA_STSGlobalSensorGeom sensor109
    (109,
     r_inner,
     (+26.89 + 23.66*3) /* *deg2rad */,
     0,
     false);

  map_sensor[sensor101.mod] = sensor101;
  map_sensor[sensor102.mod] = sensor102;
  map_sensor[sensor103.mod] = sensor103;
  map_sensor[sensor104.mod] = sensor104;
  map_sensor[sensor106.mod] = sensor106;
  map_sensor[sensor107.mod] = sensor107;
  map_sensor[sensor108.mod] = sensor108;
  map_sensor[sensor109.mod] = sensor109;
  
  for( auto iter = map_sensor.begin(); iter != map_sensor.end(); iter++){
    PrepareMatrix(iter->second);
  }
}

void E16ANA_STSGlobalGeometry::PrepareMatrix(E16ANA_STSGlobalSensorGeom& sensor){
  TGeoRotation spin;
  if (!sensor.bSpin) spin.RotateY(180.);
  TGeoTranslation trans(0,0,sensor.radius);
  TGeoRotation rot;
  rot.RotateY(sensor.angle);
  TGeoHMatrix hmat = rot * trans* spin;
  map_mat[sensor.mod] = hmat;
}

void E16ANA_STSGlobalGeometry::Local2Global(int mod,const double* local, double* global)
{
  map_mat[mod].LocalToMaster(local,global);
}

void E16ANA_STSGlobalGeometry::Global2Local(int mod,const double* global, double* local){
  map_mat[mod].MasterToLocal(global,local);
}

void E16ANA_STSGlobalGeometry::CalcPointOnPlane(int mod, double* global1, double* global2, double* global_out){
  global_out[0] = global_out[1] = global_out[2] = 0.;
  auto dequal = [](double a, double b)->bool{
    if ( fabs(a-b)< 0.00000001 ) return true;
    return false;
  };
  if ( dequal(global1[0],global2[0]) && dequal(global1[1],global2[1]) && dequal(global1[2],global2[2]) ){
    std::cout << "E16ANA_STSGlobalGeometry::CalcPointOnPlane();  Two points are same." << std::endl;
    return;
  }
  
  double tmp[3] = {0.,0.,0.,};
  double global_sensor[3];
  double global_sensor2[3];
  Local2Global(mod,tmp,global_sensor);
  
  tmp[2] = 10.;
  Local2Global(mod,tmp,global_sensor2);
  TVector3 x1(global1);
  TVector3 x2(global2);
  TVector3 sensor1(global_sensor);
  TVector3 sensor2(global_sensor2);
  TVector3 n = sensor2-sensor1;
  TVector3& n0 = sensor1;

  TVector3& x0 = x1;
  TVector3 x = x2-x1;

  double deno =  x.Dot(n);
  if ( fabs(deno) < 0.0000000001 ) {
    return;
  }
  double t = -(x0-n0).Dot(n)/deno;
  TVector3 ans = x0 + x*t;
  ans.GetXYZ(global_out);


  std::cout << "inside E16ANA_STSGlobalGeometry::CalcPointOnPlane()" << std::endl;
  std::cout << "n0 "; n0.Print();
  std::cout << "n  "; n.Print();
  std::cout << "x0 "; x0.Print();
  std::cout << "x  "; x.Print();
}
