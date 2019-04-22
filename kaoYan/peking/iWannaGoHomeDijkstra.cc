#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
	int next;
	int cost;
};

struct Vertex {
	int v;
	int dist;

	bool operator < (const Vertex & A) const {
		return A.dist < dist;	//!!! min-heap; max-heap will be dist < A.dist;
	}
};

#define INF		(500*600+1)
#define MaxCitys	(600+1)

vector<Edge> edge[MaxCitys];
int leader[MaxCitys];
bool mark[MaxCitys];
int dist[MaxCitys];

int main()
{
	int n, m;

	while (scanf("%d", &n) != EOF) {
		if (n == 0)
			break;
		for (int i = 1; i <= n; ++i)
			edge[i].clear();

		scanf("%d", &m);
		while (m--) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			Edge e;
			e.cost = c;
			e.next = b;
			edge[a].push_back(e);
			e.next = a;
			edge[b].push_back(e);
		}

		for (int i = 1; i <= n; ++i) {
			scanf("%d", &leader[i]);
			mark[i] = false;
			dist[i] = INF;
		}

		priority_queue<Vertex> que;
		Vertex x;
		x.v = 1;	//start as 1
		x.dist = 0;
		que.push(x);
		dist[x.v] = 0;
		mark[x.v] = true;

		while (!que.empty()) {
			x = que.top();
			que.pop();

			int v = x.v;
			mark[v] = true;

			for (int i = 0; i < edge[v].size(); ++i) {
				int t = edge[v][i].next;
				int cost = edge[v][i].cost;

				if (mark[t] == true)
					continue;
				if (leader[v] == 2 && leader[t] == 1)
					continue;

				if (dist[t] > dist[v] + cost) {
					dist[t] = dist[v] + cost;
					x.v = t;
					x.dist = dist[t];
					que.push(x);
				}
			}
		}

		printf("%d\n", dist[2] == INF ? -1 : dist[2]);
	}

	return 0;
}
