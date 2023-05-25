/*********************************************************************
* Filename:   crc32.h
* Author:     Jordan Smith
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Implementation of the CRC32 checksum algorithm.
				  This implementation uses little endian byte order.
*********************************************************************/

#ifndef __CRC32_H__
#define __CRC32_H__

/*************************** HEADER FILES ***************************/
#include "common.h"

/****************************** MACROS ******************************/
#define CRC32_BLOCK_SIZE    4
#define CRC32_INITIAL       0xFFFFFFFF
#define CRC32_POLY          0xEDB88320         /* p(x) reflected, with x^32 implied */
#define CRC32_STRLEN        8

/**************************** DATA TYPES ****************************/
typedef struct {
    BYTE table[256];
    WORD state;
} CRC32_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
void crc32_init(CRC32_CTX *ctx);
void crc32_update(CRC32_CTX *ctx, const BYTE data[], size_t len);
void crc32_final(CRC32_CTX *ctx);
char* crc32_file(const char* filename);
void crc32_closefile(void);


#endif
