#include "bvec.h"

bool board_vec_eq(board_vec p1, board_vec p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

board_vec board_vec_from_direction(direction d)
{
    board_vec result;
    switch (d)
    {
    case DIRECTION_NORTH:
        result = (board_vec){0, -1};
        break;
    case DIRECTION_SOUTH:
        result = (board_vec){0, 1};
        break;
    case DIRECTION_EAST:
        result = (board_vec){1, 0};
        break;
    case DIRECTION_WEST:
        result = (board_vec){-1, 0};
        break;
    }
    return result;
}

board_vec board_vec_add(board_vec a, board_vec b)
{
    return (board_vec){a.x + b.x, a.y + b.y};
}
