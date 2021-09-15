cmake_minimum_required(VERSION 3.14.7)

project(E16DST1)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${DIR}/../install/bin)
set(LIBRARY_OUTPUT_PATH ${DIR}/../install/lib)
set(CMAKE_INSTALL_PREFIX ${DIR}/../install)
set(CMAKE_INSTALL_DATADIR ${DIR}/../install/share)
set(CMAKE_CURRENT_BINARY_DIR ${DIR}/../build)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

set(CMAKE_CXX_FLAGS -lMinuit)
find_package(ROOT)
if(ROOT_FOUND)
	include(${ROOT_USE_FILE})
endif()

#find_package(Boost COMPONENTS program_options REQUIRED)
#set(Boost_LIBRARY_DIRS /opt/FairSoft/jun19p2/lib64)

#set(CMAKE_MODULE_PATH /home/yokkaich/work/200130/FairSoft/transport/geant4/environments/g4py/cmake/Modules)
#find_package(Geant4 REQUIRED)

include_directories(
	${ROOT_INCLUDE_DIRS}
#	${Boost_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
	include
	include/LG
	include/trigger
	include/track
  E16DST
  E16ANA_CalibDB/include
  E16ANA_ErrorMessage/include
  E16ANA_Geometry/include
  E16ANA_MagneticFieldMap/include
  E16ANA_RundependentName/include
  E16ANA_TargetInfo/include
  E16ANA_Tracking/include
  E16ANA_Waveform/include
#  /home/yokkaich/work/200130/FairSoft/transport/geant4/source/global/management/include #evb
#  /home/yokkaich/work/200130/FairSoft/transport/geant4/source/externals/clhep/include #evb
  /opt/E16/include/Geant4 # evb
#  /ccj/u/E16/include/Geant4 # ccj
)

link_directories(
  /opt/E16/lib64-gcc8/clhep # evb
#  /ccj/u/E16/lib64 #ccj
#  ${Boost_LIBRARY_DIRS}
)

link_libraries(
	libz.so
 # libG4clhep.so
  ${ROOT_LIBRARIES}
#	${Boost_LIBRARIES}
#	${Boost_PROGRAM_OPTIONS_LIBRARIES}
  libG4clhep.so
#  libHepPDT.so
#  libHepPID.so
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
add_library(E16ANA
  src/LG/E16ANA_LGBasic.cc
  src/LG/E16ANA_LGGeometry.cc
  src/trigger/E16ANA_TriggerCalib.cc
  src/trigger/E16ANA_TriggerCoincidenceMap.cc
  src/track/E16ANA_TrackCandidate.cc
  E16ANA_CalibDB/src/E16ANA_GTRcalib.cc
)

target_link_libraries(E16ANA
  E16ANA_CalibDB
  E16ANA_ErrorMessage
  E16ANA_GeometryV2
  E16ANA_MagneticFieldMap
  E16ANA_RundependentName
  E16ANA_TargetInfo
  E16ANA_Tracking
  E16ANA_Waveform
)

#_______________________________________________________________________________
add_library(E16DST_DST1
	src/E16DST_DST1.cc
  src/E16ANA_GTRAnalyzer2.cc
  src/E16ANA_GTRStripAnalyzer.cc
  src/E16DST_DST1GTRAnalyzerMaker.cxx
  src/E16DST_DST1GTRHitAndClusterFactory.cc
  src/E16ANA_GTRPedestal.cc
  src/E16DST_DST1LGFactory.cc
  src/E16DST_DST1GTRFactory_dst1_detector.cc
#  src/E16DST_DST1LGFactory_dst1_detector.cc
	src/E16DST_DST1TriggerFactory.cc
	src/E16DST_DST1TrackFactory.cc
)

target_link_libraries(E16DST_DST1
  E16ANA
	E16DST
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1 usr/dst0_to_dst1.cc)

target_link_libraries(dst0_to_dst1
	E16ANA_CalibDB
	E16DST
	E16DST_DST1
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_ssd_check usr/dst0_to_dst1_ssd_check.cc)

target_link_libraries(dst0_to_dst1_ssd_check
	E16ANA_CalibDB
	E16DST
	E16DST_DST1
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_gtr_check usr/dst0_to_dst1_gtr_check.cc)

target_link_libraries(dst0_to_dst1_gtr_check
	E16ANA_CalibDB
	E16DST
	E16DST_DST1
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_hbd_check usr/dst0_to_dst1_hbd_check.cc)

target_link_libraries(dst0_to_dst1_hbd_check
	E16ANA_CalibDB
	E16DST
	E16DST_DST1
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_lg_check usr/dst0_to_dst1_lg_check.cc)

target_link_libraries(dst0_to_dst1_lg_check
	E16ANA_CalibDB
	E16DST
	E16DST_DST1
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1_trigger_check usr/dst0_to_dst1_trigger_check.cc)

target_link_libraries(dst0_to_dst1_trigger_check
	E16ANA_CalibDB
	E16DST
	E16DST_DST1
)

#_______________________________________________________________________________
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
add_subdirectory(E16ANA_CalibDB)
add_subdirectory(E16ANA_ErrorMessage)
add_subdirectory(E16ANA_Geometry)
add_subdirectory(E16ANA_MagneticFieldMap)
add_subdirectory(E16ANA_RundependentName)
add_subdirectory(E16ANA_TargetInfo)
add_subdirectory(E16ANA_Tracking)
add_subdirectory(E16ANA_Waveform)
add_subdirectory(E16DST)
