#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int a[], int N)
{
	int i, j, tmp;

	for (i = 1; i < N; ++i) {
		tmp = a[i];
		for (j = i; j > 0 && a[j - 1] > tmp; j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

void print_array(int a[], int N)
{
	int i;

	for (i = 0; i < N; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

#define SENTINEL	(~0)


main()
{
	int a[] = {4, 2, 3, 6, 5, 9, 8, 1, 0};
	int N = sizeof(a)/sizeof(int);

	print_array(a, N);
	insertion_sort(a, N);
	print_array(a, N);

	return;
}
