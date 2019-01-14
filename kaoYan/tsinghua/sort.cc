#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

struct Student {
	char name[101];
	int  score;
	bool operator < (const Student &b) const {
		int tmp;

		if (score != b.score)
			return score < b.score;
	}
};

Student stu[1000];

int main(void)
{
	int n;

	while (scanf("%d", &n) != EOF) {

		for (int i = 0; i < n; ++i) {
			scanf("%s%d", stu[i].name, &stu[i].score);
		}

		sort(stu, stu+n);
		for(int i = 0; i < n; i++) {
			printf("%s %d\n", stu[i].name, stu[i].score);
		}
		printf("\n");
	}

	return 0;
}
