#include "render.h"

void render_system(Board *board, GenArena *entities, EntityID player_id) {
  Entity *player_e = GenArena__get(entities, player_id);

  assert(player_e != NULL);
  assert(BaseComponent__is_set(&player_e->PositionComponent));

  Point left_upper = (Point){
      .x = player_e->PositionComponent.x - PLAYER_RENDER_RADIUS,
      .y = player_e->PositionComponent.y - PLAYER_RENDER_RADIUS,
  };

  float texture_size_px = map_tile_size();
}

static void draw_tile(Point board_position, TileType type, float texture_size_px) {
  
}

static float map_tile_size() {
  return (float)GetScreenHeight() / PLAYER_RENDER_SQUARE_SIDE;
}
