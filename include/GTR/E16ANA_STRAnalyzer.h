#ifndef E16ANA_STRAnalyzer_h
#define E16ANA_STRAnalyzer_h 1

#include "E16ANA_GTRAnalyzer2.h"
#include "E16ANA_SSDAnalyzer.h"
#include "E16ANA_GTRStripAnalyzer.h"
#include "E16ANA_SSDStripAnalyzer.h"
#include "E16DST_DST1.hh"
//#include "GTR/E16ANA_GTRAnalyzerMaker.hh"
//#include "GTR/OnlineGTRUtility.h"
//#include "E16ANA_GTRPedestal.h"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"



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
    void SetXHit100(E16ANA_GTRAnalyzedStripHit *xhit){xhit100 = xhit;}
    void SetXHit200(E16ANA_GTRAnalyzedStripHit *xhit){xhit200 = xhit;}
    void SetXHit300(E16ANA_GTRAnalyzedStripHit *xhit){xhit300 = xhit;}
    void SetXHitSSD(E16ANA_SSDAnalyzedStripHit *shit){xhitssd = shit;}
    void SetFitSample100(TVector2 _fit_sample_100){fit_sample100 = _fit_sample_100;}
    void SetFitSample200(TVector2 _fit_sample_200){fit_sample200 = _fit_sample_200;}
    void SetFitSample300(TVector2 _fit_sample_300){fit_sample300  = _fit_sample_300;}
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
	void SetResidual100(double residual){residual_100 = residual;}
	void SetResidual200(double residual){residual_200 = residual;}
	void SetResidual300(double residual){residual_300 = residual;}
	void SetResidualSSD(double residual){residual_ssd = residual;}
 	void SetID100Hit(int _i){id100hit = _i;}
    void SetID200Hit(int _j){        id200hit = _j;    }
    void SetID300Hit(int _k){        id300hit = _k;    }
    void SetIDSSDHit(int _l){       idssdhit = _l;}
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
    int ID100Hit() const{return id100hit;}
    int ID200Hit() const{return id200hit;}
    int ID300Hit() const{return id300hit;}
    int IDSSDHit() const{return idssdhit;}
    int TrackID() {return track_id;}
    double Distance() {        return distance;    }

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
//    std::vector<TVector2> v_fit_samples;
    E16ANA_GTRAnalyzedStripHit *xhit100;
    E16ANA_GTRAnalyzedStripHit *xhit200;
    E16ANA_GTRAnalyzedStripHit *xhit300;
    E16ANA_SSDAnalyzedStripHit *xhitssd;
    TVector2 fit_sample100;
    TVector2 fit_sample200;
    TVector2 fit_sample300;
    double residual_100;
    double residual_200;
    double residual_300;
    double residual_ssd;
    TVector2 pt0_on_track;
    TVector2 pt1_on_track;
    TVector2 pt2_on_track;
   //iE16ANA_SSDAnalyzedStripHit *xhitssd;
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
		tgt_pos = kInvalidValue;
	}
	void SetYHit100(E16ANA_GTRAnalyzedStripHit *yhit){yhit100 = yhit;}
	void SetYHit200(E16ANA_GTRAnalyzedStripHit *yhit){yhit200 = yhit;}
	void SetYHit300(E16ANA_GTRAnalyzedStripHit *yhit){yhit300 = yhit;}
	void SetFitSample100(TVector2 _fit_sample_100){		fit_sample100 = _fit_sample_100;	}
	void SetFitSample200(TVector2 _fit_sample_200){		fit_sample200 = _fit_sample_200;	}
	void SetFitSample300(TVector2 _fit_sample_300){		fit_sample300  = _fit_sample_300;	}
	TVector2 GetFitSample100(){		return fit_sample100;	}
	TVector2 GetFitSample200(){		return fit_sample200;	}
	TVector2 GetFitSample300(){		return fit_sample300;	}
	void SetChi2(double _chi2){		chi2 = _chi2;			}	
	void SetTgtPos(double y){		tgt_pos = y;	}
	void SetResidual100(double residual){		residual_100 = residual;	}
	void SetResidual200(double residual){		residual_200 = residual;	}
	void SetResidual300(double residual){		residual_300 = residual;	}
	void SetID100Hit(int _i){		id100hit = _i;	}
	void SetID200Hit(int _j){		id200hit = _j;	}
	void SetID300Hit(int _k){		id300hit = _k;	}
    void SetPt0OnTrack(TVector2 tv){        pt0_on_track = tv;    }
    void SetPt1OnTrack(TVector2 tv){        pt1_on_track = tv;}
    void SetPt2OnTrack(TVector2 tv){        pt2_on_track = tv;    }
	int ModuleID(){		return module_id;	}
	double Chi2() const{		return chi2;	}
	double TgtPos(){		return tgt_pos;	}
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
    static bool CompareTrackPredicate(E16ANA_YTrackCandidate lhs, E16ANA_YTrackCandidate rhs){return (lhs.chi2 < rhs.chi2);}
    struct CompareTrackFunctor
    :public std::binary_function<E16ANA_YTrackCandidate, E16ANA_YTrackCandidate, bool>
    {
        bool operator()( E16ANA_YTrackCandidate lhs, E16ANA_YTrackCandidate rhs)
        {
            return (lhs.chi2 < rhs.chi2);
        }
    };
	E16ANA_GTRAnalyzedStripHit *GetYHit100(){
		return yhit100;
	}
	E16ANA_GTRAnalyzedStripHit *GetYHit200(){
		return yhit200;
	}
	E16ANA_GTRAnalyzedStripHit *GetYHit300(){
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
	double tgt_pos;
	std::vector<TVector2> v_fit_samples;
	E16ANA_GTRAnalyzedStripHit *yhit100;
	E16ANA_GTRAnalyzedStripHit *yhit200;
	E16ANA_GTRAnalyzedStripHit *yhit300;	
	TVector2 fit_sample100;
	TVector2 fit_sample200;
	TVector2 fit_sample300;
	double residual_100;
	double residual_200;
	double residual_300;
	double residual_ssd;
    TVector2 pt0_on_track;
    TVector2 pt1_on_track;
    TVector2 pt2_on_track;
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
class E16ANA_XYZStraightTrack {
public:
    E16ANA_XYZStraightTrack(){
        has_matched_asdhit = 0;
        has_matched_lghit = 0;
    };
    ~E16ANA_XYZStraightTrack(){};

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

private:
    std::shared_ptr<E16ANA_XZTrackCandidate> xz_track;
    std::shared_ptr<E16ANA_YTrackCandidate> y_track;
   	std::vector<TVector3> TwoPointsOnTrack; 
    int has_matched_asdhit;
    int has_matched_lghit;
    TVector3 lg_cross_pos;
    int lg_mod_id;
    int lg_channel_id;
};




class E16ANA_STRAnalyzer {
public:
    E16ANA_STRAnalyzer();
    ~E16ANA_STRAnalyzer();
    void TrackCandidateSearchXZ_OneModule(
            E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> &ssd_detector,
            E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> &gtr_detector
            );
    void Make2DCrossPoint(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk_cands,  E16ANA_GeometryV2 *geom);
   void SearchSSDHit(std::vector<std::shared_ptr<E16ANA_XZCrossPoint>> &cps, std::vector<std::reference_wrapper<std::vector<E16ANA_SSDAnalyzedStripHit>>> &v_shits, E16ANA_GeometryV2 *gome_v2);

private:
 
    std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &GetXZTrackCandidates(){return xz_trk_cands;};
    std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> &GetYTrackCandidates(){return y_trk_cands;};
    std::vector<std::shared_ptr<E16ANA_XYZStraightTrack>> &GetXYZStraightTrack(){return xyz_st_trk;};
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


};

class E16ANA_STRAnalyzerOfWire : public E16ANA_STRAnalyzer {
public:
    E16ANA_STRAnalyzerOfWire();
    ~E16ANA_STRAnalyzerOfWire();


};



#endif 
