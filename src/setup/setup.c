#include "setup.h"

struct EntityID setup_actors(struct Entities *entities, struct Board *board) {
  struct EntityID player_id;
  assert(new_entity(
      entities, &player_id,
      (ENTITY_FLAG_PLAYER | ENTITY_FLAG_POSITION | ENTITY_FLAG_PICKED_ACTION)));

  assert(place_entity_on_board(player_id, (struct Vector){.x = 0, .y = 0},
                               entities, board));

  return player_id;
}

static bool place_entity_on_board(struct EntityID entity_id,
                                  struct Vector point,
                                  struct Entities *entities,
                                  struct Board *board) {
  SET_CURRENT_ENTITY(entity_id);

  if (!is_valid_entity_id(entities, entity_id) ||
      (!(COMPONENT(flags) & ENTITY_FLAG_POSITION))) {
    return false;
  }

  if (!attempt_occupy_board_tile(board, point, entity_id)) {
    return false;
  }

  COMPONENT(position) = point;
}