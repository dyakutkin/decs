#include "textures.h"

static Texture2D load_asset_as_texture(char *filename) {
  Image image = LoadImage(filename);
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image);
  return texture;
}

struct Textures load_textures() {
  return (struct Textures){
      .chars = load_asset_as_texture("./assets/chars.png"),
      .terrain = load_asset_as_texture("./assets/terrain.png"),
      .error = load_asset_as_texture("./assets/error.png"),
  };
}

void unload_textures(struct Textures *textures) {
  UnloadTexture(textures->chars);
  UnloadTexture(textures->terrain);
  UnloadTexture(textures->error);
}
