#include <stdio.h>
#include <string.h>

char str[100];

int main()
{
	while (scanf("%s", str) != EOF) {
		int len = strlen(str);
		long a=0, b=2;
		for (int i = len-1; i >= 0; --i) {
			a = a + (str[i]-'0') * (b -1);
			b = b * 2;
		}
		printf("%ld\n", a);
	}

	return 0;
}
