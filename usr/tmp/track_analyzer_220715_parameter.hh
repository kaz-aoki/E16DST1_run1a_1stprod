#ifndef TRACK_ANALYZER_220715_PARAMETER_HH
#define TRACK_ANALYZER_220715_PARAMETER_HH

//#define TMP_SOME_Z
//#define TMP_ZX_NEAREST
#define PAIR_FIT_WO_SSD

#include "TVector3.h"

namespace track_analyzer_220715_parameter {

// Analysis basic
enum {
  kAnalyzePairFit,
  kAnalyzeNearestPoint
};
enum {
  kFitWoSSD,
  kFitWoGTR100,
  kFitWoGTR200,
  kFitWoGTR300,
  kFitAllLayers,
};
//constexpr int  kAnalyzeFlag       = kAnalyzePairFit;
constexpr int  kAnalyzeFlag       = kAnalyzeNearestPoint;
constexpr int  kFitFlag           = kFitAllLayers;
constexpr bool kForgiveSameCharge = false; // default false. for vertex search
// Event mixing
//constexpr bool kExecuteEventMixing = true;
constexpr bool kExecuteEventMixing = false;
constexpr int  kMaxPastEntries     = 1;
constexpr bool kMixOneTrackEvent   = true;
//
constexpr double   kErrorNum = -10000.;
const     TVector3 kErrorVector = {kErrorNum, kErrorNum, kErrorNum};

// Constsant
enum {
  kLR,
  kRL,
  kLL,
  kRR,
  kNumDirs
};
enum {
  kChargePlus,
  kChargeMinus,
  kNumCharges
};
enum {
  kTgtMinus,
  kTgtZero,
  kTgtPlus,
  kNumTgts
};
enum {
  kLGTypeC,
  kLGTypeB,
  kLGTypeA,
  kNumLGTypes
};
enum {
  kEE,
  kPiPi,
  kPiP,
  kKK
};
constexpr int    kNumModules           = 9; // 101 - 109
constexpr int    kNumTrackingDetectors = 7; // SSD, GTR100x, GTR100y, GTR200x, GTR200y, GTR300x, GTR300y
constexpr double kTargetZ[kNumTgts]    = {-20., 0., 20.};
constexpr int    kModuleID2013[3][11]  = {{30, 27, 24, 21, 18, 15, 12,  9, 6, 3, 0},
                                          {31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1},
                                          {32, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2}};
//const std::array<double, kNumLGTypes> kMinLGY = {388.7 + 72., 281.  + 72.,  160.7 + 72.};
//const std::array<double, kNumLGTypes> kMaxLGY = {243.2 - 72., 137.7 - 72.,    6.5 - 72.};
const std::array<double, kNumLGTypes> kMinLGY = {243.2, 137.7, 6.5};
const std::array<double, kNumLGTypes> kMaxLGY = {388.7, 281.,  160.7};
constexpr double kElectronMass  = 511.99894641e-6;
constexpr double kElectronMass2 = kElectronMass * kElectronMass;
constexpr double kPionMass      = 139.57039e-3;
constexpr double kPionMass2     = kPionMass * kPionMass;
constexpr double kProtonMass    = 938.272081e-3;
constexpr double kProtonMass2   = kProtonMass * kProtonMass;
constexpr double kKaonMass      = 493.677e-3;
constexpr double kKaonMass2     = kKaonMass * kKaonMass;

// Track selection
enum {
  kUseHBDEProb,
  kUseHBDCProb,
  kNotUseHBDProb
};
enum {
  kNoClusterDuplicationCut,
  kSSDAndGTRDuplicationCut,
  kSameChargeSSDAndGTRDuplicationCut
};
constexpr bool   kUseChi2Cut = true;
//constexpr double kMaxChi2    = 200.;
constexpr double kMaxChi2    = 100.;
constexpr bool   kUseMinMomCut = false;
constexpr double kMinMom       = 0.5;
constexpr bool   kUseMaxMomCut = false;
constexpr double kMaxMom       = 3.;
constexpr bool   kUsePosAtTargetCut = false;
constexpr double kMaxRadiusAtTarget = 5.;
constexpr bool   kUseHBDAssociationCut = true;
constexpr bool   kUseLGAssociationCut = true;
constexpr double kMaxHBDXResidual      = 25.;
constexpr double kMaxHBDYResidual      = 25.;
//constexpr double kMaxHBDXResidual      = 40.;
//constexpr double kMaxHBDYResidual      = 40.;
constexpr double kMinHBDADC            = 2.;
constexpr double kMinHBDSize           = 0.5;
constexpr int    kHBDSelection         = kNotUseHBDProb;
//constexpr bool   kUseLGAssociationCut
constexpr double kMaxLGXResidual = 200.;
constexpr double kMaxLGYResidual = 200.; 
//constexpr double kMinLGADC       = 10.;
constexpr double kMinLGADC       = 100.;
constexpr double kMinLGTime      = -1000.;
constexpr double kMaxLGTime      = 1000.;
constexpr int    kUseClulsterDuplicationCut = kSSDAndGTRDuplicationCut;
//constexpr bool   kUseHBDDuplicationCut = true;

// Pair selection
constexpr bool   kUseSSDTimeDiffCut = false;
constexpr double kMaxSSDTimeDiff = 10.;

// Pair fit parameter
const     TVector3 kInitVertex   = TVector3(0.,    0.,    0.);
const     TVector3 kVertexSigma  = TVector3(0.,    0.,    0.);
const     TVector3 kSSDSigma     = TVector3(0.067, 0.,    0.);
const     TVector3 kGTR100Sigma  = TVector3(0.265, 0.626, 0.);
const     TVector3 kGTR200Sigma  = TVector3(0.252, 0.542, 0.);
const     TVector3 kGTR300Sigma  = TVector3(0.262, 0.518, 0.);
constexpr double   kStepSize     = 5.;
constexpr int      kMaxSteps     = 80;
constexpr bool     kFixVtxXY     = false;
constexpr bool     kFixPy        = false;
constexpr bool     kFixVtxZ      = false;
constexpr int      kStrategy     = 0;
constexpr int      kMaxFuncCalls = 1.0e4;
//constexpr double   kVtxXRange[2] = {-150., 150.};
//constexpr double   kVtxYRange[2] = {-150., 150.};
//constexpr double   kVtxZRange[2] = {-150., 150.};
constexpr double   kVtxXRange[2] = {-300., 300.};
constexpr double   kVtxYRange[2] = {-300., 300.};
constexpr double   kVtxZRange[2] = {-300., 300.};

// StepTrack parameter
constexpr double kStepTrackSizeCm    = 0.1;
constexpr int    kStepTrackArraySize = 4000;

// Best target selection (parent)
enum {
  kGoodTgtNone,
  kGoodTgtMinus,
  kGoodTgtZero,
  kGoodTgtMinusZero,
  kGoodTgtPlus,
  kGoodTgtMinusPlus,
  kGoodTgtZeroPlus,
  kGoodTgtAll
};
constexpr double kMaxDiffTgtAndVtx = 3.;
constexpr double kMaxGoodTgtXDiff  = 2.;
constexpr double kMaxGoodTgtYDiff  = 2.;

// HBD and LG Projection
constexpr int kTypicalLGBlocks[3] = {0, 10, 20};
constexpr int kProjectionMaxSteps = 2000;

// Tmp
enum {
  kTmpZStatic,
  kTmpZDynamic,
  kTmpNumZMethods
};
constexpr int kTmpNumProjectionZHalf = 4;
constexpr double kTmpProjectionZWidth = 15.;

}; // track_analyzer_220715_parameter

#endif // TRACK_ANALYZER_220715_PARAMETER_HH
