#include "offsets.h"

offsets_global *offsets_global_allocate()
{
    offsets_global *t = malloc(sizeof(offsets_global));
    t->turn_current = 0;
    t->turn_next = 1;
    t->events = 0;
    return t;
}

void offsets_global_increment(offsets_global *t)
{
    t->turn_current = t->turn_next;
    t->turn_next++;
    t->events = 0;
}
