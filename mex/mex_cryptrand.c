#include "mex.h"
#include "uuid/uuid.h"
#include "version.h"
#include <stdio.h>
#include <string.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    if (nrhs != 1) {
        mexErrMsgIdAndTxt("cryptrand:InvalidSyntax", "Only one input argument was expected.");
    } else if (!mxIsScalar(prhs[0])) {
        mexErrMsgIdAndTxt("cryptrand:InvalidInput", "NUMBYTES input must be scalar.");
    }
    size_t elements;
    uint8_t *buff, *out;
    elements = (size_t)*mxGetPr(prhs[0]);
    plhs[0] = mxCreateNumericArray(1, (mwSize*)&elements, mxUINT8_CLASS, 0);
    buff = cryptrand(numbytes);
    out = (uint8_t *)mxGetPr(plhs[0]);
    memcpy(out, buff, sizeof(uint8_t) * elements);
    free(buff);
}

