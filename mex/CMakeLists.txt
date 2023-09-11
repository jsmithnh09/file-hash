cmake_minimum_required(VERSION 3.26)
find_package(Matlab REQUIRED)

# Scoop up the source files and add to the source list.
matlab_add_mex(NAME mex_mfilehash SRC mex_mfilehash.c LINK_TO hashers)
target_include_directories(mex_mfilehash PUBLIC ../include)

# add a MEX for the UUID as well.
matlab_add_mex(NAME mex_uuidrand SRC mex_uuidrand.c LINK_TO uuid)
matlab_add_mex(NAME mex_uuidspace SRC mex_uuidspace.c LINK_TO uuid)
target_include_directories(mex_uuidrand  PUBLIC ../include)
target_include_directories(mex_uuidspace PUBLIC ../include)

# adding install to a "toolbox" folder for artifacts.
install(TARGETS mex_uuidrand mex_mfilehash mex_uuidspace 
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/toolbox)
install(FILES mfilehash.m uuidrand.m uuidspace.m Contents.m 
    DESTINATION ${CMAKE_SOURCE_DIR}/toolbox)
