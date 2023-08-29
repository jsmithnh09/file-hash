#include "uuid.h"
#include <stdio.h>
#include <limits.h>
#include <errno.h>

/*********************************************************
* Filename: UUID4GEN
* Description: Generate a UUID4-compliant string to STDOUT.
**********************************************************/

/*********************************************************
* UUID4GEN [NUM_IDS=1]
**********************************************************/
int main(int argc, char *argv[]) {
    long numIds = 1;
    long iterIdx;
    if (argc > 1) {
        errno = 0;
        char *pEnd;
        numIds = strtol(argv[1], &pEnd, 10);
        if (errno != 0 || *pEnd != '\0' || numIds > INT_MAX || numIds < INT_MIN)
        {
            printf("Invalid # of UUIDs specified.\n");
            exit(1);
        }
    }
    char *uuid;
    for (iterIdx = 0; iterIdx < numIds; iterIdx++)
    {
        uuid = uuid4();
        printf("%.36s\n", uuid);
        free(uuid);
    }
    return 0;
}