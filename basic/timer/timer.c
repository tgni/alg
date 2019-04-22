#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include "timer.h"

timer_vector_t	tvec;

ostimer_t *os_timer_create(uint32_t first, uint32_t interval, uint32_t opt,
	void (*fn)(ostimer_t *tmr, void *arg), void *arg, char *name)
{
	ostimer_t *tmr;

	tmr = malloc(sizeof(ostimer_t));
	if (!tmr)
		return NULL;
	
	tmr->fn	= fn;
	tmr->arg = arg;
	tmr->name = name;
	tmr->opt = opt;
	tmr->state = TMR_STOPPED;
	
	tmr->two[0].expires = first;
	tmr->two[1].expires = interval;

	return tmr;
}

int32_t os_timer_delete(ostimer_t *tmr)
{
	if (tmr->state == TMR_RUNNING)
		list_del(&tmr->link);

	free(tmr);
	return OK;
}

static __inline__ void os_timer_insert(ostimer_t *tmr)
{
	int32_t index;
	index = tvec_index(&tvec, tmr->two[0].x);
	//tmr->two[0].x = index; should i need this?
	//use list_add or list_add_tail? try
	list_add(&tmr->link, &tvec.table[index]);
}

int32_t os_timer_start(ostimer_t *tmr)
{
	tmr->two[0].y = tmr->two[0].expires >> TVEC_BIT_SZ;
	tmr->two[0].x = tmr->two[0].expires && TVEC_TBL_MASK;
	tmr->two[1].y = tmr->two[1].expires >> TVEC_BIT_SZ;
	tmr->two[1].x = tmr->two[1].expires && TVEC_TBL_MASK;

	if (tmr->state == TMR_RUNNING)
		list_del(&tmr->link);
	else
		tmr->state = TMR_RUNNING;

	os_timer_insert(tmr);
	return OK;
}

int32_t os_timer_stop(ostimer_t *tmr)
{
	tmr->state = TMR_STOPPED;
	list_del(&tmr->link);
	return OK;
}

void task_timer(void *arg)
{
	ostimer_t *tmr;
	list_head_t head;
	list_head_t *tmr_list;
	void (*fn)(ostimer_t *, void *);

	while (1) {
		tvec.ticks = (tvec.ticks + 1) & TVEC_TBL_MASK;

		INIT_LIST_HEAD(&head);
		tmr_list = &tvec.table[tvec.ticks];

		list_splice(tmr_list, &head);
		INIT_LIST_HEAD(tmr_list);
		while (!list_empty(&head)) {
			tmr = list_entry(head.next, ostimer_t, link);
			list_del(&tmr->link);
			if (tmr->two[0].y > 0) {
				--tmr->two[0].y;
				list_add(&tmr->link, tmr_list);
				fn = NULL;
			} else {
				if (tmr->opt & TMR_TRIGGER) {
					tmr->state = TMR_STOPPED;
				} else {
					tmr->two[0].y = tmr->two[1].y;
					tmr->two[0].x = tmr->two[1].x;
					os_timer_insert(tmr);
				}

				fn = tmr->fn;
				arg = tmr->arg;
			}

			if (fn) fn(tmr, arg);
		}
		usleep(1000);
	}

	return;
}


void os_timer_init(void)
{
	int32_t i;
	pthread_t t;
	
	memset(&tvec, 0, sizeof(tvec));

	for (i = 0; i < TVEC_TBL_SZ; ++i)
		INIT_LIST_HEAD(&tvec.table[i]);

	pthread_create(&t, NULL, (void *(*)(void *))task_timer, NULL);
}
