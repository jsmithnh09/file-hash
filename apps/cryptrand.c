#include <stdio.h>
#include <string.h>
#include "uuid/uuid.h"
#include "version.h"

/*************************************************************
 * Filename: cryptrand.c
 *
 * Generate and print cryptographically secure random bytes.
 *
 *************************************************************/

 /************************************************************
  * CRYPTRAND <NUMBYTES> [-V|--VERSION]
  ************************************************************/
  int main(int argc, char *argv[]) {
    size_t numbytes = 1;
    if (argc == 2) {
        if (!strncmp(argv[1], "-v", 2) || !strncmp(argv[1], "--v", 3)) {
            printf("file-hash: cryptrand v%s\n", FILE_HASH_VERSION);
            return 0;
        } else {
            numbytes = atoi(argv[1]);
        }
    }
    uint8_t *buff;
    #if defined(_WIN32)
        buff = win32_cryptrand((size_t)numbytes);
    #else
        buff = cryptrand((size_t)numbytes);
    #endif
    int iterIdx;
    printf("$:");
    for(iterIdx = 0; iterIdx < (int)numbytes; iterIdx++) {
        printf("%02x", buff[iterIdx]);
    }
    free(buff);
    printf("\n");
    return 0;
    
  }

