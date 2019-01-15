#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

struct Student {
	int  number;
	int  score;
	bool operator < (const Student &b) const {
		int tmp;

		if (score != b.score)
			return score < b.score;

		return number < b.number;
	}
};

Student stu[100];

int main(void)
{
	int n;

	while (scanf("%d", &n) != EOF) {

		for (int i = 0; i < n; ++i)
			scanf("%d%d", &stu[i].number, &stu[i].score);

		sort(stu, stu+n);

		for(int i = 0; i < n; i++) {
			printf("%d %d\n", stu[i].number, stu[i].score);
		}
	}

	return 0;
}
