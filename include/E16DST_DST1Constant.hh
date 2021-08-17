#ifndef E16DST_DST1CONSTANT_HH
#define E16DST_DST1CONSTANT_HH

namespace E16DST_DST1Constant {

const int                kInvalidValue              = -10000;
const double             kLgTimeScale               = 960. / 1000.;
const std::array<int, 6> kGtrCoincidenceStartModule = {1, 0, 0, 4, 5, 6};
const std::array<int, 6> kHbdCoincidenceStartModule = {2, 1, 0, 4, 5, 6};

enum kDetector {
  kSSD,
  kGTR100,
  kGTR200,
  kGTR300,
  kHBD,
  kLG,
};

enum kGtrAxis {
  kIsX,
  kIsY,
  kIsYb,
};

const int kLgHitThreshold = 20;//[mV]
const int kLgHitTimingStart = 50;//[ns]
const int kLgHitTimingEnd = 150;//[ns]

const int kLgPeakSearchStart = 5;//[cell]
const int kLgPeakSearchEnd = 200;//[cell]
const int kLgTimingSearchRegion = 20;//[cell] before peaktime
const int kLgBaselineStart = -100;//[cell] +peaktime
const int kLgBaselineEnd = -50;//[cell] +peaktime
const int kLgIntegralStart = -20;//[cell] +peaktime
const int kLgIntegralEnd = 50;//[cell] +peaktime

}; // namespace E16DST_DST1Constant

#endif
