#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int len;
char str[10];
char ans[10];
bool mark[10];

void DFS(int num)
{
	if (num == len) {
		ans[num] = '\0';
		printf("%s\n", ans);
		return;
	}

	for (int i = 0; i < len; ++i) {
		if (mark[i] == false) {
			mark[i] = true;
			ans[num] = str[i];
			DFS(num+1);
			mark[i] = false;
		}
	}
}

int main()
{
	while (scanf("%s", str) != EOF) {
		len = strlen(str);
		for (int i = 0; i < len; ++i)
			mark[i] = false;
		sort(str, str+len);
		DFS(0);
		printf("\n");
	}

	return 0;
}
