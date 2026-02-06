#pragma once

#include "include/raylib/raylib.h"

#include "alist.h"

#include "assets/textures.h"

#include "entity.h"
#include "bvec.h"
#include "world.h"

#define PLAYER_RENDER_RADIUS 5
#define PLAYER_RENDER_SQUARE_SIDE (PLAYER_RENDER_RADIUS * 2 + 1)

typedef struct
{
  float tile_size_px;
    Camera2D *camera;
    textures *textures;

    ALIST(entity) actors;
    size_t current_actor_idx;

    ALIST(board_vec) visible_tiles;
} render_state;

render_state *render_state_allocate(textures *t, Camera2D *c);
void render_state_deallocate(render_state *r);
void render_state_reinit(render_state *r, world *w, percepted_events *pe);
