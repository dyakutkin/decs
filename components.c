#include "components.h"

bool BaseComponent__is_set(void *c) {
  BaseComponent *component = (BaseComponent*)c;
  return component->is_set;
}
