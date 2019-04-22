#include <stdio.h>

int lengthOfLongestSubstring(char *s)
{
	int cnt, maxcnt;
	char *p, *q, *r;

	p = q = s;
	cnt = maxcnt = 0;
	while (*q != '\0') {
		r = p;
		while (r != q) {
			if (*r == *q) {
				cnt = 0;	
				p = r+1;
				break;
			} else {
				cnt++;
				r++;
			}
		}
		q++;

		if (cnt > maxcnt) {
			maxcnt = cnt;
		}
	}

	return maxcnt;
}

int main(void)
{
	char *s = "abcabcab";
	int l;
	
	printf("%s\n", s);
	l = lengthOfLongestSubstring(s);
	printf("max sub string length: %d\n", l);
	
	return 0;
}
