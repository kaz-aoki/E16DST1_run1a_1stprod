#ifndef CHECK_LORENTZ_EFFECT_220918_PARAMETER_HH
#define CHECK_LORENTZ_EFFECT_220918_PARAMETER_HH

//#define TMP
#define VECTOR_MESON
//#define KS
//#define ONE_TRACK
//#define REVERSE_MAGFIELD
//#define DRIFT_1800
//#define DRIFT_1500
//#define DRIFT_1200

#include <array>

namespace check_lorentz_effect_220918_parameter {

enum {
  kChargePlus,
  kChargeMinus
};

enum {
  kTargetMinus,
  kTargetZero,
  kTargetPlus,
  kNumTargets
};
enum {
  kFitWoTarget,
  kFitWoSSD
};
constexpr int kModuleID2020To2013[11] = {31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1};
constexpr double kMaxChi2 = 10.;
#ifndef VECTOR_MESON
constexpr bool   kHBDForward = true;
#else
constexpr bool   kHBDForward = false;
#endif
constexpr double kMaxHBDXResidual = 25.;
constexpr double kMaxHBDYResidual = 25.;
constexpr double kTargetZ[kNumTargets] = {-20., 0., 20.};
#ifdef TMP
constexpr double kTargetZRange[2][3][2] = {{{-30., -10.}, {-10., 10.}, {10., 30.}},
                                           {{-30., -10.}, {-10., 10.}, {10., 30.}}};
#endif
#ifdef VECTOR_MESON
constexpr double kTargetZRange[2][3][2] = {{{-25., -5.}, {-5., 15.}, {15., 30.}},
                                           {{-20., 0.}, {0., 15.}, {20., 35.}}};
#endif
#ifdef KS
constexpr double kTargetZRange[3][2] = {{-25., -5.}, {-5., 15.}, {15., 35.}}; // Ks run
#endif
#ifdef ONE_TRACK
constexpr double kTargetZRange[3][2] = {{-20., 0.}, {0., 15.}, {20., 30.}}; // 30322 (1 track)
#endif
#ifdef REVERSE_MAGFIELD
#ifdef DRIFT_1800
constexpr double kTargetZRange[2][3][2] = {{{-30., -15.}, {-10., 5.}, {10., 25.}},
                                           {{-30., -10.}, {-10., 5.}, {10., 25.}}}; // 30464 (reverse magfield mesh: 1800 V)
#endif
#ifdef DRIFT_1500
constexpr double kTargetZRange[2][3][2] = {{{-30., -15.}, {-10., 5.}, {10., 25.}},
                                           {{-30., -10.}, {-10., 10.}, {10., 30.}}}; // charge, target, min/max
#endif
#ifdef DRIFT_1200
constexpr double kTargetZRange[2][3][2] = {{{-30., -10.}, {-10., 10.}, {10., 30.}}; // charge, target, min/max
#endif
#endif
constexpr int    kNumDivides = 5;
constexpr int    kNumDivides2 = kNumDivides  * kNumDivides;
constexpr int    kNumDivides3 = kNumDivides2 * kNumDivides;
#ifndef REVERSE_MAGFIELD
constexpr double kLorentzOffset[3] = {7.5 * 0.35, -5.5 * 0.35, -3. * 0.35};
#else
constexpr double kLorentzOffset[3] = {-7.5 * 0.35, 5.5 * 0.35, 3. * 0.35}; // reverse magfield
#endif
constexpr double kParamOffset[3] = {0., 0., 0.};
constexpr double kParamRange[3]  = {0.4, 1., 1.};
const     TVector3 kInitPosError = {0.2, 0.2, 0.};
const     TVector3 kSSDSigma = TVector3(0.067, 0., 0.);
const     TVector3 kGTRSigma[3] = {TVector3(0.265, 0.626, 0.), TVector3(0.252, 0.542, 0.), TVector3(0.262, 0.518, 0.)};
constexpr double   kStepSize = 5.;
constexpr int      kMaxSteps = 80.;
constexpr bool     kFixVertexXY[2]         = {true, true};
constexpr bool     kFixPy                  = false;
constexpr bool     kFixVertexZ[2]          = {false, true};
constexpr int      kMinuitStrategy         = 0;
constexpr int      kMaxMinuitFunctionCalls = 1.0e3;
constexpr double   kInitXRange[2] = {-50., 50.};
constexpr double   kInitYRange[2] = {-50., 50.};
constexpr double   kInitZRange[2] = {-50., 50.};
//constexpr double   kStepTrackStepSize  = 0.1;
//constexpr int      kStepTrackArraySize = 1000;

}; // check_lorentz_effect_220918_parameter

#endif // CHECK_LORENTZ_EFFECT_220918_PARAMETER_HH
