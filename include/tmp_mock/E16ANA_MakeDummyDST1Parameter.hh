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
constexpr double kGTRDriftSigma = 0.265;

constexpr double kSSDXSigma = 0.1;
constexpr double kGTRXYSigma[3][2] = {{0.3, 1.}, {0.3, 1.}, {0.3, 1.}};

constexpr double kSSDTimeMean    =  45.;
constexpr double kGTRTimeMean    = 300.;
constexpr double kSSDTimeSigma   =   5.;
constexpr double kGTRTimeSigma   = 120.;
constexpr double kGTRXYTimeSigma =  20.;

}; // E16ANA_MakeDummyDST1Parameter

#endif // E16ANA_MAKEDUMMYDST1PARAMETER_HH
