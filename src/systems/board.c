#include "board.h"

static void handle_move(struct board *b, struct entity e,
                        struct board_situation *s, struct picked_action *pa)
{
    // Update facing regardless of the move success.
    s->facing = pa->action.value.payload.direction;

    struct board_vec new_point = board_vec_add(
        s->point, board_vec_from_direction(pa->action.value.payload.direction));

    if (!board_occupy(b, new_point, e))
    {
        struct event event = {
            .subject = (struct event_actor){.entity = e},
            .kind = EVENT_BUMPS,
            .payload.direction = {.direction =
                                      pa->action.value.payload.direction,
                                  .origin = s->point}};
        BROADCAST_EVENT(b, event, s->point, new_point);
        return;
    }

    struct event event = {
        .subject = (struct event_actor){.entity = e},
        .kind = EVENT_WALKS,
        .payload.direction = {.direction = pa->action.value.payload.direction,
                              .origin = s->point}};
    BROADCAST_EVENT(b, event, s->point, new_point);

    assert(board_deoccupy(b, s->point));
    s->type = BOARD_SITUATION_OCCUPIER;
    s->point = new_point;
    pa->action.set = false;
}

void board_position_update_system(struct world *w, struct board *b)
{
    ITERW(w, e)
    {
        if (!valid_entity(w, e))
        {
            continue;
        }

        struct board_situation *s = WC(w, e, board_situation);
        if (!(s->type == BOARD_SITUATION_OCCUPIER))
        {
            continue;
        }

        struct picked_action *pa = WC(w, e, picked_action);
        if (pa->action.set && pa->action.value.kind == ACTION_MOVE)
        {
            handle_move(b, e, s, pa);
        }

        struct event event = {
            .subject = (struct event_actor){.entity = e},
            .kind = EVENT_EXISTS,
        };
        BROADCAST_EVENT(b, event, s->point);
    }
}
