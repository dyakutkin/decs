#include "systems.h"

bool input_system(struct Entities *entities, struct EntityID player_id) {
  SET_CURRENT_ENTITY(player_id);

  if (!MATCH_ENTITY(ENTITY_FLAG_PLAYER | ENTITY_FLAG_PICKED_ACTION)) {
    return false;
  }

  int x = 0, y = 0;
  bool got_input = false;

  if (IsKeyReleased(KEY_RIGHT)) {
    x = 1;
    y = 0;
    got_input = true;
  } else if (IsKeyReleased(KEY_LEFT)) {
    x = -1;
    y = 0;
    got_input = true;
  } else if (IsKeyReleased(KEY_UP)) {
    x = 0;
    y = -1;
    got_input = true;
  } else if (IsKeyReleased(KEY_DOWN)) {
    x = 0;
    y = 1;
    got_input = true;
  }

  if (got_input) {
    COMPONENT(action).tag = ACTION_MOVE;
    COMPONENT(action).action.ActionMove =
        (struct ActionMove){.delta = {.x = x, .y = y}};
  }

  return got_input;
}
