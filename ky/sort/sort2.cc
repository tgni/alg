#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

typedef struct score_entry_s {
	char name[101];
	int  age;
	int  score;
} score_entry_t;

score_entry_t SCORE[1000];

bool cmp(score_entry_t a, score_entry_t b)
{
	int result;

	if (a.score != b.score)
		return a.score < b.score;
	if ((result = strcmp(a.name, b.name)) != 0) {
		return result < 0;
	} else {
		return a.age < b.age;
	}
}

int main(void)
{
	int n;
	score_entry_t *ent = SCORE;

	while (scanf("%d", &n) != EOF) {

		printf("get n = %d \n", n);

		for (int i = 0; i < n; ++i) {
			scanf("%s%d%d", ent[i].name, &ent[i].age, &ent[i].score);
		}

		printf("before sort...\n");
		for(int i = 0; i < n; i++) {
			printf("%s %d %d\n", ent[i].name, ent[i].age, ent[i].score);
		}
		printf("\n");

		printf("after sort...\n");
		sort(ent, ent+n, cmp);
		for(int i = 0; i < n; i++) {
			printf("%s %d %d\n", ent[i].name, ent[i].age, ent[i].score);
		}
		printf("\n");
	}

	return 0;
}
