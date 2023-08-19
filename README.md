# File-hash

## About
This is based on the work by Brad Conte with no cross-licensing, available at
[this GitHub repository.](https://github.com/B-Con/crypto-algorithms) For each of the
cryptography source files, I've added a `<algorithm>_file` function signature for reading
in a filestream and computing the checksum. Although not necessarily a "hash" algorithm,
I've added an implementation of CRC32 where the polynomial table is pre-defined for 32-bit words.
For cleanup, I've added `atexit` methods in the event the hashing is interrupted to prevent open
file handlers on abnormal termination.

## Testing
To run MATLAB tests, the `test_filehash.m` class can be used as a test case alongside the `file_hash.py`
file to regenerate the test results for the test file "test.txt".

Building
To build, you'll need cmake and Visual Studio 2017 installed, (or a compiler compatible with your target release of MATLAB.) Unfortunately, VS2017 builds 32-bit applications by default. You'll need to specify the 64-bit architecture, or, alternatively, install VS2019 which supports 64-bit applications out of the box.

To generate the build files, run the following command with file-hash as your active directory: "C:\Program Files\CMake\bin\cmake.exe" -A x64 .

To generate the executable and MEX file, run the following: "C:\Program Files\CMake\bin\cmake.exe" --build build --target ../ALL_BUILD

The ALL_BUILD target is a result of using Visual Studio which doesn't have all as its default build target. Additionally, since we're building from the build directory, the .vscxproj file is in the top-level folder, so you need the ../ to specify where its located.
