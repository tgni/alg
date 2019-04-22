#include <stdio.h>
#include <math.h>

using namespace std;

int main(){
	
	long M = 0;

	while (scanf("%ld", &M) != EOF) {
		int count = 0;

		for (long j = 2; j <= sqrt(M); j++) {
			while (M % j == 0) {
				M = M / j;
				count++;
			}
			if (M <= 1)
				break;
		}

		if (M > 1)
			count++;

		printf("%d\n", count);
	}

	return 0;
}
