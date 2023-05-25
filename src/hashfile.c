#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "sha256.h"
#include "md5.h"
#include "sha1.h"
#include "crc32.h"

/*********************************************************
* Filename: hashfile
*
* Call a hash or checksum routine (SHA256, MD5, SHA1, CRC32) on a file.
*
**********************************************************/

/*********************************************************
* HASHFILE <FILENAME> [SHA256|MD5|SHA1|CRC32] [DOQUICK]
**********************************************************/
int main(int argc, char *argv[]) {
    char *output;
    BYTE quick = 0;
    if (argc > 3) {
        quick = 1;
    }
    if (argc >= 3) {
        if (!strcmp(argv[2], "md5")) {
            printf("MD5   : ");
            output = md5_file_quick(argv[1], quick);
        } else if (!strcmp(argv[2], "sha256")) {
            printf("SHA256: ");
            output = sha256_file_quick(argv[1], quick);
        } else if (!strcmp(argv[2], "sha1")) {
            printf("SHA1  : ");
            output = sha1_file_quick(argv[1], quick);
        } else if (!strcmp(argv[2], "crc32")) {
            printf("CRC32 : ");
            output =  crc32_file_quick(argv[1], quick);
        } else {
            printf("SHA256: ");
            output = sha256_file_quick(argv[1], quick);
        }
    } else {
        printf("SHA256: ");
        output = sha256_file_quick(argv[1], quick);
    }
    printf("%s: %s\n", argv[1], output);
    free(output);
    return 0;
}
