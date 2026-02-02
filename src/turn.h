#pragma once

#include <stdlib.h>

typedef size_t turn_id;

typedef struct
{
    turn_id current;
    turn_id next;
} turn;

turn *turn_allocate();
void turn_increment(turn *t);
