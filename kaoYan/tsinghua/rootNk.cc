/* brute force, timeout. */
#include <stdio.h>
#include <string.h>

#define maxDigits	(100)

struct bigInteger {
	int digit[maxDigits];
	int size;

	bigInteger() {
		for (int i = 0; i < maxDigits; ++i)
			digit[i] = 0;
		size = 0;
	}

	bigInteger(int x) {
		for (int i = 0; i < maxDigits; ++i)
			digit[i] = 0;
		size = 0;
		set(x);
	}

	void set(int x) {
		do {
			digit[size++] = x % 10000;
			x /= 10000;
		} while (x != 0);
	}

	void output() {
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
		int carry = 0;

		for (int i = 0; i < size; ++i) {
			int tmp = digit[i]*x + carry;
			carry = tmp / 10000;
			tmp %= 10000;
			ret.digit[ret.size++] = tmp;
		}
		if (carry != 0)
			ret.digit[ret.size++] = carry;

		return ret;
	}

	/*
	bigInteger operator + (const bigInteger &A) const {
		bigInteger ret;
		int carry = 0;

		for (int i = 0; i < A.size || i < size; ++i) {
			int tmp = digit[i] + A.digit[i] + carry;
			carry = tmp / 10000;
			tmp %= 10000;
			ret.digit[ret.size++] = tmp;
		}
		if (carry != 0)
			ret.digit[ret.size++] = carry;

		return ret;
	}
	*/

	bigInteger operator / (int x) const {
		bigInteger ret;
		int remainder = 0;

		for (int i = size-1; i >= 0; --i) {
			ret.digit[i] = (remainder*10000 + digit[i]) / x;
			remainder = (remainder*10000 + digit[i]) % x;
		}

		ret.size = 0;
		for (int i = 0; i < maxDigits; ++i)
			if (ret.digit[i] != 0) ret.size = i;
		ret.size++;

		return ret;
	}

	int operator % (int x) const {
		int remainder = 0;
		for (int i = size-1; i >= 0; --i) {
			remainder = (remainder*10000 + digit[i]) % x;
		}

		return remainder;
	}

	bool operator < (const bigInteger &A) const {
		if (size == A.size) {
			for (int i = size-1; i >= 0; --i) {
				if (digit[i] == A.digit[i])
					continue;
				return digit[i] < A.digit[i];
			}
			return false;
		}

		return size < A.size;
	}
};

bigInteger power(int x, int y)
{
	bigInteger ret = bigInteger(1);

	if (y == 0)
		return ret;

	for (int i = 0; i < y; ++i)
		ret = ret * x;

	return ret;
}

bigInteger N;

int main()
{
	int x, y, k;

	while (scanf("%d%d%d", &x, &y, &k) != EOF) {
		N = power(x, y);
		while (1) {
			if (N < bigInteger(k)) {
				N.output();
				break;
			}

			int N1 = 0;
			do {
				int t = N % k;
				N1 = N1 + t;
				N = N / k;
			} while (N.digit[0] != 0 || N.size != 1);

			N = bigInteger(N1);
		}
	}

	return 0;
}
