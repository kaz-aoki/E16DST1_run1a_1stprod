#ifndef E16ANA_TRACKANALYZERFROMTREEPARAMETER_HH
#define E16ANA_TRACKANALYZERFROMTREEPARAMETER_HH

namespace E16ANA_TrackAnalyzerFromTreeSingleTrackParameter {

const double kChiSquareThreshold = 1.0e9;
const double kSSDResidualThreshold = 1.;
const double kGTR100xResidualThreshold = 2.;
const double kGTR100yResidualThreshold = 2.;
const double kGTR200xResidualThreshold = 2.5;
const double kGTR200yResidualThreshold = 4.;
const double kGTR300xResidualThreshold = 4.;
const double kGTR300yResidualThreshold = 4.;
const double kNearTargetSquareThreshold = 100.;

}; // namespace E16ANA_TrackAnalyzerFromTreeParameter

namespace E16ANA_TrackAnalyzerFromTreePairTrackParameter {

const double kElectronMass = 511.99894641e-6;
const double kElectronMass2 = kElectronMass * kElectronMass;

//const double   kStepTrackSizeCm = ;
//const int      kStepTrackArraySize = ;
const double   kStepSize = 1.;
const int      kMaxSteps = 400;
const TVector3 kVertexSigma = {3., 3., 0.};
const TVector3 kSSDSigma = {0.1, 0., 0.};
const TVector3 kGTR100Sigma = {0.3, 1., 0.};
const TVector3 kGTR200Sigma = {0.3, 1., 0.};
const TVector3 kGTR300Sigma = {0.3, 1., 0.};
const bool     kVertexXyFixFlag = false;
const bool     kPyFixFlag = false;
const bool     kVertexZFixFlag = true;
const int      kMinuitStrategy = 2;
const int      kMaxFunctionCalls = 1.0e4;
const double   kChiSquareThreshold = 100.;

}; // namespace E16ANA_TrackAnalyzerFromTreePairTrackParameter

#endif // E16ANA_TRACKANALYZERFROMTREEPARAMETER_HH
