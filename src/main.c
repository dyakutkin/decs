#include <assert.h>

#include "actions.h"
#include "direction.h"
#include "include/raylib/raylib.h"

#include "board.h"
#include "entity.h"
#include "offsets.h"
#include "option.h"
#include "systems/board.h"
#include "world.h"

#include "setup.h"

#include "assets/textures.h"

#include "systems/render.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCREEN_TITLE "The Game"

int main(void)
{
    struct offsets_global *og = offsets_global();
    struct board *b = board(og);
    struct world *w = world();

    struct entity player = setup_actors(w, b);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    struct textures t = textures();

    Camera2D camera = {0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    do
    {
        bool got_input = false;
        enum direction direction;

        if (IsKeyReleased(KEY_RIGHT))
        {
            direction = DIRECTION_EAST;
            got_input = true;
        }
        else if (IsKeyReleased(KEY_LEFT))
        {
            direction = DIRECTION_WEST;
            got_input = true;
        }
        else if (IsKeyReleased(KEY_UP))
        {
            direction = DIRECTION_NORTH;
            got_input = true;
        }
        else if (IsKeyReleased(KEY_DOWN))
        {
            direction = DIRECTION_SOUTH;
            got_input = true;
        }

        if (got_input)
        {
            OPTSET(WC(w, player, picked_action)->action,
                   ((struct action){.kind = ACTION_MOVE,
                                    .payload.direction = direction}))
        }
        board_position_update_system(w, b, og);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        render_system(&camera, &t, b, w, player);
        EndDrawing();
    } while (!WindowShouldClose());

    textures_unload(&t);

    CloseWindow();

    return 0;
}
