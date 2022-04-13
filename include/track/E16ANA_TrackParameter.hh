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
//constexpr const std::array<double, 5> kXSigma = {50., 0.05, 0.1, 0.1, 0.1}; // x rough fit 220324
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
const std::array<TVector3, 4> kSigmas = {{{0.1, 0., 0.}, {0.3, 1., 0.}, {0.3, 1., 0.}, {0.3, 1., 0.}}};
const TVector3 kInitPosError = {3., 3.4, 0.};
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
constexpr double kGTRYDiffThreshold = 20.; // mm
constexpr std::array<double, 3> kGTRPeakSumThresholdX = {80., 150., 250.};
constexpr double kGTRPeakSumThresholdY = 50.;
//constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {200., 20.}; // x, y
constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {500., 20.}; // x, y // 220413 for statistics check
//constexpr std::array<double, 3> kRoughXFitCoefficientThreshold = {25., 0., 0.001};
constexpr std::array<double, 3> kRoughXFitCoefficientThreshold = {100., 0., 0.01}; // 220413 for statistics check
constexpr std::array<double, 2> kRoughYFitCoefficientThreshold = {25., 0.}; // coef[1] not used.

static bool ExistADCCorrelation(int layer_id, float x_adc, float y_adc) {
  if (y_adc < 0.74 * x_adc + 600. && (y_adc > 0.74 * x_adc - 600. || y_adc > 1200.)) {
    return true;
  }
  return false;
}

constexpr bool kExecutePairFit = false;
}; // E16ANA_TrackParameter

#endif // E16ANA_TRACK_PARAMETER_HH
