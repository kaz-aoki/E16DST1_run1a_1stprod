#ifndef E16ANA_GTR_LORENTZ_ANGLE_CALIB_HH
#define E16ANA_GTR_LORENTZ_ANGLE_CALIB_HH

#include <array>
#include <iostream>
#include <string>

class E16ANA_GTRLorentzAngleCalibParamManager {
 public:
  E16ANA_GTRLorentzAngleCalibParamManager() {}
  ~E16ANA_GTRLorentzAngleCalibParamManager() {}
  bool ReadConstantData(int run_id);
  bool ReadConstantDataByLocal(int run_id, std::string index_file_name);
  int RunId() { return run_id; }
  double GTRLorentzAngleCalibParam(int n) { return gtr_lorentz_angle_calib_params[n]; }
  std::array<double, 3> GTRLorentzAngleCalibParams() { return gtr_lorentz_angle_calib_params; }
  double GTRLorentzAngle(int n) { return  gtr_lorentz_angles[n]; }
  std::array<double, 3> GTRLorentzAngles() { return gtr_lorentz_angles; }
 private:
  bool ReadConstantDataCore(int _run_id, std::string _index_file_name);
  int run_id;
  std::array<double, 3> gtr_lorentz_angle_calib_params;
  std::array<double, 3> gtr_lorentz_angles;
};

#endif // E16ANA_GTR_LORENTZ_ANGLE_CALIB_HH
