#pragma once

#include <stdio.h>
#include <string.h>

#include "board.h"
#include "components.h"
#include "direction.h"
#include "entity.h"
#include "flags.h"
#include "world.h"

#define BASE_HUMANOID_ENTITY_FLAGS ENTITY_FLAG_VISION

entity setup_actors(world *w, board *b);
