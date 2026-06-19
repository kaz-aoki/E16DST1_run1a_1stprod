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
  //constexpr bool kVtxZFixFlag = false; // 220607
constexpr bool kVtxZFixFlag = true;
//constexpr double kInitXRange[2] = {-40., 40.}; // 220607
//constexpr double kInitYRange[2] = {-40., 40.}; // 220607
//constexpr double kInitZRange[2] = {-40., 40.}; // 220607
constexpr double kInitXRange[2] = {-20., 20.}; // 220607
constexpr double kInitYRange[2] = {-25., 25.}; // 220607
constexpr double kInitZRange[2] = {-80., 80.}; // 220607
//const std::array<TVector3, 4> kSigmas = {{{0.1, 0., 0.}, {0.3, 1., 0.}, {0.3, 1., 0.}, {0.3, 1., 0.}}};
const std::array<TVector3, 4> kSigmas = {{{0.035, 0.,    0.},
                                          {0.18, 0.38, 0.},
                                          {0.18, 0.38, 0.},
                                          {0.18, 0.38, 0.}}}; // 220623 TDR2206
  const TVector3 kInitPosError = {2.5, 1.5, 0.};
  //const TVector3 kInitPosError = {3.5, 2.5, 0.};
  //const TVector3 kInitPosError = {0., 0., 0.}; // 220607
//const std::array<TVector3, 4> kSigmas = {{{0.001, 0., 0.}, {0.001, 0.001, 0.}, {0.001, 0.001, 0.}, {0.001, 0.001, 0.}}};
//const TVector3 kInitPosError = {2., 2., 0.};
//constexpr std::array<double, 3> kGTRTimeDiffThreshold = {45., 70., 70.};
  //constexpr std::array<double, 3> kGTRTimeDiffThreshold = {65., 110., 120.};
//constexpr const std::array<double, 5> kXSigma = {20., 0.05, 0.1, 0.1, 0.1};
constexpr std::array<double, 3> kGTRTimeDiffThreshold = {150., 160, 170.};
//    constexpr std::array<double, 3> kGTRTimeDiffThreshold = {85., 100., 110.};
#ifndef TRACK_FIND_WO_TARGET
  //constexpr const std::array<double, 5> kXSigma = {3.5, 0.05, 0.3, 0.3, 0.3}; // 220413 for statistics check
  constexpr const std::array<double, 5> kXSigma = {3.5, 0.05, 0.3, 0.3, 0.3}; // 220413 for statistics check
constexpr std::array<double, 5> kXWeight = {1. / (kXSigma[0] * kXSigma[0]),
                                            1. / (kXSigma[1] * kXSigma[1]),
                                            1. / (kXSigma[2] * kXSigma[2]),
                                            1. / (kXSigma[3] * kXSigma[3]),
                                            1. / (kXSigma[4] * kXSigma[4])};
#else // TRACK_FIND_WO_TARGET
//constexpr const std::array<double, E16ANA_TrackConstant::kNumTrackingLayers> kXSigma = {0.025, 0.1, 0.1, 0.1};
constexpr const std::array<double, E16ANA_TrackConstant::kNumTrackingLayers> kXSigma = {0.25, 1., 1., 1.};
constexpr std::array<double, 5> kXWeight = {1. / (kXSigma[0] * kXSigma[0]),
                                            1. / (kXSigma[1] * kXSigma[1]),
                                            1. / (kXSigma[2] * kXSigma[2]),
                                            1. / (kXSigma[3] * kXSigma[3])};
#endif // TRACK_FIND_WO_TARGET
constexpr std::array<double, 4> kYSigma = {2, 1., 1., 1.}; // y rough fit
constexpr std::array<double, 4> kYWeight = {1. / (kYSigma[0] * kYSigma[0]),
                                            1. / (kYSigma[1] * kYSigma[1]),
                                            1. / (kYSigma[2] * kYSigma[2]),
                                            1. / (kYSigma[3] * kYSigma[3])};
  //constexpr int kMinHitsInXCluster = 2;
constexpr int kMinHitsInXCluster = 2;
constexpr double kGTRYDiffThreshold = 30.; // mm
  //constexpr std::array<double, 3> kGTRPeakSumThresholdX = {120., 100., 100.}; // 220418 for production
  //  constexpr std::array<double, 3> kGTRPeakSumThresholdX = {150., 140., 100.}; // 220418 for production
  //constexpr std::array<double, 3> kGTRPeakSumThresholdX = {150., 145., 140.}; // 220418 for production
constexpr std::array<double, 3> kGTRPeakSumThresholdX = {120., 105., 105.}; // 220418 for production
constexpr std::array<double, 3> kGTRMaxTotThresholdX  = {70. , 70. , 70.}; // 220418 for production
  //constexpr std::array<double, 3> kGTRMaxTotThresholdX  = {100. , 100. , 90.}; // 220418 for production
constexpr std::array<double, 3> kGTRMaxRtX            = {20. , 20. ,  20.}; // 220418 for production
constexpr std::array<double, 3> kGTRedX               = {200.,200., 200}; // 220418 for production

  //constexpr std::array<double, 3> kGTRPeakSumThresholdY = {115, 110., 105.}; // 220418 for production
  //  constexpr std::array<double, 3> kGTRPeakSumThresholdY = {135, 120., 105.}; // 220418 for production
  //constexpr std::array<double, 3> kGTRPeakSumThresholdY = {145, 140., 140.}; // 220418 for production
constexpr std::array<double, 3> kGTRPeakSumThresholdY = {120, 115, 115.}; // 220418 for production
  //constexpr std::array<double, 3> kGTRMaxTotThresholdY  = { 95,  80., 75. }; // 220418 for production
constexpr std::array<double, 3> kGTRMaxTotThresholdY  = {70,  70., 70. }; // 220418 for production
constexpr std::array<double, 3> kGTRMaxRtY            = { 25, 20. , 20}; // 220418 for production
constexpr std::array<double, 3> kGTRedY               = {200.,200., 200}; // 220418 for production
constexpr std::array<double, 3> kGTRstY1              = {95,  95., 95.}; // 220418 for production
constexpr std::array<double, 3> kGTRstY2              = {360, 370., 390.}; // 220418 for production
constexpr std::array<double, 3> kGTRstX1              = {92.5 ,  92.5 ,  92.5}; // 220418 for production
constexpr std::array<double, 3> kGTRstX2              = {390., 390 , 410.}; // 220418 for production

  
constexpr double kLrpara[3][3] ={{0.140,-0.12,0.12} ,{0.14,0.085,0.45} ,{0.129,0.033,0.078}};
constexpr double kRrpara[3][3] ={{0.134,-0.11,0.465},{0.145,0.074,0.22},{0.14,0.076,0.183}};



#ifdef TRACK_FIND_WO_TARGET
//constexpr std::array<std::array<double, 2>, 6> kXCurveCorrWindow = {{{0.2, 0.4}, {0.3, 0.5}, {0.4, 0.6}, {0.6, 0.75}, {0.7, 1.05}, {0.9, 1.3}}};
constexpr std::array<std::array<double, 2>, 6> kXCurveCorrWindow = {{{0., 0.5}, {0.1, 0.7}, {0.2, 0.8}, {0.2, 1.2}, {0.3, 1.2}, {0.9, 1.3}}};
constexpr double kInitPosBackRadius = 10.;
#endif // TRACK_FIND_WO_TARGET
#ifndef TRACK_FIND_WO_TARGET
//constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {200., 20.}; // x, y
//constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {90., 20.}; // x, y // 220413 for statistics check, 220418 for production
//constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {45., 6.5};
constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {35., 5.};
constexpr double ReRoughFitChi = 55;  

constexpr std::array<double, 3> kRoughXFitCoefficientThreshold = {25., 0., 0.0013};
//constexpr std::array<double, 3> kRoughXFitCoefficientThreshold = {100., 0., 0.01}; // 220413 for statistics check
constexpr std::array<double, 2> kRoughYFitCoefficientThreshold = {25., 0.}; // coef[1] not used.
#else // TRACK_FIND_WO_TARGET
// constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {10., 10.}; // x, y
// constexpr std::array<double, 3> kRoughXFitCoefficientThreshold = {0.1, 0.1, 0.002};
// constexpr std::array<double, 2> kRoughYFitCoefficientThreshold = {40., 0.}; // coef[1] not used.
//constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {3., 0.2}; // x, y from sim
//constexpr std::array<double, 3> kRoughXFitCoefficientThreshold = {0.06, 0.1, 0.002};
//constexpr std::array<double, 2> kRoughYFitCoefficientThreshold = {20., 0.}; // coef[1] not used.
constexpr std::array<double, 2> kRoughFitChiSquareThreshold = {4., 10.}; // x, y from previous Ks peak
constexpr std::array<double, 3> kRoughXFitCoefficientThreshold = {0.07, 0.08, 0.0015};
constexpr std::array<double, 2> kRoughYFitCoefficientThreshold = {20., 0.}; // coef[1] not used.
#endif // TRACK_FIND_WO_TARGET

static bool ExistADCCorrelation(int layer_id, float x_adc, float y_adc) {
//  if (y_adc < 0.74 * x_adc + 600. && (y_adc > 0.74 * x_adc - 600. || y_adc > 1200.)) {
  //if (y_adc < 0.74 * x_adc + 1000. && (y_adc > 0.74 * x_adc - 1000. || y_adc > 1200.)) { // 220418 for production
    return true;
    //}
    //return false;
}

// other
constexpr bool kExecutePairFit = false;
constexpr bool kReqHBDAssociation = true;
//constexpr double kHBDRadius = 1200.;
constexpr double kHBDRadius = 1196.;
#ifndef TRACK_FIND_WO_TARGET
constexpr double kMaxHBDRoughXRes = 95.;
#else // TRACK_FIND_WO_TARGET
//constexpr double kMaxHBDRoughXRes = 80.;
constexpr double kMaxHBDRoughXRes = 95.;
#endif // TRACK_FIND_WO_TARGET
constexpr double kMaxHBDRoughYRes = 22; // HBD y residual 3 sigma = 3 x 5.6 mm, 99 % threshold of residual between rough fit and RK fit = 15 mm
constexpr double kMinHBDADCForRK = 6.0;

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
