#include "board.h"
#include "turn.h"

struct board *board(struct offsets_global *og)
{
    struct board *board = calloc(1, sizeof(struct board));
    board->og = og;
    return board;
}

bool board_vec_eq(struct board_vec p1, struct board_vec p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

struct board_vec board_vec_from_direction(enum direction d)
{
    struct board_vec result;
    switch (d)
    {
    case DIRECTION_NORTH:
        result = (struct board_vec){0, -1};
        break;
    case DIRECTION_SOUTH:
        result = (struct board_vec){0, 1};
        break;
    case DIRECTION_EAST:
        result = (struct board_vec){-1, 0};
        break;
    case DIRECTION_WEST:
        result = (struct board_vec){1, 0};
        break;
    }
    return result;
}

struct board_vec board_vec_add(struct board_vec a, struct board_vec b)
{
    return (struct board_vec){a.x + b.x, a.y + b.y};
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

void board_broadcast_event(struct board *b, struct event e,
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
