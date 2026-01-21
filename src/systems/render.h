#pragma once

#include <stdlib.h>

#include "../assets/textures.h"
#include "../board.h"
#include "../entity.h"
#include "../flags.h"
#include "../include/raylib/raylib.h"
#include "../world.h"

enum tile_type
{
    TILE_TYPE_UNKNOWN,
    TILE_TYPE_GRASS,
    TILE_TYPE_WALL,
    TILE_TYPE_PLAYER,
    TILE_TYPE_NPC,
};

struct texture_desc
{
    size_t x;
    size_t y;
    Texture2D *texture;
};
void render_system(Camera2D *camera, struct textures *t, struct board *b,
                   struct world *w, struct entity player);
