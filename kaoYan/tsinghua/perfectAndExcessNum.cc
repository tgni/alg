#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> perfect;
	vector<int> excess;

	for (int i = 2; i <= 60; ++i) {
		int sum = 0;
		for (int j = 1; j <= i/2; ++j) {
			if (i % j == 0)
				sum += j;
		}
		if (sum == i)
			perfect.push_back(i);
		else if (sum > i)
			excess.push_back(i);
	}

	cout << "E:"; 
	for (auto d : perfect)
		cout << ' ' << d;
	cout << endl;

	cout << "G:"; 
	for (auto d : excess)
		cout << ' ' << d;
	cout << endl;

	return 0;
}

