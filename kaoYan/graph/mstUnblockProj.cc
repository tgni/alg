/* Given N veritces, following N(N-1)/2 lines with every two vertices have an edge,
 * which format is: 
 *	N
 *	v1, v2, cost
 *	v1, v3, cost
 *		...
 *	vN-1, VN cost
 * Calculate minimum edge cost for forming MST.
 *
 * e.g.
 * input:
 *	3
 *	1 2 1
 *	1 3 2
 *	2 3 4
 * output:
 *	3
 */

#include <stdio.h>
#include <algorithm>

using namespace std;

#define	TOWN_MAX	(101)
int Tree[TOWN_MAX];

int findRoot(int x)
{
	if (Tree[x] == -1)
		return x;

	Tree[x] = findRoot(Tree[x]);	//path compressed

	return Tree[x];
}

struct Edge {
	int a, b;
	int cost;

	bool operator < (const Edge &A) const {
		return cost < A.cost;
	}
};

Edge edge[5000];	//max edge is C^{2}_{100} = 4950

int main(void)
{
	int n;

	while (scanf("%d", &n) != EOF && n != 0) {
		for (int i = 1; i <= n*(n-1)/2; ++i)
			scanf("%d%d%d", &edge[i].a, &edge[i].b, &edge[i].cost);

		sort(edge+1, edge+1+n*(n-1)/2);

		for (int i = 1; i <= n; ++i)
			Tree[i] = -1;

		int total = 0;
		for (int i = 1; i <= n*(n-1)/2; ++i) {
			int a = findRoot(edge[i].a);	
			int b = findRoot(edge[i].b);
			if (a != b) {
				Tree[a] = b;
				total += edge[i].cost;
			}
		}
		/* Because every two vertices must have an edge, so MST existed in any case.
		   No failure judgement is needed.
		 */
		printf("%d\n", total);
	}

	return 0;
}

