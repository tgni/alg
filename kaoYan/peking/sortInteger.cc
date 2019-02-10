#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> odd;
	vector<int> even;

	int e;
	while (scanf("%d", &e) != EOF) {
		if (e % 2)
			odd.push_back(e);
		else
			even.push_back(e);

		for (int i = 1; i < 10; ++i) {
			scanf("%d", &e);
			if (e % 2)
				odd.push_back(e);
			else
				even.push_back(e);
		}

		sort(odd.begin(), odd.end());
		sort(even.begin(), even.end());

		for (auto rit = odd.rbegin(); rit != odd.rend(); ++rit)
			printf("%d ", *rit);
		for (auto i : even)
			printf("%d ", i);
		printf("\n");
	}

	return 0;
}
