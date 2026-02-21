#include "board.h"

static void handle_move(board *b, turn *t, entity e, board_situation *s,
                        picked_action *pa)
{
    // Update facing regardless of the move success.
    s->facing = pa->action.value.payload.direction;

    ivec2 new_point = ivec2_add(
        s->point, ivec2_from_direction(pa->action.value.payload.direction));

    if (!board_occupy(b, new_point, e))
    {
        event event = {.subject = {.entity = e},
                       .kind = EVENT_BUMPS,
                       .direction = pa->action.value.payload.direction,
                       .origin = s->point};
        BROADCAST_EVENT(b, t, event, s->point, new_point);
        return;
    }

    event event = {.subject = {.entity = e},
                   .kind = EVENT_WALKS,
                   .direction = pa->action.value.payload.direction,
                   .origin = s->point};
    BROADCAST_EVENT(b, t, event, s->point, new_point);

    if (!board_deoccupy(b, s->point))
    {
        PANIC("Invalid board state\n");
    }
    s->type = BOARD_SITUATION_OCCUPIER;
    s->point = new_point;
}

void board_position_update_system(world *w, board *b, turn *t)
{
    ITERW(w, e)
    {
        if (!valid_entity(w, e))
        {
            continue;
        }

        board_situation *s = COMPONENT(w, e, board_situation);
        if (!(s->type == BOARD_SITUATION_OCCUPIER))
        {
            continue;
        }

        picked_action *pa = COMPONENT(w, e, picked_action);
        if (pa->action.set && pa->action.value.kind == ACTION_MOVE)
        {
            handle_move(b, t, e, s, pa);
            pa->action.set = false;
        }
        else
        {
            event event = {
                .subject = {.entity = e},
                .kind = EVENT_EXISTS,
            };
            BROADCAST_EVENT(b, t, event, s->point);
        }
    }
}
