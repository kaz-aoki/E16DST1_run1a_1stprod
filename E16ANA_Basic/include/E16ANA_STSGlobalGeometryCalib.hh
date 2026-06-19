//E16ANA_STSGlobalGeometryCalib.hh 251231 by K.Aoki
//    Last modified at <2025-12-31 10:25:00 >
//

#ifndef E16ANA_STSGlobalGeometryCalib_HH
#define E16ANA_STSGlobalGeometryCalib_HH


#include <string>
#include <map>
#include <cstdint>

//#include "E16ANA_STSGlobalGeometry.hh"
//#include "E16ANA_STSGlobalGeometry_v2.hh"

class E16ANA_STSGlobalSensorGeom;
class E16ANA_STSGlobalGeometry_v2;

class E16ANA_STSGlobalGeometryCalib {
  friend class E16ANA_STSGlobalGeometry_v2;
public:
  E16ANA_STSGlobalGeometryCalib();
  ~E16ANA_STSGlobalGeometryCalib();

  bool ReadConstantData(int run_id);
  bool ReadConstantDataByLocal(int run_id, std::string index_file_name);

private:
  bool ReadConstantDataCore(int _run_id, std::string _index_file_name);
  void Init();
  std::map<int,E16ANA_STSGlobalSensorGeom> map_sg;
  
  int run_id;
};

#endif // E16ANA_STSGlobalGeometryCalib_HH
