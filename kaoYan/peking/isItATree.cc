#include <stdio.h>
#include <queue>
#include <vector>
#include <set>

using namespace std;

#define MaxVertices	(100001)
vector<int> E[MaxVertices];
int inDegree[MaxVertices];
queue<int> Q;
set<int> V;

int main()
{
	int a, b, cas = 1, edge = 0, vertex = 0;

	while (scanf("%d%d", &a, &b) != EOF) {
		if (a < 0 && b < 0) {
			break;
		} else if (a == 0 && b == 0) {
			if (edge + 1 != V.size())
				goto clear;

			while (Q.empty() == false)
				Q.pop();

			for (auto i : V) {
				if (inDegree[i] == 0) {
					Q.push(i);
					break;	//more than one vertex's inDegree is zero 
						//are not allowed.
				}
			}

			while (Q.empty() == false) {
				int newP = Q.front();
				Q.pop();

				vertex++;
				for (int i = 0; i < E[newP].size(); i++) {
					if (--inDegree[E[newP][i]] == 0)
						Q.push(E[newP][i]);
				}
			}
clear:
			if (vertex == V.size())
				printf("Case %d is a tree.\n", cas);
			else
				printf("Case %d is not a tree.\n", cas);

			for (auto i : V) {
				inDegree[i] = 0;
				E[i].clear();
			}
			V.clear();
			vertex = 0;
			edge = 0;
			cas++;
			continue;
		}
		V.insert(a);
		V.insert(b);
		inDegree[b]++;
		++edge;
		E[a].push_back(b);
	}

	return 0;
}
