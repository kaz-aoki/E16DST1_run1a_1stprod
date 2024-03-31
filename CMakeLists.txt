cmake_minimum_required(VERSION 3.14.7)

project(E16DST1)

set(CMAKE_CXX_FLAGS "-O2 -lMinuit -lSpectrum")
#set(CMAKE_CXX_FLAGS "-O2 -pg -lMinuit -lSpectrum")
#set(CMAKE_CXX_FLAGS "-O2 -g -lMinuit -lSpectrum")
#set(CMAKE_CXX_FLAGS "-O0 -g -Wall -lMinuit -lSpectrum")
#set(CMAKE_EXE_LINKER_FLAGS "-pg")
#set(CMAKE_SHARED_LINKER_FLAGS "-pg")

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
elseif(${_host_name} MATCHES "^ccj")
   message("-- E16SYS_DIR will be set for ccj servers.")
   set(E16SYS_DIR /ccj/u/E16)
   add_definitions(-DCCJ_CALIB_FILE) # for calib files
endif()
message(STATUS "E16SYS_DIR:  ${E16SYS_DIR}")

add_definitions(-DTRACK_FIND_WO_TARGET) # for Ks

#add_definitions(-DWO_TRACK_FIT)

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
  src/nakasuga/E16ANA_EIDSingleTrackAnalyzer.cc
  src/nakasuga/E16ANA_EIDSingleTrackAnalyzerV2.cc
  src/nakasuga/E16ANA_EIDEfficiency.cc
  src/nakasuga/E16ANA_LGGainCalibwoTrack.cc
  src/nakasuga/E16ANA_LGGainCalibwoTrackRoot.cc
  src/nakasuga/E16ANA_Massw2Gamma.cc
  src/nakasuga/E16ANA_GammaAnalyzer.cc
  src/nakasuga/straightRoot.cc
  src/nakasuga/E16ANA_LGStraightTrackRoot.cc
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
#  src/straight_track/StraightTrackAnalyzerForASDEffwithWireV0.cc
#  src/tmp/SingleTrackAnalyzerForRes.cc
#  src/tmp/AnalyzerResidualHBD.cc
  #src/tmp/EfficiencyCalc.cc
  
	src/E16DST_DST1.cc
  src/E16DST_DST1SSDFactory.cc
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
add_executable(dst0_to_dst1_ct_check usr/dst0_to_dst1_ct_check.cc)

target_link_libraries(dst0_to_dst1_ct_check
	E16DST_DST1
)

# #_______________________________________________________________________________
# add_executable(dst0_to_dst1_all_check usr/dst0_to_dst1_all_check.cc)

# target_link_libraries(dst0_to_dst1_all_check
# 	E16DST_DST1
# #	E16ANA_CalibDB
# 	E16ANA_Basic
# 	E16DST
# 	E16ANA
# )

# #_______________________________________________________________________________
# add_executable(dst0_to_dst1_all_check_hist usr/dst0_to_dst1_all_check_hist.cc)

# target_link_libraries(dst0_to_dst1_all_check_hist
# 	E16DST_DST1
# #	E16ANA_CalibDB
# 	E16ANA_Basic
# 	E16DST
# 	E16ANA
# )

# #_______________________________________________________________________________
# add_executable(dst0_to_dst1_strack_check usr/dst0_to_dst1_strack_check.cc)

# target_link_libraries(dst0_to_dst1_strack_check
# 	E16DST_DST1
# #E16ANA_CalibDB
# 	E16ANA_Basic
# 	E16DST
# 	E16ANA
# )

#_______________________________________________________________________________
add_executable(EIDana_MakeTree_EIDEfficiency usr/tmp/nakasuga/EIDana_MakeTree_EIDEfficiency.cc)

target_link_libraries(EIDana_MakeTree_EIDEfficiency
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(EIDana_MakeTree_EIDEfficiency_woY usr/tmp/nakasuga/EIDana_MakeTree_EIDEfficiency_woY.cc)

target_link_libraries(EIDana_MakeTree_EIDEfficiency_woY
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(EIDana_WaveformEfficiency usr/tmp/nakasuga/EIDana_WaveformEfficiency.cc)

target_link_libraries(EIDana_WaveformEfficiency
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(EIDana_LGHitADC usr/tmp/nakasuga/EIDana_LGHitADC.cc)

target_link_libraries(EIDana_LGHitADC
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(EIDana_ResidualandEfficiency usr/tmp/nakasuga/EIDana_ResidualandEfficiency.cc)

target_link_libraries(EIDana_ResidualandEfficiency
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(EIDana_LGGainCalibwTrack usr/tmp/nakasuga/EIDana_LGGainCalibwTrack.cc)

target_link_libraries(EIDana_LGGainCalibwTrack
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(EIDana_MakeTree_LGGainCalibwoTrack usr/tmp/nakasuga/EIDana_MakeTree_LGGainCalibwoTrack.cc)

target_link_libraries(EIDana_MakeTree_LGGainCalibwoTrack
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(EIDana_LGGainCalibwoTrack_ResidualforLGmix usr/tmp/nakasuga/EIDana_LGGainCalibwoTrack_ResidualforLGmix.cc)

target_link_libraries(EIDana_LGGainCalibwoTrack_ResidualforLGmix
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(EIDana_LGGainCalibwoTrack_ResidualforGTRymix usr/tmp/nakasuga/EIDana_LGGainCalibwoTrack_ResidualforGTRymix.cc)

target_link_libraries(EIDana_LGGainCalibwoTrack_ResidualforGTRymix
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(EIDana_LGGainCalibwoTrack_ResidualforGTRxmix usr/tmp/nakasuga/EIDana_LGGainCalibwoTrack_ResidualforGTRxmix.cc)

target_link_libraries(EIDana_LGGainCalibwoTrack_ResidualforGTRxmix
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(EIDana_LGGainCalibwoTrack_Momentum usr/tmp/nakasuga/EIDana_LGGainCalibwoTrack_Momentum.cc)

target_link_libraries(EIDana_LGGainCalibwoTrack_Momentum
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(EIDana_LGGainCalibwoTrack_LGADCLGmix usr/tmp/nakasuga/EIDana_LGGainCalibwoTrack_LGADCLGmix.cc)

target_link_libraries(EIDana_LGGainCalibwoTrack_LGADCLGmix
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(EIDana_LGGainCalibwoTrack_LGADCGTRymix usr/tmp/nakasuga/EIDana_LGGainCalibwoTrack_LGADCGTRymix.cc)

target_link_libraries(EIDana_LGGainCalibwoTrack_LGADCGTRymix
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(Massw2Gamma usr/tmp/nakasuga/Massw2Gamma.cc)

target_link_libraries(Massw2Gamma
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

# #_______________________________________________________________________________
add_executable(Gammaana_MakeRootPDF usr/tmp/nakasuga/Gammaana_MakeRootPDF.cc)

target_link_libraries(Gammaana_MakeRootPDF
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(Gammaana_MakePDF usr/tmp/nakasuga/Gammaana_MakePDF.cc)

target_link_libraries(Gammaana_MakePDF
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

# _______________________________________________________________________________
add_executable(Gammaana_CodeCheck usr/tmp/nakasuga/Gammaana_CodeCheck.cc)

target_link_libraries(Gammaana_CodeCheck
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

# _______________________________________________________________________________
add_executable(Gammaana_ChargedRatio usr/tmp/nakasuga/Gammaana_ChargedRatio.cc)

target_link_libraries(Gammaana_ChargedRatio
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(LG_MakeHVTable usr/tmp/nakasuga/LG_MakeHVTable.cc)

target_link_libraries(LG_MakeHVTable
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(LG_LEDcheck usr/tmp/nakasuga/LG_LEDcheck.cc)

target_link_libraries(LG_LEDcheck
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(LG_MakePDF usr/tmp/nakasuga/LG_MakePDF.cc)

target_link_libraries(LG_MakePDF
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(mom usr/tmp/nakasuga/mom.cc)

target_link_libraries(mom
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(LG_CheckWaveform usr/tmp/nakasuga/LG_CheckWaveform.cc)

target_link_libraries(LG_CheckWaveform
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(LG_StraightEventMatch usr/tmp/nakasuga/LG_StraightEventMatch.cc)

target_link_libraries(LG_StraightEventMatch
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(LG_StraightResidual usr/tmp/nakasuga/LG_StraightResidual.cc)

target_link_libraries(LG_StraightResidual
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(check_LGProjection usr/tmp/nakasuga/check_LGProjection.cc)

target_link_libraries(check_LGProjection
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(TrackMatchOnlineOffline usr/tmp/nakasuga/TrackMatchOnlineOffline.cc)

target_link_libraries(TrackMatchOnlineOffline
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(TrackMatchOfflineOnline usr/tmp/nakasuga/TrackMatchOfflineOnline.cc)

target_link_libraries(TrackMatchOfflineOnline
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

#_______________________________________________________________________________
add_executable(nevent usr/tmp/nakasuga/nevent.cc)

target_link_libraries(nevent
	E16DST_DST1
#E16ANA_CalibDB
	E16ANA_Basic
	E16DST
	E16ANA
)

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

##--------------------------------------------------------------------------------
##_______________________________________________________________________________
add_executable(run_StraightTrackAnalyzer2D usr/run_StraightTrackAnalyzer2D.cc)

target_link_libraries(run_StraightTrackAnalyzer2D
	E16DST
	E16DST_DST1
)
##--------------------------------------------------------------------------------
##_______________________________________________________________________________
add_executable(run_StraightTrackAnalyzerV2 usr/run_StraightTrackAnalyzerV2.cc)

target_link_libraries(run_StraightTrackAnalyzerV2
	E16DST
	E16DST_DST1
)

##--------------------------------------------------------------------------------


#add_executable(make_gtr_apv_status_file usr/make_gtr_apv_status_file.cc)
#
#target_link_libraries(make_gtr_apv_status_file
#	E16DST
#	E16DST_DST1
#)
#
#
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
add_executable(tmp_draw_dead_region usr/tmp/tmp_draw_dead_region.cc) # need to modify if you want to use it, because of GTRDeadChannel class update

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

##_______________________________________________________________________________
#add_executable(tmp_fit_mock_pair_220616_wrapper
#  usr/tmp/tmp_fit_mock_pair_220616_wrapper.cc
#  usr/tmp/tmp_fit_mock_pair_220616.C
#)
#
#target_link_libraries(tmp_fit_mock_pair_220616_wrapper
#	E16ANA_Basic
#)
#
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
add_executable(track_analyzer_220715_wrapper
  usr/tmp/track_analyzer_220715_wrapper.cc
  usr/tmp/track_analyzer_220715.C
)

target_link_libraries(track_analyzer_220715_wrapper
  E16DST_DST1
)

#_______________________________________________________________________________
add_executable(tmp_check_n_events_220811
  usr/tmp/tmp_check_n_events_220811.cc
)

target_link_libraries(tmp_check_n_events_220811
  E16DST
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
#_______________________________________________________________________________
add_executable(tmp_check_acceptance_220902 usr/tmp/tmp_check_acceptance_220902.cc)

target_link_libraries(tmp_check_acceptance_220902
  E16DST_DST1
  E16ANA_MockTrack
)

#_______________________________________________________________________________
add_executable(check_lorentz_effect_220918_wrapper
  usr/tmp/check_lorentz_effect_220918_wrapper.cc
  usr/tmp/check_lorentz_effect_220918.C
)

target_link_libraries(check_lorentz_effect_220918_wrapper
  E16DST_DST1
)

#_______________________________________________________________________________
add_executable(tmp_list_n_events
  usr/tmp/tmp_list_n_events.cc
)

target_link_libraries(tmp_list_n_events
  E16DST_DST1
)

#_______________________________________________________________________________
add_executable(draw_field_diff_221227
  usr/tmp/draw_field_diff_221227.cc
)

target_link_libraries(draw_field_diff_221227
  E16ANA_Basic
)

#_______________________________________________________________________________
add_executable(tmp_check_track_finding_230106
  usr/tmp/tmp_check_track_finding_230106_wrapper.cc
  usr/tmp/tmp_check_track_finding_230106.C
)

target_link_libraries(tmp_check_track_finding_230106
  E16ANA_Basic
)

##_______________________________________________________________________________
#add_executable(tmp_check_track_230129
#  usr/tmp/tmp_check_track_230129_wrapper.cc
#  usr/tmp/tmp_check_track_230129.C
#)
#
#target_link_libraries(tmp_check_track_230129
#  E16ANA_Basic
#)
#
##_______________________________________________________________________________
#add_executable(tmp_make_tfile_from_mock_data_230131
#  usr/tmp/tmp_make_tfile_from_mock_data_230131.cc
#)
#
#target_link_libraries(tmp_make_tfile_from_mock_data_230131
#  E16ANA_Basic
#)
#
##_______________________________________________________________________________
#add_executable(refit_track_230207
#  usr/tmp/refit_track_230207_wrapper.cc
#  usr/tmp/refit_track_230207.C
#)
#
#target_link_libraries(refit_track_230207
#  E16ANA_Basic
#)
#
##_______________________________________________________________________________
#add_executable(sanford_wang
#  usr/tmp/sanford_wang.cc
#)
#
#target_link_libraries(sanford_wang
#  E16ANA_Basic
#  E16DST_DST1
#)
#
#_______________________________________________________________________________
add_subdirectory(E16ANA_Basic)
add_subdirectory(E16DST)
