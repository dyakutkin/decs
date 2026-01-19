#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "entity.h"
#include "events.h"

#include "alist.h"
#include "option.h"

#define BOARD_SIDE_TILES_AMOUNT 5000
#define BOARD_TILES_AMOUNT (BOARD_SIDE_TILES_AMOUNT * BOARD_SIDE_TILES_AMOUNT)

typedef struct
{
    int32_t x, y;
} BoardPoint;

typedef struct
{
    OPT(Entity) occupier;
    ALIST(Entity) ground;
    ALIST(Event) events;
} BoardTile;

typedef struct
{
    BoardTile tiles[BOARD_TILES_AMOUNT];
} Board;

Board *board_alloc();
bool board_point_eq(BoardPoint p1, BoardPoint p2);
bool get_board_tile(Board *b, BoardPoint p, BoardTile **out);
bool attempt_occupy(Board *b, BoardPoint p, Entity e);
bool attempt_deoccupy(Board *b, BoardPoint p);
