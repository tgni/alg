#include <stdio.h>
#include <algorithm>
/*
	Test Data: 12 groups
	start, end
	1,	3
	3,	4
	0,	7
	3,	8
	15,	19
	15,	20
	10,	15
	8,	18
	6,	12
	5,	10
	4,	14
	2,	9
 */

using namespace std;

struct program {
	int startTime;
	int endTime;
	bool operator < (const program & A) const {
		return endTime < A.endTime;
		//return startTime < A.startTime;
		//return endTime-startTime < A.endTime-A.startTime;
	}
} buf[100];

int main()
{
	int n;

	while (scanf("%d", &n) != EOF) {
		if (n == 0)
			break;
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &buf[i].startTime, &buf[i].endTime);
		}

		printf("before sort\n");
		for (int i = 0; i < n; ++i)
			printf("idx: %d start: %d end %d\n", i, buf[i].startTime, buf[i].endTime);
		sort(buf, buf+n);
		printf("after sort\n");
		for (int i = 0; i < n; ++i)
			printf("idx: %d start: %d end %d\n", i, buf[i].startTime, buf[i].endTime);

		int currentTime = 0, answer = 0;
		for (int i = 0; i < n; ++i) {
			if (currentTime <= buf[i].startTime) {
				currentTime = buf[i].endTime;
				++answer;
				printf("currentTime: %d, idx %d\n", currentTime, i);
			}
		}
		printf("%d", answer);
	}

	return 0;
}
