#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "direction.h"

typedef struct
{
    int32_t x, y;
} ivec2;

bool ivec2_eq(ivec2 p1, ivec2 p2);
ivec2 ivec2_add(ivec2 a, ivec2 b);
ivec2 ivec2_from_direction(direction d);
