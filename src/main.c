#include "assets/textures.h"
#include "board/board.h"
#include "entity/entity.h"
#include "include/raylib.h"
#include "setup/setup.h"
#include "systems/systems.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
  struct Entities *entities = alloc_entities();
  struct Board *board = alloc_board();

  struct EntityID player_id = setup_actors(entities, board);

  InitWindow(1280, 800, "Past Recalling");

  struct Textures textures = load_textures();

  Camera2D camera = {0};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  do {
    if (input_system(entities, player_id)) {
      movement_system(board, entities);
      clear_picked_action_system(entities);
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    render_system(&camera, &textures, board, entities, player_id);
    EndDrawing();
  } while (!WindowShouldClose());

  unload_textures(&textures);

  CloseWindow();

  free(board);
  free(entities);

  return 0;
}
