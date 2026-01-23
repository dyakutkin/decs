#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "alist.h"
#include "direction.h"
#include "entity.h"
#include "events.h"
#include "flags.h"
#include "option.h"
#include "turn.h"

#define BOARD_SIDE_TILES_AMOUNT 5000
#define BOARD_TILES_AMOUNT (BOARD_SIDE_TILES_AMOUNT * BOARD_SIDE_TILES_AMOUNT)

struct board_vec
{
    int32_t x, y;
};

bool board_vec_eq(struct board_vec p1, struct board_vec p2);
struct board_vec board_vec_add(struct board_vec a, struct board_vec b);
struct board_vec board_vec_from_direction(enum direction d);

struct event_broadcast
{
    struct event event;
    size_t offset;
};

struct board_tile
{
    OPT(struct entity) occupier;
    ALIST(struct entity) ground;
    ALIST(struct event_broadcast) event_broadcasts;
};

struct board
{
    struct board_tile tiles[BOARD_TILES_AMOUNT];
    struct offsets_global *og;
};

struct board *board(struct offsets_global *og);
bool board_get_tile(struct board *b, struct board_vec p,
                    struct board_tile **out);
bool board_occupy(struct board *b, struct board_vec p, struct entity e);
bool board_deoccupy(struct board *b, struct board_vec p);
void board_broadcast_event(struct board *b, struct event e,
                           struct board_vec *points, size_t points_len);
