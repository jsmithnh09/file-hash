import zlib
import sys
import hashlib
import json
from os.path import abspath, join, isfile
from os import getcwd

BATCH_SIZE = 16384 # 16 kB buffersize.
HASH_METHODS = ["md5", "sha1", "sha256"]

# instantiate each of the hasher objects.
hashers = {}
for meth in HASH_METHODS:
    hashers[meth] = getattr(hashlib, meth)()

target = abspath(join(getcwd(), "test.txt"))
if not isfile(target):
    raise FileNotFoundError("The test file is not present. Run this in the test directory.")

# read chunks of data and CRC/hash them.
with open("test.txt", "rb") as fid:
    cksum = 0
    while True:
        data = fid.read(BATCH_SIZE)
        if not data:
            break
        for keyiter in hashers.keys():
            hashers[keyiter].update(data)
        cksum = zlib.crc32(data, cksum)

result = {}
for key in HASH_METHODS:
    result[key.upper()] = hashers[key].hexdigest().upper()
result["CRC32"] = "%08X" % (cksum & 0xFFFFFFFF)

with open("results.json", "w") as fid:
    json.dump(result, fid, indent=4)

