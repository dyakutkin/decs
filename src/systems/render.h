#pragma once

#include <stdlib.h>

#include "../assets/textures.h"
#include "../board.h"
#include "../entity.h"
#include "../flags.h"
#include "../include/raylib/raylib.h"
#include "../world.h"

typedef enum
{
    TILE_TYPE_UNKNOWN,
    TILE_TYPE_GRASS,
    TILE_TYPE_WALL,
    TILE_TYPE_PLAYER,
    TILE_TYPE_NPC,
} tile_type;

typedef struct
{
    size_t x;
    size_t y;
    Texture2D *texture;
} texture_desc;

void render_system(Camera2D *camera, textures *t, board *b, world *w,
                   entity player);
