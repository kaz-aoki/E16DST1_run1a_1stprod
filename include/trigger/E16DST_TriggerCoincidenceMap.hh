#ifndef E16DST_TRIGGERCOINCIDENCEMAP_HH
#define E16DST_TRIGGERCOINCIDENCEMAP_HH

#include <array>
#include <string_view>
#include <unordered_map>

#include "E16DST_DST1Constant.hh"

class E16DST_TriggerCoincidenceMap {
 public:
  struct Map {
    int                  gtr_start_module;
    int                  hbd_start_module;
    std::array<bool, 72> gtr_map;
    std::array<bool, 72> hbd_map;
  };
//  E16DST_TriggerCoincidenceMap(const std::string& map_w_mag_0,  const std::string& map_w_mag_1,  const std::string& map_w_mag_2,  const std::string& map_w_mag_3,  const std::string& map_w_mag_4,  const std::string& map_w_mag_5,
//                               const std::string& map_wo_mag_0, const std::string& map_wo_mag_1, const std::string& map_wo_mag_2, const std::string& map_wo_mag_3, const std::string& map_wo_mag_4, const std::string& map_wo_mag_5,
//                               const std::string& gtr_channel_map, const std::string& hbd_channel_map, const std::string& lg_channel_map);
//  E16DST_TriggerCoincidenceMap(const std::array<std::string, 12>& coincidence_map_files, const std::array<std::string, 3>& trigger_channel_map_files);
  E16DST_TriggerCoincidenceMap(const std::array<std::string_view, 12>& coincidence_map_files, const std::array<std::string_view, 3>& trigger_channel_map_files);
  ~E16DST_TriggerCoincidenceMap() {}
  E16DST_TriggerCoincidenceMap::Map CoincidenceMap(uint16_t _module_id, uint16_t _channel_id, bool _is_mag_field) {
    int key = 100 * _module_id + _channel_id;
    if (_is_mag_field) {
      return maps[0][key];
    } else {
      return maps[1][key];
    }
  }
 private:
  std::array<std::unordered_map<int, E16DST_TriggerCoincidenceMap::Map>, 2> maps;
};

#endif // E16DST_TRIGGERCOINCIDENCEMAP_HH
