/* Coding.pdf Page 179
 */

#include <stdio.h>

#define max(a, b)	((a) > (b) ? (a) : (b))

struct E {
	int w;	//weight
	int v;	//value
} list[2001]; //how to define this number?

int dp[101]; //this number is not accurate

/* state function: 0-1背包问题:
 * dp[i][j] = max{dp[i-1][j-list.v] + list.w, dp[i-1][j]}
 * 在总价值不超过j的情况下，前i个物品能够达到的最大重量。
 * 化成一维：
 * dp[j] = max{dp[j-list.v]+list.w, dp[j]}
 */

int main(void)
{
	int T;
	scanf("%d", &T);

	while (T--) {
		int s, n;
		scanf("%d%d", &s, &n);

		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			int v, w, k;
			scanf("%d%d%d", &v, &w, &k);//(v, w, k) price, weight, number
			int c = 1;
			while (k-c > 0) {
				k -= c;
				list[++cnt].w = c*w;
				list[cnt].v = c*v;

				c *= 2;
			}
			//rest of k
			list[++cnt].w = k*w;
			list[cnt].v = k*v;
		}
		n = cnt;

		for (int i = 1; i <= s; ++i)	//
			dp[i] = 0;	//不要求上限
		for (int i = 1; i <= n; ++i) {
			for (int j = s; j >= list[i].v; --j) {
				dp[j] = max(dp[j], dp[j-list[i].v]+list[i].w);
			}
		}

		printf("%d\n", dp[s]);
	}

	return 0;
}
