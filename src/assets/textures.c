#include "textures.h"

static Texture2D load_asset_as_texture(char *filename)
{
    Image image = LoadImage(filename);
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    return texture;
}

textures textures_allocate()
{
    return (textures){
        .chars = load_asset_as_texture("./assets/chars.png"),
        .terrain = load_asset_as_texture("./assets/terrain.png"),
        .error = load_asset_as_texture("./assets/error.png"),
    };
}

void textures_unload(textures *t)
{
    UnloadTexture(t->chars);
    UnloadTexture(t->terrain);
    UnloadTexture(t->error);
}
