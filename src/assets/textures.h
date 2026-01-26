#pragma once

#include "../include/raylib/raylib.h"

typedef struct
{
    Texture2D error;
    Texture2D chars;
    Texture2D terrain;
} textures;

textures textures_allocate();
void textures_unload(textures *t);
