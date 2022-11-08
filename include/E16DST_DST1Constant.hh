#ifndef E16DST_DST1CONSTANT_HH
#define E16DST_DST1CONSTANT_HH

#include <array>

#include "TVector3.h"

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

enum kRecordType {
  kPhysics,
  kScaler,
  kSpillStart,
  kSpillEnd,
  kNumRecordTypes,
};

// Common
constexpr int kInvalidValue = -10000;
const TVector3 kInvalidVector = {-10000, -10000, -10000};
const std::array<std::array<int, 11>, 3> kModuleId2020To2013 = {{{30, 27, 24, 21, 18, 15, 12, 9,  6, 3, 0},
                                                                 {31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1},
                                                                 {32, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2}}};

//GTR
constexpr double gtr_strip_pitch_x = 0.35;
constexpr double gtr_strip_pitch_y = 1.40;
const std::array<int, 3> nstrips_x = {288, 576, 864};
const std::array<int, 3> nstrips_y = {72, 144, 216};
constexpr int n_gtr_layers = 3;
constexpr int n_gtr_modules = 8;
constexpr int n_gtr_asd_chs = 24;
constexpr int gtr_module_ids[n_gtr_modules] = {101, 102, 103, 104, 106, 107, 108, 109};
constexpr int nstrips_100x = 288;
constexpr int nstrips_100y = 72;
constexpr int nstrips_200x = 576;
constexpr int nstrips_200y = 144;
constexpr int nstrips_300x = 864;
constexpr int nstrips_300y = 216;

// data
constexpr int kReserve = 1024;
//constexpr int kHeaderSize            = 1024;
//constexpr int kNumDetectorComponents = 16; // must be even number

// tmp
const double kGTRDetectPlaneOffset  = 3. * 0.5 + 2.2 * 3.; // 8.1
//const double kGTRLorentzLengthV2[3] = {7.5 * 0.35, -5.5 * 0.35, -3. * 0.35}; // tmp. old param
//const double kGTRLorentzLengthV2[3] = {3.18, -2.4, -1.15}; // 1800 V, GTR module ID: 106. Morino param
//const double kGTRLorentzLengthV2[3] = {7.5 * 0.35 * 1.28, -5.5 * 0.35 * 1.5, -3. * 0.35 * 1.45}; // 1800 V, 106. Ichikawa param
const double kGTRLorentzLengthV2[3] = {7.5 * 0.35 * 1.11, -5.5 * 0.35 * 1.17, -3. * 0.35 * 1.09}; // 1500 V, 106. Morino param modified by Ichikawa param
const double kGTRLorentzAngleV2[3]  = {TMath::ATan(kGTRLorentzLengthV2[0] / kGTRDetectPlaneOffset),
                                       TMath::ATan(kGTRLorentzLengthV2[1] / kGTRDetectPlaneOffset),
                                       TMath::ATan(kGTRLorentzLengthV2[2] / kGTRDetectPlaneOffset)}; // {0.313, -0.233, -0.129}; // tmp

}; // namespace E16DST_DST1Constant

#endif // E16DST_DST1CONSTANT_HH
