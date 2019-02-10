#include <stdio.h>
/*
int main()
{
	int p, e, i, d;
	while (scanf("%d%d%d%d", &p, &e, &i, &d) != EOF) {
		int n = 0;
		while (++n) {
			if ((n-p)%23==0 && (n-e)%28==0 && (n-i)%33==0)
				break;
		}
		printf("Case: the next triple peak occurs in %d days.", n-d);
	}

	return 0;
}
*/

int getTi(int a, int b, int c)
{
	int ti = 0;
	while ((a*b*ti)%c != 1)
		ti++;
	return ti;
}

int main()
{
	int p, e, i, d;
	while (scanf("%d%d%d%d", &p, &e, &i, &d) != EOF) {
		int lcm = 23*28*33;
		int n = (p*23*28*getTi(23,28,33) + e*23*33*getTi(23,33,28) + i*28*33*getTi(28,33,23))%lcm;
		printf("Case: the next triple peak occurs in %d days.", n-d);
	}

	return 0;

}
