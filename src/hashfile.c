#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
* HASHFILE <FILENAME> [SHA256|MD5|SHA1|CRC32]
**********************************************************/
int main(int argc, char *argv[]) {
    char *output;
    if (argc >= 3) {
        if (!strcmp(argv[2], "md5")) {
            printf("MD5   : ");
            output = md5_file(argv[1]);
        } else if (!strcmp(argv[2], "sha256")) {
            printf("SHA256: ");
            output = sha256_file(argv[1]);
        } else if (!strcmp(argv[2], "sha1")) {
            printf("SHA1  : ");
            output = sha1_file(argv[1]);
        } else if (!strcmp(argv[2], "crc32")) {
            printf("CRC32 : ");
            output =  crc32_file(argv[1]);
        } else {
            printf("SHA256: ");
            output = sha256_file(argv[1]);
        }
    } else {
        printf("SHA256: ");
        output = sha256_file(argv[1]);
    }
    printf("%s: %s\n", argv[1], output);
    free(output);
    return 0;
}
