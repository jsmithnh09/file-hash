cmake_minimum_required(VERSION 3.26)
find_package(Matlab REQUIRED)


file(GLOB_RECURSE hash_mex_cfiles ${CMAKE_SOURCE_DIR}/src/hashers/*.c)

# Scoop up the source files and add to the source list.
matlab_add_mex(NAME mex_mfilehash SRC mex_mfilehash.c ${hash_mex_cfiles})
target_include_directories(mex_mfilehash ${CMAKE_SOURCE_DIR}/src/hashers)

# add a MEX for the UUID as well.
matlab_add_mex(NAME mex_uuidgen SRC mex_uuidgen.c ${CMAKE_SOURCE_DIR}/src/uuid/uuid4.c)
target_include_directories(mex_uuidgen ${CMAKE_SOURCE_DIR}/src/uuid)
