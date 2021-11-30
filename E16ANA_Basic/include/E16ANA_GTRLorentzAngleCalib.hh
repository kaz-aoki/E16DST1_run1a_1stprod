#ifndef E16ANA_GTR_LORENTZ_ANGLE_CALIB_HH
#define E16ANA_GTR_LORENTZ_ANGLE_CALIB_HH

#include <array>
#include <iostream>
#include <string>

class E16ANA_GTRLorentzAngleCalibParam {
 public:
  E16ANA_GTRLorentzAngleCalibParam() {}
  ~E16ANA_GTRLorentzAngleCalibParam() {}
  bool ReadConstantData(int run_id);
  bool ReadConstantDataByLocal(int run_id, std::string index_file_name);
  int RunId() { return run_id; }
  double GTRLorentzAngleCalibParam(int n) { return gtr_lorentz_angle_calib_params[n]; }
  std::array<double, 3> GTRLorentzAngleCalibParams() { return gtr_lorentz_angle_calib_params; }
 private:
  bool ReadConstantDataCore(int _run_id, std::string _index_file_name);
  int run_id;
  std::array<double, 3> gtr_lorentz_angle_calib_params;
};

#endif // E16ANA_GTR_LORENTZ_ANGLE_CALIB_HH
