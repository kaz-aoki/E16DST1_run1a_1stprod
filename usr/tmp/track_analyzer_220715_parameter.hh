#ifndef TRACK_ANALYZER_220715_PARAMETER_HH
#define TRACK_ANALYZER_220715_PARAMETER_HH

#include "TVector3.h"

namespace track_analyzer_220715_parameter {

enum {
  kAnalyzePairFit,
  kAnalyzeNearestPoint
};
constexpr int kAnalyzeFlag = kAnalyzeNearestPoint;

// Constsant
enum {
  kLR,
  kRL,
  kLL,
  kRR,
  kNumDirs
};
enum {
  kTgtMinus,
  kTgtZero,
  kTgtPlus,
  kNumTgts
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
  kSameChargeSSDAndGTRDuplicationCut,
  kHBDDuplicationCut
};
constexpr bool   kUseChi2Cut = true;
constexpr double kMaxChi2    = 300.;
constexpr bool   kUseMinMomCut = true;
constexpr double kMinMom       = 0.5;
constexpr bool   kUseMaxMomCut = true;
constexpr double kMaxMom       = 3.;
constexpr bool   kUseHBDAssociationCut = true;
constexpr double kMaxHBDXResidual      = 25.;
constexpr double kMaxHBDYResidual      = 25.;
constexpr double kMinHBDADC            = 7.;
constexpr double kMinHBDSize           = 1.5;
constexpr int    kHBDSelection         = kNotUseHBDProb;
//constexpr bool   kUseLGAssociationCut
constexpr int    kUseClulsterDuplicationCut = kSSDAndGTRDuplicationCut;

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
constexpr double   kVtxXRange[2] = {-60., 60.};
constexpr double   kVtxYRange[2] = {-60., 60.};
constexpr double   kVtxZRange[2] = {-30., 60.};

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

// EventMixing
constexpr bool kExecuteEventMixing = true;
constexpr int  kMaxPastEntries     = 10;

}; // track_analyzer_220715_parameter

#endif // TRACK_ANALYZER_220715_PARAMETER_HH
