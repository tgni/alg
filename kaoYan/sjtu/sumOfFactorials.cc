#include <iostream>

using namespace std;

int main()
{
	int n;
	int a[10];

	a[0] = 1;
	for (int i = 1; i < 10; ++i)
		a[i] = a[i-1] * i;

	while (cin >> n) {
		for (int i = 9; i >= 0; --i) {
			if (n >= a[i])
				n -= a[i];
		}
		if (n == 0)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}
