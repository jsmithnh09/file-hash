/*********************************************************************
* Filename:   sha1.h
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Defines the API for the corresponding SHA1 implementation.
*********************************************************************/

#ifndef __SHA1_H__
#define __SHA1_H__

/*************************** HEADER FILES ***************************/
#include "common.h"

/****************************** MACROS ******************************/
#define SHA1_BLOCK_SIZE 20              // SHA1 outputs a 20 byte digest
#define SHA1_STRLEN 	40				// hex-string length.

/**************************** DATA TYPES ****************************/
typedef struct {
	uint8_t data[64];
	uint32_t datalen;
	unsigned long long bitlen;
	uint32_t state[5];
	uint32_t k[4];
} SHA1_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
void sha1_init(SHA1_CTX *ctx);
void sha1_update(SHA1_CTX *ctx, const uint8_t data[], size_t len);
void sha1_final(SHA1_CTX *ctx, uint8_t hash[]);
char* sha1_file(const char* filename);
uint8_t* sha1_bytes(const void* buffer, size_t nbElements);
void sha1_closefile(void);

#endif   // SHA1_H
