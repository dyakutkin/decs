#pragma once

#include "../action.h"
#include "../collections/buffer.h"
#include "../message.h"
#include "../vector.h"
#include <stdbool.h>

#define MAX_ENTITIES 1000
#define MAX_PERCEPTION_MESSAGES 50
#define MAX_VISIBLE_TILES 25

#define ENTITY_ID_UNSET ((struct EntityID){0})
#define FOREACH_ENTITY_IN(entities)                                            \
  for (int __current_entity_idx = 0;                                           \
       __current_entity_idx < entities->cursor_main; __current_entity_idx++)
#define SET_CURRENT_ENTITY(entity_id)                                          \
  size_t __current_entity_idx = entity_id.idx;
#define MATCH_ENTITY(flags_to_match)                                           \
  (entities->flags[__current_entity_idx] & ENTITY_FLAG_TAKEN | flags_to_match)
#define COMPONENT(component_name) entities->component_name[__current_entity_idx]
#define ENTITY_ID()                                                            \
  (struct EntityID) { .idx = __current_entity_idx, .rev = COMPONENT(rev) }

struct EntityID {
  size_t idx;
  uint32_t rev;
};

enum EntityFlag {
  // Flag-only values.
  ENTITY_FLAG_TAKEN = (1u << 0),
  ENTITY_FLAG_PLAYER = (1u << 1),
  ENTITY_FLAG_NPC = (1u << 2),

  // "component existence" values.
  ENTITY_FLAG_POSITION = (1u << 3),
  ENTITY_FLAG_PICKED_ACTION = (1u << 4),
  ENTITY_FLAG_VISION = (1u << 5),
  ENTITY_FLAG_PERCEPTION = (1u << 6),
};

struct Perception {
  struct FifoBufferHeader header;
  struct Message elements[MAX_PERCEPTION_MESSAGES];
};

struct Vision {
  struct FifoBufferHeader header;
  struct Vector tiles[MAX_VISIBLE_TILES];
};

struct Entities {
  size_t cursor_main;

  uint32_t rev[MAX_ENTITIES];
  uint64_t flags[MAX_ENTITIES];

  size_t free_idxs_amount;
  size_t free_idxs[MAX_ENTITIES];

  // "components":
  struct Vector position[MAX_ENTITIES];
  struct Vector facing[MAX_ENTITIES];

  struct PickedAction action[MAX_ENTITIES];

  struct Vision vision[MAX_ENTITIES];

  struct Perception perception[MAX_ENTITIES];
};

struct Entities *alloc_entities(void);
bool new_entity(struct Entities *entities, struct EntityID *id,
                unsigned int initial_flags);
bool is_valid_entity_id(struct Entities *entities, struct EntityID id);
bool entity_exists(struct Entities *entities, struct EntityID id);
size_t current_entities_amount(struct Entities *entities);
