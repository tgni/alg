/*
 * File:	que.h
 * Purpose:	Message queue manipulation structures.
 * History:
 *	Sep 16, 2016	tgni	create
 */

#ifndef __QUE_H__
#define __QUE_H__

#include "types.h"
#include "list.h"

typedef struct que_s {
	int32_t nr;
	int32_t offset;
	int32_t thd;
	struct list_head head;
} que_t;

extern void que_init(que_t *q, char *name, int32_t offset);
extern void enqueue(que_t *q, void *obj);
extern void * dequeue(que_t *q);

#endif	/* end of __QUE_H__ */
