#include "world.h"
#include "entity.h"
#include <stdlib.h>

world *world_allocate(void)
{
    world *w = calloc(1, sizeof(world));
    return w;
}

void world_deallocate(world *w)
{
    for (size_t i = 0; i < MAX_ENTITIES; i++)
    {
        free(w->percepted_events[i].broadcasts.items);
        free(w->entity_sprite[i].animations.items);
    }
    free(w);
}

bool create_entity(world *w, entity *e)
{
    size_t idx;
    if (w->free_idxs_amount > 0)
    {
        idx = w->free_idxs[w->free_idxs_amount - 1];
        w->free_idxs_amount--;
    }
    else if (w->len == MAX_ENTITIES)
    {
        return false;
    }
    else
    {
        idx = w->len;
        w->len++;
    }

    w->revision[idx]++;
    w->initialized[idx] = true;

    e->idx = idx;
    e->revision = w->revision[idx];

    return true;
}

bool remove_entity(world *w, entity e)
{
    if (!valid_entity(w, e))
    {
        return false;
    }

    if (w->free_idxs_amount == MAX_ENTITIES)
    {
        return false;
    }

    w->free_idxs[w->free_idxs_amount] = e.idx;
    w->free_idxs_amount++;

#define X(Type) w->Type[e.idx] = (Type){0};
#include "components.def"
#undef X

    return true;
}

bool valid_entity(world *w, entity e)
{
    if (e.idx >= MAX_ENTITIES)
    {
        return false;
    }
    return w->revision[e.idx] == e.revision && w->initialized[e.idx];
}
