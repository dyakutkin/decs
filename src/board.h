#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "entity.h"
#include "events.h"

#include "alist.h"
#include "option.h"

#define BOARD_SIDE_TILES_AMOUNT 5000
#define BOARD_TILES_AMOUNT (BOARD_SIDE_TILES_AMOUNT * BOARD_SIDE_TILES_AMOUNT)

struct board_point
{
    int32_t x, y;
};

typedef struct
{
    OPT(struct entity) occupier;
    ALIST(struct entity) ground;
    ALIST(struct event) events;
} BoardTile;

struct board
{
    BoardTile tiles[BOARD_TILES_AMOUNT];
};

struct board *board();
bool board_point_eq(struct board_point p1, struct board_point p2);
bool get_board_tile(struct board *b, struct board_point p, BoardTile **out);
bool attempt_occupy(struct board *b, struct board_point p, struct entity e);
bool attempt_deoccupy(struct board *b, struct board_point p);
