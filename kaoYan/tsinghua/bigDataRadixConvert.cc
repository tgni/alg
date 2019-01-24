#include <stdio.h>
#include <string.h>

#define maxDigits	(1000)

struct bigInteger {
	int digit[maxDigits];
	int size;

	void init(void) {
		for (int i = 0; i < maxDigits; ++i)
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

	void output(void) {
		for (int i = size-1; i >= 0; --i) {
			if (i != size-1)
				printf("%04d", digit[i]);
			else
				printf("%d", digit[i]);
		}
		printf("\n");
	}

	bigInteger operator * (int x) const {
		bigInteger ret;
		if (x == 0) {
			ret.set(0);
			return ret;
		}
		ret.init();
		int carry = 0;
		for (int i=0; i < size; ++i) {
			int tmp = x*digit[i] + carry;
			carry = tmp / 10000;
			tmp %= 10000;
			ret.digit[ret.size++] = tmp;
		}
		if (carry != 0)
			ret.digit[ret.size++] = carry;
		return ret;
	}

	bigInteger operator + (const bigInteger &A) const {
		bigInteger ret;
		ret.init();
		int carry = 0;
		for (int i = 0; i < A.size || i < size; ++i) {
			int tmp = A.digit[i] + digit[i] + carry;
			carry = tmp / 10000;
			tmp %= 10000;
			ret.digit[ret.size++] = tmp;
		}
		if (carry != 0)
			ret.digit[ret.size++] = carry;
		return ret;
	}
	
	bigInteger operator / (int x) const {
		bigInteger ret;
		ret.init();
		int remainder = 0;
		for (int i = size-1; i >= 0; --i) {
			ret.digit[i] = (remainder*10000 + digit[i]) / x; /* higher digit remainder plus current digit divides x */
			remainder = (remainder*10000 + digit[i]) % x;

			if (ret.digit[i] != 0 && ret.size == 0)
				ret.size = i;
		}
		ret.size++;

		return ret;
	}

	int operator % (int x) const {
		int remainder = 0;
		for (int i = size-1; i >= 0; --i) {
			remainder = (remainder*10000+digit[i]) % x;
		}

		return remainder;
	}
};

bigInteger a, b;

char str[1001];
char bin[10001];

int main(void)
{
	while (scanf("%s", str) != EOF) {
		int L = strlen(str);
		a.set(0);
		b.set(1);

		for (int i = L-1; i >= 0; i--) {
			int t = str[i] - '0';
			a = a + b*t;
			b = b * 10;
		}

		int size = 0;
		do {
			int t = a % 2;
			a = a / 2;
			bin[size++] = t + '0';
		} while (a.digit[0] != 0 || a.size != 1);

		a.set(0);
		b.set(1);
		for (int i = size-1; i >= 0; --i) {
			int t = bin[i] - '0';
			a = a + b*t;
			b = b * 2;
		}
		a.output();
	}

	return 0;
}
