#include "alist.h"

AList AList__alloc(size_t init_cap, size_t elem_size) {
  return (AList){
      .events = malloc(init_cap * elem_size),
      .len = 0,
      .cap = init_cap,
  };
}

void AList__free(AList *self) { free(self->events); }

void AList__append(AList *self, void *value) {
  if (self->len == self->cap) {
    size_t new_cap = self->cap * 2;
    self->events = realloc(self->events, self->elem_size * new_cap);
  }
  memcpy(self->events + self->len * self->elem_size, value, self->elem_size);
  self->len++;
}

void AList__clear(AList *self) { self->len = 0; }
