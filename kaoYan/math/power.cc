
#include <stdio.h>

int is_even(long int x)
{
        if (x % 2)
                return 0;
        else 
                return 1;
}
#if 0
long int power(long int x, unsigned int n)
{
        if (n == 0) 
                return 1;
        if (n == 1)
                return x;
        if (is_even(n))
                return power(x * x, n / 2);
        else
                return power(x * x, n / 2) * x;
}
#endif

long int power(long int x, unsigned int n)
{
	long int r = 1;

	if (n == 0)
		return 1;

	while (n != 0) {
		
		if ((n&1) == 1) {	/* n % 2 == 1 */
			r *= x;
		}
		n >>= 1;		/* n /= 2; */
		x *= x;
	}

	return r;
}

int perfect_power_less_hundred(void)
{
        int max = 100;
        unsigned int n;
        long int x;
        long int out;
        printf("perfect power x^n: \n");
        for (n = 2; ; n++) {
                if(power(2, n) > 100)
                        break;
                printf(" n = %d :", n); 
                for (x = 1; ; x++) {
                        out = power(x, n);
                        if (out > 100)
                                break;
                        printf(" %ld", out); 
                }
                printf("\n");
        }
        return 0;
}

int main(void)
{
        perfect_power_less_hundred();
        return 0;
}
