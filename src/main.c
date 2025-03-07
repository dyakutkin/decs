#include <assert.h>
#include <stdint.h>
#include <time.h>

#include <raylib.h>

#include "resource_dir.h"

#include "collections/alist.h"
#include "collections/genarena.h"

#include "globals/entity.h"
#include "globals/visuals.h"

#include "board.h"
#include "entity.h"
#include "entity_id.h"
#include "events.h"
#include "assets/textures.h"

#include "setup/actors.h"

#include "systems/input.h"
#include "systems/movement.h"
#include "systems/render.h"

int main(void)
{
    GenArena entities = GenArena__alloc(sizeof(Entity), MAX_ENTITIES_AMOUNT);
    Board board = Board__alloc();
    MoveEvents move_events = ALIST_ALLOC(MoveEvent, 5);

    EntityID player_id = setup_actors(&board, &entities);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Past Recalling");

    SearchAndSetResourceDir("resources");
    Textures textures = Textures__load();

    SetTargetFPS(FPS_TARGET);

    Entity *player_e = GenArena__get(&entities, player_id);

    assert(player_e != NULL);
    assert(BaseComponent__is_set(&player_e->PositionComponent));

    // TODO: handle it somewhere else.
    float texture_size_px = map_tile_size();
    Camera2D camera = {0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    clock_t start, end;
    double cpu_time_used;

    bool got_input = false;

    do
    {
        bool got_input = input_system(&move_events, player_id);

        if (got_input)
        {
            start = clock();

            movement_system(&board, &entities, move_events);

            ALIST_CLEAR((&move_events));

            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("game logic took: %f\n", cpu_time_used);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        render_system(&camera, &textures, &board, &entities, player_id);

        // DrawText("foobar", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    } while (!WindowShouldClose());

    CloseWindow();

    Textures__unload(&textures);

    ALIST_FREE((&move_events));
    Board__free(&board);
    GenArena__free(&entities);

    return 0;
}
