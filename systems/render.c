
#include "render.h"

void render_system(Textures *textures, Board *board, GenArena *entities,
                   EntityID player_id) {
  Entity *player_e = GenArena__get(entities, player_id);

  assert(player_e != NULL);
  assert(BaseComponent__is_set(&player_e->PositionComponent));

  Point left_upper = (Point){
      .x = player_e->PositionComponent.x - PLAYER_RENDER_RADIUS,
      .y = player_e->PositionComponent.y - PLAYER_RENDER_RADIUS,
  };

  float texture_size_px = map_tile_size();

  for (int x = left_upper.x; x < PLAYER_RENDER_RADIUS; x++) {
      for (int y = left_upper.y; y < PLAYER_RENDER_RADIUS; y++) {
          EntityID *occupier_id;
          TileType tile_type;
          if (Board__get_occupier(board, &(Point){.x = x, .y = y}, occupier_id)) {
              Entity *occupier = (Entity*)GenArena__get(entities, *occupier_id);
              assert(occupier);

              if (BaseComponent__is_set(&occupier->PlayerComponent)) {
                  tile_type = PLAYER;
              }
          } else {
              tile_type = GRASS;
          }
      }
  }
}

static void draw_tile(Textures *textures, Point board_position, TileType type,
                      float texture_size_px) {
  DrawTextureRec(textures->chars,
                 (Rectangle){
                     .x = 0,
                     .y = 0,
                     .width = TILE_TEXTURE_SIZE,
                     .height = TILE_TEXTURE_SIZE,
                 },
                 (Vector2){.x = board_position.x * texture_size_px,
                           .y = board_position.y * texture_size_px},
                 LIGHTGRAY);
}

static float map_tile_size() {
  return (float)GetScreenHeight() / PLAYER_RENDER_SQUARE_SIDE;
}
