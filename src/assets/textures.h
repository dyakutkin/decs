#pragma once

#include "../include/raylib/raylib.h"

typedef struct
{
    Texture2D error;
    Texture2D chars;
    Texture2D terrain;
} Textures;

Textures textures_load();
void textures_unload(Textures *textures);
