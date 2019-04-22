/*
 * File:	que.c
 * Purpose:	Message queue manipulations.
 * History:
 *	Sep 16, 2016	tgni	create
 */

#include "que.h"

void que_init(que_t *q, char *name, int32_t offset)
{
	q->nr	  = 0;
	q->offset = offset;
	INIT_LIST_HEAD(&q->head);

	return;
}

void enqueue(que_t *q, void *obj)
{
        list_head_t *pos;

	pos = (list_head_t *)(obj + q->offset);
	list_add_tail(pos, &q->head);
	++q->nr;

	return;
}

void * dequeue(que_t *q)
{
	void *obj;

	if (list_empty(&q->head))
		return NULL;

	obj = (void *)((char *)q->head.next - q->offset);
	list_del(q->head.next);
	--q->nr;

	return obj;
}
