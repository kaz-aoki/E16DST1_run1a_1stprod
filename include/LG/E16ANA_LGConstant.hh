#ifndef E16ANA_LGCONSTANT_HH
#define E16ANA_LGCONSTANT_HH

#include <array>
#include <TGraph.h>

namespace E16ANA_LGConstant {

const int n_blocks = 38;
const double             kTimeScale               = 960. / 1000.;

const int kHitThreshold = 5;//[mV]
const int kHitTimeStart = 50;//[cell]
const int kHitTimeEnd = 150;//[cell]

  //const int kPeakSearchStart = 5;//[cell]
// const int kPeakSearchStart = 50;//[cell]
// const int kPeakSearchStart = 10;//[cell]//240421 20:17
// const int kPeakSearchEnd = 160;//[cell]//240421 20:17
const int kPeakSearchStart = 30;//[cell]
const int kPeakSearchEnd = 130;//[cell]
const int kTimingSearchRegion = 20;//[cell] before peaktime
const int kBaselineStart = -60;//[cell] +peaktime
const int kBaselineEnd = -10;//[cell] +peaktime
const int kIntegralStart = -10;//[cell] +peaktime
const int kIntegralEnd = 50;//[cell] +peaktime

  //const int kTPeakSearchRegion = 190;
  //const int kTPeakSearchStart = 5;
  //const int kTPeakSearchEnd = 195;

const int kFitNone    = 0;
const int kFitSuccess = 1;
const int kFitFailure = 2;

}; // namespace E16ANA_LGConstant

#endif
