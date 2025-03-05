#include "textures.h"

static Texture2D load_asset_as_texture(char *filename)
{
    Image image = LoadImage(filename);
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    return texture;
}

Textures Textures__load()
{
    return (Textures){
        .chars = load_asset_as_texture("chars.png"),
        .terrain = load_asset_as_texture("terrain.png"),
        .error = load_asset_as_texture("error.png"),
    };
}

void Textures__unload(Textures *textures)
{
    UnloadTexture(textures->chars);
    UnloadTexture(textures->terrain);
    UnloadTexture(textures->error);
}
