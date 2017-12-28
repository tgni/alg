/**
 * find kth maximum number
 * June 30, 2015	tgni	Create
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum {
	BUBBLE,
	INSERTION,
	MAX_SORT_TYPE
};

extern void bubble_sort(int a[], int n);
extern void insertion_sort(int a[], int n);

typedef void (*sort_fp)(int *, int);

sort_fp SORT[MAX_SORT_TYPE] = {
	bubble_sort,
	insertion_sort
};

static unsigned char sort_type = BUBBLE;

void swap(int *a, int *b)
{
        int p;
        p = *a;
        *a = *b;
        *b = p;
}

/* O(n^2) */
void bubble_sort(int a[], int n)
{
	int i, j;

	for (i=0; i<n-1; i++)
		for (j=1; j<n-i; j++)
			if (a[j-1] > a[j])
				swap(&a[j-1], &a[j]);

	return;
}

void insertion_sort(int a[], int n)
{
	int i, j, key;

	for (j = 1; j < n; ++j) {
		key = a[j];
		i = j - 1;
		// Insert a[j] into the sorted sequence a[0...j-1]
		while (i >= 0 && a[i] > key) {
			a[i + 1] = a[i];
			i = i - 1;
		}
		a[i + 1] = key;
	}

	return;
}

void find_max_and_next(int a[], int n)
{
	int i, max = 0, next_max = 0;

	for (i = 0; i < n; ++i) {
		if (max < a[i]) {
			next_max = max;
			max = a[i];
		} else if (max > a[i] && next_max < a[i]) {
			next_max = a[i];
		}
	}

	printf("max :%d, next_max:%d\n", max, next_max);

}

void find_max(int a[], int n)
{
	int i, max = 0;

	for (i = 0; i < n; ++i) {
		if (max < a[i])	
			max = a[i];
	}
	printf("max :%d\n", max);
}

#if 0
int find(int a[], int n, int k)
{
	SORT[sort_type](a, n);
	return a[n - k];
}

int find(int a[], int n, int k)
{
	int i;
	/* 
	 * sort a[0...k-1] as increasing order,
	 * a[0] as the kth largest.
	 */
	SORT[sort_type](a, k);

	for(i = k; i < n; ++i) {

	/* 
	 * if a[0] < a[i], swap them,
	 * resort a[0...k-1],
	 * make sure a[0] as the kth largest.
	 */
		if (a[0] < a[i]) {
			swap(&a[i], &a[0]);
			SORT[sort_type](a, k);
		}
	}

	return a[0];
}
#endif

void shuffle(int a[], int n)
{
	int i, j, k;

	srand(time(NULL));

	for (k = 0; k < n/2; ++k) {
		i = random() % n;
		j = random() % n;
		swap(&a[i], &a[j]);
	}

	return;
}

void print_array(int a[], int n)
{
	int i;

	printf("\n");
	for (i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");

	return;
}

int main(int argc, char *argv[])
{
	int *a = NULL, i, n;
	char *type = NULL;

	if (argc > 3)
		return -1;

	if (argc == 3 && strstr(argv[2], "-sort=")) {
		type = strchr(argv[2], '=') + 1;
		if (0 == strcmp(type, "bubble")) {
			sort_type = BUBBLE;
		} else if (0 == strcmp(type, "insertion")) {
			sort_type = INSERTION;
		} else {
			printf("unknown sort type\n");	
			return -1;
		}
	}
	
	n = strtoul(argv[1], NULL, 0);
	a = malloc(sizeof(int) * n);
	if (!a) {
		printf("malloc failed\n");
		return -1;
	}
#if 0	
	for (i = 0; i < n; ++i) {
		a[i] = i;
	}

	shuffle(a, n);
#endif
	for (i = 0; i < n; ++i) {
		a[i] = random() % 10;
		printf("%d ", a[i]);
	}

	printf("\nstart..\n");
	find_max_and_next(a, n);
	find_max(a, n);
	//printf("k: %d\n", find(a, n, n/2));
	printf("end\n");

	return 0;
}
