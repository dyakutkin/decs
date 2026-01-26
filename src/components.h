#pragma once

#include "actions.h"
#include "alist.h"
#include "board.h"
#include "bvec.h"
#include "direction.h"
#include "option.h"

typedef enum
{
    BOARD_SITUATION_ABSENT,
    BOARD_SITUATION_OCCUPIER,
    BOARD_SITUATION_ITEM,
} board_situation_type;

typedef struct
{
    board_situation_type type;
    board_vec point;
    direction facing;
} board_situation;

typedef enum
{
    ENTITY_FLAG_PLAYER = 1 << 0,
    ENTITY_FLAG_NPC = 1 << 1,
    ENTITY_FLAG_VISION = 1 << 2,
} entity_flag;

typedef struct
{
    entity_flag flags;
} entity_flags;

typedef struct
{
    OPT(action) action;
} picked_action;

typedef struct
{
    ALIST(event_broadcast) broadcasts;
} percepted_events;
