cmake_minimum_required(VERSION 3.26)
find_package(Matlab REQUIRED)

# Scoop up the source files and add to the source list.
matlab_add_mex(NAME mex_mfilehash SRC mex_mfilehash.c LINK_TO hashers)
target_include_directories(mex_mfilehash PUBLIC ../include)

# add a MEX for the UUID as well.
matlab_add_mex(NAME mex_uuidgen SRC mex_uuidgen.c LINK_TO uuid)
target_include_directories(mex_uuidgen PUBLIC ../include)