cmake_minimum_required(VERSION 3.14.7)

project(E16DST1)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${DIR}/../install/bin)
set(LIBRARY_OUTPUT_PATH ${DIR}/../install/lib)
set(CMAKE_INSTALL_PREFIX ${DIR}/../install)
set(CMAKE_INSTALL_DATADIR ${DIR}/../install/share)
set(CMAKE_CURRENT_BINARY_DIR ${DIR}/../build)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT)
if(ROOT_FOUND)
	include(${ROOT_USE_FILE})
endif()

#find_package(Boost COMPONENTS program_options REQUIRED)
#set(Boost_LIBRARY_DIRS /opt/FairSoft/jun19p2/lib64)

include_directories(
	${ROOT_INCLUDE_DIRS}
#	${Boost_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
	include
	include/LG
	include/trigger
  E16DST
  E16ANA_CalibDB/include
  E16ANA_Geometry/include
  E16ANA_Geometry/include/geant4/Geant4
  E16ANA_Geometry/include/geant4/Geant4/CLHEP/Units
)

#link_directories(
#  ${Boost_LIBRARY_DIRS}
#)

link_libraries(
	${ROOT_LIBRARIES}
#	${Boost_LIBRARIES}
#	${Boost_PROGRAM_OPTIONS_LIBRARIES}
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
  E16ANA_CalibDB/src/E16ANA_GTRcalib.cc
)

target_link_libraries(E16ANA
  E16ANA_CalibDB
)

#_______________________________________________________________________________
add_library(E16DST_DST1
	src/E16DST_DST1.cc
  src/E16ANA_GTRAnalyzer2.cc
  src/E16ANA_GTRStripAnalyzer.cc
  src/E16DST_DST1GTRAnalyzerMaker.cxx
  src/E16DST_DST1GTRHitAndClusterFactory.cc
#  src/E16DST_DST1GTRFactory_dst1_detector.cc
  src/E16ANA_GTRPedestal.cc
  src/E16DST_DST1LGFactory.cc
#  src/E16DST_DST1LGFactory_dst1_detector.cc
	src/E16DST_DST1TriggerFactory.cc
)

target_link_libraries(E16DST_DST1
  E16ANA
  E16ANA_GeometryV2
	E16DST
)

#_______________________________________________________________________________
add_executable(dst0_to_dst1 usr/dst0_to_dst1.cc)

target_link_libraries(dst0_to_dst1
	E16ANA_CalibDB
	E16DST
	E16DST_DST1
  libz.so
)

#_______________________________________________________________________________
add_subdirectory(E16ANA_CalibDB)
add_subdirectory(E16ANA_Geometry)
add_subdirectory(E16DST)
