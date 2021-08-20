#ifndef E16ANA_LGCONSTANT_HH
#define E16ANA_LGCONSTANT_HH

#include <array>

namespace E16ANA_LGConstant {

const double             kTimeScale               = 960. / 1000.;

const int kHitThreshold = 20;//[mV]
const int kHitTimingStart = 50;//[ns]
const int kHitTimingEnd = 150;//[ns]

const int kPeakSearchStart = 5;//[cell]
const int kPeakSearchEnd = 200;//[cell]
const int kTimingSearchRegion = 20;//[cell] before peaktime
const int kBaselineStart = -100;//[cell] +peaktime
const int kBaselineEnd = -50;//[cell] +peaktime
const int kIntegralStart = -20;//[cell] +peaktime
const int kIntegralEnd = 50;//[cell] +peaktime


}; // namespace E16ANA_LGConstant

#endif
