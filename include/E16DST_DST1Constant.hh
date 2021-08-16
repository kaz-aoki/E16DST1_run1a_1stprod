#ifndef E16DST_DST1CONSTANT_HH
#define E16DST_DST1CONSTANT_HH

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
};

enum kGtrAxis {
  kIsX,
  kIsY,
  kIsYb,
};

}; // namespace E16DST_DST1Constant

#endif
