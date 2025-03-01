#include "assert.h"

#include "actors.h"

EntityID setup_actors(Board *board, GenArena *entities) {
  GenArenaIdx player_id = {};
  Entity player = {
      component(PersonComponent, .name = "Player"),
      component(PositionComponent, .x = 1, .y = 1),
      component(PlayerComponent),
  };
  assert(GenArena__insert(entities, &player, &player_id));

  assert(Board__attempt_occupy(board,
                               &(Point){.x = player.PositionComponent.x,
                                        .y = player.PositionComponent.y},
                               player_id));

  GenArenaIdx npc_id = {};
  Entity npc = {
      component(PersonComponent, .name = "John Doe"),
      component(PositionComponent, .x = 2, .y = 2),
  };
  assert(GenArena__insert(entities, &npc, &npc_id));

  assert(Board__attempt_occupy(
      board,
      &(Point){.x = npc.PositionComponent.x, .y = npc.PositionComponent.y},
      npc_id));

  return player_id;
}
