/*
 * File:	stack.h
 * Purpose:	simple stack implementation
 * History:
 *	Feb 8, 2017	tgni	create
 */
#ifndef __STACK_H__
#define __STACK_H__

#include "types.h"
#include "list.h"

typedef struct stack_s {
	char *name;
	int32_t nr;
	int32_t offset;
	int32_t thd;
	list_head_t head;
} stack_t;

extern void stack_init(stack_t *s, char *name, int32_t offset);
extern void push(stack_t *s, void *obj);
extern void * pop(stack_t *s);

#endif /* end of __STACK_H__ */
