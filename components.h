#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  bool is_set;
} Component;

bool Component__is_set(void *c);

typedef struct {
  Component _base;
  char *name;
} PersonComponent;

typedef struct {
  Component _base;
  int32_t x;
  int32_t y;
} PositionComponent;

typedef struct {
  Component _base;
} PlayerComponent;
