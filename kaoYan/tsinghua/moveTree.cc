#include <stdio.h>

int tree[10001];
struct Zone {
	int start;
	int end;
};

int main()
{
	int L, M;

	while (scanf("%d%d", &L, &M) != EOF) {
		Zone z[M];
		for (int i = 0; i < M; ++i) {
			scanf("%d%d", &z[i].start, &z[i].end);
		}

		for (int i = 0; i <= L; ++i)
			tree[i] = 1;
		for (int j = 0; j < M; ++j) {
			for (int k = z[j].start; k <= z[j].end; ++k) {
				if (tree[k])
					tree[k] = 0;
			}
		}
		int remain = 0;
		for (int i = 0; i <= L; ++i)
			if (tree[i])
				++remain;
		printf("%d\n", remain);
	}

	return 0;
}
