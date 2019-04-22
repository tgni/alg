#include <stdio.h>

#define INF		(500*600+1)
#define MaxCitys	(600+1)
int Matrix[MaxCitys][MaxCitys];
int Leader[MaxCitys];

int main()
{
	int n, m;

	while (scanf("%d", &n) != EOF) {
		if (n == 0)
			break;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				Matrix[i][j] = INF;
			}
			Matrix[i][i] = 0;
		}

		scanf("%d", &m);
		while (m--) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			if (Matrix[a][b] > c) //testcase may contain multi-roads bewteen a and b.
				Matrix[a][b] = Matrix[b][a] = c;
		}

		for (int i = 1; i <= n; ++i)
			scanf("%d", &Leader[i]);

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (Leader[i] == 2 && Leader[j] == 1) //startA belongs to Leader1, endB belongs to Leader2. route should only contain at most 
								      // 1 road connecting different camps. So, 1->2, 1->1, 2->2 is permitted, 2->1 is forbidden.
					Matrix[i][j] = INF;
			}
		}

		for (int k = 1; k <= n; ++k) {
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					if (Matrix[i][k] + Matrix[k][j] < Matrix[i][j])
						Matrix[i][j] = Matrix[i][k] + Matrix[k][j];
				}
			}
		}

		printf("%d\n", Matrix[1][2] == INF ? -1 : Matrix[1][2]);
	}

	return 0;
}
