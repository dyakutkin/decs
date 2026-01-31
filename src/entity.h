#pragma once

#include <stdint.h>
#include <stdlib.h>

#define MAX_ENTITIES 10000

typedef struct
{
    size_t idx;
    uint32_t revision;
} entity;
