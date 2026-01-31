#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "board.h"
#include "components.h"
#include "entity.h"

#define ITERW(_world, _entity)                                                 \
    for (entity _entity = (entity){.idx = 0, .revision = _world->revision[0]}; \
         _entity.idx < _world->len;                                            \
         _entity.idx++, _entity.revision = _world->revision[_entity.idx])
#define WC(world, entity, component)                                           \
    (valid_entity(world, entity) ? &world->component[entity.idx] : NULL)

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
} world;

world *world_allocate(void);
void world_deallocate(world *w);
bool create_entity(world *w, entity *entity);
bool remove_entity(world *w, entity entity);
bool valid_entity(world *w, entity entity);
