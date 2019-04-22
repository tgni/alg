#include <stdio.h>
#include <string.h>

#define  maxDigits	(10)
struct bigInteger {
	int digit[10];
	int size;

	void init() {
		for (int i = 0; i < maxDigits; ++i)
			digit[i] = 0;
		size = 0;
	}

	void set(char str[]) {
		init();
		int L = strlen(str);

		/* j control each four char to save as one digit,
		 * t refer to one digit temporary, while c as weight,
		 */
		for (int i = L-1, j=0, t=0, c=1; i >= 0; i--) {
			t += (str[i]-'0')*c;
			j++;
			c *= 10;
			/* i == 0 for ending, if rest of str is less than four */
			if (j == 4 || i == 0) {
				digit[size++] = t;
				j = 0;
				t = 0;
				c = 1;
			}
		}
	}

	int operator % (int x) const {
		int remainder = 0;
		for (int i = size-1; i >= 0; --i) {
			remainder = (remainder*10000+digit[i]) % x;
		}

		return remainder;
	}
};


int main()
{
	bigInteger a;
	char str[40];	

	while (scanf("%s", str) != EOF) {
		if (strlen(str) == 2 && str[0] == '-' && str[1] =='1')
			continue;

		a.set(str);

		int found = 0;
		for (int i = 2; i <= 9; ++i) {
			if (a % i == 0) {
				printf("%s%d", found ? " " : "", i);
				found = 1;
			}
		}
		printf("%s", found ? "\n" : "none\n");
	}

	return 0;
}
