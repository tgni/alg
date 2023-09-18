#include <stdio.h>

unsigned snoob(unsigned x)
{
	unsigned smallest, ripple, ones;

	smallest = x & -x;
	ripple = x + smallest;
	ones = x ^ ripple;
	ones = (ones >> 2) / smallest;
	return ripple | ones;
}

int main()
{
	unsigned x = 0xf0;

	printf("x: %0x snoob(x)= %x\n", x, snoob(x));

	return 0;
}
