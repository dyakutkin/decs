#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "panic.h"

typedef enum
{
    DIRECTION_NORTH,
    DIRECTION_SOUTH,
    DIRECTION_EAST,
    DIRECTION_WEST
} direction;

char *direction_repr(direction d);
