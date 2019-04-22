#include <stdio.h>
#include <string.h>

char pattern[1000000];
char str[1000000];
int next[1000000];

void get_next(char s[])
{
	int j = 0, k = -1, len = strlen(s);

	next[0] = -1;
	while (j < len - 1) {
		if (k == -1 || pattern[j] == pattern[k]) {
			next[++j] = ++k;
		} else {
			k = next[k];
		}
	}
}

int kmp(char *s, char *p)
{
	int i = 0, j = 0;
	int len = strlen(s), plen = strlen(p);

	while (i < len && j < plen) {
		if (j == -1 || s[i] == p[j]) {
			++i; ++j;
		} else {
			j = next[j];
		}
	}

	if (j >= plen)
		return i - j;

	return -1;
}

int main()
{
	while (scanf("%s%s", str, pattern) != EOF) {
		get_next(pattern);
		int cnt = 0, pos = 0;
		char *p = str;
		while (1) {
			if ((pos = kmp(p, pattern)) < 0)
				break;
			p += pos+1;
			++cnt;
		}
		printf("%d\n", cnt);
	}
	return 0;
}
