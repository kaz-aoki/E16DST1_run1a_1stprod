#include "E16DST_DST1.hh"

//#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DefaultCoincidenceMapPath.hh"
#include "E16DST_TriggerCoincidenceMap.hh"
#include "E16DST_DST0.hh"

namespace E16::DST1::Trigger {

uint16_t GetTriggerTime(uint64_t _timestamp, uint32_t _tdc) {
  int32_t time = (_timestamp * 8) % 0x40000 - _tdc;
  if (time >= 0) {
    return uint16_t{time};
  } else {
    return uint16_t{time + 0x40000};
  }
}

int E16DST_DST1TriggerHitAndClusterFactory(E16DST_DST0Detector<E16DST_DST0TriggerHit>& hits0, uint64_t timestamp, E16DST_DST0Detector<E16DST_DST1TriggerHit>* hits1, E16DST_DST0Detector<E16DST_DST1TriggerCluster>* clusters1) {
//  E16ANA_CalibDBManager& calib = E16ANA_CalibDBManager::Instance();
//  int run_id = 2255;
//  char* file_name = calib.CalibFileName("SSD-pedestal", run_id);
//  std::cout << file_name << std::endl;
  auto hit1 = new E16DST_DST1TriggerHit();
  auto max_hit = hits0.NumberOfHits();
  hits1->Reserve(max_hit);
  for (int n_hit = 0; n_hit < hits0.NumberOfHits(); ++n_hit) {
    hit1->SetInvalid();
    auto hit0 = hits0.Hit(n_hit);
    hit1->SetIds(hit0.ModuleID(), hit0.ChannelID());
    hit1->SetTiming(float{GetTriggerTime(timestamp, hit0.Time())});
    hits1->PushBack(*hit1);
  }
  return hits1->GetEventSize() + clusters1->GetEventSize();
}





int E16DST_DST1TriggerFactory(E16DST_DST0Detector<E16DST_DST0TriggerHit>& gtr_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& hbd_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& lg_hits, E16DST_DST0UT3& ut3, E16DST_DST1Trigger* trigger) {
//  auto coincidence_map = new E16DST_TriggerCoincidenceMap(CoincidenceMapFiles, TriggerChannelMapFiles);




} // E16DST1::Trigger

}
