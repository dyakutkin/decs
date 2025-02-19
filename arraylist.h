#pragma once

#include "stdlib.h"
#include <stdio.h>

typedef struct {
  size_t elem_size;
  void *elements;
  size_t len;
  size_t capacity;
} ArrayList;

ArrayList ArrayList__new(size_t elem_size, size_t init_cap);
void ArrayList__append(ArrayList *self, void *elem);
void *ArrayList__get(ArrayList *self, size_t idx);
void ArrayList__remove(ArrayList *self, size_t idx);
void ArrayList__free(ArrayList *self);
