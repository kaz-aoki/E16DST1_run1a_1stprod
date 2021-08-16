#include "E16DST_TriggerCoincidenceMap.hh"

#include <array>
#include <fstream>
#include <iostream>
#include <string>

#include "E16DST_DST1Constant.hh"
#include "E16DST_TriggerChannelMap.hh"

E16DST_TriggerCoincidenceMap::E16DST_TriggerCoincidenceMap(const std::array<std::string_view, 12>& coincidence_map_files, const std::array<std::string_view, 3>& trigger_channel_map_files) {
  std::array<std::array<std::ifstream, 6>, 2> coe_files;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 6; ++j) {
      coe_files[i][j].open(static_cast<std::string>(coincidence_map_files[6 * i + j]));
    }
  }
  auto channel_map = E16DST_TriggerChannelMap(static_cast<std::string>(trigger_channel_map_files[0]), static_cast<std::string>(trigger_channel_map_files[1]), static_cast<std::string>(trigger_channel_map_files[2]));
  for (int is_mag = 0; is_mag < 2; ++is_mag) {
    for (int lg_sfp = 0; lg_sfp < 6; ++lg_sfp) {
      if (!coe_files[is_mag][lg_sfp]) {
        std::cerr << "Invalid trigger coincidence file: " << is_mag << ", " << lg_sfp << std::endl;
        std::exit(1);
      }
      std::string line;
      int n_read = 0;
      while (getline(coe_files[is_mag][lg_sfp], line)) {
        if (n_read < 2) {
          ++n_read;
          continue;
        }
        auto ids = channel_map.GetDetectorIDs(256 * 3 + 64 * lg_sfp + n_read - 2);
        int key = 100 * ids.moduleID + ids.channelID;
        E16DST_TriggerCoincidenceMap::Map map;
        map.gtr_start_module = E16DST_DST1Constant::kGtrCoincidenceStartModule[lg_sfp];
        map.hbd_start_module = E16DST_DST1Constant::kHbdCoincidenceStartModule[lg_sfp];
        map.gtr_map.fill(false);
        map.hbd_map.fill(false);
        int n_gtr_channel;
        auto size = line.size();
        if (size == 120 + 1) {
          n_gtr_channel = 48;
        } else if (size == 144 + 1) {
          n_gtr_channel = 72;
        } else {
          std::cerr << "Invalid input size: " << size << std::endl;
          std::exit(1);
        }
        for (int ch = 0; ch < size; ++ch) {
          bool is_coin;
          if (line[size - 2 - ch] == '1') {
            is_coin = true;
          } else {
            is_coin = false;
          }
          if (ch < n_gtr_channel) {
            map.gtr_map[ch] = is_coin;
          } else {
            map.hbd_map[ch - n_gtr_channel] = is_coin;
          }
        }
        maps[is_mag].emplace(key, map);
        ++n_read;
      }
    }
  }
}
