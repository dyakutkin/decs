#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  size_t idx_raw;
  unsigned int rev;
} GenArenaIdx;

typedef struct {
  unsigned int rev;
  bool taken;
} GenArenaValueDesc;

typedef struct {
  size_t elem_size;
  size_t elem_amount;

  GenArenaValueDesc *descs;
  void *data;

  size_t current_idx;

  size_t *freed_idxs;
  size_t freed_idxs_amount;
} GenArena;

GenArena GenArena__alloc(size_t value_size, size_t elem_amount);
void GenArena__free(GenArena *self);
bool GenArena__insert(GenArena *self, void *value, GenArenaIdx *idx);
void *GenArena__get(GenArena *self, GenArenaIdx idx);
bool GenArena__remove(GenArena *self, GenArenaIdx idx);
