cmake_minimum_required(VERSION 3.26)

project(file-hash
        VERSION 1.0.0
        DESCRIPTION "File hashing and UUID generation."
        LANGUAGES C
        )

# "True" source files for the C-file entry points and static library files.
add_subdirectory(src)

# Main program entry-points that make use of the libraries.
add_subdirectory(apps)

# MATLAB specific "out-of-source" folder.
# add_subdirectory(mex)