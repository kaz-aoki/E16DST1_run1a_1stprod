#ifndef E16DSTN_ReStraightParameter_hh
#define E16DSTN_ReStraightParameter_hh
namespace E16DSTN_ReStraightParameter {


const TVector3 kInitPosError = {3., 3.4, 3.};
const TVector3 kInitPosErrorWire = {0.1, 3.0, 0.1};
const std::array<TVector3, 4> kSigmas = {{
//														{0.067, 0.,    0.},
														{999999, 0.,    0.},
                                          {0.265, 0.626, 0.},
                                          {0.265, 0.626, 0.},
                                          {0.265, 0.626, 0.},
	                                         }}; // 220623 TDR2206


};


#endif
