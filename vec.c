#include "vec.h"

ArrayList ArrayList__new(size_t elem_size, size_t init_cap) {
  ArrayList vec = {
      .elem_size = elem_size,
      .elements = (void **)malloc(init_cap * elem_size),
      .len = 0,
      .capacity = init_cap,
  };
  return vec;
}

void ArrayList__append(ArrayList *self, void *elem) {
  if (self->len == self->capacity) {
    self->capacity = self->capacity * 2;
    self->elements =
        (void **)realloc(self->elements, self->elem_size * self->capacity);
  }
  self->elements[self->len] = elem;
  self->len++;
}

void *ArrayList__get(ArrayList *self, size_t idx) {
  if (idx > self->len) {
    return NULL;
  }
  return self->elements[idx];
}

void ArrayList__remove(ArrayList *self, size_t idx) {
  void **elements = (void **)malloc(self->capacity * self->elem_size);
  size_t cursor = 0;
  for (size_t i = 0; i < self->len; i++) {
    if (i == idx) {
      continue;
    }
    elements[cursor] = self->elements[i];
    cursor++;
  }
  free(self->elements);
  self->elements = elements;
  self->len = cursor;
}

void ArrayList__free(ArrayList *self) { free(self->elements); }
