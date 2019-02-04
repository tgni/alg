#include <stdio.h>

float achieve(int score)
{
	if (score >= 90 && score <= 100)
		return 4.0;
	else if (score >= 85 && score <= 89)
		return 3.7;
	else if (score >= 82 && score <= 84)
		return 3.3;
	else if (score >= 78 && score <= 81)
		return 3.0;
	else if (score >= 75 && score <= 77)
		return 2.7;
	else if (score >= 72 && score <= 74)
		return 2.3;
	else if (score >= 68 && score <= 71)
		return 2.0;
	else if (score >= 64 && score <= 67)
		return 1.5;
	else if (score >= 60 && score <= 63)
		return 1.0;
	else
		return 0;
}

int main()
{
	int n;
	
	while (scanf("%d", &n) != EOF) {
		int p[n], sum=0;
		float gpa = 0.0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &p[i]);
			sum += p[i];
		}
		for (int i = 0; i < n; ++i) {
			int m;
			scanf("%d", &m);
			gpa += achieve(m) * p[i];
		}
		gpa = gpa / sum;
		printf("%.2f", gpa);
	}

	return 0;
}
