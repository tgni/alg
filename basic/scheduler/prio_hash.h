#ifndef __PRIO_HASH_H__
#define __PRIO_HASH_H__

#include "types.h"

typedef struct prio_hash_s {
	uint8_t set;
	uint8_t group[8];
} prio_hash_t;

extern int8_t const os_ffsb[];

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

#endif /* __PRIO_HASH_H__ */
