#pragma once

#include <stdlib.h>

#include "../include/raylib/raylib.h"
#include "../include/raylib/raymath.h"

#include "../dynarray.h"

#include "../flags.h"
#include "../render_state.hpp"
#include "../world.h"

enum draw_background_mode
{
    DRAW_BACKGROUND_VISIBLE,
    DRAW_BACKGROUND_NON_VISIBLE,
};

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

void render_system(render_state *r, world *w);
