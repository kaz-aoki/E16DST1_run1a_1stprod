#ifndef E16DST_DST1CONSTANT_HH
#define E16DST_DST1CONSTANT_HH

#include <array>

namespace E16DST_DST1Constant {

enum kDetector {
  kSSD,
  kGTR100,
  kGTR200,
  kGTR300,
  kHBD,
  kLG,
  kNumDetectors,
  kNumTriggerOffset = 3,
};

enum kGtrAxis {
  kIsX,
  kIsY,
  kIsYb,
  kNumAxisTypes,
};

enum kTriggerType {
  kTrackCorreration,
  kLRTrack,
  k1Track,
  kMultiTrack,
  kClock,
  kNim,
  kNumTriggerTypes,
};

// Common
const int                kInvalidValue              = -10000;
const std::array<std::array<int, 11>, 3> kModuleId2020To2013 = {{{30, 27, 24, 21, 18, 15, 12, 9,  6, 3, 0},
                                                                 {31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1},
                                                                 {32, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2}}};

// LG
const double             kLgTimeScale                 = 960. / 1000.;
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

// Trigger
const int                kMrgDelayOrderNs             = 4;
const int                kMrgTransmitCycleNs          = 64;
const std::array<int, 6> kGtrCoincidenceStartModule   = {1, 0, 0, 4, 5, 6};
const std::array<int, 6> kHbdCoincidenceStartModule   = {2, 1, 0, 4, 5, 6};
const int                kNumGtr300YSignalChannel     = 216;
const double             kGtr300ModuleSize            = 600;
const double             kHbdModuleSize               = 600;
const int                kNumHbdTriggerChannelOneAxis = 6;

}; // namespace E16DST_DST1Constant

#endif
