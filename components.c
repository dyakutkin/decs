#include "components.h"

bool Component__is_set(void *c) {
  Component *component = (Component*)c;
  return component->is_set;
}
