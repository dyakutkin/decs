#include <assert.h>

#include "flags.h"

#include "board.h"
#include "components.h"
#include "setup.h"
#include "world.h"

static bool place_entity_on_board(struct entity entity,
                                  struct board_point point, struct world *w,
                                  struct board *b)
{
    if (!valid_entity(w, entity))
    {
        return false;
    }

    if (!attempt_occupy(b, point, entity))
    {
        return false;
    }

    *(WC(w, entity, board_situation)) = (struct board_situation){
        .type = BOARD_SITUATION_OCCUPIER, .point = point};

    return true;
}

struct entity setup_actors(struct world *w, struct board *b)
{
    struct entity player;

    assert(create_entity(w, &player));
    assert(place_entity_on_board(player, (struct board_point){1, 1}, w, b));
    FSET(WC(w, player, entity_flags)->flags, ENTITY_FLAG_PLAYER);

    return player;
}
