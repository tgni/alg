#ifndef _RADIX_SORT_H_
#define _RADIX_SORT_H_

#include "types.h"
#include "list.h"

typedef struct bucket_s {
	list_head_t *base;
	int32_t nr;
} bucket;

typedef	struct bitem_s {
	list_head_t node;
	int32_t	e;
} bitem_t;

#endif /* _RADIX_SORT_H_ */
