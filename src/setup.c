#include <assert.h>

#include "flags.h"

#include "board.h"
#include "components.h"
#include "setup.h"
#include "world.h"

static bool place_entity_on_board(Entity entity, BoardPoint point, World *w,
                                  Board *b);

Entity setup_actors(World *w, Board *b)
{
    Entity player;

    assert(new_entity(w, &player));
    assert(place_entity_on_board(player, (BoardPoint){1, 1}, w, b));
    FSET(WC(w, player, EntityFlags)->flags, ENTITY_FLAG_PLAYER);

    return player;
}

static bool place_entity_on_board(Entity entity, BoardPoint point, World *w,
                                  Board *b)
{
    if (!valid_entity(w, entity))
    {
        return false;
    }

    if (!attempt_occupy(b, point, entity))
    {
        return false;
    }

    *(WC(w, entity, BoardSituation)) =
        (BoardSituation){.type = BOARD_SITUATION_OCCUPIER, .point = point};

    return true;
}
