#pragma once

// #include "./vector.h"
// #include "entity/entity.h"
#include <stdint.h>

enum MessageTag {
  MESSAGE_TAG_DUMMY,
  //   ACTION_NOT_PICKED,
  //   ACTION_MOVE,
};

union _Message {
  //   struct ActionMove ActionMove;
};

struct Message {
  uint16_t tag;
  union _Message message;
};
