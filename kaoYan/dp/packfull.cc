/* Piggy-Bank
 * Coding.pdf Page 175
 */

#include <stdio.h>

#define INF 0x7fffffff
#define min(a, b)	((a) < (b) ? (a) : (b))
#define COIN_MAX	(501)
#define WEIGHT_MAX	(10001)

struct E {
	int w;
	int v;
} list[COIN_MAX];

int dp[WEIGHT_MAX];

int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		int s, tmp;
		scanf("%d%d", &tmp, &s);
		s -= tmp;

		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%d%d", &list[i].v, &list[i].w);
		for (int i = 0; i <= s; i++)
			dp[i] = INF;
		dp[0] = 0;	//demand packet full
		
		for (int i = 1; i <= n; ++i) {
			for (int j = list[i].w; j <= s; ++j) {
				if (dp[j-list[i].w] != INF)
					dp[j] = min(dp[j], dp[j-list[i].w] + list[i].v);
			}
		}

		if (dp[s] != INF) {	//may full or not, judge is needed.
			printf("The minimum amount of money in the piggy-bank is %d.\n", dp[s]);
		} else {
			printf("This is impossible.\n");
		}
	}

	return 0;
}
