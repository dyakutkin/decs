#pragma once

#include "../board/board.h"
#include "../entity/entity.h"
#include "render.h"
#include <assert.h>

bool input_system(struct Entities *entities, struct EntityID player_id);
void movement_system(struct Board *board, struct Entities *entities);
void clear_picked_action_system(struct Entities *entities);
void render_system(Camera2D *camera, struct Textures *textures,
                   struct Board *board, struct Entities *entities,
                   struct EntityID player_id);