#include <assert.h>

#include "direction.h"
#include "include/raylib/raylib.h"

#include "actions.h"
#include "board.h"
#include "entity.h"
#include "option.h"
#include "world.h"

#include "setup.h"

#include "assets/textures.h"

#include "systems/render.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCREEN_TITLE "The Game"

int main(void)
{
    struct action a1 = (struct action){
        .kind = ACTION_MOVE,
        .payload.direction = DIRECTION_EAST,
    };
    struct world *w = world();
    struct board *b = board();

    struct entity player = setup_actors(w, b);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    struct textures t = textures();

    Camera2D camera = {0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    do
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        render_system(&camera, &t, b, w, player);
        EndDrawing();
    } while (!WindowShouldClose());

    textures_unload(&t);

    CloseWindow();

    return 0;
}
