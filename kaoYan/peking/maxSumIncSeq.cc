#include <iostream>
#include <algorithm>

using namespace std;

int dp[1001];
int list[1001];

/* largest sum of increasing sequence */
int lsis(int list[], int n)
{
	for (int i = 1; i <= n; ++i) {
		dp[i] = 0;
		int tmax = list[i];
		for (int j = 1; j < i; ++j) {
			if (list[j] < list[i])
				tmax = max(tmax, dp[j]+list[i]);
		}
		dp[i] = tmax;
	}

	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = max(ans, dp[i]);

	return ans;
}

int main()
{
	int n;
	while (cin >> n) {
		for (int i = 1; i <= n; ++i)
			cin >> list[i];
		cout << lsis(list, n) << endl;
	}

	return 0;
}
