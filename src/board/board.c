#include "board.h"
#include <stdlib.h>

struct Board *alloc_board() {
  struct Board *board = calloc(1, sizeof(struct Board));
  return board;
}

static size_t point_to_idx(struct Vector p) {
  return p.y * BOARD_SIDE_TILES_AMOUNT + p.x;
}

static bool tile_is_unset(struct BoardTile tile) {
  return tile.occupied_by.idx == ENTITY_ID_UNSET.idx &&
         tile.occupied_by.rev == ENTITY_ID_UNSET.rev;
}

static bool is_valid_board_tile(struct Vector p) {
  if (p.x < 0 || p.y < 0) {
    return false;
  }
  size_t idx = point_to_idx(p);
  return idx < BOARD_TILES_AMOUNT;
}

void board_tile_occupied(struct Board *board, struct Vector point,
                         struct BoardTileStatus *tile_status) {
  if (!is_valid_board_tile(point)) {
    tile_status->occupied = true;
    tile_status->occupied_by = ENTITY_ID_UNSET;
    return;
  }

  struct BoardTile *tile = board->tiles + point_to_idx(point);
  if (tile_is_unset(*tile)) {
    tile_status->occupied = false;
    tile_status->occupied_by = ENTITY_ID_UNSET;
    return;
  }

  tile_status->occupied = true;
  tile_status->occupied_by = tile->occupied_by;
  return;
}

bool attempt_occupy_board_tile(struct Board *board, struct Vector p,
                               struct EntityID eID) {
  bool tile_valid = is_valid_board_tile(p);
  if (!tile_valid) {
    return false;
  }

  struct BoardTileStatus status = {0};
  board_tile_occupied(board, p, &status);
  if (status.occupied) {
    return false;
  }

  size_t idx = point_to_idx(p);

  board->tiles[idx].occupied_by = eID;
  return true;
}

void deoccupy_board_tile(struct Board *board, struct Vector p) {
  struct EntityID potential_occupier = {0};

  struct BoardTileStatus status = {0};
  board_tile_occupied(board, p, &status);
  if (!status.occupied) {
    return;
  }

  size_t idx = point_to_idx(p);
  board->tiles[idx].occupied_by = ENTITY_ID_UNSET;
}
