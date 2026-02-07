#pragma once

#include <stdlib.h>

#include "../include/raylib/raylib.h"
#include "../include/raylib/raymath.h"

#include "../alist.h"

#include "../assets/textures.h"

#include "../board.h"
#include "../entity.h"
#include "../flags.h"
#include "../render_state.h"
#include "../world.h"

typedef enum
{
    DRAW_BACKGROUND_VISIBLE,
    DRAW_BACKGROUND_NON_VISIBLE,
} draw_background_mode;

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

void render_system(render_state *r, world *w);
