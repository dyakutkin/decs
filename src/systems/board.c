#include "board.h"

static void handle_move(struct board *b, struct offsets_global *og,
                        struct entity e, struct board_situation *s,
                        struct picked_action *pa)
{
    // Update facing regardless of the move success.
    s->facing = pa->action.value.payload.direction;

    struct board_vec new_point = board_vec_add(
        s->point, board_vec_from_direction(pa->action.value.payload.direction));

    if (!board_occupy(b, new_point, e))
    {
        board_broadcast_event(
            b,
            (struct event){
                .turn = og->turn_next,
                .subject = (struct event_actor){.entity = e},
                .kind = EVENT_BUMPS,
                .payload.direction = {.direction =
                                          pa->action.value.payload.direction,
                                      .origin = s->point}},

            (struct board_vec[2]){s->point, new_point}, 2);
        return;
    }

    board_broadcast_event(
        b,
        (struct event){
            .turn = og->turn_next,
            .subject = (struct event_actor){.entity = e},
            .kind = EVENT_WALKS,
            .payload.direction = {.direction =
                                      pa->action.value.payload.direction,
                                  .origin = s->point}},

        (struct board_vec[2]){s->point, new_point}, 2);

    assert(board_deoccupy(b, s->point));
    s->type = BOARD_SITUATION_OCCUPIER;
    s->point = new_point;
    pa->action.set = false;
}

void board_position_update_system(struct world *w, struct board *b,
                                  struct offsets_global *og)
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
            handle_move(b, og, e, s, pa);
        }

        board_broadcast_event(b,
                              (struct event){
                                  .turn = og->turn_next,
                                  .subject = (struct event_actor){.entity = e},
                                  .kind = EVENT_EXISTS,
                              },

                              (struct board_vec[1]){s->point}, 1);
    }
}
