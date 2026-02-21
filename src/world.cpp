#include "world.h"

world *world_allocate(void)
{
    world *w = (world *)calloc(1, sizeof(world));

    // Slot #0 is a "sentinel" value so we're starting at #1.
    w->len = 1;

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
    if (w->last_freed.idx != 0)
    {
        idx = w->last_freed.idx;
        w->last_freed = w->status[idx].prev_freed;
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

    w->status[idx].revision++;
    w->status[idx].used = true;

    e->idx = idx;
    e->revision = w->status[idx].revision;

    return true;
}

bool remove_entity(world *w, entity e)
{
    if (!valid_entity(w, e))
    {
        return false;
    }

    entity_world_status *ews = COMPONENT(w, e, status);

    ews->prev_freed = w->last_freed;
    w->last_freed = e;
    ews->used = false;

#define X(Type) w->Type[e.idx] = Type{};
#include "components.def"
#undef X

    return true;
}

bool valid_entity(world *w, entity e)
{
    if (e.idx == 0 || e.idx >= MAX_ENTITIES)
    {
        return false;
    }
    return w->status[e.idx].revision == e.revision && w->status[e.idx].used;
}
