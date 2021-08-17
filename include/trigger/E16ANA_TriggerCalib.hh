#ifndef E16ANA_TRIGGER_CALIB_HH
#define E16ANA_TRIGGER_CALIB_HH

#include <array>
#include <string>

//class E16ANA_TriggerCalibParam {
// public:
////  static const int kDataSize = ;
//  E16ANA_TriggerCalibParam() {}
//  ~E16ANA_TriggerCalibParam() {}
//  bool ReadCalibData(int run_id);
////  bool ReadCalibDataByLocal(std::string local_calib_file_name);
////  bool WriteCalibData(std::string file_name);
// private:
// bool ReadCalibDataCore(FILE* ifp);
// bool is_mag;
// int  coincidence_window; 
//};

class E16ANA_TriggerCalibParam {
 public:
  E16ANA_TriggerCalibParam() {}
  ~E16ANA_TriggerCalibParam() {}
  bool ReadConstantData(int run_id);
  bool ReadConstantDataByLocal(int run_id, std::string index_file_name);
  int  CoincidenceWindow(int n) {
    if (n < coincidence_windows.size()) {
      return coincidence_windows[n];
    } else {
      return -1;
    }
  }
  int  MinimumWidth()   { return minimum_width; }
  int  MaximumWidth()   { return maximum_width; }
  int  TimeWidth()      { return time_width; }
  bool IsHBDCut()       { return is_hbd_cut == 1; }
  bool IsYCut()         { return is_y_cut == 1; }
  bool IsMaximumWidth() { return is_maximum_width == 1; }
  int  MaxTracks()      { return max_tracks; }
  int  TrackThreshold() { return track_threshold; }
  int  NimValid(int n) {
    if (n < nim_valid.size()) {
      return nim_valid[n];
    } else {
      return -1;
    }
  }
  int  TriggerPrescale(int n) {
    if (n < trigger_prescale.size()) {
      return trigger_prescale[n];
    } else {
      return -1;
    }
  }
 private:
  bool ReadConstantDataCore(int run_id, std::string index_file_name);
  union {
    std::array<int, 35> parameters;
    struct {
      std::array<int, 2>  coincidence_windows;
      int                 minimum_width;
      int                 maximum_width;
      int                 time_width;
      int                 is_hbd_cut;
      int                 is_y_cut;
      int                 is_maximum_width;
      int                 max_tracks;
      int                 track_threshold;
      std::array<int, 18> nim_valid;
      std::array<int, 7>  trigger_prescale;
    };
  };
};

#endif // E16ANA_TRIGGER_CALIB_HH
