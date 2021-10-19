#include <algorithm> 
#include <array>
#include "TGraphErrors.h"
#include <TF1.h>
#include "straight_track/StraightTrackAnalyzerV0.h"
#include "OnlineGTRUtility.h"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16DST_DST1Constant.hh"
#include "E16ANA_TargetInfo.hh"
#include "E16ANA_RundependentName.hh"
using namespace std;

StraightTrackAnalyzerOfWire::StraightTrackAnalyzerOfWire(){
}
StraightTrackAnalyzerOfWire::~StraightTrackAnalyzerOfWire(){
}
StraightTrackAnalyzerOfWireV1::StraightTrackAnalyzerOfWireV1(double x1, double z1, double x2, double z2){
	wire_x1 = x1;
	wire_z1 = z1;
	wire_x2 = x2;
	wire_z2 = z2;	
}
StraightTrackAnalyzerOfWireV1::~StraightTrackAnalyzerOfWireV1(){
}

void StraightTrackAnalyzerV0::Clear(){
    xz_trk_cands.clear();
    cross_points.clear();
    y_trk_cands.clear();
    xyz_st_trk.clear();
    xz_trk_selected.clear();
    xz_trks_evesel.clear();
    xz_trks_evesel.shrink_to_fit();
}
void StraightTrackAnalyzerOfWireV1::OneModuleAnalyze2(E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1, int mid, E16ANA_GeometryV2 *geom_v2){
    XZStraightAnalyzeOnlyGTR2(ssd1->ClusterPtrs(mid, 0, 0),
							  gtr1->ClusterPtrs(mid, 0, 0), //GTR100 X
							  gtr1->ClusterPtrs(mid, 1, 0), //GTR200 X
							  gtr1->ClusterPtrs(mid, 2, 0), //GTR300 X 
							  mid, 
							  geom_v2);
    YRStraightAnalyze2(gtr1->ClusterPtrs(mid, 0, 1), //GTR100 Y
					   gtr1->ClusterPtrs(mid, 0, 2), //GTR100 Yb
					   gtr1->ClusterPtrs(mid, 1, 1), //GTR200
					   gtr1->ClusterPtrs(mid, 2, 1), //GTR300
					   mid,
					   geom_v2);
//	MatchingXYHitsAfterLinearFit(
//		this->GetXZTrackCandidates(),
//		this->GetYTrackCandidates()
//	);		
}


void StraightTrackAnalyzerV0::OneModule2DAnalyze(std::vector<E16ANA_SSDAnalyzedStripHit> &ssd_hits, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_xhits0, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_xhits1, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_xhits2, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_yhits0, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_yhits0b,  std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_yhits1, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_yhits2, int mid, E16ANA_GeometryV2 *geom_v2){
    XZStraightAnalyzeOnlyGTR(ssd_hits, gtr_xhits0, gtr_xhits1, gtr_xhits2,  mid, geom_v2);
//    XZStraightAnalyze(ssd_hits, gtr_xhits0, gtr_xhits1, gtr_xhits2,  mid, geom_v2);
//    YRStraightAnalyze(gtr_yhits0, gtr_yhits0b, gtr_yhits1, gtr_yhits2, mid, geom_v2);
}


void StraightTrackAnalyzerOfWireV1::OneModule2DAnalyze(std::vector<E16ANA_SSDAnalyzedStripHit> &ssd_hits, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_xhits0, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_xhits1, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_xhits2, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_yhits0, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_yhits0b,  std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_yhits1, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_yhits2, int mid, E16ANA_GeometryV2 *geom_v2){
//    XZStraightAnalyzeOnlyGTR(ssd_hits, gtr_xhits0, gtr_xhits1, gtr_xhits2,  mid, geom_v2);
//    XZStraightAnalyze(ssd_hits, gtr_xhits0, gtr_xhits1, gtr_xhits2,  mid, geom_v2);
//    YRStraightAnalyze(gtr_yhits0, gtr_yhits0b, gtr_yhits1, gtr_yhits2, mid, geom_v2);
}

//void StraightTrackAnalyzerOfWireV1::Analyze(std::vector<std::shared_ptr<E16ANA_XYZStraightTrack>> &tracks, E16ANA_GeometryV2 *geom ){
//	std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> trks;
//	for(int i=0; i < xz_tracks.size(); i++){
//	}	

//}


void StraightTrackAnalyzerOfWireV1::Analyze(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_tracks, std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> &y_tracks, E16ANA_GeometryV2 *geom_v2){
    
    std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> trks;
    for(int i = 0; i < xz_tracks.size() ; i++){
//        std::cout << "tgtpos = " << xz_tracks[i].TgtZ() << std::endl;
        if((fabs(xz_tracks[i]->TgtZ() - 40) < 20) || (fabs(xz_tracks[i]->TgtZ()+40) < 20)){
            trks.push_back(xz_tracks[i]);
        }
    }
//    std::cout << "trk size   "  << trks.size() << std::endl;
    Make2DCrossPoint(trks, geom_v2);//
    trks.clear();
//    std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> trks2;
//    for(int i = 0; i < cross_points.size() ; i++){
//       trks2.push_back(cross_points[i]->GetXZTrackCandidate1());
//        trks2.push_back(cross_points[i]->GetXZTrackCandidate2());
//    }
//    FittingAfterTrackChoice(trks2, geom_v2);
//    trks2.clear();


//3D analysis
#if 0 
//    MatchingXYZStraightTrack(xz_tracks, y_tracks);
    MatchingXYZandLeaveTargetTrack(xz_tracks, y_tracks);
//    std::cout << "found xyz track  "  << std::endl;
    std::vector<E16ANA_XZTrackCandidate> trks;
    for(int i = 0; i < xyz_st_trk.size() ; i++){
        trks.push_back(xyz_st_trk[i].GetXZTrackCandidate());
    }
    Make2DCrossPoint(trks, geom_v2);
    trks.clear();
    std::vector<E16ANA_XZTrackCandidate> trks2;
    for(int i = 0; i < cross_points.size() ; i++){
        trks2.push_back(cross_points[i].GetXZTrackCandidate1());
        trks2.push_back(cross_points[i].GetXZTrackCandidate2());
    }
    FittingAfterTrackChoice(trks2, geom_v2);
    trks2.clear();
#endif
}

void StraightTrackAnalyzerOfWireV1::Analyze(std::vector<std::shared_ptr<E16ANA_XYZStraightTrack>> &st_tracks, E16ANA_GeometryV2 *geom){
    Make3DCrossPoint(st_tracks, geom);//
}


void StraightTrackAnalyzerOfWireV1::Make3DCrossPoint(std::vector<std::shared_ptr<E16ANA_XYZStraightTrack>> &st_tracks, E16ANA_GeometryV2 *geom){
	
}

void StraightTrackAnalyzerV0::Analyze(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_tracks, std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> &y_tracks, E16ANA_GeometryV2 *geom_v2){
#if 1 //2D   
    std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> trks;
    for(int i = 0; i < xz_tracks.size() ; i++){
//        std::cout << "tgtpos = " << xz_tracks[i].TgtZ() << std::endl;
        if((fabs(xz_tracks[i]->TgtZ()) < 80)){
            trks.push_back(xz_tracks[i]);
        }
    }
//    std::cout << "trk size   "  << trks.size() << std::endl;
    Make2DCrossPoint(trks, geom_v2);//
    trks.clear();
#endif
}


void StraightTrackAnalyzerOfWireV1::SearchSSDHit(std::vector<std::shared_ptr<E16ANA_XZCrossPoint>> &cps, E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1, E16ANA_GeometryV2 *geom){
	std::vector<G4ThreeVector> l_hitpos, g_hitpos, rot_pos, l_ssd_hitpos, g_ssd_hitpos, rot_ssd_pos;
    std::vector<TVector2> v_fit_samples;
    std::vector<double> sigma_x = {0.1, 0.1, 0.1};//gtr0,1, 2 
    std::vector<double> sigma_x2 = {0.2, 0.2, 0.2, 0.1};//gtr0,1, 2 ssd
    int index = 0;
    for(int i=0; i<cps.size(); i++){
        std::shared_ptr<E16ANA_XZTrackCandidate> t1 = cps[i]->GetXZTrackCandidate1();
        std::shared_ptr<E16ANA_XZTrackCandidate> t2 = cps[i]->GetXZTrackCandidate2();
        std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> ts;
        ts.clear();
        ts.push_back(t1);
        ts.push_back(t2);
        for(int t=0; t<ts.size(); t++){
	        std::vector<E16DST_DST1SSDCluster*> &v_ssdhits = ssd1->ClusterPtrs(ts[t]->ModuleID(), 0, 0);
	        l_hitpos.clear();
	        g_hitpos.clear();
	        rot_pos.clear();
	        v_fit_samples.clear();
	        int kawama_module = ModuleID_2020to2013_33(ts[t]->ModuleID());
	        double phi = GetGTRModulePhi(geom, ts[t]->ModuleID());
	        l_hitpos.push_back(G4ThreeVector(ts[t]->GetXCluster100()->CogPos(), 0, 0));
	        l_hitpos.push_back(G4ThreeVector(ts[t]->GetXCluster200()->CogPos(), 0, 0));
	        l_hitpos.push_back(G4ThreeVector(ts[t]->GetXCluster300()->CogPos(), 0, 0));
	        for(int l=0; l<l_hitpos.size(); l++){
	            g_hitpos.push_back(G4ThreeVector(geom->GTR(kawama_module, l)->GetGPos(l_hitpos[l])));
	            rot_pos.push_back(G4ThreeVector(g_hitpos[l].rotateY(phi)));
	            v_fit_samples.push_back(TVector2(rot_pos[l].x(), rot_pos[l].z()));
	        }
	        for(int j = 0; j<v_ssdhits.size() ; j++){
    	        E16DST_DST1SSDCluster* h = v_ssdhits[j];
        	    l_ssd_hitpos.clear();
            	g_ssd_hitpos.clear();
	            rot_ssd_pos.clear();
    	        l_ssd_hitpos.push_back(G4ThreeVector(h->CogPos(), 0, 0));
        	    g_ssd_hitpos.push_back(G4ThreeVector(geom->SSD(kawama_module, 0)->GetGPos(l_ssd_hitpos[0])));
            	rot_ssd_pos.push_back(G4ThreeVector(g_ssd_hitpos[0].rotateY(phi)));
	            TVector2 rot_ssd = TVector2(rot_ssd_pos[0].x(), rot_ssd_pos[0].z());
    	        std::vector<long double> &&v_results2 = LeastSquareMethod(v_fit_samples, sigma_x);
//      	      v_fit_samples.push_back(TVector2(rot_ssd_pos[0].x(), rot_ssd_pos[0].z()));
//          	  std::vector<long double> &&v_results2 = LeastSquareMethod(v_fit_samples, sigma_x2);
//	            v_fit_samples.pop_back();
	            if(v_results2[0] < 50){
    	            std::shared_ptr<E16ANA_XZTrackCandidate> trk = std::make_shared<E16ANA_XZTrackCandidate>();
        	        trk->SetID100Hit(ts[t]->ID100Hit());
	           		trk->SetID200Hit(ts[t]->ID200Hit());
            	    trk->SetID300Hit(ts[t]->ID300Hit());
					trk->SetIDSSDHit(j);
    	    	    trk->SetModuleID(ts[t]->ModuleID());
			        trk->SetChi2(v_results2[0]);
		    	    trk->SetTgtZ(ReconstructTgtPosBeforeVertex(v_results2[1], v_results2[2], phi, kawama_module, geom, trk));
                	trk->SetResidualSSD((rot_ssd.Y() - (v_results2[1] + v_results2[2]*rot_ssd.X())));
	//                trk->SetResidual100(v_results2[3]);
	//	        	trk->SetResidual200(v_results2[4]);
	//               trk->SetResidual300(v_results2[5]);
	//	            trk->SetResidualSSD(v_results2[6]);
    		        trk->SetXHit100(ts[t]->GetXCluster100());
	    	    	trk->SetXHit200(ts[t]->GetXCluster200());
    	    	    trk->SetXHit300(ts[t]->GetXCluster300());
    	        	trk->SetXHitSSD(h);
	                trk->SetTrackID(index);
    	            xz_trks_evesel.push_back(trk);
        	        index++;
            	}
            v_results2.clear();
        }
        }
    }
	


}



void StraightTrackAnalyzerOfWireV1::SearchSSDHit(std::vector<std::shared_ptr<E16ANA_XZCrossPoint>> &cps, std::vector<std::reference_wrapper<std::vector<E16ANA_SSDAnalyzedStripHit>>> &v_shits, E16ANA_GeometryV2 *geom_v2){
    std::vector<G4ThreeVector> l_hitpos;
    std::vector<G4ThreeVector> g_hitpos;
    std::vector<G4ThreeVector> rot_pos;
    std::vector<TVector2> v_fit_samples;
    std::vector<G4ThreeVector> l_ssd_hitpos;
    std::vector<G4ThreeVector> g_ssd_hitpos;
    std::vector<G4ThreeVector> rot_ssd_pos;
    std::vector<double> sigma_x = {0.1, 0.1, 0.1};//gtr0,1, 2 
    std::vector<double> sigma_x2 = {0.2, 0.2, 0.2, 0.1};//gtr0,1, 2 ssd
    int index = 0;
    for(int i=0; i<cps.size(); i++){
        std::shared_ptr<E16ANA_XZTrackCandidate> t1 = cps[i]->GetXZTrackCandidate1();
        std::shared_ptr<E16ANA_XZTrackCandidate> t2 = cps[i]->GetXZTrackCandidate2();
        std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> ts;
        ts.clear();
        ts.push_back(t1);
        ts.push_back(t2);
        for(int t=0; t<ts.size(); t++){
        std::vector<E16ANA_SSDAnalyzedStripHit> &v_shit = v_shits[ts[t]->ModuleID()-100];
        l_hitpos.clear();
        g_hitpos.clear();
        rot_pos.clear();
        v_fit_samples.clear();
        int kawama_module = ModuleID_2020to2013_33(ts[t]->ModuleID());
        double phi = GetGTRModulePhi(geom_v2, ts[t]->ModuleID());
        l_hitpos.push_back(G4ThreeVector(ts[t]->GetXCluster100()->CogPos(), 0, 0));
        l_hitpos.push_back(G4ThreeVector(ts[t]->GetXCluster200()->CogPos(), 0, 0));
        l_hitpos.push_back(G4ThreeVector(ts[t]->GetXCluster300()->CogPos(), 0, 0));
        for(int l=0; l<l_hitpos.size(); l++){
            g_hitpos.push_back(G4ThreeVector(geom_v2->GTR(kawama_module, l)->GetGPos(l_hitpos[l])));
            rot_pos.push_back(G4ThreeVector(g_hitpos[l].rotateY(phi)));
            v_fit_samples.push_back(TVector2(rot_pos[l].x(), rot_pos[l].z()));
        }
        for(int j = 0; j<v_shit.size() ; j++){
            E16ANA_SSDAnalyzedStripHit &h = v_shit[j];
            l_ssd_hitpos.clear();
            g_ssd_hitpos.clear();
            rot_ssd_pos.clear();
            l_ssd_hitpos.push_back(G4ThreeVector(h.CogHit(), 0, 0));
            g_ssd_hitpos.push_back(G4ThreeVector(geom_v2->SSD(kawama_module, 0)->GetGPos(l_ssd_hitpos[0])));
            rot_ssd_pos.push_back(G4ThreeVector(g_ssd_hitpos[0].rotateY(phi)));
            TVector2 rot_ssd = TVector2(rot_ssd_pos[0].x(), rot_ssd_pos[0].z());
            std::vector<long double> &&v_results2 = LeastSquareMethod(v_fit_samples, sigma_x);
//            v_fit_samples.push_back(TVector2(rot_ssd_pos[0].x(), rot_ssd_pos[0].z()));
//            std::vector<long double> &&v_results2 = LeastSquareMethod(v_fit_samples, sigma_x2);
//            v_fit_samples.pop_back();
            if(v_results2[0] < 50){
                std::shared_ptr<E16ANA_XZTrackCandidate> trk = std::make_shared<E16ANA_XZTrackCandidate>();
                trk->SetID100Hit(ts[t]->ID100Hit());
	           	trk->SetID200Hit(ts[t]->ID200Hit());
                trk->SetID300Hit(ts[t]->ID300Hit());
				trk->SetIDSSDHit(j);
        	    trk->SetModuleID(ts[t]->ModuleID());
		        trk->SetChi2(v_results2[0]);
		        trk->SetTgtZ(ReconstructTgtPosBeforeVertex(v_results2[1], v_results2[2], phi, kawama_module, geom_v2, trk));
                trk->SetResidualSSD((rot_ssd.Y() - (v_results2[1] + v_results2[2]*rot_ssd.X())));
//                trk->SetResidual100(v_results2[3]);
//	        	trk->SetResidual200(v_results2[4]);
//               trk->SetResidual300(v_results2[5]);
//	            trk->SetResidualSSD(v_results2[6]);
    	        trk->SetXHit100(ts[t]->GetXHit100());
	        	trk->SetXHit200(ts[t]->GetXHit200());
    	        trk->SetXHit300(ts[t]->GetXHit300());
    	        trk->SetXHitSSD(&h);
                trk->SetTrackID(index);
                xz_trks_evesel.push_back(trk);
                index++;
            }
            v_results2.clear();
        }
        }
    }
////    xz_trks_evesel.shrink_to_fit();
}

void StraightTrackAnalyzerV0::SearchSSDHit(std::vector<std::shared_ptr<E16ANA_XZCrossPoint>> &cps, std::vector<std::reference_wrapper<std::vector<E16ANA_SSDAnalyzedStripHit>>> &v_shits, E16ANA_GeometryV2 *geom_v2){
    std::vector<G4ThreeVector> l_hitpos;
    std::vector<G4ThreeVector> g_hitpos;
    std::vector<G4ThreeVector> rot_pos;
    std::vector<TVector2> v_fit_samples;
    std::vector<G4ThreeVector> l_ssd_hitpos;
    std::vector<G4ThreeVector> g_ssd_hitpos;
    std::vector<G4ThreeVector> rot_ssd_pos;
    std::vector<double> sigma_x = {0.1, 0.1, 0.1};//gtr0,1, 2 
    std::vector<double> sigma_x2 = {0.2, 0.2, 0.2, 0.1};//gtr0,1, 2 ssd
    int index = 0;
    for(int i=0; i<cps.size(); i++){
        std::shared_ptr<E16ANA_XZTrackCandidate> t1 = cps[i]->GetXZTrackCandidate1();
        std::shared_ptr<E16ANA_XZTrackCandidate> t2 = cps[i]->GetXZTrackCandidate2();
        std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> ts;
        ts.clear();
        ts.push_back(t1);
        ts.push_back(t2);
        for(int t=0; t<ts.size(); t++){
        std::vector<E16ANA_SSDAnalyzedStripHit> &v_shit = v_shits[ts[t]->ModuleID()-100];
        l_hitpos.clear();
        g_hitpos.clear();
        rot_pos.clear();
        v_fit_samples.clear();
        int kawama_module = ModuleID_2020to2013_33(ts[t]->ModuleID());
        double phi = GetGTRModulePhi(geom_v2, ts[t]->ModuleID());
        l_hitpos.push_back(G4ThreeVector(ts[t]->GetXHit100()->CogHit(), 0, 0));
        l_hitpos.push_back(G4ThreeVector(ts[t]->GetXHit200()->CogHit(), 0, 0));
        l_hitpos.push_back(G4ThreeVector(ts[t]->GetXHit300()->CogHit(), 0, 0));
        for(int l=0; l<l_hitpos.size(); l++){
            g_hitpos.push_back(G4ThreeVector(geom_v2->GTR(kawama_module, l)->GetGPos(l_hitpos[l])));
            rot_pos.push_back(G4ThreeVector(g_hitpos[l].rotateY(phi)));
            v_fit_samples.push_back(TVector2(rot_pos[l].x(), rot_pos[l].z()));
        }
        for(int j = 0; j<v_shit.size() ; j++){
            E16ANA_SSDAnalyzedStripHit &h = v_shit[j];
            l_ssd_hitpos.clear();
            g_ssd_hitpos.clear();
            rot_ssd_pos.clear();
            l_ssd_hitpos.push_back(G4ThreeVector(h.CogHit(), 0, 0));
            g_ssd_hitpos.push_back(G4ThreeVector(geom_v2->SSD(kawama_module, 0)->GetGPos(l_ssd_hitpos[0])));
            rot_ssd_pos.push_back(G4ThreeVector(g_ssd_hitpos[0].rotateY(phi)));
            TVector2 rot_ssd = TVector2(rot_ssd_pos[0].x(), rot_ssd_pos[0].z());
            std::vector<long double> &&v_results2 = LeastSquareMethod(v_fit_samples, sigma_x);
//            v_fit_samples.push_back(TVector2(rot_ssd_pos[0].x(), rot_ssd_pos[0].z()));
//            std::vector<long double> &&v_results2 = LeastSquareMethod(v_fit_samples, sigma_x2);
//            v_fit_samples.pop_back();
            if(v_results2[0] < 50){
                std::shared_ptr<E16ANA_XZTrackCandidate> trk = std::make_shared<E16ANA_XZTrackCandidate>();
                trk->SetID100Hit(ts[t]->ID100Hit());
	           	trk->SetID200Hit(ts[t]->ID200Hit());
                trk->SetID300Hit(ts[t]->ID300Hit());
				trk->SetIDSSDHit(j);
        	    trk->SetModuleID(ts[t]->ModuleID());
		        trk->SetChi2(v_results2[0]);
		        trk->SetTgtZ(ReconstructTgtPosBeforeVertex(v_results2[1], v_results2[2], phi, kawama_module, geom_v2, trk));
                trk->SetResidualSSD((rot_ssd.Y() - (v_results2[1] + v_results2[2]*rot_ssd.X())));
//                trk->SetResidual100(v_results2[3]);
//	        	trk->SetResidual200(v_results2[4]);
//               trk->SetResidual300(v_results2[5]);
//	            trk->SetResidualSSD(v_results2[6]);
    	        trk->SetXHit100(ts[t]->GetXHit100());
	        	trk->SetXHit200(ts[t]->GetXHit200());
    	        trk->SetXHit300(ts[t]->GetXHit300());
    	        trk->SetXHitSSD(&h);
                trk->SetTrackID(index);
                xz_trks_evesel.push_back(trk);
                index++;
            }
            v_results2.clear();
        }
        }
    }
////    xz_trks_evesel.shrink_to_fit();
}




void StraightTrackAnalyzerOfWire::FittingAfterTrackChoice(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trks, E16ANA_GeometryV2 *geom_v2){
    std::vector<int> v_s,v_0,v_1,v_2;
    v_s.clear();
    v_0.clear();
    v_1.clear();
    v_2.clear();
//    std::sort(xz_trks.begin(), xz_trks.end(), E16ANA_XZTrackCandidate::CompareTrackFunctor()); //compare chi2
//    std::sort(xz_trks.begin(), xz_trks.end(), E16ANA_XZTrackCandidate::CompareDistanceFunctor());
    std::sort(xz_trks.begin(), xz_trks.end(), E16ANA_XZTrackCandidate::CompareTrackFunctor());
	std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>>::const_iterator iter = xz_trks.begin();
    while (iter != xz_trks.end()){
        bool isOnlySSD = true;
        bool isOnly100 = true;
        bool isOnly200 = true;
        bool isOnly300 = true;
        for(int i=0; i< v_s.size(); i++){
            if(v_s[i] == (*iter)->IDSSDHit()){
                isOnlySSD = false;
            }
        }
        for(int i=0; i< v_0.size(); i++){
            if(v_0[i] == (*iter)->ID100Hit()){
                isOnly100 = false;
            }
        }
        for(int i=0; i< v_1.size(); i++){
            if(v_1[i] == (*iter)->ID200Hit()){
                isOnly200 = false;
            }
        }
        for(int i=0; i< v_2.size(); i++){
            if(v_2[i] == (*iter)->ID300Hit()){
                isOnly300 = false;
            }
        }
        if(isOnlySSD * isOnly100 * isOnly200 * isOnly300){
            v_s.push_back((*iter)->IDSSDHit());
            v_0.push_back((*iter)->ID100Hit());
            v_1.push_back((*iter)->ID200Hit());
            v_2.push_back((*iter)->ID300Hit());
            ++iter;
        }
        else{
            iter = xz_trks.erase(iter);
        }
    }
    int index = 0;
//    xz_trk_selected.resize(xz_trks.size());
    for(int i=0; i<xz_trks.size(); i++){
        std::shared_ptr<E16ANA_XZTrackCandidate> t = xz_trks[i];
        int kawama_module = ModuleID_2020to2013_33(t->ModuleID());
        double phi = GetGTRModulePhi(geom_v2, t->ModuleID());
        std::shared_ptr<E16ANA_XZTrackCandidate> trk = std::make_shared<E16ANA_XZTrackCandidate>();
        trk->SetModuleID(t->ModuleID());
        trk->SetXHit100(t->GetXHit100());
        trk->SetXHit200(t->GetXHit200());
        trk->SetXHit300(t->GetXHit300());
        trk->SetXHitSSD(t->GetXHitSSD());
        std::vector<long double> &&v_out3 = CalcChamberResidual(t->GetXHitSSD(), t->GetXHit100(), t->GetXHit200(), t->GetXHit300(), geom_v2,  phi, kawama_module, 3);// ssd
//        if(v_out != nullptr){
	        trk->SetChi2ExSSD(v_out3[0]); 
            trk->SetResidualSSD(v_out3[1]);
//            std::cout << "residual = " << v_out3[1] << std::endl;
//            trk->SetTgtZ(v_out3[2]);
//        }
        v_out3.clear();
        std::vector<long double> &&v_out0 = CalcChamberResidual(t->GetXHitSSD(), t->GetXHit100(), t->GetXHit200(), t->GetXHit300(), geom_v2, phi, kawama_module, 0);// gtr0
//        if(v_out0 != nullptr){
	        trk->SetChi2Ex100(v_out0[0]);
            trk->SetResidual100(v_out0[1]);
//            trk->SetTgtZ(v_out0[2]);
//        }
        v_out0.clear();
 
        std::vector<long double> &&v_out1 = CalcChamberResidual(t->GetXHitSSD(), t->GetXHit100(), t->GetXHit200(), t->GetXHit300(), geom_v2,phi, kawama_module, 1);// gtr1
//        if(v_out1 != nullptr){
//	        trk->SetChi2(v_out1[0]);
	        trk->SetChi2Ex200(v_out1[0]);
            trk->SetResidual200(v_out1[1]);
            trk->SetTgtZ(v_out1[2]);
//        }
        v_out1.clear();

        std::vector<long double> &&v_out2 = CalcChamberResidual(t->GetXHitSSD(), t->GetXHit100(), t->GetXHit200(), t->GetXHit300(), geom_v2,phi, kawama_module, 2);// gtr2
//        if(v_out2 != nullptr){
//	        trk->SetChi2(v_out2[0]);
	        trk->SetChi2Ex300(v_out2[0]);
            trk->SetResidual300(v_out2[1]);
//            trk->SetTgtZ(v_out2[2]);
//        }
        v_out2.clear();
        xz_trk_selected.push_back(trk);
        index++;
    }
    /*
    std::vector<G4ThreeVector> l_hitpos;
    std::vector<G4ThreeVector> g_hitpos;
    std::vector<G4ThreeVector> rot_pos;
    std::vector<G4ThreeVector> l_ssd_hitpos;
    std::vector<G4ThreeVector> g_ssd_hitpos;
    std::vector<G4ThreeVector> rot_ssd_pos;
    std::vector<TVector2> v_fit_samples ;
    std::vector<double> sigma_x = {1.5, 1.5, 1.5};
    std::vector<double> sigma_x2 = {1.0, 1.0, 1.0, 1.0};//gtr0,1,2, wire
    G4ThreeVector g_wirepos1 = G4ThreeVector(-20, 0, -40);
    G4ThreeVector g_wirepos2 = G4ThreeVector(-20, 0, 40);
    int index = 0;
    xz_trk_selected.resize(xz_trks.size());
    for(int i=0; i<xz_trks.size(); i++){
        E16ANA_XZTrackCandidate &t = xz_trks[i];
        int kawama_module = ModuleID_2020to2013_33(t.ModuleID());
        double phi = GetGTRModulePhi(geom_v2, t.ModuleID());
        G4ThreeVector rot_wirepos1 = G4ThreeVector(g_wirepos1.rotateY(phi));
        G4ThreeVector rot_wirepos2 = G4ThreeVector(g_wirepos2.rotateY(phi));
        TVector2 tv_rotwire1 = TVector2(rot_wirepos1.x(), rot_wirepos1.z());
        TVector2 tv_rotwire2 = TVector2(rot_wirepos2.x(), rot_wirepos2.z());
        E16ANA_SSDAnalyzedStripHit &hs = t.GetXHitSSD();
        E16ANA_GTRAnalyzedStripHit &h0 = t.GetXHit100();
        E16ANA_GTRAnalyzedStripHit &h1 = t.GetXHit200();
        E16ANA_GTRAnalyzedStripHit &h2 = t.GetXHit300();
        l_hitpos.clear();
        g_hitpos.clear();
        rot_pos.clear();
        v_fit_samples.clear();
        l_hitpos.push_back(G4ThreeVector(h0.CogHit(), 0, 0));
        l_hitpos.push_back(G4ThreeVector(h1.CogHit(), 0, 0));
        l_hitpos.push_back(G4ThreeVector(h2.CogHit(), 0, 0));
        g_hitpos.push_back(G4ThreeVector(geom_v2->GTR(kawama_module, 0)->GetGPos(l_hitpos[0])));
        g_hitpos.push_back(G4ThreeVector(geom_v2->GTR(kawama_module, 1)->GetGPos(l_hitpos[1])));
        g_hitpos.push_back(G4ThreeVector(geom_v2->GTR(kawama_module, 2)->GetGPos(l_hitpos[2])));
        rot_pos.push_back(G4ThreeVector(g_hitpos[0].rotateY(phi)));
        rot_pos.push_back(G4ThreeVector(g_hitpos[1].rotateY(phi)));
        rot_pos.push_back(G4ThreeVector(g_hitpos[2].rotateY(phi)));
        v_fit_samples.push_back(TVector2(rot_pos[0].x(), rot_pos[0].z()));
        v_fit_samples.push_back(TVector2(rot_pos[1].x(), rot_pos[1].z()));
        v_fit_samples.push_back(TVector2(rot_pos[2].x(), rot_pos[2].z()));
        l_ssd_hitpos.push_back(G4ThreeVector(hs.CogHit(), 0, 0));
        g_ssd_hitpos.push_back(G4ThreeVector(geom_v2->SSD(kawama_module, 0)->GetGPos(l_ssd_hitpos[0])));
        rot_ssd_pos.push_back(G4ThreeVector(g_ssd_hitpos[0].rotateY(phi)));
        TVector2 rot_ssd = TVector2(rot_ssd_pos[0].x(), rot_ssd_pos[0].z());
        l_ssd_hitpos.clear();
        g_ssd_hitpos.clear();
        rot_ssd_pos.clear();
        std::vector<double> &&v_results1 = LeastSquareMethod(v_fit_samples, sigma_x);//return chi2, a, b (a+bx)

		double cross_beam = ReconstructTgtPosBeforeVertex(v_results1[1], v_results1[2], phi, kawama_module, geom_v2);
        std::cout << "cross beam" << cross_beam << std::endl;
        if(fabs(cross_beam + 40) <  20){
            v_fit_samples.push_back(tv_rotwire1);
            std::vector<double> &&v_results2 = LeastSquareMethod(v_fit_samples, sigma_x2);
            std::cout << "chi2 = " << v_results2[0] << std::endl;
            E16ANA_XZTrackCandidate &trk = xz_trk_selected[index];
        	trk.SetModuleID(t.ModuleID());
		    trk.SetChi2(v_results2[0]);
            trk.SetResidualSSD(rot_ssd.Y() - (v_results2[1] + v_results2[2]*rot_ssd.X() ));
            std::cout <<"residual ssd = " << rot_ssd.Y() - (v_results2[1] + v_results2[2]*rot_ssd.X()) << std::endl;
		    trk.SetTgtZ(ReconstructTgtPosBeforeVertex(v_results2[1], v_results2[2], phi, kawama_module, geom_v2, &trk));
            index++;
            v_results2.clear();
        }
        if(fabs(cross_beam - 40) <  20){
            v_fit_samples.push_back(tv_rotwire2);
            std::vector<double> &&v_results2 = LeastSquareMethod(v_fit_samples, sigma_x2);
            E16ANA_XZTrackCandidate &trk = xz_trk_selected[index];
        	trk.SetModuleID(t.ModuleID());
		    trk.SetChi2(v_results2[0]);
            trk.SetResidualSSD(rot_ssd.Y() - (v_results2[1] + v_results2[2]*rot_ssd.X() ));
		    trk.SetTgtZ(ReconstructTgtPosBeforeVertex(v_results2[1], v_results2[2], phi, kawama_module, geom_v2, &trk));
            index++;
            v_results2.clear();

        }

        v_results1.clear();
    }
    xz_trk_selected.resize(index);
*/
}

std::vector<long double> StraightTrackAnalyzerOfWire::CalcChamberResidual(E16ANA_SSDAnalyzedStripHit *hs, E16ANA_GTRAnalyzedStripHit *h0, E16ANA_GTRAnalyzedStripHit *h1, E16ANA_GTRAnalyzedStripHit *h2, E16ANA_GeometryV2 *geom_v2, double phi, int kawama_module, int except){
    if(except < 0 || except > 3){
        std::cout << " except value is invalid !" << std::endl;
    }
    std::vector<G4ThreeVector> l_hitpos;
    std::vector<G4ThreeVector> g_hitpos;
    std::vector<G4ThreeVector> rot_pos;
    std::vector<G4ThreeVector> l_ssd_hitpos;
    std::vector<G4ThreeVector> g_ssd_hitpos;
    std::vector<G4ThreeVector> rot_ssd_pos;
    std::vector<TVector2> v_fit_samples ;
    l_hitpos.clear();
    g_hitpos.clear();
    rot_pos.clear();
    v_fit_samples.clear();
    G4ThreeVector g_wirepos1 = G4ThreeVector(-20, 0, -40);
    G4ThreeVector g_wirepos2 = G4ThreeVector(-20, 0, 40);
    G4ThreeVector rot_wirepos1 = G4ThreeVector(g_wirepos1.rotateY(phi));
    G4ThreeVector rot_wirepos2 = G4ThreeVector(g_wirepos2.rotateY(phi));
    TVector2 tv_rotwire1 = TVector2(rot_wirepos1.x(), rot_wirepos1.z());
    TVector2 tv_rotwire2 = TVector2(rot_wirepos2.x(), rot_wirepos2.z());
    if(except == 3){//ssd
       std::vector<double> sigma_x = {1.5, 1.5, 1.5};
       std::vector<double> sigma_x2 = {0.1, 0.1, 0.2, 0.1};//gtr0,1,2, wire
//       std::vector<reference_wrapper<E16ANA_GTRAnalyzedStripHit>>hits;
       std::vector<E16ANA_GTRAnalyzedStripHit *>hits;
       hits.clear();
       hits.push_back(h0);
       hits.push_back(h1);
       hits.push_back(h2);
       l_ssd_hitpos.push_back(G4ThreeVector(hs->CogHit(), 0, 0));
       g_ssd_hitpos.push_back(G4ThreeVector(geom_v2->SSD(kawama_module, 0)->GetGPos(l_ssd_hitpos[0])));
       rot_ssd_pos.push_back(G4ThreeVector(g_ssd_hitpos[0].rotateY(phi)));
       TVector2 rot_ssd = TVector2(rot_ssd_pos[0].x(), rot_ssd_pos[0].z());
       l_ssd_hitpos.clear();
       g_ssd_hitpos.clear();
       rot_ssd_pos.clear();
       for(int l = 0; l <3; l++){
           l_hitpos.push_back(G4ThreeVector(hits[l]->CogHit(), 0, 0));
           g_hitpos.push_back(G4ThreeVector(geom_v2->GTR(kawama_module, l)->GetGPos(l_hitpos[l])));
           rot_pos.push_back(G4ThreeVector(g_hitpos[l].rotateY(phi)));
           v_fit_samples.push_back(TVector2(rot_pos[l].x(), rot_pos[l].z()));
       }
       std::vector<long double> &&v_results1 = LeastSquareMethod(v_fit_samples, sigma_x);//return chi2, a, b (a+bx)
   	double cross_beam = ReconstructTgtPosBeforeVertex(v_results1[1], v_results1[2], phi, kawama_module, geom_v2);
        if(fabs(cross_beam + 40) <  20){
            v_fit_samples.push_back(tv_rotwire1);
            std::vector<long double> &&v_results2 = LeastSquareMethod(v_fit_samples, sigma_x2);
//            std::cout << "chi2 = " << v_results2[0] << std::endl;
                double residual_s = (rot_ssd.Y() - (v_results2[1] + v_results2[2]*rot_ssd.X()));
//                std::cout <<"residu_s al ssd = " << rot_ssd.Y() - (v_results2[1] + v_results2[2]*rot_ssd.X()) << std::endl;
                
       	        double tgt_z = ReconstructTgtPosBeforeVertex(v_results2[1], v_results2[2], phi, kawama_module, geom_v2);
                v_results2.clear();
                std::vector <long double> &&v_out = {v_results2[0], residual_s, tgt_z};
                return v_out;
        }
        else if(fabs(cross_beam - 40) <  20){
            v_fit_samples.push_back(tv_rotwire2);
            std::vector<long double> &&v_results2 = LeastSquareMethod(v_fit_samples, sigma_x2);
//            std::cout << "chi2 = " << v_results2[0] << std::endl;
            double residual_s = (rot_ssd.Y() - (v_results2[1] + v_results2[2]*rot_ssd.X()));
//            std::cout <<"residual ssd = " << residual_s << std::endl;
   	        double tgt_z = ReconstructTgtPosBeforeVertex(v_results2[1], v_results2[2], phi, kawama_module, geom_v2);
            v_results2.clear();
            std::vector <long double> &&v_out = {v_results2[0], residual_s, tgt_z};
            return v_out;
        }
    }
    else{//except == 0,1,2
       std::vector<double> sigma_x = {1.5, 1.5, 1.5};
       std::vector<double> sigma_x2 = {0.1, 0.1, 0.05, 0.1};//gtr?,?, ssd, wire
       std::vector<E16ANA_GTRAnalyzedStripHit *>hits;
       hits.clear();
       hits.push_back(h0);
       hits.push_back(h1);
       hits.push_back(h2);
       l_ssd_hitpos.clear();
       g_ssd_hitpos.clear();
       rot_ssd_pos.clear();
       l_ssd_hitpos.push_back(G4ThreeVector(hs->CogHit(), 0, 0));
       g_ssd_hitpos.push_back(G4ThreeVector(geom_v2->SSD(kawama_module, 0)->GetGPos(l_ssd_hitpos[0])));
       rot_ssd_pos.push_back(G4ThreeVector(g_ssd_hitpos[0].rotateY(phi)));
       TVector2 rot_ssd = TVector2(rot_ssd_pos[0].x(), rot_ssd_pos[0].z());
       for(int l = 0; l <3; l++){
           l_hitpos.push_back(G4ThreeVector(hits[l]->CogHit(), 0, 0));
//           std::cout << "hits cog = " << hits[l].get().CogHit() << std::endl;
           g_hitpos.push_back(G4ThreeVector(geom_v2->GTR(kawama_module, l)->GetGPos(l_hitpos[l])));
//           std::cout << "g hit pos y = " << g_hitpos[l].z() << std::endl;
           rot_pos.push_back(G4ThreeVector(g_hitpos[l].rotateY(phi)));
//           std::cout << "rot pos z = " << rot_pos[l].z() << std::endl;
       }
       for(int l=0; l < 3; l++){
           if(except == l ) continue;
           v_fit_samples.push_back(TVector2(rot_pos[l].x(), rot_pos[l].z()));
       }
       v_fit_samples.push_back(rot_ssd);
       std::vector<long double> &&v_results1 = LeastSquareMethod(v_fit_samples, sigma_x);//return chi2, a, b (a+bx)
   	   double cross_beam = ReconstructTgtPosBeforeVertex(v_results1[1], v_results1[2], phi, kawama_module, geom_v2);
       if(cross_beam < 0){
           v_fit_samples.push_back(tv_rotwire1);
           std::vector<long double> &&v_results2 = LeastSquareMethod(v_fit_samples, sigma_x2);
//           std::cout << "chi2 = " << v_results2[0] << std::endl;
           double residual_g = (rot_pos[except].z() - (v_results2[1] + v_results2[2]*rot_pos[except].x()));
           std::cout <<"residual gtr = " << residual_g << std::endl;
//           std::cout << "rot pos X = " << rot_pos[except].x() << std::endl;
//           std::cout << "v results 2[1]  = " << v_results2[1] << std::endl;
//           std::cout << "a + bx  = " << v_results2[1] + v_results2[2] * rot_pos[except].x() << std::endl;
   	       double tgt_z = ReconstructTgtPosBeforeVertex(v_results2[1], v_results2[2], phi, kawama_module, geom_v2);
//           std::cout <<"tgt -40  gtr = " << tgt_z << std::endl;
           v_results2.clear();
           std::vector <long double> &&v_out = {v_results2[0], residual_g, tgt_z};
           return v_out;
       }
       else if(cross_beam >= 0){
           v_fit_samples.push_back(tv_rotwire2);
           std::vector<long double> &&v_results2 = LeastSquareMethod(v_fit_samples, sigma_x2);
//           std::cout << "chi2 = " << v_results2[0] << std::endl;
           double residual_g = rot_pos[except].z() - (v_results2[1] + v_results2[2]*rot_pos[except].x()) ;
           std::cout <<"residual gtr = " << residual_g << std::endl;
   	       double tgt_z = ReconstructTgtPosBeforeVertex(v_results2[1], v_results2[2], phi, kawama_module, geom_v2);
//           std::cout <<"tgt +40  gtr = " << tgt_z << std::endl;
           v_results2.clear();
           std::vector <long double> &&v_out = {v_results2[0], residual_g, tgt_z};
           return v_out;
       }
    }
}

void StraightTrackAnalyzerOfWireV1::XZStraightAnalyzeOnlyGTR2(std::vector<E16DST_DST1SSDCluster*> &ssd_xhits, std::vector<E16DST_DST1GTRCluster*> &gtr_xhits0,std::vector<E16DST_DST1GTRCluster*> &gtr_xhits1, std::vector<E16DST_DST1GTRCluster*> &gtr_xhits2, int mid, E16ANA_GeometryV2 *geom_v2){
    std::vector<G4ThreeVector> l_hitpos, g_hitpos, rot_pos, l_ssd_hitpos, g_ssd_hitpos, rot_ssd_pos;
    std::vector<TVector2> v_fit_samples ;
    std::vector<double> sigma_x = {0.3, 0.3, 0.3};
	int kawama_module = E16DST_DST1Constant::kModuleId2020To2013[mid/100][mid%100];
    double phi = GetGTRModulePhi(geom_v2, mid);
	double rphi = 0;
	if(101<mid&&mid<109) rphi = Agtr[mid-102];
    int index = 0;
//	std::cout << "100 size = " << gtr_xhits0.size() << ", 200 size = " << gtr_xhits1.size() << ", 300 size = " << gtr_xhits2.size() << std::endl;
//	std::cout <<"gtrxhit size = " <<  gtr_xhits0.size() * gtr_xhits1.size() * gtr_xhits2.size() << std::endl;
    for(int i=0; i < (int)gtr_xhits0.size(); i++){
        for(int j=0; j < (int)gtr_xhits1.size(); j++){
            for(int k=0; k < (int)gtr_xhits2.size(); k++){
                std::vector<E16DST_DST1GTRCluster*> hits;
                hits.clear();
                hits.push_back(gtr_xhits0[i]);
                hits.push_back(gtr_xhits1[j]);
                hits.push_back(gtr_xhits2[k]);
                l_hitpos.clear();
                g_hitpos.clear();
                rot_pos.clear();
                v_fit_samples.clear();
                for(int l = 0; l <3; l++){
//                    std::cout << "cog pos" << hits[l]->CogPos() << std::endl;
                    l_hitpos.push_back(G4ThreeVector(hits[l]->CogPos(), 0, 0));
                    g_hitpos.push_back(G4ThreeVector(geom_v2->GTR(kawama_module, l)->GetGPos(l_hitpos[l])));
//                    rot_pos.push_back(G4ThreeVector(g_hitpos[l].rotateY(phi)));
                    rot_pos.push_back(G4ThreeVector(g_hitpos[l].rotateY(rphi)));
                    //v_fit_samples.push_back(TVector2(rot_pos[l].x(), rot_pos[l].z()));
                    v_fit_samples.push_back(TVector2(rot_pos[l].z(), rot_pos[l].x()));
                }
                std::vector<long double> &&v_results1 = LeastSquareMethod(v_fit_samples, sigma_x);//return chi2, a, b (a+bx)
                if(v_results1[0] < th_chi2_first){
//				std::cout <<"chi2  = " <<  v_results1[0] << std::endl;
					double min = 9999;
					double min2 = 9999;
					int id_m = 0;
					for(int m=0; m<(int)ssd_xhits.size(); m++){
						E16DST_DST1SSDCluster* hssd1 = ssd_xhits[m];
						G4ThreeVector ref = G4ThreeVector(geom_v2->SSD(kawama_module, 0)->GetGPos(G4ThreeVector(hssd1->CogPos(),0, 0)));
						G4ThreeVector ref2 = ref.rotateY(rphi);
						double resx = fabs(ref2.x() - (ref2.z() * v_results1[2] + v_results1[1]));
						if(resx < min){
							id_m = m;
							min2 = min;
							min = resx;
						}
						else if(resx < min2){		
							min2 = resx;
						}
					}
					for(int m = id_m; m<id_m+1; m++){
						if(ssd_xhits.size() == 0 )continue;
						E16DST_DST1SSDCluster* hssd = ssd_xhits[m];
						
						l_ssd_hitpos.clear();	
						g_ssd_hitpos.clear();	
						rot_ssd_pos.clear();
						l_ssd_hitpos.push_back(G4ThreeVector(hssd->CogPos(), 0, 0));
						g_ssd_hitpos.push_back(G4ThreeVector(geom_v2->SSD(kawama_module, 0)->GetGPos(l_ssd_hitpos[0])));
						rot_ssd_pos.push_back(G4ThreeVector(g_ssd_hitpos[0].rotateY(rphi)));
						std::vector<long double> &&v_results2 = LeastSquareMethod(v_fit_samples, sigma_x);//wo SSD
						if(v_results2[0] < th_chi2_second){
                        std::shared_ptr<E16ANA_XZTrackCandidate> trk = std::make_shared<E16ANA_XZTrackCandidate>();
 						trk->SetResidualSSD2(min2);	
						trk->SetResidualSSD(rot_ssd_pos[0].x() - (rot_ssd_pos[0].z()*v_results2[2] + v_results2[1]));
						trk->SetResidual100(rot_pos[0].x() - (rot_pos[0].z()*v_results2[2]+v_results2[1]));
						trk->SetResidual200(rot_pos[1].x() - (rot_pos[1].z()*v_results2[2]+v_results2[1]));
						trk->SetResidual300(rot_pos[2].x() - (rot_pos[2].z()*v_results2[2]+v_results2[1]));
						trk->SetFitA(v_results2[1]);
						trk->SetFitB(v_results2[2]);
						//G4ThreeVector rot_pt0 = G4ThreeVector(rot_pos[0].x(), 0, rot_pos[0].z()*v_results2[2]+v_results2[1]);//comment out by nakasuga
						G4ThreeVector rot_pt0 = G4ThreeVector(rot_pos[0].z()*v_results2[2]+v_results2[1],0,rot_pos[0].z());//nakasuga
						G4ThreeVector glb_origin0 = rot_pt0.rotateY(-rphi);
						trk->SetFitPtOnGTR100(TVector2(glb_origin0.x(), glb_origin0.z()));
					
						//G4ThreeVector rot_pt1 = G4ThreeVector(rot_pos[1].x(), 0, rot_pos[1].z()*v_results2[2]+v_results2[1]);//comment out by nakasuga
						G4ThreeVector rot_pt1 = G4ThreeVector(rot_pos[1].z()*v_results2[2]+v_results2[1], 0, rot_pos[1].z());//nakasuga
						G4ThreeVector glb_origin1 = rot_pt1.rotateY(-rphi);
						trk->SetFitPtOnGTR200(TVector2(glb_origin1.x(), glb_origin1.z()));


						//G4ThreeVector rot_pt2 = G4ThreeVector(rot_pos[2].x(), 0, rot_pos[2].z()*v_results2[2]+v_results2[1]);//comment out by nakasuga
						G4ThreeVector rot_pt2 = G4ThreeVector(rot_pos[2].z()*v_results2[2]+v_results2[1], 0, rot_pos[2].z());//nakasuga
						G4ThreeVector glb_origin2 = rot_pt2.rotateY(-rphi);
						trk->SetFitPtOnGTR300(TVector2(glb_origin2.x(), glb_origin2.z()));
	
//						trk->SetFitPointOn100(TVector2());
						trk->SetFitResSSD(TVector2(rot_ssd_pos[0].z()*v_results2[2] + v_results2[1], rot_ssd_pos[0].z()));
						trk->SetFitRes100(TVector2(rot_pos[0].z()*v_results2[2] + v_results2[1], rot_pos[0].z()));
						trk->SetFitRes200(TVector2(rot_pos[1].z()*v_results2[2] + v_results2[1], rot_pos[1].z()));
						trk->SetFitRes300(TVector2(rot_pos[2].z()*v_results2[2] + v_results2[1], rot_pos[2].z()));
						trk->SetIDSSDHit(m);
                        trk->SetID100Hit(i);
	           	        trk->SetID200Hit(j);
            	        trk->SetID300Hit(k);
    	            	trk->SetModuleID(mid);
	                    trk->SetChi2(v_results1[0]);
		                trk->SetTgtZ(ReconstructTgtPosBeforeVertex(v_results1[1], v_results1[2], phi, kawama_module, geom_v2, trk));
//                        trk->SetResidual100(v_results2[3]);
//	        	        trk->SetResidual200(v_results2[4]);
//               	        trk->SetResidual300(v_results2[5]);
						
						TVector2 w1(wire_x1, wire_z1);
						TVector2 w2(wire_x2, wire_z2);
						TVector2 rot_w1 = w1.Rotate(-rphi);
						TVector2 rot_w2 = w2.Rotate(-rphi);
						double dis1 = (rot_w1.Y()*v_results2[2]-(rot_w1.X()) + v_results2[1])/sqrt(1+v_results2[2]*v_results2[2]);
						double dis2 = (rot_w2.Y()*v_results2[2]-(rot_w2.X()) + v_results2[1])/sqrt(1+v_results2[2]*v_results2[2]);
						trk->SetDistance(dis1);
						if(fabs(dis2)< fabs(dis1)) trk->SetDistance(dis2);
                    	trk->SetXHit100(hits[0]);
        	            trk->SetXHit200(hits[1]);
    	        	    trk->SetXHit300(hits[2]);
    	        	    trk->SetXHitSSD(hssd);
                        trk->SetTrackID(index);
                        xz_trk_cands.push_back(trk);
                        index++;
						}
						v_results2.clear();
					}
				}
                v_results1.clear();
            }
        }
    }
//	std::cout << "traksss " << index << std::endl;
	ssd_xhits.clear();
	gtr_xhits0.clear();
	gtr_xhits1.clear();
	gtr_xhits2.clear();
	ssd_xhits.shrink_to_fit();
	gtr_xhits0.shrink_to_fit();
	gtr_xhits1.shrink_to_fit();
	gtr_xhits2.shrink_to_fit();
}



void StraightTrackAnalyzerOfWireV1::XZStraightAnalyzeOnlyGTR(std::vector<E16ANA_SSDAnalyzedStripHit> &ssd_hits, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_xhits0, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_xhits1, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_xhits2, int mid, E16ANA_GeometryV2 *geom_v2){
    std::vector<G4ThreeVector> l_hitpos;
    std::vector<G4ThreeVector> g_hitpos;
    std::vector<G4ThreeVector> rot_pos;
    std::vector<G4ThreeVector> l_ssd_hitpos;
    std::vector<G4ThreeVector> g_ssd_hitpos;
    std::vector<G4ThreeVector> rot_ssd_pos;
    std::vector<TVector2> v_fit_samples ;
    std::vector<double> sigma_x = {0.2, 0.2, 0.2};
	int kawama_module = E16DST_DST1Constant::kModuleId2020To2013[mid/100][mid%100];
    double phi = GetGTRModulePhi(geom_v2, mid);
    int index = 0;
    for(int i=0; i < (int)gtr_xhits0.size(); i++){
        for(int j=0; j < (int)gtr_xhits1.size(); j++){
            for(int k=0; k < (int)gtr_xhits2.size(); k++){
                std::vector<std::reference_wrapper<E16ANA_GTRAnalyzedStripHit>> hits;
                hits.clear();
                hits.push_back(gtr_xhits0[i]);
                hits.push_back(gtr_xhits1[j]);
                hits.push_back(gtr_xhits2[k]);
                l_hitpos.clear();
                g_hitpos.clear();
                rot_pos.clear();
                v_fit_samples.clear();
                for(int l = 0; l <3; l++){
                    l_hitpos.push_back(G4ThreeVector(hits[l].get().CogHit(), 0, 0));
                    g_hitpos.push_back(G4ThreeVector(geom_v2->GTR(kawama_module, l)->GetGPos(l_hitpos[l])));
                    rot_pos.push_back(G4ThreeVector(g_hitpos[l].rotateY(phi)));
                    v_fit_samples.push_back(TVector2(rot_pos[l].x(), rot_pos[l].z()));
                }
                std::vector<long double> &&v_results1 = LeastSquareMethod(v_fit_samples, sigma_x);//return chi2, a, b (a+bx)
                if(v_results1[0] < th_chi2_first){
                        std::shared_ptr<E16ANA_XZTrackCandidate> trk = std::make_shared<E16ANA_XZTrackCandidate>();
                        trk->SetID100Hit(i);
	           	        trk->SetID200Hit(j);
            	        trk->SetID300Hit(k);
    	            	trk->SetModuleID(mid);
	                    trk->SetChi2(v_results1[0]);
		                trk->SetTgtZ(ReconstructTgtPosBeforeVertex(v_results1[1], v_results1[2], phi, kawama_module, geom_v2, trk));
//                        trk->SetResidual100(v_results2[3]);
//	        	        trk->SetResidual200(v_results2[4]);
//               	        trk->SetResidual300(v_results2[5]);
                    	trk->SetXHit100(&hits[0].get());
        	            trk->SetXHit200(&hits[1].get());
    	        	    trk->SetXHit300(&hits[2].get());
                        trk->SetTrackID(index);
                        xz_trk_cands.push_back(trk);
                        index++;
                    }
                    v_results1.clear();
            }
        }
    }
}
void StraightTrackAnalyzerV0::XZStraightAnalyzeOnlyGTR(std::vector<E16ANA_SSDAnalyzedStripHit> &ssd_hits, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_xhits0, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_xhits1, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_xhits2, int mid, E16ANA_GeometryV2 *geom_v2){
    std::vector<G4ThreeVector> l_hitpos;
    std::vector<G4ThreeVector> g_hitpos;
    std::vector<G4ThreeVector> rot_pos;
    std::vector<G4ThreeVector> l_ssd_hitpos;
    std::vector<G4ThreeVector> g_ssd_hitpos;
    std::vector<G4ThreeVector> rot_ssd_pos;
    std::vector<TVector2> v_fit_samples ;
    std::vector<double> sigma_x = {0.2, 0.2, 0.2};
	int kawama_module = E16DST_DST1Constant::kModuleId2020To2013[mid/100][mid%100];
    double phi = GetGTRModulePhi(geom_v2, mid);
    int index = 0;
    for(int i=0; i < (int)gtr_xhits0.size(); i++){
        for(int j=0; j < (int)gtr_xhits1.size(); j++){
            for(int k=0; k < (int)gtr_xhits2.size(); k++){
                std::vector<std::reference_wrapper<E16ANA_GTRAnalyzedStripHit>> hits;
                hits.clear();
                hits.push_back(gtr_xhits0[i]);
                hits.push_back(gtr_xhits1[j]);
                hits.push_back(gtr_xhits2[k]);
                l_hitpos.clear();
                g_hitpos.clear();
                rot_pos.clear();
                v_fit_samples.clear();
                for(int l = 0; l <3; l++){
                    l_hitpos.push_back(G4ThreeVector(hits[l].get().CogHit(), 0, 0));
                    g_hitpos.push_back(G4ThreeVector(geom_v2->GTR(kawama_module, l)->GetGPos(l_hitpos[l])));
                    rot_pos.push_back(G4ThreeVector(g_hitpos[l].rotateY(phi)));
                    v_fit_samples.push_back(TVector2(rot_pos[l].x(), rot_pos[l].z()));
                }
                std::vector<long double> &&v_results1 = LeastSquareMethod(v_fit_samples, sigma_x);//return chi2, a, b (a+bx)
                if(v_results1[0] < th_chi2_first){
                        std::shared_ptr<E16ANA_XZTrackCandidate> trk = std::make_shared<E16ANA_XZTrackCandidate>();
                        trk->SetID100Hit(i);
	           	        trk->SetID200Hit(j);
            	        trk->SetID300Hit(k);
    	            	trk->SetModuleID(mid);
	                    trk->SetChi2(v_results1[0]);
		                trk->SetTgtZ(ReconstructTgtPosBeforeVertex(v_results1[1], v_results1[2], phi, kawama_module, geom_v2, trk));
//                        trk->SetResidual100(v_results2[3]);
//	        	        trk->SetResidual200(v_results2[4]);
//               	        trk->SetResidual300(v_results2[5]);
                    	trk->SetXHit100(&hits[0].get());
        	            trk->SetXHit200(&hits[1].get());
    	        	    trk->SetXHit300(&hits[2].get());
                        trk->SetTrackID(index);
                        xz_trk_cands.push_back(trk);
                        index++;
                    }
                    v_results1.clear();
            }
        }
    }
}

void StraightTrackAnalyzerOfWireV1::YRStraightAnalyze2(std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0, std::vector<E16DST_DST1GTRCluster*> &gtr_yhits0b, std::vector<E16DST_DST1GTRCluster*> &gtr_yhits1, std::vector<E16DST_DST1GTRCluster*> &gtr_yhits2, int mid, E16ANA_GeometryV2 *geom_v2){
	int kawama_module = E16DST_DST1Constant::kModuleId2020To2013[mid/100][mid%100];
    double phi = GetGTRModulePhi(geom_v2, mid);
    double rphi = phi - 1.570796;
	std::vector<double> sigma_y = {0.5, 0.5, 0.5};	
	std::vector<TVector2> v_fit_samples; 
	std::vector<G4ThreeVector> l_hitpos, g_hitpos, rot_pos;
    G4ThreeVector pos_100 = ((geom_v2->GTR(kawama_module, 0)->GetGPos(G4ThreeVector(0,0,0))));
	double r100_2 = pos_100.x()*pos_100.x() + pos_100.y()*pos_100.y() + pos_100.z()*pos_100.z();
	double r100  = sqrt(r100_2);
    G4ThreeVector pos_300 = ((geom_v2->GTR(kawama_module, 2)->GetGPos(G4ThreeVector(0,0,0))));
	double r300_2 = pos_300.x()*pos_300.x() + pos_300.y()*pos_300.y() + pos_300.z()*pos_300.z();
	double r300  = sqrt(r300_2);
    double r3000 = r300 * 10;
	for(int i = 0; i<(int)gtr_yhits0.size(); i++){
		for(int j = 0; j<(int)gtr_yhits1.size(); j++){
			for(int k = 0; k<(int)gtr_yhits2.size(); k++){
                std::vector<E16DST_DST1GTRCluster*> hits;
                hits.clear();
                hits.push_back(gtr_yhits0[i]);
                hits.push_back(gtr_yhits1[j]);
                hits.push_back(gtr_yhits2[k]);
                l_hitpos.clear();
                g_hitpos.clear();
                rot_pos.clear();
                v_fit_samples.clear();
                for(int l = 0; l <3; l++){
                    l_hitpos.push_back(G4ThreeVector(0, hits[l]->CogPos(), 0));
                    g_hitpos.push_back(G4ThreeVector(geom_v2->GTR(kawama_module, l)->GetGPos(l_hitpos[l])));
                    rot_pos.push_back(G4ThreeVector(g_hitpos[l].rotateY(rphi)));
                    //v_fit_samples.push_back(TVector2(rot_pos[l].x(), rot_pos[l].y()));
                    v_fit_samples.push_back(TVector2(rot_pos[l].z(), rot_pos[l].y()));
                }
  //              std::cout << "v fir sample = " << v_fit_samples[2].Y() << std::endl;
				std::vector<long double> &&v_results = LeastSquareMethod(v_fit_samples, sigma_y );//return chi2, a,b (a+bx)
//                std::cout << "v result" << v_results[1] << std::endl;
				if(v_results[0] < th_chi2_y){
                    std::shared_ptr<E16ANA_YTrackCandidate> trk = std::make_shared<E16ANA_YTrackCandidate>();
//    				trk->SetInvalid();
					trk->SetModuleID(mid);
//					y_trk_cand[index].SetChi2(v_results[0]);
                    trk->SetChi2(v_results[0]);
					trk->SetResidual100(rot_pos[0].y() - (rot_pos[0].z()*v_results[2]+v_results[1]));
					trk->SetResidual200(rot_pos[1].y() - (rot_pos[1].z()*v_results[2]+v_results[1]));
					trk->SetResidual300(rot_pos[2].y() - (rot_pos[2].z()*v_results[2]+v_results[1]));
					trk->SetFitA(v_results[1]);
					trk->SetFitB(v_results[2]);

					trk->SetFitRes100(TVector2(rot_pos[0].z()*v_results[2]+v_results[1], rot_pos[0].z()));
					trk->SetFitRes200(TVector2(rot_pos[1].z()*v_results[2]+v_results[1], rot_pos[1].z()));
					trk->SetFitRes300(TVector2(rot_pos[2].z()*v_results[2]+v_results[1], rot_pos[2].z()));
					TVector2 w1(wire_x1, wire_z1);
					TVector2 w2(wire_x2, wire_z2);
					TVector2 rot_w1 = w1.Rotate(-rphi);
					TVector2 rot_w2 = w2.Rotate(-rphi);
					double dis1 = (rot_w1.Y()*v_results[2] + v_results[1])/sqrt(1+v_results[2]*v_results[2]);
					double dis2 = (rot_w2.Y()*v_results[2] + v_results[1])/sqrt(1+v_results[2]*v_results[2]);
					trk->SetDistance(dis1);	
					trk->SetTgtPos(wire_z1);
					if(fabs(dis2)<fabs(dis1) ){
						trk->SetDistance(dis2);
						trk->SetTgtPos(wire_z2);
					}
//					trk->SetTgtPos(v_results[1]);
//                    std::cout << "v_results = " << v_results[1] << std::endl;
					double a = v_results[1];
					double b = v_results[2];
					double zpos_x_at100 = b*(r100) + a;
    				double zpos_x_at300 = b*r300 + a;
                    double zpos_x_at3000 = b*r3000 + a;
//					std::cout << "z pos , r" << zpos_x_at300 << "  : " << r300 << std::endl;
//					std::cout << "local y" << hy2.CogHit() << "  : " << r300 << std::endl;
				    TVector2 ref_pt0(r100, zpos_x_at100);
				    TVector2 ref_pt1(r300, zpos_x_at300);
				    TVector2 ref_pt2(r3000, zpos_x_at3000);
				    trk->SetPt0OnTrack(ref_pt0);
				    trk->SetPt1OnTrack(ref_pt1);
				    trk->SetPt2OnTrack(ref_pt2);
//                    trk.SetXIntercept(-v_results[1]/v_results[2]);
//					std::cout << "tgt  = " << v_results[1] << std::endl;
//					std::cout << "hy2 bef = " << &hy2 << std::endl;
					trk->SetYHit100(hits[0]);
					trk->SetYHit200(hits[1]);
					trk->SetYHit300(hits[2]);
                    trk->SetID100Hit(i);
                    trk->SetID200Hit(j);
                    trk->SetID300Hit(k);
                    y_trk_cands.push_back(trk);
  			//	std::cout << "target height " << v_results[1] << std::endl;
//					trk->SetResidual100(v_results2[3]);
//					trk->SetResidual200(v_results2[4]);
//					trk->SetResidual300(v_results2[5]);
						//	std::cout << xz_trk_cand[index].Chi2() << std::endl;		
				}
				v_results.clear();
                //std::cout << "v_results after clear= " << v_results[1] << std::endl;
			}
        }
    }
	for(int i = 0; i<(int)gtr_yhits0b.size(); i++){
		for(int j = 0; j<(int)gtr_yhits1.size(); j++){
            for(int k =0; k<(int)gtr_yhits2.size(); k++){
                std::vector<E16DST_DST1GTRCluster*> hits;
                hits.clear();
                hits.push_back(gtr_yhits0b[i]);
                hits.push_back(gtr_yhits1[j]);
                hits.push_back(gtr_yhits2[k]);
                l_hitpos.clear();
                g_hitpos.clear();
                rot_pos.clear();
                v_fit_samples.clear();
                for(int l = 0; l <3; l++){
                    l_hitpos.push_back(G4ThreeVector(0, hits[l]->CogPos(), 0));
                    g_hitpos.push_back(G4ThreeVector(geom_v2->GTR(kawama_module, l)->GetGPos(l_hitpos[l])));
                    rot_pos.push_back(G4ThreeVector(g_hitpos[l].rotateY(phi)));
                    v_fit_samples.push_back(TVector2(rot_pos[l].x(), rot_pos[l].y()));
                }
				std::vector<long double> &&v_results = LeastSquareMethod(v_fit_samples, sigma_y );//return chi2, a,b (a+bx)
            //    std::cout << "v result" << v_results[1] << std::endl;
				if(v_results[0] < th_chi2_y){
                    std::shared_ptr<E16ANA_YTrackCandidate> trk = std::make_shared<E16ANA_YTrackCandidate>();
    				trk->SetInvalid();
					trk->SetModuleID(mid);
//					y_trk_cand[index].SetChi2(v_results[0]);
                    trk->SetChi2(v_results[0]);
//					trk->SetTgtPos(v_results[1]);
					trk->SetResidual100(rot_pos[0].y() - (rot_pos[0].z()*v_results[2]+v_results[1]));
					trk->SetResidual200(rot_pos[1].y() - (rot_pos[1].z()*v_results[2]+v_results[1]));
					trk->SetResidual300(rot_pos[2].y() - (rot_pos[2].z()*v_results[2]+v_results[1]));
					trk->SetFitA(v_results[1]);
					trk->SetFitB(v_results[2]);

					//trk->SetFitRes100(TVector2(rot_pos[0].z()*v_results[2]+v_results[1], rot_pos[0].z()));//comment out by nakasuga
					trk->SetFitRes100(TVector2(rot_pos[0].x()*v_results[2]+v_results[1], rot_pos[0].x()));//nakasuga
					//trk->SetFitRes200(TVector2(rot_pos[1].z()*v_results[2]+v_results[1], rot_pos[1].z()));//comment out by nakasuga
					trk->SetFitRes200(TVector2(rot_pos[1].x()*v_results[2]+v_results[1], rot_pos[1].x()));//nakasuga
					//trk->SetFitRes300(TVector2(rot_pos[2].z()*v_results[2]+v_results[1], rot_pos[2].z()));//comment out by nakasuga
					trk->SetFitRes300(TVector2(rot_pos[2].x()*v_results[2]+v_results[1], rot_pos[2].x()));//nakasuga
					TVector2 w1(wire_x1, wire_z1);
					TVector2 w2(wire_x2, wire_z2);
					TVector2 rot_w1 = w1.Rotate(-rphi);
					TVector2 rot_w2 = w2.Rotate(-rphi);
					double dis1 = (rot_w1.Y()*v_results[2] + v_results[1])/sqrt(1+v_results[2]*v_results[2]);
					double dis2 = (rot_w2.Y()*v_results[2] + v_results[1])/sqrt(1+v_results[2]*v_results[2]);
					trk->SetDistance(dis1);	
					trk->SetTgtPos(wire_z1);
					if(fabs(dis2)<fabs(dis1) ){
						trk->SetDistance(dis2);
						trk->SetTgtPos(wire_z2);
					}

					double a = v_results[1];
					double b = v_results[2];
					double zpos_x_at100 = b*(r100) + a;
    				double zpos_x_at300 = b*r300 + a;
                    double zpos_x_at3000 = b*r3000 + a;
//					std::cout << "z pos , r" << zpos_x_at300 << "  : " << r300 << std::endl;
//					std::cout << "local y" << hy2.CogHit() << "  : " << r300 << std::endl;
				    TVector2 ref_pt0(r100, zpos_x_at100);
				    TVector2 ref_pt1(r300, zpos_x_at300);
				    TVector2 ref_pt2(r3000, zpos_x_at3000);
				    trk->SetPt0OnTrack(ref_pt0);
				    trk->SetPt1OnTrack(ref_pt1);
				    trk->SetPt2OnTrack(ref_pt2);
//                    trk.SetXIntercept(-v_results[1]/v_results[2]);
//					std::cout << "tgt  = " << v_results[1] << std::endl;
//					std::cout << "hy2 bef = " << &hy2 << std::endl;
					trk->SetYHit100(hits[0]);
					trk->SetYHit200(hits[1]);
					trk->SetYHit300(hits[2]);
                    trk->SetID100Hit(i);
                    trk->SetID200Hit(j);
                    trk->SetID300Hit(k);
                    y_trk_cands.push_back(trk);

                }
				v_results.clear();
            }
		}
	}
/*
	bool i_table[yhits0.size()] = {};
	bool j_table[yhits1.size()] = {};
	bool k_table[yhits2.size()] = {};
	//bool l_tab[ssd_hits.size()] = {};
	std::fill_n(i_table, yhits0.size(), 0);
	std::fill_n(j_table, yhits1.size(), 0);
	std::fill_n(k_table, yhits2.size(), 0);
	//std::fill_n(l_tab, ssd_hits.size(), 0);
    //sort by chi2, and if the hits are overlaped, the track is erased 
    std::sort(y_trk_cand.begin(), y_trk_cand.end(), E16ANA_YTrackCandidate::CompareTrackFunctor());
	std::vector<E16ANA_YTrackCandidate>::const_iterator iter = y_trk_cand.begin();
    while(iter != y_trk_cand.end()){
		if(i_table[(*iter).ID100Hit()] == 0 && j_table[(*iter).ID200Hit()] == 0 && k_table[(*iter).ID300Hit()] == 0 ){
            i_table[(*iter).ID100Hit()] = 1;
			j_table[(*iter).ID200Hit()] = 1; 
			k_table[(*iter).ID300Hit()] = 1; 
            ++iter;
        }
        else{
            iter = y_trk_cand.erase(iter);
 //           std::cout << "a duplicated track Y is erased !" << std::endl;
        }
    }
*/
}


void StraightTrackAnalyzerV0::MatchingXYHitsAfterLinearFit(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk_cands, std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> &y_trk_cands){
    double timing_y0, timing_y1, timing_y2, timing_x0, timing_x1, timing_x2;
    int index = 0;
    double time_diff;
    for(int i = 0; i<y_trk_cands.size(); i++){
        std::shared_ptr<E16ANA_YTrackCandidate> y_track = y_trk_cands[i];
        timing_y0 = y_track->GetYCluster100()->Timing();
        timing_y1 = y_track->GetYCluster200()->Timing();
        timing_y2 = y_track->GetYCluster300()->Timing();
        for(int j=0; j<xz_trk_cands.size(); j++){
            std::shared_ptr<E16ANA_XZTrackCandidate> xz_track =xz_trk_cands[j];
            timing_x0 = xz_track->GetXCluster100()->Timing();
            timing_x1 = xz_track->GetXCluster200()->Timing();
            timing_x2 = xz_track->GetXCluster300()->Timing();
	    if(fabs(y_track->TgtPos() - xz_track->TgtZ()) > 10 ) continue; //matching which wire
            if(fabs(timing_x0 - timing_y0)<25 &&  fabs(timing_x1 - timing_y1)<40 && fabs(timing_x2 - timing_y2)<40){
                    std::shared_ptr<E16ANA_XYZStraightTrack> trk = std::make_shared<E16ANA_XYZStraightTrack>();
                    trk->SetXZTrack(xz_track);
                    trk->SetYTrack(y_track);
					trk->SetYTrackID(i);
					trk->SetXTrackID(j);
//					TVector3 pt0 = TVector3(xz_track->Pt0OnTrack().X(), y_track->Pt0OnTrack().Y(), xz_track->Pt0OnTrack().Y());
//					TVector3 pt2 = TVector3(xz_track->Pt2OnTrack().X(), y_track->Pt2OnTrack().Y(), xz_track->Pt2OnTrack().Y());
//					trk->SetTwoPointsOnTrack(pt0, pt2);
					trk->SetFitPtOnGTR100(TVector3(xz_track->FitPtOnGTR100().X(), y_track->GetFitRes100().X(), xz_track->FitPtOnGTR100().Y()));
					trk->SetFitPtOnGTR200(TVector3(xz_track->FitPtOnGTR200().X(), y_track->GetFitRes200().X(), xz_track->FitPtOnGTR200().Y()));
					trk->SetFitPtOnGTR300(TVector3(xz_track->FitPtOnGTR300().X(), y_track->GetFitRes300().X(), xz_track->FitPtOnGTR300().Y()));
                    xyz_st_trk.push_back(trk);
//					SetPointsOn3DTrack(xz_track, y_track);
					std::cout << "trk id(x, y) = " << j<<", " <<i << std::endl; 
                    index++;
            }
        }

    }
///	bool xz_table[xyz_st_trk.size()] = {};
//	bool yr_table[xyz_st_trk.size()] = {};
///	std::fill_n(xz_table, xyz_st_trk.size(), 0);
//	std::fill_n(yr_table, xyz_st_trk.size(), 0);
//	std::sort(xyz_st_trk.begin(), xyz_st_trk.end(), E16ANA_XYZStraightTrack::CompareTimingFunctor());
/*
	bool i_table[yhits0.size()] = {};
	bool j_table[yhits1.size()] = {};
	bool k_table[yhits2.size()] = {};
	//bool l_tab[ssd_hits.size()] = {};
	std::fill_n(i_table, yhits0.size(), 0);
	std::fill_n(j_table, yhits1.size(), 0);
	std::fill_n(k_table, yhits2.size(), 0);
	//std::fill_n(l_tab, ssd_hits.size(), 0);
    //sort by chi2, and if the hits are overlaped, the track is erased 
    std::sort(y_trk_cand.begin(), y_trk_cand.end(), E16ANA_YTrackCandidate::CompareTrackFunctor());
	std::vector<E16ANA_YTrackCandidate>::const_iterator iter = y_trk_cand.begin();
    while(iter != y_trk_cand.end()){
		if(i_table[(*iter).ID100Hit()] == 0 && j_table[(*iter).ID200Hit()] == 0 && k_table[(*iter).ID300Hit()] == 0 ){
            i_table[(*iter).ID100Hit()] = 1;
			j_table[(*iter).ID200Hit()] = 1; 
			k_table[(*iter).ID300Hit()] = 1; 
            ++iter;
        }
        else{
            iter = y_trk_cand.erase(iter);
 //           std::cout << "a duplicated track Y is erased !" << std::endl;
        }
    }
*/
}


//void StraightTrackAnalyzerV0::MatchingXYZandLeaveTargetTrack(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk_cands, std::vector<std::shared_ptr<E16ANA_YTrackCandidate>> &y_trk_cands){
//    double timing_y0, timing_y1, timing_y2, timing_x0, timing_x1, timing_x2;
//    int index = 0;
//    double time_diff;
//    for(int i = 0; i<y_trk_cands.size(); i++){
//        std::shared_ptr<E16ANA_YTrackCandidate> y_track = y_trk_cands[i];
//        if( fabs(y_track->TgtPos()) > 10 )continue;
//        timing_y0 = y_track->GetYHit100()->Timing();
//        timing_y1 = y_track->GetYHit200()->Timing();
//        timing_y2 = y_track->GetYHit300()->Timing();
//        for(int j=0; j<xz_trk_cands.size(); j++){
//            std::shared_ptr<E16ANA_XZTrackCandidate> xz_track =xz_trk_cands[j];
//            if(std::min( fabs(xz_track->TgtZ()-40.0), fabs(xz_track->TgtZ() + 40.0)) > 5.0 )continue;
//                timing_x0 = xz_track->GetXHit100()->Timing();
//                timing_x1 = xz_track->GetXHit200()->Timing();
//                timing_x2 = xz_track->GetXHit300()->Timing();
//                if(fabs(timing_x0 - timing_y0)<60 &&  fabs(timing_x1 - timing_y1)<80 && fabs(timing_x2 - timing_y2)<80){
//                    std::shared_ptr<E16ANA_XYZStraightTrack> trk = std::make_shared<E16ANA_XYZStraightTrack>();
//                    xyz_st_trk[index]->SetXZTrack(xz_track);
//                    xyz_st_trk[index]->SetYTrack(y_track);
//					TVector3 pt0 = TVector3(xz_track->Pt0OnTrack().X(), y_track->Pt0OnTrack().Y(), xz_track->Pt0OnTrack().Y());
//					TVector3 pt2 = TVector3(xz_track->Pt2OnTrack().X(), y_track->Pt2OnTrack().Y(), xz_track->Pt2OnTrack().Y());
//					xyz_st_trk[index]->SetTwoPointsOnTrack(pt0, pt2);
//                    xyz_st_trk.push_back(trk);
////					SetPointsOn3DTrack(xz_track, y_track);
//                    index++;
//            }
//        }
//    }
//    std::cout << " number of matching success " << index << std::endl;
//
//}
void StraightTrackAnalyzerOfWireV1::Make2DCrossPoint(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk_cands, E16ANA_GeometryV2 *geom_v2){
    //make cross_points 
    //remove cross points made from two tracks of same module
    //leave points made from LR Tracks
	int index = 0;
//    cross_points.resize(xz_trk_cands.size()* xz_trk_cands.size());
//        std::cout << "xz track size = "<< xz_trk_cands.size() << std::endl;
    std::vector<std::pair<int, int>> p;
    p.clear();
	if(xz_trk_cands.size() != 0){
		std::cout << "size of tracks before making crosspoints = " << xz_trk_cands.size() << std::endl;
    }
	for(int i=0; i<xz_trk_cands.size();i++){
        if(xz_trk_cands.size() < 2) continue;
        std::shared_ptr<E16ANA_XZTrackCandidate> track1 = xz_trk_cands[i];
            for(int j=i; j<xz_trk_cands.size(); j++){
                if(i == j) continue;
                std::shared_ptr<E16ANA_XZTrackCandidate> track2 = xz_trk_cands[j];
				std::cout << "trk z 1 = " << track1->TgtZ() << std::endl;
				std::cout << "trk z 2 = " << track2->TgtZ() << std::endl;
//                if(track1->ModuleID() == track2->ModuleID() ) continue;
//                if( signbit(track1->ModuleID() -105) == signbit(track2->ModuleID()-105 ) ) continue;
                if(fabs(track1->TgtZ() - track2->TgtZ()) <10.0 && fabs(track1->TgtZ() - track2->TgtZ()) != 0.0){
                    std::vector<double> && result_calc_cross = CalcCrossPoint2D(track1, track2);//X, Z, min_distance from target
    				if(result_calc_cross[2] < 10 && isnan(result_calc_cross[0]) == 0){
                    //std::cout << result_calc_cross[0] << std::endl;
//	    			if(fabs(track1.TgtZ()) < 10 && fabs(track2.TgtZ()) < 10 ){
                        bool isFirst = true;
                        std::pair<int, int> temp(track1->TrackID(), track2->TrackID());
                        for(int k = 0; k < p.size() ; k++){
                            if(p[k] == temp){
                                isFirst  = false;
                            }
                        }
                        if(isFirst){
                            p.push_back(temp);
                            std::shared_ptr<E16ANA_XZCrossPoint> cp = std::make_shared<E16ANA_XZCrossPoint>();
    	                    cp->SetTrack1ID(i);
	                        cp->SetTrack2ID(j);
	                        cp->SetCoordinateX(result_calc_cross[0]);
        	                cp->SetCoordinateZ(result_calc_cross[1]);
        	                cp->SetDistance(result_calc_cross[2]);
				    	    cp->SetTgtZ1(track1->TgtZ());
    		    			cp->SetTgtZ2(track2->TgtZ());
	        				cp->SetXZTrack1(track1);
	    	    			cp->SetXZTrack2(track2);
                            cross_points.push_back(cp);
    			    		index++;
                            }
                    }
                result_calc_cross.clear();
                }
            }
    }
// ----------------------- NOT allowed using duplicated tracks ----------------------------//
#if 1
    if(cross_points.size() != 0){
        std::cout << "n of cross points before  duplication cut  " << cross_points.size() << std::endl;
    }
    if(cross_points.size() > 0 && cross_points.size() < 5){
   	    bool i_table[xz_trk_cands.size()] = {};
        for(int l=0;l<xz_trk_cands.size(); l++){
   	        i_table[l] = 0;
        }
        std::sort(cross_points.begin(), cross_points.end(), E16ANA_XZCrossPoint::CompareCrossFunctor());
       	std::vector<std::shared_ptr<E16ANA_XZCrossPoint>>::const_iterator iter = cross_points.begin();
        std::vector<std::shared_ptr<E16ANA_XZCrossPoint>> tmp;
        tmp.reserve(index);
        while(iter != cross_points.end()){
   		if(i_table[(*iter)->Track1ID()] == 0 && i_table[(*iter)->Track2ID()] ==0
               && (*iter)->Distance() < 10.0){
               i_table[(*iter)->Track1ID()] = 1;
               i_table[(*iter)->Track2ID()] = 1;
               tmp.push_back((*iter));
               ++iter; 
           }
           else {
               ++iter;   
           }
        }
        cross_points = std::move(tmp);
        std::cout << "n of cross points after duplication cut  " << cross_points.size() << std::endl;
    }
#endif
}

void StraightTrackAnalyzerV0::Make2DCrossPoint(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk_cands, E16ANA_GeometryV2 *geom_v2){
    //make cross_points 
    //remove cross points made from two tracks of same module
    //leave points made from LR Tracks
	int index = 0;
//    cross_points.resize(xz_trk_cands.size()* xz_trk_cands.size());
//        std::cout << "xz track size = "<< xz_trk_cands.size() << std::endl;
    std::vector<std::pair<int, int>> p;
    p.clear();
    for(int i=0; i<xz_trk_cands.size();i++){
        if(xz_trk_cands.size() < 2) continue;
        std::shared_ptr<E16ANA_XZTrackCandidate> track1 = xz_trk_cands[i];
            for(int j=i; j<xz_trk_cands.size(); j++){
                if(i == j) continue;
                std::shared_ptr<E16ANA_XZTrackCandidate> track2 = xz_trk_cands[j];
                if(track1->ModuleID() == track2->ModuleID() ) continue;
//                if( signbit(track1->ModuleID() -105) == signbit(track2->ModuleID()-105 ) ) continue;
                if(fabs(track1->TgtZ() - track2->TgtZ()) <10.0 && fabs(track1->TgtZ() - track2->TgtZ()) != 0.0 && track1->Chi2() < 2 && track2->Chi2() < 2){
                    std::vector<double> && result_calc_cross = CalcCrossPoint2D(track1, track2);//X, Z, min_distance from target
    				if(result_calc_cross[2] < 10 && isnan(result_calc_cross[0]) == 0){
                    //std::cout << result_calc_cross[0] << std::endl;
//	    			if(fabs(track1.TgtZ()) < 10 && fabs(track2.TgtZ()) < 10 ){
                        bool isFirst = true;
                        std::pair<int, int> temp(track1->TrackID(), track2->TrackID());
                        for(int k = 0; k < p.size() ; k++){
                            if(p[k] == temp){
                                isFirst  = false;
                            }
                        }
                        if(isFirst){
                            p.push_back(temp);
                            std::shared_ptr<E16ANA_XZCrossPoint> cp = std::make_shared<E16ANA_XZCrossPoint>();
    	                    cp->SetTrack1ID(i);
	                        cp->SetTrack2ID(j);
	                        cp->SetCoordinateX(result_calc_cross[0]);
        	                cp->SetCoordinateZ(result_calc_cross[1]);
        	                cp->SetDistance(result_calc_cross[2]);
				    	    cp->SetTgtZ1(track1->TgtZ());
    		    			cp->SetTgtZ2(track2->TgtZ());
	        				cp->SetXZTrack1(track1);
	    	    			cp->SetXZTrack2(track2);
                            cross_points.push_back(cp);
    			    		index++;
                            }
                    }
                result_calc_cross.clear();
                }
            }
    }
//    std::cout << "index " << index << std::endl;
// ----------------------- NOT allowed using duplicated tracks ----------------------------//
#if 1
    if(cross_points.size() != 0){
        std::cout << "n of cross points before  duplication cut  " << cross_points.size() << std::endl;
    }
    if(cross_points.size() > 0 && cross_points.size() < 5){
   	    bool i_table[xz_trk_cands.size()] = {};
        for(int l=0;l<xz_trk_cands.size(); l++){
   	        i_table[l] = 0;
        }
        std::sort(cross_points.begin(), cross_points.end(), E16ANA_XZCrossPoint::CompareCrossFunctor());
       	std::vector<std::shared_ptr<E16ANA_XZCrossPoint>>::const_iterator iter = cross_points.begin();
        std::vector<std::shared_ptr<E16ANA_XZCrossPoint>> tmp;
        tmp.reserve(index);
        while(iter != cross_points.end()){
   		if(i_table[(*iter)->Track1ID()] == 0 && i_table[(*iter)->Track2ID()] ==0
               && (*iter)->Distance() < 10.0){
               i_table[(*iter)->Track1ID()] = 1;
               i_table[(*iter)->Track2ID()] = 1;
               tmp.push_back((*iter));
               ++iter; 
           }
           else {
               ++iter;   
           }
        }
        cross_points = std::move(tmp);
        std::cout << "n of cross points after duplication cut  " << cross_points.size() << std::endl;
    }
#endif
}

double StraightTrackAnalyzerV0::GetGTRModulePhi(E16ANA_GeometryV2 *geom, int module_id){
    int module = ModuleID_2020to2013_33(module_id);
    G4ThreeVector g4v_OriginPos = G4ThreeVector(0.0, 0.0, 0.0);
    G4ThreeVector g4v_CenterPos = geom->GTR(module, 0)->GetGPos(g4v_OriginPos);
    //layer id is not related to module phi, so temporally 0 here
    TVector2 tv_centerXZ;
    tv_centerXZ.Set(g4v_CenterPos.getX(), g4v_CenterPos.getZ());
    return  atan2(tv_centerXZ.Y(), tv_centerXZ.X());//phi
}


std::vector<long double> StraightTrackAnalyzerV0::LeastSquareMethod(std::vector<TVector2> &tv_v_pos, std::vector<double> sigma_x){
	int v_size = tv_v_pos.size();
	int v_sig_size = sigma_x.size();
	if(v_size != sigma_x.size()){
			std::cout << " sizes of vectors btw positions and sigmas are different  " << std::endl;
			std::cout << "size of pos vec = " << v_size << std::endl;
			std::cout << "size of sigma vec = " << v_sig_size << std::endl;}
	double wt=0, t=0, sx=0, sy=0, st2=0, ss = 0, sxoss = 0;
	double sx2=0, sxy=0;
	//double a=0, b=0, siga=0, sigb=0, chi2=0;//a+bx
	for(int i = 0; i < v_size; i++){
		wt = 1.0 /sigma_x[i]/sigma_x[i];
		ss  += wt;
		sx  += tv_v_pos[i].X() * wt ;
		sy  += tv_v_pos[i].Y() * wt ;
		sx2 += tv_v_pos[i].X() *tv_v_pos[i].X() * wt ;
		sxy += tv_v_pos[i].Y() *tv_v_pos[i].X() * wt ;
	}
	double a = (sx*sxy-sx2*sy)/(sx*sx-ss*sx2);
	double b = (sx*sy-ss*sxy)/(sx*sx-ss*sx2);
	/*
	sxoss = sx/ss;
	for(int i=0; i < v_size; i++ ){
		t = (tv_v_pos[i].X() -sxoss)/sigma_x[i];
		st2 += t*t;
		b += t*tv_v_pos[i].Y()/sigma_x[i]; 
	}
	b /= st2;
	a = (sy-sx*b)/ss;
	siga = sqrt((1.0 + sx*sx/(ss*st2)/ss));
	sigb = sqrt(1.0/st2);
	*/
	double chi2 = 0.0;
	for(int i=0; i < v_size; i++){
		chi2 += sqr((tv_v_pos[i].Y()- a-(b*tv_v_pos[i].X()))/sigma_x[i]);
//		q = Gammq(0.5 * (n_sample-2), 0.5* (chi2));
	}
	std::vector<long double> lst_sq_results;
	lst_sq_results.clear();
	lst_sq_results.push_back(chi2);
    //std::cout << "chi2  = " << chi2 << std::endl;
	lst_sq_results.push_back(a);
	lst_sq_results.push_back(b);
//	std::vector<double> residual;
	for(int i = 0; i<v_size; i++){
		lst_sq_results.push_back(tv_v_pos[i].Y()- a-(b*tv_v_pos[i].X()));
	}
	/*
	double residue[3] = {0, 0, 0};
	if(chi2 < th_chi2){
		for(int i = 0; i < 3; i++){
			residue[i] = tv_v_pos[i].Y()- a-(b*tv_v_pos[i].X());
		}
		h_residue[0]->Fill(residue[0]);
		h_residue[1]->Fill(residue[1]);
		h_residue[2]->Fill(residue[2]);
//		std::cout << "a " << a << std::endl;
		if(b == 0){
		std::cout << "b is 0 ? " << b << std::endl;}
		h_fitted_a[0]->Fill(a);
		h_fitted_b[0]->Fill(b);
	}
*/
	return lst_sq_results;

//
//
//
//	int v_size = tv_v_pos.size();
//	int v_sig_size = sigma_x.size();
//	if(v_size != sigma_x.size()){
//			std::cout << " sizes of vectors btw positions and sigmas are different  " << std::endl;
//			std::cout << "size of pos vec = " << v_size << std::endl;
//			std::cout << "size of sigma vec = " << v_sig_size << std::endl;}
//	double wt=0, t=0, sx=0, sy=0, st2=0, ss = 0, sxoss = 0;
//	double a=0, b=0, siga=0, sigb=0, chi2=0;//a+bx
//	for(int i = 0; i < v_size; i++){
//		wt = 1.0 / sqr(sigma_x[i]);
//		ss += wt;
//		sx += tv_v_pos[i].X() * wt ;
//		sy += tv_v_pos[i].Y() * wt ;
//	}
//	sxoss = sx/ss;
//	for(int i=0; i < v_size; i++ ){
//		t = (tv_v_pos[i].X() -sxoss)/sigma_x[i];
//		st2 += t*t;
//		b += t*tv_v_pos[i].Y()/sigma_x[i]; 
//	}
//	b /= st2;
//	a = (sy-sx*b)/ss;
//	siga = sqrt((1.0 + sx*sx/(ss*st2)/ss));
//	sigb = sqrt(1.0/st2);
//	chi2 = 0.0;
//	for(int i=0; i < v_size; i++){
//		chi2 += sqr((tv_v_pos[i].Y()- a-(b*tv_v_pos[i].X()))/sigma_x[i]);
////		q = Gammq(0.5 * (n_sample-2), 0.5* (chi2));
//	}
//	std::vector<long double> lst_sq_results;
//	lst_sq_results.clear();
//	lst_sq_results.push_back(chi2);
//    //std::cout << "chi2  = " << chi2 << std::endl;
//	lst_sq_results.push_back(a);
//	lst_sq_results.push_back(b);
////	std::vector<double> residual;
//	for(int i = 0; i<v_size; i++){
//		lst_sq_results.push_back(tv_v_pos[i].Y()- a-(b*tv_v_pos[i].X()));
//	}
//	/*
//	double residue[3] = {0, 0, 0};
//	if(chi2 < th_chi2){
//		for(int i = 0; i < 3; i++){
//			residue[i] = tv_v_pos[i].Y()- a-(b*tv_v_pos[i].X());
//		}
//		h_residue[0]->Fill(residue[0]);
//		h_residue[1]->Fill(residue[1]);
//		h_residue[2]->Fill(residue[2]);
////		std::cout << "a " << a << std::endl;
//		if(b == 0){
//		std::cout << "b is 0 ? " << b << std::endl;}
//		h_fitted_a[0]->Fill(a);
//		h_fitted_b[0]->Fill(b);
//	}
//*/
//	return lst_sq_results;
}

double StraightTrackAnalyzerV0::ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2){//a+bx
    G4ThreeVector pos_100 = ((geom_v2->GTR(kawama_module, 0)->GetGPos(G4ThreeVector(0,0,0))));
	double r100_2 = pos_100.x()*pos_100.x() + pos_100.y()*pos_100.y() + pos_100.z()*pos_100.z();
	double r100  = sqrt(r100_2);
	double zpos_x200mm = b*(r100) + a;

    G4ThreeVector pos_300 = ((geom_v2->GTR(kawama_module, 2)->GetGPos(G4ThreeVector(0,0,0))));
	double r300_2 = pos_300.x()*pos_300.x() + pos_300.y()*pos_300.y() + pos_300.z()*pos_300.z();
	double r300  = sqrt(r300_2);
    double zpos_x600mm = b*r300 + a;
	
	
    TVector2 ref_pt0(r100, zpos_x200mm);
    TVector2 ref_pt1(r300, zpos_x600mm);
	TVector2 ref_pt2(3000, b*3000 + a);
    TVector2 pt0 = ref_pt0.Rotate(phi);
    TVector2 pt1 = ref_pt1.Rotate(phi);
	TVector2 pt2 = ref_pt2.Rotate(phi);

 //   trk->SetPt0OnTrack(TVector2(1,1));
//    trk->SetPt1OnTrack(pt1);
//    trk->SetPt2OnTrack(pt2);

    double tgt_z = (pt0.X()*pt1.Y()-pt0.Y()*pt1.X())/(pt0.X()-pt1.X());//x = 0
   ref_pt0.Clear();
    ref_pt1.Clear();
    pt0.Clear();
    pt1.Clear();
    //if(fabs(tgt_z-40) < 10 || fabs(tgt_z+40)< 10){//around wire 
        return tgt_z;
    //}
}

double StraightTrackAnalyzerV0::ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2, std::shared_ptr<E16ANA_XZTrackCandidate> trk ){//a+bx
    G4ThreeVector pos_100 = ((geom_v2->GTR(kawama_module, 0)->GetGPos(G4ThreeVector(0,0,0))));
	double r100_2 = pos_100.x()*pos_100.x() + pos_100.y()*pos_100.y() + pos_100.z()*pos_100.z();
	double r100  = sqrt(r100_2);
	double zpos_x200mm = b*(r100) + a;

    G4ThreeVector pos_300 = ((geom_v2->GTR(kawama_module, 2)->GetGPos(G4ThreeVector(0,0,0))));
	double r300_2 = pos_300.x()*pos_300.x() + pos_300.y()*pos_300.y() + pos_300.z()*pos_300.z();
	double r300  = sqrt(r300_2);
    double zpos_x600mm = b*r300 + a;
	
	
    TVector2 ref_pt0(r100, zpos_x200mm);
    TVector2 ref_pt1(r300, zpos_x600mm);
	TVector2 ref_pt2(3000, b*3000 + a);
    TVector2 pt0 = ref_pt0.Rotate(phi);
    TVector2 pt1 = ref_pt1.Rotate(phi);
	TVector2 pt2 = ref_pt2.Rotate(phi);

 //   trk->SetPt0OnTrack(TVector2(1,1));
//    trk->SetPt1OnTrack(pt1);
//    trk->SetPt2OnTrack(pt2);

    trk->SetPt0OnTrack(pt0);
    trk->SetPt1OnTrack(pt1);
    trk->SetPt2OnTrack(pt2);
    double tgt_z = (pt0.X()*pt1.Y()-pt0.Y()*pt1.X())/(pt0.X()-pt1.X());//x = 0
   ref_pt0.Clear();
    ref_pt1.Clear();
    pt0.Clear();
    pt1.Clear();
    //if(fabs(tgt_z-40) < 10 || fabs(tgt_z+40)< 10){//around wire 
        return tgt_z;
    //}
}


double StraightTrackAnalyzerOfWireV1::ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2){//a+bx
    G4ThreeVector pos_100 = ((geom_v2->GTR(kawama_module, 0)->GetGPos(G4ThreeVector(0,0,0))));
	double r100_2 = pos_100.x()*pos_100.x() + pos_100.y()*pos_100.y() + pos_100.z()*pos_100.z();
	double r100  = sqrt(r100_2);
	double zpos_x200mm = b*(r100) + a;

    G4ThreeVector pos_300 = ((geom_v2->GTR(kawama_module, 2)->GetGPos(G4ThreeVector(0,0,0))));
	double r300_2 = pos_300.x()*pos_300.x() + pos_300.y()*pos_300.y() + pos_300.z()*pos_300.z();
	double r300  = sqrt(r300_2);
    double zpos_x600mm = b*r300 + a;
	
	
    TVector2 ref_pt0(r100, zpos_x200mm);
    TVector2 ref_pt1(r300, zpos_x600mm);
	TVector2 ref_pt2(3000, b*3000 + a);
    TVector2 pt0 = ref_pt0.Rotate(phi);
    TVector2 pt1 = ref_pt1.Rotate(phi);
	TVector2 pt2 = ref_pt2.Rotate(phi);

 //   trk->SetPt0OnTrack(TVector2(1,1));
//    trk->SetPt1OnTrack(pt1);
//    trk->SetPt2OnTrack(pt2);

    //double tgt_z = (pt1.Y()-pt0.Y())*(-20.0)/(pt1.X()-pt0.X())  +(pt0.X()*pt1.Y()-pt0.Y()*pt1.X())/(pt0.X()-pt1.X());//x = -20
    double tgt_z = (pt1.Y()-pt0.Y())*(20.0)/(pt1.X()-pt0.X())  +(pt0.X()*pt1.Y()-pt0.Y()*pt1.X())/(pt0.X()-pt1.X());//x = 20
    ref_pt0.Clear();
    ref_pt1.Clear();
    pt0.Clear();
    pt1.Clear();
    //if(fabs(tgt_z-40) < 10 || fabs(tgt_z+40)< 10){//around wire 
        return tgt_z;
    //}
}


//morino ver
double StraightTrackAnalyzerOfWireV1::ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2, std::shared_ptr<E16ANA_XZTrackCandidate> trk ){//a+bx
    G4ThreeVector pos_100 = ((geom_v2->GTR(kawama_module, 0)->GetGPos(G4ThreeVector(0,0,0))));
	double r100_2 = pos_100.x()*pos_100.x() + pos_100.y()*pos_100.y() + pos_100.z()*pos_100.z();
	double r100  = sqrt(r100_2);
	double zpos_x200mm = b*(r100) + a;

    G4ThreeVector pos_300 = ((geom_v2->GTR(kawama_module, 2)->GetGPos(G4ThreeVector(0,0,0))));
	double r300_2 = pos_300.x()*pos_300.x() + pos_300.y()*pos_300.y() + pos_300.z()*pos_300.z();
	double r300  = sqrt(r300_2);
    double zpos_x600mm = b*r300 + a;
	
    /*
    TVector2 ref_pt0(r100, zpos_x200mm);
    TVector2 ref_pt1(r300, zpos_x600mm);
	TVector2 ref_pt2(3000, b*3000 + a);
    TVector2 pt0 = ref_pt0.Rotate(phi);
    TVector2 pt1 = ref_pt1.Rotate(phi);
	TVector2 pt2 = ref_pt2.Rotate(phi);
    */
    TVector2 ref_pt0(zpos_x200mm,r100);
    TVector2 ref_pt1(zpos_x600mm,r300);
    TVector2 ref_pt2(b*3000 + a,3000);
    double rphi = phi - 1.570796;
    TVector2 pt0 = ref_pt0.Rotate(rphi);
    TVector2 pt1 = ref_pt1.Rotate(rphi);
    TVector2 pt2 = ref_pt2.Rotate(rphi);


 //   trk->SetPt0OnTrack(TVector2(1,1));
//    trk->SetPt1OnTrack(pt1);
//    trk->SetPt2OnTrack(pt2);

    trk->SetPt0OnTrack(pt0);
    trk->SetPt1OnTrack(pt1);
    trk->SetPt2OnTrack(pt2);
    
//    double tgt_z1 = (pt1.Y()-pt0.Y())*(-20.0)/(pt1.X()-pt0.X())  +(pt0.X()*pt1.Y()-pt0.Y()*pt1.X())/(pt0.X()-pt1.X());//x = -20
    double tgt_z = (pt1.Y()-pt0.Y())*(wire_x1)/(pt1.X()-pt0.X())  +(pt0.X()*pt1.Y()-pt0.Y()*pt1.X())/(pt0.X()-pt1.X());
	
    ref_pt0.Clear();
    ref_pt1.Clear();
    pt0.Clear();
    pt1.Clear();
    //if(fabs(tgt_z-40) < 10 || fabs(tgt_z+40)< 10){//around wire 
        return tgt_z;
    //}
}

/*
double StraightTrackAnalyzerOfWireV1::ReconstructTgtPosBeforeVertex(double a, double b, double phi, int kawama_module, E16ANA_GeometryV2 *geom_v2, std::shared_ptr<E16ANA_XZTrackCandidate> trk ){//a+bx
    G4ThreeVector pos_100 = ((geom_v2->GTR(kawama_module, 0)->GetGPos(G4ThreeVector(0,0,0))));
	double r100_2 = pos_100.x()*pos_100.x() + pos_100.y()*pos_100.y() + pos_100.z()*pos_100.z();
	double r100  = sqrt(r100_2);
	double zpos_x200mm = b*(r100) + a;

    G4ThreeVector pos_300 = ((geom_v2->GTR(kawama_module, 2)->GetGPos(G4ThreeVector(0,0,0))));
	double r300_2 = pos_300.x()*pos_300.x() + pos_300.y()*pos_300.y() + pos_300.z()*pos_300.z();
	double r300  = sqrt(r300_2);
    double zpos_x600mm = b*r300 + a;
	
	
    TVector2 ref_pt0(r100, zpos_x200mm);
    TVector2 ref_pt1(r300, zpos_x600mm);
	TVector2 ref_pt2(3000, b*3000 + a);
    TVector2 pt0 = ref_pt0.Rotate(phi);
    TVector2 pt1 = ref_pt1.Rotate(phi);
	TVector2 pt2 = ref_pt2.Rotate(phi);

 //   trk->SetPt0OnTrack(TVector2(1,1));
//    trk->SetPt1OnTrack(pt1);
//    trk->SetPt2OnTrack(pt2);

    trk->SetPt0OnTrack(pt0);
    trk->SetPt1OnTrack(pt1);
    trk->SetPt2OnTrack(pt2);
    
//    double tgt_z1 = (pt1.Y()-pt0.Y())*(-20.0)/(pt1.X()-pt0.X())  +(pt0.X()*pt1.Y()-pt0.Y()*pt1.X())/(pt0.X()-pt1.X());//x = -20
    double tgt_z = (pt1.Y()-pt0.Y())*(wire_x1)/(pt1.X()-pt0.X())  +(pt0.X()*pt1.Y()-pt0.Y()*pt1.X())/(pt0.X()-pt1.X());
	
    ref_pt0.Clear();
    ref_pt1.Clear();
    pt0.Clear();
    pt1.Clear();
    //if(fabs(tgt_z-40) < 10 || fabs(tgt_z+40)< 10){//around wire 
        return tgt_z;
    //}
}
*/

std::vector<double> StraightTrackAnalyzerV0::CalcCrossPoint2D(std::shared_ptr<E16ANA_XZTrackCandidate> trk1, std::shared_ptr<E16ANA_XZTrackCandidate>trk2){
    double ksi = 0, eta = 0, delta = 0;
    double ramda = 0, mu = 0;
    double X =-1000;
    double Y =-1000;
	double distance2, distance;
	std::vector<double> v_results;
	v_results.clear();
    TVector2 &pt1 =trk1->Pt0OnTrack();
    TVector2 &pt2 =trk1->Pt1OnTrack();
    TVector2 &pt3 =trk2->Pt0OnTrack();
    TVector2 &pt4 = trk2->Pt1OnTrack();
    ksi = ( pt4.Y()-pt3.Y() )*( pt4.X()-pt1.X() ) - ( pt4.X() - pt3.X() )*( pt4.Y()-pt1.Y());
    eta = ( pt2.X()-pt1.X() )*( pt4.Y() - pt1.Y() ) -( pt2.Y()-pt1.Y() )*( pt4.X()-pt1.X());
    delta = ( pt2.X()-pt1.X() )*( pt4.Y()-pt3.Y() ) - (pt2.Y()-pt1.Y() )*( pt4.X()-pt3.X());
    ramda = ksi / delta;
    mu = eta / delta;
  //  if((ramda >= 0 && ramda <= 1) && (mu >= 0 && mu <= 1)){//in the case of line segments
        X = pt1.X() + ramda*( pt2.X()-pt1.X());
        Y = pt1.Y() + ramda*( pt2.Y()-pt1.Y());
		v_results.push_back(X);
		v_results.push_back(Y);
		distance2 = std::min({(X*X + Y*Y),(X*X + (Y-20)*(Y-20)), (X*X + (Y+20)*(Y+20))}); //target 
	
        distance = std::sqrt(distance2);
		v_results.push_back(distance);
//        cross_points.push_back(TVector2(CrossX, CrossY));
//    std::cout << "cross x" << CrossX << std::endl;
//    std::cout << "cross y" << CrossY << std::endl;
   // }
    pt1.Clear();
    pt2.Clear();
    pt3.Clear();
    pt4.Clear();
    //is it ok clearance here?
    return v_results;
}

std::vector<double> StraightTrackAnalyzerOfWireV1::CalcCrossPoint2D(std::shared_ptr<E16ANA_XZTrackCandidate> trk1, std::shared_ptr<E16ANA_XZTrackCandidate>trk2){
    double ksi = 0, eta = 0, delta = 0;
    double ramda = 0, mu = 0;
    double X =-1000;
    double Y =-1000;
	double distance2, distance;
	std::vector<double> v_results;
	v_results.clear();
    TVector2 &pt1 =trk1->Pt0OnTrack();
    TVector2 &pt2 =trk1->Pt1OnTrack();
    TVector2 &pt3 =trk2->Pt0OnTrack();
    TVector2 &pt4 = trk2->Pt1OnTrack();
    ksi = ( pt4.Y()-pt3.Y() )*( pt4.X()-pt1.X() ) - ( pt4.X() - pt3.X() )*( pt4.Y()-pt1.Y());
    eta = ( pt2.X()-pt1.X() )*( pt4.Y() - pt1.Y() ) -( pt2.Y()-pt1.Y() )*( pt4.X()-pt1.X());
    delta = ( pt2.X()-pt1.X() )*( pt4.Y()-pt3.Y() ) - (pt2.Y()-pt1.Y() )*( pt4.X()-pt3.X());
    ramda = ksi / delta;
    mu = eta / delta;
  //  if((ramda >= 0 && ramda <= 1) && (mu >= 0 && mu <= 1)){//in the case of line segments
        X = pt1.X() + ramda*( pt2.X()-pt1.X());
        Y = pt1.Y() + ramda*( pt2.Y()-pt1.Y());
		v_results.push_back(X);
		v_results.push_back(Y);
//		distance2 = std::min({((X+20)*(X+20) + (Y-40)*(Y-40)), ((X+20)*(X+20) + (Y+40)*(Y+40))}); //wire
		distance2 = std::min({((X-wire_x1)*(X-wire_x1) + (Y-wire_z1)*(Y-wire_z1)), ((X-wire_x2)*(X-wire_x2) + (Y-wire_z2)*(Y-wire_z2))}); //wire
		
        distance = std::sqrt(distance2);
		v_results.push_back(distance);
//        cross_points.push_back(TVector2(CrossX, CrossY));
//    std::cout << "cross x" << CrossX << std::endl;
//    std::cout << "cross y" << CrossY << std::endl;
   // }
    pt1.Clear();
    pt2.Clear();
    pt3.Clear();
    pt4.Clear();
    //is it ok clearance here?
    return v_results;
}

