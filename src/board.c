#include "board.h"

Board *board_alloc()
{
    Board *board = calloc(1, sizeof(Board));
    return board;
}

bool board_point_eq(BoardPoint p1, BoardPoint p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

static size_t point_to_idx(BoardPoint p)
{
    return p.y * BOARD_SIDE_TILES_AMOUNT + p.x;
}

static bool is_valid_board_tile(BoardPoint p)
{
    if (p.x < 0 || p.y < 0)
    {
        return false;
    }
    size_t idx = point_to_idx(p);
    return idx < BOARD_TILES_AMOUNT;
}

bool get_board_tile(Board *b, BoardPoint p, BoardTile **out)
{
    if (!is_valid_board_tile(p))
    {
        return false;
    }

    BoardTile *tile = b->tiles + point_to_idx(p);

    *out = tile;
    return true;
}

bool attempt_occupy(Board *b, BoardPoint p, Entity e)
{
    BoardTile *tile;
    if (!get_board_tile(b, p, &tile))
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

bool attempt_deoccupy(Board *b, BoardPoint p)
{
    BoardTile *tile;
    if (!get_board_tile(b, p, &tile))
    {
        return false;
    }

    if (tile->occupier.set)
    {
        OPTUNSET(tile->occupier);
    }

    return true;
}
