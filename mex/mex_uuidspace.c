#include "mex.h"
#include "uuid/uuid.h"
#include <string.h>
#include <stdio.h>

/* Supported Syntax:
 *  MEX_UUIDSPACE(INSTR, VERSION[, NAMESPACE_ID])
 *  MEX_UUIDSPACE(INSTR)
 *
 * By default, we require a minimum input string and version, (3 or 5.) An additional
 * third argument would indicate one of the pre-defined namespace IDs from the original
 * RFC.
 */
 
// MEX API.
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    if (nlhs != 1) {
        mexErrMsgIdAndTxt("uuidspace:BadOutput", "Expected one string output.");
    } else if (nrhs < 2) {
        mexErrMsgIdAndTxt("uuidspace:BadInput", "Expected at least two inputs.");
    } else if (!mxIsChar(prhs[0])) {
        mexErrMsgIdAndTxt("uuidspace:BadInput", "First input must be a string.");
    } else if (!mxIsScalar(prhs[1])) {
        mexErrMsgIdAndTxt("uuidspace:BadInput", "Second input must be the UUID version.");
    }
    int vnum, nsid;
    char *uuid, *instr, *outbuf;
    instr = mxArrayToString(prhs[0]);
    vnum = (int)*mxGetPr(prhs[1]);
    if ((vnum != 3) && (vnum != 5)) {
        mexPrintf("Error: vnum = %d\n", &vnum);
        mexErrMsgIdAndTxt("uuidspace:BadInput", "Input VERSION must be 3 or 5.");
    }
    if (nrhs == 3) {
        nsid = (int)*mxGetPr(prhs[2]);
    } else {
        nsid = 0;
    }
    if ((nsid < 0) || (nsid > 3)) {
        mexPrintf("Error: NSID = %d\n", &nsid);
        mexErrMsgIdAndTxt("uuidspace:BadInput", "Namespace ID must be 0 <= id <= 3.");
    }
    char * (* idfcn)(const char*, const char*);
    idfcn = (vnum == 3) ? uuid3 : uuid5;
    switch(nsid) {
        case 1:
            uuid = idfcn(STR_UUID_URL, instr);
            break;
        case 2:
            uuid = idfcn(STR_UUID_OID, instr);
            break;
        case 3:
            uuid = idfcn(STR_UUID_X500, instr);
            break;
        default:
            uuid = idfcn(STR_UUID_DNS, instr);
            break;
    }
    outbuf = mxCalloc(NUM_UUID_CHARS+1, sizeof(char));
    size_t idx;
    for (idx = 0; idx < NUM_UUID_CHARS; idx++) {
        outbuf[idx] = uuid[idx];
    }
    outbuf[NUM_UUID_CHARS+1] = '\0'; // null-terminate.
    plhs[0] = mxCreateString(outbuf);
    free(uuid);
}
