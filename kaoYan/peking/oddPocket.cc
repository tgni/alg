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
