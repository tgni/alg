#include <stdio.h>
#include <stdlib.h>

long int Fib( int N )
{
    printf("enter %s \n", __FUNCTION__);
    if( N <= 1)
        return 1;
    else
        return Fib(N - 1) + Fib(N - 2);
}

int main(void)
{
    printf("%ld\r\n", Fib(10));
}

