#pragma once

#include <stdarg.h>

#include "alist.h"
#include "bvec.h"
#include "entity.h"
#include "events.h"
#include "flags.h"
#include "offsets.h"
#include "option.h"

#define BOARD_SIDE_TILES_AMOUNT 5000
#define BOARD_TILES_AMOUNT (BOARD_SIDE_TILES_AMOUNT * BOARD_SIDE_TILES_AMOUNT)

#define BROADCAST_EVENT(BOARD, EVENT, ...)                                     \
    board_broadcast_event((BOARD), (EVENT), __VA_ARGS__,                       \
                          ((struct board_vec){-1, -1}))

struct event_broadcast
{
    struct event event;
    turn_id turn;
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
void board_broadcast_event(struct board *b, struct event e, ...);
