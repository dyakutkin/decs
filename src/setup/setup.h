#pragma once

#include "../board/board.h"
#include "../entity/entity.h"
#include <assert.h>

static bool place_entity_on_board(struct EntityID entity_id,
                                  struct Vector point,
                                  struct Entities *entities,
                                  struct Board *board);

struct EntityID setup_actors(struct Entities *entities, struct Board *board);