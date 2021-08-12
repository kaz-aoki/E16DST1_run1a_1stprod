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
//  static auto channel_map      = new E16DST_TriggerChannelMap(TriggerChannelMapFiles[0], TriggerChannelMapFiles[1], TriggerChannelMapFiles[2]);
  static auto coincidence_maps = new E16DST_TriggerCoincidenceMap(CoincidenceMapFiles, TriggerChannelMapFiles);
  


}
  
int E16DST_DST1TriggerFactory(E16DST_DST0Detector<E16DST_DST0TriggerHit>& gtr_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& hbd_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& lg_hits, E16DST_DST0UT3& ut3, uint64_t timestamp, E16DST_DST1Trigger* trigger) {
  E16DST_DST1TriggerHitAndClusterFactory(gtr_hits, timestamp, &trigger->GTRHits(), &trigger->GTRClusters());
  E16DST_DST1TriggerHitAndClusterFactory(hbd_hits, timestamp, &trigger->HBDHits(), &trigger->HBDClusters());
  E16DST_DST1TriggerHitAndClusterFactory(lg_hits,  timestamp, &trigger->LGHits(),  &trigger->LGClusters());
  auto max_track =ut3.NumberOfTracks();
  trigger->Tracks().Reserve(max_track);
  for (int n_track = 0; n_track < max_track; ++n_track) {
    E16DST_DST1TriggerSingleHitFactory(ut3.Track(n_track), timestamp, &trigger->Tracks().Hit(n_track));
  }



//void E16ANA_Trigger::Set(E16DST_DST0PhysicsEvent* _event){
////  for(auto i=0;i<3;++i){
////    dtcTime[i].clear();
////    timeSet[i].clear();
////  }
//  gtrMapPos.clear();
//  hbdMapPos.clear();
//  trackSets.clear();
//  hitSets.clear();
//  clusters.clear();
//  
////  auto  timestamp = _event->TimeStamp();
//  std::array<E16DST_DST0Detector<E16DST_DST0TriggerHit&>, 3> trigger_hits = {gtr_hits, hbd_hits, lg_hits};
//  
////  for (int detector = 0; detector < 3; ++detector) {
////    auto n_hits = trigger_hits[i].NumberOfHits();
////    for (int hit_num = 0; hit_num < n_hits; ++hit_num) {
////      auto& hit = trigger_hits[detector].Hit(hit_num);
////      auto hit_time = GetTriggerTime(timestamp, hit.Time());
////      dtcTime[i].emplace_back(GetTime(timestamp, (uint32_t)tdc));
////      uint16_t id = 100 * hit.ModuleID() + hit.ChannelID();
////      if(timeSet[i].count(id)){
////        timeSet[i][id].emplace_back(tdc);
////      }
////      else{
////        std::vector<uint16_t> vTime = {tdc};
////        timeSet[i].emplace(id, vTime);
////      }
////    }
////  }
////
////  std::vector<E16DST_DST0TriggerHit> trackPos;
//////  auto& ut3 = _event->UT3();
////  for(auto i=0;i<ut3.NumberOfTracks();++i){
////    auto& track = ut3.Track(i);
////    auto hit = E16DST_DST0TriggerHit();
////    hit.SetIDs(track.ModuleID(), track.ChannelID());
////    hit.SetTime(track.Time());
////    trackPos.emplace_back(hit);
////    auto tmpTime = track.Time();
////    if(track_coarse_time[0]!=tmpTime/64){
////      track_coarse_time[0] = tmpTime / 64;
////    }
////    else{
////      track_coarse_time[1] = tmpTime / 64;
////    }
////    auto tdc = GetTime(timestamp, tmpTime);
////    trackTime.emplace_back(tdc);
////  }
////
////  std::vector<E16DST_DST0TriggerHit> hitPos;
////  for(auto i=0;i<trigger_hits[2].NumberOfHits();++i){
////    auto& track = trigger_hits[2].Hit(i);
////    auto hit = E16DST_DST0TriggerHit();
////    hit.SetIDs(track.ModuleID(), track.ChannelID());
////    hit.SetTime(track.Time());
////    auto tdc = track.Time();
////    if(tdc/64==track_coarse_time[0]||tdc/64==track_coarse_time[1]){
////      hitPos.emplace_back(hit);
////    }
////  }
//
//  std::array<std::array<bool, E16DST_Constant::NModules*E16DST_Constant::NTriggerChannelsGTR>, 2> gtrMaps;
//  std::array<std::array<bool, E16DST_Constant::NModules*E16DST_Constant::NTriggerChannelsHBD>, 2> hbdMaps;
//  auto& new_maps = ut3.Hitmap();
//  for (int module = 0; module < E16DST_Constant::NModules; ++module) {
//    for (int channel = 0; channel < E16DST_Constant::NTriggerChannelsGTR; ++channel) {
//      if (new_maps.GTR[module][channel] == 1) {
//        auto ids = channelMap.GetDetectorIDs(32 *module + channel);
//        E16DST_DST0Hit hit;
//        hit.SetIDs(ids.moduleID, ids.channelID);
//        gtrMapPos.emplace_back(hit);
//        gtrMaps[0][E16DST_Constant::NTriggerChannelsGTR*i+j] = true;
//      }
//      else{
//        gtrMaps[0][E16DST_Constant::NTriggerChannelsGTR*i+j] = false;
//      }
//    }
//    for(auto j=0;j<E16DST_Constant::NTriggerChannelsHBD;++j){
//      if(new_maps.HBD[i][j]==1){
//        E16DST_TriggerChannelMap::IDs ids;
//        if(j<E16DST_Constant::NTriggerChannelsHBD/2){
//          ids = chMap.GetDetectorIDs(256+64*i+j);
//        }
//        else{
//          ids = chMap.GetDetectorIDs(256+64*i+32+j-18);
//        }
//        E16DST_DST0Hit hit;
//        hit.SetIDs(ids.moduleID, ids.channelID);
//        hbdMapPos.emplace_back(hit);
//        hbdMaps[0][E16DST_Constant::NTriggerChannelsHBD*i+j] = true;
//      }
//      else{
//        hbdMaps[0][E16DST_Constant::NTriggerChannelsHBD*i+j] = false;
//      }
//    }
//  }
//  auto& old_maps = ut3.HitmapOld();
//  for(auto i=0;i<E16DST_Constant::NModules;++i){
//    for(auto j=0;j<E16DST_Constant::NTriggerChannelsGTR;++j){
//      if(old_maps.GTR[i][j]==1){
//        auto ids = chMap.GetDetectorIDs(32*i+j);
//        E16DST_DST0Hit hit;
//        hit.SetIDs(ids.moduleID, ids.channelID);
//        gtrMapPos.emplace_back(hit);
//        gtrMaps[1][E16DST_Constant::NTriggerChannelsGTR*i+j] = true;
//      }
//      else{
//        gtrMaps[1][E16DST_Constant::NTriggerChannelsGTR*i+j] = false;
//      }
//    }
//    for(auto j=0;j<E16DST_Constant::NTriggerChannelsHBD;++j){
//      if(old_maps.HBD[i][j]==1){
//        E16DST_TriggerChannelMap::IDs ids;
//        if(j<E16DST_Constant::NTriggerChannelsHBD/2){
//          ids = chMap.GetDetectorIDs(256+64*i+j);
//        }
//        else{
//          ids = chMap.GetDetectorIDs(256+64*i+32+j-18);
//        }
//        E16DST_DST0Hit hit;
//        hit.SetIDs(ids.moduleID, ids.channelID);
//        hbdMapPos.emplace_back(hit);
//        hbdMaps[1][E16DST_Constant::NTriggerChannelsHBD*i+j] = true;
//      }
//      else{
//        hbdMaps[1][E16DST_Constant::NTriggerChannelsHBD*i+j] = false;
//      }
//    }
//  }
//
//  for(auto& a:trackPos){
//    E16ANA_Trigger::_trackSet trackSet;
//    trackSet.lgcHit = a;
//    auto coinMap = coinMaps.GetCoinMap(a.ModuleID(), a.ChannelID());
//    for(auto i=0;i<coinMap.gtrMap.size();++i){
//      if(coinMap.gtrMap[i]&&(gtrMaps[0][E16DST_Constant::NTriggerChannelsGTR*coinMap.gtrStartMod+i]||gtrMaps[1][E16DST_Constant::NTriggerChannelsGTR*coinMap.gtrStartMod+i])){
//        uint16_t tmp0 = i / E16DST_Constant::NTriggerChannelsGTR;
//        uint16_t tmp1 = i % E16DST_Constant::NTriggerChannelsGTR;
//        auto ids = chMap.GetDetectorIDs(32*(coinMap.gtrStartMod+tmp0)+tmp1);
//        E16DST_DST0Hit gtrHit;
//        gtrHit.SetIDs(ids.moduleID, ids.channelID);
//        trackSet.gtrHits.emplace_back(gtrHit);
//      }
//    }
//    for(auto i=0;i<coinMap.hbdMap.size();++i){
//      if(coinMap.hbdMap[i]&&(hbdMaps[0][E16DST_Constant::NTriggerChannelsHBD*coinMap.hbdStartMod+i]||hbdMaps[1][E16DST_Constant::NTriggerChannelsHBD*coinMap.hbdStartMod+i])){
//        E16DST_TriggerChannelMap::IDs ids;
//        uint16_t tmp0 = i / (E16DST_Constant::NTriggerChannelsHBD / 2);
//        uint16_t tmp1 = i % (E16DST_Constant::NTriggerChannelsHBD / 2);
//        ids = chMap.GetDetectorIDs(256+64*coinMap.hbdStartMod+32*tmp0+tmp1);
//        E16DST_DST0Hit hbdHit;
//        hbdHit.SetIDs(ids.moduleID, ids.channelID);
//        trackSet.hbdHits.emplace_back(hbdHit);
//      }
//    }
//    trackSets.emplace_back(trackSet);
//  }
//
//  for(auto& a:hitPos){
//    E16ANA_Trigger::_trackSet trackSet;
//    trackSet.lgcHit = a;
//    auto coinMap = coinMaps.GetCoinMap(a.ModuleID(), a.ChannelID());
//    for(auto i=0;i<coinMap.gtrMap.size();++i){
//      if(coinMap.gtrMap[i]&&(gtrMaps[0][E16DST_Constant::NTriggerChannelsGTR*coinMap.gtrStartMod+i]||gtrMaps[1][E16DST_Constant::NTriggerChannelsGTR*coinMap.gtrStartMod+i])){
//        uint16_t tmp0 = i / E16DST_Constant::NTriggerChannelsGTR;
//        uint16_t tmp1 = i % E16DST_Constant::NTriggerChannelsGTR;
//        auto ids = chMap.GetDetectorIDs(32*(coinMap.gtrStartMod+tmp0)+tmp1);
//        E16DST_DST0Hit gtrHit;
//        gtrHit.SetIDs(ids.moduleID, ids.channelID);
//        trackSet.gtrHits.emplace_back(gtrHit);
//      }
//    }
//    for(auto i=0;i<coinMap.hbdMap.size();++i){
//      if(coinMap.hbdMap[i]&&(hbdMaps[0][E16DST_Constant::NTriggerChannelsHBD*coinMap.hbdStartMod+i]||hbdMaps[1][E16DST_Constant::NTriggerChannelsHBD*coinMap.hbdStartMod+i])){
//        E16DST_TriggerChannelMap::IDs ids;
//        uint16_t tmp0 = i / (E16DST_Constant::NTriggerChannelsHBD / 2);
//        uint16_t tmp1 = i % (E16DST_Constant::NTriggerChannelsHBD / 2);
//        ids = chMap.GetDetectorIDs(256+64*coinMap.hbdStartMod+32*tmp0+tmp1);
//        E16DST_DST0Hit hbdHit;
//        hbdHit.SetIDs(ids.moduleID, ids.channelID);
//        trackSet.hbdHits.emplace_back(hbdHit);
//      }
//    }
//    hitSets.emplace_back(trackSet);
//  }
//  
//  std::vector<std::vector<uint16_t>> tmpTracks;
//  for(auto i=0;i<ut3.NumberOfTracks();++i){
//    auto&    track = ut3.Track(i);
//    auto     mod   = track.ModuleID();
//    auto     ch    = track.ChannelID();
//    uint16_t hol   = ch % 10;
//    uint16_t ver   = ch / 10;
//    auto     time  = track.Time();
//    
//    std::vector<bool> isCluster;
//    bool              isAnyCluster = false;
//    for(const auto& a:tmpTracks){
//      bool tmpCluster = false;
//      for(const auto& b:a){
//        auto tmpTrack  = ut3.Track(b);
//        auto     cMod  = tmpTrack.ModuleID();
//        auto     cCh   = tmpTrack.ChannelID();
//        uint16_t cHol  = cCh % 10;
//        uint16_t cVer  = cCh / 10;
//        auto     cTime = tmpTrack.Time();
//        if(mod==cMod){
//          if(abs(hol-cHol)>2||abs(ver-cVer)>2){
//            continue;
//          }
//          if(abs(time-cTime)>E16ANA_TriggerConstant::clusterTimeRange){
//            continue;
//          }
//          tmpCluster = true;
//        }
//      }
//      isCluster.emplace_back(tmpCluster);
//      if(tmpCluster){
//        isAnyCluster = true;
//      }
//    }
//    if(!isAnyCluster){
//      std::vector<uint16_t> tmpTrack;
//      tmpTrack.emplace_back(i);
//      tmpTracks.emplace_back(tmpTrack);
//    }
//    else{
//      uint16_t firstClst = 0;
//      uint16_t nErase = 0;
//      for(int j=0;j<isCluster.size();++j){
//        if(isCluster[j]){
//          if(nErase==0){
//            tmpTracks[j].emplace_back(i);
//            firstClst = j;
//          }
//          else{
//            std::copy(tmpTracks[j-nErase].begin(), tmpTracks[j-nErase].end(), tmpTracks[firstClst].begin());
//            tmpTracks.erase(tmpTracks.begin()+j-nErase);
//          }
//          ++nErase;
//        }
//      }
//    }
//  }
//  for(const auto& a:tmpTracks){
//    E16ANA_Trigger::_cluster clst;
//    std::vector<uint16_t> cHeight;
//    std::vector<uint16_t> cWidth;
//    std::vector<uint16_t> cTime;
//    for(const auto& b:a){
//      auto& track = ut3.Track(b);
//      auto mod = track.ModuleID();
//      auto ch  = track.ChannelID();
//      clst.modMean = mod;
//      cHeight.emplace_back(ch / 10);
//      cWidth.emplace_back(7 * (mod - 101) +  ch % 10);
//      cTime.emplace_back(track.Time());
//      (clst.tracks).emplace_back(track);
//    }
//    clst.wMean     = std::accumulate(cHeight.begin(), cHeight.end(), 0.) / cHeight.size();
//    clst.hMean     = std::accumulate(cWidth.begin(),  cWidth.end(),  0.) / cWidth.size();
//    clst.tMean     = std::accumulate(cTime.begin(),   cTime.end(),   0.) / cTime.size();
//    clst.height    = *std::max_element(cHeight.begin(), cHeight.end()) - *std::min_element(cHeight.begin(), cHeight.end());
//    clst.width     = *std::max_element(cWidth.begin(),  cWidth.end())  - *std::min_element(cWidth.begin(),  cWidth.end());
//    clst.timeRange = *std::max_element(cTime.begin(),   cTime.end())   - *std::min_element(cTime.begin(),   cTime.end());
//    clst.nTracks   = (clst.tracks).size();
//    clusters.emplace_back(clst);
//  }
//}






}

} // E16DST1::Trigger
