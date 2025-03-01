#include <assert.h>
#include <raylib.h>

#include "../collections/genarena.h"

#include "../board.h"
#include "../components.h"
#include "../entity.h"
#include "../entity_id.h"

#define PLAYER_RENDER_RADIUS 5
#define PLAYER_RENDER_SQUARE_SIDE (PLAYER_RENDER_RADIUS * 2 + 1)

typedef enum {
  GRASS,
  PLAYER,
} TileType;

void render_system(Board *board, GenArena *entities, EntityID player_id);
static float map_tile_size();
