#include "mex.h"
#include "crc32.h"
#include "sha1.h"
#include "md5.h"
#include "sha256.h"

/* MEX API to use the hashing capabilities. */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    if (nlhs != 1) {
        mexErrMsgIdAndTxt("mfilehash:BadOutput", "Expected a string output.");
    } else if (nrhs != 2) {
        mexErrMsgIdAndTxt("mfilehash:InvalidSyntax", "Two input arguments were expected.");
    } else if (!mxIsChar(prhs[0])) {
        mexErrMsgIdAndTxt("mfilehash:InvalidSyntax", "First input must be a filepath.");
    } else if (!mxIsChar(prhs[1])) {
        mexErrMsgIdAndTxt("mfilehash:InvalidSyntax", "Second input must indicate a hash algorithm.");
    }

    // pull the filename, algorithm, and output.
    char *fname, *algo, *hash;
    mxChar *mxdata;
    int dims[];
    fname = mxArrayToString(prhs[0]);
    algo = mxArrayToString(prhs[1]);

    // determine which algorithm to use for what hash/checksum.
    if (!strncmpi(algo, "md5", 3)) {
        hash = md5_file(fname);
        dims = {1, MD5_STRLEN};
    } else if (!strncmpi(algo, "sha256", 6)) {
        hash = sha256_file(fname);
        dims = {1, SHA256_STRLEN};
    } else if (!strncmpi(algo, "sha1", 4)) {
        hash = sha1_file(fname);
        dims = {1, SHA1_STRLEN};
    } else if (!strncmpi(algo, "crc32", 5)) {
        hash = crc32_file(fname);
        dims = {1, CRC32_STRLEN};
    } else {
        hash = sha256_file(fname);
        dims = {1, SHA256_STRLEN};
    }

    // output the hash.
    plhs[0] = mxCreateCharArray(2, (const int *)dims);
    mxdata = (mxChar *)mxGetData(plhs[0]);
    memcpy(mxdata, hash, dims[1] * sizeof(char));


}