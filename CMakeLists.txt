cmake_minimum_required(VERSION 3.26)

project(file-hash
        VERSION 1.0.0
        DESCRIPTION "File hashing and UUID generation."
        LANGUAGES C
        )

enable_testing()

# "True" source files for the C-file entry points and static library files.
add_subdirectory(src)

# Main program entry-points that make use of the libraries.
add_subdirectory(apps)

# MATLAB specific "out-of-source" folder.
# add_subdirectory(mex)

# creating version header.
add_custom_target(mkversion
        ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/mkversion.cmake)

# add version header dependency to the targets that print out the version.
add_dependencies(uuidgen mkversion)
add_dependencies(hashfile mkversion)

# add tests for CMake.
add_subdirectory(test)