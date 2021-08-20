#ifndef E16DST_DST1CONSTANT_HH
#define E16DST_DST1CONSTANT_HH

#include <array>

namespace E16DST_DST1Constant {

const int                kInvalidValue              = -10000;
const double             kLgTimeScale               = 960. / 1000.;
const std::array<int, 6> kGtrCoincidenceStartModule = {1, 0, 0, 4, 5, 6};
const std::array<int, 6> kHbdCoincidenceStartModule = {2, 1, 0, 4, 5, 6};

enum kDetector {
  kSSD,
  kGTR100,
  kGTR200,
  kGTR300,
  kHBD,
  kLG,
  kNumDetectors,
};

enum kGtrAxis {
  kIsX,
  kIsY,
  kIsYb,
  kNumTypes,
};


const std::array<std::array<int, 11>, 3> kModuleId2020To2013 = {{{30, 27, 24, 21, 18, 15, 12, 9,  6, 3, 0},
                                                                 {31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1},
                                                                 {32, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2}}};

//const std::array<std::array<int, 9>, 3> kModuleId2020To2013_27 = {{{24, 21, 18, 15, 12, 9,  6, 3, 0},
//                                                                   {25, 22, 19, 16, 13, 10, 7, 4, 1},
//                                                                   {26, 23, 20, 17, 14, 11, 8, 5, 2}}}; // HBD, LG

}; // namespace E16DST_DST1Constant

#endif
