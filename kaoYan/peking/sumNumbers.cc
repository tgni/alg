#include <iostream>

using namespace std;

int main()
{
	int a;
	while (cin >> a) {
		int sum = 0, b;
		for (int i = 0; i < 5; ++i) {
			cin >> b;
			if (b < a)
				sum += b;
		}
		cout << sum << endl;
	}

	return 0;
}
