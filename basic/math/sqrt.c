#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* TODO */
#if 0
float newton_sqrt(float n)
{
	return 0;
}
#endif

int main(int argc, char *argv[])
{
	double n, s;

	n = atof(argv[1]);
	s = sqrt(n);

	printf("n: %f s: %f time: %ld\n", n, s, clock());

	return 0;
}
