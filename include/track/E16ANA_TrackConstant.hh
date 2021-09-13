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

constexpr int kNumTrackingLayers = 4;
constexpr int kNumDetectorLayers = 6;
constexpr int kNumRemainingLayers = kNumDetectorLayers - kNumTrackingLayers;
constexpr int kNumTargets = 3;
constexpr int kNumModules = 8;
constexpr std::array<int, kNumModules> kModuleIDs = {101, 102, 103, 104, 106, 107, 108, 109};
constexpr std::array<double, kNumTargets> kTargetZ = {-20., 0., 20.};
constexpr std::array<std::array<int, 11>, 3> kModuleID2020To2013 = {{{30, 27, 24, 21, 18, 15, 12, 9,  6, 3, 0},
                                                                 {31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1},
                                                                 {32, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2}}};
}; // E16ANA_TrackConstant

#endif // E16ANA_TRACK_CONSTANT_HH
