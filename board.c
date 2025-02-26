#include "board.h"
#include "stdbool.h"

Board Board__alloc() {
  size_t tiles_amount = BOARD_SIDE_TILES_AMOUNT * BOARD_SIDE_TILES_AMOUNT;
  Board b = {.tiles_amount = tiles_amount,
             .tiles = (BoardTile *)calloc(tiles_amount, sizeof(BoardTile))};
  return b;
}

void Board__free(Board *self) {
  free(self->tiles);
}

static size_t point_to_idx(Point *p) {
  return p->y * BOARD_SIDE_TILES_AMOUNT + p->x;
}

static bool Board__is_valid_tile(Board *self, Point *p) {
  size_t idx = point_to_idx(p);
  return idx < self->tiles_amount;
}

bool Board__get_occupier(Board *self, Point *p, EntityID *occupier) {
  bool tile_valid = Board__is_valid_tile(self, p);
  if (!tile_valid) {
    return false;
  }

  BoardTile *tile = self->tiles + point_to_idx(p);
  if (!tile->occupied) {
    return false;
  }

  memcpy(occupier, tile, sizeof(BoardTile));
  return true;
}

bool Board__attempt_occupy(Board *self, Point *p, EntityID eID) {
  EntityID *potential_occupier = NULL;
  bool occupied = Board__get_occupier(self, p, potential_occupier);
  if (occupied) {
    return false;
  }

  size_t idx = point_to_idx(p);

  self->tiles[idx].occupied = true;
  self->tiles[idx].occupied_by = eID;

  return true;
}

void Board__deoccupy(Board *self, Point *p) {
  EntityID *potential_occupier = NULL;
  bool occupied = Board__get_occupier(self, p, potential_occupier);
  if (!occupied) {
    return;
  }

  size_t idx = point_to_idx(p);
  self->tiles[idx].occupied = false;
}
