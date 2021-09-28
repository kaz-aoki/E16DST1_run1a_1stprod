#ifndef E16_DST_DST1_DEFALUT_FILE_PATH_HH
#define E16_DST_DST1_DEFALUT_FILE_PATH_HH

#include <array>
#include <string_view>

static constexpr std::string_view CalibFilePath {"/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/calib_database"};

static constexpr std::string_view GeometryFile {"/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/geometry_database/v2/geometry_Run0b_210226_design.dat"};

//static constexpr std::string_view LGCalibFilePath {"/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/lg_calibfiles"};


static constexpr std::array<std::string_view, 12> CoincidenceMapFiles {"/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/coincidence_map/track3_sym_NoMag_0.coe",
                                                                       "/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/coincidence_map/track3_sym_NoMag_1.coe",
                                                                       "/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/coincidence_map/track3_sym_NoMag_2.coe",
                                                                       "/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/coincidence_map/track3_sym_NoMag_3.coe",
                                                                       "/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/coincidence_map/track3_sym_NoMag_4.coe",
                                                                       "/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/coincidence_map/track3_sym_NoMag_5.coe",
                                                                       "/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/coincidence_map/track3_sym_0.coe",
                                                                       "/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/coincidence_map/track3_sym_1.coe",
                                                                       "/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/coincidence_map/track3_sym_2.coe",
                                                                       "/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/coincidence_map/track3_sym_3.coe",
                                                                       "/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/coincidence_map/track3_sym_4.coe",
                                                                       "/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/coincidence_map/track3_sym_5.coe"};

static constexpr std::array<std::string_view, 3> TriggerChannelMapFiles {"/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/channel_map/Trigger/trgGtr.txt",
                                                                         "/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/channel_map/Trigger/trgHbd.txt",
                                                                         "/ccj/u/kkanno/e16/E16DST1/E16DST1/../install/share/channel_map/Trigger/trgLgc.txt"};

#endif // E16_DST_DST1_DEFAULT_FILE_PATH
