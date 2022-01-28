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
#include "E16DST_DST1DetectorFactory.hh"

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

  TFile *fout = new TFile(out_file_name,"recreate");

//  bpo::variables_map vm;
//  string in_file_name;
//  string out_file_name;
//  int run_num;

//  bpo::options_description command_options("command options");
//  command_options.add_options()
//    ("in",                           bpo::value<string>(&in_file_name),                                                                "Input file name (string)\n")
//    ("out",                          bpo::value<string>(&out_file_name),                                                               "Output file name (string)\n")
//    ("coincidence-map-file-w-mag0",  bpo::value<string>(&coincidence_map_files[0])->default_value(string(CoincidenceMapWMagFile0)),    "Coincidence map file w/ mag 0 (string)\n");
//    ("coincidence-map-file-w-mag1",  bpo::value<string>(&coincidence_map_files[1])->default_value(string(CoincidenceMapWMagFile1)),    "Coincidence map file w/ mag 1 (string)\n");
//    ("coincidence-map-file-w-mag2",  bpo::value<string>(&coincidence_map_files[2])->default_value(string(CoincidenceMapWMagFile2)),    "Coincidence map file w/ mag 2 (string)\n");
//    ("coincidence-map-file-w-mag3",  bpo::value<string>(&coincidence_map_files[3])->default_value(string(CoincidenceMapWMagFile3)),    "Coincidence map file w/ mag 3 (string)\n");
//    ("coincidence-map-file-w-mag4",  bpo::value<string>(&coincidence_map_files[4])->default_value(string(CoincidenceMapWMagFile4)),    "Coincidence map file w/ mag 4 (string)\n");
//    ("coincidence-map-file-w-mag5",  bpo::value<string>(&coincidence_map_files[5])->default_value(string(CoincidenceMapWMagFile5)),    "Coincidence map file w/ mag 5 (string)\n");
//    ("coincidence-map-file-wo-mag0", bpo::value<string>(&coincidence_map_files[6])->default_value(string(CoincidenceMapWoMagFile0)),   "Coincidence map file w/o mag 0 (string)\n");
//    ("coincidence-map-file-wo-mag1", bpo::value<string>(&coincidence_map_files[7])->default_value(string(CoincidenceMapWoMagFile1)),   "Coincidence map file w/o mag 1 (string)\n");
//    ("coincidence-map-file-wo-mag2", bpo::value<string>(&coincidence_map_files[8])->default_value(string(CoincidenceMapWoMagFile2)),   "Coincidence map file w/o mag 2 (string)\n");
//    ("coincidence-map-file-wo-mag3", bpo::value<string>(&coincidence_map_files[9])->default_value(string(CoincidenceMapWoMagFile3)),   "Coincidence map file w/o mag 3 (string)\n");
//    ("coincidence-map-file-wo-mag4", bpo::value<string>(&coincidence_map_files[10])->default_value(string(CoincidenceMapWoMagFile4)),  "Coincidence map file w/o mag 4 (string)\n");
//    ("coincidence-map-file-wo-mag5", bpo::value<string>(&coincidence_map_files[11])->default_value(string(CoincidenceMapWoMagFile5)),  "Coincidence map file w/o mag 5 (string)\n");
//    ("trigger-gtr-channel-map",      bpo::value<string>(&trigger_channel_map_files[0])->default_value(string(TriggerChannelMapFile0)), "Trigger GTR channel map file (string)\n");
//    ("trigger-hbd-channel-map",      bpo::value<string>(&trigger_channel_map_files[1])->default_value(string(TriggerChannelMapFile1)), "Trigger HBD channel map file (string)\n");
//    ("trigger-lg-channel-map",       bpo::value<string>(&trigger_channel_map_files[2])->default_value(string(TriggerChannelMapFile2)), "Trigger LG channel map file (string)\n");
//
//  auto file_check = [&vm, &in_file_name, &out_file_name]() {
//    if (in_file_name.empty()) {
//      throw invalid_argument("Invalid input file name: "s + in_file_name);
//    }
//    if (out_file_name.empty()) {
//      throw invalid_argument("Invalid output file name: "s + out_file_name);
//    }
//  };

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  auto trigger_param = new E16ANA_TriggerCalibParam();
  trigger_param->ReadConstantData(calib.CurrentRunID());
  E16ANA_GTRcalibPedestal gtrped;
  gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_GTRLorentzAngleCalibParamManager gtr_lorentz_angle_calib_param_manager;
  gtr_lorentz_angle_calib_param_manager.ReadConstantData(calib.CurrentRunID());
  auto gtr_lorentz_angle_calib_params = gtr_lorentz_angle_calib_param_manager.GTRLorentzAngleCalibParams();

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
    
    auto event_type = dst0->EventType();
//    dst1->SetEventType(event_type);
      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
//      auto event1 = dynamic_cast<E16DST_DST1PhysicsEvent*>(dst1->Event());
//      auto event1 = new E16DST_DST1PhysicsEvent();
      auto& ssd_hits0         = event0->SSD();
      auto& gtr_hits0         = event0->GTR();
      auto& hbd_hits0         = event0->HBD();
      auto& lg_hits0          = event0->LG();
      auto& trigger_gtr_hits0 = event0->TriggerGTR();
      auto& trigger_hbd_hits0 = event0->TriggerHBD();
      auto& trigger_lg_hits0  = event0->TriggerLG();
      E16DST_DST0Detector<E16DST_DST1GTRHit> gtr_hits;
      E16DST_DST0Detector<E16DST_DST1GTRCluster> gtr_clusters;
//      auto& gtr_hits = record->GTR().Hits();
//      auto& gtr_clusters = record->GTR().Clusters();
//      E16DST_DST1SSDFactory(ssd_hits0, &event1->SSDHits(), &event1->SSDClusters());
	  E16DST_DST1GTRFactory(gtr_hits0, &record->GTR(), gtrped, gtr_lorentz_angle_calib_params);
	record->GTR().UpdatePtrs();
//      std::cout << "GTR factory returns :: " << E16DST_DST1GTRHitAndClusterFactory(gtr_hits0, &gtr_hits, &gtr_clusters, gtrped) << std::endl;
//      std::cout << "n_event = " << n_event << ", cluster size " << gtr_clusters.NumberOfHits() << std::endl;
//      E16DST_DST1GTRFactoryDST1Detector(gtr_hits0, &event1->GTR());
//      E16DST_DST1HBDFactory(hbd_hits0, &event1->HBDHits(), &event1->HBDClusters());
//      E16DST_DST1LGHitAndClusterFactory(lg_hits0,   event1->LGHits(),  event1->LGClusters());
//      E16DST_DST1LGFactory(lg_hits0,   &event1->LGHits(),  &event1->LGClusters());
//      E16DST_DST1LGFactoryDST1Detector(lg_hits0, &event1->LG());
//      E16DST_DST1TriggerFactory(*trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &event1->Trigger());
//      event1->GTR().SetValidFlag(1);
//      event1->LG().SetValidFlag(1);
//      event1->Trigger().SetValidFlag(1);

//   gtrhist->Fill(&gtr_hits, &gtr_clusters);
   gtrhist->Fill(&record->GTR());


// GTR
//    cout << "Number of event: " << n_event << endl << endl;
//    auto n_gtr_hits = gtr_hits.NumberOfHits();
//    cout << "Number of GTR hits: " << n_gtr_hits << endl;
//    for(int n_hit = 0; n_hit < n_gtr_hits; ++n_hit) {
//        auto hit = gtr_hits.Hit(n_hit);
////        hit.Print();
//    }

//    int n_gtr_hits = gtr_hits.NumberOfHits();
//    for(int i = 0; i < n_gtr_hits ; i++){
//        auto hit = gtr_hits.Hit(i);
//        std::cout << "hit ph" << hit.PeakHeight() << ", timing =  " << hit.Timing() << "tot = "<< hit.Tot() << std::endl;
//    }

//    auto n_gtr_clusters = gtr_clusters.NumberOfHits();
  //  cout << "Number of GTR clusters: " << n_gtr_clusters << endl;
    //for (int n_cluster = 0; n_cluster < n_gtr_clusters; ++n_cluster) {
//       std::cout << "n_cluster = " << n_cluster << std::endl;
//       auto cluster = gtr_clusters.Hit(n_cluster);
//       std::cout << "mid = " << cluster.ModuleId() << "layer id = " << cluster.LayerId() <<std::endl;
//       cluster.Print();
//    }
//    dst1->WriteAnEvent();
//    }
   ++n_event;
    ++n_physics_event;
  }
  TCanvas *c1 = new TCanvas("c1", "c1", 1024, 768);
  TString pdf_name;
  pdf_name.Form("/ccj/w/data06a/E16/user/nakasuga/output/gtr/dst1check/pdf/gtrtest%06d.pdf",run_id);
  //  pdf_name.Form("gtrtest.pdf");
  c1->SaveAs(pdf_name + "[", "pdf");

  TCanvas *c_cl_ncluster_x[10]; 
  //= new TCanvas("cl charge ", 100,0,100);
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_ncluster_x[m-102] = new TCanvas(Form("ccn%d", m-102) , Form("ccn%d", m-102), 1024, 768);
    c_cl_ncluster_x[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_ncluster_x[m-102]->cd(l+1);
        gtrhist->h_cl_ncluster_x[m-100][l]->Draw();
    }
    c_cl_ncluster_x[m-102]->SaveAs(pdf_name, "pdf");
  }

   TCanvas *c_cl_ncluster_y[10]; 
  //= new TCanvas("cl charge ", 100,0,100);
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_ncluster_y[m-102] = new TCanvas(Form("ccny%d", m-102) , Form("ccny%d", m-102), 1024, 768);
    c_cl_ncluster_y[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_ncluster_y[m-102]->cd(l+1);
        gtrhist->h_cl_ncluster_y[m-100][l]->Draw();
    }
    c_cl_ncluster_y[m-102]->SaveAs(pdf_name, "pdf");
  }
 
   TCanvas *c_cl_ncluster_yb[10]; 
  //= new TCanvas("cl charge ", 100,0,100);
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_ncluster_yb[m-102] = new TCanvas(Form("ccnyb%d", m-102) , Form("ccnyb%d", m-102), 1024, 768);
    c_cl_ncluster_yb[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_ncluster_yb[m-102]->cd(l+1);
        gtrhist->h_cl_ncluster_yb[m-100][l]->Draw();
    }
    c_cl_ncluster_yb[m-102]->SaveAs(pdf_name, "pdf");
  }
 
  TCanvas *c_cl_numhits_x[10]; 
  //= new TCanvas("cl charge ", 100,0,100);
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_numhits_x[m-102] = new TCanvas(Form("ccn%d", m-102) , Form("ccn%d", m-102), 1024, 768);
    c_cl_numhits_x[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_numhits_x[m-102]->cd(l+1);
        gtrhist->h_cl_numhits_x[m-100][l]->Draw();
    }
    c_cl_numhits_x[m-102]->SaveAs(pdf_name, "pdf");
  }

   TCanvas *c_cl_numhits_y[10]; 
  //= new TCanvas("cl charge ", 100,0,100);
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_numhits_y[m-102] = new TCanvas(Form("ccny%d", m-102) , Form("ccny%d", m-102), 1024, 768);
    c_cl_numhits_y[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_numhits_y[m-102]->cd(l+1);
        gtrhist->h_cl_numhits_y[m-100][l]->Draw();
    }
    c_cl_numhits_y[m-102]->SaveAs(pdf_name, "pdf");
  }
 
   TCanvas *c_cl_numhits_yb[10]; 
  //= new TCanvas("cl charge ", 100,0,100);
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_numhits_yb[m-102] = new TCanvas(Form("ccnyb%d", m-102) , Form("ccnyb%d", m-102), 1024, 768);
    c_cl_numhits_yb[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_numhits_yb[m-102]->cd(l+1);
        gtrhist->h_cl_numhits_yb[m-100][l]->Draw();
    }
    c_cl_numhits_yb[m-102]->SaveAs(pdf_name, "pdf");
  }
 


  TCanvas *c_cl_charge_x[10]; 
  //= new TCanvas("cl charge ", 100,0,100);
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_charge_x[m-102] = new TCanvas(Form("ccx%d", m-102) , Form("ccx%d", m-102), 1024, 768);
    c_cl_charge_x[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_charge_x[m-102]->cd(l+1);
        gtrhist->h_cl_charge_x[m-100][l]->Draw();
    }
    c_cl_charge_x[m-102]->SaveAs(pdf_name, "pdf");
  }
 
  TCanvas *c_cl_charge_y[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_charge_y[m-102] = new TCanvas(Form("ccy%d", m-102), Form("ccy%d", m-102), 1024, 768);
    c_cl_charge_y[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_charge_y[m-102]->cd(l+1);
        gtrhist->h_cl_charge_y[m-100][l]->Draw();
    }
    c_cl_charge_y[m-102]->SaveAs(pdf_name, "pdf");
  }
  
  TCanvas *c_cl_charge_yb[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_charge_yb[m-102] = new TCanvas(Form("ccyb%d", m-102), Form("ccyb%d", m-102), 1024, 768);
    c_cl_charge_yb[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_charge_yb[m-102]->cd(l+1);
        gtrhist->h_cl_charge_yb[m-100][l]->Draw();
    }
    c_cl_charge_yb[m-102]->SaveAs(pdf_name, "pdf");
  }
  
  TCanvas *c_cl_timing_x[10]; 
  //= new TCanvas("cl timing ", 100,0,100);
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_timing_x[m-102] = new TCanvas(Form("ctx%d", m-102) , Form("ctx%d", m-102), 1024, 768);
    c_cl_timing_x[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_timing_x[m-102]->cd(l+1);
        gtrhist->h_cl_timing_x[m-100][l]->Draw();
    }
    c_cl_timing_x[m-102]->SaveAs(pdf_name, "pdf");
  }
 
  TCanvas *c_cl_timing_y[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_timing_y[m-102] = new TCanvas(Form("cty%d", m-102), Form("cty%d", m-102), 1024, 768);
    c_cl_timing_y[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_timing_y[m-102]->cd(l+1);
        gtrhist->h_cl_timing_y[m-100][l]->Draw();
    }
    c_cl_timing_y[m-102]->SaveAs(pdf_name, "pdf");
  }
  
  TCanvas *c_cl_timing_yb[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_timing_yb[m-102] = new TCanvas(Form("ctyb%d", m-102), Form("ctyb%d", m-102), 1024, 768);
    c_cl_timing_yb[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_timing_yb[m-102]->cd(l+1);
        gtrhist->h_cl_timing_yb[m-100][l]->Draw();
    }
    c_cl_timing_yb[m-102]->SaveAs(pdf_name, "pdf");
  }
  
  TCanvas *c_cl_local_x[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_local_x[m-102] = new TCanvas(Form("clx%d", m-102), Form("clx%d", m-102), 1024, 768);
    c_cl_local_x[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_local_x[m-102]->cd(l+1);
        gtrhist->h_cl_local_x[m-100][l]->Draw();
    }
    c_cl_local_x[m-102]->SaveAs(pdf_name, "pdf");
  }

  TCanvas *c_cl_local_y[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_local_y[m-102] = new TCanvas(Form("cly%d", m-102), Form("cly%d", m-102), 1024, 768);
    c_cl_local_y[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_local_y[m-102]->cd(l+1);
        gtrhist->h_cl_local_y[m-100][l]->Draw();
    }
    c_cl_local_y[m-102]->SaveAs(pdf_name, "pdf");
  }
   TCanvas *c_cl_local_yb[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_local_yb[m-102] = new TCanvas(Form("clyb%d",m-102), Form("clyb%d", m-102), 1024, 768);
    c_cl_local_yb[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_local_yb[m-102]->cd(l+1);
        gtrhist->h_cl_local_yb[m-100][l]->Draw();
    }
    c_cl_local_yb[m-102]->SaveAs(pdf_name, "pdf");
  }
 
  TCanvas *c_cl_max_peak_x[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_max_peak_x[m-102] = new TCanvas(Form("clmpx%d", m-102), Form("clmpx%d", m-102), 1024, 768);
    c_cl_max_peak_x[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_max_peak_x[m-102]->cd(l+1);
        gtrhist->h_cl_max_peak_x[m-100][l]->Draw();
    }
    c_cl_max_peak_x[m-102]->SaveAs(pdf_name, "pdf");
  }
  
  TCanvas *c_cl_max_peak_y[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_max_peak_y[m-102] = new TCanvas(Form("clmpy%d",m-102), Form("clmpy%d", m-102), 1024, 768);
    c_cl_max_peak_y[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_max_peak_y[m-102]->cd(l+1);
        gtrhist->h_cl_max_peak_y[m-100][l]->Draw();
    }
    c_cl_max_peak_y[m-102]->SaveAs(pdf_name, "pdf");
  }

  TCanvas *c_cl_max_peak_yb[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_max_peak_yb[m-102] = new TCanvas(Form("clmpyb%d", m-102), Form("clmpyb%d", m-102), 1024, 768);
    c_cl_max_peak_yb[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_max_peak_yb[m-102]->cd(l+1);
        gtrhist->h_cl_max_peak_yb[m-100][l]->Draw();
    }
    c_cl_max_peak_yb[m-102]->SaveAs(pdf_name, "pdf");
  }

  TCanvas *c_cl_max_peak_ch_x[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_max_peak_ch_x[m-102] = new TCanvas(Form("clmpchx%d", m-102), Form("clmpchx%d", m-102), 1024, 768);
    c_cl_max_peak_ch_x[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_max_peak_ch_x[m-102]->cd(l+1);
        gtrhist->h_cl_max_peak_ch_x[m-100][l]->Draw();
    }
    c_cl_max_peak_x[m-102]->SaveAs(pdf_name, "pdf");
  }
 
  TCanvas *c_cl_tdcpos_x[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_tdcpos_x[m-102] = new TCanvas(Form("cltdcposx%d", m-102), Form("cltdcposx%d", m-102), 1024, 768);
    c_cl_tdcpos_x[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_tdcpos_x[m-102]->cd(l+1);
        gtrhist->h_cl_tdcpos_x[m-100][l]->Draw();
    }
    c_cl_tdcpos_x[m-102]->SaveAs(pdf_name, "pdf");
  }
 
  TCanvas *c_cl_tdcpos_y[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_tdcpos_y[m-102] = new TCanvas(Form("cltdcposy%d", m-102), Form("cltdcposy%d", m-102), 1024, 768);
    c_cl_tdcpos_y[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_tdcpos_x[m-102]->cd(l+1);
        gtrhist->h_cl_tdcpos_y[m-100][l]->Draw();
    }
    c_cl_tdcpos_y[m-102]->SaveAs(pdf_name, "pdf");
  }
   TCanvas *c_cl_tdcpos_yb[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_tdcpos_yb[m-102] = new TCanvas(Form("cltdcposyb%d", m-102), Form("cltdcposyb%d", m-102), 1024, 768);
    c_cl_tdcpos_yb[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_tdcpos_yb[m-102]->cd(l+1);
        gtrhist->h_cl_tdcpos_yb[m-100][l]->Draw();
    }
    c_cl_tdcpos_yb[m-102]->SaveAs(pdf_name, "pdf");
  }

  TCanvas *c_cl_tan_x[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_tan_x[m-102] = new TCanvas(Form("cltanx%d", m-102), Form("cltanx%d", m-102), 1024, 768);
    c_cl_tan_x[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_tan_x[m-102]->cd(l+1);
        gtrhist->h_cl_tan_x[m-100][l]->Draw();
    }
    c_cl_tan_x[m-102]->SaveAs(pdf_name, "pdf");
  }
   TCanvas *c_cl_tan_y[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_tan_y[m-102] = new TCanvas(Form("cltany%d", m-102), Form("cltany%d", m-102), 1024, 768);
    c_cl_tan_y[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_tan_y[m-102]->cd(l+1);
        gtrhist->h_cl_tan_y[m-100][l]->Draw();
    }
    c_cl_tan_y[m-102]->SaveAs(pdf_name, "pdf");
  }
    TCanvas *c_cl_tan_yb[10]; 
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
    c_cl_tan_yb[m-102] = new TCanvas(Form("cltanyb%d", m-102), Form("cltanyb%d", m-102), 1024, 768);
    c_cl_tan_yb[m-102]->Divide(2,2);
    for(int l=0; l < 3; l++){
        c_cl_tan_yb[m-102]->cd(l+1);
        gtrhist->h_cl_tan_yb[m-100][l]->Draw();
    }
    c_cl_tan_yb[m-102]->SaveAs(pdf_name, "pdf");
  }
 

  c1->SaveAs( pdf_name + "]", "pdf");

  fout->Write();
  fout->Close();


//  delete geometry;
  delete dst0;
//  dst1->Close();
  return 0;
}
