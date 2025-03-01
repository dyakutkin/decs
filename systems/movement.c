#include <stdio.h>

#include "../entity.h"
#include "../components.h"

#include "movement.h"

void movement_system(Board *board, GenArena *entities, AList events) {
  for (int i = 0; i < events.len; i++) {
    MoveEvent event = ((MoveEvent*)events.events)[i];
    Entity *e = GenArena__get(entities, event.entity_id);
    if (e == NULL) {
      continue;
    }
    if (!BaseComponent__is_set(&(e->PositionComponent))) {
      continue;
    }
    bool collided = !Board__attempt_occupy(board, &((Point){.x = e->PositionComponent.x + event.delta.x}), event.entity_id);
    if (collided) {
      printf("%zu collided while attempting to move.", event.entity_id.idx_raw);
    }
  }
}

