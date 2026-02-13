#include "board.h"

board *board_allocate()
{
    board *b = calloc(1, sizeof(board));
    return b;
}

void board_deallocate(board *b)
{
    for (size_t i = 0; i < BOARD_TILES_AMOUNT; i++)
    {
        free(b->tiles[i].ground.items);
        free(b->tiles[i].broadcasts_current.broadcasts.items);
        free(b->tiles[i].broadcasts_next.broadcasts.items);
    }
    free(b);
}

static size_t point_to_idx(ivec2 p)
{
    return p.y * BOARD_SIDE_TILES_AMOUNT + p.x;
}

static bool is_valid_board_tile(ivec2 p)
{
    if (p.x < 0 || p.y < 0)
    {
        return false;
    }
    size_t idx = point_to_idx(p);
    return idx < BOARD_TILES_AMOUNT;
}

bool board_get_tile_raw(board *b, ivec2 p, board_tile **out)
{
    if (!is_valid_board_tile(p))
    {
        return false;
    }

    board_tile *tile = b->tiles + point_to_idx(p);

    *out = tile;
    return true;
}

bool board_get_tile(board *b, turn *t, ivec2 p, board_tile **out)
{
    bool ok = board_get_tile_raw(b, p, out);
    if (!ok)
    {
        return false;
    }
    if ((*out)->broadcasts_next.turn_id != t->next)
    {
        board_tile_broadcasts prev = (*out)->broadcasts_current;
        (*out)->broadcasts_current = (*out)->broadcasts_next;

        (*out)->broadcasts_next = prev;
        DYNARRAY_CLEAR((*out)->broadcasts_next.broadcasts);
        (*out)->broadcasts_next.turn_id = t->next;
    }
    return true;
}

bool board_occupy(board *b, ivec2 p, entity e)
{
    board_tile *tile;
    if (!board_get_tile_raw(b, p, &tile))
    {
        return false;
    }

    if (tile->occupier.set)
    {
        return false;
    }

    OPTION_SET_VALUE(tile->occupier, e);
    return true;
}

bool board_deoccupy(board *b, ivec2 p)
{
    board_tile *tile;
    if (!board_get_tile_raw(b, p, &tile))
    {
        return false;
    }

    if (tile->occupier.set)
    {
        OPTION_SET_NULL(tile->occupier);
    }

    return true;
}

void board_broadcast_event(board *b, turn *t, event e, ...)
{
    va_list ap;
    va_start(ap, e);

    for (;;)
    {
        ivec2 p = va_arg(ap, ivec2);
        if (p.x < 0 || p.y < 0)
        {
            break;
        }

        board_tile *tile;
        if (!board_get_tile(b, t, p, &tile))
        {
            continue;
        }

        DYNARRAY_APPEND(tile->broadcasts_next.broadcasts,
                        ((event_broadcast){.event.value = e,
                                           .event.set = true,
                                           .offset = b->event_offset,
                                           .turn = t->next,
                                           .origin = p}));
    }

    b->event_offset++;
    va_end(ap);
}
void board_notify_new_turn(board *b) { b->event_offset = 0; }
