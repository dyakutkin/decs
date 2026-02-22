#include "textures.hpp"

textures textures::load()
{
    return textures{
        .error = load_asset_as_texture("./assets/error.png"),
        .chars = load_asset_as_texture("./assets/chars.png"),
        .terrain = load_asset_as_texture("./assets/terrain.png"),
    };
}

void textures::unload()
{
    UnloadTexture(this->chars);
    UnloadTexture(this->terrain);
    UnloadTexture(this->error);
}

Texture2D textures::load_asset_as_texture(const char *filename)
{
    Image image = LoadImage(filename);
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    return texture;
}
