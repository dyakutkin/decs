#pragma once

#include <stdlib.h>

#include "./include/raylib/raylib.h"

#include "dynarray.h"

typedef enum
{
    SPRITE_UNKNOWN,
    SPRITE_GRASS,
    SPRITE_WALL,
    SPRITE_PLAYER,
    SPRITE_NPC,
} sprite_type;

typedef enum
{
    SPRITE_ANIMATION_MOVE = 1,
} sprite_animation_kind;

typedef struct
{
    sprite_animation_kind kind;
    union
    {
        struct
        {
            Vector2 target;
        } move;
    } payload;
} sprite_animation;
