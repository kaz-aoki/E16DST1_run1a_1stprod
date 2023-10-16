#ifndef  E16DSTN_StraightParameter_HH
#define E16DSTN_StraightParameter_HH

namespace E16DSTN_StraightParameter {

constexpr int kNumTrackingDetectors = 7; //ssd, gtr100x/y, gtr200x/y, gtr300x/y

//trakcing selection
enum {
	kNoClusterDuplicationCut,
	kSSDAndGTRDuplicationCut
};

constexpr bool   kUseChi2Cut = true;
constexpr double kMaxChi2 = 100;
constexpr bool   kUsePosAtTargetCut = false;
constexpr double kMaxRadiusAtTarget = 5;
constexpr int    kUseClusterDuplicationCut = kSSDAndGTRDuplicationCut;

};
#endif
