import zlib
import sys, random
import hashlib
import json, io
from os.path import abspath, join, isfile
from os import getcwd

BATCH_SIZE = 2048 # 16 kB buffersize.
HASH_METHODS = ["md5", "sha1", "sha256"]

# instantiate each of the hasher objects.
hashers = {}
for meth in HASH_METHODS:
    hashers[meth] = getattr(hashlib, meth)()

target = abspath(join(getcwd(), "test.txt"))
if not isfile(target):
    with open(target, "w") as fid:
        fid.write("hello world!")

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