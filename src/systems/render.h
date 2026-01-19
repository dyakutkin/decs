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
    UNKNOWN,
    GRASS,
    WALL,
    PLAYER,
    NPC,
} TileType;

typedef struct
{
    size_t x;
    size_t y;
    Texture2D *texture;
} TextureDesc;
void render_system(Camera2D *camera, Textures *textures, Board *b, World *w,
                   Entity player);
