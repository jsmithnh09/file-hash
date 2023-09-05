# UUID CMake.
add_library(uuid STATIC uuid.c ../hashers/md5.c ../hashers/sha1.c)
target_include_directories(uuid PUBLIC ../../include)
target_compile_features(uuid PUBLIC cxx_std_11)
# pragma has bcrypt listed; do we add -lbcrypt here?
if (WIN32 AND MSVC)
    # warning level 4.
    target_compile_options(uuid PUBLIC /W4)
else()
    # additional warnings + optimization. NOTE: glibc may not have "getrandom" depending on the version.
    target_compile_options(uuid PUBLIC -Wall -O2)
endif()