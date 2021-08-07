cmake_minimum_required(VERSION 3.14.7)

project(E16DST1)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${DIR}/../install/bin)
set(LIBRARY_OUTPUT_PATH ${DIR}/../install/lib)
set(CMAKE_INSTALL_DATADIR ${DIR}/../install/share)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT)
if(ROOT_FOUND)
	include(${ROOT_USE_FILE})
	ROOT_GENERATE_DICTIONARY(G__stl_vector_vector LINKDEF include/stl_vector_vector_LinkDef.h)
endif()

include_directories(
	${ROOT_INCLUDE_DIRS}
	include
)

link_libraries(
	${ROOT_LIBRARIES}
)

add_library(E16DST_DST1
	src/E16DST_DST1.cc;
	src/E16DST_DST1TriggerFactory.cc;
)

target_compile_features(E16DST_DST1 PRIVATE cxx_std_17)

target_include_directories(E16DST_DST1 PRIVATE
	${ROOT_INCLUDE_DIRS};
  E16DST
)

target_link_libraries(E16DST_DST1
	E16DST;
)

add_executable(dst0_to_dst1 usr/dst0_to_dst1.cc)
target_include_directories(dst0_to_dst1 PRIVATE
	E16DST
)
target_link_libraries(dst0_to_dst1
	E16DST_DST1
  libz.so
)

add_subdirectory(E16DST)
