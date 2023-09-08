#include "mex.h"
#include "uuid/uuid.h"
#include <string.h>
#include <stdio.h>

/* MEX API. */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    if (nlhs != 1) {
        mexErrMsgIdAndTxt("uuidgen:BadOutput", "Expected one string output.");
    }
    char *uuid, *outbuf;
    uuid = uuid4();
    outbuf = mxCalloc(NUM_UUID_CHARS+1, sizeof(char));
    size_t idx;
    for (idx = 0; idx < NUM_UUID_CHARS; idx++) {
        outbuf[idx] = uuid[idx];
    }
    outbuf[NUM_UUID_CHARS+1] = '\0'; // null-terminate.
    plhs[0] = mxCreateString(outbuf);
    free(uuid);
}
