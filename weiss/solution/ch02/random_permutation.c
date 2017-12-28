/*
 * generate random permutation
 *
 * Aug 14, 2015	   tgni		Create
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*
 * binary_search are only used for already sorted array
 */
/*
int binary_search(const int a[], int N, int X)
{
	int low, high, mid;

	low = 0; high = N - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (a[mid] < X) {
			low = mid + 1;
		} else if (a[mid] > X) {
			high = mid - 1;	
		} else {
			return mid;	
		}
	}
	return -1;
}
*/

void swap(int *a, int *b)
{
        int p;
        p = *a;
        *a = *b;
        *b = p;
}

int sequence_search(const int a[], int N, int X)
{
	int i;

	for (i = 0; i < N; ++i) {
		if (a[i] == X)	
			return i;
	}
	return -1;
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

void random_a(int a[], int n)
{
	int i, rand;

	srand(time(NULL));
	printf("random series: \n");
	for (i = 0; i < n; ++i) {
		do {
			rand = random() % n;	
			printf("i=%d, rand=%d\n", i, rand);
		} while (sequence_search(a, i, rand) != -1);
		a[i] = rand;
	}
}

int random_b(int a[], int n)
{
	int i, rand;
	unsigned char *used = NULL;

	/* used is for recording */
	used = malloc(sizeof(unsigned char) * n);
	if (!used) {
		printf("malloc failed\n");
		return -1;
	}
	memset(used, 0, sizeof(unsigned char) * n);

	srand(time(NULL));
	//printf("random series: \n");
	for (i = 0; i < n; ++i) {
		do {
			rand = random() % n;
			//printf("i=%d, rand=%d\n", i, rand);
		} while (used[rand] == 1);
		used[rand] = 1; 
		a[i] = rand;
	}
	
	free(used);
	return 0;
}

void random_c(int a[], int n)
{
	int i;

	for (i = 0; i < n; ++i) {
		a[i] = i + 1;	
	}

	for (i = 1; i < n; ++i) {
		swap(&a[i], &a[random() % i]);	
	}
}


int main(int argc, char *argv[])
{
	int *a = NULL, n;

	if (argc != 2) {
		printf("invalid input params!\n");
		return -1;
	}

	n = strtoul(argv[1], NULL, 0);
	a = malloc(sizeof(int) * n);
	if (!a) {
		printf("malloc failed\n");
		return -1;
	}
	memset(a, 0, sizeof(int) * n);
	//random_a(a, n);
	random_c(a, n);
	print_array(a, n);
	
	free(a);

	return 0;
}
