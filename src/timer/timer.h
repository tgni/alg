#ifndef __TIMER_H__
#define __TIMER_H__

#include "types.h"
#include "list.h"

#define TVEC_BIT_SZ		7
#define TVEC_TBL_SZ		(1 << TVEC_BIT_SZ)
#define TVEC_TBL_MASK		(TVEC_TBL_SZ - 1)
#define NR_TIMER_MAX		()

#define TMR_STOPPED		0
#define TMR_RUNNING		1

#define TMR_NULL		0
#define TMR_PERIODIC		(1 << 0)
#define TMR_TRIGGER		(1 << 1)
#define TMR_CALLBACK		(1 << 2)
#define TMR_REALTIME		(1 << 3)

#define TICKS_TMR_PER_SEC	(1000)

typedef struct timer_vector_s {
	uint32_t	ticks;
	list_head_t	table[TVEC_TBL_SZ];
} timer_vector_t;

typedef struct ostimer_s {
	list_head_t	link;
	uint32_t	opt;
	int32_t		state;
	void		(*fn)(struct ostimer_s *, void *);
	void		*arg;
	char		*name;
	struct {
		uint32_t x, y;	
		uint32_t expires;
	} two[2];
} ostimer_t;

#define tvec_index(tv, x)		(((tv)->ticks + (x)) & TVEC_TBL_MASK)

extern ostimer_t *os_timer_create(uint32_t first, uint32_t interval, uint32_t opt,
	void (*fn)(ostimer_t *tmr, void *arg), void *arg, char *name);

extern int32_t os_timer_delete(ostimer_t *tmr);
extern int32_t os_timer_start(ostimer_t *tmr);
extern int32_t os_timer_stop(ostimer_t *tmr);
extern void os_timer_init(void);

#endif /* __TIMER_H__ */
