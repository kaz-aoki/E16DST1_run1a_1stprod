#ifndef TMP_FIT_MOCK_PAIR_220616_PARAMETER_HH
#define TMP_FIT_MOCK_PAIR_220616_PARAMETER_HH

#include "TVector3.h"

namespace tmp_fit_mock_pair_220616_parameter {

//constexpr double kTargetZ[3] = {-20., 0., 20.};
constexpr std::array<std::array<int, 11>, 3> kModuleID2020To2013 = {{{30, 27, 24, 21, 18, 15, 12, 9,  6, 3, 0},
                                                                     {31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1},
                                                                     {32, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2}}};
static int ModuleID2020To2013(int _module_id) { return kModuleID2020To2013[_module_id / 100][_module_id % 100]; }

//const TVector3 kVertexSigma = TVector3(3., 3., 0.);
const TVector3 kVertexSigma = TVector3(0., 0., 0.); // for comparing
//const TVector3 kSSDSigma    = TVector3(0.1, 0., 0.); // for comparing
//const TVector3 kGTR100Sigma = TVector3(0.3, 1., 0.); // for comparing
//const TVector3 kGTR200Sigma = TVector3(0.3, 1., 0.); // for comparing
//const TVector3 kGTR300Sigma = TVector3(0.3, 1., 0.); // for comparing
//const TVector3 kVertexSigma = TVector3(1.5, 1.5, 0.); // simlation value
const TVector3 kSSDSigma    = TVector3(0.067, 0.,    0.); // TDR2106
const TVector3 kGTR100Sigma = TVector3(0.265, 0.626, 0.);
const TVector3 kGTR200Sigma = TVector3(0.252, 0.542, 0.);
const TVector3 kGTR300Sigma = TVector3(0.262, 0.518, 0.);
//const TVector3 kSSDSigma    = TVector3(0.03, 0.,  0.); // TDR1611
//const TVector3 kGTR100Sigma = TVector3(0.1,  0.3, 0.);
//const TVector3 kGTR200Sigma = TVector3(0.1,  0.3, 0.);
//const TVector3 kGTR300Sigma = TVector3(0.1,  0.3, 0.);
//constexpr double kStepSize     = 1.;
//constexpr int    kMaxSteps     = 400;
constexpr double kStepSize     = 5.; // current DST1
constexpr int    kMaxSteps     = 80; // current DST1
constexpr bool   kFixVtxXY     = false;
constexpr bool   kFixPy        = false;
constexpr bool   kFixVtxZ      = true;
//constexpr int    kStrategy     = 2;
//constexpr double kMaxFuncCalls = 1.0e4;
constexpr int    kStrategy     = 0; // current DST1
constexpr double kMaxFuncCalls = 1.0e3; // current DST1
//constexpr double kVtxXRange[2] = {-10., 10.};
//constexpr double kVtxYRange[2] = {-10., 10.};
//constexpr double kVtxZRange[2] = {-30., 30.};
constexpr double kVtxXRange[2] = {-40., 40.};
constexpr double kVtxYRange[2] = {-40., 40.};
constexpr double kVtxZRange[2] = {-40., 40.};

};

#endif // TMP_FIT_MOCK_PAIR_220616_PARAMETER_HH
