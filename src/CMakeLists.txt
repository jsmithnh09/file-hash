file(GLOB_RECURSE hash_sources hashers/*.c hashers/*.h)
add_definitions(-D_FILE_OFFSET_BITS=64)

add_executable(hashfile hashfile.c ${hash_sources})
if (WIN32)
    message(STATUS "Windows build.")
    target_compile_options(hashfile PUBLIC)
else()
    # Unix. None of this "WinMain" garbage...
    message(STATUS "UNIX build.")
    target_compile_options(hashfile PUBLIC -O2 -Wall)
endif()
target_include_directories(hashfile PUBLIC hashers)