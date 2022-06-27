cmake_minimum_required(VERSION 3.14.7)

project(E16DST1)

#set(CMAKE_CXX_FLAGS "-O2 -lMinuit -lSpectrum")
set(CMAKE_CXX_FLAGS "-O2 -pg -lMinuit -lSpectrum")
#set(CMAKE_CXX_FLAGS "-O2 -g -lMinuit -lSpectrum")
set(CMAKE_EXE_LINKER_FLAGS "-pg")
set(CMAKE_SHARED_LINKER_FLAGS "-pg")

set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../build)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../install)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_INSTALL_PREFIX}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_INSTALL_DATADIR ${CMAKE_INSTALL_PREFIX}/share)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT)
if(ROOT_FOUND)
	include(${ROOT_USE_FILE})
endif()

#find_package(Boost COMPONENTS program_options REQUIRED)
#set(Boost_LIBRARY_DIRS /opt/FairSoft/jun19p2/lib64)

#set(CMAKE_MODULE_PATH /home/yokkaich/work/200130/FairSoft/transport/geant4/environments/g4py/cmake/Modules)
#find_package(Geant4 REQUIRED)

add_definitions(-DTRACK_EFF_CHECK)
add_definitions(-DMERGE_TRACK_PAIR)
#add_definitions(-DREMOVE_REAL_HIT)
#add_definitions(-DWO_POS_SMEAR)
#add_definitions(-DSIM_DST1_GEOM_CHECK) # ?

#add_definitions(-DWO_TRACK_FIT)

#add_definitions(-DREQ_HBD_BEFORE_FIT)

include_directories(
	${ROOT_INCLUDE_DIRS}
#	${Boost_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
#  /opt/E16/include/Geant4 # evb
  /ccj/u/E16/include
  /ccj/u/E16/include/Geant4 # ccj
  include
  include/SSD
	include/GTR
#	include/GTR_ozawa
	include/HBD
	include/LG
	include/res
	include/trigger
	include/straight_track
	include/track

  E16DST
  E16ANA_Basic/include
  include/tmp_ichikawa
  include/tmp_mock
  include/tmp_murakami
)

link_directories(
#  ${Boost_LIBRARY_DIRS}
#  /opt/E16/lib64-gcc8/clhep # evb
  /ccj/u/E16/lib64 #ccj
)

link_libraries(
  ${ROOT_LIBRARIES}
#	${Boost_LIBRARIES}
#	${Boost_PROGRAM_OPTIONS_LIBRARIES}
  libG4clhep.so
  libHepPDT.so
  libHepPID.so
	libz.so
)

#_______________________________________________________________________________
install(DIRECTORY
  coincidence_map
#  lg_calibfiles
  DESTINATION ${CMAKE_INSTALL_DATADIR}
)

#_______________________________________________________________________________
#set(DefalutPathFiles
#  include/E16DST_DefalutCoincidenceMapPath.hh
#)
#
#foreach(lvar IN ITEMS ${DefaultPathFiles})
##  configure_file(${lvar}.in ${lvar} @ONLY)
#  configure_file(${lvar}.in ${CMAKE_CURRENT_BINARY_DIR}/${lvar} @ONLY)
#message("CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR}/${lvar})
#endforeach()
configure_file(include/E16DST_DST1DefaultFilePath.hh.in E16DST_DST1DefaultFilePath.hh @ONLY)

#_______________________________________________________________________________
#set_source_files_properties(src/LG/E16ANA_LGBasic.cc PROPERTIES COMPILE_OPTIONS "-lSpectrum")

add_library(E16ANA
#  E16ANA_CalibDB/src/E16ANA_SSDcalib.cc
#  E16ANA_CalibDB/src/E16ANA_GTRcalib.cc
  src/LG/E16ANA_LGBasic.cc
  src/LG/E16ANA_LGGeometry.cc
  src/LG/E16ANA_LGWaveform.cc
  src/LG/E16ANA_LGDeadChannel.cc
  src/LG/E16ANA_LGClustering.cc
  src/trigger/E16ANA_TriggerCalib.cc
  src/trigger/E16ANA_TriggerCoincidenceMap.cc
  src/track/E16ANA_TrackCandidate.cc
)

target_link_libraries(E16ANA
  E16ANA_Basic
)

#_______________________________________________________________________________
file(GLOB E16ANA_SSD_SRCS src/SSD/*)
file(GLOB E16ANA_GTR_SRCS src/GTR/*)
file(GLOB E16ANA_HBD_SRCS src/HBD/*)

add_library(E16DST_DST1
#  src/SSD/E16ANA_SSDAnalyzer.cc
#  src/SSD/E16ANA_SSDStripAnalyzer.cc
#  src/SSD/E16DST_DST1SSDAnalyzerMaker.cxx
#  src/GTR/E16ANA_GTRAnalyzer2.cc
#  src/GTR/E16ANA_GTRPedestal.cc
#  src/GTR/E16ANA_GTRStripAnalyzer.cc
#  src/GTR/E16ANA_GTRAnalyzerMaker.cc
#  src/GTR/E16ANA_GTRStatus.cc
#  src/GTR/GTRCheckHist.cc
##  src/GTR_ozawa/E16ANA_GTRAnalyzer2.cc
##  src/GTR_ozawa/E16ANA_GTRPedestal.cc
##  src/GTR_ozawa/E16ANA_GTRStripAnalyzer.cc
##  src/GTR_ozawa/E16DST_DST1GTRAnalyzerMaker.cxx
##  src/GTR_ozawa/GTRCheckHist.cc
#  src/HBD/E16ANA_HBDChannelManager.cc
#  src/HBD/E16ANA_HBDDeadChannel.cc
#  src/HBD/E16ANA_HBDClusterAnalysis.cc
#  src/HBD/E16ANA_HBDCut.cc
#  src/HBD/E16ANA_HBDCalibration.cc
#  src/HBD/E16ANA_HBDGeometry.cc
#  src/HBD/E16ANA_HBDTH2Hex.cc
#  src/HBD/E16ANA_WaveformFitterCRRC.cc
  ${E16ANA_SSD_SRCS}
  ${E16ANA_GTR_SRCS}
  ${E16ANA_HBD_SRCS}
  src/res/AnalyzerResidualHBD.cc
  src/res/AnalyzerTrackSelection.cc
  src/res/SingleTrackAnalyzerForRes.cc
  src/straight_track/StraightTrackAnalyzerV0.cc
#  src/straight_track/StraightTrackAnalyzerForASDEffwithWireV0.cc
#  src/tmp/SingleTrackAnalyzerForRes.cc
#  src/tmp/AnalyzerResidualHBD.cc
  #src/tmp/EfficiencyCalc.cc
  
	src/E16DST_DST1.cc
  src/E16DST_DST1SSDFactory.cc
  src/E16DST_DST1GTRFactory.cc
#  src/GTR_ozawa/E16DST_DST1GTRFactory.cc
  src/E16DST_DST1HBDFactory.cc
  src/E16DST_DST1LGFactory.cc
  src/E16DST_DST1StraightTrackFactory.cc
  src/E16DST_DST1StraightTrackFactorywoGTR300.cc
	src/E16DST_DST1TriggerFactory.cc
  src/E16DST_DST1WireTrackFactory.cc
  src/E16DST_DST1WireTrackFactorywoGTR300.cc

	src/E16DST_DST1TrackFactory.cc
)

target_link_libraries(E16DST_DST1
  E16ANA
	E16DST
)

#_______________________________________________________________________________
add_library(E16ANA_Track
  src/tmp_ichikawa/E16ANA_TrackAnalyzerFromTreeV2.cc
)

target_link_libraries(E16ANA_Track
  E16DST_DST1
)

#_______________________________________________________________________________
add_library(E16ANA_MockTrack
  src/tmp_mock/E16ANA_MakeDummyDST1.cc
#  src/tmp_mock/mockdataIOtestSimple.cc
)

target_link_libraries(E16ANA_MockTrack
  E16DST_DST1
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1 usr/dst0_to_dst1.cc)

target_link_libraries(dst0_to_dst1
	E16DST_DST1
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_ssd_check usr/dst0_to_dst1_ssd_check.cc)

target_link_libraries(dst0_to_dst1_ssd_check
	E16DST_DST1
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_gtr_check usr/dst0_to_dst1_gtr_check.cc)

target_link_libraries(dst0_to_dst1_gtr_check
	E16DST_DST1
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_hbd_check usr/dst0_to_dst1_hbd_check.cc)

target_link_libraries(dst0_to_dst1_hbd_check
	E16DST_DST1
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_hbd_w_wf usr/dst0_to_dst1_hbd_w_wf.cc)

target_link_libraries(dst0_to_dst1_hbd_w_wf
	E16DST_DST1
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_hbd_w_wf_CRRCfit usr/dst0_to_dst1_hbd_w_wf_CRRCfit.cc)

target_link_libraries(dst0_to_dst1_hbd_w_wf_CRRCfit
        E16DST_DST1
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_hbd_220416 usr/dst0_to_dst1_hbd_220416.cc)

target_link_libraries(dst0_to_dst1_hbd_220416
        E16DST_DST1
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_hbd_wf_check usr/dst0_to_dst1_hbd_wf_check.cc)

target_link_libraries(dst0_to_dst1_hbd_wf_check
	E16DST_DST1
)

#_______________________________________________________________________________
add_executable(hbd_dead_ch_check usr/hbd_dead_ch_check.cc)

target_link_libraries(hbd_dead_ch_check
	E16DST_DST1
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_lg_check usr/dst0_to_dst1_lg_check.cc)

target_link_libraries(dst0_to_dst1_lg_check
	E16DST_DST1
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_all_check usr/dst0_to_dst1_all_check.cc)

target_link_libraries(dst0_to_dst1_all_check
	E16DST_DST1
#	E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_all_check_hist usr/dst0_to_dst1_all_check_hist.cc)

target_link_libraries(dst0_to_dst1_all_check_hist
	E16DST_DST1
#	E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_strack_check usr/dst0_to_dst1_strack_check.cc)

target_link_libraries(dst0_to_dst1_strack_check
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(DrawForTrackSelection usr/DrawForTrackSelection.cc)

target_link_libraries(DrawForTrackSelection
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(MkTreeForTrackSelection usr/MkTreeForTrackSelection.cc)

target_link_libraries(MkTreeForTrackSelection
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

##_______________________________________________________________________________
#add_executable(lg_check_standalone usr/lg_check_standalone.cc)
#
#target_link_libraries(lg_check_standalone
#       E16DST_DST1
##E16ANA_CalibDB
#       E16ANA_Basic
#       E16DST
#       E16ANA
#)
#
#_______________________________________________________________________________
add_executable(dst0_to_dst1_trigger_check usr/dst0_to_dst1_trigger_check.cc)

target_link_libraries(dst0_to_dst1_trigger_check
	E16ANA_Basic
  E16DST_DST1
  E16ANA_MockTrack
)

#_______________________________________________________________________________
add_executable(gtr_deadch_check usr/gtr_deadch_check.cc)

target_link_libraries(gtr_deadch_check
	E16DST
	E16DST_DST1
)

#_______________________________________________________________________________
add_executable(run_CalcASDEffUsingStraightTrack usr/run_CalcASDEffUsingStraightTrack.cc)

target_link_libraries(run_CalcASDEffUsingStraightTrack
	E16DST
	E16DST_DST1
)

##_______________________________________________________________________________
#add_executable(run_GTRResidualCalc usr/run_GTRResidualCalc.cc)
#
#target_link_libraries(run_GTRResidualCalc
#	E16DST
#	E16DST_DST1
#)
#
##_______________________________________________________________________________
add_executable(run_StraightTrackAnalyzer usr/run_StraightTrackAnalyzer.cc)

target_link_libraries(run_StraightTrackAnalyzer
	E16DST
	E16DST_DST1
)

#_______________________________________________________________________________
#add_executable(run_HBDLGResidualCalcForEff usr/run_HBDLGResidualCalcForEff.cc)
#
#target_link_libraries(run_HBDLGResidualCalcForEff
#	E16DST
#E16DST_DST1
#)
##_______________________________________________________________________________
#add_executable(run_HBDLGResidualCalc usr/run_HBDLGResidualCalc.cc)
#
#target_link_libraries(run_HBDLGResidualCalc
#	E16DST
#E16DST_DST1
#)
##_______________________________________________________________________________
add_executable(run_EfficiencyCalcV2 usr/run_EfficiencyCalcV2.cc)

target_link_libraries(run_EfficiencyCalcV2
	E16DST
	E16DST_DST1
)
#_______________________________________________________________________________
###_______________________________________________________________________________
add_executable(run_ASDEfficiencyCalcWMag usr/run_ASDEfficiencyCalcWMag.cc)

target_link_libraries(run_ASDEfficiencyCalcWMag
	E16DST
	E16DST_DST1
)
#_______________________________________________________________________________

#_______________________________________________________________________________
#add_executable(run_EfficiencyCalc usr/run_EfficiencyCalc.cc)
#
#target_link_libraries(run_EfficiencyCalc
#	E16DST
#	E16DST_DST1
#)
#
##_______________________________________________________________________________
add_executable(tmp_track_analyzer_one_file usr/tmp_track_analyzer_one_file.cc)

target_link_libraries(tmp_track_analyzer_one_file
	E16ANA_Track
)

##_______________________________________________________________________________
#add_executable(run_GTRResidualCalc usr/run_GTRResidualCalc.cc)
#
#target_link_libraries(run_GTRResidualCalc
#	E16DST
#	E16DST_DST1
#)
#
##_______________________________________________________________________________
#add_executable(tmp_track_analyzer usr/tmp_track_analyzer.cc)
#
#target_link_libraries(tmp_track_analyzer
#	E16ANA_Track
#)

#_______________________________________________________________________________
#add_executable(tmp_gtr usr/tmp_gtr.cc)
#
#target_link_libraries(tmp_gtr
#	E16DST_DST1
#)
#
##_______________________________________________________________________________
#add_executable(write_test usr/write_test.cc)
#
#target_link_libraries(write_test
#  E16DST_DST1
#)
#
##_______________________________________________________________________________
#add_executable(read_test usr/read_test.cc)
#
#target_link_libraries(read_test
#  E16DST_DST1
#)
#
##_______________________________________________________________________________
#add_executable(write_test_gtr usr/write_test_gtr.cc)
#
#target_link_libraries(write_test_gtr
#  E16DST_DST1
#)
#
##_______________________________________________________________________________
#add_executable(tmp_check_coin_map usr/tmp_check_coin_map.cc)
#
#target_link_libraries(tmp_check_coin_map
#  E16DST_DST1
#)
#
##_______________________________________________________________________________
#add_executable(read_test_gtr usr/read_test_gtr.cc)
#
#target_link_libraries(read_test_gtr
#  E16DST_DST1
#)
#
#_______________________________________________________________________________
add_executable(check_position_resolution usr/tmp/check_position_resolution.cc)

target_link_libraries(check_position_resolution
  E16DST_DST1
)

#_______________________________________________________________________________
add_executable(tmp_draw_dead_region usr/tmp/tmp_draw_dead_region.cc)

target_link_libraries(tmp_draw_dead_region
	E16ANA_Basic
  E16DST_DST1
  E16ANA_MockTrack
)

#_______________________________________________________________________________
add_executable(calc_ssd_rate usr/tmp/calc_ssd_rate.cc)

target_link_libraries(calc_ssd_rate
	E16ANA_Basic
  E16DST
)

#_______________________________________________________________________________
add_executable(tmp_fit_mock_pair_220616_wrapper
  usr/tmp/tmp_fit_mock_pair_220616_wrapper.cc
  usr/tmp/tmp_fit_mock_pair_220616.C
)

target_link_libraries(tmp_fit_mock_pair_220616_wrapper
	E16ANA_Basic
)

#_______________________________________________________________________________
add_executable(tmp_fit_mock_pair_from_dst1_220618_wrapper
  usr/tmp/tmp_fit_mock_pair_from_dst1_220618_wrapper.cc
  usr/tmp/tmp_fit_mock_pair_from_dst1_220618.C
)

target_link_libraries(tmp_fit_mock_pair_from_dst1_220618_wrapper
	E16ANA_Basic
)

#_______________________________________________________________________________
add_executable(tmp_fit_mock_pair_from_dst1_drawer_220620_wrapper
  usr/tmp/tmp_fit_mock_pair_from_dst1_drawer_220620_wrapper.cc
  usr/tmp/tmp_fit_mock_pair_from_dst1_drawer_220620.C
)

#_______________________________________________________________________________
add_executable(tmp_check_pos_smear_220627_wrapper
  usr/tmp/tmp_check_pos_smear_220627_wrapper.cc
  usr/tmp/tmp_check_pos_smear_220627.C
)

#_______________________________________________________________________________
#add_executable(tmp_gtr_deadch_check usr/tmp/tmp_gtr_deadch_check.cc)
#
#target_link_libraries(tmp_gtr_deadch_check
#	E16ANA_Basic
#  E16DST_DST1
#)
#
##_______________________________________________________________________________
#add_executable(draw_dead_channel_map tmp/draw_dead_channel_map.cc)
#
#target_link_libraries(draw_dead_channel_map
#  E16DST_DST1
#)
#
##_______________________________________________________________________________
add_subdirectory(E16ANA_Basic)
add_subdirectory(E16DST)
