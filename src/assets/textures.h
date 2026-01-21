#pragma once

#include "../include/raylib/raylib.h"

struct textures
{
    Texture2D error;
    Texture2D chars;
    Texture2D terrain;
};

struct textures textures();
void textures_unload(struct textures *t);
