#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_queen(int c[], int n)
{
	int i, j;

	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j)
			printf("%d ", j == c[i] ? 1 : 0);
		printf("\n");
	}
	printf("\n");

	return;
}

int isvalid(int c[], int k)
{
	int i;

	for (i = 0; i < k; ++i) {
		if (abs(c[i]-c[k]) == abs(i-k) || c[i] == c[k])
			return 0;
	}

	return 1;
}


static int CNT = 0;

void search(int c[], int n, int k)
{
	int i;

	if (k == n) {
		++CNT;
		print_queen(c, n);
	}

	for (i = 0; i < n; ++i) {
		c[k] = i;
		if (isvalid(c, k))
			search(c, n, k+1);
	}
}

int main()
{
	int c[8];

	search(c, 8, 0);
	printf("total: %d\n", CNT);

	return 0;
}
