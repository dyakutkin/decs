#include "npc.h"

void npc_behavior_system(world *w)
{
    ITERW(w, e)
    {
        if (!valid_entity(w, e))
        {
            continue;
        }

        entity_flags *flags = COMPONENT(w, e, entity_flags);
        if (!FCONTAINS(flags->flags, ENTITY_FLAG_NPC))
        {
            continue;
        }

        direction d =
            npc_random_move_directions[rand() %
                                       npc_random_move_directions_amount];

        action action = {.kind = ACTION_MOVE, .payload.direction = d};
        OPTION_SET_VALUE(COMPONENT(w, e, picked_action)->action, action);
    }
}
