file(GLOB_RECURSE hash_sources hashers/*.c hashers/*.h)
add_definitions(-D_FILE_OFFSET_BITS=64)

add_subdirectory(hashers)
add_subdirectory(uuid)