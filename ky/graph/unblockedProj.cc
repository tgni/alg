/* fileName:  unblockedProj.cc
 * description:
 * Given n, m. n is number of towns, m is existed ways between two towns. 
 * Find the minimum mays should be added in order to keep any of two towns connected.
 * format: first line: n, m
 *	   followed m lines indicating which two towns is connected.
 * eg:	 3, 2
 *	 1, 2
 *	 3, 2
 * the programe exit after input n == 0
 */
#include <stdio.h>

#define MAX_TREE	(1000)
int Tree[MAX_TREE];

int findRoot(int x)
{
	if (Tree[x] == -1)
		return x;

	Tree[x] = findRoot(Tree[x]);	//path compressed 

	return Tree[x];
}

int main(void)
{
	int n, m;

	while (scanf("%d", &n) != EOF) {
		if (n == 0)
			break;
		scanf("%d", &m);
		for (int i = 1; i <= n; ++i)
			Tree[i] = -1;

		while (m--) {
			int a, b;
			scanf("%d%d", &a, &b);
			a = findRoot(a);
			b = findRoot(b);
			if (a != b) Tree[a] = b;
		}
		
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			printf("%d -> %d\n", i, Tree[i]);
			if (Tree[i] == -1) ans++;
		}
		printf("%d\n", ans-1);	//minus 1 means rest of edge should be added.
	}

	return 0;
}
