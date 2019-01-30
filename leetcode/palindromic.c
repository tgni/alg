#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if 1
/* brute-force */
char* longestPalindrome(char* s) {
        int len = strlen(s);
        int i, j, k, max_len, _len, pos;
        char *r;
        
        max_len = 0;
        for (i = 0; i < len; ++i) {
                for (j = i; j < len; ++j) {
                        for (k = 0; k <= (j-i+1)/2; ++k) {
                               if (s[i+k] != s[j-k]) {
                                       break;
                               }
                        }
                        if (k > (j-i+1)/2) {
                                _len = j-i+1;
                                if (_len > max_len) {
                                        max_len = _len;
                                        pos = i;
                                }
                        }
                }
        }
        
        if (max_len == 0)
                return "";
        
        r = (char *)malloc(max_len+1);
        strncpy(r, s+pos, max_len);
        r[max_len] = '\0';
        
        return r;
}
#endif

#if 0
/* expanding center */
char* longestPalindrome(char* s) {
        int len = strlen(s);
        int max_len, pos, i, left, right;
        char *r;
        
	max_len = 0;
        for (i = 0; i < len; ++i) {
		left = i; right = i;

		//expand same char in the center
		for (; s[right+1] == s[left]; right++, i++)
			;

                for (; left-1 >= 0 && right+1 < len; left--, right++) {
                        if (s[left-1] != s[right+1])
                                break;
                }

		if (right-left+1 > max_len) {
			max_len = right-left+1; 
			pos = left;
		}
	}
        
        if (max_len == 0)
                return "";
        
        r = (char *)malloc(max_len+1);
        strncpy(r, s+pos, sub_len);
        r[max_len] = '\0';
        
        return r;
} 
#endif

int main(void)
{
	char *s, *r;

	while (scanf("%s", s) != EOF) {
		r = longestPalindrome(s);
		printf("origin: %s\n", s);
		printf("sub: %s\n", r);
		if (r) free(r);
	}

	return 0;
}
