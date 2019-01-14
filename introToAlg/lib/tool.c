#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NR	(1000)

void swap(int v[], int i, int j)
{
	int tmp;

	tmp  = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

void qqsort(int v[], int left, int right)
{
	int i, last;
	
	if (left >= right)
		return;

	swap(v, left, (left + right)/2);
	last = left;

	for (i = left + 1; i <= right; i++)
		if (v[i] < v[left])
			swap(v, ++last, i);

	swap(v, left, last);
	qqsort(v, left, last-1);
	qqsort(v, last+1, right);
}

void shuffle(int v[], int n)
{
	int i, j;
	
	srand(time(NULL));

	for (i = 0; i < n; ++i)
		swap(v, i, rand() % n);
}

void print_array(char *prompt, int a[], int N)
{
	int i;

	printf("%s", prompt);
	for (i = 0; i < N; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
}



