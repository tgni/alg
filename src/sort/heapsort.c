#include <stdio.h>
#include "types.h"

/*
 * Array's subscript starts from 0, while this algorithm starts from 1. 
 */

#define PARENT(i)	mod_ceiling(i, 2)
#define LEFT(i)		(2 * (i))
#define RIGHT(i)	(2 * (i) + 1)

void print_array(int32_t a[], int32_t length);

void adjust_down(int32_t A[], int32_t k, int len)
{
	int32_t i;
	
	A[0] = A[k];

	for (i = 2*k; i <= len; i *= 2) {
		if (i < len && A[i] < A[i+1])
			i++;
		if (A[0] >= A[i]) {
			break;
		} else {
			A[k] = A[i];
			k = i;
		}
	}
	A[k] = A[0];
}

void adjust_up(int32_t A[], int k)
{
	int32_t i = k/2; //parent

	A[0] = A[k];

	while (i > 0 && A[i] > A[0]) {
		A[k] = A[i];
		k = i;
		i = k/2;
	}
	A[k] = A[0];
}


void build_max_heap(int32_t a[], int32_t length)
{
	int32_t i;

	for (i = length/2; i > 0; --i)
		adjust_down(a, i, length);
}

void heap_sort(int32_t a[], int32_t length)
{
	int32_t i, heapsize = length;

	build_max_heap(a, length);
	print_array(a, length);

	for (i = length; i >= 2; --i) {
		swap(a[1], a[i]);
		heapsize--;
		adjust_down(a, 1, heapsize);
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
