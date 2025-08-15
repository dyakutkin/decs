#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../entity/entity.h"

#define BOARD_SIDE_TILES_AMOUNT 5000
#define BOARD_TILES_AMOUNT (BOARD_SIDE_TILES_AMOUNT * BOARD_SIDE_TILES_AMOUNT)

struct BoardTile {
  struct EntityID occupied_by;
};

struct Board {
  struct BoardTile tiles[BOARD_TILES_AMOUNT];
};

struct BoardTileStatus {
  bool occupied;
  struct EntityID occupied_by;
};

struct Board *alloc_board();
void board_tile_occupied(struct Board *board, struct Vector point,
                         struct BoardTileStatus *tile_status);
bool attempt_occupy_board_tile(struct Board *board, struct Vector point,
                               struct EntityID eID);
void deoccupy_board_tile(struct Board *board, struct Vector point);
