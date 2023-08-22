#include "uuid4.h"

/*********************************************************************
* Filename:   uuid4.c
* Author:     Jordan Smith
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Generates crypto-secure bytes and version 4 UUID (GUID). 
*             NOTE: This ought to use  Visual Studio or MinGW on 
*             Windows, Cygwin is untested.
*
*********************************************************************/

#ifdef __CYGWIN__
    #error "Cygwin builds are not supported."
#endif
#ifdef WIN32
    #include <windows.h>
    #include <bcrypt.h>
    #ifdef _MSC_VER
        #pragma comment(lib, "bcrypt.lib")
    #endif
    #ifndef STATUS_SUCCESS
        #define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
    #endif
    #ifndef BCRYPT_USE_SYSTEM_PREFERRED_RNG
        #define BCRYPT_USE_SYSTEM_PREFERRED_RNG 0x00000002
    #endif

    uint8_t* win32_cryptrand(void) {
        BYTE *buffer = calloc(NUM_UUID4_BYTES, sizeof(BYTE));
        DWORD Bsize = NUM_UUID4_BYTES * sizeof(BYTE);
        NTSTATUS stat;
        memset(buffer, 0, Bsize);
        stat = BCryptGenRandom(NULL, buffer, Bsize, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
        if (stat != STATUS_SUCCESS) {
            printf("Internal Failure.\n");
            exit(1);
        }
        return buffer;
    }
#else
    #include <sys/random.h>
    uint8_t* cryptrand(void) {
        ssize_t stat;
        uint8_t *buffer = calloc(NUM_UUID4_BYTES, sizeof(uint8_t));
        stat = getrandom((void)buffer, (size_t)NUM_UUID4_BYTES, GRND_NONBLOCK);
        if (stat == -1) {
            printf("Internal Failure.\n");
            exit(1);
        }
        return buffer;
    }
#endif

char* uuid4(void) {
    // generate the crypto-secure bytes.
    uint8_t *buffer;
    #ifdef WIN32
        buffer = win32_cryptrand();
    #else
        buffer = cryptrand();
    #endif
    char *outstr = calloc(36+1, sizeof(char)); // 36-element string.
    int byteIdx, posIdx;
    strcpy(outstr, "FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF");
    // need to mask the version and variant fields via:
    //  u &= 0xffffffffffff0fff3fffffffffffffff
    //  u |= 0x00000000000040008000000000000000

    buffer[6] = ((buffer[6] & 0x0f) | 0x40);
    buffer[8] = ((buffer[8] & 0x3f) | 0x80);
    
    uint8_t positions[16] = {0,2,4,6,9,11,14,16,19,21,24,26,28,30,32,34};
    byteIdx = 0;
    posIdx = 0;
    char scratch[3] = {0,}; // 2-bytes + null terminate.
    for (posIdx = 0; posIdx < 16; posIdx++) {
        sprintf(scratch, "%.2x", (unsigned int)buffer[byteIdx]);
        memcpy(&outstr[positions[posIdx]], &scratch, 2);
        byteIdx++;
    }
    free(buffer);
    return outstr;
}