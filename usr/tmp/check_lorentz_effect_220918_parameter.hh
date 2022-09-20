#ifndef CHECK_LORENTZ_EFFECT_220918_PARAMETER_HH
#define CHECK_LORENTZ_EFFECT_220918_PARAMETER_HH

#include <array>

namespace check_lorentz_effect_220918_parameter {

enum {
  kTargetMinus,
  kTargetZero,
  kTargetPlus,
  kNumTargets
};
constexpr int kModuleID2020To2013[11] = {31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1};
constexpr double kMaxChi2 = 10.;
constexpr double kMaxHBDXResidual = 25.;
constexpr double kMaxHBDYResidual = 25.;
constexpr int    kNumDivides = 8;
constexpr int    kNumDivides2 = kNumDivides  * kNumDivides;
constexpr int    kNumDivides3 = kNumDivides2 * kNumDivides;
constexpr double kLorentzRegion[2] = {-1., 1.};
constexpr double kLorentzOffset[3] = {7.5 * 0.35, -5.5 * 0.35, -3. * 0.35};
const     TVector3 kInitPosError = {0.2, 0.2, 0.};
const     TVector3 kGTRSigma[3] = {TVector3(0.265, 0.626, 0.), TVector3(0.252, 0.542, 0.), TVector3(0.262, 0.518, 0.)};
constexpr double   kStepSize = 5.;
constexpr int      kMaxSteps = 80.;
constexpr bool     kFixVertexXY = true;
constexpr bool     kFixPy       = false;
constexpr bool     kFixVertexZ  = true;
constexpr int      kMinuitStrategy = 0;
constexpr int      kMaxMinuitFunctionCalls = 1.0e3;
constexpr double   kInitXRange[2] = {-50., 50.};
constexpr double   kInitYRange[2] = {-50., 50.};
constexpr double   kInitZRange[2] = {-50., 50.};

}; // check_lorentz_effect_220918_parameter

#endif // CHECK_LORENTZ_EFFECT_220918_PARAMETER_HH
