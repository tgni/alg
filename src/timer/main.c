#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

void timeout(ostimer_t *tmr, void *arg)
{
	printf("%s timeout\n", tmr->name);
}

int main(void)
{
	os_timer_init();

	ostimer_t *tmr1 = os_timer_create(TICKS_TMR_PER_SEC,
				TICKS_TMR_PER_SEC,
				TMR_TRIGGER,
				timeout,
				NULL,
				"timer1");
	ostimer_t *tmr2 = os_timer_create(0,
				TICKS_TMR_PER_SEC / 2,
				TMR_PERIODIC,
				timeout,
				NULL,
				"timer2");

	os_timer_start(tmr1);
	sleep(10);
	os_timer_start(tmr2);
	sleep(10);

	os_timer_delete(tmr1);
	os_timer_delete(tmr2);
	exit(0);
}
