import zlib
import sys
import hashlib
import json
from os.path import abspath, join
from os import getcwd

BATCH_SIZE = 65536 # 65 kB buffersize.

md5 = hashlib.md5()
sha256 = hashlib.sha256()
sha1 = hashlib.sha1()

result = {"MD5": [], "SHA1": [], "SHA256": [], "CRC32": []}

target = abspath(join(getcwd(), "test.txt"))
if not isfile(target):
    raise FileNotFoundError("The test file is not present. Run this in the test directory.")

with open("test.txt", "rb") as fid:
    cksum = 0
    while True:
        data = fid.read(BATCH_SIZE)
        if not data:
            break
        md5.update(data)
        sha1.update(data)
        sha256.update(data)
        cksum = zlib.crc32(data, cksum)

result["MD5"] = md5.hexdigest().upper()
result["SHA1"] = sha1.hexdigest().upper()
result["SHA256"] = sha256.hexdigest().upper()
result["CRC32"] = "%08x" % (hash & 0xFFFFFFFF)

with open("results.json", "w") as fid:
    json.dump(results, fid)

