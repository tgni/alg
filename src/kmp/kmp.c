#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void get_next(char *pattern, int len, int next[])
{
	int j = 0, k = -1;

	next[0] = -1;
	while (j < len - 1) {
		if (k == -1 || pattern[j] == pattern[k]) {
			next[++j] = ++k;
		} else {
			k = next[k];
		}
	}

	return;
}

int get_index(char *s, int len, char *p, int plen)
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
	char *pattern = "abaabcac";
	//char *pattern = "abcac";
	char *s = "ababcabcacbab";
	int pos, poskmp, i, j, *next;

	if (!(next = malloc(strlen(pattern)*sizeof(int)))) {
		printf("failed to malloc\n");
		return -1;
	}

	printf("s: %s, strlen(s): %d\n", s, (int)strlen(s));
	printf("pattern: %s, strlen(pattern): %d\n", pattern, (int)strlen(pattern));
	pos = get_index(s, strlen(s), pattern, strlen(pattern));
	get_next(pattern, strlen(pattern), next);
	poskmp = kmp(s, strlen(s), pattern, strlen(pattern), next);
	printf("pos: %d, poskmp: %d\n", pos, poskmp);

	/*
	printf("pat: %s\n", pat);
	printf("     ");
	for (i = 0; i < strlen(pat); ++i)
		printf("%d", i);
	printf("\n");

	get_next(pat, strlen(pat), next);
	for (i = 0; i < strlen(pat); ++i) {
		printf("next[%d]: %d\n", i, next[i]);

		printf("%d ~ %d: ", 0, next[i]-1);
		for (j = 0; j < next[i]; ++j) {
			printf("%c ", pat[j]);	
		}
		printf("\n");

		printf("%d ~ %d: ", i-next[i], i-1);
		for (j = i - next[i]; j < i; ++j) {
			printf("%c ", pat[j]);	
		}
		printf("\n");
	}
	*/

	return 0;
}
