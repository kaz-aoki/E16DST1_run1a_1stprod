install(DIRECTORY
  calib_database
  DESTINATION ${CMAKE_INSTALL_DATADIR}
)

#_________________________________________________
add_library(E16ANA_CalibDB
  src/E16ANA_ErrorMessage.cc
  src/E16ANA_CalibDBManager.cc
  src/E16ANA_SSDcalib.cc
)

#_________________________________________________
add_executable(calibSample
  examples/calibSample.cc
)

target_link_libraries(calibSample
  E16ANA_CalibDB
)
