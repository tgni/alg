#include <stdio.h>
#include "types.h"

void PrintArray(int32_t a[], int32_t length);

int32_t Partition(int32_t A[], int32_t low, int32_t high)
{
	int32_t pivot = A[low];

	while (low < high) {
		while (low < high && A[high] >= pivot) --high;
		A[low] = A[high];
		while (low < high && A[low] <= pivot) ++low;
		A[high] = A[low];
	}
	A[low] = pivot;

	return low;
}

void QuickSort(int32_t a[], int32_t low, int32_t high, int32_t i)
{
	int32_t p;

	if (low < high) {
		printf("%d:", ++i);
		PrintArray(a, 6);
		p = Partition(a, low, high);
		QuickSort(a, low, p-1, i);
		QuickSort(a, p+1, high, i);
	}

	return;
}

void PrintArray(int32_t a[], int32_t length)
{
	int32_t idx;

	for (idx = 0; idx < length; ++idx)
		printf("%d ", a[idx]);
	printf("\n");
}


int main(void)
{
	int32_t a[] = {46, 79, 56, 38, 40, 84};
	//int32_t a[] = {46, 79, 80, 81, 82, 83};
	int32_t length;

	length = sizeof(a) / sizeof(int32_t);
	//PrintArray(a, length);
	QuickSort(a, 0, length-1, 0);
	//PrintArray(a, length);

	return 0;
}
