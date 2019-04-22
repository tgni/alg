#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "prio_hash.h"

/* Find First(least-significant) Set Bit (in least-significant way) */
int8_t const os_ffsb[256] = {
	-1, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x00 to 0x0F */
	4,  0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x10 to 0x1F */
	5,  0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x20 to 0x2F */
	4,  0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x30 to 0x3F */
	6,  0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x40 to 0x4F */
	4,  0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x50 to 0x5F */
	5,  0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x60 to 0x6F */
	4,  0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x70 to 0x7F */
	7,  0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x80 to 0x8F */
	4,  0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x90 to 0x9F */
	5,  0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xA0 to 0xAF */
	4,  0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xB0 to 0xBF */
	6,  0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xC0 to 0xCF */
	4,  0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xD0 to 0xDF */
	5,  0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xE0 to 0xEF */
	4,  0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0        /* 0xF0 to 0xFF */
};

static inline int32_t get_highest_prio(prio_hash_t *hash)
{
	uint8_t x, y, ret;

	if (!hash->set)
		return -1;

	y = os_ffsb[hash->set];
	x = os_ffsb[hash->group[y]];

	return (y << 3) + x;
}

static inline void set_prio_hash(int32_t prio, prio_hash_t *hash)
{
	uint8_t x, y;

	y = (prio >> 3) & 0x7;
	x = prio & 0x7;
	hash->set |= 1 << y;
	hash->group[y] |= 1 << x;
}

static inline void clr_prio_hash(int32_t prio, prio_hash_t *hash)
{
	uint8_t x, y;
	
	y = (prio >> 3) & 0x7;
	x = prio & 0x7;
	hash->group[y] &= ~(1 << x);

	if (!hash->group[y])
		hash->set &= ~(1 << y);
}

static inline void dump_prio_hash(prio_hash_t *hash)
{
	uint8_t i, j; 

	printf("\nhash->set:\n\t[");
	for (i = 0; i < 8; ++i) {
		if (hash->set & (1 << i))
			printf("1");
		else 
			printf("0");
	}
	printf("]\n");
	printf("hash->group = [\n\t");
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (hash->group[i] & (1 << j))
				printf("1");	
			else
				printf("0");	
		}
		printf("\n\t");
	}
	printf("]\n");
}


int main(int argc, char* argv[])
{
	prio_hash_t hash;
	int prio, tmp;

	memset(&hash, 0, sizeof(prio_hash_t));
#if 0
	for (prio = 0; prio < 64; prio++) {
		set_prio_hash(prio, &hash);	
	}

	dump_prio_hash(&hash);

	printf("\n");
	for (prio = 0; prio < 64; prio++) {
		clr_prio_hash(prio, &hash);	
		tmp = get_highest_prio(&hash);		
		printf(" %d", tmp);
	}

	printf("\n");
#endif
	if (argc < 2) {
		printf("usage: ./run num[int]\n");
		return -1;
	}

	set_prio_hash(atoi(argv[1]), &hash);
	dump_prio_hash(&hash);

	return 0;
}
