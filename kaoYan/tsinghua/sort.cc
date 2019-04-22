#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <functional>

using namespace std;

struct Student {
	char name[101];
	int  score;
	bool operator < (const Student &b) const {
		return score < b.score;
	}
	bool operator > (const Student &b) const {
		return score > b.score;
	}
};

Student stu[1000];

int main(void)
{
	int n, m;

	while (scanf("%d", &n) != EOF) {
		scanf("%d", &m);

		for (int i = 0; i < n; ++i) {
			scanf("%s%d", stu[i].name, &stu[i].score);
		}
		
		if (m == 1) {
			stable_sort(stu, stu+n);
		} else if (m == 0) {
			stable_sort(stu, stu+n, std::greater<Student>());
		}

		for(int i = 0; i < n; i++) {
			printf("%s %d\n", stu[i].name, stu[i].score);
		}
	}

	return 0;
}
