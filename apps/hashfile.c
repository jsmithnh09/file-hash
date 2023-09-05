#include <stdio.h>
#include <stdlib.h>
#include "hashers/sha256.h"
#include "hashers/md5.h"
#include "hashers/sha1.h"
#include "hashers/crc32.h"

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
    if (argc > 2) {
        if (!strncmp(argv[2], "md5", 3)) {
            printf("MD5   : ");
            output = md5_file(argv[1]);
        } else if (!strncmp(argv[2], "sha256", 6)) {
            printf("SHA256: ");
            output = sha256_file(argv[1]);
        } else if (!strncmp(argv[2], "sha1", 4)) {
            printf("SHA1  : ");
            output = sha1_file(argv[1]);
        } else if (!strncmp(argv[2], "crc32", 5)) {
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
