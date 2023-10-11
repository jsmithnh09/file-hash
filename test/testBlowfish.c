#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blowfish.h"
#include <stdint.h>

/************************************************************
 * BLOWFISH testing should provide a double value 
 *  we can then enc/dec and check if equivalent.
 ************************************************************/

int main(int argc, char *argv[]) {
    
    uint32_t L = 0xDEADBEEF;
    uint32_t R = 0xBEEFDEAD;

    BLOWFISH_CTX *ctx = (BLOWFISH_CTX*)malloc(sizeof(BLOWFISH_CTX));
    Blowfish_Init(ctx, "TESTKEY", 7);
    Blowfish_Encrypt(ctx, &L, &R);
    Blowfish_Decrypt(ctx, &L, &R);
    if ((L != 0xDEADBEEF) || (R != 0xBEEFDEAD)) {
        memset(ctx, 0, sizeof(BLOWFISH_CTX));
        free(ctx);
        fprintf(stderr, "Test decryption FAILED.\n");
        exit(1);
    }
    memset(ctx, 0, sizeof(BLOWFISH_CTX));
    free(ctx);
    printf("SUCCESS\n");
    return 0;
}