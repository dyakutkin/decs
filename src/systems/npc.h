#pragma once

#include "../world.h"

static const direction npc_random_move_directions[] = {
    DIRECTION_EAST, DIRECTION_WEST, DIRECTION_NORTH, DIRECTION_SOUTH};
static const size_t npc_random_move_directions_amount =
    sizeof npc_random_move_directions / sizeof npc_random_move_directions[0];

void npc_behavior_system(world *w);
