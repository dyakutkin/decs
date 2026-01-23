#pragma once

#include "actions.h"
#include "alist.h"
#include "board.h"
#include "bvec.h"
#include "direction.h"
#include "option.h"

enum board_situation_type
{
    BOARD_SITUATION_ABSENT,
    BOARD_SITUATION_OCCUPIER,
    BOARD_SITUATION_ITEM,
};

struct board_situation
{
    enum board_situation_type type;
    struct board_vec point;
    enum direction facing;
};

enum entity_flag
{
    ENTITY_FLAG_PLAYER = 1 << 0,
    ENTITY_FLAG_NPC = 1 << 1,
    ENTITY_FLAG_VISION = 1 << 2,
};

struct entity_flags
{
    enum entity_flag flags;
};

struct picked_action
{
    OPT(struct action) action;
};

struct percepted_events
{
    ALIST(struct event_broadcast) broadcasts;
};
