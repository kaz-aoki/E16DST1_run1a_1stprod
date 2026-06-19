#ifndef E16_DST_DST1_DEFALUT_FILE_PATH_HH
#define E16_DST_DST1_DEFALUT_FILE_PATH_HH

#include <array>
#include <string_view>


static constexpr std::string_view CalibFilePath {"/home/had/ymorino/run1a_st/install/calib"};
//static constexpr std::string_view CalibFilePath {"/e16/u/E16/database_ccj_230524/calib"};

//static constexpr std::string_view GeometryFile {"/home/had/ymorino/run0e_st/E16DST1/../install/share/geometry_database/v2/geometry_Run0b_210226_design.dat"};
//static constexpr std::string_view GeometryFile {"/home/had/ymorino/run0e_st/E16DST1/../install/share/database/geometry_database/v2/geometry_Run0b_210226_design.dat"};
//static constexpr std::string_view GeometryFile {"/home/had/ymorino/run0e_st/E16DST1/../install/share/database/geometry_database/v2/geometry_Run0c_211006b.dat"};
//static constexpr std::string_view GeometryFile {"/ccj/u/ymorino/geo/geometry_Run0c_211006b.dat"};
//static constexpr std::string_view GeometryFile {"/ccj/u/E16/database/geometry/v2/geometry_Run0c_211006b_ymorino_220122.dat"};
//static constexpr std::string_view GeometryFile {"/ccj/u/E16/database/geometry/v2/geometry_Run0b_210226_design.dat"};//kekcc 
//static constexpr std::string_view GeometryFile {"/home/had/snagafsa/work/Run1a/E16DST_m/E16DST1/geometry_mod.dat"};
//static constexpr std::string_view GeometryFile {"/home/had/snagafsa/work/Run1a/E16DST_m/E16DST1/geometry_mod_20260122.dat"};
static constexpr std::string_view GeometryFile {"/home/had/ymorino/run1a_st/E16DST1/geometry_mod_20260210.dat"};
//static constexpr std::string_view GeometryFile {"/ccj/u/ymorino/geometry_mod3.dat"};
//static constexpr std::string_view GeometryFile {"/ccj/u/mtomoki/E16/Photogrametry/E16ANA_Photo/geometry/geometry_bfRun0d_011_modified.dat"};

//static constexpr std::string_view MagneticFieldMapFile("/home/had/ymorino/run0e_st/E16DST1/../install/share/fieldmap/Bmap-SKS-block-far-191218-2450A.binary");
//static constexpr std::string_view MagneticFieldMapFile("/e16/u/E16/database/fieldmap/Bmap-SKS-block-far-191218-2450A.binary"); // evb
//static constexpr std::string_view MagneticFieldMapFile("/ccj/u/E16/database/fieldmap/Bmap-SKS-block-far-191218-2450A.binary"); // ccj
static constexpr std::string_view MagneticFieldMapFile("/ccj/u/E16/database/fieldmap/Bmap-SKS-block-far-191218-2450A-rev1.binary"); // ccj


//static constexpr std::string_view LGCalibFilePath {"/home/had/ymorino/run0e_st/E16DST1/../install/share/lg_calibfiles"};

// run0a - 0d
//static constexpr std::array<std::string_view, 12> CoincidenceMapFiles {"/home/had/ymorino/run0e_st/E16DST1/../install/share/coincidence_map/track3_sym_NoMag_0.coe",
//                                                                       "/home/had/ymorino/run0e_st/E16DST1/../install/share/coincidence_map/track3_sym_NoMag_1.coe",
//                                                                       "/home/had/ymorino/run0e_st/E16DST1/../install/share/coincidence_map/track3_sym_NoMag_2.coe",
//                                                                       "/home/had/ymorino/run0e_st/E16DST1/../install/share/coincidence_map/track3_sym_NoMag_3.coe",
//                                                                       "/home/had/ymorino/run0e_st/E16DST1/../install/share/coincidence_map/track3_sym_NoMag_4.coe",
//                                                                       "/home/had/ymorino/run0e_st/E16DST1/../install/share/coincidence_map/track3_sym_NoMag_5.coe",
//                                                                       "/home/had/ymorino/run0e_st/E16DST1/../install/share/coincidence_map/track3_sym_0.coe",
//                                                                       "/home/had/ymorino/run0e_st/E16DST1/../install/share/coincidence_map/track3_sym_1.coe",
//                                                                       "/home/had/ymorino/run0e_st/E16DST1/../install/share/coincidence_map/track3_sym_2.coe",
//                                                                       "/home/had/ymorino/run0e_st/E16DST1/../install/share/coincidence_map/track3_sym_3.coe",
//                                                                       "/home/had/ymorino/run0e_st/E16DST1/../install/share/coincidence_map/track3_sym_4.coe",
//                                                                       "/home/had/ymorino/run0e/run0e_st/E16DST1/../install/share/coincidence_map/track3_sym_5.coe"};
static constexpr std::array<std::string_view, 12> CoincidenceMapFiles {"@CMAKE_INSTALL_DATADIR@/coincidence_map/track_noMag_0.coe",
                                                                       "@CMAKE_INSTALL_DATADIR@/coincidence_map/track_noMag_1.coe",
                                                                       "@CMAKE_INSTALL_DATADIR@/coincidence_map/track_noMag_2.coe",
                                                                       "@CMAKE_INSTALL_DATADIR@/coincidence_map/track_noMag_3.coe",
                                                                       "@CMAKE_INSTALL_DATADIR@/coincidence_map/track_noMag_4.coe",
                                                                       "@CMAKE_INSTALL_DATADIR@/coincidence_map/track_noMag_5.coe",
                                                                       "@CMAKE_INSTALL_DATADIR@/coincidence_map/track_mag_0.coe",
                                                                       "@CMAKE_INSTALL_DATADIR@/coincidence_map/track_mag_1.coe",
                                                                       "@CMAKE_INSTALL_DATADIR@/coincidence_map/track_mag_2.coe",
                                                                       "@CMAKE_INSTALL_DATADIR@/coincidence_map/track_mag_3.coe",
                                                                       "@CMAKE_INSTALL_DATADIR@/coincidence_map/track_mag_4.coe",
                                                                       "@CMAKE_INSTALL_DATADIR@/coincidence_map/track_mag_5.coe"};

static constexpr std::array<std::string_view, 3> TriggerChannelMapFiles {"@CMAKE_INSTALL_DATADIR@/channel_map/Trigger/trgGtr.txt",
                                                                         "@CMAKE_INSTALL_DATADIR@/channel_map/Trigger/trgHbd.txt",
                                                                         "@CMAKE_INSTALL_DATADIR@/channel_map/Trigger/trgDrs4.txt"};


#endif // E16_DST_DST1_DEFAULT_FILE_PATH
