/* given N, output N's factorial. N is less than 1000.
 */

#include <stdio.h>

#define maxDigits	(1000)

struct bigInteger {
	int digit[maxDigits];
	int size;

	void init() {
		for (int i = 0; i < maxDigits; ++i)
			digit[i] = 0;
		size = 0;
	}

	void set (int x) {
		init();
		do {
			digit[size++] = x % 10000;
			x /= 10000;
		} while (x != 0);
	}

	void output() {
		for (int i = size-1; i >= 0; --i) {
			if (i == size-1)
				printf("%d", digit[i]);
			else
				printf("%04d", digit[i]);
		}
		printf("\n");
	}

	bigInteger operator * (int x) const {
		bigInteger ret;
		ret.init();
		int carry = 0;

		for (int i = 0; i < size; ++i) {
			int tmp = digit[i] * x + carry; //!!!
			ret.digit[ret.size++] = tmp % 10000;
			carry = tmp / 10000;
		}
		if (carry != 0)
			ret.digit[ret.size++] = carry;

		return ret;
	}
};

bigInteger A;

int main()
{
	int N;
	while (scanf("%d", &N) != EOF) {
		A.init();
		A.set(1);
		for (int i = 1; i <= N; i++) {
			A = A * i;
		}
		A.output();
	}
	return 0;
}
