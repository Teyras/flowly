#include <sys/types.h>

#include "flowstat.h"

void 
stat_container_init (stat_container_t * q)
{
	q->next = 0;
	q->full = 0;
}

flowstat_t *
stat_container_next (stat_container_t * q)
{
	if (q->full < STAT_COUNT) {
		++(q->full);
	}
	
	if (q->next == STAT_COUNT) {
		q->next = 1;
		return &(q->items[0]);
	}
	
	return &(q->items[q->next++]);
}

stat_number_t
stat_container_reduce (stat_container_t * q, reduce_keyfnc_t key, reduce_fnc_t fnc)
{
	size_t i = 0;
	stat_number_t result = key(&(q->items[0]));
	
	for (i = 1; i < q->full; ++i) {
		result = fnc(result, key(&(q->items[i])));
	}
	
	return result;
}

void
stat_container_free (stat_container_t * q)
{
	
}