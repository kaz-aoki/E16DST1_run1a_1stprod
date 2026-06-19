cmake_minimum_required(VERSION 3.14.7)

project(E16DST1)

set(CMAKE_CXX_FLAGS "-O2 -lMinuit -lSpectrum")
#set(CMAKE_CXX_FLAGS "-O2 -pg -lMinuit -lSpectrum")
#set(CMAKE_CXX_FLAGS "-O2 -g -lMinuit -lSpectrum")
#set(CMAKE_CXX_FLAGS "-O0 -g -Wall -lMinuit -lSpectrum")
#set(CMAKE_EXE_LINKER_FLAGS "-pg")
#set(CMAKE_SHARED_LINKER_FLAGS "-pg")

set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../build)
#if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../install)
#endif()
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


#add_definitions(-DTMP_NIM_TRIGGER) # for NIM trigger

find_package(Boost)
find_package(Boost COMPONENTS iostreams; thread;)
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_LIBRARIES:    ${Boost_LIBRARIES}")

cmake_host_system_information(RESULT _host_name QUERY HOSTNAME)
message("-- Building host is ${_host_name}")
if(${_host_name} MATCHES "^e16")
   message("-- E16SYS_DIR will be set for e16 servers.")
   set(E16SYS_DIR /opt/E16)
   set(E16_DB_DIR /e16/u/E16/database)
elseif(${_host_name} MATCHES "^ccj")
   message("-- E16SYS_DIR will be set for ccj servers.")
   set(E16SYS_DIR /ccj/u/E16)
   set(E16_DB_DIR /ccj/u/E16/database)
   add_definitions(-DCCJ_CALIB_FILE) # for calib files
elseif(${_host_name} MATCHES "cc.kek.jp$")
   message("-- E16SYS_DIR will be set for kekcc servers.")
   set(E16SYS_DIR /opt/E16)
   set(E16_DB_DIR /ccj/u/E16/database)
   add_definitions(-DCCJ_CALIB_FILE) # for calib files
endif()
message(STATUS "E16SYS_DIR:  ${E16SYS_DIR}")
message(STATUS "E16_DB_DIR:  ${E16_DB_DIR}")


#add_definitions(-DTRACK_FIND_WO_TARGET) # \\ common for wire and three targets for straight track, 
# *caution just a finding, not fitting

#tracking //murakmai
#add_definitions(-DNoExist_SSD) # //turn on this if you do not have silicon trackers as a tracking point, like Run0d 
add_definitions(-DUseSTS) # //turn on this if you have sts, like Run0e
add_definitions(-DSTS_DO_CLUSTERING) # //turn on this if you do not have ssd as a tracking point, like Run0d 
#add_definitions(-DSTS_DO_CLUSTERING) # //turn on this if you want STS clustering (Run0e)
#add_definitions(-DWIRE_STS_TRACK) # //turn on this if you want STS clustering (Run0e)
#add_definitions(-DREMOVE_GTR100) # 
#add_definitions(-DREMOVE_GTR200) # 
#add_definitions(-DREMOVE_GTR300) # 
#add_definitions(-DEFFICIENCY_EVAL) # //no used 



#add_definitions(-DWO_TRACK_FIT)
#add_definitions(-DWIRE_INCLUDE_TRACKING) #include wire for tracking 


# embedding
#add_definitions(-DTRACK_EFF_CHECK)
#add_definitions(-DREMOVE_REAL_HIT)
#add_definitions(-DWO_LAYER_EFF) # remove timing correlation cut between GTR x and y (for mock data)
##add_definitions(-DSIM_DST1_GEOM_CHECK) # tmp. print position for check

# event mixing
#add_definitions(-DDST1_EVENT_MIX)
#add_definitions(-DMIX_SSD)
#add_definitions(-DMIX_GTR100)
#add_definitions(-DMIX_GTR200)
#add_definitions(-DMIX_GTR300)

include_directories(
  ${ROOT_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${E16SYS_DIR}/include
  ${E16SYS_DIR}/include/Geant4
 include
  include/SSD
	include/GTR
#	include/GTR_ozawa
	include/HBD
	include/LG
	include/CT
	include/nakasuga
#	include/res
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
  ${Boost_LIBRARY_DIRS}
  ${E16SYS_DIR}/lib64-gcc8/clhep
)

link_libraries(
  ${ROOT_LIBRARIES}
  ${Boost_LIBRARIES}
#	${Boost_PROGRAM_OPTIONS_LIBRARIES}
  libG4clhep.so
  libHepPDT.so
  libHepPID.so
	libz.so
  -lGeom
  -lMatrix
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
  src/LG/E16ANA_LGOnlineAnalyzer.cc
  src/LG/E16ANA_LGCheckHist.cc
  src/LG/E16ANA_LGProjection.cc
  src/CT/E16ANA_CTBasic.cc
  src/CT/E16ANA_CTWaveform.cc
  src/CT/E16ANA_CTCheckHist.cc
  src/CT/E16ANA_LGCTOnlineAnalyzer.cc
  src/trigger/E16ANA_TriggerCalib.cc
  src/trigger/E16ANA_TriggerCoincidenceMap.cc
  src/track/E16ANA_TrackCandidate.cc
  src/STS/E16ANA_STSGeometry.cc
#    src/STS/E16ANA_STSGlobalGeometry.cc
  src/STS/E16ANA_STSEventDisplay.cc
  src/STS/E16ANA_EventDisplay.cc
)


#add_library(E16DST_DSTN
#	src/tmp_murakami/E16DSTN_ResEffAna.cc
#)




target_link_libraries(E16ANA
  E16ANA_Basic
#  -lMatrix
#  -lGeom
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
  src/nakasuga/E16ANA_EIDSingleTrackAnalyzer.cc
  src/nakasuga/E16ANA_EIDSingleTrackAnalyzerV2.cc
  src/nakasuga/E16ANA_EIDEfficiency.cc
  src/nakasuga/E16ANA_LGGainCalibwoTrack.cc
  src/nakasuga/E16ANA_LGGainCalibwoTrackRoot.cc
  src/nakasuga/E16ANA_Massw2Gamma.cc
  src/nakasuga/E16ANA_GammaAnalyzer.cc
  src/nakasuga/straightRoot.cc
  src/nakasuga/E16ANA_LGStraightTrackRoot.cc
  src/nakasuga/E16ANA_HBDADCwoTrack.cc
  src/nakasuga/CoincidenceMapWithLG.cc
#  src/res/AnalyzerResidualHBD.cc
#  src/res/AnalyzerTrackSelection.cc
#  src/res/SingleTrackAnalyzerForRes.cc
#  src/res/GainCalibwoTrack.cc
#  src/res/RootGainCalibwoTrack.cc
  src/straight_track/StraightTrackAnalyzerV0.cc
  src/straight_track/E16ANA_StraightTrackNameSpace.cc
  src/straight_track/E16ANA_StraightTrack.cc
  src/straight_track/E16ANA_StraightTrackCandidate.cc
  src/straight_track/E16ANA_StraightMultiTrack.cc
  src/straight_track/E16ANA_StraightStepTrack.cc
#  src/straight_track/StraightTrackAnalyzerForASDEffwithWireV0.cc
#  src/tmp/SingleTrackAnalyzerForRes.cc
#  src/tmp/AnalyzerResidualHBD.cc
  #src/tmp/EfficiencyCalc.cc

	src/E16DST_DST1.cc
  src/E16DST_DST1SSDFactory.cc
  src/E16DST_DST1STSFactory.cc
  src/STS/E16ANA_STSAnalyzer.cc
  src/E16DST_DST1GTRFactory.cc
  src/E16DST_DST1GTRFactory_ExOneGTR.cc
#  src/GTR_ozawa/E16DST_DST1GTRFactory.cc
  src/E16DST_DST1HBDFactory.cc
  src/E16DST_DST1LGFactory.cc
  src/E16DST_DST1StraightTrackFactory.cc
#  src/E16DST_DST1StraightTrackFactorywoGTR300.cc
	src/E16DST_DST1TriggerFactory.cc
  src/E16DST_DST1WireTrackFactory.cc
 # src/E16DST_DST1WireTrackFactorywoGTR300.cc
	src/E16DST_DST1TrackFactory.cc
	src/tmp_murakami/E16DSTN_PosCorrection.cc
	src/tmp_murakami/E16DSTN_ReadStraightTree.cc
	src/tmp_murakami/E16DSTN_ReStraightV2.cc
	src/tmp_murakami/E16DSTN_ReStraightV2_wire.cc
)



target_link_libraries(E16DST_DST1
	E16ANA
	E16DST
#	-lMatrix
#	-lGeom
)

#_______________________________________________________________________________
#add_library(E16ANA_Track
#  src/tmp_ichikawa/E16ANA_TrackAnalyzerFromTreeV2.cc
##)
##
#target_link_libraries(E16ANA_Track
#  E16DST_DST1
#)

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
add_executable(dst0_to_dst1_trigger_check usr/dst0_to_dst1_trigger_check.cc)

target_link_libraries(dst0_to_dst1_trigger_check
	E16ANA_Basic
  E16DST_DST1
  E16ANA_MockTrack
)

#_______________________________________________________________________________



#_______________________________________________________________________________
add_subdirectory(E16ANA_Basic)
add_subdirectory(E16DST)
