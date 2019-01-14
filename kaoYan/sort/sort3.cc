#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

typedef struct score_entry_s {
	char name[101];
	int  age;
	int  score;
	bool operator < (const score_entry_s &b) const {
		int tmp;

		if (score != b.score)
			return score < b.score;
		if ((tmp = strcmp(name, b.name)) != 0)
			return tmp < 0;
		else
			return age < b.age;
	}
} score_entry_t;

score_entry_t SCORE[1000];

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
		sort(ent, ent+n);
		for(int i = 0; i < n; i++) {
			printf("%s %d %d\n", ent[i].name, ent[i].age, ent[i].score);
		}
		printf("\n");
	}

	return 0;
}
