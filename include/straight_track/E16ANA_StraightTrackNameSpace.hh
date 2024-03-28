#ifndef E16ANA_STRAIGHT_TRACK_NAMESPACE_HH
#define E16ANA_STRAIGHT_TRACK_NAMESPACE_HH

#include <vector>
#include <array>
#include "E16DST_DST1Constant.hh"

namespace E16ANA_StraightTrackNameSpace{
	//constexpr std::vector<double> kXsigma = {0.3, 0.3, 0.3};
	//constexpr std::vector<double> kYsigma = {0.5, 0.5, 0.5};
	extern std::vector<double> kXSigmaGTR ;
	extern std::vector<double> kYSigmaGTR ;
	extern double kXSigmaSSD ;
	extern double kXSigmaTGT ;
	extern double kYSigmaTGT ;
	extern double kFitChi2ThresholdX ;
	extern double kFitChi2ThresholdY ;
	extern double kTimingWindow100;
	extern double kTimingWindow200;
	extern double kTimingWindow300;
	extern double kClusterChargeWindow100;
	extern double kClusterChargeWindow200;
	extern double kClusterChargeWindow300;
	extern std::array<double, 3> kGTRPeakSumThresholdX;
	extern std::array<double, 3> kGTRPeakSumThresholdY;
	extern double E16ANA_GTRLocalX(double lorentz_angle_calib_param, int layer_id, int type, int channel_id);
	const double Agtr[] = {1.295, 0.882, 0.469, 0, -0.469, -0.882, -1.295};

}



#endif //E16ANA_STRAIGHT_TRACK_PARAMETER_HH
