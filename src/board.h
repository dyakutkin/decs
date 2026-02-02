#pragma once

#include <stdarg.h>

#include "alist.h"
#include "bvec.h"
#include "entity.h"
#include "events.h"
#include "flags.h"
#include "turn.h"
#include "option.h"

#define BOARD_SIDE_TILES_AMOUNT 5000
#define BOARD_TILES_AMOUNT (BOARD_SIDE_TILES_AMOUNT * BOARD_SIDE_TILES_AMOUNT)

#define BROADCAST_EVENT(BOARD, TURN, EVENT, ...)                               \
    board_broadcast_event((BOARD), (TURN), (EVENT), __VA_ARGS__,               \
                          ((board_vec){-1, -1}))

typedef struct
{
    event event;
    turn_id turn;
    size_t offset;
    board_vec origin;
} event_broadcast;

typedef struct
{
    OPT(entity) occupier;
    ALIST(entity) ground;
    ALIST(event_broadcast) event_broadcasts;
} board_tile;

typedef struct
{
    board_tile tiles[BOARD_TILES_AMOUNT];
    size_t event_offset;
} board;

board *board_allocate();
void board_deallocate(board *b);
bool board_get_tile(board *b, board_vec p, board_tile **out);
bool board_occupy(board *b, board_vec p, entity e);
bool board_deoccupy(board *b, board_vec p);
void board_broadcast_event(board *b, turn *t, event e, ...);
void board_notify_new_turn(board *b);
