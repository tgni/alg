#include <stdio.h>
#include "types.h"
#include "tool.h"

void selection_sort(int32_t A[], int32_t N)
{
	int32_t i, j, k, e;

	for (i = 0; i < N; ++i) {
		k = i;
		for (j = i + 1; j < N; ++j) {
			if (A[k] > A[j])	
				k = j;
		}
		swap(A, i, k);
	}

	return;
}

int32_t main()
{
	int32_t a[] = {31, 41, 59, 26, 41, 58};
	int32_t N = sizeof(a) / sizeof(a[0]);

	print_array("Before: ", a, N);
	selection_sort(a, N);
	print_array("After: ", a, N);

	return 0;
}
