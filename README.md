# HASHFILE

## About
This is based on the work by Brad Conte with no cross-licensing, available at
[this GitHub repository.](https://github.com/B-Con/crypto-algorithms) For each of the
cryptography source files, I've added a `<algorithm>_file` function signature for reading
in a filestream and computing the checksum. Although not necessarily a "hash" algorithm,
I've added an implementation of CRC32 where the polynomial table is pre-defined for 32-bit words.

## Testing
To test, if on Windows, you can use `Get-FileHash <filename> -Algorithm <algo>` to compute
the hash function and confirm the resulting hash strings match. Thus far, SHA1, SHA256, and MD5
have been confirmed to match, (21-May-2023.)

Using `python3`, the following can be used as well:
```python
import zlib
def crcfile(filename: str, batch_size: int = 1024) -> str:
    with open(filename, "rb") as fid:
        hash = 0
        while True:
            data = fid.read(batch_size)
            if not data:
                break
            hash = zlib.crc32(data, hash)
        return "08x" % (hash & 0xFFFFFFFF)
```

## Building
To build, run the following, (assuming `mingw` or `gcc` are installed):
```
gcc -I .\ -o hashfile.exe hashfile.c md5.c md5.h sha1.c sha1.h sha256.c crc32.c crc32.h sha256.h
```
For buliding with MEX, exclude hashfile.c and compile `mex_mfilehash.c` to get the MATLAB API working.