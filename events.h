#pragma once

#include "entity_id.h"
#include "point.h"

typedef struct {
   VecDelta delta;
   EntityID entity_id;
} MoveEvent;
