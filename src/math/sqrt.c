#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

float bin_sqrt(float n)
{
	int i;

	for (i = 0; i < n; i++)
}

float newton_sqrt(float n)
{

}

int main(int argc, char *argv[])
{
	double n, s;
	clock_t c;

	n = atof(argv[1]);
	s = sqrt(n);

	printf("n: %f s: %f time: %d\n", 
		n, s, clock());

	return 0;
}
