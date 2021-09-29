#include "E16DST_DST1.hh"

#include "E16ANA_TriggerConstant.hh"
#include "E16DST_DST1Constant.hh"
#include "E16ANA_LGBasic.hh"

void E16DST_DST1Cluster::SetHitOrders(std::vector<int16_t>& _hit_orders) {
  hit_orders.clear();
  std::copy(_hit_orders.begin(), _hit_orders.end(), std::back_inserter(hit_orders));
}

double E16DST_DST1SSDHit::LocalX() {
}

TVector3 E16DST_DST1SSDHit::LocalPos(E16ANA_GeometryV2& geometry) {
  double local_x = (channel_id - 128 * 3) * 600. / (128 * 6); // tmp
  return TVector3(local_x, 0., 0.);
}

TVector3 E16DST_DST1SSDHit::GlobalPos(E16ANA_GeometryV2& geometry) {
  return geometry.SSD(ModuleId2020To2013(module_id))->GetGPos(LocalPos(geometry)); // tmp
}

TVector3 E16DST_DST1SSDCluster::LocalPos() {
  return TVector3(center_of_gravity, 0., 0.);
}

TVector3 E16DST_DST1SSDCluster::GlobalPos(E16ANA_GeometryV2& geometry) {
  return geometry.SSD(ModuleId2020To2013(module_id))->GetGPos(LocalPos()); // tmp
}

double E16DST_DST1GTRHit::LocalX() {
//    return E16DST_DST1Constant::gtr_strip_pitch_x; 
    double strip_pitch;
    double position_start;
    int n_strip_x = E16DST_DST1Constant::nstrips_x[layer_id]; 
    int n_strip_y = E16DST_DST1Constant::nstrips_y[layer_id]; 
    double inverted;
    if(IsX()){
        strip_pitch = E16DST_DST1Constant::gtr_strip_pitch_x;
        position_start = -(double)n_strip_x / 2.0 * strip_pitch + strip_pitch * 0.5;
        inverted = +1.0;
    }
    else if (IsY()){
        strip_pitch = E16DST_DST1Constant::gtr_strip_pitch_y;
        position_start = -(double)n_strip_y / 2.0 * strip_pitch + strip_pitch * 0.5;
        inverted = -1.0;
    }
    else if (IsYb()){
        strip_pitch = E16DST_DST1Constant::gtr_strip_pitch_y;
        position_start = -(double)n_strip_y / 2.0 * strip_pitch + strip_pitch * 0.5;
        inverted = +1.0;
    }
    return (channel_id * strip_pitch + position_start) * inverted;
}

TVector3 E16DST_DST1GTRHit::LocalPos(E16ANA_GeometryV2& geometry) {
    double strip_pitch;
    double position_start;
    int n_strip_x = E16DST_DST1Constant::nstrips_x[layer_id]; 
    int n_strip_y = E16DST_DST1Constant::nstrips_y[layer_id]; 
    double inverted;
    if(IsX()){
        strip_pitch = E16DST_DST1Constant::gtr_strip_pitch_x;
        position_start = -(double)n_strip_x / 2.0 * strip_pitch + strip_pitch * 0.5;
        inverted = +1.0;
    }
    else if (IsY()){
        strip_pitch = E16DST_DST1Constant::gtr_strip_pitch_y;
        position_start = -(double)n_strip_y / 2.0 * strip_pitch + strip_pitch * 0.5;
        inverted = -1.0;
    }
    else if (IsYb()){
        strip_pitch = E16DST_DST1Constant::gtr_strip_pitch_y;
        position_start = -(double)n_strip_y / 2.0 * strip_pitch + strip_pitch * 0.5;
        inverted = +1.0;
    }
    double local1d = (channel_id * strip_pitch + position_start) * inverted;
    TVector3 lpos;
    if(IsX()){
         lpos =  TVector3(local1d, 0.0, 0.0);
    }
    else {
        lpos =  TVector3(0.0, local1d, 0.0);
    }
    return lpos;
}

TVector3 E16DST_DST1GTRHit::GlobalPos(E16ANA_GeometryV2& geometry) {
    double strip_pitch;
    double position_start;
    int n_strip_x = E16DST_DST1Constant::nstrips_x[layer_id]; 
    int n_strip_y = E16DST_DST1Constant::nstrips_y[layer_id]; 
    double inverted;
    if(IsX()){
        strip_pitch = E16DST_DST1Constant::gtr_strip_pitch_x;
        position_start = -(double)n_strip_x / 2.0 * strip_pitch + strip_pitch * 0.5;
        inverted = +1.0;
    }
    else if (IsY()){
        strip_pitch = E16DST_DST1Constant::gtr_strip_pitch_y;
        position_start = -(double)n_strip_y / 2.0 * strip_pitch + strip_pitch * 0.5;
        inverted = -1.0;
    }
    else if (IsYb()){
        strip_pitch = E16DST_DST1Constant::gtr_strip_pitch_y;
        position_start = -(double)n_strip_y / 2.0 * strip_pitch + strip_pitch * 0.5;
        inverted = +1.0;
    }
    double local1d = (channel_id * strip_pitch + position_start) * inverted;
    TVector3 lpos;
    if(IsX()){
         lpos =  TVector3(local1d, 0.0, 0.0);
    }
    else {
        lpos =  TVector3(0.0, local1d, 0.0);
    }
    TVector3 gpos = TVector3(geometry.GTR(ModuleId2020To2013(module_id), layer_id)->GetGPos(lpos));
    return gpos;

}

TVector3 E16DST_DST1GTRCluster::LocalPos() {
    TVector3 lpos;
    if(IsX()){
        lpos = TVector3(center_of_gravity, 0.0, 0.0);
    }
    else{
        lpos = TVector3(0.0, center_of_gravity, 0.0);
    }
    return lpos;
}

TVector3 E16DST_DST1GTRCluster::GlobalPos(E16ANA_GeometryV2& geometry) {
    TVector3 gpos;
    if(IsX()){
        TVector3 lpos = TVector3(double(center_of_gravity), 0.0, 0.0);
        gpos = TVector3(geometry.GTR(ModuleId2020To2013(module_id), layer_id)->GetGPos(lpos));
    }
    else{
        TVector3 lpos = TVector3(0.0, double(center_of_gravity), 0.0);
        gpos = TVector3(geometry.GTR(ModuleId2020To2013(module_id), layer_id)->GetGPos(lpos));
    }
    return gpos;
}

TVector3 E16DST_DST1HBDHit::LocalPos(E16ANA_GeometryV2& geometry) {
  return lpos;
}

TVector3 E16DST_DST1HBDHit::GlobalPos(E16ANA_GeometryV2& geometry) { 
  TVector3 gpos = geometry.HBD(ModuleId2020To2013(module_id))->GetGPos(lpos);
  return gpos;
}

TVector3 E16DST_DST1HBDCluster::LocalPos() {
  
  return lpos;
}

TVector3 E16DST_DST1HBDCluster::GlobalPos(E16ANA_GeometryV2& geometry) {
  TVector3 gpos = geometry.HBD(ModuleId2020To2013(module_id))->GetGPos(lpos);
  return gpos;
}

TVector3 E16DST_DST1HBDCluster::GlobalPosWADC(E16ANA_GeometryV2& geometry) { 
  TVector3 gpos = geometry.HBD(ModuleId2020To2013(module_id))->GetGPos(lpos_w_adc);
  return gpos;
}

float E16DST_DST1LGHit::GetCalibTiming(E16ANA_LGBasic& lgbasic){
  double param = lgbasic.GetT0(module_id, channel_id);// [ns]
  return timing+100.-param;
}

float E16DST_DST1LGHit::GetEnergyDeposit(E16ANA_LGBasic& lgbasic){
  double param = lgbasic.GetGain(module_id, channel_id);
  return param*peak_height;
}

TVector3 E16DST_DST1LGHit::LocalPos(E16ANA_GeometryV2& geometry) {
  TVector3 gpos = {E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue};
  TVector3 lpos = {E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue};
  int mod = ModuleId2020To2013(module_id);
  gpos = geometry.LG( mod, channel_id )->GetDetectorCenter();
  lpos = geometry.LGVD( mod )->GetLPos(gpos);
  return lpos;
}

TVector3 E16DST_DST1LGHit::GlobalPos(E16ANA_GeometryV2& geometry) {
  TVector3 pos = {E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue};
  int mod = ModuleId2020To2013(module_id);
  pos = geometry.LG( mod, channel_id)->GetDetectorCenter();
  return pos;
}

TVector3 E16DST_DST1LGCluster::LocalPos() {
}

TVector3 E16DST_DST1LGCluster::GlobalPos(E16ANA_GeometryV2& geometry) {
}

TVector3 E16DST_DST1TriggerHit::LocalPos(E16ANA_GeometryV2& geometry) {
  TVector3 pos = {E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue};
  int geometry_module_id = ModuleId2020To2013(module_id);
  if (detector == E16DST_DST1Constant::kGTR) {
    TVector3 local_pos = {0., - E16ANA_TriggerConstant::kGTR300ModuleSize / 2 + (double{E16ANA_TriggerConstant::kGTR300ModuleSize} / E16DST_Constant::NTriggerChannelsGTR) * (channel_id + 0.5), 0.};
    return local_pos;
  } else if (detector == E16DST_DST1Constant::kHBD) {
    int x = - E16ANA_TriggerConstant::kHBDModuleSize / 2 + (double{E16ANA_TriggerConstant::kHBDModuleSize} / E16ANA_TriggerConstant::kNumHBDTriggerChannelOneAxis) * (channel_id % 10 + 0.5);
    int y = - E16ANA_TriggerConstant::kHBDModuleSize / 2 + (double{E16ANA_TriggerConstant::kHBDModuleSize} / E16ANA_TriggerConstant::kNumHBDTriggerChannelOneAxis) * (channel_id / 10 + 0.5);
    TVector3 local_pos = {x, y, 0.};
    return local_pos;
  } else if (detector == E16DST_DST1Constant::kLG) {
    return geometry.LGVD(geometry_module_id)->GetLPos(GlobalPos(geometry));
  }
  return pos;
}

TVector3 E16DST_DST1TriggerHit::GlobalPos(E16ANA_GeometryV2& geometry) {
  TVector3 pos = {E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue, E16DST_DST1Constant::kInvalidValue};
  int geometry_module_id = ModuleId2020To2013(module_id);
  if (detector == E16DST_DST1Constant::kGTR) {
    return geometry.GTR(geometry_module_id, 2)->GetGPos(LocalPos(geometry));
  } else if (detector == E16DST_DST1Constant::kHBD) {
    return geometry.HBD(geometry_module_id)->GetGPos(LocalPos(geometry));
  } else if (detector == E16DST_DST1Constant::kLG) {
    pos = geometry.LG(geometry_module_id, channel_id)->GetDetectorCenter();
  }
  return pos;
}

int E16DST_DST1DetectorHeader::Read(std::fstream* fp) {
  int read_size = sizeof(E16DST_DST1DetectorHeader);
  fp->read(reinterpret_cast<char*>(this), read_size);
  return read_size;
}

int E16DST_DST1TriggerTrackSet::GetEventSize() {
}

int E16DST_DST1TriggerTrackSet::Write(std::fstream* fp) {
}

int E16DST_DST1TriggerTrackSet::Read(std::fstream* fp) {
}

int E16DST_DST1Trigger::GetEventSize() const {
}

bool E16DST_DST1Trigger::SearchTriggerHit(std::vector<E16DST_DST1TriggerHit>& hits, int module_id, int channel_id) {
  for (auto& hit : hits) {
    if (hit.ModuleId() == module_id && hit.ChannelId() == channel_id) {
      return true;
    }
  }
  return false;
}

bool E16DST_DST1Trigger::IsTriggerHit(E16DST_DST1GTRHit& hit) {
  auto layer_id = hit.LayerId();
  auto type     = hit.Type();
  if (layer_id != 2 || type != E16DST_DST1Constant::kIsY) {
    return false;
  }
  int module_id = hit.ModuleId();
  int channel_id = E16DST_Constant::NTriggerChannelsGTR - 1 - hit.ChannelId() / (E16ANA_TriggerConstant::kNumGTR300YSignalChannel / E16DST_Constant::NTriggerChannelsGTR);
  return SearchTriggerHit(gtr_hits, module_id, channel_id);
}

bool E16DST_DST1Trigger::IsTriggerHit(E16DST_DST1HBDHit& hit) {
}

bool E16DST_DST1Trigger::IsTriggerHit(E16DST_DST1LGHit& hit) {
  return SearchTriggerHit(lg_hits, hit.ModuleId(), hit.ChannelId());
}

//std::vector<E16DS_DST1TriggerHit*> E16DST_DST1Trigger::HitsIncludedTrackSet(bool is_track, int n) {
//  std::vector<E16DST_DST1TriggerHit*> hits;
//}

void E16DST_DST1Trigger::Print() {
  auto max_track = track_sets.size();
  std::cout << "Number of tracks: " << max_track << std::endl << std::endl;
  for (int n_track = 0; n_track < max_track; ++n_track) {
    std::cout << "Track ID: " << n_track << std::endl;
    auto& track_set = track_sets[n_track];
    auto n_gtr_hits = track_set.NumGTRHits();
    auto n_hbd_hits = track_set.NumHBDHits();
    auto n_lg_hits = track_set.NumLGHits();
    std::cout << "  Number of tracked GTR: " << n_gtr_hits << std::endl;
    for (int n_hit = 0; n_hit < n_gtr_hits; ++n_hit) {
      auto order = track_set.GTRHitOrder(n_hit);
      auto& hit = gtr_hits[order];
      std::cout << "    Tracked GTR hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId() << ", timing = " << hit.Timing() << std::endl;
    }
    std::cout << "  Number of tracked HBD: " << n_hbd_hits << std::endl;
    for (int n_hit = 0; n_hit < n_hbd_hits; ++n_hit) {
      auto order = track_set.HBDHitOrder(n_hit);
      auto& hit = hbd_hits[order];
      std::cout << "    Tracked HBD hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId() << ", timing = " << hit.Timing() << std::endl;
    }
    std::cout << "  Number of tracked LG: " << n_lg_hits << std::endl;
    if (track_set.NumLGHits() == 1) {
      auto order = track_set.LGHitOrder(0);
      auto& hit = tracks[order];
      std::cout << "    Tracked LG hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId() << ", timing = " << hit.Timing() << std::endl;
    } else {
      std::cerr << "    Invalid number of LG Hits: " << track_set.NumLGHits() << std::endl;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void E16DST_DST1Trigger::Print(E16ANA_GeometryV2& geometry) {
  auto max_track = track_sets.size();
  std::cout << "Number of tracks: " << max_track << std::endl << std::endl;
  for (int n_track = 0; n_track < max_track; ++n_track) {
    std::cout << "Track ID: " << n_track << std::endl;
    auto& track_set = track_sets[n_track];
    auto n_gtr_hits = track_set.NumGTRHits();
    auto n_hbd_hits = track_set.NumHBDHits();
    auto n_lg_hits = track_set.NumLGHits();
    std::cout << "  Number of tracked GTR: " << n_gtr_hits << std::endl;
    for (int n_hit = 0; n_hit < n_gtr_hits; ++n_hit) {
      auto order = track_set.GTRHitOrder(n_hit);
      auto& hit = gtr_hits[order];
      std::cout << "    Tracked GTR hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId() << ", timing = " << hit.Timing()
                << ", local position = (" << hit.LocalPos(geometry).X() << ", " << hit.LocalPos(geometry).Y() << ", " << hit.LocalPos(geometry).Z() << ")"
                << ", global position = (" << hit.GlobalPos(geometry).X() << ", " << hit.GlobalPos(geometry).Y() << ", " << hit.GlobalPos(geometry).Z() << ")" << std::endl;
    }
    std::cout << "  Number of tracked HBD: " << n_hbd_hits << std::endl;
    for (int n_hit = 0; n_hit < n_hbd_hits; ++n_hit) {
      auto order = track_set.HBDHitOrder(n_hit);
      auto& hit = hbd_hits[order];
      std::cout << "    Tracked HBD hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId() << ", timing = " << hit.Timing()
                << ", local position = (" << hit.LocalPos(geometry).X() << ", " << hit.LocalPos(geometry).Y() << ", " << hit.LocalPos(geometry).Z() << ")"
                << ", global position = (" << hit.GlobalPos(geometry).X() << ", " << hit.GlobalPos(geometry).Y() << ", " << hit.GlobalPos(geometry).Z() << ")" << std::endl;
    }
    std::cout << "  Number of tracked LG: " << n_lg_hits << std::endl;
    if (track_set.NumLGHits() == 1) {
      auto order = track_set.LGHitOrder(0);
      auto& hit = tracks[order];
      std::cout << "    Tracked LG hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId() << ", timing = " << hit.Timing()
                << ", local position = (" << hit.LocalPos(geometry).X() << ", " << hit.LocalPos(geometry).Y() << ", " << hit.LocalPos(geometry).Z() << ")"
                << ", global position = (" << hit.GlobalPos(geometry).X() << ", " << hit.GlobalPos(geometry).Y() << ", " << hit.GlobalPos(geometry).Z() << ")" << std::endl;
    } else {
      std::cerr << "    Invalid number of LG Hits: " << track_set.NumLGHits() << std::endl;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int E16DST_DST1PhysicsRecord::Write(std::fstream* fp) {
  int write_size = sizeof(E16DST_DST1PhysicsHeader);
  fp->write(reinterpret_cast<char*>(this), write_size);
  write_size += ssd.Write(fp);
  write_size += gtr.Write(fp);
  write_size += hbd.Write(fp);
  write_size += lg.Write(fp);
//  write_size += trigger.Write(fp);
  return write_size;
}

int E16DST_DST1PhysicsRecord::Read(std::fstream* fp) {
  int read_size = sizeof(E16DST_DST1PhysicsHeader);
  fp->read(reinterpret_cast<char*>(this), read_size);
  read_size += ssd.Read(fp);
  read_size += gtr.Read(fp);
  read_size += hbd.Read(fp);
  read_size += lg.Read(fp);
//  read_size += trigger.Read(fp);
  return read_size;
}

int E16DST_DST1RecordHeader::Write(std::fstream* fp) {
  int length = sizeof(E16DST_DST1RecordHeader);
  fp->write(reinterpret_cast<char*>(this), length);
  return length;
}

int E16DST_DST1RecordHeader::Read(std::fstream* fp) {
  int length = sizeof(E16DST_DST1RecordHeader);
  fp->read(reinterpret_cast<char*>(this), length);
  return length;
}
