#pragma once

#include "include/raylib/raylib.h"

#include "dynarray.h"

#include "assets/textures.hpp"

#include "entity.hpp"
#include "ivec2.hpp"
#include "world.h"

#define PLAYER_RENDER_RADIUS 5
#define PLAYER_RENDER_SQUARE_SIDE (PLAYER_RENDER_RADIUS * 2 + 1)

#define BG_RENDER_RADIUS_DELTA 25

struct render_state
{
    float tile_size_px;
    Camera2D *camera;
    ivec2 left_upper;
    textures *textures;

    DYNARRAY(entity) actors;
    size_t current_actor_idx;

    DYNARRAY(ivec2) visible_tiles;

    static render_state *allocate(::textures *t, Camera2D *c);
    void deallocate();
    void reinit(world *w, percepted_events *pe, entity player);
};
