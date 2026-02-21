#pragma once

#include <stdarg.h>
#include <stdio.h>

#include "dynarray.h"
#include "entity.h"
#include "events.h"
#include "flags.h"
#include "ivec2.hpp"
#include "option.h"
#include "turn.h"

#define BOARD_SIDE_TILES_AMOUNT 5000
#define BOARD_TILES_AMOUNT (BOARD_SIDE_TILES_AMOUNT * BOARD_SIDE_TILES_AMOUNT)

#define BROADCAST_EVENT(BOARD, TURN, EVENT, ...)                               \
    board_broadcast_event((BOARD), (TURN), (EVENT), __VA_ARGS__,               \
                          ((ivec2){-1, -1}))

typedef struct
{
    OPTION(event) event;
    turn_id turn;
    size_t offset;
    ivec2 origin;
} event_broadcast;

typedef struct {
    DYNARRAY(event_broadcast) broadcasts;
    turn_id turn_id;
} board_tile_broadcasts;

typedef struct
{
    OPTION(entity) occupier;
    DYNARRAY(entity) ground;

    board_tile_broadcasts broadcasts_current;
    board_tile_broadcasts broadcasts_next;
} board_tile;

typedef struct
{
    board_tile tiles[BOARD_TILES_AMOUNT];
    size_t event_offset;
} board;

board *board_allocate();
void board_deallocate(board *b);
bool board_get_tile_raw(board *b, ivec2 p, board_tile **out);
bool board_get_tile(board *b, turn *t, ivec2 p, board_tile **out);
bool board_occupy(board *b, ivec2 p, entity e);
bool board_deoccupy(board *b, ivec2 p);
void board_broadcast_event(board *b, turn *t, event e, ...);
void board_notify_new_turn(board *b);
