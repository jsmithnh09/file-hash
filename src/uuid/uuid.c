#include "uuid.h"

/*********************************************************************
* Filename:   uuid.c
* Author:     Jordan Smith
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Generates crypto-secure bytes and version 4 UUID (GUID). 
*             NOTE: This ought to use  Visual Studio or GNU. MinGW and
*             Cygwin will cause issues...
*
*********************************************************************/

#if defined(__CYGWIN__)
    #error "Cygwin builds are not supported."
#elif defined(__MINGW32__)
    #error "MinGW does not support 'getrandom' API."
#endif
#ifdef _WIN32
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
        BYTE *buffer = calloc(NUM_UUID_BYTES, sizeof(BYTE));
        DWORD Bsize = NUM_UUID_BYTES * sizeof(BYTE);
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
        uint8_t *buffer = calloc(NUM_UUID_BYTES, sizeof(uint8_t));
        stat = getrandom((void)buffer, (size_t)NUM_UUID_BYTES, GRND_NONBLOCK);
        if (stat == -1) {
            printf("Internal Failure.\n");
            exit(1);
        }
        return buffer;
    }
#endif

char* bin2uuid(uint8_t *buffer) {
    char *outstr = calloc(NUM_UUID_CHARS+1, sizeof(char));
    strcpy(outstr, "FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF"); // using max-UUID.
    int byteIdx, posIdx;
    char scratch[3] = {0,};
    byteIdx = 0;
    posIdx = 0;
    while(posIdx < NUM_UUID_CHARS) {
        switch (posIdx) {
            case 8:
            case 13:
            case 18:
            case 23:
                // already have dash in-place.
                posIdx++;
                break;
            default:
                sprintf(scratch, "%.2x", (unsigned int)buffer[byteIdx]);
                memcpy(&outstr[posIdx], &scratch, 2);
                byteIdx++;
                posIdx += 2;
        }
    }
    return outstr;
}

// converts the UUID string into its byte-pack representation.
uint8_t* uuid2bin(const char* uuid) {
    uint8_t *output = calloc(NUM_UUID_BYTES, sizeof(uint8_t));
    if (strlen(uuid) != NUM_UUID_CHARS) {
        fprintf(stderr, "Invalid number of UUID characters.\n");
        exit(1);
    }
    uint8_t posIdx = 0;
    uint8_t byteIdx = 0;
    char scratch[] = "0x00";
    while(posIdx < NUM_UUID_CHARS) {
        if (uuid[posIdx] == '-') {
            posIdx++;
            continue;
        } else {
            scratch[2] = uuid[posIdx];
            scratch[3] = uuid[posIdx+1];
            output[byteIdx] = (uint8_t)strtol(scratch, NULL, 0);
            posIdx += 2;
            byteIdx++;
        }

    }
    return output;
}

char* uuid4(void) {
    // generate the crypto-secure bytes.
    uint8_t *buffer;
    char *uuidstr;
    #ifdef _WIN32
        buffer = win32_cryptrand();
    #else
        buffer = cryptrand();
    #endif
    /*
     * 
     * from the Julia stdlib:
     * https://github.com/JuliaLang/julia/blob/a4309ca/stdlib/UUIDs/src/UUIDs.jl#L114-L115
     * need to mask the version and variant fields via:
     *  u &= 0xffffffffffff0fff3fffffffffffffff
     *  u |= 0x00000000000040008000000000000000
     *
     */
    buffer[6] = ((buffer[6] & 0x0f) | 0x40);
    buffer[8] = ((buffer[8] & 0x3f) | 0x80);
    uuidstr = bin2uuid(buffer);
    free(buffer);
    return uuidstr;
}