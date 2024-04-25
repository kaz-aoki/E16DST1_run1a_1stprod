#ifndef E16ANA_STRAIGHT_TRACK_PARAMETER_HH
#define E16ANA_STRAIGHT_TRACK_PARAMETER_HH

#include <array>

#include "TVector3.h"
#include "E16ANA_TrackConstant.hh"


namespace E16ANA_StraightTrackParameter {

#ifdef NoExist_SSD
const int kNoExistLayer = 0;
#else 
const int kNoExistLayer = -1;
#endif

#ifdef REMOVE_GTR100
const int kRemovedLayer = 1;
#elif REMOVE_GTR200
const int kRemovedLayer = 2;
#elif REMOVE_GTR300
const int kRemovedLayer = 3;
#else 
const int kRemovedLayer = -1;
#endif




constexpr bool kVtxZFixFlag = false; // 220607
//constexpr bool kVtxZFixFlag = true;
constexpr double kInitXRange[2] = {-40., 0.}; // 220607
constexpr double kInitYRange[2] = {-40., 40.}; // 220607
constexpr double kInitZRange[2] = {-60., 60.}; // 220607

#ifndef TRACK_FIND_WO_TARGET
const TVector3 kInitPosErrorWire = {10, 3.4, 3};
constexpr const std::array<double, 5> kWireXSigma = {3.0, 0.05, 0.3, 0.3, 0.3}; 
const TVector3 kInitPosError = {3., 3.4, 3.};
#else 
const TVector3 kInitPosErrorWire = {999999, 3.4, 999999};
constexpr const std::array<double, 5> kWireXSigma = {999999, 0.05, 0.3, 10.0, 0.3}; 
const TVector3 kInitPosError = {999999, 3.4, 999999};
#endif

const std::array<TVector3, 4> kSigmas = {{{0.067, 0.,    0.},
#ifndef REMOVE_GTR100
                                          {0.265, 0.626, 0.},
#else 
                                          {99999, 99999, 0.},
#endif //100
#ifndef REMOVE_GTR200
                                          {0.265, 0.626, 0.},
#else 
                                          {99999, 99999, 0.},
#endif //200

#ifndef REMOVE_GTR300
                                          {0.265, 0.626, 0.},
#else 
                                          {99999, 99999, 0.},
#endif //300
//                                          {3.0, 0.542, 0.},//for Run0c
//                                         {0.252, 0.542, 0.},//for Run0c
//                                          {10., 0.542, 0.},//for Run0d
//                                          {0.262, 0.518, 0.}
                                          }}; // 220623 TDR2206


//const std::array<TVector3, 4> kSigmas = {{{0.067, 0.,    0.},
//                                          {0.265, 0.626, 0.},
////                                          {0.252, 0.542, 0.},
//                                          {10., 0.542, 0.},//for Run0d
//                                          {0.262, 0.518, 0.}}}; // 220623 TDR2206
//
//
#ifndef TRACK_FIND_WO_TARGET
constexpr const std::array<double, 5> kXSigmaIncTgt = {3., 0.005, 1, 1, 1};
#else 
constexpr const std::array<double, 5> kXSigmaIncTgt = {999999, 0.005, 0.3, 0.3, 0.3};
#endif

constexpr std::array<double, 3> kGTRTimeDiffThreshold = {40., 60., 60.};
constexpr std::array<double, 5> kXWeight = {1. / (kXSigmaIncTgt[0] * kXSigmaIncTgt[0]),
                                            1. / (kXSigmaIncTgt[1] * kXSigmaIncTgt[1]),
                                            1. / (kXSigmaIncTgt[2] * kXSigmaIncTgt[2]),
                                            1. / (kXSigmaIncTgt[3] * kXSigmaIncTgt[3]),
                                            1. / (kXSigmaIncTgt[4] * kXSigmaIncTgt[4])};
constexpr std::array<double, 3> kYSigma = {1., 1., 1.}; // y rough fit
constexpr std::array<double, 3> kYWeight = {1. / (kYSigma[0] * kYSigma[0]),
                                            1. / (kYSigma[1] * kYSigma[1]),
                                            1. / (kYSigma[2] * kYSigma[2])};
constexpr int kMinHitsInXCluster = 2;
constexpr double kGTRYDiffThreshold = 20.; // mm


constexpr double kGTRFakeADC = 99999;

#ifndef EFFICIENCY_EVAL
  constexpr std::array<double, 3> kGTRPeakSumThresholdX = {100., 100., 100.}; // 220418 for production
  #else
    #ifdef REMOVE_GTR100
    constexpr std::array<double, 3> kGTRPeakSumThresholdX = {99998., 100., 100.}; // 220418 for production
    #elif REMOVE_GTR200
    constexpr std::array<double, 3> kGTRPeakSumThresholdX = {100., 99998., 100.}; // 220418 for production
    #elif REMOVE_GTR300
    constexpr std::array<double, 3> kGTRPeakSumThresholdX = {100., 100., 99998}; // 220418 for production
  #endif // removed gtr selection
#endif // efficiancy evaluation
    
#ifndef EFFICIENCY_EVAL
    constexpr std::array<double, 3> kGTRPeakSumThresholdY = {50., 50., 50.}; // 220418 for production
    #else
      #ifdef REMOVE_GTR100
      constexpr std::array<double, 3> kGTRPeakSumThresholdY = {99998., 50., 50.}; // 220418 for production
      #elif REMOVE_GTR200
      constexpr std::array<double, 3> kGTRPeakSumThresholdY = {50., 99998., 50.}; // 220418 for production
      #elif REMOVE_GTR300
      constexpr std::array<double, 3> kGTRPeakSumThresholdY = {50., 50., 99998}; // 220418 for production
    #endif // removed gtr selection
#endif // efficiancy evaluation







constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {30., 30.}; // x, y from previous Ks peak
constexpr std::array<double, 3> kRoughXFitCoefficientThreshold = {0.07, 0.08, 0.0015}; 
constexpr std::array<double, 2> kRoughYFitCoefficientThreshold = {20., 0.}; // coef[1] not used.

static bool ExistADCCorrelation(int layer_id, float x_adc, float y_adc) {
//  if (y_adc < 0.74 * x_adc + 600. && (y_adc > 0.74 * x_adc - 600. || y_adc > 1200.)) {
  if (y_adc < 0.74 * x_adc + 1000. && (y_adc > 0.74 * x_adc - 1000. || y_adc > 1200.)) { // 220418 for production
    return true;
  }
  return false;
}

// other
constexpr bool kExecutePairFit = false;
constexpr bool kReqHBDAssociation = true;
//constexpr double kHBDRadius = 1200.;
constexpr double kHBDRadius = 1196.;
constexpr double kMaxHBDRoughXRes = 180.;
constexpr double kMaxHBDRoughYRes = 22.5; // HBD y residual 3 sigma = 3 x 5.6 mm, 99 % threshold of residual between rough fit and RK fit = 15 mm
constexpr double kMinHBDADCForRK = 2.;

constexpr double kTrackingStepSize = 15.;
constexpr int    kTrackingMaxSteps = 80;
constexpr int    kMinuitStrategy = 0;
constexpr int    kMinuitMaxFunctionCalls = 1.0e3;
//constexpr double kTrackingStepSize = 1.; // pair fit value
//constexpr int    kTrackingMaxSteps = 400;
//constexpr int    kMinuitStrategy = 2;
//constexpr int    kMinuitMaxFunctionCalls = 1.0e4;
constexpr int    kProjectionMaxSteps = 2000;

//constexpr double kMaxChi2ForSearchAssociatedHits = 500.;
constexpr double kMaxChi2ForSearchAssociatedHits = 1.0e10;

constexpr bool   kUseChi2Cut = true;
constexpr double kMaxChi2  = 1000;




}; // E16ANA_StraightTrackParameter

#endif // E16ANA_STRAIGHT_TRACK_PARAMETER_HH
