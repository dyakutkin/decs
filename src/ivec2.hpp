#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "direction.h"

struct ivec2
{
    int32_t x, y;

    bool eq(ivec2 p2);
    ivec2 add(ivec2 b);
    static ivec2 from_direction(direction d);
};
