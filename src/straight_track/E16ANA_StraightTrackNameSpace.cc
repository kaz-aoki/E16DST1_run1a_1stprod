#include "E16ANA_StraightTrackNameSpace.hh"

namespace E16ANA_StraightTrackNameSpace {
     double  kXSigmaSSD = 0.1;
     std::vector<double>  kXSigmaGTR = {0.3, 0.3, 0.3};
     std::vector<double>  kYSigmaGTR = {0.6, 0.6, 0.6};
     double  kXSigmaTGT = 2.0;
     double  kYSigmaTGT = 4.0;
//     double  kXSigmaTGT = 1.5;
//     double  kYSigmaTGT = 1.5;
	// std::vector<double> kYsigma = {0.5, 0.5, 0.5};
	 double kFitChi2ThresholdX = 20.;
	 double kFitChi2ThresholdY = 20.;
     double kTimingWindow100 = 30.;
     double kTimingWindow200 = 40.;
     double kTimingWindow300 = 40.;
     double kClusterChargeWindow100 = 1000.;
     double kClusterChargeWindow200 = 1000.;
     double kClusterChargeWindow300 = 1000.;
//	  double kFitChi2ThresholdX = 250.;
//	  double kFitChi2ThresholdY = 250.;
//	  std::array<double, 3> kGTRPeakSumThresholdX = { 80,  80, 50000};
//	  std::array<double, 3> kGTRPeakSumThresholdY = { 100, 100,50000};
//	  std::array<double, 3> kGTRPeakSumThresholdX = { 80,  50000, 80};
//	  std::array<double, 3> kGTRPeakSumThresholdY = { 100, 50000, 100};
//	  std::array<double, 3> kGTRPeakSumThresholdX = {50000, 80, 80};
//	  std::array<double, 3> kGTRPeakSumThresholdY = {50000, 100, 100};
//	  std::array<double, 3> kGTRPeakSumThresholdX = {100, 100, 100};
//	  std::array<double, 3> kGTRPeakSumThresholdY = {100, 100, 100};
	  std::array<double, 3> kGTRPeakSumThresholdX = {80, 80, 80};
	  std::array<double, 3> kGTRPeakSumThresholdY = {100, 100, 100};
		double E16ANA_GTRLocalX(double lorentz_angle_calib_param, int layer_id, int type, int channel_id) {
	  double strip_pitch;
	  double position_start;
	  int n_strip_x = E16DST_DST1Constant::nstrips_x[layer_id]; 
	  int n_strip_y = E16DST_DST1Constant::nstrips_y[layer_id]; 
	  double inverted;
	  if (type == E16DST_DST1Constant::kIsX) {
	    strip_pitch = E16DST_DST1Constant::gtr_strip_pitch_x;
		  position_start = -(double)n_strip_x / 2.0 * strip_pitch + strip_pitch * 0.5 + lorentz_angle_calib_param;
	    inverted = +1.0;
	  } else if (type == E16DST_DST1Constant::kIsY) {
	    strip_pitch = E16DST_DST1Constant::gtr_strip_pitch_y;
	    position_start = -(double)n_strip_y / 2.0 * strip_pitch + strip_pitch * 0.5;
	    inverted = -1.0;
	  } else if (type == E16DST_DST1Constant::kIsYb) {
	    strip_pitch = E16DST_DST1Constant::gtr_strip_pitch_y;
	    position_start = -(double)n_strip_y / 2.0 * strip_pitch + strip_pitch * 0.5;
	    inverted = +1.0;
	  }
	  return (channel_id * strip_pitch + position_start) * inverted;
	};


}
