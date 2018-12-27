#include <stdio.h>

int main(void)
{
	int h, i, j;

	printf("Please input h: \n");
	while (scanf("%d", &h) != EOF) {
		for (i = 0; i < h; ++i) {
			for (j = h-i-1; j > 0; --j)
				printf("  ");
			for (j = 0; j < 2*i+h; ++j)
				printf("*");
			printf("\n");
		}
	}

	return 0;
}
