#pragma once

#include <assert.h>
#include <stdlib.h>

#include "../include/raylib/raylib.h"
#include "../include/raylib/raymath.h"

#include "../assets/textures.h"

#include "../alist.h"
#include "../board.h"
#include "../entity.h"
#include "../flags.h"
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

typedef struct
{
    Camera2D *camera;
    textures *textures;

    ALIST(entity) actors;
    size_t current_actor_idx;
} render_state;

render_state *render_state_allocate(textures *t, Camera2D *c);
void render_state_deallocate(render_state *r);
void render_system(render_state *r, world *w, entity player);
void render_state_reinit(render_state *r, world *w, percepted_events *pe);
