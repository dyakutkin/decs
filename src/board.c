#include <stdarg.h>
#include <stdio.h>

#include "board.h"
#include "offsets.h"

board *board_allocate(offsets_global *og)
{
    board *b = calloc(1, sizeof(board));
    b->og = og;
    return b;
}

void board_deallocate(board *b)
{
    for (size_t i = 0; i < BOARD_TILES_AMOUNT; i++)
    {
        free(b->tiles[i].ground.items);
        free(b->tiles[i].event_broadcasts.items);
    }
    free(b);
}

static size_t point_to_idx(board_vec p)
{
    return p.y * BOARD_SIDE_TILES_AMOUNT + p.x;
}

static bool is_valid_board_tile(board_vec p)
{
    if (p.x < 0 || p.y < 0)
    {
        return false;
    }
    size_t idx = point_to_idx(p);
    return idx < BOARD_TILES_AMOUNT;
}

bool board_get_tile(board *b, board_vec p, board_tile **out)
{
    if (!is_valid_board_tile(p))
    {
        return false;
    }

    board_tile *tile = b->tiles + point_to_idx(p);

    *out = tile;
    return true;
}

bool board_occupy(board *b, board_vec p, entity e)
{
    board_tile *tile;
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

bool board_deoccupy(board *b, board_vec p)
{
    board_tile *tile;
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

void board_broadcast_event(board *b, event e, ...)
{
    va_list ap;
    va_start(ap, e);

    for (;;)
    {
        board_vec p = va_arg(ap, board_vec);
        if (p.x < 0 || p.y < 0)
        {
            break;
        }

        board_tile *tile;
        if (!board_get_tile(b, p, &tile))
        {
            continue;
        }

        // TODO: come up with events cleaning up strategy (e.g. using ring
        // buffer instead of dynamic array for board tiles' event broadcasts).
        AAPPEND(tile->event_broadcasts,
                ((event_broadcast){.event = e,
                                   .offset = b->og->events,
                                   .turn = b->og->turn_next,
                                   .origin = p}));
    }

    b->og->events++;
    va_end(ap);
}
