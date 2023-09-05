/*********************************************************************
* Filename:   common.h
* Author:     Jordan Smith
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Common definitions for use across hashing/checksums.

*********************************************************************/

#ifndef __COMMON_H__
#define __COMMON_H__

/*************************** HEADER FILES ***************************/
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

/****************************** MACROS ******************************/
#define BYTE_BATCH_SIZE     2048   //  2048 bytes = 64 KB.
#define SMALL_THRESHOLD     16384  //  128 KB small file thresold.

#define FILE_IS_SMALL(x) (x < SMALL_THRESHOLD)

#endif
