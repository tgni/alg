/*
 * Copyright: (c) 2014-2020, 2014 Triductor Technology, Inc.
 * All Rights Reserved.
 *
 * File:        crc.c
 * Purpose:     crc function
 * History:
 *	Jan 26, 2015	tgni    Create
 */
#include "crc.h"

#define K_CRC_POLY	0xEDB88320

uint32_t crc_table[256];


void init_crc_table()
{
	int32_t i, j;
	uint32_t r;

	for (i = 0; i < 256; ++i) {
		r = i;

		for (j = 0; j < 8; ++j)
			if (r & 1)
				r = (r >> 1) ^ K_CRC_POLY;
			else
				r >>= 1;

		crc_table[i] = r;
	}
}


uint32_t crc_update(uint8_t *data, uint32_t size)
{
	uint32_t crc = 0xffffffff;

	for (; size > 0 ; --size, ++data) {
		crc = crc_table[((uint8_t)crc) ^ *data] ^ (crc >> 8);
	}

	return crc;
}


int32_t crc_digest_sw(uint8_t *data, uint32_t size, uint32_t *crc)
{
	*crc = crc_update(data, size) ^ 0xffffffff;
	return OK;
}


int32_t crc_digest(uint8_t *data, uint32_t size, uint32_t mode, uint32_t *crc)
{
	switch (mode & CRC_CAC_MASK) {
	case CRC_SW:
		return crc_digest_sw(data, size, crc);
	default:
		//assert_s(FALSE);
		return ERROR;
	}
}

int32_t crc_init(void)
{
	init_crc_table();
	return OK;
}
