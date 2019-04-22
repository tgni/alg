/* Given a bundle of freckles which are discribed as (x, y) locations.
 * Calculate its minimum distance cost for connecting every freckle.
 * freckes is less than 100.
 * e.g.
 * Input:	3
 *		1.0 1.0
 *		2.0 2.0
 *		2.0 4.0
 * Output:	3.41
 */

#include <stdio.h>
#include <math.h>
#include <algorithm>

using namespace std;

#define MAX_FRECKLES	(100+1)
int Tree[MAX_FRECKLES];

struct Edge {
	int a, b;
	double cost;

	bool operator < (const Edge &A) const {
		return cost < A.cost;
	}
};

#define MAX_EDGES	(100*(100-1)/2+1)
Edge edge[MAX_EDGES];

struct Vertex {
	double x, y;

	double getDistance(const Vertex &A) {
		return sqrt((x-A.x)*(x-A.x)+(y-A.y)*(y-A.y));
	}
};

Vertex vertex[MAX_FRECKLES];

int findRoot(int x)
{
	if (Tree[x] == -1)
		return x;

	Tree[x] = findRoot(Tree[x]); //path compress

	return Tree[x];
}

int main(void)
{
	int n;

	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i)
			scanf("%lf%lf", &vertex[i].x, &vertex[i].y); // Pay attention to format 'lf': means double, 
								     // Lf means long double

		int edgeNum = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = i+1; j <= n; ++j) {
				edge[edgeNum].a = i;
				edge[edgeNum].b = j;
				edge[edgeNum].cost = vertex[i].getDistance(vertex[j]);
				edgeNum++;
			}
		}

		sort(edge, edge+edgeNum); // Take care: sort(first element, last range);

		for (int i = 1; i <= n; ++i)
			Tree[i] = -1;

		double total = 0;
		for (int i = 0; i < edgeNum; ++i) {
			int a = findRoot(edge[i].a);
			int b = findRoot(edge[i].b);
			if (a != b) {
				Tree[a] = b;
				total += edge[i].cost;
			}
		}

		printf("%.2lf\n", total);
	}

	return 0;
}
