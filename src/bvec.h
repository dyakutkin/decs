#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "direction.h"

typedef struct
{
    int32_t x, y;
} board_vec;

bool board_vec_eq(board_vec p1, board_vec p2);
board_vec board_vec_add(board_vec a, board_vec b);
board_vec board_vec_from_direction(direction d);
