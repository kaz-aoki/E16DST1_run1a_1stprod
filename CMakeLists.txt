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
#  ROOT_GENERATE_DICTIONARY(G__stl_vector_vector
#    LINKDEF LinkDef/LinkDef.h
#  )
endif()

#find_package(Boost COMPONENTS program_options REQUIRED)
#set(Boost_LIBRARY_DIRS /opt/FairSoft/jun19p2/lib64)

#set(CMAKE_MODULE_PATH /home/yokkaich/work/200130/FairSoft/transport/geant4/environments/g4py/cmake/Modules)
#find_package(Geant4 REQUIRED)

include_directories(
	${ROOT_INCLUDE_DIRS}
#	${Boost_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
#  /opt/E16/include/Geant4 # evb
  /ccj/u/E16/include/Geant4 # ccj
	include
  include/SSD
	include/GTR
#	include/GTR_ozawa
#	include/GTR_old
	include/HBD
	include/LG
	include/trigger
	include/straight_track
	include/track
  E16DST
  E16ANA_Basic/include

  include/tmp
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

#add_library(stl_vector_vector
#  LinkDef/stl_vector_vector.cc
##  SHARED G__stl_vector_vector.cc
#)

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
add_library(E16DST_DST1
  src/SSD/E16ANA_SSDAnalyzer.cc
  src/SSD/E16ANA_SSDStripAnalyzer.cc
  src/SSD/E16DST_DST1SSDAnalyzerMaker.cxx
  src/GTR/E16ANA_GTRAnalyzer2.cc
  src/GTR/E16ANA_GTRPedestal.cc
  src/GTR/E16ANA_GTRStripAnalyzer.cc
  src/GTR/E16ANA_GTRAnalyzerMaker.cc
  src/GTR/GTRCheckHist.cc
#  src/GTR_ozawa/E16ANA_GTRAnalyzer2.cc
#  src/GTR_ozawa/E16ANA_GTRPedestal.cc
#  src/GTR_ozawa/E16ANA_GTRStripAnalyzer.cc
#  src/GTR_ozawa/E16DST_DST1GTRAnalyzerMaker.cxx
#  src/GTR_ozawa/GTRCheckHist.cc
#  src/GTR_old/E16ANA_GTRAnalyzer2.cc
#  src/GTR_old/E16ANA_GTRPedestal.cc
#  src/GTR_old/E16ANA_GTRStripAnalyzer.cc
#  src/GTR_old/E16ANA_GTRAnalyzerMaker.cc
#  src/GTR_old/GTRCheckHist.cc
  src/HBD/E16ANA_HBDChannelManager.cc
  src/HBD/E16ANA_HBDDeadChannel.cc
  src/HBD/E16ANA_HBDClusterAnalysis.cc
  src/HBD/E16ANA_HBDCut.cc
  src/HBD/E16ANA_HBDCalibration.cc
  src/HBD/E16ANA_HBDGeometry.cc
  src/HBD/E16ANA_HBDTH2Hex.cc
  src/straight_track/StraightTrackAnalyzerV0.cc
  
	src/E16DST_DST1.cc
  src/E16DST_DST1SSDFactory.cc
  src/E16DST_DST1GTRFactory.cc
#  src/GTR_ozawa/E16DST_DST1GTRFactory.cc
#  src/GTR_old/E16DST_DST1GTRFactory.cc
  src/E16DST_DST1HBDFactory.cc
  src/E16DST_DST1LGFactory.cc
	src/E16DST_DST1TriggerFactory.cc
  src/E16DST_DST1WireTrackFactory.cc
	src/E16DST_DST1TrackFactory.cc
)

target_link_libraries(E16DST_DST1
#  stl_vector_vector
  E16ANA
	E16DST
)

#_______________________________________________________________________________
add_library(E16ANA_Track
  src/tmp/E16ANA_TrackAnalyzerFromTree.cc
)

target_link_libraries(E16ANA_Track
  E16DST_DST1
)

#_______________________________________________________________________________
#add_library(E16ANA_EventMixing
#  src/tmp/E16ANA_EventMixing.cc
#)
#
#target_link_libraries(E16ANA_EventMixing
#  E16DST_DST1
#)
#
##_______________________________________________________________________________
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
#add_executable(lg_check_standalone usr/lg_check_standalone.cc)
#
#target_link_libraries(lg_check_standalone
#       E16DST_DST1
##E16ANA_CalibDB
#       E16ANA_Basic
#       E16DST
#       E16ANA
#)
#_______________________________________________________________________________
add_executable(dst0_to_dst1_trigger_check usr/dst0_to_dst1_trigger_check.cc)

target_link_libraries(dst0_to_dst1_trigger_check
	E16ANA_Basic
  E16DST_DST1
)

#_______________________________________________________________________________
add_executable(run_StraightTrackAnalyzer usr/run_StraightTrackAnalyzer.cc)

target_link_libraries(run_StraightTrackAnalyzer
	E16DST
	E16DST_DST1
)

#_______________________________________________________________________________
add_executable(tmp_track_analyzer_one_file usr/tmp_track_analyzer_one_file.cc)

target_link_libraries(tmp_track_analyzer_one_file
	E16ANA_Track
)

#_______________________________________________________________________________
add_executable(tmp_track_analyzer usr/tmp_track_analyzer.cc)

target_link_libraries(tmp_track_analyzer
	E16ANA_Track
)

##_______________________________________________________________________________
#add_executable(tmp_event_mixing usr/tmp_event_mixing.cc)
#
#target_link_libraries(tmp_event_mixing
#	E16ANA_EventMixing
#)
#
##_______________________________________________________________________________
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
#add_executable(read_test_gtr usr/read_test_gtr.cc)
#
#target_link_libraries(read_test_gtr
#  E16DST_DST1
#)
#
#_______________________________________________________________________________
add_subdirectory(E16ANA_Basic)
add_subdirectory(E16DST)
