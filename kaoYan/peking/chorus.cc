#include <stdio.h>
#include <algorithm>
#include <cstring>

using namespace std;

int dp1[101];
int dp2[101];

int lis(int list[], int n)
{
	for (int i = 1; i <= n; ++i) {
		int tmax = 1;
		for (int j = 1; j < i; ++j)
			if (list[j] < list[i])
				tmax = max(tmax, dp1[j]+1);
		dp1[i] = tmax;
	}
	for (int i = n; i >= 1; --i) {
		int tmax = 1;
		for (int j = n; j > i; --j)
			if (list[j] < list[i])
				tmax = max(tmax, dp2[j]+1);
		dp2[i] = tmax;
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans = max(ans, dp1[i]+dp2[i]-1);
	}

	return n-ans;
}

int main()
{
	int n;
	while (scanf("%d", &n) != EOF) {
		int list[n+1];
		for (int i = 1; i <= n; ++i)
			scanf("%d", &list[i]);
		int ans = lis(list, n);
		printf("%d\n", ans);
	}
	return 0;
}
