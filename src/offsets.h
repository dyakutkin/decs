#pragma once

#include <stdlib.h>

typedef size_t turn_id;

typedef struct
{
    turn_id turn_current;
    turn_id turn_next;
    size_t events;
} offsets_global;

offsets_global *offsets_global_allocate();
void offsets_global_inc(offsets_global *t);
