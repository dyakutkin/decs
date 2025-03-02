#include "textures.h"
#include <raylib.h>

Textures Textures__load() {
  Image image_chars = LoadImage("assets/chars.png");
  Texture2D texture_chars = LoadTextureFromImage(image_chars);
  UnloadImage(image_chars);

  Image image_terrain = LoadImage("assets/terrain.png");
  Texture2D texture_terrain = LoadTextureFromImage(image_terrain);
  UnloadImage(image_terrain);

  return (Textures){.chars = texture_chars, .terrain = texture_terrain};
}

void Textures__unload(Textures *textures) {
  UnloadTexture(textures->chars);
  UnloadTexture(textures->terrain);
}
