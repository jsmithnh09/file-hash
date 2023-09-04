#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include "uuid.h"
#include "sha1.h"
#include "md5.h"

/*****************************************************************
* Filename: UUIDGEN
* Usage
*
*   uuidgen -v <version-number> -n <number-of-ids>
*
* Specify a UUID version number (3-5.) Specify the number of IDs
* to generate of that specific verison.
*
* Options
*   -v <version-number>     = Explicitly set version number. Default is 4.
*   -n <number-of-ids>      = prints "n" number of IDs. Deafult is 1.
******************************************************************/

char* uuid3(const char* instr)
{
    // concatenate the output and one of the DNS based inputs.
    char *input, *uuidstr;
    char namespace[] = STR_UUID_OID;
    BYTE *hash;
    size_t nchars = strlen(instr) + strlen(namespace);
    input = (char *)calloc(nchars+1, sizeof(char));
    strcpy(input, namespace);
    strcat(input, instr);
    hash = (BYTE *)md5_bytes((void *)input, strlen(input));

    // mask with the version and flip the first two bits to "10".
    hash[6] = ((hash[6] & 0x0f) | 0x30);
    hash[8] = ((hash[8] & 0x3f) | 0x80);

    // the resulting UUID will be truncated, but that's expected.
    uuidstr = bin2uuid(hash);
    
    // cleanup.
    free(input);
    free(hash);
    return uuidstr;
}

char* uuid5(const char* instr)
{
    // concatenate the output and one of the DNS based inputs.
    char *input, *uuidstr;
    char namespace[] = STR_UUID_OID;
    BYTE *hash;
    size_t nchars = strlen(instr) + strlen(namespace);
    input = (char *)calloc(nchars+1, sizeof(char));
    strcpy(input, namespace);
    strcat(input, instr);
    hash = (BYTE *)sha1_bytes((void *)input, strlen(input));

    // mask with the version and flip the first two bits to "10".
    hash[6] = ((hash[6] & 0x0f) | 0x50);
    hash[8] = ((hash[8] & 0x3f) | 0x80);

    // the resulting UUID will be truncated, but that's expected.
    uuidstr = bin2uuid(hash);
    
    // cleanup.
    free(input);
    free(hash);
    return uuidstr;
}

/*********************************************************
* UUIDGEN [NUM_IDS=1] [VERSION=4] ...VisualStudio, NO getopt???
* Uses:
*   UUIDGEN 3 <"INPUT-STR">
*   UUIDGEN 4 <NUM-IDs>
*   UUIDGEN 5 <"INPUT-STR">
*
* Default, no args: UUIDGEN 4 1
**********************************************************/
int main(int argc, char *argv[]) {
    if (argc == 3) {
        long numIds = 1;
        uint8_t vnum = 4;
        if (sscanf(argv[1], "%i", (uint8_t *)&vnum) == -1) {
            fprintf(stderr, "Cannot parse UUID version number.\n");
            exit(1);
        }
        char* uuid;
        switch(vnum) {
            case 3:
                uuid = uuid3(argv[2]);
                printf("%.36s\n", uuid);
                free(uuid);
                return 0;
            case 4:
                long iterIdx;
                if (sscanf(argv[2], "%ld", (long *)&numIds) == -1) {
                    fprintf(stderr, "Cannot parse # of version-4 UUIDs to generate.\n");
                    exit(1);
                }
                for (iterIdx = 0; iterIdx < numIds; iterIdx++) {
                    uuid = uuid4();
                    printf("%.36s\n", uuid);
                    free(uuid);
                }
                return 0;
            case 5:
                uuid = uuid5(argv[2]);
                printf("%.36s\n", uuid);
                free(uuid);
                return 0;
            default:
                fprintf(stderr, "Invalid version number %d.\n", (int)vnum);
                exit(1);
        }
    } else if (argc == 1) {
        char *uuid = uuid4();
        printf("%.36s\n", uuid);
        free(uuid);
        return 0;
    } else {
        fprintf(stderr, "Invalid syntax.\n");
        exit(1);
    }
    return 0;
}