#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "rbtree.h"
#include "que.h"

rb_tree_t tr;
sta_t sta_entry[NR_TEI_MAX];

int32_t tei_cmp(struct rb_node *n, void *key)
{
	uint16_t *tei = (uint16_t *)key;
	sta_t *sta = rb_entry(n, sta_t, rb);

	return memcmp(&sta->tei, tei, 2);
}

void compute_dist_and_depth(rb_tree_t *r)
{
	que_t que;
	struct rb_node *t = r->root.rb_node;

	que_init(&que, "rb tree que", offset_of(struct rb_node, list));

	t->dist  = DIST_MAX;
	t->depth = 0;
	enqueue(&que, t);

	while ((t = dequeue(&que))) {
		if (t->rb_left) {
			t->rb_left->depth = t->depth + 1;
			t->rb_left->dist  = t->dist - round(DIST_MAX/pow(2, t->rb_left->depth));
			enqueue(&que, t->rb_left);	
		}
		if (t->rb_right) {
			t->rb_right->depth = t->depth + 1;
			t->rb_right->dist  = t->dist + round(DIST_MAX/pow(2, t->rb_right->depth));
			enqueue(&que, t->rb_right);
		}
	}

	return;
}

static int32_t DEPTH = 0;
static int32_t DIST  = 0;
static int32_t WIDTH = 0;
static char BUF[1024] = {0};
static int32_t BUF_POS = 0;

static inline int32_t compute_width(int32_t x)
{
	int32_t width = 0;

	if (x < 0) {
		x = -x;
		++width;
	}
	do {
		++width;
	} while ((x /= 10) > 0);

	return width;
}

void print_rb_node(struct rb_node *t)
{
	int32_t i;
	sta_t *sta = rb_entry(t, sta_t, rb);
	char c[3] = {'-', 'r', 'b'};

	if (t->depth != DEPTH) {
		printf("\n");
		DIST = t->dist;
		BUF[BUF_POS++] = '\n';
		BUF[BUF_POS]   = '\0';
		printf("%s", BUF);
		//memset(BUF, 0, sizeof(BUF));
		BUF_POS = 0;
	} else {
		DIST = t->dist - DIST - WIDTH;
	}

	for (i = 0; i < DIST; ++i)
		printf(" ");
	printf("%d%c", sta->tei, c[t->rb_color]);

	DIST  = t->dist;
	DEPTH = t->depth;
	WIDTH = compute_width(sta->tei) + 1; // plus color width=1

	if (t->rb_left && !t->rb_right) {
		for ( ; BUF_POS < t->rb_left->dist; ++BUF_POS) {
			BUF[BUF_POS] = ' ';
		}
		BUF[BUF_POS++] = '/';
		for ( ; BUF_POS < t->dist; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '|';
	} else if (!t->rb_left && t->rb_right) {
		for ( ; BUF_POS < t->dist; ++BUF_POS) {
			BUF[BUF_POS] = ' ';
		}
		BUF[BUF_POS++] = '|';
		for ( ; BUF_POS < t->rb_right->dist; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '\\';
	} else if (t->rb_left && t->rb_right) {
		for ( ; BUF_POS < t->rb_left->dist; ++BUF_POS) {
			BUF[BUF_POS] = ' ';
		}
		BUF[BUF_POS++] = '/';
		for ( ; BUF_POS < t->dist; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '|';
		for ( ; BUF_POS < t->rb_right->dist; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '\\';
	}

	return;
}

void print_rb_tree(rb_tree_t *r)
{
	que_t que;
	struct rb_node *t = r->root.rb_node;


	que_init(&que, "rbtree que", offset_of(struct rb_node, list));
	enqueue(&que, t);

	while ((t = dequeue(&que))) {
		print_rb_node(t);
		if (t->rb_left)
			enqueue(&que, t->rb_left);
		if (t->rb_right)
			enqueue(&que, t->rb_right);
	}

	printf("\n");

	return;
}

int main(int argc, char *argv[])
{
	struct rb_node **p, *pa;
	struct rb_node *iter = NULL;
	sta_t *sta;
	int32_t i;
	uint32_t nr;

	if (argc < 2) {
		printf("Usage: ./rbtree <NUM>\n");
		return -1;
	}

	nr = strtoul(argv[1], NULL, 0);

	if (!(sta = malloc(sizeof(sta_t) * nr))) {
		printf("malloc failed\n");
		return -1;
	}
	memset(sta, 0, sizeof(sta_t) * nr);

	rb_tree_init(&tr,
		tei_cmp,
		rb_tree_find_default,
		rb_tree_insert_default,
		rb_tree_erase_default,
		(rb_treenode_del_fp)0,
		rb_tree_finalize_default);

	for (i = 0; i < nr; ++i) {
	//for (i = nr-1; i >= 0; --i) {
		sta[i].tei = i + 1;
		//sta[i].tei = rand() % nr;
		if (*(p = tr.find(&tr, &sta[i].tei, &pa))) {
			printf("Duplicate tei: %d\n", sta[i].tei);	
			continue;
		}

		tr.insert(&tr, &sta[i].rb, pa, p);	
	}

	compute_dist_and_depth(&tr);
	print_rb_tree(&tr);

	return 0;
}
