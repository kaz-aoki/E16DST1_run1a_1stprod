#ifndef StraightTrackAnalyzerV0_h
#define StraightTrackAnalyzerV0_h 1

#include "OnlineGTRUtility.h"
#include "E16ANA_GTRAnalyzer2.h"
#include "E16ANA_GTRPedestal.h"
#include "E16ANA_GTRStripAnalyzer.h"
#include "E16DST_DST0.hh"
#include "E16ANA_SSDAnalyzer.h"
#include "E16ANA_SSDStripAnalyzer.h"
//#include "E16ANA_SSDPedestal.h"
#include "E16DST_DST1.hh"

#include <memory>
#include <TH1D.h>
#include <TH2D.h>
#include <TString.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
//#include <E16ANA_Geometry.hh>
#include <E16ANA_GeometryV2.hh>
#include <functional>
#include <algorithm>
const int gtrmaxhit = 20;
const double th_chi2 = 100;//chisquare threshold 
const double th_chi2_first = 100;//chisquare threshold 
const double th_chi2_second = 100;//chisquare threshold 
const double th_chi2_third = 100;//chisquare threshold 
const double th_chi2_y = 100;//chisquare threshold 
const int min_ip_gap = 100;// this should be caluculated precisely
const double Agtr[] = {1.295, 0.882, 0.469, 0, -0.469, -0.882, -1.295};


enum {
   n_layers = 3,//gtr layer
	n_samples = 4,//  gtr*3
};


    inline int ModuleID_2013to2020_33(int id )
    {
    const int moduleID_2013to2020_33[33] = {
        10, 110, 210, 9, 109, 209, 8, 108, 208, 7, 107, 207, 6, 106, 206,
        5, 105, 205,
        4,  104, 204, 3, 103, 203, 2, 102, 202, 1, 101, 201, 0, 100, 200 };
    return  moduleID_2013to2020_33[ id ];
    }
    inline int ModuleID_2020to2013_33(int id ){//GTR,SSD
    const int module_id_kawama33[3][11] = {
        {30, 27, 24, 21, 18, 15, 12, 9, 6, 3, 0},
        {31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1},
        {32, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2}};
    return module_id_kawama33[ id / 100][id % 100];
    }
    inline int ModuleID_2013to2020_27( int id ){// //LG,HBD
    const int moduleID_2013to2020_27[27] = {
        9, 109, 209, 8, 108, 208, 7, 107, 207,  6, 106, 206,
        5, 105, 205,
        4, 104, 204, 3, 103, 203, 2, 102, 202,  1, 101, 201};
    return  moduleID_2013to2020_27[ id ];
    }
    inline int ModuleID_2020to2013_27(int id ){//LG,HBD
    const int module_id_kawama27[3][9] = {
        {24, 21, 18, 15, 12, 9, 6, 3, 0 },
        {25, 22, 19, 16, 13, 10, 7, 4, 1},
        {26, 23, 20, 17, 14, 11, 8, 5, 2}};
    int id2=(id %100) -1;
    return module_id_kawama27[ id / 100][ id2 ];
}


class E16ANA_XZTrackCandidate {
public:
    E16ANA_XZTrackCandidate() {
//        SetInvalid();
    };
    ~E16ANA_XZTrackCandidate() {};
    void SetModuleID(int m){
        module_id = m;
    }
    void SetInvalid(){
        module_id = -100;
        chi2 = kInvalidValue;
        tgt_z = kInvalidValue;
    }
    void SetXHit100(E16DST_DST1GTRCluster *xhit){xcluster100 = xhit;}
    void SetXHit200(E16DST_DST1GTRCluster *xhit){xcluster200 = xhit;}
    void SetXHit300(E16DST_DST1GTRCluster *xhit){xcluster300 = xhit;}
    void SetXHitSSD(E16DST_DST1SSDCluster *xhit){xclusterssd = xhit;}
    void SetXHit100(E16ANA_GTRAnalyzedStripHit *xhit){xhit100 = xhit;}
    void SetXHit200(E16ANA_GTRAnalyzedStripHit *xhit){xhit200 = xhit;}
    void SetXHit300(E16ANA_GTRAnalyzedStripHit *xhit){xhit300 = xhit;}
    void SetXHitSSD(E16ANA_SSDAnalyzedStripHit *shit){xhitssd = shit;}
    void SetFitSample100(TVector2 _fit_sample_100){fit_sample100 = _fit_sample_100;}
    void SetFitSample200(TVector2 _fit_sample_200){fit_sample200 = _fit_sample_200;}
    void SetFitSample300(TVector2 _fit_sample_300){fit_sample300  = _fit_sample_300;}
	void SetFitPtOnGTR100(TVector2 tv){fitpt_ongtr100 = tv;}
	void SetFitPtOnGTR200(TVector2 tv){fitpt_ongtr200 = tv;}
	void SetFitPtOnGTR300(TVector2 tv){fitpt_ongtr300 = tv;}	
	TVector2 FitPtOnGTR100(){return fitpt_ongtr100;}
	TVector2 FitPtOnGTR200(){return fitpt_ongtr200;}
	TVector2 FitPtOnGTR300(){return fitpt_ongtr300;}
    TVector2 GetFitSample100(){return fit_sample100;}
    TVector2 GetFitSample200(){return fit_sample200;}
    TVector2 GetFitSample300(){return fit_sample300;}
    void SetChi2(double _chi2){chi2 = _chi2;}
	void SetChi2ExSSD(double _chi2){chi2_ex_ssd = _chi2;}	
	void SetChi2Ex100(double _chi2){chi2_ex_100 = _chi2;}	
	void SetChi2Ex200(double _chi2){chi2_ex_200 = _chi2;}	
	void SetChi2Ex300(double _chi2){chi2_ex_300 = _chi2;		}	
    void SetTgtZ(double z){tgt_z = z;}
	void SetDistance(double d){distance = d;}
	void SetFitRes100(TVector2 res){fit_res100 = res;}
	void SetFitRes200(TVector2 res){fit_res200 = res;}
	void SetFitRes300(TVector2 res){fit_res300 = res;}
	void SetFitResSSD(TVector2 res){fit_resssd = res;}
	TVector2 GetFitRes100(){return fit_res100;}
	TVector2 GetFitRes200(){return fit_res200;}
	TVector2 GetFitRes300(){return fit_res300;}
	TVector2 GetFitResSSD(){return fit_resssd;}
	void SetFitA(double a ){fit_a = a;}
	void SetFitB(double b ){fit_b = b;}
	double GetFitA(){return fit_a;}
	double GetFitB(){return fit_b;}
	void SetResidual100(double residual){residual_100 = residual;}
	void SetResidual200(double residual){residual_200 = residual;}
	void SetResidual300(double residual){residual_300 = residual;}
	void SetResidualSSD(double residual){residual_ssd = residual;}
	void SetResidualSSD2(double residual){residual_ssd2 = residual;}
 	void SetID100Hit(int _i){id100hit = _i;}
    void SetID200Hit(int _j){id200hit = _j;}
    void SetID300Hit(int _k){id300hit = _k;}
    void SetIDSSDHit(int _l){idssdhit = _l;}
    void SetTrackID(int id){        track_id = id;    }
    void SetPt0OnTrack(TVector2 tv){pt0_on_track = tv;    }
    void SetPt1OnTrack(TVector2 tv){pt1_on_track = tv;    }
    void SetPt2OnTrack(TVector2 tv){pt2_on_track = tv;    }
    int ModuleID(){return module_id;    }
    double Chi2() const{return chi2;    }
	double Chi2ExSSD() const{return chi2_ex_ssd;	}
	double Chi2Ex100() const{return chi2_ex_100;	}
	double Chi2Ex200() const{return chi2_ex_200;	}
	double Chi2Ex300() const{return chi2_ex_300;	}
    double TgtZ(){return tgt_z;}
    double Residual100(){return residual_100;}
    double Residual200(){return residual_200;}
    double Residual300(){return residual_300;}
    double ResidualSSD(){return residual_ssd;}
    double ResidualSSD2(){return residual_ssd2;}
    int ID100Hit() const{return id100hit;}
    int ID200Hit() const{return id200hit;}
    int ID300Hit() const{return id300hit;}
    int IDSSDHit() const{return idssdhit;}
    int TrackID() {return track_id;}
    double Distance() {        return distance;    }
    E16DST_DST1SSDCluster *GetXClusterSSD(){
        return xclusterssd;
    }
    E16DST_DST1GTRCluster *GetXCluster100(){
        return xcluster100;
    }
    E16DST_DST1GTRCluster *GetXCluster200(){
        return xcluster200;
    }
    E16DST_DST1GTRCluster *GetXCluster300(){
        return xcluster300;
    }

    E16ANA_GTRAnalyzedStripHit *GetXHit100(){
        return xhit100;
    }
    E16ANA_GTRAnalyzedStripHit *GetXHit200(){
        return xhit200;
    }
    E16ANA_GTRAnalyzedStripHit *GetXHit300(){
        return xhit300;
    }
    E16ANA_SSDAnalyzedStripHit *GetXHitSSD(){
		return xhitssd;
  	}
    TVector2 &Pt0OnTrack() {
        return pt0_on_track;
    }
    TVector2 &Pt1OnTrack() {
        return pt1_on_track;
    }
    TVector2 &Pt2OnTrack(){
        return pt2_on_track;
    }
    enum {
        kInvalidValue = -20000,
    };

    static bool CompareTrackPredicate(std::shared_ptr<E16ANA_XZTrackCandidate> lhs, std::shared_ptr<E16ANA_XZTrackCandidate> rhs){return (lhs->chi2 < rhs->chi2);}
    struct CompareTrackFunctor
    :public std::binary_function<std::shared_ptr<E16ANA_XZTrackCandidate>, std::shared_ptr<E16ANA_XZTrackCandidate>, bool>
    {
        bool operator()( std::shared_ptr<E16ANA_XZTrackCandidate> lhs, std::shared_ptr<E16ANA_XZTrackCandidate>rhs)
        {
            return (lhs->chi2 < rhs->chi2);
        }
    };

    static bool CompareDistancePredicate(std::shared_ptr<E16ANA_XZTrackCandidate> lhs, std::shared_ptr<E16ANA_XZTrackCandidate> rhs){return (lhs->distance < rhs->distance);}
    struct CompareDistanceFunctor
    :public std::binary_function<std::shared_ptr<E16ANA_XZTrackCandidate>, std::shared_ptr<E16ANA_XZTrackCandidate>, bool>
    {
        bool operator()( std::shared_ptr<E16ANA_XZTrackCandidate> lhs, std::shared_ptr<E16ANA_XZTrackCandidate> rhs)
        {
            return (lhs->distance < rhs->distance);
        }
    };

private:
    int module_id;
    int id100hit;
    int id200hit;
    int id300hit;
    int idssdhit;
    int track_id;
    double chi2;
    double chi2_ex_ssd;//
    double chi2_ex_100;
    double chi2_ex_200;
    double chi2_ex_300;
    double tgt_z;
    double distance; //nearest target
	double fit_a;
	double fit_b;
//    std::vector<TVector2> v_fit_samples;
    E16ANA_GTRAnalyzedStripHit *xhit100;
    E16ANA_GTRAnalyzedStripHit *xhit200;
    E16ANA_GTRAnalyzedStripHit *xhit300;
    E16ANA_SSDAnalyzedStripHit *xhitssd;
 	E16DST_DST1GTRCluster *xcluster100;
 	E16DST_DST1GTRCluster *xcluster200;
 	E16DST_DST1GTRCluster *xcluster300;
 	E16DST_DST1SSDCluster *xclusterssd;
    TVector2 fit_res100;
    TVector2 fit_res200;
    TVector2 fit_res300;
    TVector2 fit_resssd;
    TVector2 fit_sample100;
    TVector2 fit_sample200;
    TVector2 fit_sample300;
	TVector2 fitpt_ongtr100;
	TVector2 fitpt_ongtr200;
	TVector2 fitpt_ongtr300;
    double residual_100;
    double residual_200;
    double residual_300;
    double residual_ssd;
    double residual_ssd2;
    TVector2 pt0_on_track;
    TVector2 pt1_on_track;
    TVector2 pt2_on_track;
   //iE16ANA_SSDAnalyzedStripHit *xhitssd;
};

class E16ANA_XZCrossPoint {
public:
	E16ANA_XZCrossPoint(){};
	~E16ANA_XZCrossPoint(){};
	void SetCoordinateX(double x){
		coordinateX = x;
	}
	void SetCoordinateZ(double z){coordinateZ = z;	}
	void SetDistance(double d){		distance  = d;	}
	void SetTgtZ1(double z1){		tgt_z1 = z1;	}
	void SetTgtZ2(double z2){		tgt_z2 = z2;	}
	double CoordinateX(){		return coordinateX;	}
	double CoordinateZ(){		return coordinateZ;	}
	double Distance() const{		return distance;	}
	double TgtZ1(){		return tgt_z1;	}
	double TgtZ2(){		return tgt_z2;	}
    void SetXZTrack1(std::shared_ptr<E16ANA_XZTrackCandidate> _xz_track){        xz_track1 = _xz_track;    }
    void SetXZTrack2(std::shared_ptr<E16ANA_XZTrackCandidate> _xz_track){        xz_track2 = _xz_track;    }

    std::shared_ptr<E16ANA_XZTrackCandidate> &GetXZTrackCandidate1(){        return xz_track1;    }
    std::shared_ptr<E16ANA_XZTrackCandidate> &GetXZTrackCandidate2(){        return xz_track2;    }
    void SetTrack1ID(int i){
        track1_id = i;
    }
    void SetTrack2ID(int i){
        track2_id = i;
    }
    int Track1ID() const{
        return track1_id;
    }
    int Track2ID() const{
        return track2_id;
    }

    static bool CompareCrossPredicate(std::shared_ptr<E16ANA_XZCrossPoint> lhs, std::shared_ptr<E16ANA_XZCrossPoint> rhs){return (lhs->distance < rhs->distance);}
    struct CompareCrossFunctor
    :public std::binary_function<std::shared_ptr<E16ANA_XZCrossPoint>, std::shared_ptr<E16ANA_XZCrossPoint>, bool>
    {
        bool operator()( std::shared_ptr<E16ANA_XZCrossPoint> lhs, std::shared_ptr<E16ANA_XZCrossPoint> rhs)
            {
            return (lhs->distance < rhs->distance);
        }
    };

private:
	double coordinateX;
	double coordinateZ;
	double distance;
	double tgt_z1;
	double tgt_z2;
    int track1_id;
    int track2_id;
    std::shared_ptr<E16ANA_XZTrackCandidate> xz_track1;
    std::shared_ptr<E16ANA_XZTrackCandidate> xz_track2;
};

class E16ANA_YTrackCandidate {
public:
	E16ANA_YTrackCandidate() {
		SetInvalid();
	};
	~E16ANA_YTrackCandidate() {};
	void SetModuleID(int m){
		module_id = m;
	}
	void SetInvalid(){
		module_id = -100;
		chi2 = kInvalidValue;
//		tgt_pos = kInvalidValue;
	}
	void SetYHit100(E16DST_DST1GTRCluster *yhit){yhit100 = yhit;}
	void SetYHit200(E16DST_DST1GTRCluster *yhit){yhit200 = yhit;}
	void SetYHit300(E16DST_DST1GTRCluster *yhit){yhit300 = yhit;}
	void SetFitSample100(TVector2 _fit_sample_100){		fit_sample100 = _fit_sample_100;	}
	void SetFitSample200(TVector2 _fit_sample_200){		fit_sample200 = _fit_sample_200;	}
	void SetFitSample300(TVector2 _fit_sample_300){		fit_sample300  = _fit_sample_300;	}
	TVector2 GetFitSample100(){		return fit_sample100;	}
	TVector2 GetFitSample200(){		return fit_sample200;	}
	TVector2 GetFitSample300(){		return fit_sample300;	}
	void SetChi2(double _chi2){		chi2 = _chi2;			}	
//	void SetTgtPos(double y){		tgt_pos = y;	}
	void SetDistanceUpstreamTgt(double d){distance_uptgt = d;}
	void SetDistanceMiddleTgt(double d){distance_middletgt = d;}
	void SetDistanceDownstreamTgt(double d){distance_downtgt = d;}
	void SetDistanceUpstreamWire(double d){distance_upwire = d;}
	void SetDistanceDownstreamWire(double d){distance_downwire = d;}
	void SetResidual100(double residual){		residual_100 = residual;	}
	void SetResidual200(double residual){		residual_200 = residual;	}
	void SetResidual300(double residual){		residual_300 = residual;	}
	void SetFitRes100(TVector2 res){fit_res100 = res;}
	void SetFitRes200(TVector2 res){fit_res200 = res;}
	void SetFitRes300(TVector2 res){fit_res300 = res;}
	void SetFitResSSD(TVector2 res){fit_resssd = res;}
	TVector2 GetFitRes100(){return fit_res100;}
	TVector2 GetFitRes200(){return fit_res200;}
	TVector2 GetFitRes300(){return fit_res300;}
	TVector2 GetFitResSSD(){return fit_resssd;}
	void SetFitA(double a ){fit_a = a;}
	void SetFitB(double b ){fit_b = b;}
	double GetFitA(){return fit_a;}
	double GetFitB(){return fit_b;}
	void SetID100Hit(int _i){		id100hit = _i;	}
	void SetID200Hit(int _j){		id200hit = _j;	}
	void SetID300Hit(int _k){		id300hit = _k;	}
    void SetPt0OnTrack(TVector2 tv){        pt0_on_track = tv;    }
    void SetPt1OnTrack(TVector2 tv){        pt1_on_track = tv;}
    void SetPt2OnTrack(TVector2 tv){        pt2_on_track = tv;    }
	int ModuleID(){		return module_id;	}
	double Chi2() const{		return chi2;	}
//	double TgtPos(){		return tgt_pos;	}
	double DistanceFromUpstreamTgt(){return distance_uptgt;}
	double DistanceFromMiddleTgt(){return distance_middletgt;}
	double DistanceFromDownstreamTgt(){return distance_downtgt;}
	double DistanceFromUpstreamWire(){return distance_upwire;}
	double DistanceFromDownstreamWire(){return distance_downwire;}
	double Residual100(){		return residual_100;	}
	double Residual200(){		return residual_200;	}
	double Residual300(){		return residual_300;	}
	double ResidualSSD(){		return residual_ssd;	}
	int ID100Hit() const{		return id100hit;	}
	int ID200Hit() const{		return id200hit;	}
	int ID300Hit() const{		return id300hit;	}
//	int IDSSDHit() const{
//		return idssdhit;
//	}
    TVector2 &Pt0OnTrack(){return pt0_on_track;}
    TVector2 &Pt1OnTrack(){        return pt1_on_track;    }
    TVector2 &Pt2OnTrack(){        return pt2_on_track;    }
    static bool CompareTrackPredicate(std::shared_ptr<E16ANA_YTrackCandidate> lhs, std::shared_ptr<E16ANA_YTrackCandidate> rhs){return (lhs->chi2 < rhs->chi2);}
    struct CompareTrackFunctor
    :public std::binary_function<std::shared_ptr<E16ANA_YTrackCandidate>, std::shared_ptr<E16ANA_YTrackCandidate>, bool>
    {
        bool operator()( std::shared_ptr<E16ANA_YTrackCandidate> lhs, std::shared_ptr<E16ANA_YTrackCandidate> rhs)
        {
            return (lhs->chi2 < rhs->chi2);
        }
    };
	E16DST_DST1GTRCluster *GetYCluster100(){
		return yhit100;
	}
	E16DST_DST1GTRCluster *GetYCluster200(){
		return yhit200;
	}
	E16DST_DST1GTRCluster *GetYCluster300(){
		return yhit300;
	}
	enum {
		kInvalidValue = -10000,
	};
private:

	int module_id;
	int id100hit;
	int id200hit;
	int id300hit;
	double chi2;
//	double tgt_pos;
    double distance_uptgt;
    double distance_middletgt;
    double distance_downtgt;
	double distance_downwire;
	double distance_upwire;
//	double distance;
	double fit_a;
	double fit_b;
	std::vector<TVector2> v_fit_samples;
	E16DST_DST1GTRCluster *yhit100;
	E16DST_DST1GTRCluster *yhit200;
	E16DST_DST1GTRCluster *yhit300;
//	E16ANA_GTRAnalyzedStripHit *yhit100;
//	E16ANA_GTRAnalyzedStripHit *yhit200;
//	E16ANA_GTRAnalyzedStripHit *yhit300;	
	TVector2 fit_sample100;
	TVector2 fit_sample200;
	TVector2 fit_sample300;
	double residual_100;
	double residual_200;
	double residual_300;
	double residual_ssd;
    TVector2 fit_res100;
    TVector2 fit_res200;
    TVector2 fit_res300;
    TVector2 fit_resssd;
    TVector2 pt0_on_track;
    TVector2 pt1_on_track;
    TVector2 pt2_on_track;
};

class E16ANA_XYZStraightTrack {
public:
    E16ANA_XYZStraightTrack(){
        has_matched_asdhit = 0;
        has_matched_lghit = 0;
    };
    ~E16ANA_XYZStraightTrack(){};
	void SetXZTrackUsedTimes(int n){xz_track_used_times = n;}
	int XZTrackUsedTimes(){return xz_track_used_times;}

    void SetXZTrack(std::shared_ptr<E16ANA_XZTrackCandidate> _xz_track){
        xz_track = _xz_track;
    }
    void SetYTrack(std::shared_ptr<E16ANA_YTrackCandidate> _y_track){
        y_track = _y_track;
    }
    void Set_hasMatchedASDHit(int num){
        has_matched_asdhit = num;
    }
    int hasMatchedASDHit(){
        return has_matched_asdhit;
    }
    void Set_hasMatchedLGHit(int num){
        has_matched_lghit = num;
    }
    int hasMatchedLGHit(){
        return has_matched_lghit;
    }

    std::shared_ptr<E16ANA_XZTrackCandidate> &GetXZTrackCandidate(){
        return xz_track;
    }
    std::shared_ptr<E16ANA_YTrackCandidate> &GetYTrackCandidate(){
        return y_track;
    }
	void SetTwoPointsOnTrack(TVector3 pt0, TVector3 pt1){
		TwoPointsOnTrack.push_back(pt0);
		TwoPointsOnTrack.push_back(pt1);
	};
	
   	std::vector<TVector3> &GetTwoPointsOnTrack(){
		return TwoPointsOnTrack;
	} 
    void SetLGCrossPos(TVector3 pt){
        lg_cross_pos = pt;
    }
    TVector3 &GetLGCrossPos(){
        return lg_cross_pos;
    }
    void SetLGModuleID(int m){
        lg_mod_id = m;
    }
    void SetLGChannelID(int c){
        lg_channel_id = c;
    }
    int GetLGModuleID(){
        return lg_mod_id;
    }
    int GetLGChannelID(){
        return lg_channel_id;
    }
	void SetXTrackID(int i ){xtrk_id = i;}
	void SetYTrackID(int i ){ytrk_id = i;}
	int XTrackID(){return xtrk_id;}
	int YTrackID(){return ytrk_id;}
	void SetFitPtOnGTR100(TVector3 v){fitpt_ongtr100 = v;}
	void SetFitPtOnGTR200(TVector3 v){fitpt_ongtr200 = v;}
	void SetFitPtOnGTR300(TVector3 v){fitpt_ongtr300 = v;}
	void SetDistanceYTrackAndTgt(double d){distance_ytrk_tgt = d;}
	double DistanceYTrackAndTgt(){return distance_ytrk_tgt;}
	TVector3 FitPtOnGTR100(){return fitpt_ongtr100;}
	TVector3 FitPtOnGTR200(){return fitpt_ongtr200;}
	TVector3 FitPtOnGTR300(){return fitpt_ongtr300;}
	void SetTgtID(int id){tgt_id = id;}
	int TgtID(){return tgt_id;}


private:
	int tgt_id;
	int xtrk_id;
	int ytrk_id;
	double distance_ytrk_tgt;
    int xz_track_used_times;//how many pairs can be made with Y track
    std::shared_ptr<E16ANA_XZTrackCandidate> xz_track;
    std::shared_ptr<E16ANA_YTrackCandidate> y_track;
	TVector3 fitpt_ongtr100;
	TVector3 fitpt_ongtr200;
	TVector3 fitpt_ongtr300;
   	std::vector<TVector3> TwoPointsOnTrack; 
    int has_matched_asdhit;
    int has_matched_lghit;
    TVector3 lg_cross_pos;
    int lg_mod_id;
    int lg_channel_id;
};



class StraightTrackAnalyzerV0 {
public:
   // std::unique_ptr<AnalyzerMap> ana_maps;
    StraightTrackAnalyzerV0(){}
    virtual ~StraightTrackAnalyzerV0(){}
//    void MatchingXYZandLeaveTargetTrack(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk, 
//                              std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> &y_trk
//            );
    void Make2DCrossPoint(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk_cands,  E16ANA_GeometryV2 *geom);

    double GetGTRModulePhi(E16ANA_GeometryV2 *geom, int module_id);
    std::vector<long double> LeastSquareMethod(std::vector<TVector2> &tv_v_pos, std::vector<double> sigma_x);
    std::vector<double> CalcCrossPoint2D(std::shared_ptr<E16ANA_XZTrackCandidate> trk1, std::shared_ptr<E16ANA_XZTrackCandidate> trk2); 
    void MatchingXYHitsAfterLinearFit(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk, std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> &y_trk);

    void Clear();
    OnlineGTR::HashMap<E16ANA_GTRAnalyzer2*> gtr_analyzer_map;
    OnlineGTR::HashMap<E16ANA_SSDAnalyzer*> ssd_analyzer_map;
    E16ANA_GTRAnalyzer2 *Chamber(uint16_t module_id, uint16_t layer_id){
        return gtr_analyzer_map[OnlineGTR::IDs(module_id, layer_id).value64];
    };
    E16ANA_SSDAnalyzer *SSD_Sensor(uint16_t module_id, uint16_t layer_id){
        return ssd_analyzer_map[OnlineGTR::IDs(module_id, layer_id).value64];
    };
	void OneModuleAnalyze2(E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1,
						   E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1,
                           int mid,
                           E16ANA_GeometryV2 *geom_v2
                           );
    virtual void XZStraightAnalyzeOnlyGTR2( std::vector<E16DST_DST1SSDCluster*> &ssd_hits,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits0,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits1,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits2,
                        int mid,
                        E16ANA_GeometryV2 *geom_v2
                        ){};
    virtual void YRStraightAnalyze2(std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0,
                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0b,
                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits1,
                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits2,
                            int mid,
                            E16ANA_GeometryV2 *geom_v2
						  	 ){};
    double ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2, std::shared_ptr<E16ANA_XZTrackCandidate> trk);// a+bx
//    double ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2);// a+bx
    void FittingAfterTrackChoice(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trks, E16ANA_GeometryV2 *geom_v2);
    std::vector<long double> CalcChamberResidual(E16ANA_SSDAnalyzedStripHit *ssd_hit,
                      E16ANA_GTRAnalyzedStripHit *gtr_xhits0,
                      E16ANA_GTRAnalyzedStripHit *gtr_xhits1,
                      E16ANA_GTRAnalyzedStripHit *gtr_xhits2,
                      E16ANA_GeometryV2 *geom_v2, 
                      double phi,
                      int kawama_module,
                      int except);
    std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &GetXZTrackCandidates(){return xz_trk_cands;};
    std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> &GetYTrackCandidates(){return y_trk_cands;};
    std::vector<std::shared_ptr<E16ANA_XYZStraightTrack>> &GetXYZStraightTracks(){return xyz_st_trk;};
    std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &GetXZSelectedTrack(){return xz_trk_selected;};
    std::vector<std::shared_ptr<E16ANA_XZCrossPoint>> &GetCrossPoints(){return cross_points;}
    std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &GetXZTracksEveSel(){return xz_trks_evesel;}

protected:
    std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> xz_trk_cands;
    std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> xz_trk_selected;
    std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> y_trk_cands;
    std::vector<std::shared_ptr<E16ANA_XYZStraightTrack>> xyz_st_trk;
    std::vector<std::shared_ptr<E16ANA_XZCrossPoint>> cross_points;
    std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> xz_trks_evesel;
	double timing_window_100 = 25.0;
	double timing_window_200 = 40.0;
	double timing_window_300 = 40.0;
	int n_tgt;
	int pm_wire = 0;
	double wire_x1 = 0;
	double wire_z1 = 0;
	double wire_x2 = 0;
	double wire_z2 = 0;
	double tgt_x1 = 0;
	double tgt_z1 = 0;
	double tgt_x2 = 0;
	double tgt_z2 = 0;
	double tgt_x3 = 0;
	double tgt_z3 = 0;

};


class StraightTrackAnalyzerOfWire : public StraightTrackAnalyzerV0 {
public :
    StraightTrackAnalyzerOfWire();
    ~StraightTrackAnalyzerOfWire();
    void FittingAfterTrackChoice(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trks, E16ANA_GeometryV2 *geom_v2);
    std::vector<long double> CalcChamberResidual(E16ANA_SSDAnalyzedStripHit *ssd_hit,
                      E16ANA_GTRAnalyzedStripHit *gtr_xhits0,
                      E16ANA_GTRAnalyzedStripHit *gtr_xhits1,
                      E16ANA_GTRAnalyzedStripHit *gtr_xhits2,
                      E16ANA_GeometryV2 *geom_v2, 
                      double phi,
                      int kawama_module,
                      int except);
    
private :
};

class StraightTrackAnalyzerOfTargets : public StraightTrackAnalyzerV0 {
public :
	StraightTrackAnalyzerOfTargets(int nt, double x1, double z1, double x2, double z2, double x3, double z3);
	~StraightTrackAnalyzerOfTargets();
    void XZStraightAnalyzeOnlyGTR2( std::vector<E16DST_DST1SSDCluster*> &ssd_hits,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits0,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits1,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits2,
                        int mid,
                        E16ANA_GeometryV2 *geom_v2
                        );

//	void OneModuleAnalyze2(E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1,
//						   E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1,
//                           int mid,
//                           E16ANA_GeometryV2 *geom_v2
//                           );
    void YRStraightAnalyze2(std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0,
                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0b,
                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits1,
                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits2,
                            int mid,
                            E16ANA_GeometryV2 *geom_v2
                            );
//    double ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2, std::shared_ptr<E16ANA_XZTrackCandidate> trk);// a+bx
 
private :
//	int n_tgt;
//	double tgt_x1;
//	double tgt_z1;
//	double tgt_x2;
//	double tgt_z2;
//	double tgt_x3;
//	double tgt_z3;
};

class StraightTrackAnalyzerOfWireV1 : public StraightTrackAnalyzerV0 { //track selection only by GTR
public : 
    StraightTrackAnalyzerOfWireV1(int ntgt, int _pm_wire, double x1, double z1, double x2, double z2);
    ~StraightTrackAnalyzerOfWireV1();
    void XZStraightAnalyzeOnlyGTR2( std::vector<E16DST_DST1SSDCluster*> &ssd_hits,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits0,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits1,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits2,
                        int mid,
                        E16ANA_GeometryV2 *geom_v2
                        );
//    void OneModuleAnalyze2(
//							E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1,
//							E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1,
//                            int mid,
//                            E16ANA_GeometryV2 *geom_v2
//                            );
    void YRStraightAnalyze2(std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0,
                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0b,
                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits1,
                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits2,
                            int mid,
                            E16ANA_GeometryV2 *geom_v2
                            );
 
    std::vector<double> CalcCrossPoint2D(std::shared_ptr<E16ANA_XZTrackCandidate> trk1, std::shared_ptr<E16ANA_XZTrackCandidate> trk2); 
//    double ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2, std::shared_ptr<E16ANA_XZTrackCandidate> trk);// a+bx
//    double ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2);// a+bx

    void Make2DCrossPoint(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk_cands,  E16ANA_GeometryV2 *geom);

private : 
//    int n_tgt;
//	int pm_wire;// wire minus : -1, wire plus : 1 based on beamline group coordinate, which is same with run summary
//	double wire_x1;
//	double wire_z1;
//	double wire_x2;
//	double wire_z2;
};


class StraightTrackAnalyzerOfTargetswoGTR300 : public StraightTrackAnalyzerV0 {
public :
	StraightTrackAnalyzerOfTargetswoGTR300(int ntgt, double x1, double z1, double x2, double z2, double x3, double z3);
	~StraightTrackAnalyzerOfTargetswoGTR300();
    void XZStraightAnalyzeOnlyGTR2( std::vector<E16DST_DST1SSDCluster*> &ssd_hits,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits0,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits1,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits2,
                        int mid,
                        E16ANA_GeometryV2 *geom_v2
                        );

//	void OneModuleAnalyze2(E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1,
//						   E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1,
//                           int mid,
//                           E16ANA_GeometryV2 *geom_v2
//                           );
    void YRStraightAnalyze2(std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0,
                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0b,
                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits1,
                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits2,
                            int mid,
                            E16ANA_GeometryV2 *geom_v2
                            );
//    double ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2, std::shared_ptr<E16ANA_XZTrackCandidate> trk);// a+bx
 
    void MatchingXYHitsAfterLinearFit(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk, std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> &y_trk);
private :
//    int n_tgt;
//	double tgt_x1;
//	double tgt_z1;
//	double tgt_x2;
//	double tgt_z2;
//	double tgt_x3;
//	double tgt_z3;
};

class StraightTrackAnalyzerOfWireV1woGTR300 : public StraightTrackAnalyzerV0 { //track selection only by GTR
public : 
    StraightTrackAnalyzerOfWireV1woGTR300(int ntgt, int _pm_wire, double x1, double z1, double x2, double z2);
    ~StraightTrackAnalyzerOfWireV1woGTR300();
    void XZStraightAnalyzeOnlyGTR2( std::vector<E16DST_DST1SSDCluster*> &ssd_hits,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits0,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits1,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits2,
                        int mid,
                        E16ANA_GeometryV2 *geom_v2
                        );
//    void OneModuleAnalyze2(
//							E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1,
//							E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1,
//                            int mid,
//                            E16ANA_GeometryV2 *geom_v2
//                            );
    void YRStraightAnalyze2(std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0,
                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0b,
                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits1,
                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits2,
                            int mid,
                            E16ANA_GeometryV2 *geom_v2
                            );
 
    std::vector<double> CalcCrossPoint2D(std::shared_ptr<E16ANA_XZTrackCandidate> trk1, std::shared_ptr<E16ANA_XZTrackCandidate> trk2); 
//    double ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2, std::shared_ptr<E16ANA_XZTrackCandidate> trk);// a+bx
 //   double ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2);// a+bx

    void Make2DCrossPoint(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk_cands,  E16ANA_GeometryV2 *geom);

    void MatchingXYHitsAfterLinearFit(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk, std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> &y_trk);
private : 
//    int n_tgt;
//	int pm_wire;// wire minus : -1, wire plus : 1 based on beamline group coordinate, which is same with run summary
//	double wire_x1;
//	double wire_z1;
//	double wire_x2;
//	double wire_z2;
};


#endif //StraightTrakAnalyzerV0
