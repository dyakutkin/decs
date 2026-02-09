#include "direction.h"

char *direction_repr(direction d)
{
    switch (d)
    {
    case DIRECTION_NORTH:
        return "north";
    case DIRECTION_SOUTH:
        return "south";
    case DIRECTION_EAST:
        return "east";
    case DIRECTION_WEST:
        return "west";
    }
    PANIC("Invalid direction\n");
}
