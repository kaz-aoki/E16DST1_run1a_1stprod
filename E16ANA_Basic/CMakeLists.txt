file(GLOB E16ANA_Basic_SRCS src/*)

add_library(E16ANA_Basic
  ${E16ANA_Basic_SRCS}
)

#________________________________________________
add_executable(calibSample
  usr/calibSample.cc
)

target_link_libraries(calibSample
  E16ANA_Basic
)

#________________________________________________
add_executable(geometryTest
  usr/geometryTest.cc
)

target_link_libraries(geometryTest
  E16ANA_Basic
)

#________________________________________________
add_executable(MakeSSDCalibfile
  usr/MakeSSDCalibfile.cc
)

target_link_libraries(MakeSSDCalibfile
  E16ANA_Basic
)

#________________________________________________
add_executable(rundependentNameTest
  usr/rundependentNameTest.cc
)

target_link_libraries(rundependentNameTest
  E16ANA_Basic
)

#________________________________________________
add_executable(targetInfoTest
  usr/targetInfoTest.cc
)

target_link_libraries(targetInfoTest
  E16ANA_Basic
)

#________________________________________________
add_executable(mockdataIOtestSimple
  usr/mockdataIOtestSimple.cc
)

target_link_libraries(mockdataIOtestSimple
  E16ANA_Basic
)
#________________________________________________
add_executable(FMfieldDump
  usr/FMfieldDump.cc
)

target_link_libraries(FMfieldDump
  E16ANA_Basic
)
