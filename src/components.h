#pragma once

#include <stdint.h>

#include "actions.h"
#include "board.h"
#include "direction.h"
#include "dynarray.h"
#include "ivec2.hpp"
#include "option.h"
#include "sprite.hpp"

#define ENTITY_NAME_MAX_LENGTH 32

typedef enum
{
    BOARD_SITUATION_ABSENT,
    BOARD_SITUATION_OCCUPIER,
    BOARD_SITUATION_ITEM,
} board_situation_type;

typedef struct
{
    board_situation_type type;
    ivec2 point;
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
    OPTION(action) action;
} picked_action;

typedef struct
{
    DYNARRAY(event_broadcast) broadcasts;
} percepted_events;

typedef struct
{
    char name[ENTITY_NAME_MAX_LENGTH];
} entity_name;

typedef struct
{
    sprite_type type;
    Vector2 position;

    DYNARRAY(sprite_animation) animations;
    size_t current_animation_idx;
} entity_sprite;
