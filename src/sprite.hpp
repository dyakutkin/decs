#pragma once

#include "./include/raylib/raylib.h"

#include "dynarray.h"

enum sprite_type
{
    SPRITE_UNKNOWN,
    SPRITE_GRASS,
    SPRITE_WALL,
    SPRITE_PLAYER,
    SPRITE_NPC,
};

enum sprite_animation_kind
{
    SPRITE_ANIMATION_MOVE = 1,
};

struct sprite_animation
{
    sprite_animation_kind kind;
    union
    {
        struct
        {
            Vector2 target;
        } move;
    } payload;
};
