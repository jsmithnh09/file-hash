#include <stdio.h>
#include "hashers/md5.h"
#include "hashers/sha1.h"
#include "hashers/sha256.h"
#include "hashers/crc32.h"

/**********************************************************************
 * TESTHASH tests the hashing algorithms to confirm expected results.
 **********************************************************************/

#define TEST_HASH_INPUT         "hello world!"
#define TEST_HASH_INPUT_LEN     12
#define TEST_HASH_CRC32         "03b4c26d"
#define TEST_HASH_MD5           "fc3ff98e8c6a0d3087d515c0473f8677"
#define TEST_HASH_SHA1          "430ce34d020724ed75a196dfc2ad67c77772d169"
#define TEST_HASH_SHA256        "7509e5bda0c762d2bac7f90d758b5b2263fa01ccbc542ab5e3df163be08e6ca9"

int main(int argc, char* argv[]) {
    // we can feed this into the "_bytes" method instead of using the pre-existing file.
    char *input;
    char *hexstr;
    uint8_t *buff;
    uint32_t word;
    int ind;
    input = (char*)calloc(TEST_HASH_INPUT_LEN+1, sizeof(char));
    strcpy(input, TEST_HASH_INPUT);
    

    /*
     * Testing CRC32.
     */
    hexstr = (char*)calloc((CRC32_STRLEN)+1, sizeof(char));
    word = crc32_bytes((void *)input, strlen(input)); // could be smarter and use a lambda.
    sprintf(hexstr, "%08x", word);

    if (strncmp(hexstr, TEST_HASH_CRC32, CRC32_STRLEN)) {
        fprintf(stderr, "FAILURE: CRC32 mismatch:\n\t%s\n\t%s\n", hexstr, TEST_HASH_CRC32);
        free(hexstr);
        free(input);
        exit(1);
    }
    free(hexstr);

    /*
     * Testing MD5.
     */
    hexstr = (char*)calloc((MD5_STRLEN)+1, sizeof(char));
    buff = md5_bytes((void *)input, strlen(input));
    for (ind = 0; ind < MD5_BLOCK_SIZE; ind++) {
        sprintf(&hexstr[ind*2], "%02x", (unsigned int)buff[ind]);
    }
    if (strncmp(hexstr, TEST_HASH_MD5, MD5_STRLEN)) {
        fprintf(stderr, "FAILURE: MD5 mismatch:\n\t%s\n\t%s\n", hexstr, TEST_HASH_MD5);
        free(hexstr);
        free(input);
        free(buff);
        exit(1);
    }
    free(buff);
    free(hexstr);

    /*
     * Testing SHA1.
     */
    hexstr = (char*)calloc((SHA1_STRLEN)+1, sizeof(char));
    buff = sha1_bytes((void *)input, strlen(input));
    for (ind = 0; ind < SHA1_BLOCK_SIZE; ind++) {
        sprintf(&hexstr[ind*2], "%02x", (unsigned int)buff[ind]);
    }
    if (strncmp(hexstr, TEST_HASH_SHA1, SHA1_STRLEN)) {
        fprintf(stderr, "FAILURE: SHA1 mismatch:\n\t%s\n\t%s\n", hexstr, TEST_HASH_SHA1);
        free(hexstr);
        free(input);
        free(buff);
        exit(1);
    }
    free(buff);
    free(hexstr);

    /*
     * Testing SHA256.
     */
    hexstr = (char*)calloc((SHA256_STRLEN)+1, sizeof(char));
    buff = sha256_bytes((void *)input, strlen(input));
    for (ind = 0; ind < SHA256_BLOCK_SIZE; ind++) {
        sprintf(&hexstr[ind*2], "%02x", (unsigned int)buff[ind]);
    }
    if (strncmp(hexstr, TEST_HASH_SHA256, SHA256_STRLEN)) {
        fprintf(stderr, "FAILURE: SHA256 mismatch:\n\t%s\n\t%s\n", hexstr, TEST_HASH_SHA256);
        free(hexstr);
        free(input);
        free(buff);
        exit(1);
    }
    free(buff);
    free(hexstr);

    // clean up last items.
    free(input);
    printf("SUCCESS\n");
    return 0;
}