#include "rbtree.h"

#define NR_TEI_MAX 256
typedef struct sta_s {
	uint16_t tei;
	struct rb_node rb;
} sta_t;

rb_tree_t tr;
sta_t sta_entry[NR_TEI_MAX];

int32_t tei_cmp(struct rb_node *n, void *key)
{
	uint16_t *tei = (uint16_t *)key;
	sta_t *sta = rb_entry(n, sta_t, rb);

	return memcmp(&sta->tei, tei, 2);
}

int test_routing(void)
{
	uint16_t tei;
	struct rb_node **p, *pa;
	struct rb_node *iter = NULL;
	sta_t *sta;

	rb_tree_init(&tr,
		tei_cmp,
		rb_tree_find_default,
		rb_tree_insert_default,
		rb_tree_erase_default,
		(rb_treenode_del_fp)0,
		rb_tree_finalize_default);

	for (tei = NR_TEI_MAX - 1; tei > 0; --tei) {
		if (*(p = tr.find(&tr, &tei, &pa))) {
			printf("Duplicate tei: %d\n", tei);	
		}

		sta = &sta_entry[tei];
		sta->tei = tei;
		tr.insert(&tr, &sta->rb, pa, p);	
	}

	printf("STA LIST:\n");
	for (iter = rb_first(&tr.root); iter != NULL; iter = rb_next(iter)) {
		sta_t *sta = rb_entry(iter, sta_t, rb);	
		printf("tei:[%d]; rb_color:[%d]\n", sta->tei, iter->rb_color);
	}

	return 0;
}
