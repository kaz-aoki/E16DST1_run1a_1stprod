#include <stdlib.h>
#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
#include <regex>
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "GTR/GTRCheckHist.hh"
#include "E16ANA_TargetInfo.hh"
#include "E16ANA_RundependentName.hh"
#include "straight_track/StraightTrackAnalyzerV0.h"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16ANA_GTRStatus.h"
#include "E16ANA_GTRChannelManager.h"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_LGClustering.hh"
//#include "E16ANA_LGStraightProj.hh"
//#include "straightRoot.hh"
#include "E16DST_Constant.hh"

#include "E16ANA_StraightMultiTrack.hh"
#include "E16ANA_StraightTrackCandidate.hh"
#include "E16ANA_StraightTrackCheckFile.hh"

//#include  "E16DSTN_PosCorrection.hh"
#include  "E16DSTN_ReStraightV2.hh"



//using namespace E16DSTN_StraightParameter;
using namespace E16ANA_StraightTrackParameter;

//struct GeomMovePattern {
//	int pattern_id = -100;
//	double dx = 0;	
//	double dy = 0;	
//	double dz = 0;	
//	double radx = 0;
//	double rady = 0;
//	double radz = 0;
//};
//
//
//void SetGeomMovePattern(GeomMovePattern &gmove_pattern, const std::string& file, int pid){
//	std::ifstream infile(file);
//	std::string line;
//	while(std::getline(infile, line)) {
//		if(line.empty() || line[0] == '#' ){
//			continue;
//		}	
//		std::istringstream iss(line);
//		GeomMovePattern p;
//		if (iss >> p.pattern_id >> p.dx >> p.dy >> p.dz >> p.radx >> p.rady >> p.radz){
//			if(p.pattern_id == pid){
//				gmove_pattern.pattern_id = p.pattern_id;
//				gmove_pattern.dx     = p.dx;
//				gmove_pattern.dy     = p.dy;
//				gmove_pattern.dz     = p.dz;
//				gmove_pattern.radx   = p.radx;
//				gmove_pattern.rady   = p.rady;
//				gmove_pattern.radz   = p.radz;
//				std::cerr << "Pattern was successfully found " << std::endl;
//				return;
//			}
//		}
//	}
//	std::cerr << "Pattern not found " << std::endl;
//	exit(0);
//}

int main (int argc, char** argv) {
	if(argc != 7){
		std::cout << "./bin/~~ [input.root] [output.root] [runID] [event_start] [event_end] [GeomMovePatternID]" << std::endl;
		return 0;	
	}
	std::string in_file  = argv[1];
	std::string out_file = argv[2];
	std::string out_file_temp = out_file + "temp";
	int run_id           = stoi(argv[3]);
	int event_start      = stoi(argv[4]);
	int event_end        = stoi(argv[5]);
	int geom_move_pid   = stoi(argv[6]); // pattern id
	TFile *fin           = new TFile(in_file.c_str());
	TTree *tree          = (TTree*)fin->Get("tree");
	int nevent           = tree->GetEntries();
	int print_cycle      = 20000;
	bool vertex_xy_fix_flag = false;
   bool py_fix_flag        = false;
	bool vetex_z_fix_flag   = false;

	int target_mid = 106;

	auto& calib = E16ANA_CalibDBManager::Instance();
	calib.SetRunID(run_id);
	E16ANA_FieldMapCalibParam field_map_param;
	field_map_param.ReadConstantData(calib.CurrentRunID());
	E16ANA_GTRcalibPedestal gtrped;
	gtrped.ReadCalibData( calib.CurrentRunID() );
	E16ANA_GTRLorentzAngleCalibParamManager gtr_lorentz_angle_calib_param_manager;
	gtr_lorentz_angle_calib_param_manager.ReadConstantData(calib.CurrentRunID());
	auto gtr_lorentz_angle_calib_params = gtr_lorentz_angle_calib_param_manager.GTRLorentzAngleCalibParams();
//	auto geom = new E16ANA_GeometryV2(static_cast <std::string>(GeometryFile));
//	std::cout << "Read Geometry : " << static_cast<std::string>(GeometryFile) << std::endl;
//	std::string gfile = "/home/had/mtomoki/E16/work_dst1/E16DST1/geometry_Run0e_240625.dat";
//
//	SetGeomMovePattern("/home/had/mtomoki/E16/work_dst1/install/GeomMovePatterns.txt", geom_move_pid);
	
	std::string gfile = "/home/had/mtomoki/E16/work_dst1/E16DST1/geometry_Run0e_240627.dat";
	auto geom = new E16ANA_GeometryV2(static_cast <std::string>(gfile));
	std::cout << "Read Geometry : " << gfile << std::endl;

//	std::vector<E16ANA_PlanarGeometry*> geom_temp;
//	{	
//		auto gp = static_cast<const E16ANA_PlanarSTSGeometry*>(geom->STS(E16ANA_StraightTrackConstant::ModuleID2020To2013(target_mid)));
//		geom_temp.push_back(new E16ANA_PlanarSTSGeometry(*gp));
//	}
//	for(int l=1; l < 4; l++){
//		auto gp = static_cast<const E16ANA_PlanarGeometry*>(geom->GTR(E16ANA_StraightTrackConstant::ModuleID2020To2013(target_mid), l-1));
//		geom_temp.push_back(new E16ANA_PlanarGeometry(*gp));
//	}
	// align1
//	double dz[] = {0.0, 0.0, 0.0, 0.0};
//	for(int l=0; l < 4; l++){
//		geom_temp[l]->LocalTranslate(TVector3(0,0,dz));
//	}
	// align2
//	double dx[] = {0.0,0.0,0.0,0.0};
//	for(int l=0; l < 4; l++){
//		geom_temp[l]->LocalTranslate(TVector3(dx,0,0));
//	}
	
//	geom_temp[1]->LocalTranslate(TVector3(gmove_pattern.dx, gmove_pattern.dy ,gmove_pattern.dz));
	

	E16ANA_GeometryV2::SetGlobalPointer(geom);
	 
	auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
	bfield_map->Initialize_binary();
	E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);

//    pc->SetGeom(geom);
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

	E16ANA_StraightMultiTrack *fitter = new E16ANA_StraightMultiTrack( nullptr, geom,  targets_pos, 1);
	E16ANA_StraightMultiTrack *pair_fitter = new E16ANA_StraightMultiTrack( nullptr, geom,  targets_pos, 2);
	E16DSTN_ReStraightV2 *re = new E16DSTN_ReStraightV2(tree, out_file_temp.c_str(), geom,  fitter, pair_fitter, targets_pos);
	
	re->SetGeomMovePattern("/home/had/mtomoki/E16/work_dst1/install/GeomMovePatterns.txt", geom_move_pid);
	re->SetGeomTemp(target_mid);

//tracking again
   re->ReTrackingAndDuplicationCut(tree, print_cycle, event_start, event_end,vertex_xy_fix_flag, py_fix_flag, vetex_z_fix_flag, target_mid);
	TTree *outtree = re->TreeOut();
	fitter->Clear();
	pair_fitter->Clear();

	E16DSTN_ReStraightV2 *re_draw = new E16DSTN_ReStraightV2(outtree, out_file.c_str(), geom,  fitter, pair_fitter, targets_pos);
	re_draw->DrawHistWire(outtree, event_start, event_end, print_cycle, -1, "temp.pdf");
//	E16DSTN_ReStraightV2 *re_draw = new E16DSTN_ReStraightV2(tree, out_file.c_str(), geom, fitter, pair_fitter, targets_pos);
//	re_draw->DrawHistWire(tree, event_start, event_end, print_cycle, -1, "temp.pdf");
	re_draw->FileOut()->Write();//outtree
	return 0;	
}





