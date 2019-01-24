#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>

using namespace std;

struct word {
	int k;
	int idx;
	char c;
};

int k1, k2, k3;
int getk(char c)
{
	if (c >= 'a' && c <= 'i')
		return k1;
	else if (c >= 'j' && c <= 'r')
		return k2;
	else if (c >= 's' && c <= 'z' || c == '_')
		return k3;

	printf("invalid %c\n", c);
	return -1;
}

int main()
{
	while (scanf("%d%d%d", &k1, &k2, &k3) != EOF) {
		if (k1 == 0 && k2 == 0 && k3 == 0)
			break;
		map<int, int> m;
		m[k1] = 0;
		m[k2] = 1;
		m[k3] = 2;

		char str[81];
		scanf("%s", str);

		vector<word> vec[3];
		for (int i = 0; i < strlen(str); ++i) {
			int k = getk(str[i]);
			word w;
			w.k   = k;
			w.idx = i;
			w.c   = str[i];
			vec[m[k]].push_back(w);
		}

		for (int i = 0; i < 3; ++i) {
			int size = vec[i].size();
			for (int j = 0; j < size; ++j) {
				word x = vec[i][j];
				word y = vec[i][(j+x.k)%size];
				str[y.idx] = x.c;
			}
		}

		printf("%s\n", str);
	}

	return 0;
}
