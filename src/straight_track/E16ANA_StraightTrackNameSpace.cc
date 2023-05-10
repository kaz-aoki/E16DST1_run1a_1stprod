#include "E16ANA_StraightTrackNameSpace.hh"

namespace E16ANA_StraightTrackNameSpace {
     std::vector<double>  kXSigma = {0.3, 0.3, 0.3};
     std::vector<double>  kYSigma = {0.3, 1, 1};
	// std::vector<double> kYsigma = {0.5, 0.5, 0.5};
	  double kFitChi2ThresholdX = 250.;
	  double kFitChi2ThresholdY = 250.;
	  std::array<double, 3> kGTRPeakSumThresholdX = {50000, 80, 80};
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
