//#include "GTR/E16ANA_STRAnalyzer.h"
#include "straight_track/StraightTrackAnalyzerV0.h"
#include "E16DST_DST1.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_TargetInfo.hh"
#include "E16ANA_RundependentName.hh"
using namespace std;

int E16DST_DST1WireTrackFactory3D(E16DST_DST0PhysicsEvent *event0, E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1, std::vector<std::shared_ptr<E16DST_DST1StraightTrack3D>> st_tracks, E16ANA_GTRcalibPedestal &gtrped,  E16ANA_GeometryV2 *geom){
	static bool isFirst = true;
	static StraightTrackAnalyzerOfWireV1 *straight_analyzer;
	if(isFirst){
        auto& calib = E16ANA_CalibDBManager::Instance();
        E16ANA_TargetInfoManager& targets = E16ANA_TargetInfoManager::Instance();
		targets.ReadInfoWithRunID(calib.CurrentRunID());
        targets.Print();
		if(targets.IsWire()){
	        double x1 = targets.Info(0).Position().x();
    	    double z1 = targets.Info(0).Position().z();
        	double x2 = targets.Info(1).Position().x();
	        double z2 = targets.Info(1).Position().z();
			straight_analyzer = new StraightTrackAnalyzerOfWireV1(x1 ,z1, x2, z2);//track selected only by GTR
	    }
		else{
			std::cerr << "### This is not wire targets run ###" << std::endl;
			return -1 ;
		}
		isFirst = false;
    	std::cout << " Parameters of Wire factory are set " << std::endl;
	}
//	for(auto &a : straight_analyzer->ssd_analyzer_map){
//		a.second->Clear();
//	}
//	int noh_ssd = event0->SSD().NumberOfHits();
//	for(int i = 0; i<noh_ssd; i++){
//		E16DST_DST0SSDHit &hit = event0->SSD().Hit(i);
//		int mid = hit.ModuleID();	
//		int sid = hit.StripID();
//		straight_analyzer->ssd_analyzer_map[OnlineGTR::IDs(mid, 0).value64]->SetFadc(sid, hit.Waveform());
//	}
//	for(auto &a : straight_analyzer->ssd_analyzer_map){
//		a.second->AnalyzeV0();
//	}

//--- search linear tracks on XZ and YR planes 
    straight_analyzer->Clear();
    for(int mid = 100; mid< 110; mid++){
 		straight_analyzer->OneModuleAnalyze2(ssd1, gtr1, mid, geom);
	}
// 
	
	straight_analyzer->MatchingXYHitsAfterLinearFit(straight_analyzer->GetXZTrackCandidates(), straight_analyzer->GetYTrackCandidates());

	int trks_size = straight_analyzer->GetXYZStraightTracks().size();
	st_tracks.clear();
//	st_tracks.resize(trks_size);
	for(int i=0; i<trks_size; i++){
		std::shared_ptr<E16ANA_XYZStraightTrack> t = straight_analyzer->GetXYZStraightTracks()[i];
		std::shared_ptr<E16ANA_XZTrackCandidate> tx = t->GetXZTrackCandidate();
		std::shared_ptr<E16ANA_YTrackCandidate> ty = t->GetYTrackCandidate();
		std::shared_ptr<E16DST_DST1StraightTrack3D> trk = std::make_shared<E16DST_DST1StraightTrack3D>();
		
		trk->SetModuleID(tx->ModuleID());
		trk->SetModuleID(tx->ModuleID());
		trk->SetXTrackID(t->XTrackID());
		trk->SetYTrackID(t->YTrackID());
		trk->SetChi2X(tx->Chi2());
		trk->SetChi2Y(ty->Chi2());
		trk->SetTgtPosZ(tx->TgtZ());
		trk->SetTgtPosY(ty->TgtPos());
	    trk->SetFitAX(tx->GetFitA());
	    trk->SetFitBX(tx->GetFitB());
	    trk->SetFitAY(ty->GetFitA());
	    trk->SetFitBY(ty->GetFitB());
		trk->SetDistanceFromTgtXZ(tx->Distance());
		trk->SetDistanceFromTgtYR(ty->Distance());
		trk->SetResidualSSD(tx->ResidualSSD());
		trk->SetFitResidual100X(tx->Residual100());
		trk->SetFitResidual200X(tx->Residual200());
		trk->SetFitResidual300X(tx->Residual300());
		trk->SetFitResidual100Y(ty->Residual100());
		trk->SetFitResidual200Y(ty->Residual200());
		trk->SetFitResidual300Y(ty->Residual300());
		trk->SetSSDCluster(tx->GetXClusterSSD());
		trk->SetGTR100XCluster(tx->GetXCluster100());
		trk->SetGTR200XCluster(tx->GetXCluster200());
		trk->SetGTR300XCluster(tx->GetXCluster300());
		trk->SetGTR100YCluster(ty->GetYCluster100());
		trk->SetGTR200YCluster(ty->GetYCluster200());
		trk->SetGTR300YCluster(ty->GetYCluster300());
		trk->SetFitPtOnGTR100(t->FitPtOnGTR100());
		trk->SetFitPtOnGTR200(t->FitPtOnGTR200());
		trk->SetFitPtOnGTR300(t->FitPtOnGTR300());

//		st_tracks[i].SetPtOnTrackGTR100(t->Pt0OnTrack());
//		st_tracks[i].SetPtOnTrackGTR300(t->Pt1OnTrack());
//		st_tracks[i].SetPtOnTrack3000mm(t->Pt2OnTrack());
		st_tracks.push_back(trk);
	}



//    ssd1->Clear();
//    gtr1->Clear();
//--- 2D
//    straight_analyzer->Analyze(straight_analyzer->GetXZTrackCandidates(), straight_analyzer->GetYTrackCandidates(), geom);
//------
//--- 3D
//	straight_analyzer->Analyze(straight_analyzer->GetXYZStraightTrack(), geom);
//-------
//    if(straight_analyzer->GetCrossPoints().size() < 5){ 
//        std::vector<std::shared_ptr<E16ANA_XZCrossPoint>> &cps = straight_analyzer->GetCrossPoints();   
//		straight_analyzer->SearchSSDHit(cps, ssd1, geom);
//	    std::vector<std::reference_wrapper<std::vector<E16ANA_SSDAnalyzedStripHit>>> v_shits;
//    	v_shits.clear();
//        for(int mid = 100; mid<110; mid++){
////	        v_shits.push_back(straight_analyzer->SSD_Sensor(mid, 0)->GetStripX()->GetAnalyzedHits());
//        }
//        straight_analyzer->SearchSSDHit(straight_analyzer->GetCrossPoints(), v_shits, geom);
//	}

//	st_tracks.clear();
//	st_tracks.resize(straight_analyzer->GetXZTracksEveSel().size());
//	for(int i=0; i<straight_analyzer->GetXZTracksEveSel().size(); i++){
//		std::shared_ptr<E16ANA_XZTrackCandidate> &sel_trk = straight_analyzer->GetXZTracksEveSel()[i];
//		st_tracks[i].SetModuleID(sel_trk->ModuleID());
//		st_tracks[i].SetChi2(sel_trk->Chi2());
//		st_tracks[i].SetTgtZ(sel_trk->TgtZ());
//		st_tracks[i].SetDistance(sel_trk->Distance());
//		st_tracks[i].SetSSDResidualExSelf(sel_trk->ResidualSSD());
//		st_tracks[i].SetSSDCluster(sel_trk->GetXClusterSSD());
//		st_tracks[i].SetGTR100XCluster(sel_trk->GetXCluster100());
//		st_tracks[i].SetGTR200XCluster(sel_trk->GetXCluster200());
//		st_tracks[i].SetGTR300XCluster(sel_trk->GetXCluster300());
//		st_tracks[i].SetPtOnTrackGTR100(sel_trk->Pt0OnTrack());
//		st_tracks[i].SetPtOnTrackGTR300(sel_trk->Pt1OnTrack());
//		st_tracks[i].SetPtOnTrack3000mm(sel_trk->Pt2OnTrack());
//	}
	return 0;
}
