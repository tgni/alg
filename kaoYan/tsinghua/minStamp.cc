/* 
题目描述
    有若干张邮票，要求从中选取最少的邮票张数凑成一个给定的总值。  如，有1分，3分，3分，3分，4分五张邮票，要求凑成10分，则使用3张邮票：3分、3分、4分即可。
输入描述:
    有多组数据，对于每组数据，首先是要求凑成的邮票总值M，M<100。然后是一个数N，N〈20，表示有N张邮票。接下来是N个正整数，分别表示这N张邮票的面值，且以升序排列。
输出描述:
      对于每组数据，能够凑成总值M的最少邮票张数。若无解，输出0。

分析:
	化解为0-1背包问题，每张邮票为一个物体，面值对应于物体的体积，物体的价值恒为1，总面值为M即背包总体积为M, 能够凑成总值M的最少邮票张数即在背包总体积为M时，
	物体具有的最小价值。此为求最小值问题。并且注意，背包必须装满。
 */

#include <iostream>

using namespace std;

#define INF	0x7fffffff

struct E {
	int w;		//物体的体积即邮票的面值
	int v = 1;	//value == 1
};

int min(int a, int b)
{
	return a < b ? a : b;
}

E list[21]; //邮票序列
int dp[101]; //dp[j] 表示在邮票总值为j时，需要的邮票最小数量。

int main()
{
	int n, m;

	while (cin >> m >> n) {
		for (int i = 1; i <= n; ++i) {
			cin >> list[i].w;
		}
		for (int i = 0; i <= m; ++i) {
			dp[i] = INF;	//求最小值，那么初值为正无穷
		}
		dp[0] = 0;	//背包恰好装满的情况，只有dp[0]为合法值

		for (int i = 1; i <= n; ++i) {
			for (int j = m; j >= list[i].w; --j) {
				if (dp[j-list[i].w] != INF) {
					dp[j] = min(dp[j-list[i].w]+list[i].v, dp[j]);
				}
			}
		}

		if (dp[m] > 0 && dp[m] != INF)
			cout << dp[m] << endl;
		else
			cout << 0 << endl;
	}

	return 0;
}
