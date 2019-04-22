#include <iostream>
#include <algorithm>

using namespace std;

#define Idx(c)	(c-'A')
#define	MAXV	(27)
int tree[MAXV];

int findRoot(int x)
{
	if (tree[x] == -1)
		return x;
	tree[x] = findRoot(tree[x]);

	return tree[x];
}

struct Edge {
	char s, e;
	int cost;

	bool operator < (const Edge &A) const {
		return cost < A.cost;
	}
};

#define MAXE	(75)
Edge edge[MAXE];


int main()
{
	int n;

	while (cin >> n && n != 0) {
		int edgeNum = 0;
		for (int i = 0; i < n-1; ++i) {
			char s, e;
			int k, cost;
			cin >> s >> k;
			for (int i = 0; i < k; ++i) {
				cin >> e >> cost;
				edge[edgeNum].s = s;
				edge[edgeNum].e = e;
				edge[edgeNum].cost = cost;
				edgeNum++;
			}
		}
		sort(edge, edge+edgeNum);

		for (int i = 0; i < n; ++i)
			tree[i] = -1;

		int total = 0;
		for (int i = 0; i < edgeNum; ++i) {
			int a = findRoot(Idx(edge[i].s));
			int b = findRoot(Idx(edge[i].e));
			if (a != b) {
				tree[a] = b;
				total += edge[i].cost;
			}
		}
		cout << total << endl;
	}

	return 0;
}
