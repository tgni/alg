#include <stdio.h>
#include <string.h>

int main()
{
	char s1[10], s2[10];

	while (scanf("%s%s", s1, s2) != EOF) {
		int carry = 0, sum = 0, len1 = strlen(s1), len2 = strlen(s2);
		for (int i = len1-1, j = len2-1; i >= 0 || j >= 0;) {
			int a = s1[i] - '0';
			int b = s2[j] - '0';

			if (i < 0) a = 0;
			if (j < 0) b = 0;

			if (a+b+carry >= 10) {
				carry = 1;
				++sum;
			} else {
				carry = 0;
			}

			if (i >= 0) --i;
			if (j >= 0) --j;
		}

		if (sum == 0)
			printf("NO carry operation.\n");
		else if (sum > 1)
			printf("%d carry operations.\n", sum);
		else if (sum == 1)
			printf("1 carry operation.\n");
	}

	return 0;
}
