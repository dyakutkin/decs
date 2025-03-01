#include "genarena.h"

GenArena GenArena__alloc(size_t value_size, size_t elem_amount) {
  size_t elem_size = value_size;
  GenArena arena = {
      .elem_size = elem_size,
      .elem_amount = elem_amount,
      .descs = calloc(elem_amount, sizeof(GenArenaValueDesc)),
      .data = malloc(elem_amount * elem_size),
      .current_idx = 0,
      .freed_idxs = malloc(sizeof(size_t) * elem_amount),
      .freed_idxs_amount = 0,
  };
  return arena;
}

void GenArena__free(GenArena *self) {
  free(self->descs);
  free(self->data);
}

bool GenArena__insert(GenArena *self, void *value, GenArenaIdx *idx) {
  if (self->current_idx >= self->elem_amount) {
    return false;
  }

  size_t idx_raw;

  if (self->freed_idxs_amount == 0) {
    idx_raw = self->current_idx;
    self->current_idx++;
  } else {
    idx_raw = self->freed_idxs_amount;
    self->freed_idxs_amount--;
  }

  void *current_elem_data_ptr = self->data + self->elem_size * idx_raw;
  GenArenaValueDesc *current_elem_desc_ptr = self->descs + idx_raw;

  memcpy(current_elem_data_ptr, value, self->elem_size);

  current_elem_desc_ptr->taken = true;
  current_elem_desc_ptr->rev++;

  idx->idx_raw = idx_raw;
  idx->rev = current_elem_desc_ptr->rev;

  return true;
}

void *GenArena__get(GenArena *self, GenArenaIdx idx) {
  if (idx.idx_raw >= self->elem_amount) {
    return NULL;
  }
  GenArenaValueDesc *requested_elem_desc_ptr = self->descs + idx.idx_raw;

  if (!requested_elem_desc_ptr->taken) {
    return NULL;
  }

  if (requested_elem_desc_ptr->rev != idx.rev) {
    return NULL;
  }

  void *current_elem_data_ptr = self->data + self->elem_size * idx.idx_raw;
  return current_elem_data_ptr;
}

bool GenArena__remove(GenArena *self, GenArenaIdx idx) {
  void *ptr = GenArena__get(self, idx);
  if (ptr == NULL) {
    return false;
  }

  GenArenaValueDesc *requested_elem_desc_ptr = self->descs + idx.idx_raw;
  requested_elem_desc_ptr->taken = false;

  self->freed_idxs[self->freed_idxs_amount] = idx.idx_raw;
  self->freed_idxs_amount++;

  return true;
}
