#ifndef E16ANA_TRACK_CONSTANT_HH
#define E16ANA_TRACK_CONSTANT_HH

#include <array>

namespace E16ANA_TrackConstant {

enum {
  kSSD,
  kGTR100,
  kGTR200,
  kGTR300,
  kHBD,
  kLG
};

const int kNumTrackingLayers = 4;
const int kNumDetectorLayers = 6;
const int kNumTargets = 3;
const std::array<std::array<int, 11>, 3> kModuleID2020To2013 = {{{30, 27, 24, 21, 18, 15, 12, 9,  6, 3, 0},
                                                                 {31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1},
                                                                 {32, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2}}};

}; // E16ANA_TrackConstant

#endif // E16ANA_TRACK_CONSTANT_HH
