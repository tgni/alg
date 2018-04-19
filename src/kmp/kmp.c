#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int match(char *s, int len, char *p, int plen)
{
	int i = 0, j = 1;

	while (i < len && j < plen) {
		if (s[i] == p[j]) {
			++i; ++j;
		} else {
			i = i - j + 1;
			j = 0;
		}
	}

	if (j >= plen)
		return i - j;

	return -1;
}

void dump_next(int next[], int len)
{
	int i;
	printf("next:");
	for (i = 0; i < len; ++i) {
		printf("%d ", next[i]);
	}
	printf("\n");
}

void get_next(char *pattern, int len, int next[])
{
	int j = 0, k = -1;

	next[0] = -1;
	while (j < len - 1) {
		dump_next(next, len);
		printf("j: %d k: %d, pat[j]:%c, pat[k]:%c\n", j, k, pattern[j], pattern[k]);
		if (k == -1 || pattern[j] == pattern[k]) {
			next[++j] = ++k;
		} else {
			k = next[k];
		}
	}

	return;
}

int kmp(char *s, int len, char *p, int plen, int next[])
{
	int i = 0, j = 0;

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
	//char *pattern = "abababca";
	char *pattern = "abaabcac";
	char *s = "ababababca";
	int pos, i, j, *next;

	if (!(next = malloc(strlen(pattern)*sizeof(int)))) {
		printf("failed to malloc\n");
		return -1;
	}

	printf("s: %s, strlen(s): %d\n", s, (int)strlen(s));
	printf("pattern: %s, strlen(pattern): %d\n", pattern, (int)strlen(pattern));
	get_next(pattern, strlen(pattern), next);
	pos = kmp(s, strlen(s), pattern, strlen(pattern), next);
	printf("pos: %d\n", pos);

#if 0	
	printf("pattern: %s\n", pattern);
	printf("       : ");
	for (i = 0; i < strlen(pattern); ++i)
		printf("%d", i);
	printf("\n");

	get_next(pattern, strlen(pattern), next);
	for (i = 0; i < strlen(pattern); ++i) {
		printf("next[%d]: %d\n", i, next[i]);

		printf("%d ~ %d: ", 0, next[i]-1);
		for (j = 0; j < next[i]; ++j) {
			printf("%c ", pattern[j]);	
		}
		printf("\n");

		printf("%d ~ %d: ", i-next[i], i-1);
		for (j = i - next[i]; j < i; ++j) {
			printf("%c ", pattern[j]);	
		}
		printf("\n");
	}
#endif
	return 0;
}
