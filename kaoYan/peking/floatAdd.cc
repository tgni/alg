#include <iostream>

using namespace std;

int main()
{
	string a, b;
	while (cin >> a >> b) {
		int ia, fa, ib, fb;	
		string a1, b1;

		ia = a.find('.');
		fa = a.size()-ia-1;
		ib = b.find('.');
		fb = b.size()-ib-1;

		for (int i = 0; i < ia-ib; ++i)
			b1 += '0';
		for (int i = 0; i < ib-ia; ++i)
			a1 += '0';
		a1 += a;
		b1 += b;
		for (int i = 0; i < fa-fb; ++i)
			b1 += '0';
		for (int i = 0; i < fb-fa; ++i)
				a1 += '0';

		int carry = 0;
		for (int i = a1.size()-1; i >= 0; --i) {
			if (a1[i] == '.')
				continue;
			int sum = carry + a1[i]-'0' + b1[i]-'0';
			a1[i] = sum % 10 + '0';
			carry = sum / 10;
		}

		if (carry == 1) {
			string ans = '1' + a1;
			cout << ans << endl;
		} else {
			cout << a1 << endl;
		}
	}

	return 0;
}
