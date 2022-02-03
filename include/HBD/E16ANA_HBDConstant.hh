#ifndef E16ANA_HBDConstant_h
#define E16ANA_HBDConstant_h

#include "E16DST_Constant.hh"

#include <cmath>
#include <vector>

namespace HBD_Board_Constant{
  constexpr double x_board_center = 305.2159; // distance [mm] from the board coodinate origin to the local coodinate origin
  constexpr double y_board_center = 302.9486; // distance [mm] from the board coodinate origin to the local coodinate origin
  constexpr double hex_pad_length = 10.0 + 0.5/std::sqrt(3.); // length of hex. pad (pad electrode of 10 mm + gap of 0.5/sqrt(3) mm)
  constexpr int n_pad_x = 40; // number of hex. pads along x-axis
  constexpr int n_pad_y = 34; // number of hex. pads alogn y-axis
}

namespace HBD_Module_Constant{
  constexpr int module_ids[E16DST_Constant::NModules] = {101, 102, 103, 104, 106, 107, 108, 109};
  constexpr int rotated_module_ids[3] = {101, 102, 104}; // ask Kanno
  constexpr int normal_module_ids[5] = {103, 106, 107, 108, 109}; // ask Kanno
  constexpr int n_chips = 24;//apv25 chips per 2 modules
  constexpr int n_pads = 1400;//hbd pads per module
}

namespace HBD_Circuit_Constant{
  constexpr int apv25_period = 24; //nsec
  constexpr int SRS_ATCA_TDC = 2; //nsec
}

#endif
