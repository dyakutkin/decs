#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"

#include "raylib.h"

#include "decs.h"

#include "window.h"
#include "game.h"

DECS_sys(draw_map_actors_system)
{
    DECS_eiter()
    {
        DECS_q(DECS_ec(PositionComponent) && DECS_ec(PersonComponent));

        size_t str_size = strlen(NAME_STR_TEMPLATE) + strlen(DECS_ec(PersonComponent)->name) - 2; // -2 stands for "%s".
        char *drawtext = malloc(sizeof(char) * str_size);
        sprintf(drawtext, NAME_STR_TEMPLATE, DECS_ec(PersonComponent)->name);

        DrawText(
            drawtext,
            DECS_ec(PositionComponent)->x * TILE_SIZE,
            DECS_ec(PositionComponent)->y * TILE_SIZE,
            FONT_SIZE, RAYWHITE);

        free(drawtext);
    }
}

DECS_sys(player_control_system)
{
    DECS_eiter()
    {
        DECS_q(DECS_ec(PositionComponent) && DECS_ec(PlayerComponent));

        if (IsKeyReleased(KEY_A))
        {
            DECS_ec(PositionComponent)->x--;
        }
        else if (IsKeyReleased(KEY_D))
        {
            DECS_ec(PositionComponent)->x++;
        }
        else if (IsKeyReleased(KEY_W))
        {
            DECS_ec(PositionComponent)->y--;
        }
        else if (IsKeyReleased(KEY_S))
        {
            DECS_ec(PositionComponent)->y++;
        }
    }
}

int main(void)
{
    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;

    InitWindow(screenWidth, screenHeight, WINDOW_TITLE);

    SetTargetFPS(TARGET_FPS);

    ComponentsStore *components_store = malloc(sizeof(ComponentsStore));

    DECS_register_component(PersonComponent, person_component_store);
    DECS_register_component(PositionComponent, position_component_store);
    DECS_register_component(PlayerComponent, player_component_store);

    printf(
        "NOTE: WORLD: total components size: %lu Mb\n",
        DECS_ENTITIES_MAX * (sizeof(PersonComponent) + sizeof(PositionComponent) + sizeof(PlayerComponent)) / 1024 / 1000);

    // Spawn "NPC".
    person_component_store[0] = malloc(sizeof(PersonComponent));
    person_component_store[0]->name = "NPC";
    position_component_store[0] = malloc(sizeof(PositionComponent));
    position_component_store[0]->x = 1;
    position_component_store[0]->y = 1;

    // Spawn player.
    person_component_store[1] = malloc(sizeof(PersonComponent));
    person_component_store[1]->name = "Player";
    position_component_store[1] = malloc(sizeof(PositionComponent));
    position_component_store[1]->x = 2;
    position_component_store[1]->y = 2;
    player_component_store[1] = malloc(sizeof(PlayerComponent));

    while (!WindowShouldClose())
    {
        player_control_system(components_store);

        BeginDrawing();
        ClearBackground(BLACK);

        draw_map_actors_system(components_store);

        EndDrawing();
    }

    for (int i = 0; i < DECS_ENTITIES_MAX; i++)
    {
        if (person_component_store[i] != NULL)
            free(person_component_store[i]);
        if (position_component_store[i] != NULL)
            free(position_component_store[i]);
        if (player_component_store[i] != NULL)
            free(player_component_store[i]);
    }
    free(person_component_store);
    free(position_component_store);
    free(player_component_store);

    free(components_store);

    CloseWindow();

    return 0;
}