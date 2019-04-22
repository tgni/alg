/**
  ���壺
  dp[i][j] ��ʾǰi����Ʒ�ﵽ���Ϊjʱ������ѡ����Ʒ�ķ�ʽ�� (1<=i<=20, 1<=j<=40)
  a[i]: ���Ϊa[i]����Ʒ����
  dp[i][j] = dp[i-1][j] + dp[i-1][j-a[i]]; ��ѡa[i]����ѡ��a[i]. (a[i] <= j)
  dp[i][j] = dp[i-1][j]; (a[i] > j)
  ��ֵ��
  dp[i][0] = 1; �ﵽ���0�ķ�ʽֻ��1�֣�����ѡ��Ʒ
  dp[0][j] = 0; �ﵽ���j��j > 0, ��û����Ʒ��û�з�ʽ����������Ϊ0.
  �����
  dp[n][40]

  consider dp[i][j] is only related to dp[i-1][j] and dp[i-1][j-a[i]], we could
  DEFINE:
	dp[j] as ways of selection of the previous i objects volume up to j.
	dp[j] = dp[j] + dp[j-a[i]], (a[i] <= j)
	dp[j] = dp[j], (a[i] > j)
  INIT:
	dp[0] = 1	   //ways to volume 0, always be 1.
	dp[j] = 0  (j > 0) //no objects, ways to volume j, always be 0.
*/

#include <stdio.h>

int dp[41];	

int main()
{
	int n;

	while (scanf("%d", &n) != EOF) {
		int a[n+1];
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		for (int j = 1; j <= 40; ++j)
			dp[j] = 0;
		dp[0] = 1;
		for (int i = 1; i <= n; ++i) {
			/* reverse update dp[j], for keeping dp[j-a[i]] not change before update dp[j]. */
			for (int j = 40; j >= 1; --j) {
				if (a[i] <= j)
					dp[j] = dp[j] + dp[j-a[i]];
			}
		}
		printf("%d\n", dp[40]);
	}

	return 0;
}
