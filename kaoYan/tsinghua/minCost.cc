/*
 * dist[N]:从第1站到第i站的距离
 * dp[i]: 从A到第i站的最小花费(A <= i <= B)
 * 初始化：
 * dist[1] = 0
 * dp[A] = 0; dp[A+i] = INF; (A < i <= B)
 * 迭代：
 * dp[i] =  min{ dp[j] + Price(dist[i]-dist[j]), dp[i] }
 *			if (dist[i]-dist[j] <= l3) (A < i <= B, A <= j < i)
 *	    else dp[i]
 * 结果：
 * dp[B]
 */
#include <stdio.h>

#define INF	(1e9)
#define min(a, b) (a < b ? a : b)

int l1, l2, l3, c1, c2, c3;

int Price(int L)
{
	if (L > 0 && L <= l1)
		return c1;
	else if (L > l1 && L <= l2)
		return c2;
	else if (L > l2 && L <= l3)
		return c3;

	return INF;
}

int main()
{
	while (scanf("%d%d%d%d%d%d", &l1, &l2, &l3, &c1, &c2, &c3) != EOF) {
		int A, B, N;
		scanf("%d%d", &A, &B);
		scanf("%d", &N);

		int dist[N+1];
		int dp[N+1];
		dist[1] = 0;
		for (int i = 2; i <= N; ++i)
			scanf("%d", &dist[i]);

		dp[A] = 0;
		for (int i = A+1; i <= B; ++i) {
			dp[i] = INF;
			for (int j = A; j < i; ++j) {
				int L = dist[i] - dist[j];
				if (L <= l3)
					dp[i] = min(dp[j]+Price(L), dp[i]);
			}
		}

		printf("%d\n", dp[B]);
	}

	return 0;
}
