#include <stdio.h>
#include <string.h>

#define maxDigits	(10)

struct bigInteger {
	int digit[maxDigits];
	int size;

	bigInteger() {
		for (int i = 0; i < maxDigits; ++i)
			digit[i] = 0;
		size = 0;
	}

	bigInteger &set(int x) {
		for (int i = 0; i < maxDigits; ++i)
			digit[i] = 0;
		size = 0;

		do {
			digit[size++] = x % 10000;
			x /= 10000;
		} while (x != 0);

		return *this;
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

char str[31];
char bin[200];

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

		for (int i = size-1; i >= 0; --i)
			printf("%c", bin[i]);
		printf("\n");
	}

	return 0;
}
