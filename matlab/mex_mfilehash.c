#include "mex.h"
#include "crc32.h"
#include "sha1.h"
#include "md5.h"
#include "sha256.h"
#include "common.h"
#include <string.h>
#include <stdio.h>

// MinGW GNU Compiler will work with the stat interface when compiling. VS2017+ will not.

/* MEX API to use the hashing capabilities. */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    if (nlhs != 1) {
        mexErrMsgIdAndTxt("mfilehash:BadOutput", "Expected a string output.");
    } else if (nrhs < 1) {
        mexErrMsgIdAndTxt("mfilehash:InvalidSyntax", "One input argument was expected.");
    } else if (!mxIsChar(prhs[0])) {
        mexErrMsgIdAndTxt("mfilehash:InvalidSyntax", "First input must be a filepath.");
    }

    // pull the filename, algorithm, and output.
    char *fname, *algo, *hash, *outbuf;
    size_t buflen;
    fname = mxArrayToString(prhs[0]);
    algo = mxArrayToString(prhs[1]);

    // determine which algorithm to use for what hash/checksum.
    if (!strncmp(algo, "md5", 3)) {
        hash = md5_file(fname);
        buflen = (size_t)MD5_STRLEN;
    } else if (!strncmp(algo, "sha256", 6)) {
        hash = sha256_file(fname);
        buflen = (size_t)SHA256_STRLEN;
    } else if (!strncmp(algo, "sha1", 4)) {
        hash = sha1_file(fname);
        buflen = (size_t)SHA1_STRLEN;
    } else if (!strncmp(algo, "crc32", 5)) {
        hash = crc32_file(fname);
        buflen = (size_t)CRC32_STRLEN;
    } else {
        hash = sha256_file(fname);
        buflen = (size_t)SHA256_STRLEN;
    }

    // output the hash and free C-style memory.
    outbuf = mxCalloc(buflen+1, sizeof(char));
    int idx;
    for (idx = 0; idx < buflen; idx++) {
        outbuf[idx] = hash[idx];   
    }
    outbuf[buflen] = '\0'; // null-terminating.
    plhs[0] = mxCreateString(outbuf);
    free(hash);


}