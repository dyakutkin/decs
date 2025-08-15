#include "alist.h"
#include <stdlib.h>
#include <string.h>

void _ArrayList_init(ArrayList(void) * self, size_t elem_size,
                     size_t init_cap) {
  self->cap = init_cap;
  self->len = 0;
  self->elem_size = elem_size;
  self->data = malloc(init_cap * elem_size);
}

void _ArrayList_append(ArrayList(void) * self, void *element) {
  if (self->len == self->cap) {
    size_t new_cap = self->cap * 2;
    self->data = realloc(self->data, self->elem_size * new_cap);
  }
  memcpy((char *)self->data + self->len * self->elem_size, element,
         self->elem_size);
  self->len++;
}

void _ArrayList_free(ArrayList(void) * self) { free(self->data); }

void _ArrayList_clear(ArrayList(void) * self) {
  _ArrayList_free(self);
  _ArrayList_init(self, self->elem_size, self->cap);
}

void _ArrayList_trim_back(ArrayList(void) * self) {
  if (self->len == 0) {
    return;
  }

  self->data = realloc(self->data, self->elem_size * (self->len - 1));
  self->len--;
}
