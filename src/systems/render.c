#include "render.h"

#define TILE_TEXTURE_SIZE 128

#define PLAYER_RENDER_RADIUS 5
#define PLAYER_RENDER_SQUARE_SIDE (PLAYER_RENDER_RADIUS * 2 + 1)

void render_system(Camera2D *camera, struct Textures *textures,
                   struct Board *board, struct Entities *entities,
                   struct EntityID player_id) {
  SET_CURRENT_ENTITY(player_id);

  if (!MATCH_ENTITY(ENTITY_FLAG_PLAYER | ENTITY_FLAG_POSITION)) {
    return;
  }

  struct Vector left_upper = {
      .x = COMPONENT(position).x - PLAYER_RENDER_RADIUS,
      .y = COMPONENT(position).y - PLAYER_RENDER_RADIUS,
  };

  float texture_size_px = map_tile_size();

  camera->target =
      (Vector2){left_upper.x * texture_size_px, left_upper.y * texture_size_px};

  BeginMode2D(*camera);

  int top_x = left_upper.x + PLAYER_RENDER_SQUARE_SIDE;
  int top_y = left_upper.y + PLAYER_RENDER_SQUARE_SIDE;

  struct BoardTileStatus tile_status = {0};

  for (int x = left_upper.x; x < top_x; x++) {
    for (int y = left_upper.y; y < top_y; y++) {
      enum TileType tile_type;

      board_tile_occupied(board, (struct Vector){.x = x, .y = y}, &tile_status);

      if (tile_status.occupied &&
          entity_exists(entities, tile_status.occupied_by)) {
        size_t entity_idx = tile_status.occupied_by.idx;

        if (MATCH_ENTITY(ENTITY_FLAG_PLAYER)) {
          tile_type = PLAYER;
        } else if (MATCH_ENTITY(ENTITY_FLAG_NPC)) {
          tile_type = NPC;
        } else {
          tile_type = UNKNOWN;
        }
      } else if (x < 0 || y < 0) {
        tile_type = WALL;
      } else {
        tile_type = GRASS;
      }

      struct TextureDesc desc = resolve_texture_desc(textures, tile_type);

      draw_tile(textures, desc, (struct Vector){.x = x, .y = y},
                texture_size_px);
    }
  }

  EndMode2D();
}

static void draw_tile(struct Textures *textures,
                      struct TextureDesc texture_desc,
                      struct Vector board_position, float texture_size_px) {
  DrawTexturePro(*texture_desc.texture,
                 (Rectangle){
                     .x = texture_desc.x * TILE_TEXTURE_SIZE,
                     .y = texture_desc.y * TILE_TEXTURE_SIZE,
                     .width = TILE_TEXTURE_SIZE,
                     .height = TILE_TEXTURE_SIZE,
                 },
                 (Rectangle){
                     .x = board_position.x * texture_size_px,
                     .y = board_position.y * texture_size_px,
                     .width = texture_size_px,
                     .height = texture_size_px,
                 },
                 (Vector2){.x = 0, .y = 0}, 0, LIGHTGRAY);
}

static struct TextureDesc resolve_texture_desc(struct Textures *textures,
                                               enum TileType tile_type) {
  switch (tile_type) {
  case PLAYER:
    return (struct TextureDesc){.texture = &textures->chars, .x = 0, .y = 0};
  case NPC:
    return (struct TextureDesc){.texture = &textures->chars, .x = 0, .y = 1};
  case GRASS:
    return (struct TextureDesc){.texture = &textures->terrain, .x = 0, .y = 0};
  case WALL:
    return (struct TextureDesc){.texture = &textures->terrain, .x = 0, .y = 1};
  case UNKNOWN:
  default:
    return (struct TextureDesc){.texture = &textures->error, .x = 0, .y = 0};
  }
}

static float map_tile_size() {
  return (float)GetScreenHeight() / PLAYER_RENDER_SQUARE_SIDE;
}