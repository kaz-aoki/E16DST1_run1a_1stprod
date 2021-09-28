//this is test for wire track factory 
//
//
//
#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
//#include <boost/program_options.hpp>

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

using namespace std;
//namespace  bpo = boost::program_options;

int main(int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [output.dst1] [run ID] [max physics event (all: -1)] " << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto run_id        = stoi(argv[3]);
  auto max_event     = stoi(argv[4]);
  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  E16ANA_RundependentName& name = E16ANA_RundependentName::Instance();
  string geomName = name.ReadNameWithRunID(run_id, "geometry", "/ccj/u/E16/database/");
  E16ANA_GeometryV2* geom = new E16ANA_GeometryV2(geomName);
  E16ANA_GeometryV2::SetGlobalPointer(geom);

  auto trigger_param = new E16ANA_TriggerCalibParam();
  trigger_param->ReadConstantData(calib.CurrentRunID());
  E16ANA_GTRcalibPedestal gtrped;
  gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_TargetInfoManager& targets = E16ANA_TargetInfoManager::Instance();
  targets.ReadInfoWithRunID( calib.CurrentRunID());
  targets.Print();
  auto record = new E16DST_DST1PhysicsRecord();
//  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  auto *gtrhist = new GTRCheckHist();
  
  auto dst0 = new E16DST_DST0();

  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
  int n_event = 0;
  int n_physics_event = 0;
  while (dst0->ReadAnEvent()) {
 //   if (max_event != -1 && n_physics_event >= max_event) {
    if (max_event != -1 && n_event >= max_event) {
      break;
    }
    if (n_event % 1000 == 0) {
      cout << "Number of event: " << n_event << endl;
    }
    if (dst0->EventType() != E16DST_DST0EventType::Physics){
        std::cout << "Event ID = " << dst0->Event()->EventID() << " is not Physics Event, Event Type =" << dst0->Event()->EventType() << std::endl;
        continue;
    }
//
//
    auto event_type = dst0->EventType();
    E16DST_DST0PhysicsEvent *event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
    auto& gtr_hits0 = event0->GTR();
    auto& ssd_hits0 = event0->SSD();
    E16DST_DST1GTRFactoryDST1Detector(gtr_hits0, &record->GTR(), gtrped);
    record->GTR().UpdatePtrs();
//    &record->GTR();
	std::vector<E16DST_DST1StraightTrack2D> st_tracks;
    E16DST_DST1WireTrackFactory2D(event0, &record->SSD(), &record->GTR(), st_tracks, gtrped, geom);
//	gtrhist->Fill();	
    ++n_event;
    ++n_physics_event;
  }

 

//  TCanvas *c1 = new TCanvas("c1", "c1", 1024, 768);
//  TString pdf_name;
//  pdf_name.Form("gtrtest.pdf");
//  c1->SaveAs(pdf_name + "[", "pdf");
//
//  TCanvas *c_cl_charge_x[10]; 
//  //= new TCanvas("cl charge ", 100,0,100);
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_charge_x[m-102] = new TCanvas(Form("ccx%d", m-102) , Form("ccx%d", m-102), 1024, 768);
//    c_cl_charge_x[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_charge_x[m-102]->cd(l+1);
//        gtrhist->h_cl_charge_x[m-100][l]->Draw();
//    }
//    c_cl_charge_x[m-102]->SaveAs(pdf_name, "pdf");
//  }
// 
//  TCanvas *c_cl_charge_y[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_charge_y[m-102] = new TCanvas(Form("ccy%d", m-102), Form("ccy%d", m-102), 1024, 768);
//    c_cl_charge_y[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_charge_y[m-102]->cd(l+1);
//        gtrhist->h_cl_charge_y[m-100][l]->Draw();
//    }
//    c_cl_charge_y[m-102]->SaveAs(pdf_name, "pdf");
//  }
//  
//  TCanvas *c_cl_charge_yb[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_charge_yb[m-102] = new TCanvas(Form("ccyb%d", m-102), Form("ccyb%d", m-102), 1024, 768);
//    c_cl_charge_yb[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_charge_yb[m-102]->cd(l+1);
//        gtrhist->h_cl_charge_yb[m-100][l]->Draw();
//    }
//    c_cl_charge_yb[m-102]->SaveAs(pdf_name, "pdf");
//  }
//  
//  TCanvas *c_cl_local_x[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_local_x[m-102] = new TCanvas(Form("clx%d", m-102), Form("clx%d", m-102), 1024, 768);
//    c_cl_local_x[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_local_x[m-102]->cd(l+1);
//        gtrhist->h_cl_local_x[m-100][l]->Draw();
//    }
//    c_cl_local_x[m-102]->SaveAs(pdf_name, "pdf");
//  }
//
//  TCanvas *c_cl_local_y[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_local_y[m-102] = new TCanvas(Form("cly%d", m-102), Form("cly%d", m-102), 1024, 768);
//    c_cl_local_y[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_local_y[m-102]->cd(l+1);
//        gtrhist->h_cl_local_y[m-100][l]->Draw();
//    }
//    c_cl_local_y[m-102]->SaveAs(pdf_name, "pdf");
//  }
//   TCanvas *c_cl_local_yb[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_local_yb[m-102] = new TCanvas(Form("clyb%d",m-102), Form("clyb%d", m-102), 1024, 768);
//    c_cl_local_yb[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_local_yb[m-102]->cd(l+1);
//        gtrhist->h_cl_local_yb[m-100][l]->Draw();
//    }
//    c_cl_local_yb[m-102]->SaveAs(pdf_name, "pdf");
//  }
// 
//  TCanvas *c_cl_max_peak_x[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_max_peak_x[m-102] = new TCanvas(Form("clmpx%d", m-102), Form("clmpx%d", m-102), 1024, 768);
//    c_cl_max_peak_x[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_max_peak_x[m-102]->cd(l+1);
//        gtrhist->h_cl_max_peak_x[m-100][l]->Draw();
//    }
//    c_cl_max_peak_x[m-102]->SaveAs(pdf_name, "pdf");
//  }
//  
//  TCanvas *c_cl_max_peak_y[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_max_peak_y[m-102] = new TCanvas(Form("clmpy%d",m-102), Form("clmpy%d", m-102), 1024, 768);
//    c_cl_max_peak_y[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_max_peak_y[m-102]->cd(l+1);
//        gtrhist->h_cl_max_peak_y[m-100][l]->Draw();
//    }
//    c_cl_max_peak_y[m-102]->SaveAs(pdf_name, "pdf");
//  }
//
//  TCanvas *c_cl_max_peak_yb[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_max_peak_yb[m-102] = new TCanvas(Form("clmpyb%d", m-102), Form("clmpyb%d", m-102), 1024, 768);
//    c_cl_max_peak_yb[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_max_peak_yb[m-102]->cd(l+1);
//        gtrhist->h_cl_max_peak_yb[m-100][l]->Draw();
//    }
//    c_cl_max_peak_yb[m-102]->SaveAs(pdf_name, "pdf");
//  }
//
//  TCanvas *c_cl_max_peak_ch_x[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_max_peak_ch_x[m-102] = new TCanvas(Form("clmpchx%d", m-102), Form("clmpchx%d", m-102), 1024, 768);
//    c_cl_max_peak_ch_x[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_max_peak_ch_x[m-102]->cd(l+1);
//        gtrhist->h_cl_max_peak_ch_x[m-100][l]->Draw();
//    }
//    c_cl_max_peak_x[m-102]->SaveAs(pdf_name, "pdf");
//  }
// 
//  TCanvas *c_cl_tdcpos_x[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_tdcpos_x[m-102] = new TCanvas(Form("cltdcposx%d", m-102), Form("cltdcposx%d", m-102), 1024, 768);
//    c_cl_tdcpos_x[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_tdcpos_x[m-102]->cd(l+1);
//        gtrhist->h_cl_tdcpos_x[m-100][l]->Draw();
//    }
//    c_cl_tdcpos_x[m-102]->SaveAs(pdf_name, "pdf");
//  }
// 
//  TCanvas *c_cl_tdcpos_y[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_tdcpos_y[m-102] = new TCanvas(Form("cltdcposy%d", m-102), Form("cltdcposy%d", m-102), 1024, 768);
//    c_cl_tdcpos_y[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_tdcpos_x[m-102]->cd(l+1);
//        gtrhist->h_cl_tdcpos_y[m-100][l]->Draw();
//    }
//    c_cl_tdcpos_y[m-102]->SaveAs(pdf_name, "pdf");
//  }
//   TCanvas *c_cl_tdcpos_yb[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_tdcpos_yb[m-102] = new TCanvas(Form("cltdcposyb%d", m-102), Form("cltdcposyb%d", m-102), 1024, 768);
//    c_cl_tdcpos_yb[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_tdcpos_yb[m-102]->cd(l+1);
//        gtrhist->h_cl_tdcpos_yb[m-100][l]->Draw();
//    }
//    c_cl_tdcpos_yb[m-102]->SaveAs(pdf_name, "pdf");
//  }
//
//  TCanvas *c_cl_tan_x[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_tan_x[m-102] = new TCanvas(Form("cltanx%d", m-102), Form("cltanx%d", m-102), 1024, 768);
//    c_cl_tan_x[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_tan_x[m-102]->cd(l+1);
//        gtrhist->h_cl_tan_x[m-100][l]->Draw();
//    }
//    c_cl_tan_x[m-102]->SaveAs(pdf_name, "pdf");
//  }
//   TCanvas *c_cl_tan_y[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_tan_y[m-102] = new TCanvas(Form("cltany%d", m-102), Form("cltany%d", m-102), 1024, 768);
//    c_cl_tan_y[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_tan_y[m-102]->cd(l+1);
//        gtrhist->h_cl_tan_y[m-100][l]->Draw();
//    }
//    c_cl_tan_y[m-102]->SaveAs(pdf_name, "pdf");
//  }
//    TCanvas *c_cl_tan_yb[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_tan_yb[m-102] = new TCanvas(Form("cltanyb%d", m-102), Form("cltanyb%d", m-102), 1024, 768);
//    c_cl_tan_yb[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_tan_yb[m-102]->cd(l+1);
//        gtrhist->h_cl_tan_yb[m-100][l]->Draw();
//    }
//    c_cl_tan_yb[m-102]->SaveAs(pdf_name, "pdf");
//  }
// 
//
//  c1->SaveAs( pdf_name + "]", "pdf");
//

//  delete geometry;
  delete dst0;
//  dst1->Close();
  return 0;
}
