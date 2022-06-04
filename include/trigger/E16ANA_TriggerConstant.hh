#ifndef E16ANA_TRIGGER_CONSTANT_HH
#define E16ANA_TRIGGER_CONSTANT_HH

#include <array>

namespace E16ANA_TriggerConstant {

enum kTriggerType {
  kTrackCorreration,
  kLRTrack,
  k1Track,
  kMultiTrack,
  kClock,
  kNim,
  kNumTriggerTypes,
};

constexpr int                   kMRGDelayOrderNs             = 4;
constexpr int                   kMRGTransmitCycleNs          = 64;
const     std::array<int, 6>    kGTRCoincidenceStartModule   = {1, 0, 0, 4, 5, 6};
const     std::array<int, 6>    kHBDCoincidenceStartModule   = {2, 1, 0, 4, 5, 6};
constexpr int                   kNumGTR300YSignalChannel     = 216;
constexpr int                   kNumGTRASDs                  = 24;
constexpr double                kGTR300ModuleSize            = 302.4;
const     std::array<double, 2> kHBDModuleSize               = {610.4318, 605.8972};
constexpr int                   kNumHBDTriggerChannelOneAxis = 6;

}; // E16ANA_TriggerConstant

#endif // #E16ANA_TRIGGER_CONSTANT_HH
