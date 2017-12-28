#include <stdio.h>
#include "types.h"

void print_array(int32_t a[], int32_t length, int32_t i, int32_t p, int32_t j, int32_t r);

int32_t partition(int32_t a[], int32_t p, int32_t r)
{
	int32_t x, i, j;

	x = a[r];
	i = p - 1;

	for (j = p; j <= r-1; ++j) {
		if (a[j] <= x) {
			i++;	
			swap(a[i], a[j]);
		}
		print_array(a, r, i, p, j, r);
	}
	swap(a[i+1], a[r]);
	print_array(a, r, i, p, j, r);

	return i+1;
}

void quicksort(int32_t a[], int32_t p, int32_t r)
{
	int32_t q;

	if (p < r) {
		q = partition(a, p, r);
		quicksort(a, p, q-1);
		quicksort(a, q+1, r);
	}

	return;
}

void print_array(int32_t a[], int32_t length, int32_t i, int32_t p, int32_t j, int32_t r)
{
	int32_t idx;

	for (idx = 1; idx <= length; ++idx)
		printf("%d ", a[idx]);
	printf(" i:%d p:%d j:%d r:%d\n", i, p, j, r);

	return;
}


int main(void)
{
	//int32_t a[] = {0, 16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
	//int32_t a[] = {0, 1, 14, 10, 8, 7, 9, 3, 2, 16, 4};
	int32_t a[] = {0, 1, 2, 3, 4, 7, 8, 9, 10, 14, 16};
	int32_t length;

	length = sizeof(a) / sizeof(int32_t) - 1;
	quicksort(a, 1, length);

	return 0;
}
