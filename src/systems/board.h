#pragma once

#include <stdio.h>

#include "../board.h"
#include "../entity.h"
#include "../turn.h"
#include "../world.h"

void board_position_update_system(world *w, board *b, turn *t);
