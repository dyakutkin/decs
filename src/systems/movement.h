#pragma once

#include "../collections/alist.h"

#include "../board.h"
#include "../events.h"

void movement_system(Board *board, GenArena *entities, AList events);
