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
#include "E16DST_DST1DetectorFactory.hh"

using namespace std;
//namespace  bpo = boost::program_options;




int main(int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [output.dst1] [run ID] [max physics event (all: -1)] " << endl;
    return -1;
  }
  
  TFile *f = new TFile("./outdir_root/output.root", "recreate");
  TTree *t = new TTree("t", "t");
  Int_t event_id;
  Int_t mod_id;
  Double_t g_x100;
  Double_t g_y100;
  Double_t g_z100;
  Double_t g_x300;
  Double_t g_y300;
  Double_t g_z300;
  Double_t l_cog_x300;
  Double_t l_cog_y300;
  Double_t clc_x100;
  Double_t clc_x200;
  Double_t clc_x300;
  Double_t clc_y100;
  Double_t clc_y200;
  Double_t clc_y300;
  Double_t timing_x100;
  Double_t timing_x200;
  Double_t timing_x300;
  Double_t timing_y100;
  Double_t timing_y200;
  Double_t timing_y300;
  Double_t residual_x100;
  Double_t residual_x200;
  Double_t residual_x300;
  Double_t residual_ssd;
  Double_t chi2_x;
  Double_t tgt_z;
  Int_t ncluster_ssd;
  Int_t asd_hit;
  Int_t lg_hit;
  TVector3 lg_cross_pos;
  Int_t lg_module_id;
  Int_t lg_channel_id;
  //	std::vector<TVector3> two_points_on_track;
  t->Branch("event_id", &event_id, "event_id/I");
  t->Branch("mod_id", &mod_id, "mod_id/I");
  t->Branch("g_x100", &g_x100, "g_x100/D");
  t->Branch("g_y100", &g_y100, "g_y100/D");
  t->Branch("g_z100", &g_z100, "g_z100/D");
  t->Branch("g_x300", &g_x300, "g_x300/D");
  t->Branch("g_y300", &g_y300, "g_y300/D");
  t->Branch("g_z300", &g_z300, "g_z300/D");
  t->Branch("l_cog_x300", &l_cog_x300, "l_cog_x300/D");
  t->Branch("l_cog_y300", &l_cog_y300, "l_cog_y300/D");
  t->Branch("clc_x100", &clc_x100, "clc_x100/D");
  t->Branch("clc_x200", &clc_x200, "clc_x200/D");
  t->Branch("clc_x300", &clc_x300, "clc_x300/D");
  t->Branch("clc_y100", &clc_y100, "clc_y100/D");
  t->Branch("clc_y200", &clc_y200, "clc_y200/D");
  t->Branch("clc_y300", &clc_y300, "clc_y300/D");
  t->Branch("timing_x100", &timing_x100, "timing_x100/D");
  t->Branch("timing_x200", &timing_x200, "timing_x200/D");
  t->Branch("timing_x300", &timing_x300, "timing_x300/D");
  t->Branch("timing_y100", &timing_y100, "timing_y100/D");
  t->Branch("timing_y200", &timing_y200, "timing_y200/D");
  t->Branch("timing_y300", &timing_y300, "timing_y300/D");
  t->Branch("residual_x100", &residual_x100, "residual_x100/D");
  t->Branch("residual_x200", &residual_x200, "residual_x200/D");
  t->Branch("residual_x300", &residual_x300, "residual_x300/D");
  t->Branch("residual_ssd", &residual_ssd, "residual_ssd/D");
  t->Branch("chi2_x", &chi2_x, "chi2_x/D");
  t->Branch("tgt_z", &tgt_z, "tgt_z/D");
  t->Branch("ncluster_ssd", &ncluster_ssd, "ncluster_ssd/I");
  t->Branch("asd_hit",&asd_hit, "asd_hit/I" );
  t->Branch("lg_hit",&lg_hit, "lg_hit/I" );
  t->Branch("lg_cross_pos", &lg_cross_pos);
  t->Branch("lg_module_id", &lg_module_id, "lg_module_id/I");
  t->Branch("lg_channel_id", &lg_channel_id,"lg_channel_id/I" );




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
    E16DST_DST1SSDFactory(ssd_hits0, &record->SSD());
    E16DST_DST1GTRFactory(gtr_hits0, &record->GTR(), gtrped);
    record->GTR().UpdatePtrs();
    record->SSD().UpdatePtrs();

//    &record->GTR();
	std::vector<std::shared_ptr<E16DST_DST1StraightTrack3D>> st_tracks;
	E16DST_DST1WireTrackFactory3D(event0, &record->SSD(), &record->GTR(), st_tracks, gtrped, geom);
	
	for(int i=0; i < st_tracks.size(); i++){
		std::shared_ptr<E16ANA_XYZStraightTrack> t = st_tracks[i];
		std::shared_ptr<E16ANA_XZTrackCandidate> tx = t->GetXZTrackCandidate();
		std::shared_ptr<E16ANA_YTrackCandidate> ty = t->GetYTrackCandidate();
		mod_id = t->ModuleID();
		
		tgt_z  = tk->TgtZ();
		xid    = t->XTrackID();
		yid    = t->YTrackID();
		chi2_x = tx->Chi2();
		chi2_y = ty->Chi2();
		tgtpos_y = ty->TgtPos();
	    fit_a_x = tx->GetFitA();
	    fit_b_x = tx->GetFitB();
	    fit_a_y = ty->GetFitA();
	    fit_b_y = ty->GetFitB();
		distance_x = tx->Distance();
		distance_y = ty->Distance();
		residual_ssdx = tx->ResidualSSD();
		residual_100x = tx->Residual100();
		residual_200x = tx->Residual200();
		residual_300x = tx->Residual300();
		residual_100y = ty->Residual100();
		residual_200y =	ty->Residual200();
		residual_300y = ty->Residual300();
		nGTR100(t->FitPtOnGTR100());
		nGTR200(t->FitPtOnGTR200());
		nGTR300(t->FitPtOnGTR300());


	}

//	if(st_tracks.size() != 0)std::cout << "st_tracks size =  " << st_tracks.size() << std::endl;
//	gtrhist->Fill(st_tracks);
//	gtrhist->Fill();	
    ++n_event;
    ++n_physics_event;
  }

 

  TCanvas *c0 = new TCanvas("c0", "c0", 1024, 768);
  TString pdf_name;
  pdf_name.Form("gtrtest.pdf");
  c0->SaveAs(pdf_name + "[", "pdf");

  TCanvas *c1 = new TCanvas();
  c1->Divide(3,2);
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
	c1->cd(m-101);
   	gtrhist->h_tgt_z[m-100]->Draw();
	if(m>105 ){
		c1->cd(m-102);
	    gtrhist->h_tgt_z[m-100]->Draw();
	}
  }
  c1->SaveAs(pdf_name, "pdf");



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
  c0->SaveAs( pdf_name + "]", "pdf");
//

//  delete geometry;
  delete dst0;
//  dst1->Close();
  return 0;
}
