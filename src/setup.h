#pragma once

#include <string.h>

#include "panic.h"
#include "board.h"
#include "components.h"
#include "direction.h"
#include "entity.h"
#include "flags.h"
#include "world.h"

#define BASE_HUMANOID_ENTITY_FLAGS ENTITY_FLAG_VISION

entity setup_actors(world *w, board *b);
