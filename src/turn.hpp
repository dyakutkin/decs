#pragma once

#include <stdlib.h>

typedef size_t turn_id;

struct turn
{
    turn_id current;
    turn_id next;

    static turn *allocate();
    void increment();
};
