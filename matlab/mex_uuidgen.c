#include "mex.h"
#include "uuid4.h"
#include <string.h>
#include <stdio.h>

/* MEX API. */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    char *uuid, *outbuf;
    uuid = uuid4();
    outbuf = mxCalloc(NUM_UUID4_CHARS+1, sizeof(char));
    for (idx = 0; idx < NUM_UUID4_CHARS; idx++) {
        outbuf[idx] = uuid[idx];
    }
    outbuf[NUM_UUID4_CHARS+1] = '\0'; // null-terminate.
    plhs[0] = mxCreateString(outbuf);
    free(uuid);
}