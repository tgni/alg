#include <stdio.h>
#include <math.h>

int main()
{
	int x0, y0, z0, x1, y1, z1;

	while (scanf("%d%d%d%d%d%d", &x0, &y0, &z0, &x1, &y1, &z1) != EOF) {
		double r = sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0) + (z1-z0)*(z1-z0));
		double v = (4/3.0) * acos(-1) * r * r * r;
		printf("%.3lf %.3lf\n", r, v);
	}

	return 0;
}
