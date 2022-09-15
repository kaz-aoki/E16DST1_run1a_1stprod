#ifndef E16ANA_TRACK_CONSTANT_HH
#define E16ANA_TRACK_CONSTANT_HH

#include <array>

namespace E16ANA_TrackConstant {

enum {
  kSSD,
  kGTR100,
  kGTR200,
  kGTR300,
  kHBD,
  kLG,
  kLG0 = 5,
  kLG1 = 6,
  kLG2 = 7,
#ifndef TRACK_EFF_CHECK
  kNumDetectorLayers = 8
#else
  kLGVD = 8,
  kNumDetectorLayers = 9
#endif
};

#ifdef TRACK_EFF_CHECK
enum { // x search
  kRej100xADC,
  kRej100xSize,
  kRej200xADC,
  kRej200xSize,
  kRej300xADC,
  kRej300xSize,
  kRejXFit,
  kNumXSearchRejectPoints
};
enum { // x fit
  kRejTgt0Curve,
  kRejTgt1Curve,
  kRejTgt2Curve,
  kRejTgt0XChi2,
  kRejTgt1XChi2,
  kRejTgt2XChi2,
  kRejTgt0XCoef0,
  kRejTgt1XCoef0,
  kRejTgt2XCoef0,
  kRejTgt0XCoef2,
  kRejTgt1XCoef2,
  kRejTgt2XCoef2,
};
enum { // y search & fit
  kRej300yADC,
  kRej200yADC,
  kRej100yADC,
  kRejYSubtract,
  kRejYChi2,
  kRejYCoef0,
  kNumYSearchRejectPoints
};
enum { // x - y match
//  kRej100YYb,
  kRej100XYModule,
  kRej200XYModule,
  kRej300XYModule,
  kRej100XYTime,
  kRej200XYTime,
  kRej300XYTime,
  kRej100XYADC,
  kRej200XYADC,
  kRej300XYADC,
  kNumXYMatchRejectPoints
};
enum { // total
  kRejXSearch,
  kTotalRejXFit,
  kRejYSearch,
  kRejYCand,
//  kTotalRej100YYb,
  kRejXYMatch,
  kNumRejectPoints
};
#endif // TRACK_EFF_CHECK

const std::array<std::string, kNumDetectorLayers> kDetectorName = {"SSD", "GTR100", "GTR200", "GTR300", "HBD", "LG c-type", "LG b-type", "LG a-type"};

constexpr int kNumTrackingLayers = 4;
//constexpr int kNumDetectorLayers = 6;
constexpr int kNumLGLayers = 3;
//constexpr int kNumDetectorLayers = 8; // SSD, GTR x 3, HBD, LG x 3
constexpr int kNumRemainingLayers = kNumDetectorLayers - kNumTrackingLayers;
constexpr int kNumClusters = 7; // SSD, GTR x 2 x 3
constexpr int kNumTargets = 3;
constexpr int kNumModules = 8;
constexpr int kNumFullModulesWidth = 11;
constexpr int kNumFullModulesHeight = 3;
constexpr int kNumFullModules = kNumFullModulesWidth * kNumFullModulesHeight;
constexpr std::array<int, kNumModules> kModuleIDs = {101, 102, 103, 104, 106, 107, 108, 109};
//constexpr std::array<double, kNumTargets> kTargetZ = {-20., 0., 20.};
constexpr std::array<double, kNumTargets> kTargetZ = {-40., 0., 40.};
constexpr std::array<int, kNumFullModules> kModuleID2013To2020 = {{10, 110, 210, 9, 109, 209, 8, 108, 208, 7, 107, 207,
                                                                    6, 106, 206, 5, 105, 205, 4, 104, 204, 3, 103, 203,
                                                                    2, 102, 202, 1, 101, 201, 0, 100, 200}};
constexpr std::array<std::array<int, kNumFullModulesWidth>, kNumFullModulesHeight> kModuleID2020To2013 = {{{30, 27, 24, 21, 18, 15, 12, 9,  6, 3, 0},
                                                                                                           {31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1},
                                                                                                           {32, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2}}};
static int ModuleID2013To2020(int _module_id) { return kModuleID2013To2020[_module_id]; }
static int ModuleID2020To2013(int _module_id) { return kModuleID2020To2013[_module_id / 100][_module_id % 100]; }
static int ModuleID2013To2020_27(int _module_id) { return kModuleID2013To2020[_module_id + 3]; }
static int ModuleID2020To2013_27(int _module_id) { return kModuleID2020To2013[_module_id / 100][_module_id % 100 + 1]; }
}; // E16ANA_TrackConstant

#endif // E16ANA_TRACK_CONSTANT_HH
