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
        PANIC("Failed to create player\n");
    }
    if (!place_entity_on_board(player, (ivec2){0, 0}, w, b))
    {
        PANIC("Failed to place player on board\n");
    }
    FSET(WC(w, player, entity_flags)->flags,
         BASE_HUMANOID_ENTITY_FLAGS | ENTITY_FLAG_PLAYER);
    strcpy(WC(w, player, entity_name)->name, "Player");

    for (size_t i = 1; i <= 1000; i++)
    {
        entity npc;
        if (!create_entity(w, &npc))
        {
            PANIC("NPC setup failed\n");
        }
        if (!place_entity_on_board(npc, (ivec2){i, i}, w, b))
        {
            PANIC("NPC setup failed\n");
        }
        FSET(WC(w, npc, entity_flags)->flags,
             BASE_HUMANOID_ENTITY_FLAGS | ENTITY_FLAG_NPC);
        entity_name *en = WC(w, npc, entity_name);
        if (en == NULL)
        {
            PANIC("NPC setup failed\n");
        }
        sprintf(en->name, "NPC#%zu", i);
    }

    return player;
}
