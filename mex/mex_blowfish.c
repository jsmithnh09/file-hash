#include "mex.h"
#include "blowfish.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// process blowfish encryption/decryption for a single double input, separated into two float words.
void processBlow(double *out, double *in, uint8_t *block, uint32_t *words,
        BLOWFISH_CTX *ctx, char *mode) {
    memcpy(block, in, sizeof(double));
    memcpy(&words[0], &block[0], 4);
    memcpy(&words[1], &block[4], 4);
    switch(*mode) {
        case 'e':
        case 'E':
            Blowfish_Encrypt(ctx, &words[0], &words[1]);
            memcpy(out, words, 8);
            break;
        case 'd':
        case 'D':
            Blowfish_Decrypt(ctx, &words[0], &words[1]);
            memcpy(out, words, 8);
            break;
        default:
            memset(ctx, 0, sizeof(BLOWFISH_CTX));
            free(ctx);
            mexErrMsgIdAndTxt("mex_blowfish:InvalidSyntax", "Input mode must be ENC or DEC.");
    } // switch
}

// y = blowfish(data, <"enc"|"dec">, <key>)
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs != 3) {
        mexErrMsgIdAndTxt("mex_blowfish:InvalidSyntax", "At least three input arguments were expected.");
    } else if (!mxIsChar(prhs[1])) {
        mexErrMsgIdAndTxt("mex_blowfish:InvalidSyntax", "Input mode must be type CHAR.");
    } else if (!mxIsChar(prhs[2])) {
        mexErrMsgIdAndTxt("mex_blowfish:InvalidSyntax", "Input key must be a string.");
    } else if (!mxIsDouble(prhs[0])) {
        mexErrMsgIdAndTxt("mex_blowfish:InvalidSyntax", "First input must be a double.");
    }

    uint8_t bdata[8] = {0,};
    uint32_t block[2] = {0,}; // head and tail float words that are the input to blowfish.
    size_t elements;
    mwSize iterIdx, numDims, cmplx;
    const mwSize *dims;
    char *mode, *key;
    double result;
    #if MX_HAS_INTERLEAVED_COMPLEX
        mxComplexDouble *pc, *pcl;
        double *pr, *pl;
    #else
        double *pr, *pi, *plr, *pli;
    #endif
    elements = mxGetNumberOfElements(prhs[0]);
    mode = mxArrayToString(prhs[1]);
    key = mxArrayToString(prhs[2]);

    // create the output array and get a pointer to write into.
    numDims = mxGetNumberOfDimensions(prhs[0]);
    dims = mxGetDimensions(prhs[0]);

    // initialize blowfish (control structure internals could be too large for the stack, per the notes.)
    BLOWFISH_CTX *ctx = (BLOWFISH_CTX*)malloc(sizeof(BLOWFISH_CTX));
    Blowfish_Init(ctx, (uint8_t*)key, strlen(key));

    #if MX_HAS_INTERLEAVED_COMPLEX
        cmplx = mxIsComplex(prhs[0]);
        plhs[0] = mxCreateNumericArray(numDims, dims, mxDOUBLE_CLASS, cmplx);
        if (cmplx) {
            pc = mxGetComplexDoubles(prhs[0]);
            pcl= mxGetComplexDoubles(plhs[0]);
            for (iterIdx = 0; iterIdx < elements; iterIdx++) {
                processBlow(&pcl[iterIdx].real, &pc[iterIdx].real, bdata, block, ctx, mode);
                processBlow(&pcl[iterIdx].imag, &pc[iterIdx].imag, bdata, block, ctx, mode);
            }
        } else {
            pl = mxGetDoubles(plhs[0]);
            pr = mxGetDoubles(prhs[0]);
            for (iterIdx = 0; iterIdx < elements; iterIdx++) {
                processBlow(&pl[iterIdx], &pr[iterIdx], bdata, block, ctx, mode);
            }
        }
    #else
        pr = (double *)mxGetPr(prhs[0]);
        pi = (double *)mxGetPi(prhs[0]);
        cmplx = ((pi == NULL) ? 0 : 1);
        plhs[0] = mxCreateNumericArray(numDims, dims, mxDOUBLE_CLASS, cmplx);
        if (cmplx) {
            plr = (double *)mxGetPr(plhs[0]);
            pli = (double *)mxGetPi(plhs[0]);
            for (iterIdx = 0; iterIdx < elements; iterIdx++) {
                processBlow(&plr[iterIdx], &pr[iterIdx], bdata, block, ctx, mode);
                processBlow(&pli[iterIdx], &pi[iterIdx], bdata, block, ctx, mode);
            }
        } else {
            plr = (double *)mxGetPr(plhs[0]);
            for (iterIdx = 0; iterIdx < elements; iterIdx++) {
                processBlow(&plr[iterIdx], &pr[iterIdx], bdata, block, ctx, mode);
            }
        }
    #endif

    // free the context structure.
    memset(ctx, 0, sizeof(BLOWFISH_CTX));
    free(ctx);
}