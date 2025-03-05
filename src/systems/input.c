#include <raylib.h>

#include "../events.h"

#include "input.h"

bool input_system(AList *events, EntityID player_id)
{
    int x = 0, y = 0;
    bool got_input = false;
    if (IsKeyReleased(KEY_RIGHT))
    {
        x = 1;
        y = 0;
        got_input = true;
    }
    else if (IsKeyReleased(KEY_LEFT))
    {
        x = -1;
        y = 0;
        got_input = true;
    }
    else if (IsKeyReleased(KEY_UP))
    {
        x = 0;
        y = -1;
        got_input = true;
    }
    else if (IsKeyReleased(KEY_DOWN))
    {
        x = 0;
        y = 1;
        got_input = true;
    }

    if (got_input)
    {
        AList__append(events, &(MoveEvent){
                                  .delta = (VecDelta){.x = x, .y = y},
                                  .entity_id = player_id,
                              });
    }

    return got_input;
}
