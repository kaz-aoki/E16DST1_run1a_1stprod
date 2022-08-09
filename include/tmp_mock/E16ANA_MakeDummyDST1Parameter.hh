#ifndef E16ANA_MAKEDUMMYDST1PARAMETER_HH
#define E16ANA_MAKEDUMMYDST1PARAMETER_HH

namespace E16ANA_MakeDummyDST1Parameter {

enum {
  kSSD,
  kGTR
};
enum {
  kGTR100,
  kGTR200,
  kGTR300
};
enum {
  kGTR100x,
  kGTR100y,
  kGTR200x,
  kGTR200y,
  kGTR300x,
  kGTR300y
};
enum {
  kGTRx,
  kGTRy,
  kNumGTRTypes
};

// constant
constexpr int    kMockClusterID = 10000;
constexpr int    kSSDDeadModuleID = 108;
constexpr double kSSDDeadX[2] = {-20.6, -10.28};
constexpr double kGTRDriftLength = 3.;
constexpr double kStripSize[3] = {0.08, 0.35, 1.4};
constexpr double kGTRStripPitch[kNumGTRTypes] = {0.35, 1.4};
constexpr double kGTRADC = 1500.;
constexpr double kHBDPE = 10.;
constexpr double kHBDTime = 10.;
constexpr double kHBDFTime = 10.;
constexpr int    kHBDSize = 5.;
constexpr double kHBDEProb = 1.;
constexpr double kLGADC = 200.;
constexpr double kLGTime = 100.;

// parameter
//constexpr double kGTRDriftSigma = 0.265;

#ifndef WO_POS_SMEAR
//constexpr double kSSDXSigma = 0.1; // current analysis
//constexpr double kGTRXYSigma[3][2] = {{0.3, 1.}, {0.3, 1.}, {0.3, 1.}};
constexpr double kSSDXSigma = 0.067; // TDR2206
constexpr double kGTRXYSigma[3][2] = {{0.265, 0.626}, {0.252, 0.542}, {0.262, 0.518}};
//constexpr double kSSDXSigma = 0.03; // Nakai's simulation
//constexpr double kGTRXYSigma[3][2] = {{0.1, 0.3}, {0.1, 0.3}, {0.1, 0.3}};
//constexpr double kSSDXSigma = 0.; // w/o smear
//constexpr double kGTRXYSigma[3][2] = {{0., 0.}, {0., 0.}, {0., 0.}};
#else
constexpr double kSSDXSigma = 0.;
constexpr double kGTRXYSigma[3][2] = {{0., 0.}, {0., 0.}, {0., 0.}};
#endif

constexpr double kSSDTimeMean    =  45.;
constexpr double kSSDTimeSigma   =   5.;
//constexpr double kGTRTimeMean    = 300.; // tmp Timing0
//constexpr double kGTRTimeSigma   = 120.;
constexpr double kGTRTimeMean    = 276.45; // 220528 Timing0, from Murakami's study
constexpr double kGTRTimeSigma   = 87.55;
//constexpr double kGTRTimeMean    = 192.9; // 220528 Timing1, from Murakami's study
//constexpr double kGTRTimeSigma   = 130.0;
//constexpr double kGTRXYTimeSigma =  20.; // tmp
constexpr double kGTRXYTimeSigma = 25.12; // 220528 from Murakami's study

constexpr double kMaxTimeDiff[3] = {10., 150., 150.}; // clustering threshold

constexpr int    kSSDClusterSize  = 1;
constexpr int    kGTRxClusterSize = 3;
constexpr int    kGTRyClusterSize = 1;

}; // E16ANA_MakeDummyDST1Parameter

#endif // E16ANA_MAKEDUMMYDST1PARAMETER_HH
