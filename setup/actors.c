#include "assert.h"

#include "actors.h"

void setup_actors(Board *board, GenArena *e_arena) {
  GenArenaIdx player_id = {};
  Entity player = {
      component(PersonComponent, .name = "Player"),
      component(PositionComponent, .x = 1, .y = 1),
      component(PlayerComponent),
  };
  assert(GenArena__insert(e_arena, &player, &player_id));

  assert(Board__attempt_occupy(board,
                               &(Point){.x = player.PositionComponent.x,
                                        .y = player.PositionComponent.y},
                               player_id));

  GenArenaIdx npc_id = {};
  Entity npc = {
      component(PersonComponent, .name = "John Doe"),
      component(PositionComponent, .x = 2, .y = 2),
  };
  assert(GenArena__insert(e_arena, &npc, &npc_id));

  assert(Board__attempt_occupy(
      board,
      &(Point){.x = npc.PositionComponent.x, .y = npc.PositionComponent.y},
      npc_id));
}
