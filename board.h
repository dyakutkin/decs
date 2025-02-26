#pragma once

#include <stdlib.h>
#include "stdbool.h"

#include "entity.h"
#include "point.h"

#define BOARD_SIDE_TILES_AMOUNT 5000

typedef struct {
  bool occupied;
  EntityID occupied_by;
} BoardTile;

typedef struct {
  size_t tiles_amount;
  BoardTile *tiles;
} Board;

Board Board__alloc();
void Board__free(Board *self);
bool Board__get_occupier(Board *self, Point *p, EntityID *occupier);
bool Board__attempt_occupy(Board *self, Point *p, EntityID eID);
void Board__deoccupy(Board *self, Point *p);
