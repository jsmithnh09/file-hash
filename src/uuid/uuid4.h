#ifndef __UUID4_H__
#define __UUID4_H__

/*********************************************************************
* Filename:   uuid4.h
* Author:     Jordan Smith
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    signatures/headers for generating version 4 UUIDs.

*********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdint.h>
#include <string.h>
#include <stdio.h>

/****************************** MACROS ******************************/
#define NUM_UUID4_BYTES 16

/*********************** FUNCTION DECLARATIONS **********************/
#ifdef WIN32
    uint8_t* win32_cryptrand(void);
#else
    uint8_t cryptrand(void);
#endif
char* uuid4(void);

#endif