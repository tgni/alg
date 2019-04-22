#include <stdio.h>

#define MAX_PRIO 64

int calc_time_slice(int prio)
{
	if (prio < MAX_PRIO/2)
		return (MAX_PRIO - prio) << 2;

	return MAX_PRIO - prio;
}

int main(void)
{
        int prio;

        for (prio = 0; prio < 64; ++prio) {
                calc_time_slice(prio);
                printf("prio: %d slice: %d\n", prio, calc_time_slice(prio));
        }
}
