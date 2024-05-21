//#include "GTR/E16ANA_STRAnalyzer.h"
#include "straight_track/StraightTrackAnalyzerV0.h"
#include "E16DST_DST1.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_TargetInfo.hh"
#include "E16ANA_RundependentName.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16ANA_StraightTrackCandidate.hh"
#include "E16ANA_StraightMultiTrack.hh"
#include "E16ANA_StraightTrackCheckFile.hh"
using namespace std;


int E16DST_DST1StraightTrackFactory3D(E16DST_DST0PhysicsEvent *event0, E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1, std::vector<std::shared_ptr<E16DST_DST1StraightTrack3D>> &st_tracks, E16ANA_GTRcalibPedestal &gtrped, const int removed_layer){
	static bool isFirst = true;
	//static StraightTrackAnalyzerOfWireV1 *straight_analyzer;
	static StraightTrackAnalyzerOfTargets *straight_analyzer;
	static E16ANA_GeometryV2 *geom;
	if(isFirst){
        auto& calib = E16ANA_CalibDBManager::Instance();
        E16ANA_TargetInfoManager& targets = E16ANA_TargetInfoManager::Instance();
		targets.ReadInfoWithRunID(calib.CurrentRunID());
        targets.Print();
//		E16ANA_RundependentName& name = E16ANA_RundependentName::Instance();
//		string geomName = name.ReadNameWithRunID(calib.CurrentRunID(), "geometry", "/ccj/u/E16/database/");
//		std::cout << "geom name = " << geomName << std::endl;
//		geom = new E16ANA_GeometryV2(geomName);
		geom = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
		if(targets.NoT() == 3 ){
	        double x1 = targets.Info(0).Position().x();
    	    double z1 = targets.Info(0).Position().z();
        	double x2 = targets.Info(1).Position().x();
	        double z2 = targets.Info(1).Position().z();
        	double x3 = targets.Info(2).Position().x();
	        double z3 = targets.Info(2).Position().z();
			straight_analyzer = new StraightTrackAnalyzerOfTargets(targets.NoT(), x1 ,z1, x2, z2, x3, z3);//track selected only by GTR
	    }
		else{
			std::cerr << "### This is not Three targets run ###" << std::endl;
			return -1 ;
		}
		isFirst = false;
    	std::cout << " Parameters of Straight Track factory are set " << std::endl;
	}
//--- search linear tracks on XZ and YR planes 
    straight_analyzer->Clear();
  	for(int mid = 100; mid< 110; mid++){
		if(removed_layer == 0){//without ssd
 			straight_analyzer->OneModuleAnalyze2woSSD(3, ssd1, gtr1, mid, geom);
 		}
		else { //with all (-1), or without one layer GTR (1,2, 3)
// 			straight_analyzer->OneModuleAnalyze2(3, ssd1, gtr1, mid, geom);
 			straight_analyzer->OneModuleAnalyze2(3, ssd1, gtr1, mid, geom);
		}
	}
	
	int trks_size = straight_analyzer->GetXYZStraightTracks().size();
	st_tracks.clear();
	st_tracks.reserve(trks_size);
	for(int i=0; i<trks_size; i++){
		std::shared_ptr<E16ANA_XYZStraightTrack> t = straight_analyzer->GetXYZStraightTracks()[i];
		std::shared_ptr<E16ANA_XZTrackCandidate> tx = t->GetXZTrackCandidate();
		std::shared_ptr<E16ANA_YTrackCandidate> ty = t->GetYTrackCandidate();
		std::shared_ptr<E16DST_DST1StraightTrack3D> trk = std::make_shared<E16DST_DST1StraightTrack3D>();
//		std::cout << "event 0 event_ID = " << event0->EventID() << std::endl;
		trk->SetEventID(event0->EventID());
        trk->SetTrackID(i);
		trk->SetModuleID(tx->ModuleID());
		trk->SetXTrackID(t->XTrackID());
		trk->SetYTrackID(t->YTrackID());
		trk->SetChi2X(tx->Chi2());
		trk->SetChi2Y(ty->Chi2());
		trk->SetTgtPosZ(tx->TgtZ());
		//trk->SetTgtPosY(ty->TgtPos());
	    trk->SetFitAX(tx->GetFitA());
	    trk->SetFitBX(tx->GetFitB());
	    trk->SetFitAY(ty->GetFitA());
	    trk->SetFitBY(ty->GetFitB());
		//trk->SetDistanceFromTgtXZ(tx->Distance());
		//trk->SetDistanceFromTgtYR(ty->Distance());
		//trk->SetDistanceFromUpWireYR(ty->DistanceFromUpstreamWire());
		//trk->SetDistanceFromDownWireYR(ty->DistanceFromDownstreamWire());
		trk->SetResidualSSD(tx->ResidualSSD());    // NOT participate in fit 
		trk->SetFitResidual100X(tx->Residual100());// participate in fit
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
		trk->SetXZTrackUsedTimes(t->XZTrackUsedTimes());
		trk->SetDistanceYTrackAndTgt(t->DistanceYTrackAndTgt());
//		st_tracks[i].SetPtOnTrackGTR100(t->Pt0OnTrack());
//		st_tracks[i].SetPtOnTrackGTR300(t->Pt1OnTrack());
//		st_tracks[i].SetPtOnTrack3000mm(t->Pt2OnTrack());
		st_tracks.push_back(trk);
	}
	return 0;
}


int E16DST_DST1StraightTrackFactory2D(E16DST_DST0PhysicsEvent *event0, E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1, std::vector<std::shared_ptr<E16DST_DST1StraightTrack2D>> &stx_tracks, std::vector<std::shared_ptr<E16DST_DST1StraightTrack2D>> &sty_tracks, std::vector<std::shared_ptr<E16DST1_DST1CrossByStraight>> &cps,E16ANA_GTRcalibPedestal &gtrped, const int removed_layer){
	static bool isFirst = true;
	//static StraightTrackAnalyzerOfWireV1 *straight_analyzer;
	static StraightTrackAnalyzerOfTargets *straight_analyzer;
	static E16ANA_GeometryV2 *geom;
	if(isFirst){
        auto& calib = E16ANA_CalibDBManager::Instance();
        E16ANA_TargetInfoManager& targets = E16ANA_TargetInfoManager::Instance();
		targets.ReadInfoWithRunID(calib.CurrentRunID());
        targets.Print();
//		E16ANA_RundependentName& name = E16ANA_RundependentName::Instance();
//		string geomName = name.ReadNameWithRunID(calib.CurrentRunID(), "geometry", "/ccj/u/E16/database/");
//		std::cout << "geom name = " << geomName << std::endl;
//		geom = new E16ANA_GeometryV2(geomName);
		geom = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
		if(targets.NoT() == 3 ){
	        double x1 = targets.Info(0).Position().x();
    	    double z1 = targets.Info(0).Position().z();
        	double x2 = targets.Info(1).Position().x();
	        double z2 = targets.Info(1).Position().z();
        	double x3 = targets.Info(2).Position().x();
	        double z3 = targets.Info(2).Position().z();
			straight_analyzer = new StraightTrackAnalyzerOfTargets(targets.NoT(), x1 ,z1, x2, z2, x3, z3);//track selected only by GTR
	    }
		else{
			std::cerr << "### This is not Three targets run ###" << std::endl;
			return -1 ;
		}
		isFirst = false;
    	std::cout << " Parameters of Straight Track factory are set " << std::endl;
	}
//--- search linear tracks on XZ and YR planes 
    straight_analyzer->Clear();
  	for(int mid = 100; mid< 110; mid++){
		if(removed_layer == 0){//without ssd
 			straight_analyzer->OneModuleAnalyze2woSSD(2, ssd1, gtr1, mid, geom);
 		}
		else { //with all (-1), or without one layer GTR (1,2, 3)
 			straight_analyzer->OneModuleAnalyze2(2, ssd1, gtr1, mid, geom);
		}
	}
	straight_analyzer->Make2DCrossPoint(straight_analyzer->GetXZTrackCandidates(), geom);
	int trksx_size = straight_analyzer->GetXZTrackCandidates().size();
	int trksy_size = straight_analyzer->GetYTrackCandidates().size();
	int cp_size = straight_analyzer->GetCrossPoints().size();
	stx_tracks.clear();
	stx_tracks.reserve(trksx_size);
	sty_tracks.clear();
	sty_tracks.reserve(trksy_size);
	cps.clear();
	cps.reserve(cp_size);
//	std::cout << "trksx size = " << trksx_size << std::endl;
	for(int i=0; i<trksx_size; i++){
		std::shared_ptr<E16ANA_XZTrackCandidate> tx = straight_analyzer->GetXZTrackCandidates()[i];
		std::shared_ptr<E16DST_DST1StraightTrack2D> trk = std::make_shared<E16DST_DST1StraightTrack2D>();
		//	std::cout << "event 0 event_ID = " << event0->EventID() << std::endl;
		trk->SetEventID(event0->EventID());
		trk->SetAxis(0);
        trk->SetTrackID(i);
		trk->SetModuleID(tx->ModuleID());
//		std::cout << "in fac mid == " << tx->ModuleID() << std::endl;
		trk->SetID100Hit(tx->ID100Hit());
		trk->SetID200Hit(tx->ID200Hit());
		trk->SetID300Hit(tx->ID300Hit());
		trk->SetChi2(tx->Chi2());
		trk->SetTgtZ(tx->TgtZ());
//		std::cout << "in fac = " << trk->TgtZ() << std::endl;
	    trk->SetFitA(tx->GetFitA());
	    trk->SetFitB(tx->GetFitB());
//		trk->SetResidualSSD(tx->ResidualSSD());    // NOT participate in fit 
		trk->SetFitResidual100(tx->Residual100());// participate in fit
		trk->SetFitResidual200(tx->Residual200());
		trk->SetFitResidual300(tx->Residual300());
//		trk->SetSSDCluster(tx->GetXClusterSSD());
		trk->SetGTR100Cluster(tx->GetXCluster100());
		trk->SetGTR200Cluster(tx->GetXCluster200());
		trk->SetGTR300Cluster(tx->GetXCluster300());
//		trk->SetFitPtOnGTR100(tx->FitPtOnGTR100());
//		trk->SetFitPtOnGTR200(tx->FitPtOnGTR200());
//		trk->SetFitPtOnGTR300(tx->FitPtOnGTR300());
		stx_tracks.push_back(trk);
	}

	for(int i=0; i<trksy_size; i++){
		std::shared_ptr<E16ANA_YTrackCandidate> ty = straight_analyzer->GetYTrackCandidates()[i];
		std::shared_ptr<E16DST_DST1StraightTrack2D> trk = std::make_shared<E16DST_DST1StraightTrack2D>();
		trk->SetEventID(event0->EventID());
		trk->SetAxis(1);
        trk->SetTrackID(i);
		trk->SetModuleID(ty->ModuleID());
		trk->SetID100Hit(ty->ID100Hit());
		trk->SetID200Hit(ty->ID200Hit());
		trk->SetID300Hit(ty->ID300Hit());
//		trk->SetYTrackID(t->YTrackID());
		trk->SetChi2(ty->Chi2());
//		trk->SetTgtPosY(ty->TgtPos());
	    trk->SetFitA(ty->GetFitA());
	    trk->SetFitB(ty->GetFitB());
//		trk->SetDistanceFromTgtXZ(tx->Distance());
//		trk->SetDistanceFromTgtYR(ty->Distance());
//		trk->SetDistanceFromUpWireYR(ty->DistanceFromUpstreamWire());
//		trk->SetDistanceFromDownWireYR(ty->DistanceFromDownstreamWire());
		trk->SetFitResidual100(ty->Residual100());
		trk->SetFitResidual200(ty->Residual200());
		trk->SetFitResidual300(ty->Residual300());
		trk->SetGTR100Cluster(ty->GetYCluster100());
		trk->SetGTR200Cluster(ty->GetYCluster200());
		trk->SetGTR300Cluster(ty->GetYCluster300());
//		trk->SetDistanceYTrackAndTgt(t->DistanceYTrackAndTgt());
//		st_tracks[i].SetPtOnTrackGTR100(t->Pt0OnTrack());
//		st_tracks[i].SetPtOnTrackGTR300(t->Pt1OnTrack());
//		st_tracks[i].SetPtOnTrack3000mm(t->Pt2OnTrack());
		sty_tracks.push_back(trk);
	}
	for(int i=0; i < cp_size; i++){
		std::shared_ptr<E16ANA_XZCrossPoint> icp = straight_analyzer->GetCrossPoints()[i];
		std::shared_ptr<E16DST1_DST1CrossByStraight> ocp = std::make_shared<E16DST1_DST1CrossByStraight>();
		ocp->SetX(icp->CoordinateX());
		ocp->SetZ(icp->CoordinateZ());
		ocp->SetDistance(icp->Distance());
		ocp->SetChi2_1(icp->GetXZTrackCandidate1()->Chi2());
		ocp->SetChi2_2(icp->GetXZTrackCandidate2()->Chi2());
		ocp->SetMod1(icp->GetXZTrackCandidate1()->ModuleID());
		ocp->SetMod2(icp->GetXZTrackCandidate2()->ModuleID());
		cps.push_back(ocp);
	}

	return 0;
}


int E16DST_DST1StraightTrackFactoryV2(E16ANA_GeometryV2& geometry, E16ANA_MagneticFieldMap &bfield_map, E16ANA_StraightMultiTrack* fitter, E16ANA_StraightMultiTrack *pair_fitter, E16DST_DST1PhysicsRecord* record, E16ANA_StraightTrackCheckFile* check_file, std::vector<TVector3> &tgt_pos) {
  E16ANA_StraightTrackCandidates track_candidates(&geometry, &bfield_map, fitter, pair_fitter,  record, tgt_pos);
  static int n_calls;
  static int n_cands;
  static bool is_fill_param;
  track_candidates.Analyze();
//  track_candidates.Print(3);
  
//  for (auto& cand : track_candidates.TrackCandidates()) {
//    check_file0->AddEntry(n_calls, cand);
//  }
//  for (auto& cand : track_candidates.SelectedTrackCandidates()) {
//    check_file1->AddEntry(n_calls, *cand);
//  }
  if (!is_fill_param && track_candidates.NumTrackCandidates() != 0) {
    check_file->AddParam(track_candidates);
    is_fill_param = true;
  }
//  check_file->AddEntry(n_calls, geometry, *record, track_candidates);
  check_file->AddEntry(n_calls, geometry, track_candidates);
  ++n_calls;
  n_cands += track_candidates.NumTrackCandidates();
  E16INFO("Total Number of Track Candidates: %d", n_cands);
  return 0;
}
