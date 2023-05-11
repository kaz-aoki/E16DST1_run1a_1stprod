#ifndef E16ANA_STRAIGHT_TRACK_NAMESPACE_HH
#define E16ANA_STRAIGHT_TRACK_NAMESPACE_HH

#include <vector>
#include <array>
#include "E16DST_DST1Constant.hh"

namespace E16ANA_StraightTrackNameSpace{
	//constexpr std::vector<double> kXsigma = {0.3, 0.3, 0.3};
	//constexpr std::vector<double> kYsigma = {0.5, 0.5, 0.5};
	 extern std::vector<double> kXSigmaGTR ;
	 extern std::vector<double> kXSigmaSSD ;
	 extern std::vector<double> kYSigma ;
	extern double kFitChi2ThresholdX ;
	extern double kFitChi2ThresholdY ;
	extern std::array<double, 3> kGTRPeakSumThresholdX;
	extern double E16ANA_GTRLocalX(double lorentz_angle_calib_param, int layer_id, int type, int channel_id);
	const double Agtr[] = {1.295, 0.882, 0.469, 0, -0.469, -0.882, -1.295};

}



#endif //E16ANA_STRAIGHT_TRACK_PARAMETER_HH
