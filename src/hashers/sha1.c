/*********************************************************************
* Filename:   sha1.c
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Implementation of the SHA1 hashing algorithm.
              Algorithm specification can be found here:
               * http://csrc.nist.gov/publications/fips/fips180-2/fips180-2withchangenotice.pdf
              This implementation uses little endian byte order.
*********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "hashers/sha1.h"

/****************************** MACROS ******************************/
#define ROTLEFT(a, b) ((a << b) | (a >> (32 - b)))

/**************************** VARIABLES *****************************/
static FILE* fid;

/*********************** FUNCTION DEFINITIONS ***********************/
void sha1_transform(SHA1_CTX *ctx, const uint8_t data[])
{
	uint32_t a, b, c, d, e, i, j, t, m[80];

	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (data[j] << 24) + (data[j + 1] << 16) + (data[j + 2] << 8) + (data[j + 3]);
	for ( ; i < 80; ++i) {
		m[i] = (m[i - 3] ^ m[i - 8] ^ m[i - 14] ^ m[i - 16]);
		m[i] = (m[i] << 1) | (m[i] >> 31);
	}

	a = ctx->state[0];
	b = ctx->state[1];
	c = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];

	for (i = 0; i < 20; ++i) {
		t = ROTLEFT(a, 5) + ((b & c) ^ (~b & d)) + e + ctx->k[0] + m[i];
		e = d;
		d = c;
		c = ROTLEFT(b, 30);
		b = a;
		a = t;
	}
	for ( ; i < 40; ++i) {
		t = ROTLEFT(a, 5) + (b ^ c ^ d) + e + ctx->k[1] + m[i];
		e = d;
		d = c;
		c = ROTLEFT(b, 30);
		b = a;
		a = t;
	}
	for ( ; i < 60; ++i) {
		t = ROTLEFT(a, 5) + ((b & c) ^ (b & d) ^ (c & d))  + e + ctx->k[2] + m[i];
		e = d;
		d = c;
		c = ROTLEFT(b, 30);
		b = a;
		a = t;
	}
	for ( ; i < 80; ++i) {
		t = ROTLEFT(a, 5) + (b ^ c ^ d) + e + ctx->k[3] + m[i];
		e = d;
		d = c;
		c = ROTLEFT(b, 30);
		b = a;
		a = t;
	}

	ctx->state[0] += a;
	ctx->state[1] += b;
	ctx->state[2] += c;
	ctx->state[3] += d;
	ctx->state[4] += e;
}

void sha1_init(SHA1_CTX *ctx)
{
	ctx->datalen = 0;
	ctx->bitlen = 0;
	ctx->state[0] = 0x67452301;
	ctx->state[1] = 0xEFCDAB89;
	ctx->state[2] = 0x98BADCFE;
	ctx->state[3] = 0x10325476;
	ctx->state[4] = 0xc3d2e1f0;
	ctx->k[0] = 0x5a827999;
	ctx->k[1] = 0x6ed9eba1;
	ctx->k[2] = 0x8f1bbcdc;
	ctx->k[3] = 0xca62c1d6;
}

void sha1_update(SHA1_CTX *ctx, const uint8_t data[], size_t len)
{
	size_t i;

	for (i = 0; i < len; ++i) {
		ctx->data[ctx->datalen] = data[i];
		ctx->datalen++;
		if (ctx->datalen == 64) {
			sha1_transform(ctx, ctx->data);
			ctx->bitlen += 512;
			ctx->datalen = 0;
		}
	}
}

void sha1_final(SHA1_CTX *ctx, uint8_t hash[])
{
	uint32_t i;

	i = ctx->datalen;

	// Pad whatever data is left in the buffer.
	if (ctx->datalen < 56) {
		ctx->data[i++] = 0x80;
		while (i < 56)
			ctx->data[i++] = 0x00;
	}
	else {
		ctx->data[i++] = 0x80;
		while (i < 64)
			ctx->data[i++] = 0x00;
		sha1_transform(ctx, ctx->data);
		memset(ctx->data, 0, 56);
	}

	// Append to the padding the total message's length in bits and transform.
	ctx->bitlen += ctx->datalen * 8;
	ctx->data[63] = ctx->bitlen;
	ctx->data[62] = ctx->bitlen >> 8;
	ctx->data[61] = ctx->bitlen >> 16;
	ctx->data[60] = ctx->bitlen >> 24;
	ctx->data[59] = ctx->bitlen >> 32;
	ctx->data[58] = ctx->bitlen >> 40;
	ctx->data[57] = ctx->bitlen >> 48;
	ctx->data[56] = ctx->bitlen >> 56;
	sha1_transform(ctx, ctx->data);

	// Since this implementation uses little endian byte ordering and MD uses big endian,
	// reverse all the bytes when copying the final state to the output hash.
	for (i = 0; i < 4; ++i) {
		hash[i]      = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4]  = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8]  = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
	}
}

void sha1_closefile(void)
{
	fclose(fid);
}

char* sha1_file(const char* filename) 
{
    unsigned char buffer[SHA1_BLOCK_SIZE]; // final checksum container.
    int ind, bytes, err; // keeps track of size of each byte read.
    SHA1_CTX ctx;
    unsigned char data[BYTE_BATCH_SIZE]; // buffer for each file-read call.
    char *fileprint = (char*)calloc((SHA1_STRLEN)+1, sizeof(char));
    fid = fopen(filename, "rb");
    if (fid == NULL) {
        perror(filename);
        exit(1);
    }
	err = atexit(sha1_closefile);
	if (err != 0)
	{
		fclose(fid);
		printf("SHA1: Unable to register file handler at-exit method.\n");
		exit(1);
	}
    // initialize the checksum state and keep reading bytes from the file.
    sha1_init(&ctx);
    while((bytes = fread(data, 1, BYTE_BATCH_SIZE, fid)) != 0) {
        sha1_update(&ctx, data, bytes);
    }

    // pass the final state to the allocated buffer.
    sha1_final(&ctx, buffer);

    // print each 2-digit hex that represents a single byte into the format string.
    for(ind = 0; ind < SHA1_BLOCK_SIZE; ind++) {
        sprintf(&fileprint[ind*2], "%02x", (unsigned int)buffer[ind]);
    }
    return fileprint;
}

uint8_t* sha1_bytes(const void* buffer, size_t nbElements)
{
	uint8_t* hashbuff = (uint8_t *)calloc(SHA1_BLOCK_SIZE, sizeof(uint8_t));
	uint8_t *byteBuff = (uint8_t *)buffer;
	size_t buffIdx = 0;
	SHA1_CTX ctx;
	sha1_init(&ctx);
	while(buffIdx < nbElements) {
		sha1_update(&ctx, &(byteBuff[buffIdx]), 1);
		buffIdx++;
	}
	sha1_final(&ctx, hashbuff);
	return hashbuff;
}
