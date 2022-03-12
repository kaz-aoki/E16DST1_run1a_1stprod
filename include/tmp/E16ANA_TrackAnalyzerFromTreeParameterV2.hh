#ifndef E16ANA_TRACKANALYZERFROMTREEPARAMETER_HH
#define E16ANA_TRACKANALYZERFROMTREEPARAMETER_HH

namespace E16ANA_TrackAnalyzerFromTreeParameter {

enum {
  kElectronFlag,
  kPionFlag,
  kBothFlag,
  kPionWoRefitFlag,
  kPionWClusterDup
};

enum {
  kLGTypeC,
  kLGTypeB,
  kLGTypeA,
  kNumLGTypes
};

const std::array<double, kNumLGTypes> kLGLocalZ = {36.7,  200.7, 356.8};
const std::array<double, kNumLGTypes> kLGMaxY   = {388.7, 281.,  160.7};
const std::array<double, kNumLGTypes> kLGMinY   = {243.2, 137.7, 6.5};

constexpr double kStepTrackStepSizeCm = 0.1;
constexpr int    kStepTrackArraySize = 4000;
constexpr double kKsMass = 493.677e-3;
constexpr double kLightSpeed = 299792458.;

}; // namespace E16ANA_TrackAnalyzerFromTreeSingleTrackParameter

namespace E16ANA_TrackAnalyzerFromTreeSingleTrackParameter {

constexpr double kChiSquareThreshold          = 20;
//constexpr double kLGADCThreshold              = 50.;
constexpr double kSSDResidualThreshold        = 1.;
constexpr double kGTR100xResidualThreshold    = 2.;
constexpr double kGTR100yResidualThreshold    = 2.;
constexpr double kGTR200xResidualThreshold    = 2.5;
constexpr double kGTR200yResidualThreshold    = 4.;
constexpr double kGTR300xResidualThreshold    = 4.;
constexpr double kGTR300yResidualThreshold    = 4.;
constexpr double kTargetXThreshold            = 5.;
constexpr double kTargetYThreshold            = 5.;
constexpr double kHBDADCThreshold             = 0.5;
constexpr double kHBDResidualThreshold        = 50.;
constexpr double kLGHitXResidualThreshold     = 70.;
constexpr double kLGClusterXResidualThreshold = 80.;

constexpr double kHBDXMean[4]  = {-3.2,  2.3, -5.,   1.3};
//constexpr double kHBDXSigma[4] = {22.3, 23.,  18.7, 15.8};
constexpr double kHBDXSigma[4] = {22.3 * 2, 23. * 2,  18.7 * 2, 15.8 * 2};
constexpr double kHBDYMean[4]  = {-0.6, -0.9, -0.2, -0.1};
//constexpr double kHBDYSigma[4] = {22.6, 18.4, 12.5, 10.6};
constexpr double kHBDYSigma[4] = {22.6 * 2, 18.4 * 2, 12.5 * 2, 10.6 * 2};

}; // namespace E16ANA_TrackAnalyzerFromTreeParameter

namespace E16ANA_TrackAnalyzerFromTreePionSingleTrackParameter {

//const     TVector3 kInitPosError = {1.5, 1.7, 0};
const     TVector3 kPreInitPosError = {3., 3.4, 0};
//constexpr double   kChiSquareThreshold = 1.0e9; // Ks
constexpr double   kChiSquareThreshold = 2000.; // Ks chi2 from initial position : (50 / 3)^ 2 + (50 / 3.4) ^2 ~494
constexpr double   kLGADCThreshold = 30.; // Ks, maximum

}; // namespace E16ANA_TrackAnalyzerFromTreeSinglePionTrackParameter

namespace E16ANA_TrackAnalyzerFromTreePairTrackParameter {

enum {
  kCalcEEMassFlag,
  kCalcPiPiMassFlag,
  kCalcPiPMassFlag,
  kCalcKKMassFlag,
  kNumCalcMassFlags
};

constexpr double kElectronMass  = 511.99894641e-6;
constexpr double kElectronMass2 = kElectronMass * kElectronMass;
constexpr double kPionMass      = 139.57039e-3;
constexpr double kPionMass2     = kPionMass * kPionMass;
constexpr double kProtonMass    = 938.272081e-3;
constexpr double kProtonMass2   = kProtonMass * kProtonMass;
constexpr double kKaonMass      = 493.677e-3;
constexpr double kKaonMass2     = kKaonMass * kKaonMass;

//constexpr double   kStepTrackSizeCm = ;
//constexpr int      kStepTrackArraySize = ;
constexpr double   kStepSize           = 1.;
constexpr int      kMaxSteps           = 400;
const     TVector3 kVertexSigma        = {3., 3., 0.};
const     TVector3 kSSDSigma           = {0.1, 0., 0.};
const     TVector3 kGTR100Sigma        = {0.3, 1., 0.};
const     TVector3 kGTR200Sigma        = {0.3, 1., 0.};
const     TVector3 kGTR300Sigma        = {0.3, 1., 0.};
constexpr bool     kVertexXyFixFlag    = false;
constexpr bool     kPyFixFlag          = false;
constexpr bool     kVertexZFixFlag     = true;
//constexpr bool     kVertexZFixFlag     = false;
constexpr int      kMinuitStrategy     = 2;
constexpr int      kMaxFunctionCalls   = 1.0e4;
constexpr double   kChiSquareThreshold = 100.;
//constexpr double   kSSDTime            = 43.5;
//constexpr double   kSSDTimeWidth       =  7.5;
constexpr double   kSSDTimeDiff        = 5.;
constexpr double   kLGTimeDiff         = 10.;
constexpr double   kLGTime             = 93.5;
constexpr double   kLGTimeWidth        = 11.5;
constexpr double   kTriggerLGTimeWidth = 10.;

constexpr bool     kVertexZFixFlagPion = false;

}; // namespace E16ANA_TrackAnalyzerFromTreePairTrackParameter

#endif // E16ANA_TRACKANALYZERFROMTREEPARAMETER_HH
