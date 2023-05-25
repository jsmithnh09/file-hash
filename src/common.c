/*********************************************************************
* Filename:   common.c
* Author:     Jordan Smith
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Common code for making platform-agnostic filesize reads.
*********************************************************************/

/*************************** HEADER FILES ***************************/
#include "common.h"
#include <string.h>
#include <stdio.h>

/***************************** MACROS *******************************/
//#if defined(_WIN32)
//    #define stat64 _stat64
//    #define stat __stat64
//#endif

/*********************** FUNCTION DEFINITIONS ***********************/

// determine the filesize.
off_t get_filesize(const char *filename)
{
    struct stat64 buf;
    int err;
    err = stat64(filename, &buf);
    if ((err != 0) || (err == ENOENT))
    {
        perror(filename);
        exit(1);
    }
    return buf.st_size;
}


BYTE* data_chunks(const char* filename, size_t *blocksize)
{
    off_t filesize;   
    int idx, err, bytes;
    size_t numFilesizeBytes;

    numFilesizeBytes = (size_t)(sizeof(off_t) / sizeof(BYTE));
    *blocksize = (BYTE_BATCH_SIZE * 3) + numFilesizeBytes;
    
    // the filesize to compute a "quicker" hash.
    BYTE *data = (BYTE*)calloc(*blocksize, sizeof(BYTE));
    filesize = get_filesize(filename);
    BYTE* fsizeBytes = (BYTE *)&filesize;
    
    // read head, middle, and tail batches.
    FILE* fid = fopen(filename, "rb");
    if (fid == NULL)
    {
        perror(filename);
        exit(1);
    }

    // specify the positions and read head/middle/tail.
    off_t positions[3] = {0, (off_t)(filesize / 2), (off_t)filesize - BYTE_BATCH_SIZE};
    for (idx = 0; idx < 3; idx++)
    {
        err = fseeko(fid, positions[idx], SEEK_SET);
        if (err != 0)
        {
            fclose(fid);
            printf("data_chunk: Cannot read chunk of file.\n");
            exit(1);
        }
        bytes = fread(&data[BYTE_BATCH_SIZE*idx], 1, BYTE_BATCH_SIZE, fid);
        if (bytes != BYTE_BATCH_SIZE)
        {
            fclose(fid);
            printf("data_chunk: data batch not equal to # of bytes read.\n");
            exit(1);
        }
    }

    // write the uint64_t value as bytes at the end of the data block.
    for(idx = 0; idx < numFilesizeBytes; idx++)
    {
        data[(BYTE_BATCH_SIZE * 3) + idx] = fsizeBytes[idx];
    }
    return data;
}