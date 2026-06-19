#_______________________________________________________________________________
set(TARGET_LIB E16DST)

add_library(${TARGET_LIB}
  E16DST_DST0.cc;
  E16DST_GTRConnection.cc;
  E16DST_LGChannelMap.cc;
  E16DST_STSChannelMap.cc;
  E16DST_TriggerChannelMap.cc;
  HBD_ChannelManager.cc;
  E16DST_DST0EventBuilder.cc;
  E16DST_File.cc;
  E16DST_STSChannelMapManager.cc;
)

target_include_directories(${TARGET_LIB} PRIVATE
  ${Boost_INCLUDE_DIRS};
  ${CMAKE_SOURCE_DIR};
)

#_______________________________________________________________________________
install(TARGETS
  ${TARGET_LIB};
  ${TARGET_LIB_RUN0B};
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY
  channel_map
  DESTINATION ${CMAKE_INSTALL_DATADIR}
)

