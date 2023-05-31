import sys, subprocess
import json, os, re
import os.path as op

# read in the JSON results.
fpath = op.abspath(op.join(os.getcwd(), "results.json"))
if not op.isfile(fpath):
    raise FileNotFoundError("Results JSON not found.")
with open(fpath, "r") as fid:
    data = json.load(fid)

# run the hashfile process and check the outputs.
(root_dir, _) = op.split(os.getcwd())
infile = op.join(root_dir, "test", "test.txt")
exepath = op.join(root_dir, "build", "hashfile.exe")

# pull the byte output into a string.
for hasher in data.keys():
    stdout = subprocess.check_output([exepath, infile, hasher.lower()]).decode()
    if os.name == 'nt':
        match = re.findall(r"(?<=\: )([0-9a-fA-F]+)", stdout[:-2])[-1] # popping the \r\n
    else:
        match = re.findall(r"(?<=\: )([0-9a-fA-F]+)", stdout[:-1])[-1]
    
    # `file_hash` generates uppercase HEX. match the syntax.
    assert match.upper() == data[hasher].upper(), f"Hash mismatch with input {hasher}."