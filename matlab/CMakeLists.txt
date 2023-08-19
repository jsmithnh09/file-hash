cmake_minimum_required(VERSION 3.26)
find_package(Matlab REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src/hashers)
file(GLOB_RECURSE hash_mex_cfiles ${CMAKE_SOURCE_DIR}/src/hashers/*.c)

# Scoop up the source files and add to the source list.
matlab_add_mex(NAME mex_mfilehash SRC mex_mfilehash.c ${hash_mex_cfiles})
