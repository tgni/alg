/*
 * File:
 *	tree.c
 * Description:
 *	searching tree implementation
 * History:
 *	Sep 16, 2016	Tgni	Create
 */

#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "types.h"
#include "que.h"
#include "tree.h"

typedef struct tree_node_s {
	list_head_t  list;
	element_t e;
	uint32_t level;
#define DIST_MAX	(100)
	uint32_t dist;
	search_tree_t *left;
	search_tree_t *right;
} tree_node_t;

search_tree_t * make_empty(search_tree_t * t)
{
	if (t) {
		make_empty(t->left);
		make_empty(t->right);
		free(t);
	}

	return NULL;
}

/*
search_tree_t * make_empty(search_tree_t * t)
{
	que_t que;

	if (!t) return NULL;

	que_init(&que, "tree que", 0);
	enqueue(&que, t);

	while ((t = dequeue(&que))) {
		if (t->left)
			enqueue(&que, t->left);
		if (t->right)
			enqueue(&que, t->right);
		free(t);
	}

	return NULL;
}
*/

position_t * find(element_t e, search_tree_t * t)
{
	if (!t)
		return NULL;
	if (e < t->e)
		return find(e, t->left);
	else if (e > t->e)
		return find(e, t->right);

	return t;
}

/*
position_t *find(element_t e, search_tree_t *t)
{
	if (!t)
		return NULL;

	while (t) {
		if (e < t->e)
			t = t->left;
		else if (e > t->e)
			t = t->right;
		else
			return t;
	}

	return NULL;
}
*/

position_t * find_min(search_tree_t * t)
{
	if (!t)
		return NULL;
	else if (!t->left)
		return t;
	else
		return find_min(t->left);
}

position_t * find_max(search_tree_t * t)
{
	if (t) {
		while (t->right)	
			t = t->right;
	}

	return t;
}

search_tree_t * __insert(element_t e, uint32_t level, uint32_t dist, search_tree_t * t)
{
	if (!t) {
		if (!(t = malloc(sizeof(tree_node_t)))) {
			printf("malloc failed\n");
			return NULL;
		}

		t->e      = e;
		t->left   = t->right = NULL;
		t->level  = level; 
		t->dist   = dist;
	} else if (e < t->e) {
		t->left  = __insert(e, level+1, dist - round(DIST_MAX/pow(2, level)), t->left);
	} else if (e > t->e) {
		t->right = __insert(e, level+1, dist + round(DIST_MAX/pow(2, level)), t->right);
	} else {
		/* e == t->e; do nothing */
	}

	return t;
}

search_tree_t * insert(element_t e, search_tree_t * t)
{
	return __insert(e, 1, DIST_MAX, t);
}

search_tree_t * delete(element_t e, search_tree_t * t)
{
	position_t * tmpcell;

	if (!t) {
		printf("element %d not found\n", e);
		return t;
	} else if (e < t->e) {
		t->left = delete(e, t->left);
	} else if (e > t->e) {
		t->right = delete(e, t->right);
	} else if (t->left && t->right) {
		tmpcell  = find_min(t->right);
		t->e     = tmpcell->e;
		t->right = delete(t->e, t->right); 
	} else {
		tmpcell = t;
		if (!t->left)
			t = t->right;
		else if (!t->right)
			t = t->left;
		free(tmpcell);
	}

	return t;
}

#if 0
static inline void print_e(search_tree_t * t, int32_t depth)
{
	int32_t i;

	for (i = 0; i < depth; ++i)
		printf("\t");
	printf("(%s|%d|%d)%d\n", 
		(t->pos == ROOT) ? "root" : (t->pos == LEFT) ? "left" : "right",
		t->dist,
		t->level,
		t->e);

	return;
}

static inline void print(search_tree_t * t, int32_t  depth)
{
	if (t) {
		print_e(t, depth);
		print(t->left, depth+1);
		print(t->right, depth+1);
	}

	return;
}

void print_tree(search_tree_t * t)
{
	print(t, 0);
}
#else

static int32_t LEVEL = 0;
static int32_t DIST  = 0;
static char BUF[1024] = {0};
static int32_t BUF_POS = 0;

void print_e(search_tree_t *t)
{
	int32_t i;
	int32_t left_pos, right_pos;

	if (t->level != LEVEL) {
		DIST = t->dist;
		printf("\n");
		for (i = 0; i < BUF_POS; ++i) {
			printf("%c", BUF[i]);
		}
		printf("\n");

		memset(BUF, 0, sizeof(BUF));
		BUF_POS = 0;
	} else {
		DIST = t->dist - DIST - 1;
	}

	for (i = 0; i < DIST; ++i)
		printf(" ");

	DIST  = t->dist;
	LEVEL = t->level;

	printf("%d", t->e);

	left_pos  = t->dist - round(DIST_MAX/pow(2, t->level));
	right_pos = t->dist + round(DIST_MAX/pow(2, t->level));

	if (t->left && !t->right) {
		for ( ; BUF_POS < left_pos; ++BUF_POS) {
			BUF[BUF_POS] = ' ';
		}
		BUF[BUF_POS++] = '/';
		for ( ; BUF_POS < t->dist; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '|';
	} else if (!t->left && t->right) {
		for ( ; BUF_POS < t->dist; ++BUF_POS) {
			BUF[BUF_POS] = ' ';
		}
		BUF[BUF_POS++] = '|';
		for ( ; BUF_POS < right_pos; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '\\';
	} else if (t->left && t->right) {
		for ( ; BUF_POS < left_pos; ++BUF_POS) {
			BUF[BUF_POS] = ' ';
		}
		BUF[BUF_POS++] = '/';
		for ( ; BUF_POS < t->dist; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '|';
		for ( ; BUF_POS < right_pos; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '\\';
	}

	return;
}

void print_tree(search_tree_t * t)
{
	que_t que;

	if (!t) 
		return;

	que_init(&que, "tree que", offset_of(tree_node_t, list));
	enqueue(&que, t);

	while ((t = dequeue(&que))) {
		print_e(t);
		if (t->left)
			enqueue(&que, t->left);
		if (t->right)
			enqueue(&que, t->right);
	}

	printf("\n");

	return;
}
#endif
