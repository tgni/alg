#include <iostream>
#include <cctype>

using namespace std;

struct bigInteger {
#define maxDigits	(1000)
	int digit[maxDigits];
	int size;
	int sign;

	bigInteger() {
		fill(digit, digit + maxDigits, 0);
		size = 0;
		sign = 1;
	}

	bigInteger(string s) {
		fill(digit, digit + maxDigits, 0);
		size = 0; sign = 1;
		for (int i = s.size()-1; i >= 0; --i) {
			if (isdigit(s[i]))
				digit[size++] = s[i] - '0';
			else
				sign = -1;
		}
	}

	void output(void) {
		if (sign > 0)
			cout << '-';
		for (int i = size-1; i >= 0; --i)
			cout << digit[i];
		cout << endl;
	}

	bigInteger operator + (const bigInteger &A) const {
		bigInteger ret;

		if (sign > A.sign) {
			ret = *this - A;
			return ret;
		} else if (sign < A.sign) {
			ret = A - *this;
			return ret;
		}

		int carry = 0;
		for (int i = 0; i < A.size || i < size; ++i) {
			int tmp = A.digit[i] + digit[i] + carry;
			carry = tmp / 10;
			tmp %= 10;
			ret.digit[ret.size++] = tmp;
		}
		if (carry != 0)
			ret.digit[ret.size++] = carry;
		return ret;
	}

	bigInteger operator - (const bigInteger &A) const {
	}
};

int main(void)
{
	string s1, s2;

	while (cin >> s1 >> s2) {
		bigInteger a(s1), b(s2);
		bigInteger c;
		c = a + b;
		c.output();
		c = a - b;
		c.output();
		//c = a * b;
		//c.output();
	}

	return 0;
}
