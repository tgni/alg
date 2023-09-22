#include <stdio.h>

#define UP		(1)
#define LEFT		(2)
#define DIAGONAL	(3) 

char X[] = {' ', 'A', 'B', 'C', 'B', 'D', 'A', 'B'};
char Y[] = {' ', 'B', 'D', 'C', 'A', 'B', 'A'};
int C[8][7]; /* c[0..7][0..6]*/
int B[8][7]; /* b[1..7][1..6] b[0][x] no use */

int lcs_length(char x[], char y[])
{
	int i, j, m = 7, n = 6;
	int (*c)[7] = C, (*b)[7] = B;

	for (i = 1; i <= m; ++i)
		c[i][0] = 0;
	for (j = 0; j <= n; ++j)
		c[0][j] = 0;

	for (i = 1; i <= m; ++i) {
		for (j = 1; j <= n; ++j) {
			if (x[i] == y[j]) {
				c[i][j] = c[i-1][j-1] + 1;
				b[i][j] = DIAGONAL;
			} else if (c[i-1][j] >= c[i][j-1]) {
				c[i][j] = c[i-1][j];
				b[i][j] = UP;
			} else {
				c[i][j] = c[i][j-1];
				b[i][j] = LEFT;
			}
		}
	}

	return 0;
}

void print_lcs(char x[], int i, int j)
{
	int (*b)[7] = B;

	if (i == 0 || j == 0)
		return;
	if (b[i][j] == DIAGONAL) {
		print_lcs(x, i - 1, j - 1);
		printf("%c", x[i]);
	} else if (b[i][j] == UP) {
		print_lcs(x, i - 1, j);
	} else if (b[i][j] == LEFT) {
		print_lcs(x, i, j - 1);
	}
}

int main()
{
	int i;

	printf("X:");
	for (i = 1; i < 8; ++i)
		printf("%c", X[i]);
	printf("\n");

	printf("Y:");
	for (i = 1; i < 7; ++i)
		printf("%c", Y[i]);
	printf("\n");

	printf("LCS:");
	lcs_length(X, Y);
	print_lcs(X, 7, 6);
	printf("\n");

	return 0;
}
