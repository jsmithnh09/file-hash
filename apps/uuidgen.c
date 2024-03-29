#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include "uuid/uuid.h"
#include "hashers/sha1.h"
#include "hashers/md5.h"
#include "version.h"

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

/**********************************************************************
* UUIDGEN [NUM_IDS=1] [VERSION=4] ...VisualStudio, NO getopt???
* Uses:
*   UUIDGEN 3 <"INPUT-STR"> [NAMESPACE-ID <0-3>]
*   UUIDGEN 4 <NUM-IDs>
*   UUIDGEN 5 <"INPUT-STR"> [NAMESPACE-ID <0-3>]
*
* UUIDGEN versions 3 and 5 accept an optional Namespace ID, where:
*   0 -- DNS namespace
*   1 -- URL namespace
*   2 -- Object-ID (OID) namespace
*   3 -- X.500 namespace 
*
* Default, no args: UUIDGEN 4 1
**********************************************************************/
int main(int argc, char *argv[]) {
    if ((argc == 2) && (!strncmp(argv[1], "-v", 2) || !strncmp(argv[1], "--v", 3))) {
        printf("file-hash: uuidgen v%s\n", FILE_HASH_VERSION);
        return 0;
    } else if((argc == 2) && (!strncmp(argv[1], "-h", 2) || !strncmp(argv[1], "--help", 6))) {
        printf("Usage\n\n\tuuidgen <version> [options]\n\tuuidgen 4 <num-ids>\n\tuuidgen 3 <seed-string>\n\tuuidgen 5 <seed-string>\n\n");
        printf("Specify a version number (3 to 5) for the version of a UUID to generate.\nVersions 3 and 5 require a seed-string to hash with.\n"); 
        printf("Version 4 uses crypto-secure random bytes to build the identifier.\n");
        return 0;
    }
    if (argc > 2) {
        unsigned long numIds = 1;
        unsigned int vnum = 4;
        unsigned int nsid = 0;
        if (sscanf(argv[1], "%d", &vnum) == -1) {
            fprintf(stderr, "Cannot parse UUID version number.\n");
            exit(1);
        }
        char* uuid;
        switch(vnum) {
            case 3:
                if (argc == 4) {
                    if (sscanf(argv[3], "%d", &nsid) == -1) {
                        fprintf(stderr, "Cannot parse namespace ID number.\n");
                        exit(1);
                    }
                }
                switch(nsid) {
                    case 0:
                        uuid = uuid3(STR_UUID_DNS, argv[2]);
                        break;
                    case 1:
                        uuid = uuid3(STR_UUID_URL, argv[2]);
                        break;
                    case 2:
                        uuid = uuid3(STR_UUID_OID, argv[2]);
                        break;
                    case 3:
                        uuid = uuid3(STR_UUID_X500, argv[2]);
                        break;
                    default:
                        uuid = uuid3(STR_UUID_DNS, argv[2]);
                        break;
                } // switch
                printf("%.36s\n", uuid);
                free(uuid);
                return 0;
            case 4:
                if (sscanf(argv[2], "%lu", &numIds) == -1) {
                    fprintf(stderr, "Cannot parse # of version-4 UUIDs to generate.\n");
                    exit(1);
                }
                unsigned int iterIdx;
                for (iterIdx = 0; iterIdx < numIds; iterIdx++) {
                    uuid = uuid4();
                    printf("%.36s\n", uuid);
                    free(uuid);
                }
                return 0;
            case 5:
                switch(nsid) {
                    case 0:
                        uuid = uuid5(STR_UUID_DNS, argv[2]);
                        break;
                    case 1:
                        uuid = uuid5(STR_UUID_URL, argv[2]);
                        break;
                    case 2:
                        uuid = uuid5(STR_UUID_OID, argv[2]);
                        break;
                    case 3:
                        uuid = uuid5(STR_UUID_X500, argv[2]);
                        break;
                    default:
                        uuid = uuid5(STR_UUID_DNS, argv[2]);
                        break;
                } // switch
                printf("%.36s\n", uuid);
                free(uuid);
                return 0;
            default:
                fprintf(stderr, "Invalid version number %d.\n", (int)vnum);
                exit(1);
        } // switch
    } else if (argc == 1) {
        char *uuid = uuid4();
        printf("%.36s\n", uuid);
        free(uuid);
        return 0;
    } else {
        fprintf(stderr, "Invalid syntax.\n");
        exit(1);
    }
}
