
#include <stdio.h>

int dp[1000001];

int divideInteger(int n)
{
	dp[1] = 1;

	for (int i = 2; i <= n; ++i) {
		if (i % 2)
			dp[i] = dp[i-1] % 1000000000;
		else
			dp[i] = (dp[i-1] + dp[i/2]) % 1000000000;

	}
	return dp[n];
}

int main()
{
	int n;

	divideInteger(1000000);

	while (scanf("%d", &n) != EOF)
		printf("%d\n", dp[n]);

	return 0;
}

