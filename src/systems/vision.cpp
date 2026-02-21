#include "vision.h"
#include <stdint.h>

static ivec2 traced_tile(int32_t d, int32_t w, ivec2 facing, ivec2 side,
                         ivec2 position)
{
    ivec2 result = {.x = position.x + facing.x * d + side.x * w,
                    .y = position.y + facing.y * d + side.y * w};
    return result;
}

static bool event_broadcast_is_new(percepted_events *pe, event_broadcast event)
{
    if (!event.event.set)
    {
        return true;
    }
    for (size_t present = 0; present < pe->broadcasts.len; present++)
    {
        if (pe->broadcasts.items[present].offset == event.offset &&
            pe->broadcasts.items[present].turn == event.turn)
        {
            return false;
        }
    }
    return true;
}

static bool read_tile_events(percepted_events *pe, board *b, turn *t, int32_t w,
                             int32_t d, ivec2 facing_vec, ivec2 side,
                             ivec2 position)
{

    board_tile *tile;
    ivec2 tt = traced_tile(d, w, facing_vec, side, position);

    if (!board_get_tile(b, t, tt, &tile))
    {
        return false;
    }

    size_t events_read = 0;

    for (size_t i = 0; i < tile->broadcasts_next.broadcasts.len; i++)
    {
        if (event_broadcast_is_new(pe,
                                   tile->broadcasts_next.broadcasts.items[i]))
        {
            DYNARRAY_APPEND(pe->broadcasts,
                            tile->broadcasts_next.broadcasts.items[i]);
            events_read++;
        }
    }

    if (events_read == 0)
    {
        DYNARRAY_APPEND(pe->broadcasts, ((event_broadcast){.event = {},
                                                           .turn = t->next,
                                                           .origin = tt}));
    }

    return true;
}

static void cast_depth(percepted_events *pe, board *b, turn *t, int32_t w,
                       ivec2 facing_vec, ivec2 side, ivec2 position)
{
    for (size_t d = 0; d < VISION_SQUARE_DEPTH; d++)
    {
        if (!read_tile_events(pe, b, t, w, d, facing_vec, side, position))
        {
            continue;
        }
    }
}

static void cast(percepted_events *pe, board *b, turn *t, ivec2 facing_vec,
                 ivec2 side, ivec2 position, bool positive)
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

    int32_t w = s;
    int32_t end = s * VISION_SQUARE_WIDTH / 2 + s;

    while (end - w)
    {
        if (read_tile_events(pe, b, t, w, 0, facing_vec, side, position))
        {
            cast_depth(pe, b, t, w, facing_vec, side, position);
        }
        w += s;
    }

    for (int32_t w = s; w < (s * VISION_SQUARE_WIDTH / 2 + s); w += s)
    {
        if (!read_tile_events(pe, b, t, w, 0, facing_vec, side, position))
        {
            continue;
        }
        cast_depth(pe, b, t, w, facing_vec, side, position);
    }
}

void percepted_events_update_system(world *w, board *b, turn *t)
{
    ITERW(w, e)
    {
        if (!valid_entity(w, e))
        {
            continue;
        }

        entity_flags *flags = COMPONENT(w, e, entity_flags);
        if (!FCONTAINS(flags->flags, ENTITY_FLAG_VISION))
        {
            continue;
        }

        board_situation *s = COMPONENT(w, e, board_situation);
        if (!(s->type == BOARD_SITUATION_OCCUPIER))
        {
            continue;
        }

        percepted_events *pe = COMPONENT(w, e, percepted_events);
        DYNARRAY_CLEAR(pe->broadcasts);

        ivec2 facing_vec = ivec2_from_direction(s->facing);
        ivec2 side = {.x = -facing_vec.y, .y = facing_vec.x};

        cast_depth(pe, b, t, 0, facing_vec, side, s->point);
        cast(pe, b, t, facing_vec, side, s->point, true);
        cast(pe, b, t, facing_vec, side, s->point, false);
    }
}
