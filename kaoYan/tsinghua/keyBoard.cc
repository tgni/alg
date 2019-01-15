#include <stdio.h>
#include <string.h>

int time[26] = {
	1, 2, 3, /* a, b, c */
	1, 2, 3, /* d, e, f */
	1, 2, 3, /* g, h, i */
	1, 2, 3, /* j, k, l */
	1, 2, 3, /* m, n, o */
	1, 2, 3, 4, /* p, q, r, s*/
	1, 2, 3, /* t, u, v */
	1, 2, 3, 4 /* w, x, y, z */
};

int group[26] = {
	1, 1, 1,
	2, 2, 2,
	3, 3, 3,
	4, 4, 4,
	5, 5, 5,
	6, 6, 6, 6,
	7, 7, 7,
	8, 8, 8, 8
};

char str[100];

int main(void)
{
	while (scanf("%s", str) != EOF) {
		int len = strlen(str);

		if (len == 1) {
			printf("%d\n", time[str[0]-'a']);
			continue;
		}

		int t = time[str[0]-'a'];

		for (int i = 1; i < len; ++i) {
			if (group[str[i-1]-'a'] != group[str[i]-'a'])
				t += 2;
			t += time[str[i]-'a'];
		}
		printf("%d\n", t);
	}

	return 0;
}
