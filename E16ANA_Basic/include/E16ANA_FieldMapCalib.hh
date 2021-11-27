#ifndef E16ANA_FIELD_MAP_CALIB_HH
#define E16ANA_FIELD_MAP_CALIB_HH

#include <array>
#include <iostream>
#include <string>

class E16ANA_FieldMapCalibParam {
 public:
  E16ANA_FieldMapCalibParam() {}
  ~E16ANA_FieldMapCalibParam() {}
  bool ReadConstantData(int run_id);
  bool ReadConstantDataByLocal(int run_id, std::string index_file_name);
  int RunId() { return run_id; }
  std::string FileName() { return file_name; }
  double FMCurrent() { return fm_current; }
 private:
  bool ReadConstantDataCore(int _run_id, std::string _index_file_name);
  int run_id;
  std::string file_name;
  double fm_current;
//  union {
//    std::array<int, 42> parameters;
//    struct {
//      std::array<int, 4>  ut3_firm_version;
//      std::array<int, 2>  coincidence_windows;
//      int                 minimum_width;
//      int                 maximum_width;
//      int                 time_width;
//      int                 is_hbd_cut;
//      int                 is_y_cut;
//      int                 is_maximum_width;
//      int                 max_tracks;
//      int                 track_threshold;
//      std::array<int, 18> nim_valid;
//      std::array<int, 7>  trigger_prescale;
//      std::array<int, 3>  mrg_delay;
//    };
//  };
};

#endif // E16ANA_FIELD_MAP_CALIB_HH
