#ifndef _SCHED_H_
#define _SCHED_H_

typedef struct queue_s {
	uint32_t nr;
	list_head_t hdr;
} queue_t;

#endif /* _SCHED_H_ */
