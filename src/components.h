#pragma once

#include "board.h"

enum board_situation_type
{
    BOARD_SITUATION_ABSENT,
    BOARD_SITUATION_OCCUPIER,
    BOARD_SITUATION_ITEM,
};

struct board_situation
{
    enum board_situation_type type;
    struct board_point point;
};

enum entity_flag
{
    ENTITY_FLAG_PLAYER = 1 << 0,
    ENTITY_FLAG_NPC = 1 << 1,
};

struct entity_flags
{
    enum entity_flag flags;
};
