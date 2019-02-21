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
		size = 0;
		sign = 1;
		for (int i = s.size()-1; i >= 0; --i)
			digit[size++] = s[i] - '0';
	}

	void output(void) {
		if (sign < 0)
			cout << '-';
		for (int i = size-1; i >= 0; --i)
			cout << digit[i];
		cout << endl;
	}

	bigInteger operator + (const bigInteger &A) const {
		bigInteger ret;

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
		bigInteger ret;
		int sz;
		if (*this < A) {
			ret.sign = -1;
			sz = A.size;
		} else {
			ret.sign = 1;
			sz = size;
		}

		int carry = 0;
		for (int i = 0; i < sz; ++i) {
			if (ret.sign > 0)
				ret.digit[i] = digit[i] - A.digit[i] - carry;
			else
				ret.digit[i] = A.digit[i] - digit[i] - carry;

			if (ret.digit[i] < 0) {
				carry = 1;
				ret.digit[i] += 10;
			} else {
				carry = 0;
				ret.digit[i] %= 10;
			}
		}

		ret.size = 0;
		for (int i = maxDigits-1; i >= 0; --i) {
			if (ret.digit[i] != 0) {
				ret.size = i+1;
				break;
			}
		}

		return ret;
	}

	/* must be two positive integer */
	bool operator < (const bigInteger &A) const {
		if (size == A.size) {
			int pos = size-1;
			while (digit[pos] == A.digit[pos]) pos--;
			return digit[pos] < A.digit[pos];
		}
		return size < A.size;
	}

	bigInteger operator * (const bigInteger &A) const {
		bigInteger ret;

		for (int i = 0; i < size+1; ++i) {
			int carry = 0;
			for (int j = 0; j < A.size+1; ++j) {
				ret.digit[i+j] = digit[i]*A.digit[j] + ret.digit[i+j] + carry;
				carry = ret.digit[i+j] / 10;
				ret.digit[i+j] = ret.digit[i+j] % 10;
			}
		}

		ret.size = 0;
		for (int i = maxDigits-1; i >= 0; --i) {
			if (ret.digit[i] != 0) {
				ret.size = i+1;
				break;
			}
		}
		return ret;
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
		c = a * b;
		c.output();
	}

	return 0;
}
