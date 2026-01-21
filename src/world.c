#include "world.h"
#include "entity.h"

struct world *world(void)
{
    struct world *w = calloc(1, sizeof(struct world));
    return w;
}

bool create_entity(struct world *w, struct entity *e)
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

bool remove_entity(struct world *w, struct entity e)
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

#define X(Type) w->Type[e.idx] = (struct Type){0};
#include "components.def"
#undef X

    return true;
}

bool valid_entity(struct world *w, struct entity e)
{
    if (e.idx >= MAX_ENTITIES)
    {
        return false;
    }
    return w->revision[e.idx] == e.revision && w->initialized[e.idx];
}
