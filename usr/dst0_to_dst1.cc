#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
//#include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_SSDcalib.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DefaultFilePath.hh"

//----arimizu include----
#include <TH1I.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TStyle.h>
//----end arimizu include----

using namespace std;
//namespace  bpo = boost::program_options;


//----arimizu----
int c_mid(int mid){
  int m=-1;
  if(mid==102||mid==103||mid==104){
    m=mid-102;
  }
  if(mid==106||mid==107||mid==108){
    m=mid-106+3;
  }
  return m;
}
//----arimizu----


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
  //  gtrped.ReadCalibData( calib.CurrentRunID() );

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));



  //----arimizu plot----
  const int n_module = 6;
  const int c_canv[6]={2,4,6,1,3,5};
  const int c_module[9]={-1,2,1,0,-1,3,4,5,-1};

  TString output_pdf_name = "ssdfit.pdf";
  TString output_pdf_name0 = "ssdfit_noPedestal.pdf";

  TH1I *h_HitID[n_module];
  for(int i=0; i<n_module; i++){
    h_HitID[i] = new TH1I(Form("hitID[%d]",i),"h",768,0,768);
  }
  TH1D *h_Timing;
  h_Timing = new TH1D("timing","h",400,-100,300);
  TH1D *h_HitTime;
  h_HitTime = new TH1D("hit time","h",150,-50,100);
  TH1D *h_PeakTime;
  h_PeakTime = new TH1D("peak time","h",400,-100,300);
  TH1D *h_PeakHeight;
  h_PeakHeight = new TH1D("peak height","h",400,-100,300);
  TH1D *h0_HitTime;
  h0_HitTime = new TH1D("hit time","h",150,-50,100);
  TH1D *h0_PeakTime;
  h0_PeakTime = new TH1D("peak time","h",400,-100,300);
  TH1D *h0_PeakHeight;
  h0_PeakHeight = new TH1D("peak height","h",400,-100,300);

  TH1D *c_HitID[n_module];
  for(int i=0; i<n_module; i++){
    c_HitID[i] = new TH1D(Form("c- hitID[%d]",i),"h",60,0,60);
  }
  TH1D *c_Timing;
  c_Timing = new TH1D("c- Timing","h",400,-100,300);
  TH1D *c_PeakSum;
  c_PeakSum = new TH1D("c- PeakSum","h",400,-100,300);
  TH1D *c_TDC;
  c_TDC = new TH1D("c- TDC","h",400,-100,300);
  TH1D *c_TanTheta;
  c_TanTheta = new TH1D("c- TanTheta","h",200,-100,100);
  TH1D *c_ClusterSize;
  c_ClusterSize = new TH1D("c- ClusterSize","h",400,-100,300);
  //----end arimizu plot----



  
  auto dst0 = new E16DST_DST0();


  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
  //  E16ANA_GTRPedestal *gtr_pedestal = new E16ANA_GTRPedestal();
  //  gtr_pedestal->Read(argv[5]);
  //  auto dst1 = new E16DST_DST1();
  //  auto dst1 = new E16DST_DST0();
  //  if (!dst1->Open(out_file_name, E16DST_DST0::WriteMode)) {
  //    std::cerr << "Cannot open output file: " << out_file_name << std::endl;
  //    return -1;
  //   }

//  TFile* froot = new TFile(out_file_name,"recreate");
//  TH1F* hlgph = new TH1F("hlgph","LGPeak",10000,0,1000);
//  TH1I* hlgpt = new TH1I("hlgpt","LGPeakTime",20000,-10000,10000);
//  TH1F* hlgtm = new TH1F("hlgtm","LGTiming",20000,-10000,10000);
//  TH1F* hlgbs = new TH1F("hlgbs","LGBaseline",20000,-10000,10000);
//  TH1F* hlgbr = new TH1F("hlgbr","LGBaselineRms",20000,-10000,10000);
//  TH1F* hlgit = new TH1F("hlgit","LGIntegral",20000,-10000,10000);

  int n_event = 0;
  int n_physics_event = 0;
  while (dst0->ReadAnEvent()) {
    if (max_event != -1 && n_physics_event >= max_event) {
      break;
    }
    if (n_event % 1000 == 0) {
      cout << "Number of event: " << n_event << endl;
    }
    auto event_type = dst0->EventType();
    //    dst1->SetEventType(event_type);
    if (event_type == E16DST_DST0EventType::Physics) {
      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
//      auto event1 = dynamic_cast<E16DST_DST1PhysicsEvent*>(dst1->Event());
//      auto event1 = new E16DST_DST1PhysicsEvent();

      auto ssd_hits0         = event0->SSD();
      auto gtr_hits0         = event0->GTR();
      auto hbd_hits0         = event0->HBD();
      auto lg_hits0          = event0->LG();
      auto trigger_gtr_hits0 = event0->TriggerGTR();
      auto trigger_hbd_hits0 = event0->TriggerHBD();
      auto trigger_lg_hits0  = event0->TriggerLG();
////      }
//
//      cout << endl << endl;
//// Check end


      //      dst1->WriteAnEvent();
    } else if (event_type == E16DST_DST0EventType::Scaler) {
      auto event0 = dynamic_cast<E16DST_DST0ScalerEvent*>(dst0->Event());
      //      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillStart) {
      auto event0 = dynamic_cast<E16DST_DST0SpillStartEvent*>(dst0->Event());
      //      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillEnd) {
      auto event0 = dynamic_cast<E16DST_DST0SpillEndEvent*>(dst0->Event());
      //      dst1->WriteAnEvent(event0);
    } else {
      std::cerr << "Invalid Event Type: " << event_type << std::endl;
      return -1;
    }
    ++n_event;
    ++n_physics_event;
  }

  //  froot->Write();
  //  froot->Close();


  delete geometry;
  delete dst0;
  //  dst1->Close();
  return 0;
}
