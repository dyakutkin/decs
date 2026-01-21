#pragma once

#include "stdlib.h"
#include <stdint.h>

#define MAX_ENTITIES 1000

struct entity
{
    size_t idx;
    uint32_t revision;
};
