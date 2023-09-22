#include <stdio.h>

#define INFINITE	(0x7fffffff)

/* A1 = 30x35 ... A6 = 20x25; */
//int P[7] = {30, 35, 15, 5, 10, 20, 25};
int P[7] = {5, 10, 3, 12, 5, 50, 6};
int M[7][7];
int S[7][7];

int matrix_chain_order(int p[])
{
	int i, j, k, l, q, n = 6;
	int (*m)[7], (*s)[7];

	printf("i    j    k    l    q\n");
	printf("--------------------------\n");

	m = M; s = S;

	for (i = 1; i <= n; ++i)
		m[i][i] = 0;
	for (l = 2; l <= n; ++l) {
		for (i = 1; i <= n - l + 1; ++i) {
			j = i + l - 1;
			m[i][j] = INFINITE;
			for (k = i; k <= j - 1; ++k) {
				q = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];
				printf("%-4d %-4d %-4d %-4d %-10d\n", i, j, k, l, q);

				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}

	return 0;
}

void print_optimal_parens(int (*s)[7], int i, int j)
{
	if (i == j) {
		printf("A%d", i);
	} else {
		printf("(");
		print_optimal_parens(s, i, s[i][j]);
		print_optimal_parens(s, s[i][j]+1, j);
		printf(")");
	}
}

int main()
{
	int i, j;

	matrix_chain_order(P);
	
	printf("M[7][7]: (1-6)x(1-6)\n");
	for (i = 1; i < 7; ++i) {
		for (j = 1; j < 7; ++j) {
			printf("%-8d ", M[i][j]);	
		}
		printf("\n");
	}
	printf("\n");
	printf("S[7][7]: (1-6)x(1-6)\n");
	for (i = 1; i < 7; ++i) {
		for (j = 1; j < 7; ++j) {
			printf("%-8d ", S[i][j]);	
		}
		printf("\n");
	}
	printf("\n");

	print_optimal_parens(S, 1, 6);
	printf("\n");

	return 0;
}
