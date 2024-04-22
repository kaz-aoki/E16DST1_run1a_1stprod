//#define E16DSTN_ReadStraightTree_cxx
#define E16DSTN_PosCorrection_cxx

//#include "E16DSTN_ReadStraightTree.hh"
#include "E16ANA_StraightTrackParameter.hh"
#include <string>
#include <map>
#include <array>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TROOT.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TVector3.h"
#include <vector>
//#include "TMLocal_StraightAnalyzer.hh"
//#include "E16ANA_GeometryV2.hh"
#include "E16ANA_StraightTrackNameSpace.hh"
#include "E16ANA_StraightTrack.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_LGClustering.hh"
#include "E16ANA_LGStraightProj.hh"
//#include "straightRoot.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16DSTN_PosCorrection.hh"
#include "E16ANA_TargetInfo.hh"
#include "E16DST_DST1DefaultFilePath.hh.in"

//using namespace E16DSTN_StraightParameter;
using namespace E16ANA_StraightTrackParameter;

int main (int argc, char** argv) {
	if(argc != 6){
		std::cout << "./bin/~~ [input.root] [output.root] [runID] [max_analyzed_event] [anaSw]" << std::endl;
		return 0;	
	}
	bool isWire = true;
	std::string in_file  = argv[1];
	std::string out_file = argv[2];
	int run_id        = stoi(argv[3]);
	int max_event        = stoi(argv[4]);
	int anaSW            = stoi(argv[5]);
	TFile *fin           = new TFile(in_file.c_str());
	TTree *tree          = (TTree*)fin->Get("tree");
	//E16DSTN_ReadStraightTree *rt = new E16DSTN_ReadStraightTree(tree, out_file.c_str());
	//rt->SetRemovedLayer(removed_layer);
	E16DSTN_PosCorrection *pc = new E16DSTN_PosCorrection(tree, out_file.c_str());
	int nevent           = tree->GetEntries();
	int print_cycle      = 2000;
	bool vertex_xy_fix_flag = false;
   bool py_fix_flag = false;
	bool vetex_z_fix_flag = false;

	auto geom = new E16ANA_GeometryV2(static_cast <std::string>(GeometryFile));
	std::cout << "Read Geometry : " << static_cast<std::string>(GeometryFile) << std::endl;
   E16ANA_GeometryV2::SetGlobalPointer(geom);
//	pc->SetGeom(geom);
	
    auto& calib = E16ANA_CalibDBManager::Instance();
    calib.SetRunID(run_id);
    E16ANA_FieldMapCalibParam field_map_param;
    field_map_param.ReadConstantData(calib.CurrentRunID());
    E16ANA_GTRcalibPedestal gtrped;
    gtrped.ReadCalibData( calib.CurrentRunID() );
    E16ANA_GTRLorentzAngleCalibParamManager gtr_lorentz_angle_calib_param_manager;
    gtr_lorentz_angle_calib_param_manager.ReadConstantData(calib.CurrentRunID());
    auto gtr_lorentz_angle_calib_params = gtr_lorentz_angle_calib_param_manager.GTRLorentzAngleCalibParams();
  
    E16ANA_TriggerCalibParam trigger_param;
    trigger_param.ReadConstantData(calib.CurrentRunID());
 

// targets info 
	 E16ANA_TargetInfoManager &targets = E16ANA_TargetInfoManager::Instance();
	 targets.ReadInfoWithRunID(calib.CurrentRunID());
	 targets.Print();
	 std::vector<TVector3> targets_pos;
	 targets_pos.clear();
    if(targets.NoT() == 3 ){
            targets_pos.push_back(TVector3( targets.Info(0).Position().x(),targets.Info(0).Position().y(),  targets.Info(0).Position().z()));
            targets_pos.push_back(TVector3( targets.Info(1).Position().x(),targets.Info(1).Position().y(),  targets.Info(1).Position().z()));
            targets_pos.push_back(TVector3( targets.Info(2).Position().x(),targets.Info(2).Position().y(),  targets.Info(2).Position().z()));
     }
     else if (targets.IsWire()){
         targets_pos.push_back(TVector3  (targets.Info(0).Position().x(), targets.Info(0).Position().y(), targets.Info(0).Position().z()));
         targets_pos.push_back(TVector3  (targets.Info(1).Position().x(), targets.Info(1).Position().y(), targets.Info(1).Position().z()));
     }
    else {
      return -1;
    }

 



	E16ANA_StraightMultiTrack *fitter = new E16ANA_StraightMultiTrack(geom, targets_pos, 1);
	pc->SetFitter(fitter);
	pc->SetIsWire(isWire);
//	pc->SetRemovedLayer(removed_layer);
	pc->PosCoLoop(tree, print_cycle, max_event, vertex_xy_fix_flag, py_fix_flag, vetex_z_fix_flag , anaSW );
	pc->FileOut()->Write();
	return 0;	
}





