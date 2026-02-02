#pragma once

#include <stdlib.h>

#include "./include/raylib/raylib.h"

#include "alist.h"

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
    MOVE = 1,
} sprite_animation_kind;

typedef struct
{
    sprite_animation_kind kind;
    union
    {
        struct
        {
        } move;
    } payload;
} sprite_animation;
