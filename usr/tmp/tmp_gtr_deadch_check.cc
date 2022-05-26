#include <stdlib.h>
#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
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
#include "E16ANA_GTRAnalyzerMaker.hh"
#include "E16ANA_GTRAnalyzer2.h"
#include "E16ANA_GTRStripAnalyzer.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [output.dst1] [run ID] [max physics event (all: -1)] " << endl;
    return 1;
  }
   auto dst0 = new E16DST_DST0();
  if (!dst0->Open(argv[1], E16DST_DST0::ReadMode)) {
    std::cout << "failed to open file : " << argv[1]  <<std::endl;
	exit(1);
//    return 1;
  }
  string in_file_name = argv[1];
  int sink_id_pos = in_file_name.length() - 10;
  string sink_id = in_file_name.substr(sink_id_pos, 1);
  std::cout << "sink id = " << sink_id << std::endl;
  int smallest_id_pos = in_file_name.length()-8;
  string smallest_id = in_file_name.substr(smallest_id_pos, 3);
  std::cout << "smallest  id = " << smallest_id << std::endl;
  string runnum = argv[3];
  string run = "g4run0" + runnum;
  string outputfile = "./dst1_test/" + run + "_sink" + sink_id +"_"+ smallest_id+".root";

  const char* c_out = outputfile.c_str();
  auto out_file_name = argv[2];
  auto run_id        = stoi(argv[3]);
  auto max_event     = stoi(argv[4]);
  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  auto trigger_param = new E16ANA_TriggerCalibParam();
  trigger_param->ReadConstantData(calib.CurrentRunID());
  E16ANA_GTRcalibPedestal gtrped;
  gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_TargetInfoManager& targets = E16ANA_TargetInfoManager::Instance();
  targets.ReadInfoWithRunID( calib.CurrentRunID());
  targets.Print();
  E16ANA_GTRLorentzAngleCalibParamManager gtr_lorentz_angle_calib_param_manager;
  gtr_lorentz_angle_calib_param_manager.ReadConstantData(calib.CurrentRunID());
  auto gtr_lorentz_angle_calib_params = gtr_lorentz_angle_calib_param_manager.GTRLorentzAngleCalibParams();
  auto record = new E16DST_DST1PhysicsRecord();
  auto geom = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  auto *gtrhist = new GTRCheckHist();
  auto gtr_status = new E16ANA_GTRStatus(calib.CurrentRunID());

  TH2D *h_deadch_map[10][3];
  for(int m = 100; m < 110; m++){
  	for(int l = 0; l < 3; l++){
		h_deadch_map[m-100][l] = new TH2D(Form("h_deadch_map_m%d_l%d", m, l ), Form("h_deadch_map_m%d_l%d", m, l ), 288 * (l +1), (l+1)*(-50), (l+1)*50, 72 * (l+1), (l+1)*(-50), (l+1)*50);
	}
  }
  
  E16ANA_GTRcalibParams gtr_params;
  gtr_params.ReadCalibData(calib.CurrentRunID());
  E16ANA_GTRAnalyzerMaker *gtr_analyzers = new E16ANA_GTRAnalyzerMaker(gtr_params);
  for(int mid=100; mid <=110; mid++){
  	 for(int lid = 0; lid < 3; lid++){
       E16ANA_GTRAnalyzer2 *analyzer = gtr_analyzers->Chamber(mid, lid);
	   int n_strips = analyzer->GetNumberOfStrips();
	   for(int strip_id = 0; strip_id < n_strips; strip_id++){
                    double ped = gtrped.GetPedestal(mid, lid, strip_id).Value();
                    double sigma = gtrped.GetPedestal(mid, lid, strip_id).Sigma();
                    analyzer->SetPedestal(strip_id, ped);
                    analyzer->SetPedestalSigma(strip_id, sigma);
                }
	 }
  }
  //auto asd_dead = gtr_status->ASDDeadChannel();
//  gtr_status->ASDDeadChannel()->ReadDeadChannelData( calib.CurrentRunID());
//  for (int m=101; m< 110; m++){
//	for(int ch=0; ch < 24; ch++){
// 		std::cout << "GEM Status : module = " << m << ", ch = " << ch << ", gtr_dead " <<  gtr_status->GEMDeadArea300()->IsYOK(m, ch) << std::endl;
//	}
//  }
//  std::cout << "Is X GEM OK  == " << gtr_status->GEMDeadArea300()->IsXOK(106, 13.2) << std::endl;//GEM  


  array<array<TH2I*, 9>, 3> h_dead;
  double range[3] = {50., 100., 150.};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 9; ++j) {
      int mid = 101 + j;
      TString name = Form("hist_%d_%d", i, j);
      h_dead[i][j] = new TH2I(name, name, 200, -1. * range[i], range[i], 200, -1. * range[i], range[i]);
    }
  }
  auto gtr100_stat = gtr_status->GEMDeadArea100();
  auto gtr200_stat = gtr_status->GEMDeadArea200();
  auto gtr300_stat = gtr_status->GEMDeadArea300();
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 9; ++j) {
      auto mid = 101 + j;
      for (int k = 0; k < 200; ++k) {
        double x = k * range[i] / 100 - range[i];
        for (int l = 0; l < 200; ++l) {
          double y = l * range[i] / 100 - range[i];
          if (i == 0) {
            if (gtr100_stat->IsXOK(mid, x) && gtr100_stat->IsYOK(mid, y)) {
              h_dead[i][j]->Fill(x, y, 1);
            } else {
              h_dead[i][j]->Fill(x, y, -1);
            }
          } else if (i == 1) {
            if (gtr200_stat->IsXOK(mid, x) && gtr200_stat->IsYOK(mid, y)) {
              h_dead[i][j]->Fill(x, y, 1);
            } else {
              h_dead[i][j]->Fill(x, y, -1);
            }
          } else if (i == 2) {
            if (gtr300_stat->IsXOK(mid, x) && gtr300_stat->IsYOK(mid, y)) {
              h_dead[i][j]->Fill(x, y, 1);
            } else {
              h_dead[i][j]->Fill(x, y, -1);
            }
          }
        }
      }
    }
  }
  TString out_name = "~/tmp/tmp_murakami.pdf";
  auto out_canvas = new TCanvas();
  out_canvas->Print(out_name + "[");
  for (int i = 0; i < 3; ++i) {
    out_canvas->Clear();
    out_canvas->Divide(3, 3);
    for (int j = 0; j < 9; ++j) {
      out_canvas->cd(1 + j);
      h_dead[i][j]->Draw("colz");
    }
    out_canvas->Print(out_name);
  }
  out_canvas->Print(out_name + "]");



//	int n_xs = 0;//n strips
//	int n_ys = 0;
//  for(int m=100; m < 110; m++){
//	for(int l=0; l<3; l++){
//  	if(l ==0) {n_xs = 288; n_ys = 72 ;}
//  	else if(l ==1) {n_xs = 576; n_ys = 144 ;}
//  	else if(l ==2) {n_xs = 864; n_ys = 216 ;}
//	for(int i = 0; i < n_ys; i++){
//		double ly = -50*(l+1) + (double)1.4*i ;
// 	 	int apv_ch_y = E16ANA_GTRChannelManager::ConvLocalYToAPVch(l, ly);//(gtr_size, local_pos[mm])
//    	for(int j = 0; j < n_xs; j++){
//		double lx = -50 *(l+1) + 0.35*j;
// 	 	int apv_ch_x = E16ANA_GTRChannelManager::ConvLocalXToAPVch(l, lx);//(gtr_size, local_pos[mm])
//  		bool x =gtr_analyzers->Chamber(m, l)->GetStripX()->IsBadStrip(apv_ch_x);
//  		bool y =gtr_analyzers->Chamber(m, l)->GetStripY()->IsBadStrip(apv_ch_y);
//		int flag = 0;
//		if(x == 0 && y == 0){flag = 1;}
//		else {flag = 0;}
//		if(flag !=1){
//	//	std::cout << "lx, ly " << lx << ", " << ly << ", " << flag << std::endl;
//		}
//		if(flag) {h_deadch_map[m-100][l]->Fill(lx, ly);}
//  		}
//	}
//	}
//	}
//
//
//	TCanvas *c0  = new TCanvas("c0", "c0", 1024, 768);
//	TString pdf_name;
//	pdf_name.Form("gtrdeadch.pdf");
//	c0->SaveAs(pdf_name + "[", "pdf");
//   
//    TCanvas *c1 = new TCanvas("c1", "c1", 1024, 768);	
//	c1->Divide(3,4);
//	for(int m=101; m<110;  m++){
//		c1->cd(m-100);
//	    h_deadch_map[m-100][0]->SetStats(0);
//	    h_deadch_map[m-100][0]->Draw("colz");
//		std::cout << m << std::endl;
//	}
//	std::cout << "here "  << std::endl;
//	c1->SaveAs(pdf_name, "pdf");	
//	
//     TCanvas *c2 = new TCanvas("c2", "c2", 1024, 768);	
//	c2->Divide(3,4);
//	for(int m=101; m<110;  m++){
//		c2->cd(m-100);
//	    h_deadch_map[m-100][1]->SetStats(0);
//	    h_deadch_map[m-100][1]->Draw("colz");
//		std::cout << m << std::endl;
//	}
//	std::cout << "here "  << std::endl;
//	c2->SaveAs(pdf_name, "pdf");	
//	    TCanvas *c3 = new TCanvas("c3", "c3", 1024, 768);	
//	c3->Divide(3,4);
//	for(int m=101; m<110;  m++){
//		c3->cd(m-100);
//	    h_deadch_map[m-100][2]->SetStats(0);
//	    h_deadch_map[m-100][2]->Draw("colz");
//		std::cout << m << std::endl;
//	}
//	std::cout << "here "  << std::endl;
//	c3->SaveAs(pdf_name, "pdf");	
//	  
//	c0->SaveAs(pdf_name + "]", "pdf");
	return 0;
}
