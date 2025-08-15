#include "entity.h"
#include <stdint.h>
#include <stdlib.h>

struct Entities *alloc_entities(void) {
  struct Entities *entities = calloc(1, sizeof(struct Entities));
  for (int i = 0; i < MAX_ENTITIES; i++) {
    entities->perception[i].header.size = MAX_PERCEPTION_MESSAGES;
    entities->vision[i].header.size = MAX_VISIBLE_TILES;
  }
  return entities;
}

bool new_entity(struct Entities *entities, struct EntityID *id,
                unsigned int initial_flags) {
  size_t idx;
  if (entities->free_idxs_amount > 0) {
    idx = entities->free_idxs[entities->free_idxs_amount - 1];
    entities->free_idxs_amount--;
  } else if (entities->cursor_main == MAX_ENTITIES) {
    return false;
  } else {
    idx = entities->cursor_main;
    entities->cursor_main++;
  }

  entities->rev[idx]++;
  entities->flags[idx] |= ENTITY_FLAG_TAKEN | initial_flags;

  id->idx = idx;
  id->rev = entities->rev[idx];

  return true;
}

bool is_valid_entity_id(struct Entities *entities, struct EntityID id) {
  if (id.idx >= MAX_ENTITIES) {
    return false;
  }
  uint32_t rev = entities->rev[id.idx];
  return rev == id.rev;
}

bool entity_exists(struct Entities *entities, struct EntityID id) {
  return is_valid_entity_id(entities, id) &&
         entities->flags[id.idx] & ENTITY_FLAG_TAKEN;
}
