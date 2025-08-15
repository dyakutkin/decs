#pragma once

#include "../assets/textures.h"
#include "../board/board.h"
#include "../entity/entity.h"
#include "../include/raylib.h"
#include <stdlib.h>

enum TileType {
  UNKNOWN,
  GRASS,
  WALL,
  PLAYER,
  NPC,
};

struct TextureDesc {
  size_t x;
  size_t y;
  Texture2D *texture;
};

static float map_tile_size();
static void draw_tile(struct Textures *textures,
                      struct TextureDesc texture_desc,
                      struct Vector board_position, float texture_size_px);
static struct TextureDesc resolve_texture_desc(struct Textures *textures,
                                               enum TileType tile_type);