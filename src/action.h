#pragma once

#include "./vector.h"
#include "entity/entity.h"
#include <stdint.h>

struct ActionMove {
  struct Vector delta;
};

enum PickedActionTag {
  ACTION_NOT_PICKED,
  ACTION_MOVE,
};

union _PickedAction {
  struct ActionMove ActionMove;
};

struct PickedAction {
  uint16_t tag;
  union _PickedAction action;
};
