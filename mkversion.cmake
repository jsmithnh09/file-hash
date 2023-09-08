#######################################################
#  MKVERSION.CMAKE updates the version header file.
#######################################################

file(STRINGS  "${CMAKE_CURRENT_LIST_DIR}/VERSION"  FILE_HASH_VERSION)
configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/include/version.h.in"
  "${CMAKE_CURRENT_LIST_DIR}/include/version.h"
  )
