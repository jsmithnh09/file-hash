#include "uuid/uuid.h"
#include <stdio.h>

/*******************************************************************************
 * Test data.
 *******************************************************************************/
// online UUID generators can be used for cross-reference.
 #define UUID_TEST_INPUT    "hashes galore"
 #define UUID_TEST_V3_DNS   "d208dbb3-bb07-371b-af09-df86a62e0c46"
 #define UUID_TEST_V3_URL   "a8513bba-5100-3329-b2f1-f35fb08f4bde"
 #define UUID_TEST_V3_OID   "17fe471c-4b9b-3dae-9939-379d9e3ade32"
 #define UUID_TEST_V3_X500  "5e9562bf-d1e7-3495-89db-290e6bd74f62"

 #define UUID_TEST_V5_DNS   "52edcf36-46a7-545d-abd7-84d459d4843f"
 #define UUID_TEST_V5_URL   "6fea2e76-48f8-501c-80be-680864d9a449"
 #define UUID_TEST_V5_OID   "55e05f43-2b2f-54e4-bb5c-d2918778079b"
 #define UUID_TEST_V5_X500  "3f31bb52-ac6a-5293-a563-7c49c66c075c"


 void test_uuidstring(const char* nspace, const char* knownid, const int vnum) {
    char *uuid;
    if (vnum == 3) {
        uuid = uuid3(nspace, UUID_TEST_INPUT);
    } else {
        uuid = uuid5(nspace, UUID_TEST_INPUT);
    }
    
    if (!strncmp(uuid, knownid, NUM_UUID_CHARS)) {
        free(uuid);
        return;
    } else {
        fprintf(stderr, "version %d FAILURE:\n\tinput:%s\n\tvalid:%s\n", vnum, knownid, uuid);
        free(uuid);
        exit(1);
    }
 }

/*******************************************************************************
 *  TESTUUID tests that the UUID generation does the following:
 *      For version 4, (a) random ID's are generated.
 *      For versions 3 and 5, a known UUID is returned for a given string seed.
 *******************************************************************************/
 int main(int argc, char* argv[]) {
    // version 3, (MD5.)
    test_uuidstring(STR_UUID_DNS,  UUID_TEST_V3_DNS,  3);
    test_uuidstring(STR_UUID_URL,  UUID_TEST_V3_URL,  3);
    test_uuidstring(STR_UUID_OID,  UUID_TEST_V3_OID,  3);
    test_uuidstring(STR_UUID_X500, UUID_TEST_V3_X500, 3);
    
    // version 5, (SHA1.)
    test_uuidstring(STR_UUID_DNS,  UUID_TEST_V5_DNS,  5);
    test_uuidstring(STR_UUID_URL,  UUID_TEST_V5_URL,  5);
    test_uuidstring(STR_UUID_OID,  UUID_TEST_V5_OID,  5);
    test_uuidstring(STR_UUID_X500, UUID_TEST_V5_X500, 5);

    // for version 4, we want to test previous UUIDs don't produce the same UUID.
    int iterIdx = 0;
    while(iterIdx < 1000) {
        if (!strncmp(uuid4(), uuid4(), NUM_UUID_CHARS)) {
            fprintf(stderr, "version 4 FAILURE: recurrent UUIDs generated.\n");
            exit(1);
        } else {
            iterIdx++;
        }
    }
    printf("SUCCESS\n");
    return 0;
 }