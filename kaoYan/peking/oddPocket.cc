/**
  定义：
  dp[i][j] 表示前i个物品达到体积为j时，可以选择物品的方式。 (1<=i<=20, 1<=j<=40)
  a[i]: 体积为a[i]的物品序列
  dp[i][j] = dp[i-1][j] + dp[i-1][j-a[i]]; 不选a[i]或者选择a[i]. (a[i] <= j)
  dp[i][j] = dp[i-1][j]; (a[i] > j)
  初值：
  dp[i][0] = 1; 达到体积0的方式只有1种，即不选物品
  dp[0][j] = 0; 达到体积j，j > 0, 但没有物品，没有方式可以做到。为0.
  结果：
  dp[n][40]
*/

#include <stdio.h>

using namespace std;

int dp[21][41];	

int main()
{
	int n;

	while (scanf("%d", &n) != EOF) {
		int a[n+1];
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		for (int i = 0; i <= n; ++i)
			dp[i][0] = 1;
		/* although c++ will initiate dp[i][j] as 0, we still do it again for clarity.*/
		for (int j = 1; j <= 40; ++j)
			dp[0][j] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= 40; ++j) {
				if (a[i] <= j) {
					dp[i][j] = dp[i-1][j] + dp[i-1][j-a[i]];
				} else {
					dp[i][j] = dp[i-1][j];
				}
			}
		}
		printf("%d\n", dp[n][40]);
	}

	return 0;
}
