#pragma once

#include "genarena.h"
#include "components.h"

typedef GenArenaIdx EntityID;

typedef struct {
  PersonComponent PersonComponent;
  PositionComponent PositionComponent;
  PlayerComponent PlayerComponent;
} Entity;
