#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "board.h"
#include "components.h"
#include "entity.h"

#define MAX_ENTITIES 10000000

#define ITERW(_world, _entity)                                                 \
    for (entity _entity =                                                      \
             (entity){.idx = 1, .revision = _world->status[1].revision};       \
         _entity.idx < _world->len; _entity.idx++,                             \
                _entity.revision = _world->status[_entity.idx].revision)
#define COMPONENT(world, entity, component)                                           \
    (valid_entity(world, entity) ? &world->component[entity.idx]               \
                                 : &world->component[0])

typedef struct
{
    bool used;
    uint32_t revision;
    entity prev_freed;
} entity_world_status;

typedef struct
{
    size_t len;
    entity last_freed;
    entity_world_status status[MAX_ENTITIES];
#define X(Type) Type Type[MAX_ENTITIES];
#include "components.def"
#undef X
} world;

world *world_allocate(void);
void world_deallocate(world *w);
bool create_entity(world *w, entity *entity);
bool remove_entity(world *w, entity entity);
bool valid_entity(world *w, entity entity);
