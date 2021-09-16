install(DIRECTORY
  calib_database
  DESTINATION ${CMAKE_INSTALL_DATADIR}
)

#_________________________________________________
add_library(E16ANA_CalibDB
  src/E16ANA_CalibDBManager.cc
)

target_link_libraries(E16ANA_CalibDB
  E16ANA_ErrorMessage
)

#_________________________________________________
add_executable(calibSample
  examples/calibSample.cc
  src/E16ANA_SSDcalib.cc
#  src/E16ANA_GTRcalib.cc
)

target_link_libraries(calibSample
  E16ANA_CalibDB
)
