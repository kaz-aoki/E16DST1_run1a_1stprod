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

bool E16DST_DST1TriggerSingleHitFactory(E16DST_DST0TriggerHit& hit0, uint64_t timestamp, E16DST_DST1TriggerHit* hit1) {
  hit1->SetInvalid();
  hit1->SetIds(hit0.ModuleID(), hit0.ChannelID());
  hit1->SetTiming(float{GetTriggerTime(timestamp, hit0.Time())});
  return true;
}

int E16DST_DST1TriggerHitAndClusterFactory(E16DST_DST0Detector<E16DST_DST0TriggerHit>& hits0, uint64_t timestamp, E16DST_DST0Detector<E16DST_DST1TriggerHit>* hits1, E16DST_DST0Detector<E16DST_DST1TriggerCluster>* clusters1) {
  auto max_hit = hits0.NumberOfHits();
  hits1->Reserve(max_hit);
  for (int n_hit = 0; n_hit < hits0.NumberOfHits(); ++n_hit) {
    E16DST_DST1TriggerSingleHitFactory(hits0.Hit(n_hit), timestamp, &hits1->Hit(n_hit));
  }
  return hits1->GetEventSize() + clusters1->GetEventSize();
}

int E16DST_DST1TriggerHitAndTrackSetFactory(E16DST_DST0UT3& ut3, uint64_t timestamp, E16DST_DST1Trigger* trigger) {
}
  
int E16DST_DST1TriggerFactory(E16DST_DST0Detector<E16DST_DST0TriggerHit>& gtr_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& hbd_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& lg_hits, E16DST_DST0UT3& ut3, uint64_t timestamp, E16DST_DST1Trigger* trigger) {
  static auto coincidence_map = new E16DST_TriggerCoincidenceMap(CoincidenceMapFiles, TriggerChannelMapFiles);
  E16DST_DST1TriggerHitAndClusterFactory(gtr_hits, timestamp, &trigger->GTRHits(), &trigger->GTRClusters());
  E16DST_DST1TriggerHitAndClusterFactory(hbd_hits, timestamp, &trigger->HBDHits(), &trigger->HBDClusters());
  E16DST_DST1TriggerHitAndClusterFactory(lg_hits,  timestamp, &trigger->LGHits(),  &trigger->LGClusters());
  auto max_track =ut3.NumberOfTracks();
  trigger->Tracks().Reserve(max_track);
  for (int n_track = 0; n_track < max_track; ++n_track) {
    E16DST_DST1TriggerSingleHitFactory(ut3.Track(n_track), timestamp, &trigger->Tracks().Hit(n_track));
  }




}

} // E16DST1::Trigger
