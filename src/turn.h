#pragma once

#include <stdlib.h>

typedef size_t turn_id;

struct offsets_global
{
    turn_id turn_current;
    turn_id turn_next;
    size_t events;
};

struct offsets_global *offsets_global();
void offsets_global_inc(struct offsets_global *t);
