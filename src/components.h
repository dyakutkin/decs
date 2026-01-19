#pragma once

#include "board.h"

typedef enum
{
    BOARD_SITUATION_ABSENT,
    BOARD_SITUATION_OCCUPIER,
    BOARD_SITUATION_ITEM,
} BoardSituationType;

typedef struct
{
    BoardSituationType type;
    BoardPoint point;
} BoardSituation;

typedef enum
{
    ENTITY_FLAG_PLAYER = 1 << 0,
    ENTITY_FLAG_NPC = 1 << 1,
} ENTITY_FLAGS;

typedef struct
{
    ENTITY_FLAGS flags;
} EntityFlags;
