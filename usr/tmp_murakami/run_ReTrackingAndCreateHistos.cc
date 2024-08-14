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

Double_t func_GTR100(Double_t *x, Double_t *par) {

     Double_t xx = x[0];
    Double_t yy = x[1];
    Double_t A = par[0];
    Double_t A2 = par[1];
    Double_t x0 = par[2];
    Double_t x1 = par[3];
    Double_t y0 = par[4];
    Double_t sigmaX = par[5];
    Double_t sigmaX2 = par[6];
    Double_t sigmaY = par[7];
    
    Double_t gaussPart = A * exp(-0.5 * pow((yy - y0) / sigmaY, 2));
    Double_t gaussPart2 = A2 * exp(-0.5 * pow((yy - y0) / sigmaY, 2));

    if (xx < x0) {
        return gaussPart * exp(-0.5 * pow((xx - x0) / sigmaX2, 2));
    } else if (xx > x1) {
        return gaussPart2 * exp(-0.5 * pow((xx - x1) / sigmaX, 2));
    } else {
    Double_t slope = (gaussPart2 - gaussPart) / (x1 - x0);
            return gaussPart + slope * (xx - x0);
                }

}



double gaussian(double x, double mean, double sigma, double amplitude) {
    return amplitude * exp(-0.5 * pow((x - mean) / sigma, 2));
}

Double_t func_GTR200(Double_t *x, Double_t *params) {
  double xx = x[0];
    // 左側のガウス関数のパラメータ
   double mean1 = params[0];
   double sigma1 = params[1];
   double amp1 = params[2];
   double x1 = params[3];  // 左側ガウスと直線の接続点

	 // 右側のガウス関数のパラメータ
   double mean2 = params[4];
   double sigma2 = params[5];
   double amp2 = params[6];
 	double x2 = params[7];  // 右側ガウスと直線の接続点
     // 直線のスロープと切片を滑らかに接続するように調整
     double y1 = gaussian(x1, mean1, sigma1, amp1);
     double y2 = gaussian(x2, mean2, sigma2, amp2);
     double slope = (y2 - y1) / (x2 - x1);


      double intercept = y1 - slope * x1;

                  if (xx <= x1) {
                          // 左側のガウス関数
                                         return gaussian(xx, mean1, sigma1, amp1);
		} else if (xx > x1 && xx <= x2) {
        // 直線
                return slope * xx + intercept;
                    } else {
       // 右側のガウス関数
            return amp2 * 2- gaussian(xx, mean2, sigma2, amp2);
       }
}



Double_t func_GTR300(Double_t *x, Double_t *params) {
	double xx = x[0];
   double amp1 = params[0];
	 // 右側のガウス関数のパラメータ
   double mean2 = params[1];
   double sigma2 = params[2];
   double amp2 = params[3];
 	double x2 = params[4];  // 右側ガウスと直線の接続点
	double x1 = -150;//most left
   double y2 = gaussian(x2, mean2, sigma2, amp2);
	double slope = (y2 - amp1) / (x2-x1);
	double intercept = amp1 - slope * x1;
   if (xx <= x2) {
			return slope * xx + intercept;
     } else {
            return amp2 * 2 - gaussian(xx, mean2, sigma2, amp2);
//            return gaussian(xx, mean2, sigma2, amp2);
       }
}


int main (int argc, char** argv) {
	if(argc != 8){
		std::cout << "./bin/~~ [input.root] [output.root] [runID] [event_start] [event_end] [GeomMovePatternID] [t0_params]" << std::endl;
		return 0;	
	}
	std::string in_file  = argv[1];
	std::string out_file = argv[2];
	std::string out_file_temp = out_file + "temp";
	int run_id           = stoi(argv[3]);
	int event_start      = stoi(argv[4]);
	int event_end        = stoi(argv[5]);
	int geom_move_pid    = stoi(argv[6]); // pattern id
	int t0_param_pid     = stoi(argv[7]);
	TFile *fin           = new TFile(in_file.c_str());
	TTree *tree          = (TTree*)fin->Get("tree");
	int nevent           = tree->GetEntries();
	int print_cycle      = 2000;
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
	
	std::string gfile = "/home/had/mtomoki/E16/work_dst1/E16DST1/geometry_Run0e_240813.dat";
//	std::string gfile = "/home/had/mtomoki/E16/work_dst1/E16DST1/geometry_Run0e_240627.dat";
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

//t0 function
    TF2 *ft0_100 = new TF2("func_gtr100", func_GTR100, -50, 50, -50, 50, 10);
// p64   ft0_100->SetParameters(300, 279, -25, 29, 13, 25 , 22, 120); // A1, A2, x0, x1, y0, sigmaX, sigmaX2, sigmaY 
    ft0_100->SetParameters(300, 279, -25, 29, 13, 25 , 22, 300); // A1, A2, x0, x1, y0, sigmaX, sigmaX2, sigmaY 
    TF2 *ft0_200 = new TF2("func_gtr200", func_GTR200, -100, 100, -100, 100, 8);
    ft0_200->SetParameters(-85, 9, 350, -85, 85, 40, 330, 70);//mean1, sigma1, amp1, connection1, mean2, sigma2 ,amp2,connecion2

//pid 63
//    TF2 *ft0_300 = new TF2("func_gtr300", func_GTR300, -150, 150, -150, 150, 5);
//    ft0_300->SetParameters(250, 80, 120, 280, 80);// amp1, mean2, sigma2 ,amp2,connecion2
//pid 49   ft0_200->SetParameters(-85, 9, 350, -85, 80, 20, 330, 70);//mean1, sigma1, amp1, connection1, mean2, sigma2 ,amp2,connecion2

	
//    TF2 *ft0_300 = new TF2("func_gtr300", "[0]*TMath::Gaus(x, [1], [2])*TMath::Gaus(y, [3], [4]) + 280", -150, 150, -150, 150);
//    ft0_300->SetParameters(250, 80, 120, 280, 80);// amp1, mean2, sigma2 ,amp2,connecion2
	

	TF2 *ft0_300;
 ft0_300= new TF2("ft0_300", "[0]*TMath::Gaus(x, [1], [2]) * TMath::Gaus(y, [3], [4]) + [5]", -150, 150, -150, 150);
	ft0_300->SetParameter(0, 20);//amp
	ft0_300->SetParameter(1, 0);//mean
	ft0_300->SetParameter(2, 200);//sigma?
	ft0_300->SetParameter(3, 0);//mean
	ft0_300->SetParameter(4, 200);//sigma
	ft0_300->SetParameter(5, 280);//sigma
	
 

	std::string t0_file = "/home/had/mtomoki/E16/work_dst1/install/t0_func_params.txt";
	std::ifstream infile(t0_file);
	std::string line;
	int gtr_size, p_id;
//	double amp_x0, amp_x1, x0, x1, y0, sigma_x0, sigma_x1, sigma_y;
	double p0, p1, p2, p3, p4, p5;
	while (std::getline(infile, line)){
		if(line.empty() || line[0] == '#'){
			continue;
		}
		std::istringstream iss(line);
		if (iss >> p_id >> gtr_size >> p0 >> p1 >> p2 >> p3 >> p4 >> p5 ){
			if(p_id == t0_param_pid){
//    			ft0->SetParameters(300, 280, -30, 28, 8.4, 32, 10, 116);
				if(gtr_size == 0 ) { 
//    				ft0_100->SetParameters(amp_x0, amp_x1, x0, x1, y0, sigma_x0, sigma_x1, sigma_y);
				}
				else if(gtr_size == 1 ) { 
//    				ft0_200->SetParameters(amp_x0, amp_x1, x0, x1, y0, sigma_x0, sigma_x1, sigma_y);
				}
				else if(gtr_size == 2 ) { 
//    				ft0_300->SetParameters(p0, p1, p2, p3, p4, p5);
						ft0_300->SetParameter(0, p0);//amp
						ft0_300->SetParameter(1, p1);//mean
						ft0_300->SetParameter(2, p2);//sigma?
						ft0_300->SetParameter(3, p3);//mean
						ft0_300->SetParameter(4, p4);//sigma
						ft0_300->SetParameter(5, p5);//offset
						std::cout << "p4 = " << p4 << std::endl;
				}
			}
		}
	}
 	re->SetT0Func_GTR100(ft0_100);
 	re->SetT0Func_GTR200(ft0_200);
 	re->SetT0Func_GTR300(ft0_300);



   re->ReTrackingAndDuplicationCut(tree, print_cycle, event_start, event_end,vertex_xy_fix_flag, py_fix_flag, vetex_z_fix_flag, target_mid);
	TTree *outtree = re->TreeOut();
	outtree->Write();
	E16DSTN_ReStraightV2 *re_draw = new E16DSTN_ReStraightV2(outtree, out_file.c_str(), geom,  fitter, pair_fitter, targets_pos);
	re_draw->SetT0Func_GTR100(ft0_100);
	fitter->Clear();
	pair_fitter->Clear();

	re_draw->DrawHistWire(outtree, event_start, event_end, print_cycle, -1, "temp.pdf");
	re_draw->FileOut()->Write();
	re->FileOut()->Close();
	re_draw->FileOut()->Close();
	return 0;	
}





