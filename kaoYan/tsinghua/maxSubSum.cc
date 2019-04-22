/*
 * dp[i] : max sub sum end of num[i]. the result will be max(dp[i], i belongs to [0 n)
 * dp[0] = num[0];
 * dp[i] = max(0, dp[i-1]) + num[i];
 */

#include <stdio.h>

#define INF	(0x7FFFFFFFFFFFFFFF)
#define max(a, b) ((a > b) ? a : b)

long A[1000000];

long maxSubSum(long A[], int n)
{
	long maxSum = -INF, sum = 0;

	for (int i = 0; i < n; ++i) {
		sum = max(0, sum) + A[i];
		maxSum = max(sum, maxSum); 
	}

	return maxSum;
}

int main()
{
	int n;

	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; ++i) {
			scanf("%ld", &A[i]);
		}
		printf("%ld\n", maxSubSum(A, n));
	}

	return 0;
}
