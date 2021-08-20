#ifndef E16ANA_TRIGGERCOINCIDENCEMAP_HH
#define E16ANA_TRIGGERCOINCIDENCEMAP_HH

#include <array>
#include <string_view>
#include <unordered_map>

#include "E16DST_DST1Constant.hh"

class E16ANA_TriggerCoincidenceMap {
 public:
  struct Map {
    int                  gtr_start_module;
    int                  hbd_start_module;
    std::array<bool, 72> gtr_map;
    std::array<bool, 72> hbd_map;
  };
  E16ANA_TriggerCoincidenceMap(const std::array<std::string_view, 12>& coincidence_map_files, const std::array<std::string_view, 3>& trigger_channel_map_files);
  ~E16ANA_TriggerCoincidenceMap() {}
  E16ANA_TriggerCoincidenceMap::Map& CoincidenceMap(uint16_t _module_id, uint16_t _channel_id, bool _is_mag_field) {
    int key = 100 * _module_id + _channel_id;
    if (_is_mag_field) {
      return maps[1][key];
    } else {
      return maps[0][key];
    }
  }
 private:
  std::array<std::unordered_map<int, E16ANA_TriggerCoincidenceMap::Map>, 2> maps;
};

#endif // E16ANA_TRIGGERCOINCIDENCEMAP_HH
