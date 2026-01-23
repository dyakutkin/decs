#include "board.h"
#include "offsets.h"
#include <stdarg.h>

struct board *board(struct offsets_global *og)
{
    struct board *board = calloc(1, sizeof(struct board));
    board->og = og;
    return board;
}

static size_t point_to_idx(struct board_vec p)
{
    return p.y * BOARD_SIDE_TILES_AMOUNT + p.x;
}

static bool is_valid_board_tile(struct board_vec p)
{
    if (p.x < 0 || p.y < 0)
    {
        return false;
    }
    size_t idx = point_to_idx(p);
    return idx < BOARD_TILES_AMOUNT;
}

bool board_get_tile(struct board *b, struct board_vec p,
                    struct board_tile **out)
{
    if (!is_valid_board_tile(p))
    {
        return false;
    }

    struct board_tile *tile = b->tiles + point_to_idx(p);

    *out = tile;
    return true;
}

bool board_occupy(struct board *b, struct board_vec p, struct entity e)
{
    struct board_tile *tile;
    if (!board_get_tile(b, p, &tile))
    {
        return false;
    }

    if (tile->occupier.set)
    {
        return false;
    }

    OPTSET(tile->occupier, e);
    return true;
}

bool board_deoccupy(struct board *b, struct board_vec p)
{
    struct board_tile *tile;
    if (!board_get_tile(b, p, &tile))
    {
        return false;
    }

    if (tile->occupier.set)
    {
        OPTUNSET(tile->occupier);
    }

    return true;
}

void _board_broadcast_event(struct board *b, struct event e,
                            struct board_vec *points, size_t points_len)
{
    for (size_t i = 0; i < points_len; i++)
    {
        struct board_tile *tile;
        if (!board_get_tile(b, points[i], &tile))
        {
            continue;
        }

        // TODO: come up with events cleaning up strategy (e.g. using ring
        // buffer instead of dynamic array for board tiles' event broadcasts).
        AAPPEND(
            tile->event_broadcasts,
            ((struct event_broadcast){.event = e, .offset = b->og->events}));
        b->og->events++;
    }
}

void board_broadcast_event(struct board *b, struct event e, ...)
{
    va_list ap;
    va_start(ap, e);

    for (;;)
    {
        struct board_vec p = va_arg(ap, struct board_vec);
        if (p.x < 0 || p.y < 0)
        {
            break;
        }

        struct board_tile *tile;
        if (!board_get_tile(b, p, &tile))
        {
            continue;
        }

        // TODO: come up with events cleaning up strategy (e.g. using ring
        // buffer instead of dynamic array for board tiles' event broadcasts).
        AAPPEND(tile->event_broadcasts,
                ((struct event_broadcast){.event = e,
                                          .offset = b->og->events,
                                          .turn = b->og->turn_next}));
        b->og->events++;
    }

    va_end(ap);
}
