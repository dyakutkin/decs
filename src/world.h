#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "board.h"
#include "components.h"
#include "entity.h"

#define ITERW(world, entity)                                                   \
    for (Entity entity = (Entity){.idx = 0, .revision = w->revision[0]};       \
         entity.idx < w->len;                                                  \
         entity.idx++, entity.revision = w->revision[entity.idx])
#define WC(world, entity, component) (&world->component[entity.idx])

typedef struct
{
    size_t len;
    size_t free_idxs_amount;
    size_t free_idxs[MAX_ENTITIES];

    uint32_t revision[MAX_ENTITIES];
    bool initialized[MAX_ENTITIES];

#define X(Type) Type Type[MAX_ENTITIES];
#include "components.def"
#undef X
} World;

World *world_alloc(void);
bool new_entity(World *world, Entity *entity);
bool remove_entity(World *world, Entity entity);
bool valid_entity(World *world, Entity entity);
