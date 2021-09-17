#install(DIRECTORY
#  fieldmap
#  DESTINATION ${CMAKE_INSTALL_DATADIR}
#)
#
##______________________________________________________
add_library(E16ANA_MagneticFieldMap
  src/E16ANA_MagneticFieldMap.cc
)
