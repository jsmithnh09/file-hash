/*********************************************************************
* Filename:   md5.h
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Defines the API for the corresponding MD5 implementation.
*********************************************************************/

#ifndef __MD5_H__
#define __MD5_H__

/*************************** HEADER FILES ***************************/
#include "common.h"

/****************************** MACROS ******************************/
#define MD5_BLOCK_SIZE 16               // MD5 outputs a 16 byte digest
#define MD5_STRLEN     32               // hex-string length.

/**************************** DATA TYPES ****************************/
typedef struct {
   uint8_t data[64];
   uint32_t datalen;
   unsigned long long bitlen;
   uint32_t state[4];
} MD5_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
void md5_init(MD5_CTX *ctx);
void md5_update(MD5_CTX *ctx, const uint8_t data[], size_t len);
void md5_final(MD5_CTX *ctx, uint8_t hash[]);
char* md5_file(const char* filename);
uint8_t* md5_bytes(const void* buffer, size_t nbElements);
void md5_closefile(void);

#endif   // MD5_H
