#include <iostream>

//#include "E16ANA_CalibDBManager.hh"
#include <E16DST_DST1.hh>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "./bin [input.dst0] [output.dst1] [run number]" << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto run_num       = stoi(argv[3]);

  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
//  auto dst1 = new E16DST_DST1();
  auto dst1 = new E16DST_DST0();
  if (!dst1->Open(out_file_name, E16DST_DST0::WriteMode)) {
    std::cerr << "Cannot open output file: " << out_file_name << std::endl;
    return -1;
   }
//  E16ANA_CalibDBManager& calib = E16ANA_CalibDBManager::Instance();
//  auto calib_file_name = calib.CalibFileName("SSD-pedestal", run_rum);
//  std::cout << calib_file_name << std::endl;
  while (dst0->ReadAnEvent()) {
    auto event_type = dst0->EventType();
    dst1->SetEventType(event_type);
    if (event_type = E16DST_DST0EventType::Physics) {
      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
      auto event1 = dynamic_cast<E16DST_DST1PhysicsEvent*>(dst1->Event());
      event1->Clear();
      auto trigger1 = event1->Trigger();
      if (event0 == nullptr) {
        continue;
      }
      auto ssd_hits0         = event0->SSD();
      auto gtr_hits0         = event0->GTR();
      auto hbd_hits0         = event0->HBD();
      auto lg_hits0          = event0->LG();
      auto trigger_gtr_hits0 = event0->TriggerGTR();
      auto trigger_hbd_hits0 = event0->TriggerHBD();
      auto trigger_lg_hits0  = event0->TriggerLG();
      auto timestamp         = event0->TimeStamp();
//      E16DST_DST1SSDHitAndClusterFactory(event0->SSD(),            event1->SSDHits(),   event1->SSDClusters());
//      E16DST_DST1GTRHitAndClusterFactory(event0->GTR(),
//                                  event1->GTR100XHits(),  event1->GTR100XClusters(), event1->GTR100YHits(),  event1->GTR100YClusters(), event1->GTR100YbHits(), event1->GTR100YbClusters(),
//                                  event1->GTR200XHits(),  event1->GTR200XClusters(), event1->GTR200YHits(),  event1->GTR200YClusters(),
//                                  event1->GTR300XHits(),  event1->GTR300XClusters(), event1->GTR300YHits(),  event1->GTR300YClusters())
//      E16DST_DST1SSDHitAndClusterFactory(event0->HBD(),            event1->HBDHits(),   event1->HBDClusters());
//      E16DST_DST1SSDHitAndClusterFactory(event0->LG(),             event1->LGHits(),    event1->LGClusters());
      E16DST_DST1TriggerHitAndClusterFactory(event0->TriggerGTR(), timestamp, trigger1.GTRHits(), trigger1.GTRClusters());
      E16DST_DST1TriggerHitAndClusterFactory(event0->TriggerHBD(), timestamp, trigger1.HBDHits(), trigger1.HBDClusters());
      E16DST_DST1TriggerHitAndClusterFactory(event0->TriggerLG(),  timestamp,  trigger1.LGHits(),  trigger1.LGClusters());
    
    
    
    
    
    
    } else if (event_type == E16DST_DST0EventType::Scaler) {
      auto event0 = dynamic_cast<E16DST_DST0ScalerEvent*>(dst0->Event());
      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillStart) {
      auto event0 = dynamic_cast<E16DST_DST0SpillStartEvent*>(dst0->Event());
      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillEnd) {
      auto event0 = dynamic_cast<E16DST_DST0SpillEndEvent*>(dst0->Event());
      dst1->WriteAnEvent(event0);
    } else {
      std::cerr << "Invalid Event Type: " << event_type << std::endl;
      return -1;
    }
  }
  delete dst0;
  dst1->Close();
  return 0;
}
