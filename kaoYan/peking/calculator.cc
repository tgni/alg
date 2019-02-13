#include <iostream>

using namespace std;

int factorial(int a)
{
	int ans = 1;
	for (int i = 1; i <= a; ++i)
		ans *= i;
	return ans;
}

int main()
{
	int a , b;
	char op;

	while (cin >> a) {
		getchar();
		cin >> op;
		if (op == '+') {
			cin >> b;
			cout << a + b << endl;
		} else if (op == '-') {
			cin >> b;
			cout << a - b << endl;
		} else if (op == '*') {
			cin >> b;
			cout << a * b << endl;
		} else if (op == '/') {
			cin >> b;
			if (b == 0)
				cout << "error" << endl;
			else
				cout << a / b << endl;
		} else if (op == '!') {
			cout << factorial(a) << endl;
		} else if (op == '%') {
			cin >> b;
			if (b == 0)
				cout << "error" << endl;
			else
				cout << a % b << endl;
		}
	}

	return 0;
}
