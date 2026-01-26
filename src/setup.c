#include <assert.h>

#include "flags.h"

#include "board.h"
#include "components.h"
#include "setup.h"
#include "world.h"

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
        (board_situation){.type = BOARD_SITUATION_OCCUPIER, .point = point};

    return true;
}

entity setup_actors(world *w, board *b)
{
    entity player;

    assert(create_entity(w, &player));
    assert(place_entity_on_board(player, (board_vec){1, 1}, w, b));
    FSET(WC(w, player, entity_flags)->flags, ENTITY_FLAG_PLAYER);
    FSET(WC(w, player, entity_flags)->flags, ENTITY_FLAG_VISION);

    return player;
}
