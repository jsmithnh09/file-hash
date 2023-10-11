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
    
    uint32_t L = 1;
    uint32_t R = 2;

    BLOWFISH_CTX *ctx = (BLOWFISH_CTX*)malloc(sizeof(BLOWFISH_CTX));
    Blowfish_Init(ctx, "TESTKEY", 7);
    Blowfish_Encrypt(ctx, &L, &R);
    if ((L != 0xDF333FD2L) || (R != 0x30A71BB4L))
    {
        memset(ctx, 0, sizeof(BLOWFISH_CTX));
        free(ctx);
        printf("%081X %081X\n", L, R);
        printf("Test encryption FAILED.\n");
        exit(1);
    }
    Blowfish_Decrypt(ctx, &L, &R);
    if ((L != 1) || (R != 2)) {
        memset(ctx, 0, sizeof(BLOWFISH_CTX));
        free(ctx);
        printf("Test decryption FAILED.\n");
        exit(1);
    }
    memset(ctx, 0, sizeof(BLOWFISH_CTX));
    free(ctx);
    printf("SUCCESS\n");
    return 0;
}