#include "setup.h"

static bool place_entity_on_board(entity entity, ivec2 point, world *w,
                                  board *b)
{
    if (!valid_entity(w, entity))
    {
        return false;
    }

    if (!board_occupy(b, point, entity))
    {
        return false;
    }

    *(WC(w, entity, board_situation)) =
        (board_situation){.type = BOARD_SITUATION_OCCUPIER,
                          .point = point,
                          .facing = DIRECTION_EAST};

    return true;
}

entity setup_actors(world *w, board *b)
{

    entity player = {0};

    if (!create_entity(w, &player))
    {
        fprintf(stderr, "Failed to create player\n");
        abort();
    }
    if (!place_entity_on_board(player, (ivec2){0, 0}, w, b))
    {
        fprintf(stderr, "Failed to place player on board\n");
        abort();
    }
    FSET(WC(w, player, entity_flags)->flags,
         BASE_HUMANOID_ENTITY_FLAGS | ENTITY_FLAG_PLAYER);
    strcpy(WC(w, player, entity_name)->name, "Player");

    for (size_t i = 1; i <= 1000; i++)
    {
        entity npc;
        if (!create_entity(w, &npc))
        {
            fprintf(stderr, "NPC setup failed\n");
            abort();
        }
        if (!place_entity_on_board(npc, (ivec2){i, i}, w, b))
        {
            fprintf(stderr, "NPC setup failed\n");
            abort();
        }
        FSET(WC(w, npc, entity_flags)->flags,
             BASE_HUMANOID_ENTITY_FLAGS | ENTITY_FLAG_NPC);
        entity_name *en = WC(w, npc, entity_name);
        if (en == NULL)
        {
            fprintf(stderr, "NPC setup failed\n");
            abort();
        }
        sprintf(en->name, "NPC#%zu", i);
    }

    return player;
}
