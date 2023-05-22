# File-hash

## About
This is based on the work by Brad Conte with no cross-licensing, available at
[this GitHub repository.](https://github.com/B-Con/crypto-algorithms) For each of the
cryptography source files, I've added a `<algorithm>_file` function signature for reading
in a filestream and computing the checksum. Although not necessarily a "hash" algorithm,
I've added an implementation of CRC32 where the polynomial table is pre-defined for 32-bit words.

## Testing
To run MATLAB tests, the `test_filehash.m` class can be used as a test case alongside the `file_hash.py`
file to regenerate the test results for the test file "test.txt".

## Building
To build, you'll need `make` and `mingw` installed on your Windows machine, (both can be done with Chocolatey.)
Windows is finnicky when it comes to removing files or directories, so I haven't included a `clean` step in the
makefile. Apologies!