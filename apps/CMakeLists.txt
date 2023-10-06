#############################################################################
# UUIDGEN and HASHFILE apps entries will go into "bin"
#############################################################################
add_executable(uuidgen uuidgen.c)
add_executable(hashfile hashfile.c)
add_executable(cryptrand cryptrand.c)

target_link_libraries(uuidgen PRIVATE uuid)
target_link_libraries(cryptrand PRIVATE uuid)
target_link_libraries(hashfile PRIVATE hashers)

target_include_directories(hashfile  PUBLIC ../include)
target_include_directories(uuidgen   PUBLIC ../include)
target_include_directories(cryptrand PUBLIC ../include)

if (MSVC) # link against -lbcrypt?
    target_compile_options(uuidgen   PUBLIC /W4)
    target_compile_options(hashfile  PUBLIC /W4)
    target_compile_options(cryptrand PUBLIC /W4)
else()
    target_compile_options(uuidgen   PUBLIC -Wall -O2)
    target_compile_options(hashfile  PUBLIC -Wall -O2)
    target_compile_options(cryptrand PUBLIC -Wall -O2)
endif()

install(TARGETS uuidgen hashfile cryptrand
        RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin)
