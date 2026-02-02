#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "direction.h"
#include "flags.h"

#include "board.h"
#include "components.h"
#include "setup.h"
#include "world.h"

#define BASE_HUMANOID_ENTITY_FLAGS ENTITY_FLAG_VISION

static bool place_entity_on_board(entity entity, board_vec point, world *w,
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

    entity player;

    assert(create_entity(w, &player));
    assert(place_entity_on_board(player, (board_vec){0, 0}, w, b));
    FSET(WC(w, player, entity_flags)->flags,
         BASE_HUMANOID_ENTITY_FLAGS | ENTITY_FLAG_PLAYER);
    strcpy(WC(w, player, entity_name)->name, "Player");

    for (size_t i = 1; i <= 100; i++)
    {
        entity npc;
        assert(create_entity(w, &npc));
        assert(place_entity_on_board(npc, (board_vec){i, i}, w, b));
        FSET(WC(w, npc, entity_flags)->flags,
             BASE_HUMANOID_ENTITY_FLAGS | ENTITY_FLAG_NPC);
        sprintf(WC(w, npc, entity_name)->name, "NPC#%zu", i);
    }

    return player;
}
