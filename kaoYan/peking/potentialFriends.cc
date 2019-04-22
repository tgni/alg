#include <stdio.h>
#include <string.h>

#define Max	(200+1)
int man[Max];	//record book which man[i] likes
int books[Max]; //record numbers of men who like book[i] except themselves

int main()
{
	int n, m;

	while (scanf("%d%d", &n, &m) != EOF) {
		memset(man, 0, sizeof(man));
		memset(books, -1, sizeof(books));

		for (int i = 1; i <= n; ++i) {
			int p;
			scanf("%d", &p);
			man[i] = p;
			books[p]++;
		}

		for (int i = 1; i <= n; ++i) {
			if (books[man[i]] > 0) {
				printf("%d\n", books[man[i]]);
			} else {
				printf("BeiJu\n");
			}
		}
	}

	return 0;
}
