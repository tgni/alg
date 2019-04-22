 /* Given <n, m>, following with m lines, each line contains <a, b, c>, a refers to a start point,
 * b is an end point, c is cost between them. range follows: 1 <= a, b <= n, 1 <= c <= 1000.
 * Find the shortest path from 1 to n. When <n, m> = <0, 0> program ends.
 */

#include <stdio.h>
#include <vector>

using namespace std;

struct E {
	int next;
	int cost;
};

#define MAX_VERTICES	(100+1)

vector<E> edge[MAX_VERTICES];
bool Mark[MAX_VERTICES];
int Distance[MAX_VERTICES];

int main()
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
			E e;
			e.cost = c;
			e.next = b;
			edge[a].push_back(e);
			e.next = a;
			edge[b].push_back(e); // no direction graph. 
					      // each edge exists in two vertex adjacent list.
		}

		for (int i = 1; i <= n; ++i) {
			Distance[i] = -1;
			Mark[i] = false;
		}

		Distance[1] = 0;
		Mark[1] = true;		//start as 1
		int newP = 1;
		
		for (int i = 1; i < n; ++i) {
			for (int j = 0; j < edge[newP].size(); ++j) {
				int t = edge[newP][j].next;
				int cost = edge[newP][j].cost;

				if (Mark[t] == true)
					continue;

				if (Distance[t] == -1 || Distance[t] > Distance[newP]+cost)
					Distance[t] = Distance[newP] + cost;
			}

			//update newP
			int min = 123123123;
			for (int j = 1; j <= n; ++j) {
				if (Mark[j] == true)
					continue;
				if (Distance[j] == -1)
					continue;
				if (Distance[j] < min) {
					min = Distance[j];
					newP = j;
				}
			}
			Mark[newP] = true;
		}
		printf("%d\n", Distance[n]);
	}

	return 0;
}
