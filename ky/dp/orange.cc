/* Separate N oranges to keep two sides of scale having the same weight.
 * Calculate maximum weight of each side. Line 1 is case Number, line 2 
 * is number N, line 3 is maximum weight of one side. N < 100, total 
 * weight is less than 2000 kilograms.
 * e.g. 
 * input 1
 *	 5
 *	 1 2 3 4 5
 * output
 *	 case 1: 7
 */

#include <stdio.h>

#define OFFSET	(2000)

int dp[101][4001];
int list[101];

#define INF	(0x7fffffff)

#define _max(a, b)	((a) > (b) ? (a) : (b))
#define max(a, b, c)	((a) > (b) ? _max((a), (c)) : _max((b), (c)))

int main(void)
{
	int T, cas = 0;
	
	scanf("%d", &T);

	while (T-- != 0) {
		int n;
		scanf("%d", &n);

		bool haveZero = false;
		int cnt = 0;

		for (int i = 1; i <= n; ++i) {
			scanf("%d", &list[++cnt]); //omit list[0]
			if (list[cnt] == 0) {
				cnt--;
				haveZero = true;
			}
		}
		n = cnt;

		for (int i = -2000; i <= 2000; ++i) {
			dp[0][i+OFFSET] = -INF;
		}
		dp[0][0+OFFSET] = 0;

		for (int i = 1; i <= n; ++i) {
			int a = -INF, b = -INF;
			for (int j = -2000; j <= 2000; ++j) {
				if (j+list[i] <= 2000 && dp[i-1][j+list[i]+OFFSET] != -INF)
					a = dp[i-1][j+list[i]+OFFSET] + list[i];
				if (j-list[i] >= -2000 && dp[i-1][j-list[i]+OFFSET] != -INF)
					b = dp[i-1][j-list[i]+OFFSET] + list[i];

				dp[i][j+OFFSET] = max(a, b, dp[i-1][j+OFFSET]);
			}
		}

		printf("Case %d: ", ++cas);
		if (dp[n][0+OFFSET] == 0)
			printf("%d\n", haveZero == true ? 0 : -1);
		else
			printf("%d\n", dp[n][0+OFFSET] / 2);
	}

	return 0;
}
