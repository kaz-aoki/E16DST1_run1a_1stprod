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
  if (argc != 3) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [run ID]  " << endl;
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
  string runnum = argv[2];
  string run = "g4run0" + runnum;
  string outputfile = "./dst1_test/" + run + "_sink" + sink_id +"_"+ smallest_id+".root";

  const char* c_out = outputfile.c_str();
//  auto out_file_name = argv[2];
  auto run_id        = stoi(argv[2]);
//  auto max_event     = stoi(argv[4]);
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
  auto *cm = new E16ANA_GTRChannelManager();

  TH2D *h_deadch_map[10][3];
  TH2D *h_deadch_map_ch[10][3];
  TH2D *h_gem_deadch_map[10][3];
  for(int m = 100; m < 110; m++){
  	for(int l = 0; l < 3; l++){
		h_deadch_map[m-100][l] = new TH2D(Form("h_deadch_map_m%d_l%d", m, l ), Form("h_deadch_map_m%d_l%d", m, l ), 288 * (l +1), (l+1)*(-50.4), (l+1)*50.4, 72 * (l+1), (l+1)*(-50), (l+1)*50);
		h_deadch_map_ch[m-100][l] = new TH2D(Form("h_deadch_map_ch_m%d_l%d", m, l ), Form("h_deadch_map_ch_m%d_l%d", m, l ), 288 * (l +1), -0.5, (l+1)*288 + 0.5, 72 * (l+1), -0.5 , (l+1)*72);
		h_gem_deadch_map[m-100][l] = new TH2D(Form("h_gem_deadch_map_m%d_l%d", m, l ), Form("h_gem_deadch_map_m%d_l%d", m, l ), 288 * (l +1), (l+1)*(-50), (l+1)*50, 72 * (l+1), (l+1)*(-50), (l+1)*50);
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
//					if(mid == 107 && lid ==0){
//					std::cout << "sid   = " << strip_id << std::endl;
//					std::cout << "ped   = " << ped << std::endl;
//					std::cout << "sigma = " << sigma << std::endl;
//					}
                    analyzer->SetPedestal(strip_id, ped);
                    analyzer->SetPedestalSigma(strip_id, sigma);
                }
	 }
  }
  auto asd_dead = gtr_status->ASDDeadChannel();
  //gtr_status->ASDDeadChannel()->ReadDeadChannelData( calib.CurrentRunID());
//<<<<<<< HEAD
//  for (int m=101; m< 110; m++){
//	for(int ch=0; ch < 24; ch++){
// 		std::cout << "GEM Status : module = " << m << ", ch = " << ch << ", gtr_dead " <<  gtr_status->GEMDeadArea300()->IsYOK(m, ch) << std::endl;
//	}
//  }
//  std::cout << "Is X GEM OK  == " << gtr_status->GEMDeadArea300()->IsXOK(106, 13.2) << std::endl;//GEM  

	int n_xs[3] = {288,576,864};//n strips
	int n_ys[3] = {72 ,144,216};
	double lx, ly;
	for(int m=101; m<110; m++){
		for(int l =0; l<3;l++){
			for(int i=0; i<n_xs[l];i++){
				lx = -0.35*(n_xs[l]/2 - 1) - 0.175 + 0.35*i;
				for(int j=0; j< n_ys[l]; j++){
					ly = -1.4*(n_ys[l]/2 - 1) -0.7 + (double)1.4*(j) ;
//					if(m == 101 && l == 2 ){
//					if(j == 20){
//					std::cout << "lx " << lx << " ly " << ly << std::endl;
//					std::cout << "apv x ch  = " << E16ANA_GTRChannelManager::ConvLocalXToAPVch(l, lx) << std::endl;
//					std::cout << "apv y ch  = " << E16ANA_GTRChannelManager::ConvLocalYToAPVch(l, lx, ly) << std::endl;
//					if(m == 103 && l == 0 ){
//						std::cout << "module = " << m << " " << l << " " << std::endl;
//						std::cout << "gtr status = " << gtr_status-> GTRStatus(m, l, lx, ly ) << std::endl;
//					}}
					if(gtr_status->GTRStatus(m, l, lx, ly) == 0){
						h_deadch_map[m-100][l]->Fill(lx, ly);
// if you want to use lx[mm], ly[mm], they have to be converted like bellow
// 	    int apv_ch_y = E16ANA_GTRChannelManager::ConvLocalYToAPVch(l,lx, ly);//(gtr_size, local_pos[mm])
// 	 	int apv_ch_x = E16ANA_GTRChannelManager::ConvLocalXToAPVch(l, lx);//(gtr_size, local_pos[mm])
					}
//}
				}
			}
		}
	}
//  for(int m=100; m < 110; m++){
//	for(int l=0; l<3; l++){
//  	if(l ==0) {n_xs = 288; n_ys = 72 ;}
//  	else if(l ==1) {n_xs = 576; n_ys = 144 ;}
//  	else if(l ==2) {n_xs = 864; n_ys = 216 ;}
//	for(int i = 0; i < n_ys; i++){
//		double ly = -50*(l+1) + (double)1.4*i ;
//    	for(int j = 0; j < n_xs; j++){
//		double lx = -50 *(l+1) + 0.35*j;
// 	
// 	    int apv_ch_y = E16ANA_GTRChannelManager::ConvLocalYToAPVch(l,lx, ly);//(gtr_size, local_pos[mm])
// 	 	int apv_ch_x = E16ANA_GTRChannelManager::ConvLocalXToAPVch(l, lx);//(gtr_size, local_pos[mm])
//		bool x =gtr_analyzers->Chamber(m, l)->GetStripX()->IsBadStrip(apv_ch_x);
//		bool y; 
//  		if(l == 0 &&  lx < 0) y =static_cast<E16ANA_GTR100Analyzer *> (gtr_analyzers->Chamber(m, l))->GetStripYb()->IsBadStrip(apv_ch_y);
//  	    else  { y =gtr_analyzers->Chamber(m, l)->GetStripY()->IsBadStrip(apv_ch_y);}
//		int flag = 0;
//		if(x == 0 && y == 0){flag = 1;}
//		else {flag = 0;}
//		if(flag !=1){
//		}
//		if(flag) {h_deadch_map[m-100][l]->Fill(lx, ly);}
//		if(l == 0 ){
//			if(gtr1_dead->IsXOK(m, lx) && gtr1_dead->IsYOK(m, ly)){
//				h_gem_deadch_map[m-100][l]->Fill(lx, ly);
//			}
//		}
//		else if(l == 1 ){
//			if(gtr2_dead->IsXOK(m, lx) && gtr2_dead->IsYOK(m, ly)){
//				h_gem_deadch_map[m-100][l]->Fill(lx, ly);
//			}
//		}
//		else if(l == 2 ){
//			if(gtr3_dead->IsXOK(m, lx) && gtr3_dead->IsYOK(m, ly)){
//				h_gem_deadch_map[m-100][l]->Fill(lx, ly);
//			}
//		}
//  		}
//	}
//	}
//	}
//

	TCanvas *c0  = new TCanvas("c0", "c0", 1024, 768);
	TString pdf_name;
	pdf_name.Form("gtrdeadch_run%d.pdf", run_id);
	c0->SaveAs(pdf_name + "[", "pdf");

    TCanvas *c11 = new TCanvas("c11", "c11", 1024, 768);	
    c11->Divide(8,3);
	int cnt = 1;
    for(int m=101; m<110;  m++){
		if(m == 105) continue;
//		for(int l=0; l < 3 ;l++){
      		c11->cd(25-cnt);
	   		h_deadch_map[m-100][0]->SetStats(0);
    	    h_deadch_map[m-100][0]->Draw("colz");
      		c11->cd(17-cnt);
	   		h_deadch_map[m-100][1]->SetStats(0);
    	    h_deadch_map[m-100][1]->Draw("colz");
      		c11->cd(9-cnt);
	   		h_deadch_map[m-100][2]->SetStats(0);
    	    h_deadch_map[m-100][2]->Draw("colz");
			cnt++;
 //		}
	}
  	c11->SaveAs(pdf_name, "pdf");	
 

	

//    TCanvas *c1 = new TCanvas("c1", "c1", 1024, 768);	
//	c1->Divide(3,4);
//	for(int m=101; m<110;  m++){
//		c1->cd(m-100);
//	    h_deadch_map[m-100][0]->SetStats(0);
//	    h_deadch_map[m-100][0]->Draw("colz");
//	}
//	c1->SaveAs(pdf_name, "pdf");	
//	
//     TCanvas *c2 = new TCanvas("c2", "c2", 1024, 768);	
//	c2->Divide(3,4);
//	for(int m=101; m<110;  m++){
//		c2->cd(m-100);
//	    h_deadch_map[m-100][1]->SetStats(0);
//	    h_deadch_map[m-100][1]->Draw("colz");
//	}
//	c2->SaveAs(pdf_name, "pdf");	
//	    TCanvas *c3 = new TCanvas("c3", "c3", 1024, 768);	
//	c3->Divide(3,4);
//	for(int m=101; m<110;  m++){
//		c3->cd(m-100);
//	    h_deadch_map[m-100][2]->SetStats(0);
//	    h_deadch_map[m-100][2]->Draw("colz");
//	}
//	std::cout << "here "  << std::endl;
//	c3->SaveAs(pdf_name, "pdf");	
	
	TCanvas *c4[3];	
	for(int i = 0; i < 3; i++){
    c4[i] = new TCanvas(Form("c4%d", i), Form("c4%d", i), 1024, 768);	
	c4[i]->Divide(3,4);
	for(int m=101; m<110;  m++){
		c4[i]->cd(m-100);
	    h_gem_deadch_map[m-100][i]->SetStats(0);
	    h_gem_deadch_map[m-100][i]->Draw("colz");
	}
	c4[i]->SaveAs(pdf_name, "pdf");	
	}
	
	  
	c0->SaveAs(pdf_name + "]", "pdf");
	return 0;
//=======
//  for (int m=101; m< 110; m++){
//	for(int ch=0; ch < 24; ch++){
// 		std::cout << "GEM Status : module = " << m << ", ch = " << ch << ", gtr_dead " <<  gtr_status->GEMDeadArea300()->IsYOK(m, ch) << std::endl;
//	}
//  }
//  std::cout << "Is X GEM OK  == " << gtr_status->GEMDeadArea300()->IsXOK(106, 13.2) << std::endl;//GEM  
//  std::cout << "apv ch convorotor returns   == " << E16ANA_GTRChannelManager::ConvLocalXToAPVch(0, 0.2) << std::endl;//
//  int apv_ch = E16ANA_GTRChannelManager::ConvLocalXToAPVch(0, 12);//(gtr_size, local_pos[mm])
//  std::cout << "is bad apv ? : "  << gtr_analyzers->Chamber(106, 1)->GetStripX()->IsBadStrip(apv_ch) << std::endl;
  
  
//  int n_event = 0;
//  int n_physics_event = 0;
//  std::cout << "here " << std::endl;
//  while (dst0->ReadAnEvent()) {
//    if (max_event != -1 && n_event >= max_event) {
//      break;
//    }
//    if (n_event % 100 == 0) {
//      cout << "Number of event: " << n_event << endl;
//    }
//    if (dst0->EventType() != E16DST_DST0EventType::Physics){
//        std::cout << "Event ID = " << dst0->Event()->EventID() << " is not Physics Event, Event Type =" << dst0->Event()->EventType() << std::endl;
//        continue;
//    }
////
//	
////	if(st_tracks.size() != 0)std::cout << "st_tracks size =  " << st_tracks.size() << std::endl;
////	gtrhist->Fill(st_tracks);
////	gtrhist->Fill();	
//    ++n_event;
//    ++n_physics_event;
//  }
//
 
  return 0;
//>>>>>>> upstream/main
}
