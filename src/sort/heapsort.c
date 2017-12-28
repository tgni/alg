#include <stdio.h>
#include "types.h"

/*
 * Array's subscript starts from 0, while this algorithm starts from 1. 
 */

#define PARENT(i)	mod_ceiling(i, 2)
#define LEFT(i)		(2 * (i))
#define RIGHT(i)	(2 * (i) + 1)

void max_heapify(int32_t a[], int32_t i, int32_t heapsize)
{
	int l, r, largest;

	l = LEFT(i);
	r = RIGHT(i);

	if (l <= heapsize && a[l] > a[i])
		largest = l;
	else
		largest = i;
	if (r <= heapsize && a[r] > a[largest])
		largest = r;

	if (largest != i) {
		swap(a[i], a[largest]);
		max_heapify(a, largest, heapsize);
	}

	return;
}


void build_max_heap(int32_t a[], int32_t length)
{
	int32_t heapsize, i;

	heapsize = length;

	for (i = mod_floor(length, 2); i >= 1; --i)
		max_heapify(a, i, heapsize);

	return;
}


void heap_sort(int32_t a[], int32_t length)
{
	int32_t i, heapsize = length;

	build_max_heap(a, length);

	for (i = length; i >= 2; --i) {
		swap(a[1], a[i]);
		heapsize--;
		max_heapify(a, 1, heapsize);
	}
	
	return;
}


void print_array(int32_t a[], int32_t length)
{
	int32_t i;

	for (i = 1; i <= length; ++i)
		printf("%d ", a[i]);
	printf("\n");
}


int main(void)
{
	//int32_t a[] = {0, 16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
	int32_t a[] = {0, 1, 14, 10, 8, 7, 9, 3, 2, 4, 16};
	int32_t length;

	length = sizeof(a) / sizeof(int32_t) - 1;
	print_array(a, length);
	heap_sort(a, length);
	print_array(a, length);

	return 0;
}
