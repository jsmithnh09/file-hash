#include "mex.h"

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
    fname = mxArrayToString(prhs[0]);
    algo = mxArrayToString(prhs[1]);

    if (!strcmpi(algo, "md5")) {
        hash = md5_file(fname);
    } else if (!strcmpi(algo, "sha256")) {
        hash = sha256_file(fname);
    } else if (!strcmpi(algo, "sha1")) {
        hash = sha1_file(fname);
    } else {
        hash = sha256_file(fname);
    }

    // output the hash.
    plhs[0] = mxCreateCharArray()


}