#ifndef E16ANA_TRACKANALYZERFROMTREEPARAMETER_HH
#define E16ANA_TRACKANALYZERFROMTREEPARAMETER_HH

namespace E16ANA_TrackAnalyzerFromTreeParameter {

enum {
  kElectronFlag,
  kPionFlag,
  kBothFlag
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
constexpr int    kStepTrackArraySize = 1000;
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

}; // namespace E16ANA_TrackAnalyzerFromTreeParameter

namespace E16ANA_TrackAnalyzerFromTreePionSingleTrackParameter {

//const     TVector3 kInitPosError = {1.5, 1.7, 0};
const     TVector3 kInitPosError = {3., 3.4, 0};
constexpr double   kChiSquareThreshold = 1.0e9; // Ks
constexpr double   kLGADCThreshold = 30.; // Ks, maximum

}; // namespace E16ANA_TrackAnalyzerFromTreeSinglePionTrackParameter

namespace E16ANA_TrackAnalyzerFromTreePairTrackParameter {

enum {
  kCalcEEMassFlag,
  kCalcPiPiMassFlag,
  kCalcPiPMassFlag
};

constexpr double kElectronMass = 511.99894641e-6;
constexpr double kElectronMass2 = kElectronMass * kElectronMass;
constexpr double kPionMass = 139.57039e-3;
constexpr double kPionMass2 = kPionMass * kPionMass;
constexpr double kProtonMass = 938.272081e-3;
constexpr double kProtonMass2 = kProtonMass * kProtonMass;

//constexpr double   kStepTrackSizeCm = ;
//constexpr int      kStepTrackArraySize = ;
constexpr double   kStepSize = 1.;
constexpr int      kMaxSteps = 400;
const     TVector3 kVertexSigma = {3., 3., 0.};
const     TVector3 kSSDSigma = {0.1, 0., 0.};
const     TVector3 kGTR100Sigma = {0.3, 1., 0.};
const     TVector3 kGTR200Sigma = {0.3, 1., 0.};
const     TVector3 kGTR300Sigma = {0.3, 1., 0.};
constexpr bool     kVertexXyFixFlag = false;
constexpr bool     kPyFixFlag = false;
//constexpr bool     kVertexZFixFlag = true;
constexpr bool     kVertexZFixFlag = false;
constexpr int      kMinuitStrategy = 2;
constexpr int      kMaxFunctionCalls = 1.0e4;
constexpr double   kChiSquareThreshold = 100.;

constexpr bool     kVertexZFixFlagPion = false;

}; // namespace E16ANA_TrackAnalyzerFromTreePairTrackParameter

#endif // E16ANA_TRACKANALYZERFROMTREEPARAMETER_HH
