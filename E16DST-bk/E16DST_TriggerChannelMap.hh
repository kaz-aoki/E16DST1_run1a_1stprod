#ifndef E16DST_TRIGGERCHANNELMAP_HH
#define E16DST_TRIGGERCHANNELMAP_HH

#include <string>
#include <vector>

#include "E16DST_Constant.hh"

class E16DST_TriggerChannelMap {
 public:
  enum DetectorType { GTR, HBD, LG, CT, Scaler, Unknown = -1000 };
  enum { ErrorValue = 255 };
  struct IDs { // detector logical id
    DetectorType type;
    int moduleID;
    int channelID;
  };
  E16DST_TriggerChannelMap(const std::string &trg_gtr_file, const std::string &trg_hbd_file, const std::string &trg_drs4_file);
  ~E16DST_TriggerChannelMap(){};
  E16DST_TriggerChannelMap::IDs GetDetectorIDs(int merger_channel_id) const;

 private:
  std::vector<uint8_t>      mod   = std::vector<uint8_t>(E16DST_Constant::NMergers * E16DST_Constant::NMergerChannels);
  std::vector<uint8_t>      ch    = std::vector<uint8_t>(E16DST_Constant::NMergers * E16DST_Constant::NMergerChannels);
  std::vector<DetectorType> types = std::vector<DetectorType>(E16DST_Constant::NMergers * E16DST_Constant::NMergerChannels);
};

#endif // E16DST_TRIGGERCHANNELMAP_HH
