#include <assert.h>
#include <stdint.h>

#include <raylib.h>

#include "resource_dir.h"

#include "collections/alist.h"
#include "collections/genarena.h"

#include "globals/entity.h"
#include "globals/game.h"

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
    AList move_events = AList__alloc(5, sizeof(MoveEvent));

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
    camera.offset = (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose())
    {
        bool got_input = input_system(&move_events, player_id);

        if (got_input)
        {
            movement_system(&board, &entities, move_events);
            camera.target = (Vector2){player_e->PositionComponent.x * texture_size_px, player_e->PositionComponent.y * texture_size_px};
            AList__clear(&move_events);
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);
        render_system(&camera, &textures, &board, &entities, player_id);

        // DrawText("foobar", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    Textures__unload(&textures);

    AList__free(&move_events);
    Board__free(&board);
    GenArena__free(&entities);

    return 0;
}
