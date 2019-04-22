#include <stdio.h>
#include "types.h"
#include "tool.h"

void insertion_sort(int a[], int N)
{
	int i, j, tmp;

	for (i = 1; i < N; ++i) {
		tmp = a[i];
		for (j = i; j > 0 && a[j - 1] < tmp; j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

int32_t main()
{
	int32_t a[] = {31, 41, 59, 26, 41, 58};
	int32_t N = sizeof(a) / sizeof(a[0]);

	print_array(a, N);
	insertion_sort(a, N);
	print_array(a, N);

	return 0;
}
