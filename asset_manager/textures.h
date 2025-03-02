#include <raylib.h>

typedef struct {
  Texture2D chars;
  Texture2D terrain;
} Textures;

Textures Textures__load();
void Textures__unload(Textures *textures);
