#ifndef E16ANA_TRACK_PARAMETER_HH
#define E16ANA_TRACK_PARAMETER_HH

#include <array>

#include "TVector3.h"
#include "E16ANA_TrackConstant.hh"

namespace E16ANA_TrackParameter {

//// pion
//const std::array<TVector3, 4> kSigmas = {{{0.1, 0., 0.}, {0.3, 1., 0.}, {0.3, 1., 0.}, {0.3, 1., 0.}}};
//const TVector3 kInitPosError = {3., 3.4, 0.};
////constexpr std::array<double, 3> kGTRTimeDiffThreshold = {40., 60., 120.};
//constexpr std::array<double, 3> kGTRTimeDiffThreshold = {40., 60., 60.}; // 20220324 traditional parameter
////constexpr const std::array<double, 5> kXSigma = {100., 0.05, 0.1, 0.1, 0.1}; // x rough fit
////constexpr const std::array<double, 5> kXSigma = {50., 0.05, 0.1, 0.1, 0.1}; // x rough fit 220324
//constexpr const std::array<double, 5> kXSigma = {3., 0.05, 0.1, 0.1, 0.1}; // x rough fit 220416
//constexpr std::array<double, 5> kXWeight = {1. / (kXSigma[0] * kXSigma[0]),
//                                            1. / (kXSigma[1] * kXSigma[1]),
//                                            1. / (kXSigma[2] * kXSigma[2]),
//                                            1. / (kXSigma[3] * kXSigma[3]),
//                                            1. / (kXSigma[4] * kXSigma[4])};
//constexpr std::array<double, 3> kYSigma = {1., 1., 1.}; // y rough fit
//constexpr std::array<double, 3> kYWeight = {1. / (kYSigma[0] * kYSigma[0]),
//                                            1. / (kYSigma[1] * kYSigma[1]),
//                                            1. / (kYSigma[2] * kYSigma[2])};
//constexpr int kMinHitsInXCluster = 2;
//constexpr double kGTRYDiffThreshold = 20.; // mm
////constexpr std::array<double, 3> kGTRPeakSumThresholdX = {80., 150., 250.};
//constexpr std::array<double, 3> kGTRPeakSumThresholdX = {50., 100., 200.}; // 220323
//constexpr double kGTRPeakSumThresholdY = 50.;
////constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {200., 20.}; // x, y
//constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {500., 100.}; // x, y, 220330
////constexpr std::array<double, 3> kRoughXFitCoefficientThreshold = {100., 0., 0.001};
//constexpr std::array<double, 3> kRoughXFitCoefficientThreshold = {100., 0., 0.005}; // 220330
////constexpr std::array<double, 2> kRoughYFitCoefficientThreshold = {50., 0.}; // coef[1] not used.
//constexpr std::array<double, 2> kRoughYFitCoefficientThreshold = {30., 0.}; // coef[1] not used. 220324
//
//static bool ExistADCCorrelation(int layer_id, float x_adc, float y_adc) {
////  if (y_adc < 0.74 * x_adc + 600. && (y_adc > 0.74 * x_adc - 600. || y_adc > 1200.)) {
////  if (y_adc < 0.74 * x_adc + 800. && (y_adc > 0.74 * x_adc - 800. || y_adc > 1200.)) {
////  if (y_adc < 0.74 * x_adc + 1000. && (y_adc > 0.74 * x_adc - 1000. || y_adc > 1200.)) { // 220323
//  if (y_adc < 0.74 * x_adc + 1500. && (y_adc > 0.74 * x_adc - 1500. || y_adc > 1200.)) { // 220323
//    return true;
//  }
//  return false;
//}

// electron
constexpr bool kVtxZFixFlag = false; // 220607
constexpr double kInitXRange[2] = {-40., 40.}; // 220607
constexpr double kInitYRange[2] = {-40., 40.}; // 220607
constexpr double kInitZRange[2] = {-40., 40.}; // 220607
//const std::array<TVector3, 4> kSigmas = {{{0.1, 0., 0.}, {0.3, 1., 0.}, {0.3, 1., 0.}, {0.3, 1., 0.}}};
const std::array<TVector3, 4> kSigmas = {{{0.067, 0.,    0.},
                                          {0.265, 0.626, 0.},
                                          {0.252, 0.542, 0.},
                                          {0.262, 0.518, 0.}}}; // 220623 TDR2206
//const TVector3 kInitPosError = {3., 3.4, 0.};
const TVector3 kInitPosError = {0., 0., 0.}; // 220607
//const std::array<TVector3, 4> kSigmas = {{{0.001, 0., 0.}, {0.001, 0.001, 0.}, {0.001, 0.001, 0.}, {0.001, 0.001, 0.}}};
//const TVector3 kInitPosError = {2., 2., 0.};
constexpr std::array<double, 3> kGTRTimeDiffThreshold = {40., 60., 60.};
//constexpr const std::array<double, 5> kXSigma = {20., 0.05, 0.1, 0.1, 0.1};
constexpr const std::array<double, 5> kXSigma = {3., 0.05, 0.1, 0.1, 0.1}; // 220413 for statistics check
constexpr std::array<double, 5> kXWeight = {1. / (kXSigma[0] * kXSigma[0]),
                                            1. / (kXSigma[1] * kXSigma[1]),
                                            1. / (kXSigma[2] * kXSigma[2]),
                                            1. / (kXSigma[3] * kXSigma[3]),
                                            1. / (kXSigma[4] * kXSigma[4])};
constexpr std::array<double, 3> kYSigma = {1., 1., 1.}; // y rough fit
constexpr std::array<double, 3> kYWeight = {1. / (kYSigma[0] * kYSigma[0]),
                                            1. / (kYSigma[1] * kYSigma[1]),
                                            1. / (kYSigma[2] * kYSigma[2])};
constexpr int kMinHitsInXCluster = 2;
//constexpr int kMinHitsInXCluster = 1;
constexpr double kGTRYDiffThreshold = 20.; // mm
//constexpr std::array<double, 3> kGTRPeakSumThresholdX = {80., 150., 250.};
constexpr std::array<double, 3> kGTRPeakSumThresholdX = {100., 100., 100.}; // 220418 for production
////constexpr std::array<double, 3> kGTRPeakSumThresholdX = {200., 220., 220.}; // Ozawa modification 220618
////constexpr std::array<double, 3> kGTRPeakSumThresholdX = {200., 220., 60.}; // Ozawa modification 220620
//constexpr std::array<double, 3> kGTRPeakSumThresholdX = {200., 220., 100.}; // Ozawa modification 220620-2 Ozawa's final value?
////constexpr std::array<double, 3> kGTRPeakSumThresholdX = {200., 220., 130.}; // Ozawa modification 220620-3
constexpr double kGTRPeakSumThresholdY = 50.;
//constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {200., 20.}; // x, y
constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {500., 20.}; // x, y // 220413 for statistics check, 220418 for production
constexpr std::array<double, 3> kRoughXFitCoefficientThreshold = {25., 0., 0.001};
//constexpr std::array<double, 3> kRoughXFitCoefficientThreshold = {100., 0., 0.01}; // 220413 for statistics check
constexpr std::array<double, 2> kRoughYFitCoefficientThreshold = {25., 0.}; // coef[1] not used.

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
constexpr double kHBDRadius = 1200.;
constexpr double kMaxHBDRoughXRes = 180.;
constexpr double kMaxHBDRoughYRes = 22.5; // HBD y residual 3 sigma = 3 x 5.6 mm, 99 % threshold of residual between rough fit and RK fit = 15 mm
constexpr double kMinHBDADCForRK = 2.;

constexpr double kTrackingStepSize = 5.;
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

}; // E16ANA_TrackParameter

#endif // E16ANA_TRACK_PARAMETER_HH
