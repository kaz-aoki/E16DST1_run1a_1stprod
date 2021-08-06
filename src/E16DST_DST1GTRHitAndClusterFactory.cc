//#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1.hh"

int E16DST_DST1TriggerHitAndClusterFactory(E16DST_DST0Detector<E16DST_DST0TriggerHit>& hits0, E16DST_DST1Detector<E16DST_DST1TriggerHit>& hits1, E16DST_DST1Detector<E16DST_DST1TriggerCluster>& clusters1) {
//  E16ANA_CalibDBManager& calib = E16ANA_CalibDBManager::Instance();
//  int run_id = 2255;
//  char* file_name = calib.CalibFileName("SSD-pedestal", run_id);
//  std::cout << file_name << std::endl;
  auto hit1 = new E16DST_DST1TriggerHit();
  auto max_hit = hits0.NumberOfHits();
  hits1.Reserve(max_hit);
  for (int n_hit = 0; n_hit < hits0.NumberOfHits(); ++n_hit) {
    hit1->SetInvalid();
    auto hit0 = hits0.Hit(n_hit);
    hit1->SetIds(hit0.ModuleID(), hit0.ChannelID());
//    hit1->SetTiming();
    hits1.PushBack(*hit1);
  }
  return hits1.GetEventSize();
}
