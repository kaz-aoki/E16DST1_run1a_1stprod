#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
//#include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DefaultFilePath.hh"

using namespace std;
using namespace E16DST_DST1Constant;
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
  auto trigger_param = new E16ANA_TriggerCalibParam();
  trigger_param->ReadConstantData(calib.CurrentRunID());
  E16ANA_GTRcalibPedestal gtrped;
  gtrped.ReadCalibData( calib.CurrentRunID() );

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  
  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }

  auto out_file = new fstream(out_file_name, ios_base::out | ios_base::binary);

  int n_event = 0;
  int n_physics_event = 0;
  auto record_header = new E16DST_DST1RecordHeader();
  record_header->SetType(kDetector);
  record_header->Write(out_file);
  while (dst0->ReadAnEvent()) {
    if (max_event != -1 && n_physics_event >= max_event) {
      break;
    }
    if (n_event % 1000 == 0) {
      cout << "Number of event: " << n_event << endl;
    }
    auto event_type = dst0->EventType();
    if (event_type == E16DST_DST0EventType::Physics) {
      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
      auto event1 = new E16DST_DST1PhysicsEvent();
      auto ssd_hits0         = event0->SSD();
      auto gtr_hits0         = event0->GTR();
      auto hbd_hits0         = event0->HBD();
      auto lg_hits0          = event0->LG();
      auto trigger_gtr_hits0 = event0->TriggerGTR();
      auto trigger_hbd_hits0 = event0->TriggerHBD();
      auto trigger_lg_hits0  = event0->TriggerLG();
      auto gtr1 = new E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster>;
//      E16DST_DST1SSDFactory(ssd_hits0, &event1->SSDHits(), &event1->SSDClusters());
//      std::cout << "GTR factory returns :: " << E16DST_DST1GTRHitAndClusterFactory(gtr_hits0, &event1->GTRHits(), &event1->GTRClusters(), gtrped) << std::endl;
      E16DST_DST1GTRFactoryDST1Detector(gtrped, gtr_hits0, gtr1);
      gtr1->Write(out_file);



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

  out_file->close();
  delete out_file;

  delete geometry;
  delete dst0;
//  dst1->Close();
  return 0;
}
