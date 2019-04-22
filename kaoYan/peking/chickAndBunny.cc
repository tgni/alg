#include <iostream>

using namespace std;

int main()
{
	int n;

	while (cin >> n) {
		int min, max;
		max = (n % 2) ? 0 : n / 2;
		min = n / 4;
		n = n % 4;
		min += n / 2;
		n = n % 2;
		min = (n == 0) ? min : 0;
		cout << min << " " << max << endl;
	}

	return 0;
}
