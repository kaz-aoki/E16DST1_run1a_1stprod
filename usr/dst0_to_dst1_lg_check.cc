#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
//#include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"

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
//  bpo::variables_map vm;
//  string in_file_name;
//  string out_file_name;
//  int run_num;


  TFile *fout = new TFile(out_file_name,"recreate");
  TTree *tree = new TTree("tree","tree");

  //TH1F *hph = new TH1F("hph","PeakHeight",1100,-100,1000);
  //TH1F *hpt = new TH1F("hpt","PeakTime",200,0,200);
  //TH1F *htm = new TH1F("htm","Timing",200,0,200);
  //TH1F *hbl = new TH1F("hbl","Baseline",200,-100,100);
  //TH1F *hbr = new TH1F("hbr","BaselineRms",200,-100,100);
  //TH1F *hit = new TH1F("hit","Integral",1100,-100,1000);
  //TH1F *ht0 = new TH1F("ht0","CalibTiming",1000,0,200);
  //TH1F *hed = new TH1F("hed","EnergyDeposit",1100,-1,10);
  TH1F *hph[7][56];
  TH1F *hpt[7][56];
  TH1F *htm[7][56];
  TH1F *hbl[7][56];
  TH1F *hbr[7][56];
  TH1F *hit[7][56];
  TH1F *ht0[7][56];
  TH1F *hed[7][56];
  TH1F *hnp[7][56];
  TH1F *hff[7][56];
  TH1F *hfp[7][56];
  TH1F *hfx[7][56];
  TH1F *hft[7][56];
  TH1F *hfw[7][56];
  TH1F *hfc[7][56];
  for(int i=0;i<7;i++){
    for(int j=0;j<56;j++){
      hph[i][j] = new TH1F(Form("hph%d%d",i,j),Form("PeakHeight%d%d",i,j),1100,-100,1000);
      hpt[i][j] = new TH1F(Form("hpt%d%d",i,j),Form("PeakTime%d%d",i,j),200,0,200);
      htm[i][j] = new TH1F(Form("htm%d%d",i,j),Form("Timing%d%d",i,j),200,0,200);
      hbl[i][j] = new TH1F(Form("hbl%d%d",i,j),Form("Baseline%d%d",i,j),200,-100,100);
      hbr[i][j] = new TH1F(Form("hbr%d%d",i,j),Form("BaselineRms%d%d",i,j),200,-100,100);
      hit[i][j] = new TH1F(Form("hit%d%d",i,j),Form("Integral%d%d",i,j),1100,-100,1000);
      ht0[i][j] = new TH1F(Form("ht0%d%d",i,j),Form("CalibTiming%d%d",i,j),1000,0,200);
      hed[i][j] = new TH1F(Form("hed%d%d",i,j),Form("EnergyDeposit%d%d",i,j),1100,-1,10);
      hnp[i][j] = new TH1F(Form("hnp%d%d",i,j),Form("Npeaks%d%d",i,j),5,0,5);
      hff[i][j] = new TH1F(Form("hff%d%d",i,j),Form("FitFlag%d%d",i,j),5,0,5);
      hfp[i][j] = new TH1F(Form("hfp%d%d",i,j),Form("FitPeak%d%d",i,j),1100,-100,1000);
      hfx[i][j] = new TH1F(Form("hfx%d%d",i,j),Form("FitPeakTime%d%d",i,j),200,0,200);
      hft[i][j] = new TH1F(Form("hft%d%d",i,j),Form("FitTiming%d%d",i,j),200,0,200);
      hfw[i][j] = new TH1F(Form("hfw%d%d",i,j),Form("FitWidth%d%d",i,j),200,0,2);
      hfc[i][j] = new TH1F(Form("hfc%d%d",i,j),Form("FitChi2%d%d",i,j),200,0,50);
    }
  }
  uint16_t module, block;
  float peakheight, timing, baseline, baselinerms, integral, calibtiming, energydeposit, fitpeak, fitpeaktime, fittiming, fitwidth, fitchi2;
  int event, peaktime, npeak, npeaks, fitflag;
  double gpos[3];
  double lpos[3];
  tree->Branch("Event",&event,"Event/I");
  tree->Branch("Module",&module,"Module/s");
  tree->Branch("Block",&block,"Block/s");
  tree->Branch("PeakHeight",&peakheight,"PeakHeight/F");
  tree->Branch("PeakTime",&peaktime,"PeakTime/I");
  tree->Branch("Timing",&timing,"timing/F");
  tree->Branch("Baseline",&baseline,"Baseline/F");
  tree->Branch("BaselineRms",&baselinerms,"BaselineRms/F");
  tree->Branch("Integral",&integral,"Integral/F");
  tree->Branch("CalibTiming",&calibtiming,"CalibTiming/F");
  tree->Branch("EnergyDeposit",&energydeposit,"EnergyDeposit/F");
  tree->Branch("Npeak",&npeak,"Npeak/I");
  tree->Branch("Npeaks",&npeaks,"Npeaks/I");
  tree->Branch("FitFlag",&fitflag,"FitFlag/I");
  tree->Branch("FitPeak",&fitpeak,"FitPeak/F");
  tree->Branch("FitPeakTime",&fitpeaktime,"FitPeakTime/F");
  tree->Branch("FitTiming",&fittiming,"FitTiming/F");
  tree->Branch("FitWidth",&fitwidth,"FitWidth/F");
  tree->Branch("FitChi2",&fitchi2,"FitChi2/F");
  //tree->Branch("Gpos",gpos,"Gpos[3]/D");
  //tree->Branch("Lpos",lpos,"Lpos[3]/D");

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
  E16ANA_LGBasic lgbasic;
  lgbasic.SetCalibMap();//it is necessary to use energy deposit and calibrated timing.

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  
  auto record = new E16DST_DST1PhysicsRecord();

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
      //      auto& ssd_hits0         = event0->SSD();
      //      auto& gtr_hits0         = event0->GTR();
      //      auto& hbd_hits0         = event0->HBD();
      auto& lg_hits0          = event0->LG();
      //      auto& trigger_gtr_hits0 = event0->TriggerGTR();
      //      auto& trigger_hbd_hits0 = event0->TriggerHBD();
      //      auto& trigger_lg_hits0  = event0->TriggerLG();
//      E16DST_DST0Detector<E16DST_DST1LGHit> lg_hits1;
//      E16DST_DST0Detector<E16DST_DST1LGCluster> lg_clusters1;
//      auto& lg_hits1 = record->LG().Hits();
//      auto& lg_clusters1 = record->LG().Clusters();
//      E16DST_DST1SSDFactory(ssd_hits0, &event1->SSDHits(), &event1->SSDClusters());
//      std::cout << "GTR factory returns :: " << E16DST_DST1GTRHitAndClusterFactory(gtr_hits0, &event1->GTRHits(), &event1->GTRClusters(), gtrped) << std::endl;
//      E16DST_DST1GTRFactoryDST1Detector(gtr_hits0, &event1->GTR());
//      E16DST_DST1HBDFactory(hbd_hits0, &event1->HBDHits(), &event1->HBDClusters());
//      E16DST_DST1LGHitAndClusterFactory(lg_hits0,   lg_hits1,  lg_clusters1);
      E16DST_DST1LGFactory(lg_hits0, &record->LG(), 0);
//      E16DST_DST1LGFactoryDST1Detector(lg_hits0, &event1->LG());
//      E16DST_DST1TriggerFactory(*trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &event1->Trigger());
//      event1->GTR().SetValidFlag(1);
//      event1->LG().SetValidFlag(1);
      //      event1->Trigger().SetValidFlag(1);


//// Check begin
//      auto event_id = event0->EventID();
//      cout << "Event ID: " << event_id << endl;
//// SSD
//
//// GTR
//      cout << "Number of event: " << n_event << endl << endl;
//      auto n_gtr_hits = event1->GTRHits().NumberOfHits();
//      cout << "Number of GTR hits: " << n_gtr_hits << endl;
//      for (int n_hit = 0; n_hit < n_gtr_hits; ++n_hit) {
//        auto hit = event1->GTRHits().Hit(n_hit);
//        hit.Print();
//      }
//      auto n_gtr_clusters = event1->GTRClusters().NumberOfHits();
//      cout << endl << endl;
//      cout << "Number of GTR clusters: " << n_gtr_clusters << endl;
//      for (int n_cluster = 0; n_cluster < n_gtr_clusters; ++n_cluster) {
//        auto cluster = event1->GTRClusters().Hit(n_cluster);
//        cluster.Print();
//      }
//      
//// HBD
//
//// LG
      auto& lg_hits1 = record->LG().Hits();
      event = event0->EventID();
      int n_lghits = lg_hits1.size();
      //std::cout<<"Event: "<<event<<"  Nhits: "<<n_lghits<<std::endl;
      if (lg_hits1.size() != 0) {
	for(int i=0;i<n_lghits;i++){//hit loop
	  auto& lghit = lg_hits1[i];
	  //lghit.Print();                                                                                 
	  //std::cout<<"LPos:("<<lghit.LocalPos(*geometry).X()<< ","<<lghit.LocalPos(*geometry).Y()<<","<<lghit.LocalPos(*geometry).Z()<<")"<<std::endl;  
	  //std::cout<<"GPos:("<<lghit.GlobalPos(*geometry).X()<< ","<<lghit.GlobalPos(*geometry).Y()<<","<<lghit.GlobalPos(*geometry).Z()<<")"<<std::endl;     
	  //std::cout<<"ph       : "<<lghit.PeakHeight()<<std::endl;
	  //std::cout<<"T0_func  : "<<lghit.GetCalibTiming(lgbasic)<<std::endl;
	  //std::cout<<"Gain_func: "<<lghit.GetEnergyDeposit(lgbasic)<<std::endl;
	  //std::cout<<"Npeaks: "<<lghit.Npeaks()<<"  PulseHeight: "<<lghit.PeakHeight()<<std::endl;

	  module = lghit.ModuleId();
	  block = lghit.ChannelId();
	  peakheight = lghit.PeakHeight();
	  peaktime = lghit.PeakTime();
	  timing = lghit.Timing();
	  baseline = lghit.Baseline();
	  baselinerms = lghit.BaselineRms();
	  integral = lghit.Integral();
	  npeak = lghit.Npeak();
	  npeaks = lghit.Npeaks();
	  fitflag = lghit.FitFlag();
	  fitpeak = lghit.FitPeak();
	  fitpeaktime = lghit.FitPeakTime();
	  fittiming = lghit.FitTiming();
	  fitwidth = lghit.FitWidth();
	  fitchi2 = lghit.FitChi2();
	  calibtiming = lghit.GetCalibTiming(lgbasic);
	  energydeposit = lghit.GetEnergyDeposit(lgbasic);
	  //gpos[0] = lghit.GlobalPos(*geometry).X();
	  //gpos[1] = lghit.GlobalPos(*geometry).Y();
	  //gpos[2] = lghit.GlobalPos(*geometry).Z();
	  //lpos[0] = lghit.LocalPos(*geometry).X();
	  //lpos[1] = lghit.LocalPos(*geometry).Y();
	  //lpos[2] = lghit.LocalPos(*geometry).Z();
	  tree->Fill();
	  if(npeak==0){
	  hph[module-102][block]->Fill(lghit.PeakHeight());
	  hpt[module-102][block]->Fill(lghit.PeakTime());
	  htm[module-102][block]->Fill(lghit.Timing());
	  hbl[module-102][block]->Fill(lghit.Baseline());
	  hbr[module-102][block]->Fill(lghit.BaselineRms());
	  hit[module-102][block]->Fill(lghit.Integral());
	  ht0[module-102][block]->Fill(lghit.GetCalibTiming(lgbasic));
	  hed[module-102][block]->Fill(lghit.GetEnergyDeposit(lgbasic));
	  hnp[module-102][block]->Fill(lghit.Npeaks());
	  hff[module-102][block]->Fill(lghit.FitFlag());
	  }
	  hfp[module-102][block]->Fill(lghit.FitPeak());
	  hfx[module-102][block]->Fill(lghit.FitPeakTime());
	  hft[module-102][block]->Fill(lghit.FitTiming());
	  hfw[module-102][block]->Fill(lghit.FitWidth());
	  hfc[module-102][block]->Fill(lghit.FitChi2());
	}//hit loop
      }

//// trigger
//      event1->Trigger().Print(*geometry);
//
//// other
////      event1->GTR().Print();
////
////      if (event1->LG().NumHits() != 0) {
////        auto lghit = event1->LG().Hit(0);                                                          
////        lghit.Print();                                                                                 
////        std::cout<<"LPos:("<<lghit.LocalPos(*geometry).X()<< ","<<lghit.LocalPos(*geometry).Y()<<","<<lghit.LocalPos(*geometry).Z()<<")"<<std::endl;  
////        std::cout<<"GPos:("<<lghit.GlobalPos(*geometry).X()<< ","<<lghit.GlobalPos(*geometry).Y()<<","<<lghit.GlobalPos(*geometry).Z()<<")"<<std::endl;     
////      }
//
//      cout << endl << endl;
//// Check end

//      dst1->WriteAnEvent();
//      delete event0;
//      delete event1;
      //delete record;

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

  fout->Write();
  fout->Close();

  delete geometry;
  delete dst0;
//  dst1->Close();
  return 0;
}
