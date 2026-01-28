#include "direction.h"

char *direction_repr(direction d)
{
    char *result;
    switch (d)
    {
    case DIRECTION_NORTH:
        result = "north";
        break;
    case DIRECTION_SOUTH:
        result = "south";
        break;
    case DIRECTION_EAST:
        result = "east";
        break;
    case DIRECTION_WEST:
        result = "west";
        break;
    }
    return result;
}
