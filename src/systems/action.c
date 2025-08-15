#include "systems.h"

void clear_picked_action_system(struct Entities *entities) {
  FOREACH_ENTITY_IN(entities) {
    if (!MATCH_ENTITY(ENTITY_FLAG_PICKED_ACTION)) {
      continue;
    }
    COMPONENT(action).tag = ACTION_NOT_PICKED;
  }
}