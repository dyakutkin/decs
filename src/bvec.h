#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "direction.h"

struct board_vec
{
    int32_t x, y;
};

bool board_vec_eq(struct board_vec p1, struct board_vec p2);
struct board_vec board_vec_add(struct board_vec a, struct board_vec b);
struct board_vec board_vec_from_direction(enum direction d);
