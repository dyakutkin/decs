#include <assert.h>

#include "include/raylib/raylib.h"

#include "actions.h"
#include "board.h"
#include "entity.h"
#include "option.h"
#include "world.h"

#include "setup.h"

#include "assets/textures.h"

#include "systems/example.h"
#include "systems/render.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCREEN_TITLE "The Game"

int main(void)
{
    World *w = world_alloc();
    Board *b = board_alloc();

    Entity player = setup_actors(w, b);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    Textures textures = textures_load();

    example_system(w);
    Camera2D camera = {0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    do
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        render_system(&camera, &textures, b, w, player);
        EndDrawing();
    } while (!WindowShouldClose());

    textures_unload(&textures);

    CloseWindow();

    return 0;
}
