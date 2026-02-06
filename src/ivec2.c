#include "ivec2.h"

bool ivec2_eq(ivec2 p1, ivec2 p2) { return p1.x == p2.x && p1.y == p2.y; }

ivec2 ivec2_from_direction(direction d)
{
    ivec2 result;
    switch (d)
    {
    case DIRECTION_NORTH:
        result = (ivec2){0, -1};
        break;
    case DIRECTION_SOUTH:
        result = (ivec2){0, 1};
        break;
    case DIRECTION_EAST:
        result = (ivec2){1, 0};
        break;
    case DIRECTION_WEST:
        result = (ivec2){-1, 0};
        break;
    }
    return result;
}

ivec2 ivec2_add(ivec2 a, ivec2 b) { return (ivec2){a.x + b.x, a.y + b.y}; }
