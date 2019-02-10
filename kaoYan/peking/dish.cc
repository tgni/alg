/* definition:
 *	dp[i][j]: represents evaluation score when the class of food is no more than 
 *	i and their price is less than j (1 <= i <= N,  1 <= j <= C).
 * Initiation:
 *	dp[0][j] = 0; the cost may be less than maximum cost, when reach best eval score.
 * iteration:
 *	dp[i][j] = max(dp[i-1][j], dp[i-1][j-a[i].p] + a[i].s) if (j >= a[i].p).
 *	dp[i][j] = dp[i-1][j]; if (j < a[i].p)
 *	a[i]: consequence of things with two attributes: price(p) and evaluation score(s).)
 * simplification:
 *	dp[j] = max(dp[j], dp[j-a[i].p]+a[i].s) if (j >= a[i].p, and reverse iteration from
 *	c to a[i].p)
 */
#if 0
#include <stdio.h>

struct E {
	int p;	//price
	int s;	//score
};

E a[101];
int dp[101][1001];

#define max(a, b) ((a) > (b) ? (a) : (b))

int main()
{
	int c, n;

	while (scanf("%d%d", &c, &n) != EOF) {
		for (int i = 1; i <= n; ++i)
			scanf("%d%d", &a[i].p, &a[i].s);

		for (int j = 0; j <= c; ++j)
			dp[0][j] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= c; ++j) {
				if (j >= a[i].p) {
					dp[i][j] = max(dp[i-1][j], dp[i-1][j-a[i].p]+a[i].s);
				} else {
					dp[i][j] = dp[i-1][j];
				}
			}
		}
		printf("%d\n", dp[n][c]);
	}

	return 0;
}
#else

#include <stdio.h>

struct E {
	int p;
	int s;
};

E a[101];
int dp[1001];

#define max(a, b) ((a) > (b) ? (a) : (b))

int main()
{
	int c, n;

	while (scanf("%d%d", &c, &n) != EOF) {
		for (int i = 1; i <= n; ++i)
			scanf("%d%d", &a[i].p, &a[i].s);

		for (int j = 0; j <= c; ++j)
			dp[j] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = c; j >= a[i].p; --j)
				dp[j] = max(dp[j], dp[j-a[i].p]+a[i].s);
		}
		printf("%d\n", dp[c]);
	}

}

#endif
