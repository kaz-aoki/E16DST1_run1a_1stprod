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
  kSTS,
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
constexpr int n_gtr_axes = 2;
constexpr int gtr_module_ids[n_gtr_modules] = {101, 102, 103, 104, 106, 107, 108, 109};
constexpr int nstrips_100x = 288;
constexpr int nstrips_100y = 72;
constexpr int nstrips_200x = 576;
constexpr int nstrips_200y = 144;
constexpr int nstrips_300x = 864;
constexpr int nstrips_300y = 216;
constexpr int n_gtr_samples = 24;

// data
constexpr int kReserve = 1024;
//constexpr int kHeaderSize            = 1024;
//constexpr int kNumDetectorComponents = 16; // must be even number

// GTR Lorentz angle correction
constexpr double kGTRDetectPlaneOffset      = 3. * 0.5 + 2.2 * 3.; // 8.1
//constexpr double kGTRGEMLorentzLength[3]    = {7.5 * 0.35, -5.5 * 0.35, -3. * 0.35}; // tmp. old param
//constexpr double kGTRGEMLorentzLength[3]    = {3.18, -2.4, -1.15}; // 1800 V, GTR module ID: 106. Morino param
//constexpr double kGTRGEMLorentzLength[3]    = {7.5 * 0.35 * 1.28, -5.5 * 0.35 * 1.5, -3. * 0.35 * 1.45}; // 1800 V, 106. Ichikawa param
//constexpr double kGTRGEMLorentzLength[3]    = {7.5 * 0.35 * 1.11, -5.5 * 0.35 * 1.17, -3. * 0.35 * 1.09}; // 1500 V, 106. Morino param modified by Ichikawa param. same as later column
//constexpr double kGTRGEMLorentzLength[3]    = {3.18 * 0.91*1.75, -2.4 * 0.94*1.75, -1.15*1.75}; // v0

//constexpr double kGTRGEMLorentzLength[3]    = {3.18 * 0.91*1.5, -2.4 * 0.94*1.5, -1.15*1.5}; // v1 tempbest
 // for normal magnetic field 
  
//  constexpr double kGTRGEMLorentzLength[9][3]    = {{4.341, -3.384, -1.725},      //101
//						    {4.341, -3.384, -1.725},      //102
//						    {4.341, -3.384, -1.725},      //103
//						    {4.341, -3.384, -1.725},      //104
//						    {4.341, -3.384, -1.725},      //105
//						    {4.481, -3.134, -1.955},      //106
//						    {3.461, -2.004, -1.505},      //107
//						    {4.341, -3.384, -1.725},      //108
//						   {4.341, -3.384, -1.725}};     //109
  
//for neg fiedl
 constexpr double kGTRGEMLorentzLength[9][3]    = {{-4.341, 3.384, 1.725},      //101
						    {-4.341, 3.384, 1.725},      //102
						    {-4.341, 3.384, 1.725},      //103
						    {-4.341, 3.384, 1.725},      //104
						    {-4.341, 3.384, 1.725},      //105
						    {-4.481, 3.134, 1.955},      //106
						    {-3.461, 2.004, 1.505},      //107
						    {-4.341, 3.384, 1.725},      //108
						   {-4.341, 3.384, 1.725}};     //109
  //constexpr double kGTRGEMLorentzLength[3]    = {3.18 * 0.91*1.25, -2.4 * 0.94*1.25, -1.15*1.25}; // v2
  //constexpr double kGTRGEMLorentzLength[3]    = {3.18 * 0.91, -2.4 * 0.94, -1.15}; // v3
  //constexpr double kGTRGEMLorentzLength[3]    = {3.18 * 0.91*0.75, -2.4 * 0.94*0.75, -1.15*0.75}; // v4
  //constexpr double kGTRGEMLorentzLength[3]    = {3.18 * 0.91*0.5, -2.4 * 0.94*0.5, -1.15*0.5}; // v5

//constexpr double kGTRLorentzAngle[3]      = {TMath::ATan(kGTRLorentzLength[0] / kGTRDetectPlaneOffset),
//                                           TMath::ATan(kGTRLorentzLength[1] / kGTRDetectPlaneOffset),
//                                           TMath::ATan(kGTRLorentzLength[2] / kGTRDetectPlaneOffset)}; // {0.313, -0.233, -0.129}; // tmp
//constexpr double kGTRDriftLorentzAngle[3]   = {0.35, -0.75, -0.14}; // 1,800 V, GTR Module ID: 106. Morino parameter
constexpr double kGTRDriftLorentzAngle[3]   = {0.35 * 0.91, -0.75 * 0.94, -0.14}; // 1,800 V, GTR Module ID: 106. Morino parameter. modified by Ichikawa study
constexpr double kGTRDriftLorentzCosine[3]  = {std::cos(kGTRDriftLorentzAngle[0]), std::cos(kGTRDriftLorentzAngle[1]), std::cos(kGTRDriftLorentzAngle[2])};
constexpr double kGTRDriftLorentzTangent[3] = {std::tan(kGTRDriftLorentzAngle[0]), std::tan(kGTRDriftLorentzAngle[1]), std::tan(kGTRDriftLorentzAngle[2])};
constexpr double kGTRDriftVelocity = 8e-3;
constexpr double kGTRTDCCenter[3] = {328, 328., 428.};

}; // namespace E16DST_DST1Constant

#endif // E16DST_DST1CONSTANT_HH
