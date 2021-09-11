#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DefaultFilePath.hh"

using namespace std;
using namespace E16DST_DST1Constant;

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
//  auto trigger_param = new E16ANA_TriggerCalibParam();
//  trigger_param->ReadConstantData(calib.CurrentRunID());
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
  record_header->SetRunNumber(run_id);
  record_header->SetType(kPhysics);
  record_header->SetVersion(0);
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
      auto record1 = new E16DST_DST1PhysicsRecord();
//      auto& ssd_hits0         = event0->SSD();
      auto& gtr_hits0         = event0->GTR();
//      auto& hbd_hits0         = event0->HBD();
//      auto& lg_hits0          = event0->LG();
//      auto& trigger_gtr_hits0 = event0->TriggerGTR();
//      auto& trigger_hbd_hits0 = event0->TriggerHBD();
//      auto& trigger_lg_hits0  = event0->TriggerLG();
      auto& gtr1 = record1->GTR();
      gtr1.SetDetectorId(1);
      gtr1.SetHitVersion(0);
      gtr1.SetClusterVersion(0);
      E16DST_DST1GTRFactoryDST1Detector(gtrped, gtr_hits0, &gtr1);
      gtr1.SetValidFlag(1);
//      gtr1.Print();
      cout << "number of GTR hits    : " << gtr1.NumHits() << endl;
      cout << "number of GTR clusters: " << gtr1.NumClusters() << endl;
      auto num_clusters = gtr1.NumClusters();
//      auto num_clusters = gtr1.NumHits();
      if (num_clusters != 0) {
        gtr1.Cluster(num_clusters - 1).Print();
//        gtr1.Hit(num_clusters - 1).Print();
      }
      record1->SSD().Clear();
      record1->HBD().Clear();
      record1->LG().Clear();
      record_header->Write(out_file);
      int tmp = record1->Write(out_file);
      cout << "write size: " << tmp << endl;


    } else if (event_type == E16DST_DST0EventType::Scaler) {
      auto event0 = dynamic_cast<E16DST_DST0ScalerEvent*>(dst0->Event());
    } else if (event_type == E16DST_DST0EventType::SpillStart) {
      auto event0 = dynamic_cast<E16DST_DST0SpillStartEvent*>(dst0->Event());
    } else if (event_type == E16DST_DST0EventType::SpillEnd) {
      auto event0 = dynamic_cast<E16DST_DST0SpillEndEvent*>(dst0->Event());
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
  return 0;
}
