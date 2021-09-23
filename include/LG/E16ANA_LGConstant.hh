#ifndef E16ANA_LGCONSTANT_HH
#define E16ANA_LGCONSTANT_HH

#include <array>
#include <TGraph.h>

namespace E16ANA_LGConstant {

const double             kTimeScale               = 960. / 1000.;

const int kHitThreshold = 5;//[mV]
const int kHitTimeStart = 50;//[cell]
const int kHitTimeEnd = 150;//[cell]

const int kPeakSearchStart = 5;//[cell]
const int kPeakSearchEnd = 160;//[cell]
const int kTimingSearchRegion = 20;//[cell] before peaktime
const int kBaselineStart = -60;//[cell] +peaktime
const int kBaselineEnd = -10;//[cell] +peaktime
const int kIntegralStart = -10;//[cell] +peaktime
const int kIntegralEnd = 50;//[cell] +peaktime

  //const int kTPeakSearchRegion = 190;
  //const int kTPeakSearchStart = 5;
  //const int kTPeakSearchEnd = 195;

}; // namespace E16ANA_LGConstant

#endif
