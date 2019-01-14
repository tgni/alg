/* Coding.pdf Page 167
 */

#include <stdio.h>
#include <algorithm>

using namespace std;

#define INF	0x7FFFFFFF

int list[2001];
int dp[1001][2001]; //在前j个物品中，搬i对物品之后的疲劳度
		    //dp[i][j] = min{ dp[i][j-1], dp[i-1][j-2] + pow(list[j]-list[j-1], 2)}
int main(void)
{
	int n, k;

	while (scanf("%d%d", &n, &k) != EOF) {
		for (int i  = 1; i <= n; ++i) {
			scanf("%d", &list[i]);
		}
		sort(list+1, list+1+n);	//sort(first, range)
		for (int i = 1; i <= n; ++i)
			dp[0][i] = 0;
		for (int i = 1; i <= k; ++i) {
			for (int j = 2*i; j <= n; ++j) {
				if (j > 2*i)
					dp[i][j] = dp[i][j-1];
				else
					dp[i][j] = INF;
				if (dp[i][j] > dp[i-1][j-2]+(list[j]-list[j-1])*(list[j]-list[j-1]))
					dp[i][j] = dp[i-1][j-2] + (list[j]-list[j-1])*(list[j]-list[j-1]);
			}
		}
		printf("%d\n", dp[k][n]);
	}

	return 0;
}
