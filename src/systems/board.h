#pragma once

#include <assert.h>

#include "../board.h"
#include "../entity.h"
#include "../offsets.h"
#include "../world.h"

void board_position_update_system(struct world *w, struct board *b,
                                  struct offsets_global *og);
