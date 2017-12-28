/**
 * radix_sort.c
 * Description: radix sorting implementation
 *	Dec 11, 2015    Daniel Ni    Create
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "radix_sort.h"

#define NR_BKT	(10)

void show_bucket(bucket *bkt);

bitem_t *get_bitem(int32_t e)
{
	bitem_t *item;

	item = malloc(sizeof(bitem_t));
	if (!item) return NULL;

	INIT_LIST_HEAD(&item->node);
	item->e = e;

	return item;
}

void put_bitem(bitem_t *item)
{
	free(item);
}

void put_bitem_all(bucket *bkt)
{
	//TODO	
}

void push_bitem(bucket *bkt, bitem_t *item, int32_t idx)
{
	list_add_tail(&item->node, &bkt->base[idx]);
}

void pop_bitem(bitem_t *item)
{
	list_del_init(&item->node);
}

bucket *create_bucket(int32_t nr)
{
	bucket *bkt;
	int32_t i;

	bkt = malloc(sizeof(bucket) + sizeof(list_head_t) * nr);
	if (!bkt) return NULL;

	bkt->base = (list_head_t *)((void *)bkt + sizeof(bucket));
	for (i = 0; i < nr; ++i)
		INIT_LIST_HEAD(&bkt->base[i]);
	bkt->nr = nr;

	return bkt;
}

void destroy_bucket(bucket *b)
{
	//TODO	
}

int32_t is_even(int32_t x)
{
        if (x % 2)
                return 0;
        else 
                return 1;
}

int32_t power(int32_t x, int32_t n)
{
        if (n == 0) 
                return 1;
        if (n == 1)
                return x;
        if (is_even(n))
                return power(x * x, n / 2);
        else
                return power(x * x, n / 2) * x;
}

int32_t radix_sort(bucket *bkt, int32_t a[], int32_t nr)
{
	bitem_t *item;
	int32_t i, j, p, idx, tmp, max = 0;
	list_head_t *pos, *n, head;

	for (i = 0; i < nr; ++i)
		if (max < a[i]) max = a[i];
	printf("max: %d\n", max);

	for (p = 0; (power(bkt->nr, p) - 1) < max; ++p)
		;
	printf("power: %d\n", p);

	for (i = 0; i < nr; ++i) {
		item = get_bitem(a[i]);	
		if (!item) {
			put_bitem_all(bkt);	
			return ERROR;
		}
		idx  = item->e % bkt->nr;
		push_bitem(bkt, item, idx);
	}
	show_bucket(bkt);

	INIT_LIST_HEAD(&head);
	for (i = 1; i < p; ++i) {
		for (j = 0; j < bkt->nr; ++j) {
			list_for_each_safe(pos, n, &bkt->base[j]) {
				item = list_entry(pos, bitem_t, node);
				tmp = item->e / power(bkt->nr, i);
				idx = tmp % bkt->nr;
				if (idx != j) {
					pop_bitem(item);	
					push_bitem(bkt, item, idx);
				} else {
					/* trick here */
					tmp = item->e / power(bkt->nr, i - 1);	
					tmp = tmp % bkt->nr;
					if (idx == tmp) {
						pop_bitem(item);
						list_add_tail(&item->node, &head);
					}
				}
			}
			list_for_each_safe(pos, n, &head) {
				item = list_entry(pos, bitem_t, node);	
				pop_bitem(item);
				push_bitem(bkt, item, j);
			}
		}
		show_bucket(bkt);
	}

	i = 0;
	for (j = 0; j < bkt->nr; ++j) {
		list_for_each(pos, &bkt->base[j]) {
			item = list_entry(pos, bitem_t, node);
			a[i++] = item->e;
		}
	}

	return OK;
}

void show_bucket(bucket *bkt)
{
	int32_t j;
	list_head_t *pos;
	bitem_t *item;

	printf("Bucket\n");
	printf("----------------------------------------------------\n");
	for (j = 0; j < bkt->nr; ++j) {
		printf("%-5d|", j);
		if (list_empty(&bkt->base[j])) {
			printf("     ");	
		} else {
			list_for_each(pos, &bkt->base[j]) {
				item = list_entry(pos, bitem_t, node);
				printf("%-5d", item->e);
			}
		}
		printf("\n");
	}
	return;
}

void print_array(int32_t a[], int32_t n)
{
        int32_t i;

        for (i=0; i<n; i++)        
                printf("%d ", a[i]);
        printf("\n");
	return;
}

int main(int argc , char *argv[])
{
	bucket *bkt;
	int32_t i, nr_bkt, nr_ar, max;
	int32_t *A;
//	int32_t A[10] = {64, 8, 216, 512, 27, 729, 0, 1, 343, 125};

	if (argc != 4) {
		printf("\nUsage: ./radix_sort <bucket size> <array size> <max number>\n\n");
		return -1;
	}

	nr_bkt = strtoul(argv[1], NULL, 0);
	nr_ar  = strtoul(argv[2], NULL, 0);
	max    = strtoul(argv[3], NULL, 0);

	A = malloc(sizeof(int) * nr_ar);
	if (!A) {
		assert(!A);
		return -1;
	}

	srand(time(NULL));
	for (i = 0; i < nr_ar; ++i) {
		A[i] = random() % max;
	}
	print_array(A, nr_ar);
	bkt = create_bucket(nr_bkt);
	radix_sort(bkt, A, nr_ar);
	print_array(A, nr_ar);
	destroy_bucket(bkt);

	return 0;
}
