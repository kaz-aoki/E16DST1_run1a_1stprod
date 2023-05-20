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

int E16DST_DST1WireTrackFactory3D(E16DST_DST0PhysicsEvent *event0, E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1, std::vector<std::shared_ptr<E16DST_DST1StraightTrack3D>> &st_tracks, E16ANA_GTRcalibPedestal &gtrped, const int removed_layer){
	static bool isFirst = true;
	static StraightTrackAnalyzerOfWireV1 *straight_analyzer;
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
		if(targets.IsWire()){
	        double x1 = targets.Info(0).Position().x();
    	    double z1 = targets.Info(0).Position().z();
        	double x2 = targets.Info(1).Position().x();
	        double z2 = targets.Info(1).Position().z();
			if(x1 < 0){
			straight_analyzer = new StraightTrackAnalyzerOfWireV1(2, 1, x1 ,z1, x2, z2);//track selected only by GTR : first arg is n of tgt, second is plus or minus, this is opposite with x1 sign cuz arg is based on beam coordinate
			}
			else if(x1 > 0){
			straight_analyzer = new StraightTrackAnalyzerOfWireV1(2, -1, x1 ,z1, x2, z2);//track selected only by GTR : first arg is n of tgt, second is plus or minus. this is oposite with x1 sign

			}
	    }
		else{
			std::cerr << "### This is not wire targets run ###" << std::endl;
			return -1 ;
		}
		isFirst = false;
    	std::cout << " Parameters of Wire factory are set " << std::endl;
	}
//--- search linear tracks on XZ and YR planes 
    straight_analyzer->Clear();
  	for(int mid = 100; mid< 110; mid++){
		if(removed_layer == 0){//without SSD
 			straight_analyzer->OneModuleAnalyze2woSSD(ssd1, gtr1, mid, geom);
		}
		else	{
 			straight_analyzer->OneModuleAnalyze2(ssd1, gtr1, mid, geom);
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
		trk->SetEventID(event0->EventID());
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
		trk->SetDistanceFromTgtXZ(tx->Distance());
		//trk->SetDistanceFromTgtYR(ty->Distance());
		trk->SetDistanceFromUpWireYR(ty->DistanceFromUpstreamWire());
		trk->SetDistanceFromDownWireYR(ty->DistanceFromDownstreamWire());
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
//		st_tracks[i].SetPtOnTrackGTR100(t->Pt0OnTrack());
//		st_tracks[i].SetPtOnTrackGTR300(t->Pt1OnTrack());
//		st_tracks[i].SetPtOnTrack3000mm(t->Pt2OnTrack());
		st_tracks.push_back(trk);
	}
	return 0;
}
