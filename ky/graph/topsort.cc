/* Given <n, m> n is numbers of vertices, following m pair of relationship between them.
 * one number as one vertex. range at: 0 <= i <= n-1. 2 <= N, M <= 100
 */
#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

#define MAX_EDGE	(101)
vector<int> edge[MAX_EDGE];
queue<int> Q;
int inDegree[MAX_EDGE];

int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {
		if (n == 0 && m == 0)
			break;

		for (int i = 0; i < n; ++i) {
			inDegree[i] = 0;
			edge[i].clear();
		}
		while (m--) {
			int a, b;
			scanf("%d%d", &a, &b);
			inDegree[b]++;
			edge[a].push_back(b);
		}

		while (Q.empty() == false) Q.pop();  //clear queue

		for (int i = 0; i < n; ++i)
			if (inDegree[i] == 0) Q.push(i);

		int cnt = 0;
		while (Q.empty() == false) {
			int newP = Q.front();
			Q.pop();

			cnt++;
			for (int i = 0; i < edge[newP].size(); i++) {
				if (--inDegree[edge[newP][i]] == 0)
					Q.push(edge[newP][i]);
			}
		}
		if (cnt == n)
			puts("YES");
		else
			puts("NO");
	}

	return 0;
}
