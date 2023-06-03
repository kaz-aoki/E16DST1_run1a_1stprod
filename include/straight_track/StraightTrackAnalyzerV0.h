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

#include <E16ANA_StraightTrack.hh>

//const int gtrmaxhit = 20;
//const double th_chi2 = 100;//chisquare threshold 
//const double th_chi2_first = 100;//chisquare threshold 
//const double th_chi2_second = 100;//chisquare threshold 
//const double th_chi2_third = 100;//chisquare threshold 
//const double th_chi2_y = 100;//chisquare threshold 
//const double th_chi2_wossd = 30;
//const int min_ip_gap = 100;// this should be caluculated precisely
//const double Agtr[] = {1.295, 0.882, 0.469, 0, -0.469, -0.882, -1.295};


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






class StraightTrackAnalyzerV0 {
public:
   // std::unique_ptr<AnalyzerMap> ana_maps;
    StraightTrackAnalyzerV0(){
		fitter_x = new E16ANA_StraightTrackFitX();	
		fitter_y = new E16ANA_StraightTrackFitY();	
	}
    virtual ~StraightTrackAnalyzerV0(){}
//    void MatchingXYZandLeaveTargetTrack(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk, 
//                              std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> &y_trk
//            );
    void Make2DCrossPoint(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk_cands,  E16ANA_GeometryV2 *geom);

    double GetGTRModulePhi(E16ANA_GeometryV2 *geom, int module_id);
    std::vector<long double> LeastSquareMethod(std::vector<TVector2> &tv_v_pos, std::vector<double> sigma_x);
    std::vector<double> CalcCrossPoint2D(std::shared_ptr<E16ANA_XZTrackCandidate> trk1, std::shared_ptr<E16ANA_XZTrackCandidate> trk2); 
    virtual void MatchingXYHitsAfterLinearFit(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk, std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> &y_trk){};

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
   	void OneModuleAnalyze2woSSD(E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1,
						   E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1,
                           int mid,
                           E16ANA_GeometryV2 *geom_v2
                           );
    virtual void XZStraightAnalyzeSSDGTR( std::vector<E16DST_DST1SSDCluster*> &ssd_hits,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits0,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits1,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits2,
                        int mid,
                        E16ANA_GeometryV2 *geom_v2
                        ){}; 
   virtual void XZStraightAnalyzewoSSD(
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
    double ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2);// a+bx
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
	virtual bool IsMatchedXandYTrack(std::shared_ptr<E16ANA_XZTrackCandidate> x, std::shared_ptr<E16ANA_YTrackCandidate> y){};

protected:
    std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> xz_trk_cands;
    std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> xz_trk_selected;
    std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> y_trk_cands;
    std::vector<std::shared_ptr<E16ANA_XYZStraightTrack>> xyz_st_trk;
    std::vector<std::shared_ptr<E16ANA_XZCrossPoint>> cross_points;
    std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> xz_trks_evesel;
//	double timing_window_100 = 60.0;
//	double timing_window_200 = 60.0;
//	double timing_window_300 = 60.0;
//	double clc_window_100 = 4000.0;
//	double clc_window_200 = 4000.0;
//	double clc_window_300 = 4000.0;
	int n_tgt;
	int pm_wire = 0;
	double wire_x1 = 0;
	double wire_z1 = 0;
	double wire_x2 = 0;
	double wire_z2 = 0;
	double tgt_x1 = 0;
	double tgt_z1 = -20;
	double tgt_x2 = 0;
	double tgt_z2 = 0;
	double tgt_x3 = 0;
	double tgt_z3 = 20;
	
	double timing_offset0 = 0;
	double timing_offset1 = 0;
	double timing_offset2 = 0;
	double clc_offset0 = 100;
	double clc_offset1 = 100;
	double clc_offset2 = 100;
	E16ANA_StraightTrackFit *fitter_x;
	E16ANA_StraightTrackFit *fitter_y;

};


//class StraightTrackAnalyzerOfWire : public StraightTrackAnalyzerV0 {
//public :
//    StraightTrackAnalyzerOfWire();
//    ~StraightTrackAnalyzerOfWire();
//private :
//};

class StraightTrackAnalyzerOfTargets : public StraightTrackAnalyzerV0 {
public :
	StraightTrackAnalyzerOfTargets(int nt, double x1, double z1, double x2, double z2, double x3, double z3);
	~StraightTrackAnalyzerOfTargets();
    void XZStraightAnalyzeSSDGTR( std::vector<E16DST_DST1SSDCluster*> &ssd_hits,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits0,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits1,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits2,
                        int mid,
                        E16ANA_GeometryV2 *geom_v2
                        );

    void XZStraightAnalyzewoSSD(
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits0,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits1,
					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits2,
                        int mid,
                        E16ANA_GeometryV2 *geom_v2
	); 
	bool IsMatchedXandYTrack(std::shared_ptr<E16ANA_XZTrackCandidate> x, std::shared_ptr<E16ANA_YTrackCandidate> y);
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
    void XZStraightAnalyzeSSDGTR( std::vector<E16DST_DST1SSDCluster*> &ssd_hits,
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

	bool IsMatchedXandYTrack(std::shared_ptr<E16ANA_XZTrackCandidate> x, std::shared_ptr<E16ANA_YTrackCandidate> y);

    void FittingAfterTrackChoice(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trks, E16ANA_GeometryV2 *geom_v2);
    std::vector<long double> CalcChamberResidual(E16ANA_SSDAnalyzedStripHit *ssd_hit,
                      E16ANA_GTRAnalyzedStripHit *gtr_xhits0,
                      E16ANA_GTRAnalyzedStripHit *gtr_xhits1,
                      E16ANA_GTRAnalyzedStripHit *gtr_xhits2,
                      E16ANA_GeometryV2 *geom_v2, 
                      double phi,
                      int kawama_module,
                      int except);
     
    void MatchingXYHitsAfterLinearFit(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk, std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> &y_trk);



private : 
//    int n_tgt;
//	int pm_wire;// wire minus : -1, wire plus : 1 based on beamline group coordinate, which is same with run summary
//	double wire_x1;
//	double wire_z1;
//	double wire_x2;
//	double wire_z2;
};


//class StraightTrackAnalyzerOfTargetswoGTR300 : public StraightTrackAnalyzerV0 {
//public :
//	StraightTrackAnalyzerOfTargetswoGTR300(int ntgt, double x1, double z1, double x2, double z2, double x3, double z3);
//	~StraightTrackAnalyzerOfTargetswoGTR300();
//    void XZStraightAnalyzeSSDGTR( std::vector<E16DST_DST1SSDCluster*> &ssd_hits,
//					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits0,
//					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits1,
//					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits2,
//                        int mid,
//                        E16ANA_GeometryV2 *geom_v2
//                        );
//
////	void OneModuleAnalyze2(E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1,
////						   E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1,
////                           int mid,
////                           E16ANA_GeometryV2 *geom_v2
////                           );
//    void YRStraightAnalyze2(std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0,
//                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0b,
//                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits1,
//                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits2,
//                            int mid,
//                            E16ANA_GeometryV2 *geom_v2
//                            );
////    double ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2, std::shared_ptr<E16ANA_XZTrackCandidate> trk);// a+bx
// 
//    void MatchingXYHitsAfterLinearFit(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk, std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> &y_trk);
//private :
////    int n_tgt;
////	double tgt_x1;
////	double tgt_z1;
////	double tgt_x2;
////	double tgt_z2;
////	double tgt_x3;
////	double tgt_z3;
//};
//
//class StraightTrackAnalyzerOfWireV1woGTR300 : public StraightTrackAnalyzerV0 { //track selection only by GTR
//public : 
//    StraightTrackAnalyzerOfWireV1woGTR300(int ntgt, int _pm_wire, double x1, double z1, double x2, double z2);
//    ~StraightTrackAnalyzerOfWireV1woGTR300();
//    void XZStraightAnalyzeSSDGTR( std::vector<E16DST_DST1SSDCluster*> &ssd_hits,
//					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits0,
//					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits1,
//					 	std::vector<E16DST_DST1GTRCluster*> &gtr_hits2,
//                        int mid,
//                        E16ANA_GeometryV2 *geom_v2
//                        );
////    void OneModuleAnalyze2(
////							E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1,
////							E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1,
////                            int mid,
////                            E16ANA_GeometryV2 *geom_v2
////                            );
//    void YRStraightAnalyze2(std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0,
//                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0b,
//                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits1,
//                            std::vector<E16DST_DST1GTRCluster*> &gtr_yhits2,
//                            int mid,
//                            E16ANA_GeometryV2 *geom_v2
//                            );
// 
//    std::vector<double> CalcCrossPoint2D(std::shared_ptr<E16ANA_XZTrackCandidate> trk1, std::shared_ptr<E16ANA_XZTrackCandidate> trk2); 
////    double ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2, std::shared_ptr<E16ANA_XZTrackCandidate> trk);// a+bx
// //   double ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2);// a+bx
//
//    void Make2DCrossPoint(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk_cands,  E16ANA_GeometryV2 *geom);
//
//    void MatchingXYHitsAfterLinearFit(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk, std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> &y_trk);
//private : 
////    int n_tgt;
////	int pm_wire;// wire minus : -1, wire plus : 1 based on beamline group coordinate, which is same with run summary
////	double wire_x1;
////	double wire_z1;
////	double wire_x2;
////	double wire_z2;
//};
//

#endif //StraightTrakAnalyzerV0
