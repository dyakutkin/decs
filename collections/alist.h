#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct {
  void *events;
  size_t elem_size;
  size_t len;
  size_t cap;
} AList;

AList AList__alloc(size_t init_cap, size_t elem_size);
void AList__free(AList *self);
void AList__append(AList *self, void *value);
void AList__clear(AList *self);
