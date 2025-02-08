#include "stdint.h"

#include "vec.h"

#include "entity.h"
#include "components.h"
#include "store.h"

bool arch_person_fn(Entity *entity) {
  return Component__is_set((void*)&entity->PersonComponent);
}

int main(void) {
  int elem1 = 1;
  int elem2 = 3;

  ArrayList list = ArrayList__new(sizeof(int), 1);
  ArrayList__append(&list, &elem1);
  ArrayList__append(&list, &elem2);
    
  ArrayList__free(&list);

  Entity entity = {.PersonComponent = {._base.is_set = true, .name = "player"}};
  EntityStore store = EntityStore__new();

  Arch arch_person = {.matcher = &arch_person_fn};
  if (!EntityStore__register_arch(&store, &arch_person)) {
    return 1;
  };

  return 0;
}
