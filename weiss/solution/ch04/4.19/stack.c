/*
 * File:	stack.c
 * Purpose:	simple stack implementation using linked list
 * History:
 *	Sep 16, 2016	tgni	create
 */

#include "stack.h"

void stack_init(stack_t *s, char *name, int32_t offset)
{
	s->name   = name;
	s->nr	  = 0;
	s->offset = offset;
	INIT_LIST_HEAD(&s->head);

	return;
}

void push(stack_t *s, void *obj)
{
        list_head_t *pos;

	pos = (list_head_t *)(obj + s->offset);
	list_add(pos, &s->head);
	++s->nr;

	return;
}

void * pop(stack_t *s)
{
	void *obj;

	if (list_empty(&s->head))
		return NULL;

	obj = (void *)((char *)s->head.next - s->offset);
	list_del(s->head.next);
	--s->nr;

	return obj;
}
