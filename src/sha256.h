
/*********************************************************************
* Filename:   sha256.h
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Defines the API for the corresponding SHA1 implementation.
*********************************************************************/

#ifndef __SHA256_H__
#define __SHA256_H__

/*************************** HEADER FILES ***************************/
#include "common.h"

/****************************** MACROS ******************************/
#define SHA256_BLOCK_SIZE 	32            // SHA256 outputs a 32 byte digest
#define SHA256_STRLEN 		  64			      // hex-string length on output.

/**************************** DATA TYPES ****************************/
typedef struct {
	BYTE data[64];
	WORD datalen;
	unsigned long long bitlen;
	WORD state[8];
} SHA256_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const BYTE data[], size_t len);
void sha256_final(SHA256_CTX *ctx, BYTE hash[]);
char* sha256_file(const char* filename);
char* sha256_file_quick(const char* filename, BYTE quick);
void sha256_closefile(void);

#endif   // SHA256_H
