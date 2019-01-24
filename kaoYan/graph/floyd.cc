/* Given <n, m>, following with m lines, each line contains <a, b, c>, a refers to a start point,
 * b is an end point, c is cost between them. range follows: 1 <= a, b <= n, 1 <= c <= 1000.
 * Find the shortest path from 1 to n. When <n, m> = <0, 0> program ends.
 */

#include <stdio.h>

#define MAX_POINT	(100+1)
int Matrix[MAX_POINT][MAX_POINT];

int main(void)
{
	int n, m;

	while (scanf("%d%d", &n, &m) != EOF) {
		if (n == 0 && m == 0)
			break;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				Matrix[i][j] = -1;
			}
			Matrix[i][i] = 0;
		}
		
		int a, b, c;
		while (m--) {
			scanf("%d%d%d", &a, &b, &c);
			Matrix[a][b] = Matrix[b][a] = c;
		}

		for (int k = 1; k <= n; ++k) {
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					if (Matrix[i][k] == -1 || Matrix[k][j] == -1)
						continue;
					if (Matrix[i][j] == -1 || Matrix[i][k]+Matrix[k][j] < Matrix[i][j])
						Matrix[i][j] = Matrix[i][k]+Matrix[k][j];
				}
			}
		}
		printf("%d\n", Matrix[1][n]);
	}

	return 0;
}
