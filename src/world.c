#include "world.h"
#include "entity.h"

World *world_alloc(void)
{
    World *world = calloc(1, sizeof(World));
    return world;
}

bool new_entity(World *world, Entity *entity)
{
    size_t idx;
    if (world->free_idxs_amount > 0)
    {
        idx = world->free_idxs[world->free_idxs_amount - 1];
        world->free_idxs_amount--;
    }
    else if (world->len == MAX_ENTITIES)
    {
        return false;
    }
    else
    {
        idx = world->len;
        world->len++;
    }

    world->revision[idx]++;
    world->initialized[idx] = true;

    entity->idx = idx;
    entity->revision = world->revision[idx];

    return true;
}

bool remove_entity(World *world, Entity entity)
{
    if (!valid_entity(world, entity))
    {
        return false;
    }

    if (world->free_idxs_amount == MAX_ENTITIES)
    {
        return false;
    }

    world->free_idxs[world->free_idxs_amount] = entity.idx;
    world->free_idxs_amount++;

#define X(Type) world->Type[entity.idx] = (Type){0};
#include "components.def"
#undef X

    return true;
}

bool valid_entity(World *w, Entity entity)
{
    if (entity.idx >= MAX_ENTITIES)
    {
        return false;
    }
    return w->revision[entity.idx] == entity.revision &&
           w->initialized[entity.idx];
}
