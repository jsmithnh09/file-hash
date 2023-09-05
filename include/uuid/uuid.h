#ifndef __UUID_H__
#define __UUID_H__

/*********************************************************************
* Filename:   uuid.h
* Author:     Jordan Smith
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    signatures/headers for generating version 4 UUIDs.

*********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/****************************** MACROS ******************************/
#define NUM_UUID_BYTES  16
#define NUM_UUID_CHARS  36

// from the UUID RFC, four namespaces defined for v3 and v5.
#define STR_UUID_DNS    "6ba7b810-9dad-11d1-80b4-00c04fd430c8"
#define STR_UUID_OID    "6ba7b812-9dad-11d1-80b4-00c04fd430c8"
#define STR_UUID_URL    "6ba7b811-9dad-11d1-80b4-00c04fd430c8"
#define STR_UUID_X500   "6ba7b814-9dad-11d1-80b4-00c04fd430c8"

/*********************** FUNCTION DECLARATIONS **********************/
#ifdef _WIN32
    uint8_t* win32_cryptrand(void);
#else
    uint8_t cryptrand(void);
#endif
char* bin2uuid(uint8_t *buffer);
uint8_t* uuid2bin(const char* uuid);
char* uuid3(const char* namespace, const char* instr);
char* uuid4(void);
char* uuid5(const char* namespace, const char* instr);


#endif