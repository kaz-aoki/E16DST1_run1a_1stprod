#ifndef E16DST_DST1CONSTANT_HH
#define E16DST_DST1CONSTANT_HH

#include <array>

namespace E16DST_DST1Constant {

enum kDetector {
  kSSD,
  kGTR,
  kHBD,
  kLG,
  kNumDetectors,
  kNumTriggerOffset = 1,
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

enum kRecordType {
  kDetector,
  kTrigger,
  kScaler,
  kSpillStart,
  kSpillEnd,
  kNumRecordTypes,
};

// Common
const int                kInvalidValue              = -10000;
const std::array<std::array<int, 11>, 3> kModuleId2020To2013 = {{{30, 27, 24, 21, 18, 15, 12, 9,  6, 3, 0},
                                                                 {31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1},
                                                                 {32, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2}}};

//GTR
const double gtr_strip_pitch_x = 0.35;
const double gtr_strip_pitch_y = 1.40;
const std::array<int, 3> nstrips_x = {288, 576, 864};
const std::array<int, 3> nstrips_y = {72, 144, 216};
//const int nstrips_100y = 72;
////const int nstrips_200x = 576;
//const int nstrips_200y = 144;
//const int nstrips_300x = 864;
//const int nstrips_300y = 216;

// LG
const double kLgTimeScale = 960. / 1000.;

// Trigger
const int                kMrgDelayOrderNs             = 4;
const int                kMrgTransmitCycleNs          = 64;
const std::array<int, 6> kGtrCoincidenceStartModule   = {1, 0, 0, 4, 5, 6};
const std::array<int, 6> kHbdCoincidenceStartModule   = {2, 1, 0, 4, 5, 6};
const int                kNumGtr300YSignalChannel     = 216;
const double             kGtr300ModuleSize            = 600;
const double             kHbdModuleSize               = 600;
const int                kNumHbdTriggerChannelOneAxis = 6;

// data
const int kHeaderSize            = 1024;
const int kNumDetectorComponents = 16; // must be even number

}; // namespace E16DST_DST1Constant

#endif