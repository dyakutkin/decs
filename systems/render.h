#include <assert.h>
#include <raylib.h>

#include "../collections/genarena.h"

#include "../asset_manager/textures.h"
#include "../board.h"
#include "../components.h"
#include "../entity.h"
#include "../entity_id.h"

#define TILE_TEXTURE_SIZE 128

#define PLAYER_RENDER_RADIUS 5
#define PLAYER_RENDER_SQUARE_SIDE (PLAYER_RENDER_RADIUS * 2 + 1)

typedef enum {
  UNKNOWN,
  GRASS,
  WALL,
  PLAYER,
} TileType;

void render_system(Textures *textures, Board *board, GenArena *entities, EntityID player_id);
static float map_tile_size();
