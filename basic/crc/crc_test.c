/*
 * Copyright: (c) 2014-2020, 2014 Triductor Technology, Inc.
 * All Rights Reserved.
 *
 * File:        crc.c
 * Purpose:     crc function
 * History:
 *	Jan 26, 2015	tgni    Create
 */
//#include "lightelf_acu_reg.h"
//#include "ose_printf.h"
#include <stdio.h>
#include "crc.h"

#define DATA_LEN	(1025)

//int32_t test_data[DATA_LEN / 4] __attribute__((aligned(32)));
int8_t test_data[DATA_LEN] __attribute__((aligned(32)));
void crc_test(void)
{
	int32_t i;
	uint32_t out;

	for (i = 0; i < (DATA_LEN - 1) / 2; ++i)
		test_data[i] = 0xaa;

	for (i = (DATA_LEN - 1) / 2; i < (DATA_LEN - 1); ++i)
		test_data[i] = 0x55;

	test_data[DATA_LEN - 1] = 0x5a;

	//crc_digest((uint8_t *)test_data, DATA_LEN, CRC_32 | CRC_HW, &out);	
	//printf_d("hw:0x%08x\n", out);
	out = 0;
	crc_digest((uint8_t *)test_data, DATA_LEN, CRC_32 | CRC_SW, &out);	
	printf("sw:0x%08x\n", out);

	return;
}


int main(void)
{
	crc_init();
	crc_test();

	return 0;
}
