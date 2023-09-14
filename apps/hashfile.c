#include <stdio.h>
#include <stdlib.h>
#include "hashers/sha256.h"
#include "hashers/md5.h"
#include "hashers/sha1.h"
#include "hashers/crc32.h"
#include "version.h"

/*********************************************************
* Filename: hashfile
*
* Call a hash or checksum routine (SHA256, MD5, SHA1, CRC32) on a file.
*
**********************************************************/

/*********************************************************
* HASHFILE <FILENAME> [SHA256|MD5|SHA1|CRC32|-V|--VERSION]
**********************************************************/
int main(int argc, char *argv[]) {
    if ((argc == 2) && (!strncmp(argv[1], "-v", 2) || !strncmp(argv[1], "--v", 3))) {
        printf("file-hash: hashfile v%s\n", FILE_HASH_VERSION);
        return 0;
    } else if ((argc == 2) && (!strncmp(argv[1], "-h", 2) || !strncmp(argv[1], "--help", 6))) {
        printf("Usage\n\n\thashfile <filename> <algorithm>\n\thashfile <filename> [sha256]\n\n");
        printf("Hash a file and generate the hex-string associated with the checksum or hash.\n");
        printf("Available algorithms include crc32, sha1, sha256, and md5. By default, sha256 is used.\n");
        return 0;
    }
    char *output;
    if (argc > 2) {
        if (!strncmp(argv[2], "md5", 3)) {
            output = md5_file(argv[1]);
        } else if (!strncmp(argv[2], "sha256", 6)) {
            output = sha256_file(argv[1]);
        } else if (!strncmp(argv[2], "sha1", 4)) {
            output = sha1_file(argv[1]);
        } else if (!strncmp(argv[2], "crc32", 5)) {
            output =  crc32_file(argv[1]);
        } else {
            output = sha256_file(argv[1]);
        }
    } else {
        output = sha256_file(argv[1]);
    }
    printf("%s\n", output);
    free(output);
    return 0;
}
