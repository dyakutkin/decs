#include "example.h"

void example_system(World *w)
{
    ITERW(w, e)
    {
        if (!valid_entity(w, e))
        {
            continue;
        }

        BoardSituation *situation = WC(w, e, BoardSituation);
        if (situation->type == BOARD_SITUATION_ABSENT)
        {
            continue;
        }

        printf("e: idx=%zu, rev=%d, pos.x=%d\n", e.idx, e.revision,
               situation->point.x);
    }
}
