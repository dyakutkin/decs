#include <assert.h>
#include <stdint.h>

#include <raylib.h>

#include "collections/alist.h"
#include "collections/genarena.h"

#include "globals/entity.h"
#include "board.h"
#include "entity.h"
#include "entity_id.h"
#include "events.h"
#include "asset_manager/textures.h"

#include "setup/actors.h"

#include "systems/input.h"
#include "systems/movement.h"

int main(void) {
  GenArena entities = GenArena__alloc(sizeof(Entity), MAX_ENTITIES_AMOUNT);
  Board board = Board__alloc();
  AList move_events = AList__alloc(5, sizeof(MoveEvent));

  EntityID player_id = setup_actors(&board, &entities);

  const int screenWidth = 1920;
  const int screenHeight = 1080;

  InitWindow(screenWidth, screenHeight, "Past Recalling");

  Textures textures = Textures__load();

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    bool got_input = input_system(&move_events, player_id);

    if (got_input) {
      movement_system(&board, &entities, move_events);
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    // DrawTextureRec(texture_chars,
    //                (Rectangle){.x = 0, .y = 0, .width = 128, .height = 128},
    //                (Vector2){.x = 0, .y = 0}, LIGHTGRAY);

    DrawText("foobar", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
  }

  CloseWindow();

  Textures__unload(&textures);

  AList__free(&move_events);
  Board__free(&board);
  GenArena__free(&entities);

  return 0;
}
