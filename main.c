#include "assert.h"
#include "stdint.h"

#include <raylib.h>

#include "genarena.h"

#include "board.h"
#include "components.h"
#include "entity.h"

#include "./setup/actors.h"

#define MAX_ENTITIES_AMOUNT 1000000

bool arch_person_fn(Entity *entity) {
  return BaseComponent__is_set((void *)&entity->PersonComponent);
}

int main(void) {
  GenArena arena = GenArena__alloc(sizeof(Entity), MAX_ENTITIES_AMOUNT);
  Board board = Board__alloc();

  setup_actors(&board, &arena);

  Board__free(&board);
  GenArena__free(&arena);

  const int screenWidth = 1920;
  const int screenHeight = 1080;

  InitWindow(screenWidth, screenHeight, "Past Recalling");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20,
             LIGHTGRAY);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
