#pragma once

#include "../include/raylib.h"

struct Textures {
  Texture2D error;
  Texture2D chars;
  Texture2D terrain;
};

struct Textures load_textures();
void unload_textures(struct Textures *textures);
