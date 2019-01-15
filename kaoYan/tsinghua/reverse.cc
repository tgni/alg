#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[5];

	while (scanf("%s", str) != EOF) {
		int len = strlen(str);

		for (int i = len-1; i >= 0; --i)
			printf("%c", str[i]);
		printf("\n");
	}

	return 0;
}
