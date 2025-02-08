#include "store.h"

EntityStore EntityStore__new() {
  EntityStore store = {._base = {}, .archetypes_amount = 0, .archetypes = malloc(MAX_ARCHETYPES * sizeof(Arch))};
  return store;
}

bool EntityStore__register_arch(EntityStore *self, Arch *arch) {
  if (self->archetypes_amount == MAX_ARCHETYPES) {
    return false;
  }
  self->archetypes[self->archetypes_amount] = arch;
  self->archetypes_amount++;
  return true;
}

