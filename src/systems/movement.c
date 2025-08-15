#include "systems.h"

void movement_system(struct Board *board, struct Entities *entities) {
  FOREACH_ENTITY_IN(entities) {
    if (!MATCH_ENTITY(ENTITY_FLAG_POSITION | ENTITY_FLAG_PICKED_ACTION)) {
      continue;
    }

    if (!(COMPONENT(action).tag == ACTION_MOVE)) {
      continue;
    }

    struct Vector new_attempted_point = {
        .x =
            COMPONENT(position).x + COMPONENT(action).action.ActionMove.delta.x,
        .y =
            COMPONENT(position).y + COMPONENT(action).action.ActionMove.delta.y,
    };

    bool collided =
        !attempt_occupy_board_tile(board, new_attempted_point, ENTITY_ID());

    printf("attempts move to: x: %d, y: %d\n", new_attempted_point.x,
           new_attempted_point.y);

    if (collided) {
      printf("collided\n");
      continue;
    }

    deoccupy_board_tile(board, (struct Vector){.x = COMPONENT(position).x,
                                               .y = COMPONENT(position).y});
    COMPONENT(position).x = new_attempted_point.x;
    COMPONENT(position).y = new_attempted_point.y;
    printf("moved\n");
  }
}