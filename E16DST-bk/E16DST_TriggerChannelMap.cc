#include "E16DST_TriggerChannelMap.hh"
#include "E16DST_Constant.hh"

#include <fstream>

E16DST_TriggerChannelMap::E16DST_TriggerChannelMap(const std::string &trg_gtr_file, const std::string &trg_hbd_file, const std::string &trg_drs4_file) {
  std::ifstream gtrTxt(trg_gtr_file);
  if (!gtrTxt) {
    std::exit(1);
  }
  for (int i = 0; i < E16DST_Constant::NMergerChannels; ++i) {
    if (gtrTxt.eof()) {
      std::exit(1);
    }
    uint16_t a, b, c, d, e, f, g;
    gtrTxt >> a >> b >> c >> d >> e >> f >> g;
    if (d == 255 || e == 255) {
      types[i] = Unknown;
    } else {
      types[i] = GTR;
    }
    mod[i] = d;
    ch[i]  = e;
  }
  std::ifstream hbdTxt(trg_hbd_file);
  if (!hbdTxt) {
    std::exit(0);
  }
  for (int i = 0; i < 512; ++i) {
    if (hbdTxt.eof()) {
      std::exit(0);
    }
    uint16_t a, b, c, d, e, f, g;
    hbdTxt >> a >> b >> c >> d >> e >> f >> g;
    if (d == 255 || e == 255) {
      types[E16DST_Constant::NMergerChannels + i] = Unknown;
    } else {
      types[E16DST_Constant::NMergerChannels + i] = HBD;
    }
    mod[E16DST_Constant::NMergerChannels + i] = d;
    ch[E16DST_Constant::NMergerChannels + i]  = e;
  }
  std::ifstream drs4Txt(trg_drs4_file);
  if (!drs4Txt) {
    std::exit(0);
  }
  for (int i = 0; i < 512; ++i) {
    if (drs4Txt.eof()) {
      std::exit(1);
    }
    uint16_t a, b, c, d, e, f, g, h;
    drs4Txt >> a >> b >> c >> d >> e >> f >> g >> h;
    if (d == 0) {
      types[E16DST_Constant::NMergerChannels * 3 + i] = LG;
    } else if (d == 1) {
      types[E16DST_Constant::NMergerChannels * 3 + i] = CT;
    } else if (d == 2) {
      types[E16DST_Constant::NMergerChannels * 3 + i] = Scaler;
    } else {
      types[E16DST_Constant::NMergerChannels * 3 + i] = Unknown;
    }
    mod[E16DST_Constant::NMergerChannels * 3 + i] = e;
    ch[E16DST_Constant::NMergerChannels * 3 + i]  = f;
  }
}

E16DST_TriggerChannelMap::IDs E16DST_TriggerChannelMap::GetDetectorIDs(int merger_channel_id) const {
  IDs detector_ids;
  if (merger_channel_id < 0 || merger_channel_id >= E16DST_Constant::NMergerChannels * E16DST_Constant::NMergers) {
    detector_ids.type      = Unknown;
    detector_ids.moduleID  = ErrorValue;
    detector_ids.channelID = ErrorValue;
    return detector_ids;
  }
  detector_ids.type      = types[merger_channel_id];
  detector_ids.moduleID  = mod[merger_channel_id];
  detector_ids.channelID = ch[merger_channel_id];
  return detector_ids;
}
