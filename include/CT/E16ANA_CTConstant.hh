#ifndef E16ANA_CTCONSTANT_HH
#define E16ANA_CTCONSTANT_HH

#include "E16DST_Constant.hh"
#include <array>
#include <TGraph.h>

namespace E16ANA_CTConstant {

const double             kTimeScale               = 960. / 1000.;

// const int kHitThreshold = 5;//[mV]
// const int kHitTimeStart = 50;//[cell]
// const int kHitTimeEnd = 150;//[cell]

// const int kPeakSearchStart = 5;//[cell]
const int kPeakSearchStart = 30;//[cell]
const int kPeakSearchEnd = E16DST_Constant::NSamplesCT;//[cell]
const int kTimingSearchRegion = 20;//[cell] before peaktime
const int kBaselineStart = -65;//[cell] +peaktime
const int kBaselineEnd = -15;//[cell] +peaktime
const int kIntegralStart = -15;//[cell] +peaktime
const int kIntegralEnd = 10;//[cell] +peaktime

}; // namespace E16ANA_CTConstant

#endif
