#include "bvec.h"

bool board_vec_eq(struct board_vec p1, struct board_vec p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

struct board_vec board_vec_from_direction(enum direction d)
{
    struct board_vec result;
    switch (d)
    {
    case DIRECTION_NORTH:
        result = (struct board_vec){0, -1};
        break;
    case DIRECTION_SOUTH:
        result = (struct board_vec){0, 1};
        break;
    case DIRECTION_EAST:
        result = (struct board_vec){-1, 0};
        break;
    case DIRECTION_WEST:
        result = (struct board_vec){1, 0};
        break;
    }
    return result;
}

struct board_vec board_vec_add(struct board_vec a, struct board_vec b)
{
    return (struct board_vec){a.x + b.x, a.y + b.y};
}
