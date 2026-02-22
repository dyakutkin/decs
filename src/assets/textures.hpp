#pragma once

#include "../include/raylib/raylib.h"

struct textures
{
    Texture2D error;
    Texture2D chars;
    Texture2D terrain;

    static textures load();
    void unload();

  private:
    static Texture2D load_asset_as_texture(const char *filename);
};
