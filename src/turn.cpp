#include "turn.hpp"

turn *turn::allocate()
{
    turn *t = (turn *)malloc(sizeof(turn));
    t->current = 0;
    t->next = 1;
    return t;
}

void turn::increment()
{
    this->current = this->next;
    this->next++;
}
