#include <stdio.h>
#include <string.h>

int main(void)
{
	int l1, l2, i, j;
	char s1[32], s2[32];
	int sum;
	
	while (scanf("%s%s", s1, s2) != EOF) {
		l1 = strlen(s1);
		l2 = strlen(s2);
		sum = 0;
		for (i = 0; i < l1; ++i) {
			for (j = 0; j < l2; ++j) {
				sum += (s1[i]-'0')*(s2[j]-'0');
			}
		}
		printf("%d\n", sum);
	}

	return 0;
}
