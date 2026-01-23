#pragma once

#include "../world.h"

#define VISION_SQUARE_WIDTH 5
#define VISION_SQUARE_DEPTH VISION_SQUARE_WIDTH

void percepted_events_update_system(struct world *w, struct board *b);
