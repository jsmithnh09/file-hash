#include "uuid/uuid.h"
#include "hashers/md5.h"
#include "hashers/sha1.h"

/*********************************************************************
* Filename:   uuid.c
* Author:     Jordan Smith
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Generates crypto-secure bytes and version 4 UUID (GUID). 
*             NOTE: This ought to use  Visual Studio or GNU. MinGW and
*             Cygwin will use Wincrypt, but that API may deprecate in
*             the future...more of a detail about MinGW being outdated.
*
*********************************************************************/

#if defined(__CYGWIN__)
    #error "Cygwin builds are not supported."
#endif
#if defined(__MINGW32__)
    // using the Wincrypt API since that's visible to MinGW.
    #include <windows.h>
    #include <Wincrypt.h>
    uint8_t* win32_cryptrand(void) {
        uint8_t *buffer = calloc(NUM_UUID_BYTES, sizeof(uint8_t));
        DWORD Bsize = NUM_UUID_BYTES * sizeof(uint8_t);
        NTSTATUS stat;
        HCRYPTPROV hCryptProv;
        stat = CryptAcquireContext(&hCryptProv, 
            NULL, 
            "Microsoft Base Cryptographic Provider v1.0", 
            PROV_RSA_FULL, 
            CRYPT_VERIFYCONTEXT);
        if (!stat) {
            fprintf(stderr, "uuid: Internal Wincrypt failure.\n");
            free(buffer);
            exit(1);
        }
        stat = CryptGenRandom(hCryptProv, Bsize, (BYTE *)buffer);
        if (!stat) {
            fprintf(stderr, "uuid: Internal Wincrypt failure. Cannot generate random bytes.\n");
            free(buffer);
            exit(1);
        }
        stat = CryptReleaseContext(hCryptProv, 0);
        if (!stat) {
            fprintf(stderr, "uuid: Error during CryptReleaseContext.\n");
            free(buffer);
            exit(1);
        }
        return buffer;
    }
#endif
#if defined(_WIN32) && !defined(__MINGW32__)
    // using the more advanced BCrypt API here. MinGW can't seem to find the bcrypt library.
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
        uint8_t *buffer = calloc(NUM_UUID_BYTES, sizeof(uint8_t));
        DWORD Bsize = NUM_UUID_BYTES * sizeof(uint8_t);
        NTSTATUS stat;
        memset(buffer, 0, Bsize);
        stat = BCryptGenRandom(NULL, buffer, Bsize, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
        if (stat != STATUS_SUCCESS) {
            printf("Internal Failure.\n");
            exit(1);
        }
        return buffer;
    }
#endif
#if defined(__unix__)
    #include <sys/random.h>
    uint8_t* cryptrand(void) {
        ssize_t stat;
        uint8_t *buffer = calloc(NUM_UUID_BYTES, sizeof(uint8_t));
        stat = getrandom((void *)buffer, (size_t)NUM_UUID_BYTES, GRND_NONBLOCK);
        if (stat == -1) {
            fprintf(stderr, "Internal Failure.\n");
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

char* uuid3(const char* namespace, const char* instr)
{
    // concatenate the output and one of the DNS based inputs.
    char *input, *uuidstr;
    uint8_t *nsbytes, *hash;
    uint8_t bIdx;

    // convert the namespace UUID to its byte representation.
    nsbytes = (uint8_t *)uuid2bin(namespace);

    // concatenate the UUID namespace bytes and the ASCII input string.
    size_t nchars = strlen(instr) + NUM_UUID_BYTES;
    input = (char *)calloc(nchars, sizeof(char));
    memcpy(input, nsbytes, NUM_UUID_BYTES);

    // fill up the second half with the ASCII character bytes.
    for (bIdx = NUM_UUID_BYTES; bIdx < nchars; bIdx++) {
        input[bIdx] = instr[bIdx-NUM_UUID_BYTES];
    }
    hash = md5_bytes((void *)input, nchars);

    // mask with the version and flip the first two bits to "10".
    hash[6] = ((hash[6] & 0x0f) | 0x30);
    hash[8] = ((hash[8] & 0x3f) | 0x80);

    // the resulting UUID will be truncated, but that's expected.
    uuidstr = bin2uuid(hash);
    
    // cleanup.
    free(input);
    free(hash);
    free(nsbytes);
    return uuidstr;
}

char* uuid5(const char* namespace, const char* instr)
{
   // concatenate the output and one of the DNS based inputs.
    char *input, *uuidstr;
    uint8_t *nsbytes, *hash;
    uint8_t bIdx;

    // convert the namespace UUID to its uint8_t representation.
    nsbytes = (uint8_t *)uuid2bin(namespace);

    // concatenate the UUID namespace bytes and the ASCII input string.
    size_t nchars = strlen(instr) + NUM_UUID_BYTES;
    input = (char *)calloc(nchars, sizeof(char));
    memcpy(input, nsbytes, NUM_UUID_BYTES);

    // fill up the second half with the ASCII character bytes.
    for (bIdx = NUM_UUID_BYTES; bIdx < nchars; bIdx++) {
        input[bIdx] = instr[bIdx-NUM_UUID_BYTES];
    }
    hash = sha1_bytes((void *)input, nchars);

    // mask with the version and flip the first two bits to "10".
    hash[6] = ((hash[6] & 0x0f) | 0x50);
    hash[8] = ((hash[8] & 0x3f) | 0x80);

    // the resulting UUID will be truncated, but that's expected.
    uuidstr = bin2uuid(hash);
    
    // cleanup.
    free(input);
    free(hash);
    free(nsbytes);
    return uuidstr;
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
