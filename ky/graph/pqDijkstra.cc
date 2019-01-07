 /* Given <n, m>, following with m lines, each line contains <a, b, c>, a refers to a start point,
 * b is an end point, c is cost between them. range follows: 1 <= a, b <= n, 1 <= c <= 1000.
 * Find the shortest path from 1 to n. When <n, m> = <0, 0> program ends.
 */

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

	bool operator < (const Vertex &A) const {
		return A.dist < dist;		// min-heap
	}
};

#define MAX_VERTICES	(100+1)

vector<Edge> edge[MAX_VERTICES];
bool Mark[MAX_VERTICES];
int Distance[MAX_VERTICES];

int main(void)
{
	int n, m;

	while (scanf("%d%d", &n, &m) != EOF) {
		if (n == 0 && m == 0)
			break;
		for (int i = 1; i <= n; ++i)
			edge[i].clear();
		
		while (m--) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			Edge e;
			e.cost = c;
			e.next = b;
			edge[a].push_back(e);
			e.next = a;
			edge[b].push_back(e); // no direction graph. 
					      // each edge exists in two vertex adjacent list.
		}

		for (int i = 1; i <= n; ++i) {
			Mark[i] = false;
			Distance[i] = -1;
		}

		priority_queue<Vertex> que;
		Vertex x;
		x.v = 1;		//start as 1
		x.dist = 0;
		que.push(x);

		Distance[x.v] = 0;
		Mark[x.v] = true;
		
		while (!que.empty()) {
			x = que.top();
			que.pop();

			Mark[x.v] = true;

			for (int j = 0; j < edge[x.v].size(); ++j) {
				int t = edge[x.v][j].next;
				int cost = edge[x.v][j].cost;

				if (Mark[t] == true)
					continue;

				if (Distance[t] == -1 || Distance[t] > Distance[x.v]+cost) {
					Distance[t] = Distance[x.v] + cost;
					Vertex y;
					y.v = t;
					y.dist = Distance[t];
					que.push(y);
				}
			}
		}

		printf("%d\n", Distance[n]);
	}

	return 0;
}
