install(DIRECTORY
  geometry_database
  DESTINATION ${CMAKE_INSTALL_DATADIR}
)

#________________________________________________
add_library(E16ANA_GeometryV2
  src/E16ANA_GeometryV2.cc
  src/E16ANA_Geometry.cc
  src/E16ANA_Transform.cc
)

target_link_libraries(E16ANA_GeometryV2
  E16ANA_ErrorMessage
)

#________________________________________________
add_executable(geometryTest
  examples/geometryTest.cc
)

target_link_libraries(geometryTest
  E16ANA_GeometryV2
)
