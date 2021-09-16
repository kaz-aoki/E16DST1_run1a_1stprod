add_library(E16ANA_TargetInfo
  src/E16ANA_TargetInfo.cc
)

#_________________________________________________
add_executable(targetInfoTest
  examples/targetInfoTest.cc
)

target_link_libraries(targetInfoTest
  E16ANA_CalibDB
  E16ANA_ErrorMessage
  E16ANA_TargetInfo
)
