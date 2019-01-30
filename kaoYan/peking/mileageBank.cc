#include<iostream>
#include<string>

using namespace std;

int main()
{
	string from, to;
	char c;
	int sum = 0, n;

	while (cin >> from && from != "0") {
		cin >> to >> n >> c;
		switch (c) {
		case 'F':
			sum += 2 * n;
			break;
		case 'B':
			sum += (int)(n * 1.5 + 0.5);
			break;
		case 'Y':
			if (n > 500)
				sum += n;
			else
				sum += 500;
			break;
		}
	}
	cout << sum <<endl;

	return 0;
}
