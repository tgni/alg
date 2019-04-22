#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#if 0
#define NR_MAX_FLOW	(1 << 9)
/* type=3bit, dir=1bit, dtei=8bit, lid=8bit */
uint32_t hash_idx(uint8_t type, uint8_t dir, uint8_t dtei, uint8_t lid)
{
	int32_t idx = type;

	idx = (idx << 8) ^ dtei;
	idx = (idx << 1) ^ dir;
	idx = (idx << 8) ^ lid;

	idx ^= (idx >> 1);
	idx ^= (idx >> 8);
	idx ^= (idx >> 3);

	idx &= (NR_MAX_FLOW - 1);

	return idx;
}


main()
{
	uint32_t type, dir, dtei, lid;
	uint32_t idx;

	for (type = 0; type < 1; ++type) {
		for (dir = 0; dir < 2; ++dir) {
			for (dtei = 0; dtei < 1; ++dtei) {
				for (lid = 0; lid < 256; ++lid) {
					printf("%d ", hash_idx(type, dir, dtei, lid));
				}
				printf("\n");
			}
		}
	}
}
#endif

#define NR_HASH_MAX	64	

uint32_t statis[NR_HASH_MAX];

uint32_t hash_tei(uint16_t tei)
{
	//return tei & (NR_HASH_MAX-1);
	return tei % NR_HASH_MAX;
	/*
	uint32_t x;
	
	x = tei & 0xFF;
	x = (x << 8) ^ (tei >> 8);
	x ^= x >> 8;

	return x & (NR_HASH_MAX - 1);
	*/
}

int main(int argc, char *argv[])
{
	int32_t nr_tei, i;
	
	if (argc != 2) {
		printf("Usage: ./test <NR_STA>\n");
		return -1;
	}

	nr_tei = strtoul(argv[1], NULL, 0);	

	for (i = 0; i < nr_tei; ++i)
		++statis[hash_tei(i)];

	for (i = 0; i < NR_HASH_MAX; ++i)
		printf("index: %d count %d\n", i, statis[i]);

	return 0;
}
