#include "ivec2.hpp"

bool ivec2::eq(ivec2 p2) { return (*this).x == p2.x && (*this).y == p2.y; }

ivec2 ivec2::from_direction(direction d)
{
    ivec2 result;
    switch (d)
    {
    case DIRECTION_NORTH:
        result = {0, -1};
        break;
    case DIRECTION_SOUTH:
        result = {0, 1};
        break;
    case DIRECTION_EAST:
        result = {1, 0};
        break;
    case DIRECTION_WEST:
        result = {-1, 0};
        break;
    }
    return result;
}

ivec2 ivec2::add(ivec2 b) { return {(*this).x + b.x, (*this).y + b.y}; }
