#include "assert.h"
#include "stdint.h"

#include <raylib.h>

#include "components.h"
#include "entity.h"
#include "genarena.h"

bool arch_person_fn(Entity *entity) {
  return BaseComponent__is_set((void *)&entity->PersonComponent);
}

int main(void) {
  GenArena arena = GenArena__alloc(sizeof(Entity), 1000000);

  GenArenaIdx idx = {};
  Entity e = {
      component(PersonComponent, .name = "John"),
      component(PositionComponent, .x = 0, .y = 0),
  };
  assert(GenArena__insert(&arena, &e, &idx));

  GenArenaIdx idx1 = {};
  Entity e1 = {
      component(PersonComponent, .name = "Jack"),
      component(PositionComponent, .x = 1, .y = 1),
  };
  assert(GenArena__insert(&arena, &e1, &idx1));

  GenArenaIdx idx2 = {};
  Entity e2 = {
      component(PersonComponent, .name = "Tom"),
      component(PositionComponent, .x = 2, .y = 2),
  };
  assert(GenArena__insert(&arena, &e2, &idx2));

  assert(GenArena__remove(&arena, idx1));

  GenArenaIdx idx3 = {};
  Entity e3 = {
      component(PersonComponent, .name = "Newby"),
      component(PositionComponent, .x = 3, .y = 3),
  };
  assert(GenArena__insert(&arena, &e3, &idx3));
  
  Entity *got1 = GenArena__get(&arena, idx1);
  Entity *got3 = GenArena__get(&arena, idx3);

  GenArena__free(&arena);

  return 0;
}
