/*  Catalan Number
 *  how many binary trees can be created by n nodes?
 *   C(n, 2n)/(n+1)
 */

#include <cstdio>
#include <cstring>

using namespace std;

int BiTreeNum(int n)
{
	int r = 0;

	if (n == 0 || n == 1)
		return 1;

	if (n >= 2) {
		int k;
		for (int k=n-1; k >= 0; k--)
			r +=  BiTreeNum(k) * BiTreeNum(n-k-1);
	}

	return r;
}

int main(void)
{
	printf("Catalan Number: ");
	for (int i = 0; i < 10; ++i)
		printf("%d ", BiTreeNum(i));
	printf("\n");

	return 0;
}


