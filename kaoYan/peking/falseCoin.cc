/* 1. 将结果分为三组，相等组，小于组，大于组。
	A = B， A，B都加入相等组。
	A < B,  A加入小于组，B加入大于组，同时，不等于A或B的其他数加入相等组。
	A > B,  A加入大于组，B加入小于组，同时，不等于A或B的其他数加入相等组。
   2. 如果一个数既出现在小于组又出现在大于组，那么把它加入相等组。
   3. 判断相等组中未出现的数字，如果超过一个，则返回结果0，如果恰好为1个则结果
      为该数字。
 */

#include <stdio.h>
#include <set>

using namespace std;

int main()
{
	int n, k;
	while (scanf("%d%d", &n, &k) != EOF) {
		set<int> equal;
		set<int> less;
		set<int> great;
		while (k--) {
			int m;
			scanf("%d", &m);
			int t[2*m+1];
			for (int i = 1; i <= 2*m; ++i)
				scanf("%d", &t[i]);

			getchar();//skip 'enter'

			char flag;
			scanf("%c", &flag);

			if (flag == '<') {
				for (int i = 1; i <= m; ++i)
					less.insert(t[i]);
				for (int i = m+1; i <= 2*m; ++i)
					great.insert(t[i]);
				for (int i = 1; i <= n; ++i) {
					int j;
					for (j = 1; j <= 2*m; ++j) {
						if (i == t[j])
							break;
					}
					if (j == 2*m+1)
						equal.insert(i);
				}
			} else if (flag == '>') {
				for (int i = 1; i <= m; ++i)
					great.insert(t[i]);
				for (int i = m+1; i <= 2*m; ++i)
					less.insert(t[i]);
				for (int i = 1; i <= n; ++i) {
					int j;
					for (j = 1; j <= 2*m; ++j) {
						if (i == t[j])
							break;
					}
					if (j == 2*m+1)
						equal.insert(i);
				}
			} else if (flag == '=') {
				for (int i = 1; i <= 2*m; ++i)
					equal.insert(t[i]);
			}
		}

		for (auto c : less) {
			if (great.find(c) != great.end()) {
				equal.insert(c);
			}
		}

		int cnt = 0, ans = -1;
		for (int i = 1; i <= n; ++i) {
			if (equal.find(i) == equal.end()) {
				if (++cnt > 1)
					break;
				ans = i;
			}
		}
		if (cnt == 1)
			printf("%d\n", ans);
		else
			printf("0\n");
	}

	return 0;
}
