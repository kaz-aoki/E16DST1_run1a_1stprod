add_library(E16ANA_GeometryV2
  src/E16ANA_GeometryV2.cc
  src/E16ANA_Geometry.cc
  src/E16ANA_Transform.cc
)

#________________________________________________
add_executable(geometryTest
  examples/geometryTest.cc
)

target_link_libraries(geometryTest
  E16ANA_GeometryV2
)
