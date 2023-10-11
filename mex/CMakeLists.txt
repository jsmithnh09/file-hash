cmake_minimum_required(VERSION 3.26)
find_package(Matlab REQUIRED)

#-------------------------------------------
# FILEHASH
#-------------------------------------------
matlab_add_mex(NAME mex_mfilehash SRC mex_mfilehash.c LINK_TO hashers)
target_include_directories(mex_mfilehash PUBLIC ../include)

#-------------------------------------------
# UUIDRAND, UUIDSPACE, CRYPTRAND
#-------------------------------------------
matlab_add_mex(NAME mex_uuidrand SRC mex_uuidrand.c LINK_TO uuid)
matlab_add_mex(NAME mex_uuidspace SRC mex_uuidspace.c LINK_TO uuid)
matlab_add_mex(NAME mex_cryptrand SRC mex_cryptrand.c LINK_TO uuid)
target_include_directories(mex_uuidrand  PUBLIC ../include)
target_include_directories(mex_uuidspace PUBLIC ../include)
target_include_directories(mex_cryptrand PUBLIC ../include)

#-------------------------------------------
# BLOWFISH
#-------------------------------------------
matlab_add_mex(NAME mex_blowfish SRC mex_blowfish.c ../src/blowfish/blowfish.c)
target_include_directories(mex_blowfish PUBLIC ../src/blowfish)

# adding install to a "toolbox" folder for artifacts.
install(TARGETS mex_uuidrand mex_mfilehash mex_uuidspace mex_cryptrand mex_blowfish
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/toolbox)
install(FILES mfilehash.m cryptrand.m uuidrand.m uuidspace.m Contents.m 
    DESTINATION ${CMAKE_SOURCE_DIR}/toolbox)
