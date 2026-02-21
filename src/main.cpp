#include "actions.h"
#include "direction.h"
#include "include/raylib/raylib.h"

#include "board.h"
#include "entity.h"
#include "log.h"
#include "option.h"
#include "turn.hpp"
#include "world.h"

#include "setup.h"

#include "assets/textures.h"

#include "systems/board.hpp"
#include "systems/npc.h"
#include "systems/render.h"
#include "systems/vision.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCREEN_TITLE "The Game"

void run_turn(world *w, board *b, turn *t, entity player, render_state *r)
{
    double stamp = GetTime();

    npc_behavior_system(w);

    board_position_update_system(w, b, t);
    percepted_events_update_system(w, b, t);
    print_player_percepted_events_system(player, w, t);

    t->increment();
    board_notify_new_turn(b);

    stamp = (GetTime() - stamp) * 1000.0;
    printf("Update took %.3f ms\n", stamp);

    render_state_reinit(r, w, COMPONENT(w, player, percepted_events), player);
}

int main(void)
{
    turn *t = turn::allocate();
    board *b = board_allocate();
    world *w = world_allocate();

    entity player = setup_actors(w, b);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    textures txtrs = textures_allocate();

    Camera2D camera{.rotation = 0.0f, .zoom = .75f};

    render_state *r = render_state_allocate(&txtrs, &camera);

    // Initial run.
    run_turn(w, b, t, player, r);

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
            action action = {
                .kind = ACTION_MOVE,
            };
            action.payload.direction = direction;
            OPTION_SET_VALUE(COMPONENT(w, player, picked_action)->action,
                             action);

            run_turn(w, b, t, player, r);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        render_system(r, w);
        EndDrawing();
    } while (!WindowShouldClose());

    render_state_deallocate(r);
    textures_unload(&txtrs);

    world_deallocate(w);
    board_deallocate(b);
    free(t);

    CloseWindow();

    return 0;
}
