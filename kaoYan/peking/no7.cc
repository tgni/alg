#include <cstdio>
#include <cmath>
#include <string>

using namespace std;

int main()
{
	int n;

	while (scanf("%d", &n) != EOF) {
		int sum = 0;
		for (int i = 1; i <= n; ++i) {
			if (i % 7 == 0)
				continue;
			if (to_string(i).find('7') != string::npos)
				continue;
			sum +=  i*i;
		}
		printf("%d\n", sum);
	}

	return 0;
}
