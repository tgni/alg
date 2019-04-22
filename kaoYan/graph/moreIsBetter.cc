/* Calculate size of one Union, select the maximum.
 */
#include <stdio.h>

#define MAX_TREE	(10000001)
int Tree[MAX_TREE];
int Sum[MAX_TREE];

int findRoot(int x)
{
	if (Tree[x] == -1)
		return x;

	Tree[x] = findRoot(Tree[x]);	//path compressed 

	return Tree[x];
}

int main(void)
{
	int n;

	while (scanf("%d", &n) != EOF) {
		if (n == 0)
			break;
		for (int i = 1; i < MAX_TREE; ++i) {
			Tree[i] = -1;
			Sum[i] = 1;
		}

		while (n--) {
			int a, b;
			scanf("%d%d", &a, &b);
			a = findRoot(a);
			b = findRoot(b);
			if (a != b) { 
				Tree[a] = b;
				Sum[b] += Sum[a];
			}
		}
		
		int ans = 0;
		for (int i = 1; i < MAX_TREE; ++i) {
			if (Tree[i] != -1) {
				printf("%d->%d\n", i, Tree[i]);
			}
			if (Tree[i] == -1 && Sum[i] > ans) { 
				printf("Sum[%d]:%d\n", i, Sum[i]);
				ans = Sum[i];
			}
		}
		printf("%d\n", ans);
	}

	return 0;
}
