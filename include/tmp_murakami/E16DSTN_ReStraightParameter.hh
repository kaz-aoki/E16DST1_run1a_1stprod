#ifndef E16DSTN_ReStraightParameter_hh
#define E16DSTN_ReStraightParameter_hh
namespace E16DSTN_ReStraightParameter {


constexpr double kchi2_threshold = 9999999;
const TVector3 kInitPosError = {3., 3.4, 3.};
const TVector3 kInitPosErrorWire = {0.05, 3.0, 0.05};
const std::array<TVector3, 4> kSigmas = {{
														{0.067, 0.,    0.},
														{0, 0, 0.},
														{0, 0, 0.},
														{0, 0, 0.}
////                                          {0.265, 0.626, 0.},
////                                          {0.265, 0.626, 0.},
//                                          {99999, 99999, 0.},
//                                          {99999, 99999, 0.},
//                                          {0.265, 0.626, 0.}
	                                         }}; // 220623 TDR2206


};


#endif
