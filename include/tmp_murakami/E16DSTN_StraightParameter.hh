#ifndef  E16DSTN_StraightParameter_HH
#define E16DSTN_StraightParameter_HH

#include <array>
#include <TVector3.h>


//#define CHECK_100
#define CHECK_200
//#define CHECK_300

//#define CALIB
//#define COG_INFO
#define DRIFT_V
//#define TDC_INFO

namespace E16DSTN_StraightParameter {

static constexpr std::string_view GeometryFile {"/ccj/u/E16/database/geometry/v2/geometry_Run0c_211006b_ymorino_220122.dat"};
//static constexpr std::string_view GeometryFile {"/ccj/u/ymorino/geometry_mod3.dat"};
constexpr int kNumTrackingDetectors = 7; //ssd, gtr100x/y, gtr200x/y, gtr300x/y

//trakcing selection
enum {
	kNoClusterDuplicationCut,
	kSSDAndGTRDuplicationCut
};


constexpr bool   kUseChi2Cut = true;
constexpr double kMaxChi2 = 10;
constexpr double kWireZRegion = 2;//plus minus distance
constexpr bool   kUsePosAtTargetCut = false;
constexpr double kMaxRadiusAtTarget = 5;
constexpr int    kUseClusterDuplicationCut = kSSDAndGTRDuplicationCut;

#ifdef CHECK_100
const std::array<TVector3, 4> kSigmas = {{{0.067, 0.,    0.},
//                                          {0.265, 0.626, 0.},
                                          {99999., 0.542, 0.},//for Run0d
                                         {0.252, 0.542, 0.},//for Run0c
                                          {0.262, 0.518, 0.}}}; // 220623 TDR2206
#endif

#ifdef CHECK_200
const std::array<TVector3, 4> kSigmas = {{{0.067, 0.,    0.},
                                          {0.265, 0.626, 0.},
                                          {99999., 0.542, 0.},//for Run0d
//                                         {0.252, 0.542, 0.},//for Run0c
                                          {0.262, 0.518, 0.}}}; // 220623 TDR2206
#endif


#ifdef CHECK_300
const std::array<TVector3, 4> kSigmas = {{{0.067, 0.,    0.},
                                          {0.265, 0.626, 0.},
                                         {0.252, 0.542, 0.},//for Run0c
                                          {99999., 0.542, 0.}}};//for Run0d
#endif




//                                          {99999., 0.542, 0.}}};//for Run0d
const TVector3 kInitPosError     = {3., 3.4, 3.0};
const TVector3 kInitPosErrorWire = {0.1, 3.4, 0.1};//For Position Correction
//const TVector3 kInitPosErrorWire = {99999, 99999, 99999};//For Position Correction
const double kUpTargetgz = -40;
const double kDownTargetgz = 40;
const double kUpTargetgx   = 20-0.3;
const double kDownTargetgx = 20+0.2;

constexpr double kMaxSSDClusterN = 30;

constexpr bool kExecutePairFit = false;
constexpr bool kReqHBDAssociation = true;
//constexpr double kHBDRadius = 1200.;
constexpr double kHBDRadius = 1196.;
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



};
#endif
