#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "types.h"
#include "list.h"

typedef struct bucket_s {
	list_head_t *list;	/* for each number i less than base, 
				   storing data at list[i]. */
	int base;		/* radix number */
} bucket;

typedef	struct bitem_s {
	list_head_t link;
	int e;
} bitem_t;


void print_array(int a[], int n)
{
	int i;

	for (i = 0; i < n; ++i) {
		printf("%2d ", a[i]);
	}
	printf("\n");
}

void insert_sort_1(int a[], int n)
{
	int i, j, tmp;

	for (i = 1; i < n; ++i) {
		tmp = a[i];
		for (j = i; j > 0 && a[j - 1] > tmp; j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

/* Using binary search to find position for inserting. */
void insert_sort_2(int a[], int n)
{
	int i, j, low, high, mid, tmp;

	for (i = 1; i < n; ++i) {
		tmp = a[i];
		low = 0; high = i-1;
		/* find insert position at low */
		while (low <= high) {
			mid = (low + high)/2;
			if (a[mid] > tmp)
				high = mid-1;
			else
				low  = mid+1;
		}
		for (j = i; j > low; j--)
			a[j] = a[j-1];
		a[j] = tmp;
	}
}

void shell_sort(int a[], int n)
{
	int dk, i, j, tmp;

	for (dk = n/2; dk > 0; dk = dk/2) {
		for (i = dk; i < n; ++i) {
			if (a[i] < a[i-dk]) {
				tmp = a[i];
				for (j=i-dk; j >= 0 && a[j] > tmp; j-=dk)
					a[j+dk] = a[j];
				a[j+dk] = tmp;
			}
		}
	}
}


void bubble_sort(int a[], int n)
{
        int i, j, flag = 0;

	for (i = 0; i < n; ++i) {
		flag = 0;

		for (j = n-1; j > i; j--) {
			if (a[j-1] > a[j]) {
				swap(a[j-1], a[j]);
				flag = 1;
			}
		}

		if (flag == 0)
			return;
	}
}

int partition(int a[], int low, int high)
{
	int pivot = a[low];

	while (low < high) {
		while (low < high && a[high] >= pivot) --high;
		a[low] = a[high];
		while (low < high && a[low] <= pivot) ++low;
		a[high] = a[low];
	}
	a[low] = pivot;

	return low;
}

void quick_sort(int a[], int low, int high)
{
	int p;

	if (low < high) {
		p = partition(a, low, high);
		quick_sort(a, low, p-1);
		quick_sort(a, p+1, high);
	}

	return;
}


void select_sort(int a[], int n)
{
	int i, j, min;

	for (i = 0; i < n-1; ++i) {
		min = i;
		for (j = i+1; j < n; ++j)
			if (a[j] < a[min]) min = j;

		if (min != i) swap(a[min], a[i]);
	}
}


/*
 * array's subscript starts from 0, while this algorithm starts from 1. 
 */

#define PaREnT(i)	mod_ceiling(i, 2)
#define LEFT(i)		(2 * (i))
#define RIGHT(i)	(2 * (i) + 1)

void adjust_down(int a[], int k, int len)
{
	int i;
	
	a[0] = a[k];

	for (i = 2*k; i <= len; i *= 2) {
		if (i < len && a[i] < a[i+1])
			i++;
		if (a[0] >= a[i]) {
			break;
		} else {
			a[k] = a[i];
			k = i;
		}
	}
	a[k] = a[0];
}

void adjust_up(int a[], int k)
{
	int i = k/2; //parent

	a[0] = a[k];

	while (i > 0 && a[i] > a[0]) {
		a[k] = a[i];
		k = i;
		i = k/2;
	}
	a[k] = a[0];
}


void build_max_heap(int a[], int n)
{
	int i;

	for (i = n/2; i > 0; --i)
		adjust_down(a, i, n);
}

void heap_sort(int a[], int n)
{
	int i, heapsize = n;

	build_max_heap(a, n);
	//print_array(a, n);

	for (i = n; i >= 2; --i) {
		swap(a[1], a[i]);
		heapsize--;
		adjust_down(a, 1, heapsize);
	}
	
	return;
}

void merge(int a[], int t[], int low, int mid, int high)
{
	int i, j, k;

	for (k = low; k <= high; ++k)
		t[k] = a[k];

	for (i = low, j = mid+1, k = i; i <= mid && j <= high; ++k) {
		if (t[i] <= t[j])
			a[k] = t[i++];
		else
			a[k] = t[j++];
	}

	while (i <= mid)  a[k++] = t[i++];
	while (j <= high) a[k++] = t[j++];
}

void __merge_sort(int a[], int tmp[], int low, int high)
{
	int mid;

	if (low < high) {
		mid = (low + high) / 2;
		__merge_sort(a, tmp, low, mid);
		__merge_sort(a, tmp, mid+1, high);
		merge(a, tmp, low, mid, high);
	}
}

void merge_sort(int a[], int n)
{
	int *tmp;

	if (!(tmp = (int *)malloc(n * sizeof(int))))
		return;

	__merge_sort(a, tmp, 0, n-1);

	free(tmp);
}

int is_even(int x)
{
        if (x % 2)
                return 0;
        else 
                return 1;
}

int power(int x, int n)
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

int get_idx(int data, int base, int exp)
{
	return (data / power(base, exp)) % base;
}


bitem_t *get_bitem(int e)
{
	bitem_t *item;

	if (!(item = malloc(sizeof(bitem_t))))
		return NULL;

	item->e = e;
	return item;
}

void put_bitem(bitem_t *item)
{
	list_del(&item->link);
	free(item);
}

void push_bitem(bucket *bkt, bitem_t *item, int idx)
{
	list_add_tail(&item->link, &bkt->list[idx]);
}

void pop_bitem(bitem_t *item)
{
	list_del(&item->link);
}

bucket *get_bucket(int base)
{
	bucket *bkt;
	int i;

	if (!(bkt = malloc(sizeof(bucket) + sizeof(list_head_t) * base)))
		return NULL;

	bkt->list = (list_head_t *)((void *)bkt + sizeof(bucket));
	for (i = 0; i < base; ++i)
		INIT_LIST_HEAD(&bkt->list[i]);
	bkt->base = base;

	return bkt;
}

void put_bucket(bucket *bkt)
{
	list_head_t *pos, *n;
	bitem_t *item;
	int j;
	
	for (j = 0; j < bkt->base; ++j) {
		list_for_each_safe(pos, n, &bkt->list[j]) {
			item = list_entry(pos, bitem_t, link);
			put_bitem(item);
		}
	}

	free(bkt);
}

void show_bucket(bucket *bkt)
{
	int j;
	list_head_t *pos;
	bitem_t *item;

	printf("Bucket\n");
	printf("----------------------------------------------------\n");
	for (j = 0; j < bkt->base; ++j) {
		printf("%-5d|", j);
		if (list_empty(&bkt->list[j])) {
			printf("     ");	
		} else {
			list_for_each(pos, &bkt->list[j]) {
				item = list_entry(pos, bitem_t, link);
				printf("%-5d", item->e);
			}
		}
		printf("\n");
	}
	return;
}

void __radix_sort(int a[], int nr, int base)
{
	bitem_t *item;
	bucket *bkt;
	int i, j, k, exp, idx, max = 0;
	list_head_t *pos, *n;

	/* get exp */
	for (i = 0; i < nr; ++i) {
		if (max < a[i]) max = a[i];
	}

	for (exp = 0; power(base, exp) < max; ++exp)
		;

	if (!(bkt = get_bucket(base)))
		return;

	for (k = 0; k < exp; ++k) {
		/* allocation */
		for (i = 0; i < nr; ++i) {
			if (!(item = get_bitem(a[i]))) {
				put_bucket(bkt);	
				return;
			}

			idx = get_idx(item->e, bkt->base, k);
			push_bitem(bkt, item, idx);
		}

		/* collection */
		for (i =0, j = 0; j < bkt->base; ++j) {
			list_for_each_safe(pos, n, &bkt->list[j]) {
				item = list_entry(pos, bitem_t, link);
				a[i++] = item->e;
				put_bitem(item);
			}
		}
	}

	put_bucket(bkt);

	return;
}

/* default base is 10 */
void radix_sort(int a[], int n)
{
	__radix_sort(a, n, 10);
}

void counting_sort(int a[], int n)
{

}


int main(char *argv[], int argc)
{
	int b[10];
	int a[11];
	int n = sizeof(b)/sizeof(int), i;

	srand(time(NULL));
	for (i = 0; i < n; ++i)
		b[i] = rand() & 0xf;

	memcpy(a, b, sizeof(b));
	printf("original data: ");
	print_array(a, n);

	printf("insert sort 1: ");
	insert_sort_1(a, n);
	print_array(a, n);

	memcpy(a, b, sizeof(b));
	printf("insert sort 2: ");
	insert_sort_1(a, n);
	print_array(a, n);

	memcpy(a, b, sizeof(b));
	printf("shell sort:    ");
	shell_sort(a, n);
	print_array(a, n);

	memcpy(a, b, sizeof(b));
	printf("bubble sort:   ");
	bubble_sort(a, n);
	print_array(a, n);

	memcpy(a, b, sizeof(b));
	printf("quick sort:    ");
	quick_sort(a, 0, n-1);
	print_array(a, n);

	memcpy(a, b, sizeof(b));
	printf("select sort:   ");
	select_sort(a, n);
	print_array(a, n);

	memcpy(&a[1], b, sizeof(b));
	a[0] = 0;
	printf("heap sort:     ");
	heap_sort(a, n);
	print_array(&a[1], n);

	memcpy(a, b, sizeof(b));
	printf("merge sort:    ");
	merge_sort(a, n);
	print_array(a, n);

	memcpy(a, b, sizeof(b));
	printf("radix sort:    ");
	radix_sort(a, n);
	print_array(a, n);

	return 0;
}
