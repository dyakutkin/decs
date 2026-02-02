#include <assert.h>

#include "actions.h"
#include "direction.h"
#include "include/raylib/raylib.h"

#include "board.h"
#include "entity.h"
#include "log.h"
#include "offsets.h"
#include "option.h"
#include "world.h"

#include "setup.h"

#include "assets/textures.h"

#include "systems/board.h"
#include "systems/render.h"
#include "systems/vision.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCREEN_TITLE "The Game"

void run_turn(world *w, board *b, offsets_global *og, entity player)
{
    board_position_update_system(w, b);
    percepted_events_update_system(w, b);
    print_player_percepted_events_system(player, w, og);

    offsets_global_increment(og);
}

int main(void)
{
    offsets_global *og = offsets_global_allocate();
    board *b = board_allocate(og);
    world *w = world_allocate();

    entity player = setup_actors(w, b);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    textures t = textures_allocate();

    Camera2D camera = {0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Initial run.
    run_turn(w, b, og, player);

    do
    {
        bool got_input = false;
        direction direction;

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
            action action = {.kind = ACTION_MOVE,
                             .payload.direction = direction};
            OPTSET(WC(w, player, picked_action)->action, action);

            run_turn(w, b, og, player);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        render_system(&camera, &t, b, w, player);
        EndDrawing();
    } while (!WindowShouldClose());

    textures_unload(&t);

    world_deallocate(w);
    board_deallocate(b);
    free(og);

    CloseWindow();

    return 0;
}
