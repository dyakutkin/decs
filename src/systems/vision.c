#include "vision.h"
#include <stdint.h>

static board_vec traced_tile(int32_t d, int32_t w, board_vec facing,
                             board_vec side, board_vec position)
{
    return (board_vec){.x = position.x + facing.x * d + side.x * w,
                       .y = position.y + facing.y * d + side.y * w};
}

static bool event_broadcast_is_new(percepted_events pe, event_broadcast new)
{
    if (new.event.kind == EVENT_NOTHING)
    {
        return true;
    }
    for (size_t present; present < pe.broadcasts.len; present++)
    {
        if (pe.broadcasts.items[present].offset == new.offset &&
            pe.broadcasts.items[present].turn == new.turn)
        {
            return false;
        }
    }
    return true;
}

static bool read_tile_events(percepted_events pe, board *b, int32_t w,
                             int32_t d, board_vec facing_vec, board_vec side,
                             board_vec position)
{
    board_tile *tile;
    if (!board_get_tile(b, traced_tile(d, w, facing_vec, side, position),
                        &tile))
    {
        return false;
    }

    if (tile->event_broadcasts.len == 0)
    {
        AAPPEND(pe.broadcasts,
                ((event_broadcast){
                    .turn = b->og->turn_next,
                    .event = (event){.kind = EVENT_NOTHING,
                                     .payload.direction.origin = position}}));
    }
    else
    {
        for (size_t i = 0; i < tile->event_broadcasts.len; i++)
        {
            if (event_broadcast_is_new(pe, tile->event_broadcasts.items[i]))
            {
                AAPPEND(pe.broadcasts, tile->event_broadcasts.items[i]);
            }
        }
    }

    return !tile->occupier.set;
}

static void cast_depth(percepted_events pe, board *b, int32_t w,
                       board_vec facing_vec, board_vec side, board_vec position)
{
    for (size_t d = 0; d < VISION_SQUARE_DEPTH; d++)
    {
        if (!read_tile_events(pe, b, w, d, facing_vec, side, position))
        {
            continue;
        }
    }
}

static void cast(percepted_events pe, board *b, board_vec facing_vec,
                 board_vec side, board_vec position, bool positive)
{
    int32_t s;
    if (positive)
    {
        s = 1;
    }
    else
    {
        s = -1;
    }

    for (int32_t w = s; w < s * VISION_SQUARE_WIDTH / 2 + s; w += s)
    {
        if (!read_tile_events(pe, b, w, 0, facing_vec, side, position))
        {
            continue;
        }
        cast_depth(pe, b, w, facing_vec, side, position);
    }
}

void percepted_events_update_system(world *w, board *b)
{
    ITERW(w, e)
    {
        if (!valid_entity(w, e))
        {
            continue;
        }

        entity_flags *flags = WC(w, e, entity_flags);
        if (!FCONTAINS(flags->flags, ENTITY_FLAG_VISION))
        {
            continue;
        }

        board_situation *s = WC(w, e, board_situation);
        if (!(s->type == BOARD_SITUATION_OCCUPIER))
        {
            continue;
        }

        percepted_events *pe = WC(w, e, percepted_events);
        ACLEAR(pe->broadcasts);

        board_vec facing_vec = board_vec_from_direction(s->facing);
        board_vec side = {.x = -facing_vec.y, .y = facing_vec.x};

        cast_depth(*pe, b, 0, facing_vec, side, s->point);
        cast(*pe, b, facing_vec, side, s->point, true);
        cast(*pe, b, facing_vec, side, s->point, false);
    }
}
