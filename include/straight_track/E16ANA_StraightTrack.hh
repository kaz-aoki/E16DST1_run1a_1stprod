#ifndef E16ANA_STRAIGHTTRACK_HH
#define E16ANA_STRAIGHTTRACK_HH

#include "E16ANA_GTRAnalyzer2.h"
#include "E16ANA_GTRStripAnalyzer.h"
#include "E16ANA_GeometryV2.hh"
#include "E16DST_DST1Constant.hh"
#include "E16DST_DST1.hh"
#include "OnlineGTRUtility.h"
#include "E16DST_DST0.hh"
#include "E16ANA_SSDAnalyzer.h"
#include "E16ANA_SSDStripAnalyzer.h"
//#include "E16ANA_SSDPedestal.h"
#include <memory>
#include <TString.h>
//#include <E16ANA_Geometry.hh>
#include <E16ANA_GeometryV2.hh>
#include <functional>
#include <algorithm>

#include <E16ANA_StraightTrack.hh>



using namespace E16DST_DST1Constant;

struct Hit_t;
class E16ANA_StraightTrackFit {
public:
	E16ANA_StraightTrackFit();
	~E16ANA_StraightTrackFit();
	void Clear();
	void AddHit(G4ThreeVector &lpos, double sigma, int mid,int lid, const E16ANA_DetectorGeometry *geom, double rphi); //lid{0,1,2,3} = {ssd,gtr1, gtr2, gtr3}

	void AddTgt(G4ThreeVector &gpos_tgt, double sigma);
	virtual void Fit() = 0;
	std::vector<long double> LeastSquareMethod(std::vector<TVector2> &tv, std::vector<double> sigmas);
	
	double Chi2(){return chi2;}
	double FitA(){return fit_a;}
	double FitB(){return fit_b;}
	inline double FitResidual(int lid){
		for(int i = 0; i < Hits.size(); i++){
			if(Hits[i]->layer == lid){
				return Hits[i]->residual;
			}
		}
	};
    inline G4ThreeVector &FitGPos(int lid){
		for(int i = 0; i < Hits.size(); i++){
			if(Hits[i]->layer == lid){
				return Hits[i]->fit_gpos;
			}
		}
	};


protected:
//	std::vector<TVector2> fit_samples
	double chi2;
	double fit_a;//a+bx
	double fit_b;//\a+bx
	G4ThreeVector gpos_tgt = G4ThreeVector(kInvalidValue, kInvalidValue, kInvalidValue);
	double tgt_sigma;

	struct Hit_t {
		G4ThreeVector lpos;
		G4ThreeVector rot_pos;
		double sigma;
		const E16ANA_DetectorGeometry *geom;
		int layer;
		double rphi;
		double residual;//participated in fitting
		G4ThreeVector fit_gpos;
		Hit_t(const int _layer, const G4ThreeVector &_lpos, const double _sigma, const E16ANA_DetectorGeometry *_geom, double _rphi){
			lpos = _lpos;
			sigma = _sigma;
			geom = _geom;
			layer = _layer;// 0 = ssd, 1 = gtr100, ,,,
			residual = kInvalidValue;
			fit_gpos = G4ThreeVector(kInvalidValue, kInvalidValue, kInvalidValue);
			rphi = _rphi;
		}	
	};
	std::vector<Hit_t*> Hits;
};

class E16ANA_StraightTrackFitX: public E16ANA_StraightTrackFit {
public:
	E16ANA_StraightTrackFitX(){
	};
	~E16ANA_StraightTrackFitX(){
	};
	void Fit();
};

class E16ANA_StraightTrackFitY: public E16ANA_StraightTrackFit {
public:
	E16ANA_StraightTrackFitY(){
	};
	~E16ANA_StraightTrackFitY(){
	};
	void Fit();
};

class E16ANA_XZTrackCandidate {
public:
    E16ANA_XZTrackCandidate() {
        SetInvalid();
    };
    ~E16ANA_XZTrackCandidate() {};
    void SetModuleID(int m){
        module_id = m;
    }
    void SetInvalid(){
        module_id = -100;
        chi2 = kInvalidValue;
        tgt_z = kInvalidValue;
		xclusterssd = nullptr;
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
	void SetFitResidual100(double residual){residual_100 = residual;}
	void SetFitResidual200(double residual){residual_200 = residual;}
	void SetFitResidual300(double residual){residual_300 = residual;}
	void SetFitResidualSSD(double residual){residual_ssd = residual;}
	void SetFitResidualSSD2(double residual){residual_ssd2 = residual;}
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
	void SetWhichTgt(int i){ which_tgt = i;}
	int  WhichTgt(){return which_tgt;}
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
	int which_tgt; //0...up, 1..middle, 2..down
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
	void SetWhichTgt(int i){ which_tgt = i;}
	int  WhichTgt(){return which_tgt;}
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
	int which_tgt;
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
	void SetTrackID (int i ){trk_id = i;}
	void SetXTrackID(int i ){xtrk_id = i;}
	void SetYTrackID(int i ){ytrk_id = i;}
	int XTrackID(){return xtrk_id;}
	int YTrackID(){return ytrk_id;}
	int TrackID(){return trk_id;}
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
    double SumTimingDiff(){return 
	 fabs(xz_track->GetXCluster100()->Timing() - y_track->GetYCluster100()->Timing() - timing_offset0)
	+fabs(xz_track->GetXCluster200()->Timing() - y_track->GetYCluster200()->Timing() - timing_offset1)
	+fabs(xz_track->GetXCluster300()->Timing() - y_track->GetYCluster300()->Timing() - timing_offset2)
	 ;}

    static bool CompareTimingDifference(std::shared_ptr<E16ANA_XYZStraightTrack> lhs, std::shared_ptr<E16ANA_XYZStraightTrack> rhs){return (lhs->SumTimingDiff() < rhs->SumTimingDiff());}
    struct CompareTimingDifferenceFunctor
    :public std::binary_function<std::shared_ptr<E16ANA_XYZStraightTrack>, std::shared_ptr<E16ANA_XYZStraightTrack>, bool>
    {
        bool operator()( std::shared_ptr<E16ANA_XYZStraightTrack> lhs, std::shared_ptr<E16ANA_XYZStraightTrack> rhs)
        {
            return (lhs->SumTimingDiff() < rhs->SumTimingDiff());
        }
    };





private:
	int tgt_id;
    int trk_id;
	int xtrk_id;
	int ytrk_id;
	double distance_ytrk_tgt;
	double sum_time_diff;
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
	double timing_offset0 = 0;
	double timing_offset1 = 0;
	double timing_offset2 = 0;
	double clc_offset0 = 0;
	double clc_offset1 = 0;
	double clc_offset2 = 0;
	

};






#endif
