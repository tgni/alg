/* given a, b, ... n, output Sum of these big Integer.
 */

#include <stdio.h>
#include <string.h>


struct bigInteger {
#define maxDigits	(100)
	int digit[maxDigits];
	int size;

	void init(void) {
		for (int i = 0; i < maxDigits; i++)
			digit[i] = 0;
		size = 0;
	}

	void set(int x) {
		init();
		do {
			digit[size++] = x % 10000;
			x /= 10000;
		} while (x != 0);
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

	void output(void) {
		printf("%d", digit[size-1]);
		for (int i = size-2; i >= 0; i--)
			printf("%04d", digit[i]);
		printf("\n");
	}

	bigInteger operator + (const bigInteger &A) const {
		bigInteger ret;
		ret.init();

		int carry = 0;
		for (int i=0; i<A.size || i<size; ++i) {
			int tmp = A.digit[i] + digit[i] + carry;

			carry = tmp / 10000;
			tmp %= 10000;
			ret.digit[ret.size++] = tmp;
		}

		if (carry != 0)
			ret.digit[ret.size++] = carry;

		return ret;
	}
};

bigInteger a, b;
char str[101];

int main(void)
{
	b.set(0);

	while (scanf("%s", str) != EOF) {
		if (str[0] == '0' && strlen(str) == 1) {
			b.output();
			break;
		}
		a.set(str);
		b = b + a;
	}

	return 0;
}
