#include "turn.h"

turn *turn_allocate()
{
    turn *t = (turn *)malloc(sizeof(turn));
    t->current = 0;
    t->next = 1;
    return t;
}

void turn_increment(turn *t)
{
    t->current = t->next;
    t->next++;
}
