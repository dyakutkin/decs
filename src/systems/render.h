#include <assert.h>
#include <raylib.h>

#include "../globals/game.h"

#include "../collections/genarena.h"

#include "../assets/textures.h"
#include "../board.h"
#include "../components.h"
#include "../entity.h"
#include "../entity_id.h"

#define TILE_TEXTURE_SIZE 128

#define PLAYER_RENDER_RADIUS 5
#define PLAYER_RENDER_SQUARE_SIDE (PLAYER_RENDER_RADIUS * 2 + 1)

typedef enum
{
    UNKNOWN,
    GRASS,
    WALL,
    PLAYER,
} TileType;

typedef struct
{
    size_t x;
    size_t y;
    Texture2D *texture;
} TextureDesc;

void render_system(Camera2D *camera, Textures *textures, Board *board, GenArena *entities, EntityID player_id);
float map_tile_size();

static void draw_tile(Textures *textures, TextureDesc texture_desc, Point board_position,
                      float texture_size_px);
static TextureDesc resolve_texture_desc(Textures *textures, TileType tile_type);
